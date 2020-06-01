// ------------------------------------------
//
// �}�l�[�W���[�����̐���[manager.cpp]
// Author : Fujiwara Masato
//
// ------------------------------------------
/* My */
#include "manager.h"

/* �`�� */
#include "scene.h"
#include "title.h"
#include "game.h"
//#include "tutorial.h"
//#include "ranking.h"
#include "fade.h"
#include "light.h"
#include "pointlight.h"
#include "camera.h"
#include "pause.h"
#include "manual.h"

// ------------------------------------------
//
// �}�N���֐�
//
// ------------------------------------------
#define STARTMODE (MODE_TITLE)

// ------------------------------------------
//
// �ÓI�ϐ��錾
//
// ------------------------------------------
CRenderer *CManager::m_renderer = NULL;
CKeyboard * CManager::m_keyboard = NULL;
CJoypad * CManager::m_joypad = NULL;
CMouse * CManager::m_mouse = NULL;
CSound * CManager::m_sound = NULL;
CFade * CManager::m_fade = NULL;
CTitle * CManager::m_title = NULL;
CGame * CManager::m_game = NULL;
CTutorial * CManager::m_tutorial = NULL;
//CRanking * CManager::m_ranking = NULL;
CManager::MODE CManager::m_mode = CManager::MODE_TITLE;
bool CManager::m_bWire = false;

// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CManager::CManager()
{
}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CManager::~CManager()
{
}

// ------------------------------------------
// ����������
// ------------------------------------------
HRESULT CManager::Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance)
{
	/* �������̐��� */
	/* ���̓f�o�C�X */
	// �L�[�{�[�h�̐���
	m_keyboard = new CKeyboard;
	// �W���C�p�b�h�̐���
	m_joypad = new CJoypad;
	// �}�E�X�̐���
	m_mouse = new CMouse;
	/* �Q�[���Ɍ������Ȃ����� */
	// �T�E���h�̐���
	m_sound = new CSound;
	// �����_�����O�̐���
	m_renderer = new CRenderer;

	/* ��� */
	// ��ʑJ�ڂ̐���
	m_fade = new CFade;
	// �^�C�g���̐���
	m_title = new CTitle;
	// �Q�[���̐���
	m_game = new CGame;
	// �`���[�g���A���̐���
	//m_tutorial = new CTutorial;
	// �����L���O�̐���
	//m_ranking = new CRanking;
	// ���[�h�̐ݒ�
	m_mode = STARTMODE;

	/* ������ */
	// �L�[�{�[�h
	m_keyboard->Init(hInstance, hWnd);
	// �W���C�p�b�h
	if (m_joypad->Init(hInstance, hWnd) == E_FAIL)
	{

	}
	// �}�E�X
	m_mouse->Init(hInstance, hWnd);
	// �T�E���h
	m_sound->Init(hWnd);
	// �����_�����O
	m_renderer->Init(hWnd, bWindow);
	//m_renderer->Init(hWnd, FALSE);
	// ��ʑJ��
	m_fade->Init(STARTMODE);
	CManager::SetMode(STARTMODE);
	srand((unsigned int)time(NULL));

	/*CPause::Create();
	CManual::Create();*/

	return S_OK;
}

// ------------------------------------------
// �I������
// ------------------------------------------
void CManager::Uninit(void)
{
	/* �I�� */
	// �L�[�{�[�h
	m_keyboard->Uninit();
	// �}�E�X
	m_mouse->Uninit();
	// ���̓f�o�C�X
	CInput::ReleaseAll();
	// �T�E���h
	m_sound->Uninit();
	// �����_�����O
	m_renderer->Uninit();
	// ��ʑJ��
	m_fade->Uninit();

	/* �������̔j�� */
	// �L�[�{�[�h
	if (m_keyboard != NULL)
	{
		delete m_keyboard;
		m_keyboard = NULL;
	}
	// �W���C�p�b�h
	if (m_joypad != NULL)
	{
		// �W���C�p�b�h
		m_joypad->Uninit();

		delete m_joypad;
		m_joypad = NULL;
	}
	// �}�E�X
	if (m_mouse != NULL)
	{
		delete m_mouse;
		m_mouse = NULL;
	}
	// �T�E���h
	if (m_sound != NULL)
	{
		delete m_sound;
		m_sound = NULL;
	}
	// �����_�����O
	if (m_renderer != NULL)
	{
		delete m_renderer;
		m_renderer = NULL;
	}
	// ��ʑJ��
	if (m_fade != NULL)
	{
		delete m_fade;
		m_fade = NULL;
	}
	// �^�C�g��
	if (m_title != NULL)
	{
		m_title->Uninit();
		delete m_title;
		m_title = NULL;
	}
	// �Q�[��
	if (m_game != NULL)
	{
		m_game->Uninit();
		delete m_game;
		m_game = NULL;
	}
	// �`���[�g���A��
	/*if (m_tutorial != NULL)
	{
		m_tutorial->Uninit();
		delete m_tutorial;
		m_tutorial = NULL;
	}*/
	// �����L���O
	/*if (m_ranking != NULL)
	{
		m_ranking->Uninit();
		delete m_ranking;
		m_ranking = NULL;
	}*/
}

// ------------------------------------------
// �X�V����
// ------------------------------------------
void CManager::Update(void)
{
	// �L�[�{�[�h
	m_keyboard->Update();
	// �W���C�p�b�h
	m_joypad->Update();
	// �}�E�X
	m_mouse->Update();
	// �����_�����O
	m_renderer->Update();
	// ���C���t���[��
	if (m_keyboard->GetKeyboardTrigger(DIK_F1))
	{
		if (m_bWire == false)
		{
			m_bWire = true;
		}
		else
		{
			m_bWire = false;
		}
	}

	if (m_bWire)
	{
		// �����_���[�X�e�[�g�̐ݒ�
		m_renderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}
	else
	{
		// �����_���[�X�e�[�g�̐ݒ�
		m_renderer->GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	}
	// �O�̃��[�h�I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		m_title->Update();
		break;
		// �Q�[��
	case MODE_GAME:
		m_game->Update();
		break;
		// �`���[�g���A��
	//case MODE_TUTORIAL:
		//m_tutorial->Update();
		//break;
		// �����L���O
	/*case MODE_RANKING:
		m_ranking->Update();
		break;*/
	default:
		break;
	}

	// ��ʑJ��
	m_fade->Update();
}

// ------------------------------------------
//
// �`��֐�
//
// ------------------------------------------
void CManager::Draw(void)
{
	// �����_�����O
	m_renderer->Draw();
}

// ------------------------------------------
// ���[�h�ݒ�֐�
// ------------------------------------------
void CManager::SetMode(MODE mode)
{
	// �O�̃��[�h�I��
	switch (m_mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		//m_sound->StopSound(CSound::LABEL_BGM_TITLE);
		m_title->Uninit();
		break;
		// �Q�[��
	case MODE_GAME:

		m_game->Uninit();

		// �Q�[��BGM
		//m_sound->StopSound(CSound::LABEL_BGM_GAME);

		break;

		// �����L���O
	//case MODE_RANKING:
	//	m_ranking->Uninit();

	//	//m_sound->StopSound(CSound::LABEL_BGM_RESULT);

	//	break;
	default:
		break;
	}

	m_mode = mode;	// ���݂̃��[�h����

	// ���݂̃��[�h������
	switch (mode)
	{
		// �^�C�g��
	case MODE_TITLE:
		m_title->Init();
		CLight::SetLight();
		//CPointLight::SetPointLight();
		// �^�C�g��BGM
		//m_sound->PlaySound(CSound::LABEL_BGM_TITLE);

		break;
		// �Q�[��
	case MODE_GAME:
		//CRenderer::GetCamera()->SetRot();
		m_game->Init();
		CLight::SetLight();
		//CPointLight::SetPointLight();
		// �Q�[��BGM
		//m_sound->PlaySound(CSound::LABEL_BGM_GAME);

		break;
		// �`���[�g���A��
	//case MODE_TUTORIAL:
		//m_tutorial->Init();

		// �Q�[��BGM
		//m_sound->PlaySound(CSound::LABEL_BGM_GAME);

		//break;
		// �����L���O
	//case MODE_RANKING:
	//	m_ranking->Init();

	//	//m_sound->PlaySound(CSound::LABEL_BGM_RESULT);

	//	break;
	default:
		break;
	}
}

// ------------------------------------------
// �����_�����O�擾�֐�
// ------------------------------------------
CRenderer * CManager::GetRenderer(void)
{
	return m_renderer;
}

// ------------------------------------------
// �L�[�{�[�h�擾�֐�
// ------------------------------------------
CKeyboard * CManager::GetKeyboard(void)
{
	return m_keyboard;
}

// ------------------------------------------
// �W���C�p�b�h�擾�֐�
// ------------------------------------------
CJoypad * CManager::GetJoy(void)
{
	return m_joypad;
}

// ------------------------------------------
// �}�E�X�擾�֐�
// ------------------------------------------
CMouse * CManager::GetMouse(void)
{
	return m_mouse;
}

// ------------------------------------------
// �T�E���h�擾�֐�
// ------------------------------------------
CSound * CManager::GetSound(void)
{
	return m_sound;
}

// ------------------------------------------
// ��ʑJ�ڎ擾�֐�
// ------------------------------------------
CFade * CManager::GetFade(void)
{
	return m_fade;
}

// ------------------------------------------
// �Q�[���擾�֐�
// ------------------------------------------
CGame * CManager::GetGame(void)
{
	return m_game;
}

// ------------------------------------------
// �`���[�g���A���擾�֐�
// ------------------------------------------
CTutorial * CManager::GetTutorial(void)
{
	return m_tutorial;
}

// ------------------------------------------
// �^�C�g���擾�֐�
// ------------------------------------------
CTitle * CManager::GetTitle(void)
{
	return m_title;
}

// ------------------------------------------
// �����L���O�擾�֐�
// ------------------------------------------
//CRanking * CManager::GetRanking(void)
//{
//	return m_ranking;
//}

// ------------------------------------------
// ���[�h�擾�֐�
// ------------------------------------------
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}
