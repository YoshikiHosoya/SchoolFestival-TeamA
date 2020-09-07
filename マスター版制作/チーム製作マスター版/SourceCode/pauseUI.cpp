// =====================================================================================================================================================================
//
// ポーズUIの処理 [pauseUI.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "pauseUI.h"			// インクルードファイル
#include "renderer.h"
#include "pause.h"
#include "scene2D.h"
#include "UIManager.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
int					CPauseUI::m_nNum								= 0;

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MENU_POSY			(200.0f)		// メニューの位置Y					( メニュー )
#define MENU_SPACE			(100.0f)		// メニューのスペース				( メニュー )
#define ICON_POSX			(450.0f)		// アイコンの位置X					( アイコン )

#define BG_SIZE				(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))					// 背景のサイズ
#define MENU_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, (MENU_POSY + MENU_SPACE * nCnt), 0.0f))		// メニューの位置
#define MENU_SIZE			(D3DXVECTOR3(125.0f, 40.0f, 0.0f))											// メニューのサイズ

#define LOGO_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f))								// ロゴの位置
#define LOGO_SIZE			(D3DXVECTOR3(250.0f, 75.0f, 0.0f))											// ロゴのサイズ
#define ICON_POS			(D3DXVECTOR3(450.0f, (MENU_POSY + MENU_SPACE), 0.0f))						// アイコンの位置
#define ICON_SIZE			(D3DXVECTOR3(40.0f, 40.0f, 0.0f))											// アイコンのサイズ

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPauseUI::CPauseUI()
{
	// 初期化
	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = nullptr;
	}
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPauseUI::~CPauseUI()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CPauseUI::Init()
{
	// 変数の初期化
	m_nNum = 0;												// ナンバー

	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			switch (nCnt)
			{
			case PAUSEUITYPE::P_UI_BG:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(BG_SIZE, BG_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_BG));
				// 色の設定
				m_apScene2D[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
				break;

			case PAUSEUITYPE::P_UI_RESUME:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(MENU_POS, MENU_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_RESUME));
				break;

			case PAUSEUITYPE::P_UI_RESTART:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(MENU_POS, MENU_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_RESTART));
				break;

			case PAUSEUITYPE::P_UI_EXIT:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(MENU_POS, MENU_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_EXIT));
				break;

			case PAUSEUITYPE::P_UI_LOGO:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(LOGO_POS, LOGO_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_LOGO));
				break;

			case PAUSEUITYPE::P_UI_ICON:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(ICON_POS, ICON_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_ICON));
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
void CPauseUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
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
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CPauseUI::Update(void)
{
	m_nNum = CPause::GetNum();

	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
	{
		// UIの内容設定
		UIConfig(nCnt);

		// 更新
		m_apScene2D[nCnt]->Update();
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CPauseUI::Draw(void)
{	
	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// ポーズしているとき
			if (CScene::GetStopFlag())
			{
				m_apScene2D[nCnt]->Draw();
			}
		}
	}
}

// =====================================================================================================================================================================
//
// ポーズUIの生成
//
// =====================================================================================================================================================================
CPauseUI * CPauseUI::Create()
{
	// メモリの確保
	CPauseUI *pPauseUI = new CPauseUI();

	// 初期化
	pPauseUI->Init();

	//オブジェタイプ設定してSceneに所有権を渡す
	CUIManager::AddUIList(std::move(pPauseUI));

	return pPauseUI;
}

// =====================================================================================================================================================================
//
// UIの内容設定
//
// =====================================================================================================================================================================
void CPauseUI::UIConfig(int nCnt)
{
	switch (nCnt)
	{
	case PAUSEUITYPE::P_UI_ICON:
		// アイコンの移動座標
		switch (m_nNum)
		{
		// 再開
		case CPause::PAUSE_RESUME:
			//位置の設定
			m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(ICON_POSX, (MENU_POSY + MENU_SPACE * m_nNum), 0.0f));
			break;

		// リスタート
		case CPause::PAUSE_RESTART:
			//位置の設定
			m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(ICON_POSX, (MENU_POSY + MENU_SPACE * m_nNum), 0.0f));
			break;

		// タイトル
		case CPause::PAUSE_TITLE:
			//位置の設定
			m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(ICON_POSX, (MENU_POSY + MENU_SPACE * m_nNum), 0.0f));
			break;
		}
		break;
	}
}