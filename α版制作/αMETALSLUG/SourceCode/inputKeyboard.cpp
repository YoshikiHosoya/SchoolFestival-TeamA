//====================================================
// 入力処理 [Keyboard.cpp]
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
// キーボードの初期化
//====================================================
HRESULT CKeyboard::InitInput(HINSTANCE hInstance, HWND hWnd)
{
	KeyTF = 0;
	// DirectInputオブジェクトの作成
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}
	// 入力デバイス（キーボード）の作成
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	// データフォーマットを設定
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}
	// キーボードへのアクセス権を獲得(入力制御開始)
	m_pDevKeyboard->Acquire();
	return S_OK;
}

//======================================================
// キーボードの終了処理
//======================================================
void CKeyboard::UninitInput(void)
{
}
//======================================================
// キーボードの更新処理
//======================================================
void CKeyboard::UpdateInput(void)
{
	BYTE aKeyState[NUM_KEY_MAX];
	int nCntKey;
	// デバイスからデータを取得
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_aKeyTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyState[nCntKey] = aKeyState[nCntKey];	//キープレス情報
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();						//キーボードへのアクセス権を取得
	}
}
//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool CKeyboard::GetKeyboardTrigger(int nKey)
{
	return(m_aKeyTrigger[nKey] & 0x80) ? true : false;
}
bool CKeyboard::GetKeyboardPress(int nKey)
{
	return(m_aKeyState[nKey] & 0x80) ? true : false;
}