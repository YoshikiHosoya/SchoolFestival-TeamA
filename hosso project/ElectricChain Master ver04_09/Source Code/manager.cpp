//------------------------------------------------------------------------------
//
//�}�l�[�W���[����  [manager.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "input.h"
#include "keyboard.h"
#include "pad_XInput.h"
#include "mouse.h"
#include "fade.h"
#include "game.h"
#include "title.h"
#include "tutorial.h"
#include "demoplay.h"
#include "result.h"
#include "ranking.h"
#include "basemode.h"
#include "scene.h"
#include "enemy.h"
#include "Debug/debug_motionviewer.h"
#include "Debug/Debug_room.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
std::unique_ptr<CRenderer> CManager::m_pRenderer = nullptr;
std::unique_ptr<CSound> CManager::m_pSound = nullptr;
std::unique_ptr<CKeyboard> CManager::m_pKeyboard = nullptr;
std::unique_ptr<CMouse> CManager::m_pMouse = nullptr;
std::unique_ptr<CPad_XInput> CManager::m_pXInput = nullptr;

std::unique_ptr<CBaseMode> CManager::m_pBaseMode = nullptr;
CManager::MODE CManager::m_mode = CManager::MODE_GAME;
HWND CManager::m_hWnd = nullptr;
int CManager::m_nNumChangeMode = 0;
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	//�������m��
	m_pRenderer.reset(new CRenderer);
	m_pSound.reset(new CSound);
	m_pKeyboard.reset(new CKeyboard);
	m_pMouse.reset(new CMouse);
	m_pXInput.reset(new CPad_XInput);
	m_nNumChangeMode = 0;

	m_hWnd = hWnd;

	//�����_���[������
	if (FAILED(m_pRenderer->Init(hInstance, hWnd, bWindow)))
	{
		//���s
		MessageBox(hWnd, "�����_���[�ݒ莸�s", "Renderer", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}
	//�����_���[������
	if (FAILED(m_pSound->Init(hWnd)))
	{
		//���s
		MessageBox(hWnd, "�T�E���h�ݒ莸�s", "Sound", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//�L�[�{�[�h������
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		//���s
		MessageBox(hWnd, "���������s", "KeyBoard", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//�}�E�X������
	if (FAILED(m_pMouse->Init(hInstance, hWnd)))
	{
		//���s
		MessageBox(hWnd, "���������s", "Mouse", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//�Q�[���p�b�h������
	if (FAILED(m_pXInput->Init(hInstance, hWnd)))
	{
		//���s
		MessageBox(hWnd, "���������s", "m_pXInput", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//���C�u��������
	if (FAILED(CHossoLibrary::InitImgui(hWnd)))
	{
		//���s
		MessageBox(hWnd, "���������s", "InputMacro", MB_OK | MB_ICONHAND);
		return E_FAIL;
	}

	//�x�[�X�̑f�ސ���
	CBaseMode::BaseLoad(hWnd);

	//���[�h�ݒ�
	SetMode(m_mode);

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CManager::Uninit()
{
	//ImGui�I��
	CHossoLibrary::UninitImgui();

	//�x�[�X�̑f�ޔj��
	CBaseMode::BaseUnload();

	//�������J��
	if (m_pRenderer)
	{	//�����_���[
		m_pRenderer->Uninit();
		m_pRenderer.reset();
	}

	if (m_pKeyboard)
	{	//�L�[�{�[�h
		m_pKeyboard->Uninit();
		m_pKeyboard.reset();
	}

	if (m_pMouse)
	{	//�}�E�X
		m_pMouse->Uninit();
		m_pMouse.reset();
	}

	if (m_pXInput)
	{	//�Q�[���p�b�h
		m_pXInput->Uninit();
		m_pXInput.reset();
	}
	if (m_pBaseMode)
	{
		//���[�h
		m_pBaseMode->Uninit();
		m_pBaseMode.reset();

	}

	if (m_pSound)
	{//�T�E���h
		m_pSound->Uninit();
		m_pSound.reset();
		m_pSound = nullptr;
	}
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CManager::Update()
{
	//�X�V
	if (m_pKeyboard)
	{	//�L�[�{�[�h
		m_pKeyboard->Update();
	}

	if (m_pMouse)
	{	//�}�E�X
		m_pMouse->Update();
	}

	if (m_pXInput)
	{	//�Q�[���p�b�h
		m_pXInput->Update();
	}


	//�X�e�B�b�N�̏��X�V
	CHossoLibrary::ResetStickInfo();

	if (m_pRenderer)
	{	//�����_���[
		m_pRenderer->Update();

	}
	if (m_pBaseMode)
	{	//���[�h
		m_pBaseMode->Update();
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CManager::Draw()
{
	if (m_pBaseMode)
	{	//���[�h
		m_pBaseMode->Draw();
	}
	if (m_pRenderer)
	{
		//�����_���[
		m_pRenderer->Draw();
	}
}

//------------------------------------------------------------------------------
//���[�h�ݒ�
//------------------------------------------------------------------------------
void CManager::SetMode(MODE nextmode)
{
	//�J�E���g
	m_nNumChangeMode++;
	std::cout << "SetMode - " << m_nNumChangeMode << NEWLINE;;

	//�T�E���h�X�g�b�v
	m_pSound->StopAll();

	//nullcheck
	if (m_pBaseMode)
	{
		//�I������
		m_pBaseMode->Uninit();

		//�������J��
		m_pBaseMode.reset();
		std::cout << "delete BaseMode" << NEWLINE;;
		m_pBaseMode = nullptr;

	}

	m_mode = nextmode;

	//���̃��[�h�̃������m��
	switch (nextmode)
	{
		//title
	case MODE_TITLE:
		m_pBaseMode.reset(new CTitle);
		std::cout << "new BaseMode[Title]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_TITLE);
		break;

		//demoplay
	case MODE_DEMOPLAY:
		m_pBaseMode.reset(new CDemoPlay);
		std::cout << "new BaseMode[Demoplay]" << NEWLINE;
		break;

		//tutorial
	case MODE_TUTORIAL:
		m_pBaseMode.reset(new CTutorial);
		std::cout << "new BaseMode[Tutorial]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_TUTORIAL);
		break;

		//game
	case MODE_GAME:
		m_pBaseMode.reset(new CGame);
		std::cout << "new BaseMode[Game]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_GAME);
		break;

		//result
	case MODE_RESULT:
		m_pBaseMode.reset(new CResult);
		std::cout << "new BaseMode[result]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_RESULT);
		break;

		//ranking
	case MODE_RANKING:
		m_pBaseMode.reset(new CRanking);
		std::cout << "new BaseMode[ranking]" << NEWLINE;
		m_pSound->Play(CSound::LABEL_BGM_RANKING);
		break;

		//debug
	case MODE_DEBUG_MOTION_VIEWER:
		m_pBaseMode.reset(new CDebug_MotionViewer);
		std::cout << "new BaseMode[CDebug_MotionViewer]" << NEWLINE;
		break;

		//debug
	case MODE_DEBUG_ROOM:
		m_pBaseMode.reset(new CDebug_Room);
		std::cout << "new BaseMode[CDebug_Room]" << NEWLINE;
		break;

		//gameend
	case MODE_END:
		PostQuitMessage(0);
		break;

		//����ȊO
	default:
		//�G���[
		MessageBox(m_hWnd, "�J�ڎ��s", "Manager", MB_OK | MB_ICONHAND);
		break;
	}

	//�G�̏�񏉊���
	CEnemy:: ResetEnemyStaticInfo();

	//nullcheck
	if (m_pBaseMode)
	{
		//������
		if (FAILED(m_pBaseMode->Init(m_hWnd)))
		{
			//���s
			MessageBox(m_hWnd, "���������s", "BaseMode", MB_OK | MB_ICONHAND);
		}
	}
	CScene::SetStop(false);
}

//------------------------------------------------------------------------------
//�x�[�X���[�h�̏��擾
//------------------------------------------------------------------------------
CBaseMode * CManager::GetBaseMode()
{
	//nullcheck
	if (m_pBaseMode)
	{
		return m_pBaseMode.get();
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�Q�[�����擾����
//------------------------------------------------------------------------------
CGame * CManager::GetGame()
{
	//�Q�[�������ǂ���
	if (m_mode == CManager::MODE_GAME)
	{
		//nullcheck
		if (m_pBaseMode)
		{
			//�L���X�g
			CGame *pGame = ((CGame*)m_pBaseMode.get());

			//nullcheck
			if (pGame)
			{
				return pGame;
			}
		}
	}
	return nullptr;
}
