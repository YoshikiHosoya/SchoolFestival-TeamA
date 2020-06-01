// ----------------------------------------
//
// ライトエフェクト処理の説明[lighteffect.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "lighteffect.h"

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
LPDIRECT3DTEXTURE9 CLightEffect::m_pTexture[TYPE_MAX] = {};		// テクスチャへのポインタ
int		CLightEffect::m_nAll = 0;									// 番号

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CLightEffect::CLightEffect() : CScene_THREE::CScene_THREE(ACTOR_3DLIGHTEFFECT, LAYER_EFFECT)
{
	// 変数の初期化
	m_fLengh = 0;
	m_fAngle = 0;
	m_type = TYPE_S_LIGHT;
	m_bBillboard = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//エフェクトが生成されるたびに合計数を加算
	m_nAll++;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CLightEffect::~CLightEffect()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CLightEffect::Init(void)
{
	// シーン3Dの初期化
	CScene_THREE::Init();
	if (m_bBillboard == true)
	{
		CScene_THREE::SetBillboard(true);				// ビルボード
	}
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CLightEffect::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CLightEffect::Update(void)
{
	Transparency();
	CScene_THREE::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CLightEffect::Draw(void)
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
// 生成処理
// ----------------------------------------
CLightEffect * CLightEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, bool bBill)
{
	// 変数宣言
	CLightEffect * pLightEffect;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pLightEffect = new CLightEffect();
	// 種類
	pLightEffect->m_type = type;
	//テクスチャの設定
	pLightEffect->SetTexure(type);
	// ビルボード
	pLightEffect->m_bBillboard = bBill;
	// 初期化処理
	pLightEffect->Init();
	// 座標
	pLightEffect->m_pos = pos;
	pLightEffect->SetPos(pLightEffect->m_pos);
	// 回転
	pLightEffect->m_rot = rot;
	pLightEffect->SetRot(pLightEffect->m_rot);
	// 大きさ
	pLightEffect->m_size = size;
	pLightEffect->SetSize(pLightEffect->m_size);
	// 色
	pLightEffect->m_col = col;
	pLightEffect->SetCol(pLightEffect->m_col);

	// 生成したオブジェクトを返す
	return pLightEffect;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CLightEffect::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/Effect/effect002.bmp",
		"data/TEXTURE/Effect/effect000.jpg",
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
void CLightEffect::UnLoad(void)
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
// 指定された種類のライトを削除
// ----------------------------------------
void CLightEffect::ReleaseLight(TYPE type)
{
	CLightEffect *pLightEffect[5] = {};
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_EFFECT); nCntLayer++)
	{
		pLightEffect[nCntLayer] = (CLightEffect*)CScene::GetActor(CScene::ACTOR_3DLIGHTEFFECT,CScene::LAYER_EFFECT, nCntLayer);
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if (pLightEffect[nCnt] != NULL)
		{
			if (pLightEffect[nCnt]->m_type == type)
			{
				pLightEffect[nCnt]->Release();
				m_nAll--;
			}
		}
	}
}

// ----------------------------------------
// 位置の設定処理
// ----------------------------------------
void CLightEffect::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CLightEffect::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CLightEffect::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void CLightEffect::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// 表示テクスチャー設定処理
// ----------------------------------------
void CLightEffect::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
}

// ----------------------------------------
// テクスチャの設定
// ----------------------------------------
void CLightEffect::SetTexure(TYPE type)
{
	// 設定
	CScene_THREE::BindTexture(m_pTexture[type]);	// テクスチャー
}

// ----------------------------------------
// 透明
// ----------------------------------------
void CLightEffect::Transparency(void)
{
	if (m_type == TYPE_S_LIGHT)
	{
		// 徐々にα値を加算
		if (m_col.a <= 1.0f)
		{
			//徐々に透明にする
			m_col.a += 0.01f;
			//色の更新
			SetCol(m_col);
		}
	}
}

// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR3 CLightEffect::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// 回転の取得処理
// ----------------------------------------
D3DXVECTOR3 CLightEffect::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CLightEffect::GetPos(void)
{
	return CScene_THREE::GetPos();
}