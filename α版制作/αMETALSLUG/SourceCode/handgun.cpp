// =====================================================================================================================================================================
//
// ハンドガンの処理 [handgun.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "handgun.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "texture.h"

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
CHandgun * CHandgun::Create(D3DXVECTOR3 rot)
{
	// 変数
	CHandgun *pHandgun;

	// メモリの確保
	pHandgun = new CHandgun(OBJTYPE_BULLET);

	// ハンドガンのパラメーター取得
	BULLET_PARAM *pBulletParam = pHandgun->GetBulletParam(CGun::GUNTYPE_HANDGUN);

	// 初期化
	pHandgun->Init();

	// 撃つ方向に合わせる
	pHandgun->GetMove() = D3DXVECTOR3(-sinf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed, sinf(rot.x) * pBulletParam->fBulletSpeed, -cosf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed);

	// モデルタイプの設定
	pHandgun->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pHandgun->SetModelConut(MODEL_BULLET_SPHERE);

	return pHandgun;
}