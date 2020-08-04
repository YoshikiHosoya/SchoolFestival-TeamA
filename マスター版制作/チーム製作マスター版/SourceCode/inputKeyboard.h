#pragma once
//=============================================================================
// 入力処理 [input.h]
// Author : hanzawa
//=============================================================================
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

#define _CRT_SECURE_NO_WARNINGS

//========================================
// インクルードファイル
//========================================
#include "main.h"
#include "manager.h"
#define	NUM_KEY_MAX			(256)	// キーの最大数
//========================================
// プロトタイプ宣言
//========================================
class CKeyboard 
{
public:
	CKeyboard();
	~CKeyboard();
	HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
	void UninitInput(void);
	void UpdateInput(void);
	bool GetKeyboardPress(int nKey);
	bool GetKeyboardTrigger(int nKey);
	int KeyTF;
private:
	LPDIRECTINPUT8 m_pInput = NULL;
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard = NULL;
	BYTE m_aKeyTrigger[256];
	BYTE m_aKeyState[NUM_KEY_MAX];
};


#endif