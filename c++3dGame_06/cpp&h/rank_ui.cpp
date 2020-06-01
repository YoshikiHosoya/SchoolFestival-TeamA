// ----------------------------------------
//
// �����N�pui�����̐���[rank_ui.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "rank_ui.h"
#include "fade.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define RANK_UI "data/hackdoll3.png"

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
LPDIRECT3DTEXTURE9 CRank_ui::m_pTex[MAX_RANK_UI] = {};
D3DXVECTOR3 CRank_ui::m_pos[MAX_RANK_UI] = {};
D3DXVECTOR2 CRank_ui::m_size[MAX_RANK_UI] = {};
int CRank_ui::m_nSelect = 0;

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CRank_ui::CRank_ui() : CScene::CScene(ACTOR_RANK_UI, LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < MAX_RANK_UI; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
	m_nCntCol = 0;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CRank_ui::~CRank_ui()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CRank_ui::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_RANK_UI; nCnt++)
	{
		if (m_pTex[nCnt] != NULL)
		{
			m_aScene_Two[nCnt] = new CScene_TWO;
			m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
			m_aScene_Two[nCnt]->Init();
			m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
			m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);
			if (nCnt > 1)
			{
				// �X�R�A
				/*CTopscore * pTopscore = CTopscore::Create(
					m_aScene_Two[nCnt]->GetPosition() +
					D3DXVECTOR3(300.0f, 10.0f, 0.0f));
				pTopscore->SetTopscore(nCnt - 2);*/
			}
		}
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CRank_ui::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_RANK_UI; nCnt++)
	{
		if (m_pTex[nCnt] != NULL)
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
void CRank_ui::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_RANK_UI; nCnt++)
	{
		// �k���`�F�b�N
		if (m_pTex[nCnt] != NULL)
		{
			// ��ނɂ���ď�����ς���
			m_aScene_Two[nCnt]->Update();
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CRank_ui::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_RANK_UI; nCnt++)
	{
		if (m_pTex[nCnt] != NULL)
		{
			m_aScene_Two[nCnt]->Draw();
		}
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CRank_ui::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[MAX_RANK_UI][72] =
	{
		{"data/TEXTURE/RANKING/ranking_name.png"},
		{"data/TEXTURE/RANKING/ranking_frame.png"},
		{"data/TEXTURE/RANKING/1st.png"},
		{"data/TEXTURE/RANKING/2nd.png"},
		{"data/TEXTURE/RANKING/3rd.png"},
		{"data/TEXTURE/RANKING/4th.png"},
		{"data/TEXTURE/RANKING/5th.png"},
	};
	// �ʒu�����
	D3DXVECTOR3 pos[MAX_RANK_UI] =
	{
		{ D3DXVECTOR3(SCREEN_WIDTH * 0.5f,80.0f,0.0f) },
		{ D3DXVECTOR3(SCREEN_WIDTH * 0.5f,400.0f,0.0f) },
		{ D3DXVECTOR3(300.0f,200.0f,0.0f)},
		{ D3DXVECTOR3(300.0f,300,0.0f)},
		{ D3DXVECTOR3(300.0f,400.0f,0.0f)},
		{ D3DXVECTOR3(300.0f,500.0f,0.0f)},
		{ D3DXVECTOR3(300.0f,600.0f,0.0f)},
	};
	// �T�C�Y�����
	D3DXVECTOR2 size[MAX_RANK_UI] =
	{
		{ D3DXVECTOR2(500.0f,150.0f) },
		{ D3DXVECTOR2(700.0f,500.0f) },
		{ D3DXVECTOR2(150.0f,100.0f) },
		{ D3DXVECTOR2(150.0f,100.0f) },
		{ D3DXVECTOR2(150.0f,100.0f) },
		{ D3DXVECTOR2(150.0f,100.0f)},
		{ D3DXVECTOR2(150.0f,100.0f)},
	};

	for (int nCnt = 0; nCnt < MAX_RANK_UI; nCnt++)
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
void CRank_ui::UnLoad(void)
{
	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < MAX_RANK_UI; nCnt++)
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
CRank_ui * CRank_ui::Create(void)
{
	// �ϐ��錾
	CRank_ui * pRank_ui;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pRank_ui = new CRank_ui();
	// ����������
	pRank_ui->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pRank_ui;
}
