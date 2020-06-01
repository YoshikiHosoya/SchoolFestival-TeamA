// ------------------------------------------
//
// ���̓w�b�_�[���� [keyboard.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ------------------------------------------
#include "main.h"
#include "input.h"

// ------------------------------------------
//
// �}�N����`
//
// ------------------------------------------
#define	NUM_KEY_MAX			(256)	// �L�[�̍ő吔

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CKeyboard : public CInput
{
public:
	/* �֐� */
	CKeyboard();
	~CKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetKeyboardPress(int nKey);	// ������Ă�����擾
	bool GetKeyboardTrigger(int nKey);	// ���������擾
	bool GetKeyboardDetach(int nKey);	// ���������擾

protected:
private:
	LPDIRECTINPUTDEVICE8 m_pDevice;	// ���̓f�o�C�X�ւ̃|�C���^
	BYTE m_aState[NUM_KEY_MAX];		// ���͂��Ă�����
	BYTE m_aTrigger[NUM_KEY_MAX];	// ���͎����
	BYTE m_aDetach[NUM_KEY_MAX];	//�������Ƃ��̏��
};
#endif
