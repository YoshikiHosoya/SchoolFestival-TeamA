//------------------------------------------------------------------------------
//
//�L�[�{�[�h����  [keyboard.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "input.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define	NUM_KEY_MAX		(256)	// �L�[�̍ő吔
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CKeyboard : public CInput
{
public:
	CKeyboard();
	~CKeyboard();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit();									//�I��
	void Update();									//�X�V
	bool GetPress(int nKey);						//�v���X����
	bool GetTrigger(int nKey);						//�g���K�[����

private:
	LPDIRECTINPUTDEVICE8	m_pDevKeyboard = NULL;
	BYTE					m_aKeyState[NUM_KEY_MAX];
	BYTE					m_aKeyStateTrigger[NUM_KEY_MAX];

};

#endif