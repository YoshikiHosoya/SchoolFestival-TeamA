#include "manager.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Player.h"
#include "model.h"
#include "game.h"
#include "texture.h"
#include "Xinput.h"
#include "texture.h"
#include "BaseMode.h"
#include "mouse.h"
#include "SourceCode/hosso/Debug_ModelViewer.h"

//���̂Ƃ��ł��g����悤�ɂ��郁���o
CRenderer	*CManager::m_pRendere		= NULL;
CKeyboard	*CManager::m_pInputKeyboard	= NULL;
CParticle	*CManager::m_Particle		= NULL;
CBaseMode	*CManager::m_pBaseMode		= NULL;
CMouse		*CManager::m_pMouse			= NULL;
CManager::GAME_MODE CManager::m_mode = CManager::MODE_GAME;
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
	m_pRendere		 = new CRenderer;
	m_pInputKeyboard = new CKeyboard;
	m_pMouse = new CMouse;
	//m_pMouse = new CMouse;
	//����������
	if (FAILED(m_pRendere->Init(hWnd, TRUE)))
	{
		return -1;
	}
	m_pInputKeyboard->InitInput(hInstance, hWnd);
	m_pMouse->Init(hInstance, hWnd);
	CBaseMode::BaseLoad(hWnd);
	CManager::SetGameMode(MODE_GAME);
	return S_OK;
}
//===========================================
//�I��
//===========================================
void CManager::Uninit(void)
{
	//�x�[�X�̑f�ޔj��
	CBaseMode::BaseUnload();
	m_pRendere->Uninit();
	m_pMouse->Uninit();
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
	m_pRendere->Update();
	m_pMouse->Update();
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
	m_pRendere->Draw();
}
//===========================================
//���[�h�̐ݒ�
//===========================================
void CManager::SetGameMode(GAME_MODE mode)
{
	if (m_pBaseMode)
	{
		CScene::RereaseAll();
		m_pBaseMode->Uninit();
		delete m_pBaseMode;
		m_pBaseMode = nullptr;
	}
	m_mode = mode;

	switch (mode)
	{
	case MODE_TITLE:
		break;
	case MODE_GAME:
		m_pBaseMode = new CGame;
		m_pBaseMode->Init();
		break;
	case MODE_RESULT:
		break;
	case MODE_TUTORIAL:
		break;
	case MODE_CLEAR:
		break;
	case MODE_DEBUG_MODELVIEWER:
		m_pBaseMode = new CDebug_ModelViewer;
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
CRenderer * CManager::GetRendere(void)
{
	return m_pRendere;
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
