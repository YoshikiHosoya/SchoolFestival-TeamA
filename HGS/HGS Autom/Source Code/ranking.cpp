//------------------------------------------------------------------------------
//
//リザルト処理  [result.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "scene2D.h"
#include "multinumber.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define VERTICAL_SPACE		(70.0f)									// 縦の間隔
#define WAITTIME_BASE		(180)									// 待ち時間
#define ONE_SECOND			(60)									// 1秒
#define RANKINGSIZE			(D3DXVECTOR3(80.0f, 30.0f, 0.0f))		// ランキングUIのサイズ
#define RANKING_SPACE		(10)									// ランキングの間隔
#define RANKINGSCORESIZE	(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// ランキングスコアサイズ
#define RANKINGSCOREDIGITS	(7)										// ランキングの桁数

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
char *CRanking::m_RankingFileName =
{
	"data/Ranking/RankingData.txt" 			// ランキングの情報
};
char *CRanking::m_SaveScoreFileName =
{
	"data/Ranking/SaveScoreData.txt" 			// ランキングの情報
};


//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CRanking::CRanking()
{
	// 初期化
	m_nRankingScore.clear();
	m_apScene2D.clear();
	m_apRankScore.clear();
	m_nCntResult = 0;

	RankingUICreate();	// 生成
	RankingScoreCreate(); // スコア生成
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CRanking::~CRanking()
{
	m_apScene2D.clear();
	m_apRankScore.clear();
}

//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CRanking::Init(HWND hWnd)
{
	//カメラ座標設定
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_FIXED);

	return S_OK;
}

//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CRanking::Uninit()
{

}

//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CRanking::Update()
{
	//カウンタ++
	m_nCntResult++;

	// ランキングUIの更新
	for (int nCnt = 0; nCnt < (int)RANKING_UI::RANKING_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			m_apScene2D[nCnt]->Update();
		}
	}

	//フェードしてない時
	if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//何かボタン押したとき
		if (CHossoLibrary::CheckAnyButton())
		{
				//ステート変更
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CRanking::Draw()
{
	// ランキングUIの描画
	for (int nCnt = 0; nCnt < (int)RANKING_UI::RANKING_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			m_apScene2D[nCnt]->Draw();
		}
	}

}

//------------------------------------------------------------------------------
//ランキングUIの生成
//------------------------------------------------------------------------------
void CRanking::RankingUICreate()
{
	for (int nCnt = 0; nCnt < (int)RANKING_UI::RANKING_MAX; nCnt++)
	{
		// ランキングタイトルロゴ
		if (nCnt == (int)RANKING_UI::RANKING_NAME)
		{
			// シーン2Dの生成
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 65.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f), CScene::OBJTYPE_UI));
			// テクスチャの割り当て
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_NAME));
		}

		// 順位
		else
		{
			// シーン2Dの生成
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.2f), (100.0f + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f), RANKINGSIZE, CScene::OBJTYPE_UI));
			// テクスチャの割り当て
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(CTexture::TEX_UI_RANKING_1st + nCnt - 1)));

			m_apScene2D[nCnt]->SetDisp(false);
		}
	}
}

//------------------------------------------------------------------------------
//ランキングスコアの生成
//------------------------------------------------------------------------------
void CRanking::RankingScoreCreate()
{
	for (int nCnt = 0; nCnt < (int)RANKING_SCORE::SCORE_MAX; nCnt++)
	{
		m_nRankingScore.emplace_back(0);

		// スコアの生成
		m_apRankScore.emplace_back((CMultiNumber::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.4f), ((200.0f - 15.0f) + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f),
								RANKINGSCORESIZE,
								m_nRankingScore[nCnt],
								RANKINGSCOREDIGITS,
								CScene::OBJTYPE_UI)));
	}
}