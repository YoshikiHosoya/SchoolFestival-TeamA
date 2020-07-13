//==========================================================
// Scene3D処理：NORI
//==========================================================
//==========================================================
// インクルードファイル
//==========================================================
#include "main.h"
#include "scene3D.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "inputKeyboard.h"
//==========================================================
// コンストラクタ
//==========================================================
CScene3D::CScene3D(OBJ_TYPE type) : CSceneBase(type)
{
}
//==========================================================
// コンストラクタ
//==========================================================
CScene3D::~CScene3D()
{
}
//==========================================================
// コンストラクタ
//==========================================================
HRESULT CScene3D::Init(void)
{
	m_bBillboard = false;														// ビルボードフラグ

	CSceneBase::Init();
	MakeVertex();

	return S_OK;
}
//==========================================================
// コンストラクタ
//==========================================================
void CScene3D::Uninit(void)
{
}
//==========================================================
// コンストラクタ
//==========================================================
void CScene3D::Update(void)
{

}
//==========================================================
// コンストラクタ
//==========================================================
void CScene3D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	//ワールドマトリックスの計算
	MtxCalc();
	// ビルボードするとき
	if (m_bBillboard)
	{
		CHossoLibrary::SetBillboard(GetMtxWorld());
	}
	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, GetMtxWorld());
	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));
	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);
	//テクスチャの設定
	pDevice->SetTexture(0, GetTexture());
	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}
//==========================================================
// デバッグ
//==========================================================
void CScene3D::DebugInfo(void)
{
}
//==========================================================
// コンストラクタ
//==========================================================
void CScene3D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize)
{
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	CSceneBase::GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + UVsize.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y + UVsize.y);

	//頂点データをアンロック
	CSceneBase::GetVtxBuff()->Unlock();
}
//==========================================================
// コンストラクタ
//==========================================================
CScene3D * CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size,D3DXVECTOR3 rot)
{
	CScene3D*pScene3D;
	pScene3D = new CScene3D();
	pScene3D->Init();
	pScene3D->SetPosition(pos);
	pScene3D->SetSize(size);
	pScene3D->SetRot(rot);
	return pScene3D;
}
//==========================================================
// サイズ設定
//==========================================================
void CScene3D::SetSize(D3DXVECTOR3 size)
{
	GetSize() = size;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の
	pVtx[0].pos = D3DXVECTOR3(-GetSize().x, +GetSize().y, +GetSize().z);
	pVtx[1].pos = D3DXVECTOR3(+GetSize().x, +GetSize().y, +GetSize().z);
	pVtx[2].pos = D3DXVECTOR3(-GetSize().x, -GetSize().y, -GetSize().z);
	pVtx[3].pos = D3DXVECTOR3(+GetSize().x, -GetSize().y, -GetSize().z);

	//頂点データをアンロック
	GetVtxBuff()->Unlock();
}
//==========================================================
// カラー設定
//==========================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	GetColor() = col;

	//頂点情報へのポインタ
	VERTEX_3D *pVtx;

	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報の
	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	//頂点データをアンロック
	GetVtxBuff()->Unlock();
}
//==========================================================
// コンストラクタ
//==========================================================
void CScene3D::MakeVertex(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	CRenderer*pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);
	//頂点情報へのポインタ
	VERTEX_3D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の
	pVtx[0].pos = D3DXVECTOR3(-GetSize().x, +GetSize().y, +GetSize().z);
	pVtx[1].pos = D3DXVECTOR3(+GetSize().x, +GetSize().y, +GetSize().z);
	pVtx[2].pos = D3DXVECTOR3(-GetSize().x, -GetSize().y, -GetSize().z);
	pVtx[3].pos = D3DXVECTOR3(+GetSize().x, -GetSize().y, -GetSize().z);

	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	//頂点データをアンロック
	pVtxBuff->Unlock();

	CSceneBase::BindVtxBuff(pVtxBuff);
}
