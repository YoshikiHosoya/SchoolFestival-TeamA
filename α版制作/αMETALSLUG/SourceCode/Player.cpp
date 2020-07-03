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
	m_pPrisoner = nullptr;
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
	// �e�̒e�̎��
	m_pGun->GetBulletType() = CGun::TYPE_PLAYER;
	// �i�C�t�̐���
	m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());

	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(PLAYER_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->SetType(CCollision::COLLISION_PLAYER);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CPlayer::Uninit(void)
{
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

	//�L�[�{�[�h����
	// �e������ or �ߐڍU��
	if (key->GetKeyboardTrigger(DIK_P))
	{

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
			CEnemy		*pEnemy		= GetCollision()->ForPlayer_EnemyCollision();

			if (pEnemy != nullptr)
			{
				// �ߐڍU��
				SetMotion(CCharacter::PLAYER_MOTION_ATTACK01);
				m_pKnife->StartMeleeAttack();
				// �G�l�~�[�փ_���[�W
				pEnemy->AddDamage(ATTACK_DAMAGE_ENEMY);
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
					// ���̕ߗ��̃|�C���^�͎擾�ł��Ȃ��悤�ɂ���
					pPrisoner->SetPrisonerUseFlag(true);
				}
			}
		}
	}

	// �O���l�[�h�𓊂���
	if (key->GetKeyboardTrigger(DIK_O))
	{
		// �O���l�[�h����
		CGrenade::Create(GetShotDirection() , GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
		SetMotion(CCharacter::PLAYER_MOTION_GRENADE);
	}
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


	//�W�����v�����Ƃ��̉�������
	if (key->GetKeyboardPress(DIK_S) && GetJump() == false)
	{
		SetCharacterDirection(CHARACTER_DOWN);
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
	if (m_DebugState != DEBUG_NORMAL)
	{
	}
	//�W�����v
	if (key->GetKeyboardTrigger(DIK_SPACE) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
	{
		GetMove().y += 27;
	}

	else if (key->GetKeyboardPress(DIK_SPACE) && m_DebugState != DEBUG_NORMAL)
	{
		GetMove().y += 2;
	}

	if (key->GetKeyboardTrigger(DIK_1))
	{
		SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	}
	if (key->GetKeyboardTrigger(DIK_2))
	{
		SetMotion(CCharacter::PLAYER_MOTION_WALK);
	}

	// �����蔻��
	if (GetCollision() != nullptr)
	{
		// ���W�̍X�V pos��posold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());

		// �G�l�~�[�ƂƂ̔���
		if (GetCollision()->ForPlayer_EnemyCollision(ATTACK_PENETRATION))
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

	// ����̃{�^�������������ɕ������[�V�����ɕύX
	if (CHossoLibrary::PressAnyButton())
	{
		SetMotion(CCharacter::PLAYER_MOTION_WALK);
	}
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
	SetMotion(CCharacter::PLAYER_MOTION_NORMAL);
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
	SetMotion(PLAYER_MOTION_WALK);
}
