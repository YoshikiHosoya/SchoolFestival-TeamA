//------------------------------------------------------------------------------
//
//���b�V������  [mesh.cpp]
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
#include "meshsphere.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
int CMesh::m_nNumMesh = 0;

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMesh::CMesh()
{
	//������
	m_pos = ZeroVector3;
	m_rot = ZeroVector3;
	m_col = WhiteColor;
	m_nNumVertex = 0;
	m_nNumIdx = 0;
	m_nNumPolygon = 0;
	m_apNormalList.clear();
	m_pVtxMeshList.clear();
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
	m_bTex = true;

	//�������Z
	m_nNumMesh++;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMesh::~CMesh()
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuff)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
	//�C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff)
	{
		m_pIdxBuff->Release();
		m_pIdxBuff = nullptr;
	}

	//�z��̏���
	m_apNormalList.clear();
	m_pVtxMeshList.clear();

	//�������炷
	m_nNumMesh--;
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CMesh::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CMesh::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CMesh::Update()
{
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CMesh::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�22
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	//bTex��false�̏ꍇ�̓e�N�X�`���𒣂�Ȃ�
	m_bTex ?
		pDevice->SetTexture(0, m_pTexture) :
		pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
									0,
									0,
									m_nNumVertex,			//�g�p���钸�_��
									0,						//���_�̓ǂݎ����J�n����ʒu
									m_nNumPolygon);			//�|���S���̖���

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CMesh::ShowDebugInfo()
{
#ifdef _DEBUG

	//mesh���
	if (ImGui::TreeNode("MeshInfo"))
	{
		//���W
		if (ImGui::TreeNode("pos"))
		{
			if (ImGui::InputFloat3("pos", m_pos))
			{
				//���W�ݒ�
				SetPos(m_pos);
			}
			ImGui::TreePop();
		}
		//���_
		if (ImGui::TreeNode("Vtx"))
		{
			for (int nCnt = 0; nCnt < m_nNumVertex; nCnt++)
			{
				ImGui::InputFloat3("pos", m_pVtxMeshList[nCnt]->pos);
			}
			ImGui::TreePop();
		}
		//�@��
		if (ImGui::TreeNode("Nor"))
		{
			for (int nCnt = 0; nCnt < m_nNumVertex; nCnt++)
			{
				ImGui::InputFloat3("nor", m_pVtxMeshList[nCnt]->nor);
			}
			ImGui::TreePop();
		}
		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//�F�ݒ�
//------------------------------------------------------------------------------
void CMesh::SetCol(D3DXCOLOR const & col)
{
	//�F���f
	m_col = col;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�c
	for (int nCntVertical = 0; nCntVertical < m_BlockNum.y + 1; nCntVertical++)
	{	//��
		for (int nCntHorizon = 0; nCntHorizon < m_BlockNum.x + 1; nCntHorizon++)
		{
			//���_�ԍ�
			int nID = (nCntVertical * (m_BlockNum.x + 1)) + nCntHorizon;

			//�F�ݒ�
			pVtx[nID].col = m_col;
		}
	}

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

}
//------------------------------------------------------------------------------
//���_���X�V
//------------------------------------------------------------------------------
void CMesh::ResetVtx(D3DXVECTOR3 size)
{
	SetSize(size);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�c
	for (int nCntVertical = 0; nCntVertical < m_BlockNum.y + 1; nCntVertical++)
	{	//��
		for (int nCntHorizon = 0; nCntHorizon < m_BlockNum.x + 1; nCntHorizon++)
		{
			//���_�ԍ�
			int nID = (nCntVertical * (m_BlockNum.x + 1)) + nCntHorizon;

			//���_���ݒ�
			//�h���N���X���I�[�o�[���C�h�ŏ������L��
			pVtx[nID].pos = SetVtx(INTEGER2(nCntHorizon, nCntVertical), m_BlockNum);
			m_pVtxMeshList[nID]->pos = pVtx[nID].pos + m_pos;
		}
	}

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//��p�̃e�N�X�`���ݒ�
//------------------------------------------------------------------------------
void CMesh::SetTexSphere()
{
	D3DXVECTOR2 UVSize = D3DXVECTOR2(1.0f / m_BlockNum.x, 1.0f / m_BlockNum.y);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	//�c
	for (int nCntVertical = 0; nCntVertical < m_BlockNum.y + 1; nCntVertical++)
	{	//��
		for (int nCntHorizon = 0; nCntHorizon < m_BlockNum.x + 1; nCntHorizon++)
		{
			//���_�ԍ�
			int nID = (nCntVertical * (m_BlockNum.x + 1)) + nCntHorizon;

			//�e�N�X�`�����W
			pVtx[nID].tex = D3DXVECTOR2(UVSize.x * nCntHorizon, UVSize.y * nCntVertical);
		}
	}
	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//�@���ݒ�
//------------------------------------------------------------------------------
void CMesh::SetNormal()
{
	//�ϐ��錾
	D3DXVECTOR3 VecA = ZeroVector3;
	D3DXVECTOR3 VecB = ZeroVector3;
	D3DXVECTOR3 VecC = ZeroVector3;
	int nID = 0;
	int nCntNormal = 0;

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//�c
	for (int nCntVertical = 0; nCntVertical < m_BlockNum.y; nCntVertical++)
	{
		//��
		for (int nCntHorizon = 0; nCntHorizon < m_BlockNum.x; nCntHorizon++, nCntNormal += 2)
		{
			//���_�ԍ�
			int nID = (nCntVertical * (m_BlockNum.x + 1)) + nCntHorizon;

			//�x�N�g���v�Z
			VecA = m_pVtxMeshList[nID + m_BlockNum.x + 1]->pos - m_pVtxMeshList[nID]->pos;
			VecB = m_pVtxMeshList[nID + m_BlockNum.x + 2]->pos - m_pVtxMeshList[nID]->pos;
			VecC = m_pVtxMeshList[nID + 1]->pos - m_pVtxMeshList[nID]->pos;

			//�O�ς��g���Ėʂ̖@�������߂�
			D3DXVec3Cross(m_apNormalList[nCntNormal].get(), &-VecA, &VecB);
			D3DXVec3Cross(m_apNormalList[nCntNormal + 1].get(), &-VecB, &VecC);

			//���K��
			D3DXVec3Normalize(m_apNormalList[nCntNormal].get(), m_apNormalList[nCntNormal].get());
			D3DXVec3Normalize(m_apNormalList[nCntNormal + 1].get(), m_apNormalList[nCntNormal + 1].get());
		}
	}

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	nCntNormal = 0;
	//�c
	for (int nCntVertical = 0; nCntVertical < m_BlockNum.y + 1; nCntVertical++)
	{
		//��
		for (int nCntHorizon = 0; nCntHorizon < m_BlockNum.x + 1; nCntHorizon++, nID++)
		{
			//�E���̒[�̂Ƃ�
			if (nCntHorizon == m_BlockNum.x && nCntVertical == m_BlockNum.y)
			{
				m_pVtxMeshList[nID]->nor = pVtx[nID].nor = (*m_apNormalList[(nCntNormal * 2)] + (*m_apNormalList[(nCntNormal * 2) + 1])) / 2;
			}

			//��ԉE�ƈ�ԉ��ȊO�̎�
			if (nCntHorizon != m_BlockNum.x && nCntVertical != m_BlockNum.y)
			{
				if (nCntVertical == 0 && nCntHorizon == 0)
				{
					//����
					m_pVtxMeshList[nID]->nor = pVtx[nID].nor = (*m_apNormalList[0] + *m_apNormalList[1]) / 2;
				}

				//��ԏ�̒i
				else if (nCntVertical == 0)
				{
					//3�ʂ̖@�������Z���Ċ���
					m_pVtxMeshList[nID]->nor = pVtx[nID].nor = (*m_apNormalList[(nCntNormal * 2)] + *m_apNormalList[(nCntNormal * 2) + 1] + *m_apNormalList[(nCntNormal * 2) - 1]) / 3;
				}
				//��ԍ��̗�
				else if (nCntHorizon == 0)
				{
					//3�ʂ̖@�������Z���Ċ���
					m_pVtxMeshList[nID]->nor = pVtx[nID].nor = (*m_apNormalList[(nCntNormal * 2)] + *m_apNormalList[(nCntNormal * 2) + 1] + *m_apNormalList[((nCntNormal - m_BlockNum.x) * 2)]) / 3;
				}
				//���̑��@(�[�ɖʂ��ĂȂ�����
				else
				{
					m_pVtxMeshList[nID]->nor = pVtx[nID].nor =
						(	*m_apNormalList[(nCntNormal * 2)] +								//���̖�
							*m_apNormalList[(nCntNormal * 2) + 1] + 						//�E���̖�
							*m_apNormalList[(nCntNormal * 2) - 1] +							//�����̖�
							*m_apNormalList[((nCntNormal - m_BlockNum.x) * 2)] +			//�E��̖�
							*m_apNormalList[((nCntNormal - m_BlockNum.x - 1) * 2)] + 		//����̖�
							*m_apNormalList[((nCntNormal - m_BlockNum.x - 1) * 2) + 1]) 	//��̖�
							/ 6;	//������
				}

				//normal�p�̃J�E���^
				nCntNormal++;

				//�J�E���^����������
				if (nCntNormal >= (m_BlockNum.x * m_BlockNum.y))
				{
					//��ԉ��̗���������邽�߂ɖ߂�
					nCntNormal -= m_BlockNum.x;
				}
			}
			//�E�[�̎�
			else if (nCntHorizon == m_BlockNum.x)
			{
				//��ԏ�ȊO�̎�

				if (nCntVertical == 0)
				{
					m_pVtxMeshList[nID]->nor = pVtx[nID].nor = *m_apNormalList[(nCntNormal * 2) + 1];
				}
				else if (nCntVertical != m_BlockNum.y)
				{
					m_pVtxMeshList[nID]->nor = pVtx[nID].nor = (*m_apNormalList[((nCntNormal - m_BlockNum.x) * 2)] + *m_apNormalList[((nCntNormal - m_BlockNum.x) * 2) + 1] + *m_apNormalList[(nCntNormal * 2) + 1]) / 3;
				}
			}
			//���[�̎�
			else if (nCntVertical == m_BlockNum.y)
			{
				if (nCntHorizon == 0)
				{
					m_pVtxMeshList[nID]->nor = pVtx[nID].nor = *m_apNormalList[(nCntNormal * 2)];
				}
				else if (nCntHorizon != m_BlockNum.x)
				{
					m_pVtxMeshList[nID]->nor = pVtx[nID].nor = (*m_apNormalList[((nCntNormal - m_BlockNum.x - 1) * 2)] + *m_apNormalList[((nCntNormal - m_BlockNum.x - 1) * 2) + 1] + *m_apNormalList[((nCntNormal - m_BlockNum.x) * 2)]) / 3;
				}
				//normal�p�̃J�E���^
				nCntNormal++;

				//�J�E���^����������
				if (nCntNormal >= (m_BlockNum.x * m_BlockNum.y))
				{
					//��ԉ��̗���������邽�߂ɖ߂�
					nCntNormal = m_BlockNum.x * m_BlockNum.y - 1;
				}
			}
		}
	}

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//���_����
//------------------------------------------------------------------------------
void CMesh::MakeVertex()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//�u���b�N������K�v�ȏ��������o��
	m_nNumVertex = (m_BlockNum.x + 1) * (m_BlockNum.y + 1);						//���_��
	m_nNumIdx = (m_BlockNum.x * 2 + 2) * m_BlockNum.y + ((m_BlockNum.y - 1) * 2);	//�C���f�b�N�X��
	m_nNumPolygon = (m_BlockNum.x * m_BlockNum.y) * 2 + (m_BlockNum.y - 1) * 4;	//�|���S����

	//�������m��
	//���_���
	for (int nCnt = 0; nCnt < m_nNumVertex; nCnt++)
	{
		//�������m��
		std::unique_ptr<VERTEX_3D> vertex(new VERTEX_3D);
		m_pVtxMeshList.emplace_back(std::move(vertex));
	}

	//�@�����
	for (int nCnt = 0; nCnt < (m_BlockNum.x * m_BlockNum.y) * 2; nCnt++)
	{
		//�������m��
		std::unique_ptr<D3DXVECTOR3> normal(new D3DXVECTOR3);
		m_apNormalList.emplace_back(std::move(normal));
	}

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X���̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIdx,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,				//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//�C���f�b�N�X�f�[�^�ւ̃|�C���^
	WORD * pIdx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	float fHeight = 0.0f;

	//�c
	for (int nCntVertical = 0; nCntVertical < m_BlockNum.y + 1; nCntVertical++)
	{	//��
		for (int nCntHorizon = 0; nCntHorizon < m_BlockNum.x + 1; nCntHorizon++)
		{
			//���_�ԍ�
			int nID = (nCntVertical * (m_BlockNum.x + 1)) + nCntHorizon;

			//���_���ݒ�
			//�h���N���X���I�[�o�[���C�h�ŏ������L��
			pVtx[nID].pos = SetVtx(INTEGER2(nCntHorizon,nCntVertical),m_BlockNum);
			m_pVtxMeshList[nID]->pos = pVtx[nID].pos + m_pos;

			//�@���͏������@���ƂŌv�Z
			pVtx[nID].nor = ZeroVector3;

			//������
			pVtx[nID].col = WhiteColor;

			//���Ԋu
			pVtx[nID].tex = D3DXVECTOR2((float)nCntHorizon, (float)nCntVertical);		//(�e�N�X�`����UV���W)

		}
	}

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�ݒ�
	//�c
	for (int nCntVertical = 0; nCntVertical < m_BlockNum.y; nCntVertical++)
	{	//��
		for (int nCntHorizon = 0; nCntHorizon < m_BlockNum.x + 1; nCntHorizon++)
		{
			//�C���f�b�N�X�ݒ�
			pIdx[0] = (m_BlockNum.x + 1) + nCntHorizon + nCntVertical * (m_BlockNum.x + 1);
			pIdx[1] = nCntHorizon + nCntVertical * (m_BlockNum.x + 1);

			//�|�C���^�i�߂�
			pIdx += 2;

			//�k�ރ|���S���̕�
			if ((nCntHorizon + 1) % (m_BlockNum.x + 1) == 0 && nCntVertical < m_BlockNum.y - 1)
			{
				pIdx[0] = nCntHorizon + nCntVertical * (m_BlockNum.x + 1);
				pIdx[1] = (m_BlockNum.x + 1) + nCntHorizon + nCntVertical * (m_BlockNum.x + 1) + 1;

				//�|�C���^�i�߂�
				pIdx += 2;
			}
		}
	}

	//�C���f�b�N�X�̃o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();

	//�@���ݒ�
	SetNormal();
}
