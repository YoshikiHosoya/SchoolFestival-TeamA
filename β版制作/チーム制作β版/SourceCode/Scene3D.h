#pragma once
#ifndef _SCENE3D_H_
#define _SCENE3D_H_

#include "main.h"
#include "SceneBase.h"
//レンダリングクラス
class CScene3D :public CSceneBase
{
public:
	CScene3D() {};//Sceneで管理されないコンストラクタ
	CScene3D(OBJ_TYPE type);
	~CScene3D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize);
	//ゲットするもの
	static CScene3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot);

	//set関数　オーバーライド
	void SetSize(D3DXVECTOR3 size);
	void SetColor(D3DXCOLOR col);
	void SetBillboard(bool bBillboard)	{ m_bBillboard = bBillboard; };			// ビルボードの設定
	bool GetBillboard()					{ return m_bBillboard; };				// ビルボードの取得
protected:

private:
	void MakeVertex(void);
	bool					m_bBillboard;			// ビルボードフラグ

};
#endif