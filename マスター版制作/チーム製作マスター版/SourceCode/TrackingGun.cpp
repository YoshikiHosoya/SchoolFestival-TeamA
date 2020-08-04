// =====================================================================================================================================================================
//
// 追従射撃の処理 [Tracking.cpp]
// Author : HANZAWA NORITUKI
//
// =====================================================================================================================================================================
#include "TrackingGun.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "particle.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CTracking::CTracking(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CTracking::~CTracking()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CTracking::Init()
{
	// 初期化
	CBullet::Init();

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CTracking::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CTracking::Update(void)
{
	// 更新
	CBullet::Update();

	float fAngle = atan2f(GetMove().x, GetMove().y);

	//パーティクル発生 軌跡みたいな
	CParticle::CreateFromText(GetPosition(), D3DXVECTOR3(0.0f,0.0f, -fAngle + 1.57f), CParticleParam::EFFECT_HEAVY_MACHINEGUN, CBullet::GetTag());

}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CTracking::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CTracking::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CTracking::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CTracking::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 弾が追従する銃の生成
//
// =====================================================================================================================================================================
CTracking * CTracking::Create(D3DXVECTOR3 rot)
{
	// 変数
	CTracking *pTracking;

	// メモリの確保
	pTracking = new CTracking(OBJTYPE_BULLET);

	// ハンドガンのパラメーター取得
	BULLET_PARAM *pBulletParam = pTracking->GetBulletParam(CGun::GUNTYPE_TRACKINGGUN);

	// 初期化
	pTracking->Init();

	// 撃つ方向に合わせる
	pTracking->GetMove() = rot * pBulletParam->fBulletSpeed;

	// モデルタイプの設定
	pTracking->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pTracking->SetModelConut(MODEL_BULLET_SPHERE);

	return pTracking;
}