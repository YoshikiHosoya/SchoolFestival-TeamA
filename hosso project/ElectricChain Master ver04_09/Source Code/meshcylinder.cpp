//------------------------------------------------------------------------------
//
//メッシュシリンダー処理  [meshcylinder.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "camera.h"
#include "meshcylinder.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CMeshCylinder::CMeshCylinder()
{
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CMeshCylinder::~CMeshCylinder()
{

}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CMeshCylinder::Init()
{
	CMesh::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CMeshCylinder::Uninit()
{
	CMesh::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CMeshCylinder::Update()
{
	CMesh::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CMeshCylinder::Draw()
{
	//Mtx取得
	D3DXMATRIX *pMtx = GetMtx();

	CHossoLibrary::CalcMatrix(pMtx, GetPos(), GetRot());
	D3DXMatrixMultiply(pMtx, pMtx, m_pParentMtx);


	////Mtx初期化
	//D3DXMatrixIdentity(pMtx);

	////親mtx合成
	//D3DXMatrixMultiply(pMtx, pMtx, m_pParentMtx);

#ifdef _DEBUG
	//ライティングOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//描画
	//CMesh::Draw();

	//ライティングを元に戻す
	CHossoLibrary::CheckLighting();

#endif // _DEBUG
}
//------------------------------------------------------------------------------
//影用の描画
//------------------------------------------------------------------------------
void CMeshCylinder::DrawShadowMesh()
{
	//Mtx取得
	D3DXMATRIX *pMtx = GetMtx();

	CHossoLibrary::CalcMatrix(pMtx, GetPos(), GetRot());
	D3DXMatrixMultiply(pMtx, pMtx, m_pParentMtx);

	////Mtx初期化
	//D3DXMatrixIdentity(pMtx);

	////親mtx合成
	//D3DXMatrixMultiply(pMtx, pMtx, m_pParentMtx);

#ifdef _DEBUG
	//ライティングOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//描画
	CMesh::Draw();

	//ライティングを元に戻す
	CHossoLibrary::CheckLighting();

#endif // _DEBUG
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CMeshCylinder::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
std::shared_ptr<CMeshCylinder> CMeshCylinder::Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const onesize, INTEGER2 const BlockNum, D3DXMATRIX *pMtx)
{
	//メモリ確保
	std::shared_ptr<CMeshCylinder> pMesh(new CMeshCylinder);

	//nullcheck
	if (pMesh)
	{
		//初期化
		pMesh->Init();
		pMesh->SetPos(pos);
		pMesh->m_size = onesize;
		pMesh->SetBlockNum(BlockNum);
		pMesh->m_pParentMtx = pMtx;

		//頂点設定
		pMesh->MakeVertex();
		pMesh->SetNormal();

		//Sceneの配列に追加
		pMesh->SetObjType(OBJTYPE_DEBUG_CYLINDER);
		pMesh->AddSharedList(pMesh);

	}

	//return
	return pMesh;
}

//------------------------------------------------------------------------------
//頂点設定
//------------------------------------------------------------------------------
D3DXVECTOR3 CMeshCylinder::SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum)
{
	//円の１ピース分の角度
	float fRot = (D3DX_PI * 2) / BlockNum.x;

	//座標計算
	return D3DXVECTOR3( sinf(fRot * nCnt.x) * m_size.x,
						m_size.y * nCnt.y,
						cosf(fRot * nCnt.x) * m_size.x);
}