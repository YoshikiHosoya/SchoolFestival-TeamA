// =====================================================================================================================================================================
//
// シーンXの処理 [sceneX.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _SCENEX_H_
#define _SCENEX_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "scene.h"

// =====================================================================================================================================================================
// 構造体定義
// =====================================================================================================================================================================
// === モデル描画に必要な情報 ===
typedef struct
{
	LPD3DXMESH					Mesh;				// メッシュ情報へのポインタ
	LPD3DXBUFFER				BuffMat;			// マテリアル情報へのポインタ
	DWORD						nNumMat;			// マテリアル情報の数
}MODEL_DRAWINFO;

// =====================================================================================================================================================================
// オブジェクトクラス
// =====================================================================================================================================================================
class CSceneX : public CScene
{
public:
	CSceneX();								// コンストラクタ
	CSceneX(PRIORITY Priority);				// コンストラクタ
	virtual ~CSceneX();						// デストラクタ
	 
	/* メンバ関数 */
	virtual void	Init();					// 初期化
	virtual void	Uninit();				// 終了
	virtual void	Update();				// 更新
	virtual void	Draw();					// 描画

	/* 静的メンバ関数 */
	static	CSceneX		*Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);			// 3Dポリゴンの生成	

	/* メンバ関数 */
	void			SetPos(D3DXVECTOR3 pos)						{ m_pos = pos; };						// 位置の設定
	void			SetRot(D3DXVECTOR3 rot)						{ m_rot = rot; };						// 回転の設定
	void			SetMatrix(D3DXMATRIX mtx)					{ m_mtxWorld = mtx; };					// マトリックスの設定
	void			SetModelDraw(MODEL_DRAWINFO *ModelDrawInfo)	{ m_pModelDrawInfo = ModelDrawInfo; };	// モデル描画情報の設定
	D3DXVECTOR3		GetPos()									{ return m_pos; };						// 位置の取得
	D3DXVECTOR3		GetRot()									{ return m_rot; };						// 回転の取得
	D3DXMATRIX		*GetMatrix()								{ return &m_mtxWorld; };				// マトリックスの取得
	void			SetTexture(char TexName[]);									// 画像の設定
	void			BindTexture(LPDIRECT3DTEXTURE9 pTexture);					// 画像の代入
	void			DrawModel();												// モデルの描画
private:

	D3DXVECTOR3				m_pos;		// 位置
	D3DXVECTOR3				m_move;		// 移動
	D3DXVECTOR3				m_size;		// サイズ
	D3DXVECTOR3				m_rot;		// 向き(回転)

	MODEL_DRAWINFO			*m_pModelDrawInfo;	// モデルの描画に必要な情報
	D3DXMATRIX				m_mtxWorld;			// ワールドマトリックス
	LPDIRECT3DTEXTURE9		m_pTexture	= {};	// テクスチャへのポインタ
};
#endif
