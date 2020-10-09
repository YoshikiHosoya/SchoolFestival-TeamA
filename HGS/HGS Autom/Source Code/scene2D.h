//------------------------------------------------------------------------------
//
//�V�[��2D����  [scene2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE2D_H_
#define _SCENE2D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "SceneBase.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D : public CSceneBase
{
public:
	CScene2D();
	virtual ~CScene2D();

	virtual HRESULT Init();					//������
	virtual void Uninit();					//�I��
	virtual void Update();					//�X�V
	virtual void Draw();					//�`��
	virtual void ShowDebugInfo();			//�f�o�b�O���\�L
	void SetAnimation(D3DXVECTOR2 UV,D3DXVECTOR2 size);		//�e�N�X�`��UV���W�ݒ�
	void SetColor(D3DXCOLOR col);	// �F�ݒ�
	static std::shared_ptr<CScene2D> Create_Shared			(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);	//���������iScene��Return��ŋ��L�Ǘ�
	static void Create_SceneManagement						(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);	//���������iCScene�݂̂ŊǗ�
	static std::unique_ptr<CScene2D> Create_SelfManagement	(D3DXVECTOR3 pos, D3DXVECTOR3 size);					//���������iReturn��ŊǗ�

	static int GetNumScene2D()	{ return m_nNumScene2D; };					//2D�̑����擾

private:
	static int m_nNumScene2D;								//����
	float m_fAngle;											//�p�x�@2D�|���S������]���鎞�Ɏg��
	float m_fLength;										//����

	HRESULT MakeVertex();										//���_�o�b�t�@�쐬
};

#endif