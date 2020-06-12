// =====================================================================================================================================================================
//
// ゲームの処理 [game.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

// =====================================================================================================================================================================
// 前方宣言	( ポインタだけなら使える )
// =====================================================================================================================================================================
class	CManager;				// マネージャークラス
class	CScore;					// スコアクラス
class	CScene3D;				// シーン3Dクラス
class	CSlope;					// 坂クラス
class	CPlayer;				// プレイヤークラス
class	CObjectModel;			// オブジェクトクラス
class	CEffect;				// エフェクトクラス
class	CGameUI;				// ゲームUIクラス
class	CItem;					// アイテムクラス
class	CObject2D;				// 2Dオブジェクトクラス

// =====================================================================================================================================================================
// ゲームクラス
// =====================================================================================================================================================================
class CGame
{
public:

	// ゲームモード
	enum GAME_MODE
	{
		GAME_MODE_NONE = -1,
		GAME_MODE_MAIN,											// メイン
		GAME_MODE_END,											// ゲームエンド
		GAME_MODE_CLEAR,										// クリア
		GAME_MODE_MAX,
	};

	CGame();													// コンストラクタ
	~CGame();													// デストラクタ

	/* メンバ関数 */
	HRESULT					Init();								// 初期化
	void					Uninit();							// 終了
	void					Update();							// 更新
	void					Draw();								// 描画

	/* 静的メンバ関数 */
	static	CGame			*Create();							// ゲームクラスの生成
	static	CScore			*GetScore();						// スコアの取得
	static	CScene3D		*GetScene3D();						// シーン3Dの取得
	static	CSlope			*GetSlope();						// 坂の取得
	static	CPlayer			*GetPlayer();						// プレイヤーの取得
	static	CItem			*GetItemModel();					// アイテムの取得
	static	CEffect			*GetEffect();						// エフェクトの取得
	static	CGameUI			*GetGameUI();						// ゲームUIの取得
	static	GAME_MODE		GetGameMode();						// ゲームモードの取得

	/* メンバ関数 */
	void					SetGameMode(GAME_MODE GameMode)		{ m_GameMode = GameMode; };	// ゲームモードの設定

private:
	/* メンバ関数 */
	void					LoadAll();							// 全て読み込み
	void					UnloadAll();						// すべて破棄
	/* 静的メンバ変数 */
	static  CScore			*m_pScore;							// スコアクラスのポインタ
	static	CSlope			*m_pSlope;							// 坂のポインタ
	static	CScene3D		*m_pScene3D;						// シーン3Dのポインタ
	static	CPlayer			*m_pPlayer;							// プレイヤーのポインタ
	static	CObjectModel	*m_pObjectModel;					// オブジェクトモデルのポインタ
	static	CItem			*m_pItem;							// アイテムのポインタ
	static	CEffect			*m_pEffect;							// エフェクトのポインタ
	static  CGameUI			*m_pGameUI;							// ゲームクラスのポインタ
	static  CObject2D		*m_pObject2D;						// 2Dオブジェクトのポインタ
	/* メンバ変数 */
	int						m_nCntTransition;					// 遷移するまでの時間
	static	GAME_MODE		m_GameMode;							// ゲームモード
	bool					m_bDisplayGameEndUI;				// ゲームエンドUIの表示フラグ
};
#endif
