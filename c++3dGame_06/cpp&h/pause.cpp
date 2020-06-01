// ----------------------------------------
//
// pause処理の説明[pause.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
/* 描画 */
#include "pause.h"
#include "keyboard.h"
#include "fade.h"
#include "game.h"
#include "manager.h"
#include "title.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CPause::m_pTex = {};
D3DXVECTOR3 CPause::m_pos = {};
D3DXVECTOR2 CPause::m_size = {};
bool CPause::m_bPause = false;
// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CPause::CPause() : CScene::CScene(ACTOR_PAUSE_UI, LAYER_UI)
{
	m_aScene_Two = NULL;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CPause::~CPause()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CPause::Init(void)
{
	m_aScene_Two = new CScene_TWO;
	m_aScene_Two->SetSize(m_size);
	m_aScene_Two->Init();
	m_aScene_Two->SetPosition(m_pos);
	m_aScene_Two->BindTexture(m_pTex);
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CPause::Uninit(void)
{
	if (m_aScene_Two != NULL)
	{
		m_aScene_Two->Uninit();
		delete m_aScene_Two;
		m_aScene_Two = NULL;
	}
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CPause::Update(void)
{
	if (m_aScene_Two != NULL)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE && CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_FREE)
		{
			m_aScene_Two->Update();
		}
	}
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CPause::Draw(void)
{
	// NULLチェック
	if (m_aScene_Two != NULL)
	{
		// ポーズ状態じゃないとき
		if (m_bPause == false)
		{
			// タイトルモードだったら
			if (CManager::GetMode() == CManager::MODE_TITLE && CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_FREE)
			{
				m_aScene_Two->Draw();
			}
			//// ゲームモードだったら
			else if (CManager::GetMode() == CManager::MODE_GAME)
			{
				m_aScene_Two->Draw();
			}
		}
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CPause::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// テクスチャー情報代入
	char TexData[72] =
	{
		"data/TEXTURE/PAUSE/Pause_ui.png",
	};
	// 位置情報代入
	D3DXVECTOR3 pos =
	{
		D3DXVECTOR3(1100.0f,600,0.0f),
	};
	// サイズ情報代入
	D3DXVECTOR2 size =
	{
		D3DXVECTOR2(200.0f,30.0f),
	};

	// テクスチャーがあったら
	if (strcmp(TexData, "") != 0)
	{
		/* テクスチャーのロード */
		D3DXCreateTextureFromFile(pDevice, TexData, &m_pTex);
		/* 位置・サイズの タイプのロード */
		m_pos = pos;
		m_size = size;
	}

	return S_OK;
}

// ----------------------------------------
// 読み込んだ情報を破棄
// ----------------------------------------
void CPause::UnLoad(void)
{
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}


// ----------------------------------------
// 作成処理
// ----------------------------------------
CPause * CPause::Create(void)
{
	// 変数宣言
	CPause * pPause;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pPause = new CPause();
	// 初期化処理
	pPause->Init();
	// 生成したオブジェクトを返す
	return pPause;
}

// ------------------------------------------
// 状態設定
// ------------------------------------------
void CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
}

// ------------------------------------------
// 状態取得
// ------------------------------------------
bool CPause::GetPause(void)
{
	return m_bPause;
}