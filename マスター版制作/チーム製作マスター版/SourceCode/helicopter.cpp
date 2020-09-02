// =====================================================================================================================================================================
//
// �w���R�v�^�[���� [helicopter.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "helicopter.h"
#include "player.h"
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
#include "grenadefire.h"

//====================================================================
//�}�N����`
//====================================================================
#define HELICOPTER_SIZE			(D3DXVECTOR3(90.0f,65.0f,0.0f)) // �w���̂̔���̃T�C�Y
#define SHOT_BULLET_POS_X		(0.0f)			// �e�̔��ˈʒuX
#define SHOT_BULLET_POS_Y		(25.0f)			// �e�̔��ˈʒuY
#define SHOT_BULLET_POS_Z		(0.0f)			// �e�̔��ˈʒuZ

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CHelicopter::CHelicopter(OBJ_TYPE type) :CVehicle(type)
{
	// �I�u�W�F�N�g�̐ݒ�
	SetObjType(OBJTYPE_ENEMY_VEHICLE);
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CHelicopter::~CHelicopter()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CHelicopter::Init(void)
{
	// ��蕨�̏����ݒ�
	CVehicle::Init();
	// �I�t�Z�b�g�̓ǂݍ���
	LoadOffset(CVehicle::VEHICLE_TYPE_HELICOPTER);
	// ��蕨�̃^�C�v�̐ݒ�
	SetVehicleType(CVehicle::VEHICLE_TYPE_HELICOPTER);
	// �e�̐���
	m_pGun = CGun::Create();
	// �e�̃}�g���b�N�X�ݒ�
	m_pGun->SetHandMtx(GetVehicleModelPartsList(CModel::MODEL_HELIGUN)->GetMatrix());
	// �O���l�[�h���ʒu�̐���
	m_pGrenadeFire = CGrenadeFire::Create(GetVehicleModelPartsList(CModel::MODEL_HELIBODY)->GetMatrix(), CGrenadeFire::TANK_GRENADE);
	// �e�̒e�̎��
	m_pGun->GetTag() = TAG::ENEMY;
	// �e�̒e�̎��
	m_pGun->SetGunType(CGun::GUNTYPE_HELIGUN);
	// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(SHOT_BULLET_POS_X, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));
	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(HELICOPTER_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	// �v���C���[�̃|�C���^
	m_pPlayer = nullptr;

	return S_OK;
}

//====================================================================
//
// �I��
//
//====================================================================
void CHelicopter::Uninit(void)
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
	CVehicle::Uninit();
}
//====================================================================
//
// �X�V
//
//====================================================================
void CHelicopter::Update(void)
{
	// �w���R�v�^�[���e��������
	//Shot();

	// �w���R�v�^�[�̈ړ��p
	//Operation();

	// �p�[�c�̉�]����
	VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_HELIPROPELLER), MODEL_ROT_TYPE_ALWAYS);
	VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_HELIGUN), MODEL_ROT_TYPE_OPERATION);

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
void CHelicopter::Draw(void)
{
	CVehicle::Draw();

	m_pGun->Draw();

}

//====================================================================
// �f�o�b�O
//====================================================================
void CHelicopter::DebugInfo(void)
{
	CVehicle::DebugInfo();
}

//====================================================================
// ��ԃ��f���̃N���G�C�g
//====================================================================
CHelicopter *CHelicopter::Create(void)
{
	// �������̊m��
	CHelicopter *pHelicopter = new CHelicopter(OBJTYPE_ENEMY_VEHICLE);
	// ������
	pHelicopter->Init();
	// �|�C���^��Ԃ�
	return pHelicopter;
}

//====================================================================
// �e��ł���
//====================================================================
void CHelicopter::Shot()
{
	// �K���̃��f���̔��ˌ�����e�𐶐�
	m_pGun->Shot();

	// �e����������ݒ�
	m_pGun->SetShotRot(GetVehicleModelPartsList(CModel::MODEL_HELIGUN)->GetRot());

	// �O���l�[�h
	m_pGrenadeFire->Fire(GetShotDirection());
}

//====================================================================
// ���쏈��
//====================================================================
void CHelicopter::Operation()
{
}

//====================================================================
// �����蔻��
//====================================================================
void CHelicopter::Collision()
{
	// �����蔻��
	if (GetCollision() != nullptr)
	{
		// ���W�̍X�V pos��posold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());
	}
}
