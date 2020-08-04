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
	void DebugInfo(void);
	static CScene2D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 size);
	static CScene2D *CreateSceneManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size, CScene::OBJ_TYPE objtype);
	//�Z�b�g�������
	void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize);
	void SetDisp(bool bDisp) { m_bDisp = bDisp; };		// �\���E��\���̐ݒ�

	bool GetDisp() { return m_bDisp; };
protected:

private:
	void MakeVertex(void);
	bool m_bDisp;			// �\���E��\������t���O
};
#endif