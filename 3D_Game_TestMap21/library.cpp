// =====================================================================================================================================================================
//
// ���C�u�����̏��� [library.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "library.h"			// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"

// =====================================================================================================================================================================
//
// �}�g���b�N�X�̌v�Z
//
// =====================================================================================================================================================================
void CLibrary::MatrixCalculation(D3DXMATRIX *mtxWorld, D3DXVECTOR3 rot, D3DXVECTOR3 pos)
{
	D3DXMATRIX			mtxRot, mtxTrans;				// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(mtxWorld);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(mtxWorld, mtxWorld, &mtxTrans);
}

// =====================================================================================================================================================================
//
// �r���{�[�h�}�g���b�N�X�̌v�Z
//
// =====================================================================================================================================================================
void CLibrary::BillboardMatrixCalculation(D3DXMATRIX * mtxWorld)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	D3DXMATRIX		mtxView;				// �v�Z�p�}�g���b�N�X

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

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, mtxWorld);
}

// =====================================================================================================================================================================
//
// ���_���̐ݒ�
//
// =====================================================================================================================================================================
void CLibrary::SetVertexObject(D3DXVECTOR3 *vtxMin, D3DXVECTOR3 *vtxMax, LPD3DXMESH	Mesh)
{
	// ���f���̒��_���W�̍ő�l�E�ŏ��l�̐ݒ�
	int				nNumVertices;							// ���_��
	DWORD			sizeFVF;								// ���_�t�H�[�}�b�g�̃T�C�Y
	BYTE			*pVertexBuffer;							// ���_�o�b�t�@�ւ̃|�C���^

	*vtxMin = D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);
	*vtxMax = D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);

	// ���_�����擾
	nNumVertices = Mesh->GetNumVertices();

	// ���_�t�H�[�}�b�g�̃T�C�Y�̎擾
	sizeFVF = D3DXGetFVFVertexSize(Mesh->GetFVF());

	// ���_�o�b�t�@�����b�N
	Mesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVertexBuffer);

	for (int nCntVtx = 0; nCntVtx < nNumVertices; nCntVtx++)
	{
		D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVertexBuffer;

		// �S�Ă̒��_�����r���čŏ��A�ő�l�𔲂��o��
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

		// �T�C�Y���|�C���^��i�߂�
		pVertexBuffer += sizeFVF;
	}
	// ���_�o�b�t�@���A�����b�N
	Mesh->UnlockVertexBuffer();
}

// =====================================================================================================================================================================
//
// �I�u�W�F�N�g�̃R���{�{�b�N�X( �Q�Ɠn��
//
// =====================================================================================================================================================================
bool CLibrary::SetObjectComboBox(int & nType)
{
	bool bSelect = false;	// �I��

	// �I�u�W�F�N�g��
	const char* items[] = {"Stone", "Box", "Ground_L", "Ground_M", "Ground_S", "Gayser", "Scaffold", "Scaffold_Hit", "Scaffold_Move", "Wall", "Ground_Half",
							"Ground_Quarter", "Signboard_Fall", "Signboard_Jump", "Signboard_Gayser", "Signboard_Change", "Signboard_AllRide", "Signboard_3DRide"};

	// �R���{�{�b�N�X
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
// �I�u�W�F�N�g�̃R���{�{�b�N�X( �Q�Ɠn��
//
// =====================================================================================================================================================================
bool CLibrary::SetObject2DComboBox(int & nType)
{
	bool bSelect = false;	// �I��

	const char* items[] = { "Floor", "Wall"};

	// �R���{�{�b�N�X
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
// �A�C�e���̃R���{�{�b�N�X( �Q�Ɠn��
//
// =====================================================================================================================================================================
bool CLibrary::SetItemComboBox(int & nType)
{
	bool bSelect = false;	// �I��

	const char* items[] = { "Speed", "Diamond", "Jewel", "Gold", "Key", "1up", "Treasure", "Energy"};

	// �R���{�{�b�N�X
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