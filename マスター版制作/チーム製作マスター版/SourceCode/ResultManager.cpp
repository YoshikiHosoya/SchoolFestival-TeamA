// =====================================================================================================================================================================
//
// リザルトマネージャーの処理 [resultmanager.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"
#include "resultmanager.h"
#include "game.h"
#include "basemode.h"
#include "manager.h"
#include "resultui.h"
#include "renderer.h"
#include "fade.h"
#include "player.h"
#include "playerui.h"
#include "sound.h"
#include "map.h"
#include "UI.h"
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
CResultManager::CResultManager()
{
	m_bNextFlag = false;
	m_nNextCount = 240;
	m_ResultState = RESULT_STATE::RESULT_STATE_0;
	m_pResultUI = nullptr;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CResultManager::~CResultManager()
{
	if (m_pResultUI)
	{
		m_pResultUI->SetDeleteFlag(true);
	}
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CResultManager::Init(void)
{
	// リザルトUIの生成
	m_pResultUI = CResultUI::Create();

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CResultManager::Uninit(void)
{

}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CResultManager::Update(void)
{
	if (m_bNextFlag == true)
	{
		m_nNextCount--;

		if (m_nNextCount <= 0)
		{
			// 次の状態へ移行する
			NextMode();
		}
	}

	if (m_ResultState == RESULT_STATE::RESULT_STATE_0)
	{
		// 順番通りに描画し処理していく
		ResultUiOrder();
	}
}

// =====================================================================================================================================================================
//
// 生成
//
// =====================================================================================================================================================================
CResultManager * CResultManager::Create()
{
	//メモリの確保
	CResultManager *pResultManager = new CResultManager();

	// 初期化
	pResultManager->Init();

	//音を止める
	CManager::GetSound()->Stop(CSound::LABEL_BGM_STAGE_01_BOSS);
	CManager::GetSound()->Stop(CSound::LABEL_BGM_STAGE_02_BOSS);

	return pResultManager;
}

// =====================================================================================================================================================================
//
// Uiの出現順番
//
// =====================================================================================================================================================================
void CResultManager::ResultUiOrder()
{
}

// =====================================================================================================================================================================
//
// Uiの描画条件
//
// =====================================================================================================================================================================
void CResultManager::DrawConditions(RESULT_STATE state)
{
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CResultManager::NextMode()
{
	// リザルトの状態が0だった時
	if (m_ResultState == RESULT_STATE::RESULT_STATE_0)
	{
		m_nNextCount = 240;
		m_bNextFlag = false;
		// 状態を1に移行する
		m_ResultState = RESULT_STATE::RESULT_STATE_1;

		CManager::GetSound()->Play(CSound::LABEL_SE_GAMECLEAR);
	}

	// リザルトの状態が1だった時
	else if (m_ResultState == RESULT_STATE::RESULT_STATE_1)
	{
		CResultUI::SetPlayerScoreFlag(false);

		// マップ2に移行
		if (CManager::GetGame()->GetMap()->GetMapNum() == CMap::MAP_1_BOSS)
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_STAGE_CHANGE, CMap::MAP_2_1);
		}
		// ランキングに遷移する
		else if (CManager::GetBaseMode() != nullptr)
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_RANKING);
		}
	}
}
