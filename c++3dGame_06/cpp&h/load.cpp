// ----------------------------------------
//
// ���[�h��񏈗� [load.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------
#include "load.h"

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CLoad::CLoad()
{
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CLoad::~CLoad()
{
}

// ----------------------------------------
// Unload
// ----------------------------------------
void CLoad::Unload(void)
{
}

// ----------------------------------------
// �ǂݍ���
// ----------------------------------------
int CLoad::Load(const char * filename)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	// �ϐ��錾
	int	nCntObj = 0;		// ���f���J�E���g
	char cRaedText[128];	// �����Ƃ��ēǂݎ��p
	char cHeadText[128];	// ��r����悤
	char cDie[128];			// �s�K�v�ȕ���

	// �t�@�C���J
	pFile = fopen(filename, "r");

	// �J����
	if (pFile != NULL)
	{
		// �X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cRaedText, sizeof(cRaedText), pFile);	// �ꕶ��ǂݍ���
			sscanf(cRaedText, "%s", &cHeadText);		// ��r�p�e�N�X�g�ɕ�������

			// 3d�A�C�e���̑����ǂݍ���
			if (strcmp(cHeadText, "TOTAL") == 0)
			{
				sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
					&m_nMax3DItem);
			}
		}

		// �X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// �G���h�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				// ������
				cHeadText[0] = '\0';
				fgets(cRaedText, sizeof(cRaedText), pFile);
				sscanf(cRaedText, "%s", &cHeadText);
				// �}�e���A���Z�b�g������
				if (strcmp(cHeadText, "OBJECTSET") == 0)
				{
					// �G���h�}�e���A���Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_OBJECTSET") != 0)
					{
						// ������
						cHeadText[0] = '\0';
						fgets(cRaedText, sizeof(cRaedText), pFile);
						sscanf(cRaedText, "%s", &cHeadText);
						// �e���ǂݍ���
						if (strcmp(cHeadText, "TYPE") == 0)
						{
							sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
								&info[nCntObj].nType);
						}
						// �ʒu���ǂݍ���
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f",
								&cDie, &cDie,
								&info[nCntObj].pos.x,
								&info[nCntObj].pos.y,
								&info[nCntObj].pos.z);
						}
						// ��]���ǂݍ���
						else if (strcmp(cHeadText, "ROT") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f", &cDie, &cDie,
								&info[nCntObj].rot.x,
								&info[nCntObj].rot.y,
								&info[nCntObj].rot.z);
						}

						// �F���ǂݍ���
						else if (strcmp(cHeadText, "COL") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f %f", &cDie, &cDie,
								&info[nCntObj].col.r,
								&info[nCntObj].col.g,
								&info[nCntObj].col.b,
								&info[nCntObj].col.a);
						}
						// �c�u���b�N���ǂݍ���
						else if (strcmp(cHeadText, "BLOCK_DEPTH") == 0)
						{
							sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
								&info[nCntObj].nBlockDipth);
						}
						// ���u���b�N���ǂݍ���
						else if (strcmp(cHeadText, "BLOCK_WIDTH") == 0)
						{
							sscanf(cRaedText, "%s %s %d", &cDie, &cDie,
								&info[nCntObj].nBlockWidth);
						}
						// �T�C�Y���ǂݍ���
						else if (strcmp(cHeadText, "SIZE") == 0)
						{
							sscanf(cRaedText, "%s %s %f %f %f", &cDie, &cDie,
								&info[nCntObj].size.x,
								&info[nCntObj].size.y,
								&info[nCntObj].size.z);
						}
					}
					// ���f���̍X�V
					nCntObj++;
				}
			}
		}
		// �t�@�C����
		fclose(pFile);
	}

	// �J���Ȃ�
	else
	{
		MessageBox(NULL, "�I�u�W�F�N�g�ǂݍ��݂Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
	}

	// �S�̂̑���
	return nCntObj;
}

// ----------------------------------------
// �ǂݍ���
// ----------------------------------------
CLoad::INFO &CLoad::GetInfo(int nID)
{
	return info[nID];
}

// ----------------------------------------
// �W�����v�擾
// ----------------------------------------
int & CLoad::GetShard(void)
{
	return m_nMax3DItem;
}