// =====================================================================================================================================================================
//
// シーン2Dnewの処理 [scene2Dnew.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SCENE2DNEW_H_
#define _SCENE2DNEW_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"

// =====================================================================================================================================================================
// オブジェクトクラス
// =====================================================================================================================================================================
class CScene2Dnew
{
public:
	CScene2Dnew();														// コンストラクタ
	virtual ~CScene2Dnew();												// デストラクタ
	
	/* メンバ関数 */
	virtual void	Init();												// 初期化
	virtual void	Uninit();											// 終了
	virtual void	Update();											// 更新
	virtual void	Draw();												// 描画

	/* メンバ関数 */
	void			SetPos(D3DXVECTOR3 pos)		{ m_pos = pos; };			// 位置の設定
	D3DXVECTOR3		GetPos()					{ return m_pos; };			// 位置の取得
	D3DXVECTOR3		GetSize()					{ return m_size; };			// サイズの取得
	void			SetSize(D3DXVECTOR3 size)	{ m_size = size; };			// サイズの設定
	void			SetAnim(D3DXVECTOR2 UVsize, D3DXVECTOR2 UV);			// アニメーションの設定
	void			SetRadius(float fRadius);								// 半径の設定
	void			SetRotation(float fAngle, float fLength, float fRot);	// 回転の設定
	void			SetCol(D3DXCOLOR col);									// 色の設定
	void			BindTexture(LPDIRECT3DTEXTURE9 pTexture);				// 画像の代入

	/* 静的メンバ関数 */
	static			CScene2Dnew *Create();										// 2Dポリゴンの生成

private:
	/* メンバ変数 */
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;	// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;	// 頂点バッファへのポインタ
	D3DXVECTOR3				m_pos;				// 位置
	D3DXVECTOR3				m_size;				// サイズ
	D3DXVECTOR3				m_rot;				// 回転
	float					m_fAngle;			// 角度
	float					m_fLength;			// 長さ
};
#endif