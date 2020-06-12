// =====================================================================================================================================================================
//
// ランキングUIの処理[rankbg.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "rankingUI.h"
#include "ranking.h"
#include "renderer.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CRankingUI::m_apTexture[RANKINGUITYPE::RK_UI_MAX] = {};			// 先頭は型名

// =====================================================================================================================================================================
//
// マクロ定義
//
// =====================================================================================================================================================================
#define TEXTURE_FILE01			"data/TEXTURE/rank_1.png"		// 読み込むテクスチャファイル名		( 1位 )
#define TEXTURE_FILE02			"data/TEXTURE/rank_2.png"		// 読み込むテクスチャファイル名		( 2位 )
#define TEXTURE_FILE03			"data/TEXTURE/rank_3.png"		// 読み込むテクスチャファイル名		( 3位 )
#define TEXTURE_FILE04			"data/TEXTURE/rank_4.png"		// 読み込むテクスチャファイル名		( 4位 )
#define TEXTURE_FILE05			"data/TEXTURE/rank_5.png"		// 読み込むテクスチャファイル名		( 5位 )
#define TEXTURE_FILE06			"data/TEXTURE/rank.png"			// 読み込むテクスチャファイル名		( ランキング )
#define TEXTURE_FILE07			"data/TEXTURE/gototitle.png"	// 読み込むテクスチャファイル名		( Enter )

#define BG_SIZEX				(SCREEN_WIDTH / 2)				// 背景の幅
#define BG_SIZEY				(SCREEN_HEIGHT / 2)				// 背景の高さ

#define RANKING_SIZEX			(600 / 2)						// ランキングの幅
#define RANKING_SIZEY			(80 / 2)						// ランキングの高さ

#define ENTER_SIZEX				(300 / 2)						// Enterの幅
#define ENTER_SIZEY				(80 / 2)						// Enterの高さ

#define RANK_NUM_POSX			(380.0f)						// ランキングの順位の位置X
#define RANK_NUM_POSY			(180.0f)						// ランキングの順位の位置Y
#define RANK_NUM_SIZEX			(80 / 2)						// ランキングの順位の幅
#define RANK_NUM_SIZEY			(80 / 2)						// ランキングの順位の高さ
#define RANK_NUM_SPACE			(90.0f)							// ランキングの順位の間	

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CRankingUI::CRankingUI() :CScene2D(PRIORITY_UI)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CRankingUI::~CRankingUI()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CRankingUI::Init()
{
	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			// 変数初期化
			m_UV[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 移動

			// シーン2Dの生成
			m_apScene2D[nCnt] = CScene2D::Create();

			// テクスチャの割り当て
			m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);

			// 初期化
			m_apScene2D[nCnt]->Init();

			switch (nCnt)
			{
			case RANKINGUITYPE::RK_UI_RANK_1:
				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANK_2:
				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANK_3:
				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANK_4:
				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANK_5:
				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANKING:

				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(BG_SIZEX, 70.0f, 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANKING_SIZEX, RANKING_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_ENTER:

				//位置の設定
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(BG_SIZEX, 650.0f, 0.0f));
				// サイズの設定
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(ENTER_SIZEX, ENTER_SIZEY, 0.0f));
				break;
			}
		}
	}
}

// ================================================================================================================================================================================
//
// 終了処理
//
// ================================================================================================================================================================================
void CRankingUI::Uninit()
{
	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
		}
	}
}

// ================================================================================================================================================================================
//
// 更新処理
//
// ================================================================================================================================================================================
void CRankingUI::Update()
{
	// 変数
	D3DXVECTOR3 pos;

	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		// 更新
		m_apScene2D[nCnt]->Update();
	}
}

// ================================================================================================================================================================================
//
// 描画処理
//
// ================================================================================================================================================================================
void CRankingUI::Draw()
{
	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// ランキングUIの生成
//
// =====================================================================================================================================================================
CRankingUI * CRankingUI::Create()
{
	// 変数
	CRankingUI *pRankingUI;

	// メモリの確保
	pRankingUI = new CRankingUI();

	// 初期化
	pRankingUI->Init();

	return pRankingUI;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CRankingUI::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE01, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE02, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE03, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE04, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE05, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE06, &m_apTexture[RANKINGUITYPE::RK_UI_RANKING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE07, &m_apTexture[RANKINGUITYPE::RK_UI_ENTER]);

	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		// エラーチェック
		if (m_apTexture[nCnt] == NULL)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

// =====================================================================================================================================================================
//
// アンロード
//
// =====================================================================================================================================================================
void CRankingUI::Unload(void)
{
	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		// テクスチャの開放
		if (m_apTexture[nCnt])
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

