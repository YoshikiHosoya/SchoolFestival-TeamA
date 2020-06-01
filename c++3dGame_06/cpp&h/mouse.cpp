//=============================================================================
//
// ���͏��� [mouse.cpp]
// Author : Fujiwara Masato
//
//=============================================================================

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "mouse.h"

// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CMouse::CMouse()
{
}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CMouse::~CMouse()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMouse::Init(HINSTANCE hInstance, HWND hWnd)
{
	// �ϐ��錾
	DIPROPDWORD diprop;

	// ���̓f�o�C�X�̏�����
	CInput::Init(hInstance,hWnd);

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̍쐬
	if (FAILED(m_pInput->CreateDevice(GUID_SysMouse, &m_pDevice, NULL)))
	{
		return E_FAIL;
	}
	// �}�E�X�p�̃f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevice->SetDataFormat(&c_dfDIMouse2)))
	{
		return E_FAIL;
	}
	// �����ݒ�
	if (FAILED(m_pDevice->SetCooperativeLevel(hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		return E_FAIL;
	}

	/* ----------diprop�̐ݒ�---------- */
	diprop.diph.dwSize = sizeof(diprop);			// diprop�\���̂̃������T�C�Y���i�[
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);	// diph�\���̂̃������T�C�Y���i�[
	diprop.diph.dwObj = 0;							// �}�E�X���̏�����
	diprop.diph.dwHow = DIPH_DEVICE;
	//diprop.dwData = DIPROPAXISMODE_REL;			// ���Βl���[�h�Őݒ�i��Βl��DIPROPAXISMODE_ABS�j
	// �}�E�X�f�o�C�X�̐ݒ�X�V
	m_pDevice->SetProperty(DIPROP_AXISMODE, &diprop.diph);
	// ���͐���J�n
	m_pDevice->Acquire();

	// Window���擾
	m_hWnd = hWnd;
	return S_OK;
}

//=============================================================================
// �X�V����
//=============================================================================
void CMouse::Update(void)
{
	// �ϐ��錾
	POINT point;

	// �J�[�\���̈ʒu���擾
	GetCursorPos(&point);
	// �X�N���[����̈ʒu���ɕϊ�
	ScreenToClient(m_hWnd, &point);
	/* �}�E�X�̈ʒu���i�[ */
	m_mouse.lX = point.x;	// x���W
	m_mouse.lY = point.y;	// y���W

	m_pos = D3DXVECTOR3(m_mouse.lX, m_mouse.lY,0.0f);

	// �}�E�X�̏����擾�o������
	if (SUCCEEDED(m_pDevice->GetDeviceState(sizeof(DIMOUSESTATE2), &m_mouse)))
	{
		for (int nCntButton = 0; nCntButton < NUM_BUTTON_MAX; nCntButton++)
		{
			// �l�̏�����
			m_mouse.rgbButtons[nCntButton] = 0;

			// �r���I�_���a���ǂ������f
			m_aTrigger[nCntButton] = (m_aPress[nCntButton] ^ m_mouse.rgbButtons[nCntButton]) & m_mouse.rgbButtons[nCntButton];
			m_aDouble[nCntButton] = (m_aPress[nCntButton] ^ m_mouse.rgbButtons[nCntButton]);
			m_aPress[nCntButton] = m_mouse.rgbButtons[nCntButton];	// �L�[�v���X���ۑ�
		}
	}
	// �o���Ȃ�������
	else
	{
		m_pDevice->Acquire(); // �P���ڂ�Q���ڂɃG���[���o�邪�������Ă悢�B
	}
}

//=============================================================================
// �I������
//=============================================================================
void CMouse::Uninit(void)
{
	// ���̓f�o�C�X�̏I��
	CInput::Uninit();
	// �}�E�X�f�o�C�X�̏I��
	if (m_pDevice != NULL)
	{
		m_pDevice->Unacquire();	// �}�E�X�ւ̃A�N�Z�X�����J��
		m_pDevice->Release();
		m_pDevice = NULL;
	}
}

//=============================================================================
// ������Ă�����擾����
//=============================================================================
bool CMouse::GetPress(int nButton)
{
	return (m_mouse.rgbButtons[nButton] & 0x80) ? true : false;
}

//=============================================================================
// ���������擾����
//=============================================================================
bool CMouse::GetTrigger(int nButton)
{
	return (m_aTrigger[nButton] & 0x80) ? true : false;
}

//=============================================================================
// �_�u���N���b�N���擾����
//=============================================================================
bool CMouse::GetDouble(int nButton)
{
	return (m_aDouble[nButton] & 0x80) ? true : false;
}

//=============================================================================
// X���W�擾����
//=============================================================================
LONG CMouse::GetX(void)
{
	return m_mouse.lX;
}

//=============================================================================
// Y���W�擾����
//=============================================================================
LONG CMouse::GetY(void)
{
	return m_mouse.lY;
}

BYTE CMouse::GetButton(void)
{
	return m_mouse.rgbButtons[0];
}

//=============================================================================
// ���W�擾����
//=============================================================================
D3DXVECTOR3 CMouse::GetPos(void)
{
	return m_pos;
}

