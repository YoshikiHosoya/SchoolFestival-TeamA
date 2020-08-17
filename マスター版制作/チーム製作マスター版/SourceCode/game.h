// =====================================================================================================================================================================
//
// ゲームの処理 [game.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "BaseMode.h"

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CRenderer;
class CKeyboard;
class CPlayer;
class CPause;
class CMap;
class CResultManager;
class CGameManager;
class CShield;
// =====================================================================================================================================================================
// ゲームクラス
// =====================================================================================================================================================================
class CGame :public CBaseMode
{
public:
	// ゲームモード
	enum GAME_STATE
	{
		GAME_MODE_NORMAL,		// 通常のゲームプレイ状態
		GAME_MODE_RESULT,		// リザルト表示状態
	};

	/* メンバ関数 */
	CGame();
	~CGame();
	HRESULT		Init(void);
	void		Uninit(void);
	void		Update(void);
	CPlayer		*GetPlayer(void);
	CMap		*GetMap(void);

	GAME_STATE	GetGameMode()					{ return m_GameState; };
	void		SetGameMode(GAME_STATE mode)	{ m_GameState = mode; };
	CResultManager *GetResultManager()			{ return m_pResultManager; };

	void Draw(void);							//描画
	void ShowDebugInfo(void);					//デバッグ情報表記


private:
	/* メンバ関数 */
	void DebugCollision(CKeyboard *key);		// デバッグ用当たり判定の可視化on off
	void DebugItem(CKeyboard *key);				// デバッグ用アイテム

	/* 静的メンバ変数 */
	static LPDIRECT3DTEXTURE9			m_pTexture;
	static CPlayer						*m_pPlayer;
	static CMap							*m_pMap;
	static int							m_Counter;

	/* メンバ変数 */
	CPause								*m_pPause;
	GAME_STATE							m_GameState;
	CResultManager						*m_pResultManager;
	std::unique_ptr<CGameManager>		m_pGameManager;			//ゲームの進行管理
	int									m_nFrame;
	int									m_nCntNum;
	bool								m_bEventFlag;
	CShield								*m_pShield;
};
#endif