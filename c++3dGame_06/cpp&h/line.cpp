// ----------------------------------------
//
// �������̐���[line.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "line.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

// ----------------------------------------
//
// �O���[�o���ϐ�
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CLine::m_pTex = NULL;

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CLine::CLine() : CScene::CScene(ACTOR_LINE, LAYER_3DOBJECT)
{
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CLine::~CLine()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CLine::Init(void)
{	
	// �ϐ��錾
	VERTEX_2D *pVtx;							// ���_���
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 2,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	// ���_���W
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f, 0.0f);
	// ���_�̑傫��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	// ���_�e�N�X�`���[
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CLine::Uninit(void)
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
void CLine::Update(void)
{
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CLine::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTex);
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_LINELIST, 0, 1);						// ���_��
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void CLine::SetPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;							// ���_���

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	// ���_���W
	pVtx[0].pos = pos1;
	pVtx[1].pos = pos2;

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CLine * CLine::Create(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	// �ϐ��錾
	CLine * pLine;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pLine = new CLine();
	// ����������
	pLine->Init();
	// �ʒu�ݒ�
	pLine->SetPos(pos1, pos2);
	// ���������I�u�W�F�N�g��Ԃ�
	return pLine;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CLine::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	D3DXCreateTextureFromFile(pDevice,"png", &m_pTex);
	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CLine::UnLoad(void)
{
		// �e�N�X�`���̊J��
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}
