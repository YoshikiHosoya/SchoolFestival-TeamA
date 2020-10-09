//------------------------------------------------------------------------------
//
//���b�V���V�����_�[����  [meshcylinder.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "renderer.h"
#include "keyboard.h"
#include "camera.h"
#include "meshcylinder.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMeshCylinder::CMeshCylinder()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMeshCylinder::~CMeshCylinder()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CMeshCylinder::Init()
{
	CMesh::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CMeshCylinder::Uninit()
{
	CMesh::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CMeshCylinder::Update()
{
	CMesh::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CMeshCylinder::Draw()
{
	//Mtx�擾
	D3DXMATRIX *pMtx = GetMtx();

	//Mtx������
	D3DXMatrixIdentity(pMtx);

	//�emtx����
	D3DXMatrixMultiply(pMtx, pMtx, m_pParentMtx);

#ifdef _DEBUG
	//���C�e�B���OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//�`��
	//CMesh::Draw();

	//���C�e�B���O�����ɖ߂�
	CHossoLibrary::CheckLighting();

#endif // _DEBUG


}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CMeshCylinder::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::shared_ptr<CMeshCylinder> CMeshCylinder::Create(D3DXVECTOR3 const pos, D3DXVECTOR3 const onesize, INTEGER2 const BlockNum, D3DXMATRIX *pMtx)
{
	//�������m��
	std::shared_ptr<CMeshCylinder> pMesh(new CMeshCylinder);

	//nullcheck
	if (pMesh)
	{
		//������
		pMesh->Init();
		pMesh->SetPos(pos);
		pMesh->m_size = onesize;
		pMesh->SetBlockNum(BlockNum);
		pMesh->m_pParentMtx = pMtx;

		//���_�ݒ�
		pMesh->MakeVertex();
		pMesh->SetNormal();

		//Scene�̔z��ɒǉ�
		pMesh->SetObjType(OBJTYPE_MESHFIELD);
		pMesh->AddSharedList(pMesh);

	}

	//return
	return pMesh;
}

//------------------------------------------------------------------------------
//���_�ݒ�
//------------------------------------------------------------------------------
D3DXVECTOR3 CMeshCylinder::SetVtx(INTEGER2 nCnt, INTEGER2 BlockNum)
{
	//�~�̂P�s�[�X���̊p�x
	float fRot = (D3DX_PI * 2) / BlockNum.x;

	//���W�v�Z
	return D3DXVECTOR3( sinf(fRot * nCnt.x) * m_size.x,
						m_size.y * nCnt.y,
						cosf(fRot * nCnt.x) * m_size.x);
}