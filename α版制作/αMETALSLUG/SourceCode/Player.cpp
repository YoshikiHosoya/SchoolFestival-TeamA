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
#include "bullet.h"

//====================================================================
//�}�N����`
//====================================================================
#define PLAYER_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f)) //�G�̃T�C�Y
// �ђʂ����邩�̃t���O
#define ATTACK_PENETRATION		(true)			// �v���C���[�̔��肪�ђʂ��邩�ǂ���
#define ATTACK_DAMAGE_ENEMY		(50)			// �G�l�~�[�ւ̃_���[�W

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
	m_bAttack_Enemy = false;
	m_bAttack_Prisoner = false;
	 // �e�̐���
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_RHAND)->GetMatrix());
	// �O���l�[�h���ʒu�̐���
	m_pGrenadeFire = CGrenadeFire::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
	// �e�̒e�̎��
	m_pGun->GetTag() = TAG_PLAYER;
	// �i�C�t�̐���
	m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
	// �v���C���[UI�̐���
	m_pPlayerUI = CPlayerUI::Create();

	// �e�̎c���\��
	m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo());
	// �O���l�[�h�̎c���\��
	m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());

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

		delete m_pPlayerUI;
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
	if (m_DebugState != DEBUG_NORMAL)
	{
	}

	if (key->GetKeyboardTrigger(DIK_1))
	{
		SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	}
	if (key->GetKeyboardTrigger(DIK_2))
	{
		SetMotion(PLAYER_MOTION_JUMP);
	}

	// ����̃{�^�������������ɕ������[�V�����ɕύX
	if (CHossoLibrary::PressAnyButton())
	{
		//SetMotion(CCharacter::PLAYER_MOTION_WALK);
	}
	MoveUpdate();
	AttackUpdate();
	CollisionUpdate();

	// �e�̎c���\��
	m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo());
	// �O���l�[�h�̎c���\��
	m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());

	CCharacter::Update();
}
//====================================================================
//�`��
//====================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//�f�o�b�O
//====================================================================
void CPlayer::DebugInfo(void)
{
	CDebugProc::Print("�v���C���[�̃��[�V�����F%d\n", GetMotionType());
	CDebugProc::Print("�v���C���[�̃��[�V�����t���[���F%d\n", GetFram());
	CDebugProc::Print("�v���C���[�̃��[�V�����L�[�F%d\n", GetKeySet());
	if (GetJump() == false)
	{
		CDebugProc::Print("�W�����v�ł��Ȃ�\n");
	}
	else
	{
	}
}
//====================================================================
//�ړ��֘A
//====================================================================
void CPlayer::MoveUpdate(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
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
	if (GetMotionType() != PLAYER_MOTION_JUMP)
	{
		if (GetMotionType() != PLAYER_MOTION_JUMPSTOP)
		{
			if (GetMove().x > 0.2f || GetMove().x < -0.2f)
			{
				SetMotion(PLAYER_MOTION_WALK);
			}
			else
			{
				SetMotion(PLAYER_MOTION_NORMAL);
			}
		}
		else if (GetJump() == true)
		{
			SetMotion(PLAYER_MOTION_NORMAL);
		}
	}
	else if (GetMotionType() == PLAYER_MOTION_JUMP)
	{
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
//====================================================================
//�����蔻��֘A
//====================================================================
void CPlayer::CollisionUpdate(void)
{

	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// �}�b�v���f�������݂�����
	if (pMap != nullptr)
	{
		// ���C�̔���
		if (GetCollision()->RayBlockCollision(pMap))
		{
			// �W�����v���邱�Ƃ����F����
			SetJump(true);
		}
		else
		{
			// �W�����v���邱�Ƃ����F���Ȃ�
			SetJump(false);
			//�󒆂ɂ��邩
		}
	}

	// �����蔻��
	if (GetCollision() != nullptr)
	{
		// ���W�̍X�V pos��posold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());

		// �G�l�~�[�ƂƂ̔���
		if (GetCollision()->ForPlayer_EnemyCollision(ATTACK_PENETRATION) == true)
		{
			// �ߐڍU���\�ɂ���
			m_bAttack_Enemy = true;
		}
		else
		{
			// �ߐڍU���������ɂȂ�
			m_bAttack_Enemy = false;
		}

		// �ߗ��Ƃ̔���
		if (GetCollision()->ForPlayer_PrisonerCollision(ATTACK_PENETRATION) == true)
		{
			// �ߐڍU���\�ɂ���
			m_bAttack_Prisoner = true;
		}
		else
		{
			// �ߐڍU���������ɂȂ�
			m_bAttack_Prisoner = false;
		}

		// ��Q���Ƃ̔���
		if (GetCollision()->ForPlayer_ObstacleCollision())
		{
			// �W�����v�t���O���\�ɂ���
			CCharacter::SetJump(true);
		}

		// �A�C�e���Ƃ̔���
		if (GetCollision()->ForPlayer_ItemCollision())
		{
		}
	}


}
//====================================================================
//�U���֘A
//====================================================================
void CPlayer::AttackUpdate(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

	// �e������ or �ߐڍU��
	if (key->GetKeyboardTrigger(DIK_P))
	{
		// �ߗ��̃|�C���^���擾
		CPrisoner	*pPrisoner = GetCollision()->ForPlayer_PrisonerCollision();

		// �|�C���^��null����Ȃ�������
		if (pPrisoner != nullptr)
		{
			// �e�����Ă��Ԃ�������
			if (m_bAttack_Enemy == false && m_bAttack_Prisoner == false)
			{// �e���ˏ���
				m_pGun->Shot(GetShotDirection());
			}
			// �ߗ�������\�ȏ�Ԃ�������
			else if (pPrisoner->GetPrisonerState() != CPrisoner::PRISONER_STATE_STAY)
			{
				m_pGun->Shot(GetShotDirection());
			}
		}
		// �ߗ������Ȃ����͒ʏ�ʂ�e������
		else
		{
			m_pGun->Shot(GetShotDirection());
		}

		// �ߐڍU���������Ԃ�������
		if (m_bAttack_Enemy == true)
		{// �ߐڍU��
		 // �G�l�~�[�Ƃ̐ڐG���� �ߗ��̏�Ԃ�ς���
			CEnemy		*pEnemy = GetCollision()->ForPlayer_EnemyCollision();
			if (pEnemy != nullptr)
			{
				// �ߐڍU��
				SetMotion(CCharacter::PLAYER_MOTION_ATTACK01);
				m_pKnife->StartMeleeAttack();
			}
		}

		// �ߐڔ��肪�o�Ă��鎞�͋ߐڍU��������
		if (m_bAttack_Prisoner == true)
		{// �ߐڍU��
		 // �ߗ��Ƃ̐ڐG���� �ߗ��̏�Ԃ�ς���
			CPrisoner	*pPrisoner = GetCollision()->ForPlayer_PrisonerCollision();

			// �|�C���^��null����Ȃ�������
			if (pPrisoner != nullptr)
			{
				// �ߗ�������\�ȏ�Ԃ�������
				if (pPrisoner->GetPrisonerState() == CPrisoner::PRISONER_STATE_STAY)
				{
					// �ߐڍU��
					SetMotion(CCharacter::PLAYER_MOTION_ATTACK01);
					// �i�C�t����
					m_pKnife->StartMeleeAttack();
					// �ߗ��̏�Ԃ��A�C�e���𗎂Ƃ���Ԃɂ���
					pPrisoner->SetPrisonerState(CPrisoner::PRISONER_STATE_DROPITEM);
				}
			}
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
		if (m_bAttack_Enemy == false && m_bAttack_Prisoner == false)
		{
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
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}
