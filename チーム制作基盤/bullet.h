// =====================================================================================================================================================================
//
// バレットの処理 [bullet.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _BULLET_H_
#define _BULLET_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene3D.h"

// =====================================================================================================================================================================
// バレットクラス
// =====================================================================================================================================================================
class CBullet : public CScene3D
{
public:

	CBullet(OBJ_TYPE type);											// コンストラクタ
	~CBullet();											// デストラクタ

	/* メンバ関数 */
	virtual HRESULT				Init();					// 初期化
	virtual void				Uninit();				// 終了
	virtual void				Update();				// 更新
	virtual void				Draw();					// 描画

	/* メンバ関数 */
	D3DXVECTOR3					&GetMove()					{ return m_move; };		// 移動値の取得
	void						SetMove(D3DXVECTOR3 move)	{ m_move = move; };		// 移動値の設定
private:
	/* メンバ変数 */
	D3DXVECTOR3					m_move;					// 移動値
	int							m_nLife;				// 体力

};
#endif
