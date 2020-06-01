// ----------------------------------------
//
// マニュアル処理の説明[manual.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MANUAL_H_
#define _MANUAL_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene_two.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------

// ----------------------------------------
//
// 前方宣言
//
// ----------------------------------------

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CManual : public CScene
{
public:
	/* 関数 */
	CManual();
	~CManual();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);		// 読み込み
	static void UnLoad(void);		// UnLoadする
	static CManual * Create(void);	// 作成
protected:

private:
	/* 列挙型 */
	typedef enum
	{
		MANUAL_STATE_PAUSE = 0,	// 通常のポーズ画面
		MANUAL_STATE_MANUAL,	// 遊び方を表示する
	} MANUAL_STATE;

	typedef enum
	{
		MANUAL_SELECT_PAGE_CONTROLLER = 0,	// 操作説明
		MANUAL_SELECT_PAGE_ITEM,			// アイテム説明
		MANUAL_SELECT_PAGE_ABILITY,			// プレイヤーの能力説明
	} MANUAL_SELECT;

	typedef enum
	{
		MANUAL_TYPE_BG = 0,		// pause時の背景
		MANUAL_TYPE_PAUSEUI,	// pauseの文字
		MANUAL_TYPE_PAUSE,		// pauseの文字 pause画面へモード変更
		MANUAL_TYPE_MANUAL,		// 遊び方 文字 遊び方へモード変更
		MANUAL_TYPE_RESUME,		// 続ける の文字 ポーズを解除
		MANUAL_TYPE_GOTITLE,	// タイトルへ の文字 タイトルへ画面遷移
		MANUAL_TYPE_PICTURE,	// 遊び方を説明する画像
		MANUAL_TYPE_CROSSBUTTON,// 十字ボタン
		MANUAL_TYPE_ABUTTON,	// Aボタン 決定ボタン
		MANUAL_TYPE_MAX,
	} MANUAL_TYPE;

	/* 関数 */
	void Various(int nCnt);											// 種類別処理
																	/* 変数 */
	static LPDIRECT3DTEXTURE9 m_pTex[MANUAL_TYPE_MAX];	// テクスチャー設定
	static D3DXVECTOR3 m_pos[MANUAL_TYPE_MAX];			// 位置情報
	static D3DXVECTOR2 m_size[MANUAL_TYPE_MAX];			// サイズ情報

	CScene_TWO *m_aScene_Two[MANUAL_TYPE_MAX];			// チュートリアル用ui2D
	MANUAL_STATE m_ManualState;
	MANUAL_SELECT m_ManualSelect;
	int		m_nSelect;									// 選択番号
	int		m_nPauseCount;								// 選択番号
	int		m_nCntCol;									// カラーカウント
	float	m_fAnim;									// アニメーション
	float	m_fMult;									// 倍数
	float	m_fAdd;										// 加算
};

#endif