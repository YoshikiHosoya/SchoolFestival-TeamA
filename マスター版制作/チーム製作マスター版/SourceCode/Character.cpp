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
#include "collision.h"
#include "hosso\/Debug_ModelViewer.h"
#include "particle.h"

//=============================================================================
// �ÓI�����o�ϐ�������
//=============================================================================
std::vector<CCharacter::MOTION*> CCharacter::m_CharacterMotion = {};

//�I�t�Z�b�g�̓ǂݍ��݃t�@�C��
char *CCharacter::m_LoadOffsetFileName[CHARACTER_TYPE_MAX] =
{
	{ "data/Load/Player/PlayerOffset.txt"},
	{"data/Load/Enemy/EnemyOffset.txt"},
	{"data/Load/Prisoner/PrisonerOffset.txt"},
	{"data/Load/Boss/BossOffset.txt"},
	{ "data/Load/DragonNosuke/Boss_OneOffset.txt" },
};
//���[�V�����̓ǂݍ��݃t�@�C��
char *CCharacter::m_LoadMotionFileName[CHARACTER_MOTION_MAX] =
{
	{ "data/Load/Player/Motion/Neutral.txt" },
	{ "data/Load/Player/Motion/Walk.txt" },
	{ "data/Load/Player/Motion/Attack.txt" },
	{ "data/Load/Player/Motion/Grenade.txt" },
	{ "data/Load/Player/Motion/Jump.txt" },
	{ "data/Load/Player/Motion/JumpStop.txt" },
	{ "data/Load/Player/Motion/Shoot.txt" },
	{ "data/Load/Player/Motion/Squat.txt" },
	{ "data/Load/Player/Motion/SquatStop.txt" },
	{ "data/Load/Player/Motion/Dead.txt" },
	{ "data/Load/Enemy/Motion/EnemyNeutral.txt" },
	{ "data/Load/Enemy/Motion/EnemyWalk.txt" },
	{ "data/Load/Enemy/Motion/EnemySquatStop.txt" },
	{ "data/Load/Enemy/Motion/EnemyDead_1.txt" },
	{ "data/Load/Enemy/Motion/EnemyDead_2.txt" },
	{ "data/Load/Enemy/Motion/EnemyGrenade.txt" },
	{ "data/Load/Enemy/Motion/EnemyJumpAttack.txt" },
	{ "data/Load/Boss/Motion/Neutral.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerStay.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerRelease.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerRun.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerSalute.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerFall.txt" },
	{ "data/Load/Prisoner/Motion/PrisonerSkip.txt" },
};


//=============================================================================
// �}�N��
//=============================================================================
#define ADD_ROTATION_SPEED (0.15f)

//====================================================================
//�R���X�g���N�^
//====================================================================
CCharacter::CCharacter(OBJ_TYPE type) :CScene(type)
{
	// �����蔻��̃|�C���^��null�ɂ���
	m_pCollision = nullptr;
}
//====================================================================
//�f�X�g���N�^
//====================================================================
CCharacter::~CCharacter()
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	//nullcheck
	if (!m_vModelList.empty())
	{
		//�p�[�c����
		for (size_t nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
		{
			//�������J��
			delete m_vModelList[nCnt];
			m_vModelList[nCnt] = nullptr;
		}
		//�z�����ɂ���
		m_vModelList.clear();
	}
}
//====================================================================
//������
//====================================================================
HRESULT CCharacter::Init(void)
{
	m_pos				= ZeroVector3;										// �ʒu
	m_move				= ZeroVector3;										// �ړ���
	m_rot				= ZeroVector3;										// ��]
	m_AddArmRot			= ZeroVector3;										//
	m_AddHeadRot		= ZeroVector3;										//
	m_ShotRotDest		= D3DXVECTOR3(0.0f, 0.0f, 0.5f*  D3DX_PI);			// ������
	m_rotDest.y			= -0.5f*  D3DX_PI;									// ��]���鍷��
	m_Life				= 50;												// �̗�
	m_HeightBet			= 0.0f;												//
	m_state				= CHARACTER_STATE_NORMAL;							// ���
	m_bCanJump				= false;											// �W�����v�t���O
	m_bGravity			= true;												//
	m_bDieFlag			= false;											// ���S�t���O
	m_bMotion			= true;												// ���[�V�������邩�ǂ���
	m_bFall				= false;											//
	m_bDraw				= false;											//�`�悷�邩�ǂ���

	// �����蔻�萶��
	m_pCollision = CCollision::Create();

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
	//�`��͈͓̔����`�F�b�N
	CheckDrawRange();

	if (!m_bDraw)
	{
		return;
	}

	//�OF�̏��ۑ�
	m_posold = m_pos;
	m_MotionOld = m_MotionType;
	m_CharacterDirectionOld = m_CharacterDirection;

	//�ړ��Ɋւ���v�Z
	CalcMove();

	//��]�Ɋւ���v�Z
	CalcRotation();

	//�e�ł��������߂�
	CalcShotDirection();

	//�X�e�[�g�ɉ���������
	State();

	//�������Ȃ��璅�n�����Ƃ�
	if (m_CharacterDirection == DIRECTION::DOWN && GetJump() == true)
	{
		ResetCharacterDirection();
	}

	//�����蔻�菈��
	//���z�֐�
	Collision();

	//���[�V��������
	Motion();
}
//====================================================================
//�`��
//====================================================================
void CCharacter::Draw(void)
{
	//�`�悵�Ȃ���
	if (!m_bDraw)
	{
		//return
		return;
	}
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);


	//���f���̕`��
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		if (m_CharaType != CHARACTER_TYPE_BOSS_ONE)
		{
			if (nCnt == 2)
			{
				//�ڕW�_�ƌ��݂̍����i��]�j
				D3DXVECTOR3 diffHeadRot = m_AddHeadRot - m_vModelList[nCnt]->GetRot();

				//3.14�̒��ߕ��̏������i��]�j
				CHossoLibrary::CalcRotation(m_vModelList[nCnt]->GetRot().x);

				//3.14�̒��ߕ��̏������i��]�j
				CHossoLibrary::CalcRotation(diffHeadRot.x);

				//���߂����������Ǐ]����v�Z
				m_vModelList[nCnt]->GetRot().x += diffHeadRot.x * ADD_ROTATION_SPEED;
			}
			else if (nCnt == 3 || nCnt == 4)
			{
				//�ڕW�_�ƌ��݂̍����i��]�j
				D3DXVECTOR3 diffArmRot = m_AddArmRot - m_vModelList[nCnt]->GetRot();

				//3.14�̒��ߕ��̏������i��]�j
				CHossoLibrary::CalcRotation(m_vModelList[nCnt]->GetRot().x);

				//3.14�̒��ߕ��̏������i��]�j
				CHossoLibrary::CalcRotation(diffArmRot.x);

				//���߂����������Ǐ]����v�Z
				m_vModelList[nCnt]->GetRot().x += diffArmRot.x * ADD_ROTATION_SPEED;
			}
		}

		//�`�揈��
		m_vModelList[nCnt]->Draw(m_mtxWorld);

		/*if (nCnt == 2 || nCnt == 3 || nCnt == 4)
		{
			m_vModelList[nCnt]->SetRot(m_vModelList[nCnt]->GetRot());
		}*/
	}
}
//====================================================================
//�_���[�W���󂯂����̃��A�N�V����
//====================================================================
void CCharacter::DamageReaction()
{
	SetState(CHARACTER_STATE_DAMAGE);
}
//====================================================================
//���S���̃��A�N�V����
//====================================================================
void CCharacter::DeathReaction()
{
	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//====================================================================
//�X�e�[�g�ɉ���������
//====================================================================
void CCharacter::State()
{
	//�J�E���g�_�E��
	m_nStateCnt--;

	//�X�e�[�^�X�̏���
	switch (m_state)
	{
	case CHARACTER_STATE_NORMAL:
		break;
	case CHARACTER_STATE_DAMAGE:
		//�J�E���g��0�ɂȂ�����ʏ�ɖ߂�
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
		}

		//�_�ŏ���
		else if (m_nStateCnt % 4 == 0 && m_nStateCnt % 8 != 0)
		{
			ChangeColor(true, D3DXCOLOR(0.0f, 0.0f, 0.0f, -1.0f));
		}
		else if (m_nStateCnt % 8 == 0)
		{
			ChangeColor(true, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
		}
		break;
	case CHARACTER_STATE_DAMAGE_RED:

		//���Ԍo�߂�
		if (m_nStateCnt <= 0)
		{
			//�X�e�[�g�����ɖ߂�
			SetState(CHARACTER_STATE_NORMAL);
		}
		else
		{
			//�Ԃ��_��
			ChangeColor(true, D3DXCOLOR(1.0f, 0.2f, 0.0f, 0.0f));
		}
		break;
	case CHARACTER_STATE_INVINCIBLE:
		//�J�E���g��0�ɂȂ�����ʏ�ɖ߂�
		if (m_nStateCnt <= 0)
		{
			SetState(CHARACTER_STATE_NORMAL);
		}

		//�����_��
		else if (m_nStateCnt % 4 == 0 && m_nStateCnt % 8 != 0)
		{
			ChangeColor(true, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}
		else if (m_nStateCnt % 8 == 0)
		{
			ChangeColor(true, D3DXCOLOR(0.6f, 0.6f, 0.6f, 0.0f));
		}
		break;

	case CHARACTER_STATE_DEATH:
		//�J�E���g��0�ɂȂ�����
		if (m_nStateCnt <= 0)
		{
			//���S���̃��A�N�V��������
			//�h���N���X���I�[�o�[���C�h
			DeathReaction();
		}

		break;
	}

}

//====================================================================
//�X�e�[�g���ύX�����u��
//�ǂꂭ�炢���̃X�e�[�g��������
//�I�[�o�[���C�h�ŏ㏑������
//====================================================================
void CCharacter::StateChangeReaction()
{
	switch (m_state)
	{
	case CHARACTER_STATE_NORMAL:
		m_nStateCnt = 0;
		break;

	case CHARACTER_STATE_DAMAGE:
		m_nStateCnt = 60;

		break;
	case CHARACTER_STATE_DAMAGE_RED:
		m_nStateCnt = 3;

		break;
	case CHARACTER_STATE_INVINCIBLE:
		m_nStateCnt = 120;

		break;
	case CHARACTER_STATE_DEATH:
		m_nStateCnt = 10;

		//���̃G�t�F�N�g
		CParticle::CreateFromText(GetPosition(), GetShotDirection(), CParticleParam::EFFECT_BLOOD);

		break;
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
	//���C�t�����炷
	GetLife() -= Damage;

	//HP��0�ɂȂ�����
	if (GetLife() <= 0)
	{
		//���S��Ԃɂ���
		SetState(CHARACTER_STATE_DEATH);
	}
	else
	{
		//�_���[�W���󂯂����̃��A�N�V����
		//�I�[�o�[���C�h
		DamageReaction();
	}
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
//�W�����v�t���O�̐ݒ�
//====================================================================
void CCharacter::SetJump(bool bJump)
{
	m_bCanJump = bJump;
}
//====================================================================
//�L������Ԃ̐ݒ�
//====================================================================
void CCharacter::SetState(CHARACTER_STATE state)
{
	if (m_state != state)
	{
		m_state = state;
		m_nStateCnt = 0;
		ChangeColor(false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));

		//�X�e�[�g���ύX�������̃��A�N�V����
		StateChangeReaction();
	}
}
//====================================================================
//�X�e�[�g�̃J�E���g�ݒ�
//====================================================================
void CCharacter::SetStateCount(int nCntState)
{
	m_nStateCnt = nCntState;
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
int &CCharacter::GetLife(void)
{
	return m_Life;
}

//====================================================================
//�W�����v�̎擾
//====================================================================
bool CCharacter::GetJump(void)
{
	return m_bCanJump;
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
//�������̎擾
//====================================================================
D3DXVECTOR3 CCharacter::GetShotDirection(void)
{
	return m_ShotRotDest;
}
//====================================================================
//���[�V�������̎擾
//====================================================================
CCharacter::MOTION *CCharacter::GetCharacterMotion(CHARACTER_MOTION_STATE type)
{
	return m_CharacterMotion[type];
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
//�F�ύX
//====================================================================
void CCharacter::ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor)
{
	//���f���̐F�ύX
	for (unsigned int nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	{
		// ���Z����F�̐ݒ�
		m_vModelList[nCnt]->SetAddColor(AddColor);
		// �F�ύX�t���O�̐ݒ�
		m_vModelList[nCnt]->SetColorChangeFlag(ColorChangeFlag);
	}
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
							//����
							else if (strcmp(cHeadText, "HEIGHT") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_CharacterMotion[nCnt]->key_info[nCntKeySet]->fHeight);
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

			//debug
			std::cout << "Motion Load - " << nCnt << m_LoadMotionFileName[nCnt] << NEWLINE;

			//�t�@�C�������
			fclose(pFile);
		}
		else
		{
			//debug
			std::cout << "LOAD FAILED!!! MotionFile - " << nCnt << m_LoadMotionFileName[nCnt] << NEWLINE;

			//���s
			MessageBox(NULL, "���[�V�����ǂݍ��ݎ��s", m_LoadMotionFileName[nCnt], MB_OK | MB_ICONHAND);
		}
	}
}
//====================================================================
//���[�V����
//====================================================================
void CCharacter::Motion(void)
{
	D3DXVECTOR3 Difrot;
	float Difpos;
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
					Difpos = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->fHeight - m_vModelList[0]->GetPosition().y;
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

					m_HeightBet = Difpos / (float)m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
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
				if (nCnt == 0)
				{
				m_vModelList[0]->GetPosition().y += m_HeightBet;
				}

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
					if (DefaultMotion())
					{
						m_CntKeySet = 0;
						m_Fram = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->nFram;
					}
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
			//���[�V����������Ƃ�
			if (m_bMotion)
			{
				m_Fram++;
			}
		}
	}
	else
	{
		m_Fram = 0;
		m_CntKeySet = 0;
	}
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

	cReadText[0] = '\0';
	cHeadText[0] = '\0';
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
						pModel->SetParentIdx(nIdxParent);
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

	m_vModelList[0]->GetPosition().y = m_CharacterMotion[m_MotionType]->key_info[m_CntKeySet]->fHeight;
}
//====================================================================
//�L�����N�^�[�̌����ݒ肵�Ȃ���
//====================================================================
void CCharacter::ResetCharacterDirection()
{
	if (GetRot().y > 0)
	{
		m_ShotRotDest.z = D3DX_PI * 0.5f;
		SetCharacterDirection(DIRECTION::LEFT);
	}
	else if (GetRot().y < 0)
	{
		m_ShotRotDest.z = -D3DX_PI * 0.5f;
		SetCharacterDirection(DIRECTION::RIGHT);
	}
}
//====================================================================
//�J��
//====================================================================
void CCharacter::CharacterUnLoad(void)
{
	if (!m_CharacterMotion.empty())
	{
		for (size_t nCnt = 0; nCnt < m_CharacterMotion.size(); nCnt++)
		{
			if (!m_CharacterMotion[nCnt]->key_info.empty())
			{
				for (size_t nCntinfo = 0; nCntinfo < m_CharacterMotion[nCnt]->key_info.size(); nCntinfo++)
				{
					if (!m_CharacterMotion[nCnt]->key_info[nCntinfo]->key.empty())
					{
						for (size_t nCntkey = 0; nCntkey < m_CharacterMotion[nCnt]->key_info[nCntinfo]->key.size(); nCntkey++)
						{
							delete m_CharacterMotion[nCnt]->key_info[nCntinfo]->key[nCntkey];
							m_CharacterMotion[nCnt]->key_info[nCntinfo]->key[nCntkey] = nullptr;
						}
					}
					delete m_CharacterMotion[nCnt]->key_info[nCntinfo];
					m_CharacterMotion[nCnt]->key_info[nCntinfo] = nullptr;

				}
			}
			delete m_CharacterMotion[nCnt];
			m_CharacterMotion[nCnt] = nullptr;
		}
	}
	m_CharacterMotion.clear();
}

//====================================================================
//�f�o�b�O
//====================================================================
void CCharacter::DebugInfo(void)
{
	CDebug_ModelViewer::OffsetViewer(m_vModelList);

	//CDebugProc::Print("���̍���%2f\n", m_vModelList[0]->GetPosition().y);

	//CDebugProc::Print("state >>%d\n", GetCharacterState());

	//CDebugProc::Print("");
}
//====================================================================
//�e�̌������ݒ�
//====================================================================
void CCharacter::CalcShotDirection()
{
	//������
	if (m_CharacterDirection == DIRECTION::LEFT)
	{
		m_ShotRotDest.z = 0.5f*D3DX_PI;
		m_AddHeadRot.x = 0.5f;
		m_AddArmRot.x = 0.5f* D3DX_PI;

	}
	else if (m_CharacterDirection == DIRECTION::RIGHT)
	{
		m_ShotRotDest.z = -0.5f*D3DX_PI;
		m_AddHeadRot.x = 0.5f;
		m_AddArmRot.x = 0.5f* D3DX_PI;
	}
	else if (m_CharacterDirection == DIRECTION::UP)
	{
		m_ShotRotDest.z = 0.0f*D3DX_PI;
		m_AddHeadRot.x = 1.0f;
		m_AddArmRot.x = 1.0f* D3DX_PI;
	}
	else if (m_CharacterDirection == DIRECTION::DOWN)
	{
		m_ShotRotDest.z = D3DX_PI;
		m_AddHeadRot.x = -0.5f;
		m_AddArmRot.x = -0.3f* D3DX_PI;
	}
}
//====================================================================
//�ړ��̌v�Z
//====================================================================
void CCharacter::CalcMove()
{
	//�����̒�R
	m_move.x += (0 - m_move.x)* 0.4f;
	m_move.z += (0 - m_move.z)* 0.4f;
	m_move.y += m_move.y * -0.1f;

	//�d�͂������Ƃ�
	if (m_bGravity == true)
	{
		//�d�͉��Z
		m_move.y -= 0.5f;
	}

	//�ړ�����
	m_pos += m_move;


	//�ߗ��֘A
	if (m_bFall == false)
	{
		m_posfall = m_pos;
	}
	if (m_pos.y <= -100 && m_bFall == true)
	{
		if (m_pos.x < m_posfall.x)
		{
			m_pos.x = m_posfall.x + 50;
		}
		else
		{
			m_pos.x = m_posfall.x - 50;
		}
		m_pos.y = m_posfall.y + 30;
		m_bFall = false;
	}
}

//====================================================================
//��]�̌v�Z
//====================================================================
void CCharacter::CalcRotation()
{

	//�ڕW�_�ƌ��݂̍����i��]�j
	float diffRot = m_rotDest.y - m_rot.y;

	//3.14�̒��ߕ��̏������i��]�j
	CHossoLibrary::CalcRotation(m_rot.y);
	CHossoLibrary::CalcRotation(diffRot);

	//���߂����������Ǐ]����v�Z
	m_rot.y += diffRot * ADD_ROTATION_SPEED;
}
//====================================================================
//�����蔻��̏���
//====================================================================
void CCharacter::Collision()
{
	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// �}�b�v���f�������݂��������ē����蔻�肪���݂��鎞
	if (pMap && m_pCollision)
	{
		m_pCollision->SetHeight(m_vModelList[0]->GetPosition().y);
		// ���C�̔���
		if (m_pCollision->RayBlockCollision(pMap, m_vModelList[0]->GetMatrix()))
		{
			// �W�����v���邱�Ƃ����F����
			SetJump(true);
			m_bFall = false;
		}
		else
		{
			// �W�����v���邱�Ƃ����F���Ȃ�
			SetJump(false);
			m_bFall = true;
		}
	}
}
//====================================================================
//�`��͈͓̔����ǂ����m�F
//====================================================================
void CCharacter::CheckDrawRange()
{
	m_bDraw = CManager::GetRenderer()->CheckScreenRange(m_pos);
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
//���[�V�������Ă邩�ǂ����擾
//====================================================================
bool & CCharacter::GetMotion()
{
	return m_bMotion;
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
//���f���̃��X�g��Ԃ�	�Q�Ɠn��
//====================================================================
std::vector<CModel*>& CCharacter::GetCharacterModelList()
{
	return m_vModelList;
}
//====================================================================
//���f���p�[�c�̃��X�g��Ԃ�	�Q�Ɠn��
//====================================================================
CModel* CCharacter::GetCharacterModelPartsList(int nCnt)
{
	return m_vModelList[nCnt];
}

//====================================================================
//�����擾
//====================================================================
DIRECTION &CCharacter::GetCharacterDirection(void)
{
	return m_CharacterDirection;
}
//====================================================================
//1F�O�̌����擾
//====================================================================
DIRECTION & CCharacter::GetCharacterDirectionOld(void)
{
	return m_CharacterDirectionOld;
}
//====================================================================
//���̍����̎擾
//====================================================================
float CCharacter::GetHeightBet(void)
{
	return m_HeightBet;
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
//====================================================================
//�L�����N�^�[�̌���
//====================================================================
void CCharacter::SetCharacterDirection(DIRECTION direction)
{
	m_CharacterDirection = direction;
}
//====================================================================
//�������̐ݒ�
//====================================================================
void CCharacter::SetShotDirection(D3DXVECTOR3 direction)
{
	m_ShotRotDest = direction;
}
