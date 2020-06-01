//=============================================================================
//
// �}�E�X���� [mouse.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _MOUSE_H_
#define _MOUSE_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �}�N����`
//=============================================================================
#define	NUM_BUTTON_MAX (8)		// �{�^��(�}�E�X)�̍ő吔

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "input.h"

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CMouse : public CInput
{
public:
	/* �֐� */
	CMouse();
	~CMouse();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Update(void);
	void Uninit(void);
	bool GetPress(int nButton);		// ������Ă�����擾
	bool GetTrigger(int nButton);	// ���������擾
	bool GetDouble(int nButton);	// �_�u���N���b�N���擾
	LONG GetX(void);				// X���W�擾
	LONG GetY(void);				// Y���W�擾
	BYTE GetButton(void);
	D3DXVECTOR3 GetPos(void);		// ���W�擾

protected:
private:
	DIMOUSESTATE2			m_mouse;
	LPDIRECTINPUTDEVICE8	m_pDevice;					// ���̓f�o�C�X(�}�E�X)�ւ̃|�C���^
	BYTE					m_aPress[NUM_BUTTON_MAX];	// �}�E�X�̓��͏�񃏁[�N
	BYTE					m_aTrigger[NUM_BUTTON_MAX];	// �}�E�X�̃g���K�[
	BYTE					m_aDouble[NUM_BUTTON_MAX];	// �}�E�X�̃I���I�t
	HWND					m_hWnd;						// �E�B���h�E�n���h��
	D3DXVECTOR3				m_pos;						// �}�E�X�̍��W
};

#endif
