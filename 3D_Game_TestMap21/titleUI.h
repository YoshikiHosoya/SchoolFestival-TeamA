// =====================================================================================================================================================================
//
// �^�C�g��UI�̏��� [titleUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _TITLEUI_H_
#define _TITLEUI_H_

#include "main.h"
#include "scene2D.h"
#include "title.h"

// =====================================================================================================================================================================
// �^�C�g��UI�N���X
// =====================================================================================================================================================================
class CTitleUI : public CScene2D
{
public:

	// UI�̎��
	enum TYTLEUITYPE
	{
		T_UI_NONE = -1,
		T_UI_LOGO,								// �^�C�g�����S
		T_UI_ENTER,								// �G���^�[
		T_UI_MAX,
	};

	CTitleUI();									// �R���X�g���N�^
	~CTitleUI();								// �f�X�g���N�^

	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �ÓI�����o�֐� */
	static  CTitleUI	*Create();				// �^�C�g��UI�̐���
	static	HRESULT		Load();					// ���[�h
	static	void		Unload();				// �A�����[�h

private:
	/* �����o�֐� */
	void						UIConfig(int nCnt);						// UI�̓��e�ݒ�
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[TYTLEUITYPE::T_UI_MAX];		// ���L�e�N�X�`���̃|�C���^
	static	int					m_nNum;									// �A�C�R���ړ��̃i���o�[
	/* �����o�ϐ� */
	CScene2D					*m_apScene2D[TYTLEUITYPE::T_UI_MAX];	// �V�[��2D�̃|�C���^
	D3DXCOLOR					m_aCol[TYTLEUITYPE::T_UI_MAX];			// �F
	int							m_nTime;								// �_�Ŏ���
	bool						m_bFlash;								// �_�Ő؂�ւ�
};
#endif
