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

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

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
	{ "data/Load/Enemy/Enemy_Map01.txt" },
	{ "data/Load/Enemy/Enemy_Map01.txt" },
};

char *CMap::m_ObstacleFileName[MAP_MAX] =
{
	{ "data/Load/Map/Obstacle_Box.txt" },
	{ "data/Load/Map/Obstacle_Box.txt" },
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
void CMap::ModelLoad(int nCnt)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	CModel::CREATE_MAP_MODEL ModelCount = CModel::MODEL_MAP_BLOCK;		// ���

	// �t�@�C�����J��
	pFile = fopen(m_MapFileName[nCnt], "r");

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
void CMap::EnemyLoad(int nCnt)
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
	pFile = fopen(m_EnemyFileName[nCnt], "r");

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
// ��Q���̔z�u
//
// =====================================================================================================================================================================
void CMap::ObstacleLoad(int nCnt)
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
	pFile = fopen(m_ObstacleFileName[nCnt], "r");

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
				if (strcmp(cHeadText, "OBSTACLESET") == 0)
				{
					// END_ENEMYSET������܂Ń��[�v
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
							m_pObstacle[m_pObstacle.size() - 1]->SetType(nType);
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
// �}�b�v�̃f�o�b�O�z�u
//
// =====================================================================================================================================================================
void CMap::DebugMap()
{
	//CKeyboard *key;
	//key = CManager::GetInputKeyboard();
	////�v���C���[���W�̎擾
	//D3DXVECTOR3 pPos;
	//int pState;
	//CScene *pScene;
	//pScene = CScene::GetScene(OBJTYPE_PLAYER);
	//if (pScene != NULL)
	//{
	//	pPos = ((CPlayer*)pScene)->GetPosition();
	//	pState = ((CPlayer*)pScene)->GetDebugState();

	//	if (pState == CPlayer::DEBUG_CREATE_MAP)
	//	{
	//		//���f���^�C�v��O�̃��f���ɕύX
	//		if (key->GetKeyboardTrigger(DIK_1))
	//		{
	//			if (m_type > 0)
	//			{
	//				m_type--;
	//			}
	//		}
	//		//���f���^�C�v�����̃��f���ɕύX
	//		if (key->GetKeyboardTrigger(DIK_2))
	//		{
	//			if (m_type < CModel::MODEL_MAP_MAX - 1)
	//			{
	//				m_type++;
	//			}
	//		}
	//		//���f���̐ݒu
	//		if (key->GetKeyboardTrigger(DIK_RETURN))
	//		{
	//			//�����ɗv�f��ǉ�����
	//			m_vec.emplace_back(CModel::Create(CModel::MAP_MODEL, m_type));
	//			m_vec[m_vec.size() - 1]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y, pPos.z));
	//			m_vec[m_vec.size() - 1]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//		}
	//		//���f���̈ʒu���Z�[�u
	//		if (key->GetKeyboardTrigger(DIK_F9))
	//		{
	//			Save();
	//		}
	//		//���f���̃��[�h
	//		if (key->GetKeyboardTrigger(DIK_F7))
	//		{
	//			Load(0);
	//		}

	//		if (m_map.size() > 0)
	//		{
	//			m_map[m_map.size() - 1]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y, pPos.z));
	//			m_map[m_map.size() - 1]->SetSize(D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	//			m_map[0]->SetType(m_type);
	//		}
	//		CDebugProc::Print("[�ݒu�̑���]\n");
	//		CDebugProc::Print("�}�b�v�̃Z�[�u    :[F9]\n");
	//		CDebugProc::Print("�}�b�v�̃��[�h     :[F7]\n");
	//		CDebugProc::Print("���f���̐؂�ւ�:[1]:[2]\n");
	//		CDebugProc::Print("���f���̈ړ�      :[0]\n");
	//		CDebugProc::Print("���f���̍폜      :[3]\n");
	//		CDebugProc::Print("���f���̐ݒu      :[ENTER]\n");
	//		CDebugProc::Print("�㏸                   :[SPACE]\n");
	//		CDebugProc::Print("����                   :[LCTRL]\n");
	//	}
	//	//if (pState == CPlayer::DEBUG_CREATE_ENEMY)
	//	//{
	//	//	if (m_type > CEnemy::ENEMY_TYPE_MAX - 1)
	//	//	{
	//	//		m_type = 0;
	//	//	}
	//	//	//���f���^�C�v��O�̃��f���ɕύX
	//	//	if (key->GetKeyboardTrigger(DIK_1))
	//	//	{
	//	//		if (m_type > 0)
	//	//		{
	//	//			m_type--;
	//	//		}
	//	//	}
	//	//	//���f���^�C�v�����̃��f���ɕύX
	//	//	if (key->GetKeyboardTrigger(DIK_2))
	//	//	{
	//	//		if (m_type < CEnemy::ENEMY_TYPE_MAX - 1)
	//	//		{
	//	//			m_type++;
	//	//		}
	//	//	}
	//	//	if (key->GetKeyboardTrigger(DIK_RETURN))
	//	//	{
	//	//		//�����ɗv�f��ǉ�����
	//	//		m_Enemy.emplace_back(CEnemy::Create(m_type));
	//	//		m_Enemy[m_Enemy.size() - 1]->SetPosition(D3DXVECTOR3(pPos.x, pPos.y - 50, pPos.z));
	//	//	}
	//	//	//���f���̈ʒu���Z�[�u
	//	//	if (key->GetKeyboardTrigger(DIK_F9))
	//	//	{
	//	//		Save();
	//	//	}
	//	//	CDebugProc::Print("[�ݒu�̑���]\n");
	//	//	CDebugProc::Print("�}�b�v�̃Z�[�u    :[F9]\n");
	//	//	CDebugProc::Print("�G�l�~�[�̐؂�ւ�:[1]:[2]\n");
	//	//	CDebugProc::Print("�G�l�~�[�̐ݒu      :[ENTER]\n");
	//	//	CDebugProc::Print("�㏸                   :[SPACE]\n");
	//	//	CDebugProc::Print("����                   :[LCTRL]\n");
	//	//	CDebugProc::Print("�G�l�~�[�^�C�v%d\n", m_type);
	//	//}
	//}
	//if (m_Enemy.size() == 0)
	//{
	//	for (unsigned int nCnt = 0; nCnt < m_vec.size(); nCnt++)
	//	{
	//		if (m_vec[nCnt]->GetType() == CModel::MODEL_MAP_BLOCK02)
	//		{
	//			m_vec.erase(m_vec.begin() + nCnt);//�ŏ�����[nCnt]�Ԗڂ�����
	//		}
	//	}
	//}
	//else
	//{
	//	CDebugProc::Print("[F2]�Ń}�b�v�G�f�B�^\n");
	//}
	////for (unsigned int nCnt = 0; nCnt < m_Enemy.size(); nCnt++)
	////{
	////	if (m_Enemy[nCnt] != nullptr)
	////	{
	////		if (m_Enemy[nCnt]->GetLife() <= 0)
	////		{
	////			m_Enemy[nCnt]->Uninit();
	////			m_Enemy[nCnt]->Rerease();
	////			m_Enemy.erase(m_Enemy.begin() + nCnt);
	////		}
	////	}
	////}
	//Collision();
}

// =====================================================================================================================================================================
//
// ���f���̍ő吔�擾
//
// =====================================================================================================================================================================
CMap *CMap::MapCreate(int nCnt)
{
	// �ϐ�
	CMap *pMap;

	// �������̊m��
	pMap = new CMap();

	// ���f���̃��[�h
	pMap->ModelLoad(nCnt);
	// �G�̃��[�h
	pMap->EnemyLoad(nCnt);
	// ��Q���̃��[�h
	pMap->ObstacleLoad(nCnt);

	return pMap;
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
void CMap::ModelSave()
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(m_MapFileName[MAP_1], "w");

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
		MessageBox(NULL, "�t�@�C�����J����Ă��܂�", "�x��", MB_OK | MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// �G�̃Z�[�u
//
// =====================================================================================================================================================================
void CMap::EnemySave()
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �t�@�C�����J��
	pFile = fopen(m_EnemyFileName[MAP_1], "w");

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
			if (!m_pEnemy[nCntEnemy])
			{
				D3DXVECTOR3 EnemyPos = m_pEnemy[nCntEnemy]->GetPosition();	// ���f���̈ʒu�擾

				fprintf(pFile, "ENEMYSET									# %d\n", nCntEnemy);
				fprintf(pFile, "	TYPE	= %d\n", 0 /*m_pEnemy[nCntEnemy]->GetType()*/);
				fprintf(pFile, "	POS		= %.0f %.0f %.0f\n", EnemyPos.x, EnemyPos.y, EnemyPos.z);
				fprintf(pFile, "	LIFE	= %d\n", m_pEnemy[nCntEnemy]->GetLife());
				fprintf(pFile, "END_ENEMYSETSET\n\n");
			}
		}
		fprintf(pFile, "END_SCRIPT\n");

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		// ���b�Z�[�W�E�B���h�E�Ōx��
		MessageBox(NULL, "�t�@�C�����J����Ă��܂�", "�x��", MB_OK | MB_ICONWARNING);
	}
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
}
