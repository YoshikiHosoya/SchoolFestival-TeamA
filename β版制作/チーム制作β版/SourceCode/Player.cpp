//====================================================================
// �v���C���[���� [player.cpp]: NORI
//====================================================================
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

//====================================================================
//�}�N����`
//====================================================================
#define PLAYER_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f)) //�G�̃T�C�Y
// �ђʂ����邩�̃t���O
#define ATTACK_PENETRATION		(true)			// �v���C���[�̔��肪�ђʂ��邩�ǂ���
#define ATTACK_DAMAGE_ENEMY		(50)			// �G�l�~�[�ւ̃_���[�W
#define SHOT_BULLET_POS_Y		(-15.0f)		// �e�̔��ˈʒuY
#define SHOT_BULLET_POS_Z		(-5.0f)			// �e�̔��ˈʒuZ

CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
}

CPlayer::~CPlayer()
{
}
//====================================================================
//������
//====================================================================
HRESULT CPlayer::Init(void)
{
	//�L�����̏�����
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_PLAYER);
	SetCharacterType(CCharacter::CHARACTER_TYPE_PLAYER);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_bAttack = false;
	m_bKnifeAttack = false;
	m_bCruch = false;
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
	// �v���C���[UI�̐���
	m_pPlayerUI = CPlayerUI::Create();
	// ��蕨�ɏ�荞��ł��邩�ǂ����̃t���O
	m_bRideVehicle = false;

	// �e�̎c���\��
	m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
	// �O���l�[�h�̎c���\��
	m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
	//�����̌���
	SetCharacterDirection(CHARACTER_RIGHT);
	//���X�|�[�����̃J�E���g
	m_nRespawnCnt = 0;
	//�v���C���[�̏�ԃX�e�[�^�X
	m_PlayerState = PLAYER_STATE_NORMAL;

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
		m_pGun->Rerease();
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
	m_pPlayerUI->SetLifeUI(GetLife());
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
	if (m_bRespawn == false)
	{
		if (key->GetKeyboardPress(DIK_W))
		{
			SetCharacterDirection(CHARACTER_UP);
		}

		// A�̏���
		if (key->GetKeyboardPress(DIK_A))
		{
			CPlayer::Move(0.5f, 0.5f);
			if (key->GetKeyboardPress(DIK_W))
			{
				SetCharacterDirection(CHARACTER_UP);
			}
			else
			{
				SetCharacterDirection(CHARACTER_LEFT);
			}
		}
		// D�̏���
		else if (key->GetKeyboardPress(DIK_D))
		{
			CPlayer::Move(-0.5f, -0.5f);
			if (key->GetKeyboardPress(DIK_W))
			{
				SetCharacterDirection(CHARACTER_UP);
			}
			else
			{
				SetCharacterDirection(CHARACTER_RIGHT);
			}
		}

		//�W�����v
		if (key->GetKeyboardTrigger(DIK_SPACE) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
		{
			GetMove().y += 27;
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
					//�ړ����ĂȂ��������Ⴊ�݃X�g�b�v����Ȃ���
					else if (GetMotionType() != PLAYER_MOTION_SQUATSTOP&& m_bCruch == false)
					{
						SetMotion(PLAYER_MOTION_NORMAL);
					}
					//S���������炵�Ⴊ�݃��[�V����
					if (key->GetKeyboardPress(DIK_S) && GetJump() == true)
					{
						if (m_bCruch == false && GetMotionType() != PLAYER_MOTION_WALK)
						{
							SetMotion(PLAYER_MOTION_SQUATSTOP);
							m_bCruch = true;
						}
					}
					else if (GetJump() == true && GetMotionType() != PLAYER_MOTION_WALK)
					{
						m_bCruch = false;
						SetMotion(PLAYER_MOTION_NORMAL);
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
			SetCharacterDirection(CHARACTER_DOWN);
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
			// �G�l�~�[�ƂƂ̔���
			if (GetCollision()->ForPlayer_EnemyCollision(ATTACK_PENETRATION) == true||
				GetCollision()->ForPlayer_PrisonerCollision(ATTACK_PENETRATION) == true)
			{
				m_bAttack = true;
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
	if (m_bRespawn == false)
	{
		// �e������ or �ߐڍU��
		if (key->GetKeyboardTrigger(DIK_P))
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
		if (key->GetKeyboardTrigger(DIK_O))
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
//���f���̃N���G�C�g
//====================================================================
CPlayer *CPlayer::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->Init();
	return pPlayer;
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

		// �e����������ݒ�
		m_pGun->SetShotRot(GetShotDirection());
		// �e�̎c���\��
		m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
		// �O���l�[�h�̎c���\��
		m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
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
			// �v���C���[�̍��W���Ԃ̍��W�ɍ��킹��
			this->SetPosition(pPlayertank->GetPosition());

			// �e�̎c���\��
			m_pPlayerUI->SetBulletAmmo(pPlayertank->GetGun()->GetGunAmmo(), pPlayertank->GetGun()->GetGunType());
			// �O���l�[�h�̎c���\��
			m_pPlayerUI->SetGrenadeAmmo(pPlayertank->GetGrenadeFire()->GetGrenadeAmmo());
		}

		// �퓬�@�ɏ���Ă��鎞
		else if (pBattlePlane != nullptr)
		{
			// �v���C���[�̍��W��퓬�@�̍��W�ɍ��킹��
			this->SetPosition(pBattlePlane->GetPosition());

			// �e�̎c���\��
			m_pPlayerUI->SetBulletAmmo(pBattlePlane->GetGun()->GetGunAmmo(), pBattlePlane->GetGun()->GetGunType());
		}

		// ��蕨�ɏ���Ă��鎞�ɃW�����v���Đ�Ԃ���~���
		CKeyboard *key = CManager::GetInputKeyboard();
		if (key->GetKeyboardTrigger(DIK_SPACE) && GetJump() == false)
		{
			m_bRideVehicle = false;
			GetMove().y += 40;
			SetMotion(PLAYER_MOTION_JUMP);

			// ���G����
		}
	}
}
//====================================================================
//���X�|�[��
//====================================================================
void CPlayer::ReSpawn(void)
{
	m_nRespawnCnt++;
	m_PlayerState = PLAYER_STATE_RESPAWN;

	if (m_nRespawnCnt == 120)
	{
		m_nRespawnCnt = 0;
		m_bRespawn = false;
		m_pGun->SetGunType(CGun::GUNTYPE_HANDGUN);
		SetLife(10);
	}
}
