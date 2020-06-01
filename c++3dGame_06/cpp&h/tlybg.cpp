// ----------------------------------------
//
// �V�[�������̐���[tlybg.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "tlybg.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define TLYBG "data/.png"

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
LPDIRECT3DTEXTURE9 CTlyBg::m_pTex[CManager::MODE_MAX][MAX_TLYBG] = {};
CManager::MODE CTlyBg::m_mode = CManager::MODE_TITLE;
D3DXVECTOR3 CTlyBg::m_pos[CManager::MODE_MAX][MAX_TLYBG] = {};
D3DXVECTOR2 CTlyBg::m_size[CManager::MODE_MAX][MAX_TLYBG] = {};

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CTlyBg::CTlyBg() : CScene::CScene(ACTOR_BG, LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < MAX_TLYBG; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CTlyBg::~CTlyBg()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTlyBg::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_TLYBG; nCnt++)
	{
		if (m_pTex[m_mode][nCnt] != NULL)
		{
			m_aScene_Two[nCnt] = new CScene_TWO;
			m_aScene_Two[nCnt]->SetSize(m_size[m_mode][nCnt]);
			m_aScene_Two[nCnt]->Init();
			m_aScene_Two[nCnt]->SetPosition(m_pos[m_mode][nCnt]);
			m_aScene_Two[nCnt]->BindTexture(m_pTex[m_mode][nCnt]);
		}
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CTlyBg::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_TLYBG; nCnt++)
	{
		if (m_pTex[m_mode][nCnt] != NULL)
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
void CTlyBg::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_TLYBG; nCnt++)
	{
		if (m_pTex[m_mode][nCnt] != NULL)
		{
			m_aScene_Two[nCnt]->Update();
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CTlyBg::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_TLYBG; nCnt++)
	{
		if (m_pTex[m_mode][nCnt] != NULL)
		{
			m_aScene_Two[nCnt]->Draw();
		}
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CTlyBg::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[CManager::MODE_MAX][MAX_TLYBG][36] =
	{
		{ "data/TEXTURE/BG/0Title00.png" },		// �Q�[���p�̔w�i
		{ "data/TEXTURE/BG/0Title00.png" },		// �^�C�g���p�̔w�i
		//{ "data/TEXTURE/BG/0Title00.png" },		// �����L���O�̔w�i
	};
	// �ʒu�����
	D3DXVECTOR3 pos[CManager::MODE_MAX][MAX_TLYBG] =
	{
		{ D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f) },
		{ D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f) },
		//{ D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f) },
	};
	// �T�C�Y�����
	D3DXVECTOR2 size[CManager::MODE_MAX][MAX_TLYBG] =
	{
		{ D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT) },
		{ D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT) },
		//{ D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT) },
	};

	// �ǂݍ���
	for (int nCntMode = 0; nCntMode < CManager::MODE_MAX; nCntMode++)
	{
		for (int nCnt = 0; nCnt < MAX_TLYBG; nCnt++)
		{
			// �e�N�X�`���[����������
			if (strcmp(TexData[nCntMode][nCnt], "") != 0)
			{
				D3DXCreateTextureFromFile(pDevice, TexData[nCntMode][nCnt], &m_pTex[nCntMode][nCnt]);
				/* �ʒu�E�T�C�Y�̃��[�h */
				m_pos[nCntMode][nCnt] = pos[nCntMode][nCnt];
				m_size[nCntMode][nCnt] = size[nCntMode][nCnt];
			}
		}
	}

	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CTlyBg::UnLoad(void)
{
	// �e�N�X�`���̊J��
	for (int nCntMode = 0; nCntMode < CManager::MODE_MAX; nCntMode++)
	{
		for (int nCnt = 0; nCnt < MAX_TLYBG; nCnt++)
		{
			if (m_pTex[nCntMode][nCnt] != NULL)
			{
				m_pTex[nCntMode][nCnt]->Release();
				m_pTex[nCntMode][nCnt] = NULL;
			}
		}
	}
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CTlyBg * CTlyBg::Create(CManager::MODE mode)
{
	// �ϐ��錾
	CTlyBg * pTlyBg;
	// ���[�h���ݒ�
	m_mode = mode;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pTlyBg = new CTlyBg();
	// ����������
	pTlyBg->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pTlyBg;
}