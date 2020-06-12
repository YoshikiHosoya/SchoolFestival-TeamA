// =====================================================================================================================================================================
//
// Xinputジョイパッド処理 [xinputGpad.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "xinputGpad.h"						// インクルードファイル
#include "debugproc.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MAX_STICK_VALUE	(32767)			// スティックの最大値

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CXinputGpad::Update(void)
{
	// 過去の状態の保存
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

	// 左スティックのデッドゾーン内の入力を0にする
	if ((m_state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		m_state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			m_state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbLX = 0;
		m_state.Gamepad.sThumbLY = 0;
	}

	// 右スティックのデッドゾーン内の入力を0にする
	if ((m_state.Gamepad.sThumbRX <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
		m_state.Gamepad.sThumbRX > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) &&
		(m_state.Gamepad.sThumbRY <  XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE &&
			m_state.Gamepad.sThumbRY > -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		m_state.Gamepad.sThumbRX = 0;
		m_state.Gamepad.sThumbRY = 0;
	}

	// スティックの左が押された
	if ((m_state.Gamepad.sThumbLX <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
		m_state.Gamepad.sThumbLX >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ||
		(m_state.Gamepad.sThumbLY <= -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE||
		m_state.Gamepad.sThumbLY >= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		CDebugProc::Print("左スティック X ( %f )\n", (float)m_state.Gamepad.sThumbLX);
		CDebugProc::Print("左スティック Y ( %f )\n", (float)m_state.Gamepad.sThumbLY);
	}

	// スティックの左が押された
	if ((m_state.Gamepad.sThumbRX <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
		m_state.Gamepad.sThumbRX >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ||
		(m_state.Gamepad.sThumbRY <= -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
			m_state.Gamepad.sThumbRY >= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE))
	{
		CDebugProc::Print("右スティック X ( %f )\n", (float)m_state.Gamepad.sThumbRX);
		CDebugProc::Print("右スティック Y ( %f )\n", (float)m_state.Gamepad.sThumbRY);
	}
}

// =====================================================================================================================================================================
//
// Xinputのプレス入力
//
// =====================================================================================================================================================================
bool CXinputGpad::GetPressXinputGpad(XINPUT_CONTROLLER nKey)
{
	return (m_state.Gamepad.wButtons & nKey) ? true : false;

}

// =====================================================================================================================================================================
//
// Xinputのトリガー入力
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
// 左スティックの値の取得
//
// =====================================================================================================================================================================
void CXinputGpad::GetLeftStickValue(float & sThumbX, float & sThumbY)
{
	// スティックの値を最大値で割る
	sThumbX = (float)m_state.Gamepad.sThumbLX / MAX_STICK_VALUE;
	sThumbY = (float)m_state.Gamepad.sThumbLY / MAX_STICK_VALUE;
}

// =====================================================================================================================================================================
//
// 右スティックの値の取得
//
// =====================================================================================================================================================================
void CXinputGpad::GetRightStickValue(float & sThumbX, float & sThumbY)
{
	// スティックの値を最大値で割る
	sThumbX = (float)m_state.Gamepad.sThumbRX / MAX_STICK_VALUE;
	sThumbY = (float)m_state.Gamepad.sThumbRY / MAX_STICK_VALUE;
}

// =====================================================================================================================================================================
//
// スティックの入力を方向パッドフラグに変換
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


	// 左スティックからの入力を方向パッドに変換
	//m_state.Gamepad.wButtons |= ThumbToDPad(m_state.Gamepad.sThumbLX, m_state.Gamepad.sThumbLY, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

	return wButtons;
}