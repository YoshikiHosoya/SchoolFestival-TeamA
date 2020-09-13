//------------------------------------------------------------------------------
//
//メッシュボックス処理  [meshbox.cpp]
//Author:fujiwaramasato
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "meshbox.h"
#include "texture.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define SURFACE_H (3)								// 横の面の数Horizontal
#define SURFACE_V (2)								// 縦の面の数Vertical
#define SURFACE_TOTAL (SURFACE_H * SURFACE_V)		// 面の総数
#define ONE_SURFACE_VERTEX (4)						// 1つの面に含まれる頂点数
#define VERTEX_NUM (8)								// 頂点の数
#define VERTEX_INDEX_NUM ((SURFACE_H + 1) * (SURFACE_V + 1) + 4) // 頂点インデックスの数(面の数+1で頂点を求め 残りの頂点分2を加算する)
#define TRIANGLE_POLIGON_NUM ((SURFACE_H * SURFACE_V) * 2 + (SURFACE_V - 1) * ONE_SURFACE_VERTEX)// 立方体の三角形の数
#define INDEX_NUM (((6 * SURFACE_H) * 2) - 2)// インデックスの数 1つの面あたりに6頂点 * 横 * 縦 - かぶってる頂点 34


//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CMeshBox::CMeshBox()
{
	//初期化
	m_pos = ZeroVector3;
	m_col = WhiteColor;
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CMeshBox::~CMeshBox()
{
	//頂点バッファの開放
	if (m_pVtxBuff)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//インデックスバッファの開放
	if (m_pIdxBuff)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CMeshBox::Init()
{
	//初期化
	m_pos = ZeroVector3;
	m_col = WhiteColor;
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;

	return S_OK;

}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CMeshBox::Uninit()
{
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CMeshBox::Update()
{
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CMeshBox::Draw()
{
	//マトリックス計算
	CHossoLibrary::CalcMatrix(GetMtx(), GetPos(), GetRot());

	//デバイス取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//インデックスバッファをデバイスのデータストリームにバインド
	pDevice->SetIndices(m_pIdxBuff);

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CTexture::GetTexture(CTexture::TEX_TYPE::TEX_NONE));

	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CW);

	// ポリゴンの描画
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,		//プリミティブの種類
		0,
		0,
		8,		//使用する頂点数 三角ポリゴンの頂点
		0,		//頂点の読み取りを開始する位置
		16);	//ポリゴンの枚数

	// カリングしない
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

	//ライティングON
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CMeshBox::DebugInfo()
{
#ifdef _DEBUG

	CDebugProc::Print_Left("座標　%f,%f,%f\n",GetPos().x, GetPos().y, GetPos().z);

#endif //DEBUG
}
//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
CMeshBox *CMeshBox::Create(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &onesize, COLLISION_TYPE  const &type)
{
	//メモリ確保
	CMeshBox *pMesh = new CMeshBox(OBJTYPE_DEBUGCOLLISION);

	//nullcheck
	if (pMesh)
	{
		// タイプの設定
		pMesh->m_Type = type;
		// 初期化
		pMesh->Init();
		//頂点生成
		pMesh->MakeVertex();
		// 座標の設定
		pMesh->SetPos(pos);
		// サイズの設定
		pMesh->SetSize(onesize);
		// カラーの設定
		pMesh->SetCol(RedColor);
		// テクスチャ座標の設定
		pMesh->SetTexPos();
	}
	return pMesh;
}

//------------------------------------------------------------------------------
//色設定
//------------------------------------------------------------------------------
void CMeshBox::SetCol(D3DXCOLOR const & col)
{
}

//------------------------------------------------------------------------------
//座標設定
//------------------------------------------------------------------------------
void CMeshBox::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_Type == TYPE_CENTER)
	{
		// 頂点の合計 = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
	}

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
// 1つの面に1つテクスチャを設定する
//------------------------------------------------------------------------------
void CMeshBox::SetTexPos()
{
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CMeshBox::SetPos(D3DXVECTOR3 const & pos)
{
	m_pos = pos;
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_Type == TYPE_CENTER)
	{
		// 頂点の合計 = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
	}

	else
	{
		// 頂点の合計 = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y, m_pos.z + m_size.z * 0.5f);
	}

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//頂点生成
//------------------------------------------------------------------------------
void CMeshBox::MakeVertex()
{
	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 8,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// インデックス情報の作成
	pDevice->CreateIndexBuffer(sizeof(WORD) * 18,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,				//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	//インデックスデータへのポインタ
	WORD * pIdx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_Type == TYPE_CENTER)
	{
		// 頂点の合計 = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
	}

	else
	{
		// 頂点の合計 = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y, m_pos.z + m_size.z * 0.5f);
	}

	//頂点の合計 = 8
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// 頂点の合計 = 8
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);

	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);

	//頂点データをアンロック
	m_pVtxBuff->Unlock();

	//インデックスバッファのロックし、インデックスデータへのポインタを取得
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//インデックス設定
	pIdx[0]  = 7;
	pIdx[1]  = 6;
	pIdx[2]  = 5;
	pIdx[3]  = 4;
	pIdx[4]  = 2;
	pIdx[5]  = 1;
	pIdx[6]  = 3;
	pIdx[7]  = 0;
	pIdx[8]  = 0;
	pIdx[9]  = 1;
	pIdx[10] = 1;
	pIdx[11] = 4;
	pIdx[12] = 0;
	pIdx[13] = 6;
	pIdx[14] = 3;
	pIdx[15] = 7;
	pIdx[16] = 2;
	pIdx[17] = 5;

	//インデックスのバッファのアンロック
	m_pIdxBuff->Unlock();
}