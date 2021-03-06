// =====================================================================================================================================================================
//
// フレイムバレットの処理 [flamebullet.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _FLAMEBULLET_H_
#define _FLAMEBULLET_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "bullet.h"

// =====================================================================================================================================================================
// フレイムバレットクラス
// =====================================================================================================================================================================
class CFlameBullet : public CBullet
{
public:

	CFlameBullet(OBJ_TYPE type);							// コンストラクタ
	~CFlameBullet();										// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();						// 初期化
	void						Uninit();					// 終了
	void						Update();					// 更新
	void						Draw();						// 描画
	void						DeleteBullet();				// 弾を消す処理
	void						DebugInfo();				//デバッグ
	virtual void				BulletReaction(D3DXVECTOR3 rot);						// 弾の反応

	/* 静的メンバ関数 */
	static	CFlameBullet		*Create(D3DXVECTOR3 rot);	// フレイムバレットの生成

private:
	/* 静的メンバ変数 */

};
#endif