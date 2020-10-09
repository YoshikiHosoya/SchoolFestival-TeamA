//------------------------------------------------------------------------------
//
//�V�[��3D����  [scene3D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCENE3D_H_
#define _SCENE3D_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scenebase.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene3D : public CSceneBase
{
public:

	CScene3D();
	virtual ~CScene3D();

	virtual HRESULT Init();								//������
	virtual void Uninit();								//�I��
	virtual void Update();								//�X�V
	virtual void Draw();								//�`��
	virtual void ShowDebugInfo();						//�f�o�b�O���\�L

	void DrawSettingMtx(D3DXMATRIX const &Mtx);				//�n�����Ōv�Z�������[���h�}�g���b�N�X�����ɕ`��
	void DrawPolygon();

	void SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 size);		//�e�N�X�`��UV���W�ݒ�
	void SetNormal();											//�@���ݒ�

	void SetBboard(bool bBboard)	{m_bBboard = bBboard;};		//�r���{�[�h��

	static std::shared_ptr<CScene3D> Create_Shared(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);	//���������iCScene��Return��ŋ��L�Ǘ�
	static void Create_SceneManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size, OBJTYPE objtype);				//���������iCScene�݂̂ŊǗ�
	static std::unique_ptr<CScene3D> Create_SelfManagement(D3DXVECTOR3 pos, D3DXVECTOR3 size);			//���������iReturn��ŊǗ�

	static int GetNumScene3D() { return m_nNumScene3D; };												//3D�|���S�������擾

private:
	static int m_nNumScene3D;

	bool m_bBboard;										//�r���{�[�h���ǂ���
	VERTEX_3D		m_Vtx3D[4];							//���_���@debug�p
	HRESULT MakeVertex();										//���_�o�b�t�@�쐬


};
#endif