#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "model.h"
#include "game.h"
#include "texture.h"
#include "Xinput.h"
#include "texture.h"
#include "BaseMode.h"
//他のとこでも使えるようにするメンバ
CRenderer *CManager::m_pRendere		  = NULL;
CKeyboard *CManager::m_pInputKeyboard = NULL;
CSceneX   *CManager::m_SceneX		  = NULL;
CCreateMap*CManager::m_CreateMap      = NULL;
CParticle *CManager::m_Particle       = NULL;
CModel    *CManager::m_Model = NULL;
CBaseMode *CManager::m_pBaseMode = NULL;
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
	CBaseMode::BaseLoad(hWnd);
	CManager::SetGameMode(MODE_GAME);
	return S_OK;
}
//===========================================
//終了
//===========================================
void CManager::Uninit(void)
{
	//ベースの素材破棄
	CBaseMode::BaseUnload();
	m_pRendere->Uninit();
	if (m_pBaseMode)
	{
		//モード
		m_pBaseMode->Uninit();
	}
}
//===========================================
//更新
//===========================================
void CManager::Update(void)
{
	m_pInputKeyboard->UpdateInput();
	m_pRendere->Update();
	m_Model->Update();
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
	m_pRendere->Draw();
}
//===========================================
//モードの設定
//===========================================
void CManager::SetGameMode(GAME_MODE mode)
{
	if (m_pBaseMode)
	{
		CScene::RereaseAll();
		m_pBaseMode->Uninit();
		delete m_pBaseMode;
		m_pBaseMode = nullptr;
	}
	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		break;
	case MODE_GAME:
		m_pBaseMode = new CGame;
		m_pBaseMode->Init();
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
	return nullptr;
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
