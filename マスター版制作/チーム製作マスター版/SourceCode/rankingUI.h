// =====================================================================================================================================================================
//
// ランキングUIの処理 [rankingUI.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _RANKINGUI_H_
#define _RANKINGUI_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "UI.h"
#include <array>
#include "player.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define RANKING_NUM (7) //表示するランキングデータの数

// =====================================================================================================================================================================
// ランキングのデータ
// =====================================================================================================================================================================
struct RUNKING_DATA
{
	int					nScore[CPlayer::PLAYER_NUM_TWO];					// スコア
};

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CScene2D;
class CMultiNumber;

// =====================================================================================================================================================================
// ランキングUIクラス
// =====================================================================================================================================================================
class CRankingUI : CUI
{
public:
	// ランキングUIの種類
	enum RANKING_UI
	{
		RANKING_NAME,				// 名前ロゴ
		RANKING_1st,				// 順位1位
		RANKING_2nd,				// 順位2位
		RANKING_3rd,				// 順位3位
		RANKING_4th,				// 順位4位
		RANKING_5th,				// 順位5位
		RANKING_6th,				// 順位6位
		RANKING_7th,				// 順位7位
		RANKING_SCORE_1P,			// 2人プレイ用表示スコア
		RANKING_SCORE_2P,			// 2人プレイ用表示スコア
		RANKING_SCORE_TOTAL,		// 2人プレイ用表示スコア
		RANKING_SCORE_THANKS,		// 遊んでくれてありがとう
		RANKING_UI_MAX
	};

	// ランキングデータ
	enum RANKING_SCORE
	{
		SCORE_1st,					// 順位1位
		SCORE_2nd,					// 順位2位
		SCORE_3rd,					// 順位3位
		SCORE_4th,					// 順位4位
		SCORE_5th,					// 順位5位
		SCORE_6th,					// 順位6位
		SCORE_7th,					// 順位7位
		SCORE_MAX
	};

	// 2人プレイ用スコアデータ
	enum PLAYER_SCORE
	{
		PLAYER_SCORE_1P,				// 順位1位
		PLAYER_SCORE_2P,				// 順位2位
		PLAYER_SCORE_TOTAL,				// 合計スコア
		PLAYER_SCORE_MAX
	};

	// ランキングの評価ランク
	enum RANKING_EVALUATION
	{
		RANKING_EVALUATION_BEST,			// 最高評価 1
		RANKING_EVALUATION_SECONDBEDT,		// 評価	2から3位
		RANKING_EVALUATION_THIRDBEST,		// 評価 4から7位
		RANKING_EVALUATION_NONE,			// 評価無し
		RANKING_EVALUATION_MAXNUM			// 最大数
	};

	CRankingUI();							// コンストラクタ
	~CRankingUI();							// デストラクタ

	/* メンバ関数 */
	HRESULT					Init(void);		// 初期化
	void					Uninit(void);	// 終了
	void					Update(void);	// 更新
	void					Draw(void);		// 描画

	/* 静的メンバ関数 */
	static  CRankingUI		*Create();									// ランキングUIの生成
	static	void			PlayerScoreSave();							// プレイヤーのスコアをデーブ

	/* メンバ関数 */

private:
	/* 静的メンバ関数 */

	/* メンバ関数 */
	bool					ConfirmExistsRankingFile();					// ランキングファイルが存在するか確認
	void					RankingDataSave();							// ランキングのデータのセーブ
	void					RankingDataLoad();							// ランキングのデータのロード
	void					PlayerScoreLoad();							// プレイヤーのスコアをロード
	void					RankingCalculation();						// 順位の計算

	void					Flashing(CScene2D *m_apScene2D);			// 点滅処理
	void					BubbleSort(std::vector<int> &data);			// 優先度の入れ替え 高い順に0番目から
	bool					BubbleSort_Compare(std::vector<int> data);	// ランキングの値とスコアの値を比較

	bool					TargetValueAdd(const int &Target,
		int &Value,
		int Add,
		CMultiNumber *pMultiNumber);			// 目標の値になるまで値を計算する

	bool					TargetValueSubtract(const int &Target,
		int &Value,
		int Subtract,
		CMultiNumber *pMultiNumber);			// 目標の値になるまで値をマイナスに計算する

	void					RankUiCreate();
	void					RankScoreUiCreate();
	void					PlayerScoreUiCreate();

	void					RankingState();// ステートごとの評価
	void					RankingState_Draw_Score();
	void					RankingState_Score_Calculation();
	void					RankingState_Compare_Ranking();
	void					RankingState_Sort_Ranking();
	void					RankingState_Ranking();

	void					RankingEvaluation();// 順位ごとの評価



	/* 静的メンバ変数 */
	static char				*m_RankingFileName;							// ランキングのファイル名
	static char				*m_SaveScoreFileName;						// スコアのファイル名

	/* メンバ変数 */
	std::vector<int>		m_nRankingScore;							// 上位5位のランキング情報
	std::vector<int>		m_nPlayerScore;								// プレイヤーが獲得したスコア
	RUNKING_DATA			m_RunkingData;								// ランキングデータの構造体変数
	CScene2D				*m_apScene2D[RANKING_UI_MAX];				// シーン2Dのポインタ
	CMultiNumber			*m_pRankScore[RANKING_NUM];					// スコアのUI
	CMultiNumber			*m_pPlayerScore[PLAYER_SCORE_MAX];			// スコアのUI
	int						m_nColCnt;									// カラーカウント
	int						m_WaitTime;
	int						m_nRankNum;
	int						m_nTimeToExplosion;
	D3DXVECTOR3				m_RankScoreMove;
	int						m_nTimeToDraw;
	int						m_nTimeToFlash;
	int						m_nTimeToFireworks;


	int						m_nDrawCount;
	bool					m_bCompleted;
	bool					m_bCompletedEnd;

	bool					m_bMoveRank[SCORE_MAX];
	float					m_fCol;
	int						m_nTimeToTransition;
	bool					m_bEvaluation[3];
	bool					m_bRankingFail;
};
#endif