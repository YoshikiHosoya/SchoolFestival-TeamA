// =====================================================================================================================================================================
//
// �}�l�[�W���[�̏��� [manager.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "manager.h"			// �C���N���[�h�t�@�C��
#include "renderer.h"
#include "scene2D.h"
#include "scene3D.h"
#include "sceneX.h"
#include "scene.h"
#include "keyboard.h"
#include "xinputGpad.h"
#include "player.h"
#include "meshfield.h"
#include "title.h"
#include "game.h"
#include "result.h"
#include "ranking.h"
#include "sound.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CRenderer		*CManager::m_pRenderer	= NULL;			// �����_���[
CKeyboard		*CManager::m_pKeyboard	= NULL;			// �L�[�{�[�h
CXinputGpad		*CManager::m_pXinputGpad = NULL;		// �Q�[���p�b�h
CManager::MODE	CManager::m_mode		= MODE::GAME;	// �Q�[�����[�h
CTitle			*CManager::m_pTitle		= NULL;			// �^�C�g��
CGame			*CManager::m_pGame		= NULL;			// �Q�[��
CResult			*CManager::m_pResult	= NULL;			// ���U���g
CRanking		*CManager::m_pRanking	= NULL;			// �����L���O
CSound			*CManager::m_pSound		= NULL;			// �T�E���h

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CManager::CManager()
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CManager::~CManager()
{

}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	// �������̊m��
	m_pRenderer		= new CRenderer;
	m_pKeyboard		= new CKeyboard;
	m_pXinputGpad	= new CXinputGpad;
	m_pSound		= new CSound;

	// ����������			 
	if (FAILED(m_pRenderer->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}
	// �L�[�{�[�h�̏�����
	m_pKeyboard->Init(hInstance, hWnd);

	//// �Q�[���p�b�h�̏�����
	//m_pXinputGpad->Init(hInstance, hWnd);

	// �T�E���h�̏�����
	m_pSound->Init(hWnd);

	// �Z�b�g���[�h
	SetMode(m_mode);

	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CManager::Uninit(void)
{
	// �L�[�{�[�h
	if (m_pKeyboard != NULL)
	{
		// �L�[�{�[�h�̏I��
		m_pKeyboard->Uninit();

		// �������̊J��
		delete m_pKeyboard;
		m_pKeyboard = NULL;
	}

	// �Q�[���p�b�h
	//if (m_pInputGpad != NULL)
	//{
	//	// �Q�[���p�b�h�̏I��
	//	m_pXinputGpad->Uninit();

	//	// �������̊J��
	//	delete m_pInputGpad;
	//	m_pInputGpad = NULL;
	//}

	// �T�E���h
	if (m_pSound != NULL)
	{
		// �T�E���h�̏I��
		m_pSound->Uninit();

		// �������̊J��
		delete m_pSound;
		m_pSound = NULL;
	}

	// �����_���[
	if (m_pRenderer != NULL)
	{
		// �I������
		m_pRenderer->Uninit();

		// �������̊J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}

	// �^�C�g��
	if (m_pTitle != NULL)
	{
		// �I������
		m_pTitle->Uninit();

		// �������̊J��
		delete m_pTitle;
		m_pTitle = NULL;
	}

	// �Q�[��
	if (m_pGame != NULL)
	{
		// �I������
		m_pGame->Uninit();

		// �������̊J��
		delete m_pGame;
		m_pGame = NULL;
	}

	// ���U���g
	if (m_pResult != NULL)
	{
		// �I������
		m_pResult->Uninit();

		// �������̊J��
		delete m_pResult;
		m_pResult = NULL;
	}

	// �����L���O
	if (m_pRanking != NULL)
	{
		// �I������
		m_pRanking->Uninit();

		// �������̊J��
		delete m_pRanking;
		m_pRanking = NULL;
	}

	CScene::ReleaseAll();

}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CManager::Update(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

#ifdef _DEBUG
	if (m_pKeyboard->GetKeyboardPress(DIK_F7))
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		// ���C���[�t���[���̕\��
	}
	if (m_pKeyboard->GetKeyboardPress(DIK_F8))
	{
		pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);			// ���C���[�t���[���̔�\��
	}
#endif

	// �����_���[
	if (m_pRenderer != NULL)
	{
		// �����_���[�̍X�V
		m_pRenderer->Update();
	}

	// �L�[�{�[�h
	if (m_pKeyboard != NULL)
	{
		// �L�[�{�[�h�̍X�V
		m_pKeyboard->Update();
	}

	// �Q�[���p�b�h
	if (m_pXinputGpad != NULL)
	{
		// �Q�[���p�b�h�̍X�V
		m_pXinputGpad->Update();
	}

	// ���[�h�ʂ̍X�V
	switch (m_mode)
	{
	case TITLE:
		// �^�C�g���̍X�V
		m_pTitle->Update();
		break;

	case GAME:
		// �Q�[���̍X�V
		m_pGame->Update();
		break;

	case RESULT:
		// ���U���g�̍X�V
		m_pResult->Update();
		break;

	case RANKING:
		// �����L���O�̍X�V
		m_pRanking->Update();
		break;
	}
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CManager::Draw(void)
{	
	// �����_���[
	if (m_pRenderer != NULL)
	{
		// �`�揈��
		m_pRenderer->Draw();

		// ���[�h�ʂ̕`��
		switch (m_mode)
		{
		case TITLE:
			// �^�C�g���̕`��
			m_pTitle->Draw();
			break;

		case GAME:
			// �Q�[���̕`��
			m_pGame->Draw();
			break;

		case RESULT:
			// ���U���g�̕`��
			m_pResult->Draw();
			break;

		case RANKING:
			// �����L���O�̕`��
			m_pRanking->Draw();
			break;
		}
	}
}

// =====================================================================================================================================================================
//
// ���[�h�̐ݒ�
//
// =====================================================================================================================================================================
void CManager::SetMode(MODE mode)
{
	// �S�Ē�~
	m_pSound->StopSound();

	// ���[�h�ʂ̏I��
	switch (m_mode)
	{
	case TITLE:
		// �^�C�g���̏I��
		m_pTitle->Uninit();

		// �������̊J��
		delete m_pTitle;
		m_pTitle = NULL;
		break;

	case GAME:
		// �Q�[���̏I��
		m_pGame->Uninit();

		// �������̊J��
		delete m_pGame;
		m_pGame = NULL;
		break;

	case RESULT:
		// ���U���g�̏I��
		m_pResult->Uninit();

		// �������̊J��
		delete m_pResult;
		m_pResult = NULL;
		break;

	case RANKING:
		// �����L���O�̏I��
		m_pRanking->Uninit();

		// �������̊J��
		delete m_pRanking;
		m_pRanking = NULL;
		break;
	}

	m_mode = mode;

	// ���[�h�ʂ̏�����
	switch (mode)
	{
	case TITLE:
		// �^�C�g���̐���
		m_pTitle = CTitle::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_TITLE);
		break;

	case GAME:
		// �Q�[���̐���
		m_pGame = CGame::Create();
		//m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_GAME);
		break;

	case RESULT:
		// ���U���g�̐���
		m_pResult = CResult::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_OVER);
		break;

	case RANKING:
		// �����L���O�̐���
		m_pRanking = CRanking::Create();
		m_pSound->PlaySound(CSound::SOUND_LABEL_BGM_RANK);
		break;
	}
}

// =====================================================================================================================================================================
//
// �����_��-�̎擾
//
// =====================================================================================================================================================================
CRenderer * CManager::GetRenderer(void)
{
	if (m_pRenderer != NULL)
	{
		return m_pRenderer;
	}
	return NULL;
}

// =====================================================================================================================================================================
//
// ���͂̎擾
//
// =====================================================================================================================================================================
CKeyboard * CManager::GetKeyboard(void)
{
	if (m_pKeyboard != NULL)
	{
		return m_pKeyboard;
	}
	return NULL;
}

// =====================================================================================================================================================================
//
// �Q�[���p�b�h�̎擾
//
// =====================================================================================================================================================================
CXinputGpad * CManager::GetXinputGpad(void)
{
	if (m_pXinputGpad != NULL)
	{
		return m_pXinputGpad;
	}
	return NULL;
}

// =====================================================================================================================================================================
//
// �Q�[���̎擾
//
// =====================================================================================================================================================================
CGame * CManager::GetGame(void)
{
	if (m_pGame != NULL)
	{
		return m_pGame;
	}
	return NULL;
}

// =====================================================================================================================================================================
//
// �T�E���h�̎擾
//
// =====================================================================================================================================================================
CSound * CManager::GetSound(void)
{
	return m_pSound;
}