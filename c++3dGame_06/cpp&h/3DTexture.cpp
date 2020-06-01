// ----------------------------------------
//
// 3dtexture処理の説明[3dtexture.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "3dtexture.h"
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
LPDIRECT3DTEXTURE9 C3DTexture::m_pTexture[TYPE_MAX] = {};		// テクスチャへのポインタ

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
C3DTexture::C3DTexture() : CScene_THREE::CScene_THREE(ACTOR_3DTEXTURE, LAYER_3DOBJECT)
{
	// 変数の初期化
	m_Type = TYPE_EFFECT_000;
	m_bBillboard = false;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
C3DTexture::~C3DTexture()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void C3DTexture::Init(void)
{
	// シーン3Dの初期化
	CScene_THREE::Init();
	CScene_THREE::SetBillboard(m_bBillboard);				// ビルボード
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void C3DTexture::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void C3DTexture::Update(void)
{
	if (m_Type == TYPE_EFFECT_000)
	{

	}
	CScene_THREE::SetRot(CScene_THREE::GetRot() + D3DXVECTOR3(0.0f, 0.01f, 0.0f));
	CScene_THREE::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void C3DTexture::Draw(void)
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
void C3DTexture::SetTexture(TYPE type)
{
	// 設定
	CScene_THREE::BindTexture(m_pTexture[type]);	// テクスチャー
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
C3DTexture * C3DTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size,D3DXCOLOR col,TYPE type,  bool bBillboard)
{
	// 変数宣言
	C3DTexture * p3DTexture;		// シーン3Dクラス
											// メモリの生成(初め->基本クラス,後->派生クラス)
	p3DTexture = new C3DTexture();
	// 種類の設定
	p3DTexture->m_Type = type;
	// ビルボードのかけるかどうか
	p3DTexture->m_bBillboard = bBillboard;
	// 初期化処理
	p3DTexture->Init();
	// 座標の設定
	p3DTexture->SetPos(pos);
	// 回転の設定
	p3DTexture->SetRot(rot);
	// 大きさの設定
	p3DTexture->SetSize(size);
	// 色の設定
	p3DTexture->SetCol(col);
	// テクスチャの設定
	p3DTexture->SetTexture(type);
	// 生成したオブジェクトを返す
	return p3DTexture;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT C3DTexture::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/Effect/Effect002.jpg",
		"data/TEXTURE/Effect/Effect0002.jpg",
	};

	// テクスチャー設定
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void C3DTexture::UnLoad(void)
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
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void C3DTexture::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void C3DTexture::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void C3DTexture::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void C3DTexture::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// 表示テクスチャー設定処理
// ----------------------------------------
void C3DTexture::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_THREE::SetTex(first, last);
}

// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR3 C3DTexture::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// 回転の取得処理
// ----------------------------------------
D3DXVECTOR3 C3DTexture::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 C3DTexture::GetPos(void)
{
	return CScene_THREE::GetPos();
}
