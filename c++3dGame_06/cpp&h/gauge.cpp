// ----------------------------------------
//
// �|�[�Y�pui�����̐���[tutorial_ui.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "gauge.h"
#include "fade.h"
#include "input.h"
#include "player.h"
#include "game.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define GAUGE_X				(500)		//�Q�[�W�̉���
#define GAUGE_Y				(25)			//�Q�[�W�̏c��

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
LPDIRECT3DTEXTURE9	CGauge::m_pTex[GAUGE_MAX] = {};
D3DXVECTOR3			CGauge::m_pos[GAUGE_MAX] = {};
D3DXVECTOR2			CGauge::m_size[GAUGE_MAX] = {};

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CGauge::CGauge() : CScene::CScene(ACTOR_GAME_UI, LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < GAUGE_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}

	m_nMaxGauge = GAUGE_X;  //�Q�[�W�̃`���[�W�ʂ̏����l
	m_fTex = 1.0f;
	m_fAbilityTime = 10.0f;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CGauge::~CGauge()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CGauge::Init(void)
{
	for (int nCnt = 0; nCnt < GAUGE_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
		m_aScene_Two[GAUGE_GAUGE]->SetTex(D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
		m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CGauge::Uninit(void)
{
	for (int nCnt = 0; nCnt < GAUGE_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			m_aScene_Two[nCnt]->Uninit();
			delete m_aScene_Two[nCnt];
			m_aScene_Two[nCnt] = NULL;
		}
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CGauge::Update(void)
{
	for (int nCnt = 0; nCnt < GAUGE_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// ��ނɂ���ď�����ς���
			Various(GAUGE_GAUGE);
			// ��ނɂ���ď�����ς���
			//m_aScene_Two[nCnt]->Update();
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CGauge::Draw(void)
{
	for (int nCnt = 0; nCnt < GAUGE_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// ��ނɂ���ď�����ς���
			m_aScene_Two[nCnt]->Draw();
		}
	}

}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CGauge::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[GAUGE_MAX][72] =
	{
		"data/TEXTURE/UI/Gauge.png",
		"data/TEXTURE/UI/frame.png",
	};
	// �ʒu�����
	D3DXVECTOR3 pos[GAUGE_MAX] =
	{
		D3DXVECTOR3(640 - (GAUGE_X/2),600,0),
		D3DXVECTOR3(640,600,0),
	};
	// �T�C�Y�����
	D3DXVECTOR2 size[GAUGE_MAX] =
	{
		D3DXVECTOR2(GAUGE_X,GAUGE_Y),
		D3DXVECTOR2(GAUGE_X + 30,GAUGE_Y),
	};
	for (int nCnt = 0; nCnt < GAUGE_MAX; nCnt++)
	{
		// �e�N�X�`���[����������
		if (strcmp(TexData[nCnt], "") != 0)
		{
			/* �e�N�X�`���[�̃��[�h */
			D3DXCreateTextureFromFile(pDevice, TexData[nCnt], &m_pTex[nCnt]);
			/* �ʒu�E�T�C�Y�̃��[�h */
			m_pos[nCnt] = pos[nCnt];
			m_size[nCnt] = size[nCnt];
		}
	}
	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CGauge::UnLoad(void)
{
	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < GAUGE_MAX; nCnt++)
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
CGauge * CGauge::Create(void)
{
	// �ϐ��錾
	CGauge * pGauge;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pGauge = new CGauge();
	// ����������
	pGauge->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pGauge;
}

// ----------------------------------------
// ��ޕʂ̏���
// ----------------------------------------
void CGauge::Various(int nCnt)
{
	if (nCnt == GAUGE_GAUGE)
	{
		float fWidth = (float)m_nMaxGauge * (m_fAbilityTime) / 10;

		if (fWidth > 0)
		{
			m_fAbilityTime -= (1.0f/120.0f);
			D3DXVECTOR2 size(fWidth, GAUGE_Y/2);
			m_aScene_Two[GAUGE_GAUGE]->SetGaugeSize(size);

			m_fTex -= 0.0006f;

			m_aScene_Two[GAUGE_GAUGE]->SetTex(D3DXVECTOR2(0.0f, 1.0f), D3DXVECTOR2(m_fTex, 0.0f));
		}

		if (fWidth <= 0)
		{
			Release();
		}
	}
}
