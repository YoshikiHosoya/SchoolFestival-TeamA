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
#include "Player.h"
#include "BaseMode.h"
#include "item.h"
#include "Boss.h"
#include "scene2D.h"
#include "Boss_One.h"
#include "WeakEnemy.h"
#include "sound.h"
#include "ModelSet.h"
#include "model.h"
// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CMap::MAP					CMap::m_MapNum				= MAP_TUTORIAL;				// �}�b�v�ԍ�
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
	{ "data/Load/Map/Map_2_1.txt" },
	{ "data/Load/Map/Map_2_2.txt" },
	{ "data/Load/Map/Map_2_3.txt" },
	{ "data/Load/Map/Map_2_BOSS.txt" },
};

/* ----- �E�F�[�u ----- */
char *CMap::m_WaveFileName[WAVE_MAX] =
{
	{ "data/Load/Wave/Wave_1_1_1.txt" },
	{ "data/Load/Wave/Wave_1_1_2.txt" },
	{ "data/Load/Wave/Wave_1_2_1.txt" },
	{ "data/Load/Wave/Wave_1_2_2.txt" },
	{ "data/Load/Wave/Wave_1_3_1.txt" },
	{ "data/Load/Wave/Wave_1_3_2.txt" },
	{ "data/Load/Wave/Wave_1_BOSS.txt" },

	{ "data/Load/Wave/Wave_2_1_1.txt" },
	{ "data/Load/Wave/Wave_2_1_2.txt" },
	{ "data/Load/Wave/Wave_2_2_1.txt" },
	{ "data/Load/Wave/Wave_2_2_2.txt" },
	{ "data/Load/Wave/Wave_2_3_1.txt" },
	{ "data/Load/Wave/Wave_2_3_2.txt" },
	{ "data/Load/Wave/Wave_2_BOSS.txt" },

};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TranslucentColor			(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.5f))		// ������
#define ButtonSpace					(250)									// �{�^���̊Ԋu
#define CameraMoveSpeed				(25.0f)									// �J�����̈ړ����x
#define BG_ID						(100)									// �w�i�̔F��ID

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CMap::CMap()
{
	// ������
	m_pMapModel.clear();											// �}�b�v���f��
	m_pEnemy.clear();												// �G
	m_pPrisoner.clear();											// �ߗ�
	m_pObstacle.clear();											// ��Q��
	m_pPlayerTank.clear();											// ���

	m_nOldSelect			= 0;									// �O��I�����Ă�������
	m_WavePos				= ZeroVector3;							// �E�F�[�u�̈ʒu
	m_TransitionPos			= ZeroVector3;							// �J�ڂ���ʒu
	m_CameraPos				= ZeroVector3;							// �J�����̈ʒu
	m_TransitionMapID		= 0;									// ���ɑJ�ڂ��邽�߂̔ԍ�
	m_nBGTexID				= 0;									// �w�i�̃e�N�X�`���ԍ�
	m_bCameraFollowing		= false;								// �J������Ǐ]����t���O
	m_bMapExclusion			= false;								// �}�b�v���f���ȊO�K�p����t���O
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
	D3DXVECTOR3		pos				= ZeroVector3;						// �ʒu
	int				nType			= 0;								// ���
	int				nItemType		= 0;								// �A�C�e���̎��
	char			*cFileName		= nullptr;							// �t�@�C����
	int				nModelType		= -1;								// ���f���̎��
	int				nBGTexID		= 0;								// �w�i�̃e�N�X�`���ԍ�
	char			cReadText[128];										// �����Ƃ��ēǂݎ��
	char			cHeadText[128];										// ��r�p
	char			cDie[128];											// �s�v�ȕ���


	switch (m_MapNum)
	{
	case CMap::MAP_1_1:
		CManager::GetSound()->StopAll();
		CManager::GetSound()->Play(CSound::LABEL_BGM_STAGE_01);
		break;

	case CMap::MAP_2_1:
		CManager::GetSound()->StopAll();
		CManager::GetSound()->Play(CSound::LABEL_BGM_STAGE_02);
		break;


	case CMap::MAP_1_BOSS:
		CManager::GetSound()->StopAll();
		CManager::GetSound()->Play(CSound::LABEL_BGM_STAGE_01_BOSS);
		break;

	case CMap::MAP_2_BOSS:
		CManager::GetSound()->StopAll();
		CManager::GetSound()->Play(CSound::LABEL_BGM_STAGE_02_BOSS);
		break;

	default:
		break;
	}

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

				if (strcmp(cHeadText, "TRANSITION_POS_X") == 0)
				{
					sscanf(cReadText, "%s %s %f", &cDie, &cDie,&m_TransitionPos.x);
				}
				if (strcmp(cHeadText, "TRANSITION_MAP_ID") == 0)
				{
					sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_TransitionMapID);
				}

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
				else if (strcmp(cHeadText, "BOSSSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BOSSSET");
					nModelType = ARRANGEMENT_MODEL_BOSS;
				}
				else if (strcmp(cHeadText, "BGSET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BGSET");
					nModelType = BG_ID;
				}
				else if (strcmp(cHeadText, "BOSSONESET") == 0)
				{
					sprintf(cEndSetText, "%s", "END_BOSSONESET");
					nModelType = ARRANGEMENT_MODEL_BOSS_ONE;
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
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nType);
						}
						// ITEMTYPE��������
						else if (strcmp(cHeadText, "ITEMTYPE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nItemType);
						}
						// POS��������
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);
						}
						// BG_TEX_ID��������
						else if (strcmp(cHeadText, "BG_TEX_ID") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBGTexID);
						}
						else if (strcmp(cHeadText, cEndSetText) == 0)
						{
							if (nModelType < ARRANGEMENT_MODEL_MAX)
							{
								// �z�u���郂�f���̐���
								MapModelCreate(nModelType, nType, pos, nItemType);
							}
							else if (nModelType == BG_ID)
							{
								// �w�i�̐����ƃe�N�X�`���̐ݒ�
								CScene2D *pScene2D = CScene2D::CreateSceneManagement(SCREEN_CENTER_POS, SCREEN_SIZE, CScene::OBJTYPE_BG);
								pScene2D->BindTexture(CTexture::GetTexture(CTexture::TEX_BG_SKY_SUNNY));
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
		MessageBox(NULL, "�ǂݍ��ݎ��s", m_MapModelFileName[m_MapNum], MB_ICONWARNING);
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

		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �J�ڂ��邽�߂̏��\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "TRANSITION_POS_X		= %.0f\n", m_TransitionPos.x);
		fprintf(pFile, "TRANSITION_MAP_ID		= %d\n", m_TransitionMapID);
		fprintf(pFile, NEWLINE);

		for (int nModelType = 0; nModelType < ARRANGEMENT_MODEL_MAX; nModelType++)
		{
			// �Z�[�u���郂�f���̃w�b�_�[
			SaveModelHeader(pFile, nModelType);

			// �e���f���̎�ޕ���
			for (size_t nCntModel = 0; nCntModel < GetMaxMapModel(nModelType); nCntModel++)
			{
				if (GetMapModel(nModelType, nCntModel))
				{
					// �Z�[�u���郂�f���̏��
					SaveModelContents(pFile, nModelType, nCntModel, nNum);

					nNum++;
				}
			}
		}
		// �Z�[�u����w�i�̏��
		SaveBGContents(pFile);

		fprintf(pFile, "END_SCRIPT\n");

		// �ǂݍ��ݐ������̌��ʕ\��
		MessageBox(NULL, "�Z�[�u���܂���", m_MapModelFileName[m_MapNum], MB_OK | MB_ICONINFORMATION);

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// �ǂݍ��ݎ��s���̌x���\��
		MessageBox(NULL, "�ǂݍ��ݎ��s", m_MapModelFileName[m_MapNum], MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̐���
//
// =====================================================================================================================================================================
void CMap::MapModelCreate(int ModelType, int nType, D3DXVECTOR3 pos,int nItemType)
{
	switch (ModelType)
	{
	/* --- �}�b�v --- */
	case CMap::ARRANGEMENT_MODEL_MAP:
		// �I�u�W�F�N�g�̐���
		m_pMapModel.emplace_back(CModel::CreateSceneManagement(CModel::MODEL_TYPE::MAP_MODEL, m_MapNum));
		// �ʒu�̐ݒ�
		m_pMapModel[m_pMapModel.size() - 1]->SetPosition(pos);
		break;

	/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// �I�u�W�F�N�g�̐���
		m_pEnemy.emplace_back(CWeakEnemy::Create((CWeakEnemy::ENEMY_TYPE)nType));
		// �ʒu�̐ݒ�
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		break;

	/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// �I�u�W�F�N�g�̐���
		m_pPrisoner.emplace_back(CPrisoner::Create());
		// �ʒu�̐ݒ�
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPosition(pos);
		// �h���b�v�^�C�v�̐ݒ�
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerType((CPrisoner::PRISONER_ITEM_DROPTYPE)nType);
		// �A�C�e���̎�ނ̐ݒ�
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerItem((CItem::ITEMTYPE)nItemType);

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

		/* --- �{�X --- */
	case CMap::ARRANGEMENT_MODEL_BOSS:
		// �I�u�W�F�N�g�̐���
		m_pEnemy.emplace_back(CBoss::Create());
		// �ʒu�̐ݒ�
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
		break;

		/* --- �{�X1 --- */
	case CMap::ARRANGEMENT_MODEL_BOSS_ONE:
		// �I�u�W�F�N�g�̐���
		m_pEnemy.emplace_back(CBoss_One::Create());
		// �ʒu�̐ݒ�
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
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
	ImGui::Begin("MapEditor", nullptr, ImGuiWindowFlags_MenuBar);

	//Tab
	if (ImGui::BeginTabBar("EditorType"))
	{
		if (ImGui::BeginTabItem("MapEditor"))
		{
			// �}�b�v�̃R���{�{�b�N�X
			MapComboBox(nNowMapSelect, nNowMapSelect);
			// �}�b�v���f���̃^�u
			MapModelTab();
			ImGui::Separator();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("MapModelType"))
		{
			// �}�b�v���f���̕ύX
			MapTypeComboBox();
			ImGui::Separator();
			ImGui::EndTabItem();
		}

		//TabEnd
		ImGui::EndTabBar();
	}

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
	if (MapNum == CMap::MAP_2_BOSS)
	{
		CManager::GetRenderer()->GetCamera()->SetCameraStopMove(true);
		CManager::GetRenderer()->GetCamera()->SetPosR(D3DXVECTOR3(0.0f, 250.0f, 0.0f));

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
void CMap::WaveLoad()
{
	FILE		*pFile				= nullptr;							// �t�@�C���|�C���^
	char		*cFileName			= nullptr;							// �t�@�C����
	int			nFrame				= 0;								// �t���[��
	D3DXVECTOR3	pos					= ZeroVector3;						// �ʒu
	int			nModelType			= -1;								// ���f���̎��
	int			nType				= 0;								// ���
	int			nItemType			= 0;								// �h���b�v����A�C�e���̎��
	int			nEvent				= 0;								// bool�ɕϊ�����悤�̊i�[
	WAVE_PARAM	*pParam				= nullptr;							// �E�F�[�u�̃p�����[�^�ۑ��p
	char		cReadText[128];											// �����Ƃ��ēǂݎ��
	char		cHeadText[128];											// ��r�p
	char		cDie[128];												// �s�v�ȕ���

	for (int nCnt = 0; nCnt < CMap::WAVE::WAVE_MAX; nCnt++)
	{
		// �t�@�C�����J��
		pFile = fopen(m_WaveFileName[nCnt], "r");

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

					// �C�x���g���N����}�b�v�ԍ�
					if (strcmp(cHeadText, "EVENT_BEGIN_MAP") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aWaveInfo[nCnt].EventBeginMapNum);
					}

					// �C�x���g���N����ʒu��ۑ�
					if (strcmp(cHeadText, "EVENTPOS") == 0)
					{
						sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_aWaveInfo[nCnt].EventPos.x);
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
							// ITEMTYPE��������
							else if (strcmp(cHeadText, "ITEMTYPE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nItemType);
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
							// EVENT��������
							else if (strcmp(cHeadText, "EVENT") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nEvent);
							}
							else if (strcmp(cHeadText, cEndSetText) == 0)
							{
								pParam->pos = pos;
								pParam->nType = nType;
								pParam->nItemType = nItemType;
								pParam->nFrame = nFrame;
								pParam->bEvent = nEvent ? true : false;

								// ���ۑ�
								if (nModelType == ARRANGEMENT_MODEL_ENEMY)
								{
									m_aWaveInfo[nCnt].EnemyWaveInfo.emplace_back(pParam);
								}
								else if (nModelType == ARRANGEMENT_MODEL_PRISONER)
								{
									m_aWaveInfo[nCnt].PrisonerWaveInfo.emplace_back(pParam);
								}
								nModelType = -1;
							}
						}
					}
				}
			}

			//�p�����[�^���[�h
			std::cout << "Load WaveInfo - " << nCnt << m_WaveFileName[nCnt] << NEWLINE;

			// �t�@�C�������
			fclose(pFile);
		}
		else
		{
			// �ǂݍ��ݎ��s���̌x���\��
			MessageBox(NULL, "�ǂݍ��ݎ��s", m_WaveFileName[nCnt], MB_ICONWARNING);
		}
	}
}
// =====================================================================================================================================================================
//
// �E�F�[�u���J��
//
// =====================================================================================================================================================================
void CMap::WaveUnLoad()
{
	if (m_aWaveInfo)
	{
		for (int nCntWave = 0; nCntWave < CMap::WAVE::WAVE_MAX; nCntWave++)
		{
			if (!m_aWaveInfo[nCntWave].EnemyWaveInfo.empty())
			{
				for (size_t nCnt = 0; nCnt < m_aWaveInfo[nCntWave].EnemyWaveInfo.size(); nCnt++)
				{
					delete m_aWaveInfo[nCntWave].EnemyWaveInfo[nCnt];
					m_aWaveInfo[nCntWave].EnemyWaveInfo[nCnt] = nullptr;
				}
			}
			if (!m_aWaveInfo[nCntWave].PrisonerWaveInfo.empty())
			{
				for (size_t nCnt = 0; nCnt < m_aWaveInfo[nCntWave].PrisonerWaveInfo.size(); nCnt++)
				{
					delete m_aWaveInfo[nCntWave].PrisonerWaveInfo[nCnt];
					m_aWaveInfo[nCntWave].PrisonerWaveInfo[nCnt] = nullptr;
				}
			}
			m_aWaveInfo[nCntWave].EnemyWaveInfo.clear();
			m_aWaveInfo[nCntWave].PrisonerWaveInfo.clear();
		}
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
		fprintf(pFile, "// �}�b�v�̎�� ( TYPE )\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	�`���[�g���A��\n");
		fprintf(pFile, "//	[ 1 ]	�X�e�[�W1_1\n");
		fprintf(pFile, "//	[ 2 ]	�X�e�[�W1_2\n");
		fprintf(pFile, "//	[ 3 ]	�X�e�[�W1_3\n");
		fprintf(pFile, "//	[ 4 ]	�X�e�[�W1_BOSS\n");
		fprintf(pFile, "//	[ 5 ]	�X�e�[�W2_1\n");
		fprintf(pFile, "//	[ 6 ]	�X�e�[�W2_2\n");
		fprintf(pFile, "//	[ 7 ]	�X�e�[�W2_3\n");
		fprintf(pFile, "//	[ 8 ]	�X�e�[�W2_BOSS\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �G�̔z�u���\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �G�̎�� ( TYPE )\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	�ʏ핺�m\n");
		fprintf(pFile, "//	[ 1 ]	���������m\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �ߗ��̔z�u���\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �ߗ��̎�� ( TYPE )\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ 0 ]	�m��h���b�v����ߗ�\n");
		fprintf(pFile, "//	[ 1 ]	�͈̓h���b�v����ߗ�\n");
		fprintf(pFile, "//	[ 2 ]	�����_���h���b�v����ߗ�\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// �ߗ��̎�� ( ITEMTYPE )\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, "//	[ -1 ]	NONE\n");
		fprintf(pFile, "//	[ 0 ]	�w�r�[�}�V���K��\n");
		fprintf(pFile, "//	[ 1 ]	�V���b�g�K��\n");
		fprintf(pFile, "//	[ 2 ]	���[�U�[�K��\n");
		fprintf(pFile, "//	[ 3 ]	���P�b�g�����`���[\n");
		fprintf(pFile, "//	[ 4 ]	�t���C���V���b�g\n");
		fprintf(pFile, "//	[ 5 ]	�N�}\n");
		fprintf(pFile, "//	[ 6 ]	�R�C��\n");
		fprintf(pFile, "//	[ 7 ]	���\n");
		fprintf(pFile, "//	[ 8 ]	���_��\n");
		fprintf(pFile, "//	[ 9 ]	�{������\n");
		fprintf(pFile, "//	[ 10 ]	�G�l���M�[����\n");
		fprintf(pFile, "//	[ 11 ]	�e�򐔑���\n");
		fprintf(pFile, COMMENT01);
		fprintf(pFile, COMMENT02);
		fprintf(pFile, NEWLINE);
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// ��Q���̔z�u���\n");
		fprintf(pFile, COMMENT02);
		fprintf(pFile, "// ��Q���̎�� ( TYPE )\n");
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
		fprintf(pFile, "MAPSET										# %d\n", nNum);
		fprintf(pFile, "	TYPE		= %d\n", m_pMapModel[nCnt]->GetModelCount());
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pMapModel[nCnt]->GetPosition().x, m_pMapModel[nCnt]->GetPosition().y, m_pMapModel[nCnt]->GetPosition().z);
		fprintf(pFile, "END_MAPSET\n\n");
		break;

		/* --- �G --- */
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		fprintf(pFile, "ENEMYSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE		= %d\n", m_pEnemy[nCnt]->GetEnemyType());
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pEnemy[nCnt]->GetPosition().x, m_pEnemy[nCnt]->GetPosition().y, m_pEnemy[nCnt]->GetPosition().z);
		fprintf(pFile, "END_ENEMYSET\n\n");
		break;

		/* --- �ߗ� --- */
	case CMap::ARRANGEMENT_MODEL_PRISONER:
		fprintf(pFile, "PRISONERSET									# %d\n", nNum);
		fprintf(pFile, "	TYPE		= %d\n", m_pPrisoner[nCnt]->GetPrisonerDropType());
		fprintf(pFile, "	ITEMTYPE	= %d\n", m_pPrisoner[nCnt]->GetPrisonerDropItem());
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pPrisoner[nCnt]->GetPosition().x, m_pPrisoner[nCnt]->GetPosition().y, m_pPrisoner[nCnt]->GetPosition().z);
		fprintf(pFile, "END_PRISONERSET\n\n");
		break;

		/* --- ��Q�� --- */
	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		fprintf(pFile, "OBSTACLESET									# %d\n", nNum);
		fprintf(pFile, "	TYPE		= %d\n", m_pObstacle[nCnt]->GetModelCount());
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pObstacle[nCnt]->GetPosition().x, m_pObstacle[nCnt]->GetPosition().y, m_pObstacle[nCnt]->GetPosition().z);
		fprintf(pFile, "END_OBSTACLESET\n\n");
		break;

		/* --- ��� --- */
	case CMap::ARRANGEMENT_MODEL_TANK:
		fprintf(pFile, "TANKSET										# %d\n", nNum);
		fprintf(pFile, "	POS			= %.0f %.0f %.0f\n", m_pPlayerTank[nCnt]->GetPosition().x, m_pPlayerTank[nCnt]->GetPosition().y, m_pPlayerTank[nCnt]->GetPosition().z);
		fprintf(pFile, "END_TANKSET\n\n");
		break;
	}
}

// =====================================================================================================================================================================
//
// �Z�[�u����w�i�̏��
//
// =====================================================================================================================================================================
void CMap::SaveBGContents(FILE * pFile)
{
	fprintf(pFile, COMMENT02);
	fprintf(pFile, "// �w�i�̃e�N�X�`�����\n");
	fprintf(pFile, COMMENT02);
	fprintf(pFile, COMMENT01);
	fprintf(pFile, "//	[ %d ]	��̔w�i ( ���� )\n", CTexture::TEX_BG_SKY_SUNNY);
	fprintf(pFile, "//	[ %d ]	��̔w�i ( �܂� )\n", CTexture::TEX_BG_SKY_CLOUDY);
	fprintf(pFile, "//	[ %d ]	��̔w�i ( �É_ )\n", CTexture::TEX_BG_SKY_DARKCLOUDS);
	fprintf(pFile, COMMENT01);
	fprintf(pFile, COMMENT02);
	fprintf(pFile, "BGSET\n");
	fprintf(pFile, "	BG_TEX_ID			= %d\n", CTexture::TEX_BG_SKY_SUNNY);
	fprintf(pFile, "END_BGSET\n");
	fprintf(pFile, NEWLINE);
}

// =====================================================================================================================================================================
//
// �z�u���郂�f���̍ő吔�擾
//
// =====================================================================================================================================================================
size_t CMap::GetMaxMapModel(int ModelType)
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
	}
	return nullptr;
}

// =====================================================================================================================================================================
//
// �z�u�������f�����f���[�g
//
// =====================================================================================================================================================================
void CMap::ModelDelete(int nNowSelect)
{
	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_MAP:
		// �}�b�v
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
	}
}

// =====================================================================================================================================================================
//
// �z�u�������f���𐶐�����
//
// =====================================================================================================================================================================
void CMap::ModelCreat()
{
	// ����
	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// �G
		m_pEnemy.emplace_back(CWeakEnemy::Create(CWeakEnemy::ENEMY_TYPE::ENEMY_NORMAL));
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
	}
}

// =====================================================================================================================================================================
//
// �z�u���Ă��郂�f����S�Ĕj�����鏈��
//
// =====================================================================================================================================================================
void CMap::AllDelete()
{
	if (!m_bMapExclusion)
	{
		// �}�b�v���f��
		for (size_t nCnt = 0; nCnt < m_pMapModel.size(); nCnt++)
		{
			m_pMapModel[nCnt]->Rerease();
			m_pMapModel[nCnt] = nullptr;
		}
	}
	// ��Q��
	for (size_t nCnt = 0; nCnt < m_pObstacle.size(); nCnt++)
	{
		m_pObstacle[nCnt]->Rerease();
		m_pObstacle[nCnt] = nullptr;
	}
	// �G
	for (size_t nCnt = 0; nCnt < m_pEnemy.size(); nCnt++)
	{
		m_pEnemy[nCnt]->Rerease();
		m_pEnemy[nCnt] = nullptr;
	}

	// �ߗ�
	for (size_t nCnt = 0; nCnt < m_pPrisoner.size(); nCnt++)
	{
		m_pPrisoner[nCnt]->Rerease();
		m_pPrisoner[nCnt] = nullptr;
	}
	// ���
	for (size_t nCnt = 0; nCnt < m_pPlayerTank.size(); nCnt++)
	{
		m_pPlayerTank[nCnt]->Rerease();
		m_pPlayerTank[nCnt] = nullptr;
	}
	// �S�Ă̗v�f�̍폜
	if (!m_bMapExclusion)
	{
		m_pMapModel.clear();
	}
	m_pObstacle.clear();
	m_pEnemy.clear();
	m_pPrisoner.clear();
	m_pPlayerTank.clear();

	m_bMapExclusion = false;
}


// =====================================================================================================================================================================
//
// Wave�̐���
//
// =====================================================================================================================================================================
void CMap::WaveCreate(int nModelType, D3DXVECTOR3 eventpos, WAVE_PARAM * pWaveParam)
{
	if (nModelType == ARRANGEMENT_MODEL_ENEMY)
	{
		// �G
		m_pEnemy.emplace_back(CWeakEnemy::Create(CWeakEnemy::ENEMY_TYPE::ENEMY_NORMAL));
		m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pWaveParam->pos + eventpos);
		m_pEnemy[m_pEnemy.size() - 1]->SetEventFlag(pWaveParam->bEvent);
	}
	else if (nModelType == ARRANGEMENT_MODEL_PRISONER)
	{
		// �ߗ�
		m_pPrisoner.emplace_back(CPrisoner::Create());
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPosition(pWaveParam->pos + eventpos);
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerType((CPrisoner::PRISONER_ITEM_DROPTYPE)pWaveParam->nType);
		m_pPrisoner[m_pPrisoner.size() - 1]->SetPrisonerItem((CItem::ITEMTYPE)pWaveParam->nItemType);
	}
}

// =====================================================================================================================================================================
//
// �}�b�v���\�L
//
// =====================================================================================================================================================================
void CMap::ShowDebugInfo()
{
	CDebugProc::Print_Left("------ MapInfo ----------\n");

	CDebugProc::Print_Left("EnemyNum >> %d\n", m_pEnemy.size());
	CDebugProc::Print_Left("PrisonerNum >> %d\n", m_pPrisoner.size());
}

// =====================================================================================================================================================================
//
// �I�����Ă��郂�f���̈ʒu�̎擾
//
// =====================================================================================================================================================================
D3DXVECTOR3 CMap::GetMapModelPos(int nNowSelect)
{
	D3DXVECTOR3 pos = ZeroVector3;

	if (nNowSelect < 0)
	{
		nNowSelect = 0;
	}

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
			m_pEnemy[nNowSelect]->GetModelSet()->ChangeColor(true, -TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// �ߗ�
			m_pPrisoner[nNowSelect]->GetModelSet()->ChangeColor(true, -TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// ��Q��
			m_pObstacle[nNowSelect]->SetColorChangeFlag(true);
			m_pObstacle[nNowSelect]->SetAddColor(-TranslucentColor);
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// ���
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
			m_pEnemy[m_nOldSelect]->GetModelSet()->ChangeColor(false, ZeroColor);
			break;

		case CMap::ARRANGEMENT_MODEL_PRISONER:
			// �ߗ�
			m_pPrisoner[m_nOldSelect]->GetModelSet()->ChangeColor(false, ZeroColor);
			break;

		case CMap::ARRANGEMENT_MODEL_OBSTACLE:
			// ��Q��
			m_pObstacle[m_nOldSelect]->SetColorChangeFlag(false);
			break;

		case CMap::ARRANGEMENT_MODEL_TANK:
			// ���
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
	if (ImGui::BeginTabBar("MapType"))
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
	// �J������Ǐ]����t���O�̐؂�ւ�
	ImGui::Checkbox("CameraFollowing", &m_bCameraFollowing);

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

			if (m_bCameraFollowing)
			{
				// �I�����Ă��郂�f���𒍎��_�̖ړI�n�ɐݒ�
				SetSelectMapModelPosRDest(GetMapModelPos(nNowSelect));
				// �J�����̌��ݒn
				m_CameraPos = GetMapModelPos(nNowSelect);
			}

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

	if (!m_bCameraFollowing)
	{
		// ���f����Ǐ]�����J�����݂̂̈ړ�
		SetSelectMapModelPosRDest(m_CameraPos);
	}

	// ���s
	ImGui::Separator();

	if (ImGui::Button("Crate"))
	{
		//���f���𐶐�����
		ModelCreat();

		// �V���������������f�������ݑI�����Ă��郂�f���Ɠ����ʒu�ɐ�������
		SetMapModelPos(GetMapModelPos(nNowSelect), (int)GetMaxMapModel(m_ArrangmentModel) - 1);
	}

	// ���s�L�����Z��
	ImGui::SameLine();

	if (ImGui::Button("Save"))
	{
		// �z�u�������f�����Z�[�u����
		MapModelSave();
	}

	ImGui::SameLine();

	ImGui::SameLine(ButtonSpace);

	if (ImGui::Button("Delete"))
	{
		// �z�u�������f�����f���[�g����
		ModelDelete(nNowSelect);
	}

	ImGui::SameLine();

	if (ImGui::Button("AllDelete"))
	{
		// �}�b�v���f��������
		m_bMapExclusion = true;
		// �z�u�������f����S�ăf���[�g����
		AllDelete();
	}
#endif
}

// =====================================================================================================================================================================
//
// �S�ẴR���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::ComboBoxAll(int nNowSelect)
{
	static int nSelectType		= 0;	// �I��ł�����
	static int nSelectItemType	= 0;	// �I��ł���A�C�e���̎��

	switch (m_ArrangmentModel)
	{
	case CMap::ARRANGEMENT_MODEL_ENEMY:
		// �G�̎�ޑI��
		EnemyTypeComboBox(nSelectType, nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_PRISONER:
		// �ߗ��̃h���b�v�^�C�v�I��
		PrisonerDropTypeComboBox(nSelectType, nNowSelect);
		// �ߗ��̃A�C�e���^�C�v�I��
		PrisonerItemTypeComboBox(nSelectItemType, nNowSelect);
		break;

	case CMap::ARRANGEMENT_MODEL_OBSTACLE:
		// ��Q���̎�ޑI��
		ObstacleTypeComboBox(nSelectType, nNowSelect);
		break;
	}
}

// =====================================================================================================================================================================
//
// �}�b�v�̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::MapComboBox(int & nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	// �t�@�C�����i�[�p
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < MAP::MAP_MAX; nCnt++)
	{
		//�z��ɒǉ�
		aFileName.emplace_back(m_MapModelFileName[nCnt]);
	}

	if (CHossoLibrary::ImGui_Combobox(aFileName, "MapTxt", nSelectType))
	{
		// �}�b�v�̃��[�h
		AllDelete();
		MapLoad((MAP)nSelectType);
	}
#endif
}

// =====================================================================================================================================================================
//
// �}�b�v�̎�ނ̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::MapTypeComboBox()
{
#ifdef _DEBUG
	//static int nSelectType = 0;		// �I��ł�����
	//int nNowSelect = 0;
	//// �t�@�C�����i�[�p
	//std::vector<std::string > aFileName = {};

	//	int nCnt = GetModelSet()->
	////for
	//for (int nCnt = 0; nCnt < CModel::MODEL_MAP_MAX; nCnt++)
	//{
	//	//�z��ɒǉ�
	//	aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::MAP_MODEL, nCnt));
	//}

	//if (CHossoLibrary::ImGui_Combobox(aFileName, "MapModelType", nSelectType))
	//{
	//	// NULL�`�F�b�N
	//	if (m_pMapModel[nNowSelect])
	//	{
	//		// �}�b�v�̎�ނ̎擾
	//		int MapType = m_pMapModel[nNowSelect]->GetModelCount();

	//		// �O��ƈႤ�Ƃ�
	//		if (MapType != nSelectType)
	//		{
	//			// ��ޑ��
	//			MapType = nSelectType;
	//			// �}�b�v�̂̎�ނ̐ݒ�
	//			m_pMapModel[nNowSelect]->SetModelConut(MapType);
	//		}
	//	}
	//}
#endif
}

// =====================================================================================================================================================================
//
// ��Q���̎�ނ̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::ObstacleTypeComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	// �t�@�C�����i�[�p
	std::vector<std::string > aFileName = {};

	//for
	for (int nCnt = 0; nCnt < (CModel::OBSTACLE_TYPE_MAX - CModel::OBSTACLE_TYPE_BOX); nCnt++)
	{
		//�z��ɒǉ�
		aFileName.emplace_back(CModel::GetModelFileName(CModel::MODEL_TYPE::OBSTACLE_MODEL, nCnt));
	}

	if (CHossoLibrary::ImGui_Combobox(aFileName, "Type", nSelectType))
	{
		// NULL�`�F�b�N
		if (m_pObstacle[nNowSelect])
		{
			// ��Q���̎�ނ̎擾
			int ObstacleType = m_pObstacle[nNowSelect]->GetModelCount();

			// �O��ƈႤ�Ƃ�
			if (ObstacleType != nSelectType)
			{
				// ��ޑ��
				ObstacleType = nSelectType;
				// ��Q���̎�ނ̐ݒ�
				m_pObstacle[nNowSelect]->SetModelConut(ObstacleType);
			}
		}
	}
#endif
}

// =====================================================================================================================================================================
//
// �G�̎�ނ̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::EnemyTypeComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	std::vector<std::string > aEnemyType = {"NORMAL", "SHIELD", "HELICOPTER", "MELTYHONEY", "ZYCOCCA"};

	// ���݂̃^�C�v�𔽉f
	nSelectType = (int)m_pEnemy[nNowSelect]->GetEnemyType();

	if (CHossoLibrary::ImGui_Combobox(aEnemyType, "Type", nSelectType))
	{
		// NULL�`�F�b�N
		if (m_pEnemy[nNowSelect])
		{
			// �G�̎�ނ̎擾
			CWeakEnemy::ENEMY_TYPE EnemyType = m_pEnemy[nNowSelect]->GetEnemyType();

			// �O��ƈႤ�Ƃ�
			if ((int)EnemyType != nSelectType)
			{
				// ��ޑ��
				EnemyType = (CWeakEnemy::ENEMY_TYPE)nSelectType;
				// �G�̎�ނ̐ݒ�
				m_pEnemy[nNowSelect]->SetEnemyType(EnemyType);
			}
		}
	}
#endif
}

// =====================================================================================================================================================================
//
// �ߗ��̃h���b�v�^�C�v�̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::PrisonerDropTypeComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	std::vector<std::string > aPrisonerType = { "DESIGNATE_ONE", "DESIGNATE_RANGE", "ALL" };

	// ���݂̃h���b�v�^�C�v�𔽉f
	nSelectType = (int)m_pPrisoner[nNowSelect]->GetPrisonerDropType();

	if (CHossoLibrary::ImGui_Combobox(aPrisonerType, "DropType", nSelectType))
	{
		// NULL�`�F�b�N
		if (m_pPrisoner[nNowSelect])
		{
			// �ߗ��̃h���b�v�^�C�v�̎擾
			CPrisoner::PRISONER_ITEM_DROPTYPE PrisonerType = m_pPrisoner[nNowSelect]->GetPrisonerDropType();

			// �O��ƈႤ�Ƃ�
			if (PrisonerType != nSelectType)
			{
				// ��ޑ��
				PrisonerType = (CPrisoner::PRISONER_ITEM_DROPTYPE)nSelectType;
				// �ߗ��̃h���b�v�^�C�v�̐ݒ�
				m_pPrisoner[nNowSelect]->SetPrisonerType(PrisonerType);
			}
		}
	}

#endif
}

// =====================================================================================================================================================================
//
// �ߗ��̃A�C�e���^�C�v�̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
void CMap::PrisonerItemTypeComboBox(int &nSelectType, int nNowSelect)
{
#ifdef _DEBUG
	std::vector<std::string > aPrisonerItem = { "NONE","HMG","SG","LG","RL","FS","BEAR","COIN","JEWELRY","MEDAL","BOMBUP","ENERGYUP","BULLETUP" };

	// ���݂̃A�C�e���^�C�v�𔽉f	( NONE�����邽�� +1 )
	nSelectType = (int)m_pPrisoner[nNowSelect]->GetPrisonerDropItem() + 1;

	if (CHossoLibrary::ImGui_Combobox(aPrisonerItem, "ItemType", nSelectType))
	{
		// NULL�`�F�b�N
		if (m_pPrisoner[nNowSelect])
		{
			// �ߗ������Ƃ��A�C�e���̎�ނ̎擾
			CItem::ITEMTYPE PrisonerItem = m_pPrisoner[nNowSelect]->GetPrisonerDropItem();

			// �O��ƈႤ�Ƃ�
			if (PrisonerItem != nSelectType)
			{
				// ��ޑ��	( NONE�����邽�� -1 )
				PrisonerItem = (CItem::ITEMTYPE)(nSelectType - 1);
				// �ߗ������Ƃ��A�C�e���̎�ނ̐ݒ�
				m_pPrisoner[nNowSelect]->SetPrisonerItem(PrisonerItem);
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
	D3DXVECTOR3 pos = ZeroVector3;

	// �J�����̎擾
	CCamera *pCamera = CManager::GetRenderer()->GetCamera();
	// �L�[�{�[�h�̎擾
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	// �Ǐ]�t���O
	if (m_bCameraFollowing)
	{
		pos = posR;
	}
	else
	{
		//[W]�L�[����������
		if (pKeyboard->GetKeyboardPress(DIK_W))
		{
			//��
			m_CameraPos.y += CameraMoveSpeed;
		}
		//[S]�L�[����������
		if (pKeyboard->GetKeyboardPress(DIK_S))
		{
			//�O
			m_CameraPos.y += -CameraMoveSpeed;
		}
		//[A]�L�[����������
		if (pKeyboard->GetKeyboardPress(DIK_A))
		{
			//��
			m_CameraPos.x += -CameraMoveSpeed;
		}
		//[D]�L�[����������
		if (pKeyboard->GetKeyboardPress(DIK_D))
		{
			//�E
			m_CameraPos.x += CameraMoveSpeed;
		}
		pos = m_CameraPos;
	}
	// �����_�̖ړI�n�̐ݒ�
	pCamera->SetCameraPosRDest(pos);
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
}