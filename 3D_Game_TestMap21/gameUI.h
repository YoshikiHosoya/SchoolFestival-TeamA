// =====================================================================================================================================================================
//
// �Q�[��UI�̏��� [gameUI.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _GAMEUI_H_
#define _GAMEUI_H_

#include "main.h"
#include"scene2D.h"

#define LIFE_DIGIT	(2)				// ����

// =====================================================================================================================================================================
// �O���錾	( �|�C���^�����Ȃ�g���� )
// =====================================================================================================================================================================
class	CNumber;					// �i���o�[�N���X

// =====================================================================================================================================================================
// �Q�[��UI�N���X
// =====================================================================================================================================================================
class CGameUI : public CScene2D
{
public:

	// UI�̎��
	enum GAMEUITYPE
	{
		G_UI_NONE = -1,
		G_UI_ICON,								// �A�C�R��
		G_UI_STOP_MIN,							// �ŏ��l
		G_UI_START_MAX,							// �ő�l
		G_UI_GAGE,								// �Q�[�W
		G_UI_TRIANGLE,							// �l�a�O�p
		G_UI_MAX,
	};

	CGameUI();										// �R���X�g���N�^
	~CGameUI();										// �f�X�g���N�^

	/* �����o�֐� */
	void				Init();						// ������
	void				Uninit();					// �I��
	void				Update();					// �X�V
	void				Draw();						// �`��

	/* �ÓI�����o�֐� */
	static	void		SetLife(int nLife);			// �̗͂̐ݒ�
	static  CGameUI		*Create();					// �Q�[��UI�̐���
	static	HRESULT		Load();						// ���[�h				( �ǂݍ��� )
	static	void		Unload();					// �A�����[�h			( �j�� )
	static	void		RecoveryGage();				// �Q�[�W����

private:
	/* �����o�֐� */
	void						MoveTriangle(void);							// �O�p�̈ړ�����
	/* �ÓI�����o�ϐ� */
	static	LPDIRECT3DTEXTURE9	m_apTexture[GAMEUITYPE::G_UI_MAX];			// ���L�e�N�X�`���̃|�C���^
	static CNumber				*m_apNumber[LIFE_DIGIT];					// �i���o�[�̃|�C���^
	static	D3DXVECTOR2			m_UVsize;									// UV�T�C�Y
	static	bool				m_bGageDecrease;							// �Q�[�W���������Ă��邩
	/* �����o�ϐ� */
	CScene2D					*m_apScene2D[GAMEUITYPE::G_UI_MAX];			// �V�[��2D�̃|�C���^
	D3DXVECTOR3					m_UV[GAMEUITYPE::G_UI_MAX];					// �ړ�
	D3DXCOLOR					m_aCol[GAMEUITYPE::G_UI_MAX];				// �F
	float						m_fTriangleMoveX;							// �O�p�̉��ړ�
};
#endif