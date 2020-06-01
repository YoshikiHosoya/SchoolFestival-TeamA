// ----------------------------------------
//
// マップ処理の説明[map.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "map.h"
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
LPDIRECT3DTEXTURE9 CMap::m_pTex[MAP_UI_MAX] = {};
D3DXVECTOR3 CMap::m_pos[MAP_UI_MAX] = {};
D3DXVECTOR2 CMap::m_size[MAP_UI_MAX] = {};
CMap::MAP_UI_TYPE CMap::m_type[MAP_UI_MAX] = {};
// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CMap::CMap() : CScene::CScene(ACTOR_MAP, LAYER_UI)
{
	// 初期化
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CMap::~CMap()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CMap::Init(void)
{
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
		m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);
	}

	CMapMark::Create();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CMap::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
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
void CMap::Update(void)
{
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// 種類によって処理を変える
			m_aScene_Two[nCnt]->Update();
		}
	}
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CMap::Draw(void)
{
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
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
HRESULT CMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();

	// テクスチャー情報代入
	char TexData[MAP_UI_MAX][72] =
	{
		"data/TEXTURE/MAP/Map000.png",
		"data/TEXTURE/MAP/Frame.png",
		"data/TEXTURE/MAP/Map_Mission00.png",
	};
	// 位置情報代入
	D3DXVECTOR3 pos[MAP_UI_MAX] =
	{
		D3DXVECTOR3(1100.0f,180,0.0f),
		D3DXVECTOR3(1100.0f,350.0f,0.0f),
		D3DXVECTOR3(1100.0f,350.0f,0.0f),
	};
	// サイズ情報代入
	D3DXVECTOR2 size[MAP_UI_MAX] =
	{
		D3DXVECTOR2(248.8f,260.8f),
		D3DXVECTOR2(250.0f,50.0f),
		D3DXVECTOR2(250.0f,30.0f),
	};
	//
	MAP_UI_TYPE type[MAP_UI_MAX] =
	{
		MAP_UI_MAP,
		MAP_UI_FRAME,
		MAP_UI_MISSION00,
	};

	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
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
void CMap::UnLoad(void)
{
	// テクスチャの開放
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
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
CMap * CMap::Create(void)
{
	// 変数宣言
	CMap * pMap;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pMap = new CMap();
	// 初期化処理
	pMap->Init();
	// 生成したオブジェクトを返す
	return pMap;
}
