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
#include "grenadefire.h"

//====================================================================
//�}�N����`
//====================================================================
#define PLAYERTANK_SIZE			(D3DXVECTOR3(90.0f,65.0f,0.0f)) // �v���C���[�̔���̃T�C�Y
#define PLAYERTANK_JUMP			(60.0f)				// ��Ԃ���Ԉړ���
#define SHOT_BULLET_POS_X		(0.0f)			// �e�̔��ˈʒuX
#define SHOT_BULLET_POS_Y		(25.0f)				// �e�̔��ˈʒuY
#define SHOT_BULLET_POS_Z		(0.0f)			// �e�̔��ˈʒuZ

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
	m_pGun = CGun::Create(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKGUN)->GetMatrix());
	// �O���l�[�h���ʒu�̐���
	m_pGrenadeFire = CGrenadeFire::Create(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKHEAD)->GetMatrix());
	// �e�̒e�̎��
	m_pGun->GetTag() = TAG_PLAYER;
	// �e�̒e�̎��
	m_pGun->SetGunType(CGun::GUNTYPE_TANKGUN);
	// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(SHOT_BULLET_POS_X, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));
	// �n�ʂɂ��Ă��邩�̃t���O
	m_bLand = true;
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
	// �e�̃|�C���^
	if (m_pGun)
	{
		delete m_pGun;
		m_pGun = nullptr;
	}

	// �O���l�[�h���ˈʒu�̃|�C���^
	if (m_pGrenadeFire)
	{
		m_pGrenadeFire->Rerease();
		m_pGrenadeFire = nullptr;
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
void CPlayertank::Update(void)
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
			VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_TANK_TANK_FRONTWHEEL), MODEL_ROT_TYPE_MOVING);
			VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_TANK_TANK_BACKWHEEL), MODEL_ROT_TYPE_MOVING);
			VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKGUN), MODEL_ROT_TYPE_OPERATION);

			// ��蕨�̔���
			GetCollision()->ForVehicleCollision();
			// ��Ԃ̔���
			GetCollision()->ForTankCollision();
		}
	}

	// ������܂Ƃ߂čs��
	Collision();

	m_pGun->Update();


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
	m_pGun->Draw();

	CVehicle::Draw();
}

//====================================================================
// �f�o�b�O
//====================================================================
void CPlayertank::DebugInfo(void)
{
	CVehicle::DebugInfo();
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
		// �K���̃��f���̔��ˌ�����e�𐶐�
		m_pGun->Shot();
	}
	// �e����������ݒ�
	m_pGun->SetShotRot(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKGUN)->GetRot());

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
		SetVehicleDirection(DIRECTION::UP);
	}
	// �������
	else if (key->GetKeyboardPress(DIK_S))
	{
		SetVehicleDirection(DIRECTION::DOWN);
	}

	// ���ɓ�������
	if (key->GetKeyboardPress(DIK_A))
	{
		if (m_bLand == true)
		{
			CVehicle::Move(0.5f, -0.5f);
		}
		else if(m_bLand == false)
		{
			CVehicle::Move(0.3f, -0.5f);
		}

		// �������
		if (key->GetKeyboardPress(DIK_W))
		{
			SetVehicleDirection(DIRECTION::UP);
		}

		// ��������
		else if (key->GetKeyboardPress(DIK_S))
		{
			SetVehicleDirection(DIRECTION::DOWN);
		}

		// ��������
		else
		{
			SetVehicleDirection(DIRECTION::LEFT);
		}
	}

	// �E�ɓ�������
	else if (key->GetKeyboardPress(DIK_D))
	{
		if (m_bLand == true)
		{
			CVehicle::Move(-0.5f, -0.5f);
		}
		else if (m_bLand == false)
		{
			CVehicle::Move(-0.3f, -0.5f);
		}
		// �������
		if (key->GetKeyboardPress(DIK_W))
		{
			SetVehicleDirection(DIRECTION::UP);
		}

		// ��������
		else if (key->GetKeyboardPress(DIK_S))
		{
			SetVehicleDirection(DIRECTION::DOWN);
		}

		// �E������
		else
		{
			SetVehicleDirection(DIRECTION::RIGHT);
		}
	}

	// �W�����v����
	if (key->GetKeyboardTrigger(DIK_UP))
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
	if (GetJump() == false)
	{
		GetMove().y += PLAYERTANK_JUMP;
	}

	// �W�����v�t���O��true�ɂ��W�����v�ł��Ȃ�����
	SetJump(true);
}

//====================================================================
// �����蔻��
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
		if (GetCollision()->RayBlockCollision(pMap, GetMtxWorld()))
		{
			// �W�����v���邱�Ƃ����F����
			SetJump(false);

			m_bLand = true;
			// �}�b�v���f���̎Ζʂ̊p�x�Ɏԑ̂��X����
			//
		}
		else
		{
			m_bLand = false;
			// �W�����v���邱�Ƃ����F���Ȃ�
			SetJump(true);

		}
	}
}
