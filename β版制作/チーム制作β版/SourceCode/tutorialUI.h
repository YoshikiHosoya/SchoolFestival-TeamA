// =====================================================================================================================================================================
//
// チュートリアルUIの処理 [tutorialUI.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _TUTORIALUI_H_
#define _TUTORIALUI_H_

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
class CScene2D;
class CMultiNumber;

// =====================================================================================================================================================================
// チュートリアルUIクラス
// =====================================================================================================================================================================
class CTutorialUI : CUI
{
public:
	// チュートリアルUIの種類
	enum TUTORIAL_UI
	{
		UI_NAME,			// 名前ロゴ HOW TO PLAY
		UI_ORDER0,			// 操作について
		UI_ORDER1,			// 指令1
		UI_ORDER2,			// 指令2
		UI_ORDER3,			// 指令3
		UI_ORDER4,			// 指令4
		UI_ORDER5,			// 指令5
		UI_ORDER6,			// 指令6
		UI_MAX
	};

	CTutorialUI();							// コンストラクタ
	~CTutorialUI();							// デストラクタ

	/* メンバ関数 */
	HRESULT					Init(void);		// 初期化
	void					Uninit(void);	// 終了
	void					Update(void);	// 更新
	void					Draw(void);		// 描画

	/* 静的メンバ関数 */
	static  CTutorialUI		*Create();							// ランキングUIの生成

	/* メンバ関数 */

private:
	/* 静的メンバ関数 */

	/* メンバ関数 */
	void					Flashing(CScene2D *m_apScene2D);	// 点滅処理

	/* 静的メンバ変数 */
	static LPDIRECT3DTEXTURE9	m_TexNum[UI_MAX];		// バインドするテクスチャの情報
	static D3DXVECTOR3			m_Pos[UI_MAX];			// 座標情報
	static D3DXVECTOR3			m_Size[UI_MAX];			// サイズ情報

	/* メンバ変数 */
	CScene2D				*m_apScene2D[UI_MAX];			// シーン2Dのポインタ
	int						m_nColCnt;							// カラーカウント
};
#endif