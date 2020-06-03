//=============================================================================
// �L�����N�^�[���f���������� [Character.cpp] : NORI
//=============================================================================
#include "Character.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "createmap.h"
#include "Xinput.h"

#define MAX_RAY_LENGTH (35)		//Ray�̍ő�̒���
#define RAY_FIRST_POINT (40.0f)	//Ray�̎n�_
char *CCharacter::m_LoadFileName = { "data/Load/LoadOffset01.txt" };

CCharacter::CCharacter(OBJ_TYPE type) :CScene(type)
{
	SetObjType(OBJTYPE_PLAYER);
}

CCharacter::~CCharacter()
{
}
//====================================================================
//������
//====================================================================
HRESULT CCharacter::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Life = 50;
	m_state = CHARACTER_STATE_NORMAL;
	LoadOffset();
	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CCharacter::Uninit(void)
{
}
//====================================================================
//�X�V
//====================================================================
void CCharacter::Update(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	m_posold = m_pos;
	m_MotionOld = m_MotionType;
	//�����̒�R
	m_move.x += (0 - m_move.x)* 0.2f;
	m_move.z += (0 - m_move.z)* 0.2f;
	m_move.y -= 1;
	m_pos += m_move;

	if (m_pos.y < 0)
	{
		m_move.y = 0;
		m_pos.y = 0;
	}
	//�ڕW�_�ƌ��݂̍����i��]�j
	float diffRot = m_rotDest.y - m_rot.y;
	//3.14�̒��ߕ��̏������i��]�j
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
	if (diffRot > D3DX_PI)
	{
		diffRot -= D3DX_PI * 2;
	}
	else if (diffRot < -D3DX_PI)
	{
		diffRot += D3DX_PI * 2;
	}
	//�X�e�[�^�X�̏���
	switch (m_state)
	{
	case CHARACTER_STATE_NORMAL:
		break;
	case CHARACTER_STATE_DAMAGE:
		m_nStateCnt++;
		if (m_nStateCnt % 60 == 0)
		{
			m_state = CHARACTER_STATE_NORMAL;
		}

		break;
	case CHARACTER_STATE_INVINCIBLE:
		m_nStateCnt++;
		if (m_nStateCnt % 30 == 0)
		{
			m_state = CHARACTER_STATE_NORMAL;
		}
		break;
	}
	//���񂾂Ƃ�
	if (m_Life <= 0)
	{
		CFADE::SetFade(CManager::MODE_RESULT);
		Rerease();
	}
	m_MotionType = PLAYER_MOTION_WALK;
	RayCollision();
}
//====================================================================
//�`��
//====================================================================
void CCharacter::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y,
		m_rot.x,
		m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	//���f���̕`��
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		m_vModelList[nCnt]->Draw(m_mtxWorld);
	}
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CCharacter *CCharacter::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	CCharacter*pSceneX;
	pSceneX = new CCharacter(OBJTYPE_PLAYER);
	pSceneX->Init();
	return pSceneX;
}
//====================================================================
//���f���̃��[��
//====================================================================
void CCharacter::Move(float move, float fdest)
{
	m_move.x += sinf(move * -D3DX_PI) * 1.0f;
	m_move.z += cosf(move * -D3DX_PI) * 1.0f;
	m_rotDest.y = fdest *  D3DX_PI;
}
//====================================================================
//�|�W�V�����̐ݒ�
//====================================================================
void CCharacter::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//====================================================================
//�O�̃|�W�V�����̐ݒ�
//====================================================================
void CCharacter::SetPotisionOld(D3DXVECTOR3 posOld)
{
	m_posold = posOld;
}
//====================================================================
//���[�u�̐ݒ�
//====================================================================
void CCharacter::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//====================================================================
//��]�̐ݒ�
//====================================================================
void CCharacter::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}
//====================================================================
//�_���[�W���󂯂����̏���
//====================================================================
void CCharacter::AddDamage(int Damage)
{
	m_state = CHARACTER_STATE_DAMAGE;
	int Life = GetLife();
	Life -= Damage;
	SetLife(Life);
}
//====================================================================
//��]�̍����̐ݒ�
//====================================================================
void CCharacter::SetRotDest(D3DXVECTOR3 rotDest)
{
	m_rotDest = rotDest;
}
//====================================================================
//�̗͂̐ݒ�
//====================================================================
void CCharacter::SetLife(int Life)
{
	m_Life = Life;
}
//====================================================================
//�L������Ԃ̐ݒ�
//====================================================================
void CCharacter::SetState(CHARACTER_STATE state)
{
	m_state = state;
}
//====================================================================
//�}�g���b�N�X�̐ݒ�
//====================================================================
void CCharacter::SetMtxWorld(D3DXMATRIX mtxWorld)
{
	m_mtxWorld = mtxWorld;
}
//====================================================================
//��]�̍����̎擾
//====================================================================
D3DXVECTOR3 CCharacter::GetRotDest(void)
{
	return m_rotDest;
}
//====================================================================
//�L�����N�^�[�̏�Ԃ̎擾
//====================================================================
CCharacter::CHARACTER_STATE CCharacter::GetCharacterState(void)
{
	return m_state;
}
//====================================================================
//�|�W�V�����̎擾
//====================================================================
D3DXVECTOR3 CCharacter::GetPosition(void)
{
	return m_pos;
}
//====================================================================
//�O�̃|�W�V�����̎擾
//====================================================================
D3DXVECTOR3 CCharacter::GetPositionOld(void)
{
	return m_posold;
}
//====================================================================
//���[�u�̎擾
//====================================================================
D3DXVECTOR3 &CCharacter::GetMove(void)
{
	return m_move;
}
//====================================================================
//��]�̎擾
//====================================================================
D3DXVECTOR3 CCharacter::GetRot(void)
{
	return m_rot;
}
//====================================================================
//�̗͂̎擾
//====================================================================
int CCharacter::GetLife(void)
{
	return m_Life;
}
//====================================================================
//�}�g���b�N�X�̎擾
//====================================================================
D3DXMATRIX CCharacter::GetMtxWorld(void)
{
	return m_mtxWorld;
}
//====================================================================
//�����蔻��
//====================================================================
void CCharacter::RayCollision(void)
{
	CCreateMap *pCreateMap;
	pCreateMap = CManager::GetGame()->GetCreateMap();
	// �n�`����
	BOOL  bIsHit = false;
	float fLandDistance = 0;
	DWORD dwHitIndex = -1;
	float fHitU = 0;
	float fHitV = 0;
	D3DXMATRIX invmat;		//	�t�s����i�[����ϐ�
	D3DXVECTOR3 m_posAfter;	//	�t�s��ŏo�����I�_�����i�[����
	D3DXVECTOR3 m_posBefore;//	�I�_�����i�[����
	D3DXVECTOR3 direction;	//	�ϊ���̈ʒu�A�������i�[����ϐ��F
	std::vector<float> vDistance;//�����̔z��ۑ�
	float fData = 0.0f;
	for (int nCnt = 0; nCnt < pCreateMap->GetMaxModel(); nCnt++)
	{
		D3DXMatrixInverse(&invmat, NULL, pCreateMap->GetModel(nCnt)->GetMatrix());	//	�t�s��̎擾
																					//	�t�s����g�p���A���C�n�_����ϊ��@�ʒu�ƌ����ŕϊ�����֐����قȂ�̂ŗv����
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(m_pos.x, m_pos.y + RAY_FIRST_POINT, m_pos.z), &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), &invmat);
		//	���C��������ϊ�
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));
		//Ray���΂�
		D3DXIntersect(pCreateMap->GetMesh(nCnt), &m_posBefore, &direction, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bIsHit == TRUE)
		{
			CDebugProc::Print("�������Ă��\n");
			vDistance.emplace_back(fLandDistance); //�����̕ۑ��ǉ�
		}
		else
		{
			CDebugProc::Print("�������Ė�����\n");
		}
	}
	//Ray�̃q�b�g���������������Ƃ�
	if (!vDistance.empty())
	{
		//�ŏ��̔�r�Ώ�
		fData = vDistance[0];
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fData)
			{
				//��r�Ώۂ���������������
				fData = vDistance[nCnt];
			}
		}
		if (fData < MAX_RAY_LENGTH)//Ray�̒����̎w�����
		{
			m_pos.y = m_pos.y - fData + MAX_RAY_LENGTH;
			m_move.y = 0;
		}
	}
	CDebugProc::Print("Ray�̒���(%f)\n", fLandDistance);
	CDebugProc::Print("�L�����̍���(%f)\n", m_pos.y);
	CDebugProc::Print("Ray����L�����̈ʒu���������l(%f)\n", m_pos.y - fLandDistance);
}
//====================================================================
//���[�V�����̃��[�h
//====================================================================
void CCharacter::LoadMotion(void)
{
	//�t�@�C���|�C���g
	FILE *pFile;
	int nCntMotion = 0;		//���[�V�����̐�
	int nCntModel = 0;		//���f���̃J�E���g
	int nCntKeySet = 0;		//�t�[���[���̕�����
	int nCntKey = 0;		//�p�[�c�̔ԍ�
	char cReadText[128];	//�����Ƃ��ēǂݎ��p
	char cHeadText[128];	//��r����p
	char cDie[128];			//�s�v�ȕ���

							//�t�@�C�����J��
	pFile = fopen("data/Load/PlayerMotion.txt", "r");

	//��������
	if (pFile != NULL)
	{
		//�X�N���v�g������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);	//�ꕶ��ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);		//��r�p�e�L�X�g�ɕ�������
		}
		//�X�N���v�g��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			//�G���h�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
				//���[�V�����Z�b�g��������
				if (strcmp(cHeadText, "MOTIONSET") == 0)
				{
					//�t���[���������̏�����
					nCntKeySet = 0;
					//�G���h���[�V�����Z�b�g������܂Ń��[�v
					while (strcmp(cHeadText, "END_MOTIONSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile);//�ꕶ�𔲂����
						sscanf(cReadText, "%s", &cHeadText);
						//���[�v���邩�ǂ����̏��ǂݍ���
						if (strcmp(cHeadText, "LOOP") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nLoop);
						}
						else if (strcmp(cHeadText, "NUM_KEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].nNumKey);
						}
						else if (strcmp(cHeadText, "KEYSET") == 0)
						{
							nCntKey = 0;//�L�[��񏉊���
							while (strcmp(cHeadText, "END_KEYSET") != 0)
							{
								fgets(cReadText, sizeof(cReadText), pFile);
								sscanf(cReadText, "%s", &cHeadText);

								if (strcmp(cHeadText, "FRAME") == 0)
								{
									sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerMotion[nCntMotion].key_info[nCntKeySet].nFram);
								}
								else if (strcmp(cHeadText, "KEY") == 0)
								{
									while (strcmp(cHeadText, "END_KEY") != 0)
									{
										fgets(cReadText, sizeof(cReadText), pFile);
										sscanf(cReadText, "%s", &cHeadText);
										if (strcmp(cHeadText, "POS") == 0)
										{
											//sscanf(cReadText, "%s %s %f %f %f",
											//	&cDie, &cDie,
											//	&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.x,
											//	&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.y,
											//	&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos.z);

											//m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].pos += m_vModelList[nCntKey]->GetPosition();
										}
										else if (strcmp(cHeadText, "ROT") == 0)
										{
											sscanf(cReadText, "%s %s %f %f %f",
												&cDie, &cDie,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.x,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.y,
												&m_PlayerMotion[nCntMotion].key_info[nCntKeySet].key[nCntKey].rot.z);
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
		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "���f���f�[�^�̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}
//====================================================================
//���[�V����
//====================================================================
void CCharacter::Moation(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	D3DXVECTOR3 Difrot;
	if (m_MotionType != m_MotionOld)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		if (m_Fram == 0)
		{
			if (m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram != 0)
			{
				//�ړ���ROT�̌v�Z-------------------------------------����������
				Difrot = (m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot - m_vModelList[nCnt]->GetRot());

				if (Difrot.y > D3DX_PI)
				{
					Difrot.y -= D3DX_PI * 2;
				}
				else if (Difrot.y < -D3DX_PI)
				{
					Difrot.y += D3DX_PI * 2;
				}

				if (Difrot.x > D3DX_PI)
				{
					Difrot.x -= D3DX_PI * 2;
				}
				else if (Difrot.x < -D3DX_PI)
				{
					Difrot.x += D3DX_PI * 2;
				}

				rotBET[nCnt] = Difrot / (float)m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram;
				//----------------------------------------------------����������
			}
			else
			{
				//m_vModelList[nCnt]->GetPosition() = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].pos;
				//m_vModelList[nCnt]->GetRot()		 = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot;
				//posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				//rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			}
		}

		//�t���[���ړ�--------------------------------------------����������
		if (m_Fram <= m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram)
		{
			//	m_vModelList[nCnt]->SetPosition(m_vModelList[nCnt]->GetPosition() + posBET[nCnt]);
			m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + rotBET[nCnt]);
			if (m_vModelList[nCnt]->GetRot().y > D3DX_PI)
			{
				m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() - D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
			}
			else if (m_vModelList[nCnt]->GetRot().y < -D3DX_PI)
			{
				m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + D3DXVECTOR3(0.0f, D3DX_PI * 2.0f, 0.0f));
			}
			if (m_vModelList[nCnt]->GetRot().x > D3DX_PI)
			{
				m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() - D3DXVECTOR3(D3DX_PI * 2.0f, 0.0f, 0.0f));
			}
			else if (m_vModelList[nCnt]->GetRot().x < -D3DX_PI)
			{
				m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + D3DXVECTOR3(D3DX_PI * 2.0f, 0.0f, 0.0f));
			}
		}
		//--------------------------------------------------------����������
	}
	if (m_Fram == m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram)
	{
		m_CntKeySet++;
		m_Fram = 0;
		//�L�[�Z�b�g�����K��l�Ɠ����ɂȂ�����--------------------����������
		if (m_CntKeySet == m_PlayerMotion[m_MotionType].nNumKey)
		{
			//���[�v���Ȃ��Ƃ�------------------------------------����������
			if (m_PlayerMotion[m_MotionType].nLoop == 0)
			{
				m_CntKeySet = 0;
				m_MotionType = 0;
				m_Fram = m_PlayerMotion[m_MotionType].key_info[m_CntKeySet].nFram;
			}
			//���[�v����Ƃ�--------------------------------------����������
			else if (m_PlayerMotion[m_MotionType].nLoop == 1)
			{
				m_CntKeySet = 0;
				m_MotionType = 0;
			}
		}
	}
	//�t���[�������K��l�Ɠ����ł͂Ȃ��Ƃ�------------------------����������
	else
	{
		m_Fram++;
	}
}
//====================================================================
//�I�t�Z�b�g�̓ǂݍ���
//====================================================================
void CCharacter::LoadOffset(void)
{
	char cReadText[1080];	//�����Ƃ��ēǂݎ��p
	char cHeadText[1080];	//��r����p
	char cDie[1080];		//�s�v�ȕ���
	int nCnt = 0;
	FILE *pFile;

	D3DXVECTOR3 pos;
	int nIdxParent;			//�e�̃C���f�b�N�X
	int nIdx;				//���f���̃C���f�b�N�X
	int type;

	pFile = fopen(m_LoadFileName, "r");
	if (pFile != NULL)
	{
		while (strcmp(cHeadText, "MODEL_OFFSET_END") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile);
			sscanf(cReadText, "%s", &cHeadText);
			//�z�u���郂�f���̍ő吔�̓ǂݍ���
			if (strcmp(cHeadText, "SET_START") == 0)
			{
				//END_SET������܂Ń��[�v
				while (strcmp(cHeadText, "SET_END") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					//MODEL_TYPE��������
					if (strcmp(cHeadText, "MODEL_TYPE") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&type);
					}
					//IDX��������
					else if (strcmp(cHeadText, "INDEX") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdx);
					}
					//PARENT��������
					else if (strcmp(cHeadText, "PARENT") == 0)
					{
						sscanf(cReadText, "%s %s %d",
							&cDie, &cDie,
							&nIdxParent);
					}
					//POS��������
					else if (strcmp(cHeadText, "POS") == 0)
					{
						sscanf(cReadText, "%s %s %f %f %f",
							&cDie, &cDie,
							&pos.x,
							&pos.y,
							&pos.z);
					}
					//SET_END��������쐬���ǉ�
					else if (strcmp(cHeadText, "SET_END") == 0)
					{
						CModel *pModel = CModel::Create(type , nIdx);
						pModel->SetPosition(pos);
						if (nIdxParent == -1)
						{
							pModel->SetParent(NULL);
						}
						else
						{
						pModel->SetParent(m_vModelList[nIdxParent]);
						}
						m_vModelList.emplace_back(pModel);
					}
				}
			}
		}

		fclose(pFile);
	}
	else
	{

	}

}
