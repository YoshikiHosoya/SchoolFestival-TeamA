//------------------------------------------------------------------------------
//
//�|�[�Y����  [Pause.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "pause.h"		//�C���N���[�h�t�@�C��
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "menu.h"
#include "game.h"
#include "option.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CPause::CPause()
{
	m_pScene2DList.clear();
	m_pMenu.reset();
	m_pOption.reset();
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CPause::~CPause()
{
	m_pScene2DList.clear();
	m_pMenu.reset();
	m_pOption.reset();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CPause::Init()
{
	//���S�Ɣw�i�̐���
	m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 450.0f, 0.0f), D3DXVECTOR3(1600.0f, 900.0f, 0.0f)));
	m_pScene2DList[TEX_BG]->SetVtxCol(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.8f));
	m_pScene2DList[TEX_BG]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TITLE_BG));

	m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0, 0.0f), D3DXVECTOR3(750.0f, 150.0f, 0.0f)));
	m_pScene2DList[TEX_LOGO]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_LOGO));

	//�|�[�Y���j���[�̐���
	m_pMenu = CMenu::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 500.0f, 0.0f), D3DXVECTOR3(500.0f, 100.0f, 0.0f),
							CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_PAUSE_MENU), D3DXVECTOR2(1, 4),CMenu::MENU_VERTICAL);


	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CPause::Uninit()
{
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CPause::Update()
{
	//�I�v�V�����J���Ă��邩�ǂ���
	//nullcheck
	if (m_pOption)
	{
		//�X�V
		m_pOption->Update();

		//�L�����Z���{�^��
		if (CHossoLibrary::CheckCancel())
		{
			//�I�v�V�����J��
			m_pOption.reset();
		}
	}
	else
	{
		//nullcehck
		if (!m_pScene2DList.empty())
		{
			for (size_t nCnt = 0; nCnt < m_pScene2DList.size(); nCnt++)
			{
				//nullcheck
				if (m_pScene2DList[nCnt])
				{
					//�X�V����
					m_pScene2DList[nCnt]->Update();
				}
			}
		}

		//�|�[�Y����scene���~�܂�̂ł����ŏ���
		m_pMenu->MenuSelect();
		m_pMenu->Update();


		//����{�^�������ꂽ�Ƃ�
		if (CHossoLibrary::CheckDecision())
		{
			//���I��ł���ԍ��ŏ����ύX
			switch (m_pMenu->GetSelectNum())
			{
			case 0:
				//�Q�[���ɖ߂�
				CManager::GetGame()->SetGamestate(CGame::STATE_NORMAL);
				break;
			case 1:
				//�Q�[�����X�^�[�g
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
				break;
			case 2:
				//�I�v�V�������J��
				m_pOption = COption::Create();
				break;
			case 3:
				//�^�C�g���ɖ߂�
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
				break;
			default:
				//�Q�[���ɖ߂�
				CManager::GetGame()->SetGamestate(CGame::STATE_NORMAL);
				break;
			}
		}
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CPause::Draw()
{
	//nullcehck
	if (!m_pScene2DList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_pScene2DList.size(); nCnt++)
		{
			//nullcheck
			if (m_pScene2DList[nCnt])
			{
				//�`��
				m_pScene2DList[nCnt]->Draw();
			}
		}
	}
	//�|�[�Y����scene���~�܂�̂ł����ŏ���
	m_pMenu->Draw();

	//nullcheck
	if (m_pOption)
	{
		//�`��
		m_pOption->Draw();
	}
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CPause::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
std::shared_ptr<CPause> CPause::Create()
{
	//�ϐ��錾
	std::shared_ptr<CPause> pPause(new CPause);

	//������
	pPause->Init();

	//Scene�ɒǉ�
	pPause->SetObjType(CScene::OBJTYPE_PAUSE);
	pPause->AddSharedList(pPause);

	//�����������
	return pPause;
}

//------------------------------------------------------------------------------
//�I�v�V�����J���Ă��邩�ǂ���
//------------------------------------------------------------------------------
bool CPause::GetOptionWindow()
{
	if (m_pOption)
	{
		return true;
	}
	return false;
}
