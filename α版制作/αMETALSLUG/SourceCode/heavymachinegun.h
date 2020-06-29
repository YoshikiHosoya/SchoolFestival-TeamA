// =====================================================================================================================================================================
//
// ヘビーマシンガンの処理 [heavymachinegun.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _HEAVYMACHINEGUN_H_
#define _HEAVYMACHINEGUN_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "bullet.h"

// =====================================================================================================================================================================
// ヘビーマシンガンクラス
// =====================================================================================================================================================================
class CHeavyMachinegun : public CBullet
{
public:

	CHeavyMachinegun(OBJ_TYPE type);						// コンストラクタ
	~CHeavyMachinegun();									// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();						// 初期化
	void						Uninit();					// 終了
	void						Update();					// 更新
	void						Draw();						// 描画
	void						DeleteBullet();				// 弾を消す処理
	void						DebugInfo();				//デバッグ
	/* 静的メンバ関数 */
	static	CHeavyMachinegun	*Create(D3DXVECTOR3 rot);	// ヘビーマシンガンの生成

private:
	/* 静的メンバ変数 */

};
#endif