// =====================================================================================================================================================================
//
// �|�[�YUI�̏��� [pauseUI.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "pauseUI.h"			// �C���N���[�h�t�@�C��
#include "renderer.h"
#include "pause.h"
#include "scene2D.h"
#include "UIManager.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
int					CPauseUI::m_nNum								= 0;

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MENU_POSY			(200.0f)		// ���j���[�̈ʒuY					( ���j���[ )
#define MENU_SPACE			(100.0f)		// ���j���[�̃X�y�[�X				( ���j���[ )
#define ICON_POSX			(450.0f)		// �A�C�R���̈ʒuX					( �A�C�R�� )

#define BG_SIZE				(D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f))					// �w�i�̃T�C�Y
#define MENU_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, (MENU_POSY + MENU_SPACE * nCnt), 0.0f))		// ���j���[�̈ʒu
#define MENU_SIZE			(D3DXVECTOR3(200.0f, 80.0f, 0.0f))											// ���j���[�̃T�C�Y

#define LOGO_POS			(D3DXVECTOR3(SCREEN_WIDTH / 2, 150.0f, 0.0f))								// ���S�̈ʒu
#define LOGO_SIZE			(D3DXVECTOR3(250.0f, 75.0f, 0.0f))											// ���S�̃T�C�Y
#define ICON_POS			(D3DXVECTOR3(450.0f, (MENU_POSY + MENU_SPACE), 0.0f))						// �A�C�R���̈ʒu
#define ICON_SIZE			(D3DXVECTOR3(40.0f, 40.0f, 0.0f))											// �A�C�R���̃T�C�Y

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPauseUI::CPauseUI()
{
	// ������
	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = nullptr;
	}
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CPauseUI::~CPauseUI()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CPauseUI::Init()
{
	// �ϐ��̏�����
	m_nNum = 0;												// �i���o�[

	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			switch (nCnt)
			{
			case PAUSEUITYPE::P_UI_BG:

				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(BG_SIZE, BG_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_BG));
				// �F�̐ݒ�
				m_apScene2D[nCnt]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.5f));
				break;

			case PAUSEUITYPE::P_UI_RESUME:

				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(MENU_POS, MENU_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_RESUME));
				break;

			case PAUSEUITYPE::P_UI_EXIT:

				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(MENU_POS, MENU_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_EXIT));
				break;

			case PAUSEUITYPE::P_UI_LOGO:

				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(LOGO_POS, LOGO_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_LOGO));
				break;

			case PAUSEUITYPE::P_UI_ICON:

				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(ICON_POS, ICON_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_ICON));
				break;
			}
		}
	}
	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CPauseUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �I��
			delete m_apScene2D[nCnt];
			m_apScene2D[nCnt] = nullptr;

			// �f���[�g�t���O��L���ɂ���
			SetDeleteFlag(true);
		}
	}
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CPauseUI::Update(void)
{
	m_nNum = CPause::GetNum();

	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
	{
		// UI�̓��e�ݒ�
		UIConfig(nCnt);

		// �X�V
		m_apScene2D[nCnt]->Update();
	}
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CPauseUI::Draw(void)
{	
	for (int nCnt = 0; nCnt < PAUSEUITYPE::P_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �|�[�Y���Ă���Ƃ�
			if (CScene::GetStopFlag())
			{
				m_apScene2D[nCnt]->Draw();
			}
		}
	}
}

// =====================================================================================================================================================================
//
// �|�[�YUI�̐���
//
// =====================================================================================================================================================================
CPauseUI * CPauseUI::Create()
{
	// �������̊m��
	CPauseUI *pPauseUI = new CPauseUI();

	// ������
	pPauseUI->Init();

	//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
	CUIManager::AddUIList(std::move(pPauseUI));

	return pPauseUI;
}

// =====================================================================================================================================================================
//
// UI�̓��e�ݒ�
//
// =====================================================================================================================================================================
void CPauseUI::UIConfig(int nCnt)
{
	switch (nCnt)
	{
	case PAUSEUITYPE::P_UI_ICON:
		// �A�C�R���̈ړ����W
		switch (m_nNum)
		{
		// �ĊJ
		case CPause::PAUSE_RESUME:
			//�ʒu�̐ݒ�
			m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(ICON_POSX, (MENU_POSY + MENU_SPACE * m_nNum), 0.0f));
			break;

		// ���X�^�[�g
		case CPause::PAUSE_RESTART:
			//�ʒu�̐ݒ�
			m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(ICON_POSX, (MENU_POSY + MENU_SPACE * m_nNum), 0.0f));
			break;

		// �^�C�g��
		case CPause::PAUSE_TITLE:
			//�ʒu�̐ݒ�
			m_apScene2D[nCnt]->SetPosition(D3DXVECTOR3(ICON_POSX, (MENU_POSY + MENU_SPACE * m_nNum), 0.0f));
			break;
		}
		break;
	}
}