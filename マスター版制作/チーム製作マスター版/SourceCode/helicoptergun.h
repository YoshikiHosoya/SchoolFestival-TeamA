// =====================================================================================================================================================================
//
// ヘリの銃の処理 [heli.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _HELIGUN_H_
#define _HELIGUN_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "bullet.h"

// =====================================================================================================================================================================
// ヘリの銃クラス
// =====================================================================================================================================================================
class CHeliGun : public CBullet
{
public:

	CHeliGun(OBJ_TYPE type);										// コンストラクタ
	~CHeliGun();													// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();								// 初期化
	void						Uninit();							// 終了
	void						Update();							// 更新
	void						Draw();								// 描画
	void						DeleteBullet();						// 弾を消す処理
	void						BulletReaction(D3DXVECTOR3 rot);	// 弾の反応
	void						DebugInfo();						// デバッグ

	/* 静的メンバ関数 */
	static	CHeliGun			*Create(D3DXVECTOR3 rot);			// ヘリの銃の生成

private:
	/* 静的メンバ変数 */

};
#endif