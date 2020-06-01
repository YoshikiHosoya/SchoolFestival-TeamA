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
#include "startingpoint.h"
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
LPDIRECT3DTEXTURE9 CStartingPoint::m_pTexture[TYPE_MAX] = {};		// テクスチャへのポインタ
CLoad	*CStartingPoint::m_pload = NULL;								// ロード
int		CStartingPoint::m_nAll = 0;									// 番号

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CStartingPoint::CStartingPoint()
{
	// 変数の初期化
	m_Type = TYPE_TURN_R;
	m_fLengh = 0;
	m_fAngle = 0;
	m_bBillboard = false;
}

// ----------------------------------------
// イニシャライザコンストラクタ
// ----------------------------------------
CStartingPoint::CStartingPoint(ACTOR actor, LAYER layer) : CScene_THREE::CScene_THREE(actor, layer)
{
	// 変数の初期化
	m_fLengh = 0;
	m_fAngle = 0;
	m_bBillboard = false;
	m_Type = TYPE_TURN_R;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CStartingPoint::~CStartingPoint()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CStartingPoint::Init(void)
{
	// シーン3Dの初期化
	CScene_THREE::Init();
	//CScene_THREE::SetBillboard(true);				// ビルボード
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CStartingPoint::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CStartingPoint::Update(void)
{
	// 変数宣言
	CPlayer *pPlayer = NULL;	// プレイヤー
							// 情報取得
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	//if (CCalculation::Cube_Juge(
	//	GetPos(),
	//	D3DXVECTOR3(150.0f,150.0f,30.0f),
	//	pPlayer->GetPos(),
	//	D3DXVECTOR3(60.0f, 60.0f, 60.0f)))
	//{
	//	// SEを鳴らす
	//	CManager::GetSound()->PlaySound(CSound::LABEL_SE_8);
	//	CManager::GetFade()->SetFade(CManager::MODE_GAME);
	//}



	// アイテムの取得
	if (CCalculation::Collision_Circle(
		GetPos(),					// 自分の位置
		60.0f, 						// 自分の半径
		pPlayer->GetPos(), 			// 相手の位置
		PLAYERCOLLISION_SIZE))		// 相手の半径
	{
		// SEを鳴らす
		CManager::GetSound()->PlaySound(CSound::LABEL_SE_7);
		// ゲームモードに遷移
		CManager::GetFade()->SetFade(CManager::MODE_GAME);

		// 触れたら消える
		Release();
	}

	CScene_THREE::SetCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	CScene_THREE::SetRot(CScene_THREE::GetRot() + D3DXVECTOR3(0.0f, 0.0f, 0.01f));
	CScene_THREE::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CStartingPoint::Draw(void)
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
void CStartingPoint::SetTexture(TYPE type)
{
	// 設定
	CScene_THREE::BindTexture(m_pTexture[type]);	// テクスチャー
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CStartingPoint * CStartingPoint::Create(bool bBillboard)
{
	// 変数宣言
	CStartingPoint * pStartingPoint;		// シーン3Dクラス
						// メモリの生成(初め->基本クラス,後->派生クラス)
	pStartingPoint = new CStartingPoint(ACTOR_ITEM, LAYER_3DOBJECT);
	// ビルボードのかけるかどうか
	pStartingPoint->m_bBillboard = bBillboard;
	// 初期化処理
	pStartingPoint->Init();
	// 生成したオブジェクトを返す
	return pStartingPoint;
}

// ----------------------------------------
// 読み込み作成処理
// ----------------------------------------
void CStartingPoint::LoadCreate(void)
{
	// 変数宣言
	CStartingPoint * pStartingPoint;	// ブロック
					// ブロック
	for (int nCntItem = 0; nCntItem < m_nAll; nCntItem++)
	{
		pStartingPoint = CStartingPoint::Create(true);						// 生成
		pStartingPoint->SetTexture((TYPE)m_pload->GetInfo(nCntItem).nType);
		pStartingPoint->m_Type = (TYPE)m_pload->GetInfo(nCntItem).nType;
		pStartingPoint->SetPos(m_pload->GetInfo(nCntItem).pos);		// 位置
		pStartingPoint->SetRot(m_pload->GetInfo(nCntItem).rot);		// 回転
		pStartingPoint->SetSize(m_pload->GetInfo(nCntItem).size);	// サイズ
	}
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CStartingPoint::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/UI/StartPoint.png",
		"data/TEXTURE/UI/StartPoint.png",
	};

	// テクスチャー設定
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ロード生成
	m_pload = new CLoad;
	// ロード読み込み
	m_nAll = m_pload->Load("data/LOAD/OBJECT/StartPoint_Location.txt");

	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CStartingPoint::UnLoad(void)
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
CLoad * CStartingPoint::GetLoad(void)
{
	return m_pload;
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CStartingPoint::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CStartingPoint::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CStartingPoint::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void CStartingPoint::SetCol(D3DXCOLOR col)
{
}

// ----------------------------------------
// 表示テクスチャー設定処理
// ----------------------------------------
void CStartingPoint::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
}

// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR3 CStartingPoint::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// 回転の取得処理
// ----------------------------------------
D3DXVECTOR3 CStartingPoint::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CStartingPoint::GetPos(void)
{
	return CScene_THREE::GetPos();
}
