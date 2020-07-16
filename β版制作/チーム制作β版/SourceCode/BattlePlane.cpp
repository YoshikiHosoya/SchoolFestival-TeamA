// =====================================================================================================================================================================
//
// �퓬�@���� [BattlePlane.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "battleplane.h"
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

//====================================================================
//�}�N����`
//====================================================================
#define PLANE_SIZE				(D3DXVECTOR3(90.0f,40.0f,0.0f)) // �퓬�@�̔���̃T�C�Y
#define SHOT_BULLET_POS_X		(0.0f)			// �e�̔��ˈʒuX
#define SHOT_BULLET_POS_Y		(25.0f)			// �e�̔��ˈʒuY
#define SHOT_BULLET_POS_Z		(0.0f)			// �e�̔��ˈʒuZ

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CBattlePlane::CBattlePlane(OBJ_TYPE type) :CVehicle(type)
{
	// �I�u�W�F�N�g�̐ݒ�
	SetObjType(OBJTYPE_PLAYER_VEHICLE);
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CBattlePlane::~CBattlePlane()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CBattlePlane::Init(void)
{
	// ��蕨�̏����ݒ�
	CVehicle::Init();
	// �I�t�Z�b�g�̓ǂݍ���
	LoadOffset(CVehicle::VEHICLE_TYPE_PLANE);
	// ��蕨�̃^�C�v�̐ݒ�
	SetVehicleType(CVehicle::VEHICLE_TYPE_PLANE);
	// �e�̐���
	m_pGun = CGun::Create(GetVehicleModelPartsList(CModel::MODEL_PLANE_GUN)->GetMatrix());
	// �e�̒e�̎��
	m_pGun->GetTag() = TAG_PLAYER;
	// �e�̒e�̎��
	m_pGun->SetGunType(CGun::GUNTYPE_PLANEGUN);
	// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(SHOT_BULLET_POS_X, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));
	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(PLANE_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}

//====================================================================
//
// �I��
//
//====================================================================
void CBattlePlane::Uninit(void)
{
	// �e�̃|�C���^
	if (m_pGun)
	{
		m_pGun->Rerease();
		m_pGun = nullptr;
	}

	// �v���C���[�̃|�C���^���擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	if (pPlayer != nullptr)
	{
		pPlayer->SetRideFlag(false);
	}

	CVehicle::Uninit();
}
//====================================================================
//
// �X�V
//
//====================================================================
void CBattlePlane::Update(void)
{
	// �L�[���̎擾
	CKeyboard *key = CManager::GetInputKeyboard();

	// �v���C���[�̃|�C���^���擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	if (pPlayer != nullptr)
	{
		// ��蕨�ɏ���Ă��鎞
		if (pPlayer->GetRideFlag())
		{
			// ��Ԃ��e��������
			Shot(key);

			// ��Ԃ𑀍삷�鏈��
			Operation(key);

			// �p�[�c�̉�]����
			VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_PLANE_GUN), MODEL_ROT_TYPE_OPERATION);
		}
	}

	// ������܂Ƃ߂čs��
	Collision();

	// ��蕨�N���X�̍X�V
	CVehicle::Update();
}
//====================================================================
//
// �`��
//
//====================================================================
void CBattlePlane::Draw(void)
{
	CVehicle::Draw();
}

//====================================================================
// �f�o�b�O
//====================================================================
void CBattlePlane::DebugInfo(void)
{
	CVehicle::DebugInfo();
}

//====================================================================
// ��ԃ��f���̃N���G�C�g
//====================================================================
CBattlePlane *CBattlePlane::Create(void)
{
	// �������̊m��
	CBattlePlane *pPlayertank = new CBattlePlane(OBJTYPE_PLAYER_VEHICLE);
	// ������
	pPlayertank->Init();
	// �|�C���^��Ԃ�
	return pPlayertank;
}

//====================================================================
// �e��ł���
//====================================================================
void CBattlePlane::Shot(CKeyboard *key)
{
	// �}�V���K��������
	if (key->GetKeyboardTrigger(DIK_P))
	{
		// �K���̃��f���̔��ˌ�����e�𐶐�
		m_pGun->Shot();
	}
	// �e����������ݒ�
	m_pGun->SetShotRot(GetVehicleModelPartsList(CModel::MODEL_PLANE_GUN)->GetRot());
}

//====================================================================
// ���쏈��
//====================================================================
void CBattlePlane::Operation(CKeyboard * key)
{
	// �������
	if (key->GetKeyboardPress(DIK_W))
	{
		CVehicle::MovePlane(D3DXVECTOR3(0.0f, 1.0f, 0.0f), -0.5f);
		SetVehicleDirection(VEHICLE_UP);
	}
	// �������
	else if (key->GetKeyboardPress(DIK_S))
	{
		CVehicle::MovePlane(D3DXVECTOR3(0.0f, -1.0f, 0.0f), -0.5f);
		SetVehicleDirection(VEHICLE_DOWN);
	}

	// ���ɓ�������
	if (key->GetKeyboardPress(DIK_A))
	{
		// �������
		if (key->GetKeyboardPress(DIK_W))
		{
			CVehicle::MovePlane(D3DXVECTOR3(-1.0f, 1.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_UP);
		}

		// ��������
		else if (key->GetKeyboardPress(DIK_S))
		{
			CVehicle::MovePlane(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_DOWN);
		}

		// ��������
		else
		{
			CVehicle::MovePlane(D3DXVECTOR3(-1.0f, 0.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_LEFT);
		}
	}

	// �E�ɓ�������
	else if (key->GetKeyboardPress(DIK_D))
	{
		// �������
		if (key->GetKeyboardPress(DIK_W))
		{
			CVehicle::MovePlane(D3DXVECTOR3(1.0f, 1.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_UP);
		}

		// ��������
		else if (key->GetKeyboardPress(DIK_S))
		{
			CVehicle::MovePlane(D3DXVECTOR3(1.0f, -1.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_DOWN);
		}

		// �E������
		else
		{
			CVehicle::MovePlane(D3DXVECTOR3(1.0f, 0.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_RIGHT);
		}
	}
}

//====================================================================
// �����蔻��
//====================================================================
void CBattlePlane::Collision()
{
	// �����蔻��
	if (GetCollision() != nullptr)
	{
		// ���W�̍X�V pos��posold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());
	}

	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// �}�b�v���f�������݂�����
	if (pMap != nullptr)
	{
		// ���C�̔���
		if (GetCollision()->RayBlockCollision(pMap, GetMtxWorld()))
		{
		}
	}
}
