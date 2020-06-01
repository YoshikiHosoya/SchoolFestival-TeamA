// ----------------------------------------
//
// ゲームUI処理の説明[game_ui.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _GAME_UI_H_
#define _GAME_UI_H_	 // ファイル名を基準を決める

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
#define MAX_GAME_UI (GAME_UI_MAX)
#define MAX_GAME_UI_TEX (6)

#define GAME_UI_SIZE_X (80)
#define GAME_UI_SIZE_Y (80)

#define ACTIONBUTTON_SIZE_X (500)
#define ACTIONBUTTON_SIZE_Y (50)


#define ABILITYPOINT (10)
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
class CGame_ui : public CScene
{
public:
	/* 関数 */
	CGame_ui();
	~CGame_ui();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);		// 読み込み
	static void UnLoad(void);		// UnLoadする
	static CGame_ui * Create(void);	// 作成
	static void SetAP(int number);						// アビリティ―ポイントの加算減算
	static bool GetbUse();
protected:

private:
	/* 列挙型 */
	typedef enum
	{
		/* タイトルプレイ中には出現しないUI */
		GAME_UI_KEY0 = 0,
		GAME_UI_KEY1,
		GAME_UI_KEY2,
		GAME_UI_LOCK0,
		GAME_UI_LOCK1,
		GAME_UI_LOCK2,
		GAME_UI_ACTIONBUTTON,
		GAME_UI_MISSION0,
		GAME_UI_MISSION1,
		GAME_UI_MAP,
		GAME_UI_MAX
	} GAME_UI;

	/* 関数 */
	void ConditionalDraw(int nCnt);						// 描画条件
	static void SetDrawFlag(int nCnt);					// 描画判別
	void Various();										// 種類別処理

														/* 変数 */
	static LPDIRECT3DTEXTURE9 m_pTex[MAX_GAME_UI_TEX];				// テクスチャー設定
	static D3DXVECTOR3 m_pos[MAX_GAME_UI];				// 位置情報
	static D3DXVECTOR2 m_size[MAX_GAME_UI];				// サイズ情報
	static bool m_bUse[MAX_GAME_UI];					// サイズ情報

	CScene_TWO *m_aScene_Two[MAX_GAME_UI];				// チュートリアル用ui2D
	int		m_nSelect;									// 選択番号
	int		m_nCntCol;									// カラーカウント
	float	m_fAnim;									// アニメーション
	float	m_fMult;									// 倍数
	float	m_fAdd;										// 加算

	static int		m_nAP;								// アビリティ―ポイント
};

#endif