#pragma once
//==========================================================
// ゲームパッド処理 [Xinput.h]
//==========================================================
#ifndef _GAMEPAD_XINPUT_H_
#define _GAMEPAD_XINPUT_H_
//==========================================================
// インクルードファイル
//==========================================================
#include "main.h"

//==========================================================
// マクロ定義
//==========================================================
#define MAX_SAVE_KEYSTATE (60)		//キーを保存する最大値
#define STICK_MAX_RANGE (32768.0f)
//==========================================================
//クラス定義
//==========================================================
class CXInputPad
{
public:
	CXInputPad();
	~CXInputPad();

	//入力キー
	enum XINPUT_KEY
	{
		JOYPADKEY_UP	 = XINPUT_GAMEPAD_DPAD_UP,			//十字キー ↑
		JOYPADKEY_DOWN	 = XINPUT_GAMEPAD_DPAD_DOWN,		//十字キー ↓
		JOYPADKEY_LEFT	 = XINPUT_GAMEPAD_DPAD_LEFT,		//十字キー ←
		JOYPADKEY_RIGHT	 = XINPUT_GAMEPAD_DPAD_RIGHT,		//十字キー →
		JOYPADKEY_START	 = XINPUT_GAMEPAD_START,			//START
		JOYPADKEY_BACK	 = XINPUT_GAMEPAD_BACK,				//BACK
		JOYPADKEY_L1	 = XINPUT_GAMEPAD_LEFT_THUMB,		//L1
		JOYPADKEY_R1	 = XINPUT_GAMEPAD_RIGHT_THUMB,		//R1
		JOYPADKEY_L2	 = XINPUT_GAMEPAD_LEFT_SHOULDER,	//L2
		JOYPADKEY_R2	 = XINPUT_GAMEPAD_RIGHT_SHOULDER,	//R2
		JOYPADKEY_A		 = XINPUT_GAMEPAD_A,				//A
		JOYPADKEY_B		 = XINPUT_GAMEPAD_B,				//B
		JOYPADKEY_X		 = XINPUT_GAMEPAD_X,				//X
		JOYPADKEY_Y		 = XINPUT_GAMEPAD_Y,				//Y
	};

	HRESULT Init(HINSTANCE hInstance, HWND hWnd, CONTROLLER Controller);	//初期化
	void Uninit(void);								//終了
	void Update(void);								//更新

	bool GetTrigger(XINPUT_KEY Button, size_t Frame);
	bool GetPress(XINPUT_KEY Button);
	void GetStickLeft(float *pValueX, float *pValueZ);		//左スティック値取得
	void GetStickRight(float *pValueX, float *pValueZ);		//右スティック値取得
	bool GetConnect() { return m_bConnect; };		//コントローラが接続されているかどうか

													//バイブレーション関係
	void StartVibration(int nCnt) { m_bVibration = true, m_nCntVibration = nCnt; };		//バイブレーション開始
	void EndVibration() { m_bVibration = false; };								//バイブレーション終了

private:
	XINPUT_STATE m_pState;							//現在のコントローラの状態
	WORD Oldstate;
	bool m_bVibration;								//バイブレーションしてるかどうか
	bool m_bConnect;								//コントローラーが接続されているかどうか
	int m_nCntVibration;							//バイブレーション用のカウント
	CONTROLLER	m_Controller;						//コントローラータグ
};

#endif