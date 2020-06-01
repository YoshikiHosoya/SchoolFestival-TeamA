// ----------------------------------------
//
// 3Dテクスチャ処理の説明[3dtexture.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _3DTEXTURE_H_
#define _3DTEXTURE_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene_three.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class C3DTexture : public CScene_THREE
{
public:
	/* 列挙型 */
	// タイプ
	typedef enum
	{
		TYPE_EFFECT_000 = 0,	// Effect000
		TYPE_EFFECT_001,		// Effect001
		TYPE_MAX
	} TYPE;

	/* 関数 */
	C3DTexture();
	~C3DTexture();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetTexture(TYPE type);							// テクスチャー設定
	void SetSize(D3DXVECTOR3 size);						// サイズ設定
	void SetPos(D3DXVECTOR3 pos);						// 位置設定
	void SetRot(D3DXVECTOR3 rot);						// 回転設定
	void SetCol(D3DXCOLOR col);							// 色設定
	void SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last);	// 表示テクスチャー設定
	D3DXVECTOR3 GetSize(void);							// サイズ取得
	D3DXVECTOR3 GetRot(void);							// 回転取得
	D3DXVECTOR3 GetPos(void);							// 位置取得

	static C3DTexture * Create(	D3DXVECTOR3 pos,
								D3DXVECTOR3 rot,
								D3DXVECTOR3 size,
								D3DXCOLOR col,
								TYPE type,
								bool bBillboard);		// 作成

	static HRESULT Load(void);							// 読み込み
	static void UnLoad(void);							// 破棄
protected:
private:
	static LPDIRECT3DTEXTURE9 m_pTexture[TYPE_MAX];		// テクスチャへのポインタ
	D3DXMATRIX		m_mtxWorld;		// ワールドマトリックス
	TYPE			m_Type;		// タイプ
	bool			m_bBillboard;	// ビルボード状態
};
#endif