// =====================================================================================================================================================================
//
// Xinput�W���C�p�b�h���� [xinputGpad.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _XINPUTGPAD_H_
#define _XINPUTGPAD_H_

#define _CRT_SECURE_NO_WARNINGS

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include"main.h"
#include"input.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �Q�[���p�b�h�N���X
// =====================================================================================================================================================================
class CXinputGpad : public CInput
{
public:
	// Xinput�̑���L�[
	enum XINPUT_CONTROLLER
	{
		XINPUT_UP				= XINPUT_GAMEPAD_DPAD_UP,				// �\���L�[ ��
		XINPUT_DOWN				= XINPUT_GAMEPAD_DPAD_DOWN,				// �\���L�[ ��
		XINPUT_LEFT				= XINPUT_GAMEPAD_DPAD_LEFT,				// �\���L�[ ��
		XINPUT_RIGHT			= XINPUT_GAMEPAD_DPAD_RIGHT,			// �\���L�[ �E
		XINPUT_START			= XINPUT_GAMEPAD_START,					// �X�^�[�g
		XINPUT_BACK				= XINPUT_GAMEPAD_BACK,					// �o�b�N
		XINPUT_LEFT_THUMB		= XINPUT_GAMEPAD_LEFT_THUMB,			// ��
		XINPUT_RIGHT_THUMB		= XINPUT_GAMEPAD_RIGHT_THUMB,			// �E
		XINPUT_LEFT_SHOULDER	= XINPUT_GAMEPAD_LEFT_SHOULDER,			// ��
		XINPUT_RIGHT_SHOULDER	= XINPUT_GAMEPAD_RIGHT_SHOULDER,		// �E
		XINPUT_A				= XINPUT_GAMEPAD_A,						// A
		XINPUT_B				= XINPUT_GAMEPAD_B,						// B
		XINPUT_X				= XINPUT_GAMEPAD_X,						// X
		XINPUT_Y				= XINPUT_GAMEPAD_Y,						// Y
	};

	/* �����o�֐� */
	// ( �R���g���[���[�̃C���f�b�N�X...dwUserIndex, ��Ԃ��󂯎�� XINPUT_STATE �\���̂ւ̃|�C���^�[...pState )
	void			Update();														// �X�V

	bool			GetPressXinputGpad(XINPUT_CONTROLLER nKey);						// Xinput�̃{�^������
	bool			GetTriggerXinputGpad(XINPUT_CONTROLLER nKey);					// Xinput�̃g���K�[����
	void			GetLeftStickValue(float &sThumbX, float &sThumbY);				// ���X�e�B�b�N�̒l�̎擾
	void			GetRightStickValue(float &sThumbX, float &sThumbY);				// �E�X�e�B�b�N�̒l�̎擾

	WORD			ThumbToDPad(float sThumbX, float sThumbY, float sDeadZone);		// �X�e�B�b�N�̓��͂�����p�b�h�t���O�ɕϊ�

private:
	/* �����o�ϐ� */
	XINPUT_STATE	m_state;		// ���
	XINPUT_STATE	m_stateOld;		// �ߋ��̏��
};
#endif 