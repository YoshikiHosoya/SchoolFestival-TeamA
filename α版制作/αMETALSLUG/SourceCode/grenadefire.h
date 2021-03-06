// =====================================================================================================================================================================
//
// グレネード発射の処理 [grenadefire.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GRENADEFIRE_H_
#define _GRENADEFIRE_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"

// =====================================================================================================================================================================
// グレネード発射クラス
// =====================================================================================================================================================================
class CGrenadeFire : public CScene
{
public:

	CGrenadeFire(OBJ_TYPE type);							// コンストラクタ
	~CGrenadeFire();										// デストラクタ

	/* メンバ関数 */
	HRESULT						Init();						// 初期化
	void						Uninit();					// 終了
	void						Update();					// 更新
	void						Draw();						// 描画
	void						DebugInfo(void);			// デバッグ

	/* 静的メンバ関数 */
	static	CGrenadeFire		*Create(D3DXMATRIX *mtx);	// グレネード放つ位置の生成

	/* メンバ関数 */
	void						Fire(D3DXVECTOR3 rot);					// グレネードを放つ
	int							GetGrenadeAmmo() { return m_nAmmo; };	// グレネードの残弾数取得
	void						GrenadeAddAmmo();						// グレネードの弾数追加

private:
	/* メンバ変数 */
	int							m_nAmmo;					// 残弾数
	int							m_nInterval;				// インターバル
	D3DXMATRIX					*m_mtx;						// マトリックス
	TAG							m_Tag;						// タグ

	/* 静的メンバ変数 */
};
#endif