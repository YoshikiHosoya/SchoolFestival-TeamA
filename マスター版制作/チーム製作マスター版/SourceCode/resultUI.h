// =====================================================================================================================================================================
//
// リザルトUIの処理 [resultUI.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _RESULTUI_H_
#define _RESULTUI_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "UI.h"
#include "game.h"
#include "resultmanager.h"

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CScene2D;
class CMultiNumber;

// =====================================================================================================================================================================
// リザルトUIクラス
// =====================================================================================================================================================================
class CResultUI : CUI
{
public:
	// リザルトUIの種類
	enum RESULT_UI
	{
		RESULT_UI_BG,				// 背景
		RESULT_UI_NAME,				// リザルトの名前
		RESULT_UI_1P,				// 1プレイヤー
		RESULT_UI_2P,				// 2プレイヤー
		RESULT_UI_EVALUATION01P,	// 評価0
		RESULT_UI_EVALUATION11P,	// 評価1
		RESULT_UI_EVALUATION21P,	// 評価2
		RESULT_UI_EVALUATION02P,	// 評価0
		RESULT_UI_EVALUATION12P,	// 評価1
		RESULT_UI_EVALUATION22P,	// 評価2
		RESULT_UI_MISSIONCOMP1,		// ミッションクリア1
		RESULT_UI_MISSIONCOMP2,		// ミッションクリア2
		RESULT_UI_MAX
	};

	CResultUI();							// コンストラクタ
	~CResultUI();							// デストラクタ

	/* メンバ関数 */
	HRESULT					Init(void);		// 初期化
	void					Uninit(void);	// 終了
	void					Update(void);	// 更新
	void					Draw(void);		// 描画

	/* 静的メンバ関数 */
	static  CResultUI		*Create();									// リザルトUIの生成
	static	int				GetTotalScore() { return m_nTotalScore; };	// トータルスコアの取得
	static	void			TotalScoreCalculation();					// ゲームスコアとボーナススコアの計算

	/* メンバ関数 */

private:
	/* メンバ関数 */
	void					DrawConditions(CResultManager::RESULT_STATE state);	// 描画条件
	void					ResultUICreate();									// リザルトUIをまとめて生成する
	void					AllDraw();											// 全て描画
	void					AllNotDraw();										// 全て描画しない
	void					Result0Draw();										// 0番目のリザルトで表示するUIの設定
	void					Result1Draw();										// 1番目のリザルトで表示するUIの設定
	void					ScoreCal();											// マルチナンバーに値を代入
	void					Conditions();										// 条件によって処理を進める
	void					TargetValue(const int &Target,
										int &Value,
										int Add,
										CMultiNumber *pMultiNumber);			// 目標の値になるまで値を計算する

	void					SetWaitTime(int time) { m_nWaitTime = time; };		// 待ち時間の設定
	void					WaitTime(int nTime, bool &bFlag,bool &bUse);		// 待ち時間の計算
	void					ResultUiOrder(bool bUse0, bool bUse1, bool bUse2);	// Uiの出現順番
	void					Flashing(CScene2D *m_apScene2D);					// 点滅処理

	/* 静的メンバ変数 */
	static LPDIRECT3DTEXTURE9	m_TexNum[RESULT_UI_MAX];						// バインドするテクスチャの情報
	static D3DXVECTOR3			m_Pos[RESULT_UI_MAX];							// 座標情報
	static D3DXVECTOR3			m_Size[RESULT_UI_MAX];							// サイズ情報
	static int					m_nTotalScore;									// スコアとボーナスを加算したスコア
	static int					m_nBonusScore;									// ボーナススコア
	static int					m_PlayerScore;									// ゲームモードで稼いだスコア

	/* メンバ変数 */
	CScene2D				*m_apScene2D[RESULT_UI_MAX];						// シーン2Dのポインタ
	CMultiNumber			*m_pPrisonerNum;									// プレイヤーの残機の数のUI
	CMultiNumber			*m_pBonusScore;										// ボーナススコアのUI

	int						m_nPrisonerNum;										// プレイヤーの残機の数
	bool					m_bPrisonerNum;										// 捕虜の数を表示更新していいかどうか
	bool					m_bBonusScore;										// 追加得点を表示更新していいかどうか
	bool					m_bEvaluation;										// 評価を表示していいかどうか
	int						m_nWaitTime;										// 次の処理をするまでの時間
	bool					m_bWaitFlag;										// 待ち時間が発生した際に使うフラグ
	int						m_nColCnt;											// カラーカウント

	bool					m_bUseUIFlag[3];									// UIを出現させるためのフラグ 3行程あるため
	bool					m_bUse_One[3];										// 処理を1度だけ通すためのフラグ
};
#endif