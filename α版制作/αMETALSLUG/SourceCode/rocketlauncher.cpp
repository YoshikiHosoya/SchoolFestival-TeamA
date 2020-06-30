// =====================================================================================================================================================================
//
// ロケットランチャーの処理 [rocketlauncher.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "rocketlauncher.h"			// インクルードファイル
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
CRocketlauncher::CRocketlauncher(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CRocketlauncher::~CRocketlauncher()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CRocketlauncher::Init()
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
void CRocketlauncher::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CRocketlauncher::Update(void)
{
	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CRocketlauncher::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CRocketlauncher::DeleteBullet()
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CRocketlauncher::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// ロケットランチャーの生成
//
// =====================================================================================================================================================================
CRocketlauncher * CRocketlauncher::Create(D3DXVECTOR3 rot)
{
	// 変数
	CRocketlauncher *pRocketlauncher;

	// メモリの確保
	pRocketlauncher = new CRocketlauncher(OBJTYPE_BULLET);

	// ロケットランチャーのパラメーター取得
	BULLET_PARAM *pBulletParam = pRocketlauncher->GetBulletParam(CGun::GUNTYPE_ROCKETLAUNCHER);

	// 初期化
	pRocketlauncher->Init();

	// プレイヤーの向きに合わせる
	pRocketlauncher->GetMove() = D3DXVECTOR3(-sinf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed, sinf(rot.x) * pBulletParam->fBulletSpeed, -cosf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed);

	// モデルタイプの設定
	pRocketlauncher->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pRocketlauncher->SetModelConut(MODEL_BULLET_ROCKETLAUNCHER);

	return pRocketlauncher;
}