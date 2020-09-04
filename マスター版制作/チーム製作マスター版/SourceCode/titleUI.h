// =====================================================================================================================================================================
//
// タイトルUIの処理 [titleUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _TITLEUI_H_
#define _TITLEUI_H_

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
// タイトルUIクラス
// =====================================================================================================================================================================
class CTitleUI : CUI
{
public:
	// タイトルUIの種類
	enum TITLE_UI
	{
		TITLE_LOGO,				// タイトルロゴ
		UI_START,				// スタート
		UI_BULLETHOLE_1,		// 弾痕1
		UI_BULLETHOLE_2,		// 弾痕2
		UI_BULLETHOLE_3,		// 弾痕3
		UI_PLAYER_COUNT_1,		// プレイ人数選択1
		UI_PLAYER_COUNT_2,		// プレイ人数選択2
		UI_ARROWMARK,			// 人数選択用矢印
		TITLE_UI_MAX
	};

	CTitleUI();								// コンストラクタ
	~CTitleUI();							// デストラクタ

	/* メンバ関数 */
	HRESULT					Init(void);		// 初期化
	void					Uninit(void);	// 終了
	void					Update(void);	// 更新
	void					Draw(void);		// 描画

	/* 静的メンバ関数 */
	static  CTitleUI		*Create();		// タイトルUIの生成

	/* メンバ関数 */
	void					Flashing(CScene2D *m_apScene2D);	// 点滅処理
	void					SetDrawFlag(int nNum, bool bDraw);
	void					SetPos(TITLE_UI Num, D3DXVECTOR3 pos);

private:
	/* メンバ関数 */
	/* 静的メンバ変数 */
	/* 静的メンバ変数 */
	static LPDIRECT3DTEXTURE9	m_TexNum[TITLE_UI_MAX];		// バインドするテクスチャの情報
	static D3DXVECTOR3			m_Pos[TITLE_UI_MAX];		// 座標情報
	static D3DXVECTOR3			m_Size[TITLE_UI_MAX];		// サイズ情報

	/* メンバ変数 */
	CScene2D				*m_apScene2D[TITLE_UI_MAX];		// シーン2Dのポインタ
	int						m_nColCnt;						// カラーカウント
	bool					m_bDrawFlag[TITLE_UI_MAX];		// 演出用の描画フラグ
};
#endif