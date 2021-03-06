//------------------------------------------------------------------------------
//
//ゲームの進行管理  [GameManager.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CScene2D;

class CGameManager
{
public:

	enum class GAMESTATE
	{
		NORMAL = 0,
		WAVE,
		BOSSBUTTLE,
	};

	void Update();
	void Draw();

	CGameManager();
	~CGameManager();
	void ShowDebugInfo();						//デバッグ情報表記

	static std::unique_ptr<CGameManager> Create();

private:
	int			m_nCnt;					//カウント
	CScene2D	*m_pScene2D_GoSign;		//2Dポリゴン　Goサイン
	GAMESTATE	m_state;				//ゲームの状態
	int			m_nTimeCnt;				//時間のカウント
};

#endif