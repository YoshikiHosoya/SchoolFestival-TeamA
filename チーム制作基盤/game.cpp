#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "Enemy.h"
#include "pause.h"
#define _CRT_SECURE_NO_WARNINGS // 警告除去
int			CGame::m_Counter	= 0;
CPlayer		*CGame::m_pPlayer	= NULL;
CEnemy		*CGame::m_pEnemy	= NULL;
CMap		*CGame::m_pMap		= NULL;

int CGame::HP = 0;
int CGame::HPPotion = 0;
int CGame::MP = 0;
int CGame::MPPotion = 0;

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

	m_pEnemy = CEnemy::Create();
	m_pEnemy->SetLife(50);
	m_pEnemy->SetPosition(D3DXVECTOR3(0.0f, 100.0f, 0.0f));

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
int CGame::GetHP(void)
{
	return HP;
}
void CGame::Draw(void)
{
}
void CGame::ShowDebugInfo(void)
{
}