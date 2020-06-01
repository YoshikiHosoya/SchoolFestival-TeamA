// ----------------------------------------
//
// ワープゲート処理の説明[warp.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "warp.h"
#include "player.h"
#include "fade.h"
#include "debugproc.h"
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
LPDIRECT3DTEXTURE9 CWarp::m_pTexture[TYPE_MAX] = {};		// テクスチャへのポインタ
CLoad	*CWarp::m_pload = NULL;								// ロード
int		CWarp::m_nAll = 0;									// 番号

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CWarp::CWarp()
{
	// 変数の初期化
	m_Type = TYPE_ENTRANCE;
}

// ----------------------------------------
// イニシャライザコンストラクタ
// ----------------------------------------
CWarp::CWarp(ACTOR actor, LAYER layer) : CScene_THREE::CScene_THREE(actor, layer)
{
	// 変数の初期化
	m_Type = TYPE_ENTRANCE;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CWarp::~CWarp()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CWarp::Init(void)
{
	// シーン3Dの初期化
	CScene_THREE::Init();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CWarp::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CWarp::Update(void)
{
	// 変数宣言
	CPlayer *pPlayer = NULL;	// プレイヤー
								// 情報取得
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	// アイテムの取得
	if (CCalculation::Collision_Circle(
		GetPos(),					// 自分の位置
		50, 		// 自分の半径
		pPlayer->GetPos(), 			// 相手の位置
		PLAYERCOLLISION_SIZE))		// 相手の半径
	{
		if (m_Type == TYPE_ENTRANCE)
		{
			//pPlayer->SetRotPos(0, 1);
		}
		else if (m_Type == TYPE_EXIT)
		{
			//pPlayer->SetRotPos(1, 0);
		}

		// SEを鳴らす
		//CManager::GetSound()->PlaySound(CSound::LABEL_SE_8);
		//CManager::GetFade()->SetFade(CManager::MODE_GAME);
	}

	CScene_THREE::SetRot(CScene_THREE::GetRot() + D3DXVECTOR3(0.0f, 0.0f, 0.01f));
	CScene_THREE::Update();

	CDebugproc::Print("座標		: %.2f,%.2f,%.2f\n", GetPos().x, GetPos().y, GetPos().z);
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CWarp::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9	pDevice;					// デバイスのポインタ

	pDevice = CManager::GetRenderer()->GetDevice();	// デバイスの取得

													// ライティングモード無効
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Zバッファ　有効　無効
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);

	// レンダーステート(加算合成処理)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// 裏面(左回り)をカリングする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CScene_THREE::Draw();

	//アルファテスト戻す
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//Zバッファ　有効　無効
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	// ライティングモード有効
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// 裏面(左回り)をカリングする
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// レンダーステート(通常ブレンド処理)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

// ----------------------------------------
// テクスチャー設定処理
// ----------------------------------------
void CWarp::SetTexture(TYPE type)
{
	// 設定
	CScene_THREE::BindTexture(m_pTexture[type]);	// テクスチャー
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CWarp * CWarp::Create()
{
	// 変数宣言
	CWarp * pWarp;		// シーン3Dクラス
											// メモリの生成(初め->基本クラス,後->派生クラス)
	pWarp = new CWarp(ACTOR_WARP, LAYER_3DOBJECT);
	// 初期化処理
	pWarp->Init();
	// 生成したオブジェクトを返す
	return pWarp;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void CWarp::LoadCreate(void)
{
	// 変数宣言
	CWarp * pWarp;
	for (int nCntWarp = 0; nCntWarp < m_nAll; nCntWarp++)
	{
		pWarp = CWarp::Create();						// 生成
		pWarp->SetTexture((TYPE)m_pload->GetInfo(nCntWarp).nType);
		pWarp->m_Type = (TYPE)m_pload->GetInfo(nCntWarp).nType;
		pWarp->SetPos(m_pload->GetInfo(nCntWarp).pos);		// 位置
		pWarp->SetRot(m_pload->GetInfo(nCntWarp).rot);		// 回転
		pWarp->SetSize(m_pload->GetInfo(nCntWarp).size);	// サイズ
		pWarp->SetCol(m_pload->GetInfo(nCntWarp).col);
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CWarp::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/Effect/Effect0002.jpg",
		"data/TEXTURE/Effect/Effect0002.jpg",
	};

	// テクスチャー設定
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ロード生成
	m_pload = new CLoad;
	// ロード読み込み
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Warp_Location.txt");

	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CWarp::UnLoad(void)
{
	// テクスチャー設定
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
	// ロードの破棄
	delete m_pload;
	m_pload = NULL;
}

// ----------------------------------------
// ロード取得
// ----------------------------------------
CLoad * CWarp::GetLoad(void)
{
	return m_pload;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CWarp::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CWarp::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CWarp::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void CWarp::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// 表示テクスチャー設定処理
// ----------------------------------------
void CWarp::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
}

// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR3 CWarp::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// 回転の取得処理
// ----------------------------------------
D3DXVECTOR3 CWarp::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CWarp::GetPos(void)
{
	return CScene_THREE::GetPos();
}
