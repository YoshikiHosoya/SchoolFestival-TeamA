#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "SceneBase.h"
//レンダリングクラス
class CScene2D :public CSceneBase
{
public:
	CScene2D() {};//Sceneで管理されないコンストラクタ
	CScene2D(OBJ_TYPE type);
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	//セットするもの
	void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize);
protected:

private:
	void MakeVertex(void);
};
#endif