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
bool C3DLine::m_bDrawFlag = true;		// ラインの描画フラグ

// ----------------------------------------
// コンストラクタ処理
// ----------------------------------------
C3DLine::C3DLine(OBJ_TYPE type) : CSceneBase(type)
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
	// 頂点の生成
	MakeVertex();

	return S_OK;
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void C3DLine::Uninit(void)
{
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void C3DLine::Update(void)
{
}

// ----------------------------------------
// 描画処理
// ----------------------------------------
void C3DLine::Draw(void)
{
	if (m_bDrawFlag)
	{
		// 変数宣言
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// 回転・位置の計算用変数
		D3DXMATRIX mtxRot, mtxTrans;

		// ワールドマトリックスの初期化(単位行列にするため)
		D3DXMatrixIdentity(GetMtxWorld());

		// 回転を反映 //
		// 回転行列作成(y,x,z)
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			m_rot.y, m_rot.x, m_rot.z);

		// 行列の積
		D3DXMatrixMultiply(GetMtxWorld(),
			GetMtxWorld(),
			&mtxRot);

		// 位置を反映 //
		// 平行移動行列作成
		D3DXMatrixTranslation(&mtxTrans,
			m_pos.x, m_pos.y, m_pos.z);

		// 行列の積
		D3DXMatrixMultiply(GetMtxWorld(),
			GetMtxWorld(),
			&mtxTrans);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, GetMtxWorld());

		// 頂点バッファをデータストリームに設定
		pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		//テクスチャ設定
		pDevice->SetTexture(0, nullptr);

		// ポリゴンの描画
		pDevice->DrawPrimitive(
			D3DPT_LINELIST,
			0,
			2
		);
	}
}
// ----------------------------------------
// デバッグ
// ----------------------------------------
void C3DLine::DebugInfo(void)
{
}

void C3DLine::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize)
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
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロック
	GetVtxBuff()->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].pos = pos1;
	pVtx[1].pos = pos2;
	GetVtxBuff()->Unlock();
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
	VERTEX_3D *pVtx;

	// 頂点データの範囲をロック
	GetVtxBuff()->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	GetVtxBuff()->Unlock();
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
	// メモリの生成
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
//==========================================================
// コンストラクタ
//==========================================================
void C3DLine::MakeVertex(void)
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
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//頂点データをアンロック
	pVtxBuff->Unlock();

	CSceneBase::BindVtxBuff(pVtxBuff);
}
