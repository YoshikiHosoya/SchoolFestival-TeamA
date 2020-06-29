//------------------------------------------------------------------------------
//
//�I�v�V��������  [option.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "option.h"		//�C���N���[�h�t�@�C��
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "menu.h"
#include "game.h"
#include "sound.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
bool COption::m_bAutoRotation = false;
bool COption::m_bCameraFlip_X = false;
bool COption::m_bCameraFlip_Y = false;

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
COption::COption()
{
	m_pScene2DList.clear();
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
COption::~COption()
{
	m_pScene2DList.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT COption::Init()
{
	//BG
	m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f)));
	m_pScene2DList[TEX_OPTION_BG]->SetVtxCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//LOGO
	m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0, 0.0f), D3DXVECTOR3(750.0f, 150.0f, 0.0f)));
	m_pScene2DList[TEX_OPTION_LOGO]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_OPTION_LOGO));


	//UV�̏c�̒����v�Z
	float fUV_y = 1.0f / COption::OPTOIN_MAX;

	for (int nCnt = 0; nCnt < COption::OPTOIN_MAX; nCnt++)
	{
		//����
		m_pOptionItemList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(450.0f,300.0f + (nCnt * 100.0f), 0.0f), D3DXVECTOR3(600.0f, 50.0f, 0.0f)));
		m_pOptionItemList[nCnt]->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_OPTIONMENU));
		m_pOptionItemList[nCnt]->SetAnimation(D3DXVECTOR2(0.0f, fUV_y * nCnt), D3DXVECTOR2(1.0f, fUV_y));

		//ONOFF
		m_OnOffList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(900.0f, 300.0f + (nCnt * 100.0f), 0.0f), D3DXVECTOR3(150.0f, 80.0f, 0.0f)));
		m_OnOffList[nCnt]->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_ON_OFF));
	}

	m_OnOffList[OPTION_CAMERA_AUTO_ROTATION]->SetAnimation(D3DXVECTOR2(0.0f, 0.5f * m_bAutoRotation), D3DXVECTOR2(1.0f, 0.5f));
	m_OnOffList[OPTION_CAMERA_FLIP_X]->SetAnimation(D3DXVECTOR2(0.0f, 0.5f * m_bCameraFlip_X), D3DXVECTOR2(1.0f, 0.5f));
	m_OnOffList[OPTION_CAMERA_FLIP_Y]->SetAnimation(D3DXVECTOR2(0.0f, 0.5f * m_bCameraFlip_Y), D3DXVECTOR2(1.0f, 0.5f));


	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void COption::Uninit()
{


}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void COption::Update()
{

	CHossoLibrary::SelectVerticalMenu(m_NowSelectItem, m_pOptionItemList.size());

	//nullcehck
	if (!m_pScene2DList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_pScene2DList.size(); nCnt++)
		{
			//nullcheck
			if (m_pScene2DList[nCnt])
			{
				//�X�V
				m_pScene2DList[nCnt]->Update();
			}
		}
	}
	//nullcehck
	if (!m_OnOffList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_OnOffList.size(); nCnt++)
		{
			//nullcheck
			if (m_OnOffList[nCnt])
			{
				//�X�V
				m_OnOffList[nCnt]->Update();
			}
		}
	}
	//nullcehck
	if (!m_pOptionItemList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_pOptionItemList.size(); nCnt++)
		{
			//nullcheck
			if (m_pOptionItemList[nCnt])
			{
				//�J�[�\���̍��������͖̂��邭
				if (nCnt == m_NowSelectItem)
				{
					m_pOptionItemList[nCnt]->SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
					m_OnOffList[nCnt]->SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));


					if (CHossoLibrary::CheckSelect() == CHossoLibrary::LEFT || CHossoLibrary::CheckSelect() == CHossoLibrary::RIGHT)
					{
						switch (m_NowSelectItem)
						{
						case OPTION_CAMERA_AUTO_ROTATION:
							m_bAutoRotation ^= 1;
							m_OnOffList[nCnt]->SetAnimation(D3DXVECTOR2(0.0f, 0.5f * m_bAutoRotation), D3DXVECTOR2(1.0f, 0.5f));
							CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);

							break;
						case OPTION_CAMERA_FLIP_X:
							m_bCameraFlip_X ^= 1;
							m_OnOffList[nCnt]->SetAnimation(D3DXVECTOR2(0.0f, 0.5f * m_bCameraFlip_X), D3DXVECTOR2(1.0f, 0.5f));
							CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);

							break;
						case OPTION_CAMERA_FLIP_Y:
							m_bCameraFlip_Y ^= 1;
							m_OnOffList[nCnt]->SetAnimation(D3DXVECTOR2(0.0f, 0.5f * m_bCameraFlip_Y), D3DXVECTOR2(1.0f, 0.5f));
							CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);

							break;
						}


					}


				}
				//����ȊO�̍��ڂ͈Â�
				else
				{
					m_pOptionItemList[nCnt]->SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
					m_OnOffList[nCnt]->SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

				}
				//�X�V
				m_pOptionItemList[nCnt]->Update();
			}
		}
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void COption::Draw()
{
	//nullcehck
	if (!m_pScene2DList.empty())
	{
		//�`�揈��
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
	//nullcehck
	if (!m_OnOffList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_OnOffList.size(); nCnt++)
		{
			//nullcheck
			if (m_OnOffList[nCnt])
			{
				//�`��
				m_OnOffList[nCnt]->Draw();
			}
		}
	}
	//nullcehck
	if (!m_pOptionItemList.empty())
	{
		for (size_t nCnt = 0; nCnt < m_pOptionItemList.size(); nCnt++)
		{
			//nullcheck
			if (m_pOptionItemList[nCnt])
			{
				//�`��
				m_pOptionItemList[nCnt]->Draw();
			}
		}
	}
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void COption::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
std::unique_ptr<COption> COption::Create()
{
	//�ϐ��錾
	std::unique_ptr<COption> pPause(new COption);

	//������
	pPause->Init();

	//�����������
	return pPause;
}
