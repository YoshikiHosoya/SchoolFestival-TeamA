// =====================================================================================================================================================================
//
// デバッグ マップエディターの処理 [Debug_MapEditor.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "Debug_MapEditor.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "pause.h"
#include "ParticleManager.h"
#include "item.h"
#include "UIManager.h"
#include "Scene.h"
#include "3Dline.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CMap		*CDebugMapEditor::m_pMap		= nullptr;

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CDebugMapEditor::CDebugMapEditor()
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CDebugMapEditor::~CDebugMapEditor()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CDebugMapEditor::Init(void)
{
	// マップの生成
	m_pMap		= CMap::MapCreate();
	// マップのロード
	m_pMap->MapLoad(CMap::MAP_1_1);

	//パーティクル生成
	CParticleManager::Create();

	// 更新を止める
	CScene::SetStopFlag(true);

	return S_OK;

}
// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CDebugMapEditor::Uninit(void)
{
	if (m_pMap)
	{
		// マップの破棄
		delete m_pMap;
		m_pMap = nullptr;
	}
}
// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CDebugMapEditor::Update(void)
{
	// マップの死亡フラグ確認関数
	m_pMap->UpdateDieFlag();
 }
// =====================================================================================================================================================================
//
// プレイヤーの取得
//
// =====================================================================================================================================================================
CPlayer * CDebugMapEditor::GetPlayer(CONTROLLER Controller)
{
	return nullptr;
}
// =====================================================================================================================================================================
//
// マップの取得
//
// =====================================================================================================================================================================
CMap * CDebugMapEditor::GetMap(void)
{
	return m_pMap;
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CDebugMapEditor::Draw(void)
{
}

// =====================================================================================================================================================================
//
// デバッグ情報表記
//
// =====================================================================================================================================================================
void CDebugMapEditor::ShowDebugInfo(void)
{
	//キーボード情報取得
	CKeyboard *key = CManager::GetInputKeyboard();

	//使い方説明
	CDebugProc::Print_Left("---------Debug Collision----------\n");
	CDebugProc::Print_Left("[Ctrl] + テンキー [5] : 当たり判定のラインの表示非表示\n");

	if (C3DLine::GetDrawFlag())
	{
		CDebugProc::Print_Left("デバッグ用当たり判定ラインを描画しています\n");
	}
	else
	{
		CDebugProc::Print_Left("デバッグ用当たり判定ラインを描画していません\n");
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

	// マップの更新
	m_pMap->MapUpdate();
}