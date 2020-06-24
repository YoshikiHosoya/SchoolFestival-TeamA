//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
//
//=============================================================================
#include "fade.h"
#include "renderer.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_FADE	"data/TEXTURE/fade000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define FADE_COLOR	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
//=============================================================================
// ����������
//=============================================================================
void CFADE::InitFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_colorFade = D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f);
	m_fadeState = FADE_NONE;
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FADE,		// �t�@�C���̖��O
		&m_pTextureFade);	// �ǂݍ��ރ������[
							// ���_���̐ݒ�
	MakeVertexFade();
}

//=============================================================================
// �I������
//=============================================================================
void CFADE::UninitFade(void)
{
	// �e�N�X�`���̊J��
	if (m_pTextureFade != NULL)
	{
		m_pTextureFade->Release();
		m_pTextureFade = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void CFADE::UpdateFade(void)
{
	VERTEX_2D *pVtx;
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);
	if (m_fadeState == FADE_IN)
	{
			m_colorFade.a -= 0.01f;
			if (m_colorFade.a <= 0.0f)
			{
				m_colorFade.a = 0.0f;
				m_fadeState = FADE_NONE;
			}

	}
	else if (m_fadeState == FADE_OUT)
	{
		m_colorFade.a += 0.05f;
		if (m_colorFade.a >= 1.0f)
		{
			m_colorFade.a = 1.0f;
			m_fadeState = FADE_IN;
			if (m_modeNext != CManager::MODE_NONE)
			{
				CManager::SetGameMode(m_modeNext);
			}
			else
			{

			}
		}
	}
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;
	m_pVtxBuffFade->Unlock();
}

//=============================================================================
// �^�C�g�����
//=============================================================================
void CFADE::DrawFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTextureFade);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
void CFADE::MakeVertexFade(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	VERTEX_2D *pVtx;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4 * 1, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);


	// ���_�J���[�̐ݒ�
	pVtx[0].rhm = 1.0f;
	pVtx[1].rhm = 1.0f;
	pVtx[2].rhm = 1.0f;
	pVtx[3].rhm = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuffFade->Unlock();
}

//=============================================================================
// �t�F�[�h�̏�Ԑݒ�
//=============================================================================
void CFADE::SetFade(CManager::GAME_MODE modeNext)
{
	if (m_fadeState == FADE_NONE)
	{
		m_fadeState = FADE_OUT;
		m_modeNext = modeNext;
		m_colorFade = FADE_COLOR;
	}
}
//=============================================================================
// �t�F�[�h�̏�Ԏ擾
//=============================================================================
CFADE::FADE CFADE::GetFadeState(void)
{
	return m_fadeState;
}
//=============================================================================
// �t�F�[�h�̃N���G�C�g
//=============================================================================
CFADE *CFADE::CreateFade(void)
{
	CFADE *pfade;
	pfade = new CFADE;
	pfade->InitFade();
	return pfade;
}
