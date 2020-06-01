// ------------------------------------------
//
// ゲームヘッダー処理 [game.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
//
// インクルードファイル
//
// ------------------------------------------
#include "main.h"
#include "pause.h"

// ------------------------------------------
//
// マクロ定義
//
// ------------------------------------------

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------
class CPause;
class CPlayer;
class CGauge;
class CTime;

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class CGame
{
public:
	/* 列挙型 */
	typedef enum
	{
		STATE_NORMAL,
		STATE_START,
		STATE_CLEAR,
		STATE_GAMEOVER,
		STATE_PAUSE,
		STATE_MAX
	} STATE;
	/* 関数 */
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static STATE GetState(void);					// 状態の取得
	static int GetStage(void);						// ステージ取得
	static void SetState(STATE state);				// 状態設定

protected:
private:
	static CPlayer	*m_pPlayer;
	static STATE m_state;	// 状態
	static int m_nStage;	// ステージ
	CPause	*m_pPause;	// ポーズの状態
	int m_Shard;
};
#endif
