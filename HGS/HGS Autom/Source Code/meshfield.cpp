//------------------------------------------------------------------------------
//
//���b�V���t�B�[���h����  [meshfield.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "mesh.h"
#include "renderer.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "camera.h"
#include "meshfield.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMeshField::CMeshField()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMeshField::~CMeshField()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CMeshField::Init()
{
	CMesh::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CMeshField::Uninit()
{
	CMesh::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CMeshField::Update()
{
	CMesh::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CMeshField::Draw()
{
	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtx(), GetPos(), GetRot());

	//�t�H�OON
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_FOG_ON);

	//�`��
	CMesh::Draw();

	//�t�H�OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_FOG_OFF);

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CMeshField::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::shared_ptr<CMeshField> CMeshField::Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const onesize, INTEGER2 const BlockNum)
{
	//�������m��
	std::shared_ptr<CMeshField> pMesh(new CMeshField);

	//nullcheck
	if (pMesh)
	{
		//������
		pMesh->Init();
		pMesh->SetPos(pos);
		pMesh->m_size = onesize;
		pMesh->SetBlockNum(BlockNum);

		//���_����
		pMesh->MakeVertex();
		pMesh->SetNormal();

		//�e�N�X�`���ݒ�
		pMesh->BindTexture(CTexture::GetTexture(CTexture::TEX_NONE));

		//Scene�̔z��ɒǉ�
		pMesh->SetObjType(OBJTYPE_MESHFIELD);
		pMesh->AddSharedList(pMesh);
	}

	return pMesh;
}

//------------------------------------------------------------------------------
//���_�ݒ�
//------------------------------------------------------------------------------
D3DXVECTOR3 CMeshField::SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum)
{
	//���W�v�Z
	return D3DXVECTOR3(-m_size.x * BlockNum.x * 0.5f + m_size.x * nCnt.x,
						nCnt.x * 0.0f,
						m_size.z * BlockNum.y * 0.5f - m_size.z * nCnt.y);;

}

//------------------------------------------------------------------------------
//�����擾
//------------------------------------------------------------------------------
bool CMeshField::GetHeight(D3DXVECTOR3 &pos)
{
	//�u���b�N��
	INTEGER2 BlockNum = GetBlockNum();

	//�|���S����ID
	int nNormalID = 0;
	//�c
	for (int nCntVertical = 0; nCntVertical < BlockNum.y; nCntVertical++)
	{
		//��
		for (int nCntHorizon = 0; nCntHorizon < BlockNum.x; nCntHorizon++, nNormalID += 2)
		{
			//���_�ԍ�
			int nID = (nCntVertical * (BlockNum.x + 1)) + nCntHorizon;

			//�x�N�g���v�Z
			//�ꖇ�ڂ̃|���S���̃x�N�g��
			D3DXVECTOR3 VecAB = m_pVtxMeshList[nID]->pos - m_pVtxMeshList[nID + BlockNum.x + 1]->pos;
			D3DXVECTOR3 VecBC = m_pVtxMeshList[nID + BlockNum.x + 2]->pos - m_pVtxMeshList[nID]->pos;
			D3DXVECTOR3 VecCA = m_pVtxMeshList[nID + BlockNum.x + 1]->pos - m_pVtxMeshList[nID + BlockNum.x + 2]->pos;

			//�񖇖ڂ̃|���S���̃x�N�g��
			D3DXVECTOR3 VecCB = m_pVtxMeshList[nID]->pos - m_pVtxMeshList[nID + BlockNum.x + 2]->pos;
			D3DXVECTOR3 VecDC = m_pVtxMeshList[nID + BlockNum.x + 2]->pos - m_pVtxMeshList[nID + 1]->pos;
			D3DXVECTOR3 VecBD = m_pVtxMeshList[nID + 1]->pos - m_pVtxMeshList[nID]->pos;

			//�e���_����v���C���[�ւ̃x�N�g��
			D3DXVECTOR3 VecAP = pos - m_pVtxMeshList[nID + BlockNum.x + 1]->pos;
			D3DXVECTOR3 VecBP = pos - m_pVtxMeshList[nID]->pos;
			D3DXVECTOR3 VecCP = pos - m_pVtxMeshList[nID + BlockNum.x + 2]->pos;
			D3DXVECTOR3 VecDP = pos - m_pVtxMeshList[nID + 1]->pos;

			//�����
			D3DXVECTOR3 nullvec = ZeroVector3;

			//�ꖇ�ڂ̃|���S���̒����ǂ���
			if (D3DXVec3Cross(&nullvec, &VecAB, &VecAP)->y >= 0 && D3DXVec3Cross(&nullvec, &VecBC, &VecBP)->y >= 0 && D3DXVec3Cross(&nullvec, &VecCA, &VecCP)->y >= 0)
			{
				//�����v�Z
				float fHeight = m_pVtxMeshList[nID]->pos.y + (-m_apNormalList[nNormalID]->x * VecBP.x - m_apNormalList[nNormalID]->z * VecBP.z) / m_apNormalList[nNormalID]->y;

				if (fHeight >= pos.y)
				{
					//�l���
					pos.y = fHeight;
					return true;
				}
			}

			//�񖇖ڂ̃|���S���̒����ǂ���
			if (D3DXVec3Cross(&nullvec, &VecCB, &VecCP)->y >= 0 && D3DXVec3Cross(&nullvec, &VecDC, &VecDP)->y >= 0 && D3DXVec3Cross(&nullvec, &VecBD, &VecBP)->y >= 0)
			{
				//�����v�Z
				float fHeight = m_pVtxMeshList[nID]->pos.y + (-m_apNormalList[nNormalID + 1]->x * VecBP.x - m_apNormalList[nNormalID + 1]->z * VecBP.z) / m_apNormalList[nNormalID + 1]->y;

				if (fHeight >= pos.y)
				{
					//�l���
					pos.y = fHeight;
					return true;
				}

			}
		}
	}
	return false;
}
