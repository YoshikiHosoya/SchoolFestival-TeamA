// =====================================================================================================================================================================
//
// ドローンビーム処理 [dronebeam.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _DRONEBEAM_H_
#define _DRONEBEAM_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "bullet.h"

// =====================================================================================================================================================================
// ショットガンクラス
// =====================================================================================================================================================================
class CDroneBeam : public CBullet
{
public:

	CDroneBeam(OBJ_TYPE type);								// コンストラクタ
	~CDroneBeam();											// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();								// 初期化
	void						Uninit();							// 終了
	void						Update();							// 更新
	void						Draw();								// 描画
	void						DeleteBullet();						// 弾を消す処理
	void						BulletReaction(D3DXVECTOR3 rot);	// 弾の反応
	void						DebugInfo();						// デバッグ

	/* 静的メンバ関数 */
	static	CDroneBeam			*Create(D3DXVECTOR3 rot);			// ドローンビームの生成

private:
	/* 静的メンバ変数 */

};
#endif