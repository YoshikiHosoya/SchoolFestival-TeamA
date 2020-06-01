#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "model.h"
#include "game.h"
#include "Xinput.h"
//他のとこでも使えるようにするメンバ
CRenderer *CManager::m_pRendere		  = NULL;
CKeyboard *CManager::m_pInputKeyboard = NULL;
CSceneX   *CManager::m_SceneX		  = NULL;
CCreateMap*CManager::m_CreateMap      = NULL;
CParticle *CManager::m_Particle       = NULL;
CModel    *CManager::m_Model = NULL;
CGame *CManager::m_pGame = NULL;
CManager::GAME_MODE CManager::m_mode = CManager::MODE_TITLE;
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
	m_pRendere		 = new CRenderer;
	m_pInputKeyboard = new CKeyboard;
	//m_pMouse = new CMouse;
	//初期化処理
	if (FAILED(m_pRendere->Init(hWnd, TRUE)))
	{
		return -1;
	}
	m_pInputKeyboard->InitInput(hInstance, hWnd);


	CModel::LoadModel();
	CManager::SetGameMode(MODE_GAME);
	return S_OK;
}
//===========================================
//終了
//===========================================
void CManager::Uninit(void)
{
	CModel::UnLoad();
	m_pRendere->Uninit();
}
//===========================================
//更新
//===========================================
void CManager::Update(void)
{
	m_pInputKeyboard->UpdateInput();
	m_pRendere->Update();
	m_Model->Update();
	switch (m_mode)
	{
	case MODE_TITLE:
		break;
	case MODE_RESULT:
		break;
	case MODE_GAME:
		m_pGame->Update();
		break;
	case MODE_GAME2:
		break;
	case MODE_GAME3:
		break;
	case MODE_TUTORIAL:
		break;
	case MODE_CLEAR:
		break;
	}
}
//===========================================
//描画
//===========================================
void CManager::Drow(void)
{
	m_pRendere->Draw();
}
//===========================================
//モードの設定
//===========================================
void CManager::SetGameMode(GAME_MODE mode)
{
	switch (m_mode)
	{
	case MODE_TITLE:
		CScene::RereaseAll();
		break;
	case MODE_GAME:
		CScene::RereaseAll();
		m_pGame->Uninit();
		delete m_pGame;
		m_pGame = NULL;
		break;
	case MODE_GAME2:
		CScene::RereaseAll();
		break;
	case MODE_GAME3:
		CScene::RereaseAll();
		break;

	case MODE_RESULT:
		CScene::RereaseAll();
		break;
	case MODE_TUTORIAL:
		CScene::RereaseAll();
		break;
	case MODE_CLEAR:
		CScene::RereaseAll();
		break;
	}

	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		break;
	case MODE_GAME:
		m_pGame = new CGame;
		m_pGame->Init();
		break;
	case MODE_GAME2:
		break;
	case MODE_GAME3:
		break;
	case MODE_RESULT:
		break;
	case MODE_TUTORIAL:
		break;
	case MODE_CLEAR:
		break;
	}
}

//===========================================
//ゲームの状態取得
//===========================================
CManager::GAME_MODE CManager::GetGameState(void)
{
	return m_mode;
}
//===========================================
//レンダラーの所得
//===========================================
CRenderer * CManager::GetRendere(void)
{
	return m_pRendere;
}
//===========================================
//キーボード取得
//===========================================
CKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//===========================================
//クリエイトマップの取得
//===========================================
CCreateMap * CManager::GetCreateMap(void)
{
	if (m_CreateMap)
	{
	return m_CreateMap;
	}
}
//===========================================
//ゲーム情報の取得
//===========================================
CGame * CManager::GetGame(void)
{
	if (m_pGame)
	{
	return m_pGame;
	}
}