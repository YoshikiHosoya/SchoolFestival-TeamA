// =====================================================================================================================================================================
//
// プレイヤーUIの処理 [playerUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _PLAYERUI_H_
#define _PLAYERUI_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "UI.h"
#include "gun.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CScene2D;
class CMultiNumber;
class CPlayerGSUI;
// =====================================================================================================================================================================
// プレイヤーUIクラス
// =====================================================================================================================================================================
class CPlayerUI : CUI
{
public:
	// プレイヤーUIの種類
	enum PLAYER_UI
	{
		FRAME,						// 枠
		STOCK_LETTER,				// 残機		( 文字 )
		BULLET_AMMO_LETTER,			// 残弾数 ( 文字 )
		GRENADE_AMMO_LETTER,		// グレネードの残数 ( 文字 )
		LIFE_ICON,					// 体力アイコン
		INFINITY_AMMO,				// 弾数無限
		SCORE_GETLETTER,			// 入手したスコアの値
		PLAYER_UI_MAX
	};

	CPlayerUI();								// コンストラクタ
	~CPlayerUI();								// デストラクタ

	/* メンバ関数 */
	HRESULT				Init(void);				// 初期化
	void				Uninit(void);			// 終了
	void				Update(void);			// 更新
	void				Draw(void);				// 描画

	/* 静的メンバ関数 */
	static				CPlayerUI	*Create(CONTROLLER Controller);		// プレイヤーUIの生成

	/* メンバ関数 */
	void				SetScore(int nScore);				// スコアの設定
	void				SetItemScore(int nScore);			// アイテムスコアの設定

	void				SetBulletAmmo(int nBulletAmmo, CGun::GUN_TYPE GunType);		// 残弾数の設定
	void				SetGrenadeAmmo(int nGrenadeAmmo);	// グレネードの残数の設定
	void				SetLifeUI(int nLife);				// 体力UIの設定
	void				SetStockUI(int nStock);				// 残機の数の設定
	void				SetTimeUI(int nTime);				// 残り時間の設定

	int					GetScore() { return m_nScore; };	// スコアの取得
	int					GetTime() { return m_nTime; };		// 時間の取得
	int					GetStock() { return m_nStock; };	// 残機の取得
	void				DecrementTime();					// 時間の減少
	void				ResetTime();						// 時間のリセット
private:
	/* 静的メンバ関数 */

	/* メンバ関数 */
	void				PlayerUICreate(CONTROLLER Controller);	// プレイヤーUIの生成

	/* 静的メンバ変数 */

	/* メンバ変数 */
	CScene2D					*m_apScene2D[PLAYER_UI_MAX];	// シーン2Dのポインタ
	CPlayerGSUI					*m_pPGSUI;						// 表示スコアのポインタ
	CMultiNumber				*m_pScore;						// スコアのポインタ
	CMultiNumber				*m_pBulletAmmo;					// 残弾数のポインタ
	CMultiNumber				*m_pGrenadeAmmo;				// グレネードの残数のポインタ
	CMultiNumber				*m_pLife;						// 体力の残数のポインタ
	CMultiNumber				*m_pStock;						// 残機の数のポインタ
	CMultiNumber				*m_pTime;						// ゲームの残り時間
	int							m_nScore;						// スコア
	int							m_nBulletAmmo;					// 残弾数
	int							m_nGrenadeAmmo;					// グレネードの残数
	int							m_nLife;						// 体力
	int							m_nStock;						// 残機の数
	int							m_nTime;						// 残り時間

	float						m_P2_UI_FramePos;				// プレイヤー2の枠の位置
	float						m_P2_UI_ScorePos;				// プレイヤー2のスコアの位置
	float						m_P2_UI_LifePos;				// プレイヤー2の体力の位置
};
#endif