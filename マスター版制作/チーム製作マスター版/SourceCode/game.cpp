// =====================================================================================================================================================================
//
// ゲームの処理 [game.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "playerui.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "pause.h"
#include "ParticleManager.h"
#include "item.h"
#include "UIManager.h"
#include "Scene.h"
#include "3Dline.h"
#include "resultUI.h"
#include "Boss.h"
#include "GameManager.h"
#include "ResultManager.h"
#include "shield.h"
#include "title.h"
#include "ModelSet.h"
#include "meshbox.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define _CRT_SECURE_NO_WARNINGS // 警告除去

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
int			CGame::m_Counter	= 0;

CPlayer		*CGame::m_pPlayer[MAX_CONTROLLER] = {};
CMap		*CGame::m_pMap		= nullptr;

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
	m_pGameManager = nullptr;

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		if (m_pPlayer[nCnt])
		{
			m_pPlayer[nCnt] = nullptr;
		}
	}
}
//==========================================================
// 初期化
//==========================================================
HRESULT CGame::Init(void)
{
	m_nFrame = 0;
	m_nCntNum = 0;

	m_pMap		= CMap::MapCreate();		// マップの生成
	m_pMap->MapLoad(CMap::MAP_1_1);			// マップのロード

	// 捕虜の数を初期化
	CResultUI::ResetPrisonerNum();

	m_pPlayer[(int)TAG::PLAYER_1] = CPlayer::Create(TAG::PLAYER_1);

	if (CPlayer::GetTwoPPlayFlag() && !m_pPlayer[(int)TAG::PLAYER_2])
	{
		// プレイヤー2の配置
		m_pPlayer[(int)TAG::PLAYER_2] = CPlayer::Create(TAG::PLAYER_2);
	}

	//ゲームの進行管理クラス作成
	m_pGameManager = CGameManager::Create();
	m_pGameManager->SetGameState(CGameManager::GAMESTATE::NORMAL);

	//パーティクル生成
	CParticleManager::Create();

	// UI生成
	CUIManager::Create();

	return S_OK;
}
//==========================================================
// 終了
//==========================================================
void CGame::Uninit(void)
{

	// アイテムクラスの静的変数の初期化
	CItem::InitVariable();
	// スコアの計算
	CResultUI::TotalScoreCalculation();

	if (m_pResultManager != nullptr)
	{
		// リザルトマネジャーの破棄
		delete m_pResultManager;
		m_pResultManager = nullptr;
	}

	if (m_pGameManager)
	{
		// ゲームマネージャーのメモリ開放
		m_pGameManager.reset();
		m_pGameManager = nullptr;
	}

	if (m_pMap)
	{
		// マップの破棄
		delete m_pMap;
		m_pMap = nullptr;
	}
}
//==========================================================
// 更新
//==========================================================
void CGame::Update(void)
{
	if (m_pMap)
	{
		// 死亡判定が出ているかの確認
		m_pMap->UpdateDieFlag();
	}

	//nullcheck
	if (m_pGameManager)
	{
		//ゲームの進行管理の更新
		m_pGameManager->Update();
	}

	// リザルトマネージャークラスが生成された時
	if (m_pResultManager != nullptr)
	{
		// リザルトマネージャー更新
		m_pResultManager->Update();
	}
}
//==========================================================
// プレイヤー取得
//==========================================================
CPlayer * CGame::GetPlayer(TAG Tag)
{
	return m_pPlayer[(int)Tag];
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
// ステート変更時のリアクション
//==========================================================
void CGame::StateChangeReaction()
{
	//ステートによって処理が変わる
	switch (m_pGameManager->GetGameState())
	{
	case CGameManager::GAMESTATE::NORMAL:
		//nullcheck
		if (m_pResultManager)
		{
			// リザルト管理クラスの破棄
			delete m_pResultManager;
			m_pResultManager = nullptr;
		}
		break;

	case CGameManager::GAMESTATE::RESULT:
		//nullcheck
		if (m_pResultManager)
		{
			// リザルト管理クラス破棄
			delete m_pResultManager;
			m_pResultManager = nullptr;

		}

		// リザルト管理クラスの生成
		for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
		{
			if (m_pPlayer[nCnt])
			{
				m_pPlayer[nCnt]->SetState(CPlayer::CHARACTER_STATE_INVINCIBLE);
			}
		}

		m_pResultManager = CResultManager::Create();

		break;

	case CGameManager::GAMESTATE::GAMEOVER:
		break;

	case CGameManager::GAMESTATE::PAUSE:
		break;

	default:

		break;
	}
}

//==========================================================
// 体力の取得
//==========================================================
void CGame::Draw(void)
{
	m_pGameManager->Draw();
}
//==========================================================
// デバッグ情報表記
//==========================================================
void CGame::ShowDebugInfo(void)
{
	//キーボード情報取得
	CKeyboard *key = CManager::GetInputKeyboard();

	m_pGameManager->ShowDebugInfo();

	if (m_pMap)
	{
		m_pMap->ShowDebugInfo();
	}

	// デバッグ用当たり判定
	DebugCollision(key);
	// デバッグ用アイテム
	//DebugItem(key);
}

//==========================================================
// デバッグ用当たり判定の可視化on off
//==========================================================
void CGame::DebugCollision(CKeyboard *key)
{
	//使い方説明
	CDebugProc::Print_Right("\n---------Debug Collision----------\n");
	CDebugProc::Print_Right("[Ctrl] + テンキー [5] : 当たり判定のラインの表示非表示\n");


	if (CMeshBox::GetDisp())
	{
		CDebugProc::Print_Right("デバッグ用当たり判定ラインを描画しています\n");
	}
	else
	{
		CDebugProc::Print_Right("デバッグ用当たり判定ラインを描画していません\n");
	}

	//ボスマップ
	if (key->GetKeyboardTrigger(DIK_F7))
	{
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CMap::MAP_1_BOSS);
	}
	if (key->GetKeyboardTrigger(DIK_F8))
	{
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CMap::MAP_2_BOSS);
	}

	// 当たり判定ラインの表示非表示
	if (key->GetKeyboardPress(DIK_LCONTROL))
	{// Ctrl + 5
		if (key->GetKeyboardTrigger(DIK_NUMPAD5))
		{
			if (CMeshBox::GetDisp())
			{// 表示中なら非表示
				CMeshBox::SetDisp(false);
			}
			else
			{// 非表示なら表示
				CMeshBox::SetDisp(true);
			}
		}

		if (key->GetKeyboardTrigger(DIK_8))
		{
			if (m_pMap->GetMapNum() - 1 > 0)
			{
				CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, (CMap::MAP)(m_pMap->GetMapNum() - 1));
			}
		}
		if (key->GetKeyboardTrigger(DIK_9))
		{
			if (m_pMap->GetMapNum() + 1 < CMap::MAP_MAX)
			{
				CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, (CMap::MAP)(m_pMap->GetMapNum() + 1));
			}
		}
		if (key->GetKeyboardTrigger(DIK_0))
		{
			//タイマー減少

			m_pPlayer[(int)TAG::PLAYER_1]->GetPlayerUI()->DecrementTime();
		}
	}
}

//==========================================================
// デバッグ用アイテム
//==========================================================
void CGame::DebugItem(CKeyboard *key)
{
	// デバッグ用アイテムコマンド
	CItem::DebugItemCommand(key);
}
