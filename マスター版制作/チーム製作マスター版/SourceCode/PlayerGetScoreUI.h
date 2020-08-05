// =====================================================================================================================================================================
//
// 取得スコアの表示処理 [playergetscoreui.h]
// Author : Fujiwara Masato
//
// =====================================================================================================================================================================
#ifndef _PLAYERGSUI_H_
#define _PLAYERGSUI_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "UI.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class C3DMultiNumber;

// =====================================================================================================================================================================
// プレイヤーUIクラス
// =====================================================================================================================================================================
class CPlayerGSUI : CUI
{
public:

	CPlayerGSUI();													// コンストラクタ
	~CPlayerGSUI();													// デストラクタ

	/* メンバ関数 */
	HRESULT				Init(void);									// 初期化
	void				Uninit(void);								// 終了
	void				Update(void);								// 更新
	void				Draw(void);									// 描画

	/* 静的メンバ関数 */
	static				CPlayerGSUI	*Create(int nScore);			// 獲得したスコア表示UIの生成
	static				void		Set_Score_Value(int nValue);	// スコアの値の取得

	/* メンバ関数 */
private:
	/* 静的メンバ関数 */
	static	void				Set_Get_Score(int nScore);					// スコアの設定
	/* メンバ関数 */
	void						ScoreDataInitialize();						// 構造体の初期化
	void						Flashing(C3DMultiNumber *m_pMultiNumber);	// 点滅処理
	void						GetScoreUICreate();							// 獲得したスコア表示UIの生成
	void						Move();										// UIの移動用関数

	/* 静的メンバ変数 */
	static	int					m_nDigits;									// 桁数
	static	int					m_nGetScore;								// 得点を取得した際の点数

	/* メンバ変数 */
	C3DMultiNumber				*m_pGetScore;								// 得点を取得した際の点数のポインタ
	int							m_nTime;									// 存在できる時間
	int							m_nCalCnt;									// 点滅用時間
	float						m_fmove;									// 移動量
};
#endif