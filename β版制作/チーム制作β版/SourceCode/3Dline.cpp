// ----------------------------------------
//
// 3D�������̐���[3Dline.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "3Dline.h"
#include "manager.h"
#include "renderer.h"

#ifdef _DEBUG
#include "debugproc.h"
#endif // _DEBUG

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
bool C3DLine::m_bDrawFlag = true;		// ���C���̕`��t���O

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
C3DLine::C3DLine(OBJ_TYPE type) : CSceneBase(type)
{
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
C3DLine::~C3DLine()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
HRESULT C3DLine::Init(void)
{
	// ���_�̐���
	MakeVertex();

	return S_OK;
}

// ----------------------------------------
// �I������
// ----------------------------------------
void C3DLine::Uninit(void)
{
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void C3DLine::Update(void)
{
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void C3DLine::Draw(void)
{
	if (m_bDrawFlag)
	{
		// �ϐ��錾
		LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

		// ��]�E�ʒu�̌v�Z�p�ϐ�
		D3DXMATRIX mtxRot, mtxTrans;

		// ���[���h�}�g���b�N�X�̏�����(�P�ʍs��ɂ��邽��)
		D3DXMatrixIdentity(GetMtxWorld());

		// ��]�𔽉f //
		// ��]�s��쐬(y,x,z)
		D3DXMatrixRotationYawPitchRoll(&mtxRot,
			m_rot.y, m_rot.x, m_rot.z);

		// �s��̐�
		D3DXMatrixMultiply(GetMtxWorld(),
			GetMtxWorld(),
			&mtxRot);

		// �ʒu�𔽉f //
		// ���s�ړ��s��쐬
		D3DXMatrixTranslation(&mtxTrans,
			m_pos.x, m_pos.y, m_pos.z);

		// �s��̐�
		D3DXMatrixMultiply(GetMtxWorld(),
			GetMtxWorld(),
			&mtxTrans);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, GetMtxWorld());

		// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
		pDevice->SetStreamSource(0, GetVtxBuff(), 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		//�e�N�X�`���ݒ�
		pDevice->SetTexture(0, nullptr);

		// �|���S���̕`��
		pDevice->DrawPrimitive(
			D3DPT_LINELIST,
			0,
			2
		);
	}
}
// ----------------------------------------
// �f�o�b�O
// ----------------------------------------
void C3DLine::DebugInfo(void)
{
}

void C3DLine::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize)
{
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void C3DLine::SetPos(
	D3DXVECTOR3 &pos1,
	D3DXVECTOR3 &pos2
)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N
	GetVtxBuff()->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].pos = pos1;
	pVtx[1].pos = pos2;
	GetVtxBuff()->Unlock();
}

// ----------------------------------------
// �f�o�b�N����p�ʒu�ݒ菈��
// ----------------------------------------
void C3DLine::SetPosColi(D3DXVECTOR3 & pos1)
{
	m_pos = pos1;
}

// ----------------------------------------
// �F�ݒ菈��
// ----------------------------------------
void C3DLine::SetCol(D3DXCOLOR & col)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N
	GetVtxBuff()->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	GetVtxBuff()->Unlock();
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
C3DLine * C3DLine::Create(
	D3DXVECTOR3 &pos,
	D3DXVECTOR3 &rot,
	D3DXVECTOR3 &pos1,
	D3DXVECTOR3 &pos2,
	D3DXCOLOR	&col
)
{
	// �ϐ��錾
	C3DLine * p3DLine;
	// �������̐���
	p3DLine = new C3DLine(OBJTYPE_DEBUG3DLINE);
	p3DLine->m_pos = pos;
	p3DLine->m_rot = rot;
	p3DLine->m_col = col;

	// ����������
	p3DLine->Init();
	// �ʒu�ݒ�
	p3DLine->SetPos(pos1, pos2);
	// �ʒu�ݒ�
	p3DLine->SetCol(col);
	// ���������I�u�W�F�N�g��Ԃ�
	return p3DLine;
}
//==========================================================
// �R���X�g���N�^
//==========================================================
void C3DLine::MakeVertex(void)
{
	LPDIRECT3DVERTEXBUFFER9 pVtxBuff;

	CRenderer*pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&pVtxBuff,
		NULL);
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);
	// ���_����
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f);

	//���_�f�[�^���A�����b�N
	pVtxBuff->Unlock();

	CSceneBase::BindVtxBuff(pVtxBuff);
}
