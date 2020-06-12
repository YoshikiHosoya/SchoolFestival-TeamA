// =====================================================================================================================================================================
//
// ライブラリの処理 [library.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "library.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"

// =====================================================================================================================================================================
//
// マトリックスの計算
//
// =====================================================================================================================================================================
void CLibrary::MatrixCalculation(D3DXMATRIX *mtxWorld, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	D3DXMATRIX			mtxRot, mtxTrans;				// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTrans);
}

// =====================================================================================================================================================================
//
// ビルボードマトリックスの計算
//
// =====================================================================================================================================================================
void CLibrary::BillboardMatrixCalculation(D3DXMATRIX * mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	D3DXMATRIX		mtxView;				// 計算用マトリックス

	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	mtxWorld->_11 = mtxView._11;
	mtxWorld->_12 = mtxView._21;
	mtxWorld->_13 = mtxView._31;
	mtxWorld->_21 = mtxView._12;
	mtxWorld->_22 = mtxView._22;
	mtxWorld->_23 = mtxView._32;
	mtxWorld->_31 = mtxView._13;
	mtxWorld->_32 = mtxView._23;
	mtxWorld->_33 = mtxView._33;

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, mtxWorld);
}

// =====================================================================================================================================================================
//
// 頂点情報の設定
//
// =====================================================================================================================================================================
void CLibrary::SetVertexObject(D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, LPD3DXMESH	Mesh)
{
	// モデルの頂点座標の最大値・最小値の設定
	int				nNumVertices;							// 頂点数
	DWORD			sizeFVF;								// 頂点フォーマットのサイズ
	BYTE			*pVertexBuffer;							// 頂点バッファへのポインタ

	*vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	*vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	// 頂点数を取得
	nNumVertices = Mesh->GetNumVertices();

	// 頂点フォーマットのサイズの取得
	sizeFVF = D3DXGetFVFVertexSize(Mesh->GetFVF());

	// 頂点バッファをロック
	Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

	for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

		// 全ての頂点情報を比較して最小、最大値を抜き出す
		if (vtxMin->x > vtx.x)
		{
			vtxMin->x = vtx.x;
		}
		if (vtxMin->y > vtx.y)
		{
			vtxMin->y = vtx.y;
		}
		if (vtxMin->z > vtx.z)
		{
			vtxMin->z = vtx.z;
		}

		if (vtxMax->x < vtx.x)
		{
			vtxMax->x = vtx.x;
		}
		if (vtxMax->y < vtx.y)
		{
			vtxMax->y = vtx.y;
		}
		if (vtxMax->z < vtx.z)
		{
			vtxMax->z = vtx.z;
		}

		// サイズ分ポインタを進める
		pVertexBuffer += sizeFVF;
	}
	// 頂点バッファをアンロック
	Mesh->UnlockVertexBuffer();
}

// =====================================================================================================================================================================
//
// オブジェクトのコンボボックス( 参照渡し
//
// =====================================================================================================================================================================
bool CLibrary::SetObjectComboBox(int & nType)
{
	bool bSelect = false;	// 選択

	// オブジェクト名
	const char* items[] = {"Stone", "Box", "Ground_L", "Ground_M", "Ground_S", "Gayser", "Scaffold", "Scaffold_Hit", "Scaffold_Move", "Wall", "Ground_Half",
							"Ground_Quarter", "Signboard_Fall", "Signboard_Jump", "Signboard_Gayser", "Signboard_Change", "Signboard_AllRide", "Signboard_3DRide"};

	// コンボボックス
	if (ImGui::BeginCombo("Type", items[nType]))
	{
		for (int nCnt = 0; nCnt < IM_ARRAYSIZE(items); nCnt++)
		{
			bool is_selected = (items[nType] == items[nCnt]);

			if (ImGui::Selectable(items[nCnt], is_selected))
			{
				nType = nCnt;
				bSelect = true;
			}
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	return bSelect;
}

// =====================================================================================================================================================================
//
// オブジェクトのコンボボックス( 参照渡し
//
// =====================================================================================================================================================================
bool CLibrary::SetObject2DComboBox(int & nType)
{
	bool bSelect = false;	// 選択

	const char* items[] = { "Floor", "Wall"};

	// コンボボックス
	if (ImGui::BeginCombo("Type", items[nType]))
	{
		for (int nCnt = 0; nCnt < IM_ARRAYSIZE(items); nCnt++)
		{
			bool is_selected = (items[nType] == items[nCnt]);

			if (ImGui::Selectable(items[nCnt], is_selected))
			{
				nType = nCnt;
				bSelect = true;
			}
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	return bSelect;
}

// =====================================================================================================================================================================
//
// アイテムのコンボボックス( 参照渡し
//
// =====================================================================================================================================================================
bool CLibrary::SetItemComboBox(int & nType)
{
	bool bSelect = false;	// 選択

	const char* items[] = { "Speed", "Diamond", "Jewel", "Gold", "Key", "1up", "Treasure", "Energy"};

	// コンボボックス
	if (ImGui::BeginCombo("Type", items[nType]))
	{
		for (int nCnt = 0; nCnt < IM_ARRAYSIZE(items); nCnt++)
		{
			bool is_selected = (items[nType] == items[nCnt]);

			if (ImGui::Selectable(items[nCnt], is_selected))
			{
				nType = nCnt;
				bSelect = true;
			}
			if (is_selected)
			{
				ImGui::SetItemDefaultFocus();
			}
		}
		ImGui::EndCombo();
	}
	return bSelect;
}