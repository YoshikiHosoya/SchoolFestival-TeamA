// =====================================================================================================================================================================
//
// マネージャーの処理 [manager.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "manager.h"			// インクルードファイル
#include "renderer.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "scene.h"
#include "keyboard.h"
#include "xinputGpad.h"
#include "player.h"
#include "meshfield.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "sound.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CRenderer		*CManager::m_pRenderer	= NULL;			// レンダラー
CKeyboard		*CManager::m_pKeyboard	= NULL;			// キーボード
CXinputGpad		*CManager::m_pXinputGpad = NULL;		// ゲームパッド
CManager::MODE	CManager::m_mode		= MODE::GAME;	// ゲームモード
CTitle			*CManager::m_pTitle		= NULL;			// タイトル
CGame			*CManager::m_pGame		= NULL;			// ゲーム
CResult			*CManager::m_pResult	= NULL;			// リザルト
CRanking		*CManager::m_pRanking	= NULL;			// ランキング
CSound			*CManager::m_pSound		= NULL;			// サウンド

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CManager::CManager()
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CManager::~CManager()
{

}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// メモリの確保
	m_pRenderer		= new CRenderer;
	m_pKeyboard		= new CKeyboard;
	m_pXinputGpad	= new CXinputGpad;
	m_pSound		= new CSound;

	// 初期化処理			 
	if (FAILED(m_pRenderer->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	// キーボードの初期化
	m_pKeyboard->Init(hInstance, hWnd);

	//// ゲームパッドの初期化
	//m_pXinputGpad->Init(hInstance, hWnd);

	// サウンドの初期化
	m_pSound->Init(hWnd);

	// セットモード
	SetMode(m_mode);

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CManager::Uninit(void)
{
	// キーボード
	if (m_pKeyboard != NULL)
	{
		// キーボードの終了
		m_pKeyboard->Uninit();

		// メモリの開放
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	// ゲームパッド
	//if (m_pInputGpad != NULL)
	//{
	//	// ゲームパッドの終了
	//	m_pXinputGpad->Uninit();

	//	// メモリの開放
	//	delete m_pInputGpad;
	//	m_pInputGpad = NULL;
	//}

	// サウンド
	if (m_pSound != NULL)
	{
		// サウンドの終了
		m_pSound->Uninit();

		// メモリの開放
		delete m_pSound;
		m_pSound = NULL;
	}

	// レンダラー
	if (m_pRenderer != NULL)
	{
		// 終了処理
		m_pRenderer->Uninit();

		// メモリの開放
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// タイトル
	if (m_pTitle != NULL)
	{
		// 終了処理
		m_pTitle->Uninit();

		// メモリの開放
		delete m_pTitle;
		m_pTitle = NULL;
	}

	// ゲーム
	if (m_pGame != NULL)
	{
		// 終了処理
		m_pGame->Uninit();

		// メモリの開放
		delete m_pGame;
		m_pGame = NULL;
	}

	// リザルト
	if (m_pResult != NULL)
	{
		// 終了処理
		m_pResult->Uninit();

		// メモリの開放
		delete m_pResult;
		m_pResult = NULL;
	}

	// ランキング
	if (m_pRanking != NULL)
	{
		// 終了処理
		m_pRanking->Uninit();

		// メモリの開放
		delete m_pRanking;
		m_pRanking = NULL;
	}

	CScene::ReleaseAll();

}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CManager::Update(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

#ifdef _DEBUG
	if (m_pKeyboard->GetKeyboardPress(DIK_F7))
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		// ワイヤーフレームの表示
	}
	if (m_pKeyboard->GetKeyboardPress(DIK_F8))
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);			// ワイヤーフレームの非表示
	}
#endif

	// レンダラー
	if (m_pRenderer != NULL)
	{
		// レンダラーの更新
		m_pRenderer->Update();
	}

	// キーボード
	if (m_pKeyboard != NULL)
	{
		// キーボードの更新
		m_pKeyboard->Update();
	}

	// ゲームパッド
	if (m_pXinputGpad != NULL)
	{
		// ゲームパッドの更新
		m_pXinputGpad->Update();
	}

	// モード別の更新
	switch (m_mode)
	{
	case TITLE:
		// タイトルの更新
		m_pTitle->Update();
		break;

	case GAME:
		// ゲームの更新
		m_pGame->Update();
		break;

	case RESULT:
		// リザルトの更新
		m_pResult->Update();
		break;

	case RANKING:
		// ランキングの更新
		m_pRanking->Update();
		break;
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CManager::Draw(void)
{	
	// レンダラー
	if (m_pRenderer != NULL)
	{
		// 描画処理
		m_pRenderer->Draw();

		// モード別の描画
		switch (m_mode)
		{
		case TITLE:
			// タイトルの描画
			m_pTitle->Draw();
			break;

		case GAME:
			// ゲームの描画
			m_pGame->Draw();
			break;

		case RESULT:
			// リザルトの描画
			m_pResult->Draw();
			break;

		case RANKING:
			// ランキングの描画
			m_pRanking->Draw();
			break;
		}
	}
}

// =====================================================================================================================================================================
//
// モードの設定
//
// =====================================================================================================================================================================
void CManager::SetMode(MODE mode)
{
	// 全て停止
	m_pSound->StopSound();

	// モード別の終了
	switch (m_mode)
	{
	case TITLE:
		// タイトルの終了
		m_pTitle->Uninit();

		// メモリの開放
		delete m_pTitle;
		m_pTitle = NULL;
		break;

	case GAME:
		// ゲームの終了
		m_pGame->Uninit();

		// メモリの開放
		delete m_pGame;
		m_pGame = NULL;
		break;

	case RESULT:
		// リザルトの終了
		m_pResult->Uninit();

		// メモリの開放
		delete m_pResult;
		m_pResult = NULL;
		break;

	case RANKING:
		// ランキングの終了
		m_pRanking->Uninit();

		// メモリの開放
		delete m_pRanking;
		m_pRanking = NULL;
		break;
	}

	m_mode = mode;

	// モード別の初期化
	switch (mode)
	{
	case TITLE:
		// タイトルの生成
		m_pTitle = CTitle::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
		break;

	case GAME:
		// ゲームの生成
		m_pGame = CGame::Create();
		//m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
		break;

	case RESULT:
		// リザルトの生成
		m_pResult = CResult::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_OVER);
		break;

	case RANKING:
		// ランキングの生成
		m_pRanking = CRanking::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RANK);
		break;
	}
}

// =====================================================================================================================================================================
//
// レンダラ-の取得
//
// =====================================================================================================================================================================
CRenderer * CManager::GetRenderer(void)
{
	if (m_pRenderer != NULL)
	{
		return m_pRenderer;
	}
	return NULL;
}

// =====================================================================================================================================================================
//
// 入力の取得
//
// =====================================================================================================================================================================
CKeyboard * CManager::GetKeyboard(void)
{
	if (m_pKeyboard != NULL)
	{
		return m_pKeyboard;
	}
	return NULL;
}

// =====================================================================================================================================================================
//
// ゲームパッドの取得
//
// =====================================================================================================================================================================
CXinputGpad * CManager::GetXinputGpad(void)
{
	if (m_pXinputGpad != NULL)
	{
		return m_pXinputGpad;
	}
	return NULL;
}

// =====================================================================================================================================================================
//
// ゲームの取得
//
// =====================================================================================================================================================================
CGame * CManager::GetGame(void)
{
	if (m_pGame != NULL)
	{
		return m_pGame;
	}
	return NULL;
}

// =====================================================================================================================================================================
//
// サウンドの取得
//
// =====================================================================================================================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}