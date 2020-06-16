//=============================================================================
// �L�����N�^�[���f���������� [Character.cpp] : NORI
//=============================================================================
#include "Character.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "map.h"
#include "Xinput.h"

#define MAX_RAY_LENGTH (40)		//Ray�̍ő�̒���
#define RAY_FIRST_POINT (30.0f)	//Ray�̎n�_
//�I�t�Z�b�g�̓ǂݍ��݃t�@�C��
char *CCharacter::m_LoadOffsetFileName[CHARACTER_TYPE_MAX] =
{
	{ "data/Load/PlayerOffset.txt"},
	{"data/Load/EnemyOffset.txt"},
	{"data/Load/EnemyOffset.txt"}
};
//���[�V�����̓ǂݍ��݃t�@�C��
char *CCharacter::m_LoadMotionFileName[CHARACTER_MOTION_MAX] =
{
	{ "data/Load/PlayerNeutral.txt" },
	{ "data/Load/PlayerWalk.txt" },
	{ "data/Load/PlayerAttack.txt" },
	{ "data/Load/EnemyNeutral.txt" },
	{ "data/Load/EnemyWalk.txt" },
	{ "data/Load/EnemyAttack.txt" }
};
std::vector<CCharacter::MOTION*> CCharacter::m_CharacterMotion = {};
//====================================================================
//�R���X�g���N�^
//====================================================================
CCharacter::CCharacter(OBJ_TYPE type) :CScene(type)
{
}
//====================================================================
//�f�X�g���N�^
//====================================================================
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
	m_rotDest.y = -0.5f*  D3DX_PI;
	m_bJump = false;
	m_bGravity = true;
	//�}�g���b�N�X������
	D3DXMatrixIdentity(&m_mtxWorld);
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
	m_move.y += m_move.y * -0.1f;
	if (m_bGravity == true)
	{
	m_move.y -= 0.5f;
	}

	m_pos += m_move;


	if (m_pos.y < 0)
	{
		m_move.y = 0;
		m_pos.y = 0;
	}

	if (m_move.x < 0)
	{
		m_CharacterDirection = CHARACTER_LEFT;
		CDebugProc::Print("�������Ă܂�\n");
	}
	else
	{
		m_CharacterDirection = CHARACTER_RIGHT;
		CDebugProc::Print("�E�����Ă܂�\n");
	}
	if (m_CharacterDirection == CHARACTER_DOWN)
	{
		CDebugProc::Print("�������Ă܂�\n");
	}
	else if (m_CharacterDirection == CHARACTER_UP)
	{
		CDebugProc::Print("������Ă܂�\n");
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
	//���߂����������Ǐ]����v�Z
	m_rot.y += diffRot * 0.1f;
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
		Rerease();
	}
	CDebugProc::Print("move.y:%2f\n",m_move.y);

	Moation();
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
//���[�V�����̐ݒ�
//====================================================================
void CCharacter::SetMotion(CHARACTER_MOTION_STATE type)
{
	if (m_MotionType != type)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	m_MotionType = type;
}
//====================================================================
//��]�̍����̎擾
//====================================================================
D3DXVECTOR3 &CCharacter::GetRotDest(void)
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
D3DXVECTOR3 &CCharacter::GetPosition(void)
{
	return m_pos;
}
//====================================================================
//�O�̃|�W�V�����̎擾
//====================================================================
D3DXVECTOR3 &CCharacter::GetPositionOld(void)
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
D3DXVECTOR3 &CCharacter::GetRot(void)
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
//�W�����v�̎擾
//====================================================================
bool CCharacter::GetJump(void)
{
	return m_bJump;
}
//====================================================================
//�d�͂̎擾
//====================================================================
bool CCharacter::GetGravity(void)
{
	return m_bGravity;
}
//====================================================================
//�}�g���b�N�X�̎擾
//====================================================================
D3DXMATRIX *CCharacter::GetMtxWorld(void)
{
	return &m_mtxWorld;
}
//====================================================================
//���[�V�������̎擾
//====================================================================
CCharacter::MOTION *CCharacter::GetCharacterMotion(CHARACTER_MOTION_STATE type)
{
	return m_CharacterMotion[type];
}
//====================================================================
//�����蔻��
//====================================================================
void CCharacter::RayCollision(void)
{
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	//nullcheck
	if (!pMap)
	{
		//null�������珈�����Ȃ�
		return;
	}
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
	for (int nCnt = 0; nCnt < pMap->GetMaxModel(); nCnt++)
	{
		D3DXMatrixInverse(&invmat, NULL, pMap->GetModel(nCnt)->GetMatrix());	//	�t�s��̎擾
		//	�t�s����g�p���A���C�n�_����ϊ��@�ʒu�ƌ����ŕϊ�����֐����قȂ�̂ŗv����
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(m_pos.x, m_pos.y + RAY_FIRST_POINT, m_pos.z), &invmat);
		//	���C�I�_����ϊ�
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), &invmat);
		//	���C��������ϊ�
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));
		//Ray���΂�
		D3DXIntersect(pMap->GetMesh(nCnt), &m_posBefore, &direction, &bIsHit, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
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
			m_bJump = true;
			CDebugProc::Print("�W�����v�ł����\n");
		}
		//Ray�̔��茗������Ȃ�������W�����v�ł��Ȃ�
		else
		{
			m_bJump = false;
			CDebugProc::Print("�W�����v�o��������\n");
		}
	}
	//Ray�ɔ��肪�Ȃ�������W�����v�ł��Ȃ�
	else
	{
		m_bJump = false;
		CDebugProc::Print("�W�����v�o��������\n");
	}

}
//====================================================================
//�I�t�Z�b�g�̃t�@�C���擾
//====================================================================
char * CCharacter::GetOffsetFileName(CHARACTER_TYPE type)
{
	return m_LoadOffsetFileName[type];
}
//====================================================================
//���[�V�����̃t�@�C���擾
//====================================================================
char * CCharacter::GetMotionFileName(CHARACTER_MOTION_STATE motionstate)
{
	return m_LoadMotionFileName[motionstate];
}
//====================================================================
//���[�V�����̃��[�h
//====================================================================
void CCharacter::LoadMotion(void)
{
	//�t�@�C���|�C���g
	FILE *pFile;
	int nCntModel = 0;		//���f���̃J�E���g
	int nCntKeySet = 0;		//�t�[���[���̕�����
	int nCntKey = 0;
	char cReadText[128];	//�����Ƃ��ēǂݎ��p
	char cHeadText[128];	//��r����p
	char cDie[128];			//�s�v�ȕ���

	KEY *key;
	KEY_INFO *key_info;

	MOTION *pMotion;
	for (int nCnt = 0; nCnt < CHARACTER_MOTION_MAX; nCnt++)
	{
		pFile = fopen(m_LoadMotionFileName[nCnt], "r");//�t�@�C�����J��
		//��������
		if (pFile != NULL)
		{
			pMotion = new MOTION;
			m_CharacterMotion.emplace_back(pMotion);
			//�X�N���v�g������܂Ń��[�v
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);	//�ꕶ��ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		//��r�p�e�L�X�g�ɕ�������
			}
			//�X�N���v�g��������
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//�t���[���������̏�����
				nCntKeySet = 0;
				//�G���h�X�N���v�g������܂Ń��[�v
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);

					//���[�v���邩�ǂ����̏��ǂݍ���
					if (strcmp(cHeadText, "LOOP") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->nLoop);
					}
					else if (strcmp(cHeadText, "NUM_KEY") == 0)
					{
						sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->nNumKey);
					}
					else if (strcmp(cHeadText, "KEYSET") == 0)
					{
						key_info = new KEY_INFO;
						m_CharacterMotion[nCnt]->key_info.emplace_back(key_info);
						nCntKey = 0;

						while (strcmp(cHeadText, "END_KEYSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);

							if (strcmp(cHeadText, "FRAME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_CharacterMotion[nCnt]->key_info[nCntKeySet]->nFram);
							}
							//�L�[��������
							else if (strcmp(cHeadText, "KEY") == 0)
							{
								//�������m��
								key = new KEY;

								//�z��ɒǉ�
								m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key.emplace_back(key);

								sscanf(cReadText, "%s %s %s %f %f %f", &cDie, &cDie, &cDie,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.x,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.y,
									&m_CharacterMotion[nCnt]->key_info[nCntKeySet]->key[nCntKey]->rot.z);

								//�L�[���Z
								nCntKey++;
							}
						}
						nCntKeySet++;
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
}
//====================================================================
//���[�V����
//====================================================================
void CCharacter::Moation(void)
{
	D3DXVECTOR3 Difrot;
	if (m_MotionType != m_MotionOld)
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	if (m_MotionType != -1)
	{
		for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
		{
			if (m_Fram == 0)
			{
				if (m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram != 0)
				{
					//�ړ���ROT�̌v�Z-------------------------------------����������
					Difrot = (m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->key[nCnt]->rot - m_vModelList[nCnt]->GetRot());

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

					m_rotBET[nCnt] = Difrot / (float)m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
					//----------------------------------------------------����������
				}
				else
				{
					//m_vModelList[nCnt]->GetPosition() = m_CharacterMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].pos;
					//m_vModelList[nCnt]->GetRot()		 = m_CharacterMotion[m_MotionType].key_info[m_CntKeySet].key[nCnt].rot;
					//posBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
					//rotBET[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				}
			}

			//�t���[���ړ�--------------------------------------------����������
			if (m_Fram <= m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram)
			{
				//	m_vModelList[nCnt]->SetPosition(m_vModelList[nCnt]->GetPosition() + posBET[nCnt]);
				m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot() + m_rotBET[nCnt]);
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
		if (m_Fram == m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram)
		{
			m_CntKeySet++;
			m_Fram = 0;
			//�L�[�Z�b�g�����K��l�Ɠ����ɂȂ�����--------------------����������
			if (m_CntKeySet == m_CharacterMotion[m_MotionType]->nNumKey)
			{
				//���[�v���Ȃ��Ƃ�------------------------------------����������
				if (m_CharacterMotion[m_MotionType]->nLoop == 0)
				{
					m_CntKeySet = 0;
					DefaultMotion();
					m_Fram = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
				}
				//���[�v����Ƃ�--------------------------------------����������
				else if (m_CharacterMotion[m_MotionType]->nLoop == 1)
				{
					m_CntKeySet = 0;
				}
			}
		}
		//�t���[�������K��l�Ɠ����ł͂Ȃ��Ƃ�------------------------����������
		else
		{
			m_Fram++;
		}
	}
	else
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
	CDebugProc::Print("���[�V�����^�C�v: %d \n", m_MotionType);
	CDebugProc::Print("�J�E���g�L�[�Z�b�g: %d \n", m_CntKeySet);
	CDebugProc::Print("�t���[��: %d \n", m_Fram);
}
//====================================================================
//�I�t�Z�b�g�̓ǂݍ���
//====================================================================
void CCharacter::LoadOffset(CHARACTER_TYPE nType)
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

	pFile = fopen(m_LoadOffsetFileName[nType], "r");
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
						CModel *pModel = CModel::Create(type, nIdx);
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
//====================================================================
//�����I�ɍX�V
//====================================================================
void CCharacter::ForcedUpdate()
{
	//���f�������J��Ԃ�
	for (size_t nCntKey = 0; nCntKey < m_vModelList.size(); nCntKey++)
	{
		//���[�V�����̉�]�̌����擾
		m_vModelList[nCntKey]->SetRot(m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->key[nCntKey]->rot);
	}
}
//====================================================================
//���[�V�����^�C�v�̎擾
//====================================================================
CCharacter::CHARACTER_MOTION_STATE &CCharacter::GetMotionType(void)
{
	return m_MotionType;
}
//====================================================================
//�O�̃��[�V�����^�C�v�̎擾
//====================================================================
CCharacter::CHARACTER_MOTION_STATE CCharacter::GetMotionOldType(void)
{
	return m_MotionOld;
}
//====================================================================
//�L�[�Z�b�g�̎擾
//====================================================================
int &CCharacter::GetKeySet(void)
{
	return m_CntKeySet;
}
//====================================================================
//�t���[���̎擾
//====================================================================
int &CCharacter::GetFram(void)
{
	return m_Fram;

}
//====================================================================
//�O�̃��[�V�����^�C�v�̐ݒ�
//====================================================================
CCharacter::CHARACTER_TYPE CCharacter::GetCharacterType()
{
	return m_CharaType;
}

//====================================================================
//���f���̃��X�g��Ԃ��@�Q�Ɠn��
//====================================================================
std::vector<CModel*>& CCharacter::GetCharacterModelList()
{
	return m_vModelList;
}
CCharacter::CHARACTER_DIRECTION CCharacter::GetCharacterDirection(void)
{
	return m_CharacterDirection;
}
//====================================================================
//�O�̃��[�V�����^�C�v�̐ݒ�
//====================================================================
void CCharacter::SetMotionOldType(CHARACTER_MOTION_STATE type)
{
	m_MotionOld = type;
}
//====================================================================
//�L�[�Z�b�g�̐ݒ�
//====================================================================
void CCharacter::SetKeySet(int keyset)
{
	m_CntKeySet = keyset;
}
//====================================================================
//�t���[���̐ݒ�
//====================================================================
void CCharacter::SetFram(int fram)
{
	m_Fram = fram;
}
//====================================================================
//�L�����N�^�[�^�C�v�ݒ�
//====================================================================
void CCharacter::SetCharacterType(CHARACTER_TYPE CharaType)
{
	m_CharaType = CharaType;
}
//====================================================================
//�d�͂̐ݒ�
//====================================================================
void CCharacter::SetGravity(bool gravity)
{
	m_bGravity = gravity;
}

void CCharacter::SetCharacterDirection(CHARACTER_DIRECTION direction)
{
	m_CharacterDirection = direction;
}
