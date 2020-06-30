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
#include "meshfield.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CMeshField::CMeshField()
{
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CMeshField::~CMeshField()
{

}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CMeshField::Init()
{
	CMesh::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CMeshField::Uninit()
{
	CMesh::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CMeshField::Update()
{
	CMesh::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CMeshField::Draw()
{
	//マトリックス計算
	CHossoLibrary::CalcMatrix(GetMtx(), GetPos(), GetRot());

	//描画
	CMesh::Draw();

}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CMeshField::DebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//生成
//------------------------------------------------------------------------------
CMeshField *CMeshField::Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const onesize, INTEGER2 const BlockNum)
{
	//メモリ確保
	CMeshField *pMesh = new CMeshField(OBJTYPE_FIELD);

	//nullcheck
	if (pMesh)
	{
		//初期化
		pMesh->Init();
		pMesh->SetPos(pos);
		pMesh->m_size = onesize;
		pMesh->SetBlockNum(BlockNum);

		//頂点生成
		pMesh->MakeVertex();
		pMesh->SetNormal();

		//テクスチャ設定
		pMesh->BindTexture(CTexture::GetTexture(CTexture::TEX_MESH_GRASS));

	}
	return pMesh;
}

//------------------------------------------------------------------------------
//頂点設定
//------------------------------------------------------------------------------
D3DXVECTOR3 CMeshField::SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum)
{
	//座標計算
	return D3DXVECTOR3(-m_size.x * BlockNum.x * 0.5f + m_size.x * nCnt.x,
						nCnt.x * 0.0f,
						m_size.z * BlockNum.y * 0.5f - m_size.z * nCnt.y);;

}

//------------------------------------------------------------------------------
//高さ取得
//------------------------------------------------------------------------------
bool CMeshField::GetHeight(D3DXVECTOR3 &pos)
{
	//ブロック数
	INTEGER2 BlockNum = GetBlockNum();

	//ポリゴンのID
	int nNormalID = 0;
	//縦
	for (int nCntVertical = 0; nCntVertical < BlockNum.y; nCntVertical++)
	{
		//横
		for (int nCntHorizon = 0; nCntHorizon < BlockNum.x; nCntHorizon++, nNormalID += 2)
		{
			//頂点番号
			int nID = (nCntVertical * (BlockNum.x + 1)) + nCntHorizon;

			//ベクトル計算
			//一枚目のポリゴンのベクトル
			D3DXVECTOR3 VecAB = m_pVtxMeshList[nID]->pos - m_pVtxMeshList[nID + BlockNum.x + 1]->pos;
			D3DXVECTOR3 VecBC = m_pVtxMeshList[nID + BlockNum.x + 2]->pos - m_pVtxMeshList[nID]->pos;
			D3DXVECTOR3 VecCA = m_pVtxMeshList[nID + BlockNum.x + 1]->pos - m_pVtxMeshList[nID + BlockNum.x + 2]->pos;

			//二枚目のポリゴンのベクトル
			D3DXVECTOR3 VecCB = m_pVtxMeshList[nID]->pos - m_pVtxMeshList[nID + BlockNum.x + 2]->pos;
			D3DXVECTOR3 VecDC = m_pVtxMeshList[nID + BlockNum.x + 2]->pos - m_pVtxMeshList[nID + 1]->pos;
			D3DXVECTOR3 VecBD = m_pVtxMeshList[nID + 1]->pos - m_pVtxMeshList[nID]->pos;

			//各頂点からプレイヤーへのベクトル
			D3DXVECTOR3 VecAP = pos - m_pVtxMeshList[nID + BlockNum.x + 1]->pos;
			D3DXVECTOR3 VecBP = pos - m_pVtxMeshList[nID]->pos;
			D3DXVECTOR3 VecCP = pos - m_pVtxMeshList[nID + BlockNum.x + 2]->pos;
			D3DXVECTOR3 VecDP = pos - m_pVtxMeshList[nID + 1]->pos;

			//空っぽ
			D3DXVECTOR3 nullvec = ZeroVector3;

			//一枚目のポリゴンの中かどうか
			if (D3DXVec3Cross(&nullvec, &VecAB, &VecAP)->y >= 0 && D3DXVec3Cross(&nullvec, &VecBC, &VecBP)->y >= 0 && D3DXVec3Cross(&nullvec, &VecCA, &VecCP)->y >= 0)
			{
				//高さ計算
				float fHeight = m_pVtxMeshList[nID]->pos.y + (-m_apNormalList[nNormalID]->x * VecBP.x - m_apNormalList[nNormalID]->z * VecBP.z) / m_apNormalList[nNormalID]->y;

				if (fHeight >= pos.y)
				{
					//値代入
					pos.y = fHeight;
					return true;
				}
			}

			//二枚目のポリゴンの中かどうか
			if (D3DXVec3Cross(&nullvec, &VecCB, &VecCP)->y >= 0 && D3DXVec3Cross(&nullvec, &VecDC, &VecDP)->y >= 0 && D3DXVec3Cross(&nullvec, &VecBD, &VecBP)->y >= 0)
			{
				//高さ計算
				float fHeight = m_pVtxMeshList[nID]->pos.y + (-m_apNormalList[nNormalID + 1]->x * VecBP.x - m_apNormalList[nNormalID + 1]->z * VecBP.z) / m_apNormalList[nNormalID + 1]->y;

				if (fHeight >= pos.y)
				{
					//値代入
					pos.y = fHeight;
					return true;
				}

			}
		}
	}
	return false;
}
