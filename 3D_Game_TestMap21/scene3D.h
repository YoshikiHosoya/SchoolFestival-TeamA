// =====================================================================================================================================================================
//
// シーン3Dの処理 [scene3D.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"

// =====================================================================================================================================================================
// オブジェクトクラス
// =====================================================================================================================================================================
class CScene3D : public CScene
{
public:
	CScene3D(PRIORITY Priority);			// コンストラクタ
	virtual ~CScene3D();					// デストラクタ
	 
	/* メンバ関数 */
	virtual void	Init();					// 初期化
	virtual void	Uninit();				// 終了
	virtual void	Update();				// 更新
	virtual void	Draw();					// 描画

	/* 静的メンバ関数 */
	static			CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 3Dポリゴンの生成	

	/* メンバ関数 */
	void			SetPos(D3DXVECTOR3 pos)						{ m_pos = pos; };								// 位置の設定
	void			SetRot(D3DXVECTOR3 rot)						{ m_rot = rot; };								// 回転の設定
	void			SetSize(D3DXVECTOR3 size)					{ m_size = size; };								// サイズの設定
	void			SetBillboard(bool bBillboard)				{ m_bBillboard = bBillboard; };					// ビルボードの設定
	void			SetBothSideCulling(bool bBothSideCulling)	{ m_bBothSideCulling = bBothSideCulling; };		// 両面カリングの設定
	void			SetTexture(char TexName[]);										// 画像の設定
	void			SetRadius(float fRadius);										// 半径の設定
	void			SetScaling(D3DXVECTOR3 size);									// 拡縮の設定
	void			SetNormal();													// 法線の設定
	void			SetAnim(D3DXVECTOR2 UVsize, D3DXVECTOR2 UV);					// アニメーションの設定
	void			SetColor(D3DXCOLOR col);										// 色の設定
	void			SetTexSeparate(int nSeparate);									// テクスチャの分割設定
	void			SetSlope(float Slope);											// 坂の斜面の設定
	void			BindTexture(LPDIRECT3DTEXTURE9 pTexture);						// 画像の代入
	bool			GetHeight(D3DXVECTOR3 &pos);									// 高さの取得
	D3DXVECTOR3		GetPos()									{ return m_pos; };	// 位置の取得
	D3DXVECTOR3		GetSize()									{ return m_size; };	// サイズの取得

private:
	/* メンバ変数 */
	LPDIRECT3DTEXTURE9		m_pTexture = NULL;		// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff = NULL;		// 頂点バッファへのポインタ
	D3DXMATRIX				m_mtxWorld;				// ワールドマトリックス
	bool					m_bBillboard;			// ビルボードフラグ
	bool					m_bBothSideCulling;		// 両面カリングフラグ

	D3DXVECTOR3				m_pos;					// 位置
	D3DXVECTOR3				m_size;					// サイズ
	D3DXVECTOR3				m_rot;					// 回転
	float					m_fSlope;				// 傾斜

	D3DXVECTOR3				m_vec2_0;				// ベクトル2_0
	D3DXVECTOR3				m_vec1_2;				// ベクトル1_2
	D3DXVECTOR3				m_vec2_3;				// ベクトル2_3

	D3DXVECTOR3				m_nor1_2_0;				// 法線1_2_0
	D3DXVECTOR3				m_nor1_2_3;				// 法線1_2_3
	D3DXVECTOR3				m_nor1_2;				// 法線1_2;	
};
#endif
