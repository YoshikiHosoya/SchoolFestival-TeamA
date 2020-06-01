// ----------------------------------------
//
// pause�����̐���[pause.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "pause.h"
#include "keyboard.h"
#include "fade.h"
#include "game.h"
#include "manager.h"
#include "title.h"

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
LPDIRECT3DTEXTURE9 CPause::m_pTex = {};
D3DXVECTOR3 CPause::m_pos = {};
D3DXVECTOR2 CPause::m_size = {};
bool CPause::m_bPause = false;
// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CPause::CPause() : CScene::CScene(ACTOR_PAUSE_UI, LAYER_UI)
{
	m_aScene_Two = NULL;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CPause::~CPause()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CPause::Init(void)
{
	m_aScene_Two = new CScene_TWO;
	m_aScene_Two->SetSize(m_size);
	m_aScene_Two->Init();
	m_aScene_Two->SetPosition(m_pos);
	m_aScene_Two->BindTexture(m_pTex);
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CPause::Uninit(void)
{
	if (m_aScene_Two != NULL)
	{
		m_aScene_Two->Uninit();
		delete m_aScene_Two;
		m_aScene_Two = NULL;
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CPause::Update(void)
{
	if (m_aScene_Two != NULL)
	{
		if (CManager::GetMode() == CManager::MODE_TITLE && CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_FREE)
		{
			m_aScene_Two->Update();
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CPause::Draw(void)
{
	// NULL�`�F�b�N
	if (m_aScene_Two != NULL)
	{
		// �|�[�Y��Ԃ���Ȃ��Ƃ�
		if (m_bPause == false)
		{
			// �^�C�g�����[�h��������
			if (CManager::GetMode() == CManager::MODE_TITLE && CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_FREE)
			{
				m_aScene_Two->Draw();
			}
			//// �Q�[�����[�h��������
			else if (CManager::GetMode() == CManager::MODE_GAME)
			{
				m_aScene_Two->Draw();
			}
		}
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CPause::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[72] =
	{
		"data/TEXTURE/PAUSE/Pause_ui.png",
	};
	// �ʒu�����
	D3DXVECTOR3 pos =
	{
		D3DXVECTOR3(1100.0f,600,0.0f),
	};
	// �T�C�Y�����
	D3DXVECTOR2 size =
	{
		D3DXVECTOR2(200.0f,30.0f),
	};

	// �e�N�X�`���[����������
	if (strcmp(TexData, "") != 0)
	{
		/* �e�N�X�`���[�̃��[�h */
		D3DXCreateTextureFromFile(pDevice, TexData, &m_pTex);
		/* �ʒu�E�T�C�Y�� �^�C�v�̃��[�h */
		m_pos = pos;
		m_size = size;
	}

	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CPause::UnLoad(void)
{
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}


// ----------------------------------------
// �쐬����
// ----------------------------------------
CPause * CPause::Create(void)
{
	// �ϐ��錾
	CPause * pPause;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pPause = new CPause();
	// ����������
	pPause->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pPause;
}

// ------------------------------------------
// ��Ԑݒ�
// ------------------------------------------
void CPause::SetPause(bool bPause)
{
	m_bPause = bPause;
}

// ------------------------------------------
// ��Ԏ擾
// ------------------------------------------
bool CPause::GetPause(void)
{
	return m_bPause;
}