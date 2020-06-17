// =====================================================================================================================================================================
//
// バレットの処理 [bullet.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "bullet.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "gun.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define BULLET_LIFE			(100)			// 弾の体力

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CBullet::CBullet(OBJ_TYPE type) :CScene3D(type)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CBullet::~CBullet()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CBullet::Init()
{
	// 変数初期化
	m_move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動値
	m_nLife			= BULLET_LIFE;							// 体力

	// 初期化
	CScene3D::Init();

	// ビルボードの設定
	CScene3D::SetBillboard(true);

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CBullet::Uninit(void)
{
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CBullet::Update(void)
{
	// プレイヤーの情報取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	// 位置の取得
	D3DXVECTOR3 pos		= CScene3D::GetPosition();
	D3DXVECTOR3 size	= CScene3D::GetSize();

	// 位置更新
	pos += m_move;

	// 体力減少
	m_nLife--;

	// 体力が0になったら
	if (m_nLife <= 0)
	{
		Rerease();
	}

	// 位置の設定
	CScene3D::SetPosition(pos);

	// 更新
	CScene3D::Update();

	// デバッグ表示
	CDebugProc::Print("\nbullet_pos %.1f, %.1f, %.1f\n", pos);
	CDebugProc::Print("bullet_move %.1f, %.1f, %.1f\n\n", m_move);
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CBullet::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();

	// ライティングモード無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	// 描画
	CScene3D::Draw();

	// ライティングモード有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
}