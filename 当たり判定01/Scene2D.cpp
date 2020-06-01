#define _CRT_SECURE_NO_WARNINGS				// �x������
#include "main.h"
#include "scene2D.h"
#include "renderer.h"
#include "manager.h"
#include "player.h"
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
//=============================================================================
CScene2D::CScene2D(OBJ_TYPE type) : CScene(type)
{

}
CScene2D::~CScene2D()
{
}
//==============================================================================
HRESULT CScene2D::Init(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffBG,
		NULL);
	VERTEX_3D *pVtx;
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +m_size.y , 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +m_size.y , 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y , 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -m_size.y , 0.0f);

	pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuffBG->Unlock();

	return S_OK;
}
HRESULT CScene2D::Init2(void)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffBG,
		NULL);
	VERTEX_2D *pVtx;
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -m_size.y, 0.0f);

	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	m_pVtxBuffBG->Unlock();

	return S_OK;
}

//�|���S���J������
void CScene2D::Uninit(void)
{
	//���_�o�b�t�@�̊J��
	if (m_pVtxBuffBG != NULL)
	{
		m_pVtxBuffBG->Release();
		m_pVtxBuffBG = NULL;
	}
}
//==========================================================
void CScene2D::Update(void)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -m_size.y, 0.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^���A�����b�N
	m_pVtxBuffBG->Unlock();
}
void CScene2D::Update2(void)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// ���_���̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y +m_size.y, 0.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
	//���_�f�[�^���A�����b�N
	m_pVtxBuffBG->Unlock();
}

void CScene2D::PlayerUIUpdate(int State, float Double)
{
	//���_���ւ̃|�C���^
	VERTEX_2D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// ���_����
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + (State * Double), m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + (State * Double), m_pos.y + m_size.y, 0.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^���A�����b�N
	m_pVtxBuffBG->Unlock();
}
void CScene2D::EnemyUIUpdate(int State, float Double)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;
	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);
	// ���_����
	pVtx[0].pos = D3DXVECTOR3(0.0f, + m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(+ (State * Double), + m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, - m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(+ (State * Double), - m_size.y, 0.0f);

	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//���_�f�[�^���A�����b�N
	m_pVtxBuffBG->Unlock();
}

//�|���S���`�揈��
void CScene2D::BillboardDrow(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);						// ���C�e�B���O���[�h����

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);
	pDevice->GetTransform(D3DTS_VIEW, &mtxView);

	m_mtxWorld._11 = mtxView._11;
	m_mtxWorld._12 = mtxView._21;
	m_mtxWorld._13 = mtxView._31;

	m_mtxWorld._21 = mtxView._12;
	m_mtxWorld._22 = mtxView._22;
	m_mtxWorld._23 = mtxView._32;

	m_mtxWorld._31 = mtxView._13;
	m_mtxWorld._32 = mtxView._23;
	m_mtxWorld._33 = mtxView._33;

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	pDevice->SetTexture(0, m_pTextureBG);

	// �e�N�X�`���̐ݒ�
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffBG, 0, sizeof(VERTEX_3D));

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��

}
void CScene2D::Drow(void)
{
	D3DXMATRIX mtxRot, mtxTrans, mtxView;
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	pDevice->SetTexture(0, m_pTextureBG);

	// �e�N�X�`���̐ݒ�
	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans,
		m_pos.x,
		m_pos.y,
		m_pos.z);

	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld,
		&mtxTrans);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffBG, 0, sizeof(VERTEX_2D));

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

}

void CScene2D::SetColor(D3DXCOLOR col)
{
	m_col = col;
}
//====�T�C�Y�Z�b�g
void CScene2D::SetSize(D3DXVECTOR2 size)
{
	m_size = size;
}
//�p�x
void CScene2D::SetBec(D3DXVECTOR3 bec)
{
	m_bec = bec;
}
//====�|�W�V�����Z�b�g
void CScene2D::SetPosition(float fx, float fy, float fz)
{
	m_pos.x = fx;
	m_pos.y = fy;
	m_pos.z = fz;
}
//====
void CScene2D::SetTex(D3DXVECTOR2 tex)
{
	m_tex = tex;
}
//====�A�j���[�V�����Z�b�g
void CScene2D::SetAnimation(D3DXVECTOR2 UV, D3DXVECTOR2 UVsize)
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffBG->Lock(0, 0, (void**)&pVtx, 0);

	//�e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + UVsize.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y + UVsize.y);

	//���_�f�[�^���A�����b�N
	m_pVtxBuffBG->Unlock();
}
//====�e�N�X�`���̃o�C���h
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 tex)
{
	m_pTextureBG = tex;
}
//====���������߂�
void CScene2D::SetCenter(void)
{
	////����
	//m_Angle = atan2(m_size, m_size.y);
	////�Ίp���̒���
	//m_fLength = sqrt(m_size.x * m_size.x + m_size.y*m_size.y);
}
void CScene2D::SetMove(D3DXVECTOR3 move)
{
	m_move = move;
}
//====�|�W�V�����擾
D3DXVECTOR3 CScene2D::GetPosition(void)
{
	return m_pos;
}
D3DXVECTOR3 CScene2D::GetMove(void)
{
	return m_move;
}
//====�J���[�擾
D3DXCOLOR CScene2D::GetColor(void)
{
	return m_col;
}
//====�T�C�Y�擾
D3DXVECTOR2 CScene2D::GetSize(void)
{
	return m_size;
}
