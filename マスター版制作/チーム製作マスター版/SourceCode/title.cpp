// =====================================================================================================================================================================
//
// �^�C�g���̏��� [title.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "title.h"
#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "UIManager.h"
#include "titleUI.h"
#include "Xinput.h"
#include "XInputPad.h"
#include "UI.h"
#include "sound.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define INTERBALCOUNT (30)
// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CTitle::PLAYER_NUM		CTitle::m_PlayerNum = PLAYER_NUM_ONE;
// =====================================================================================================================================================================
// �R���X�g���N�^
// =====================================================================================================================================================================
CTitle::CTitle()
{
	// �^�C�g���̏������
	m_TitleMode = MODE_PENDING;
	m_nStagingInterval = 0;
	m_nStagingNum = 0;
	m_bEndStaging = false;
	m_PlayerNum = PLAYER_NUM_ONE;
}

//==========================================================
// �f�X�g���N�^
//==========================================================
CTitle::~CTitle()
{
}

//==========================================================
// ������
//==========================================================
HRESULT CTitle::Init(void)
{
	// UI����
	CUIManager::Create();

	// �^�C�g��UI�̐���
	m_pTitleUI = CTitleUI::Create();

	return S_OK;
}

//==========================================================
// �I��
//==========================================================
void CTitle::Uninit(void)
{

}

//==========================================================
// �X�V
//==========================================================
void CTitle::Update(void)
{
	TitleMode();

	if (m_TitleMode != MODE_FADE)
	{
		// �G���^�[���������Ƃ�
		if (CHossoLibrary::PressAnyButton() && m_TitleMode != MODE_STAGING)
		{
			// �^�C�g���̃��[�h�����̃��[�h�Ɉڍs����
			TitleModeNext();
			//���艹
			CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}
	else
	{
		if (CManager::GetRenderer()->GetFade()->GetFadeState() == CFADE::FADESTATE::FADESTATE_NONE)
		{
			// �Q�[�����[�h�֏�ԑJ��7
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_TUTORIAL);

			//���艹
			CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}
}

//==========================================================
// �`�揈��
//==========================================================
void CTitle::Draw(void)
{
}

//==========================================================
// �f�o�b�O���\�L
//==========================================================
void CTitle::ShowDebugInfo(void)
{
}

//==========================================================
// �^�C�g���̃��[�h�����̃��[�h�Ɉڍs����
//==========================================================
void CTitle::TitleModeNext()
{
	for (int nCnt = 0; nCnt < MODE_MAX; nCnt++)
	{
		if (m_TitleMode != nCnt && m_TitleMode < nCnt)
		{
			m_TitleMode = (TITLE_MODE)nCnt;
			break;
		}
	}
}

//==========================================================
// �^�C�g���̃��[�h���Ƃ̏���
//==========================================================
void CTitle::TitleMode()
{
	CKeyboard *Keyboard;
	Keyboard = CManager::GetInputKeyboard();
	CXInputPad *InpudPad[MAX_CONTROLLER] = {};

	switch (m_TitleMode)
	{
	case CTitle::MODE_PENDING:
		// ���̃J�E���g�̐ݒ�
		m_nStagingInterval = INTERBALCOUNT;
		break;
	case CTitle::MODE_STAGING:
		// ���o
		TitleStaging();
		break;
	case CTitle::MODE_CHARACTERSELECT:

		if (m_bEndStaging)
		{
			m_pTitleUI->SetDrawFlag(CTitleUI::UI_START, false);

			if (m_nStagingInterval <= 0)
			{
				// �`��t���O��ύX����
				for (int nCnt = 0; nCnt < 3; nCnt++)
				{
					m_pTitleUI->SetDrawFlag(static_cast<CTitleUI::TITLE_UI> (nCnt + CTitleUI::UI_PLAYER_COUNT_1), true);
				}
			}
			else
			{
				m_nStagingInterval--;
			}
		}

		for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
		{
			InpudPad[nCnt] = CManager::GetPad((TAG)nCnt);

			if (Keyboard->GetKeyboardTrigger(DIK_UP) || InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_UP, 1) ||
				Keyboard->GetKeyboardTrigger(DIK_DOWN) || InpudPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_DOWN, 1))
			{
				if (m_PlayerNum == PLAYER_NUM_ONE)
				{
					m_PlayerNum = PLAYER_NUM_TWO;
					m_pTitleUI->SetPos(CTitleUI::UI_ARROWMARK, D3DXVECTOR3(400.0f, 650.0f, 0.0f));
					//���艹
					CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);
					break;
				}
				else
				{
					m_PlayerNum = PLAYER_NUM_ONE;
					m_pTitleUI->SetPos(CTitleUI::UI_ARROWMARK, D3DXVECTOR3(400.0f, 550.0f, 0.0f));
					//���艹
					CManager::GetSound()->Play(CSound::LABEL_SE_SELECT);
					break;
				}
			}
		}
		break;
	case CTitle::MODE_FADE:
		break;
	}
}

//==========================================================
// ���o
//==========================================================
void CTitle::TitleStaging()
{
	if (m_nStagingNum < 3)
	{
		// �C���^�[�o���̃J�E���g��0�ȉ��ɂȂ�����
		if (m_nStagingInterval <= 0)
		{
			// �`��t���O��true�ɂ���
			m_pTitleUI->SetDrawFlag(static_cast<CTitleUI::TITLE_UI> (CTitleUI::UI_BULLETHOLE_1 + m_nStagingNum), true);
			// ���ʉ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_TITLE_BULLET);
			// ���̃J�E���g�̐ݒ�
			m_nStagingInterval = INTERBALCOUNT;

			m_nStagingNum++;
		}
		m_nStagingInterval--;
	}
	else
	{
		m_bEndStaging = true;
		m_TitleMode = MODE_CHARACTERSELECT;
		m_nStagingInterval = INTERBALCOUNT;
	}

}
