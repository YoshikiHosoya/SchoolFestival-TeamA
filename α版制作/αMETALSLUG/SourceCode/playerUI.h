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
#include "scene2D.h"

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CScene2D;
class CMultiNumber;

// =====================================================================================================================================================================
// プレイヤーUIクラス
// =====================================================================================================================================================================
class CPlayerUI
{
public:
	// プレイヤーUIの種類
	enum PLAYER_UI
	{
		REMAIN_LETTER,				// 残機		( 文字 )
		BULLET_AMMO_LETTER,			// 弾の残数 ( 文字 )
		GRENADE_AMMO_LETTER,		// グレネードの残数 ( 文字 )
		LIFE_ICON,					// 体力アイコン
		PLAYER_UI_MAX
	};

	CPlayerUI();								// コンストラクタ
	~CPlayerUI();								// デストラクタ

	/* メンバ関数 */
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	/* 静的メンバ関数 */
	static  CPlayerUI	*Create();				// プレイヤーUIの生成

	/* メンバ関数 */
	void				SetScore(int nScore);				// スコアの設定
	void				SetBulletAmmo(int nBulletAmmo);		// 弾の残数の設定
	void				SetGrenadeAmmo(int nGrenadeAmmo);	// グレネードの残数の設定
	int					GetScore() { return m_nScore; };	// スコアの取得

private:
	/* メンバ関数 */

	/* 静的メンバ変数 */

	/* メンバ変数 */
	CScene2D					*m_apScene2D[PLAYER_UI_MAX];	// シーン2Dのポインタ
	CMultiNumber				*m_pScore;						// マルチナンバーのポインタ
	CMultiNumber				*m_pBulletAmmo;					// 弾の残数のポインタ
	CMultiNumber				*m_pGrenadeAmmo;				// グレネードの残数のポインタ

	int							m_nScore;						// スコア
	int							m_nBulletAmmo;					// 弾の残数
	int							m_nGrenadeAmmo;					// グレネードの残数
};
#endif