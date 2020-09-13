//------------------------------------------------------------------------------
//
//���b�V���{�b�N�X����  [meshbox.cpp]
//Author:fujiwaramasato
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "meshbox.h"
#include "texture.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define SURFACE_H (3)								// ���̖ʂ̐�Horizontal
#define SURFACE_V (2)								// �c�̖ʂ̐�Vertical
#define SURFACE_TOTAL (SURFACE_H * SURFACE_V)		// �ʂ̑���
#define ONE_SURFACE_VERTEX (4)						// 1�̖ʂɊ܂܂�钸�_��
#define VERTEX_NUM (8)								// ���_�̐�
#define VERTEX_INDEX_NUM ((SURFACE_H + 1) * (SURFACE_V + 1) + 4) // ���_�C���f�b�N�X�̐�(�ʂ̐�+1�Œ��_������ �c��̒��_��2�����Z����)
#define TRIANGLE_POLIGON_NUM ((SURFACE_H * SURFACE_V) * 2 + (SURFACE_V - 1) * ONE_SURFACE_VERTEX)// �����̂̎O�p�`�̐�
#define INDEX_NUM (((6 * SURFACE_H) * 2) - 2)// �C���f�b�N�X�̐� 1�̖ʂ������6���_ * �� * �c - ���Ԃ��Ă钸�_ 34


//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CMeshBox::CMeshBox()
{
	//������
	m_pos = ZeroVector3;
	m_col = WhiteColor;
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CMeshBox::~CMeshBox()
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

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CMeshBox::Init()
{
	//������
	m_pos = ZeroVector3;
	m_col = WhiteColor;
	m_pVtxBuff = nullptr;
	m_pIdxBuff = nullptr;

	return S_OK;

}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CMeshBox::Uninit()
{
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CMeshBox::Update()
{
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CMeshBox::Draw()
{
	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(GetMtx(), GetPos(), GetRot());

	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetIndices(m_pIdxBuff);

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexture::GetTexture(CTexture::TEX_TYPE::TEX_NONE));

	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CW);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,		//�v���~�e�B�u�̎��
		0,
		0,
		8,		//�g�p���钸�_�� �O�p�|���S���̒��_
		0,		//���_�̓ǂݎ����J�n����ʒu
		16);	//�|���S���̖���

	// �J�����O���Ȃ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

	//���C�e�B���OON
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CMeshBox::DebugInfo()
{
#ifdef _DEBUG

	CDebugProc::Print_Left("���W�@%f,%f,%f\n",GetPos().x, GetPos().y, GetPos().z);

#endif //DEBUG
}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
CMeshBox *CMeshBox::Create(D3DXVECTOR3 const &pos, D3DXVECTOR3 const &onesize, COLLISION_TYPE  const &type)
{
	//�������m��
	CMeshBox *pMesh = new CMeshBox(OBJTYPE_DEBUGCOLLISION);

	//nullcheck
	if (pMesh)
	{
		// �^�C�v�̐ݒ�
		pMesh->m_Type = type;
		// ������
		pMesh->Init();
		//���_����
		pMesh->MakeVertex();
		// ���W�̐ݒ�
		pMesh->SetPos(pos);
		// �T�C�Y�̐ݒ�
		pMesh->SetSize(onesize);
		// �J���[�̐ݒ�
		pMesh->SetCol(RedColor);
		// �e�N�X�`�����W�̐ݒ�
		pMesh->SetTexPos();
	}
	return pMesh;
}

//------------------------------------------------------------------------------
//�F�ݒ�
//------------------------------------------------------------------------------
void CMeshBox::SetCol(D3DXCOLOR const & col)
{
}

//------------------------------------------------------------------------------
//���W�ݒ�
//------------------------------------------------------------------------------
void CMeshBox::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_Type == TYPE_CENTER)
	{
		// ���_�̍��v = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
	}

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
// 1�̖ʂ�1�e�N�X�`����ݒ肷��
//------------------------------------------------------------------------------
void CMeshBox::SetTexPos()
{
}

//------------------------------------------------------------------------------
//
//------------------------------------------------------------------------------
void CMeshBox::SetPos(D3DXVECTOR3 const & pos)
{
	m_pos = pos;
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	if (m_Type == TYPE_CENTER)
	{
		// ���_�̍��v = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
	}

	else
	{
		// ���_�̍��v = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y, m_pos.z + m_size.z * 0.5f);
	}

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}

//------------------------------------------------------------------------------
//���_����
//------------------------------------------------------------------------------
void CMeshBox::MakeVertex()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 8,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X���̍쐬
	pDevice->CreateIndexBuffer(sizeof(WORD) * 18,	//�m�ۂ���o�b�t�@�T�C�Y
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

	if (m_Type == TYPE_CENTER)
	{
		// ���_�̍��v = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y - m_size.y * 0.5f, m_pos.z + m_size.z * 0.5f);
	}

	else
	{
		// ���_�̍��v = 8
		pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z - m_size.z * 0.5f);
		pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z - m_size.z * 0.5f);
		pVtx[2].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y, m_pos.z - m_size.z * 0.5f);
		pVtx[3].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y, m_pos.z - m_size.z * 0.5f);
		pVtx[4].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z + m_size.z * 0.5f);
		pVtx[5].pos = D3DXVECTOR3(m_pos.x + m_size.x * 0.5f, m_pos.y, m_pos.z + m_size.z * 0.5f);
		pVtx[6].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y + m_size.y, m_pos.z + m_size.z * 0.5f);
		pVtx[7].pos = D3DXVECTOR3(m_pos.x - m_size.x * 0.5f, m_pos.y, m_pos.z + m_size.z * 0.5f);
	}

	//���_�̍��v = 8
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[4].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[5].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[6].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[7].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�̍��v = 8
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[4].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[5].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[6].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);
	pVtx[7].col = D3DXCOLOR(1.0f, 1.0f, 0.0f, 0.5f);

	pVtx[0].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[4].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[5].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[6].tex = D3DXVECTOR2(1.0f, 1.0f);
	pVtx[7].tex = D3DXVECTOR2(1.0f, 0.0f);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	//�C���f�b�N�X�o�b�t�@�̃��b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	//�C���f�b�N�X�ݒ�
	pIdx[0]  = 7;
	pIdx[1]  = 6;
	pIdx[2]  = 5;
	pIdx[3]  = 4;
	pIdx[4]  = 2;
	pIdx[5]  = 1;
	pIdx[6]  = 3;
	pIdx[7]  = 0;
	pIdx[8]  = 0;
	pIdx[9]  = 1;
	pIdx[10] = 1;
	pIdx[11] = 4;
	pIdx[12] = 0;
	pIdx[13] = 6;
	pIdx[14] = 3;
	pIdx[15] = 7;
	pIdx[16] = 2;
	pIdx[17] = 5;

	//�C���f�b�N�X�̃o�b�t�@�̃A�����b�N
	m_pIdxBuff->Unlock();
}