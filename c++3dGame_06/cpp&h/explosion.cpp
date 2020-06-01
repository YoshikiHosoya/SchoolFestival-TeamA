// ----------------------------------------
//
// 爆発エフェクト処理の[explosion.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
#include "explosion.h"
// ----------------------------------------
//
// マクロ定義
//
// ----------------------------------------
#define TEX_X_SMO (0.1f)
#define TEX_X_EXP (0.1428f)
// ----------------------------------------
//
// 静的変数宣言
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[TYPE_MAX] = {};		// テクスチャへのポインタ
D3DXVECTOR2 CExplosion::m_Tex[TYPE_MAX] = {};

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
CExplosion::CExplosion() : CScene_THREE::CScene_THREE(ACTOR_EXPLOSION, LAYER_3DPARTICLE)
{
	// 変数の初期化
	m_fLengh = 0;
	m_fAngle = 0;
	m_Type = TYPE_SMOKE;
	m_bBillboard = false;
	m_nCntAnim = 0;
	m_nPatternAnim = 0;
	m_TexFirst = D3DXVECTOR2(0.0f, 0.0f);
	m_TexFirstSMO = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLast = D3DXVECTOR2(TEX_X_EXP, 1.0f);
	m_TexLastSMO = D3DXVECTOR2(TEX_X_SMO, 1.0f);
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
CExplosion::~CExplosion()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CExplosion::Init(void)
{
	// シーン3Dの初期化
	CScene_THREE::Init();
	//if (m_Type == TYPE_P_LIGHT)
	//{
	//	CScene_THREE::SetBillboard(true);				// ビルボード
	//}

	/*if (m_Type == TYPE_EXPLOSION)
	{
		SetCol(D3DXCOLOR(0.1f, 0.0f, 1.0f, 1.0f));
	}*/

}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CExplosion::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CExplosion::Update(void)
{
	SetAnim();
	CScene_THREE::Update();
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void CExplosion::Draw(void)
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
void CExplosion::SetTexture(TYPE type)
{
	// 設定
	CScene_THREE::BindTexture(m_pTexture[type]);	// テクスチャー
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// 変数宣言
	CExplosion * pExplosion;		// シーン3Dクラス
										// メモリの生成(初め->基本クラス,後->派生クラス)
	pExplosion = new CExplosion();
	//タイプ設定
	pExplosion->m_Type = type;
	// 初期化処理
	pExplosion->Init();
	//座標設定
	pExplosion->SetPos(pos);
	//サイズ設定
	pExplosion->m_Size = size;
	pExplosion->SetSize(size);
	//テクスチャ設定
	pExplosion->SetTexture(type);
	//テクスチャ座標の設定
	//pExplosion->SetTex(pExplosion->m_TexFirst, pExplosion->m_TexLast);
	if (pExplosion->m_Type == TYPE_EXPLOSION)
	{
		pExplosion->SetTex(pExplosion->m_TexFirst, pExplosion->m_TexLast);
	}
	else if (pExplosion->m_Type == TYPE_SMOKE)
	{
		pExplosion->SetTex(pExplosion->m_TexFirstSMO, pExplosion->m_TexLastSMO);
	}
	// 生成したオブジェクトを返す
	return pExplosion;
}

// ----------------------------------------
// 読み込み処理
// ----------------------------------------
HRESULT CExplosion::Load(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =					// デバイスの取得
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// テクスチャー名
	{
		"data/TEXTURE/Effect/Explosion00.png",
		"data/TEXTURE/Effect/Explosion01.png",
	};

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// テクスチャーがあったら
		if (strcmp(cTex[nCnt], "") != 0)
		{
			/* テクスチャーのロード */
			D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
			/* 位置・サイズのロード */
			//m_Tex[nCnt] = tex[nCnt];
		}
	}

	return S_OK;
}

// ----------------------------------------
// unload処理
// ----------------------------------------
void CExplosion::UnLoad(void)
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
void CExplosion::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CExplosion::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// 回転の設定処理
// ----------------------------------------
void CExplosion::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// 色の設定処理
// ----------------------------------------
void CExplosion::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// 表示テクスチャー設定処理
// ----------------------------------------
void CExplosion::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_THREE::SetTex(first, last);
}

// ----------------------------------------
// アニメーションの設定
// ----------------------------------------
void CExplosion::SetAnim(void)
{
	switch (m_Type)
	{
	case TYPE_SMOKE:
		m_nCntAnim++;//カウンター加算
		if (m_nCntAnim % 7 == 0)
		{
			if (m_TexFirstSMO.x < 1.0f - TEX_X_SMO)
			{
				m_TexFirstSMO.x += TEX_X_SMO;
				m_TexLastSMO.x += TEX_X_SMO;

				if (m_nCntAnim <= 18)
				{
					//大きさ加算
					m_Size += D3DXVECTOR3(200.0f, 200.0f, 0.0f);
					SetSize(D3DXVECTOR3(m_Size));
				}
			}

			else if(m_TexFirstSMO.x >= 1.0f - TEX_X_SMO)
			{
				if (m_nCntAnim >= 78)
				{
					//透明度を減算
					m_Col.a -= 0.06f;
				}
				SetCol(m_Col);

				//見えなくなったら削除
				if (m_Col.a <= 0.0f)
				{
					Release();
					m_nCntAnim = 0;
				}
			}

			SetTex(D3DXVECTOR2(m_TexFirstSMO.x, m_TexFirstSMO.y), D3DXVECTOR2(m_TexLastSMO.x, m_TexLastSMO.y));
		}
		break;

	case TYPE_EXPLOSION:
		m_nCntAnim++;//カウンター加算
		SetCol(D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f));
		if (m_nCntAnim % 6 == 0)
		{
			if (m_TexFirst.x < 1.0f - TEX_X_EXP)
			{
				m_TexFirst.x += TEX_X_EXP;
				m_TexLast.x	 += TEX_X_EXP;
			}

			else if (m_TexFirst.x >= 1.0f - TEX_X_EXP)
			{
				Release();
			}

			SetTex(D3DXVECTOR2(m_TexFirst.x, m_TexFirst.y), D3DXVECTOR2(m_TexLast.x, m_TexLast.y));

			if (m_nCntAnim >= 18)
			{
				CExplosion::Create(D3DXVECTOR3(0.000f, 500.000f, - 1700.000f), D3DXVECTOR3(400.0f,400.0f,0.0f), CExplosion::TYPE_SMOKE);
				m_nCntAnim = 0;
			}

		}
		break;

	default:
		break;
	}
}

// ----------------------------------------
// サイズの取得処理
// ----------------------------------------
D3DXVECTOR3 CExplosion::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// 回転の取得処理
// ----------------------------------------
D3DXVECTOR3 CExplosion::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// 位置の取得処理
// ----------------------------------------
D3DXVECTOR3 CExplosion::GetPos(void)
{
	return CScene_THREE::GetPos();
}
