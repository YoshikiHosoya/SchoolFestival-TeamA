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
#define MENU_POSY			(150.0f)		// メニューの位置Y
#define MENU_SPACE			(200.0f)		// メニューのスペース
#define ARROW_POSX			(400.0f)		// 矢印の位置X

#define BG_SIZE				(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))					// 背景のサイズ
#define MENU_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, (MENU_POSY + MENU_SPACE * nCnt), 0.0f))		// メニューの位置
#define MENU_SIZE			(D3DXVECTOR3(180.0f, 100.0f, 0.0f))											// メニューのサイズ

#define TEXT_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, 120.0f, 0.0f))								// ポーズ(文字)の位置
#define TEXT_SIZE			(D3DXVECTOR3(400.0f, 125.0f, 0.0f))											// ポーズ(文字)のサイズ
#define ARROW_POS			(D3DXVECTOR3(ARROW_POSX, (MENU_POSY + MENU_SPACE), 0.0f))		// 矢印の位置
#define ARROW_SIZE			(D3DXVECTOR3(40.0f, 40.0f, 0.0f))											// 矢印のサイズ

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

	// 初期設定
	InitSetting();

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
// 初期設定
//
// =====================================================================================================================================================================
void CPauseUI::InitSetting()
{
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

			case PAUSEUITYPE::P_UI_EXIT:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(MENU_POS, MENU_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_EXIT));
				break;

			case PAUSEUITYPE::P_UI_RESET:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(MENU_POS, MENU_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_RESET));
				break;

			case PAUSEUITYPE::P_UI_TEXT:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(TEXT_POS, TEXT_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_TEXT));
				break;

			case PAUSEUITYPE::P_UI_ARROW:

				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(ARROW_POS, ARROW_SIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_ARROW));
				break;
			}
		}
	}
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
	case PAUSEUITYPE::P_UI_ARROW:
		// アイコンの移動座標
		switch (m_nNum)
		{
		// 再開
		case CPause::PAUSE_EXIT:
			//位置の設定
			m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(ARROW_POSX, (MENU_POSY + MENU_SPACE * m_nNum), 0.0f));
			break;

		// タイトルに戻る
		case CPause::PAUSE_RESET:
			//位置の設定
			m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(ARROW_POSX, (MENU_POSY + MENU_SPACE * m_nNum), 0.0f));
			break;
		}
		break;
	}
}