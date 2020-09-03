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
#include "playergetscoreui.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define PLAYER_MAX_LIFE						(5)															// 体力を表示する最大数

#define PLAYER_UI_FRAME_POS					(D3DXVECTOR3(305.0f + m_PLAYER_2_UI_FramePos, 65.0f, 0.0f))	// 枠の位置
#define PLAYER_UI_FRAME_SIZE				(D3DXVECTOR3(80.0f, 45.0f, 0.0f))						// 枠のサイズ
#define PLAYER_UI_STOCK_LETTER_POS			(D3DXVECTOR3(140.0f + m_PLAYER_2_UI_ScorePos, 90.0f, 0.0f))	// 残機( 文字 )の位置
#define PLAYER_UI_STOCK_LETTER_SIZE			(D3DXVECTOR3(30.0f, 25.0f, 0.0f))						// 残機( 文字 )のサイズ
#define PLAYER_UI_BULLET_AMMO_LETTER_POS	(D3DXVECTOR3(270.0f + m_PLAYER_2_UI_FramePos, 50.0f, 0.0f))	// 残弾数( 文字 )の位置
#define PLAYER_UI_BULLET_AMMO_LETTER_SIZE	(D3DXVECTOR3(30.0f, 25.0f, 0.0f))						// 残弾数( 文字 )のサイズ
#define PLAYER_UI_GRENADE_AMMO_LETTER_POS	(D3DXVECTOR3(340.0f + m_PLAYER_2_UI_FramePos, 50.0f, 0.0f))	// グレネードの残数( 文字 )の位置
#define PLAYER_UI_GRENADE_AMMO_LETTER_SIZE	(D3DXVECTOR3(30.0f, 25.0f, 0.0f))						// グレネードの残数( 文字 )のサイズ
#define PLAYER_UI_LIFE_ICON_POS				(D3DXVECTOR3(130.0f + m_PLAYER_2_UI_LifePos, 650.0f, 0.0f))	// 体力アイコンの位置
#define PLAYER_UI_LIFE_ICON_SIZE			(D3DXVECTOR3(80.0f, 80.0f, 0.0f))						// 体力アイコンのサイズ
#define PLAYER_UI_INFINITY_AMMO_POS			(D3DXVECTOR3(270.0f + m_PLAYER_2_UI_FramePos, 80.0f, 0.0f))	// 弾数無限の位置
#define PLAYER_UI_INFINITY_AMMO_SIZE		(D3DXVECTOR3(40.0f, 40.0f, 0.0f))						// 弾数無限のサイズ

#define PLAYER_UI_NUM_SCORE_POS				(D3DXVECTOR3(120.0f + m_PLAYER_2_UI_ScorePos, 50.0f, 0.0f))	// スコアの位置
#define PLAYER_UI_NUM_SCORE_SIZE			(D3DXVECTOR3(25.0f, 25.0f, 0.0f))						// スコアのサイズ
#define PLAYER_UI_NUM_BULLET_AMMO_POS		(D3DXVECTOR3(275.0f + m_PLAYER_2_UI_FramePos, 80.0f, 0.0f))	// 残弾数の位置
#define PLAYER_UI_NUM_BULLET_AMMO_SIZE		(D3DXVECTOR3(20.0f, 20.0f, 0.0f))						// 残弾数のサイズ
#define PLAYER_UI_NUM_GRENADE_AMMO_POS		(D3DXVECTOR3(340.0f + m_PLAYER_2_UI_FramePos, 80.0f, 0.0f))	// グレネードの残数の位置
#define PLAYER_UI_NUM_GRENADE_AMMO_SIZE		(D3DXVECTOR3(20.0f, 20.0f, 0.0f))						// グレネードの残数のサイズ
#define PLAYER_UI_NUM_LIFE_POS				(D3DXVECTOR3(180.0f + m_PLAYER_2_UI_LifePos, 650.0f, 0.0f))	// 体力の位置
#define PLAYER_UI_NUM_LIFE_SIZE				(D3DXVECTOR3(25.0f, 25.0f, 0.0f))						// 体力のサイズ
#define PLAYER_UI_NUM_STOCK_POS				(D3DXVECTOR3(200.0f + m_PLAYER_2_UI_ScorePos, 90.0f, 0.0f))	// 残機の位置
#define PLAYER_UI_NUM_STOCK_SIZE			(D3DXVECTOR3(20.0f, 20.0f, 0.0f))						// 残機のサイズ
#define PLAYER_UI_NUM_TIME_POS				(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 50.0f, 0.0f))		// 残り時間の位置
#define PLAYER_UI_NUM_TIME_SIZE				(D3DXVECTOR3(50.0f, 50.0f, 0.0f))						// 残り時間のサイズ

#define PLAYER_2_UI_FRAME_POS				(650.0f)						// プレイヤー2の枠の位置 ( プレイヤ1の位置に加算 )
#define PLAYER_2_UI_SCORE_POS				(1020.0f)						// プレイヤー2のスコアの位置 ( 〃 )
#define PLAYER_2_UI_LIFE_POS				(950.0f)						// プレイヤー2の体力の位置 ( 〃 )

#define DEFAULT_TIME						(60)								// デフォルトのタイマー
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

	m_pPGSUI = nullptr;

	// 変数初期化
	m_nScore = 0;							// スコア
	m_nBulletAmmo = 0;						// 弾の残弾数
	m_nGrenadeAmmo = 0;						// グレネードの残弾数
	m_nLife = 0;							// 体力
	m_nStock = 0;							// 残機の数
	m_nTime = DEFAULT_TIME;					// 残り時間
	m_PLAYER_2_UI_FramePos = 0;					// プレイヤー2の枠の位置
	m_PLAYER_2_UI_ScorePos = 0;					// プレイヤー2のスコアの位置
	m_PLAYER_2_UI_LifePos = 0;					// プレイヤー2の体力の位置
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
			delete m_apScene2D[nCnt];
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
CPlayerUI * CPlayerUI::Create(TAG Tag)
{
	//メモリの確保
	CPlayerUI *pPlayerUI = new CPlayerUI();

	// 初期化
	pPlayerUI->Init();

	// プレイヤーUIの生成
	pPlayerUI->PlayerUICreate(Tag);

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
// アイテムのスコアの設定
//
// =====================================================================================================================================================================
void CPlayerUI::SetItemScore(int nScore)
{
	// スコア加算
	m_nScore += nScore;

	// スコアの設定
	m_pScore->SetMultiNumber(m_nScore);

	// 表示スコアの生成
	m_pPGSUI = CPlayerGSUI::Create(nScore);
}

// =====================================================================================================================================================================
//
// 残弾数の設定
//
// =====================================================================================================================================================================
void CPlayerUI::SetBulletAmmo(int nBulletAmmo, CGun::GUN_TYPE GunType)
{
	// ハンドガンと戦車の銃以外のとき
	if (CGun::GUN_TYPE::GUNTYPE_HANDGUN != GunType && CGun::GUN_TYPE::GUNTYPE_TANKGUN != GunType)
	{
		// 弾数無限のUI非表示
		m_apScene2D[INFINITY_AMMO]->SetDisp(false);
		// 残弾数の表示
		m_pBulletAmmo->SetDisp(true);
		// 残弾数減算
		m_nBulletAmmo = nBulletAmmo;
		// 残弾数の設定
		m_pBulletAmmo->SetMultiNumber(m_nBulletAmmo);
	}
	// ハンドガンと戦車の銃のとき
	else
	{
		// 残弾数の非表示
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
	// 残機減算
	m_nStock = nStock;

	//0以下にならないように設定
	CHossoLibrary::RangeLimit_Equal(m_nStock, 0, 9);

	// 残機の設定
	m_pStock->SetMultiNumber(m_nStock);
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

	//表示の切替
	m_pTime->SetMultiNumber(m_nTime);

}

// =====================================================================================================================================================================
//
// 残り時間の減少
//
// =====================================================================================================================================================================
void CPlayerUI::DecrementTime()
{
	m_nTime--;

	//0以下にならないようにする
	CHossoLibrary::RangeLimit_Equal(m_nTime, 0, DEFAULT_TIME);

	if (m_nTime <= 10)
	{
		//赤
		m_pTime->SetCol(RedColor);
	}
	else
	{
		//白
		m_pTime->SetCol(WhiteColor);
	}


	// スコアの設定
	m_pTime->SetMultiNumber(m_nTime);
}
// =====================================================================================================================================================================
//
// 時間のリセット
//
// =====================================================================================================================================================================
void CPlayerUI::ResetTime()
{
	//白
	m_pTime->SetCol(WhiteColor);

	//時間リセット
	SetTimeUI(DEFAULT_TIME);
}
// =====================================================================================================================================================================
//
// プレイヤーUIの生成
//
// =====================================================================================================================================================================
void CPlayerUI::PlayerUICreate(TAG Tag)
{
	// プレイヤー2のUIの位置
	if (Tag == TAG::PLAYER_2)
	{
		m_PLAYER_2_UI_FramePos	= PLAYER_2_UI_FRAME_POS;
		m_PLAYER_2_UI_ScorePos	= PLAYER_2_UI_SCORE_POS;
		m_PLAYER_2_UI_LifePos	= PLAYER_2_UI_LIFE_POS;
	}

	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			switch (nCnt)
			{
				// 枠
			case PLAYER_UI::FRAME:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_FRAME_POS, PLAYER_UI_FRAME_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_FRAME));
				break;

				// 残機		( 文字 )
			case PLAYER_UI::STOCK_LETTER:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_STOCK_LETTER_POS, PLAYER_UI_STOCK_LETTER_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_REMAIN));
				break;

				// 残弾数 ( 文字 )
			case PLAYER_UI::BULLET_AMMO_LETTER:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_BULLET_AMMO_LETTER_POS, PLAYER_UI_BULLET_AMMO_LETTER_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_ARMS));
				break;

				// グレネードの残数 ( 文字 )
			case PLAYER_UI::GRENADE_AMMO_LETTER:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_GRENADE_AMMO_LETTER_POS, PLAYER_UI_GRENADE_AMMO_LETTER_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_BOMB));
				break;

				// 体力アイコン
			case PLAYER_UI::LIFE_ICON:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_LIFE_ICON_POS, PLAYER_UI_LIFE_ICON_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_LIFE));
				// アニメーションの設定
				m_apScene2D[nCnt]->SetAnimation(CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_UI_LIFE), CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE));
				break;

				// 弾数無限
			case PLAYER_UI::INFINITY_AMMO:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_INFINITY_AMMO_POS, PLAYER_UI_INFINITY_AMMO_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_INFINITY));
				break;
			}
		}
	}

	// スコアの生成
	m_pScore = CMultiNumber::Create(PLAYER_UI_NUM_SCORE_POS, PLAYER_UI_NUM_SCORE_SIZE, m_nScore, 8, CScene::OBJTYPE_UI);
	// 残弾数の生成
	m_pBulletAmmo = CMultiNumber::Create(PLAYER_UI_NUM_BULLET_AMMO_POS, PLAYER_UI_NUM_BULLET_AMMO_SIZE, m_nBulletAmmo, 3, CScene::OBJTYPE_UI);
	// グレネードの残数の生成
	m_pGrenadeAmmo = CMultiNumber::Create(PLAYER_UI_NUM_GRENADE_AMMO_POS, PLAYER_UI_NUM_GRENADE_AMMO_SIZE, m_nGrenadeAmmo, 2, CScene::OBJTYPE_UI);
	// 体力の残数の生成
	m_pLife = CMultiNumber::Create(PLAYER_UI_NUM_LIFE_POS, PLAYER_UI_NUM_LIFE_SIZE, m_nLife, 2, CScene::OBJTYPE_UI);
	// 残機の生成
	m_pStock = CMultiNumber::Create(PLAYER_UI_NUM_STOCK_POS, PLAYER_UI_NUM_STOCK_SIZE, m_nStock, 2, CScene::OBJTYPE_UI);
	// 残り時間の生成
	if (Tag == TAG::PLAYER_1)
	{
		m_pTime = CMultiNumber::Create(PLAYER_UI_NUM_TIME_POS, PLAYER_UI_NUM_TIME_SIZE, m_nTime, 2, CScene::OBJTYPE_UI);
	}
}
