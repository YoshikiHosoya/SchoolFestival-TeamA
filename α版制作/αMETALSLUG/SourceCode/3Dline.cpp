// ----------------------------------------
//
// 3D線処理の説明[3Dline.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// インクルードファイル
//
// ----------------------------------------
/* 描画 */
#include "3Dline.h"
#include "manager.h"
#include "renderer.h"
#ifdef _DEBUG
#include "debugproc.h"
#endif // _DEBUG

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

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
C3DLine::C3DLine(OBJ_TYPE type) : CScene(type)
{
}

// ----------------------------------------
// デストラクタ処理
// ----------------------------------------
C3DLine::~C3DLine()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
HRESULT C3DLine::Init(void)
{
	// 変数宣言
	VERTEX_3D *pVtx;	// 頂点情報へのポイント
	LPDIRECT3DDEVICE9 pDevice =		// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	// 頂点データの範囲をロックし、頂点バッファへのポインタ
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
	m_pVtxBuff->Unlock();

	return S_OK;
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void C3DLine::Uninit(void)
{
	// 頂点バッファの開放
	if (m_pVtxBuff != nullptr)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void C3DLine::Update(void)
{
#ifdef _DEBUG
	//CDebugproc::Print("pos:(%.3f,%.3f,%.3f)\n", m_pos.x, m_pos.y, m_pos.z);
#endif // _DEBUG

}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void C3DLine::Draw(void)
{
	// 変数宣言
	LPDIRECT3DDEVICE9 pDevice =		// デバイスの取得
		CManager::GetRenderer()->GetDevice();

	// 回転・位置の計算用変数
	D3DXMATRIX mtxRot, mtxTrans;

	// ワールドマトリックスの初期化(単位行列にするため)
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映 //
	// ヨーピッチロールによる回転行列作成(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot,					// 総合の入れ物
		m_rot.y, m_rot.x, m_rot.z);	// それぞれの回転量

									// 行列の積(1:ワールド行列 = 2:ワールド行列 * 3:回転行列)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,					// 2
		&mtxRot);							// 3


	// 位置を反映 //
	// 平行移動行列作成(オフセット)
	D3DXMatrixTranslation(&mtxTrans,						// 総合の入れ物
		m_pos.x, m_pos.y, m_pos.z);	// それぞれの移動量

									// 行列の積(1:ワールド行列 = 2:ワールド行列 * 3:移動行列)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,					// 2
		&mtxTrans);							// 3

											// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴンの描画
	pDevice->DrawPrimitive(
		D3DPT_LINELIST,
		0,
		2
	);

}
// ----------------------------------------
// デバッグ
// ----------------------------------------
void C3DLine::DebugInfo(void)
{
}

// ----------------------------------------
// 位置設定処理
// ----------------------------------------
void C3DLine::SetPos(
	D3DXVECTOR3 &pos1,
	D3DXVECTOR3 &pos2
)
{
	// 変数宣言
	VERTEX_3D *pVtx;	// 頂点情報へのポイント

	// 頂点データの範囲をロックし、頂点バッファへのポインタ
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].pos = pos1;
	pVtx[1].pos = pos2;
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// デバック判定用位置設定処理
// ----------------------------------------
void C3DLine::SetPosColi(D3DXVECTOR3 & pos1)
{
	m_pos = pos1;
}

// ----------------------------------------
// 色設定処理
// ----------------------------------------
void C3DLine::SetCol(D3DXCOLOR & col)
{
	// 変数宣言
	VERTEX_3D *pVtx;	// 頂点情報へのポイント

						// 頂点データの範囲をロックし、頂点バッファへのポインタ
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// 作成処理
// ----------------------------------------
C3DLine * C3DLine::Create(
	D3DXVECTOR3 &pos,
	D3DXVECTOR3 &rot,
	D3DXVECTOR3 &pos1,
	D3DXVECTOR3 &pos2,
	D3DXCOLOR	&col
)
{
	// 変数宣言
	C3DLine * p3DLine;
	// メモリの生成(初め->基本クラス,後->派生クラス)
	p3DLine = new C3DLine(OBJTYPE_DEBUG3DLINE);
	p3DLine->m_pos = pos;
	p3DLine->m_rot = rot;
	p3DLine->m_col = col;

	// 初期化処理
	p3DLine->Init();
	// 位置設定
	p3DLine->SetPos(pos1, pos2);
	// 位置設定
	p3DLine->SetCol(col);
	// 生成したオブジェクトを返す
	return p3DLine;
}
