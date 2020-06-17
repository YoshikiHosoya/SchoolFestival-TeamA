// =====================================================================================================================================================================
//
// ハンドガンの処理 [handgun.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _HANDGUN_H_
#define _HANDGUN_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "bullet.h"

// =====================================================================================================================================================================
// ハンドガンクラス
// =====================================================================================================================================================================
class CHandgun : public CBullet
{
public:

	CHandgun(OBJ_TYPE type);									// コンストラクタ
	~CHandgun();								// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();					// 初期化
	void						Uninit();				// 終了
	void						Update();				// 更新
	void						Draw();					// 描画

	/* 静的メンバ関数 */
	static	CHandgun			*Create(D3DXVECTOR3 rot);	// ハンドガンの生成

private:
	/* 静的メンバ変数 */

};
#endif