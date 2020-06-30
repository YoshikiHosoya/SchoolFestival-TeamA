// =====================================================================================================================================================================
//
// グレネードの処理 [grenade.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "grenade.h"			// インクルードファイル
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
CGrenade::CGrenade(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CGrenade::~CGrenade()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CGrenade::Init()
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
void CGrenade::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CGrenade::Update(void)
{
	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CGrenade::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CGrenade::DeleteBullet()
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CGrenade::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// グレネードの生成
//
// =====================================================================================================================================================================
CGrenade * CGrenade::Create(D3DXVECTOR3 rot)
{
	// 変数
	CGrenade *pGrenade;

	// メモリの確保
	pGrenade = new CGrenade(OBJTYPE_BULLET);

	// グレネードのパラメーター取得
	BULLET_PARAM *pBulletParam = pGrenade->GetBulletParam(CGun::GUNTYPE_HANDGUN);

	// 初期化
	pGrenade->Init();

	// プレイヤーの向きに合わせる
	pGrenade->GetMove() = D3DXVECTOR3(-sinf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed, sinf(rot.x) * pBulletParam->fBulletSpeed, -cosf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed);

	// モデルタイプの設定
	pGrenade->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pGrenade->SetModelConut(MODEL_BULLET_GRENADE);

	// 位置の設定
	pGrenade->SetPosition(D3DXVECTOR3(m_mtx->_41, m_mtx->_42, m_mtx->_43));

	// 弾のパラメーターの設定
	pGrenade->SetBulletParam(CGun::GUNTYPE_GRENADE);

	return pGrenade;
}