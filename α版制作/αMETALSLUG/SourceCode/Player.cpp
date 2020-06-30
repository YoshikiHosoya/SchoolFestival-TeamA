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

//====================================================================
//�}�N����`
//====================================================================
#define PLAYER_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f)) //�G�̃T�C�Y

CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
	m_pCollision = nullptr;
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
	m_Attack = false;
	m_ShotRot = D3DXVECTOR3(0.0f, 0.5f, 0.0f);

	 // �e�̐���
	m_pGun = CGun::Create(CCharacter::GetMtxWorld());
	// �e�̒e�̎��
	m_pGun->GetBulletType() = CGun::TYPE_PLAYER;

	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(PLAYER_SIZE);
	m_pCollision->SetMove(&GetMove());
	m_pCollision->SetType(CCollision::OBJTYPE_PLAYER);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

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
	// �O���l�[�h�𓊂���
	if (key->GetKeyboardTrigger(DIK_O))
	{
		// �O���l�[�h����
		CGrenade::Create(m_ShotRot);
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
	if (m_pCollision != nullptr)
	{
		// ���W�̍X�V pos��posold
		m_pCollision->SetPos(&GetPosition());
		m_pCollision->SetPosOld(&GetPositionOld());

		//���肪�G�l�~�[��������
		// �G�̑�����
		for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
		{
			CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
			if (pEnemy != nullptr)
			{
				if (m_pCollision->CharCollision2D(pEnemy->GetCollision()))
				{
					CDebugProc::Print("\n���@���G�ɓ���������I\n");
				}
				else
				{
					CDebugProc::Print("\n���@���G�ɓ������ĂȂ���I \n");
				}
			}
		}

		//���肪��Q����������
		// ��Q���̂̑�����
		for (int nCntObst = 0; nCntObst < CManager::GetBaseMode()->GetMap()->GetMaxObstacle(); nCntObst++)
		{
			CObstacle *pObstacle = CManager::GetBaseMode()->GetMap()->GetObstacle(nCntObst);
			if (pObstacle != nullptr)
			{
				if (m_pCollision->BlockCollision2D(pObstacle->GetCollision()))
				{
					CCharacter::SetJump(true);
					CDebugProc::Print("\n���@����Q���ɓ���������I\n");
				}
				else
				{
					CDebugProc::Print("\n���@����Q���ɓ������ĂȂ���I \n");
				}
			}
		}

		//���肪�A�C�e����������
		// �x�N�^�[�^�̕ϐ�
		std::vector<CScene*> SceneList;

		// �w�肵���I�u�W�F�N�g�̃|�C���^���擾
		CScene::GetSceneList(OBJTYPE_ITEM, SceneList);

		//�A�C�e���̑�����
		for (size_t nCnt = 0; nCnt < SceneList.size(); nCnt++)
		{
			CItem *pItem = (CItem*)SceneList[nCnt];
			if (pItem != nullptr)
			{
				if (m_pCollision->OtherCollision2D(pItem->GetCollision()))
				{
					// �A�C�e�����Ƃ̏�����ʂ�
					pItem->HitItem(pItem->GetItemType());
					pItem->DeleteCollision();
					pItem = nullptr;
				}
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
}
