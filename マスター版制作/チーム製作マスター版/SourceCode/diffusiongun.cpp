// =====================================================================================================================================================================
//
// 追従射撃の処理 [Tracking.cpp]
// Author : HANZAWA NORITUKI
//
// =====================================================================================================================================================================
#include "diffusiongun.h"			// インクルードファイル
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
CDiffusion::CDiffusion(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CDiffusion::~CDiffusion()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CDiffusion::Init()
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
void CDiffusion::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CDiffusion::Update(void)
{
	// 更新
	CBullet::Update();

	//パーティクル発生 軌跡みたいな
	CParticle::CreateFromText(GetPosition(), GetRot(), CParticleParam::EFFECT_HEAVY_MACHINEGUN, CBullet::GetTag());

}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CDiffusion::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CDiffusion::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CDiffusion::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CDiffusion::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 弾が追従する銃の生成
//
// =====================================================================================================================================================================
CDiffusion * CDiffusion::Create(D3DXVECTOR3 rot)
{
	// 変数
	CDiffusion *pTracking;

	// メモリの確保
	pTracking = new CDiffusion(OBJTYPE_BULLET);

	// ハンドガンのパラメーター取得
	BULLET_PARAM *pBulletParam = pTracking->GetBulletParam(CGun::GUNTYPE_DIFFUSIONGUN);

	// 初期化
	pTracking->Init();

	// 撃つ方向に合わせる
	pTracking->CalcBulletMove(rot, CGun::GUNTYPE_DIFFUSIONGUN);

	//回転量設定
	pTracking->SetRot(rot);

	// モデルタイプの設定
	pTracking->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pTracking->SetModelID(MODEL_BULLET_SPHERE);

	return pTracking;
}