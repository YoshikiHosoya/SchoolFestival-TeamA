// =====================================================================================================================================================================
//
// �v���C���[�̏��� [player.cpp]
// Author : NORI
//
// =====================================================================================================================================================================
#include "Player.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "Xinput.h"
#include "handgun.h"
#include "heavymachinegun.h"
#include "gun.h"
#include "grenadefire.h"
#include "collision.h"
#include "BaseMode.h"
#include "manager.h"
#include "enemy.h"
#include "map.h"
#include "XInputPad.h"
#include "item.h"
#include "Obstacle.h"
#include "grenade.h"
#include "prisoner.h"
#include "Knife.h"
#include "playerUI.h"
#include "playertank.h"
#include "battleplane.h"
#include "resultmanager.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
PLAYER_DATA		CPlayer::m_PlayerData	 = {};
int				CPlayer::m_nLife[2] = {};
int				CPlayer::m_nRespawnCnt	 = 0;
float			CPlayer::m_fRunSpeed	 = 0.0f;
float			CPlayer::m_fCrouchSpeed	 = 0.0f;
float			CPlayer::m_fJump		 = 0.0f;
float			CPlayer::m_fRideJump	 = 0.0f;
D3DXVECTOR3		CPlayer::m_pos[2] = {};
// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CPlayer::m_PlayerFileName =
{
	"data/Load/Player/PlayerData.txt" 			// �v���C���[�̏��
};

//====================================================================
//�}�N����`
//====================================================================
#define PLAYER_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f)) //�v���C���[�̃T�C�Y
#define PLAYER_SIZE_CRUCH	(D3DXVECTOR3(50.0f,34.0f,0.0f)) //���Ⴊ�񂾎��̃T�C�Y
// �ђʂ����邩�̃t���O
#define ATTACK_PENETRATION		(true)			// �v���C���[�̔��肪�ђʂ��邩�ǂ���
#define ATTACK_DAMAGE_ENEMY		(50)			// �G�l�~�[�ւ̃_���[�W
#define SHOT_BULLET_POS_Y		(-15.0f)		// �e�̔��ˈʒuY
#define SHOT_BULLET_POS_Z		(-5.0f)			// �e�̔��ˈʒuZ

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CPlayer::~CPlayer()
{
}
//====================================================================
//������
//====================================================================
HRESULT CPlayer::Init(void)
{
	// �ǂݍ��񂾏��̑��
	SetPlayerData();

	//�L�����̏�����
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_PLAYER);
	SetCharacterType(CCharacter::CHARACTER_TYPE_PLAYER);
	m_bAttack = false;
	m_bKnifeAttack = false;
	 // �e�̐���
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_RHAND)->GetMatrix());
	// �O���l�[�h���ʒu�̐���
	m_pGrenadeFire = CGrenadeFire::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
	// �e�̒e�̎��
	m_pGun->GetTag() = TAG_PLAYER;
	// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(0.0f, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));

	// �i�C�t�̐���
	m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
	// ��蕨�ɏ�荞��ł��邩�ǂ����̃t���O
	m_bRideVehicle = false;

	// �Q�[�����[�h��������
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �Q�[���N���X�̃|�C���^�擾
		CGame *pGame = (CGame*)CManager::GetBaseMode();
		if (pGame != nullptr)
		{
			// �v���C���[UI�̐���
			m_pPlayerUI = CPlayerUI::Create();
			// �e�̎c���\��
			m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
			// �O���l�[�h�̎c���\��
			m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
		}
	}

	// �`���[�g���A�����[�h��������
	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));
		SetLife(5);
	}
	// �Q�[�����[�h��������
	else if(CManager::GetMode() == CManager::MODE_GAME)
	{
		SetPosition(m_pos[0]);
		SetLife(m_nLife[0]);
	}

	//�����̌���
	SetCharacterDirection(DIRECTION::RIGHT);
	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(PLAYER_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CPlayer::Uninit(void)
{
	// �e�̃|�C���^
	if (m_pGun)
	{
		delete m_pGun;
		m_pGun = nullptr;
	}

	// �i�C�t�̃|�C���^
	if (m_pKnife)
	{
		m_pKnife->Rerease();
		m_pKnife = nullptr;
	}

	// �O���l�[�h���ˈʒu�̃|�C���^
	if (m_pGrenadeFire)
	{
		m_pGrenadeFire->Rerease();
		m_pGrenadeFire = nullptr;
	}

	// �v���C��UI�̃|�C���^
	if (m_pPlayerUI)
	{
		m_pPlayerUI->Uninit();
		m_pPlayerUI = nullptr;
	}

	CCharacter::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CPlayer::Update(void)
{
	float rot = 0.0f;
	static bool trigger = false;
	static bool trigger2 = false;
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

	m_pGun->Update();

	// ����̃{�^�������������ɕ������[�V�����ɕύX
	if (CHossoLibrary::PressAnyButton())
	{
		//SetMotion(CCharacter::PLAYER_MOTION_WALK);
	}
	// ��蕨�ɏ���Ă��Ȃ����Ƃ��Ȃ����̔���
	Ride();

	CollisionUpdate();
	if (m_bRespawn == true)
	{
		ReSpawn();
	}
	// �̗�UI�̐ݒ�
	if (m_pPlayerUI)
	{
		m_pPlayerUI->SetLifeUI(GetLife());
	}

	CCharacter::Update();

	CDebugProc::Print("���@�̃��C�t %d\n",GetLife());
	if (m_bAttack == true)
	{
		CDebugProc::Print("�U���\\n");
	}
	else
	{
		CDebugProc::Print("�U���s�\\n");
	}
	if (m_bKnifeAttack == true)
	{
		CDebugProc::Print("�U�����イ����\n");
	}
	else
	{
		CDebugProc::Print("�U�����ĂȂ���\n");
	}
	PadMoveUpdate();//�p�b�h�̍X�V
	//�X�N���[���͈͓̔�����o�Ȃ��悤�ɐ���
	CManager::GetRenderer()->ScreenLimitRange(GetPosition());
}
//====================================================================
//�`��
//====================================================================
void CPlayer::Draw(void)
{
	// ��蕨�ɏ���Ă�����`�悵�Ȃ� �܂��̓��C�t��0��flag����������
	if (m_bRideVehicle == false )
	{
		CCharacter::Draw();
	}

	m_pGun->Draw();

}
//====================================================================
//�f�o�b�O
//====================================================================
void CPlayer::DebugInfo(void)
{
	static bool trigger = false;
	static bool trigger2 = false;
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

	//�f�o�b�O���[�h�̐؂�ւ�
	if (key->GetKeyboardTrigger(DIK_F2))
	{
		trigger ^= 1;
	}
	if (trigger == true)
	{
		m_DebugState = DEBUG_CREATE_MAP;
		SetGravity(false);
	}
	else
	{
		m_DebugState = DEBUG_NORMAL;
		SetGravity(true);
	}

}
//====================================================================
//�ړ��֘A
//====================================================================
void CPlayer::MoveUpdate(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	CXInputPad *pad;
	pad = CManager::GetPad();
	float x, y;
	pad->GetStickLeft(&x, &y);//�p�b�h�̓��͒l����
	x /= STICK_MAX_RANGE;//�l�̐��K��
	y /= STICK_MAX_RANGE;//�l�̐��K��

	if (m_bRespawn == false)
	{
		if (key->GetKeyboardPress(DIK_W))
		{
			SetCharacterDirection(DIRECTION::UP);
		}

		// A�̏���
		if (key->GetKeyboardPress(DIK_A))
		{
			CPlayer::Move(m_fRunSpeed, 0.5f);
			if (key->GetKeyboardPress(DIK_W))
			{
				SetCharacterDirection(DIRECTION::UP);
			}
			else
			{
				SetCharacterDirection(DIRECTION::LEFT);
			}
		}
		// D�̏���
		else if (key->GetKeyboardPress(DIK_D))
		{
			CPlayer::Move(-m_fRunSpeed, -0.5f);
			if (key->GetKeyboardPress(DIK_W))
			{
				SetCharacterDirection(DIRECTION::UP);
			}
			else
			{
				SetCharacterDirection(DIRECTION::RIGHT);
			}
		}

		//�W�����v
		if ((key->GetKeyboardTrigger(DIK_SPACE)|| pad->GetTrigger(pad->JOYPADKEY_A, 1)) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
		{
			GetMove().y += m_fJump;
			SetMotion(PLAYER_MOTION_JUMP);
		}
		else if (GetJump() == false && GetMove().y < 0 && GetMotionType() != PLAYER_MOTION_JUMPSTOP)
		{
			SetMotion(PLAYER_MOTION_JUMP);
		}
		else if (key->GetKeyboardPress(DIK_SPACE) && m_DebugState != DEBUG_NORMAL)
		{
			GetMove().y += 2;
		}
		//�W�����v���[�V��������Ȃ���
		if (GetMotionType() != PLAYER_MOTION_JUMP)
		{
			//�W�����v�X�g�b�v���[�V��������Ȃ���
			if (GetMotionType() != PLAYER_MOTION_JUMPSTOP)
			{
				if (GetMotionType() != PLAYER_MOTION_ATTACK01)
				{
					//�ړ�������E�H�[�N���[�V����
					if (GetMove().x > 0.2f || GetMove().x < -0.2f)
					{
						SetMotion(PLAYER_MOTION_WALK);
						m_bCruch = false;
					}
					//���Ⴊ��łȂ���
					else if (m_bCruch == false)
					{
						SetMotion(PLAYER_MOTION_NORMAL);
						GetCollision()->SetSize2D(PLAYER_SIZE_CRUCH);
					}
					//S���������炵�Ⴊ�݃��[�V����
					if (key->GetKeyboardPress(DIK_S)|| y < -0.6f && GetJump() == true)
					{
						if (m_bCruch == false && GetMotionType() != PLAYER_MOTION_WALK)
						{
							SetMotion(PLAYER_MOTION_SQUATSTOP);
							GetCollision()->SetSize2D(PLAYER_SIZE_CRUCH);
							m_bCruch = true;
						}
					}
					else if (GetJump() == true && GetMotionType() != PLAYER_MOTION_WALK && y > -0.6f)
					{
						m_bCruch = false;
						SetMotion(PLAYER_MOTION_NORMAL);
						GetCollision()->SetSize2D(PLAYER_SIZE);
					}
				}
			}
			//�W�����v�A���Ⴊ�݂����ĂȂ�������j���[�g����
			else if (GetJump() == true && m_bCruch == false && GetMotionType() != PLAYER_MOTION_ATTACK01)
			{
				SetMotion(PLAYER_MOTION_NORMAL);
			}
		}
		//�W�����v�����Ƃ�
		else if (GetMotionType() == PLAYER_MOTION_JUMP)
		{
			m_bCruch = false;
			//�L�[�Z�b�g���R�ɂȂ�����X�g�b�v���[�V������
			if (GetKeySet() == 3)
			{
				SetMotion(PLAYER_MOTION_JUMPSTOP);
			}
		}

		//�W�����v�����Ƃ��̉�������
		if (key->GetKeyboardPress(DIK_S) && GetJump() == false)
		{
			SetCharacterDirection(DIRECTION::DOWN);
		}

	}
}
//====================================================================
//�����蔻��֘A
//====================================================================
void CPlayer::CollisionUpdate(void)
{
	// �����蔻��
	if (GetCollision() != nullptr)
	{
		// ���W�̍X�V pos��posold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());

		// ��蕨�ɏ���Ă��鎞�ɏ�蕨�ȊO�̔�������Ȃ�
		if (m_bRideVehicle == false)
		{
			CPrisoner *pPrisoner = GetCollision()->ForPlayer_PrisonerCollision();
			// �G�l�~�[�ƂƂ̔���
			if (GetCollision()->ForPlayer_EnemyCollision(ATTACK_PENETRATION) == true||
				GetCollision()->ForPlayer_PrisonerCollision(ATTACK_PENETRATION) == true)
			{
				if (pPrisoner != nullptr)
				{
					m_bAttack = true;
				}
			}
			else
			{
				m_bAttack = false;
			}

			// ��Q���Ƃ̔���
			//if (GetCollision()->ForPlayer_ObstacleCollision())
			//{
			//	// �W�����v�t���O���\�ɂ���
			//	CCharacter::SetJump(true);
			//}

			// �A�C�e���Ƃ̔���
			if (GetCollision()->ForPlayer_ItemCollision())
			{
			}
		}

		if (m_bRideVehicle == false)
		{
			// ��蕨�Ƃ̔���
			if (GetCollision()->ForPlayer_VehicleCollision())
			{
				// ��荞�񂾎�
				m_bRideVehicle = true;
			}
			else
			{
				// ����Ă��Ȃ��Ƃ�
				m_bRideVehicle = false;
			}
		}
	}

	// �e�̕`��t���O�̐ݒ�
	m_pGun->SetDrawFlag(m_bRideVehicle);
}
//====================================================================
//�U���֘A
//====================================================================
void CPlayer::AttackUpdate(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	CXInputPad *pad;
	pad = CManager::GetPad();
	if (m_bRespawn == false)
	{
		// �e������ or �ߐڍU��
		if (key->GetKeyboardTrigger(DIK_P)|| pad->GetTrigger(pad->JOYPADKEY_X,1))
		{
			// �e�����Ă��Ԃ�������
			if (m_bAttack == false && m_bKnifeAttack == false)
			{
				// �e���ˏ���
				m_pGun->Shot();
			}

			// �ߐڍU���������Ԃ�������
			if (m_bAttack == true && m_bKnifeAttack == false)
			{
				// �ߐڍU��
				m_bKnifeAttack = true;
				m_pKnife->StartMeleeAttack();
				SetMotion(CCharacter::PLAYER_MOTION_ATTACK01);
			}
		}
		// �O���l�[�h�𓊂���
		if (key->GetKeyboardTrigger(DIK_O)|| pad->GetTrigger(pad->JOYPADKEY_Y, 1))
		{
			// �O���l�[�h�̒e�����c���Ă���Ƃ�
			if (m_pGrenadeFire->GetGrenadeAmmo() > 0)
			{
				// �O���l�[�h����
				m_pGrenadeFire->Fire(GetShotDirection());

				SetMotion(CCharacter::PLAYER_MOTION_GRENADE);
			}
		}

		// �U�����[�V��������ʂ̃��[�V�����ɂȂ�����
		if (GetMotionType() != CCharacter::PLAYER_MOTION_ATTACK01)
		{
			m_bKnifeAttack = false;
			m_pKnife->EndMeleeAttack();
		}
	}
}
//====================================================================
//�p�b�h�̈ړ��֘A�X�V
//====================================================================
void CPlayer::PadMoveUpdate(void)
{
	D3DXVECTOR3 MoveValue = ZeroVector3;
	if (m_bRespawn == false)
	{

		if (CHossoLibrary::PadMoveInput(MoveValue, GetCharacterDirection(), GetJump()))
		{
			Move(MoveValue.x, MoveValue.y);
		}

		CXInputPad *pad = CManager::GetPad();
		D3DXVECTOR3 InputValue = ZeroVector3;
		pad->GetStickLeft(&InputValue.x, &InputValue.y);//�p�b�h�̓��͒l����

		InputValue.x /= STICK_MAX_RANGE;//�l�̐��K��
		InputValue.y /= STICK_MAX_RANGE;//�l�̐��K��

		//�W�����v���[�V��������Ȃ���
		if (GetMotionType() != PLAYER_MOTION_JUMP)
		{
			//�W�����v�X�g�b�v���[�V��������Ȃ���
			if (GetMotionType() != PLAYER_MOTION_JUMPSTOP)
			{
				if (GetMotionType() != PLAYER_MOTION_ATTACK01)
				{
					//S���������炵�Ⴊ�݃��[�V����
					if (InputValue.y < -0.6f && GetJump() == true)
					{
						if (m_bCruch == false && GetMotionType() != PLAYER_MOTION_WALK)
						{
							SetMotion(PLAYER_MOTION_SQUATSTOP);
							m_bCruch = true;
						}
					}
				}
			}
		}
	}
}
//====================================================================
//�f�t�H���g���[�V�����ɖ߂�
//====================================================================
bool CPlayer::DefaultMotion(void)
{
	if (GetJump() == true)
	{
		SetMotion(CCharacter::PLAYER_MOTION_NORMAL);
	}
	return true;
}
//====================================================================
//�v���C���[���X�|�[������
//====================================================================
void CPlayer::MapChangePlayerRespawn()
{
	SetState(CCharacter::CHARACTER_STATE_INVINCIBLE);
	SetPosition(ZeroVector3);
	m_bRideVehicle = false;
	m_pKnife->EndMeleeAttack();
}

//====================================================================
//�_���[�W���̃��A�N�V����
//====================================================================
void CPlayer::DamageReaction()
{
	CCharacter::DamageReaction();
}

//====================================================================
//���S���̃��A�N�V����
//====================================================================
void CPlayer::DeathReaction()
{
	CCharacter::DeathReaction();
}
//====================================================================
//�X�e�[�g���؂�ւ�������̃��A�N�V����
//====================================================================
void CPlayer::StateChangeReaction()
{
	CCharacter::StateChangeReaction();

	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_NORMAL:

		break;

	case CHARACTER_STATE_DAMAGE:


		break;
	case CHARACTER_STATE_DAMAGE_RED:


		break;
	case CHARACTER_STATE_INVINCIBLE:


		break;
	case CHARACTER_STATE_DEATH:
		SetRespawnFlag(true);

		break;
	}
}
//====================================================================
//�f�o�b�O�X�e�[�^�X�̎擾
//====================================================================
CPlayer::DEBUG_STATE CPlayer::GetDebugState(void)
{
	return m_DebugState;
}
//====================================================================
//�ړ�
//====================================================================
void CPlayer::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.3f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.3f;
	GetRotDest().y = fdest *  D3DX_PI;
}

//====================================================================
// ��蕨�ɏ���Ă��鎞
//====================================================================
void CPlayer::Ride()
{
	// ��蕨�ɏ���Ă��Ȃ����ɍX�V����
	if (m_bRideVehicle == false)
	{
		MoveUpdate();
		AttackUpdate();
		if (m_pGun->GetGunType() != m_pGun->GUNTYPE_HEAVYMACHINEGUN)
		{
		// �e����������ݒ�
			m_pGun->SetShotRot(GetShotDirection());
		}
		else
		{
		// �e����������ݒ�
		m_pGun->SetShotRot(GetAddShotRot());
		CDebugProc::Print("�ˌ������l:%2f\n", GetAddShotRot().z);
		}
		if (m_pPlayerUI)
		{
			// �e�̎c���\��
			m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
			// �O���l�[�h�̎c���\��
			m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
		}
	}
	else
	{
		CPlayertank *pPlayertank = nullptr;
		pPlayertank = this->GetCollision()->ForPlayer_TankCollision();

		CBattlePlane *pBattlePlane = nullptr;
		pBattlePlane = this->GetCollision()->ForPlayer_PlaneCollision();

		// ��Ԃɏ���Ă��鎞
		if (pPlayertank != nullptr)
		{
			//�X�N���[���͈͓̔�����o�Ȃ��悤�ɐ���
			CManager::GetRenderer()->ScreenLimitRange(pPlayertank->GetPosition());

			// �v���C���[�̍��W���Ԃ̍��W�ɍ��킹��
			this->SetPosition(pPlayertank->GetPosition());

			if (m_pPlayerUI)
			{
				// �e�̎c���\��
				m_pPlayerUI->SetBulletAmmo(pPlayertank->GetGun()->GetGunAmmo(), pPlayertank->GetGun()->GetGunType());
				// �O���l�[�h�̎c���\��
				m_pPlayerUI->SetGrenadeAmmo(pPlayertank->GetGrenadeFire()->GetGrenadeAmmo());
			}
		}

		// �퓬�@�ɏ���Ă��鎞
		else if (pBattlePlane != nullptr)
		{
			//�X�N���[���͈͓̔�����o�Ȃ��悤�ɐ���
			CManager::GetRenderer()->ScreenLimitRange(pBattlePlane->GetPosition());

			// �v���C���[�̍��W��퓬�@�̍��W�ɍ��킹��
			this->SetPosition(pBattlePlane->GetPosition());

			if (m_pPlayerUI)
			{
				// �e�̎c���\��
				m_pPlayerUI->SetBulletAmmo(pBattlePlane->GetGun()->GetGunAmmo(), pBattlePlane->GetGun()->GetGunType());
			}
		}

		// ��蕨�ɏ���Ă��鎞�ɃW�����v���Đ�Ԃ���~���
		CKeyboard *key = CManager::GetInputKeyboard();
		CXInputPad *pad = CManager::GetPad();
		//�v���C���[����蕨����~���Ƃ�
		if (key->GetKeyboardTrigger(DIK_SPACE)|| pad->GetTrigger(pad->JOYPADKEY_B,1) && GetJump() == false)
		{
			m_bRideVehicle = false;
			GetMove().y += m_fRideJump;
			SetMotion(PLAYER_MOTION_JUMP);
		}
	}
}
//====================================================================
//���X�|�[��
//====================================================================
void CPlayer::ReSpawn(void)
{
	m_nRespawnCnt++;
	SetState(CHARACTER_STATE_INVINCIBLE);

	if (m_nRespawnCnt == m_nRespawnCnt)
	{
		m_nRespawnCnt = 0;
		m_bRespawn = false;
		m_pGun->SetGunType(CGun::GUNTYPE_HANDGUN);
		SetState(CHARACTER_STATE_NORMAL);
		SetLife(m_nLife[0]);
	}
}

//====================================================================
//���f���̃N���G�C�g
//====================================================================
CPlayer *CPlayer::Create(void)
{
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->Init();
	return pPlayer;
}

//====================================================================
//�v���C���[�̃f�[�^�̓ǂݍ���
//====================================================================
void CPlayer::PlayerLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

									// �t�@�C�����J��
	pFile = fopen(m_PlayerFileName, "r");

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

															// ITEMSET��������
				if (strcmp(cHeadText, "PLAYERSET") == 0)
				{
					// END_ITEMSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_PLAYERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

																	// SPEED��������
						if (strcmp(cHeadText, "LIFE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerData.nLife);			// ��r�p�e�L�X�g��LIFE����
						}
						else if (strcmp(cHeadText, "RESPAEN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerData.nRespawnCnt);		// ��r�p�e�L�X�g��RESPAEN����
						}
						else if (strcmp(cHeadText, "RUNSPEED") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PlayerData.fRunSpeed);		// ��r�p�e�L�X�g��RUNSPEED����
						}
						else if (strcmp(cHeadText, "CROUCHSPEED") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PlayerData.fCrouchSpeed);	// ��r�p�e�L�X�g��CROUCHSPEED����
						}
						else if (strcmp(cHeadText, "RIDEJUMP") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PlayerData.fRideJump);		// ��r�p�e�L�X�g��RIDEJUMP����
						}
						else if (strcmp(cHeadText, "JUMP") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PlayerData.fJump);			// ��r�p�e�L�X�g��JUMP����
						}
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_PlayerData.pos.x,
								&m_PlayerData.pos.y,
								&m_PlayerData.pos.z);													// ��r�p�e�L�X�g��POS����
						}

						else if (strcmp(cHeadText, "END_PLAYERSET") == 0)
						{
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
		MessageBox(NULL, "�v���C���[�̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}

//====================================================================
//�v���C���[�̃f�[�^�̐ݒ�
//====================================================================
void CPlayer::SetPlayerData()
{
	// �̗͂̏����擾
	m_nLife[0] = m_PlayerData.nLife;
	// �������W�̏����擾
	m_pos[0] = m_PlayerData.pos;
	// �������Ԃ̏����擾
	m_nRespawnCnt = m_PlayerData.nRespawnCnt;
	// �ړ����x�̏����擾
	m_fRunSpeed = m_PlayerData.fRunSpeed;
	// ���Ⴊ�ݎ��̈ړ����x�̏����擾
	m_fCrouchSpeed = m_PlayerData.fCrouchSpeed;
	// �ʏ펞�̃W�����v��
	m_fJump = m_PlayerData.fJump;
	// ��蕨����~��鎞�̃W�����v��
	m_fRideJump = m_PlayerData.fRideJump;
}
