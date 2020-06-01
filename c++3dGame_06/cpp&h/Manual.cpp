// ----------------------------------------
//
// マニュアル処理の説明[manual.h]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
/* 描画 */
#include "manual.h"
#include "input.h"
#include "pause.h"
#include "manager.h"
#include "fade.h"
#include "debugproc.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define TUTORIAL_UI_ANIM (3)
#define TUTORIAL_UI_SPLIT (1.0f / TUTORIAL_UI_ANIM)

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
LPDIRECT3DTEXTURE9	CManual::m_pTex[MANUAL_TYPE_MAX] = {};
D3DXVECTOR3			CManual::m_pos[MANUAL_TYPE_MAX] = {};
D3DXVECTOR2			CManual::m_size[MANUAL_TYPE_MAX] = {};

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CManual::CManual() : CScene::CScene(ACTOR_MANUAL_UI, LAYER_UI)
{
	// 初期化
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
	m_fMult = 1.0f;
	m_fAdd = 0.001f;
	m_nCntCol = 0;
	m_nSelect = 0;
	m_fAnim = 0;
	m_ManualState = MANUAL_STATE_PAUSE;
	m_ManualSelect = MANUAL_SELECT_PAGE_CONTROLLER;
	m_nPauseCount = MANUAL_TYPE_MANUAL;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CManual::~CManual()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CManual::Init(void)
{
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
		if (nCnt == MANUAL_TYPE_PICTURE)
		{
			m_aScene_Two[MANUAL_TYPE_PICTURE]->SetTex(D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f), D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
		}
		m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);
	}
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CManual::Uninit(void)
{
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
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
void CManual::Update(void)
{
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			if (CPause::GetPause() == true)
			{


				// 種類によって処理を変える
				m_aScene_Two[nCnt]->Update();
			}
		}
	}

	// 種類によって処理を変える
	Various(0);

	CDebugproc::Print("ポーズ中の選択 %d\n" ,m_nPauseCount);
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CManual::Draw(void)
{
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			m_aScene_Two[MANUAL_TYPE_BG]->Draw();
			m_aScene_Two[MANUAL_TYPE_PAUSEUI]->Draw();
			m_aScene_Two[MANUAL_TYPE_CROSSBUTTON]->Draw();
			m_aScene_Two[MANUAL_TYPE_ABUTTON]->Draw();

			if (m_ManualState == MANUAL_STATE_PAUSE)
			{
				m_aScene_Two[MANUAL_TYPE_MANUAL]->Draw();
				m_aScene_Two[MANUAL_TYPE_RESUME]->Draw();
				m_aScene_Two[MANUAL_TYPE_GOTITLE]->Draw();
			}

			else if (m_ManualState = MANUAL_STATE_MANUAL)
			{
				m_aScene_Two[MANUAL_TYPE_PAUSE]->Draw();
				m_aScene_Two[MANUAL_TYPE_PICTURE]->Draw();
			}
		}
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CManual::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// テクスチャー情報代入
	char TexData[MANUAL_TYPE_MAX][72] =
	{
		"data/TEXTURE/MANUAL/BG00.png",
		"data/TEXTURE/MANUAL/PAUSE00.png",
		"data/TEXTURE/MANUAL/BACK00.png",
		"data/TEXTURE/MANUAL/MANUAL00.png",
		"data/TEXTURE/MANUAL/RESUME00.png",
		"data/TEXTURE/MANUAL/TITLE00.png",
		"data/TEXTURE/MANUAL/PICTURE000.png",
		"data/TEXTURE/MANUAL/CROSSBUTTON00.png",
		"data/TEXTURE/MANUAL/ABUTTON00.png",

	};
	// 位置情報代入
	D3DXVECTOR3 pos[MANUAL_TYPE_MAX] =
	{
		D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,200.0f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,300,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,300,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,400,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,500,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,400,0.0f),
		D3DXVECTOR3(380.0f,550,0.0f),
		D3DXVECTOR3(900.0f,550,0.0f),
	};
	// サイズ情報代入
	D3DXVECTOR2 size[MANUAL_TYPE_MAX] =
	{
		D3DXVECTOR2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 1.5),
		D3DXVECTOR2(400.0f,100.0f),
		D3DXVECTOR2(200.0f, 50.0f),
		D3DXVECTOR2(200.0f, 50.0f),
		D3DXVECTOR2(200.0f, 50.0f),
		D3DXVECTOR2(200.0f, 50.0f),
		D3DXVECTOR2(400.0f,300.0f),
		D3DXVECTOR2(50.0f,50.0f),
		D3DXVECTOR2(50.0f,50.0f),
	};

	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
	{
		// テクスチャーがあったら
		if (strcmp(TexData[nCnt], "") != 0)
		{
			/* テクスチャーのロード */
			D3DXCreateTextureFromFile(pDevice, TexData[nCnt], &m_pTex[nCnt]);
			/* 位置・サイズのロード */
			m_pos[nCnt] = pos[nCnt];
			m_size[nCnt] = size[nCnt];
		}
	}
	return S_OK;
}

// ----------------------------------------
// 読み込んだ情報を破棄
// ----------------------------------------
void CManual::UnLoad(void)
{
	// テクスチャの開放
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
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
CManual * CManual::Create(void)
{
	// 変数宣言
	CManual * pTutorial_ui;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pTutorial_ui = new CManual();
	// 初期化処理
	pTutorial_ui->Init();
	// 生成したオブジェクトを返す
	return pTutorial_ui;
}

// ----------------------------------------
// 種類別の処理
// ----------------------------------------
void CManual::Various(int nCnt)
{
	//
	if (m_ManualState == MANUAL_STATE_PAUSE)
	{
		// 下を押したとき選択している状態を一つのものにする
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_DOWN))
		{
			m_nPauseCount++;

			if (m_nPauseCount > MANUAL_TYPE_GOTITLE)
			{
				m_nPauseCount = MANUAL_TYPE_MANUAL;
			}
		}
		// 下を押したとき選択している状態を一つのものにする
		else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_UP))
		{
			m_nPauseCount--;

			if (m_nPauseCount < MANUAL_TYPE_MANUAL)
			{
				m_nPauseCount = MANUAL_TYPE_GOTITLE;
			}
		}

		// 選択されているUIを拡大する
		m_aScene_Two[m_nPauseCount]->SetSize(D3DXVECTOR2(300.0f, 100.0f));

		// 選ばれていないUIは元の大きさに戻す
		if (m_nPauseCount != MANUAL_TYPE_MANUAL)
		{
			m_aScene_Two[MANUAL_TYPE_MANUAL]->SetSize(D3DXVECTOR2(200.0f, 50.0f));
		}
		if (m_nPauseCount != MANUAL_TYPE_RESUME)
		{
			m_aScene_Two[MANUAL_TYPE_RESUME]->SetSize(D3DXVECTOR2(200.0f, 50.0f));
		}
		if (m_nPauseCount != MANUAL_TYPE_GOTITLE)
		{
			m_aScene_Two[MANUAL_TYPE_GOTITLE]->SetSize(D3DXVECTOR2(200.0f, 50.0f));
		}


		// 決定キーを押したとき
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
		{
			if (m_nPauseCount == MANUAL_TYPE_MANUAL)
			{
				m_ManualState = MANUAL_STATE_MANUAL;
			}
			else if (m_nPauseCount == MANUAL_TYPE_RESUME)
			{
				CPause::SetPause(false);
			}
			else if (m_nPauseCount == MANUAL_TYPE_GOTITLE)
			{
				CPause::SetPause(false);
				if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
				{
					CManager::GetFade()->SetFade(CManager::MODE_TITLE);
				}
			}
		}
	}

	//
	else if (m_ManualState == MANUAL_STATE_MANUAL)
	{
		// 決定キーを押したとき
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
		{
			m_ManualState = MANUAL_STATE_PAUSE;
		}

		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RIGHT))
		{
			m_nSelect++;
			// 次のページへ
			if(m_nSelect > MANUAL_SELECT_PAGE_ABILITY)
			{
				m_nSelect = MANUAL_SELECT_PAGE_ABILITY;
			}
			else
			{
				m_aScene_Two[MANUAL_TYPE_PICTURE]->SetTex(
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f),
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
			}
		}

		//
		else if(CManager::GetKeyboard()->GetKeyboardTrigger(DIK_LEFT))
		{
			m_nSelect--;
			// 次のページへ
			if (m_nSelect < MANUAL_SELECT_PAGE_CONTROLLER)
			{
				m_nSelect = MANUAL_SELECT_PAGE_CONTROLLER;
			}
			else
			{
				m_aScene_Two[MANUAL_TYPE_PICTURE]->SetTex(
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f),
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
			}
		}
	}

	// ボタン
	if (m_aScene_Two[MANUAL_TYPE_CROSSBUTTON] || m_aScene_Two[MANUAL_TYPE_ABUTTON])
	{
		// カウントカラーアップ
		m_nCntCol++;
		// 表示状態へ
		if (m_nCntCol % 80 == 0)
		{
			m_aScene_Two[MANUAL_TYPE_CROSSBUTTON]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_aScene_Two[MANUAL_TYPE_ABUTTON]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		// 非表示状態へ
		else if (m_nCntCol % 40 == 0)
		{
			m_aScene_Two[MANUAL_TYPE_CROSSBUTTON]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_aScene_Two[MANUAL_TYPE_ABUTTON]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	//	//ジョイスティック 十字キー
	//	if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_RIGHT))
	//	{
	//	}
	//	else if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_LEFT))
	//	{
	//	}
}
