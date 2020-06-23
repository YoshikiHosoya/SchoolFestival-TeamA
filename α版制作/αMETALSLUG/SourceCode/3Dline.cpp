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

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
C3DLine::C3DLine(OBJ_TYPE type) : CScene(type)
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
	// �ϐ��錾
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���g
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRendere()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f,1.0f,0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);
	m_pVtxBuff->Unlock();

	return S_OK;
}

// ----------------------------------------
// �I������
// ----------------------------------------
void C3DLine::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void C3DLine::Update(void)
{
#ifdef _DEBUG
	//CDebugproc::Print("pos:(%.3f,%.3f,%.3f)\n", m_pos.x, m_pos.y, m_pos.z);
#endif // _DEBUG

}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void C3DLine::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRendere()->GetDevice();

	// ��]�E�ʒu�̌v�Z�p�ϐ�
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����(�P�ʍs��ɂ��邽��)
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f //
	// ���[�s�b�`���[���ɂ���]�s��쐬(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot,					// �����̓��ꕨ
		m_rot.y, m_rot.x, m_rot.z);	// ���ꂼ��̉�]��

									// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��]�s��)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,					// 2
		&mtxRot);							// 3


	// �ʒu�𔽉f //
	// ���s�ړ��s��쐬(�I�t�Z�b�g)
	D3DXMatrixTranslation(&mtxTrans,						// �����̓��ꕨ
		m_pos.x, m_pos.y, m_pos.z);	// ���ꂼ��̈ړ���

									// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:�ړ��s��)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,					// 2
		&mtxTrans);							// 3

											// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S���̕`��
	pDevice->DrawPrimitive(
		D3DPT_LINELIST,
		0,
		2
	);

}
// ----------------------------------------
// �f�o�b�O
// ----------------------------------------
void C3DLine::DebugInfo(void)
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
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���g

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].pos = pos1;
	pVtx[1].pos = pos2;
	m_pVtxBuff->Unlock();
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
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���g

						// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	pVtx[0].col = col;
	pVtx[1].col = col;
	m_pVtxBuff->Unlock();
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
	// �������̐���(����->��{�N���X,��->�h���N���X)
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
