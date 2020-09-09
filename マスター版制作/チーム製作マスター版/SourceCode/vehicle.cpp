// =====================================================================================================================================================================
//
//��蕨�̏��� [vehicle.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "vehicle.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "map.h"
#include "manager.h"
#include "debugproc.h"
#include "inputKeyboard.h"
#include "Xinput.h"
#include "hosso\/Debug_ModelViewer.h"
#include "playertank.h"
#include "battleplane.h"
#include "helicopter.h"
#include "Character.h"
#include "ModelSet.h"
//====================================================================
// ���f���̃I�t�Z�b�g�ǂݍ��݃t�@�C���̐ݒ�
//====================================================================
char *CVehicle::m_LoadOffsetFileName[VEHICLE_TYPE_MAX] =
{
	{ "data/Load/PlayerTank/PlayerTankOffset.txt" },
	{ "data/Load/BattlePlane/BattlePlaneOffset.txt" },
	{ "data/Load/Helicopter/HelicopterOffset.txt" },
};

//====================================================================
//�}�N����`
//====================================================================
#define VEHICLE_GRAVITY (0.3f)
#define VEHICLE_SPEED	(2.0f)
#define VESSEL_SPEED	(10.0f)

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CVehicle::CVehicle()
{
	// ��蕨�̍s����Ԃ�������
	m_Behaviorstate = VEHICLE_BEHAVIOR_NORMAL;
	// ��ނ�������
	m_VehicleType = VEHICLE_TYPE_TANK;
	// �d�͉��Z�p�J�E���g
	m_nGravityCnt = 0;

}
// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CVehicle::~CVehicle()
{
	//nullcheck
	//if (!m_vModelList.empty())
	//{
	//	//�p�[�c����
	//	for (size_t nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	//	{
	//		//�������J��
	//		delete m_vModelList[nCnt];
	//		m_vModelList[nCnt] = nullptr;
	//	}
	//	//�z�����ɂ���
	//	m_vModelList.clear();
	//}
}
//====================================================================
//�f�o�b�O
//====================================================================
void CVehicle::DebugInfo(void)
{
	//CDebug_ModelViewer::OffsetViewer(m_vModelList);


	//CDebugProc::Print_Left("");
}

//====================================================================
// �p�[�c�̉�]�����ʏ���
//====================================================================
void CVehicle::VehiclePartsRotCondition(CModel *pModel, PARTS_ROT_TYPE type,D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	switch (type)
	{
		// �������Ȃ�
	case MODEL_ROT_TYPE_NONE:
		break;

		// ��ɉ�]����
	case MODEL_ROT_TYPE_ALWAYS:
		// �������Ɖ�]������
		this->VehiclePartsRot(pModel, 0.1f);
		break;

		// �ړ����Ă��鎞�̂�
	case MODEL_ROT_TYPE_MOVING:
		// �ԗւ̉�]����
		WheelRot(pModel,move);
		break;

		// ���삵�Ă��鎞�̂�
	case MODEL_ROT_TYPE_OPERATION:
		// �e�̉�]����
		GunRot(pModel, rot);
		break;

	default:
		break;
	}
}

//====================================================================
// �p�[�c�̉�]�����ʏ���
//====================================================================
void CVehicle::VehiclePartsRot(CModel *pModel, float fRot)
{
	//3.14�̒��ߕ��̏������i��]�j
	CHossoLibrary::CalcRotation(fRot);
	// ���f���̉�]
	pModel->GetRot().x += fRot;
	// ���f���̉�]�̍X�V�ݒ�
	pModel->SetRot(pModel->GetRot());
}

//====================================================================
// �p�[�c�̉�]�����ʏ��� ����t��
//====================================================================
void CVehicle::VehiclePartsRotLimit(CModel * pModel, float fRot)
{
	//3.14�̒��ߕ��̉�]�ʂ̏�����
	CHossoLibrary::CalcRotation(pModel->GetRot().x);
	// --- �w�肳�ꂽ�p�x�ɂȂ�܂ŉ�]���� --- //

	// �ڕW��]�ʂƌ��݂̉�]�ʂ̍��������߂�
	float diffRot = fRot - pModel->GetRot().x;

	//3.14�̒��ߕ��̏������i��]�j
	CHossoLibrary::CalcRotation(pModel->GetRot().x);

	//3.14�̒��ߕ��̏������i��]�j
	CHossoLibrary::CalcRotation(diffRot);

	//���߂�����������]����v�Z
	pModel->GetRot().x += diffRot * 0.1f;

	// ���f���̉�]�̍X�V�ݒ�
	pModel->SetRot(pModel->GetRot());
}


//====================================================================
// �ԗւ̉�]�ԗ�
//====================================================================
void CVehicle::WheelRot(CModel *pModel , D3DXVECTOR3 move)
{
	// ����]
	if (move.x <= -2)
	{
		// �������Ɖ�]������
		this->VehiclePartsRot(pModel, 0.1f);
	}
	// �E��]
	else if (move.x >= 2)
	{
		// �������Ɖ�]������
		this->VehiclePartsRot(pModel, -0.1f);
	}
	// ����]
	else if (move.x <= 1.0f && move.x >= -1.0f)
	{
		// �������Ɖ�]������
		this->VehiclePartsRot(pModel, 0.0f);
	}
}

//====================================================================
// �e�̉�]�ԗ�
//====================================================================
void CVehicle::GunRot(CModel * pModel,D3DXVECTOR3 shotrot)
{
	// ��Ԃ̑�����
	for (int nCntVehicle = 0; nCntVehicle < CManager::GetBaseMode()->GetMap()->GetMaxPlayerTank(); nCntVehicle++)
	{
		// ��蕨�̃|�C���^�擾
		CPlayertank *pPlayertank = CManager::GetBaseMode()->GetMap()->GetPlayertank(nCntVehicle);
		// ��Ԃ����݂�����
		if (pPlayertank != nullptr)
		{
			if (pPlayertank->GetCharacterDirection() == DIRECTION::LEFT)
			{
				// �������Ɖ�]������
				this->VehiclePartsRotLimit(pModel, shotrot.z);
			}
			else if (pPlayertank->GetCharacterDirection() == DIRECTION::RIGHT)
			{
				// �������Ɖ�]������
				this->VehiclePartsRotLimit(pModel, shotrot.z);
			}
			else if (pPlayertank->GetCharacterDirection() == DIRECTION::UP)
			{
				// �������Ɖ�]������
				this->VehiclePartsRotLimit(pModel, shotrot.z);
			}
			else if (pPlayertank->GetCharacterDirection() == DIRECTION::DOWN)
			{
				// �������Ɖ�]������
				this->VehiclePartsRotLimit(pModel, shotrot.z);
			}
		}
	}

	//// �퓬�@�̑�����
	//for (int nCntVehicle = 0; nCntVehicle < CManager::GetBaseMode()->GetMap()->GetMaxBattlePlane(); nCntVehicle++)
	//{
	//	// ��蕨�̃|�C���^�擾
	//	CBattlePlane *pBattlePlane = CManager::GetBaseMode()->GetMap()->GetBattlePlane(nCntVehicle);
	//	// ��Ԃ����݂�����
	//	if (pBattlePlane != nullptr)
	//	{
	//		if (pBattlePlane->GetVehicleDirection() == DIRECTION::LEFT)
	//		{
	//			// �������Ɖ�]������
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.5f);
	//		}
	//		else if (pBattlePlane->GetVehicleDirection() == DIRECTION::RIGHT)
	//		{
	//			// �������Ɖ�]������
	//			this->VehiclePartsRotLimit(pModel, -D3DX_PI * 0.5f);
	//		}
	//		else if (pBattlePlane->GetVehicleDirection() == DIRECTION::UP)
	//		{
	//			// �������Ɖ�]������
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.0f);
	//		}
	//		else if (pBattlePlane->GetVehicleDirection() == DIRECTION::DOWN)
	//		{
	//			// �������Ɖ�]������
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 1.0f);
	//		}
	//	}
	//}

	//// �w���R�v�^�[�̑�����
	//for (int nCntVehicle = 0; nCntVehicle < CManager::GetBaseMode()->GetMap()->GetMaxHelicopter(); nCntVehicle++)
	//{
	//	// ��蕨�̃|�C���^�擾
	//	CHelicopter *pHelicopter = CManager::GetBaseMode()->GetMap()->GetHelicopter(nCntVehicle);
	//	// ��Ԃ����݂�����
	//	if (pHelicopter != nullptr)
	//	{
	//		if (pHelicopter->GetVehicleDirection() == DIRECTION::LEFT)
	//		{
	//			// �������Ɖ�]������
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.5f);
	//		}
	//		else if (pHelicopter->GetVehicleDirection() == DIRECTION::RIGHT)
	//		{
	//			// �������Ɖ�]������
	//			this->VehiclePartsRotLimit(pModel, -D3DX_PI * 0.5f);
	//		}
	//		else if (pHelicopter->GetVehicleDirection() == DIRECTION::UP)
	//		{
	//			// �������Ɖ�]������
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.0f);
	//		}
	//		else if (pHelicopter->GetVehicleDirection() == DIRECTION::DOWN)
	//		{
	//			// �������Ɖ�]������
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 1.0f);
	//		}
	//	}
	//}
}

