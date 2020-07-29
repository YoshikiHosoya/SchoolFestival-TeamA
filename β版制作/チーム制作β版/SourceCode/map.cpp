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

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CMap::MAP					CMap::m_MapNum			= MAP_1;					// �}�b�v�ԍ�
CMap::WAVE					CMap::m_WaveNum			= WAVE_1;					// �E�F�[�u�ԍ�
CMap::EDITOR				CMap::m_Editor			= EDITOR_MAP;				// �}�b�v�G�f�B�^�[
int							CMap::m_ArrangmentModel = ARRANGEMENT_MODEL_MAP;	// �z�u���郂�f���̎��

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
/* ----- �}�b�v(�����z�u) ----- */
// �}�b�v
char *CMap::m_MapFileName[MAP_MAX] =
{
	{ "data/Load/Map/testMap.txt" },
	{ "data/Load/Map/testMap.txt" },
};
// �G
char *CMap::m_EnemyFileName[MAP_MAX] =
{
	{ "data/Load/Enemy/Enemy_Map_01.txt" },
	{ "data/Load/Enemy/Enemy_Map_02.txt" },
};
// �ߗ�
char *CMap::m_PrisonerFileName[MAP_MAX] =
{
	{ "data/Load/Prisoner/Prisoner_Map_01.txt" },
	{ "data/Load/Prisoner/Prisoner_Map_02.txt" },
};
// ��Q��
char *CMap::m_ObstacleFileName[MAP_MAX] =
{
	{ "data/Load/Obstacle/Obstacle_Map_01.txt" },
	{ "data/Load/Obstacle/Obstacle_Map_02.txt" },
};
// ���
char *CMap::m_PlayerTankFileName[MAP_MAX] =
{
	{ "data/Load/PlayerTank/PlayerTank_Map_01.txt" },
	{ "data/Load/PlayerTank/PlayerTank_Map_02.txt" },
};
// �퓬�@
char *CMap::m_BattlePlaneFileName[MAP_MAX] =
{
	{ "data/Load/BattlePlane/BattlePlane_Map_01.txt" },
	{ "data/Load/BattlePlane/BattlePlane_Map_02.txt" },
};
// �w���R�v�^�[
char *CMap::m_HelicopterFileName[MAP_MAX] =
{
	{ "data/Load/Helicopter/Helicopter_Map_01.txt" },
	{ "data/Load/Helicopter/Helicopter_Map_02.txt" },
};

/* ----- �E�F�[�u ----- */
// �G
char *CMap::m_EnemyWaveFileName[WAVE_MAX] =
{
	{ "data/Load/Enemy/Enemy_Wave_01.txt" },
	{ "data/Load/Enemy/Enemy_Wave_02.txt" },
	{ "data/Load/Enemy/Enemy_Wave_03.txt" },
};
// �ߗ�
char *CMap::m_PrisonerWaveFileName[WAVE_MAX] =
{
	{ "data/Load/Prisoner/Prisoner_Wave_01.txt" },
	{ "data/Load/Prisoner/Prisoner_Wave_02.txt" },
	{ "data/Load/Prisoner/Prisoner_Wave_03.txt" },
};
// ���
char *CMap::m_PlayerTankWaveFileName[WAVE_MAX] =
{
	{ "data/Load/PlayerTank/PlayerTank_Wave_01.txt" },
	{ "data/Load/PlayerTank/PlayerTank_Wave_02.txt" },
	{ "data/Load/PlayerTank/PlayerTank_Wave_03.txt" },
};
// �퓬�@
char *CMap::m_BattlePlaneWaveFileName[WAVE_MAX] =
{
	{ "data/Load/BattlePlane/BattlePlane_Wave_01.txt" },
	{ "data/Load/BattlePlane/BattlePlane_Wave_02.txt" },
	{ "data/Load/BattlePlane/BattlePlane_Wave_03.txt" },
};
// �w���R�v�^�[
char *CMap::m_HelicopterWaveFileName[WAVE_MAX] =
{
	{ "data/Load/Helicopter/Helicopter_Wave_01.txt" },
	{ "data/Load/Helicopter/Helicopter_Wave_02.txt" },
	{ "data/Load/Helicopter/Helicopter_Wave_03.txt" },
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
	m_pModel.clear();
	m_pEnemy.clear();
	m_pPrisoner.clear();
	m_pObstacle.clear();
	m_pPlayerTank.clear();
	m_pBattlePlane.clear();
	m_pHelicopter.clear();
	m_nOldSelect = 0;
	m_nWaveID = 0;
	m_WavePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
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
void CMap::ArrangementModelLoad(EDITOR Editor, int ModelType)
{
	// �t�@�C���|�C���g
	FILE *pFile = nullptr;
	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	D3DXVECTOR3 size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �傫��
	int nLife = 0;										// �̗�
	int nType = 0;										// ���
	char *cFileName = nullptr;			// �t�@�C����

	// �e���f���t�@�C���̃t�@�C�����J��
	switch (Editor)
	{
	case CMap::EDITOR_MAP:
		pFile = fopen(ArrangementModelFileName(ModelType), "r");
		break;
	}

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
				fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

				// MODELSET��������
				if (strcmp(cHeadText, "MODELSET") == 0)
				{
					// END_MODELSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_MODELSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

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
						// LIFE��������
						else if (strcmp(cHeadText, "LIFE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nLife);		// ��r�p�e�L�X�g��TYPE����
						}
						// SIZE��������
						else if (strcmp(cHeadText, "SIZE") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f ", &cDie, &cDie, &size.x, &size.y, &size.z);		// ��r�p�e�L�X�g��TYPE����
						}
						else if (strcmp(cHeadText, "END_MODELSET") == 0)
						{
							// �����̂Ƃ�
							if (Editor == EDITOR_PLATOON)
							{
								// �E�F�[�u�̈ʒu���Z
								pos += m_aWaveInfo[m_nWaveID].pos;
							}
							// �z�u���郂�f���̐���
							ArrangementModelCreate(ModelType, nType, pos, nLife, size);
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
		LoadFailureMessage(ModelType);
	}
}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̃Z�[�u
//
// =====================================================================================================================================================================
void CMap::ArrangementModelSave(int ModelType)
{
	// �t�@�C���|�C���g
	FILE	*pFile = nullptr;

	// �}�b�v���f���ȊO�̂Ƃ�
	if (ModelType != ARRANGEMENT_MODEL_MAP)
	{
		// �e���f���t�@�C���̃t�@�C�����J��
		switch (m_Editor)
		{
		case CMap::EDITOR_MAP:
			pFile = fopen(ArrangementModelFileName(ModelType), "w");
			break;

		case CMap::EDITOR_WAVE:
			pFile = fopen(WaveFileName(ModelType), "w");
			break;
		}

		// �J���Ă���Ƃ�
		if (pFile != NULL)
		{
			// �Z�[�u���郂�f���̃w�b�_�[
			SaveModelHeader(pFile, ModelType);

			fprintf(pFile, "SCRIPT\n\n");

			for (unsigned int nCntModel = 0; nCntModel < GetMaxArrangementModel(ModelType); nCntModel++)
			{
				if (GetArrangementModel(ModelType, nCntModel))
				{
					fprintf(pFile, "MODELSET									# %d\n", nCntModel);

					// �Z�[�u���郂�f���̏��
					SaveModelContents(pFile, ModelType, nCntModel);

					fprintf(pFile, "END_MODELSET\n\n");
				}
			}
			fprintf(pFile, "END_SCRIPT\n");

			// �ǂݍ��ݐ������̌��ʕ\��
			LoadSuccessMessage(ModelType);

			// �t�@�C�������
			fclose(pFile);
		}
		else
		{
			// �ǂݍ��ݎ��s���̌x���\��
			LoadFailureMessage(ModelType);
		}
	}
}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̐���
//
// =====================================================================================================================================================================
void CMap::ArrangementModelCreate(int ModelType, int nType, D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 size)
{
	switch (ModelType)
	{
	/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		// �I�u�W�F�N�g�̐���
		m_pModel.emplace_back(CModel::CreateSceneManagement(CModel::MAP_MODEL, nType));
		// �ʒu�̐ݒ�
		m_pModel[m_pModel.size() - 1]->SetPosition(pos);
		break;

	/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// �I�u�W�F�N�g�̐���
		m_pEnemy.emplace_back(CEnemy::Create());
		// �ʒu�̐ݒ�
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		// �̗͂̐ݒ�
		m_pEnemy[m_pEnemy.size() - 1]->SetLife(nLife);
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
		// �̗͂̐ݒ�
		m_pObstacle[m_pObstacle.size() - 1]->SetLife(nLife);
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
// �z�u���郂�f���t�@�C����(�����z�u)
//
// =====================================================================================================================================================================
char * CMap::ArrangementModelFileName(int ModelType)
{
	char *cFileName = nullptr;			// �t�@�C����

	switch (ModelType)
	{
	/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		cFileName = m_MapFileName[m_MapNum];
		break;

	/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		cFileName = m_EnemyFileName[m_MapNum];
		break;

	/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		cFileName = m_PrisonerFileName[m_MapNum];
		break;

	/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		cFileName = m_ObstacleFileName[m_MapNum];
		break;

	/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		cFileName = m_PlayerTankFileName[m_MapNum];
		break;

	/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		cFileName = m_BattlePlaneFileName[m_MapNum];
		break;

	/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		cFileName = m_HelicopterFileName[m_MapNum];
		break;
	}
	return cFileName;
}

// =====================================================================================================================================================================
//
// �e�E�F�[�u�t�@�C����
//
// =====================================================================================================================================================================
char * CMap::WaveFileName(int ModelType)
{
	char *cFileName = nullptr;			// �t�@�C����

	switch (ModelType)
	{
		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		cFileName = m_EnemyWaveFileName[m_WaveNum];
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		cFileName = m_PrisonerWaveFileName[m_WaveNum];
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		cFileName = m_PlayerTankWaveFileName[m_WaveNum];
		break;

		/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		cFileName = m_BattlePlaneWaveFileName[m_WaveNum];
		break;

		/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		cFileName = m_HelicopterWaveFileName[m_WaveNum];
		break;
	}
	return cFileName;
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
			// �}�b�v�G�f�B�^�[
			m_Editor = EDITOR_MAP;

			// �I�u�W�F�N�g�ԍ��̑I��
			ImGui::InputInt("nowMapNum", &nNowMapSelect, 1, 20, 0);

			// �͈͐���
			if (nNowMapSelect <= 0)
			{
				nNowMapSelect = 0;
			}
			else if (nNowMapSelect >= MAP_MAX)
			{
				// �Ō�̔ԍ��ɂ���
				nNowMapSelect = MAP_MAX - 1;
			}

			// �I�������}�b�v�ԍ����
			m_MapNum = (MAP)nNowMapSelect;

			ImGui::EndTabItem();
		}
		// �E�F�[�u�G�f�B�^�[
		if (ImGui::BeginTabItem("WaveEditor"))
		{
			// �E�F�[�u�G�f�B�^�[
			m_Editor = EDITOR_WAVE;

			// �I�u�W�F�N�g�ԍ��̑I��
			ImGui::InputInt("nowWaveNum", &nNowMapSelect, 1, 20, 0);

			// �͈͐���
			if (nNowMapSelect <= 0)
			{
				nNowMapSelect = 0;
			}
			else if (nNowMapSelect >= WAVE_MAX)
			{
				// �Ō�̔ԍ��ɂ���
				nNowMapSelect = WAVE_MAX - 1;
			}

			// �I�������}�b�v�ԍ����
			m_WaveNum = (WAVE)nNowMapSelect;

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

	for (int nCnt = 0; nCnt < ARRANGEMENT_MODEL_MAX; nCnt++)
	{
		// �}�b�v�Ŕz�u���郂�f���̃��[�h
		ArrangementModelLoad(EDITOR_MAP, nCnt);
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

	// �t�@�C���|�C���g
	FILE *pFile				= nullptr;
	char *cFileName			= nullptr;							// �t�@�C����
	int nWaveID				= 0;								// �E�F�[�u�̏o���ԍ�
	int nFrame				= 0;								// �t���[��
	D3DXVECTOR3 pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	int nPlatoonType		= 0;								// �����̎��
	char cReadText[128];										// �����Ƃ��ēǂݎ��
	char cHeadText[128];										// ��r�p
	char cDie[128];												// �s�v�ȕ���

	for (int nCnt = 0; nCnt < ARRANGEMENT_MODEL_MAX; nCnt++)
	{
		// �}�b�v���f���Ə�Q���ȊO�̂Ƃ�
		if (nCnt != ARRANGEMENT_MODEL_MAP && nCnt != ARRANGEMENT_MODEL_OBSTACLE)
		{
			// �e���f���t�@�C���̃t�@�C�����J��
			pFile = fopen(WaveFileName(nCnt), "r");

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
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// WAVESET��������
						if (strcmp(cHeadText, "WAVESET") == 0)
						{
							// END_WAVESET������܂Ń��[�v
							while (strcmp(cHeadText, "END_WAVESET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
								sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

								// POS��������
								if (strcmp(cHeadText, "POS") == 0)
								{
									sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
								}
								// FRAME��������
								else if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nFrame);				// ��r�p�e�L�X�g��FRAME����
								}
								// PLATOONTYPE��������
								else if (strcmp(cHeadText, "PLATOONTYPE") == 0)
								{
									sscanf(cReadText, "%s %s %d ", &cDie, &cDie, &nPlatoonType);		// ��r�p�e�L�X�g��PLATOONTYPE����
								}
								else if (strcmp(cHeadText, "END_WAVESET") == 0)
								{
									// Wave��txt���ۑ�
									m_aWaveInfo[nWaveID].pos			= pos;
									m_aWaveInfo[nWaveID].nFrame			= nFrame;
									// �J�E���g�A�b�v
									nWaveID++;
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
				LoadFailureMessage(nCnt);
			}
		}
	}
}

// =====================================================================================================================================================================
//
// �E�F�[�u�̐���
//
// =====================================================================================================================================================================
void CMap::WaveCreate(WAVE WaveNum, int ModelType, int &frame)
{
	// �E�F�[�u�ԍ�
	m_WaveNum = WaveNum;

	if (m_aWaveInfo[m_nWaveID].nFrame == frame)
	{
		// �����̃��[�h
		ArrangementModelLoad(EDITOR_PLATOON, ModelType);

		// �J�E���g�A�b�v
		m_nWaveID++;

		// ������
		frame = 0;
	}
}

// =====================================================================================================================================================================
//
// ���f���̍ő吔�擾
//
// =====================================================================================================================================================================
int CMap::GetMaxModel()
{
	if (!m_pModel.empty())
	{
		return m_pModel.size();
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
	if (!m_pModel.empty())
	{
		return m_pModel[nCnt]->GetMesh();
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
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �}�b�v���f���̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	��\n");
		fprintf(pFile, "#	[ 1 ]	��\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �G�̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	���m\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �ߗ��̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	�ߗ�\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ��Q���̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	��\n");
		fprintf(pFile, "#	[ 1 ]	�M\n");
		fprintf(pFile, "#	[ 2 ]	��\n");
		fprintf(pFile, "#	[ 3 ]	����\n");
		fprintf(pFile, "#	[ 4 ]	�y�X\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ��Ԃ̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �퓬�@�̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	�퓬�@\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;

		/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �w���R�v�^�[�̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	�w���R�v�^�[\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		break;
	}
}

// =====================================================================================================================================================================
//
// �Z�[�u���郂�f���̏��
//
// =====================================================================================================================================================================
void CMap::SaveModelContents(FILE *pFile, int ModelType, int nCnt)
{
	switch (ModelType)
	{
		/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCnt]->GetType()*/);
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pEnemy[nCnt]->GetPosition().x, m_pEnemy[nCnt]->GetPosition().y, m_pEnemy[nCnt]->GetPosition().z);
		fprintf(pFile, "	LIFE	= %d\n", m_pEnemy[nCnt]->GetLife());
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPrisoner[nCnt]->GetPosition().x, m_pPrisoner[nCnt]->GetPosition().y, m_pPrisoner[nCnt]->GetPosition().z);
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, "	TYPE	= %d\n", m_pObstacle[nCnt]->GetModelCount());
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pObstacle[nCnt]->GetPosition().x, m_pObstacle[nCnt]->GetPosition().y, m_pObstacle[nCnt]->GetPosition().z);
		fprintf(pFile, "	LIFE	= %d\n", m_pObstacle[nCnt]->GetLife());
		fprintf(pFile, "	SIZE	= %.0f %.0f %.0f\n", m_pObstacle[nCnt]->GetSize().x, m_pObstacle[nCnt]->GetSize().y, m_pObstacle[nCnt]->GetSize().z);
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pPlayerTank[nCnt]->GetPosition().x, m_pPlayerTank[nCnt]->GetPosition().y, m_pPlayerTank[nCnt]->GetPosition().z);
		break;

		/* --- �퓬�@ --- */
	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pBattlePlane[nCnt]->GetPosition().x, m_pBattlePlane[nCnt]->GetPosition().y, m_pBattlePlane[nCnt]->GetPosition().z);
		break;

		/* --- �w���R�v�^�[ --- */
	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", m_pHelicopter[nCnt]->GetPosition().x, m_pHelicopter[nCnt]->GetPosition().y, m_pHelicopter[nCnt]->GetPosition().z);
		break;
	}
}

// =====================================================================================================================================================================
//
// �Z�[�u����E�F�[�u�̏��
//
// =====================================================================================================================================================================
void CMap::SaveWaveContents(FILE * pFile, int ModelType, int nCnt)
{
	fprintf(pFile, "	POS				= %.0f %.0f %.0f\n", m_WavePos.x, m_WavePos.y, m_WavePos.z);
	fprintf(pFile, "	FRAME			= %d\n", 0);
	fprintf(pFile, "	PLATOONTYPE		= %d\n", 0);
}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̍ő吔�擾
//
// =====================================================================================================================================================================
unsigned int CMap::GetMaxArrangementModel(int ModelType)
{
	switch (ModelType)
	{
		/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		return m_pModel.size();
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
void * CMap::GetArrangementModel(int ModelType, int nCnt)
{
	switch (ModelType)
	{
		/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		return m_pModel[nCnt];
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
			ArrangementModelSave(nCnt);
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
		for (int nCnt = 0; nCnt < ARRANGEMENT_MODEL_MAX; nCnt++)
		{
			// �}�b�v���f���Ə�Q���ȊO�̂Ƃ�
			if (nCnt != ARRANGEMENT_MODEL_MAP && nCnt != ARRANGEMENT_MODEL_OBSTACLE)
			{
				// �}�b�v�Ŕz�u���郂�f���̃��[�h
				ArrangementModelLoad(EDITOR_MAP, nCnt);
			}
		}
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
		// ��Q��
		for (unsigned int nCnt = 0; nCnt < m_pObstacle.size(); nCnt++)
		{
			m_pObstacle[nCnt]->Rerease();
			m_pObstacle[nCnt] = nullptr;
			//m_pObstacle.erase(m_pObstacle.begin() + nCnt);
		}
		// �G
		for (unsigned int nCnt = 0; nCnt < m_pEnemy.size(); nCnt++)
		{
			m_pEnemy[nCnt]->Rerease();
			m_pEnemy[nCnt] = nullptr;
			//m_pEnemy.erase(m_pEnemy.begin() + nCnt);
		}
		// �ߗ�
		for (unsigned int nCnt = 0; nCnt < m_pPrisoner.size(); nCnt++)
		{
			m_pPrisoner[nCnt]->Rerease();
			m_pPrisoner[nCnt] = nullptr;
			//m_pPrisoner.erase(m_pPrisoner.begin() + nCnt);
		}
		// ���
		for (unsigned int nCnt = 0; nCnt < m_pPlayerTank.size(); nCnt++)
		{
			m_pPlayerTank[nCnt]->Rerease();
			m_pPlayerTank[nCnt] = nullptr;
			//m_pPlayerTank.erase(m_pPlayerTank.begin() + nCnt);
		}
		// �퓬�@
		for (unsigned int nCnt = 0; nCnt < m_pBattlePlane.size(); nCnt++)
		{
			m_pBattlePlane[nCnt]->Rerease();
			m_pBattlePlane[nCnt] = nullptr;
			//m_pBattlePlane.erase(m_pBattlePlane.begin() + nCnt);
		}
		// �w���R�v�^�[
		for (unsigned int nCnt = 0; nCnt < m_pHelicopter.size(); nCnt++)
		{
			m_pHelicopter[nCnt]->Rerease();
			m_pHelicopter[nCnt] = nullptr;
			//m_pHelicopter.erase(m_pHelicopter.begin() + nCnt);
		}
		// �S�Ă̗v�f�̍폜
		m_pObstacle.clear();
		m_pEnemy.clear();
		m_pPrisoner.clear();
		m_pPlayerTank.clear();
		m_pBattlePlane.clear();
		m_pHelicopter.clear();
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
// �I�����Ă��郂�f���̈ʒu�̎擾
//
// =====================================================================================================================================================================
D3DXVECTOR3 CMap::GetArrangementModelPos(int nNowSelect)
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
void CMap::SetArrangementModelPos(D3DXVECTOR3 pos, int nNowSelect)
{
	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// �G
		m_pEnemy[nNowSelect]->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// �ߗ�
		m_pPrisoner[nNowSelect]->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// ��Q��
		m_pObstacle[nNowSelect]->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
		break;

	case CMap::ARRANGEMENT_MODEL_TANK:
		// ���
		m_pPlayerTank[nNowSelect]->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
		break;

	case CMap::ARRANGEMENT_MODEL_BATTLEPLANE:
		// �퓬�@
		m_pBattlePlane[nNowSelect]->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
		break;

	case CMap::ARRANGEMENT_MODEL_HELICOPTER:
		// �w���R�v�^�[
		m_pHelicopter[nNowSelect]->SetPosition(D3DXVECTOR3(pos.x, pos.y, pos.z));
		break;
	}
}

// =====================================================================================================================================================================
//
// �I�����Ă��郂�f���̐F�𔼓����ɂ���t���O�̐ݒ�
//
// =====================================================================================================================================================================
void CMap::SetArrangementModelColorChangeFlag(bool bFlag, int nNowSelect)
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
		// �}�b�v�G�f�B�^�̂Ƃ��̂�
		if (m_Editor == EDITOR_MAP)
		{
			// ��Q��
			if (ImGui::BeginTabItem("Obstacle"))
			{
				// �z�u���郂�f��(��Q��)
				m_ArrangmentModel = ARRANGEMENT_MODEL_OBSTACLE;

				// ��Q���̐ݒu
				MapModelSet();
				ImGui::EndTabItem();
			}
		}
		// �ߗ�
		if (ImGui::BeginTabItem("Prisoner"))
		{
			// �z�u���郂�f��(�ߗ�)
			m_ArrangmentModel = ARRANGEMENT_MODEL_PRISONER;

			// �ߗ��̐ݒu
			MapModelSet();
			ImGui::EndTabItem();
		}
		// �G
		if (ImGui::BeginTabItem("Enemy"))
		{
			// �z�u���郂�f��(�G)
			m_ArrangmentModel = ARRANGEMENT_MODEL_ENEMY;

			// �G�̐ݒu
			MapModelSet();
			ImGui::EndTabItem();
		}
		// ���
		if (ImGui::BeginTabItem("Tank"))
		{
			// �z�u���郂�f��(���)
			m_ArrangmentModel = ARRANGEMENT_MODEL_TANK;

			// ��Ԃ̐ݒu
			MapModelSet();
			ImGui::EndTabItem();
		}
		// �퓬�@
		if (ImGui::BeginTabItem("BattlePlane"))
		{
			// �z�u���郂�f��(�퓬�@)
			m_ArrangmentModel = ARRANGEMENT_MODEL_BATTLEPLANE;

			// �퓬�@�̐ݒu
			MapModelSet();
			ImGui::EndTabItem();
		}
		// �w��
		if (ImGui::BeginTabItem("Helicopter"))
		{
			// �z�u���郂�f��(�w��)
			m_ArrangmentModel = ARRANGEMENT_MODEL_HELICOPTER;

			// �w���̐ݒu
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

	static int nObstacleType = 0;		// ��Q���̎��
	static int nNowSelect = -1;			// ���ݑI�����Ă���ԍ�

	// �I�u�W�F�N�g�ԍ��̑I��
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// �͈͐���
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)GetMaxArrangementModel(m_ArrangmentModel))
	{
		nNowSelect = (int)GetMaxArrangementModel(m_ArrangmentModel);
	}
	// �I�����Ă��郂�f������������Ă���Ƃ�
	else if (nNowSelect >= 0 || nNowSelect <= (int)GetMaxArrangementModel(m_ArrangmentModel))
	{
		// �R���{�{�b�N�X
		ComboBoxAll(nNowSelect);

		// NULL�`�F�b�N
		if (GetArrangementModel(m_ArrangmentModel, nNowSelect))
		{
			// ���ݒn
			int x = (int)GetArrangementModelPos(nNowSelect).x,
				y = (int)GetArrangementModelPos(nNowSelect).y,
				z = (int)GetArrangementModelPos(nNowSelect).z;

			// �I�u�W�F�N�g�̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// �I�����Ă��郂�f���̈ʒu�̐ݒ�
			SetArrangementModelPos(D3DXVECTOR3((float)x, (float)y, (float)z), nNowSelect);

			// �I�����Ă��郂�f���𒍎��_�̖ړI�n�ɐݒ�
			SetSelectMapModelPosRDest(GetArrangementModelPos(nNowSelect));

			// �O��I�����Ă������̂ƈႤ�Ƃ�
			if (m_nOldSelect != nNowSelect)
			{
				// �z�u����Ă��郂�f���̂�
				if ((int)GetMaxArrangementModel(m_ArrangmentModel) > m_nOldSelect)
				{
					// �F�ύX����
					SetArrangementModelColorChangeFlag(false, nNowSelect);
				}
			}
			else
			{
				// �F�ύX�t���O���I�����đI�����Ă����Q���𔼓�����
				SetArrangementModelColorChangeFlag(true, nNowSelect);
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
		ArrangementModelSave(m_ArrangmentModel);
	}

	// �z�u�������f����S�ăZ�[�u����{�^��
	AllSaveButton();

	// �}�b�v�G�f�B�^�[�̂Ƃ�
	if (m_Editor == EDITOR_MAP)
	{
		// �z�u�������f����S�ă��[�h����{�^��
		AllLoadButton();
	}

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
	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		//static int nEnemyType = 0;		// �ߗ��̎��
		//if (EnemyComboBox(nEnemyType))
		//{
		//	// NULL�`�F�b�N
		//	if (m_pEnemy[nNowSelect])
		//	{
		//		// �G�̎�ނ̎擾
		//		CModel::ENEMY_TYPE EnemyType = (CModel::OBSTACLE_TYPE)m_pEnemy[nNowSelect]->GetModelCount();

		//		// �O��ƈႤ�Ƃ�
		//		if (EnemyType != nEnemyType)
		//		{
		//			// ��ޑ��
		//			EnemyType = (CModel::ENEMY_TYPE)nEnemyType;
		//			// �G�̃^�C�v�̐ݒ�
		//			m_pEnemy[nNowSelect]->SetModelConut(EnemyType);
		//		}
		//	}
		//}
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		//static int nPrisonerType = 0;		// �ߗ��̎��
		// �R���{�{�b�N�X
		//if (PrisonerComboBox(nPrisonerType))
		//{
		//	// NULL�`�F�b�N
		//	if (m_pPrisoner[nNowSelect])
		//	{
		//		// �ߗ��̎�ނ̎擾
		//		CModel::PRISONER_TYPE PrisonerType = (CModel::OBSTACLE_TYPE)m_pPrisoner[nNowSelect]->GetModelCount();

		//		// �O��ƈႤ�Ƃ�
		//		if (PrisonerType != nPrisonerType)
		//		{
		//			// ��ޑ��
		//			PrisonerType = (CModel::PRISONER_TYPE)nPrisonerType;
		//			// �G�̃^�C�v�̐ݒ�
		//			m_pPrisoner[nNowSelect]->SetModelConut(PrisonerType);
		//		}
		//	}
		//}

		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		static int nObstacleType = 0;		// ��Q���̎��
		// �R���{�{�b�N�X
		if (ObstacleComboBox(nObstacleType))
		{
			// NULL�`�F�b�N
			if (m_pObstacle[nNowSelect])
			{
				// ��Q���̎�ނ̎擾
				CModel::OBSTACLE_TYPE ObstacleType = (CModel::OBSTACLE_TYPE)m_pObstacle[nNowSelect]->GetModelCount();

				// �O��ƈႤ�Ƃ�
				if (ObstacleType != nObstacleType)
				{
					// ��ޑ��
					ObstacleType = (CModel::OBSTACLE_TYPE)nObstacleType;
					// ��Q���̃^�C�v�̐ݒ�
					m_pObstacle[nNowSelect]->SetModelConut(ObstacleType);
				}
			}
		}
		break;
	}
}

// =====================================================================================================================================================================
//
// ��Q���̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
bool CMap::ObstacleComboBox(int &nType)
{
	bool bSelect = false;	// �I��

#ifdef _DEBUG

	// �t�@�C�����i�[�p
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < CModel::OBSTACLE_TYPE_MAX; nCnt++)
	{
		//�z��ɒǉ�
		aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::OBSTACLE_MODEL, nCnt));
	}

	// �R���{�{�b�N�X
	if (ImGui::BeginCombo("Type", aFileName[nType].data()))
	{
		for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
		{
			//�I��ԍ��������Ă邩�ǂ���
			bool is_selected = (aFileName[nType] == aFileName[nCnt]);

			//�I�����ꂽ���̏���
			if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
			{
				//���݂̑I�����ڐݒ�
				nType = nCnt;
				bSelect = true;
			}
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
#endif
	return bSelect;
}

// =====================================================================================================================================================================
//
// �G�̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
bool CMap::EnemyComboBox(int & nType)
{
	bool bSelect = false;	// �I��

#ifdef _DEBUG

	//// �t�@�C�����i�[�p
	//std::vector<std::string > aFileName = {};

	////for
	//for (int nCnt = 0; nCnt < CModel::ENEMY_TYPE_MAX; nCnt++)
	//{
	//	//�z��ɒǉ�
	//	aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::ENEMY_MODEL, nCnt));
	//}

	//// �R���{�{�b�N�X
	//if (ImGui::BeginCombo("Type", aFileName[nType].data()))
	//{
	//	for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
	//	{
	//		//�I��ԍ��������Ă邩�ǂ���
	//		bool is_selected = (aFileName[nType] == aFileName[nCnt]);

	//		//�I�����ꂽ���̏���
	//		if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
	//		{
	//			//���݂̑I�����ڐݒ�
	//			nType = nCnt;
	//			bSelect = true;
	//		}
	//		if (is_selected)
	//		{
	//			ImGui::SetItemDefaultFocus();
	//		}
	//	}
	//	ImGui::EndCombo();
	//}
#endif
	return bSelect;
}

// =====================================================================================================================================================================
//
// �ߗ��̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
bool CMap::PrisonerComboBox(int & nType)
{
	bool bSelect = false;	// �I��

#ifdef _DEBUG

							//// �t�@�C�����i�[�p
							//std::vector<std::string > aFileName = {};

							////for
							//for (int nCnt = 0; nCnt < CModel::ENEMY_TYPE_MAX; nCnt++)
							//{
							//	//�z��ɒǉ�
							//	aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::ENEMY_MODEL, nCnt));
							//}

							//// �R���{�{�b�N�X
							//if (ImGui::BeginCombo("Type", aFileName[nType].data()))
							//{
							//	for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
							//	{
							//		//�I��ԍ��������Ă邩�ǂ���
							//		bool is_selected = (aFileName[nType] == aFileName[nCnt]);

							//		//�I�����ꂽ���̏���
							//		if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
							//		{
							//			//���݂̑I�����ڐݒ�
							//			nType = nCnt;
							//			bSelect = true;
							//		}
							//		if (is_selected)
							//		{
							//			ImGui::SetItemDefaultFocus();
							//		}
							//	}
							//	ImGui::EndCombo();
							//}
#endif
	return bSelect;}

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