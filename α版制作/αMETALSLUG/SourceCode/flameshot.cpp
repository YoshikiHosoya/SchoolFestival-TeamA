// =====================================================================================================================================================================
//
// フレイムショットの処理 [flameshot.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "flameshot.h"			// インクルードファイル
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
CFlameshot::CFlameshot(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CFlameshot::~CFlameshot()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CFlameshot::Init()
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
void CFlameshot::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CFlameshot::Update(void)
{
	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CFlameshot::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CFlameshot::DeleteBullet()
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CFlameshot::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// フレイムショットの生成
//
// =====================================================================================================================================================================
CFlameshot * CFlameshot::Create(D3DXVECTOR3 rot)
{
	// 変数
	CFlameshot *pFlameshot;

	// メモリの確保
	pFlameshot = new CFlameshot(OBJTYPE_BULLET);

	// フレイムショットのパラメーター取得
	BULLET_PARAM *pBulletParam = pFlameshot->GetBulletParam(CGun::GUNTYPE_FLAMESHOT);

	// 初期化
	pFlameshot->Init();

	// フレイムショットの弾のサイズ
	pFlameshot->SetSize(D3DXVECTOR3(pBulletParam->size.x, pBulletParam->size.y, 0.0f));

	// プレイヤーの向きに合わせる
	pFlameshot->GetMove() = D3DXVECTOR3(-sinf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed, sinf(rot.x) * pBulletParam->fBulletSpeed, -cosf(rot.y) * cosf(rot.x) * pBulletParam->fBulletSpeed);

	// テクスチャの割り当て
	pFlameshot->BindTexture(CTexture::GetTexture(CTexture::TEX_TYPE::TEX_BULLET_HANDGUN));

	return pFlameshot;
}