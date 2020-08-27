// =====================================================================================================================================================================
//
// ハンドガンの処理 [handgun.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "handgun.h"			// インクルードファイル
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
CHandgun::CHandgun(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CHandgun::~CHandgun()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CHandgun::Init()
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
void CHandgun::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CHandgun::Update(void)
{
	// 更新
	CBullet::Update();

	//パーティクル発生 軌跡みたいな
	if (GetTag() == TAG::TAG_PLAYER)
	{
		CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_HANDGUN);
	}
	else if (GetTag() == TAG::TAG_ENEMY)
	{
		CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_HANDGUN, GetTag(), -1, RedColor);
	}

}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CHandgun::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CHandgun::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CHandgun::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CHandgun::DebugInfo()
{
}



// =====================================================================================================================================================================
//
// ハンドガンの生成
//
// =====================================================================================================================================================================
CHandgun * CHandgun::Create(D3DXVECTOR3 rot, TAG tag)
{
	// 変数
	CHandgun *pHandgun;

	// メモリの確保
	pHandgun = new CHandgun(OBJTYPE_BULLET);

	// 初期化
	pHandgun->Init();

	// 弾の移動量計算
	if (tag == TAG::TAG_PLAYER)
	{
		pHandgun->CalcBulletMove(rot, CGun::GUNTYPE_HANDGUN);
	}
	else if(tag == TAG::TAG_ENEMY)
	{
		pHandgun->CalcBulletMove(rot, CGun::GUNTYPE_HANDGUN_ENEMY);
	}
	// モデルタイプの設定
	pHandgun->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pHandgun->SetModelConut(MODEL_BULLET_SPHERE);

	return pHandgun;
}
