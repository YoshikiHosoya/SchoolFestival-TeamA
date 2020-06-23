#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "pause.h"
#include "TexAnimation3D.h"
#include "TexAnimation2D.h"
#define _CRT_SECURE_NO_WARNINGS // 警告除去
int			CGame::m_Counter	= 0;
CPlayer		*CGame::m_pPlayer	= NULL;
CMap		*CGame::m_pMap		= NULL;

//==========================================================
// コンストラクタ
//==========================================================
CGame::CGame()
{
}
//==========================================================
// デストラクタ
//==========================================================
CGame::~CGame()
{
}
//==========================================================
// 初期化
//==========================================================
HRESULT CGame::Init(void)
{
	m_pMap		= CMap::MapCreate(0);	// マップの生成
	m_pPlayer	= CPlayer::Create();
	m_pPlayer->SetLife(50);
	m_pPlayer->SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	m_pPause->CreatePause();
	return S_OK;
}
//==========================================================
// 終了
//==========================================================
void CGame::Uninit(void)
{
}
//==========================================================
// 更新
//==========================================================
void CGame::Update(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	if (key->GetKeyboardTrigger(DIK_F9))
	{
		CScene::StopUpdate();
	}
	m_pMap->UpdateDieFlag();
 }
//==========================================================
// プレイヤー取得
//==========================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}
//==========================================================
// マップ取得
//==========================================================
CMap * CGame::GetMap(void)
{
	if (m_pMap)
	{
		return m_pMap;
	}
	return nullptr;
}

//==========================================================
// 体力の取得
//==========================================================
void CGame::Draw(void)
{
}
//==========================================================
// デバッグ情報表記
//==========================================================
void CGame::ShowDebugInfo(void)
{
	//キーボード情報取得
	CKeyboard *key = CManager::GetInputKeyboard();;

	//2Dエフェクト
	if (key->GetKeyboardTrigger(DIK_2))
	{
		CTexAnimation2D::Create(SCREEN_CENTER_POS, D3DXVECTOR3(150.0f, 150.0f, 0.0f), ZeroVector3, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION, 3, CScene::OBJTYPE_EXPROSION);
	}
	//3Dエフェクト
	if (key->GetKeyboardTrigger(DIK_3))
	{
		CTexAnimation3D::Create(m_pPlayer->GetPosition(), D3DXVECTOR3(150.0f, 150.0f, 0.0f), ZeroVector3, CTexture::SEPARATE_TEX_EFFECT_EXPLOSION, 3, CScene::OBJTYPE_EXPROSION);
	}
}