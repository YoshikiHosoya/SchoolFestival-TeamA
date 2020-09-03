// =====================================================================================================================================================================
//
// チュートリアルuiの処理 [tutorialui.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "UIManager.h"
#include "tutorialUI.h"
#include "tutorialmanager.h"
#include "scene2D.h"
#include "debugproc.h"
// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define _CRT_SECURE_NO_WARNINGS // 警告除去

// テクスチャの種類
#define TUTORIAL_UI_TEXTURE		(TUTORIAL_UI)

// UIの座標
#define TUTORIAL_UI_NAME_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,80.0f,0.0f))
#define TUTORIAL_UI_ORDER_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,200.0f,0.0f))

// UIの大きさ
#define TUTORIAL_UI_NAME_SIZE	(D3DXVECTOR3(SCREEN_WIDTH * 0.45f,50.0f,0.0f))
#define TUTORIAL_UI_ORDER_SIZE	(D3DXVECTOR3(SCREEN_WIDTH * 0.4f,50.0f,0.0f))

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9		CTutorialUI::m_TexNum[UI_MAX] = {};					// バインドするテクスチャの情報

D3DXVECTOR3				CTutorialUI::m_Pos[UI_MAX] = {
	TUTORIAL_UI_NAME_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
};

D3DXVECTOR3				CTutorialUI::m_Size[UI_MAX] = {
	TUTORIAL_UI_NAME_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
};

// =====================================================================================================================================================================
// コンストラクタ
// =====================================================================================================================================================================
CTutorialUI::CTutorialUI()
{
	// 初期化
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = nullptr;
	}

	m_nColCnt = 0;
}

// =====================================================================================================================================================================
// デストラクタ
// =====================================================================================================================================================================
CTutorialUI::~CTutorialUI()
{
}

// =====================================================================================================================================================================
// 初期化
// =====================================================================================================================================================================
HRESULT CTutorialUI::Init(void)
{
	// テクスチャの取得
	for (int nCntNum = 0 ,nCnt = CTexture::TEX_UI_TUTORIAL_NAME; nCntNum < UI_MAX; nCntNum++,nCnt++)
	{
		m_TexNum[nCntNum] = CTexture::GetTexture((CTexture::TEX_TYPE)nCnt);	// バインドするテクスチャの情報
	}

	// UIの生成
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			// シーン2Dの生成
			m_apScene2D[nCnt] = CScene2D::Create(m_Pos[nCnt], m_Size[nCnt]);
			// テクスチャの割り当て
			m_apScene2D[nCnt]->BindTexture(m_TexNum[nCnt]);

			if (nCnt != UI_NAME)
			{
				m_apScene2D[nCnt]->SetDisp(false);
			}
		}
	}

	return S_OK;
}

// =====================================================================================================================================================================
// 終了
// =====================================================================================================================================================================
void CTutorialUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 終了
			m_apScene2D[nCnt]->Uninit();
			delete m_apScene2D[nCnt];
			m_apScene2D[nCnt] = nullptr;

			// デリートフラグを有効にする
			SetDeleteFlag(true);
		}
	}
}

// =====================================================================================================================================================================
// 更新
// =====================================================================================================================================================================
void CTutorialUI::Update(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			if (m_apScene2D[nCnt]->GetDisp())
			{
				// 更新
				m_apScene2D[nCnt]->Update();
			}

			CDebugProc::Print_Left("TutorialUI %d,%d\n", m_apScene2D[nCnt]->GetDisp(), nCnt);
		}
	}
}

// =====================================================================================================================================================================
// 描画処理
// =====================================================================================================================================================================
void CTutorialUI::Draw(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// 描画
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// チュートリアルUIの生成
//
// =====================================================================================================================================================================
CTutorialUI * CTutorialUI::Create()
{
	//メモリの確保
	CTutorialUI *pTutorialUI = new CTutorialUI();

	// 初期化
	pTutorialUI->Init();

	//オブジェタイプ設定してSceneに所有権を渡す
	CUIManager::AddUIList(std::move(pTutorialUI));

	return pTutorialUI;
}

// =====================================================================================================================================================================
//
// 選択したuiを描画し1個目のuiを非表示にする
//
// =====================================================================================================================================================================
void CTutorialUI::SetDrawDisp(TUTORIAL_UI ui)
{
	// 最初の1回目は何も非表示にしない
	if (ui == UI_ORDERFIRST)
	{
		// 引数の番号のuiを表示させる
		if (m_apScene2D[ui])
		{
			m_apScene2D[ui]->SetDisp(true);
		}
	}
	else
	{
		// nullじゃなかった時
		if (m_apScene2D[ui - 1])
		{
			// 1ステート前に使っていたuiを非表示にする
			m_apScene2D[ui - 1]->SetDisp(false);

			// 引数の番号のuiを表示させる
			if (m_apScene2D[ui])
			{
				m_apScene2D[ui]->SetDisp(true);
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 今使われているuiの種類の取得
//
// =====================================================================================================================================================================
CTutorialUI::TUTORIAL_UI CTutorialUI::GetTutorialUiType()
{
	int nFlaseCnt = 0;
	for (int nCnt = UI_ORDERFIRST,nCntArray = UI_ORDERFINAL; nCnt < TUTORIAL_UI::UI_MAX; nCnt++, nCntArray--)
	{
		if (m_apScene2D[nCntArray]->GetDisp() == true)
		{
			// 描画されているuiの番号を列挙型に変換し変数に代入
			return m_TutorialUiType = static_cast<TUTORIAL_UI>(nCntArray+1);
		}

		// 配列の値全てがfalseだった時1番目をtrueにする
		else if (m_apScene2D[nCnt]->GetDisp() == false)
		{
			nFlaseCnt++;
		}
	}

	if (nFlaseCnt >= UI_ORDERFINAL)
	{
		// 一番最初だけはすべてfalseなので一番目のuiの番号を代入
		return m_TutorialUiType = static_cast<TUTORIAL_UI>(UI_ORDERFIRST);
	}

	return m_TutorialUiType;
}

// =====================================================================================================================================================================
//
// 点滅処理
//
// =====================================================================================================================================================================
void CTutorialUI::Flashing(CScene2D *m_apScene2D)
{
	// カウント加算
	m_nColCnt++;
	// 余りが0の時透明にする
	if (m_nColCnt % 60 == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// 余りが0の時通常状態にする
	else if (m_nColCnt % 30 == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
