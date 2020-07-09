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
// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CMap::MAP CMap::m_MapNum = MAP_1;		// �}�b�v�ԍ�

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CMap::m_MapFileName[MAP_MAX] =
{
	{ "data/Load/Map/testMap.txt" },
	{ "data/Load/Map/testMap.txt" },
};
char *CMap::m_EnemyFileName[MAP_MAX] =
{
	{ "data/Load/Enemy/Enemy_Map_01.txt" },
	{ "data/Load/Enemy/Enemy_Map_02.txt" },
};
char *CMap::m_PrisonerFileName[MAP_MAX] =
{
	{ "data/Load/Prisoner/Prisoner_Map_01.txt" },
	{ "data/Load/Prisoner/Prisoner_Map_02.txt" },
};

char *CMap::m_ObstacleFileName[MAP_MAX] =
{
	{ "data/Load/Obstacle/Obstacle_Map_01.txt" },
	{ "data/Load/Obstacle/Obstacle_Map_02.txt" },
};

char *CMap::m_PlayerTankFileName[MAP_MAX] =
{
	{ "data/Load/PlayerTank/PlayerTank_Map_01.txt" },
	{ "data/Load/PlayerTank/PlayerTank_Map_02.txt" },
};


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
// ���f���̃��[�h
//
// =====================================================================================================================================================================
void CMap::ModelLoad(MAP MapNum)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	CModel::CREATE_MAP_MODEL ModelCount = CModel::MODEL_MAP_BLOCK;		// ���

	// �t�@�C�����J��
	pFile = fopen(m_MapFileName[MapNum], "r");

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
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &ModelCount);		// ��r�p�e�L�X�g��TYPE����
						}
						// POS��������
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
						}
						else if (strcmp(cHeadText, "END_MODELSET") == 0)
						{
							// �I�u�W�F�N�g�̐���
							m_pModel.emplace_back(CModel::CreateSceneManagement(CModel::MAP_MODEL, ModelCount));
							// �ʒu�̐ݒ�
							m_pModel[m_pModel.size() - 1]->SetPosition(pos);
						}
					}
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
}

// =====================================================================================================================================================================
//
// �G�l�~�[�̃��[�h
//
// =====================================================================================================================================================================
void CMap::EnemyLoad(MAP MapNum)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	int nLife		= 0;								// �̗�
	//CEnemy::TYPE type = CEnemy::NONE;		// ���
	int nType = 0;

	// �t�@�C�����J��
	pFile = fopen(m_EnemyFileName[MapNum], "r");

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

				// ENEMYSET��������
				if (strcmp(cHeadText, "ENEMYSET") == 0)
				{
					// END_ENEMYSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_ENEMYSET") != 0)
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
						else if (strcmp(cHeadText, "END_ENEMYSET") == 0)
						{
							// �I�u�W�F�N�g�̐���
							m_pEnemy.emplace_back(CEnemy::Create());
							// �ʒu�̐ݒ�
							m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
							// �̗͂̐ݒ�
							m_pEnemy[m_pEnemy.size() - 1]->SetLife(nLife);
						}
					}
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
}

// =====================================================================================================================================================================
//
// �ߗ��̔z�u
//
// =====================================================================================================================================================================
void CMap::PrisonerLoad(MAP MapNum)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];								// �����Ƃ��ēǂݎ��
	char cHeadText[128];								// ��r�p
	char cDie[128];										// �s�v�ȕ���
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	// �t�@�C�����J��
	pFile = fopen(m_PrisonerFileName[MapNum], "r");

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

				// PRISONERSET��������
				if (strcmp(cHeadText, "PRISONERSET") == 0)
				{
					// END_PRISONERSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_PRISONERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// POS��������
						if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
						}
						else if (strcmp(cHeadText, "END_PRISONERSET") == 0)
						{
							// �ߗ��̐���
							m_pPrisoner.emplace_back(CPrisoner::Create());
							// �ʒu�̐ݒ�
							m_pPrisoner[m_pPrisoner.size() - 1]->SetPosition(pos);
						}
					}
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
}

// =====================================================================================================================================================================
//
// ��Q���̔z�u
//
// =====================================================================================================================================================================
void CMap::ObstacleLoad(MAP MapNum)
{
	// �t�@�C���|�C���g
	FILE *pFile;
	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	int nLife = 0;										// �̗�
	int nType = 0;										// ���

	// �t�@�C�����J��
	pFile = fopen(m_ObstacleFileName[MapNum], "r");

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

				// OBSTACLESET��������
				if (strcmp(cHeadText, "OBSTACLESET") == 0)
				{
					// END_OBSTACLESET������܂Ń��[�v
					while (strcmp(cHeadText, "END_OBSTACLESET") != 0)
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
						else if (strcmp(cHeadText, "END_OBSTACLESET") == 0)
						{
							// �I�u�W�F�N�g�̐���
							m_pObstacle.emplace_back(CObstacle::Create());
							// �^�C�v�̑��
							m_pObstacle[m_pObstacle.size() - 1]->SetModelConut(nType);
							// �ʒu�̐ݒ�
							m_pObstacle[m_pObstacle.size() - 1]->SetPosition(pos);
							// �̗͂̐ݒ�
							m_pObstacle[m_pObstacle.size() - 1]->SetLife(nLife);
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
		MessageBox(NULL, "��Q���̃p�����[�^�[�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// �v���C���[�p�̐�Ԃ̔z�u
//
// =====================================================================================================================================================================
void CMap::PlayerTankLoad(MAP MapNum)
{
	// �t�@�C���|�C���g
	FILE *pFile;
	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu

	// �t�@�C�����J��
	pFile = fopen(m_PlayerTankFileName[MapNum], "r");

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

															// OBSTACLESET��������
				if (strcmp(cHeadText, "PLAYERTANKSET") == 0)
				{
					// END_OBSTACLESET������܂Ń��[�v
					while (strcmp(cHeadText, "END_PLAYERTANKSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// POS��������
						if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &pos.x, &pos.y, &pos.z);		// ��r�p�e�L�X�g��POS����
						}
						else if (strcmp(cHeadText, "END_PLAYERTANKSET") == 0)
						{
							// �I�u�W�F�N�g�̐���
							m_pPlayerTank.emplace_back(CPlayertank::Create());
							// �ʒu�̐ݒ�
							m_pPlayerTank[m_pPlayerTank.size() - 1]->SetPosition(pos);
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
		MessageBox(NULL, "�v���C���[��Ԃ̃p�����[�^�[�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// �}�b�v�̐���
//
// =====================================================================================================================================================================
CMap *CMap::MapCreate(MAP MapNum)
{
	// �ϐ�
	CMap *pMap;

	// �������̊m��
	pMap = new CMap();

	// ���f���̃��[�h
	pMap->ModelLoad(MapNum);
	// �G�̃��[�h
	pMap->EnemyLoad(MapNum);
	// �ߗ��̃��[�h
	//pMap->PrisonerLoad(MapNum);
	// ��Q���̃��[�h
	//pMap->ObstacleLoad(MapNum);
	// �v���C���[��Ԃ̃��[�h
	pMap->PlayerTankLoad(MapNum);

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

	// �}�b�v���f���̃^�u
	MapModelTab();

	ImGui::End();
#endif
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
// ���f���̃Z�[�u
//
// =====================================================================================================================================================================
void CMap::ModelSave(MAP MapNum)
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(m_MapFileName[MapNum], "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ���f���̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	��\n");
		fprintf(pFile, "#	[ 1 ]	��\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (unsigned int nCntModel = 0; nCntModel < m_pModel.size(); nCntModel++)
		{
			// NULL�`�F�b�N
			if (!m_pModel[nCntModel])
			{
				D3DXVECTOR3 ModelPos = m_pModel[nCntModel]->GetPosition();	// ���f���̈ʒu�擾

				fprintf(pFile, "MODELSET									# %d\n", nCntModel);
				fprintf(pFile, "	TYPE	= %d\n", m_pModel[nCntModel]->GetType());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", ModelPos.x, ModelPos.y, ModelPos.z);
				fprintf(pFile, "END_MODELSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// ���b�Z�[�W�E�B���h�E�Ōx��
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���", "�x��", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// �G�̃Z�[�u
//
// =====================================================================================================================================================================
void CMap::EnemySave(MAP MapNum)
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(m_EnemyFileName[MapNum], "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �G�̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	���m\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (unsigned int nCntEnemy = 0; nCntEnemy < m_pEnemy.size(); nCntEnemy++)
		{
			// NULL�`�F�b�N
			if (m_pEnemy[nCntEnemy])
			{
				D3DXVECTOR3 EnemyPos = m_pEnemy[nCntEnemy]->GetPosition();	// ���f���̈ʒu�擾

				fprintf(pFile, "ENEMYSET									# %d\n", nCntEnemy);
				fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCntEnemy]->GetType()*/);
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", EnemyPos.x, EnemyPos.y, EnemyPos.z);
				fprintf(pFile, "	LIFE	= %d\n", m_pEnemy[nCntEnemy]->GetLife());
				fprintf(pFile, "END_ENEMYSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		// ���b�Z�[�W�E�B���h�E�ŕ\��
		MessageBox(NULL, "�G�̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// ���b�Z�[�W�E�B���h�E�Ōx��
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���", "�x��", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// �ߗ��̃Z�[�u
//
// =====================================================================================================================================================================
void CMap::PrisonerSave(MAP MapNum)
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(m_PrisonerFileName[MapNum], "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �ߗ��̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	���m\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (unsigned int nCntPrisoner = 0; nCntPrisoner < m_pPrisoner.size(); nCntPrisoner++)
		{
			// NULL�`�F�b�N
			if (m_pPrisoner[nCntPrisoner])
			{
				D3DXVECTOR3 PrisonerPos = m_pPrisoner[nCntPrisoner]->GetPosition();	// ���f���̈ʒu�擾

				fprintf(pFile, "PRISONERSET									# %d\n", nCntPrisoner);
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", PrisonerPos.x, PrisonerPos.y, PrisonerPos.z);
				fprintf(pFile, "END_PRISONERSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		// ���b�Z�[�W�E�B���h�E�ŕ\��
		MessageBox(NULL, "�ߗ��̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// ���b�Z�[�W�E�B���h�E�Ōx��
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���", "�x��", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// ��Q���̃Z�[�u
//
// =====================================================================================================================================================================
void CMap::ObstacleSave(MAP MapNum)
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(m_ObstacleFileName[MapNum], "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ��Q���̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	��\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		fprintf(pFile, "SCRIPT\n\n");

		for (unsigned int nCntObstacle = 0; nCntObstacle < m_pObstacle.size(); nCntObstacle++)
		{
			// NULL�`�F�b�N
			if (m_pObstacle[nCntObstacle])
			{
				D3DXVECTOR3 ObstaclePos = m_pObstacle[nCntObstacle]->GetPosition();	// ���f���̈ʒu�擾

				fprintf(pFile, "OBSTACLESET									# %d\n", nCntObstacle);
				fprintf(pFile, "	TYPE	= %d\n", m_pObstacle[nCntObstacle]->GetModelCount());
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", ObstaclePos.x, ObstaclePos.y, ObstaclePos.z);
				fprintf(pFile, "	LIFE	= %d\n", m_pObstacle[nCntObstacle]->GetLife());
				fprintf(pFile, "END_OBSTACLESET\n\n");
			}
		}
		// ���b�Z�[�W�E�B���h�E�ŕ\��
		MessageBox(NULL, "��Q���̔z�u�f�[�^���Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);

		fprintf(pFile, "END_SCRIPT\n");

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// ���b�Z�[�W�E�B���h�E�Ōx��
		MessageBox(NULL, "�t�@�C�����ǂݍ��߂܂���", "�x��", MB_OK | MB_ICONWARNING);
	}
}

void CMap::PlayerTankSave(MAP MapNum)
{
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
		// ��Q���̃Z�[�u
		ObstacleSave(m_MapNum);
		// �ߗ��̃Z�[�u
		PrisonerSave(m_MapNum);
		// �G�̃Z�[�u
		EnemySave(m_MapNum);
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
		// ��Q��
		if (ImGui::BeginTabItem("Obstacle"))
		{
			// ��Q���̐ݒu
			ObstacleSet();
			ImGui::EndTabItem();
		}
		// �ߗ�
		if (ImGui::BeginTabItem("Prisoner"))
		{
			// �ߗ��̐ݒu
			PrisonerSet();
			ImGui::EndTabItem();
		}
		// �G
		if (ImGui::BeginTabItem("Enemy"))
		{
			// �G�̐ݒu
			EnemySet();
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
}

// =====================================================================================================================================================================
//
// ��Q���̐ݒu
//
// =====================================================================================================================================================================
void CMap::ObstacleSet()
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
	else if (nNowSelect >= (int)m_pObstacle.size())
	{
		nNowSelect = (int)m_pObstacle.size();
	}
	// �I�����Ă��郂�f������������Ă���Ƃ�
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pObstacle.size())
	{
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

		// NULL�`�F�b�N
		if (m_pObstacle[nNowSelect])
		{
			// ���ݒn
			int x = (int)m_pObstacle[nNowSelect]->GetPosition().x,
				y = (int)m_pObstacle[nNowSelect]->GetPosition().y,
				z = (int)m_pObstacle[nNowSelect]->GetPosition().z;

			// �I�u�W�F�N�g�̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// �I�u�W�F�N�g�̈ʒu�̐ݒ�
			m_pObstacle[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));
		}
	}

	// ���s
	ImGui::Separator();

	// ����
	if (ImGui::Button("Crate"))
	{
		// �I�u�W�F�N�g�̐���
		m_pObstacle.emplace_back(CObstacle::Create());
	}

	// ���s�L�����Z��
	ImGui::SameLine();

	// �Z�[�u
	if (ImGui::Button("Save"))
	{
		// ��Q���̃Z�[�u
		ObstacleSave(m_MapNum);
	}

	// �S�ăZ�[�u
	AllSaveButton();

#endif
}

// =====================================================================================================================================================================
//
// �ߗ��̐ݒu
//
// =====================================================================================================================================================================
void CMap::PrisonerSet()
{
#ifdef _DEBUG

	static int nPrisonerType = 0;		// �ߗ��̎��
	static int nNowSelect = -1;			// ���ݑI�����Ă���ԍ�

	// �I�u�W�F�N�g�ԍ��̑I��
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// �͈͐���
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)m_pPrisoner.size())
	{
		nNowSelect = (int)m_pPrisoner.size();
	}
	// �I�����Ă��郂�f������������Ă���Ƃ�
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pPrisoner.size())
	{
		//// �R���{�{�b�N�X
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

		// NULL�`�F�b�N
		if (m_pPrisoner[nNowSelect])
		{
			// ���ݒn
			int x = (int)m_pPrisoner[nNowSelect]->GetPosition().x,
				y = (int)m_pPrisoner[nNowSelect]->GetPosition().y,
				z = (int)m_pPrisoner[nNowSelect]->GetPosition().z;

			// �I�u�W�F�N�g�̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// �I�u�W�F�N�g�̈ʒu�̐ݒ�
			m_pPrisoner[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));
		}
	}

	// ���s
	ImGui::Separator();

	// ����
	if (ImGui::Button("Crate"))
	{
		// �I�u�W�F�N�g�̐���
		m_pPrisoner.emplace_back(CPrisoner::Create());
	}

	// ���s�L�����Z��
	ImGui::SameLine();

	// �Z�[�u
	if (ImGui::Button("Save"))
	{
		// �ߗ��̃Z�[�u
		PrisonerSave(m_MapNum);
	}

	// �S�ăZ�[�u
	AllSaveButton();

#endif
}

// =====================================================================================================================================================================
//
// �G�̐ݒu
//
// =====================================================================================================================================================================
void CMap::EnemySet()
{
#ifdef _DEBUG

	static int nEnemyType = 0;			// �G�̎��
	static int nNowSelect = -1;			// ���ݑI�����Ă���ԍ�

	// �I�u�W�F�N�g�ԍ��̑I��
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// �͈͐���
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)m_pEnemy.size())
	{
		nNowSelect = (int)m_pEnemy.size();
	}
	// �I�����Ă��郂�f������������Ă���Ƃ�
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pEnemy.size())
	{
		//// �R���{�{�b�N�X
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

		// NULL�`�F�b�N
		if (m_pEnemy[nNowSelect])
		{
			// ���ݒn
			int x = (int)m_pEnemy[nNowSelect]->GetPosition().x,
				y = (int)m_pEnemy[nNowSelect]->GetPosition().y,
				z = (int)m_pEnemy[nNowSelect]->GetPosition().z;

			// �I�u�W�F�N�g�̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// �I�u�W�F�N�g�̈ʒu�̐ݒ�
			m_pEnemy[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));
		}
	}

	// ���s
	ImGui::Separator();

	// ����
	if (ImGui::Button("Crate"))
	{
		// �I�u�W�F�N�g�̐���
		m_pEnemy.emplace_back(CEnemy::Create());
	}

	// ���s�L�����Z��
	ImGui::SameLine();

	// �Z�[�u
	if (ImGui::Button("Save"))
	{
		// �G�̃Z�[�u
		EnemySave(m_MapNum);
	}

	// �S�ăZ�[�u
	AllSaveButton();

#endif
}

// =====================================================================================================================================================================
//
// �v���C���[�̐�Ԃ̐ݒu
//
// =====================================================================================================================================================================
void CMap::PlayerTankSet()
{
#ifdef _DEBUG

	static int nPlayerTankType = 0;		// ��Ԃ̎��
	static int nNowSelect = -1;			// ���ݑI�����Ă���ԍ�

										// �I�u�W�F�N�g�ԍ��̑I��
	ImGui::InputInt("nowSelect", &nNowSelect, 1, 20, 0);

	// �͈͐���
	if (nNowSelect <= -1)
	{
		nNowSelect = -1;
	}
	else if (nNowSelect >= (int)m_pPlayerTank.size())
	{
		nNowSelect = (int)m_pPlayerTank.size();
	}
	// �I�����Ă��郂�f������������Ă���Ƃ�
	else if (nNowSelect >= 0 || nNowSelect <= (int)m_pPlayerTank.size())
	{
		//// �R���{�{�b�N�X
		//if (EnemyComboBox(nPlayerTankType))
		//{
		//	// NULL�`�F�b�N
		//	if (m_pPlayerTank[nNowSelect])
		//	{
		//		// �G�̎�ނ̎擾
		//		CModel::PLAYERTANK_TYPE PlayerTankType = (CModel::OBSTACLE_TYPE)m_pPlayerTank[nNowSelect]->GetModelCount();

		//		// �O��ƈႤ�Ƃ�
		//		if (PlayerTankType != nPlayerTankType)
		//		{
		//			// ��ޑ��
		//			PlayerTankType = (CModel::PLAYERTANK_TYPE)nPlayerTankType;
		//			// �G�̃^�C�v�̐ݒ�
		//			m_pPlayerTank[nNowSelect]->SetModelConut(PlayerTankType);
		//		}
		//	}
		//}

		// NULL�`�F�b�N
		if (m_pPlayerTank[nNowSelect])
		{
			// ���ݒn
			int x = (int)m_pPlayerTank[nNowSelect]->GetPosition().x,
				y = (int)m_pPlayerTank[nNowSelect]->GetPosition().y,
				z = (int)m_pPlayerTank[nNowSelect]->GetPosition().z;

			// �I�u�W�F�N�g�̈ړ�
			ImGui::DragInt("X", &x);
			ImGui::DragInt("Y", &y);
			ImGui::DragInt("Z", &z);

			// �I�u�W�F�N�g�̈ʒu�̐ݒ�
			m_pPlayerTank[nNowSelect]->SetPosition(D3DXVECTOR3((float)x, (float)y, (float)z));
		}
	}

	// ���s
	ImGui::Separator();

	// ����
	if (ImGui::Button("Crate"))
	{
		// �I�u�W�F�N�g�̐���
		m_pPlayerTank.emplace_back(CPlayertank::Create());
	}

	// ���s�L�����Z��
	ImGui::SameLine();

	// �Z�[�u
	if (ImGui::Button("Save"))
	{
		// �G�̃Z�[�u
		EnemySave(m_MapNum);
	}

	// �S�ăZ�[�u
	AllSaveButton();

#endif

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
// �v���C���[�̐�Ԃ̃R���{�{�b�N�X
//
// =====================================================================================================================================================================
bool CMap::PlayerTankComboBox(int & nType)
{
	return false;
}

// =====================================================================================================================================================================
//
// ���S�t���O�m�F�֐�
//
// =====================================================================================================================================================================
void CMap::UpdateDieFlag()
{
	for (size_t nCnt = 0; nCnt < m_pEnemy.size(); nCnt++)
	{
		if (m_pEnemy[nCnt]->GetDieFlag())
		{
			m_pEnemy[nCnt]->Rerease();
			m_pEnemy[nCnt] = nullptr;
			m_pEnemy.erase(m_pEnemy.begin() + nCnt);
		}
	}

	for (size_t nCnt = 0; nCnt < m_pObstacle.size(); nCnt++)
	{
		if (m_pObstacle[nCnt]->GetDieFlag())
		{
			m_pObstacle[nCnt]->Rerease();
			m_pObstacle[nCnt] = nullptr;
			m_pObstacle.erase(m_pObstacle.begin() + nCnt);
		}
	}

	for (size_t nCnt = 0; nCnt < m_pPrisoner.size(); nCnt++)
	{
		if (m_pPrisoner[nCnt]->GetDieFlag())
		{
			m_pPrisoner[nCnt]->Rerease();
			m_pPrisoner[nCnt] = nullptr;
			m_pPrisoner.erase(m_pPrisoner.begin() + nCnt);
		}
	}

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
