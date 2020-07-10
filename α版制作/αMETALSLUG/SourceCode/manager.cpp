#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "model.h"
#include "game.h"
#include "title.h"
#include "result.h"
#include "ranking.h"
#include "texture.h"
#include "Xinput.h"
#include "texture.h"
#include "BaseMode.h"
#include "mouse.h"
#include "hosso/Debug_ModelViewer.h"
#include "hosso/Debug_EffectViewer.h"
#include "XInputPad.h"
//���̂Ƃ��ł��g����悤�ɂ��郁���o
CRenderer	*CManager::m_pRenderer		= nullptr;
CKeyboard	*CManager::m_pInputKeyboard	= nullptr;
CParticle	*CManager::m_Particle		= nullptr;
CBaseMode	*CManager::m_pBaseMode		= nullptr;
CMouse		*CManager::m_pMouse			= nullptr;
CManager::GAME_MODE CManager::m_mode = CManager::MODE_TITLE;
CXInputPad	*CManager::m_pPad			= nullptr;
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
	//m_pMouse = new CMouse;
	//����������
	if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
	{
		return -1;
	}
	m_pInputKeyboard->InitInput(hInstance, hWnd);
	m_pMouse->Init(hInstance, hWnd);
	m_pPad->Init(hInstance, hWnd);
	CBaseMode::BaseLoad(hWnd);
	CManager::SetGameMode(m_mode);
	return S_OK;
}
//===========================================
//�I��
//===========================================
void CManager::Uninit(void)
{
	//�x�[�X�̑f�ޔj��
	CBaseMode::BaseUnload();
	m_pRenderer->Uninit();
	m_pMouse->Uninit();
	m_pPad->Uninit();
	if (m_pBaseMode)
	{
		//���[�h
		m_pBaseMode->Uninit();
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
void CManager::SetGameMode(GAME_MODE mode)
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

	//���[�h�ؑ�
	m_mode = mode;

	//�����_���[���Z�b�g
	m_pRenderer->ResetRenderer();

	switch (mode)
	{
		//Title
	case MODE_TITLE:
		m_pBaseMode = new CTitle;
		m_pBaseMode->Init();
		break;

		//Game
	case MODE_GAME:
		m_pBaseMode = new CGame;
		m_pBaseMode->Init();
		break;

		//Result
	case MODE_RESULT:
		m_pBaseMode = new CResult;
		m_pBaseMode->Init();
		break;

		//Ranking
	case MODE_RANKING:
		m_pBaseMode = new CRanking;
		m_pBaseMode->Init();
		break;

		//Tutorial
	/*case MODE_TUTORIAL:
		break;*/

		//MotionViewer
	case MODE_DEBUG_MODELVIEWER:
		m_pBaseMode = new CDebug_ModelViewer;
		m_pBaseMode->Init();

		break;

		//EffectViewer
	case MODE_DEBUG_EFFECTVIEWER:
		m_pBaseMode = new CDebug_EffectViewer;
		m_pBaseMode->Init();

		break;
	}
}

//===========================================
//�Q�[���̏�Ԏ擾
//===========================================
CManager::GAME_MODE CManager::GetGameState(void)
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
