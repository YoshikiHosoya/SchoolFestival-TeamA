// ----------------------------------------
//
// 3D線処理の説明[3Dline.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _3DLINE_H_
#define _3DLINE_H_	 // ファイル名を基準を決める

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "scene.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------

// ------------------------------------------
//
// 前方宣言
//
// ------------------------------------------

// ------------------------------------------
//
// クラス
//
// ------------------------------------------
class C3DLine : public CScene
{
public:
	/* メンバ関数 */
	C3DLine(OBJ_TYPE type);
	~C3DLine();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void DebugInfo(void);
	virtual void SetPos(						// 位置設定
		D3DXVECTOR3 &pos1,
		D3DXVECTOR3 &pos2
	);

	void SetPosColi(							// デバック判定用位置設定
		D3DXVECTOR3 &pos1
	);

	void SetCol(								// 色設定
		D3DXCOLOR &col
	);

	/* 静的メンバ関数 */
	static C3DLine * Create(					// 作成
		D3DXVECTOR3 &pos,
		D3DXVECTOR3 &rot,
		D3DXVECTOR3 &pos1,
		D3DXVECTOR3 &pos2,
		D3DXCOLOR	&col
	);
protected:

private:
	/* メンバ変数 */
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// 頂点バッファへのポインタ
	D3DXMATRIX					m_mtxWorld;		// ワールドマトリックス
	D3DXVECTOR3					m_pos;			// 位置
	D3DXVECTOR3					m_rot;			// 回転
	D3DXCOLOR					m_col;			// 色
};

#endif