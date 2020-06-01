// ------------------------------------------
//
// マネージャー処理の説明[manager.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_	 // ファイル名を基準を決める

// ------------------------------------------
//
// インクルードファイル
//
// ------------------------------------------
/* 基本 */
#include "main.h"
#include "Calculation.h"

/* 描画 */
#include "renderer.h"

/* 入力デバイス */
#include "keyboard.h"
#include "joypad.h"
#include "mouse.h"

/* サウンド */
#include "sound.h"

// ------------------------------------------
//
// マクロ関数
//
// ------------------------------------------
#define ONEPLAYER_STAGE (5)
#define DOUBLEPLAYER_STAGE (5)

#define ONEMIN			(60)		// 1分
#define HALF			(0.5f)		// 半分
#define ONE				(1.0f)		// 1
#define ONEFRAME		(6)			// 1フレーム

#define COLOR_RED		(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// 赤色
#define COLOR_GREEN		(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))	// 緑色
#define COLOR_BLUE		(D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))	// 青色
#define COLOR_PURPLE	(D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))	// 紫色
#define COLOR_YELLOW	(D3DXCOLOR(0.0f,1.0f,1.0f,1.0f))	// 水色
#define COLOR_WATER		(D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))	// 黄色
#define COLOR_BLACK		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// 黒色
#define COLOR_WHITE		(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))	// 白色

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------
class CFade;		// 画面遷移
class CTitle;		// タイトル
class CTutorial;	// チュートリアル
class CGame;		// ゲーム
//class CRanking;		// ランキング

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CManager
{
public:
	/* 列挙型 */
	// モード
	typedef enum
	{
		MODE_GAME = 0,
		MODE_TITLE,
		//MODE_RANKING,
		MODE_MAX
	} MODE;
	// プレイ番号
	typedef enum
	{
		PLAYER_1 = 0,
		PLAYER_2,
		PLAYER_MAX
	} PLAYER;
	/* 関数 */
	CManager();
	~CManager();
	HRESULT  Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);				// モード設定
	static CRenderer * GetRenderer(void);		// レンダリングの取得
	static CKeyboard * GetKeyboard(void);		// キーボードの取得
	static CJoypad * GetJoy(void);				// ジョイパッドの取得
	static CMouse * GetMouse(void);				// マウスの取得
	static CSound * GetSound(void);				// サウンドの取得
	static CFade * GetFade(void);				// 画面遷移の取得
	static CGame * GetGame(void);				// ゲームの取得
	static CTutorial * GetTutorial(void);		// チュートリアル取得
	static CTitle * GetTitle(void);				// タイトルの取得
	//static CRanking * GetRanking(void);			// ランキングの取得
	static MODE GetMode(void);					// モードの取得
protected:

private:
	// ゲームに欠かせないもの
	static CRenderer * m_renderer;			// レンダリング
	static CSound * m_sound;				// サウンド

	// 入力デバイス
	static CKeyboard * m_keyboard;			// キーボード
	static CJoypad * m_joypad;				// ジョイパッド
	static CMouse * m_mouse;				// マウス

	// 画面
	static CFade * m_fade;					// 画面遷移
	static CTitle * m_title;				// タイトル
	static CGame * m_game;					// ゲーム
	static CTutorial * m_tutorial;			// チュートリアル
	//static CRanking * m_ranking;			// ランキング

	static MODE m_mode;						// モード
	static bool	m_bWire;						// ワイヤーモード
};

#endif // !_MANAGER_H_