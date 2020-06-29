//------------------------------------------------------------------------------
//
//オプション処理  [option.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "option.h"		//インクルードファイル
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "menu.h"
#include "game.h"
#include "sound.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
bool COption::m_bAutoRotation = false;
bool COption::m_bCameraFlip_X = false;
bool COption::m_bCameraFlip_Y = false;

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
COption::COption()
{
	m_pScene2DList.clear();
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
COption::~COption()
{
	m_pScene2DList.clear();
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT COption::Init()
{
	//BG
	m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f)));
	m_pScene2DList[TEX_OPTION_BG]->SetVtxCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//LOGO
	m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0, 0.0f), D3DXVECTOR3(750.0f, 150.0f, 0.0f)));
	m_pScene2DList[TEX_OPTION_LOGO]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_OPTION_LOGO));


	//UVの縦の長さ計算
	float fUV_y = 1.0f / COption::OPTOIN_MAX;

	for (int nCnt = 0; nCnt < COption::OPTOIN_MAX; nCnt++)
	{
		//項目
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
//終了処理
//------------------------------------------------------------------------------
void COption::Uninit()
{


}
//------------------------------------------------------------------------------
//更新処理
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
				//更新
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
				//更新
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
				//カーソルの合ったものは明るく
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
				//それ以外の項目は暗く
				else
				{
					m_pOptionItemList[nCnt]->SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));
					m_OnOffList[nCnt]->SetVtxCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f));

				}
				//更新
				m_pOptionItemList[nCnt]->Update();
			}
		}
	}
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void COption::Draw()
{
	//nullcehck
	if (!m_pScene2DList.empty())
	{
		//描画処理
		for (size_t nCnt = 0; nCnt < m_pScene2DList.size(); nCnt++)
		{
			//nullcheck
			if (m_pScene2DList[nCnt])
			{
				//描画
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
				//描画
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
				//描画
				m_pOptionItemList[nCnt]->Draw();
			}
		}
	}
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void COption::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
std::unique_ptr<COption> COption::Create()
{
	//変数宣言
	std::unique_ptr<COption> pPause(new COption);

	//初期化
	pPause->Init();

	//生成した情報
	return pPause;
}
