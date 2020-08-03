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
#include "multinumber.h"
#include "UIManager.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define PLAYER_MAX_LIFE		(5)

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlayerUI::CPlayerUI()
{
	// 初期化
	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = nullptr;
	}
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
	m_nScore		= 0;							// スコア
	m_nBulletAmmo	= 0;							// 弾の残弾数
	m_nGrenadeAmmo	= 0;							// グレネードの残弾数
	m_nLife			= 0;							// 体力
	m_nStock		= 0;							// 残機の数
	m_nTime			= 60;							// 残機の数

	// プレイヤーUIの生成
	PlayerUICreate();

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
			m_apScene2D[nCnt]->Rerease();
			m_apScene2D[nCnt] = nullptr;

			// デリートフラグを有効にする
			SetDeleteFlag(true);
		}
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Rerease();
		m_pScore = nullptr;
	}
	if (m_pBulletAmmo != nullptr)
	{
		m_pBulletAmmo->Rerease();
		m_pBulletAmmo = nullptr;
	}
	if (m_pGrenadeAmmo != nullptr)
	{
		m_pGrenadeAmmo->Rerease();
		m_pGrenadeAmmo = nullptr;
	}
	if (m_pLife != nullptr)
	{
		m_pLife->Rerease();
		m_pLife = nullptr;
	}
	if (m_pStock != nullptr)
	{
		m_pStock->Rerease();
		m_pStock = nullptr;
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
	//メモリの確保
	CPlayerUI *pPlayerUI = new CPlayerUI();

	// 初期化
	pPlayerUI->Init();

	//オブジェタイプ設定してSceneに所有権を渡す
	CUIManager::AddUIList(std::move(pPlayerUI));

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
void CPlayerUI::SetBulletAmmo(int nBulletAmmo, CGun::GUN_TYPE GunType)
{
	// ハンドガンと戦車の銃以外のとき
	if (CGun::GUN_TYPE::GUNTYPE_HANDGUN != GunType && CGun::GUN_TYPE::GUNTYPE_TANKGUN != GunType)
	{
		// 弾数無限のUI非表示
		m_apScene2D[INFINITY_AMMO]->SetDisp(false);
		// 弾の残数の表示
		m_pBulletAmmo->SetDisp(true);
		// 弾の残数減算
		m_nBulletAmmo = nBulletAmmo;
		// 弾の残数の設定
		m_pBulletAmmo->SetMultiNumber(m_nBulletAmmo);
	}
	// ハンドガンと戦車の銃のとき
	else
	{
		// 弾の残数の非表示
		m_pBulletAmmo->SetDisp(false);
		// 弾数無限のUI表示
		m_apScene2D[INFINITY_AMMO]->SetDisp(true);
	}
}

// =====================================================================================================================================================================
//
// グレネードの残数の設定
//
// =====================================================================================================================================================================
void CPlayerUI::SetGrenadeAmmo(int nGrenadeAmmo)
{
	// グレネードの残数減算
	m_nGrenadeAmmo = nGrenadeAmmo;

	// グレネードの残数の設定
	m_pGrenadeAmmo->SetMultiNumber(m_nGrenadeAmmo);
}

// =====================================================================================================================================================================
//
// 体力UIの設定
//
// =====================================================================================================================================================================
void CPlayerUI::SetLifeUI(int nLife)
{
	m_nLife = nLife;

	if (m_nLife <= PLAYER_MAX_LIFE)
	{
		// 体力の残数の非表示
		m_pLife->SetDisp(false);

		// テクスチャの分割数
		D3DXVECTOR2 UVsize = D3DXVECTOR2(CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE).x * m_nLife, CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE).y);
		// アニメーションの設定
		m_apScene2D[LIFE_ICON]->SetAnimation(CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_UI_LIFE), UVsize);
		// サイズの設定
		m_apScene2D[LIFE_ICON]->SetSize(D3DXVECTOR3(20.0f * m_nLife, 20.0f, 0.0f));
	}
	else if (m_nLife <= 0)
	{
		// 体力を0に
		m_nLife = 0;
		// 体力の残数の非表示
		m_pLife->SetDisp(false);
	}
	else
	{
		// テクスチャの分割数
		D3DXVECTOR2 UVsize = D3DXVECTOR2(CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE).x * 1, CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE).y);
		// アニメーションの設定
		m_apScene2D[LIFE_ICON]->SetAnimation(CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_UI_LIFE), UVsize);
		// サイズの設定
		m_apScene2D[LIFE_ICON]->SetSize(D3DXVECTOR3(20.0f * 1, 20.0f, 0.0f));
		// 体力の残数の表示
		m_pLife->SetDisp(true);
		// 体力の残数の設定
		m_pLife->SetMultiNumber(m_nLife);
	}
}

// =====================================================================================================================================================================
//
// 残機の数の設定
//
// =====================================================================================================================================================================
void CPlayerUI::SetStockUI(int nStock)
{
	// グレネードの残数減算
	m_nStock = nStock;

	// グレネードの残数の設定
	m_pGrenadeAmmo->SetMultiNumber(m_nStock);
}

// =====================================================================================================================================================================
//
// 残り時間の設定
//
// =====================================================================================================================================================================
void CPlayerUI::SetTimeUI(int nTime)
{
	// 残り時間の設定
	m_nTime = nTime;
}

// =====================================================================================================================================================================
//
// 残り時間の減少
//
// =====================================================================================================================================================================
void CPlayerUI::DecrementTime()
{
	m_nTime--;
	// スコアの設定
	m_pTime->SetMultiNumber(m_nTime);
}

// =====================================================================================================================================================================
//
// プレイヤーUIの生成
//
// =====================================================================================================================================================================
void CPlayerUI::PlayerUICreate()
{
	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			switch (nCnt)
			{
				// 枠
			case PLAYER_UI::FRAME:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(225.0f, 65.0f, 0.0f), D3DXVECTOR3(70.0f, 35.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_FRAME));
				break;

				// 残機		( 文字 )
			case PLAYER_UI::REMAIN_LETTER:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(90.0f, 80.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_REMAIN));
				break;

				// 弾の残数 ( 文字 )
			case PLAYER_UI::BULLET_AMMO_LETTER:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(200.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_ARMS));
				break;

				// グレネードの残数 ( 文字 )
			case PLAYER_UI::GRENADE_AMMO_LETTER:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(250.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_BOMB));
				break;

				// 体力アイコン
			case PLAYER_UI::LIFE_ICON:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(100.0f, 650.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_LIFE));
				// アニメーションの設定
				m_apScene2D[LIFE_ICON]->SetAnimation(CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_UI_LIFE), CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE));

				break;

				// 弾数無限
			case PLAYER_UI::INFINITY_AMMO:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(200.0f, 80.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_INFINITY));
				break;
			}
		}
	}

	// スコアの生成
	m_pScore = CMultiNumber::Create(D3DXVECTOR3(80.0f, 50.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), m_nScore, 8, CScene::OBJTYPE_UI);
	// 弾の残数の生成
	m_pBulletAmmo = CMultiNumber::Create(D3DXVECTOR3(200.0f, 80.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), m_nBulletAmmo, 3, CScene::OBJTYPE_UI);
	// グレネードの残数の生成
	m_pGrenadeAmmo = CMultiNumber::Create(D3DXVECTOR3(250.0f, 80.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), m_nGrenadeAmmo, 2, CScene::OBJTYPE_UI);
	// 体力の残数の生成
	m_pLife = CMultiNumber::Create(D3DXVECTOR3(150.0f, 650.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), m_nLife, 2, CScene::OBJTYPE_UI);
	// 体力の残数の生成
	m_pStock = CMultiNumber::Create(D3DXVECTOR3(130.0f, 80.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), m_nStock, 2, CScene::OBJTYPE_UI);
	// 残り時間の生成
	m_pTime = CMultiNumber::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 50.0f, 0.0f), D3DXVECTOR3(50.0f, 50.0f, 0.0f), m_nTime, 2, CScene::OBJTYPE_UI);
}