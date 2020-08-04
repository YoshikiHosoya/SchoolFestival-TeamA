#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "model.h"
#include "game.h"
#include "title.h"
#include "ranking.h"
#include "tutorial.h"
#include "texture.h"
#include "Xinput.h"
#include "texture.h"
#include "BaseMode.h"
#include "mouse.h"
#include "hosso/Debug_ModelViewer.h"
#include "hosso/Debug_EffectViewer.h"
#include "Debug_MapEditor.h"
#include "XInputPad.h"
#include "sound.h"
//他のとこでも使えるようにするメンバ
CRenderer		*CManager::m_pRenderer		= nullptr;
CKeyboard		*CManager::m_pInputKeyboard	= nullptr;
CParticle		*CManager::m_Particle		= nullptr;
CBaseMode		*CManager::m_pBaseMode		= nullptr;
CMouse			*CManager::m_pMouse			= nullptr;
CManager::MODE	CManager::m_mode = CManager::MODE_TITLE;
CXInputPad		*CManager::m_pPad			= nullptr;
CSound			*CManager::m_pSound = nullptr;


CManager::CManager()
{
}

CManager::~CManager()
{
}
//===========================================
//初期化
//===========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//メモリ確保
	m_pRenderer = new CRenderer;
	m_pInputKeyboard = new CKeyboard;
	m_pMouse = new CMouse;
	m_pPad = new CXInputPad;
	m_pSound = new CSound;

	//初期化処理
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}
	m_pInputKeyboard->InitInput(hInstance, hWnd);
	m_pMouse->Init(hInstance, hWnd);
	m_pPad->Init(hInstance, hWnd);

	m_pSound->Init(hWnd);
	CBaseMode::BaseLoad(hWnd);
	CManager::SetMode(m_mode);
	return S_OK;
}
//===========================================
//終了
//===========================================
void CManager::Uninit(void)
{
	//ベースの素材破棄
	CBaseMode::BaseUnload();
	//nullcheck
	if (m_pRenderer)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	if (m_pMouse)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}
	if (m_pPad)
	{
		m_pPad->Uninit();
		delete m_pPad;
		m_pPad = nullptr;
	}
	if (m_pInputKeyboard)
	{
		m_pInputKeyboard->UninitInput();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	if (m_pBaseMode)
	{
		m_pBaseMode->Uninit();

		delete m_pBaseMode;
		m_pBaseMode = nullptr;
	}
	if (m_pSound)
	{
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = nullptr;
	}
}
//===========================================
//更新
//===========================================
void CManager::Update(void)
{
	m_pInputKeyboard->UpdateInput();
	m_pRenderer->Update();
	m_pMouse->Update();
	m_pPad->Update();
	if (m_pBaseMode)
	{	//モード
		m_pBaseMode->Update();
	}

}
//===========================================
//描画
//===========================================
void CManager::Draw(void)
{
	if (m_pBaseMode)
	{	//モード
		m_pBaseMode->Draw();
	}
	m_pRenderer->Draw();
}
//===========================================
//モードの設定
//===========================================
void CManager::SetMode(MODE mode)
{
	//nullcheck
	if (m_pBaseMode)
	{
		//終了処理
		CScene::RereaseAll();
		m_pBaseMode->Uninit();
		delete m_pBaseMode;
		m_pBaseMode = nullptr;
	}

	//音源ストップ
	m_pSound->StopAll();

	//モード切替
	m_mode = mode;

	//レンダラーリセット
	m_pRenderer->ResetRenderer();

	switch (mode)
	{
		//Title
	case MODE_TITLE:
		m_pBaseMode = new CTitle;
		m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;

		//Tutorial
	case MODE_TUTORIAL:
		m_pBaseMode = new CTutorial;
		m_pSound->Play(CSound::LABEL_BGM_TUTORIAL);
		break;

		//Game
	case MODE_GAME:
		m_pBaseMode = new CGame;
		m_pSound->Play(CSound::LABEL_BGM_GAME);

		break;

		//Ranking
	case MODE_RANKING:
		m_pBaseMode = new CRanking;
		m_pSound->Play(CSound::LABEL_BGM_RESULT);
		break;

		//MotionViewer
	case MODE_DEBUG_MODELVIEWER:
		m_pBaseMode = new CDebug_ModelViewer;
		break;

		//EffectViewer
	case MODE_DEBUG_EFFECTVIEWER:
		m_pBaseMode = new CDebug_EffectViewer;
		break;

		//MapEditor
	case MODE_DEBUG_MAPEDITOR:
		m_pBaseMode = new CDebugMapEditor;
		break;
	}

	//nullcheck
	if (m_pBaseMode)
	{
		//初期化
		m_pBaseMode->Init();
	}
}

//===========================================
//ゲームの状態取得
//===========================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}
//===========================================
//レンダラーの所得
//===========================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//===========================================
//キーボード取得
//===========================================
CKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//===========================================
//ベースモード情報の取得
//===========================================
CBaseMode * CManager::GetBaseMode(void)
{
	if (m_pBaseMode)
	{
		return m_pBaseMode;
	}
	return nullptr;
}
//===========================================
//マウスの情報取得
//===========================================
CMouse * CManager::GetMouse()
{
	if (m_pMouse)
	{
		return m_pMouse;
	}
	return nullptr;
}
//===========================================
//パッドの情報取得
//===========================================
CXInputPad * CManager::GetPad(void)
{
	if (m_pPad)
	{
		return m_pPad;
	}
	return nullptr;
}

//===========================================
//ゲームの情報取得
//別のモードの時だとnullptrが返ってくる
//===========================================
CGame * CManager::GetGame()
{
	//nullcheck
	if (m_pBaseMode)
	{
		//Gameクラスにキャスト
		CGame *pGame = (CGame*)m_pBaseMode;

		//nullcheck
		if (pGame)
		{
			return pGame;
		}
	}
	return nullptr;
}

//===========================================
//サウンド取得
//===========================================
CSound * CManager::GetSound()
{
	return m_pSound;
}
