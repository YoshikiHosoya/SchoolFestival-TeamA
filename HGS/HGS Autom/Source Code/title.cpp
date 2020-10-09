//------------------------------------------------------------------------------
//
//�^�C�g������  [title.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "fade.h"
#include "title.h"
#include "scene2D.h"
#include "bg.h"
#include "sound.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEMOPLAY_FADE_COUNT		(1000)		//�f���v���C�ɍs���܂ł̃J�E���^

#define TITLE_LOGO_SIZE			(D3DXVECTOR3(900.0f, 400.0f, 0.0f))

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTitle::CTitle()
{
	m_apScene2D.clear();

	m_nCntState = DEMOPLAY_FADE_COUNT;
	m_titlestate = STATE_START;

}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTitle::~CTitle()
{
	m_apScene2D.clear();
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTitle::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);

	// �^�C�g��UI�̐���
	TitleUICreate();

	CBg::Create(95);
	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CTitle::Uninit()
{
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTitle::Update()
{
	//�J�E���g�_�E��
	m_nCntState--;

	// �^�C�g��UI�̍X�V
	for (int nCnt = 0; nCnt < (int)TITLE_UI::TITLE_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			m_apScene2D[nCnt]->Update();
		}
	}


	//�t�F�[�h���ĂȂ���
	if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//�����{�^���������Ƃ�
		if (CHossoLibrary::CheckAnyButton())
		{
			//�X�e�[�g�ύX
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_2DGAME);
			CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}

}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTitle::Draw()
{
	// �^�C�g��UI�̕`��
	for (int nCnt = 0; nCnt < (int)TITLE_UI::TITLE_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			m_apScene2D[nCnt]->Draw();
		}
	}
}

//------------------------------------------------------------------------------
//�^�C�g��UI�̐���
//------------------------------------------------------------------------------
void CTitle::TitleUICreate()
{
	for (int nCnt = 0; nCnt < (int)TITLE_UI::TITLE_MAX; nCnt++)
	{
		if (nCnt == (int)TITLE_UI::TITLE_BLACK)
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3((SCREEN_WIDTH * 0.5f), SCREEN_HEIGHT, 0.0f), CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_NONE));
			// �F�ύX
			m_apScene2D[nCnt]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
		}

		if (nCnt == (int)TITLE_UI::TITLE_NAME)
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 200.0f, 0.0f), TITLE_LOGO_SIZE, CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TITLE_NAME));
		}

		if (nCnt == (int)TITLE_UI::TITLE_ENTER)
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 600.0f, 0.0f), D3DXVECTOR3(500.0f, 100.0f, 0.0f), CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_ENTER));
		}
	}
}