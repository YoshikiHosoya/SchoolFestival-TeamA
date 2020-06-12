// =====================================================================================================================================================================
//
// ���U���gUI�̏��� [resultUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _RESULTUI_H_
#define _RESULTUI_H_

#include "main.h"
#include"scene2D.h"

// =====================================================================================================================================================================
// ���U���gUI�N���X
// =====================================================================================================================================================================
class CResultUI : public CScene2D
{
public:

	// UI�̎��
	enum RESULTUITYPE
	{
		R_UI_NONE = -1,
		R_UI_LOGO,					// ���S
		R_UI_ENTER,					// Enter�L�[
		R_UI_MAOU,					// ������
		R_UI_MAX,
	};

	CResultUI();								// �R���X�g���N�^
	~CResultUI();								// �f�X�g���N�^

	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �ÓI�����o�֐� */
	static  CResultUI	*Create();				// ���U���gUI�̐���
	static	HRESULT		Load();					// ���[�h
	static	void		Unload();				// �A�����[�h

private:
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[RESULTUITYPE::R_UI_MAX];		// ���L�e�N�X�`���̃|�C���^
	/* �����o�ϐ� */
	CScene2D					*m_apScene2D[RESULTUITYPE::R_UI_MAX];		// �V�[��2D�̃|�C���^
	D3DXVECTOR3					m_UV[RESULTUITYPE::R_UI_MAX];				// UV
};
#endif