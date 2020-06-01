//=============================================================================
//
// ���[�V�������� [player.cpp]
// Author : Fujiwara Masato
//
//=============================================================================
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CMotion::CMotion()
{
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CMotion::~CMotion()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CMotion::Init(void)
{
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CMotion::Uninit(void)
{
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CMotion::Update(void)
{
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CMotion::Draw(void)
{
}

// ----------------------------------------
// ��������
// ----------------------------------------
CMotion * CMotion::Create()
{
	return NULL;
}

// ----------------------------------------
// �ǂݍ��ݐݒ�
// ----------------------------------------
void CMotion::Load(
	MOTION * pMotion,
	MODEL_OFFSET * pOffset,
	int nMaxkey,
	const char * file_name
)
{
	// �t�@�C���|�C���g
	FILE *pFile;

	// �ϐ��錾
	int	nCntMotion = 0;		// ���[�V�����J�E���g
	int	nCntKeySet = 0;		// �t���[����
	int	nCntKey = 0;		// ���f����
	char cRaedText[128];	// �����Ƃ��ēǂݎ��p
	char cHeadText[128];	// ��r����悤
	char cDie[128];			// �s�K�v�ȕ���

	// �t�@�C���J
	pFile = fopen(file_name, "r");

	// �J����
	if (pFile != NULL)
	{
		// �X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			// ������
			cHeadText[0] = '\0';
			fgets(cRaedText, sizeof(cRaedText), pFile);	// �ꕶ��ǂݍ���
			sscanf(cRaedText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������
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

				// ���[�V�����Z�b�g��������
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					// ���f���̏�����
					nCntKeySet = 0;
					// �G���h���[�V�����Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						// ������
						cHeadText[0] = '\0';
						fgets(cRaedText, sizeof(cRaedText), pFile);
						sscanf(cRaedText, "%s", &cHeadText);

						// ���[�v���邩�ǂ������ǂݍ���
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cRaedText, "%s %s %d",
								&cDie, &cDie,
								&pMotion[nCntMotion].nLoop);
						}
						// �L�[�����ǂݍ���
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cRaedText, "%s %s %d", &cDie, &cDie, &pMotion[nCntMotion].nNumKey);
							// ���[�V����������
							pMotion[nCntMotion].KeyInfo = new KEY_INFO[pMotion[nCntMotion].nNumKey];
						}

						// �����蔻����ǂݍ���
						else if (strcmp(cHeadText, "COLLISION") == 0)
						{
							sscanf(cRaedText, "%s %s %d %f %f %f %f %d %d",
								&cDie, &cDie,
								&pMotion[nCntMotion].Collision_nParts,
								&pMotion[nCntMotion].Collision_Ofset.x,
								&pMotion[nCntMotion].Collision_Ofset.y,
								&pMotion[nCntMotion].Collision_Ofset.z,
								&pMotion[nCntMotion].Collision_Radius,
								&pMotion[nCntMotion].Collision_StartFram,
								&pMotion[nCntMotion].Collision_EndFram);
						}

						// �_���[�W���ǂݍ���
						else if (strcmp(cHeadText, "COLLISION_DAMAGE") == 0)
						{
							sscanf(cRaedText, "%s %s %d",
								&cDie, &cDie,
								&pMotion[nCntMotion].Collision_Damage);
						}

						// �O�Տ��ǂݍ���
						else if (strcmp(cHeadText, "ORBIT") == 0)
						{
							sscanf(cRaedText, "%s %s %d %f %f %f %d %d %d",
								&cDie, &cDie,
								&pMotion[nCntMotion].Orbit_nParts,
								&pMotion[nCntMotion].Orbit_Ofset.x,
								&pMotion[nCntMotion].Orbit_Ofset.y,
								&pMotion[nCntMotion].Orbit_Ofset.z,
								&pMotion[nCntMotion].Orbit_Mesh,
								&pMotion[nCntMotion].Orbit_StartFram,
								&pMotion[nCntMotion].Orbit_EndFram);

							// �L�����N�^�[�^�C�v
							//pMotion[nCntMotion].Orbit_nType = TRAJECTORYTYPE_PLAYER;

							// �g�p���
							pMotion[nCntMotion].Orbit_bUse = true;
						}

						// �L�[���ǂݍ���
						else if (strcmp(cHeadText, "KEYSET") == 0)
						{
							// ������
							cHeadText[0] = '\0';
							fgets(cRaedText, sizeof(cRaedText), pFile);
							sscanf(cRaedText, "%s", &cHeadText);

							// �t���[�����ǂݍ���
							if (strcmp(cHeadText, "FRAME") == 0)
							{
								// �t���[����
								sscanf(cRaedText, "%s %s %d",
									&cDie, &cDie,
									&pMotion[nCntMotion].KeyInfo[nCntKeySet].nFrame);
							}

							// �L�[�̏�����
							nCntKey = 0;
							// ���f��������
							pMotion[nCntMotion].KeyInfo[nCntKeySet].Key = new KEY[nMaxkey];
							// �G���h�L�[�Z�b�g������܂Ń��[�v
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								// ������
								cHeadText[0] = '\0';
								fgets(cRaedText, sizeof(cRaedText), pFile);
								sscanf(cRaedText, "%s", &cHeadText);

								// �L�[���ǂݍ���
								if (strcmp(cHeadText, "KEY") == 0)
								{
									// �G���h�L�[������܂Ń��[�v
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cRaedText, sizeof(cRaedText), pFile);
										sscanf(cRaedText, "%s", &cHeadText);

										// �ʒu���ǂݍ���
										if (strcmp(cHeadText, "POS") == 0)
										{
											// �t���[����
											sscanf(cRaedText, "%s %s %f %f %f",
												&cDie, &cDie,
												&pMotion[nCntMotion].KeyInfo[nCntKeySet].Key[nCntKey].pos.x,
												&pMotion[nCntMotion].KeyInfo[nCntKeySet].Key[nCntKey].pos.y,
												&pMotion[nCntMotion].KeyInfo[nCntKeySet].Key[nCntKey].pos.z);

											// �p�[�c�̈ʒu����������
											pMotion[nCntMotion].KeyInfo[nCntKeySet].Key[nCntKey].pos += pOffset[nCntKey].pos;
										}

										// ��]���ǂݍ���
										else if (strcmp(cHeadText, "ROT") == 0)
										{
											// �t���[����
											sscanf(cRaedText, "%s %s %f %f %f",
												&cDie, &cDie,
												&pMotion[nCntMotion].KeyInfo[nCntKeySet].Key[nCntKey].rot.x,
												&pMotion[nCntMotion].KeyInfo[nCntKeySet].Key[nCntKey].rot.y,
												&pMotion[nCntMotion].KeyInfo[nCntKeySet].Key[nCntKey].rot.z);
											// �p�[�c�̈ʒu����������
											pMotion[nCntMotion].KeyInfo[nCntKeySet].Key[nCntKey].rot += pOffset[nCntKey].rot;
										}
									}
									// �J�E���g�L�[
									nCntKey++;
								}
							}
							// �J�E���g���f��
							nCntKeySet++;
						}
					}
					// �J�E���g�v���C���[
					nCntMotion++;
				}
			}
		}

		// �t�@�C����
		fclose(pFile);
	}

	// �J���Ȃ�
	else
	{
		MessageBox(NULL, "�v���C���[�f�[�^�̓ǂݍ��݂Ɏ��s���܂���", "�x���I", MB_ICONWARNING);
	}
}

// ----------------------------------------
// ���̔j���ݒ�
// ----------------------------------------
void CMotion::UnLoad(
	MOTION * pMotion,
	int nMaxMotion
)
{
	// �ϐ��錾
	int	nCntMotion = 0;		// ���[�V�����J�E���g
	int	nCntKeySet = 0;		// �t���[����6

	for (nCntMotion = 0; nCntMotion < nMaxMotion; nCntMotion++)
	{
		// �L�[�̔j��
		for (nCntKeySet = 0; nCntKeySet < pMotion[nCntMotion].nNumKey; nCntKeySet++)
		{
			if (pMotion[nCntMotion].KeyInfo[nCntKeySet].Key != NULL)
			{
				delete[] pMotion[nCntMotion].KeyInfo[nCntKeySet].Key;
				pMotion[nCntMotion].KeyInfo[nCntKeySet].Key = NULL;
			}
		}

		if (pMotion[nCntMotion].KeyInfo != NULL)
		{
			// �L�[���̔j��
			//delete[] pMotion[nCntMotion].KeyInfo;
			pMotion[nCntMotion].KeyInfo = NULL;
		}
	}
	delete[] pMotion;
	pMotion = NULL;
}