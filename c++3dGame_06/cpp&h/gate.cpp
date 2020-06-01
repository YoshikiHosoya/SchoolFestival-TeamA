// ----------------------------------------
//
// スタート地点処理の説明[startingpoint.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "gate.h"
#include "player.h"
#include "fade.h"
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
LPDIRECT3DTEXTURE9 CGate::m_pTexture[TYPE_MAX] = {};		// テクスチャへのポインタ
CLoad	*CGate::m_pload = NULL;								// ロード
int		CGate::m_nAll = 0;									// 番号

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CGate::CGate() : CScene_THREE::CScene_THREE(ACTOR_GATE, LAYER_3DOBJECT)
{
	// 変数の初期化
	m_Type = TYPE_TURN_R;
	m_UseType = USETYPE_TITLE;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CGate::~CGate()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CGate::Init(void)
{
	// シーン3Dの初期化
	CScene_THREE::Init();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CGate::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CGate::Update(void)
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
		60.0f, 						// 自分の半径
		pPlayer->GetPos(), 			// 相手の位置
		PLAYERCOLLISION_SIZE))		// 相手の半径
	{
		// SEを鳴らす
		//CManager::GetSound()->PlaySound(CSound::LABEL_SE_7);

		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			// ゲームモードに遷移
			CManager::GetFade()->SetFade(CManager::MODE_GAME);
		}
		else if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// ゲームモードに遷移
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}

		// 触れたら消える
		Release();
	}

	if (m_Type == TYPE_TURN_R)
	{
		CScene_THREE::SetRot(CScene_THREE::GetRot() + D3DXVECTOR3(0.0f, 0.0f, 0.01f));

	}
	else
	{
		CScene_THREE::SetRot(CScene_THREE::GetRot() - D3DXVECTOR3(0.0f, 0.0f, 0.01f));
	}

	CScene_THREE::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CGate::Draw(void)
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
void CGate::SetTexture(TYPE type)
{
	// 設定
	CScene_THREE::BindTexture(m_pTexture[type]);	// テクスチャー
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CGate * CGate::Create()
{
	// 変数宣言
	CGate * pStartingPoint;		// シーン3Dクラス
											// メモリの生成(初め->基本クラス,後->派生クラス)
	pStartingPoint = new CGate();
	// 初期化処理
	pStartingPoint->Init();
	// 生成したオブジェクトを返す
	return pStartingPoint;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void CGate::LoadCreate(void)
{
	// 変数宣言
	CGate * pGate;	// ブロック
										// ブロック
	for (int nCntItem = 0; nCntItem < USETYPE_MAX; nCntItem++)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE)
		{
			pGate = CGate::Create();						// 生成
			pGate->SetTexture((TYPE)m_pload->GetInfo(nCntItem).nType);
			pGate->m_Type = (TYPE)m_pload->GetInfo(nCntItem).nType;
			pGate->SetPos(m_pload->GetInfo(nCntItem).pos);		// 位置
			pGate->SetRot(m_pload->GetInfo(nCntItem).rot);		// 回転
			pGate->SetSize(m_pload->GetInfo(nCntItem).size);	// サイズ
			pGate->SetCol(m_pload->GetInfo(nCntItem).col);	// 色
		}
		else if (CManager::GetMode() == CManager::MODE_GAME)
		{
			pGate = CGate::Create();						// 生成
			pGate->SetTexture((TYPE)m_pload->GetInfo(nCntItem + 2).nType);
			pGate->m_Type = (TYPE)m_pload->GetInfo(nCntItem + 2).nType;
			pGate->SetPos(m_pload->GetInfo(nCntItem + 2).pos);		// 位置
			pGate->SetRot(m_pload->GetInfo(nCntItem + 2).rot);		// 回転
			pGate->SetSize(m_pload->GetInfo(nCntItem + 2).size);	// サイズ
			pGate->SetCol(m_pload->GetInfo(nCntItem + 2).col);	// 色
		}

	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CGate::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/UI/StartPoint.png",
		"data/TEXTURE/GAME/key01.png",
	};

	// テクスチャー設定
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ロード生成
	m_pload = new CLoad;
	// ロード読み込み
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Gate_Location.txt");

	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CGate::UnLoad(void)
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
CLoad * CGate::GetLoad(void)
{
	return m_pload;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CGate::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CGate::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CGate::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void CGate::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// 表示テクスチャー設定処理
// ----------------------------------------
void CGate::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
}

// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR3 CGate::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// 回転の取得処理
// ----------------------------------------
D3DXVECTOR3 CGate::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CGate::GetPos(void)
{
	return CScene_THREE::GetPos();
}
