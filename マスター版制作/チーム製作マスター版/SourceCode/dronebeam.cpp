// =====================================================================================================================================================================
//
// ドローンビーム処理 [dronebeam.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "dronebeam.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "texture.h"
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
CDroneBeam::CDroneBeam(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CDroneBeam::~CDroneBeam()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CDroneBeam::Init()
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
void CDroneBeam::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CDroneBeam::Update(void)
{
	// 更新
	CBullet::Update();

	//パーティクル発生 軌跡みたいな
	CParticle::CreateFromText(GetPosition(), GetRot(), CParticleParam::EFFECT_HEAVY_MACHINEGUN, CBullet::GetTag(), -1, D3DXCOLOR(1.0f, 0.2f, 0.2f, 1.0f));
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CDroneBeam::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CDroneBeam::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CDroneBeam::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CDroneBeam::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// バルカンの生成
//
// =====================================================================================================================================================================
CDroneBeam * CDroneBeam::Create(D3DXVECTOR3 rot)
{
	// 変数
	CDroneBeam *pDroneBeam;

	// メモリの確保
	pDroneBeam = new CDroneBeam(OBJTYPE_BULLET);

	// バルカンのパラメーター取得
	BULLET_PARAM *pBulletParam = pDroneBeam->GetBulletParam(CGun::GUNTYPE_DRONEBEAM);

	// 初期化
	pDroneBeam->Init();

	// 弾の移動量計算
	pDroneBeam->CalcBulletMove(rot, CGun::GUNTYPE_DRONEBEAM);

	// 回転量設定
	pDroneBeam->GetRot() = rot;

	// モデルタイプの設定
	pDroneBeam->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pDroneBeam->SetModelID(MODEL_BULLET_SPHERE);

	return pDroneBeam;
}