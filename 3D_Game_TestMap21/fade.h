// =====================================================================================================================================================================
//
// �t�F�[�h�̏��� [fade.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _FADE_H_
#define _FADE_H_

#define _CRT_SECURE_NO_WARNINGS

#include "main.h"			// �C���N���[�h�t�@�C��
#include "manager.h"

// =====================================================================================================================================================================
// �t�F�[�h�N���X
// =====================================================================================================================================================================
class CFade
{
public:

	// �t�F�[�h�̏��
	enum FADE
	{
		FADE_NONE = -1,
		FADE_IN,			// �t�F�[�h�C������
		FADE_OUT,			// �t�F�[�h�A�E�g����
		FADE_MAX
	};

	CFade();				// �R���X�g���N�^
	~CFade();				// �f�X�g���N�^

	/* �����o�֐� */
	void Init();					// ������
	void Uninit();					// �I��
	void Update();					// �X�V
	void Draw();					// �`��

	/* �ÓI�����o�֐� */
	static	CFade		*Create();								// �Q�[���N���X�̐���
	static	void		SetFade(CManager::MODE modeNext);		// �t�F�[�h�̐ݒ�
	static	FADE		GetFadeState()		{ return m_fade; };	// �t�F�[�h�̏�Ԏ擾

private:
	/* �����o�֐� */
	void MakeVertexFade(LPDIRECT3DDEVICE9 pDevice);				// ���_�̍쐬
	/* �����o�ϐ� */
	LPDIRECT3DTEXTURE9				m_pTextureFade = NULL;		// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9			m_pVtxBuffFade = NULL;		// ���_�o�b�t�@�ւ̃|�C���^
	static	FADE					m_fade;						// �t�F�[�h���
	static	CManager::MODE			m_modeNext;					// ���̉�ʁi���[�h�j
	static	D3DXCOLOR				m_colorFade;				// �t�F�[�h�F

};
#endif