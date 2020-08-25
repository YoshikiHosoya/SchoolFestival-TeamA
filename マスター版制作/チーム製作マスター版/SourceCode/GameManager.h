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
		RESULT,
	};

	void Update();
	void Draw();

	CGameManager();
	~CGameManager();
	void ShowDebugInfo();						//デバッグ情報表記
	static std::unique_ptr<CGameManager> Create();

	GAMESTATE GetGameState() { return m_state; };
	void SetGameState(GAMESTATE state) { m_state = state; };
	void EventClear();

private:
	int			m_nCnt;							//カウント
	int			m_nWaveEnemyCnt;				//敵のフレームカウント
	int			m_nWavePrisonerCnt;				//捕虜のフレームカウント
	int			m_nWaveEnemyNum;				//ウェーブの敵のナンバー
	int			m_nWavePrisonerNum;				//ウェーブの捕虜のナンバー

	int			m_nNowWave;				//ウェーブ
	CScene2D	*m_pScene2D_GoSign;		//2Dポリゴン　Goサイン
	GAMESTATE	m_state;				//ゲームの状態
	int			m_nTimeCnt;				//時間のカウント

	void StartWave();
	void UpdateWave();
	void EndWave();
	void UpdateGoSign();
	void UpdateTimer();
};

#endif