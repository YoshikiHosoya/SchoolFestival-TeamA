#pragma once
#ifndef _SCENEX_H_
#define _SCENEX_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#define MAX_MODEL (1)
//レンダリングクラス
class CSceneX :public CScene
{
public:
	CSceneX() {};
	CSceneX(OBJ_TYPE type);
	~CSceneX();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	static CSceneX *Create(void);
private:
	typedef struct
	{
		int nLife;
		D3DXVECTOR3 pos;					//位置
		D3DXVECTOR3 posold;					//位置
		D3DXVECTOR3 move;					//移動量
		LPD3DXBUFFER pBuffmat;				//バッファ
		DWORD nNumMat;						//マテリアルの数
		LPD3DXMESH pMesh;					//メッシュ
		D3DXVECTOR3 vtxMin;					//最少
		D3DXVECTOR3 vtxMax;					//最大
		D3DXCOLOR col;						//カラー
		D3DXVECTOR3 rot;					//回転
		D3DXMATRIX mtxWorld;				//マトリックス
		int nType;							//タイプ
	} MODEL;
	static MODEL m_Model[MAX_MODEL];		//モデル
	DWORD m_nNumMatModel = MAX_MODEL;		//マテリアル情報の数 
	LPDIRECT3DTEXTURE9 m_pTextureModel;		//テクスチャ
};
#endif