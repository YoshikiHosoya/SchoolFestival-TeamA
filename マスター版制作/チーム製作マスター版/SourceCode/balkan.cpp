// =====================================================================================================================================================================
//
// バルカンの処理 [balkangun.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "balkan.h"			// インクルードファイル
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
CBalkan::CBalkan(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CBalkan::~CBalkan()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CBalkan::Init()
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
void CBalkan::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CBalkan::Update(void)
{
	// 更新
	CBullet::Update();

	//パーティクル発生 軌跡みたいな
	CParticle::CreateFromText(GetPosition(), GetRot(), CParticleParam::EFFECT_BALKAN, CBullet::GetTag());

	//弾を回転させエフェクトも回転しているように見せる
	this->GetRot().z += 0.05f;
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CBalkan::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CBalkan::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CBalkan::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CBalkan::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// バルカンの生成
//
// =====================================================================================================================================================================
CBalkan * CBalkan::Create(D3DXVECTOR3 rot)
{
	// 変数
	CBalkan *pBalkan;

	// メモリの確保
	pBalkan = new CBalkan(OBJTYPE_BULLET);

	// バルカンのパラメーター取得
	BULLET_PARAM *pBulletParam = pBalkan->GetBulletParam(CGun::GUNTYPE_BALKAN);

	// 初期化
	pBalkan->Init();

	// 弾の移動量計算
	pBalkan->CalcBulletMove(rot, CGun::GUNTYPE_BALKAN);

	// 回転量設定
	pBalkan->GetRot() = rot;

	// モデルタイプの設定
	pBalkan->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pBalkan->SetModelID(MODEL_BULLET_SPHERE);

	return pBalkan;
}