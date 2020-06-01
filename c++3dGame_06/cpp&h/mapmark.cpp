// ----------------------------------------
//
// マップマーク処理の説明[mapmark.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "mapmark.h"
#include "player.h"
#include "renderer.h"
#include "camera.h"
//#include "warp.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
//#define MARK_SIZE (10.0f)
#define MARK_SIZE (8.0f)

//#define MAPMARK_MOVESPEED_MINUS (-0.25f)
//#define MAPMARK_MOVESPEED_PLUS (0.25f)
//#define MAPMARK_MOVESPEED_MINUS (-0.50f)
//#define MAPMARK_MOVESPEED_PLUS (0.50f)
//
//#define MAPMARK_MOVESPEED_MINUS2 (-0.50f)
//#define MAPMARK_MOVESPEED_PLUS2 (0.50f)

#define MAPMARK_MOVESPEED_MINUS (-0.50f)
#define MAPMARK_MOVESPEED_PLUS (0.50f)
#define MAPMARK_MOVESPEED_MINUS2 (-0.50f)
#define MAPMARK_MOVESPEED_PLUS2 (0.50f)

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
D3DXVECTOR3 CMapMark::m_pos[TOTAL_MARK] = {};
D3DXVECTOR2 CMapMark::m_size[MAP_MARK_MAX] = {};
D3DXCOLOR CMapMark::m_col[MAP_MARK_MAX] = {};
CMapMark::MAP_MARK_TYPE CMapMark::m_type[MAP_MARK_MAX] = {};
//D3DXVECTOR3	CMapMark::m_move[TOTAL_MARK] = {};			// 位置情報

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CMapMark::CMapMark() : CScene::CScene(ACTOR_MAPMARK, LAYER_UI)
{
	// 初期化
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	//m_pos[35] = D3DXVECTOR3(1098.0f, 297.0f, 0.0f);	// プレイヤー
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CMapMark::~CMapMark()
{
	m_pos[35] = D3DXVECTOR3(1098.0f, 285.0f, 0.0f);	// プレイヤー
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CMapMark::Init(void)
{
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);

		if (nCnt >= MAX_SHARDMARK)
		{
			m_nCount++;
		}

		if (m_type[MAP_MARK_SHARD] == MAP_MARK_SHARD)
		{
			m_aScene_Two[nCnt]->SetCol(m_col[m_nCount]);
		}
		else if (m_type[MAP_MARK_PLAYER] == MAP_MARK_PLAYER)
		{
			m_aScene_Two[nCnt]->SetCol(m_col[m_nCount]);
		}
		/*else if (m_type[MAP_MARK_ENEMY] == MAP_MARK_ENEMY)
		{
			m_aScene_Two[nCnt]->SetCol(m_col[m_nCount]);
		}*/

		m_aScene_Two[nCnt]->SetSize(m_size[m_nCount]);
	}
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CMapMark::Uninit(void)
{
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			m_aScene_Two[nCnt]->Uninit();
			delete m_aScene_Two[nCnt];
			m_aScene_Two[nCnt] = NULL;
		}
	}
}

int g_nCnt = 0;
// ----------------------------------------
// 更新処理
// ----------------------------------------
void CMapMark::Update(void)
{
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// 種類によって処理を変える
			Various(nCnt);
			// 種類によって処理を変える
			m_aScene_Two[nCnt]->Update();
		}
	}

	//if (g_nCnt <= MAX_SHARDMARK)
	//{
	//	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_0))
	//	{
	//		if (m_aScene_Two[g_nCnt] != NULL)
	//		{
	//			m_aScene_Two[g_nCnt]->Release();
	//			m_aScene_Two[g_nCnt] = NULL;
	//			//m_aScene_Two[g_nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//		}
	//		g_nCnt++;
	//	}
	//}
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CMapMark::Draw(void)
{
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
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
HRESULT CMapMark::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();

	// 位置情報代入
	D3DXVECTOR3 pos[TOTAL_MARK] =
	{
		D3DXVECTOR3(1005.0f,61.5f,0.0f),	// 欠片00〇
		D3DXVECTOR3(1048.0f,61.5f,0.0f),	// 欠片01〇
		D3DXVECTOR3(1151.7f,61.5f,0.0f),	// 欠片02〇
		D3DXVECTOR3(1199.0f,61.5f,0.0f),	// 欠片03〇

		D3DXVECTOR3(992.0f,71.5f,0.0f),		// 欠片04〇
		D3DXVECTOR3(1208.0f,71.5f,0.0f),	// 欠片05〇

		D3DXVECTOR3(1067.5f,89.0f,0.0f),	// 欠片06〇
		D3DXVECTOR3(1133.0f,89.0f,0.0f),	// 欠片07〇

		D3DXVECTOR3(1067.5f,106.5f,0.0f),	// 欠片08〇
		D3DXVECTOR3(1133.0f,106.5f,0.0f),	// 欠片09〇

		D3DXVECTOR3(992.0f,123.0f,0.0f),	// 欠片10〇
		D3DXVECTOR3(1067.5f,123.0f,0.0f),	// 欠片11〇
		D3DXVECTOR3(1208.0f,123.0f,0.0f),	// 欠片12〇

		D3DXVECTOR3(1077.5f,130.0f,0.0f),	// 欠片13〇
		D3DXVECTOR3(1142.0f,130.0f,0.0f),	// 欠片14〇

		D3DXVECTOR3(992.0f,138.0f,0.0f),	// 欠片15〇
		D3DXVECTOR3(1035.0f,138.0f,0.0f),	// 欠片16〇
		D3DXVECTOR3(1165.0f,138.0f,0.0f),	// 欠片17〇

		D3DXVECTOR3(1089.5f,164.0f,0.0f),	// 欠片18〇
		D3DXVECTOR3(1109.5f,164.0f,0.0f),	// 欠片19〇

		D3DXVECTOR3(992.0f,170.0f,0.0f),	// 欠片20〇
		D3DXVECTOR3(1035.0f,170.0f,0.0f),	// 欠片21〇
		D3DXVECTOR3(1077.5f,170.0f,0.0f),	// 欠片22〇
		D3DXVECTOR3(1121.5f,170.0f,0.0f),	// 欠片23〇
		D3DXVECTOR3(1165.0f,170.0f,0.0f),	// 欠片24〇

		D3DXVECTOR3(1002.0f,180.0f,0.0f),	// 欠片25〇
		D3DXVECTOR3(1045.0f,180.0f,0.0f),	// 欠片26〇
		D3DXVECTOR3(1155.0f,180.0f,0.0f),	// 欠片27〇
		D3DXVECTOR3(1195.0f,180.0f,0.0f),	// 欠片28〇

		D3DXVECTOR3(1035.0f,190.0f,0.0f),	// 欠片29〇
		D3DXVECTOR3(1077.5f,190.0f,0.0f),	// 欠片30〇
		D3DXVECTOR3(1121.5f,190.0f,0.0f),	// 欠片31〇
		D3DXVECTOR3(1165.0f,190.0f,0.0f),	// 欠片32〇
		D3DXVECTOR3(1208.0f,190.0f,0.0f),	// 欠片33〇

		D3DXVECTOR3(1089.5f,197.5f,0.0f),	// 欠片34〇
		D3DXVECTOR3(1109.5f,197.5f,0.0f),	// 欠片35〇

		D3DXVECTOR3(1035.0f,222.0f,0.0f),	// 欠片36〇
		D3DXVECTOR3(1165.0f,222.0f,0.0f),	// 欠片37〇
		D3DXVECTOR3(1208.0f,222.0f,0.0f),	// 欠片38〇

		D3DXVECTOR3(1055.0f,230.0f,0.0f),	// 欠片39〇
		D3DXVECTOR3(1121.5f,230.0f,0.0f),	// 欠片40〇

		D3DXVECTOR3(992.0f,240.0f,0.0f),	// 欠片41〇
		D3DXVECTOR3(1133.0f,240.0f,0.0f),	// 欠片42〇
		D3DXVECTOR3(1208.0f,240.0f,0.0f),	// 欠片43〇

		D3DXVECTOR3(1067.5f,255.0f,0.0f),	// 欠片44〇
		D3DXVECTOR3(1133.0f,255.0f,0.0f),	// 欠片45〇

		D3DXVECTOR3(1067.5f,272.0f,0.0f),	// 欠片46〇
		D3DXVECTOR3(1133.0f,272.0f,0.0f),	// 欠片47〇

		D3DXVECTOR3(992.0f,290.0f,0.0f),	// 欠片48〇
		D3DXVECTOR3(1208.0f,290.0f,0.0f),	// 欠片49〇

		D3DXVECTOR3(1005.0f,298.0f,0.0f),	// 欠片50〇
		D3DXVECTOR3(1048.0f,298.0f,0.0f),	// 欠片51〇
		D3DXVECTOR3(1155.0f,298.0f,0.0f),	// 欠片52〇
		D3DXVECTOR3(1198.0f,298.0f,0.0f),	// 欠片53〇

		D3DXVECTOR3(1100.0f,180.0f,0.0f),	// プレイヤー
	};
	// サイズ情報代入
	D3DXVECTOR2 size[MAP_MARK_MAX] =
	{
		D3DXVECTOR2(MARK_SIZE,MARK_SIZE),
		D3DXVECTOR2(MARK_SIZE,MARK_SIZE),
	};
	// 色情報代入
	D3DXCOLOR col[MAP_MARK_MAX] =
	{
		COLOR_PURPLE,
		COLOR_BLUE,
		//COLOR_RED,
	};
	// タイプの代入
	MAP_MARK_TYPE type[MAP_MARK_MAX] =
	{
		MAP_MARK_SHARD,
		MAP_MARK_PLAYER,
	};

	for (int nCnt = 0; nCnt < MAP_MARK_MAX; nCnt++)
	{
		// 大きさ 種類 色
		m_size[nCnt] = size[nCnt];
		m_type[nCnt] = type[nCnt];
		m_col[nCnt] = col[nCnt];
	}

	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		// 位置
		m_pos[nCnt] = pos[nCnt];
	}
	return S_OK;
}

// ----------------------------------------
// 読み込んだ情報を破棄
// ----------------------------------------
void CMapMark::UnLoad(void)
{
}

// ----------------------------------------
// 消えた3Dアイテムと同じIdを持つマーカーを削除する
// ----------------------------------------
void CMapMark::ReleseMaker(int nId)
{
	if (m_aScene_Two[nId] != NULL)
	{
		m_aScene_Two[nId]->Release();
		m_aScene_Two[nId] = NULL;
	}
}

// ----------------------------------------
// 座標の更新
// ----------------------------------------
void CMapMark::SetMapMaker(D3DXVECTOR3 pos)
{
	m_aScene_Two[36]->SetPosition(pos);
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CMapMark * CMapMark::Create(void)
{
	// 変数宣言
	CMapMark * pMapMark;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pMapMark = new CMapMark();
	// 初期化処理
	pMapMark->Init();
	// 生成したオブジェクトを返す
	return pMapMark;
}

// ----------------------------------------
// 種類別の処理
// ----------------------------------------
void CMapMark::Various(int nCnt)
{
	CPlayer *pPlayer = NULL;

	int nValueH = 0;//スティックの横
	int nValueV = 0;//スティックの縦

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	m_move.x = pPlayer->GetMove().x * 0.9f;
	m_move.y = pPlayer->GetMove().z * -0.9f;

	if (m_aScene_Two[nCnt] == m_aScene_Two[TOTAL_MARK-1])
	{
		m_pos[nCnt].x += (m_move.x / 22.0f);
		m_pos[nCnt].y += (m_move.y / 29.0f);
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
	}
}