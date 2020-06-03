#ifndef _SCENE2D_H_
#define _SCENE2D_H_

#include "main.h"
#include "SceneBase.h"
//�����_�����O�N���X
class CScene2D :public CSceneBase
{
public:
	CScene2D() {};//Scene�ŊǗ�����Ȃ��R���X�g���N�^
	CScene2D(OBJ_TYPE type);
	~CScene2D();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	//�Z�b�g�������
	void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize);
protected:

private:
	void MakeVertex(void);
};
#endif