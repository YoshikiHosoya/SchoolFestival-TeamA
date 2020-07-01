//------------------------------------------------------------------------------
//
//軌跡処理  [orbit.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MESHORBIT_H_
#define _MESHORBIT_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "scene2D.h"
#include "scene.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define MAX_ORBIT_LENGTH	(50)
//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class COrbit : public CScene
{
public:
	COrbit();
	COrbit(OBJ_TYPE obj) : CScene(obj) {};
	~COrbit();

	HRESULT Init();													//初期化
	void Uninit();													//終了
	void Update();													//更新
	void Draw();													//描画
	void DebugInfo();												//デバッグ情報表記
	void SetOrbit(D3DXVECTOR3 pos01, D3DXVECTOR3 pos02);			//軌跡設定
	void DeleteOrbit();												//軌跡消去
	static COrbit *Create(D3DXMATRIX *pMtx);		//生成処理

	//Set関数
	void SetLife(int nLife) { m_nLife = nLife; };									//ライフ設定
	void SetCol(D3DXCOLOR col) { m_coldefault = col; };								//色設定
	void SetMtx(D3DXMATRIX *pMtx) { m_pParentMtx = pMtx; };							//マトリックスのポインタ設定
	void SetPosOffset(D3DXVECTOR3 posOffset) { m_posOffset = posOffset; };			//相対座標設定

private:
	LPDIRECT3DVERTEXBUFFER9	m_pVtxBuff;						//頂点バッファへのポインタ

	D3DXMATRIX *m_pParentMtx;								//親のマトリックスへのポインタ
	D3DXVECTOR3 m_posOffset;								//先端への相対座標

	int m_nLife;											//フラグがたってからのライフ
	bool m_bDeleteFlag;										//消えるかどうか
	float m_fLength;										//軌跡の長さ
	D3DXCOLOR m_coldefault;									//最初の色
	D3DXCOLOR m_col[MAX_ORBIT_LENGTH];						//色
	D3DXVECTOR3 m_posVertex[MAX_ORBIT_LENGTH];				//各頂点の座標

	void CalcOrbitPos();									//軌跡の座標計算
	void SetDefaultVtxPos();								//初期設定

};

#endif