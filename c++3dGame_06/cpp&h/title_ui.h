// ----------------------------------------
//
// タイトルUI処理の説明[title_ui.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TITLE_UI_H_
#define _TITLE_UI_H_	 // ファイル名を基準を決める

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
class CMark;
class CSelectMark;

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CTitle_ui : public CScene
{
public:
	/* 列挙 */
	typedef enum
	{
		TITLESELECT_NEWGAME = 0,	//1つめを選択中
	} TITLESELECT;

	/* 関数 */
	CTitle_ui();
	~CTitle_ui();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);			// 読み込み
	static void UnLoad(void);			// UnLoadする
	static CTitle_ui * Create(void);	// 作成
	static bool GetFlag(void);			// フラグの消滅フラグの取得
	void SetTitleModeDown(void);			// タイトルモードを設定
	void SetTitleModeUp(void);			// タイトルモードを設定
	void TitleMode(void);				// 選択されたモードの処理
	TITLESELECT GetSelect(void);

protected:

private:
	/* 列挙型 */
	typedef enum
	{
		TITLE_UI_NAME = 0,		// タイトルロゴ
		TITLE_UI_NEWGAME,		// newgameロゴ
		TITLE_UI_MAX
	} TITLE_UI;

	/* 関数 */
	void Various(int nCnt);								// 種類別処理
	void Transparency(int nCnt);						// 透明化

	/* 変数 */
	static LPDIRECT3DTEXTURE9 m_pTex[TITLE_UI_MAX];		// テクスチャー設定
	static D3DXVECTOR3 m_pos[TITLE_UI_MAX];				// 位置情報
	static D3DXVECTOR2 m_size[TITLE_UI_MAX];			// サイズ情報
	static TITLE_UI m_type[TITLE_UI_MAX];				// uiの種類
	TITLESELECT m_Select;
	float	m_fMult;									// 倍数
	float	m_fAdd;										// 加算
	D3DXCOLOR m_Col;									// カラー
	static bool	m_bUse;									// タイトルUIが存在しているかどうか
	bool m_bCol_a;										//
	CScene_TWO *m_aScene_Two[TITLE_UI_MAX];				// ポーズ用ui2D
	static CSelectMark *m_pSelectMark;					//目印
};

#endif