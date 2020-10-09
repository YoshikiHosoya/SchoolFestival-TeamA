//------------------------------------------------------------------------------
//
//ゲーム処理  [game.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "player_3D.h"
#include "fade.h"
#include "sound.h"
#include "keyboard.h"
#include "camera.h"
#include "Map.h"
#include "multinumber.h"
#include "Pad_XInput.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
int CGame::m_nScore = 0;
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS	(D3DXVECTOR3(0.0f, 300.0f, -800.0f))		//プレイヤーの初期座標
#define DEFAULT_TIMER		(120)									//タイマー
#define GAMEEND_INTERVAL	(240)									//ゲーム終了してから遷移するまでのカウンタ
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CGame::CGame()
{
	//初期化
	m_pPlayer.reset();

	m_nCntState = 0;
	m_gamestate = STATE_READY;
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CGame::~CGame()
{
	//開放
	m_pPlayer.reset();

}

//------------------------------------------------------------------------------
//ゲームステートセット
//------------------------------------------------------------------------------
void CGame::SetGamestate(STATE gamestate)
{
	//ステートが進んでいる場合
	if (m_gamestate != CGame::STATE_NONE)
	{
		//ステート変更
		m_gamestate = gamestate;
	}
}

//------------------------------------------------------------------------------
//プレイヤー取得
//------------------------------------------------------------------------------
CPlayer * CGame::GetPlayer()
{
	if (m_pPlayer)
	{
		return m_pPlayer.get();
	}
	return nullptr;
}
