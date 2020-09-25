// =====================================================================================================================================================================
//
// プレイヤーの戦車処理 [playertank.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _PLAYERTANK_H_
#define _PLAYERTANK_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "Character.h"
#include "vehicle.h"
// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CGun;
class CGrenadeFire;
class CPlayer;

// =====================================================================================================================================================================
// プレイヤーの戦車クラス
// =====================================================================================================================================================================
class CPlayertank :public CCharacter, public CVehicle
{
public:
	CPlayertank(OBJ_TYPE type);								// コンストラクタ
	~CPlayertank();											// デストラクタ

	/* メンバ関数 */
	HRESULT Init(void);										// 初期化
	void	Uninit(void);									// 終了
	void	Update(void);									// 更新
	void	Draw(void);										// 描画
	bool	DefaultMotion(void);
	void	State();										// ステートに応じた処理
	void	StateChangeReaction();							// ステート切り替わった時の処理
	void	DeathReaction();								// 死亡時のリアクション
	/* 静的メンバ関数 */
	static CPlayertank	*Create();							// 生成

	/* メンバ関数 */
	void				DebugInfo(void);					// デバッグ
	CGun				*GetGun() { return  m_pGun; };					// 銃のポインタ取得
	CGrenadeFire		*GetGrenadeFire() { return  m_pGrenadeFire; };	// グレネード発射位置のポインタ取得
	bool				GetLandFlag() { return m_bLand; };				// 地面についているかどうかのフラグの取得

private:
	/* メンバ関数 */
	void				Shot(CKeyboard *key, TAG Tag);				// 弾を撃つ処理
	void				Operation(CKeyboard *key, TAG Tag);			// 操作する処理
	void				Jump();										// ジャンプ処理
	void				Collision();								// 当たり判定をまとめてする処理
	void				PadInput(TAG Tag);							// ゲームパッドでの入力処理
	void				TankSE();									// タンクから出る音設定
	/* メンバ変数 */
	CGun				*m_pGun;									// ガンクラスのポインタ
	CGrenadeFire		*m_pGrenadeFire;							// グレネード発射クラスのポインタ
	bool				m_bLand;									// 地面についているかどうか
	int					m_nCnt;										// カウント　SE用
};
#endif