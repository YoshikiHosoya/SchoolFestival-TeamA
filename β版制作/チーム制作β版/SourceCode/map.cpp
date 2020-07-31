// =====================================================================================================================================================================
//
// �}�b�v�̏��� [map.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "main.h"			// �C���N���[�h�t�@�C��
#include "map.h"
#include "debugproc.h"
#include "enemy.h"
#include "model.h"
#include <stdio.h>
#include "Obstacle.h"
#include "prisoner.h"
#include "playertank.h"
#include "battleplane.h"
#include "helicopter.h"
#include "Player.h"
#include "BaseMode.h"
#include "item.h"
#include "Boss.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CMap::MAP					CMap::m_MapNum				= MAP_TUTORIAL;				// �}�b�v�ԍ�
CMap::WAVE					CMap::m_WaveNum				= WAVE_1;					// �E�F�[�u�ԍ�
CMap::ARRANGEMENT_MODEL		CMap::m_ArrangmentModel		= ARRANGEMENT_MODEL_MAP;	// �z�u���郂�f���̎��
CMap::WAVE_INFO				CMap::m_aWaveInfo[WAVE_MAX] = {};						// �E�F�[�u�̏��

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
/* ----- �}�b�v(�����z�u) ----- */
// �}�b�v
char *CMap::m_MapModelFileName[MAP_MAX] =
{
	{ "data/Load/Map/MAP_Tutorial.txt" },
	{ "data/Load/Map/Map_1_1.txt" },
	{ "data/Load/Map/Map_1_2.txt" },
	{ "data/Load/Map/Map_1_3.txt" },
	{ "data/Load/Map/Map_1_BOSS.txt" },

};

/* ----- �E�F�[�u ----- */
char *CMap::m_WaveFileName[WAVE_MAX] =
{
	{ "data/Load/Wave/Wave_01.txt" },
	{ "data/Load/Wave/Wave_02.txt" },
	{ "data/Load/Wave/Wave_03.txt" },
};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TranslucentColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))		//������
#define ButtonSpace					(250)									// �{�^���̊Ԋu

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CMap::CMap()
{
	// ������
	m_pMapModel.clear();
	m_pEnemy.clear();
	m_pPrisoner.clear();
	m_pObstacle.clear();
	m_pPlayerTank.clear();
	m_pBattlePlane.clear();
	m_pHelicopter.clear();
	m_pVehicle.clear();
	m_nOldSelect = 0;
	m_WavePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_ModelPosOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CMap::~CMap()
{
}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̃��[�h
//
// =====================================================================================================================================================================
void CMap::MapModelLoad()
{
	FILE			*pFile			= nullptr;							// �t�@�C���̃|�C���^
	char			cReadText[128];										// �����Ƃ��ēǂݎ��
	char			cHeadText[128];										// ��r�p
	char			cDie[128];											// �s�v�ȕ���
	D3DXVECTOR3		pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	int				nType			= 0;								// ���
	char			*cFileName		= nullptr;							// �t�@�C����
	int				nModelType		= -1;								// ���f���̎��

	// �t�@�C�����J��
	pFile = fopen(m_MapModelFileName[m_MapNum], "r");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		// SCRIPT������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������
		}

		// SCRIPT��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPT������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				char cEndSetText[32];			// END_SET

				if (strcmp(cHeadText, "MAPSET") == 0)
				{
					strcpy(cEndSetText, "END_MAPSET");
					nModelType = ARRANGEMENT_MODEL_MAP;
				}
				else if (strcmp(cHeadText, "ENEMYSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_ENEMYSET");
					nModelType = ARRANGEMENT_MODEL_ENEMY;
				}
				else if (strcmp(cHeadText, "PRISONERSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_PRISONERSET");
					nModelType = ARRANGEMENT_MODEL_PRISONER;
				}
				else if (strcmp(cHeadText, "OBSTACLESET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_OBSTACLESET");
					nModelType = ARRANGEMENT_MODEL_OBSTACLE;
				}
				else if (strcmp(cHeadText, "TANKSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_TANKSET");
					nModelType = ARRANGEMENT_MODEL_TANK;
				}
				else if (strcmp(cHeadText, "BATTLEPLANESET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BATTLEPLANESET");
					nModelType = ARRANGEMENT_MODEL_BATTLEPLANE;
				}
				else if (strcmp(cHeadText, "HELICOPTERSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_HELICOPTERSET");
					nModelType = ARRANGEMENT_MODEL_HELICOPTER;
				}
				else if (strcmp(cHeadText, "BOSSSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BOSSSET");
					nModelType = ARRANGEMENT_MODEL_BOSS;
				}

				if (nModelType >= 0)
				{
					// END_MODELSET������܂Ń��[�v
					while (strcmp(cHeadText, cEndSetText) != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						// TYPE��������
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nType);		// ��r�p�e�L�X�g��TYPE����
						}
						// POS��������
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
						}
						else if (strcmp(cHeadText, cEndSetText) == 0)
						{
							// �z�u���郂�f���̐���
							MapModelCreate(nModelType, nType, pos);
							nModelType = -1;
						}
					}
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// �ǂݍ��ݎ��s���̌x���\��
		LoadFailureMessage(nModelType);
	}
}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̃Z�[�u
//
// =====================================================================================================================================================================
void CMap::MapModelSave()
{
	int nNum = 0;

	// �t�@�C���|�C���g
	FILE	*pFile = nullptr;

	// �t�@�C�����J��
	pFile = fopen(m_MapModelFileName[m_MapNum], "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �}�b�v�̏����z�u���\n");
		fprintf(pFile, COMMENT02);

		fprintf(pFile, "SCRIPT\n");
		fprintf(pFile, NEWLINE);

		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
		{
			// �Z�[�u���郂�f���̃w�b�_�[
			SaveModelHeader(pFile, nModelType);

			// �e���f���̎�ޕ���
			for (unsigned int nCntModel = 0; nCntModel < GetMaxMapModel(nModelType); nCntModel++)
			{
				if (GetMapModel(nModelType, nCntModel))
				{
					// �Z�[�u���郂�f���̏��
					SaveModelContents(pFile, nModelType, nCntModel, nNum);

					nNum++;
				}
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
		{
			// �ǂݍ��ݐ������̌��ʕ\��
			LoadSuccessMessage(nModelType);
		}

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// �ǂݍ��ݎ��s���̌x���\��
		//LoadFailureMessage(ModelType);
	}
}

//// =====================================================================================================================================================================
////
//// �E�F�[�u�̃Z�[�u
////
//// =====================================================================================================================================================================
//void CMap::WaveSave()
//{
//	int nNum = 0;
//
//	// �t�@�C���|�C���g
//	FILE	*pFile = nullptr;
//
//	// �t�@�C�����J��
//	pFile = fopen(m_WaveFileName[m_WaveNum], "w");
//
//	// �J���Ă���Ƃ�
//	if (pFile != NULL)
//	{
//		fprintf(pFile, COMMENT02);
//		fprintf(pFile, "// �E�F�[�u�̔z�u���\n");
//		fprintf(pFile, COMMENT02);
//
//		fprintf(pFile, "SCRIPT\n");
//		fprintf(pFile, NEWLINE);
//		fprintf(pFile, "	EVENTPOS		= %.0f %.0f %.0f\n", m_aWaveInfo[m_WaveNum].EventPos.x, m_aWaveInfo[m_WaveNum].EventPos.y, m_aWaveInfo[m_WaveNum].EventPos.z);
//		fprintf(pFile, NEWLINE);
//
//		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
//		{
//			if (nModelType == ARRANGEMENT_MODEL_ENEMY || nModelType == ARRANGEMENT_MODEL_PRISONER)
//			{
//				// �Z�[�u���郂�f���̃w�b�_�[
//				SaveModelHeader(pFile, nModelType);
//
//				// �e���f���̎�ޕ���
//				for (unsigned int nCntModel = 0; nCntModel < GetMaxMapModel(nModelType); nCntModel++)
//				{
//					if (GetMapModel(nModelType, nCntModel))
//					{
//						// �Z�[�u���郂�f���̏��
//						//SaveWaveContents(pFile, nModelType, nCntModel, nNum);
//
//						nNum++;
//					}
//				}
//			}
//		}
//		fprintf(pFile, "END_SCRIPT\n");
//
//		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
//		{
//			// �ǂݍ��ݐ������̌��ʕ\��
//			LoadSuccessMessage(nModelType);
//		}
//
//		// �t�@�C�������
//		fclose(pFile);
//	}
//	else
//	{
//		// �ǂݍ��ݎ��s���̌x���\��
//		//LoadFailureMessage(ModelType);
//	}
//}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̐���
//
// =====================================================================================================================================================================
void CMap::MapModelCreate(int ModelType, int nType, D3DXVECTOR3 pos)
{
	switch (ModelType)
	{
	/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		// �I�u�W�F�N�g�̐���
		m_pMapModel.emplace_back(CModel::CreateSceneManagement(CModel::MODEL_TYPE::MAP_MODEL, nType));
		// �ʒu�̐ݒ�
		m_pMapModel[m_pMapModel.size() - 1]->SetPosition(pos);
		break;

	/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// �I�u�W�F�N�g�̐���
		m_pEnemy.emplace_back(CEnemy::Create());
		// �ʒu�̐ݒ�
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		break;

	/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// �I�u�W�F�N�g�̐���
		m_pPrisoner.emplace_back(CPrisoner::Create());
		// �ʒu�̐ݒ�
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPosition(pos);
		// ��ނ̐ݒ�
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerType((CPrisoner::PRISONER_ITEM_DROPTYPE)nType);
		break;

	/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// �I�u�W�F�N�g�̐���
		m_pObstacle.emplace_back(CObstacle::Create());
		// ��Q����ނ̐ݒ�
		m_pObstacle[m_pObstacle.size() - 1]->SetModelConut(nType);
		// �ʒu�̐ݒ�
		m_pObstacle[m_pObstacle.size() - 1]->SetPosition(pos);
		// �����蔻��̑傫���̐ݒ�
		m_pObstacle[m_pObstacle.size() - 1]->SetCollisionSize((CObstacle::OBSTACLE_TYPE)nType);
		break;

	/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		// �I�u�W�F�N�g�̐���
		m_pPlayerTank.emplace_back(CPlayertank::Create());
		// �ʒu�̐ݒ�
		m_pPlayerTank[m_pPlayerTank.size() - 1]->SetPosition(pos);
		break;

	/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		//// �I�u�W�F�N�g�̐���
		//m_pBattlePlane.emplace_back(CBattlePlane::Create());
		//// �ʒu�̐ݒ�
		//m_pBattlePlane[m_pBattlePlane.size() - 1]->SetPosition(pos);
		break;

	/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		//// �I�u�W�F�N�g�̐���
		//m_pHelicopter.emplace_back(CHelicopter::Create());
		//// �ʒu�̐ݒ�
		//m_pHelicopter[m_pHelicopter.size() - 1]->SetPosition(pos);
		//// ��ނ̐ݒ�
		//m_pHelicopter[m_pHelicopter.size() - 1]->SetVehicleType((CVehicle::VEHICLE_TYPE)nType);
		break;

		/* --- �{�X --- */
	case CMap::ARRANGEMENT_MODEL_BOSS:
		// �I�u�W�F�N�g�̐���
		m_pEnemy.emplace_back(CBoss::Create());
		// �ʒu�̐ݒ�
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		break;
	}
}

// =====================================================================================================================================================================
//
// �ǂݍ��ݎ��s���̌x���\��
//
// =====================================================================================================================================================================
void CMap::LoadFailureMessage(int ModelType)
{
	switch (ModelType)
	{
		/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		MessageBox(NULL, "�}�b�v���f���̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		MessageBox(NULL, "�G�̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		MessageBox(NULL, "�ߗ��̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		MessageBox(NULL, "��Q���̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		MessageBox(NULL, "��Ԃ̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
		break;

		/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		MessageBox(NULL, "�퓬�@�̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
		break;

		/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		MessageBox(NULL, "�w���R�v�^�[�̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
		break;
	}
}

// =====================================================================================================================================================================
//
// �ǂݍ��ݐ������̌��ʕ\��
//
// =====================================================================================================================================================================
void CMap::LoadSuccessMessage(int ModelType)
{
	switch (ModelType)
	{
		/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		MessageBox(NULL, "�}�b�v���f���̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		MessageBox(NULL, "�G�̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		MessageBox(NULL, "�ߗ��̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		MessageBox(NULL, "��Q���̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		MessageBox(NULL, "��Ԃ̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		MessageBox(NULL, "�퓬�@�̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
		break;

		/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		MessageBox(NULL, "�w���R�v�^�[�̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
		break;
	}
}

// =====================================================================================================================================================================
//
// �}�b�v�̐���
//
// =====================================================================================================================================================================
CMap *CMap::MapCreate()
{
	// �ϐ�
	CMap *pMap;

	// �������̊m��
	pMap = new CMap();

	return pMap;
}

// =====================================================================================================================================================================
//
// �}�b�v�̍X�V
//
// =====================================================================================================================================================================
void CMap::MapUpdate()
{
#ifdef _DEBUG

	static int nNowMapSelect = 0;		// ���ݑI�����Ă���}�b�v�ԍ�

	// �I�u�W�F�N�g�E�B���h�E
	ImGui::Begin("MapModel", nullptr, ImGuiWindowFlags_MenuBar);

	//Tab
	if (ImGui::BeginTabBar("EditorType"))
	{
		// �}�b�v�G�f�B�^�[
		if (ImGui::BeginTabItem("MapEditor"))
		{
			MapComboBox(nNowMapSelect, nNowMapSelect);

			//// �I�u�W�F�N�g�ԍ��̑I��
			//ImGui::InputInt("nowMapNum", &nNowMapSelect, 1, 20, 0);

			//// �͈͐���
			//if (nNowMapSelect <= 0)
			//{
			//	nNowMapSelect = 0;
			//}
			//else if (nNowMapSelect >= MAP_MAX)
			//{
			//	// �Ō�̔ԍ��ɂ���
			//	nNowMapSelect = MAP_MAX - 1;
			//}

			//// �I�������}�b�v�ԍ����
			//m_MapNum = (MAP)nNowMapSelect;

			////m_pMapModel[nNowMapSelect]->SetModelConut(nNowMapSelect);

			ImGui::EndTabItem();
		}
		//TabEnd
		ImGui::EndTabBar();
	}

	// �}�b�v���f���̃^�u
	MapModelTab();

	ImGui::End();
#endif
}

// =====================================================================================================================================================================
//
// �}�b�v�̃��[�h
//
// =====================================================================================================================================================================
void CMap::MapLoad(MAP MapNum)
{
	// ���݂̃}�b�v�ԍ�
	m_MapNum = MapNum;

	// �}�b�v�Ŕz�u���郂�f���̃��[�h
	MapModelLoad();

	if (MapNum == CMap::MAP_1_BOSS)
	{
		CManager::GetRenderer()->GetCamera()->SetCameraStopMove(true);
		CManager::GetRenderer()->GetCamera()->SetPosR(D3DXVECTOR3(0.0f, 200.0f, 0.0f));

	}
	if (MapNum == CMap::MAP_TUTORIAL)
	{
		CManager::GetRenderer()->GetCamera()->SetCameraStopMove(true);
		CManager::GetRenderer()->GetCamera()->SetPosR(D3DXVECTOR3(0.0f, 200.0f, 0.0f));

	}

}

// =====================================================================================================================================================================
//
// �E�F�[�u�̃��[�h
//
// =====================================================================================================================================================================
void CMap::WaveLoad(WAVE WaveNum)
{
	// ���݂̃E�F�[�u�ԍ�
	m_WaveNum = WaveNum;

	FILE		*pFile				= nullptr;							// �t�@�C���|�C���^
	char		*cFileName			= nullptr;							// �t�@�C����
	int			nFrame				= 0;								// �t���[��
	D3DXVECTOR3	pos					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	char		cReadText[128];											// �����Ƃ��ēǂݎ��
	char		cHeadText[128];											// ��r�p
	char		cDie[128];												// �s�v�ȕ���
	int			nModelType			= -1;								// ���f���̎��
	int			nType				= 0;								// ���
	int			nEvent				= 0;								//bool�ɕϊ�����悤�̊i�[
	WAVE_PARAM	*pParam				= nullptr;							// �E�F�[�u�̃p�����[�^�ۑ��p

	// �t�@�C�����J��
	pFile = fopen(m_MapModelFileName[WaveNum], "r");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		// SCRIPT������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������
		}

		// SCRIPT��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPT������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);

				// �C�x���g���N����ʒu��ۑ�
				if (strcmp(cHeadText, "EVENTPOS") == 0)
				{
					sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
						&m_aWaveInfo[WaveNum].EventPos.x, &m_aWaveInfo[WaveNum].EventPos.y, &m_aWaveInfo[WaveNum].EventPos.z);
				}

				char cEndSetText[32];			// END_SET

				// �ǂݍ��݃��f��
				if (strcmp(cHeadText, "ENEMYSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_ENEMYSET");
					nModelType = ARRANGEMENT_MODEL_ENEMY;
				}
				else if (strcmp(cHeadText, "PRISONERSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_PRISONERSET");
					nModelType = ARRANGEMENT_MODEL_PRISONER;
				}

				if (nModelType >= 0)
				{
					pParam = new WAVE_PARAM;

					// END_�Z�ZSET������܂Ń��[�v
					while (strcmp(cHeadText, cEndSetText) != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);
						sscanf(cReadText, "%s", &cHeadText);

						// TYPE��������
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nType);
						}
						// POS��������
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);
						}
						// FRAME��������
						else if (strcmp(cHeadText, "FRAME") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nFrame);
						}
						// FRAME��������
						else if (strcmp(cHeadText, "EVENT") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nEvent);
						}
						else if (strcmp(cHeadText, cEndSetText) == 0)
						{
							pParam->pos = pos;
							pParam->nType = nType;
							pParam->nFrame = nFrame;
							pParam->bEvent = nEvent ? true : false;

							if (nModelType == ARRANGEMENT_MODEL_ENEMY)
							{
								m_aWaveInfo[WaveNum].EnemyWaveInfo.emplace_back(pParam);
							}
							else if (nModelType == ARRANGEMENT_MODEL_PRISONER)
							{
								m_aWaveInfo[WaveNum].PrisonerWaveInfo.emplace_back(pParam);
							}
							nModelType = -1;
						}
					}
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// �ǂݍ��ݎ��s���̌x���\��
		LoadFailureMessage(nModelType);
	}
}

// =====================================================================================================================================================================
//
// ���f���̍ő吔�擾
//
// =====================================================================================================================================================================
int CMap::GetMaxModel()
{
	if (!m_pMapModel.empty())
	{
		return m_pMapModel.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// �G�̍ő吔�擾
//
// =====================================================================================================================================================================
int CMap::GetMaxEnemy()
{
	if (!m_pEnemy.empty())
	{
		return m_pEnemy.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// �ߗ��̍ő吔�擾
//
// =====================================================================================================================================================================
int CMap::GetMaxPrisoner()
{
	if (!m_pPrisoner.empty())
	{
		return m_pPrisoner.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// ��Q���̍ő吔�擾
//
// =====================================================================================================================================================================
int CMap::GetMaxObstacle()
{
	if (!m_pObstacle.empty())
	{
		return m_pObstacle.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// ��Ԃ̍ő吔�擾
//
// =====================================================================================================================================================================
int CMap::GetMaxPlayerTank()
{
	if (!m_pPlayerTank.empty())
	{
		return m_pPlayerTank.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// �퓬�@�̍ő吔�擾
//
// =====================================================================================================================================================================
int CMap::GetMaxBattlePlane()
{
	if (!m_pBattlePlane.empty())
	{
		return m_pBattlePlane.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// �w���̍ő吔�擾
//
// =====================================================================================================================================================================
int CMap::GetMaxHelicopter()
{
	if (!m_pHelicopter.empty())
	{
		return m_pHelicopter.size();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// ���b�V���̎擾
//
// =====================================================================================================================================================================
LPD3DXMESH CMap::GetMesh(int nCnt)
{
	if (!m_pMapModel.empty())
	{
		return m_pMapModel[nCnt]->GetMesh();
	}
	return 0;
}

// =====================================================================================================================================================================
//
// �Z�[�u���郂�f���̃w�b�_�[
//
// =====================================================================================================================================================================
void CMap::SaveModelHeader(FILE * pFile, int ModelType)
{
	switch (ModelType)
	{
		/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �}�b�v���f���̔z�u���\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// MAPTYPE���\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	��\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �G�̔z�u���\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// ENEMYTYPE���\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	���m\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �ߗ��̔z�u���\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// PRISONERTYPE���\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	�m��h���b�v����ߗ�\n");
		fprintf(pFile, "//	[ 1 ]	�͈̓h���b�v����ߗ�\n");
		fprintf(pFile, "//	[ 2 ]	�����_���h���b�v����ߗ�\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// ��Q���̔z�u���\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// OBSTACLETYPE���\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	��\n");
		fprintf(pFile, "//	[ 1 ]	�M\n");
		fprintf(pFile, "//	[ 2 ]	��\n");
		fprintf(pFile, "//	[ 3 ]	����\n");
		fprintf(pFile, "//	[ 4 ]	�y�X\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// ��Ԃ̔z�u���\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �퓬�@�̔z�u���\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �w���R�v�^�[�̔z�u���\n");
		fprintf(pFile, COMMENT02);
		break;
	}
}

// =====================================================================================================================================================================
//
// �Z�[�u���郂�f���̏��
//
// =====================================================================================================================================================================
void CMap::SaveModelContents(FILE *pFile, int ModelType, int nCnt, int nNum)
{
	switch (ModelType)
	{
		/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		fprintf(pFile, "MAPSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", m_pMapModel[nCnt]->GetModelCount());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pMapModel[nCnt]->GetPosition().x, m_pMapModel[nCnt]->GetPosition().y, m_pMapModel[nCnt]->GetPosition().z);
		fprintf(pFile, "END_MAPSET\n\n");
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "ENEMYSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pEnemy[nCnt]->GetPosition().x, m_pEnemy[nCnt]->GetPosition().y, m_pEnemy[nCnt]->GetPosition().z);
		fprintf(pFile, "END_ENEMYSET\n\n");
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "PRISONERSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", m_pPrisoner[nCnt]->GetPrisonerDropType());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPrisoner[nCnt]->GetPosition().x, m_pPrisoner[nCnt]->GetPosition().y, m_pPrisoner[nCnt]->GetPosition().z);
		fprintf(pFile, "END_PRISONERSET\n\n");
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, "OBSTACLESET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", m_pObstacle[nCnt]->GetModelCount());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pObstacle[nCnt]->GetPosition().x, m_pObstacle[nCnt]->GetPosition().y, m_pObstacle[nCnt]->GetPosition().z);
		fprintf(pFile, "END_OBSTACLESET\n\n");
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, "TANKSET									# %d\n", nNum);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPlayerTank[nCnt]->GetPosition().x, m_pPlayerTank[nCnt]->GetPosition().y, m_pPlayerTank[nCnt]->GetPosition().z);
		fprintf(pFile, "END_TANKSET\n\n");
		break;

		/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		fprintf(pFile, "BATTLEPLANESET									# %d\n", nNum);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pBattlePlane[nCnt]->GetPosition().x, m_pBattlePlane[nCnt]->GetPosition().y, m_pBattlePlane[nCnt]->GetPosition().z);
		fprintf(pFile, "END_BATTLEPLANESET\n\n");
		break;

		/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		fprintf(pFile, "HELICOPTERSET									# %d\n", nNum);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pHelicopter[nCnt]->GetPosition().x, m_pHelicopter[nCnt]->GetPosition().y, m_pHelicopter[nCnt]->GetPosition().z);
		fprintf(pFile, "END_HELICOPTERSET\n\n");
		break;
	}
}

// =====================================================================================================================================================================
//
// �Z�[�u����E�F�[�u�̏��
//
// =====================================================================================================================================================================
void CMap::SaveWaveContents(FILE * pFile, int ModelType, int nType, int nCnt, int nNum)
{
	switch (ModelType)
	{
		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "ENEMYSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pEnemy[nCnt]->GetPosition().x, m_pEnemy[nCnt]->GetPosition().y, m_pEnemy[nCnt]->GetPosition().z);
		fprintf(pFile, "	FRAME	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "	EVENT	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "END_ENEMYSET\n\n");
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "PRISONERSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE	= %d\n", m_pPrisoner[nCnt]->GetPrisonerDropType());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPrisoner[nCnt]->GetPosition().x, m_pPrisoner[nCnt]->GetPosition().y, m_pPrisoner[nCnt]->GetPosition().z);
		fprintf(pFile, "	FRAME	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "END_PRISONERSET\n\n");
		break;
	}
}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̍ő吔�擾
//
// =====================================================================================================================================================================
unsigned int CMap::GetMaxMapModel(int ModelType)
{
	switch (ModelType)
	{
		/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		return m_pMapModel.size();
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		return m_pEnemy.size();
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		return m_pPrisoner.size();
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		return m_pObstacle.size();
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		return m_pPlayerTank.size();
		break;

		/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		return m_pBattlePlane.size();
		break;

		/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		return m_pHelicopter.size();
		break;
	}
	return 0;
}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̃|�C���^
//
// =====================================================================================================================================================================
void * CMap::GetMapModel(int ModelType, int nCnt)
{
	switch (ModelType)
	{
		/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		return m_pMapModel[nCnt];
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		return m_pEnemy[nCnt];
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		return m_pPrisoner[nCnt];
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		return m_pObstacle[nCnt];
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		return m_pPlayerTank[nCnt];
		break;

		/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		return m_pBattlePlane[nCnt];
		break;

		/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		return m_pHelicopter[nCnt];
		break;
	}
	return nullptr;
}

// =====================================================================================================================================================================
//
// �z�u�������f����S�ăZ�[�u����{�^��
//
// =====================================================================================================================================================================
void CMap::AllSaveButton()
{
	// ���s�L�����Z��
	ImGui::SameLine();

	// �Z�[�u
	if (ImGui::Button("AllSave"))
	{
		for (int nCnt = 0; nCnt < ARRANGEMENT_MODEL_MAX; nCnt++)
		{
			// �z�u���郂�f���̃Z�[�u
			MapModelSave();
		}
	}
}

// =====================================================================================================================================================================
//
// �z�u�������f����S�ă��[�h����{�^��
//
// =====================================================================================================================================================================
void CMap::AllLoadButton()
{
	// ���s�L�����Z��
	ImGui::SameLine();

	// �Z�[�u
	if (ImGui::Button("AllLoad"))
	{
		// �}�b�v�Ŕz�u���郂�f���̃��[�h
		MapModelLoad();
	}
}

// =====================================================================================================================================================================
//
// �z�u�������f����S�ăf���[�g����{�^��
//
// =====================================================================================================================================================================
void CMap::AllDeleteButton()
{
	// ���s�L�����Z��
	ImGui::SameLine();

	// �S�ăf���[�g
	if (ImGui::Button("AllDelete"))
	{
		AllDelete();
	}
}

// =====================================================================================================================================================================
//
// �z�u�������f�����f���[�g����{�^��
//
// =====================================================================================================================================================================
void CMap::ModelDeleteButton(int nNowSelect)
{
	// ����
	if (ImGui::Button("Delete"))
	{
		switch (m_ArrangmentModel)
		{
		case CMap::ARRANGEMENT_MODEL_MAP:
			// �G
			m_pMapModel[nNowSelect]->Rerease();
			m_pMapModel[nNowSelect] = nullptr;
			m_pMapModel.erase(m_pMapModel.begin() + nNowSelect);
			break;

		case CMap::ARRANGEMENT_MODEL_ENEMY:
			// �G
			m_pEnemy[nNowSelect]->Rerease();
			m_pEnemy[nNowSelect] = nullptr;
			m_pEnemy.erase(m_pEnemy.begin() + nNowSelect);
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// �ߗ�
			m_pPrisoner[nNowSelect]->Rerease();
			m_pPrisoner[nNowSelect] = nullptr;
			m_pPrisoner.erase(m_pPrisoner.begin() + nNowSelect);
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// ��Q��
			m_pObstacle[nNowSelect]->Rerease();
			m_pObstacle[nNowSelect] = nullptr;
			m_pObstacle.erase(m_pObstacle.begin() + nNowSelect);
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// ���
			m_pPlayerTank[nNowSelect]->Rerease();
			m_pPlayerTank[nNowSelect] = nullptr;
			m_pPlayerTank.erase(m_pPlayerTank.begin() + nNowSelect);
			break;

		case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
			// �퓬�@
			m_pBattlePlane[nNowSelect]->Rerease();
			m_pBattlePlane[nNowSelect] = nullptr;
			m_pBattlePlane.erase(m_pBattlePlane.begin() + nNowSelect);
			break;

		case CMap::ARRANGEMENT_MODEL_HELICOPTER:
			// �w���R�v�^�[
			m_pHelicopter[nNowSelect]->Rerease();
			m_pHelicopter[nNowSelect] = nullptr;
			m_pHelicopter.erase(m_pHelicopter.begin() + nNowSelect);
			break;
		}
	}
}

// =====================================================================================================================================================================
//
// �z�u�������f���𐶐�����{�^��
//
// =====================================================================================================================================================================
void CMap::ModelCreateButton()
{
	// ����
	if (ImGui::Button("Crate"))
	{
		switch (m_ArrangmentModel)
		{
		case CMap::ARRANGEMENT_MODEL_ENEMY:
			// �G
			m_pEnemy.emplace_back(CEnemy::Create());
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// �ߗ�
			m_pPrisoner.emplace_back(CPrisoner::Create());
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// ��Q��
			m_pObstacle.emplace_back(CObstacle::Create());
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// ���
			m_pPlayerTank.emplace_back(CPlayertank::Create());
			break;

		case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
			// �퓬�@
			m_pBattlePlane.emplace_back(CBattlePlane::Create());
			break;

		case CMap::ARRANGEMENT_MODEL_HELICOPTER:
			// �w���R�v�^�[
			m_pHelicopter.emplace_back(CHelicopter::Create());
			break;
		}
	}
}

// =====================================================================================================================================================================
//
// �z�u���Ă��郂�f����S�Ĕj�����鏈��
//
// =====================================================================================================================================================================
void CMap::AllDelete()
{
	// ��Q��
	for (unsigned int nCnt = 0; nCnt < m_pMapModel.size(); nCnt++)
	{
		m_pMapModel[nCnt]->Rerease();
		m_pMapModel[nCnt] = nullptr;
	}
	// ��Q��
	for (unsigned int nCnt = 0; nCnt < m_pObstacle.size(); nCnt++)
	{
		m_pObstacle[nCnt]->Rerease();
		m_pObstacle[nCnt] = nullptr;
	}
	// �G
	for (unsigned int nCnt = 0; nCnt < m_pEnemy.size(); nCnt++)
	{
		m_pEnemy[nCnt]->Rerease();
		m_pEnemy[nCnt] = nullptr;
	}
	// �ߗ�
	for (unsigned int nCnt = 0; nCnt < m_pPrisoner.size(); nCnt++)
	{
		m_pPrisoner[nCnt]->Rerease();
		m_pPrisoner[nCnt] = nullptr;
	}
	// ���
	for (unsigned int nCnt = 0; nCnt < m_pPlayerTank.size(); nCnt++)
	{
		m_pPlayerTank[nCnt]->Rerease();
		m_pPlayerTank[nCnt] = nullptr;
	}
	// �퓬�@
	for (unsigned int nCnt = 0; nCnt < m_pBattlePlane.size(); nCnt++)
	{
		m_pBattlePlane[nCnt]->Rerease();
		m_pBattlePlane[nCnt] = nullptr;
	}
	// �w���R�v�^�[
	for (unsigned int nCnt = 0; nCnt < m_pHelicopter.size(); nCnt++)
	{
		m_pHelicopter[nCnt]->Rerease();
		m_pHelicopter[nCnt] = nullptr;
	}
	// �S�Ă̗v�f�̍폜
	m_pMapModel.clear();
	m_pObstacle.clear();
	m_pEnemy.clear();
	m_pPrisoner.clear();
	m_pPlayerTank.clear();
	m_pBattlePlane.clear();
	m_pHelicopter.clear();
}

// =====================================================================================================================================================================
//
// �I�����Ă��郂�f���̈ʒu�̎擾
//
// =====================================================================================================================================================================
D3DXVECTOR3 CMap::GetMapModelPos(int nNowSelect)
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// �G
		pos = m_pEnemy[nNowSelect]->GetPosition();
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// �ߗ�
		pos = m_pPrisoner[nNowSelect]->GetPosition();
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// ��Q��
		pos = m_pObstacle[nNowSelect]->GetPosition();
		break;

	case CMap::ARRANGEMENT_MODEL_TANK:
		// ���
		pos = m_pPlayerTank[nNowSelect]->GetPosition();
		break;

	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		// �퓬�@
		pos = m_pBattlePlane[nNowSelect]->GetPosition();
		break;

	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		// �w���R�v�^�[
		pos = m_pHelicopter[nNowSelect]->GetPosition();
		break;
	}

	return pos;
}

// =====================================================================================================================================================================
//
// �I�����Ă��郂�f���̈ʒu�̐ݒ�
//
// =====================================================================================================================================================================
void CMap::SetMapModelPos(D3DXVECTOR3 pos, int nNowSelect)
{
	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// �G
		m_pEnemy[nNowSelect]->SetPosition(pos);
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// �ߗ�
		m_pPrisoner[nNowSelect]->SetPosition(pos);
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// ��Q��
		m_pObstacle[nNowSelect]->SetPosition(pos);
		break;

	case CMap::ARRANGEMENT_MODEL_TANK:
		// ���
		m_pPlayerTank[nNowSelect]->SetPosition(pos);
		break;

	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		// �퓬�@
		m_pBattlePlane[nNowSelect]->SetPosition(pos);
		break;

	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		// �w���R�v�^�[
		m_pHelicopter[nNowSelect]->SetPosition(pos);
		break;
	}
}

// =====================================================================================================================================================================
//
// �I�����Ă��郂�f���̐F�𔼓����ɂ���t���O�̐ݒ�
//
// =====================================================================================================================================================================
void CMap::SetMapModelColorChangeFlag(bool bFlag, int nNowSelect)
{
	// �F�ύX�t���O���I�����đI�����Ă����Q���𔼓�����
	if (bFlag)
	{
		switch (m_ArrangmentModel)
		{
		case CMap::ARRANGEMENT_MODEL_ENEMY:
			// �G
			m_pEnemy[nNowSelect]->ChangeColor(true, -TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// �ߗ�
			m_pPrisoner[nNowSelect]->ChangeColor(true, -TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// ��Q��
			m_pObstacle[nNowSelect]->SetColorChangeFlag(true);
			m_pObstacle[nNowSelect]->SetAddColor(-TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// ���
			break;

		case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
			// �퓬�@
			break;

		case CMap::ARRANGEMENT_MODEL_HELICOPTER:
			// �w���R�v�^�[
			break;
		}
	}
	// �F�ύX����
	else
	{
		switch (m_ArrangmentModel)
		{
		case CMap::ARRANGEMENT_MODEL_ENEMY:
			// �G�̈ʒu�̐ݒ�
			m_pEnemy[m_nOldSelect]->ChangeColor(false, ZeroColor);
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// �ߗ�
			m_pPrisoner[m_nOldSelect]->ChangeColor(false, ZeroColor);
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// ��Q��
			m_pObstacle[m_nOldSelect]->SetColorChangeFlag(false);
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// ���
			break;

		case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
			// �퓬�@
			break;

		case CMap::ARRANGEMENT_MODEL_HELICOPTER:
			// �w���R�v�^�[
			break;
		}
	}
}

// =====================================================================================================================================================================
//
// �}�b�v�ɔz�u���郂�f���̃^�u
//
// =====================================================================================================================================================================
void CMap::MapModelTab()
{
	//Tab
	if (ImGui::BeginTabBar("MapModelType"))
	{
		// ��Q���̐ݒu
		if (ImGui::BeginTabItem("Obstacle"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_OBSTACLE;
			MapModelSet();
			ImGui::EndTabItem();
		}
		// �ߗ��̐ݒu
		if (ImGui::BeginTabItem("Prisoner"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_PRISONER;
			MapModelSet();
			ImGui::EndTabItem();
		}
		// �G�̐ݒu
		if (ImGui::BeginTabItem("Enemy"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_ENEMY;
			MapModelSet();
			ImGui::EndTabItem();
		}
		// ��Ԃ̐ݒu
		if (ImGui::BeginTabItem("Tank"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_TANK;
			MapModelSet();
			ImGui::EndTabItem();
		}
		// �퓬�@�̐ݒu
		if (ImGui::BeginTabItem("BattlePlane"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_BATTLEPLANE;
			MapModelSet();
			ImGui::EndTabItem();
		}
		// �w���̐ݒu
		if (ImGui::BeginTabItem("Helicopter"))
		{
			m_ArrangmentModel = ARRANGEMENT_MODEL_HELICOPTER;
			MapModelSet();
			ImGui::EndTabItem();
		}
		//TabEnd
		ImGui::EndTabBar();
	}
}

// =====================================================================================================================================================================
//
// �}�b�v�ɔz�u���郂�f���̐ݒu
//
// =====================================================================================================================================================================
void CMap::MapModelSet()
{
#ifdef _DEBUG

	static int nNowSelect = -1;			// ���ݑI�����Ă���ԍ�
	static int nFrame = 0;
	static bool bEvent = false;

	// �I�u�W�F�N�g�ԍ��̑I��
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// �͈͐���
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)GetMaxMapModel(m_ArrangmentModel))
	{
		nNowSelect = (int)GetMaxMapModel(m_ArrangmentModel);
	}
	// �I�����Ă��郂�f������������Ă���Ƃ�
	else if (nNowSelect >= 0 || nNowSelect <= (int)GetMaxMapModel(m_ArrangmentModel))
	{
		// �R���{�{�b�N�X
		ComboBoxAll(nNowSelect);

		// NULL�`�F�b�N
		if (GetMapModel(m_ArrangmentModel, nNowSelect))
		{
			// ���ݒn
			int x = (int)GetMapModelPos(nNowSelect).x,
				y = (int)GetMapModelPos(nNowSelect).y,
				z = (int)GetMapModelPos(nNowSelect).z;

			// �I�u�W�F�N�g�̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// �I�����Ă��郂�f���̈ʒu�̐ݒ�
			SetMapModelPos(D3DXVECTOR3((float)x, (float)y, (float)z), nNowSelect);

			// ���f���̑O��̈ʒu�ۑ�
			m_ModelPosOld = GetMapModelPos(nNowSelect);

			// �I�����Ă��郂�f���𒍎��_�̖ړI�n�ɐݒ�
			SetSelectMapModelPosRDest(GetMapModelPos(nNowSelect));

			// �O��I�����Ă������̂ƈႤ�Ƃ�
			if (m_nOldSelect != nNowSelect)
			{
				// �z�u����Ă��郂�f���̂�
				if ((int)GetMaxMapModel(m_ArrangmentModel) > m_nOldSelect)
				{
					// �F�ύX����
					SetMapModelColorChangeFlag(false, nNowSelect);
				}
			}
			else
			{
				// �F�ύX�t���O���I�����đI�����Ă����Q���𔼓�����
				SetMapModelColorChangeFlag(true, nNowSelect);
			}
			// �O��I�����Ă�������
			m_nOldSelect = nNowSelect;
		}
	}

	// ���s
	ImGui::Separator();

	// �z�u�������f���𐶐�����{�^��
	ModelCreateButton();

	// ���s�L�����Z��
	ImGui::SameLine();

	// �z�u�������f�����Z�[�u����{�^��
	if (ImGui::Button("Save"))
	{
		// �Z�[�u
		MapModelSave();
	}

	// �z�u�������f����S�ă��[�h����{�^��
	AllLoadButton();

	// ���s�L�����Z��
	ImGui::SameLine(ButtonSpace);

	// �z�u�������f�����f���[�g����{�^��
	ModelDeleteButton(nNowSelect);

	// �z�u�������f����S�ăf���[�g����{�^��
	AllDeleteButton();
#endif
}

// =====================================================================================================================================================================
//
// �S�ẴR���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::ComboBoxAll(int nNowSelect)
{
	static int nSelectType = 0;		// �I��ł�����

	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		//// �G�̎�ޑI��
		//EnemyComboBox(nSelectType, nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// �ߗ��̎�ޑI��
		PrisonerComboBox(nSelectType, nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// ��Q���̎�ޑI��
		ObstacleComboBox(nSelectType, nNowSelect);
		break;
	}
}

// =====================================================================================================================================================================
//
// ��Q���̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::MapComboBox(int & nSelectType, int nNowSelect)
{
	// �t�@�C�����i�[�p
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < CModel::OBSTACLE_TYPE_MAX; nCnt++)
	{
		//�z��ɒǉ�
		aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::MAP_MODEL, nCnt));
	}

	if (CHossoLibrary::ImGui_Combobox(aFileName, "MapType", nSelectType))
	{
		// �}�b�v�̃��[�h
		AllDelete();
		MapLoad((MAP)nSelectType);

		//// NULL�`�F�b�N
		//if (m_pMapModel[nNowSelect])
		//{
		//	// �ߗ��̎�ނ̎擾
		//	int MapType = m_pMapModel[nNowSelect]->GetModelCount();

		//	// �O��ƈႤ�Ƃ�
		//	if (MapType != nSelectType)
		//	{
		//		// ��ޑ��
		//		MapType = nSelectType;
		//		// �G�̃^�C�v�̐ݒ�
		//		m_pMapModel[nNowSelect]->SetModelConut(MapType);
		//	}
		//}
	}
}

// =====================================================================================================================================================================
//
// ��Q���̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::ObstacleComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	// �t�@�C�����i�[�p
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < CModel::OBSTACLE_TYPE_MAX; nCnt++)
	{
		//�z��ɒǉ�
		aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::OBSTACLE_MODEL, nCnt));
	}

	if (CHossoLibrary::ImGui_Combobox(aFileName, "Type", nSelectType))
	{
		// NULL�`�F�b�N
		if (m_pObstacle[nNowSelect])
		{
			// �ߗ��̎�ނ̎擾
			CModel::OBSTACLE_TYPE ObstacleType = (CModel::OBSTACLE_TYPE)m_pObstacle[nNowSelect]->GetModelCount();

			// �O��ƈႤ�Ƃ�
			if (ObstacleType != nSelectType)
			{
				// ��ޑ��
				ObstacleType = (CModel::OBSTACLE_TYPE)nSelectType;
				// �G�̃^�C�v�̐ݒ�
				m_pObstacle[nNowSelect]->SetModelConut(ObstacleType);
			}
		}
	}
#endif
}

// =====================================================================================================================================================================
//
// �G�̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::EnemyComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	//std::vector<std::string > aEnemyType = { "DESIGNATE_ONE", "DESIGNATE_RANGE", "ALL" };

	//if (CHossoLibrary::ImGui_Combobox(aEnemyType, "Type", nSelectType))
	//{
	//	// NULL�`�F�b�N
	//	if (m_pPrisoner[nNowSelect])
	//	{
	//		// �ߗ��̎�ނ̎擾
	//		CPrisoner::PRISONER_ITEM_DROPTYPE PrisonerType = m_pPrisoner[nNowSelect]->GetPrisonerDropType();

	//		// �O��ƈႤ�Ƃ�
	//		if (PrisonerType != nSelectType)
	//		{
	//			// ��ޑ��
	//			PrisonerType = (CPrisoner::PRISONER_ITEM_DROPTYPE)nSelectType;
	//			// �G�̃^�C�v�̐ݒ�
	//			m_pPrisoner[nNowSelect]->SetPrisonerType(PrisonerType);
	//		}
	//	}
	//}
#endif
}

// =====================================================================================================================================================================
//
// �ߗ��̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::PrisonerComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	std::vector<std::string > aPrisonerType = { "DESIGNATE_ONE", "DESIGNATE_RANGE", "ALL" };

	if (CHossoLibrary::ImGui_Combobox(aPrisonerType, "Type", nSelectType))
	{
		// NULL�`�F�b�N
		if (m_pPrisoner[nNowSelect])
		{
			// �ߗ��̎�ނ̎擾
			CPrisoner::PRISONER_ITEM_DROPTYPE PrisonerType = m_pPrisoner[nNowSelect]->GetPrisonerDropType();

			// �O��ƈႤ�Ƃ�
			if (PrisonerType != nSelectType)
			{
				// ��ޑ��
				PrisonerType = (CPrisoner::PRISONER_ITEM_DROPTYPE)nSelectType;
				// �G�̃^�C�v�̐ݒ�
				m_pPrisoner[nNowSelect]->SetPrisonerType(PrisonerType);
			}
		}
	}
#endif
}

// =====================================================================================================================================================================
//
// �I�����Ă��郂�f���𒍎��_�̖ړI�n�ɐݒ�
//
// =====================================================================================================================================================================
void CMap::SetSelectMapModelPosRDest(D3DXVECTOR3 posR)
{
	// �J�����̎擾
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();

	// �����_�̖ړI�n�̐ݒ�
	pCamera->SetCameraPosRDest(posR);
}

// =====================================================================================================================================================================
//
// ���S�t���O�m�F�֐�
//
// =====================================================================================================================================================================
void CMap::UpdateDieFlag()
{
	// �G�l�~�[�̍폜
	for (size_t nCnt = 0; nCnt < m_pEnemy.size(); nCnt++)
	{
		if (m_pEnemy[nCnt]->GetDieFlag())
		{
			// �����_���Ȋm���ŃA�C�e�����h���b�v����
			if (CItem::DropRate())
			{
				//�A�C�e���𐶐�
				CItem::DropCreate(m_pEnemy[nCnt]->GetPosition(),
					CItem::ITEMDROP_WEAPON,
					CItem::ITEMDROP_PATTERN_RANDOM,
					CItem::ITEMTYPE_HEAVYMACHINEGUN);
			}
			m_pEnemy[nCnt]->Rerease();
			m_pEnemy[nCnt] = nullptr;
			m_pEnemy.erase(m_pEnemy.begin() + nCnt);
		}
	}

	// ��Q���̍폜
	for (size_t nCnt = 0; nCnt < m_pObstacle.size(); nCnt++)
	{
		if (m_pObstacle[nCnt]->GetDieFlag())
		{
			m_pObstacle[nCnt]->Rerease();
			m_pObstacle[nCnt] = nullptr;
			m_pObstacle.erase(m_pObstacle.begin() + nCnt);
		}
	}

	// �ߗ��̍폜
	for (size_t nCnt = 0; nCnt < m_pPrisoner.size(); nCnt++)
	{
		if (m_pPrisoner[nCnt]->GetDieFlag())
		{
			m_pPrisoner[nCnt]->Rerease();
			m_pPrisoner[nCnt] = nullptr;
			m_pPrisoner.erase(m_pPrisoner.begin() + nCnt);
		}
	}

	// �v���C���[�p��Ԃ̍폜
	for (size_t nCnt = 0; nCnt < m_pPlayerTank.size(); nCnt++)
	{
		if (m_pPlayerTank[nCnt]->GetDieFlag())
		{
			m_pPlayerTank[nCnt]->Rerease();
			m_pPlayerTank[nCnt] = nullptr;
			m_pPlayerTank.erase(m_pPlayerTank.begin() + nCnt);
		}
	}

	// �퓬�@�̍폜
	for (size_t nCnt = 0; nCnt < m_pBattlePlane.size(); nCnt++)
	{
		if (m_pBattlePlane[nCnt]->GetDieFlag())
		{
			m_pBattlePlane[nCnt]->Rerease();
			m_pBattlePlane[nCnt] = nullptr;
			m_pBattlePlane.erase(m_pBattlePlane.begin() + nCnt);
		}
	}

	// �w���̍폜
	for (size_t nCnt = 0; nCnt < m_pHelicopter.size(); nCnt++)
	{
		if (m_pHelicopter[nCnt]->GetDieFlag())
		{
			m_pHelicopter[nCnt]->Rerease();
			m_pHelicopter[nCnt] = nullptr;
			m_pHelicopter.erase(m_pHelicopter.begin() + nCnt);
		}
	}
}