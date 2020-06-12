// =====================================================================================================================================================================
//
// メッシュシリンダー処理 [meshcylinder.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "meshcylinder.h"						// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CMeshCylinder::m_pTexture		= NULL;

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
CMeshCylinder::CMeshCylinder()
{
}

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CMeshCylinder::CMeshCylinder(PRIORITY Priority) : CScene(Priority)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CMeshCylinder::~CMeshCylinder()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
void CMeshCylinder::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// デバイスの取得

	// 計算式
	m_nNumVertex		= POLY_VTX_X * POLY_VTX_Z;							// 総頂点数
	m_nNumPolygon		= POLY_X * POLY_Z * 2 + 4 * (POLY_Z - 1);			// 総ポリゴン数
	m_nNumIndex			= POLY_VTX_X * 2 * POLY_Z + 2 * (POLY_Z - 1);		// 総インデックス数

	// 位置・回転の初期設定
	m_pos				= D3DXVECTOR3(0.0f, -20.0f, 0.0f);
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nSize				= INTEGER2(10, 10);

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
void CMeshCylinder::Uninit(void)
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
void CMeshCylinder::Update(void)
{
	float fPosDown = 20.0f;

	// プレイヤーの情報取得
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();

	// プレイヤーの位置に合わせる
	m_pos = D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y - fPosDown, pPlayer->GetPos().z);
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CMeshCylinder::Draw(void)
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

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);					// ステンシルバッファを有効にする
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zテストon
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);					// ZBuffer書き込みoff
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z条件式　

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					//　ライティングoff




	pDevice->SetRenderState(D3DRS_STENCILREF, 0);						// ステンシル参照値(0)
	//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);					// 色情報を0に
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// ステンシルの対象
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_ZERO);	// ステンシルZテスト共に合格している
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_INCR);	// ステンシルテストに合格、Zテストに不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// ステンシルテストに不合格

	SetCylinderCol(D3DXCOLOR(1, 0, 0, 1));

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);				// 表面カリング設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);	// ポリゴンの描画



	pDevice->SetRenderState(D3DRS_STENCILREF, 1);						// ステンシル参照値(1)
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// ステンシルの対象
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_INCR);	// ステンシルZテスト共に合格している
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_ZERO);	// ステンシルテストに合格、Zテストに不合格
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// ステンシルテストに不合格

	SetCylinderCol(D3DXCOLOR(0, 0, 1, 1));


	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面カリング設定
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);	// ポリゴンの描画




	//pDevice->SetRenderState(D3DRS_STENCILREF, 2);						// ステンシル参照値(2)
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);				// 色をデフォルト値に戻す
	//pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// ステンシルの対象
	//pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_KEEP);	// ステンシルZテスト共に合格している
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_KEEP);	// ステンシルテストに合格、Zテストに不合格
	//pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_KEEP);	// ステンシルテストに不合格

	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);	// ポリゴンの描画


	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);					// Zバッファ書き込み禁止


	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);				// ステンシルバッファを無効にする
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					// Aバッファ書き込み禁止

}

// =====================================================================================================================================================================
//
// メッシュシリンダーの生成
//
// =====================================================================================================================================================================
CMeshCylinder * CMeshCylinder::Create(void)
{
	// 変数
	CMeshCylinder *pMeshCylinder;

	// メモリの確保
	pMeshCylinder = new CMeshCylinder(CScene::PRIORITY_MODEL);

	// 初期化
	pMeshCylinder->Init();

	return pMeshCylinder;
}

// =====================================================================================================================================================================
//
// ロード
//
// =====================================================================================================================================================================
HRESULT CMeshCylinder::Load(void)
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
void CMeshCylinder::Unload(void)
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
// 画像の代入
//
// =====================================================================================================================================================================
void CMeshCylinder::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

// =====================================================================================================================================================================
//
// 頂点情報の作成
//
// =====================================================================================================================================================================
void CMeshCylinder::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
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
	// 円柱の処理
	// ===================================================

	int nCountDirect	= 0;			// 縦のカウント
	int nCountWidth		= 0;			// 横のカウント
	float fAngle		= 0.0f;			// 角度
	float fRadian		= 0.0f;			// ラジアン値
	float fHeight		= 70.0f;		// 高さ

	// 角度の計算
	fAngle = D3DX_PI * 2 / POLY_X;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//行ループ
	for (nCountDirect = 0; nCountDirect < POLY_VTX_Z; nCountDirect++)
	{
		// 列ループ
		for (nCountWidth = 0; nCountWidth < POLY_VTX_X; nCountWidth++)
		{
			// ラジアン値
			fRadian = fAngle * nCountWidth;

			// 回転情報の差分をただす
			if (fRadian < -D3DX_PI)
			{
				fRadian += D3DX_PI * 2;
			}
			if (fRadian > D3DX_PI)
			{
				fRadian += -D3DX_PI * 2;
			}
			

			pVtx[0].pos = D3DXVECTOR3((sinf(fRadian) * (float)m_nSize.x), fHeight * nCountDirect, (cosf(fRadian) * (float)m_nSize.y));

			// カラーの設定
			pVtx[0].col = m_col;

			// テクスチャーの設定
			pVtx[0].tex = D3DXVECTOR2(
				1.0f / POLY_X * nCountWidth,
				1.0f / POLY_Z * (POLY_Z - nCountDirect));

			// ポイント合わせ
			pVtx++;
		}
	}
	pVtx -= m_nNumVertex;

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


// =====================================================================================================================================================================
//
// 頂点色変更
//
// =====================================================================================================================================================================
void CMeshCylinder::SetCylinderCol(D3DXCOLOR col)
{

	//色変更
	m_col = col;

	VERTEX_3D	*pVtx;

	// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//行ループ
	for (int nCountDirect = 0; nCountDirect < POLY_VTX_Z; nCountDirect++)
	{
		// 列ループ
		for (int nCountWidth = 0; nCountWidth < POLY_VTX_X; nCountWidth++)
		{
			// カラーの設定
			pVtx[nCountDirect *POLY_VTX_Z + nCountWidth].col = m_col;

		}
	}

	// 頂点データをアンロックする
	m_pVtxBuff->Unlock();
}

