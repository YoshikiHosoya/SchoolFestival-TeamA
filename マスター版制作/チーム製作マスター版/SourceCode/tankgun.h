// =====================================================================================================================================================================
//
// 戦車の銃の処理 [tankgun.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _TANKGUN_H_
#define _TANKGUN_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "bullet.h"

// =====================================================================================================================================================================
// 戦車の銃クラス
// =====================================================================================================================================================================
class CTankGun : public CBullet
{
public:

	CTankGun(OBJ_TYPE type);						// コンストラクタ
	~CTankGun();									// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();								// 初期化
	void						Uninit();							// 終了
	void						Update();							// 更新
	void						Draw();								// 描画
	void						DeleteBullet();						// 弾を消す処理
	void						BulletReaction(D3DXVECTOR3 rot);	// 弾の反応
	void						DebugInfo();						//デバッグ

	/* 静的メンバ関数 */
	static	CTankGun			*Create(D3DXVECTOR3 rot);			// 戦車の銃の生成

private:
	/* 静的メンバ変数 */

};
#endif