// =====================================================================================================================================================================
//
// 2D�I�u�W�F�N�g�̏��� [object2D.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "scene3D.h"

// =====================================================================================================================================================================
// 2D�I�u�W�F�N�g�N���X
// =====================================================================================================================================================================
class CObject2D : public CScene3D
{
public:

	// 2D�I�u�W�F�N�g�̎��
	enum OBJECT_2D_TYPE
	{
		OBJECT_2D_TYPE_NONE = -1,
		OBJECT_2D_TYPE_FLOOR,					// ��
		OBJECT_2D_TYPE_WALL,					// ��
		OBJECT_2D_TYPE_MAX,
	};

	CObject2D();								// �R���X�g���N�^
	~CObject2D();								// �f�X�g���N�^

	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �ÓI�����o�֐� */
	static	CObject2D	*Create(D3DXVECTOR3 pos, OBJECT_2D_TYPE type);	// 2D�I�u�W�F�N�g�̐���
	static	HRESULT		Load();					// ���[�h
	static	void		Unload();				// �A�����[�h

	/* �����o�֐� */
	bool				CollisionObject2D(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize, CObject2D **ppObjectRet);	// 2D�I�u�W�F�N�g�̓����蔻��
	OBJECT_2D_TYPE		GetObject2DType()	{ return m_type; };		// 2D�I�u�W�F�N�g�̎�ނ̎擾
	void				SetObject2DType(OBJECT_2D_TYPE type);		// 2D�I�u�W�F�N�g�̎�ނ̐ݒ�

private:
	/* �����o�֐� */
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[OBJECT_2D_TYPE::OBJECT_2D_TYPE_MAX];		// ���L�e�N�X�`���̃|�C���^
	/* �����o�ϐ� */
	D3DXVECTOR3					m_size;											// �T�C�Y
	D3DXCOLOR					m_col;											// �F
	OBJECT_2D_TYPE				m_type;											// ���
};
#endif
