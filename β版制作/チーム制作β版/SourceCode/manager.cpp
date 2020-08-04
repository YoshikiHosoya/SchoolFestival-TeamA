#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "model.h"
#include "game.h"
#include "title.h"
#include "ranking.h"
#include "tutorial.h"
#include "texture.h"
#include "Xinput.h"
#include "texture.h"
#include "BaseMode.h"
#include "mouse.h"
#include "hosso/Debug_ModelViewer.h"
#include "hosso/Debug_EffectViewer.h"
#include "Debug_MapEditor.h"
#include "XInputPad.h"
#include "sound.h"
//���̂Ƃ��ł��g����悤�ɂ��郁���o
CRenderer		*CManager::m_pRenderer		= nullptr;
CKeyboard		*CManager::m_pInputKeyboard	= nullptr;
CParticle		*CManager::m_Particle		= nullptr;
CBaseMode		*CManager::m_pBaseMode		= nullptr;
CMouse			*CManager::m_pMouse			= nullptr;
CManager::MODE	CManager::m_mode = CManager::MODE_TITLE;
CXInputPad		*CManager::m_pPad			= nullptr;
CSound			*CManager::m_pSound = nullptr;


CManager::CManager()
{
}

CManager::~CManager()
{
}
//===========================================
//������
//===========================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�������m��
	m_pRenderer = new CRenderer;
	m_pInputKeyboard = new CKeyboard;
	m_pMouse = new CMouse;
	m_pPad = new CXInputPad;
	m_pSound = new CSound;

	//����������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}
	m_pInputKeyboard->InitInput(hInstance, hWnd);
	m_pMouse->Init(hInstance, hWnd);
	m_pPad->Init(hInstance, hWnd);

	m_pSound->Init(hWnd);
	CBaseMode::BaseLoad(hWnd);
	CManager::SetMode(m_mode);
	return S_OK;
}
//===========================================
//�I��
//===========================================
void CManager::Uninit(void)
{
	//�x�[�X�̑f�ޔj��
	CBaseMode::BaseUnload();
	//nullcheck
	if (m_pRenderer)
	{
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
	if (m_pMouse)
	{
		m_pMouse->Uninit();
		delete m_pMouse;
		m_pMouse = nullptr;
	}
	if (m_pPad)
	{
		m_pPad->Uninit();
		delete m_pPad;
		m_pPad = nullptr;
	}
	if (m_pInputKeyboard)
	{
		m_pInputKeyboard->UninitInput();
		delete m_pInputKeyboard;
		m_pInputKeyboard = nullptr;
	}
	if (m_pBaseMode)
	{
		m_pBaseMode->Uninit();

		delete m_pBaseMode;
		m_pBaseMode = nullptr;
	}
	if (m_pSound)
	{
		m_pSound->Uninit();

		delete m_pSound;
		m_pSound = nullptr;
	}
}
//===========================================
//�X�V
//===========================================
void CManager::Update(void)
{
	m_pInputKeyboard->UpdateInput();
	m_pRenderer->Update();
	m_pMouse->Update();
	m_pPad->Update();
	if (m_pBaseMode)
	{	//���[�h
		m_pBaseMode->Update();
	}

}
//===========================================
//�`��
//===========================================
void CManager::Draw(void)
{
	if (m_pBaseMode)
	{	//���[�h
		m_pBaseMode->Draw();
	}
	m_pRenderer->Draw();
}
//===========================================
//���[�h�̐ݒ�
//===========================================
void CManager::SetMode(MODE mode)
{
	//nullcheck
	if (m_pBaseMode)
	{
		//�I������
		CScene::RereaseAll();
		m_pBaseMode->Uninit();
		delete m_pBaseMode;
		m_pBaseMode = nullptr;
	}

	//�����X�g�b�v
	m_pSound->StopAll();

	//���[�h�ؑ�
	m_mode = mode;

	//�����_���[���Z�b�g
	m_pRenderer->ResetRenderer();

	switch (mode)
	{
		//Title
	case MODE_TITLE:
		m_pBaseMode = new CTitle;
		m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;

		//Tutorial
	case MODE_TUTORIAL:
		m_pBaseMode = new CTutorial;
		m_pSound->Play(CSound::LABEL_BGM_TUTORIAL);
		break;

		//Game
	case MODE_GAME:
		m_pBaseMode = new CGame;
		m_pSound->Play(CSound::LABEL_BGM_GAME);

		break;

		//Ranking
	case MODE_RANKING:
		m_pBaseMode = new CRanking;
		m_pSound->Play(CSound::LABEL_BGM_RESULT);
		break;

		//MotionViewer
	case MODE_DEBUG_MODELVIEWER:
		m_pBaseMode = new CDebug_ModelViewer;
		break;

		//EffectViewer
	case MODE_DEBUG_EFFECTVIEWER:
		m_pBaseMode = new CDebug_EffectViewer;
		break;

		//MapEditor
	case MODE_DEBUG_MAPEDITOR:
		m_pBaseMode = new CDebugMapEditor;
		break;
	}

	//nullcheck
	if (m_pBaseMode)
	{
		//������
		m_pBaseMode->Init();
	}
}

//===========================================
//�Q�[���̏�Ԏ擾
//===========================================
CManager::MODE CManager::GetMode(void)
{
	return m_mode;
}
//===========================================
//�����_���[�̏���
//===========================================
CRenderer * CManager::GetRenderer(void)
{
	return m_pRenderer;
}
//===========================================
//�L�[�{�[�h�擾
//===========================================
CKeyboard * CManager::GetInputKeyboard(void)
{
	return m_pInputKeyboard;
}
//===========================================
//�x�[�X���[�h���̎擾
//===========================================
CBaseMode * CManager::GetBaseMode(void)
{
	if (m_pBaseMode)
	{
		return m_pBaseMode;
	}
	return nullptr;
}
//===========================================
//�}�E�X�̏��擾
//===========================================
CMouse * CManager::GetMouse()
{
	if (m_pMouse)
	{
		return m_pMouse;
	}
	return nullptr;
}
//===========================================
//�p�b�h�̏��擾
//===========================================
CXInputPad * CManager::GetPad(void)
{
	if (m_pPad)
	{
		return m_pPad;
	}
	return nullptr;
}

//===========================================
//�Q�[���̏��擾
//�ʂ̃��[�h�̎�����nullptr���Ԃ��Ă���
//===========================================
CGame * CManager::GetGame()
{
	//nullcheck
	if (m_pBaseMode)
	{
		//Game�N���X�ɃL���X�g
		CGame *pGame = (CGame*)m_pBaseMode;

		//nullcheck
		if (pGame)
		{
			return pGame;
		}
	}
	return nullptr;
}

//===========================================
//�T�E���h�擾
//===========================================
CSound * CManager::GetSound()
{
	return m_pSound;
}
