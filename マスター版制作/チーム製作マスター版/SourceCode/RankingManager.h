// =====================================================================================================================================================================
//
// ランキングマネージャーの処理 [ranking.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _RANKINGMANAGER_H_
#define _RANKINGMANAGER_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CRankingUI;
// =====================================================================================================================================================================
// リザルトUIクラス
// =====================================================================================================================================================================
class CRankingManager
{
public:
	// ランキングの種類
	enum RANKING_STATE
	{
		RANKING_STATE_DRAW_SCORE,
		RANKING_STATE_SCORE_CALCULATION,
		RANKING_STATE_COMPARE_RANKING,
		RANKING_STATE_SORT_RANKING,
		RANKING_STATE_RANKING,
		RANKING_STATE_WAITTIME,
	};
	CRankingManager();						// コンストラクタ
	~CRankingManager();						// デストラクタ

	/* メンバ関数 */
	HRESULT					Init(void);		// 初期化
	void					Uninit(void);	// 終了
	void					Update(void);	// 更新

	/* 静的メンバ関数 */
	static					CRankingManager	*Create();						// 生成
	/* メンバ関数 */
	void					RankingUiOrder();								// Uiの出現順番
	static RANKING_STATE	GetRankingState() {return m_RankingState;};
	static void				SetRankingState(RANKING_STATE state) { m_RankingState = state; };
	static RANKING_STATE	GetRankingStateOld() { return m_RankingStateOld; };
	static void				SetRankingStateOld(RANKING_STATE state) { m_RankingStateOld = state; };

private:
	/* 静的メンバ変数 */
	static RANKING_STATE			m_RankingState;									// ランキング状態
	static RANKING_STATE			m_RankingStateOld;								// 1つ前の状態

	/* メンバ関数 */
	/* メンバ変数 */
	CRankingUI				*m_pRankingUI;									// ランキングUIのポインタ
};
#endif