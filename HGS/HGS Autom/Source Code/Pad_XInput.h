//----------------------------------------------------------------------------
//
// �Q�[���p�b�h���� [Xinput.h]
// Author : Yoshiki Hosoya
//
//----------------------------------------------------------------------------
#ifndef _GAMEPAD_XINPUT_H_
#define _GAMEPAD_XINPUT_H_
//----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//----------------------------------------------------------------------------
#include "main.h"
#include "input.h"

//----------------------------------------------------------------------------
// �}�N����`
//----------------------------------------------------------------------------
#define MAX_SAVE_KEYSTATE (60)		//�L�[��ۑ�����ő�l

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CPad_XInput
{
public:
	CPad_XInput();
	~CPad_XInput();

	//���̓L�[�@�񋓁@���X�}�N���ł��邯�ǎg���₷�����邽��
	enum XINPUT_KEY
	{
		JOYPADKEY_UP					= XINPUT_GAMEPAD_DPAD_UP,				//�\���L�[ ��
		JOYPADKEY_DOWN					= XINPUT_GAMEPAD_DPAD_DOWN,				//�\���L�[ ��
		JOYPADKEY_LEFT					= XINPUT_GAMEPAD_DPAD_LEFT,				//�\���L�[ ��
		JOYPADKEY_RIGHT					= XINPUT_GAMEPAD_DPAD_RIGHT,			//�\���L�[ ��
		JOYPADKEY_START					= XINPUT_GAMEPAD_START,					//START
		JOYPADKEY_BACK					= XINPUT_GAMEPAD_BACK,					//BACK
		JOYPADKEY_L1					= XINPUT_GAMEPAD_LEFT_THUMB,			//L1
		JOYPADKEY_R1					= XINPUT_GAMEPAD_RIGHT_THUMB,			//R1
		JOYPADKEY_L2					= XINPUT_GAMEPAD_LEFT_SHOULDER,			//L2
		JOYPADKEY_R2					= XINPUT_GAMEPAD_RIGHT_SHOULDER,		//R2
		JOYPADKEY_A						= XINPUT_GAMEPAD_A,						//A
		JOYPADKEY_B						= XINPUT_GAMEPAD_B,						//B
		JOYPADKEY_X						= XINPUT_GAMEPAD_X,						//X
		JOYPADKEY_Y						= XINPUT_GAMEPAD_Y,						//Y
	};

	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	//������
	void Uninit(void);								//�I��
	void Update(void);								//�X�V

	bool GetTrigger(XINPUT_KEY Button,size_t Frame);
	bool GetPress(XINPUT_KEY Button);
	void GetStickLeft(float *pValueX, float *pValueZ);		//���X�e�B�b�N�l�擾
	void GetStickRight(float *pValueX, float *pValueZ);		//�E�X�e�B�b�N�l�擾
	bool GetConnect() { return m_bConnect; };		//�R���g���[�����ڑ�����Ă��邩�ǂ���

	//�o�C�u���[�V�����֌W
	void StartVibration(int nCnt)	{ m_bVibration = true, m_nCntVibration = nCnt; };		//�o�C�u���[�V�����J�n
	void EndVibration()				{ m_bVibration = false; };								//�o�C�u���[�V�����I��

private:
	XINPUT_STATE m_pState;							//���݂̃R���g���[���̏��
	XINPUT_STATE m_pStateOld;						//1F�O�̂̃R���g���[���̏��
	bool m_bVibration;								//�o�C�u���[�V�������Ă邩�ǂ���
	bool m_bConnect;								//�R���g���[���[���ڑ�����Ă��邩�ǂ���
	int m_nCntVibration;							//�o�C�u���[�V�����p�̃J�E���g

};

#endif