// =====================================================================================================================================================================
//
// �|�[�YUI�̏��� [pauseUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _PAUSEUI_H_
#define _PAUSEUI_H_

#include "main.h"
#include "scene2D.h"

// =====================================================================================================================================================================
// �|�[�YUI�N���X
// =====================================================================================================================================================================
class CPauseUI
{
public:

	// UI�̎��
	enum PAUSEUITYPE
	{
		P_UI_NONE = -1,
		P_UI_RESUME,							// �ĊJ
		P_UI_RESTART,							// ���X�^�[�g
		P_UI_TITLE,								// �^�C�g��
		P_UI_LOGO,								// �|�[�Y���S
		P_UI_MAX,
	};

	CPauseUI();									// �R���X�g���N�^
	~CPauseUI();								// �f�X�g���N�^

	/* �����o�֐� */
	void				Init();					// ������
	void				Uninit();				// �I��
	void				Update();				// �X�V
	void				Draw();					// �`��

	/* �ÓI�����o�֐� */
	static  CPauseUI	*Create();				// �|�[�YUI�̐���
	static	HRESULT		Load();					// ���[�h
	static	void		Unload();				// �A�����[�h

private:
	/* �����o�֐� */
	void						UIConfig(int nCnt);						// UI�̓��e�ݒ�
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[PAUSEUITYPE::P_UI_MAX];		// ���L�e�N�X�`���̃|�C���^
	static	int					m_nNum;									// �A�C�R���ړ��̃i���o�[
	/* �����o�ϐ� */
	CScene2D					*m_apScene2D[PAUSEUITYPE::P_UI_MAX];	// �V�[���̃|�C���^
	D3DXCOLOR					m_aCol[PAUSEUITYPE::P_UI_MAX];			// �F
	int							m_nTime;								// �_�Ŏ���
	bool						m_bFlash;								// �_�Ő؂�ւ�
};
#endif
