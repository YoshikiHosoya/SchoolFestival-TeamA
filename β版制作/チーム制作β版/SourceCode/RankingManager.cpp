// =====================================================================================================================================================================
//
// ランキングマネージャーの処理 [rankingmanager.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"
#include "rankingmanager.h"
#include "game.h"
#include "basemode.h"
#include "manager.h"
#include "rankingui.h"
#include "renderer.h"
#include "fade.h"
#include "inputKeyboard.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CRankingManager::CRankingManager()
{
	m_RankingState = RANKING_STATE_0;
	m_pRankingUI = nullptr;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CRankingManager::~CRankingManager()
{
	// uiの解放
	if (m_pRankingUI)
	{
		m_pRankingUI->Uninit();
		m_pRankingUI = nullptr;
	}
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CRankingManager::Init(void)
{
	// リザルトUIの生成
	m_pRankingUI = CRankingUI::Create();
	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CRankingManager::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CRankingManager::Update(void)
{
	//キーボード情報取得
	CKeyboard *key = CManager::GetInputKeyboard();

	// エンターを押したとき
	if (key->GetKeyboardTrigger(DIK_RETURN))
	{
		// ゲームモードへ状態遷移
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_TITLE);
	}
}

// =====================================================================================================================================================================
//
// 生成
//
// =====================================================================================================================================================================
CRankingManager * CRankingManager::Create()
{
	//メモリの確保
	CRankingManager *pRankingManager = new CRankingManager();

	// 初期化
	pRankingManager->Init();

	return pRankingManager;
}

// =====================================================================================================================================================================
//
// Uiの出現順番
//
// =====================================================================================================================================================================
void CRankingManager::RankingUiOrder()
{

}
