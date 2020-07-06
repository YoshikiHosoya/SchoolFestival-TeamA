// =====================================================================================================================================================================
//
// プレイヤーUIの処理 [playerUI.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "main.h"			// インクルードファイル
#include "playerUI.h"
#include "debugproc.h"
#include "bullet.h"
#include "gun.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlayerUI::CPlayerUI()
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPlayerUI::~CPlayerUI()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CPlayerUI::Init(void)
{
	// 変数初期化
	m_nScore = 0;
	m_nBulletAmmo = 0;
	m_nGrenadeAmmo = 0;

	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			switch (nCnt)
			{
			// 残機		( 文字 )
			case PLAYER_UI::REMAIN_LETTER:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_LIFE));
				break;

			// 弾の残数 ( 文字 )
			case PLAYER_UI::BULLET_AMMO_LETTER:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_ARMS));
				break;

			// グレネードの残数 ( 文字 )
			case PLAYER_UI::GRENADE_AMMO_LETTER:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_BOMB));
				break;

			// 体力アイコン
			case PLAYER_UI::LIFE_ICON:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_LIFE));
				break;
			}
		}
	}
	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CPlayerUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 終了
			m_apScene2D[nCnt]->Uninit();
		}
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CPlayerUI::Update(void)
{
	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 更新
			m_apScene2D[nCnt]->Update();
		}
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CPlayerUI::Draw(void)
{
	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 描画
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// プレイヤーUIの生成
//
// =====================================================================================================================================================================
CPlayerUI * CPlayerUI::Create()
{
	//メモリ確保
	CPlayerUI *pPlayerUI = new CPlayerUI();

	// メモリの確保
	pPlayerUI = new CPlayerUI();

	// 初期化
	pPlayerUI->Init();

	// スコアの生成
	pPlayerUI->m_pScore = CMultiNumber::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f),0, 8, CScene::OBJTYPE_UI);
	// 弾の残数の生成
	pPlayerUI->m_pBulletAmmo = CMultiNumber::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), 0, 3, CScene::OBJTYPE_UI);
	// グレネードの残数の生成
	pPlayerUI->m_pGrenadeAmmo = CMultiNumber::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(5.0f, 5.0f, 0.0f), 0, 2, CScene::OBJTYPE_UI);

	return pPlayerUI;
}

// =====================================================================================================================================================================
//
// スコアの設定
//
// =====================================================================================================================================================================
void CPlayerUI::SetScore(int nScore)
{
	// スコア加算
	m_nScore += nScore;

	// スコアの設定
	m_pScore->SetMultiNumber(m_nScore);
}

// =====================================================================================================================================================================
//
// 弾の残数の設定
//
// =====================================================================================================================================================================
void CPlayerUI::SetBulletAmmo(int nBulletAmmo)
{
	// 弾の残数減算
	m_nBulletAmmo -= nBulletAmmo;

	// 弾の残数の設定
	m_pBulletAmmo->SetMultiNumber(m_nBulletAmmo);
}

// =====================================================================================================================================================================
//
// グレネードの残数の設定
//
// =====================================================================================================================================================================
void CPlayerUI::SetGrenadeAmmo(int nGrenadeAmmo)
{
	// グレネードの残数減算
	m_nGrenadeAmmo -= nGrenadeAmmo;

	// グレネードの残数の設定
	m_pGrenadeAmmo->SetMultiNumber(m_nGrenadeAmmo);
}