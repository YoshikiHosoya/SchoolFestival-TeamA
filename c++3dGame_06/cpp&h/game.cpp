// ------------------------------------------
//
// ゲーム処理 [game.cpp]
// Author : Fujiwara Masato
//
// ------------------------------------------
#include "game.h"
/* 描画 */
#include "tlybg.h"
#include "fade.h"
#include "item.h"
#include "floor.h"
#include "player.h"
#include "item.h"
#include "scene_X.h"
#include "3Deffect.h"
#include "meshsphere.h"
#include "player.h"
#include "gauge.h"

/* 当たり判定 */
#include "collision.h"

/* ポーズ */
#include "pause.h"
#include "wall.h"
#include "enemy.h"
#include "3ditem.h"
#include "camera.h"
#include "renderer.h"
#include "debugproc.h"
#include "Debugcollision.h"
#include "object.h"
#include "floartile.h"
#include "warp.h"
#include "ceiling.h"
#include "titleEnemy.h"
#include "gameui.h"
#include "key.h"
#include "Manual.h"
// ------------------------------------------
//
// マクロ定義
//
// ------------------------------------------

// ------------------------------------------
//
// 静的変数宣言
//
// ------------------------------------------
CGame::STATE CGame::m_state = CGame::STATE_NORMAL;
int CGame::m_nStage = 0;	// ステージ
CPause *m_pPause = NULL;
CPlayer *CGame::m_pPlayer = NULL;

// ------------------------------------------
// コンストラクタ
// ------------------------------------------
CGame::CGame()
{
	m_state = CGame::STATE_NORMAL;
	m_Shard = 0;
}

// ------------------------------------------
// デストラクタ
// ------------------------------------------
CGame::~CGame()
{
}

// ------------------------------------------
// 初期化
// ------------------------------------------
void CGame::Init(void)
{
	// 状態
	m_state = STATE_NORMAL;
	// ステージ
	m_nStage = 0;
	CManager::PLAYER playerID = CManager::PLAYER_1;
	// プレイヤー
	m_pPlayer = CPlayer::Create();
	// 敵
	CEnemy::Create();
	// 壁の生成
	//CWall::LoadCreate();
	// 床タイル
	CFloarTile::LoadCreate();
	// ゲームuiの生成
	CGame_ui::Create();

	// 天井の生成
	//CCeiling::LoadCreate();
	// 3DItemの生成
	C3DItem::LoadCreate();
	// エフェクト生成
	C3DEffect::Create();
	// 鍵生成
	CKey::Create();

	// メッシュスフィア
	//CMeshsphere::create();
	//CMeshsphere::Set(D3DXVECTOR3(0.0f, 0.0f, 0.0f), 10000.0f);
	//CMeshsphere::SetRadius(0, 10000.0f);

	CPause::Create();
	CManual::Create();

	// 2d当たり判定の生成
	//CCollision::LoadCreate2D();
}

// ------------------------------------------
// 終了
// ------------------------------------------
void CGame::Uninit(void)
{
	//CGameUI::Unload();
	// シーン情報の削除
	CScene::ReleaseAll();
	// 当たり判定の削除
	CCollision::DeleteAll();
}

// ------------------------------------------
// 更新
// ------------------------------------------
void CGame::Update(void)
{
	// 画面遷移の状態が遷移していない状態だったら
	if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
	{
		C3DItem * p3DItem = NULL;	// 3dアイテム

		for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
		{
			if (p3DItem == NULL) p3DItem = (C3DItem*)CScene::GetActor(CScene::ACTOR_3DITEM, CScene::LAYER_3DOBJECT, nCntLayer);	// 3Dアイテム
		}

		//欠片の数を取得
		if (p3DItem != NULL)
		{
			CDebugproc::Print("欠片の総数: %d\n", C3DItem::GetShardNum());
		}
		else if (p3DItem == NULL)
		{
			CDebugproc::Print("欠片の総数: %d\n", 0);
		}
	}

	//ポーズ処理
	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_P) || CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_START))
	{
		if (CPause::GetPause())
		{
			CPause::SetPause(false);
		}
		else
		{
			CPause::SetPause(true);
		}
	}

	/*if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_9))
	{
		if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
		{
			CManager::GetFade()->SetFade(CManager::MODE_RANKING);
		}
	}*/

	// 当たり判定
	CCollision::UpdateAll();
}

// ------------------------------------------
// 描画
// ------------------------------------------
void CGame::Draw(void)
{
}

// ------------------------------------------
// 状態取得
// ------------------------------------------
CGame::STATE CGame::GetState(void)
{
	return m_state;
}

// ------------------------------------------
// ステージ取得
// ------------------------------------------
int CGame::GetStage(void)
{
	return m_nStage;
}

// ------------------------------------------
// 状態設定
// ------------------------------------------
void CGame::SetState(STATE state)
{
	m_state = state;
}
