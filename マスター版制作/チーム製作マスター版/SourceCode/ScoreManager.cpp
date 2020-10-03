// =====================================================================================================================================================================
//
// スコアマネージャーの処理 [scoremanager.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"
#include "scoremanager.h"
#include "manager.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
int CScoreManager::m_nScore[SCORE_TYPE_MAX]		= {};
SCORE_DATA	CScoreManager::m_ScoreData			= {};

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CScoreManager::m_ScoreFileName =
{
	"data/Load/Score/ScoreData.txt" 			// スコアの情報
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CScoreManager::CScoreManager()
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CScoreManager::~CScoreManager()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CScoreManager::Init(void)
{
	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CScoreManager::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CScoreManager::Update(void)
{
}

// =====================================================================================================================================================================
//
// アイテムの情報の設定
//
// =====================================================================================================================================================================
void CScoreManager::SetScoreData()
{
	m_nScore[SCORE_ITEM_FRUIT]			 = m_ScoreData.nFruit;
	m_nScore[SCORE_ITEM_FOOD]			 = m_ScoreData.nFood;
	m_nScore[SCORE_ITEM_GCOIN]			 = m_ScoreData.nGoldCoin;
	m_nScore[SCORE_ITEM_SCOIN]			 = m_ScoreData.nSilverCoin;
	m_nScore[SCORE_ITEM_BCOIN]			 = m_ScoreData.nBronzeCoin;
	m_nScore[SCORE_ITEM_BEAR]			 = m_ScoreData.nBear;
	m_nScore[SCORE_ITEM_LETTER]			 = m_ScoreData.nLetter;
	m_nScore[SCORE_ITEM_DIAMOND]		 = m_ScoreData.nDiamond;

	m_nScore[SCORE_ITEM_ANI_BEAR]		 = m_ScoreData.nAni_Bear;
	m_nScore[SCORE_ITEM_ANI_COIN]		 = m_ScoreData.nAni_Coin;
	m_nScore[SCORE_ITEM_ANI_FOOD]		 = m_ScoreData.nAni_Food;
	m_nScore[SCORE_ITEM_ANI_LETTER]		 = m_ScoreData.nAni_Letter;
	m_nScore[SCORE_ITEM_ANI_MEDAL]		 = m_ScoreData.nAni_Jewelry;
	m_nScore[SCORE_ITEM_ANI_JEWELRY]	 = m_ScoreData.nAni_Medal;
	m_nScore[SCORE_ITEM_ANI_MONKEY]		 = m_ScoreData.nAni_Monkey;

	m_nScore[SCORE_DAMAGE_BULLET]		 = m_ScoreData.nBullet;
	m_nScore[SCORE_DAMAGE_ATTACK]		 = m_ScoreData.nAttack;
	m_nScore[SCORE_RESCUE_PRISONER]		 = m_ScoreData.nPrisoner;
	m_nScore[SCORE_BONUS]				 = m_ScoreData.nBonus;
	m_nScore[SCORE_KILLED_BOSS]			 = m_ScoreData.nBoss;
}

// =====================================================================================================================================================================
//
// スコアのデータの読み込み
//
// =====================================================================================================================================================================
void CScoreManager::ScoreLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

									// ファイルを開く
	pFile = fopen(m_ScoreFileName, "r");

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
						if (strcmp(cHeadText, "FRUIT") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nFruit);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "FOOD") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nFood);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "GCOIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nGoldCoin);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "SCOIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nSilverCoin);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "BCOIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBronzeCoin);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "BEAR") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBear);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "LETTER") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nLetter);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "DIAMOND") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nDiamond);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "ANI_BEAR") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Bear);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "ANI_COIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Coin);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "ANI_FOOD") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Food);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "ANI_LETTER") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Letter);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "ANI_MEDAL") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Jewelry);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "ANI_JEWELRY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Medal);	// 比較用テキストにBEARを代入
						}
						if (strcmp(cHeadText, "ANI_MONKEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Monkey);	// 比較用テキストにBEARを代入
						}

						// BEARが来たら
						else if (strcmp(cHeadText, "BULLET") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBullet);	// 比較用テキストにBULLETを代入
						}
						// BEARが来たら
						else if (strcmp(cHeadText, "ATTACK") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAttack);	// 比較用テキストにATTACKを代入
						}
						// BEARが来たら
						else if (strcmp(cHeadText, "PRISONER") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nPrisoner);// 比較用テキストにPRISONERを代入
						}
						// BEARが来たら
						else if (strcmp(cHeadText, "BONUS") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBonus);	// 比較用テキストにBONUSを代入
						}
						// BEARが来たら
						else if (strcmp(cHeadText, "BOSS") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBoss);	// 比較用テキストにBOSSを代入
						}
						else if (strcmp(cHeadText, "END_SCORESET") == 0)
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
		MessageBox(NULL, "スコアのデータ読み込み失敗", "警告", MB_ICONWARNING);
	}

	// 読み込んだ情報の代入
	SetScoreData();
}
