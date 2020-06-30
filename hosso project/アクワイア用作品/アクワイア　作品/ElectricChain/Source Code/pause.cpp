//------------------------------------------------------------------------------
//
//ポーズ処理  [Pause.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "pause.h"		//インクルードファイル
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "fade.h"
#include "menu.h"
#include "game.h"
#include "option.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CPause::CPause()
{
	m_pScene2DList.clear();
	m_pMenu.reset();
	m_pOption.reset();
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CPause::~CPause()
{
	m_pScene2DList.clear();
	m_pMenu.reset();
	m_pOption.reset();
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CPause::Init()
{
	//ロゴと背景の生成
	m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 450.0f, 0.0f), D3DXVECTOR3(1600.0f, 900.0f, 0.0f)));
	m_pScene2DList[TEX_BG]->SetVtxCol(D3DXCOLOR(0.3f, 0.3f, 0.3f, 0.8f));
	m_pScene2DList[TEX_BG]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_TITLE_BG));

	m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 150.0, 0.0f), D3DXVECTOR3(750.0f, 150.0f, 0.0f)));
	m_pScene2DList[TEX_LOGO]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_PAUSE_LOGO));

	//ポーズメニューの生成
	m_pMenu = CMenu::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 500.0f, 0.0f), D3DXVECTOR3(500.0f, 100.0f, 0.0f),
							CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_PAUSE_MENU), D3DXVECTOR2(1, 4),CMenu::MENU_VERTICAL);


	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CPause::Uninit()
{
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CPause::Update()
{
	//オプション開いているかどうか
	//nullcheck
	if (m_pOption)
	{
		//更新
		m_pOption->Update();

		//キャンセルボタン
		if (CHossoLibrary::CheckCancel())
		{
			//オプション開放
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
					//更新処理
					m_pScene2DList[nCnt]->Update();
				}
			}
		}

		//ポーズ中はsceneも止まるのでここで処理
		m_pMenu->MenuSelect();
		m_pMenu->Update();


		//決定ボタン押されたとき
		if (CHossoLibrary::CheckDecision())
		{
			//今選んでいる番号で処理変更
			switch (m_pMenu->GetSelectNum())
			{
			case 0:
				//ゲームに戻る
				CManager::GetGame()->SetGamestate(CGame::STATE_NORMAL);
				break;
			case 1:
				//ゲームリスタート
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
				break;
			case 2:
				//オプションを開く
				m_pOption = COption::Create();
				break;
			case 3:
				//タイトルに戻る
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
				break;
			default:
				//ゲームに戻る
				CManager::GetGame()->SetGamestate(CGame::STATE_NORMAL);
				break;
			}
		}
	}
}
//------------------------------------------------------------------------------
//描画処理
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
				//描画
				m_pScene2DList[nCnt]->Draw();
			}
		}
	}
	//ポーズ中はsceneも止まるのでここで処理
	m_pMenu->Draw();

	//nullcheck
	if (m_pOption)
	{
		//描画
		m_pOption->Draw();
	}
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CPause::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
std::shared_ptr<CPause> CPause::Create()
{
	//変数宣言
	std::shared_ptr<CPause> pPause(new CPause);

	//初期化
	pPause->Init();

	//Sceneに追加
	pPause->SetObjType(CScene::OBJTYPE_PAUSE);
	pPause->AddSharedList(pPause);

	//生成した情報
	return pPause;
}

//------------------------------------------------------------------------------
//オプション開いているかどうか
//------------------------------------------------------------------------------
bool CPause::GetOptionWindow()
{
	if (m_pOption)
	{
		return true;
	}
	return false;
}
