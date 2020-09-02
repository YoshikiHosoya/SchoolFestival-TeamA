//==========================================================
// ゲームパッド処理 [gamepad.cpp]:NORI
//==========================================================

//==========================================================
//インクルード
//==========================================================
#include "XInputPad.h"
#include "manager.h"
//==========================================================
//静的メンバ変数の初期化
//==========================================================

//==========================================================
//コンストラクタ
//==========================================================
CXInputPad::CXInputPad()
{
	m_Controller = CONTROLLER::P1;
	m_bVibration = false;
	m_nCntVibration = 0;
	Oldstate = 0;
}

//==========================================================
//デストラクタ
//==========================================================
CXInputPad::~CXInputPad()
{
}
//==========================================================
//初期化
//==========================================================
HRESULT CXInputPad::Init(HINSTANCE hInstance, HWND hWnd, CONTROLLER Controller)
{
	m_Controller = Controller;
	return TRUE;
}
//==========================================================
//終了
//==========================================================
void CXInputPad::Uninit(void)
{
	XInputEnable(false);
}
//==========================================================
//更新
//==========================================================
void CXInputPad::Update(void)
{
	//前回の入力情報を保存
	Oldstate = m_pState.Gamepad.wButtons;
	//初期化
	ZeroMemory(&m_pState, sizeof(XINPUT_STATE));

	// XInputの入力情報取得
	DWORD dwResult = XInputGetState((int)m_Controller, &m_pState);

	//接続されているか
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

	// スティックの入力が弱い時は０にしとく （デッドゾーン設定）
	if ((m_pState.Gamepad.sThumbLX < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_pState.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(m_pState.Gamepad.sThumbLY < XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE && m_pState.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		m_pState.Gamepad.sThumbLX = 0;
		m_pState.Gamepad.sThumbLY = 0;
	}

	//バイブレーションの構造体
	XINPUT_VIBRATION vibration;

	//バイブレーションの値初期化
	vibration.wLeftMotorSpeed = 0;
	vibration.wRightMotorSpeed = 0;

	//バイブレーションするおt気
	if (m_bVibration)
	{
		//カウントダウン
		m_nCntVibration--;

		//0になったら停止
		if (m_nCntVibration <= 0)
		{
			m_bVibration = false;
		}

		//振動するのはゲーム中のみ
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			//振動のパラメータ設定
			vibration.wLeftMotorSpeed = 65535;
			vibration.wRightMotorSpeed = 65535;
		}
	}


	//ジョイスティックにバイブレータデータを送信。
	XInputSetState(0, &vibration);
}
//==========================================================
//入力
//==========================================================
bool CXInputPad::GetTrigger(XINPUT_KEY Button, size_t Frame)
{
	//1F前は入力されておらず今入力されている時
	if (m_pState.Gamepad.wButtons & Button && !(Oldstate & Button))
	{
		//true
		return true;
	}

	if (Button == XINPUT_KEY::JOYPADKEY_L2)
	{
		if (m_pState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && Oldstate <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			// 左トリガーが押された
			return true;
		}
	}

	if (Button == XINPUT_KEY::JOYPADKEY_R2)
	{
		if (m_pState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD && Oldstate <= XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			// 左トリガーが押された
			return true;
		}
	}

	//false
	return false;
}

//==========================================================
//入力
//==========================================================
bool CXInputPad::GetPress(XINPUT_KEY Button)
{
	//入力されてる時
	if (m_pState.Gamepad.wButtons & Button)
	{
		//true
		return true;
	}

	if (Button == XINPUT_KEY::JOYPADKEY_L2)
	{
		if (m_pState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			// 左トリガーが押された
			return true;
		}
	}

	if (Button == XINPUT_KEY::JOYPADKEY_R2)
	{
		if (m_pState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
		{
			// 左トリガーが押された
			return true;
		}
	}
	//false
	return false;
}

//==========================================================
//左スティックの入力取得
//==========================================================
void CXInputPad::GetStickLeft(float * pValueX, float * pValueZ)
{
	*pValueX = m_pState.Gamepad.sThumbLX;
	*pValueZ = m_pState.Gamepad.sThumbLY;

}
//==========================================================
//右スティックの入力取得
//==========================================================
void CXInputPad::GetStickRight(float * pValueX, float * pValueZ)
{
	*pValueX = m_pState.Gamepad.sThumbRX;
	*pValueZ = m_pState.Gamepad.sThumbRY;
}