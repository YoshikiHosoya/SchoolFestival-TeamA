//*************************************************************************************************************
//
// 3D�p�[�e�B�N���̏���[particle.h]
// Author : Fujiwara Masato
//
//*************************************************************************************************************
//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "3Dparticle.h"
#include "3Deffect.h"

//-------------------------------------------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-------------------------------------------------------------------------------------------------------------
C3DParticle::PARTICLE_OFFSET C3DParticle::m_ParticleOffset[C3DParticle::OFFSET_ID_MAX] = {};

//-------------------------------------------------------------------------------------------------------------
// �R���X�g���N�^
//-------------------------------------------------------------------------------------------------------------
C3DParticle::C3DParticle():CScene(ACTOR_3DPARTICLE,LAYER_3DPARTICLE)
{
}

//-------------------------------------------------------------------------------------------------------------
// �f�X�g���N�^
//-------------------------------------------------------------------------------------------------------------
C3DParticle::~C3DParticle()
{
}

//-------------------------------------------------------------------------------------------------------------
// ������
//-------------------------------------------------------------------------------------------------------------
void C3DParticle::Init(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// �I��
//-------------------------------------------------------------------------------------------------------------
void C3DParticle::Uninit(void)
{

}

//-------------------------------------------------------------------------------------------------------------
// �X�V
//-------------------------------------------------------------------------------------------------------------
void C3DParticle::Update(void)
{
	m_nFlameCount++;

	if (m_nFlameCount > m_ParticleOffset[m_offsetID].nFrame)
	{
		Release();
	}
	else
	{
		// �ϐ��錾
		D3DXVECTOR3	move;		// �ړ���
		D3DXVECTOR3	pos;		// �ʒu
		D3DXCOLOR	col;		// �F
		float		fRadius;	// ���a
		int			nLife;		// ���C�t
		float		fSpeed;		// ���x
		float		fAngle[3];		// �p�x

		// �ݒ萔���[�v
		for (int nCntEffect = 0; nCntEffect < m_ParticleOffset[m_offsetID].nNumber; nCntEffect++)
		{
			if (m_ParticleOffset[m_offsetID].pCol != NULL)
			{
				col = *m_ParticleOffset[m_offsetID].pCol;
			}
			else
			{
				col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			}
			// ���a�̐ݒ�
			if (m_ParticleOffset[m_offsetID].pnRadiusRand == NULL &&
				m_ParticleOffset[m_offsetID].pfRadius == NULL)
			{// �ǂ������񂪂Ȃ��Ƃ�
				fRadius = 0.0f;
			}
			else if(m_ParticleOffset[m_offsetID].pnRadiusRand != NULL)
			{// �����_���ɏ�񂪂���Ƃ�
				fRadius = (rand() % m_ParticleOffset[m_offsetID].pnRadiusRand->nMax + m_ParticleOffset[m_offsetID].pnRadiusRand->nMin) * 0.1f;
			}
			else
			{// ����ȊO
				fRadius = *m_ParticleOffset[m_offsetID].pfRadius;
			}

			// ���C�t�̐ݒ�
			if (m_ParticleOffset[m_offsetID].pnLifeRand == NULL &&
				m_ParticleOffset[m_offsetID].pnLife == NULL)
			{// �ǂ������񂪂Ȃ��Ƃ�
				nLife = 0;
			}
			else if (m_ParticleOffset[m_offsetID].pnLifeRand != NULL)
			{// �����_���ɏ�񂪂���Ƃ�
				nLife = (rand() % m_ParticleOffset[m_offsetID].pnLifeRand->nMax + m_ParticleOffset[m_offsetID].pnLifeRand->nMin);
			}
			else
			{// ����ȊO
				nLife = *m_ParticleOffset[m_offsetID].pnLife;
			}

			// ���x�̐ݒ�
			if (m_ParticleOffset[m_offsetID].pnSpeedRand == NULL &&
				m_ParticleOffset[m_offsetID].pfSpeed == NULL)
			{// �ǂ������񂪂Ȃ��Ƃ�
				fSpeed = 0.0f;
			}
			else if (m_ParticleOffset[m_offsetID].pnSpeedRand != NULL)
			{// �����_���ɏ�񂪂���Ƃ�
				fSpeed = (float)(rand() % m_ParticleOffset[m_offsetID].pnSpeedRand->nMax + m_ParticleOffset[m_offsetID].pnSpeedRand->nMin);
			}
			else
			{// ����ȊO
				fSpeed = *m_ParticleOffset[m_offsetID].pfSpeed;
			}

			// �p�x�̐ݒ�
			if (m_ParticleOffset[m_offsetID].pnAngleRand == NULL &&
				m_ParticleOffset[m_offsetID].pfAngle == NULL)
			{// �ǂ������񂪂Ȃ��Ƃ�
				fAngle[0] = 0.0f;
				fAngle[1] = 0.0f;
				fAngle[2] = 0.0f;
			}
			else if (m_ParticleOffset[m_offsetID].pnAngleRand != NULL)
			{// �����_���ɏ�񂪂���Ƃ�
				fAngle[0] = (rand() % m_ParticleOffset[m_offsetID].pnAngleRand->nMax + m_ParticleOffset[m_offsetID].pnAngleRand->nMin)*0.01f;
				fAngle[1] = (rand() % m_ParticleOffset[m_offsetID].pnAngleRand->nMax + m_ParticleOffset[m_offsetID].pnAngleRand->nMin)*0.01f;
				fAngle[2] = (rand() % m_ParticleOffset[m_offsetID].pnAngleRand->nMax + m_ParticleOffset[m_offsetID].pnAngleRand->nMin)*0.01f;
			}
			else
			{// ����ȊO
				fAngle[0] = *m_ParticleOffset[m_offsetID].pfAngle;
				fAngle[1] = *m_ParticleOffset[m_offsetID].pfAngle;
				fAngle[2] = *m_ParticleOffset[m_offsetID].pfAngle;
			}

			if (m_ParticleOffset[m_offsetID].type == TYPE_CHARGE)
			{
				// ���_����̋����̐ݒ�
				float fLength;

				//(m_nLengthRand != NULL) ?
				//(rand() % m_nLengthRand->nMax + m_nLengthRand->nMin)*0.1f :
				//m_fLength;
				if (m_ParticleOffset[m_offsetID].pnLengthRand == NULL &&
					m_ParticleOffset[m_offsetID].pfLength == NULL)
				{// �ǂ������񂪂Ȃ��Ƃ�
					fLength = 0.0f;
				}
				else if (m_ParticleOffset[m_offsetID].pnLengthRand != NULL)
				{// �����_���ɏ�񂪂���Ƃ�
					fLength = (rand() % m_ParticleOffset[m_offsetID].pnLengthRand->nMax + m_ParticleOffset[m_offsetID].pnLengthRand->nMin)*0.1f;
				}
				else
				{// ����ȊO
					fLength = *m_ParticleOffset[m_offsetID].pfLength;
				}


				// �ʒu�̐ݒ�
				if (m_ParticleOffset[m_offsetID].pPos != NULL)
				{
					pos =
					{
						m_ParticleOffset[m_offsetID].pPos->x + sinf(fAngle[0] + *m_ParticleOffset[m_offsetID].pfAngle)*sinf(fAngle[1] + *m_ParticleOffset[m_offsetID].pfAngle)*fLength,
						m_ParticleOffset[m_offsetID].pPos->y + cosf(fAngle[1] + *m_ParticleOffset[m_offsetID].pfAngle)*sinf(fAngle[2] + *m_ParticleOffset[m_offsetID].pfAngle)*fLength,
						m_ParticleOffset[m_offsetID].pPos->z + cosf(fAngle[0] + *m_ParticleOffset[m_offsetID].pfAngle)*cosf(fAngle[2] + *m_ParticleOffset[m_offsetID].pfAngle)*fLength
					};
				}

				// �x�N�g���̍쐬
				D3DXVECTOR3 vec = *m_ParticleOffset[m_offsetID].pPos - pos;
				// �x�N�g���̐��K��
				D3DXVec3Normalize(&vec, &vec);
				// �ړ��ʂɑ��
				move.x = (vec.x*fSpeed)*m_ParticleOffset[m_offsetID].pSpeedRate->x;
				move.y = (vec.y*fSpeed)*m_ParticleOffset[m_offsetID].pSpeedRate->y;
				move.z = (vec.z*fSpeed)*m_ParticleOffset[m_offsetID].pSpeedRate->z;
			}
			else
			{
				// �ʒu�̐ݒ�
				pos = *m_ParticleOffset[m_offsetID].pPos;

				// �ړ��ʂ̐ݒ�
				move =
				{
					sinf(fAngle[0])*sinf(fAngle[1])*fSpeed*m_ParticleOffset[m_offsetID].pSpeedRate->x,
					cosf(fAngle[1])*sinf(fAngle[2])*fSpeed*m_ParticleOffset[m_offsetID].pSpeedRate->y,
					cosf(fAngle[0])*cosf(fAngle[2])*fSpeed*m_ParticleOffset[m_offsetID].pSpeedRate->z
				};
			}
			C3DEffect::Set3DEffect(
				(C3DEffect::EFFECT_TYPE)m_ParticleOffset[m_offsetID].nEffeType, m_ParticleOffset[m_offsetID].nEffeTexType,
				pos + m_Origin, move, col, fRadius, nLife);
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// �`��
//-------------------------------------------------------------------------------------------------------------
void C3DParticle::Draw(void)
{
}

//-------------------------------------------------------------------------------------------------------------
// ����
//-------------------------------------------------------------------------------------------------------------
C3DParticle * C3DParticle::Create(PARTICLE_OFFSET_ID OffsetID, CONST D3DXVECTOR3 origin)
{
	C3DParticle *p3DParticle = new C3DParticle;
	p3DParticle->SetParticle(OffsetID);
	p3DParticle->SetOrigin(origin);
	return p3DParticle;
}

//-------------------------------------------------------------------------------------------------------------
// �p�[�e�B�N���̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void C3DParticle::SetParticle(PARTICLE_OFFSET_ID OffsetID)
{
	m_offsetID = OffsetID;
}

//-------------------------------------------------------------------------------------------------------------
// �ǂݍ���
//-------------------------------------------------------------------------------------------------------------
void C3DParticle::Load(void)
{
	// �ϐ��錾
	FILE *pFile = NULL;				// �t�@�C���̃|�C���^
	char cRead[128];				// �ǂݍ��ݗp
	char cComp[128];				// ��r�p
	char cEmpty[128];				// �v��Ȃ����̗p
	int nCntError = 0;				// �G���[�p
	int nCntOffset = 0;				// �I�t�Z�b�g�̃J�E���g

	// �ꎞ�ۑ��p
	INTEGER2 Save;
	// �t�@�C�����J����Ă��Ȃ�������
	if ((pFile = fopen("data/LOAD/ParticleInfo.txt", "r")) == NULL)
	{
		return;
	}

	while (strcmp(cComp, "SCRIPT") != 0)
	{
		// 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);

		// �G���[�J�E���g���C���N�������g
		nCntError++;
		if (nCntError > 1048576)
		{// �G���[
			nCntError = 0;
			return;
		}
	}

	while (strcmp(cComp, "END_SCRIPT") != 0)
	{// END_SCRIPT�܂Ń��[�v
	 // 1�s�ǂݍ���
		fgets(cRead, sizeof(cRead), pFile);
		// �ǂݍ���Ǖ�������
		sscanf(cRead, "%s", &cComp);

		// �G���[�J�E���g���C���N�������g
		nCntError++;
		if (nCntError > 1048576)
		{// �G���[
			nCntError = 0;
			fclose(pFile);
			return;
		}
		else if (strcmp(cComp, "OFFSET") == 0)
		{
			while (strcmp(cComp, "END_OFFSET") != 0)
			{
				// 1�s�ǂݍ���
				fgets(cRead, sizeof(cRead), pFile);
				// �ǂݍ���Ǖ�������
				sscanf(cRead, "%s", &cComp);
				if (strcmp(cComp, "IF") == 0)
				{
					// �ǂݍ���Ǖ�������
					sscanf(cRead, "%s %s", &cEmpty, &cComp);
					if (strcmp(cComp, "POSRAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty , &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);

								if (strcmp(cComp, "POSX") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty, &Save.nMax, &Save.nMin);
									if (Save.nMax != -1 && Save.nMin != -1)
									{// �������̊m��
										m_ParticleOffset[nCntOffset].pPosXRand = new INTEGER2;
										// �ő�
										m_ParticleOffset[nCntOffset].pPosXRand->nMax = Save.nMax;
										// �ŏ�
										m_ParticleOffset[nCntOffset].pPosXRand->nMin = Save.nMin;
										Save.nMax = -1;
										Save.nMin = -1;
									}
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "POSY") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty, &Save.nMax, &Save.nMin);
									if (Save.nMax != -1 && Save.nMin != -1)
									{// �������̊m��
										m_ParticleOffset[nCntOffset].pPosYRand = new INTEGER2;
										// �ő�
										m_ParticleOffset[nCntOffset].pPosYRand->nMax = Save.nMax;
										// �ŏ�
										m_ParticleOffset[nCntOffset].pPosYRand->nMin = Save.nMin;
										Save.nMax = -1;
										Save.nMin = -1;
									}

									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "POSZ") == 0)
								{
									sscanf(cRead, "%s %s %d %d", &cEmpty, &cEmpty, &Save.nMax, &Save.nMin);
									if (Save.nMax != -1 && Save.nMin != -1)
									{// �������̊m��
										m_ParticleOffset[nCntOffset].pPosZRand = new INTEGER2;
										// �ő�
										m_ParticleOffset[nCntOffset].pPosZRand->nMax = Save.nMax;
										// �ŏ�
										m_ParticleOffset[nCntOffset].pPosZRand->nMin = Save.nMin;
										Save.nMax = -1;
										Save.nMin = -1;
									}

									// ������̏�����
									cComp[0] = '\0';
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "LENGTHRAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMax);
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMin);
									// ������̏�����
									cComp[0] = '\0';
								}

								if (Save.nMax != -1 && Save.nMin != -1)
								{
									// �������̊m��
									m_ParticleOffset[nCntOffset].pnLengthRand = new INTEGER2;
									// �ő�
									m_ParticleOffset[nCntOffset].pnLengthRand->nMax = Save.nMax;
									// �ŏ�
									m_ParticleOffset[nCntOffset].pnLengthRand->nMin = Save.nMin;
									Save.nMax = -1;
									Save.nMin = -1;
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "RADIUSRAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMax);
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMin);
									// ������̏�����
									cComp[0] = '\0';
								}
								if (Save.nMax != -1 && Save.nMin != -1)
								{
									// �������̊m��
									m_ParticleOffset[nCntOffset].pnRadiusRand = new INTEGER2;
									// �ő�
									m_ParticleOffset[nCntOffset].pnRadiusRand->nMax = Save.nMax;
									// �ŏ�
									m_ParticleOffset[nCntOffset].pnRadiusRand->nMin = Save.nMin;
									Save.nMax = -1;
									Save.nMin = -1;
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "ANGLERAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMax);
									// ������̏�����
									cComp[0] = '\0';

								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMin);
									// ������̏�����
									cComp[0] = '\0';

								}
								if (Save.nMax != -1 && Save.nMin != -1)
								{
									// �������̊m��
									m_ParticleOffset[nCntOffset].pnAngleRand = new INTEGER2;
									// �ő�
									m_ParticleOffset[nCntOffset].pnAngleRand->nMax = Save.nMax;
									// �ŏ�
									m_ParticleOffset[nCntOffset].pnAngleRand->nMin = Save.nMin;
									Save.nMax = -1;
									Save.nMin = -1;
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "SPEEDRAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMax);
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMin);
									// ������̏�����
									cComp[0] = '\0';
								}
								if (Save.nMax != -1 && Save.nMin != -1)
								{
									// �������̊m��
									m_ParticleOffset[nCntOffset].pnSpeedRand = new INTEGER2;
									// �ő�
									m_ParticleOffset[nCntOffset].pnSpeedRand->nMax = Save.nMax;
									// �ŏ�
									m_ParticleOffset[nCntOffset].pnSpeedRand->nMin = Save.nMin;
									Save.nMax = -1;
									Save.nMin = -1;
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
					else if (strcmp(cComp, "LIFERAND") == 0)
					{
						// �ǂݍ���Ǖ�������
						sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);
						if (strcmp(cComp, "NULL") != 0)
						{
							while (strcmp(cComp, "}") != 0)
							{
								// 1�s�ǂݍ���
								fgets(cRead, sizeof(cRead), pFile);
								// �ǂݍ���Ǖ�������
								sscanf(cRead, "%s", &cComp);
								if (strcmp(cComp, "MAX") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMax);
									// ������̏�����
									cComp[0] = '\0';
								}
								else if (strcmp(cComp, "MIN") == 0)
								{
									sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty, &Save.nMin);
									// ������̏�����
									cComp[0] = '\0';
								}
								if (Save.nMax != -1 && Save.nMin != -1)
								{
									// �������̊m��
									m_ParticleOffset[nCntOffset].pnLifeRand = new INTEGER2;
									// �ő�
									m_ParticleOffset[nCntOffset].pnLifeRand->nMax = Save.nMax;
									// �ŏ�
									m_ParticleOffset[nCntOffset].pnLifeRand->nMin = Save.nMin;
									Save.nMax = -1;
									Save.nMin = -1;
								}
							}
							// ������̏�����
							cComp[0] = '\0';
						}
						// ������̏�����
						cComp[0] = '\0';
					}
				}
				else if (strcmp(cComp, "POS") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						m_ParticleOffset[nCntOffset].pPos = new D3DXVECTOR3;
						sscanf(cRead, "%s %s %f %f %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].pPos->x,
							&m_ParticleOffset[nCntOffset].pPos->y,
							&m_ParticleOffset[nCntOffset].pPos->z);
					}

					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "LENGTH") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						m_ParticleOffset[nCntOffset].pfLength = new float;
						sscanf(cRead, "%s %s %f", &cEmpty, &cEmpty,
							m_ParticleOffset[nCntOffset].pfLength);
					}
					// ������̏�����
					cComp[0] = '\0';

				}
				else if (strcmp(cComp, "COL") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						m_ParticleOffset[nCntOffset].pCol = new D3DXCOLOR;
						sscanf(cRead, "%s %s %f %f %f %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].pCol->r,
							&m_ParticleOffset[nCntOffset].pCol->g,
							&m_ParticleOffset[nCntOffset].pCol->b,
							&m_ParticleOffset[nCntOffset].pCol->a);
					}

					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "RADIUS") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						m_ParticleOffset[nCntOffset].pfRadius = new float;
						sscanf(cRead, "%s %s %f", &cEmpty, &cEmpty,
							m_ParticleOffset[nCntOffset].pfRadius);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "SPEED") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						m_ParticleOffset[nCntOffset].pfSpeed = new float;
						sscanf(cRead, "%s %s %f", &cEmpty, &cEmpty,
							m_ParticleOffset[nCntOffset].pfSpeed);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "LIFE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						m_ParticleOffset[nCntOffset].pnLife = new int;
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							m_ParticleOffset[nCntOffset].pnLife);
					}
					// ������̏�����
					cComp[0] = '\0';
				}

				else if (strcmp(cComp, "FRAME") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nFrame);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "NUMBER") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nNumber);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "TEXTYPE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nEffeTexType);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "EFFETYPE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].nEffeType);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "PARTICLETYPE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						sscanf(cRead, "%s %s %d", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].type);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
				else if (strcmp(cComp, "SPEEDRATE") == 0)
				{
					// ������̏�����
					cComp[0] = '\0';
					sscanf(cRead, "%s %s %s", &cEmpty, &cEmpty, &cComp);

					if (strcmp(cComp, "NULL") != 0)
					{
						m_ParticleOffset[nCntOffset].pSpeedRate = new D3DXVECTOR3;
						sscanf(cRead, "%s %s %f %f %f", &cEmpty, &cEmpty,
							&m_ParticleOffset[nCntOffset].pSpeedRate->x,
							&m_ParticleOffset[nCntOffset].pSpeedRate->y,
							&m_ParticleOffset[nCntOffset].pSpeedRate->z);
					}
					// ������̏�����
					cComp[0] = '\0';
				}
			}
			// �I�t�Z�b�g�J�E���g��i�߂�
			nCntOffset++;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// �J��
//-------------------------------------------------------------------------------------------------------------
void C3DParticle::Unload(void)
{
	for (int nCntOffset = 0; nCntOffset < C3DParticle::OFFSET_ID_MAX; nCntOffset++)
	{
		if (m_ParticleOffset[nCntOffset].pPosXRand != NULL)
		{// X���W�̃����_���̊J��
			delete m_ParticleOffset[nCntOffset].pPosXRand;
			m_ParticleOffset[nCntOffset].pPosXRand = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pPosYRand != NULL)
		{// Y���W�̃����_���̊J��
			delete m_ParticleOffset[nCntOffset].pPosYRand;
			m_ParticleOffset[nCntOffset].pPosYRand = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pPosZRand != NULL)
		{// Z���W�̃����_���̊J��
			delete m_ParticleOffset[nCntOffset].pPosZRand;
			m_ParticleOffset[nCntOffset].pPosZRand = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pnLengthRand != NULL)
		{// ���_���������_���̊J��
			delete m_ParticleOffset[nCntOffset].pnLengthRand;
			m_ParticleOffset[nCntOffset].pnLengthRand = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pnAngleRand != NULL)
		{// �����_���p�x�̊J��
			delete m_ParticleOffset[nCntOffset].pnAngleRand;
			m_ParticleOffset[nCntOffset].pnAngleRand = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pnLifeRand != NULL)
		{// ���C�t�̃����_���̊J��
			delete m_ParticleOffset[nCntOffset].pnLifeRand;
			m_ParticleOffset[nCntOffset].pnLifeRand = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pnRadiusRand != NULL)
		{// �����_�����a�̊J��
			delete m_ParticleOffset[nCntOffset].pnRadiusRand;
			m_ParticleOffset[nCntOffset].pnRadiusRand = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pnSpeedRand != NULL)
		{// �����_�����x�̊J��
			delete m_ParticleOffset[nCntOffset].pnSpeedRand;
			m_ParticleOffset[nCntOffset].pnSpeedRand = NULL;
		}

		if (m_ParticleOffset[nCntOffset].pPos != NULL)
		{// ���_����̈ʒu�̊J��
			delete m_ParticleOffset[nCntOffset].pPos;
			m_ParticleOffset[nCntOffset].pPos = NULL;
		}

		if (m_ParticleOffset[nCntOffset].pfLength != NULL)
		{// ���_����̋����̊J��
			delete m_ParticleOffset[nCntOffset].pfLength;
			m_ParticleOffset[nCntOffset].pfLength = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pCol != NULL)
		{// �F�̊J��
			delete m_ParticleOffset[nCntOffset].pCol;
			m_ParticleOffset[nCntOffset].pCol = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pfRadius != NULL)
		{// ���a�̊J��
			delete m_ParticleOffset[nCntOffset].pfRadius;
			m_ParticleOffset[nCntOffset].pfRadius = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pfSpeed != NULL)
		{// ���x�̊J��
			delete m_ParticleOffset[nCntOffset].pfSpeed;
			m_ParticleOffset[nCntOffset].pfSpeed = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pnLife != NULL)
		{// ���C�t�̊J��
			delete m_ParticleOffset[nCntOffset].pnLife;
			m_ParticleOffset[nCntOffset].pnLife = NULL;
		}
		if (m_ParticleOffset[nCntOffset].pSpeedRate != NULL)
		{// ���x�̕ω��ʂ̊J��
			delete m_ParticleOffset[nCntOffset].pSpeedRate;
			m_ParticleOffset[nCntOffset].pSpeedRate = NULL;
		}
	}
}

//-------------------------------------------------------------------------------------------------------------
// ���_�ʒu�̐ݒ�
//-------------------------------------------------------------------------------------------------------------
void C3DParticle::SetOrigin(CONST D3DXVECTOR3 & Origin)
{
	m_Origin = Origin;
}

