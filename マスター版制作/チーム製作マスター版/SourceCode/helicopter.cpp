// =====================================================================================================================================================================
//
// ヘリコプター処理 [helicopter.cpp]
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
//マクロ定義
//====================================================================
#define HELICOPTER_SIZE			(D3DXVECTOR3(90.0f,65.0f,0.0f)) // ヘリのの判定のサイズ
#define SHOT_BULLET_POS_X		(0.0f)			// 弾の発射位置X
#define SHOT_BULLET_POS_Y		(25.0f)			// 弾の発射位置Y
#define SHOT_BULLET_POS_Z		(0.0f)			// 弾の発射位置Z

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CHelicopter::CHelicopter(OBJ_TYPE type) :CVehicle(type)
{
	// オブジェクトの設定
	SetObjType(OBJTYPE_ENEMY_VEHICLE);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CHelicopter::~CHelicopter()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CHelicopter::Init(void)
{
	// 乗り物の初期設定
	CVehicle::Init();
	// オフセットの読み込み
	LoadOffset(CVehicle::VEHICLE_TYPE_HELICOPTER);
	// 乗り物のタイプの設定
	SetVehicleType(CVehicle::VEHICLE_TYPE_HELICOPTER);
	// 銃の生成
	m_pGun = CGun::Create();
	// 銃のマトリックス設定
	m_pGun->SetHandMtx(GetVehicleModelPartsList(CModel::MODEL_HELIGUN)->GetMatrix());
	// グレネード放つ位置の生成
	m_pGrenadeFire = CGrenadeFire::Create(GetVehicleModelPartsList(CModel::MODEL_HELIBODY)->GetMatrix(), CGrenadeFire::TANK_GRENADE);
	// 銃の弾の種類
	m_pGun->GetTag() = TAG::ENEMY;
	// 銃の弾の種類
	m_pGun->SetGunType(CGun::GUNTYPE_HELIGUN);
	// 発射位置のオフセットの設定
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(SHOT_BULLET_POS_X, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(HELICOPTER_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	// プレイヤーのポインタ
	m_pPlayer = nullptr;

	return S_OK;
}

//====================================================================
//
// 終了
//
//====================================================================
void CHelicopter::Uninit(void)
{
	// 銃のポインタ
	if (m_pGun)
	{
		delete m_pGun;
		m_pGun = nullptr;
	}

	// グレネード発射位置のポインタ
	if (m_pGrenadeFire)
	{
		m_pGrenadeFire->Rerease();
		m_pGrenadeFire = nullptr;
	}
	CVehicle::Uninit();
}
//====================================================================
//
// 更新
//
//====================================================================
void CHelicopter::Update(void)
{
	// ヘリコプターが弾を撃つ処理
	//Shot();

	// ヘリコプターの移動用
	//Operation();

	// パーツの回転処理
	VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_HELIPROPELLER), MODEL_ROT_TYPE_ALWAYS);
	VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_HELIGUN), MODEL_ROT_TYPE_OPERATION);

	// 判定をまとめて行う
	Collision();

	m_pGun->Update();

	// 乗り物クラスの更新
	CVehicle::Update();
}
//====================================================================
//
// 描画
//
//====================================================================
void CHelicopter::Draw(void)
{
	CVehicle::Draw();

	m_pGun->Draw();

}

//====================================================================
// デバッグ
//====================================================================
void CHelicopter::DebugInfo(void)
{
	CVehicle::DebugInfo();
}

//====================================================================
// 戦車モデルのクリエイト
//====================================================================
CHelicopter *CHelicopter::Create(void)
{
	// メモリの確保
	CHelicopter *pHelicopter = new CHelicopter(OBJTYPE_ENEMY_VEHICLE);
	// 初期化
	pHelicopter->Init();
	// ポインタを返す
	return pHelicopter;
}

//====================================================================
// 弾を打つ処理
//====================================================================
void CHelicopter::Shot()
{
	// ガンのモデルの発射口から弾を生成
	m_pGun->Shot();

	// 弾を撃つ方向を設定
	m_pGun->SetShotRot(GetVehicleModelPartsList(CModel::MODEL_HELIGUN)->GetRot());

	// グレネード
	m_pGrenadeFire->Fire(GetShotDirection());
}

//====================================================================
// 操作処理
//====================================================================
void CHelicopter::Operation()
{
}

//====================================================================
// 当たり判定
//====================================================================
void CHelicopter::Collision()
{
	// 当たり判定
	if (GetCollision() != nullptr)
	{
		// 座標の更新 posとposold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());
	}
}
