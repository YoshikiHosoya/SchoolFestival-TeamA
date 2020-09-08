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
class CPause;

class CGameManager
{
public:

	enum class GAMESTATE
	{
		NONE = 0,
		NORMAL,
		WAVE,
		RESULT,
		GAMEOVER,
		PAUSE,
	};

	void Update();
	void Draw();

	CGameManager();
	~CGameManager();
	void ShowDebugInfo();						//デバッグ情報表記
	static std::unique_ptr<CGameManager> Create();

	GAMESTATE GetGameState() { return m_state; };				//ステート取得
	GAMESTATE GetGameStateOld() { return m_stateOld; };			//前回のステート取得
	void SetGameState(GAMESTATE state);	//ステート設定
	void EventClear();											//イベントクリア
	void MapTransitionWaveSet(int nNextID);						//マップ遷移時にウェーブ設定

private:
	int			m_nCnt;							//カウント
	int			m_nWaveEnemyCnt;				//敵のフレームカウント
	int			m_nWavePrisonerCnt;				//捕虜のフレームカウント
	int			m_nWaveEnemyNum;				//ウェーブの敵のナンバー
	int			m_nWavePrisonerNum;				//ウェーブの捕虜のナンバー

	int			m_nNowWave;				//ウェーブ
	CScene2D	*m_pScene2D_GoSign;		//2Dポリゴン　Goサイン
	CScene2D	*m_pScene2D_GameOver;	//2Dポリゴン　ゲームオーバー
	CPause		*m_pPause;				//ポーズ

	GAMESTATE	m_state;				//ゲームの状態
	GAMESTATE	m_stateOld;				//前回のゲームの状態

	int			m_nTimeCnt;				//時間のカウント

	void StartWave();
	void UpdateWave();
	void EndWave();
	void UpdateGoSign();
	void UpdateTimer();
	void UpdateGameover();
	void PauseSet();					// ポーズ
};

#endif