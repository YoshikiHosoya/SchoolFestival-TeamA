//==========================================================
// �Q�[���p�b�h���� [gamepad.cpp]:NORI
//==========================================================

//==========================================================
//�C���N���[�h
//==========================================================
#include "XInputPad.h"
#include "manager.h"
//==========================================================
//�ÓI�����o�ϐ��̏�����
//==========================================================

//==========================================================
//�R���X�g���N�^
//==========================================================
CXInputPad::CXInputPad()
{
	m_Controller = CONTROLLER::P1;
	m_bVibration = false;
	m_nCntVibration = 0;
	Oldstate = 0;
}

//==========================================================
//�f�X�g���N�^
//==========================================================
CXInputPad::~CXInputPad()
{
}
//==========================================================
//������
//==========================================================
HRESULT CXInputPad::Init(HINSTANCE hInstance, HWND hWnd, CONTROLLER Controller)
{
	m_Controller = Controller;
	return TRUE;
}
//==========================================================
//�I��
//==========================================================
void CXInputPad::Uninit(void)
{
	XInputEnable(false);
}
//==========================================================
//�X�V
//==========================================================
void CXInputPad::Update(void)
{
	//�O��̓��͏���ۑ�
	Oldstate = m_pState.Gamepad.wButtons;
	//������
	ZeroMemory(&m_pState, sizeof(XINPUT_STATE));

	// XInput�̓��͏��擾
	DWORD dwResult = XInputGetState((int)m_Controller, &m_pState);

	//�ڑ�����Ă��邩
	if (dwResult == ERROR_SUCCESS)
	{
		//connected
		m_bConnect = true;
	}
	else
	{
		//not connected
		m_bConnect = false;
	}

	// �X�e�B�b�N�̓��͂��ア���͂O�ɂ��Ƃ� �i�f�b�h�]�[���ݒ�j
	if ((m_pState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_pState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_pState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_pState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_pState.Gamepad.sThumbLX = 0;
		m_pState.Gamepad.sThumbLY = 0;
	}

	//�o�C�u���[�V�����̍\����
	XINPUT_VIBRATION vibration;

	//�o�C�u���[�V�����̒l������
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;

	//�o�C�u���[�V�������邨t�C
	if (m_bVibration)
	{
		//�J�E���g�_�E��
		m_nCntVibration--;

		//0�ɂȂ������~
		if (m_nCntVibration <= 0)
		{
			m_bVibration = false;
		}

		//�U������̂̓Q�[�����̂�
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			//�U���̃p�����[�^�ݒ�
			vibration.wLeftMotorSpeed = 65535;
			vibration.wRightMotorSpeed = 65535;
		}
	}


	//�W���C�X�e�B�b�N�Ƀo�C�u���[�^�f�[�^�𑗐M�B
	XInputSetState(0, &vibration);
}
//==========================================================
//����
//==========================================================
bool CXInputPad::GetTrigger(XINPUT_KEY Button, size_t Frame)
{
	//1F�O�͓��͂���Ă��炸�����͂���Ă��鎞
	if (m_pState.Gamepad.wButtons & Button && !(Oldstate & Button))
	{
		//true
		return true;
	}

	if (Button == XINPUT_KEY::JOYPADKEY_L2)
	{
		if (m_pState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && Oldstate <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			// ���g���K�[�������ꂽ
			return true;
		}
	}

	if (Button == XINPUT_KEY::JOYPADKEY_R2)
	{
		if (m_pState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && Oldstate <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			// ���g���K�[�������ꂽ
			return true;
		}
	}

	//false
	return false;
}

//==========================================================
//����
//==========================================================
bool CXInputPad::GetPress(XINPUT_KEY Button)
{
	//���͂���Ă鎞
	if (m_pState.Gamepad.wButtons & Button)
	{
		//true
		return true;
	}

	if (Button == XINPUT_KEY::JOYPADKEY_L2)
	{
		if (m_pState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			// ���g���K�[�������ꂽ
			return true;
		}
	}

	if (Button == XINPUT_KEY::JOYPADKEY_R2)
	{
		if (m_pState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			// ���g���K�[�������ꂽ
			return true;
		}
	}
	//false
	return false;
}

//==========================================================
//���X�e�B�b�N�̓��͎擾
//==========================================================
void CXInputPad::GetStickLeft(float * pValueX, float * pValueZ)
{
	*pValueX = m_pState.Gamepad.sThumbLX;
	*pValueZ = m_pState.Gamepad.sThumbLY;

}
//==========================================================
//�E�X�e�B�b�N�̓��͎擾
//==========================================================
void CXInputPad::GetStickRight(float * pValueX, float * pValueZ)
{
	*pValueX = m_pState.Gamepad.sThumbRX;
	*pValueZ = m_pState.Gamepad.sThumbRY;
}