// ----------------------------------------
//
// �|�[�Y�pui�����̐���[title_ui.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "title_ui.h"
#include "fade.h"
#include "title.h"

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
LPDIRECT3DTEXTURE9 CTitle_ui::m_pTex[TITLE_UI_MAX] = {};
D3DXVECTOR3 CTitle_ui::m_pos[TITLE_UI_MAX] = {};
D3DXVECTOR2 CTitle_ui::m_size[TITLE_UI_MAX] = {};
CTitle_ui::TITLE_UI CTitle_ui::m_type[TITLE_UI_MAX] = {};
CSelectMark * CTitle_ui::m_pSelectMark = NULL;
bool CTitle_ui::m_bUse = false;
// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CTitle_ui::CTitle_ui() : CScene::CScene(ACTOR_TITLE_UI, LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
	m_fMult = 1.0f;
	m_fAdd = 0.001f;
	m_bCol_a = false;
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	//m_bUse = false;
	m_Select = TITLESELECT_NEWGAME;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CTitle_ui::~CTitle_ui()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTitle_ui::Init(void)
{
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
		m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);
	}

	//// �I�����Ă�UI�Ɉ��t����
	//m_pSelectMark = CSelectMark::Create(D3DXVECTOR3(150.0f, 350.0f, 0.0f),
	//	0.0f,
	//	D3DXVECTOR2(125.0f, 30.0f),
	//	D3DXCOLOR(1.0f, 0.0f, 0.0f, 0.5f),
	//	CSelectMark::MARK_ARROW);
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CTitle_ui::Uninit(void)
{
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
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
void CTitle_ui::Update(void)
{
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			if (CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_TITLE)
			{
				// ��ނɂ���ď�����ς���
				Various(nCnt);
			}
			// ��ނɂ���ď�����ς���
			m_aScene_Two[nCnt]->Update();

			//�^�C�g�����[�h���`���[�g���A���ɂȂ�����
			if (CManager::GetTitle()->GetMode() == CManager::GetTitle()->TITLEMODE_TUTORIAL)
			{
				//������
				Transparency(nCnt);
			}

			if (m_bUse == true)
			{
				Release();
			}
		}
	}

	//// �I���}�[�N����
	//if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_DOWN))
	//{
	//	if (m_pSelectMark->GetCount() < 2)
	//	{
	//		m_pSelectMark->SetPos(m_pSelectMark->GetPos() + D3DXVECTOR3(0.0f, 50.0f, 0.0f));
	//		m_pSelectMark->CalculationCount(1);
	//	}

	//	else if (m_pSelectMark->GetCount() >= 2)
	//	{
	//		m_pSelectMark->SetPos(D3DXVECTOR3(150.0f, 350.0f, 0.0f));
	//		m_pSelectMark->SetCount(0);
	//	}

	//	// �}�[�N��������
	//	SetTitleModeDown();
	//}

	//// �I���}�[�N�㏸
	//else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_UP))
	//{
	//	if (m_pSelectMark->GetCount() > -1)
	//	{
	//		m_pSelectMark->SetPos(m_pSelectMark->GetPos() + D3DXVECTOR3(0.0f, -50.0f, 0.0f));
	//		m_pSelectMark->CalculationCount(-1);
	//	}

	//	if (m_pSelectMark->GetCount() <= -1)
	//	{
	//		m_pSelectMark->SetPos(D3DXVECTOR3(150.0f, 450.0f, 0.0f));
	//		m_pSelectMark->SetCount(2);
	//	}

	//	// �}�[�N���グ��
	//	SetTitleModeUp();
	//}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CTitle_ui::Draw(void)
{
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
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
HRESULT CTitle_ui::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[TITLE_UI_MAX][72] =
	{
		"data/TEXTURE/TITLE/Title00.png",
		"data/TEXTURE/TITLE/newgame.png",
	};
	// �ʒu�����
	D3DXVECTOR3 pos[TITLE_UI_MAX] =
	{
		D3DXVECTOR3(640.0f,150,0.0f),
		D3DXVECTOR3(640.0f,650,0.0f),
	};
	// �T�C�Y�����
	D3DXVECTOR2 size[TITLE_UI_MAX] =
	{
		D3DXVECTOR2(700.0f,200.0f),
		D3DXVECTOR2(500.0f,40.0f),
	};
	//
	TITLE_UI type[TITLE_UI_MAX] =
	{
		TITLE_UI_NAME,
		TITLE_UI_NEWGAME,
	};

	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
	{
		// �e�N�X�`���[����������
		if (strcmp(TexData[nCnt], "") != 0)
		{
			/* �e�N�X�`���[�̃��[�h */
			D3DXCreateTextureFromFile(pDevice, TexData[nCnt], &m_pTex[nCnt]);
			/* �ʒu�E�T�C�Y�� �^�C�v�̃��[�h */
			m_pos[nCnt] = pos[nCnt];
			m_size[nCnt] = size[nCnt];
			m_type[nCnt] = type[nCnt];
		}
	}
	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CTitle_ui::UnLoad(void)
{
	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < TITLE_UI_MAX; nCnt++)
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
CTitle_ui * CTitle_ui::Create(void)
{
	// �ϐ��錾
	CTitle_ui * pTitle_ui;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pTitle_ui = new CTitle_ui();
	// ����������
	pTitle_ui->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pTitle_ui;
}

// ----------------------------------------
// ��ޕʂ̏���
// ----------------------------------------
void CTitle_ui::Various(int nCnt)
{
	// �^�C�g���̖��O�̏ꍇ
	if (nCnt == TITLE_UI_NAME)
	{
		D3DXVECTOR2 size = m_size[nCnt];	// �T�C�Y�̎擾
													// ���Z�����Z
		if (m_fMult >= 1.1f || m_fMult <= 0.9f)
		{
			m_fAdd *= -1;
		}
		// �T�C�Y�̕ω�
		m_fMult += m_fAdd;
		size *= m_fMult;

		// �T�C�Y�̐ݒ�
		m_aScene_Two[nCnt]->SetSize(size);
	}

	else if (nCnt == TITLE_UI_NEWGAME)
	{
		if (m_Col.a > 0.1f && m_bCol_a == false)
		{
			m_Col.a -= 0.01f;
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Col.a));
			if (m_Col.a <= 0.1f)
			{
				m_bCol_a = true;
			}
		}
		else if (m_Col.a < 1.0f && m_bCol_a == true)
		{
			m_Col.a += 0.01f;
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, m_Col.a));
			if (m_Col.a >= 1.0f)
			{
				m_bCol_a = false;
			}
		}

		// �T�C�Y�̐ݒ�
		//m_aScene_Two[nCnt]->SetCol(D3DXCOLOR (1.0f, 1.0f, 1.0f, m_fCntCol));
	}
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTitle_ui::Transparency(int nCnt)
{
	//���X�ɓ����ɂ���
	m_Col.a -= 0.005f;
	//�F�̍X�V
	m_aScene_Two[nCnt]->SetCol(m_Col);

	//�����x��0�ȉ��ɂȂ�����폜
	if (m_Col.a <= 0.0f)
	{
		m_bUse = true;
	}
}

// ----------------------------------------
// �t���O�̎擾
// ----------------------------------------
bool CTitle_ui::GetFlag(void)
{
	return m_bUse;
}

// ----------------------------------------
// ���[�h�̑I��ݒ�
// ----------------------------------------
void CTitle_ui::SetTitleModeUp(void)
{
	switch (m_Select)
	{
	case TITLESELECT_NEWGAME:
		break;

	default:
		break;
	}
}

// ----------------------------------------
// ���[�h�̑I��ݒ�
// ----------------------------------------
void CTitle_ui::SetTitleModeDown(void)
{
	switch (m_Select)
	{
	case TITLESELECT_NEWGAME:
	//	m_Select = TITLESELECT_CHAPTERS;
		break;

	default:
		break;
	}
}


// ----------------------------------------
//
// ----------------------------------------
void CTitle_ui::TitleMode(void)
{
	switch (m_Select)
	{
	case TITLESELECT_NEWGAME:

		break;

	default:
		break;
	}
}

// ----------------------------------------
// �I�����ꂽ�����擾
// ----------------------------------------
CTitle_ui::TITLESELECT CTitle_ui::GetSelect(void)
{
	return m_Select;
}

