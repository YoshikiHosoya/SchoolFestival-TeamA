// =====================================================================================================================================================================
//
// メッシュフィールド処理 [meshfield.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "meshfield.h"						// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture = NULL;

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TEXTURE_FILE00		"data/TEXTURE/stone.jpg"	// 読み込むテクスチャファイル名

#define POLY_VTX_X			(POLY_X + 1)				// ポリゴンの頂点数	( 横 )
#define POLY_VTX_Z			(POLY_Z + 1)				// ポリゴンの頂点数	( 縦 )

#define MAX_RAISE			(5.0f)						// 上方
#define WAVE_ANGLE			(10.0f)						// 波の角度

#define WAVE_WIDTH			(240.0f)					// 波の横幅の
#define WAVE_HEIGHT			(3.0f)						// 波の高さの

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CMeshField::CMeshField()
{
}

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CMeshField::CMeshField(PRIORITY Priority) : CScene(Priority)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CMeshField::~CMeshField()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// デバイスの取得

	// 計算式
	m_nNumVertex		= POLY_VTX_X * POLY_VTX_Z;							// 総頂点数
	m_nNumPolygon		= POLY_X * POLY_Z * 2 + 4 * (POLY_Z - 1);			// 総ポリゴン数
	m_nNumIndex			= POLY_VTX_X * 2 * POLY_Z + 2 * (POLY_Z - 1);		// 総インデックス数

	// 位置・回転の初期設定
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSize				= INTEGER2(100, 100);

	// 法線初期化
	for (int nCnt = 0; nCnt < MAX_NOR; nCnt++)
	{
		m_aNor[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// 頂点情報の作成
	MakeVertex(pDevice);
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CMeshField::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != NULL)
	{			 
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// インデックスバッファの開放
	if (m_pIdxBuff != NULL)
	{	   
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CMeshField::Update(void)
{
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CMeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// デバイスの取得
	D3DXMATRIX		mtxRot, mtxTrans;			// 計算用マトリックス

	// ワールドマトリックスの計算
	CLibrary::MatrixCalculation(&m_mtxWorld, m_rot, m_pos);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// インデックスバッファをデータストリームに設定
	pDevice->SetIndices(m_pIdxBuff);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャ設定
	pDevice->SetTexture(0, m_pTexture);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);
}

// =====================================================================================================================================================================
//
// メッシュフィールドの生成
//
// =====================================================================================================================================================================
CMeshField * CMeshField::Create(void)
{
	// 変数
	CMeshField *pMeshField;

	// メモリの確保
	pMeshField = new CMeshField(CScene::PRIORITY_MODEL);

	// 初期化
	pMeshField->Init();

	return pMeshField;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CMeshField::Load(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// テクスチャ読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE00, &m_pTexture);

	return S_OK;
}

// =====================================================================================================================================================================
//
// アンロード
//
// =====================================================================================================================================================================
void CMeshField::Unload(void)
{
	// テクスチャの開放
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture= NULL;
	}
}

// =====================================================================================================================================================================
//
// 高さの取得
//
// =====================================================================================================================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D	*pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntExclusion = 0;			// 除外するカウント
	int nCntNor = 0;
	int nCntVtx = 0;

	// ブロック分回す
	for (int nCnt = 0; nCnt < (POLY_X * POLY_Z); nCnt++)
	{
		if (nCntVtx == POLY_X + (POLY_VTX_X * nCntExclusion))
		{
			// カウントアップ
			nCntExclusion++;
			nCntVtx++;
			pVtx++;
		}

		// ベクトル	(左
		D3DXVECTOR3 vecUp		= pVtx[0].pos - pVtx[POLY_VTX_X].pos ;			// 上
		D3DXVECTOR3 vecDUnder	= pVtx[POLY_VTX_X + 1].pos - pVtx[0].pos;		// 斜め下
		D3DXVECTOR3 vecLeft		= pVtx[POLY_VTX_X].pos - pVtx[POLY_VTX_X + 1].pos;		// 左

		// ベクトル	(右
		D3DXVECTOR3 vecUnder	= pVtx[POLY_VTX_X + 1].pos - pVtx[1].pos;		// 下
		D3DXVECTOR3 vecDUp		= pVtx[0].pos - pVtx[POLY_VTX_X + 1].pos;			// 斜め上
		D3DXVECTOR3 vecRight	= pVtx[1].pos - pVtx[0].pos;		// 右
								
		// 法線	(右
		D3DXVECTOR3 norRight0;
		D3DXVECTOR3 norRight1;
		D3DXVECTOR3 norRight2;
		// 法線	(左
		D3DXVECTOR3 norLeft0;
		D3DXVECTOR3 norLeft1;
		D3DXVECTOR3 norLeft2;

		// プレイヤーへのベクトル
		D3DXVECTOR3 vecP0 = pos - m_pos - pVtx[0].pos;
		D3DXVECTOR3 vecP1 = pos - m_pos - pVtx[1].pos;
		D3DXVECTOR3 vecP2 = pos - m_pos - pVtx[POLY_VTX_X].pos;
		D3DXVECTOR3 vecP3 = pos - m_pos - pVtx[POLY_VTX_X + 1].pos;

		// 外積	(右
		D3DXVec3Cross(&norRight0, &vecUnder, &vecP3);
		D3DXVec3Cross(&norRight1, &vecDUp, &vecP0);
		D3DXVec3Cross(&norRight2, &vecRight, &vecP1);

		// 外積	(左
		D3DXVec3Cross(&norLeft0, &vecUp, &vecP0);
		D3DXVec3Cross(&norLeft1, &vecDUnder, &vecP3);
		D3DXVec3Cross(&norLeft2, &vecLeft, &vecP2);


		CDebugProc::Print("\n\n NorRight0 %.2f\n", norRight0.y);
		CDebugProc::Print(" NorRight1 %.2f\n", norRight1.y);
		CDebugProc::Print(" NorRight2 %.2f\n", norRight2.y);

		CDebugProc::Print("\n\n NorLeft0 %.2f\n", norLeft0.y);
		CDebugProc::Print(" NorLeft1 %.2f\n", norLeft1.y);
		CDebugProc::Print(" NorLeft2 %.2f\n", norLeft2.y);

		// 右に乗っているとき
		if (norRight0.y >= 0 && norRight1.y >= 0 && norRight2.y >= 0)
		{
			// モデルの高さ計算
			pos.y = m_pos.y + pVtx[1].pos.y + (-m_aNor[nCntNor + 1].x * (vecP1.x) - m_aNor[nCntNor + 1].z * (vecP1.z)) / m_aNor[nCntNor + 1].y;

			// 頂点データをアンロックする
			m_pVtxBuff->Unlock();

			return pos.y;
		}

		// 左に乗っているとき
		if (norLeft0.y >= 0 && norLeft1.y >= 0 && norLeft2.y >= 0)
		{
			// モデルの高さ計算
			pos.y =m_pos.y + pVtx[POLY_VTX_X].pos.y + (-m_aNor[nCntNor].x * (vecP2.x) - m_aNor[nCntNor].z * (vecP2.z)) / m_aNor[nCntNor].y;

			// 頂点データをアンロックする
			m_pVtxBuff->Unlock();

			return pos.y;
		}

		// 2つ進める
		nCntNor += 2;
		// カウントアップ
		pVtx++;
		nCntVtx++;
	}
	
	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();

	return pos.y;
}

// =====================================================================================================================================================================
//
// 画像の代入
//
// =====================================================================================================================================================================
void CMeshField::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

// =====================================================================================================================================================================
//
// 頂点情報の作成
//
// =====================================================================================================================================================================
void CMeshField::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntZ = 0;
	int nCntX = 0;

	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,					// ←頂点数忘れがち
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// オブジェクトのインデックスバッファを生成
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,					// ←インデックス数忘れがち
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D	*pVtx;

	// ===================================================
	// 頂点情報の設定
	// ===================================================

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntZ = 0; nCntZ < POLY_VTX_Z; nCntZ++)
	{
		for (nCntX = 0; nCntX < POLY_VTX_X; nCntX++)
		{
			// 頂点座標の設定
			pVtx[0].pos = D3DXVECTOR3(-((float)m_nSize.x * POLY_X / 2) + (float)m_nSize.x * nCntX,
				0.0f,
				((float)m_nSize.y * POLY_Z / 2) - (float)m_nSize.y * nCntZ);

			// 頂点カラーの設定
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// テクスチャ座標の設定
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);
			pVtx++;
		}
	}
	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();

	// ===================================================
	// 試験的 法線計算
	// ===================================================

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntExclusion = 0;			// 除外するカウント
	int nCntNor = 0;
	int nCntVtx = 0;

	// ブロック分回す
	for (int nCnt = 0; nCnt < (POLY_X * POLY_Z); nCnt++)
	{
		if (nCntVtx == POLY_X + (POLY_VTX_X * nCntExclusion))
		{
			// カウントアップ
			nCntExclusion++;
			nCntVtx++;
			pVtx++;
		}
			D3DXVECTOR3 vecU = {};			// 下
			D3DXVECTOR3 vecD = {};			// 斜め
			D3DXVECTOR3 vecR = {};			// 右

			// ベクトル
			vecU = pVtx[POLY_VTX_X].pos		- pVtx[0].pos;
			vecD = pVtx[POLY_VTX_X + 1].pos	- pVtx[0].pos;
			vecR = pVtx[1].pos				- pVtx[0].pos;

			// 外積
			D3DXVec3Cross(&m_aNor[nCntNor], &vecD, &vecU);
			D3DXVec3Cross(&m_aNor[nCntNor + 1], &vecR, &vecD);

			// 正規化
			D3DXVec3Normalize(&m_aNor[nCntNor], &m_aNor[nCntNor]);
			D3DXVec3Normalize(&m_aNor[nCntNor + 1], &m_aNor[nCntNor + 1]);

			// 頂点に法線加算
			// 左上
			pVtx[0].nor += m_aNor[nCntNor] + m_aNor[nCntNor + 1];
			// 右上
			pVtx[1].nor += m_aNor[nCntNor + 1];
			// 左下
			pVtx[POLY_VTX_X].nor += m_aNor[nCntNor];
			// 右下
			pVtx[POLY_VTX_X + 1].nor += m_aNor[nCntNor] + m_aNor[nCntNor + 1];

			// 2つ進める
			nCntNor += 2;
			// カウントアップ
			pVtx++;
			nCntVtx++;

	}
	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
	
	// ===================================================
	// 頂点法線を代入
	// ===================================================

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntZ = 0; nCntZ < POLY_VTX_Z; nCntZ++)
	{
		for (nCntX = 0; nCntX < POLY_VTX_X; nCntX++)
		{
			// === 左上端 ===
			if (nCntZ == 0 && nCntX == 0)
			{
				pVtx[0].nor = pVtx[0].nor / 2;
			}
			// === 右上端 ===
			else if (nCntZ == 0 && nCntX == POLY_X)
			{
				pVtx[0].nor;
			}
			// === 左下端 ===
			else if (nCntZ == POLY_Z && nCntX == 0)
			{
				pVtx[0].nor;
			}
			// === 右下端 ===
			else if (nCntZ == POLY_Z && nCntX == POLY_X)
			{
				pVtx[0].nor = pVtx[0].nor / 2;
			}
			// === 上端 ===
			else if (nCntZ == 0 && nCntX > 0 && nCntX < POLY_X)
			{
				pVtx[0].nor = pVtx[0].nor / 3;
			}
			// === 下端 ===
			else if (nCntZ == POLY_Z && nCntX > 0 && nCntX < POLY_X)
			{
				pVtx[0].nor = pVtx[0].nor / 3;
			}
			// === 左端 ===
			else if (nCntZ > 0 && nCntZ < POLY_Z && nCntX == 0)
			{
				pVtx[0].nor = pVtx[0].nor / 3;
			}
			// === 右端 ===
			else if (nCntZ > 0 && nCntZ < POLY_Z && nCntX == POLY_X)
			{
				pVtx[0].nor = pVtx[0].nor / 3;
			}
			// === 中 ===
			else
			{
				pVtx[0].nor = pVtx[0].nor / 6;
			}
			pVtx++;
		}
	}

	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();

	WORD	*pIdx;

	// ===================================================
	// インデックス情報の設定
	// ===================================================

	// インデックスデータの範囲をロックし、インデックスバッファへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntZ = 0; nCntZ < POLY_Z; nCntZ++)
	{
		// 通常インデックス
		for (nCntX = 0; nCntX < POLY_VTX_X; nCntX++)
		{
			pIdx[0] = POLY_VTX_X + nCntX + (nCntZ * POLY_VTX_X);
			pIdx[1] = nCntX + (nCntZ * POLY_VTX_X);
		
			pIdx += 2;

			// 縮退ポリゴンの計算
			if (nCntX == POLY_X && nCntZ != (POLY_Z - 1))
			{
				pIdx[0] = nCntX + (nCntZ * POLY_VTX_X);
				pIdx[1] = POLY_VTX_X + nCntX + 1 + (nCntZ * POLY_VTX_X);

				pIdx += 2;
			}
		}
	}
	// インデックスデータをアンロックする
	m_pIdxBuff->Unlock();
}