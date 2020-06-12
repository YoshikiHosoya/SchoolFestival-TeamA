// =====================================================================================================================================================================
//
// Xinputジョイパッド処理 [xinputGpad.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _XINPUTGPAD_H_
#define _XINPUTGPAD_H_

#define _CRT_SECURE_NO_WARNINGS

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include"main.h"
#include"input.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// ゲームパッドクラス
// =====================================================================================================================================================================
class CXinputGpad : public CInput
{
public:
	// Xinputの操作キー
	enum XINPUT_CONTROLLER
	{
		XINPUT_UP				= XINPUT_GAMEPAD_DPAD_UP,				// 十字キー 上
		XINPUT_DOWN				= XINPUT_GAMEPAD_DPAD_DOWN,				// 十字キー 下
		XINPUT_LEFT				= XINPUT_GAMEPAD_DPAD_LEFT,				// 十字キー 左
		XINPUT_RIGHT			= XINPUT_GAMEPAD_DPAD_RIGHT,			// 十字キー 右
		XINPUT_START			= XINPUT_GAMEPAD_START,					// スタート
		XINPUT_BACK				= XINPUT_GAMEPAD_BACK,					// バック
		XINPUT_LEFT_THUMB		= XINPUT_GAMEPAD_LEFT_THUMB,			// 左
		XINPUT_RIGHT_THUMB		= XINPUT_GAMEPAD_RIGHT_THUMB,			// 右
		XINPUT_LEFT_SHOULDER	= XINPUT_GAMEPAD_LEFT_SHOULDER,			// 左
		XINPUT_RIGHT_SHOULDER	= XINPUT_GAMEPAD_RIGHT_SHOULDER,		// 右
		XINPUT_A				= XINPUT_GAMEPAD_A,						// A
		XINPUT_B				= XINPUT_GAMEPAD_B,						// B
		XINPUT_X				= XINPUT_GAMEPAD_X,						// X
		XINPUT_Y				= XINPUT_GAMEPAD_Y,						// Y
	};

	/* メンバ関数 */
	// ( コントローラーのインデックス...dwUserIndex, 状態を受け取る XINPUT_STATE 構造体へのポインター...pState )
	void			Update();														// 更新

	bool			GetPressXinputGpad(XINPUT_CONTROLLER nKey);						// Xinputのボタン入力
	bool			GetTriggerXinputGpad(XINPUT_CONTROLLER nKey);					// Xinputのトリガー入力
	void			GetLeftStickValue(float &sThumbX, float &sThumbY);				// 左スティックの値の取得
	void			GetRightStickValue(float &sThumbX, float &sThumbY);				// 右スティックの値の取得

	WORD			ThumbToDPad(float sThumbX, float sThumbY, float sDeadZone);		// スティックの入力を方向パッドフラグに変換

private:
	/* メンバ変数 */
	XINPUT_STATE	m_state;		// 状態
	XINPUT_STATE	m_stateOld;		// 過去の状態
};
#endif 