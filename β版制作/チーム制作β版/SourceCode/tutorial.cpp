// =====================================================================================================================================================================
//
// チュートリアルの処理 [tutorial.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "UIManager.h"
#include "tutorialUI.h"
#include "tutorialmanager.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define _CRT_SECURE_NO_WARNINGS // 警告除去

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

//==========================================================
// コンストラクタ
//==========================================================
CTutorial::CTutorial()
{
	m_pTutorialManager = nullptr;
}

//==========================================================
// デストラクタ
//==========================================================
CTutorial::~CTutorial()
{
}

//==========================================================
// 初期化
//==========================================================
HRESULT CTutorial::Init(void)
{
	// UI生成
	CUIManager::Create();

	// チュートリアルマネージャーの生成
	m_pTutorialManager = CTutorialManager::Create();

	return S_OK;
}

//==========================================================
// 終了
//==========================================================
void CTutorial::Uninit(void)
{
	if (m_pTutorialManager != nullptr)
	{
		// ランキングマネジャーの破棄
		delete m_pTutorialManager;
		m_pTutorialManager = nullptr;
	}
}

//==========================================================
// 更新
//==========================================================
void CTutorial::Update(void)
{
	m_pTutorialManager->Update();
}

//==========================================================
// 描画処理
//==========================================================
void CTutorial::Draw(void)
{
}

//==========================================================
// デバッグ情報表記
//==========================================================
void CTutorial::ShowDebugInfo(void)
{
}
