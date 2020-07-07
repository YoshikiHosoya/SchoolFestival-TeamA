// =====================================================================================================================================================================
//
// �v���C���[�̐�ԏ��� [playertank.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "playertank.h"
#include "player.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "Xinput.h"
#include "gun.h"
#include "collision.h"
#include "BaseMode.h"
#include "manager.h"
#include "enemy.h"
#include "map.h"
#include "XInputPad.h"
#include "Obstacle.h"
#include "prisoner.h"
#include "grenade.h"
#include "grenadefire.h"

//====================================================================
//�}�N����`
//====================================================================
#define PLAYERTANK_SIZE			(D3DXVECTOR3(70.0f,65.0f,0.0f)) // �v���C���[�̔���̃T�C�Y
#define PLAYERTANK_JUMP			(20.0f)							 // ��Ԃ���Ԉړ���

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPlayertank::CPlayertank(OBJ_TYPE type) :CVehicle(type)
{
	// �I�u�W�F�N�g�̐ݒ�
	SetObjType(OBJTYPE_PLAYER_VEHICLE);
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CPlayertank::~CPlayertank()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CPlayertank::Init(void)
{
	// ��蕨�̏����ݒ�
	CVehicle::Init();
	// �I�t�Z�b�g�̓ǂݍ���
	LoadOffset(CVehicle::VEHICLE_TYPE_TANK);
	// ��蕨�̃^�C�v�̐ݒ�
	SetVehicleType(CVehicle::VEHICLE_TYPE_TANK);
	// �e�̐���
	m_pGun = CGun::Create(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKHEAD)->GetMatrix());
	// �O���l�[�h���ʒu�̐���
	m_pGrenadeFire = CGrenadeFire::Create(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKHEAD)->GetMatrix());
	// �e�̒e�̎��
	m_pGun->GetTag() = TAG_PLAYER;

	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(PLAYERTANK_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}

//====================================================================
//
// �I��
//
//====================================================================
void CPlayertank::Uninit(void)
{
	CVehicle::Uninit();
}
//====================================================================
//
// �X�V
//
//====================================================================
void CPlayertank::Update(void)
{
	// �L�[���̎擾
	CKeyboard *key = CManager::GetInputKeyboard();

	// �����蔻�菈��
	Collision();

	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	if (pPlayer != nullptr)
	{
		// ��Ԃɏ���Ă�����
		if (pPlayer->GetRideFlag())
		{
			// ��Ԃ��e��������
			Shot(key);

		if (GetCollision()->RayBlockCollision(pMap,GetMtxWorld()))
			// ��Ԃ𑀍삷�鏈��
			Operation(key);
		}
	}

	// ��蕨�N���X�̍X�V
	CVehicle::Update();
}
//====================================================================
//
// �`��
//
//====================================================================
void CPlayertank::Draw(void)
{
	CVehicle::Draw();
}

//====================================================================
// �f�o�b�O
//====================================================================
void CPlayertank::DebugInfo(void)
{
	//CVehicle::DebugInfo();
}

//====================================================================
// ��ԃ��f���̃N���G�C�g
//====================================================================
CPlayertank *CPlayertank::Create(void)
{
	// �������̊m��
	CPlayertank *pPlayertank = new CPlayertank(OBJTYPE_PLAYER_VEHICLE);
	// ������
	pPlayertank->Init();
	// �|�C���^��Ԃ�
	return pPlayertank;
}

//====================================================================
// �e��ł���
//====================================================================
void CPlayertank::Shot(CKeyboard *key)
{
	// �}�V���K��������
	if (key->GetKeyboardTrigger(DIK_P))
	{
		// �}�V���K�����ˏ���
		m_pGun->Shot(GetShotDirection());
	}

	// �O���l�[�h������
	if (key->GetKeyboardTrigger(DIK_O))
	{
		// �O���l�[�h�̒e�����c���Ă���Ƃ�
		if (m_pGrenadeFire->GetGrenadeAmmo() > 0)
		{
			// �O���l�[�h����
			m_pGrenadeFire->Fire(GetShotDirection());
		}
	}
}

//====================================================================
// ���쏈��
//====================================================================
void CPlayertank::Operation(CKeyboard * key)
{
	// �������
	if (key->GetKeyboardPress(DIK_W))
	{
		SetVehicleDirection(VEHICLE_UP);
	}
	// �������
	else if (key->GetKeyboardPress(DIK_S))
	{
		SetVehicleDirection(VEHICLE_DOWN);
	}

	// ���ɓ�������
	if (key->GetKeyboardPress(DIK_A))
	{
		CVehicle::Move(0.5f, 0.5f);

		// �������
		if (key->GetKeyboardPress(DIK_W))
		{
			SetVehicleDirection(VEHICLE_UP);
		}

		// ��������
		else
		{
			SetVehicleDirection(VEHICLE_LEFT);
		}
	}

	// �E�ɓ�������
	else if (key->GetKeyboardPress(DIK_D))
	{
		CVehicle::Move(-0.5f, -0.5f);

		// �������
		if (key->GetKeyboardPress(DIK_W))
		{
			SetVehicleDirection(VEHICLE_UP);
		}

		// ��������
		else
		{
			SetVehicleDirection(VEHICLE_RIGHT);
		}
	}

	// �W�����v����
	if (key->GetKeyboardPress(DIK_W))
	{
		// 1��W�����v������
		Jump();
	}
}

//====================================================================
// �W�����v����
//====================================================================
void CPlayertank::Jump()
{
	// 1�񕪃W�����v����
	if (GetJump() == true)
	{
		GetMove().y += PLAYERTANK_JUMP;
	}
	// �W�����v�t���O��true�ɂ��W�����v�ł��Ȃ�����
	SetJump(false);
}

//====================================================================
// �����蔻�菈��
//====================================================================
void CPlayertank::Collision()
{
	// �����蔻��
	if (GetCollision() != nullptr)
	{
		// ���W�̍X�V pos��posold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());

		// ��Q���Ƃ̔���
		//if (GetCollision()->ForPlayer_ObstacleCollision())
		//{
		//	// �W�����v�t���O���\�ɂ���
		//	CVehicle::SetJump(true);
		//}
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
}
