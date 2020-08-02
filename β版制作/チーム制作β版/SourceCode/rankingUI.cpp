// =====================================================================================================================================================================
//
// ランキングUIの処理 [resultUI.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"			// インクルードファイル
#include "rankingUI.h"
#include "debugproc.h"
#include "UIManager.h"
#include "scene2D.h"
#include "multinumber.h"
#include "resultui.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
RANKING_DATA	CRankingUI::m_RankingData				= {};
RANKING_SCORE_DATA	CRankingUI::m_ScoreData = {};

int				CRankingUI::m_nRankingScore[SCORE_MAX]	= {};
int				CRankingUI::m_nScore = 0;
// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CRankingUI::m_RankingFileName =
{
	"data/Load/Ranking/RankingData.txt" 			// アイテムの情報
};
char *CRankingUI::m_SaveScoreFileName =
{
	"data/Load/Ranking/SaveScoreData.txt" 			// アイテムの情報
};


// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define RANKINGSIZE (D3DXVECTOR3(100.0f, 50.0f, 0.0f))
#define RANKING_SPACE (10)

#define RANKINGSCORESIZE (D3DXVECTOR3(70.0f, 70.0f, 0.0f))
#define RANKINGSCOREDIGITS (7)

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CRankingUI::CRankingUI()
{
	// 初期化
	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < RANKING_NUM; nCnt++)
	{
		m_pRankScore[nCnt] = nullptr;
	}
	m_nColCnt = 0;
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
	// スコアの読み込み
	CRankingUI::RankingLoad();
	// ランキングの計算
	RankingCalculation();
	// ランキングスコアのセーブ
	RankingSave();

	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			// ランキングタイトルロゴ
			if (nCnt == RANKING_NAME)
			{
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 65.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f));
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_NAME));
			}

			// 順位
			else
			{
				// シーン2Dの生成
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.25f), ((200.0f - 100.0f) + (100.0f * nCnt)) + RANKING_SPACE * nCnt, 0.0f), RANKINGSIZE);
				// テクスチャの割り当て
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(CTexture::TEX_UI_RANKING_1st + nCnt - 1)));
			}
		}
	}

	// スコアの生成
	for (int nCnt = 0; nCnt < RANKING_NUM; nCnt++)
	{
		// スコアの生成
		m_pRankScore[nCnt] = CMultiNumber::Create(
			D3DXVECTOR3((SCREEN_WIDTH * 0.6f), ((200.0f) + (100.0f * nCnt)) + RANKING_SPACE * nCnt+1, 0.0f),
			RANKINGSCORESIZE,
			m_nRankingScore[nCnt],
			RANKINGSCOREDIGITS,
			CScene::OBJTYPE_UI);

		// 描画許可
		m_pRankScore[nCnt]->SetDisp(true);
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
			m_apScene2D[nCnt]->Rerease();
			m_apScene2D[nCnt] = nullptr;

			// デリートフラグを有効にする
			SetDeleteFlag(true);
		}
	}

	for (int nCnt = 0; nCnt < RANKING_NUM; nCnt++)
	{
		if (m_pRankScore[nCnt] != nullptr)
		{
			m_pRankScore[nCnt]->Rerease();
			m_pRankScore[nCnt] = nullptr;
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

// =====================================================================================================================================================================
//
// ランキング情報の読み込み
//
// =====================================================================================================================================================================
void CRankingUI::RankingLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

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

															// ITEMSETが来たら
				if (strcmp(cHeadText, "RANKINGSET") == 0)
				{
					// END_ITEMSETが来るまでループ
					while (strcmp(cHeadText, "END_RANKINGSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

																	// SPEEDが来たら
						if (strcmp(cHeadText, "RANKING_1st") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_1st]);		// 比較用テキストにRANKIG_1stを代入
						}
						else if (strcmp(cHeadText, "RANKING_2nd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_2nd]);		// 比較用テキストにRANKIG_2ndを代入
						}
						else if (strcmp(cHeadText, "RANKING_3rd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_3rd]);		// 比較用テキストにRANKIG_3rdを代入
						}
						else if (strcmp(cHeadText, "RANKING_4th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_4th]);		// 比較用テキストにRANKIG_4thを代入
						}
						else if (strcmp(cHeadText, "RANKING_5th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_5th]);		// 比較用テキストにRANKIG_5thを代入
						}

						else if (strcmp(cHeadText, "END_RANKINGSET") == 0)
						{
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

	// 読み込んだ情報の代入
	SetRankingData();
}

// =====================================================================================================================================================================
//
// ランキングのセーブ
//
// =====================================================================================================================================================================
void CRankingUI::RankingSave()
{
	// ファイルポイント
	FILE	*pFile;

	// 各モデルファイルのファイルを開く
	pFile = fopen(m_RankingFileName, "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ランキングデータの情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "\n");

		fprintf(pFile, "SCRIPT\n\n");
		fprintf(pFile, "RANKINGSET\n");

		// セーブするランキングの情報
		fprintf(pFile, "	RANKING_1st	= %d\n", m_nRankingScore[SCORE_1st]);
		fprintf(pFile, "	RANKING_2nd	= %d\n", m_nRankingScore[SCORE_2nd]);
		fprintf(pFile, "	RANKING_3rd	= %d\n", m_nRankingScore[SCORE_3rd]);
		fprintf(pFile, "	RANKING_4th	= %d\n", m_nRankingScore[SCORE_4th]);
		fprintf(pFile, "	RANKING_5th	= %d\n", m_nRankingScore[SCORE_5th]);

		fprintf(pFile, "END_RANKINGSET\n\n");
		fprintf(pFile, "END_SCRIPT\n");


#ifdef _DEBUG
		// 読み込み成功時の結果表示
		MessageBox(NULL, "ランキング情報をセーブしました", "結果", MB_OK | MB_ICONINFORMATION);
#endif // DEBUG

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
#ifdef _DEBUG
		// 読み込み失敗時の警告表示
		MessageBox(NULL, "ランキング情報の読み込み失敗", "警告", MB_ICONWARNING);
#endif // DEBUG
	}
}

// =====================================================================================================================================================================
//
// ランキング順位の計算
//
// =====================================================================================================================================================================
void CRankingUI::RankingCalculation()
{
	// トータルスコアを取得をし書き換え不可能な変数にする
	BonusScoreLoad();
	const int CurrentScore = m_nScore;
	int nCnt = SCORE_5th;

	// 取得したスコアとランキングスコアを1位から比較し
	// 取得したスコアの方が大きかったら値を書き換える
	for (int nRank = 0; nRank < SCORE_MAX; nRank++)
	{
		if (CurrentScore >= m_nRankingScore[nRank])
		{
			if (nRank >= SCORE_5th)
			{
				m_nRankingScore[SCORE_5th] = CurrentScore;
			}
			else
			{
				while (nRank < nCnt)
				{
					m_nRankingScore[nCnt] = m_nRankingScore[nCnt - 1];
					nCnt--;
				}
				m_nRankingScore[nRank] = CurrentScore;
				break;
			}
		}
	}
}

// =====================================================================================================================================================================
//
//
//
// =====================================================================================================================================================================
void CRankingUI::ScoreSave()
{
	// ファイルポイント
	FILE	*pFile;

	// 各モデルファイルのファイルを開く
	pFile = fopen(m_SaveScoreFileName, "w");

	// 開いているとき
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# スコアの情報\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "\n");

		fprintf(pFile, "SCRIPT\n\n");
		fprintf(pFile, "SCORESET\n");

		// セーブするランキングの情報
		fprintf(pFile, "	SCORE	= %d\n", CResultUI::GetTotalScore());

		fprintf(pFile, "END_SCORESET\n\n");
		fprintf(pFile, "END_SCRIPT\n");


#ifdef _DEBUG
		// 読み込み成功時の結果表示
		MessageBox(NULL, "スコア情報をセーブしました", "結果", MB_OK | MB_ICONINFORMATION);
#endif // DEBUG

		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
#ifdef _DEBUG
		// 読み込み失敗時の警告表示
		MessageBox(NULL, "スコア情報の読み込み失敗", "警告", MB_ICONWARNING);
#endif // DEBUG
	}
}

// =====================================================================================================================================================================
//
//
//
// =====================================================================================================================================================================
void CRankingUI::BonusScoreLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

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

															// ITEMSETが来たら
				if (strcmp(cHeadText, "SCORESET") == 0)
				{
					// END_ITEMSETが来るまでループ
					while (strcmp(cHeadText, "END_SCORESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

																	// SPEEDが来たら
						if (strcmp(cHeadText, "SCORE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nTotalScore);		// 比較用テキストにRANKIG_1stを代入
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


	m_nScore = m_ScoreData.nTotalScore;
}

// =====================================================================================================================================================================
//
// 読み込んだスコアの反映
//
// =====================================================================================================================================================================
void CRankingUI::SetRankingData()
{
	// ランキングのスコアの情報を代入
	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_nRankingScore[nCnt] = m_RankingData.nRankingScore[nCnt];
	}
}

// =====================================================================================================================================================================
//
// 点滅処理
//
// =====================================================================================================================================================================
void CRankingUI::Flashing(CScene2D *m_apScene2D)
{
	// カウント加算
	m_nColCnt++;
	// 余りが0の時透明にする
	if (m_nColCnt % 60 == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// 余りが0の時通常状態にする
	else if (m_nColCnt % 30 == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
