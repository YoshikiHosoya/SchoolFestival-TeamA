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
#define RANKINGSIZE			(D3DXVECTOR3(80.0f, 50.0f, 0.0f))		// ランキングUIのサイズ
#define PLAYER_SCORE_SIZE	(D3DXVECTOR3(70.0f, 150.0f, 0.0f))		// プレイヤースコアのサイズ

#define RANKING_GOTITLESIZE			(D3DXVECTOR3(240.0f, 100.0f, 0.0f))		// ランキングUIのサイズ	タイトルへ

#define RANKING_SPACE		(10)									// ランキングの間隔
#define RANKINGSCORESIZE	(D3DXVECTOR3(40.0f, 80.0f, 0.0f))		// ランキングスコアサイズ
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
	m_pPlayerScore.clear();
	m_nRankingScore.clear();
	m_apScene2D.clear();
	m_apRankScore.clear();
	m_nPlayerScore = 0;
	m_nCntResult = 0;
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

	// スコアの読み込み
	RankingDataLoad();
	// プレイヤーのスコアを読み込み
	PlayerScoreLoad();
	// UI生成
	RankingUICreate();
	// スコア生成
	RankingScoreCreate();
	// プレイヤースコア生成
	PlayerScoreCreate();

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
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.75f), 65.0f, 0.0f), D3DXVECTOR3(500.0f, 100.0f, 0.0f), CScene::OBJTYPE_UI));
			// テクスチャの割り当て
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_NAME));
		}
		// プレイヤースコア
		else if (nCnt == (int)RANKING_UI::RANKING_SCORE)
		{
			// シーン2Dの生成
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.25f), SCREEN_HEIGHT * 0.45f, 0.0f), RANKING_GOTITLESIZE, CScene::OBJTYPE_UI));
			// テクスチャの割り当て
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_SCORE));
		}
		// タイトルへ
		else if (nCnt == (int)RANKING_UI::RANKING_GO_TITLE)
		{
			// シーン2Dの生成
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 650.0f, 0.0f), RANKING_GOTITLESIZE, CScene::OBJTYPE_UI));
			// テクスチャの割り当て
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_GO_TITLE));
		}
		// 順位
		else
		{
			// シーン2Dの生成
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.6f), (20.0f + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f), RANKINGSIZE, CScene::OBJTYPE_UI));
			// テクスチャの割り当て
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(CTexture::TEX_UI_RANKING_1st + nCnt - 2)));
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
		m_nRankingScore.emplace_back(1000000);

		// スコアの生成
		m_apRankScore.emplace_back((CMultiNumber::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.8f), ((200.0f - 15.0f) + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f),
								RANKINGSCORESIZE,
								m_nRankingScore[nCnt],
								RANKINGSCOREDIGITS,
								CScene::OBJTYPE_UI)));
	}
}

//------------------------------------------------------------------------------
//プレイヤースコアの生成
//------------------------------------------------------------------------------
void CRanking::PlayerScoreCreate()
{
	// スコアの生成
	m_pPlayerScore.emplace_back((CMultiNumber::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.25f), SCREEN_HEIGHT * 0.6f, 0.0f),
											PLAYER_SCORE_SIZE,
											m_nPlayerScore,
											RANKINGSCOREDIGITS,
											CScene::OBJTYPE_UI)));
}

//------------------------------------------------------------------------------
//ランキングのデータのロード
//------------------------------------------------------------------------------
void CRanking::RankingDataLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

	static int nRnak[(int)RANKING_SCORE::SCORE_MAX] = {};

	// ファイルを開く
	pFile = fopen(m_RankingFileName, "r");

	// 開いているとき
	if (pFile != NULL)
	{
		// SCRIPTが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
			sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入
		}

		// SCRIPTが来たら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPTが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
				sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

															// RANKINGSETが来たら
				if (strcmp(cHeadText, "RANKINGSET") == 0)
				{
					// END_RANKINGSETが来るまでループ
					while (strcmp(cHeadText, "END_RANKINGSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						if (strcmp(cHeadText, "RANKING_1st") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_1st]);		// 比較用テキストにRANKIG_1stを代入
						}
						else if (strcmp(cHeadText, "RANKING_2nd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_2nd]);		// 比較用テキストにRANKIG_2ndを代入
						}
						else if (strcmp(cHeadText, "RANKING_3rd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_3rd]);		// 比較用テキストにRANKIG_3rdを代入
						}
						else if (strcmp(cHeadText, "RANKING_4th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_4th]);		// 比較用テキストにRANKIG_4thを代入
						}
						else if (strcmp(cHeadText, "RANKING_5th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_5th]);		// 比較用テキストにRANKIG_5thを代入
						}
						else if (strcmp(cHeadText, "END_RANKINGSET") == 0)
						{
							for (int nCnt = 0; nCnt < (int)RANKING_SCORE::SCORE_MAX; nCnt++)
							{
								// 末尾にランキングのスコアデータを追加
								m_nRankingScore.emplace_back(nRnak[nCnt]);
							}
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "ランキングのデータ読み込み失敗", "警告", MB_ICONWARNING);
	}
}

//------------------------------------------------------------------------------
//ランキングスコアのロード
//------------------------------------------------------------------------------
void CRanking::PlayerScoreLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	int nScore = 0;					// スコア

	// ファイルを開く
	pFile = fopen(m_SaveScoreFileName, "r");

	// 開いているとき
	if (pFile != NULL)
	{
		// SCRIPTが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
			sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入
		}

		// SCRIPTが来たら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPTが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
				sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

				// SCORESETが来たら
				if (strcmp(cHeadText, "SCORESET") == 0)
				{
					// END_SCORESETが来るまでループ
					while (strcmp(cHeadText, "END_SCORESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

						if (strcmp(cHeadText, "SCORE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_nPlayerScore);
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "スコアのデータ読み込み失敗", "警告", MB_ICONWARNING);
	}
}