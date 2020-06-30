//------------------------------------------------------------------------------
//
//ゲーム処理  [game.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "basemode.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
//前方宣言
class CMap;
class CPause;
class CScore;
class CTimer;
class CPlayer;
class CMultiNumber;

class CGame : public CBaseMode
{
public:
	//ゲームの状態遷移
	enum STATE
	{
		STATE_NONE = -1,				//始まってない
		STATE_READY,					//開始前の状態
		STATE_NORMAL,					//通常状態　信仰
		STATE_PAUSE,					//ポーズ状態
		STATE_GAMEOVER,					//ゲームオーバー
		STATE_GAMECLEAR,				//ゲームクリア

		STATE_DEBUG,
		STATE_MAX
	};

	CGame();
	~CGame();
	HRESULT Init(HWND hWnd);								//初期化
	void Uninit();											//終了
	void Update();											//更新
	void Draw();											//描画
	void ShowDebugInfo();									//デバッグ情報表記

	void SetGamestate(STATE gamestate);						//ゲームの状態設定

	STATE GetGamestate() { return m_gamestate; };			//ゲームの状態取得
	CMap *GetMap(); 										//マップ情報取得
	CScore *GetScore(); 									//スコアのポインタ
	CPlayer *GetPlayer(); 									//プレイヤーのポインタ取得z

private:
	std::unique_ptr<CMap> m_pMap;						//マップのポインタ
	std::unique_ptr<CScore> m_pScore;					//スコアのポインタ
	std::unique_ptr<CTimer> m_pTimer;					//タイマーのポインタ
	std::shared_ptr<CPause> m_pPause;					//ポーズへのポインタ
	std::shared_ptr<CPlayer> m_pPlayer;					//プレイヤーのポインタ

	STATE m_gamestate;					//ゲームステート
	int m_nCntState;					//ステートのカウンタ
	int m_nReadyCount;					//readyの時のカウント

	int m_nEnemyPopTime;				//敵出現カウント
	int m_nEnemuPopWave;				//敵出現のウェーブ
	void EnemyRespawn();				//敵出現
};

#endif