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

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define RANKING_NUM (5)

// =====================================================================================================================================================================
// ランキングのデータ
// =====================================================================================================================================================================
typedef struct
{
	std::array<int, RANKING_NUM> nRankingScore;     // 上位5位のランキング情報
	//int					nRankingScore[RANKING_NUM];	// 上位5位のランキング情報
}RANKING_DATA;

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
		RANKING_UI_MAX
	};

	// ランキング
	enum RANKING_SCORE
	{
		SCORE_1st,				// 順位1位
		SCORE_2nd,				// 順位2位
		SCORE_3rd,				// 順位3位
		SCORE_4th,				// 順位4位
		SCORE_5th,				// 順位5位
		SCORE_MAX
	};

	CRankingUI();							// コンストラクタ
	~CRankingUI();							// デストラクタ

	/* メンバ関数 */
	HRESULT					Init(void);		// 初期化
	void					Uninit(void);	// 終了
	void					Update(void);	// 更新
	void					Draw(void);		// 描画

	/* 静的メンバ関数 */
	static  CRankingUI		*Create();							// ランキングUIの生成
	static	void			RankingLoad();						// ランキングのロード
	static	void			RankingSave();						// ランキングのセーブ
	static	void			RankingCalculation();				// 順位の計算

	/* メンバ関数 */

private:
	/* 静的メンバ関数 */
	static void				SetRankingData();					// 読み込んだデータの設定

	/* メンバ関数 */
	void					Flashing(CScene2D *m_apScene2D);					// 点滅処理

	/* 静的メンバ変数 */
	static int				m_nRankingScore[RANKING_NUM];		// 上位5位のランキング情報
	static char				*m_RankingFileName;					// ランキングのファイル名
	static RANKING_DATA		m_RankingData;						// ランキングのデータ


	/* メンバ変数 */
	CScene2D				*m_apScene2D[RANKING_UI_MAX];		// シーン2Dのポインタ
	CMultiNumber			*m_pRankScore[RANKING_NUM];			// スコアのUI
	int						m_nColCnt;							// カラーカウント

	//std::array<int, SCORE_MAX> ranking;       // ローカル変数として、ar を生成
	//for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	//{
	//	ranking[nCnt] = m_nRankingScore[nCnt];
	//}
};
#endif