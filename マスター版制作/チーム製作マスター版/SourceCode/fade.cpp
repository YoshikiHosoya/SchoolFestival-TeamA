//=============================================================================
//
// �t�F�[�h���� [fade.cpp]
//
//=============================================================================
#include "fade.h"
#include "renderer.h"
#include "game.h"
#include "GameManager.h"
#include "ResultManager.h"
#include "map.h"
#include "Player.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define	TEXTURE_FADE					"data/TEXTURE/fade000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define FADE_COLOR_WHITE				(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))
#define WAPE_SPEED						(50.0f)
#define FADE_ALPHADAMPING_MODE			(0.05f)
#define FADE_ALPHADAMPING_STAGE			(0.02f)

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
	m_pos = SCREEN_CENTER_POS;
	m_fadeState = FADESTATE::FADESTATE_NONE;
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
	if (m_fadeState != FADESTATE::FADESTATE_NONE)
	{
		//�t�F�[�h�̃^�C�v�œ�����ς���
		switch (m_fadeType)
		{
		case CFADE::FADETYPE::FADETYPE_MODE:
		case CFADE::FADETYPE::FADETYPE_STAGE_CHANGE:
			//�z���C�g�A�E�g
			FadeWhiteOut();
			break;
		case CFADE::FADETYPE::FADETYPE_MAPMOVE:
			//���C�v
			FadeWipe();
			break;

		}
	}

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
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4, D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�X�V
	pVtx[0].pos = m_pos + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(+SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-SCREEN_WIDTH, +SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(+SCREEN_WIDTH, +SCREEN_HEIGHT, 0.0f);

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
// �t�F�[�h�̏�Ԏ擾
//=============================================================================
CFADE::FADESTATE CFADE::GetFadeState(void)
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
//=============================================================================
// �t�F�[�h�ɕK�v�ȏ��̏�����
//=============================================================================
void CFADE::ResetFadeParam()
{
	switch (m_fadeType)
	{
		//���[�h�̃t�F�[�h�̎�
	case CFADE::FADETYPE::FADETYPE_MODE:
		m_colorFade = FADE_COLOR_WHITE;
		m_pos = SCREEN_CENTER_POS;

		break;
		//�}�b�v�̃t�F�[�h��
	case CFADE::FADETYPE::FADETYPE_MAPMOVE:
		m_colorFade = BlackColor;
		m_pos = D3DXVECTOR3(-SCREEN_WIDTH, SCREEN_HEIGHT * 0.5f, 0.0f);
		break;

		//�}�b�v�̃t�F�[�h��
	case CFADE::FADETYPE::FADETYPE_STAGE_CHANGE:
		m_colorFade = ZeroColor;
		m_pos = SCREEN_CENTER_POS;

		break;
	}

	m_fadeState = FADESTATE::FADESTATE_OUT;

}
//=============================================================================
// �t�F�[�h�@�z���C�g�A�E�g���Ă��^�C�v
//=============================================================================
void CFADE::FadeWhiteOut()
{
	//�t�F�[�h�A�E�g��
	if (m_fadeState == FADESTATE::FADESTATE_OUT)
	{
		if (m_fadeType == CFADE::FADETYPE::FADETYPE_MODE)
		{
			//�ǂ�ǂ񔒂�
			m_colorFade.a += FADE_ALPHADAMPING_MODE;
		}
		else
		{
			//�ǂ�ǂ񔒂�
			m_colorFade.a += FADE_ALPHADAMPING_STAGE;

		}

		//���l��1��������
		if (m_colorFade.a >= 1.0f)
		{
			//a�l��1�ɌŒ�
			m_colorFade.a = 1.0f;

			//�t�F�[�h�C���ɐ؂�ւ�
			m_fadeState = FADESTATE::FADESTATE_IN;

			//�t�F�[�h�A�E�g���̐؂�ւ�����
			FadeOut();
		}
	}
	//�t�F�[�h�C����
	else if (m_fadeState == FADESTATE::FADESTATE_IN)
	{
		//�ǂ�ǂ񔖂�
		m_colorFade.a -= FADE_ALPHADAMPING_MODE;

		//���l��0�ɂȂ�����
		if (m_colorFade.a <= 0.0f)
		{
			//���l��0�ɌŒ�
			m_colorFade.a = 0.0f;

			//�t�F�[�h�I��
			m_fadeState = FADESTATE::FADESTATE_NONE;
			m_fadeType = FADETYPE::FADETYPE_NONE;
		}
	}
	UpdateVertex();
}

//=============================================================================
// �t�F�[�h�@���C�v���Ă����^�C�v
//=============================================================================
void CFADE::FadeWipe()
{
	//���C�v
	m_pos.x += WAPE_SPEED;

	//�t�F�[�h�A�E�g��
	if (m_fadeState == FADESTATE::FADESTATE_OUT)
	{
		//��ʑS�̂����܂�����
		if (m_pos.x > SCREEN_CENTER_POS.x)
		{
			//�t�F�[�h�C���ɐ؂�ւ�
			m_fadeState = FADESTATE::FADESTATE_IN;

			//�t�F�[�h�A�E�g���̐؂�ւ�����
			FadeOut();
		}
	}
	//�t�F�[�h�C����
	else if (m_fadeState == FADESTATE::FADESTATE_IN)
	{
		//���l��0�ɂȂ�����
		if (m_pos.x > SCREEN_WIDTH * 2)
		{
			//�t�F�[�h�I��
			m_fadeState = FADESTATE::FADESTATE_NONE;
			m_fadeType = FADETYPE::FADETYPE_NONE;
		}
	}
	UpdateVertex();
}
//=============================================================================
// �t�F�[�h�A�E�g���̏���
//=============================================================================
void CFADE::FadeOut()
{
	switch (m_fadeType)
	{
		//���[�h�̃t�F�[�h�̎�
	case CFADE::FADETYPE::FADETYPE_MODE:
		CManager::SetMode((CManager::MODE)m_NextID);
		break;
		//�}�b�v�̃t�F�[�h��
	case CFADE::FADETYPE::FADETYPE_MAPMOVE:
	case CFADE::FADETYPE::FADETYPE_STAGE_CHANGE:

		//�}�b�v�̃|�C���^�擾
		CMap *pMap = CManager::GetBaseMode()->GetMap();

		//�v���C���[�̃}�b�v�J�ڎ��̏���
		CManager::GetBaseMode()->GetPlayer()->MapChangePlayerRespawn();

		//�����_���[�ݒ菉����
		CManager::GetRenderer()->ResetRenderer();

		//nullcheck
		if (pMap)
		{
			//�}�b�v�X�V
			pMap->AllDelete();
			pMap->MapLoad((CMap::MAP)m_NextID);
			CManager::GetGame()->GetGameManager()->MapTransitionWaveSet((CMap::MAP)m_NextID);
		}

		//�V�[���Ǘ��ɂ���}�b�v�ύX���ɕK�v�Ȃ����̂�����
		CScene::MapChangeRelease();

		if (m_fadeType == CFADE::FADETYPE::FADETYPE_STAGE_CHANGE)
		{
			CManager::GetGame()->GetGameManager()->SetGameState(CGameManager::GAMESTATE::NORMAL);

		}
		break;

	}
}
//=============================================================================
// ���_�o�b�t�@�X�V
//=============================================================================
void CFADE::UpdateVertex()
{
	//�ϐ��錾
	VERTEX_2D *pVtx;

	//���_�o�b�t�@���b�N
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�X�V
	pVtx[0].pos = m_pos + D3DXVECTOR3(-SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(+SCREEN_WIDTH, -SCREEN_HEIGHT, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(-SCREEN_WIDTH, +SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(+SCREEN_WIDTH, +SCREEN_HEIGHT, 0.0f);

	//���_�J���[�X�V
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	//���_�o�b�t�@�A�����b�N
	m_pVtxBuffFade->Unlock();
}
