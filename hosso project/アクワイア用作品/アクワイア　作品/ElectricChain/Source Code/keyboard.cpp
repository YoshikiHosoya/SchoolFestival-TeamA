//------------------------------------------------------------------------------
//
//�L�[�{�[�h����  [keyboard.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "keyboard.h"
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CKeyboard::CKeyboard()
{
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CKeyboard::~CKeyboard()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CKeyboard::Init(HINSTANCE hInstance, HWND hWnd)
{
	CInput::Init(hInstance ,hWnd);

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		//���s
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		//���s
		return E_FAIL;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		//���s
		return E_FAIL;
	}
	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	m_pDevKeyboard->Acquire();

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CKeyboard::Uninit()
{
	CInput::Uninit();

	// ���̓f�o�C�X(�L�[�{�[�h)�̊J��
	if (m_pDevKeyboard != NULL)
	{
		m_pDevKeyboard->Unacquire();
		m_pDevKeyboard->Release();
		m_pDevKeyboard = NULL;
	}
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CKeyboard::Update()
{
	//�ϐ��錾
	BYTE aKeyState[NUM_KEY_MAX];	//�L�[����

	// �f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (int nCntkey = 0; nCntkey < NUM_KEY_MAX; nCntkey++)
		{
			//�g���K�[����
			m_aKeyStateTrigger[nCntkey] = (aKeyState[nCntkey] ^ m_aKeyState[nCntkey]) & aKeyState[nCntkey];

			m_aKeyState[nCntkey] = aKeyState[nCntkey];
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();
	}
}
//------------------------------------------------------------------------------
//�v���X�擾����
//------------------------------------------------------------------------------
bool CKeyboard::GetPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}
//------------------------------------------------------------------------------
//�g���K�[�擾����
//------------------------------------------------------------------------------
bool CKeyboard::GetTrigger(int nKey)
{
	return(m_aKeyStateTrigger[nKey] & 0x80) ? true : false;
}
