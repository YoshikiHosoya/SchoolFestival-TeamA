// =====================================================================================================================================================================
//
// ランキングUIの処理 [resultUI.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "main.h"			// インクルードファイル
#include "rankingUI.h"
#include "debugproc.h"
#include "UIManager.h"
#include "scene2D.h"

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
CRankingUI::CRankingUI()
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CRankingUI::~CRankingUI()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CRankingUI::Init(void)
{
	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			switch (nCnt)
			{
			// ランキング
			case RANKING_UI::RANKING:
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 65.0f, 0.0f), D3DXVECTOR3(70.0f, 65.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING));
				break;
			}
		}
	}
	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CRankingUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 終了
			m_apScene2D[nCnt]->Uninit();
		}
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CRankingUI::Update(void)
{
	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 更新
			m_apScene2D[nCnt]->Update();
		}
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CRankingUI::Draw(void)
{
	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 描画
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// タイトルUIの生成
//
// =====================================================================================================================================================================
CRankingUI * CRankingUI::Create()
{
	//メモリの確保
	CRankingUI *pRankingUI = new CRankingUI();

	// 初期化
	pRankingUI->Init();

	//オブジェタイプ設定してSceneに所有権を渡す
	CUIManager::AddUIList(std::move(pRankingUI));

	return pRankingUI;
}