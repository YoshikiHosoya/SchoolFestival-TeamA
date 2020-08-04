//------------------------------------------------------------------------------
//
//メッシュフィールド処理  [meshfield.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "meshcircle.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CMeshCircle::CMeshCircle()
{
	//初期化
	m_fRadius = 0.0f;
	m_fWidth = 0.0f;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CMeshCircle::~CMeshCircle()
{

}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CMeshCircle::Init()
{
	CMesh::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CMeshCircle::Uninit()
{
	CMesh::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CMeshCircle::Update()
{
	CMesh::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CMeshCircle::Draw()
{
	//マトリックス計算
	CHossoLibrary::CalcMatrix(GetMtx(), GetPos(), GetRot());

	//描画
	CMesh::Draw();
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CMeshCircle::DebugInfo()
{
#ifdef _DEBUG

	CMesh::DebugInfo();

#endif //DEBUG
}

//------------------------------------------------------------------------------
//頂点設定
//------------------------------------------------------------------------------
D3DXVECTOR3 CMeshCircle::SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum)
{
	//角度を求める
	float fRot = (D3DX_PI * 2) / BlockNum.x;

	//座標設定
	return D3DXVECTOR3(sinf(fRot * nCnt.x) * (m_fRadius + m_fWidth * nCnt.y),
							//m_fWidth * nCnt.y,
							0.1f,
							cosf(fRot * nCnt.x) * (m_fRadius + m_fWidth * nCnt.y));

}
