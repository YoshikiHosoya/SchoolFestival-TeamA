#define _CRT_SECURE_NO_WARNINGS				// 警告除去
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
//=============================================================================
CScene2D::CScene2D(OBJ_TYPE type) : CScene(type)
{

}
CScene2D::~CScene2D()
{
}
//==============================================================================
HRESULT CScene2D::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffBG,
		NULL);
	VERTEX_3D *pVtx;
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +m_size.y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +m_size.y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -m_size.y , 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuffBG->Unlock();

	return S_OK;
}
HRESULT CScene2D::Init2(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffBG,
		NULL);
	VERTEX_2D *pVtx;
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -m_size.y, 0.0f);

	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuffBG->Unlock();

	return S_OK;
}

//ポリゴン開放処理
void CScene2D::Uninit(void)
{
	//頂点バッファの開放
	if (m_pVtxBuffBG != NULL)
	{
		m_pVtxBuffBG->Release();
		m_pVtxBuffBG = NULL;
	}
}
//==========================================================
void CScene2D::Update(void)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -m_size.y, 0.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロック
	m_pVtxBuffBG->Unlock();
}
void CScene2D::Update2(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の設定
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y +m_size.y, 0.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//頂点データをアンロック
	m_pVtxBuffBG->Unlock();
}

void CScene2D::PlayerUIUpdate(int State, float Double)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (State * Double), m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (State * Double), m_pos.y + m_size.y, 0.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロック
	m_pVtxBuffBG->Unlock();
}
void CScene2D::EnemyUIUpdate(int State, float Double)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の
	pVtx[0].pos = D3DXVECTOR3(0.0f, + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ (State * Double), + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ (State * Double), - m_size.y, 0.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//頂点データをアンロック
	m_pVtxBuffBG->Unlock();
}

//ポリゴン描画処理
void CScene2D::BillboardDrow(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);						// ライティングモード無効

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;

	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;

	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, m_pTextureBG);

	// テクスチャの設定
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffBG, 0, sizeof(VERTEX_3D));

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ライティングモード有効

}
void CScene2D::Drow(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, m_pTextureBG);

	// テクスチャの設定
	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, m_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//====サイズセット
void CScene2D::SetSize(D3DXVECTOR2 size)
{
	m_size = size;
}
//角度
void CScene2D::SetBec(D3DXVECTOR3 bec)
{
	m_bec = bec;
}
//====ポジションセット
void CScene2D::SetPosition(float fx, float fy, float fz)
{
	m_pos.x = fx;
	m_pos.y = fy;
	m_pos.z = fz;
}
//====
void CScene2D::SetTex(D3DXVECTOR2 tex)
{
	m_tex = tex;
}
//====アニメーションセット
void CScene2D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + UVsize.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y + UVsize.y);

	//頂点データをアンロック
	m_pVtxBuffBG->Unlock();
}
//====テクスチャのバインド
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 tex)
{
	m_pTextureBG = tex;
}
//====中央を求める
void CScene2D::SetCenter(void)
{
	////方向
	//m_Angle = atan2(m_size, m_size.y);
	////対角線の長さ
	//m_fLength = sqrt(m_size.x * m_size.x + m_size.y*m_size.y);
}
void CScene2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//====ポジション取得
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}
D3DXVECTOR3 CScene2D::GetMove(void)
{
	return m_move;
}
//====カラー取得
D3DXCOLOR CScene2D::GetColor(void)
{
	return m_col;
}
//====サイズ取得
D3DXVECTOR2 CScene2D::GetSize(void)
{
	return m_size;
}
