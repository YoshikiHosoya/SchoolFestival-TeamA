// ----------------------------------------
//
// ��ʑJ�ڏ����̐���[fade.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "fade.h"
#include "manager.h"

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
LPDIRECT3DTEXTURE9 CFade::m_pTex = NULL;

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CFade::CFade()
{
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CFade::~CFade()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CFade::Init(CManager::MODE Mode)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;				// ���_���
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	m_fade = FADE_IN;
	m_modeNext = Mode;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ������ʁi�s�����j

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
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	// ���_�̑傫��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// ���_�J���[
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;
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
void CFade::Uninit(void)
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
void CFade::Update(void)
{
	VERTEX_2D *pVtx;

	if (m_fade != FADE_NONE)
	{
		if (m_fade == FADE_IN)
		{
			m_col.a -= 0.01f;
			if (m_col.a <= 0.0f)
			{
				// �t�F�[�h�I��
				m_col.a = 0.0f;
				m_fade = FADE_NONE;
			}
		}

		else if (m_fade == FADE_OUT)
		{
			// �t�F�[�h�A�E�g
			m_col.a += 0.05f;
			if (m_col.a >= 1.0f)
			{
				// �t�F�[�h�I��
				m_col.a = 1.0f;
				m_fade = FADE_IN;
				CManager::SetMode(m_modeNext);
			}
		}

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_�J���[�̐ݒ�
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		// ���_�f�[�^���A�����b�N����
		m_pVtxBuff->Unlock();
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CFade::Draw(void)
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
	pDevice->SetTexture(0, m_pTex);
	// �|���S���`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);
}

// ----------------------------------------
// ��ʑJ�ڐݒ菈��
// ----------------------------------------
void CFade::SetFade(CManager::MODE Mode)
{
	m_fade = FADE_OUT;
	m_modeNext = Mode;
	m_col = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);	// ������ʁi����)
}

// ----------------------------------------
// ��ʑJ�ڎ擾����
// ----------------------------------------
CFade::FADE CFade::GetFade(void)
{
	return m_fade;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CFade::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���[�̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/fade000.png", &m_pTex);

	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CFade::UnLoad(void)
{
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}