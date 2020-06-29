//------------------------------------------------------------------------------
//
//���͏���  [input.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "dinput.h"
#include <XInput.h>

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CInput
{
public:
	CInput();			//�R���X�g���N�^
	virtual ~CInput();	//�R���X�g���N�^

	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	virtual void Uninit();									//�I��
	virtual void Update() = 0;								//�X�V

protected:
	static LPDIRECTINPUT8 m_pInput;							//Input
};

#endif