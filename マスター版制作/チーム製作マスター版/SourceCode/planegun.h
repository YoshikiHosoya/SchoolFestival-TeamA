// =====================================================================================================================================================================
//
// 戦闘機の銃の処理 [planegun.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _PLANEGUN_H_
#define _PLANEGUN_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "bullet.h"

// =====================================================================================================================================================================
// 戦闘機の銃クラス
// =====================================================================================================================================================================
class CPlaneGun : public CBullet
{
public:

	CPlaneGun(OBJ_TYPE type);										// コンストラクタ
	~CPlaneGun();													// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();								// 初期化
	void						Uninit();							// 終了
	void						Update();							// 更新
	void						Draw();								// 描画
	void						DeleteBullet();						// 弾を消す処理
	void						BulletReaction(D3DXVECTOR3 rot);	// 弾の反応
	void						DebugInfo();						// デバッグ

	/* 静的メンバ関数 */
	static	CPlaneGun			*Create(D3DXVECTOR3 rot);			// 戦闘機の銃の生成

private:
	/* 静的メンバ変数 */

};
#endif