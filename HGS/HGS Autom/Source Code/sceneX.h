//------------------------------------------------------------------------------
//
//X�t�@�C�����f������  [SceneX.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "SceneBase.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModelInfo;

class CSceneX : public CSceneBase
{
public:
	CSceneX();
	virtual ~CSceneX();

	virtual HRESULT Init();						//������
	virtual void Uninit();						//�I��
	virtual void Update();						//�X�V
	virtual void Draw();						//�`��
	void SetAnimation() {};
	void DrawMesh();							//���f���̃��b�V���`��
	void DrawShadow();							//�e�̕`��
	virtual void ShowDebugInfo();				//�f�o�b�O���\�L

	static CSceneX *Create(D3DXVECTOR3 pos,OBJTYPE objtype);		//��������
	static int GetNumSceneX() { return m_nNumSceneX; };				//���擾
	void BindModelInfo(std::shared_ptr<CModelInfo> pSceneXInfo) { m_SceneXInfo = pSceneXInfo; };	//���f���Z�b�g

private:
	static int m_nNumSceneX;									//�����J�E���g
	std::shared_ptr<CModelInfo>	m_SceneXInfo;					//���f�����

};
#endif