// =====================================================================================================================================================================
//
//乗り物の処理 [vehicle.h]
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
// モデルのオフセット読み込みファイルの設定
//====================================================================
char *CVehicle::m_LoadOffsetFileName[VEHICLE_TYPE_MAX] =
{
	{ "data/Load/PlayerTank/PlayerTankOffset.txt" },
	{ "data/Load/BattlePlane/BattlePlaneOffset.txt" },
	{ "data/Load/Helicopter/HelicopterOffset.txt" },
};

//====================================================================
//マクロ定義
//====================================================================
#define VEHICLE_GRAVITY (0.3f)
#define VEHICLE_SPEED	(2.0f)
#define VESSEL_SPEED	(10.0f)

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CVehicle::CVehicle()
{
	// 乗り物の行動状態を初期化
	m_Behaviorstate = VEHICLE_BEHAVIOR_NORMAL;
	// 種類を初期化
	m_VehicleType = VEHICLE_TYPE_TANK;
	// 重力加算用カウント
	m_nGravityCnt = 0;

}
// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CVehicle::~CVehicle()
{
	//nullcheck
	//if (!m_vModelList.empty())
	//{
	//	//パーツ数分
	//	for (size_t nCnt = 0; nCnt < m_vModelList.size(); nCnt++)
	//	{
	//		//メモリ開放
	//		delete m_vModelList[nCnt];
	//		m_vModelList[nCnt] = nullptr;
	//	}
	//	//配列を空にする
	//	m_vModelList.clear();
	//}
}
//====================================================================
//デバッグ
//====================================================================
void CVehicle::DebugInfo(void)
{
	//CDebug_ModelViewer::OffsetViewer(m_vModelList);


	//CDebugProc::Print_Left("");
}

//====================================================================
// パーツの回転条件別処理
//====================================================================
void CVehicle::VehiclePartsRotCondition(CModel *pModel, PARTS_ROT_TYPE type,D3DXVECTOR3 move, D3DXVECTOR3 rot)
{
	switch (type)
	{
		// 動かさない
	case MODEL_ROT_TYPE_NONE:
		break;

		// 常に回転する
	case MODEL_ROT_TYPE_ALWAYS:
		// 条件ごと回転させる
		this->VehiclePartsRot(pModel, 0.1f);
		break;

		// 移動している時のみ
	case MODEL_ROT_TYPE_MOVING:
		// 車輪の回転処理
		WheelRot(pModel,move);
		break;

		// 操作している時のみ
	case MODEL_ROT_TYPE_OPERATION:
		// 銃の回転処理
		GunRot(pModel, rot);
		break;

	default:
		break;
	}
}

//====================================================================
// パーツの回転条件別処理
//====================================================================
void CVehicle::VehiclePartsRot(CModel *pModel, float fRot)
{
	//3.14の超過分の初期化（回転）
	CHossoLibrary::CalcRotation(fRot);
	// モデルの回転
	pModel->GetRot().x += fRot;
	// モデルの回転の更新設定
	pModel->SetRot(pModel->GetRot());
}

//====================================================================
// パーツの回転条件別処理 上限付き
//====================================================================
void CVehicle::VehiclePartsRotLimit(CModel * pModel, float fRot)
{
	//3.14の超過分の回転量の初期化
	CHossoLibrary::CalcRotation(pModel->GetRot().x);
	// --- 指定された角度になるまで回転する --- //

	// 目標回転量と現在の回転量の差分を求める
	float diffRot = fRot - pModel->GetRot().x;

	//3.14の超過分の初期化（回転）
	CHossoLibrary::CalcRotation(pModel->GetRot().x);

	//3.14の超過分の初期化（回転）
	CHossoLibrary::CalcRotation(diffRot);

	//求めた差分だけ回転する計算
	pModel->GetRot().x += diffRot * 0.1f;

	// モデルの回転の更新設定
	pModel->SetRot(pModel->GetRot());
}


//====================================================================
// 車輪の回転車輪
//====================================================================
void CVehicle::WheelRot(CModel *pModel , D3DXVECTOR3 move)
{
	// 左回転
	if (move.x <= -2)
	{
		// 条件ごと回転させる
		this->VehiclePartsRot(pModel, 0.1f);
	}
	// 右回転
	else if (move.x >= 2)
	{
		// 条件ごと回転させる
		this->VehiclePartsRot(pModel, -0.1f);
	}
	// 無回転
	else if (move.x <= 1.0f && move.x >= -1.0f)
	{
		// 条件ごと回転させる
		this->VehiclePartsRot(pModel, 0.0f);
	}
}

//====================================================================
// 銃の回転車輪
//====================================================================
void CVehicle::GunRot(CModel * pModel,D3DXVECTOR3 shotrot)
{
	// 戦車の総数分
	for (int nCntVehicle = 0; nCntVehicle < CManager::GetBaseMode()->GetMap()->GetMaxPlayerTank(); nCntVehicle++)
	{
		// 乗り物のポインタ取得
		CPlayertank *pPlayertank = CManager::GetBaseMode()->GetMap()->GetPlayertank(nCntVehicle);
		// 戦車が存在した時
		if (pPlayertank != nullptr)
		{
			if (pPlayertank->GetCharacterDirection() == DIRECTION::LEFT)
			{
				// 条件ごと回転させる
				this->VehiclePartsRotLimit(pModel, shotrot.z);
			}
			else if (pPlayertank->GetCharacterDirection() == DIRECTION::RIGHT)
			{
				// 条件ごと回転させる
				this->VehiclePartsRotLimit(pModel, shotrot.z);
			}
			else if (pPlayertank->GetCharacterDirection() == DIRECTION::UP)
			{
				// 条件ごと回転させる
				this->VehiclePartsRotLimit(pModel, shotrot.z);
			}
			else if (pPlayertank->GetCharacterDirection() == DIRECTION::DOWN)
			{
				// 条件ごと回転させる
				this->VehiclePartsRotLimit(pModel, shotrot.z);
			}
		}
	}

	//// 戦闘機の総数分
	//for (int nCntVehicle = 0; nCntVehicle < CManager::GetBaseMode()->GetMap()->GetMaxBattlePlane(); nCntVehicle++)
	//{
	//	// 乗り物のポインタ取得
	//	CBattlePlane *pBattlePlane = CManager::GetBaseMode()->GetMap()->GetBattlePlane(nCntVehicle);
	//	// 戦車が存在した時
	//	if (pBattlePlane != nullptr)
	//	{
	//		if (pBattlePlane->GetVehicleDirection() == DIRECTION::LEFT)
	//		{
	//			// 条件ごと回転させる
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.5f);
	//		}
	//		else if (pBattlePlane->GetVehicleDirection() == DIRECTION::RIGHT)
	//		{
	//			// 条件ごと回転させる
	//			this->VehiclePartsRotLimit(pModel, -D3DX_PI * 0.5f);
	//		}
	//		else if (pBattlePlane->GetVehicleDirection() == DIRECTION::UP)
	//		{
	//			// 条件ごと回転させる
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.0f);
	//		}
	//		else if (pBattlePlane->GetVehicleDirection() == DIRECTION::DOWN)
	//		{
	//			// 条件ごと回転させる
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 1.0f);
	//		}
	//	}
	//}

	//// ヘリコプターの総数分
	//for (int nCntVehicle = 0; nCntVehicle < CManager::GetBaseMode()->GetMap()->GetMaxHelicopter(); nCntVehicle++)
	//{
	//	// 乗り物のポインタ取得
	//	CHelicopter *pHelicopter = CManager::GetBaseMode()->GetMap()->GetHelicopter(nCntVehicle);
	//	// 戦車が存在した時
	//	if (pHelicopter != nullptr)
	//	{
	//		if (pHelicopter->GetVehicleDirection() == DIRECTION::LEFT)
	//		{
	//			// 条件ごと回転させる
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.5f);
	//		}
	//		else if (pHelicopter->GetVehicleDirection() == DIRECTION::RIGHT)
	//		{
	//			// 条件ごと回転させる
	//			this->VehiclePartsRotLimit(pModel, -D3DX_PI * 0.5f);
	//		}
	//		else if (pHelicopter->GetVehicleDirection() == DIRECTION::UP)
	//		{
	//			// 条件ごと回転させる
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 0.0f);
	//		}
	//		else if (pHelicopter->GetVehicleDirection() == DIRECTION::DOWN)
	//		{
	//			// 条件ごと回転させる
	//			this->VehiclePartsRotLimit(pModel, D3DX_PI * 1.0f);
	//		}
	//	}
	//}
}

