//------------------------------------------------------------------------------
//
//メッシュスフィア処理  [meshsphere.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "meshsphere.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CMeshSphere::CMeshSphere()
{
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CMeshSphere::~CMeshSphere()
{

}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CMeshSphere::Init()
{
	CMesh::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CMeshSphere::Uninit()
{
	CMesh::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CMeshSphere::Update()
{
	CMesh::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CMeshSphere::Draw()
{
	CHossoLibrary::CalcMatrix(GetMtx(), GetPos(), GetRot());

	CMesh::Draw();
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CMeshSphere::DebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
CMeshSphere *CMeshSphere::Create(D3DXVECTOR3 const pos,float const fRadius, INTEGER2 const BlockNum)
{
	//メモリ確保
	CMeshSphere *pMesh = new CMeshSphere;

	//nullcheck
	if (pMesh)
	{
		//初期化
		pMesh->Init();

		//情報設定
		pMesh->SetPos(pos);
		pMesh->m_fRadius = fRadius;
		pMesh->SetBlockNum(BlockNum);

		//頂点生成
		pMesh->MakeVertex();
		pMesh->SetNormal();

	}
	//return
	return pMesh;
}


//------------------------------------------------------------------------------
//頂点設定
//------------------------------------------------------------------------------
D3DXVECTOR3 CMeshSphere::SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum)
{
	//角度をそれぞれ計算
	float fRotH = (D3DX_PI * 2) / BlockNum.x;
	float fRotV = (D3DX_PI * 2) / BlockNum.y;

	//座標計算
	return D3DXVECTOR3(sinf(fRotH * nCnt.x) * sinf(fRotV * nCnt.y * 0.5f) * m_fRadius,
						-cosf(fRotV * nCnt.y * 0.5f) * m_fRadius,
						cosf(fRotH * nCnt.x) * sinf(fRotV * nCnt.y * 0.5f) * m_fRadius);

}