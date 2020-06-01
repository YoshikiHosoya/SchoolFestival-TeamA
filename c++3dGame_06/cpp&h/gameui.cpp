// ----------------------------------------
//
// ポーズ用ui処理の説明[tutorial_ui.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
/* 描画 */
#include "gameui.h"
#include "player.h"
#include "key.h"
#include "mapmark.h"
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
LPDIRECT3DTEXTURE9	CGame_ui::m_pTex[MAX_GAME_UI_TEX] = {};
D3DXVECTOR3			CGame_ui::m_pos[MAX_GAME_UI]  = {};
D3DXVECTOR2			CGame_ui::m_size[MAX_GAME_UI] = {};
bool				CGame_ui::m_bUse[MAX_GAME_UI] = {};
int					CGame_ui::m_nAP = 0;
// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CGame_ui::CGame_ui() : CScene::CScene(ACTOR_GAME_UI, LAYER_UI)
{
	// 初期化
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
	m_fMult = 1.0f;
	m_fAdd = 0.001f;
	m_nCntCol = 0;
	m_nSelect = 0;
	m_fAnim = 0;
	//m_nAP = 0;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CGame_ui::~CGame_ui()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CGame_ui::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		if (nCnt == GAME_UI_KEY0 || nCnt == GAME_UI_KEY1 || nCnt == GAME_UI_KEY2)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[0]);
		}
		else if (nCnt == GAME_UI_LOCK0 || nCnt == GAME_UI_LOCK1 || nCnt == GAME_UI_LOCK2)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[1]);
		}
		else if (nCnt == GAME_UI_ACTIONBUTTON)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[2]);
		}
		else if (nCnt == GAME_UI_MISSION0)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[3]);
		}
		else if (nCnt == GAME_UI_MISSION1)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[4]);
		}
		else if (nCnt == GAME_UI_MAP)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[5]);
		}

		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
	}

	CMapMark::Create();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CGame_ui::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
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
void CGame_ui::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// 種類によって処理を変える
			m_aScene_Two[nCnt]->Update();
		}
	}

	// 種類によって処理を変える
	Various();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CGame_ui::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// 描画条件
			ConditionalDraw(nCnt);
		}
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CGame_ui::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// テクスチャー情報代入
	char TexData[MAX_GAME_UI_TEX][72] =
	{
		"data/TEXTURE/GAME/key.png",
		"data/TEXTURE/GAME/lock.png",
		"data/TEXTURE/GAME/ActionButton000.png",
		"data/TEXTURE/GAME/Mission000.png",
		"data/TEXTURE/GAME/Mission001.png",
		"data/TEXTURE/GAME/Map000.png",
	};
	// 位置情報代入
	D3DXVECTOR3 pos[MAX_GAME_UI] =
	{
		D3DXVECTOR3(1040.0f,450,0.0f),
		D3DXVECTOR3(1120.0f,450,0.0f),
		D3DXVECTOR3(1200.0f,450,0.0f),
		D3DXVECTOR3(1040.0f,450,0.0f),
		D3DXVECTOR3(1120.0f,450,0.0f),
		D3DXVECTOR3(1200.0f,450,0.0f),
		D3DXVECTOR3(640.0f,650.0f,0.0f),
		D3DXVECTOR3(1100.0f,350.0f,0.0f),
		D3DXVECTOR3(1100.0f,350.0f,0.0f),
		D3DXVECTOR3(1100.0f,180,0.0f),
	};
	// サイズ情報代入
	D3DXVECTOR2 size[MAX_GAME_UI] =
	{
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(ACTIONBUTTON_SIZE_X,ACTIONBUTTON_SIZE_Y),
		D3DXVECTOR2(250.0f,30.0f),
		D3DXVECTOR2(250.0f,30.0f),
		D3DXVECTOR2(248.8f,260.8f),
	};

	// 初期描画フラグ代入
	bool flag[MAX_GAME_UI] =
	{
		false,
		false,
		false,
		true,
		true,
		true,
		false,
		true,
		false,
		true,
	};


	for (int nTexCnt = 0; nTexCnt < MAX_GAME_UI_TEX; nTexCnt++)
	{
		/* テクスチャーのロード */
		D3DXCreateTextureFromFile(pDevice, TexData[nTexCnt], &m_pTex[nTexCnt]);
	}
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		/* 位置・サイズのロード */
		m_pos[nCnt]  = pos[nCnt];
		m_size[nCnt] = size[nCnt];
		m_bUse[nCnt] = flag[nCnt];
	}
	return S_OK;
}

// ----------------------------------------
// 読み込んだ情報を破棄
// ----------------------------------------
void CGame_ui::UnLoad(void)
{
	// テクスチャの開放
	for (int nCnt = 0; nCnt < MAX_GAME_UI_TEX; nCnt++)
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
CGame_ui * CGame_ui::Create(void)
{
	// 変数宣言
	CGame_ui * pGame_ui;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pGame_ui = new CGame_ui();
	// 初期化処理
	pGame_ui->Init();
	// 生成したオブジェクトを返す
	return pGame_ui;
}

// ----------------------------------------
// 描画するための条件
// ----------------------------------------
void CGame_ui::ConditionalDraw(int nCnt)
{
	if (m_bUse[nCnt] == true)
	{
		// 種類によって処理を変える
		m_aScene_Two[nCnt]->Draw();
	}
}

// ----------------------------------------
// 描画フラグを変更する処理
// ----------------------------------------
void CGame_ui::SetDrawFlag(int nCnt)
{
	m_bUse[nCnt] = false;
}

// ----------------------------------------
// 種類別の処理
// ----------------------------------------
void CGame_ui::Various()
{
	for (int nCntAP = 0; nCntAP < 3; nCntAP++)
	{
		if (m_nAP >= ABILITYPOINT * (nCntAP + 1))
		{
			m_bUse[nCntAP] = true;
			m_bUse[nCntAP + 3] = false;
		}
		else if (m_nAP <= ABILITYPOINT * (nCntAP + 1))
		{
			m_bUse[nCntAP] = false;
			m_bUse[nCntAP + 3] = true;
		}
	}

	// 鍵を取得したら
	if (CKey::bGetFlag())
	{
		m_bUse[GAME_UI_MISSION0] = false;
		m_bUse[GAME_UI_MISSION1] = true;
	}

	CPlayer *pPlayer = NULL;	// プレイヤー
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}
	if (m_bUse[0] == true && pPlayer->GetAbilityFlag() != true)
	{
		m_bUse[GAME_UI_ACTIONBUTTON] = true;
	}
	else if (m_bUse[0] == false || pPlayer->GetAbilityFlag() == true)
	{
		m_bUse[GAME_UI_ACTIONBUTTON] = false;
	}

}

// ----------------------------------------
// APの計算
// ----------------------------------------
void CGame_ui::SetAP(int number)
{
	if (m_nAP < (ABILITYPOINT*3))
	{
		m_nAP += number;
	}
}

// ----------------------------------------
// フラグの取得
// ----------------------------------------
bool CGame_ui::GetbUse(void)
{
	return m_bUse[0];
}
