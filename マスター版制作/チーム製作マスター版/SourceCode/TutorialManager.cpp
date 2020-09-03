// =====================================================================================================================================================================
//
// �`���[�g���A���}�l�[�W���[�̏��� [tutorialmanager.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"
#include "tutorialmanager.h"
#include "basemode.h"
#include "manager.h"
#include "tutorialui.h"
#include "renderer.h"
#include "fade.h"
#include "inputKeyboard.h"
#include "player.h"
#include "debugproc.h"
#include "Xinput.h"
#include "XInputPad.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
// �p�b�h�{�^��
#define PAD_A (pad->GetTrigger(pad->JOYPADKEY_A, 1))			// �W�����v
#define PAD_B (pad->GetTrigger(pad->JOYPADKEY_B, 1))			// ��蕨����~���
#define PAD_X (pad->GetTrigger(pad->JOYPADKEY_X, 1))			// �e
#define PAD_Y (pad->GetTrigger(pad->JOYPADKEY_Y, 1))			// �O���l�[�h
#define PAD_START (pad->GetTrigger(pad->JOYPADKEY_START, 1))	// �`���[�g���A�����X�L�b�v����

// �L�[�{�[�h
#define KEY_A (key->GetKeyboardPress(DIK_A))					// �ړ���
#define KEY_D (key->GetKeyboardPress(DIK_D))					// �ړ��E
#define KEY_O (key->GetKeyboardPress(DIK_O))					// �O���l�[�h
#define KEY_P (key->GetKeyboardPress(DIK_P))					// �e
#define KEY_SPACE (key->GetKeyboardTrigger(DIK_SPACE))			// �W�����v

#define WAITTIME (180)											// �X�e�[�g�Ԃ̑҂�����

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CTutorialManager::CTutorialManager()
{
	m_TutorialState = TUTORIAL_STATE_NONE;
	m_OldState = TUTORIAL_STATE_NONE;
	m_pTutorialUI = nullptr;
	m_nWaitTime = 0;
	m_bOneFlag = false;
	m_bPushButton = false;
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CTutorialManager::~CTutorialManager()
{

}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CTutorialManager::Init(void)
{
	// �`���[�g���A��UI�̐���
	m_pTutorialUI = CTutorialUI::Create();
	// �J�������Œ肷��
	CRenderer *pRenderer = CManager::GetRenderer();
	pRenderer->GetCamera()->SetCameraStopMove(true);
	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CTutorialManager::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CTutorialManager::Update(void)
{
	//�L�[�{�[�h���擾
	CKeyboard *key = CManager::GetInputKeyboard();
	// �p�b�h�擾
	CXInputPad *pad = CManager::GetPad(CONTROLLER::P1);

	// �G���^�[���������Ƃ�
	if (CHossoLibrary::PressStartButton() || PAD_START)
	{
		// �Q�[�����[�h�փX�e�[�g�J��
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_GAME);
	}

	// �e�X�e�[�g���Ƃ̊֐����Ǘ�����
	StateManager();
	// �`���[�g���A���̏��ԊǗ�
	TutorialState();

	// �ŏ���1��ڂ͖������ɒʂ�
	if (m_TutorialState == TUTORIAL_STATE_NONE)
	{
		// ���݂̃X�e�[�g��ۑ�
		m_OldState = m_TutorialState;
		// �^�C�}�[�J�n
		WaitTime();
	}

	// 1��ڈȍ~
	else
	{
		// ���̃X�e�[�g��1�O�̃X�e�[�g���ʂ�������
		if (m_TutorialState != static_cast<TUTORIAL_STATE>(m_OldState - 1))
		{
			// �{�^����������Ă��邩�`�F�b�N
			JudgPushButton();
			// �v���C���[���`���[�g���A���ʂ�Ƀ{�^������������
			if (m_bPushButton)
			{
				// �^�C�}�[�J�n
				WaitTime();
			}
		}
	}

	CDebugProc::Print_Left("Tutorial�̃X�e�[�g %d\n", m_TutorialState);
	CDebugProc::Print_Left("Old�̃X�e�[�g %d\n", m_OldState);

}

// =====================================================================================================================================================================
//
// ����
//
// =====================================================================================================================================================================
CTutorialManager * CTutorialManager::Create()
{
	//�������̊m��
	CTutorialManager *pTutorialManager = new CTutorialManager();

	// ������
	pTutorialManager->Init();

	// �|�C���^��Ԃ�
	return pTutorialManager;
}

// =====================================================================================================================================================================
//
// Ui�̏o������
//
// =====================================================================================================================================================================
void CTutorialManager::TutorialState()
{
	// ����
	switch (m_TutorialState)
	{
	case CTutorialManager::TUTORIAL_STATE_FIRST:
		break;
	case CTutorialManager::TUTORIAL_STATE_1:
		break;
	case CTutorialManager::TUTORIAL_STATE_2:
		break;
	case CTutorialManager::TUTORIAL_STATE_3:
		break;
	case CTutorialManager::TUTORIAL_STATE_4:
		break;
	case CTutorialManager::TUTORIAL_STATE_5:
		break;
	case CTutorialManager::TUTORIAL_STATE_6:
		break;
	case CTutorialManager::TUTORIAL_STATE_FINAL:
		break;
	}
}

// =====================================================================================================================================================================
//
// �X�e�[�g��؂�ւ���ۂ̎��Ԃ̐ݒ�
//
// =====================================================================================================================================================================
void CTutorialManager::WaitTime()
{
	// ���Ԃ̌���
	m_nWaitTime--;

	// ���Ԃ�0�ȉ��ɂȂ�����
	if (m_nWaitTime <= 0)
	{
		// ���̃X�e�[�g�Ɉڍs����
		NextState();
		//
		m_bPushButton = false;
		// ���݂̃X�e�[�g��ۑ�
		m_OldState = m_TutorialState;
	}
}

// =====================================================================================================================================================================
//
// �X�e�[�g��؂�ւ���ۂ̎��Ԃ̊Ǘ�
//
// =====================================================================================================================================================================
void CTutorialManager::SetWaitTime(int Time)
{
	// �҂����Ԃ�ݒ肷��
	m_nWaitTime = Time;
}

// =====================================================================================================================================================================
//
// �X�e�[�g��؂�ւ���ۂ̎��Ԃ̐ݒ�
//
// =====================================================================================================================================================================
void CTutorialManager::NextState()
{
	// ���̃X�e�[�g�Ɉڍs����
	if (m_TutorialState != TUTORIAL_STATE_FINAL)
	{
		m_TutorialState = static_cast<TUTORIAL_STATE>(m_TutorialState + 1);
		m_bOneFlag = false;

		if (m_pTutorialUI)
		{
			m_pTutorialUI->SetDrawDisp(m_pTutorialUI->GetTutorialUiType());
		}
	}
	else
	{
		// �Q�[�����[�h�փX�e�[�g�J��
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_GAME);
	}
}

// =====================================================================================================================================================================
//
// �e�X�e�[�g���Ƃ̊֐����Ǘ�����
//
// =====================================================================================================================================================================
void CTutorialManager::StateManager()
{
	// ���̏������܂��ʂ��Ă��Ȃ�������
	if (!m_bOneFlag)
	{
		// ��ԍŏ��̃X�e�[�g��������
		if (m_TutorialState == TUTORIAL_STATE_NONE)
		{
			// ���̃X�e�[�g�Ɉڍs����܂ł̎��Ԃ̐ݒ�
			SetWaitTime(120);
		}
		// ����ȊO��������
		else
		{
			// ���̃X�e�[�g�Ɉڍs����܂ł̎��Ԃ̐ݒ�
			SetWaitTime(WAITTIME);
		}

		// ���̏��������ɋ����o��܂Œʂ��Ȃ�
		m_bOneFlag = true;
	}
}

// =====================================================================================================================================================================
//
// �w�肵���{�^���������ꂽ���ǂ���
//
// =====================================================================================================================================================================
void CTutorialManager::JudgPushButton()
{
	// �L�[�{�[�h�擾
	CKeyboard *key = CManager::GetInputKeyboard();
	// �p�b�h�擾
	CXInputPad *pad = CManager::GetPad(CONTROLLER::P1);
	// �X�e�B�b�N�̒l��������
	D3DXVECTOR3 InputValue = ZeroVector3;
	// �l�̐��K��
	InputValue.x /= STICK_MAX_RANGE;
	InputValue.y /= STICK_MAX_RANGE;
	// ���X�e�B�b�N�̓��͒l���擾
	pad->GetStickLeft(&InputValue.x, &InputValue.y);
	// �v���C���[�̃|�C���^���擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(CONTROLLER::P1);

	// �e�X�e�[�g���̃{�^�������������ǂ���
	switch (m_TutorialState)
	{
		// padX,Y,A,B�܂���keyD�ŊJ�n
	case CTutorialManager::TUTORIAL_STATE_FIRST:
		m_bPushButton = true;
		break;
		// padLSTICK�܂���keyAD�ňړ�
	case CTutorialManager::TUTORIAL_STATE_1:
		if (InputValue.x < -1.0f || InputValue.x > 1.0f ||
			KEY_A ||
			KEY_D)
		{
			m_bPushButton = true;
		}
		break;
		// padX�܂���keySPACE�ŃW�����v
	case CTutorialManager::TUTORIAL_STATE_2:
		if (PAD_X ||
			KEY_SPACE)
		{
			m_bPushButton = true;
		}
		break;
		// padA�܂���keyP�Œe����
	case CTutorialManager::TUTORIAL_STATE_3:
		if (PAD_A ||
			KEY_P)
		{
			m_bPushButton = true;
		}
		break;
		// padY�܂���keyO�ŃO���l�[�h
	case CTutorialManager::TUTORIAL_STATE_4:
		if (PAD_Y ||
			KEY_O)
		{
			m_bPushButton = true;
		}
		break;
		// ��Ԃ̋߂���padX�܂���keySPACE�ŃW�����v�����
	case CTutorialManager::TUTORIAL_STATE_5:
		// null�`�F�b�N
		if (pPlayer != nullptr)
		{
			// ��蕨�ɏ���Ă��鎞
			if (pPlayer->GetRideFlag())
			{
				m_bPushButton = true;
			}
		}
		break;
		// ��Ԃɏ���Ă��鎞padB�܂���keySPACE�ŃW�����v���~���
	case CTutorialManager::TUTORIAL_STATE_6:
		// ��Ԃ���~���
		// null�`�F�b�N
		if (pPlayer != nullptr)
		{
			// ��蕨�ɏ���Ă��鎞
			if (pPlayer->GetRideFlag())
			{
				if (PAD_B || KEY_SPACE)
				{
					m_bPushButton = true;
				}
			}
		}
		break;
	case CTutorialManager::TUTORIAL_STATE_FINAL:
			m_bPushButton = true;
		break;
	}
}
