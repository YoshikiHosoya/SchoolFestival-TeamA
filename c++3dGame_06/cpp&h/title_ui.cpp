// ----------------------------------------
//
// ポーズ用ui処理の説明[title_ui.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
/* 描画 */
#include "title_ui.h"
#include "fade.h"
#include "title.h"

// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------

// ----------------------------------------
//
// グローバル変数
//
// ----------------------------------------

// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CTitle_ui::m_pTex[TITLE_UI_MAX] = {};
D3DXVECTOR3 CTitle_ui::m_pos[TITLE_UI_MAX] = {};
D3DXVECTOR2 CTitle_ui::m_size[TITLE_UI_MAX] = {};
CTitle_ui::TITLE_UI CTitle_ui::m_type[TITLE_UI_MAX] = {};
CSelectMark * CTitle_ui::m_pSelectMark = NULL;
bool CTitle_ui::m_bUse = false;
// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CTitle_ui::CTitle_ui() : CScene::CScene(ACTOR_TITLE_UI, LAYER_UI)
{
	// 初期化
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
	m_fMult = 1.0f;
	m_fAdd = 0.001f;
	m_bCol_a = false;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//m_bUse = false;
	m_Select = TITLESELECT_NEWGAME;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CTitle_ui::~CTitle_ui()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CTitle_ui::Init(void)
{
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
		m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);
	}

	//// 選択してるUIに印を付ける
	//m_pSelectMark = CSelectMark::Create(D3DXVECTOR3(150.0f, 350.0f, 0.0f),
	//	0.0f,
	//	D3DXVECTOR2(125.0f, 30.0f),
	//	D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f),
	//	CSelectMark::MARK_ARROW);
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CTitle_ui::Uninit(void)
{
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			m_aScene_Two[nCnt]->Uninit();
			delete m_aScene_Two[nCnt];
			m_aScene_Two[nCnt] = NULL;
		}
	}
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CTitle_ui::Update(void)
{
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			if (CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_TITLE)
			{
				// 種類によって処理を変える
				Various(nCnt);
			}
			// 種類によって処理を変える
			m_aScene_Two[nCnt]->Update();

			//タイトルモードがチュートリアルになったら
			if (CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_TUTORIAL)
			{
				//透明化
				Transparency(nCnt);
			}

			if (m_bUse == true)
			{
				Release();
			}
		}
	}

	//// 選択マーク効果
	//if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_DOWN))
	//{
	//	if (m_pSelectMark->GetCount() < 2)
	//	{
	//		m_pSelectMark->SetPos(m_pSelectMark->GetPos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	//		m_pSelectMark->CalculationCount(1);
	//	}

	//	else if (m_pSelectMark->GetCount() >= 2)
	//	{
	//		m_pSelectMark->SetPos(D3DXVECTOR3(150.0f, 350.0f, 0.0f));
	//		m_pSelectMark->SetCount(0);
	//	}

	//	// マークを下げる
	//	SetTitleModeDown();
	//}

	//// 選択マーク上昇
	//else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_UP))
	//{
	//	if (m_pSelectMark->GetCount() > -1)
	//	{
	//		m_pSelectMark->SetPos(m_pSelectMark->GetPos() + D3DXVECTOR3(0.0f, -50.0f, 0.0f));
	//		m_pSelectMark->CalculationCount(-1);
	//	}

	//	if (m_pSelectMark->GetCount() <= -1)
	//	{
	//		m_pSelectMark->SetPos(D3DXVECTOR3(150.0f, 450.0f, 0.0f));
	//		m_pSelectMark->SetCount(2);
	//	}

	//	// マークを上げる
	//	SetTitleModeUp();
	//}
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CTitle_ui::Draw(void)
{
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// 種類によって処理を変える
			m_aScene_Two[nCnt]->Draw();
		}
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CTitle_ui::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// テクスチャー情報代入
	char TexData[TITLE_UI_MAX][72] =
	{
		"data/TEXTURE/TITLE/Title00.png",
		"data/TEXTURE/TITLE/newgame.png",
	};
	// 位置情報代入
	D3DXVECTOR3 pos[TITLE_UI_MAX] =
	{
		D3DXVECTOR3(640.0f,150,0.0f),
		D3DXVECTOR3(640.0f,650,0.0f),
	};
	// サイズ情報代入
	D3DXVECTOR2 size[TITLE_UI_MAX] =
	{
		D3DXVECTOR2(700.0f,200.0f),
		D3DXVECTOR2(500.0f,40.0f),
	};
	//
	TITLE_UI type[TITLE_UI_MAX] =
	{
		TITLE_UI_NAME,
		TITLE_UI_NEWGAME,
	};

	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		// テクスチャーがあったら
		if (strcmp(TexData[nCnt], "") != 0)
		{
			/* テクスチャーのロード */
			D3DXCreateTextureFromFile(pDevice, TexData[nCnt], &m_pTex[nCnt]);
			/* 位置・サイズの タイプのロード */
			m_pos[nCnt] = pos[nCnt];
			m_size[nCnt] = size[nCnt];
			m_type[nCnt] = type[nCnt];
		}
	}
	return S_OK;
}

// ----------------------------------------
// 読み込んだ情報を破棄
// ----------------------------------------
void CTitle_ui::UnLoad(void)
{
	// テクスチャの開放
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		if (m_pTex[nCnt] != NULL)
		{
			m_pTex[nCnt]->Release();
			m_pTex[nCnt] = NULL;
		}
	}
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CTitle_ui * CTitle_ui::Create(void)
{
	// 変数宣言
	CTitle_ui * pTitle_ui;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pTitle_ui = new CTitle_ui();
	// 初期化処理
	pTitle_ui->Init();
	// 生成したオブジェクトを返す
	return pTitle_ui;
}

// ----------------------------------------
// 種類別の処理
// ----------------------------------------
void CTitle_ui::Various(int nCnt)
{
	// タイトルの名前の場合
	if (nCnt == TITLE_UI_NAME)
	{
		D3DXVECTOR2 size = m_size[nCnt];	// サイズの取得
													// 加算か減算
		if (m_fMult >= 1.1f || m_fMult <= 0.9f)
		{
			m_fAdd *= -1;
		}
		// サイズの変化
		m_fMult += m_fAdd;
		size *= m_fMult;

		// サイズの設定
		m_aScene_Two[nCnt]->SetSize(size);
	}

	else if (nCnt == TITLE_UI_NEWGAME)
	{
		if (m_Col.a > 0.1f && m_bCol_a == false)
		{
			m_Col.a -= 0.01f;
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Col.a));
			if (m_Col.a <= 0.1f)
			{
				m_bCol_a = true;
			}
		}
		else if (m_Col.a < 1.0f && m_bCol_a == true)
		{
			m_Col.a += 0.01f;
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Col.a));
			if (m_Col.a >= 1.0f)
			{
				m_bCol_a = false;
			}
		}

		// サイズの設定
		//m_aScene_Two[nCnt]->SetCol(D3DXCOLOR (1.0f, 1.0f, 1.0f, m_fCntCol));
	}
}

// ----------------------------------------
// 透明化処理
// ----------------------------------------
void CTitle_ui::Transparency(int nCnt)
{
	//徐々に透明にする
	m_Col.a -= 0.005f;
	//色の更新
	m_aScene_Two[nCnt]->SetCol(m_Col);

	//透明度が0以下になったら削除
	if (m_Col.a <= 0.0f)
	{
		m_bUse = true;
	}
}

// ----------------------------------------
// フラグの取得
// ----------------------------------------
bool CTitle_ui::GetFlag(void)
{
	return m_bUse;
}

// ----------------------------------------
// モードの選択設定
// ----------------------------------------
void CTitle_ui::SetTitleModeUp(void)
{
	switch (m_Select)
	{
	case TITLESELECT_NEWGAME:
		break;

	default:
		break;
	}
}

// ----------------------------------------
// モードの選択設定
// ----------------------------------------
void CTitle_ui::SetTitleModeDown(void)
{
	switch (m_Select)
	{
	case TITLESELECT_NEWGAME:
	//	m_Select = TITLESELECT_CHAPTERS;
		break;

	default:
		break;
	}
}


// ----------------------------------------
//
// ----------------------------------------
void CTitle_ui::TitleMode(void)
{
	switch (m_Select)
	{
	case TITLESELECT_NEWGAME:

		break;

	default:
		break;
	}
}

// ----------------------------------------
// 選択された情報を取得
// ----------------------------------------
CTitle_ui::TITLESELECT CTitle_ui::GetSelect(void)
{
	return m_Select;
}

