// =====================================================================================================================================================================
//
// �Q�[���G���hUI�̏��� [gameendtUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GAMEENDUI_H_
#define _GAMEENDUI_H_

#include "main.h"
#include"scene2D.h"

// =====================================================================================================================================================================
// �Q�[���G���hUI�N���X
// =====================================================================================================================================================================
class CGameEndUI : public CScene2D
{
public:

	// UI�̎��
	enum GAMEENDUITYPE
	{
		GE_UI_NONE = -1,
		GE_UI_HAZE,				// ����
		GE_UI_CLEAR,			// �N���A
		GE_UI_OVER,				// �Q�[���I�[�o�[
		GE_UI_MAX,
	};

	CGameEndUI();										// �R���X�g���N�^
	~CGameEndUI();										// �f�X�g���N�^

	/* �����o�֐� */
	void						Init();					// ������
	void						Uninit();				// �I��
	void						Update();				// �X�V
	void						Draw();					// �`��

	/* �ÓI�����o�֐� */
	static  CGameEndUI			*Create();				// �Q�[���G���hUI�̐���
	static	HRESULT				Load();					// ���[�h
	static	void				Unload();				// �A�����[�h

private:
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[GAMEENDUITYPE::GE_UI_MAX];		// ���L�e�N�X�`���̃|�C���^
	/* �����o�ϐ� */
	CScene2D					*m_apScene2D[GAMEENDUITYPE::GE_UI_MAX];		// �V�[��2D�̃|�C���^
	D3DXVECTOR3					m_UV[GAMEENDUITYPE::GE_UI_MAX];				// UV
};
#endif