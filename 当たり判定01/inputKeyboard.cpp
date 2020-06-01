//====================================================
// ���͏��� [Keyboard.cpp]
// Author : hanzawa
//====================================================
#include "inputKeyboard.h"
CKeyboard::CKeyboard()
{
}
CKeyboard::~CKeyboard()
{
}
//====================================================
// �L�[�{�[�h�̏�����
//====================================================
HRESULT CKeyboard::InitInput(HINSTANCE hInstance, HWND hWnd)
{
	KeyTF = 0;
	// DirectInput�I�u�W�F�N�g�̍쐬
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	// ���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevKeyboard->Acquire();
	return S_OK;
}

//======================================================
// �L�[�{�[�h�̏I������
//======================================================
void CKeyboard::UninitInput(void)
{
}
//======================================================
// �L�[�{�[�h�̍X�V����
//======================================================
void CKeyboard::UpdateInput(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//�L�[�v���X���
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();						//�L�[�{�[�h�ւ̃A�N�Z�X�����擾
	}
}
//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool CKeyboard::GetKeyboardTrigger(int nKey)
{
	return(m_aKeyTrigger[nKey] & 0x80) ? true : false;
}
bool CKeyboard::GetKeyboardPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}