// =====================================================================================================================================================================
//
// ���[�h�̏��� [motion.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "motion.h"			// �C���N���[�h�t�@�C��
#include "keyboard.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
MOTION_INFO CMotion::m_aMotion[PLAYER_MOTION] = {};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MOTION_FILE_NAME			("data/MOTION/PlayerMotion0.txt")		// �Z�[�u�t�@�C��

// =====================================================================================================================================================================
//
// ���[�V�����̓ǂݍ���
//
// =====================================================================================================================================================================
void CMotion::MotionLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char		cReadText[128];			// �����Ƃ��ēǂݎ��
	char		cHeadText[128];			// ��r�p
	char		cDie[128];				// �s�v�ȕ���
	int			nCntMotion	= 0;		// ���[�V�����J�E���g
	int			nCntKeySet	= 0;		// �L�[�Z�b�g�J�E���g
	int			nCntKey		= 0;		// �L�[�J�E���g
	int			nLoop		= 0;		// ���[�v�̗L��
	int			nNumKey		= 0;		// ���Ԗڂ̃L�[
	int			nNumFrame	= 0;		// �t���[����
	D3DXVECTOR3 pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ʒu

	// �t�@�C�����J��
	pFile = fopen(MOTION_FILE_NAME, "r");

	// �J���Ă���
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

				// MOTIONSET��������
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					// �L�[�Z�b�g�̏�����
					nCntKeySet = 0;

					// END_POSSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						// LOOP��������
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aMotion[nCntMotion].nLoop);		// ��r�p�e�L�X�g�Ƀ��[�v���邩�̐�������
						}

						// NUM_KEY��������
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aMotion[nCntMotion].nNumKey);		// ��r�p�e�L�X�g�ɃL�[������
						}

						// KEYSET��������
						else if (strcmp(cHeadText, "KEYSET") == 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
							sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

							// FRAME��������
							if (strcmp(cHeadText, "FRAME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_aMotion[nCntMotion].aKeySet[nCntKeySet].nFrame);		// ��r�p�e�L�X�g�Ƀt���[��������
							}

							// �L�[�̏�����
							nCntKey = 0;

							// END_KEYSET������܂Ń��[�v
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
								sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

								// KEY��������
								if (strcmp(cHeadText, "KEY") == 0)
								{
									// END_KEY������܂Ń��[�v
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
										sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

										// ROT��������
										if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_aMotion[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.x,
												&m_aMotion[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.y,
												&m_aMotion[nCntMotion].aKeySet[nCntKeySet].aKey[nCntKey].rot.z);		// ��r�p�e�L�X�g��ROT����
										}
									}
									nCntKey++;
								}
							}
							nCntKeySet++;
						}
					}
					nCntMotion++;
				}
			}
		}
	}
}