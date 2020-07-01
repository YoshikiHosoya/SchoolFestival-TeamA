//------------------------------------------------------------------------------
//
//軌跡処理  [orbit.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "orbit.h"
#include "manager.h"
#include "renderer.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define DELETE_INTERVAL (MAX_ORBIT_LENGTH / 2)	//削除巻数呼ばれてから消えるまでのインターバル
#define TRANSPARENT_VALUE (0.06f)				//a値加算する値

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
COrbit::COrbit()
{
	//初期化
	m_nLife = 1;
	m_coldefault = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bDeleteFlag = false;
	m_pVtxBuff = nullptr;

	m_posOffset = ZeroVector3;

	for (int nCnt = 0; nCnt < MAX_ORBIT_LENGTH; nCnt++)
	{
		//初期化
		m_posVertex[nCnt] = ZeroVector3;
		m_col[nCnt] = m_coldefault;
	}
}
//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
COrbit::~COrbit()
{
	//nullcheck
	if (m_pVtxBuff)
	{
		//頂点バッファの開放
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT COrbit::Init()
{

	//デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_ORBIT_LENGTH,	//確保するバッファサイズ
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//頂点フォーマット
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_ORBIT_LENGTH; nCnt++)
	{
		//頂点の座標
		pVtx[nCnt].pos = ZeroVector3;

		//法線
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f,-1.0f,0.0f);

		//頂点の色
		pVtx[nCnt].col = m_coldefault;

		//テクスチャ座標
		switch (nCnt % 2)
		{
		case 0:
			pVtx[nCnt].tex = D3DXVECTOR2(0.0f, 1.0f);
			break;
		case 1:
			pVtx[nCnt].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}
	}
	//頂点データをアンロック
	m_pVtxBuff->Unlock();

	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void COrbit::Uninit()
{

}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void COrbit::Update()
{
	//フラグ確認
	if (m_bDeleteFlag)
	{
		//体力
		m_nLife--;

		//ライフが0以下になった時
		if (m_nLife <= 0)
		{
			//消す
			Rerease();
			return;
		}
	}

	//頂点情報を下げる
	for (int nCnt = MAX_ORBIT_LENGTH - 1; nCnt >= 0; nCnt--)
	{
		//最後の頂点の二つ前より小さいとき
		if (nCnt < MAX_ORBIT_LENGTH - 2)
		{
			//2つ前の頂点情報代入
			m_posVertex[nCnt + 2] = m_posVertex[nCnt];
			m_col[nCnt + 2] = m_col[nCnt];

		}
	}

	//フラグ確認
	if (!m_bDeleteFlag)
	{
		//軌跡座標設定
		CalcOrbitPos();
	}
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//現在あるポリゴン枚数分
	for (int nCntVtx = 0; nCntVtx < MAX_ORBIT_LENGTH; nCntVtx++)
	{
		//頂点座標更新
		pVtx[nCntVtx].pos = m_posVertex[nCntVtx];

		//少し透明化
		m_col[nCntVtx].a -= TRANSPARENT_VALUE;

		//色情報代入
		pVtx[nCntVtx].col = m_col[nCntVtx];
	}


	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void COrbit::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//加算合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Zテスト無効でZライティング有効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//カリング無効
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);

	//ライティングOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//計算用変数
	D3DXMATRIX mtx;

	//マトリックス初期化
	D3DXMatrixIdentity(&mtx);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	//頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	//テクスチャの設定
	pDevice->SetTexture(0, CTexture::GetTexture(CTexture::TEX_NONE));

	//ポリゴン描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//プリミティブの種類
							0,					//開始するインデックス(頂点)
							MAX_ORBIT_LENGTH - 2);	//ポリゴンの枚数
													//カリング無効

	//カリングを戻す
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);

	//ライティングを元に戻す
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);

	//Zテスト通常
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//通常合成
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void COrbit::DebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//座標設定　軌跡用のやつ
//------------------------------------------------------------------------------
void COrbit::SetOrbit(D3DXVECTOR3 pos01,D3DXVECTOR3 pos02)
{
	//戦闘座標の代入
	m_posVertex[0] = pos01;
	m_posVertex[1] = pos02;

	//色設定
	m_col[0] = m_coldefault;
	m_col[1] = m_coldefault;
}
//------------------------------------------------------------------------------
//消去処理
//------------------------------------------------------------------------------
void COrbit::DeleteOrbit()
{
	//削除までのインターバル設定
	m_nLife = DELETE_INTERVAL;

	//フラグをtrue
	m_bDeleteFlag = true;
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
COrbit *COrbit::Create(D3DXMATRIX *pMtx)
{
	//変数宣言
	COrbit *pOrbit = new COrbit;

	if (pOrbit)
	{
		//初期化
		pOrbit->Init();
		pOrbit->SetMtx(pMtx);

		//初期座標計算
		pOrbit->CalcOrbitPos();

		//頂点座標初期設定
		pOrbit->SetDefaultVtxPos();

		//オブジェクトタイプ設定
		pOrbit->SetObjType(OBJTYPE_ORBIT);

	}

	//プレイヤーを返す
	return pOrbit;
}

//------------------------------------------------------------------------------
//座標設定
//------------------------------------------------------------------------------
void COrbit::CalcOrbitPos()
{
	//ワールドマトリックスを元に座標設定
	D3DXVECTOR3 pos1 = D3DXVECTOR3(m_pParentMtx->_41, m_pParentMtx->_42, m_pParentMtx->_43);

	D3DXVECTOR3 pos2;
	D3DXVec3TransformCoord(&pos2, &m_posOffset, m_pParentMtx);

	//軌跡の座標設定
	SetOrbit(pos1, pos2);
}
//------------------------------------------------------------------------------
//初期座標設定
//------------------------------------------------------------------------------
void COrbit::SetDefaultVtxPos()
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_ORBIT_LENGTH; nCnt++)
	{
		//テクスチャ座標
		switch (nCnt % 2)
		{
		case 0:
			//頂点の座標
			pVtx[nCnt].pos = m_posVertex[nCnt] = m_posVertex[0];

			break;
		case 1:
			//頂点の座標
			pVtx[nCnt].pos = m_posVertex[nCnt] = m_posVertex[1];

			break;
		default:
			int ndata = 0;
			break;
		}
	}

	//頂点データをアンロック
	m_pVtxBuff->Unlock();
}
