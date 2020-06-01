#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "createmap.h"
#define _CRT_SECURE_NO_WARNINGS // Œxœ‹Ž
int CGame::m_Counter = 0;
CPlayer *CGame::m_pPlayer = NULL;
int CGame::HP = 0;
int CGame::HPPotion = 0;
int CGame::MP = 0;
int CGame::MPPotion = 0;

//========================================
CGame::CGame()
{
}
//========================================
CGame::~CGame()
{
}
//========================================
HRESULT CGame::Init(void)
{
	m_pCreateMap = CCreateMap::Create(1);
	m_pPlayer = CPlayer::Create();
	m_pPlayer->SetLife(50);
	m_pPlayer->SetPosition(D3DXVECTOR3(0.0f, 55.0f, 0.0f));
	return S_OK;
}
//========================================
void CGame::Uninit(void)
{
}

void CGame::Update(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	if (key->GetKeyboardPress(DIK_P))
	{
		CFADE::SetFade(CManager::MODE_GAME2);
	}
 }

CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
}
int CGame::GetHP(void)
{
	return HP;
}

int CGame::GetMP(void)
{
	return MP;
}

int CGame::GetHPPotion(void)
{
	return HPPotion;
}

int CGame::GetMPPotion(void)
{
	return MPPotion;
}

CCreateMap * CGame::GetCreateMap(void)
{
	return m_pCreateMap;
}
