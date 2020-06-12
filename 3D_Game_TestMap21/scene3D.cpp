// =====================================================================================================================================================================
//
// シーン3Dの処理 [scene3D.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "scene3D.h"			// インクルードファイル
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CScene3D::CScene3D(PRIORITY Priority) : CScene(Priority)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CScene3D::~CScene3D()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CScene3D::Init(void)
{
	// 初期化
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 位置
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 位置
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// 回転
	m_fSlope			= 0.0f;															// 斜面
	m_bBillboard		= false;														// ビルボードフラグ
	m_bBothSideCulling	= false;														// 両面カリングフラグ

	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();
	
	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,					// ←頂点数忘れがち
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;		// 頂点情報へのポインタ

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 法線ベクトルの設定
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点カラーの設定
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// 頂点データのアンロック
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CScene3D::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CScene3D::Update(void)
{
	// 頂点情報へのポインタ
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(- m_size.x, + m_size.y, + m_size.z);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x, + m_size.y, + m_size.z);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x, - m_size.y, - m_size.z);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x, - m_size.y, - m_size.z);

	// 頂点データのアンロック
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CScene3D::Draw(void)
{	
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの計算
	CLibrary::MatrixCalculation(&m_mtxWorld, m_rot, m_pos);

	// ビルボードのとき
	if (m_bBillboard)
	{
		CLibrary::BillboardMatrixCalculation(&m_mtxWorld);
	}

	// 両面カリングするとき
	if (m_bBothSideCulling)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// 両面カリング設定
	}

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	// テクスチャの設定
	pDevice->SetTexture(0, m_pTexture);
	// ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	// 裏面カリング設定
}

// =====================================================================================================================================================================
//
// 画像の設定
//
// =====================================================================================================================================================================
void CScene3D::SetTexture(char TexName[])
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TexName, &m_pTexture);
}

// =====================================================================================================================================================================
//
// 半径の設定
//
// =====================================================================================================================================================================
void CScene3D::SetRadius(float fRadius)
{
	// 頂点情報へのポインタ
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y + fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y + fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y - fRadius, 0.0f);

	// 頂点データのアンロック
	m_pVtxBuff->Unlock();

}

// =====================================================================================================================================================================
//
// 拡縮の設定
//
// =====================================================================================================================================================================
void CScene3D::SetScaling(D3DXVECTOR3 size)
{
	// 頂点情報へのポインタ
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点の設定
	pVtx[0].pos = D3DXVECTOR3(-size.x, +size.y, +0.0f);
	pVtx[1].pos = D3DXVECTOR3(+size.x, +size.y, +0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x, 0.0f, -0.0f);
	pVtx[3].pos = D3DXVECTOR3(+size.x, 0.0f, -0.0f);

	// 頂点データのアンロック
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// アニメーションの設定
//
// =====================================================================================================================================================================
void CScene3D::SetAnim(D3DXVECTOR2 UVsize, D3DXVECTOR2 UV)
{
	// 頂点情報へのポインタ
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + UVsize.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y + UVsize.y);

	// 頂点データのアンロック
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// 色の設定
//
// =====================================================================================================================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	// 頂点情報へのポインタ
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点カラー
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	// 頂点データのアンロック
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// テクスチャの分割設定
//
// =====================================================================================================================================================================
void CScene3D::SetTexSeparate(int nSeparate)
{
	// 頂点情報へのポインタ
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f * nSeparate, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * nSeparate);
	pVtx[3].tex = D3DXVECTOR2(1.0f * nSeparate, 1.0f * nSeparate);

	// 頂点データのアンロック
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// 画像の代入
//
// =====================================================================================================================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

// =====================================================================================================================================================================
//
// 高さの取得
//
// =====================================================================================================================================================================
bool CScene3D::GetHeight(D3DXVECTOR3 &pos)
{
	// 頂点情報へのポインタ
	VERTEX_3D *pVtx;

	bool bLand = false;

	CPlayer * pPlayer = CManager::GetGame()->GetPlayer();			// プレイヤーの取得

	if (pPlayer != NULL)
	{
		D3DXVECTOR3 sizePlayer		= pPlayer->GetSize();			// プレイヤーのサイズ取得
		D3DXVECTOR3 posOldPlayer	= pPlayer->GetOldPos();			// プレイヤーの過去の位置取得

		if (m_fSlope < 0)
		{
			m_fSlope *= -1;
		}

		// プレイヤーが上から乗るとき
		if (posOldPlayer.y > pos.y || posOldPlayer.y == pos.y)
		{
			// ブロックの範囲 ( 横 )
			if (m_pos.x - m_size.x < pos.x + sizePlayer.x &&
				m_pos.x + m_size.x > pos.x - sizePlayer.x)
			{
				// ブロックの範囲 ( 縦 )
				if (m_pos.z - m_size.z < pos.z + sizePlayer.z &&
					m_pos.z + m_size.z > pos.z - sizePlayer.z)
				{
					// ブロックの範囲 ( 高さ )
					if (m_pos.y - m_fSlope <= pos.y &&
						m_pos.y + m_fSlope > pos.y)
					{

						// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
						m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						// ベクトル
						D3DXVECTOR3 vec1_0 = pVtx[0].pos - pVtx[1].pos;					// 左
						D3DXVECTOR3 vec0_2 = pVtx[2].pos - pVtx[0].pos;					// 下
						D3DXVECTOR3 vec2_1 = pVtx[1].pos - pVtx[2].pos;					// 右斜め上
						D3DXVECTOR3 vec1_2 = pVtx[2].pos - pVtx[1].pos;					// 左斜め下
						D3DXVECTOR3 vec2_3 = pVtx[3].pos - pVtx[2].pos;					// 右
						D3DXVECTOR3 vec3_1 = pVtx[1].pos - pVtx[3].pos;					// 上

						// 頂点からモデルへのベクトル
						D3DXVECTOR3 vec0_X = pos - m_pos - pVtx[0].pos;
						D3DXVECTOR3 vec1_X = pos - m_pos - pVtx[1].pos;
						D3DXVECTOR3 vec2_X = pos - m_pos - pVtx[2].pos;
						D3DXVECTOR3 vec3_X = pos - m_pos - pVtx[3].pos;

						// 法線	(左
						D3DXVECTOR3 nor1_0_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						D3DXVECTOR3 nor0_2_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						D3DXVECTOR3 nor2_1_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						// 法線	(右
						D3DXVECTOR3 nor2_3_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						D3DXVECTOR3 nor3_1_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						D3DXVECTOR3 nor1_2_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						// 外積	(左
						D3DXVec3Cross(&nor1_0_X, &vec0_X, &vec1_0);
						D3DXVec3Cross(&nor0_2_X, &vec2_X, &vec0_2);
						D3DXVec3Cross(&nor2_1_X, &vec1_X, &vec2_1);
						// 外積	(右
						D3DXVec3Cross(&nor2_3_X, &vec3_X, &vec2_3);
						D3DXVec3Cross(&nor3_1_X, &vec1_X, &vec3_1);
						D3DXVec3Cross(&nor1_2_X, &vec2_X, &vec1_2);

						CDebugProc::Print("nor1_0_X: %.1f, %.1f, %.1f \n", nor1_0_X.x, nor1_0_X.y, nor1_0_X.z);
						CDebugProc::Print("nor0_2_X: %.1f, %.1f, %.1f \n", nor0_2_X.x, nor0_2_X.y, nor0_2_X.z);
						CDebugProc::Print("nor2_1_X: %.1f, %.1f, %.1f \n", nor2_1_X.x, nor2_1_X.y, nor2_1_X.z);
						CDebugProc::Print("nor2_3_X: %.1f, %.1f, %.1f \n", nor2_3_X.x, nor2_3_X.y, nor2_3_X.z);
						CDebugProc::Print("nor3_1_X: %.1f, %.1f, %.1f \n", nor3_1_X.x, nor3_1_X.y, nor3_1_X.z);
						CDebugProc::Print("nor1_2_X: %.1f, %.1f, %.1f \n\n", nor1_2_X.x, nor1_2_X.y, nor1_2_X.z);

						if (nor1_0_X.y >= 0 && nor0_2_X.y >= 0 && nor2_1_X.y >= 0)
						{
							// モデルの高さ計算
							pos.y = m_pos.y + pVtx[0].pos.y + (-pVtx[0].nor.x * (vec0_X.x) - pVtx[0].nor.z * (vec0_X.z)) / pVtx[0].nor.y;
							bLand = true;
						}
						if (nor2_3_X.y >= 0 && nor3_1_X.y >= 0 && nor1_2_X.y >= 0)
						{
							// モデルの高さ計算
							pos.y = m_pos.y + pVtx[3].pos.y + (-pVtx[3].nor.x * (vec3_X.x) - pVtx[3].nor.z * (vec3_X.z)) / pVtx[3].nor.y;
							bLand = true;
						}
						// 頂点データのアンロック
						m_pVtxBuff->Unlock();
					}
				}
			}
		}
		else
		{
			bLand = false;
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// 坂の斜面の設定
//
// =====================================================================================================================================================================
void CScene3D::SetSlope(float Slope)
{
	m_fSlope = Slope;

	// 頂点情報へのポインタ
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +Slope, +m_size.z);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +Slope, +m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -Slope, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -Slope, -m_size.z);

	// 頂点データのアンロック
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// 法線の設定
//
// =====================================================================================================================================================================
void CScene3D::SetNormal()
{
	// 頂点情報へのポインタ
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ベクトル
	m_vec2_0 = pVtx[0].pos - pVtx[2].pos;
	m_vec1_2 = pVtx[1].pos - pVtx[2].pos;
	m_vec2_3 = pVtx[3].pos - pVtx[2].pos;

	// 法線
	m_nor1_2_0	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nor1_2_3	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nor1_2	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// 外積
	D3DXVec3Cross(&m_nor1_2_0, &m_vec2_0, &m_vec1_2);
	D3DXVec3Cross(&m_nor1_2_3, &m_vec1_2, &m_vec2_3);

	// 正規化
	D3DXVec3Normalize(&m_nor1_2_0, &m_nor1_2_0);
	D3DXVec3Normalize(&m_nor1_2_3, &m_nor1_2_3);

	// 法線の加算
	m_nor1_2 = (m_nor1_2_3 + m_nor1_2_0) / 2;
	// 正規化
	D3DXVec3Normalize(&m_nor1_2, &m_nor1_2);

	// 法線ベクトルの設定
	pVtx[0].nor = m_nor1_2_0;
	pVtx[1].nor = m_nor1_2;
	pVtx[2].nor = m_nor1_2;
	pVtx[3].nor = m_nor1_2_3;

	// 頂点データのアンロック
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// 3Dポリゴンの生成
//
// =====================================================================================================================================================================
CScene3D * CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// 変数
	CScene3D *pScene3D;

	// メモリの確保
	pScene3D = new CScene3D(CScene::PRIORITY_MODEL);

	// 初期化
	pScene3D->Init();

	// 位置の設定
	pScene3D->SetPos(pos);

	// サイズの設定
	pScene3D->SetSize(size);

	return pScene3D;
}