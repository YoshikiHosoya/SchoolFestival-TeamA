// =====================================================================================================================================================================
//
// 火炎放射器の処理 [flamethrower.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "flamethrower.h"			// インクルードファイル
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
CFlamethrower::CFlamethrower(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CFlamethrower::~CFlamethrower()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CFlamethrower::Init()
{
	// 初期化
	CBullet::Init();

	//CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION);

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CFlamethrower::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CFlamethrower::Update(void)
{
	// エフェクトの生成
	//パーティクル発生 軌跡みたいな
	CParticle::CreateFromText(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, CHossoLibrary::Random_PI()), CParticleParam::EFFECT_SMOKE, CBullet::GetTag());

	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CFlamethrower::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CFlamethrower::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CFlamethrower::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CFlamethrower::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 火炎放射の生成
//
// =====================================================================================================================================================================
CFlamethrower * CFlamethrower::Create(D3DXVECTOR3 rot)
{
	// 変数
	CFlamethrower *pBalkan;

	// メモリの確保
	pBalkan = new CFlamethrower(OBJTYPE_BULLET);

	// 火炎放射器のパラメーター取得
	BULLET_PARAM *pBulletParam = pBalkan->GetBulletParam(CGun::GUNTYPE_FLAMETHROWER);

	// 初期化
	pBalkan->Init();

	// 弾の移動量計算
	pBalkan->CalcBulletMove(rot, CGun::GUNTYPE_FLAMETHROWER);

	// モデルタイプの設定
	pBalkan->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pBalkan->SetModelConut(MODEL_BULLET_SPHERE);

	return pBalkan;
}