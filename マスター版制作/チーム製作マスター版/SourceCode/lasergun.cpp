// =====================================================================================================================================================================
//
// レーザーガンの処理 [lasergun.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "lasergun.h"			// インクルードファイル
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
CLasergun::CLasergun(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CLasergun::~CLasergun()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CLasergun::Init()
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
void CLasergun::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CLasergun::Update(void)
{
	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CLasergun::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CLasergun::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CLasergun::BulletReaction(D3DXVECTOR3 rot)
{
	//パーティクル発生 レーザー
	CParticle::CreateFromText(GetPosition(), rot, CParticleParam::EFFECT_LAZER, CBullet::GetTag(),GetBulletParam(CGun::GUNTYPE_LASERGUN)->nPower);

	CBullet::Rerease();
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CLasergun::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// レーザーガンの生成
//
// =====================================================================================================================================================================
CLasergun * CLasergun::Create(D3DXVECTOR3 rot)
{
	// 変数
	CLasergun *pLasergun;

	// メモリの確保
	pLasergun = new CLasergun(OBJTYPE_BULLET);

	// レーザーガンのパラメーター取得
	BULLET_PARAM *pBulletParam = pLasergun->GetBulletParam(CGun::GUNTYPE_LASERGUN);

	// 初期化
	pLasergun->Init();

	// 弾の移動量計算
	pLasergun->CalcBulletMove(rot, CGun::GUNTYPE_LASERGUN);

	// モデルタイプの設定
	pLasergun->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pLasergun->SetModelConut(MODEL_BULLET_SPHERE);

	return pLasergun;
}