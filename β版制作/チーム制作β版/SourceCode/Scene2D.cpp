//==========================================================
// Scene2D処理：NORI
//==========================================================
//==========================================================
// インクルードファイル
//==========================================================
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
//==========================================================
// コンストラクタ
//==========================================================
CScene2D::CScene2D(OBJ_TYPE type) : CSceneBase(type)
{
}
//==========================================================
// デストラクタ
//==========================================================
CScene2D::~CScene2D()
{
}
//==========================================================
// 初期化
//==========================================================
HRESULT CScene2D::Init(void)
{
	// 変数初期化
	m_bDisp = true;

	CSceneBase::Init();
	MakeVertex();
	return S_OK;
}
//==========================================================
// 終了
//==========================================================
void CScene2D::Uninit(void)
{
}
//==========================================================
// 更新
//==========================================================
void CScene2D::Update(void)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;
	//頂点データの範囲をロックし、頂点バッファへのポインタを取得
	CSceneBase::GetVtxBuff()->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の設定
	pVtx[0].pos = GetPosition() + D3DXVECTOR3(-GetSize().x, -GetSize().y, 0.0f);
	pVtx[1].pos = GetPosition() + D3DXVECTOR3(+GetSize().x, -GetSize().y, 0.0f);
	pVtx[2].pos = GetPosition() + D3DXVECTOR3(-GetSize().x, +GetSize().y, 0.0f);
	pVtx[3].pos = GetPosition() + D3DXVECTOR3(+GetSize().x, +GetSize().y, 0.0f);

	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();
	//頂点データをアンロック
	CSceneBase::GetVtxBuff()->Unlock();
}
//==========================================================
// 描画
//==========================================================
void CScene2D::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// 表示する
	if (m_bDisp)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);
		pDevice->SetTexture(0, GetTexture());

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_2D));

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	}
}
//==========================================================
// デバッグ
//==========================================================
void CScene2D::DebugInfo(void)
{
}
//==========================================================
// クリエイト
//==========================================================
CScene2D * CScene2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	CScene2D*pScene2D;
	pScene2D = new CScene2D();
	pScene2D->SetPosition(pos);
	pScene2D->SetSize(size);
	pScene2D->Init();
	return pScene2D;
}

//==========================================================
// アニメーションの設定
//==========================================================
void CScene2D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize)
{
	//頂点情報へのポインタ
	VERTEX_2D *pVtx;

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
// 頂点バッファ作成
//==========================================================
void CScene2D::MakeVertex(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	// オブジェクトの頂点バッファを生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);
	VERTEX_2D *pVtx;
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// 頂点情報の設定
	pVtx[0].pos = GetPosition() + D3DXVECTOR3(-GetSize().x, -GetSize().y, 0.0f);
	pVtx[1].pos = GetPosition() + D3DXVECTOR3(+GetSize().x, -GetSize().y, 0.0f);
	pVtx[2].pos = GetPosition() + D3DXVECTOR3(-GetSize().x, +GetSize().y, 0.0f);
	pVtx[3].pos = GetPosition() + D3DXVECTOR3(+GetSize().x, +GetSize().y, 0.0f);

	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	pVtx[0].col = GetColor();
	pVtx[1].col = GetColor();
	pVtx[2].col = GetColor();
	pVtx[3].col = GetColor();

	//テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	pVtxBuff->Unlock();

	CSceneBase::BindVtxBuff(pVtxBuff);

}
