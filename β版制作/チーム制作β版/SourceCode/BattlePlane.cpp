// =====================================================================================================================================================================
//
// 戦闘機処理 [BattlePlane.h]
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
//マクロ定義
//====================================================================
#define PLANE_SIZE				(D3DXVECTOR3(90.0f,40.0f,0.0f)) // 戦闘機の判定のサイズ
#define SHOT_BULLET_POS_X		(0.0f)			// 弾の発射位置X
#define SHOT_BULLET_POS_Y		(25.0f)			// 弾の発射位置Y
#define SHOT_BULLET_POS_Z		(0.0f)			// 弾の発射位置Z

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CBattlePlane::CBattlePlane(OBJ_TYPE type) :CVehicle(type)
{
	// オブジェクトの設定
	SetObjType(OBJTYPE_PLAYER_VEHICLE);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CBattlePlane::~CBattlePlane()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CBattlePlane::Init(void)
{
	// 乗り物の初期設定
	CVehicle::Init();
	// オフセットの読み込み
	LoadOffset(CVehicle::VEHICLE_TYPE_PLANE);
	// 乗り物のタイプの設定
	SetVehicleType(CVehicle::VEHICLE_TYPE_PLANE);
	// 銃の生成
	m_pGun = CGun::Create(GetVehicleModelPartsList(CModel::MODEL_PLANE_GUN)->GetMatrix());
	// 銃の弾の種類
	m_pGun->GetTag() = TAG_PLAYER;
	// 銃の弾の種類
	m_pGun->SetGunType(CGun::GUNTYPE_PLANEGUN);
	// 発射位置のオフセットの設定
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(SHOT_BULLET_POS_X, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(PLANE_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}

//====================================================================
//
// 終了
//
//====================================================================
void CBattlePlane::Uninit(void)
{
	// 銃のポインタ
	if (m_pGun)
	{
		m_pGun->Rerease();
		m_pGun = nullptr;
	}

	// プレイヤーのポインタを取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	if (pPlayer != nullptr)
	{
		pPlayer->SetRideFlag(false);
	}

	CVehicle::Uninit();
}
//====================================================================
//
// 更新
//
//====================================================================
void CBattlePlane::Update(void)
{
	// キー情報の取得
	CKeyboard *key = CManager::GetInputKeyboard();

	// プレイヤーのポインタを取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	if (pPlayer != nullptr)
	{
		// 乗り物に乗っている時
		if (pPlayer->GetRideFlag())
		{
			// 戦車が弾を撃つ処理
			Shot(key);

			// 戦車を操作する処理
			Operation(key);

			// パーツの回転処理
			VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_PLANE_GUN), MODEL_ROT_TYPE_OPERATION);
		}
	}

	// 判定をまとめて行う
	Collision();

	// 乗り物クラスの更新
	CVehicle::Update();
}
//====================================================================
//
// 描画
//
//====================================================================
void CBattlePlane::Draw(void)
{
	CVehicle::Draw();
}

//====================================================================
// デバッグ
//====================================================================
void CBattlePlane::DebugInfo(void)
{
	CVehicle::DebugInfo();
}

//====================================================================
// 戦車モデルのクリエイト
//====================================================================
CBattlePlane *CBattlePlane::Create(void)
{
	// メモリの確保
	CBattlePlane *pPlayertank = new CBattlePlane(OBJTYPE_PLAYER_VEHICLE);
	// 初期化
	pPlayertank->Init();
	// ポインタを返す
	return pPlayertank;
}

//====================================================================
// 弾を打つ処理
//====================================================================
void CBattlePlane::Shot(CKeyboard *key)
{
	// マシンガンを撃つ
	if (key->GetKeyboardTrigger(DIK_P))
	{
		// ガンのモデルの発射口から弾を生成
		m_pGun->Shot();
	}
	// 弾を撃つ方向を設定
	m_pGun->SetShotRot(GetVehicleModelPartsList(CModel::MODEL_PLANE_GUN)->GetRot());
}

//====================================================================
// 操作処理
//====================================================================
void CBattlePlane::Operation(CKeyboard * key)
{
	// 上を向く
	if (key->GetKeyboardPress(DIK_W))
	{
		CVehicle::MovePlane(D3DXVECTOR3(0.0f, 1.0f, 0.0f), -0.5f);
		SetVehicleDirection(VEHICLE_UP);
	}
	// 上を向く
	else if (key->GetKeyboardPress(DIK_S))
	{
		CVehicle::MovePlane(D3DXVECTOR3(0.0f, -1.0f, 0.0f), -0.5f);
		SetVehicleDirection(VEHICLE_DOWN);
	}

	// 左に動かせる
	if (key->GetKeyboardPress(DIK_A))
	{
		// 上を向く
		if (key->GetKeyboardPress(DIK_W))
		{
			CVehicle::MovePlane(D3DXVECTOR3(-1.0f, 1.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_UP);
		}

		// 下を向く
		else if (key->GetKeyboardPress(DIK_S))
		{
			CVehicle::MovePlane(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_DOWN);
		}

		// 左を向く
		else
		{
			CVehicle::MovePlane(D3DXVECTOR3(-1.0f, 0.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_LEFT);
		}
	}

	// 右に動かせる
	else if (key->GetKeyboardPress(DIK_D))
	{
		// 上を向く
		if (key->GetKeyboardPress(DIK_W))
		{
			CVehicle::MovePlane(D3DXVECTOR3(1.0f, 1.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_UP);
		}

		// 下を向く
		else if (key->GetKeyboardPress(DIK_S))
		{
			CVehicle::MovePlane(D3DXVECTOR3(1.0f, -1.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_DOWN);
		}

		// 右を向く
		else
		{
			CVehicle::MovePlane(D3DXVECTOR3(1.0f, 0.0f, 0.0f), -0.5f);
			SetVehicleDirection(VEHICLE_RIGHT);
		}
	}
}

//====================================================================
// 当たり判定
//====================================================================
void CBattlePlane::Collision()
{
	// 当たり判定
	if (GetCollision() != nullptr)
	{
		// 座標の更新 posとposold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());
	}

	// マップのポインタ取得
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// マップモデルが存在した時
	if (pMap != nullptr)
	{
		// レイの判定
		if (GetCollision()->RayBlockCollision(pMap, GetMtxWorld()))
		{
		}
	}
}
