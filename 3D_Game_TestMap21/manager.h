// =====================================================================================================================================================================
//
// �}�l�[�W���[�̏��� [manager.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _MANAGER_H_
#define _MANAGER_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"

// =====================================================================================================================================================================
// �O���錾	( �|�C���^�����Ȃ�g���� )
// =====================================================================================================================================================================
class CKeyboard;						// �L�[�{�[�h�N���X
class CXinputGpad;						// �W���C�p�b�h�N���X
class CGame;							// �Q�[���N���X
class CTitle;							// �^�C�g���N���X
class CResult;							// ���U���g�N���X
class CRanking;							// �����L���O�N���X
class CSound;							// �T�E���h�N���X

// =====================================================================================================================================================================
// �Ǘ��N���X
// =====================================================================================================================================================================
class CManager
{
public:
	// ��ʎ��
	enum MODE
	{
		NONE = -1,
		TITLE,					// �^�C�g��
		GAME,					// �Q�[��
		RESULT,					// ���U���g
		RANKING,				// �����L���O
		MAX
	};

	CManager();													// �R���X�g���N�^
	~CManager();												// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, bool bWindow);	// ������
	void	Uninit();											// �I��
	void	Update();											// �X�V
	void	Draw();												// �`��

	/* �ÓI�����o�֐� */
	static	void		SetMode(MODE mode);						// ���[�h�̐ݒ�
	static	MODE		GetMode()	{ return m_mode; };			// ���[�h�̎擾
	static	CRenderer	*GetRenderer();						// �����_���[�̎擾
	static	CKeyboard	*GetKeyboard();						// ���͂̎擾
	static	CXinputGpad	*GetXinputGpad();					// �Q�[���p�b�h�̎擾
	static	CGame		*GetGame();							// �Q�[���̎擾
	static	CSound		*GetSound();						// �T�E���h�̎擾

private:
	/* �ÓI�����o�ϐ� */
	static	MODE		m_mode;									// ���݂̃��[�h
	static	CRenderer	*m_pRenderer;							// �����_���[�̃|�C���^
	static	CKeyboard	*m_pKeyboard;							// ���͂̃|�C���^
	static	CXinputGpad	*m_pXinputGpad;							// �Q�[���p�b�h�̃|�C���^
	static	CGame		*m_pGame;								// �Q�[���N���X�̃|�C���^
	static	CTitle		*m_pTitle;								// �^�C�g���N���X�̃|�C���^
	static	CResult		*m_pResult;								// �Q�[���N���X�̃|�C���^
	static	CRanking	*m_pRanking;							// �����L���O�N���X�̃|�C���^
	static	CSound		*m_pSound;								// �T�E���h�N���X�̃|�C���^
};
#endif