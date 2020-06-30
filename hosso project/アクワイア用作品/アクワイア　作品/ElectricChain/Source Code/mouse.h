//-----------------------------------------------------------------------------
// �}�E�X���� [mouse.h]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#ifndef _MOUSE_H_
#define _MOUSE_H_

#define _CRT_SECURE_NO_WARNINGS

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "main.h"
#include "input.h"

//-----------------------------------------------------------------------------
// �}�N����`
//-----------------------------------------------------------------------------
#define	NUM_BUTTON_MAX			(8)		// �{�^��(�}�E�X)�̍ő吔

//-----------------------------------------------------------------------------
// �N���X��`
//-----------------------------------------------------------------------------
class CMouse : public CInput
{
public :
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//����������
	void Uninit();									//�I������
	void Update();									//�X�V����
	bool GetPress(int nButton) { return (m_mouseState.rgbButtons[nButton] & 0x80) ? true : false; };					//�v���X����
	bool GetTrigger(int nButton) { return (m_aButtonStateTrigger[nButton] & 0x80) ? true : false; };					//�g���K�[����
	bool GetRelease(int nButton) { return (m_aButtonStateRelease[nButton] & 0x80) ? true : false; };					//�����[�X����
	D3DXVECTOR2 GetMousePos() { return D3DXVECTOR2(m_mousepos.x, m_mousepos.y); };



private:
	DIMOUSESTATE2 m_mouseState;						//�}�E�X���
	D3DXVECTOR2 m_mousepos;							//�}�E�X���W

	LPDIRECTINPUT8			m_pMouseput = NULL;						// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8	m_pDevMouse = NULL;						// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^
	BYTE					m_aButtonState[NUM_BUTTON_MAX];			// �}�E�X�̓��͏�񃏁[�N
	BYTE					m_aButtonStateTrigger[NUM_BUTTON_MAX];	// �}�E�X�̃g���K�[
	BYTE					m_aButtonStateRelease[NUM_BUTTON_MAX];	// �}�E�X�̕������u��

	HWND					m_hWnd;									// �E�B���h�E�n���h��

};
#endif
