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
#include "GameManager.h"
#include "sound.h"
#include "ModelSet.h"
// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
PLAYER_DATA		CPlayer::m_PlayerData	 = {};
int				CPlayer::m_nLife[2] = {};
float			CPlayer::m_fRunSpeed	 = 0.0f;
float			CPlayer::m_fCrouchSpeed	 = 0.0f;
float			CPlayer::m_fJump		 = 0.0f;
float			CPlayer::m_fRideJump	 = 0.0f;
D3DXVECTOR3		CPlayer::m_pos[2] = {};
bool			CPlayer::m_bTwoPPlay = false;

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
#define PLAYER_SIZE			(D3DXVECTOR3(40.0f,70.0f,0.0f)) //�v���C���[�̃T�C�Y
#define PLAYER_SIZE_CRUCH	(D3DXVECTOR3(40.0f,30.0f,0.0f)) //���Ⴊ�񂾎��̃T�C�Y
// �ђʂ����邩�̃t���O
#define ATTACK_PENETRATION		(true)			// �v���C���[�̔��肪�ђʂ��邩�ǂ���
#define SHOT_BULLET_POS_Y		(-15.0f)		// �e�̔��ˈʒuY
#define SHOT_BULLET_POS_Z		(-5.0f)			// �e�̔��ˈʒuZ
#define KNIFE_COLLISOIN_SIZE	(D3DXVECTOR3(80.0f,80.0f,0.0f))
#define RESPAWN_INTERVAL		(120)
#define DEFAULT_STOCK			(3)				// �����c�@

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
	m_pGrenadeFire	= nullptr;
	m_pGun			= nullptr;
	m_pKnife		= nullptr;
	m_pPlayerUI		= nullptr;
	m_pVehicle		= nullptr;
	m_pPad			= nullptr;
	m_nRespawnCnt = 0;
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
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_PLAYER);
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_PLAYER);

	 // �e�̐���
	m_pGun = CGun::Create();
	// ��̃|�C���^�ݒ�
	m_pGun->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());

	// �O���l�[�h���ʒu�̐���
	m_pGrenadeFire = CGrenadeFire::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), CGrenadeFire::HAND_GRENADE);
	// �e�̒e�̎��
	m_pGun->SetTag(GetTag());
	// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(0.0f, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));

	// �i�C�t�̐���
	m_pKnife = CKnife::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), KNIFE_COLLISOIN_SIZE, TAG::PLAYER_1);
	// ��蕨�ɏ�荞��ł��邩�ǂ����̃t���O
	m_bRideVehicle = false;
	//�r����]���邩
	SetRotArm(true);
	// �Q�[�����[�h��������
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �Q�[���N���X�̃|�C���^�擾
		CGame *pGame = (CGame*)CManager::GetBaseMode();
		if (pGame != nullptr)
		{
			// �v���C���[UI�̐���
			m_pPlayerUI = CPlayerUI::Create(GetTag());
			// �e�̎c���\��
			m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
			// �O���l�[�h�̎c���\��
			m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
			// �c�@�̐ݒ�
			m_pPlayerUI->SetStockUI(DEFAULT_STOCK);

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
		//�v���C���[�ݒ�
		ResetPlayer();
	}

	//�����̌���
	SetCharacterDirection(DIRECTION::RIGHT);
	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(PLAYER_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	// �Q�[���I�u�W�F�N�g( �^�O )�̐ݒ�
	GetCollision()->SetGameObject(this);

	// �����I�p�b�h�̃|�C���^�擾
	m_pPad = CManager::CManager::GetPad(GetTag());

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

	//�Q�[�����̎�
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (m_bRespawn == true)
		{
			//���X�|�[���̏���
			ReSpawn();
		}
		//�Q�[���I�[�o�[��
		else if (CManager::GetGame()->GetGameManager()->GetGameState() == CGameManager::GAMESTATE::GAMEOVER ||
				CManager::GetGame()->GetGameManager()->GetGameState() == CGameManager::GAMESTATE::NONE)
		{
			//�����Ǝ��S
			SetLife(0);
			GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_DEAD);

		}
		//���U���g��ʈȊO�̂Ƃ�
		else if (CManager::GetGame()->GetGameManager()->GetGameState() != CGameManager::GAMESTATE::RESULT)
		{
			// ��蕨�ɏ���Ă��Ȃ����Ƃ��Ȃ����̔���
			Ride();
		}
		else
		{
			DefaultMotion();
		}
	}
	else
	{
		// ��蕨�ɏ���Ă��Ȃ����Ƃ��Ȃ����̔���
		Ride();
	}

	//�����蔻�菈��
	CollisionUpdate();
	// �̗�UI�̐ݒ�
	if (m_pPlayerUI)
	{
		m_pPlayerUI->SetLifeUI(GetLife());
	}
	if (m_pGun->GetGunType() == m_pGun->GUNTYPE_HEAVYMACHINEGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_HEAVYMACHINEGUN);
	}

	CCharacter::Update();

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
	DrawWepon();
	m_pGun->Draw();

}
//====================================================================
//����̌����ڕύX
//====================================================================
void CPlayer::DrawWepon(void)
{
	//�n���h�K��
	if (m_pGun->GetGunType() == m_pGun->GUNTYPE_HANDGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_HANDGUN);
	}
	//�w�r�[�}�V���K��
	else if (m_pGun->GetGunType() == m_pGun->GUNTYPE_HEAVYMACHINEGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_HEAVYMACHINEGUN);
	}
	//�V���b�g�K��
	else if (m_pGun->GetGunType() == m_pGun->GUNTYPE_SHOTGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_SHOTGUN);
	}
	//�t���C��
	else if (m_pGun->GetGunType() == m_pGun->GUNTYPE_FLAMESHOT)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_FLAMESHOT);
	}
	//���[�U�[
	else if (m_pGun->GetGunType() == m_pGun->GUNTYPE_LASERGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_LASERGUN);
	}
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

	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "PlayerInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{
		ImGui::Text("m_ShotRot [%.2f %.2f %.2f]", m_ShotRot.x, m_ShotRot.y, m_ShotRot.z);

		ImGui::Text("m_bAttack [%d]", m_bAttack); ImGui::SameLine();
		ImGui::Text("m_bKnifeAttack [%d]", m_bKnifeAttack);
		ImGui::Text("m_bRespawn [%d]", m_bRespawn); ImGui::SameLine();
		ImGui::Text("m_bCruch [%d]", m_bCruch);
		ImGui::Text("m_bRideVehicle [%d]", m_bRideVehicle);


		ImGui::Text("---DebugCommand---");
		ImGui::Text("[G] >> PlayerDamage");
		ImGui::Text("[F2] >> DebugTrigger(Player Fly)"); ImGui::SameLine();
		ImGui::Text("DebugTrigger [%d]", trigger);

		CCharacter::DebugInfo();

		m_pGun->DebugInfo();

		m_pGrenadeFire->DebugInfo();

		m_pKnife->DebugInfo();

		ImGui::TreePop();
	}

	if (key->GetKeyboardTrigger(DIK_G))
	{
		AddDamage(1);
	}

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
	float Pad_X, Pad_Y;

	if (m_pPad)
	{
		//�p�b�h�̓��͒l����
		m_pPad->GetStickLeft(&Pad_X, &Pad_Y);

		Pad_X /= STICK_MAX_RANGE;//�l�̐��K��
		Pad_Y /= STICK_MAX_RANGE;//�l�̐��K��
	}
	// A�̏���
	if (key->GetKeyboardPress(DIK_A))
	{
		CPlayer::Move(m_fRunSpeed, 0.5f);
		SetCharacterDirection(DIRECTION::LEFT);

	}

	// D�̏���
	else if (key->GetKeyboardPress(DIK_D))
	{
		CPlayer::Move(-m_fRunSpeed, -0.5f);

		SetCharacterDirection(DIRECTION::RIGHT);
	}

	// ���Ⴊ��łȂ�����W�����Ă����ނ�
	if (key->GetKeyboardPress(DIK_W) && !m_bCruch)
	{
		SetCharacterDirection(DIRECTION::UP);
	}

	//�W�����v
	if ((key->GetKeyboardTrigger(DIK_SPACE) || m_pPad->GetTrigger(m_pPad->JOYPADKEY_A, 1)) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
	{
		GetMove().y += m_fJump;
		GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_JUMP);
	}
	//�W�����v���̓W�����v���[�V����
	else if (GetJump() == false && GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_JUMPSTOP)
	{
		GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_JUMP);
	}

	//�f�o�b�O�p
	else if (key->GetKeyboardPress(DIK_SPACE) && m_DebugState != DEBUG_NORMAL)
	{
		GetMove().y += 2;
	}

	//�W�����v���ĂȂ���
	if (GetJump())
	{
		//�U�����ĂȂ���
		if (GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_ATTACK01)
		{
			//�ړ�������E�H�[�N���[�V����
			if (fabsf(GetMove().x) > 0.3f)
			{
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_WALK);
				m_bCruch = false;
			}
			//S���������炵�Ⴊ�݃��[�V����
			else if ((key->GetKeyboardPress(DIK_S) || Pad_Y < -0.8f) && GetJump() == true)
			{
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_SQUATSTOP);
				m_bCruch = true;
			}
			//�W�����v�A���Ⴊ�݂����ĂȂ�������j���[�g����
			else
			{
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
				m_bCruch = false;
			}
		}
	}

	//�W�����v�����Ƃ�
	else if (GetModelSet()->GetMotionType() == CModelSet::PLAYER_MOTION_JUMP)
	{
		m_bCruch = false;

		//�L�[�Z�b�g���R�ɂȂ�����X�g�b�v���[�V������
		if (GetModelSet()->GetKeySet() == 3)
		{
			GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_JUMPSTOP);
		}
	}

	//�W�����v�����Ƃ��̉�������
	if (key->GetKeyboardPress(DIK_S) && GetJump() == false)
	{
		SetCharacterDirection(DIRECTION::DOWN);
	}

	//����������͂���Ă��Ȃ����͐��ʂ�����
	if (!(key->GetKeyboardPress(DIK_S) || key->GetKeyboardPress(DIK_W) || fabsf(Pad_Y) > 0.8f))
	{
		//���ʂ�����
		ResetCharacterDirection();
	}

	//���Ⴊ��ł��邩�ǂ����œ����蔻��̑傫���ݒ�
	m_bCruch ?
		GetCollision()->SetSize2D(PLAYER_SIZE_CRUCH):	//���Ⴊ�ݎ��̓����蔻��T�C�Y
		GetCollision()->SetSize2D(PLAYER_SIZE);			//�ʏ펞�̓����蔻��T�C�Y

	PadMoveUpdate();//�p�b�h�̍X�V

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
		// �Q�[���I�u�W�F�N�g( �^�O )�̐ݒ�
		GetCollision()->SetGameObject(this);

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

			// �A�C�e���Ƃ̔���
			if (GetCollision()->ForPlayer_ItemCollision(GetTag()))
			{
			}
		}

		if (m_bRideVehicle == false)
		{
			m_pVehicle = (CVehicle*)GetCollision()->ForPlayer_VehicleCollision();

			// ��蕨�Ƃ̔���
			if (m_pVehicle)
			{
				// ��荞�񂾎�
				m_bRideVehicle = true;
				m_pVehicle->SetTag(GetTag());
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

	if (m_pPad || key)
	{
		// �e������ or �ߐڍU��
		if (key->GetKeyboardTrigger(DIK_U) || m_pPad->GetTrigger(m_pPad->JOYPADKEY_X, 1))
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
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_ATTACK01);
			}
		}
		// �O���l�[�h�𓊂���
		if (key->GetKeyboardTrigger(DIK_O) || m_pPad->GetTrigger(m_pPad->JOYPADKEY_Y, 1))
		{
			// �O���l�[�h�̒e�����c���Ă���Ƃ�
			if (m_pGrenadeFire->GetGrenadeAmmo() > 0)
			{
				// �O���l�[�h����
				m_pGrenadeFire->Fire(GetShotDirection());

				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_GRENADE);
			}
		}
	}
	// �U�����[�V��������ʂ̃��[�V�����ɂȂ�����
	if (GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_ATTACK01)
	{
		m_bKnifeAttack = false;
		m_pKnife->EndMeleeAttack();
	}
}
//====================================================================
//�p�b�h�̈ړ��֘A�X�V
//====================================================================
void CPlayer::PadMoveUpdate(void)
{
	//�ړ���
	D3DXVECTOR3 MoveValue = ZeroVector3;


	//�p�b�h�ɂ����͏���
	if (CHossoLibrary::PadMoveInput(MoveValue, GetCharacterDirection(), GetJump(), GetTag()))
	{
		//�ړ��ʌv�Z
		Move(MoveValue.x, MoveValue.y);
	}

	D3DXVECTOR3 InputValue = ZeroVector3;

	if (m_pPad)
	{
		m_pPad->GetStickLeft(&InputValue.x, &InputValue.y);//�p�b�h�̓��͒l����

		InputValue.x /= STICK_MAX_RANGE;//�l�̐��K��
		InputValue.y /= STICK_MAX_RANGE;//�l�̐��K��
	}
	//�W�����v���[�V��������Ȃ������W�����v�X�g�b�v���[�V��������Ȃ���
	if (GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_JUMP &&
		GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_JUMPSTOP &&
		GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_ATTACK01)
	{
		//S���������炵�Ⴊ�݃��[�V����
		if (InputValue.y < -0.8f && GetJump() == true)
		{
			if (m_bCruch == false && GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_WALK)
			{
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_SQUATSTOP);
				m_bCruch = true;
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
		GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
	}
	return true;
}
//====================================================================
//�v���C���[���X�|�[������
//====================================================================
void CPlayer::MapChangePlayerRespawn()
{
	SetState(CCharacter::CHARACTER_STATE_INVINCIBLE);

	if (GetTwoPPlayFlag())
	{
		for (int nCnt = 0; nCnt < PLAYER_NUM_MAX; nCnt++)
		{
			// �v���C���[2�̔z�u
			SetPosition(GetPosition() + D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		}
	}
	else
	{
		SetPosition(m_pos[0]);
	}

	m_bRideVehicle = false;
	GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
}

//====================================================================
//�v���C���[���Z�b�g
//====================================================================
void CPlayer::ResetPlayer()
{
	D3DXVECTOR3 pos = D3DXVECTOR3(m_pos[0].x - 200.0f, m_pos[0].y, m_pos[0].z);
	SetPosition(pos);
	SetLife(m_nLife[0]);
	SetState(CCharacter::CHARACTER_STATE_INVINCIBLE);
	GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
	m_pGun->SetGunType(CGun::GUNTYPE_HANDGUN);
	m_pKnife->EndMeleeAttack();
	SetCharacterDirection(DIRECTION::RIGHT);
	m_pGrenadeFire->SetGrenadeAmmoDefault();
	m_bRideVehicle = false;
	m_bAttack = false;
	m_bCruch = false;
	m_bKnifeAttack = false;
	m_bRespawn = false;
}

//====================================================================
//�X�e�[�g�ɉ���������
//====================================================================
void CPlayer::State()
{
	//�X�e�[�g�؂�ւ������̃��A�N�V����
	CCharacter::State();

	//Player���ŃI�[�o�[���C�h
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_DAMAGE_FLASHING:
	case CHARACTER_STATE_INVINCIBLE:
	case CHARACTER_STATE_DEATH:
		GetCollision()->SetCanCollision(false);
		break;
	}
}

//====================================================================
//�_���[�W���̃��A�N�V����
//====================================================================
void CPlayer::DamageReaction()
{
	//�ߖ�
	CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_PLAYER_DAMAGE);

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
	//�X�e�[�g�؂�ւ������̃��A�N�V����
	CCharacter::StateChangeReaction();

	//Player���ŃI�[�o�[���C�h
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_NORMAL:
		break;

	case CHARACTER_STATE_DAMAGE_FLASHING:

		break;
	case CHARACTER_STATE_INVINCIBLE:

		break;
	case CHARACTER_STATE_ITEMGET_FLASH:
		GetModelSet()->ChangeColor(true, FlashColor);
		SetStateCount(3);
		break;

	case CHARACTER_STATE_DEATH:
		GetCollision()->SetCanCollision(false);
		SetStateCount(120);
		SetRespawnFlag(true);
		//�ߖ�
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_PLAYER_DEATH);

		GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_DEAD);
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
// ��蕨�ɏ���Ă��鎞
//====================================================================
void CPlayer::Ride()
{
	// ��蕨�ɏ���Ă��Ȃ����ɍX�V����
	if (m_bRideVehicle == false)
	{
		//�ړ��̍X�V
		MoveUpdate();

		//�U���̍X�V
		AttackUpdate();


		//�w�r�[�}�V���K���̂Ƃ�
		if (m_pGun->GetGunType() == CGun::GUNTYPE_HEAVYMACHINEGUN)
		{
			//������E�@���邢�͉E���獶�ɕ����]��������
			if ((CCharacter::GetCharacterDirection() == DIRECTION::LEFT && CCharacter::GetCharacterDirectionOld() == DIRECTION::RIGHT) ||
				(CCharacter::GetCharacterDirection() == DIRECTION::RIGHT && CCharacter::GetCharacterDirectionOld() == DIRECTION::LEFT))
			{
				//�ˊp�ݒ�
				m_ShotRot = GetShotDirection();
			}
			else
			{
				//�΂ߕ����ɂ��e�����Ă�悤�ɂ�������������]������
				D3DXVECTOR3 ShotRotDif = GetShotDirection() - m_ShotRot;

				//3.14�ȓ��ɗ}����
				CHossoLibrary::CalcRotation(ShotRotDif.z);

				//���X�ɉ�]
				m_ShotRot += ShotRotDif * 0.15f;
			}
		}
		//����ȊO�̂Ƃ�
		else
		{
			//�ˊp�ݒ�
			m_ShotRot = GetShotDirection();
		}

		// �e����������ݒ�
		m_pGun->SetShotRot(m_ShotRot);


		if (m_pGun->GetGunType() != m_pGun->GUNTYPE_HEAVYMACHINEGUN)
		{

		}

		//nullcheck
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
		//�v���C���[����蕨����~���Ƃ�
		if (key->GetKeyboardTrigger(DIK_SPACE)|| m_pPad->GetTrigger(m_pPad->JOYPADKEY_B,1) && GetJump() == false)
		{
			if(m_pVehicle != nullptr)
			{
				m_pVehicle->SetTag(TAG::NONE);
				m_pVehicle = nullptr;
			}
			m_bRideVehicle = false;
			GetMove().y += m_fRideJump;
			GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_JUMP);
		}
	}
}
//====================================================================
//���X�|�[��
//====================================================================
void CPlayer::ReSpawn(void)
{
	m_nRespawnCnt++;

	if (m_nRespawnCnt >= RESPAWN_INTERVAL)
	{
		//�c�@�������ꍇ
		if (m_pPlayerUI->GetStock() <= 0)
		{
			//�Q�[���I�[�o�[
			CManager::GetGame()->GetGameManager()->SetGameState(CGameManager::GAMESTATE::GAMEOVER);
		}
		else
		{
			//���Z�b�g
			m_nRespawnCnt = 0;
			m_bRespawn = false;
			m_pGun->SetGunType(CGun::GUNTYPE_HANDGUN);
			GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
			SetState(CHARACTER_STATE_INVINCIBLE);
			SetLife(m_nLife[0]);
			m_pPlayerUI->SetStockUI(m_pPlayerUI->GetStock() - 1);
			m_pGrenadeFire->SetGrenadeAmmoDefault();
			m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());

		}
	}
}

//====================================================================
//���f���̃N���G�C�g
//====================================================================
CPlayer *CPlayer::Create(TAG Tag)
{
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->SetTag(Tag);
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
	// �ړ����x�̏����擾
	m_fRunSpeed = m_PlayerData.fRunSpeed;
	// ���Ⴊ�ݎ��̈ړ����x�̏����擾
	m_fCrouchSpeed = m_PlayerData.fCrouchSpeed;
	// �ʏ펞�̃W�����v��
	m_fJump = m_PlayerData.fJump;
	// ��蕨����~��鎞�̃W�����v��
	m_fRideJump = m_PlayerData.fRideJump;
}
