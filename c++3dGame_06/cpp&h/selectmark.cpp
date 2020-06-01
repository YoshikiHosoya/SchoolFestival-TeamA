// ----------------------------------------
//
// 印処理の説明[selectmark.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "selectmark.h"

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
LPDIRECT3DTEXTURE9 CSelectMark::m_pTexture[MARK_MAX] = {};		// テクスチャへのポインタ

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CSelectMark::CSelectMark() : CScene_TWO::CScene_TWO(ACTOR_MARK, LAYER_UI)
{
	// 変数の初期化
	m_fLengh = 0;
	m_fAngle = 0;
	m_type = MARK_ARROW;
	m_pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	m_frot = 0.0f;
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nSelectCount = 0;
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CSelectMark::~CSelectMark()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CSelectMark::Init(void)
{
	// シーン3Dの初期化
	CScene_TWO::Init();
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CSelectMark::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CSelectMark::Update(void)
{
	CScene_TWO::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CSelectMark::Draw(void)
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

	CScene_TWO::Draw();

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
CSelectMark * CSelectMark::Create(D3DXVECTOR3 pos, float rot, D3DXVECTOR2 size, D3DXCOLOR col, MARK type)
{
	// 変数宣言
	CSelectMark * pSelectMark;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	pSelectMark = new CSelectMark();
	// 種類
	pSelectMark->m_type = type;
	//テクスチャの設定
	pSelectMark->SetTexure(type);
	// 初期化処理
	pSelectMark->Init();
	// 座標
	pSelectMark->m_pos = pos;
	pSelectMark->SetPos(pSelectMark->m_pos);
	// 回転
	pSelectMark->m_frot = rot;
	pSelectMark->SetRot(pSelectMark->m_frot);
	// 大きさ
	pSelectMark->m_size = size;
	pSelectMark->SetSize(pSelectMark->m_size);
	// 色
	pSelectMark->m_col = col;
	pSelectMark->SetCol(pSelectMark->m_col);

	// 生成したオブジェクトを返す
	return pSelectMark;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CSelectMark::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[MARK_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/Effect/.png",
		"data/TEXTURE/Effect/.jpg",
	};

	// テクスチャー設定
	for (int nCnt = 0; nCnt < MARK_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CSelectMark::UnLoad(void)
{
	// テクスチャー設定
	for (int nCnt = 0; nCnt < MARK_MAX; nCnt++)
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
void CSelectMark::SetPos(D3DXVECTOR3 pos)
{
	CScene_TWO::SetPosition(pos);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CSelectMark::SetSize(D3DXVECTOR2 size)
{
	CScene_TWO::SetSize(size);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CSelectMark::SetRot(float rot)
{
	CScene_TWO::SetRot(rot);
}
// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void CSelectMark::SetCol(D3DXCOLOR col)
{
	CScene_TWO::SetCol(col);
}

// ----------------------------------------
// テクスチャの設定
// ----------------------------------------
void CSelectMark::SetTexure(MARK type)
{
	// 設定
	CScene_TWO::BindTexture(m_pTexture[type]);	// テクスチャー
}

// ----------------------------------------
// カウント設定
// ----------------------------------------
void CSelectMark::SetCount(int nCnt)
{
	m_nSelectCount = nCnt;
}

// ----------------------------------------
// カウント設定
// ----------------------------------------
void CSelectMark::CalculationCount(int nCnt)
{
	m_nSelectCount += nCnt;
}

// ----------------------------------------
// カウントをリセット
// ----------------------------------------
void CSelectMark::ResetCount(void)
{
	m_nSelectCount = 0;
}

// ----------------------------------------
// マークの削除
// ----------------------------------------
void CSelectMark::ReleaseSelMark(void)
{
	Release();
}

// ----------------------------------------
// 透明化処理
// ----------------------------------------
void CSelectMark::Transparency(void)
{
	//透明度じゃなかった時
	if (m_col.a > 0.0f)
	{
		//徐々に透明にする
		m_col.a -= 0.005f;
		//色の更新
		SetCol(m_col);
	}

	//透明度が0以下になったら削除
	if (m_col.a <= 0.0f)
	{
		Release();
	}
}

// ----------------------------------------
// カウント取得
// ----------------------------------------
int CSelectMark::GetCount(void)
{
	return m_nSelectCount;
}

// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR2 CSelectMark::GetSize(void)
{
	return CScene_TWO::GetSize();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CSelectMark::GetPos(void)
{
	return CScene_TWO::GetPosition();
}