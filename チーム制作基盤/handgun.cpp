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

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TEXTURE_FILE_HUNDGUN		"data/TEXTURE/00.png"		// 読み込むテクスチャファイル名

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CHandgun::CHandgun() :CBullet()
{
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
// ハンドガンの生成
//
// =====================================================================================================================================================================
CHandgun * CHandgun::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// 変数
	CHandgun *pHandgun;

	// メモリの確保
	pHandgun = new CHandgun();

	// 初期化
	pHandgun->Init();

	// ハンドガンの位置の設定
	pHandgun->SetPosition(pos);

	// プレイヤーの向きに合わせる
	pHandgun->GetMove() = D3DXVECTOR3(-sinf(rot.y), 0.0f, -cosf(rot.y) * 2.0f);

	// テクスチャの割り当て
	//pHandgun->BindTexture(m_pTexture);

	return pHandgun;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CHandgun::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();

	//テクスチャ
	LPDIRECT3DTEXTURE9 pTex;

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE_HUNDGUN, &pTex);

	return S_OK;
}

// =====================================================================================================================================================================
//
// アンロード
//
// =====================================================================================================================================================================
void CHandgun::Unload(void)
{
	//// テクスチャの開放
	//if (m_pTexture)
	//{
	//	m_pTexture->Release();
	//	m_pTexture = NULL;
	//}
}