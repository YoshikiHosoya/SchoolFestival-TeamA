// ----------------------------------------
//
// �ԍ������̐���[number.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "number.h"

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
LPDIRECT3DTEXTURE9 CNumber::m_pTex[CNumber::TEX_MAX] = {};

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CNumber::CNumber()
{
	m_pVtxBuff = NULL;
	m_rot = 0;
	m_fLengh = 0;
	m_fAngle = 0;
	m_texID = TEX_SCORE;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CNumber::~CNumber()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CNumber::Init(void)
{	
	// �ϐ��錾
	VERTEX_2D *pVtx;				// ���_���
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
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
	pVtx[0].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f,0.0f,0.0f);
	// ���_�̑傫��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// ���_�e�N�X�`���[
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CNumber::Uninit(void)
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
void CNumber::Update(void)
{
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CNumber::Draw(void)
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

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTex[m_texID]);
	// �|���S���`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);
}

// ----------------------------------------
// �ԍ��ݒ菈��
// ----------------------------------------
void CNumber::SetNum(int nNum)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;	// ���_���
	float fTex;			// �e�N�X�`���[�͈�

	// �e�N�X�`���[�͈͂̌v�Z
	fTex = (float)nNum / 10.0f;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// ���_�e�N�X�`���[
	pVtx[0].tex = D3DXVECTOR2(fTex, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(fTex + 0.1f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(fTex, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(fTex + 0.1f, 1.0f);
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void CNumber::SetPos(D3DXVECTOR3 pos,float fsize)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;	// ���_���

	// �O�p�֐����g���΂߂̒��������߂�
	m_fLengh = sqrtf((fsize / 2) * (fsize / 2) + (fsize / 2) * (fsize / 2));
	m_fAngle = atan2f((fsize / 2), (fsize / 2));

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// ���_���W
	pVtx[0].pos = pos + D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, cosf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[1].pos = pos + D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, cosf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[2].pos = pos + D3DXVECTOR3(sinf(-m_fAngle + m_rot) * m_fLengh, cosf(-m_fAngle + m_rot) * m_fLengh, 0.0f);
	pVtx[3].pos = pos + D3DXVECTOR3(sinf(m_fAngle + m_rot) * m_fLengh, cosf(m_fAngle + m_rot) * m_fLengh, 0.0f);
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �e�N�X�`���[����
// ----------------------------------------
void CNumber::SetTex(TEX tex)
{
	m_texID = tex;
}

// ----------------------------------------
// �J���[�ݒ菈��
// ----------------------------------------
void CNumber::SetCol(D3DXCOLOR col)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;	// ���_���

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// ���_�J���[
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CNumber::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[TEX_MAX][72] =
	{
		{ "data/TEXTURE/number000.png" },
		{ "data/TEXTURE/UI/stage_number.png" },
	};
	// �e�N�X�`���[�̓ǂݍ���
	for (int nCnt = 0; nCnt < TEX_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, TexData[nCnt], &m_pTex[nCnt]);
	}

	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CNumber::UnLoad(void)
{
	// �e�N�X�`���[�̓ǂݍ���
	for (int nCnt = 0; nCnt < TEX_MAX; nCnt++)
	{
		if (m_pTex[nCnt] != NULL)
		{
			m_pTex[nCnt]->Release();
			m_pTex[nCnt] = NULL;
		}
	}
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CNumber * CNumber::Create()
{
	// �ϐ��錾
	CNumber * pNumber;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pNumber = new CNumber();
	// ����������
	pNumber->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pNumber;
}