//====================================================================
// �v���C���[���� [player.cpp]: NORI
//====================================================================
#include "Player.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "createmap.h"
#include "Xinput.h"
#include "handgun.h"
#include "heavymachinegun.h"

CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
}

CPlayer::~CPlayer()
{
}
//====================================================================
//������
//====================================================================
HRESULT CPlayer::Init(void)
{
	//�L�����̏�����
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_PLAYER);
	SetCharacterType(CCharacter::CHARACTER_TYPE_PLAYER);

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	m_Attack = false;
	ZeroMemory(&state, sizeof(XINPUT_STATE));
	ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));

	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CPlayer::Update(void)
{
	float rot = 0.0f;
	static bool trigger = false;
	static bool trigger2 = false;
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	Oldstate = state.Gamepad.wButtons;

	//�Q�[���p�b�h����
	// Simply get the state of the controller from XInput.
	DWORD dwResult = XInputGetState(0, &state);
	if (dwResult == ERROR_SUCCESS)
	{
		// Controller is connected
		CDebugProc::Print("controller�ڑ�\n");
	}
	else
	{
		// Controller is not connected
		CDebugProc::Print("controller�ؒf\n");
	}
	if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A && m_Attack == false)
	{
		// A �{�^���������ꂽ
	}
	if (state.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD &&state.Gamepad.wButtons & XINPUT_GAMEPAD_X)
	{
		// ���g���K�[�������ꂽ
		//vibration.wLeftMotorSpeed =  65535; // use any value between 0-65535 here
		//vibration.wRightMotorSpeed = 65535; // use any value between 0-65535 here
	}
	else
	{
		vibration.wLeftMotorSpeed = 0;
		vibration.wRightMotorSpeed = 0;
	}
	 //�f�b�g�]�[���̏���
	if ((state.Gamepad.sThumbLX <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
		state.Gamepad.sThumbLX > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) &&
		(state.Gamepad.sThumbLY <  XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE &&
			state.Gamepad.sThumbLY > -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE))
	{
		state.Gamepad.sThumbLX = 0;
		state.Gamepad.sThumbLY = 0;
	}
		D3DXVECTOR3 speed = D3DXVECTOR3(state.Gamepad.sThumbLX / 32767.0f, 0.0f, state.Gamepad.sThumbLY / 32767.0f);

		float fDistance = D3DXVec2Length(&D3DXVECTOR2(speed.x, speed.z));
		if (fabsf(fDistance) > 0.2f && m_Attack == false)
		{
			//m_MotionType = PLAYER_MOTION_WALK;
			//�p�x�̌v�Z
			GetMove().x += sinf(m_Angle) * 1;
			GetMove().z += cosf(m_Angle) * 1;
		}
	//Dest.y = atan2f(-m_move.x, -m_move.z);

	//�L�[�{�[�h����

		// �e������
		if (key->GetKeyboardTrigger(DIK_P))
		{
			// �n���h�K���̒e�̐���
			CHandgun::Create(CPlayer::GetPosition(), CPlayer::GetRot());
		}
		if (key->GetKeyboardTrigger(DIK_O))
		{
			// �w�r�[�}�V���K���̒e�̐���
			CHeavyMachinegun::Create(CPlayer::GetPosition(), CPlayer::GetRot());
		}

		// A�Ƃ̑g�ݍ��킹
	if (key->GetKeyboardPress(DIK_A))
	{
		if (key->GetKeyboardPress(DIK_S))
		{
			CPlayer::Move(0.75f, 0.25f);
		}
		else if (key->GetKeyboardPress(DIK_W))
		{
			CPlayer::Move(0.25f, 0.75f);
		}
		else
		{
			CPlayer::Move(0.5f, 0.5f);
		}
	}
	// D�Ƃ̑g�ݍ��킹
	else if (key->GetKeyboardPress(DIK_D))
	{
		if (key->GetKeyboardPress(DIK_W))
		{
			CPlayer::Move(-0.25f, -0.75f);
		}
		else if (key->GetKeyboardPress(DIK_S))
		{
			CPlayer::Move(-0.75f, -0.25f);
		}
		else
		{
			CPlayer::Move(-0.5f, -0.5f);
		}
	}
	// W�Ƃ̑g�ݍ��킹
	else if (key->GetKeyboardPress(DIK_W))
	{
		CPlayer::Move(0.0f, 1.0f);
	}
	// S�Ƃ̑g�ݍ��킹
	else if (key->GetKeyboardPress(DIK_S))
	{
		CPlayer::Move(1.0f, 0.0f);
	}
	//�f�o�b�O���[�h�̐؂�ւ�
	if (key->GetKeyboardTrigger(DIK_F2))
	{
		trigger ^= 1;
	}
	if (trigger == true)
	{
		if (key->GetKeyboardTrigger(DIK_F3))
		{
			trigger2 ^= 1;
		}
		if (trigger2 == true)
		{
		m_DebugState = DEBUG_CREATE_ENEMY;
		}
		else
		{
		m_DebugState = DEBUG_CREATE_MAP;
		}
	}
	else
	{
		m_DebugState = DEBUG_NORMAL;
	}
	if (m_DebugState != DEBUG_NORMAL)
	{
	}
	if (key->GetKeyboardPress(DIK_SPACE))
	{
		GetMove().y += 2;
	}
	if (key->GetKeyboardPress(DIK_LCONTROL))
	{
		GetMove().y -= 2;
	}
	if (key->GetKeyboardTrigger(DIK_1))
	{
		SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	}
	if (key->GetKeyboardTrigger(DIK_2))
	{
		SetMotion(CCharacter::PLAYER_MOTION_WALK);
	}
	XInputSetState(0, &vibration);
	CCharacter::Update();
}
//====================================================================
//�`��
//====================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxWorld = GetMtxWorld();
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CPlayer *CPlayer::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->Init();
	return pPlayer;
}
void CPlayer::DefaultMotion(void)
{
	SetMotion(CCharacter::PLAYER_MOTION_NORMAL);
}
//====================================================================
//�f�o�b�O�X�e�[�^�X�̎擾
//====================================================================
CPlayer::DEBUG_STATE CPlayer::GetDebugState(void)
{
	return m_DebugState;
}
//====================================================================
//�ړ�
//====================================================================
void CPlayer::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	//m_rotDest.y = fdest *  D3DX_PI;
}
