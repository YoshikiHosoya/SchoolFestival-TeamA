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

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
std::vector<CModel*>	CMap::m_pModel = {};
std::vector<CEnemy*>	CMap::m_pEnemy = {};

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CMap::m_FileName[MAPOBJECT_MAX] =
{
	{ "data/Load/testMap.txt" },
	{ "data/Load/Enemy.txt" },
};

// =====================================================================================================================================================================
//
// ���f���̃��[�h
//
// =====================================================================================================================================================================
void CMap::ModelLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	static int nCntModel = 0;		// �ԍ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	CModel::CREATE_MAP_MODEL ModelCount = CModel::MODEL_MAP_BLOCK;		// ���

	// �t�@�C�����J��
	pFile = fopen(m_FileName[MAPOBJECT_MODEL], "r");

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
							if (m_pModel[nCntModel])
							{
								// �I�u�W�F�N�g�̐���
								m_pModel.emplace_back(CModel::Create(CModel::MAP_MODEL, ModelCount));
								// �ʒu�̐ݒ�
								m_pModel[m_pModel.size() - 1]->SetPosition(pos);
							}
						}
					}
					// �J�E���g�A�b�v
					nCntModel++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	nCntModel = 0;
}

// =====================================================================================================================================================================
//
// �G�l�~�[�̃��[�h
//
// =====================================================================================================================================================================
void CMap::EnemyLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	static int nCntEnemy = 0;		// �ԍ�
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	//CEnemy::TYPE type = CEnemy::NONE;		// ���
	int nType = 0;

	// �t�@�C�����J��
	pFile = fopen(m_FileName[MAPOBJECT_ENEMY], "r");

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
						else if (strcmp(cHeadText, "END_ENEMYSET") == 0)
						{
							if (m_pEnemy[nCntEnemy])
							{
								// �I�u�W�F�N�g�̐���
								m_pEnemy.emplace_back(CEnemy::Create());
								// �ʒu�̐ݒ�
								m_pEnemy[m_pEnemy.size() - 1]->SetPosition(pos);
							}
						}
					}
					// �J�E���g�A�b�v
					nCntEnemy++;
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	nCntEnemy = 0;
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
	pFile = fopen(m_FileName[MAPOBJECT_MODEL], "w");

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
	pFile = fopen(m_FileName[MAPOBJECT_ENEMY], "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �G�̔z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# TYPE���\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#	[ 0 ]	��\n");
		fprintf(pFile, "#	[ 1 ]	��\n");
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
// ���f���̎擾
//
// =====================================================================================================================================================================
CModel * CMap::GetModel(int nCnt)
{
	return m_pModel[nCnt];
}

// =====================================================================================================================================================================
//
// �G�̎擾
//
// =====================================================================================================================================================================
CEnemy * CMap::GetEnemy(int nCnt)
{
	return m_pEnemy[nCnt];
}