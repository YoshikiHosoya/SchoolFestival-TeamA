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
#include "sound.h"
#include "ModelSet.h"
#include "Character.h"
//====================================================================
//�}�N����`
//====================================================================
#define PLAYERTANK_SIZE			(D3DXVECTOR3(90.0f,65.0f,0.0f)) // �v���C���[�̔���̃T�C�Y
#define PLAYERTANK_JUMP			(60.0f)				// ��Ԃ���Ԉړ���
#define SHOT_BULLET_POS_X		(0.0f)			// �e�̔��ˈʒuX
#define SHOT_BULLET_POS_Y		(40.0f)				// �e�̔��ˈʒuY
#define SHOT_BULLET_POS_Z		(0.0f)			// �e�̔��ˈʒuZ

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPlayertank::CPlayertank(OBJ_TYPE type) :CCharacter(type)
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
	CCharacter::Init();

	// �I�t�Z�b�g�̓ǂݍ���
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_TANK);
	// ��蕨�̃^�C�v�̐ݒ�
	//SetVehicleType(CVehicle::VEHICLE_TYPE_TANK);
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_TANK);
	// �e�̐���
	m_pGun = CGun::Create();
	// �O���l�[�h���ʒu�̐���
	//m_pGrenadeFire = CGrenadeFire::Create(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKBODY)->GetMatrix(), CGrenadeFire::TANK_GRENADE);
	m_pGrenadeFire = CGrenadeFire::Create(GetModelSet()->GetCharacterModelList()[0] ->GetMatrix(), CGrenadeFire::TANK_GRENADE);
	// �}�g���b�N�X�ݒ�
	//m_pGun->SetHandMtx(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKGUN)->GetMatrix());
	m_pGun->SetHandMtx(GetModelSet()->GetCharacterModelList()[3]->GetMatrix());
	// �e�̒e�̎��
	m_pGun->SetTag(TAG::PLAYER_1);		// ���~��)�v���C���[1�A2�ǂ��炩����� �ϐ�?
	// �e�̒e�̎��
	m_pGun->SetGunType(CGun::GUNTYPE_TANKGUN);
	// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(SHOT_BULLET_POS_X, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));
	// �n�ʂɂ��Ă��邩�̃t���O
	m_bLand = true;
	//�^�O�̏�����
	m_Tag = TAG::NONE;
	// �v���C���[�̃|�C���^
	//CVehicle::SetPlayerTank(nullptr);
	//������
	m_nCntEngineSE = 0;
	CCharacter::GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);
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

	//if (CVehicle::GetPlayer() != nullptr)
	//{
	//	CVehicle::GetPlayer()->SetRideFlag(false);
	//}

	CCharacter::Uninit();
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
	// ��蕨�N���X�̍X�V
	CCharacter::Update();

	if (CVehicle::GetTag() != TAG::NONE)
	{
		 //��蕨�ɏ���Ă��鎞
		//if (CVehicle::GetPlayer()->GetRideFlag())
		{
			// ��Ԃ��e��������
			Shot(key, m_Tag);

			// ��Ԃ𑀍삷�鏈��
			Operation(key, m_Tag);

			// ��Ԃ̑���
			PadInput(m_Tag);

			// �p�[�c�̉�]����
			VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[1], MODEL_ROT_TYPE_MOVING,CCharacter::GetMove(),CCharacter::GetShotDirection());
			VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[2], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection());
			VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[3], MODEL_ROT_TYPE_OPERATION, CCharacter::GetMove(), CCharacter::GetShotDirection());

			// ��蕨�̔���
			GetCollision()->ForVehicleCollision();
			// ��Ԃ̔���
			GetCollision()->ForTankCollision();
		}
		//else
		{
			//CVehicle::SetPlayerTank(nullptr);
		}
	}
	//��蕨��SE
	TankSE();

	// ������܂Ƃ߂čs��
	//Collision();

	m_pGun->Update();


}
//====================================================================
//
// �`��
//
//====================================================================
void CPlayertank::Draw(void)
{
	//�K���̃}�g���b�N�X�̌v�Z����
	m_pGun->NoDrawCalcMatrixOnly();
	GetModelSet();
	CCharacter::Draw();
}
//====================================================================
// �f�t�H���g�̃��[�V�����i�g�p�Ȃ��j
//====================================================================
bool CPlayertank::DefaultMotion(void)
{
	return false;
}

//====================================================================
// �f�o�b�O
//====================================================================
void CPlayertank::DebugInfo(void)
{
	CCharacter::DebugInfo();
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
void CPlayertank::Shot(CKeyboard *key, TAG Tag)
{
	CXInputPad *pXInput = CManager::GetPad(Tag);

	// �e����������ݒ�
	// ���f���̉�]�̌����ƒe�̔��˕����̌v�Z�̉�]�����킹��
	m_pGun->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[3]->GetRot().x)));

	// �}�V���K��������
	if (key->GetKeyboardTrigger(DIK_P) || pXInput->GetTrigger(CXInputPad::JOYPADKEY_X, 1))
	{
		// �K���̃��f���̔��ˌ�����e�𐶐�
		m_pGun->Shot();
	}
	// �O���l�[�h������
	if (key->GetKeyboardTrigger(DIK_O) || pXInput->GetTrigger(CXInputPad::JOYPADKEY_Y, 1))
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
// �p�b�h�̓���
//====================================================================
void CPlayertank::PadInput(TAG Tag)
{
	D3DXVECTOR3 MoveValue = ZeroVector3;

	if (CHossoLibrary::PadMoveInput(MoveValue, CCharacter::GetCharacterDirection(), false, Tag))
	{
		CCharacter::Move(MoveValue.x, -0.5f);
	}

}
//====================================================================
// ��Ԃ̌��ʉ�
//====================================================================
void CPlayertank::TankSE()
{
	//nullcheck
	//if (CVehicle::GetPlayer())
	//{
	//	if (CVehicle::GetPlayer()->GetRideFlag())
	//	{
	//		m_nCntEngineSE++;

	//		//������
	//		if (m_nCntEngineSE % 120 == 1)
	//		{
	//			//�G���W�����Đ�
	//			CManager::GetSound()->Play(CSound::LABEL_SE_TANK_ENGINE);
	//		}
	//		//���ړ����ĂăW�����v���ĂȂ���
	//		if (fabsf(GetMove().x) >= 1.0f && !GetJump() && m_nCntEngineSE % 10 == 0)
	//		{
	//			//���Đ�
	//			CManager::GetSound()->Play(CSound::LABEL_SE_TANK_CATERPILLAR);
	//		}
	//	}
	//	else
	//	{
	//		m_nCntEngineSE = 0;
	//	}
	//}
}

//====================================================================
// ���쏈��
//====================================================================
void CPlayertank::Operation(CKeyboard * key, TAG Tag)
{
	CXInputPad *pXInput = CManager::GetPad(Tag);

	// �������
	if (key->GetKeyboardPress(DIK_W))
	{
		SetCharacterDirection(DIRECTION::UP);
	}
	// �������
	else if (key->GetKeyboardPress(DIK_S))
	{
		SetCharacterDirection(DIRECTION::DOWN);
	}

	// ���ɓ�������
	if (key->GetKeyboardPress(DIK_A))
	{
		if (m_bLand == true)
		{
			CCharacter::Move(0.5f, -0.5f);
		}
		else if(m_bLand == false)
		{
			CCharacter::Move(0.5f, -0.5f);
		}

		// �������
		if (key->GetKeyboardPress(DIK_W))
		{
			SetCharacterDirection(DIRECTION::UP);
		}

		// ��������
		else if (key->GetKeyboardPress(DIK_S))
		{
			SetCharacterDirection(DIRECTION::DOWN);
		}

		// ��������
		else
		{
			SetCharacterDirection(DIRECTION::LEFT);
		}
	}

	// �E�ɓ�������
	else if (key->GetKeyboardPress(DIK_D))
	{
		if (m_bLand == true)
		{
			CCharacter::Move(-0.5f, -0.5f);
		}
		else if (m_bLand == false)
		{
			CCharacter::Move(-0.5f, -0.5f);
		}
		// �������
		if (key->GetKeyboardPress(DIK_W))
		{
			SetCharacterDirection(DIRECTION::UP);
		}

		// ��������
		else if (key->GetKeyboardPress(DIK_S))
		{
			SetCharacterDirection(DIRECTION::DOWN);
		}

		// �E������
		else
		{
			SetCharacterDirection(DIRECTION::RIGHT);
		}
	}

	// �W�����v����
	if (key->GetKeyboardTrigger(DIK_UP) || pXInput->GetTrigger(CXInputPad::JOYPADKEY_A, 1))
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
