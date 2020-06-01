#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "scene.h"
//レンダリングクラス
class CScene2D :public CScene
{
public:
	CScene2D(OBJ_TYPE type);
	~CScene2D();
	HRESULT Init(void);
	HRESULT Init2(void);
	void Uninit(void);
	void Update(void);
	void Update2(void);
	void PlayerUIUpdate(int State, float Double);
	void EnemyUIUpdate(int State, float Double);
	void BillboardDrow(void);
	void Drow(void);
	//セットするもの
	void SetColor(D3DXCOLOR col);
	void SetSize(D3DXVECTOR2 size);
	void SetBec(D3DXVECTOR3 bec);
	void SetPosition(float fx, float fy, float fz);
	void SetTex(D3DXVECTOR2 tex);
	void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize);
	void BindTexture(LPDIRECT3DTEXTURE9 tex);
	void SetCenter(void);
	void SetMove(D3DXVECTOR3 move);
	//ゲットするもの
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR2 GetSize(void);
	D3DXCOLOR GetColor(void);

protected:

private:
	LPDIRECT3DTEXTURE9 m_pTextureBG;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuffBG = NULL;	//頂点バッファへのポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_bec;
	D3DXVECTOR3 m_move;
	float rot;
	D3DXVECTOR2 m_size;
	float m_fLength;
	float m_Angle;
	D3DXVECTOR2 m_tex;
	D3DXCOLOR m_col;
	bool m_bUse;

	D3DXMATRIX m_mtxWorld;						// ワールドマトリックス
};
#endif