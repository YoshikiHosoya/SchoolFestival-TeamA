// =====================================================================================================================================================================
//
// ランキングUIの処理 [rankingUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _RANKINGUI_H_
#define _RANKINGUI_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "UI.h"

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CScene2D;

// =====================================================================================================================================================================
// ランキングUIクラス
// =====================================================================================================================================================================
class CRankingUI : CUI
{
public:
	// ランキングUIの種類
	enum RANKING_UI
	{
		RANKING,				// ランキング
		RANKING_UI_MAX
	};

	CRankingUI();							// コンストラクタ
	~CRankingUI();							// デストラクタ

	/* メンバ関数 */
	HRESULT					Init(void);		// 初期化
	void					Uninit(void);	// 終了
	void					Update(void);	// 更新
	void					Draw(void);		// 描画

	/* 静的メンバ関数 */
	static  CRankingUI		*Create();		// ランキングUIの生成

	/* メンバ関数 */

private:
	/* メンバ関数 */
	/* 静的メンバ変数 */

	/* メンバ変数 */
	CScene2D				*m_apScene2D[RANKING_UI_MAX];		// シーン2Dのポインタ
};
#endif