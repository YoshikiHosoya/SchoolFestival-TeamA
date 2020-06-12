// =====================================================================================================================================================================
//
// Xinput�W���C�p�b�h���� [xinputGpad.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "xinputGpad.h"						// �C���N���[�h�t�@�C��
#include "debugproc.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MAX_STICK_VALUE	(32767)			// �X�e�B�b�N�̍ő�l

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CXinputGpad::Update(void)
{
	// �ߋ��̏�Ԃ̕ۑ�
	m_stateOld = m_state;

	ZeroMemory(&m_state, sizeof(XINPUT_STATE));
	DWORD dwResult = XInputGetState(0, &m_state);

	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		CDebugProc::Print("Connect!!!!\n\n");
	}
	else
	{
		// Controller is not connected
		CDebugProc::Print("Not Connect!!!!\n\n");
	}

	// ���X�e�B�b�N�̃f�b�h�]�[�����̓��͂�0�ɂ���
	if ((m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;
	}

	// �E�X�e�B�b�N�̃f�b�h�]�[�����̓��͂�0�ɂ���
	if ((m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;
	}

	// �X�e�B�b�N�̍��������ꂽ
	if ((m_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		m_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ||
		(m_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE||
		m_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		CDebugProc::Print("���X�e�B�b�N X ( %f )\n", (float)m_state.Gamepad.sThumbLX);
		CDebugProc::Print("���X�e�B�b�N Y ( %f )\n", (float)m_state.Gamepad.sThumbLY);
	}

	// �X�e�B�b�N�̍��������ꂽ
	if ((m_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		m_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ||
		(m_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
			m_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		CDebugProc::Print("�E�X�e�B�b�N X ( %f )\n", (float)m_state.Gamepad.sThumbRX);
		CDebugProc::Print("�E�X�e�B�b�N Y ( %f )\n", (float)m_state.Gamepad.sThumbRY);
	}
}

// =====================================================================================================================================================================
//
// Xinput�̃v���X����
//
// =====================================================================================================================================================================
bool CXinputGpad::GetPressXinputGpad(XINPUT_CONTROLLER nKey)
{
	return (m_state.Gamepad.wButtons & nKey) ? true : false;

}

// =====================================================================================================================================================================
//
// Xinput�̃g���K�[����
//
// =====================================================================================================================================================================
bool CXinputGpad::GetTriggerXinputGpad(XINPUT_CONTROLLER nKey)
{
	if (m_state.Gamepad.wButtons != m_stateOld.Gamepad.wButtons)
	{
		return (m_state.Gamepad.wButtons & nKey) ? true : false;
	}
	else
	{
		return false;
	}
}

// =====================================================================================================================================================================
//
// ���X�e�B�b�N�̒l�̎擾
//
// =====================================================================================================================================================================
void CXinputGpad::GetLeftStickValue(float & sThumbX, float & sThumbY)
{
	// �X�e�B�b�N�̒l���ő�l�Ŋ���
	sThumbX = (float)m_state.Gamepad.sThumbLX / MAX_STICK_VALUE;
	sThumbY = (float)m_state.Gamepad.sThumbLY / MAX_STICK_VALUE;
}

// =====================================================================================================================================================================
//
// �E�X�e�B�b�N�̒l�̎擾
//
// =====================================================================================================================================================================
void CXinputGpad::GetRightStickValue(float & sThumbX, float & sThumbY)
{
	// �X�e�B�b�N�̒l���ő�l�Ŋ���
	sThumbX = (float)m_state.Gamepad.sThumbRX / MAX_STICK_VALUE;
	sThumbY = (float)m_state.Gamepad.sThumbRY / MAX_STICK_VALUE;
}

// =====================================================================================================================================================================
//
// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�
//
// =====================================================================================================================================================================
WORD CXinputGpad::ThumbToDPad(float sThumbX, float sThumbY, float sDeadZone)
{
	WORD wButtons = 0;

	if (sThumbY >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_UP;
	}
	else if (sThumbY <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
	}

	if (sThumbX <= -sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
	}
	else if (sThumbX >= sDeadZone)
	{
		wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
	}


	// ���X�e�B�b�N����̓��͂�����p�b�h�ɕϊ�
	//m_state.Gamepad.wButtons |= ThumbToDPad(m_state.Gamepad.sThumbLX, m_state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

	return wButtons;
}