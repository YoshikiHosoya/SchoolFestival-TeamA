// =====================================================================================================================================================================
//
// 焼夷弾の処理 [Incendiary.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "incendiary.h"			// インクルードファイル
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
#define INCENDIARY_GRAVITY				(0.1f)								// 焼夷弾の重力

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CIncendiary::CIncendiary(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CIncendiary::~CIncendiary()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CIncendiary::Init()
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
void CIncendiary::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CIncendiary::Update(void)
{
	// 重力
	GetMove().y -= INCENDIARY_GRAVITY;

	// 更新
	CBullet::Update();

	//パーティクル発生 軌跡みたいな
	CParticle::CreateFromText(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, CHossoLibrary::Random_PI()), CParticleParam::EFFECT_SMOKE, CBullet::GetTag());
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CIncendiary::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CIncendiary::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CIncendiary::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CIncendiary::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 焼夷弾の生成
//
// =====================================================================================================================================================================
CIncendiary * CIncendiary::Create(D3DXVECTOR3 rot)
{
	// 変数
	CIncendiary *pIncendiary;

	// メモリの確保
	pIncendiary = new CIncendiary(OBJTYPE_BULLET);

	// 焼夷弾のパラメーター取得
	BULLET_PARAM *pBulletParam = pIncendiary->GetBulletParam(CGun::GUNTYPE_INCENDIARY);

	// 初期化
	pIncendiary->Init();

	// 弾の移動量計算
	pIncendiary->CalcBulletMove(rot, CGun::GUNTYPE_INCENDIARY);

	// モデルタイプの設定
	pIncendiary->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pIncendiary->SetModelConut(MODEL_BULLET_SPHERE);

	return pIncendiary;
}