// =====================================================================================================================================================================
//
// ショットガンの処理 [shotgun.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "shotgun.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "texture.h"
#include "TexAnimation3D_Collision.h"

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
CShotgun::CShotgun(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CShotgun::~CShotgun()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CShotgun::Init()
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
void CShotgun::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CShotgun::Update(void)
{
	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CShotgun::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CShotgun::DeleteBullet()
{
	CBullet::DeleteBullet();

}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CShotgun::BulletReaction(D3DXVECTOR3 rot)
{
	CTexAnimation3D_Collision::Create(GetPosition(), D3DXVECTOR3(100.0f, 200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, rot.y),
		CTexture::SEPARATE_TEX_EFFECT_SHOTGUN, 2, OBJTYPE_EXPROSION, GetTag(), GetBulletParam(CGun::GUNTYPE_SHOTGUN)->fPower, 1, false);

}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CShotgun::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// ショットガンの生成
//
// =====================================================================================================================================================================
CShotgun * CShotgun::Create(D3DXVECTOR3 rot)
{
	// 変数
	CShotgun *pShotGun;

	// メモリの確保
	pShotGun = new CShotgun(OBJTYPE_BULLET);

	// ショットガンのパラメーター取得
	BULLET_PARAM *pBulletParam = pShotGun->GetBulletParam(CGun::GUNTYPE_SHOTGUN);

	// 初期化
	pShotGun->Init();

	// 撃つ方向に合わせる
	pShotGun->GetMove() = D3DXVECTOR3(-sinf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed, sinf(rot.x) * pBulletParam->fBulletSpeed, -cosf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed);

	// モデルタイプの設定
	pShotGun->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pShotGun->SetModelConut(MODEL_BULLET_SPHERE);

	return pShotGun;
}