//-----------------------------------------------------------------------------
//
// �}�E�X���� [mouse.cpp]
// Author : Yohsiki Hosoya
//
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "mouse.h"

//-----------------------------------------------------------------------------
// ������
//-----------------------------------------------------------------------------
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)& m_pMouseput, NULL)))
	{
		return E_FAIL;
	}

	m_pMouseput->CreateDevice(GUID_SysMouse, &m_pDevMouse, NULL);
	m_pDevMouse->SetDataFormat(&c_dfDIMouse2); // �}�E�X�p�̃f�[�^�E�t�H�[�}�b�g��ݒ�

	m_pDevMouse->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);

	// �f�o�C�X�̐ݒ�
	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = DIPROPAXISMODE_REL; // ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
	m_pDevMouse->SetProperty(DIPROP_AXISMODE, &diprop.diph);

	// ���͐���J�n
	m_pDevMouse->Acquire();

	// ���
	m_hWnd = hWnd;

	return S_OK;
}
//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CMouse::Uninit()
{

	// ���̓f�o�C�X(�}�E�X)�̊J��
	if (m_pDevMouse != NULL)
	{
		m_pDevMouse->Unacquire();	// �}�E�X�ւ̃A�N�Z�X�����J��
		m_pDevMouse->Release();
		m_pDevMouse = NULL;
	}
	// DirectInput�I�u�W�F�N�g�̊J��
	if (m_pMouseput != NULL)
	{
		m_pMouseput->Release();
		m_pMouseput = NULL;
	}
}
//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CMouse::Update()
{
	// �ϐ��錾
	int nCntButton;
	POINT point;

	// �l�̏�����
	m_mouseState.rgbButtons[0] = 0;

	GetCursorPos(&point);
	ScreenToClient(m_hWnd, &point);
	m_mousepos.x = (float)point.x;
	m_mousepos.y = (float)point.y;



	// �l�̍X�V
	if (SUCCEEDED(m_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &m_mouseState)))
	{
		for (nCntButton = 0; nCntButton < NUM_BUTTON_MAX; nCntButton++)
		{
			// �r���I�_���a���ǂ������f
			m_aButtonStateTrigger[nCntButton] = (m_aButtonState[nCntButton] ^ m_mouseState.rgbButtons[nCntButton]) & m_mouseState.rgbButtons[nCntButton];
			m_aButtonStateRelease[nCntButton] = (m_aButtonState[nCntButton] ^ m_mouseState.rgbButtons[nCntButton]) & m_aButtonState[nCntButton];

			m_aButtonState[nCntButton] = m_mouseState.rgbButtons[nCntButton];	// �L�[�v���X���ۑ�
		}
	}
	else
	{
		m_pDevMouse->Acquire(); // �P���ڂ�Q���ڂɃG���[���o�邪�������Ă悢�B
	}
}

