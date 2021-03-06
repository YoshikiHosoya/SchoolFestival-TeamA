// =====================================================================================================================================================================
//
// ショットガンの処理 [shotgun.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SHOTGUN_H_
#define _SHOTGUN_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "bullet.h"

// =====================================================================================================================================================================
// ショットガンクラス
// =====================================================================================================================================================================
class CShotgun : public CBullet
{
public:

	CShotgun(OBJ_TYPE type);								// コンストラクタ
	~CShotgun();											// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();								// 初期化
	void						Uninit();							// 終了
	void						Update();							// 更新
	void						Draw();								// 描画
	void						DeleteBullet();						// 弾を消す処理
	void						BulletReaction(D3DXVECTOR3 rot);	// 弾の反応
	void						DebugInfo();						//デバッグ

	/* 静的メンバ関数 */
	static	CShotgun			*Create(D3DXVECTOR3 rot);	// ショットガンの生成

private:
	/* 静的メンバ変数 */

};
#endif