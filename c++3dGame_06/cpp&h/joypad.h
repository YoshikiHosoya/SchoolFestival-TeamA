// ------------------------------------------
//
// �R���g���[���[�w�b�_�[���� [joypad.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _JOYPAD_H_
#define _JOYPAD_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ------------------------------------------
#include "main.h"
#include "input.h"

// ------------------------------------------
//
// �}�N����`
//
// ------------------------------------------
#define MAX_GAMEPAD (1)

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CJoypad : public CInput
{
public:
	/* �\���̔ԍ�(enum) */
	typedef enum
	{
		KEY_X = 0,
		KEY_Y,
		KEY_A,
		KEY_B,
		KEY_LEFT_1,
		KEY_RIGHT_1,
		KEY_LEFT_2,
		KEY_RIGHT_2,
		KEY_LEFT_STICK,
		KEY_RIGHT_STICK,
		KEY_BACK,
		KEY_START,
		KEY_LEFT,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_MAX,
	}KEY;

	/* �֐� */
	CJoypad();
	~CJoypad();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);
	void Uninit(void);
	void Update(void);
	bool GetPress(int nJoy, KEY key);
	bool GetTrigger(int nJoy, KEY key);
	bool GetRelease(int nJoy, KEY key);
	bool GetRepeat(int nJoy, KEY key);
	int GetTriggerLeft(int nJoy, KEY key);
	int GetTriggerRight(int nJoy, KEY key);
	void GetStickLeft(int nJoy, int *pValueH, int *pValueV);
	void GetStickRight(int nJoy, int *pValueH, int *pValueV);

protected:
private:
	/* �ϐ��錾 */
	static LPDIRECTINPUTDEVICE8 m_pJoyDevice[MAX_GAMEPAD];	// ���̓f�o�C�X�ւ̃|�C���^
	DIJOYSTATE2 m_aState[MAX_GAMEPAD];				// �Q�[���p�b�h��Ԃ��󂯎�郏�[�N
	D3DXVECTOR3 m_aStateAxis[MAX_GAMEPAD];			// �X�e�B�b�N�̈ʒu���
	int m_nCntWaitRepeat;						// �J�E���g�}�b�N�X
	int m_nIntervalRepeat;						// �����̊�
	static int m_nCntpad;								// �J�E���g
	int m_aStateRepeatCnt[MAX_GAMEPAD][KEY_MAX];	// ���s�[�g��
	bool m_abState[MAX_GAMEPAD][KEY_MAX];			// �Q�[���p�b�h��Ԃ̕ۑ��ꏊ
	bool m_abStateTrigger[MAX_GAMEPAD][KEY_MAX];	// �Q�[���p�b�h��Ԃ̃I���E�I�t
	bool m_abStateRelease[MAX_GAMEPAD][KEY_MAX];	// �Q�[���p�b�h��Ԃ̕Ԃ�
	bool m_abStateRepeat[MAX_GAMEPAD][KEY_MAX];		// �Q�[���p�b�h��Ԃ��J��Ԃ�

	/* �֐� */
	static BOOL CALLBACK EnumCallback(const DIDEVICEINSTANCE *pdidInstance, VOID *pContext);	// �\�͎擾
	void SetState(int nJoy);															// �{�^���ݒ�
};
#endif
