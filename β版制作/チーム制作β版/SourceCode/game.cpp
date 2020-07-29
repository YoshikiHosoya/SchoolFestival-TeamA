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
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "pause.h"
#include "ParticleManager.h"
#include "TexAnimation3D_Collision.h"
#include "item.h"
#include "UIManager.h"
#include "Scene.h"
#include "3Dline.h"
#include "resultUI.h"
#include "ResultManager.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define _CRT_SECURE_NO_WARNINGS // 警告除去

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
int			CGame::m_Counter	= 0;
CPlayer		*CGame::m_pPlayer	= nullptr;
CMap		*CGame::m_pMap		= nullptr;

//==========================================================
// コンストラクタ
//==========================================================
CGame::CGame()
{
	// ゲームモードの初期状態
	m_GameMode = GAME_MODE_NORMAL;
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
	m_pMap		= CMap::MapCreate(CMap::MAP_1);	// マップの生成
	m_pPlayer	= CPlayer::Create();
	m_pPlayer->SetLife(30);
	m_pPlayer->SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	m_pPause->CreatePause();

	// ゲームモードの初期設定
	m_GameMode = GAME_MODE_NORMAL;

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
}
//==========================================================
// 更新
//==========================================================
void CGame::Update(void)
{
	// 死亡判定が出ているかの確認
	m_pMap->UpdateDieFlag();

	// リザルトモードでまだリザルトマネージャーが生成されていなかった時
	if (m_GameMode == GAME_MODE_RESULT && m_pResultManager == nullptr)
	{
		// リザルト管理クラスの生成
		m_pResultManager = CResultManager::Create();
	}
	else
	{
		// リザルトマネージャークラスが生成された時
		if (m_pResultManager != nullptr)
		{
			// リザルトマネージャー更新
			m_pResultManager->Update();
		}
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
void CGame::Draw(void)
{
}
//==========================================================
// デバッグ情報表記
//==========================================================
void CGame::ShowDebugInfo(void)
{
	//キーボード情報取得
	CKeyboard *key = CManager::GetInputKeyboard();

	// デバッグ用当たり判定
	DebugCollision(key);
	// デバッグ用アイテム
	DebugItem(key);
}

//==========================================================
// デバッグ用当たり判定の可視化on off
//==========================================================
void CGame::DebugCollision(CKeyboard *key)
{
	//使い方説明
	CDebugProc::Print("\n---------Debug Collision----------\n");
	CDebugProc::Print("[Ctrl] + テンキー [5] : 当たり判定のラインの表示非表示\n");

	if (C3DLine::GetDrawFlag())
	{
		CDebugProc::Print("デバッグ用当たり判定ラインを描画しています\n");
	}
	else
	{
		CDebugProc::Print("デバッグ用当たり判定ラインを描画していません\n");
	}

	// 当たり判定ラインの表示非表示
	if (key->GetKeyboardPress(DIK_LCONTROL))
	{// Ctrl + 5
		if (key->GetKeyboardTrigger(DIK_NUMPAD5))
		{
			if (C3DLine::GetDrawFlag())
			{// 表示中なら非表示
				C3DLine::SetDrawFlag(false);
			}
			else
			{// 非表示なら表示
				C3DLine::SetDrawFlag(true);
			}
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
