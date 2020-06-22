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
#include"XInputPad.h"

CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
	m_pCollision = NULL;
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	m_Attack = false;
	m_ShotRot = D3DXVECTOR3(0.0f, 0.5f, 0.0f);

	 // �e�̐���
	m_pGun = CGun::Create(CCharacter::GetMtxWorld());
	// �e�̒e�̎��
	m_pGun->GetBulletType() = CGun::TYPE_PLAYER;

	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(D3DXVECTOR3(50.0f, 100.0f, 0.0f));
	m_pCollision->SetMove(&GetMove());
	m_pCollision->SetType(CCollision::OBJTYPE_PLAYER);

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
	// �e������
	if (key->GetKeyboardTrigger(DIK_P))
	{
		// �e���ˏ���
		m_pGun->Shot(m_ShotRot);
	}

	// A�̏���
	if (key->GetKeyboardPress(DIK_A))
	{
		CPlayer::Move(0.5f, 0.5f);
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = 0.5f * D3DX_PI;
		SetCharacterDirection(CHARACTER_LEFT);
	}
	// D�̏���
	else if (key->GetKeyboardPress(DIK_D))
	{
		CPlayer::Move(-0.5f, -0.5f);
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = -0.5f * D3DX_PI;
		SetCharacterDirection(CHARACTER_RIGHT);
	}

	else if (key->GetKeyboardPress(DIK_W))
	{
		SetCharacterDirection(CHARACTER_UP);
		m_ShotRot.y = 0.0f;
		m_ShotRot.x = 0.5f * D3DX_PI;
	}
	//�W�����v�����Ƃ��̉�������
	if (key->GetKeyboardPress(DIK_S) && GetJump() == false)
	{
		SetCharacterDirection(CHARACTER_DOWN);
		m_ShotRot.y = 0.0f;
		m_ShotRot.x = -0.5f * D3DX_PI;
	}
	if (GetCharacterDirection() == CHARACTER_DOWN && GetJump() == true)
	{
		if (GetRot().y > 1.5f)
		{
			m_ShotRot.x = 0.0f;
			m_ShotRot.y = 0.5f * D3DX_PI;
			SetCharacterDirection(CHARACTER_LEFT);
		}
		else if (GetRot().y < -1.5f)
		{
			m_ShotRot.x = 0.0f;
			m_ShotRot.y = -0.5f * D3DX_PI;
			SetCharacterDirection(CHARACTER_RIGHT);
		}
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
	if (m_pCollision != NULL)
	{
		// ���W�̍X�V pos��posold
		m_pCollision->SetPos(&GetPosition());

		// �����蔻�� ���肪�G�l�~�[��������
		// �G�̑�����
		for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
		{
			CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
			if (pEnemy != NULL)
			{
				/*if (m_pCollision->Collision2D(pEnemy->GetCollision()))
				{
					CDebugProc::Print("\n���@���G�ɓ���������I\n");
				}
				else
				{
					CDebugProc::Print("\n���@���G�ɓ������ĂȂ���I \n");
				}*/
			}
		}

	}
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
	CDebugProc::Print("�v���C���[�̌���%2f", GetRot().y);
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CPlayer *CPlayer::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->Init();
	return pPlayer;
}
void CPlayer::DefaultMotion(void)
{
	SetMotion(CCharacter::PLAYER_MOTION_NORMAL);
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
