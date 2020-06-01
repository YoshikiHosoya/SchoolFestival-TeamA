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
#include "tutorial_ui.h"
#include "fade.h"
#include "input.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define TUTORIAL_UI_ANIM (2)
#define TUTORIAL_UI_SPLIT (1.0f / TUTORIAL_UI_ANIM)

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
LPDIRECT3DTEXTURE9	CTutorial_ui::m_pTex[TUTORIAL_UI_MAX] = {};
D3DXVECTOR3			CTutorial_ui::m_pos[TUTORIAL_UI_MAX] = {};
D3DXVECTOR2			CTutorial_ui::m_size[TUTORIAL_UI_MAX] = {};

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CTutorial_ui::CTutorial_ui() : CScene::CScene(ACTOR_TUTORIAL_UI, LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < TUTORIAL_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
	m_fMult = 1.0f;
	m_fAdd = 0.001f;
	m_nCntCol = 0;
	m_nSelect = 0;
	m_fAnim = 0;
	m_TutorialState = TUTORIAL_STATE_FIRST;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CTutorial_ui::~CTutorial_ui()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTutorial_ui::Init(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
		m_aScene_Two[TUTORIAL_UI_MANUAL]->SetTex(D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f), D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
		m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CTutorial_ui::Uninit(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI_MAX; nCnt++)
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
void CTutorial_ui::Update(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// ��ނɂ���ď�����ς���
			Various(nCnt);
			// ��ނɂ���ď�����ς���
			m_aScene_Two[nCnt]->Update();
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CTutorial_ui::Draw(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			m_aScene_Two[TUTORIAL_UI_MANUAL]->Draw();

			if (m_TutorialState == TUTORIAL_STATE_FIRST)
			{
				m_aScene_Two[TUTORIAL_UI_CLICK_R]->Draw();
			}

			if (m_TutorialState == TUTORIAL_STATE_SECOND)
			{
				m_aScene_Two[TUTORIAL_UI_CLICK_L]->Draw();
				m_aScene_Two[TUTORIAL_UI_START]->Draw();
			}

			// ��ނɂ���ď�����ς���
			//m_aScene_Two[nCnt]->Draw();
		}
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CTutorial_ui::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[TUTORIAL_UI_MAX][72] =
	{
		"data/TEXTURE/TUTORIAL/0Tutorial_Manual.png",
		"data/TEXTURE/TUTORIAL/ClickBottunR.png",
		"data/TEXTURE/TUTORIAL/ClickBottunL.png",
		"data/TEXTURE/TUTORIAL/ClickBottunS.png"
	};
	// �ʒu�����
	D3DXVECTOR3 pos[TUTORIAL_UI_MAX] =
	{
		D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),
		D3DXVECTOR3(1200.0f,650,0.0f),
		D3DXVECTOR3(50.0f,650,0.0f),
		D3DXVECTOR3(1200.0f,650,0.0f)
	};
	// �T�C�Y�����
	D3DXVECTOR2 size[TUTORIAL_UI_MAX] =
	{
		D3DXVECTOR2(SCREEN_WIDTH,SCREEN_HEIGHT),
		D3DXVECTOR2(100.0f,100.0f),
		D3DXVECTOR2(100.0f,100.0f),
		D3DXVECTOR2(150.0f,150.0f)
	};

	for (int nCnt = 0; nCnt < TUTORIAL_UI_MAX; nCnt++)
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
void CTutorial_ui::UnLoad(void)
{
	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < TUTORIAL_UI_MAX; nCnt++)
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
CTutorial_ui * CTutorial_ui::Create(void)
{
	// �ϐ��錾
	CTutorial_ui * pTutorial_ui;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pTutorial_ui = new CTutorial_ui();
	// ����������
	pTutorial_ui->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pTutorial_ui;
}

// ----------------------------------------
// ��ޕʂ̏���
// ----------------------------------------
void CTutorial_ui::Various(int nCnt)
{
	// �������̏ꍇ
	if (nCnt == TUTORIAL_UI_MANUAL)
	{
		//�L�[�{�[�h
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RIGHT))
		{
			m_nSelect++;
			m_TutorialState = TUTORIAL_STATE_SECOND;
			// �G���^�[��
			//CManager::GetSound()->PlaySound(CSound::LABEL_SE_1);

			// �I����ʂ�
			if (m_nSelect >= 2)
			{
				// ��ʑJ�ڂ̏�Ԃ��J�ڂ��Ă��Ȃ���Ԃ�������
				if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
				{
					CManager::GetFade()->SetFade(CManager::MODE_GAME);
				}
			}
			// ���̃y�[�W��
			else
			{
				m_aScene_Two[TUTORIAL_UI_MANUAL]->SetTex(
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f),
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
			}
		}

		else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_LEFT))
		{
			m_nSelect--;
			m_TutorialState = TUTORIAL_STATE_FIRST;
			// �G���^�[��
			//CManager::GetSound()->PlaySound(CSound::LABEL_SE_1);

			// �I����ʂ�
			if (m_nSelect < 0)
			{
				m_nSelect = 0;
			}
			// �O�̃y�[�W��
			else
			{
				m_aScene_Two[TUTORIAL_UI_MANUAL]->SetTex(
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f),
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
			}
		}

		//�W���C�X�e�B�b�N �\���L�[
		if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_RIGHT))
		{
			m_nSelect++;
			m_TutorialState = TUTORIAL_STATE_SECOND;
			// �G���^�[��
			//CManager::GetSound()->PlaySound(CSound::LABEL_SE_1);

			// �I����ʂ�
			if (m_nSelect >= 2)
			{
				// ��ʑJ�ڂ̏�Ԃ��J�ڂ��Ă��Ȃ���Ԃ�������
				if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
				{
					CManager::GetFade()->SetFade(CManager::MODE_GAME);
				}
			}
			// ���̃y�[�W��
			else
			{
				m_aScene_Two[TUTORIAL_UI_MANUAL]->SetTex(
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f),
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
			}
		}
		else if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_LEFT))
		{
			m_nSelect--;
			m_TutorialState = TUTORIAL_STATE_FIRST;
			// �G���^�[��
			//CManager::GetSound()->PlaySound(CSound::LABEL_SE_1);

			// �I����ʂ�
			if (m_nSelect < 0)
			{
				m_nSelect = 0;
			}
			// �O�̃y�[�W��
			else
			{
				m_aScene_Two[TUTORIAL_UI_MANUAL]->SetTex(
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f),
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
			}
		}

		//���������񖇖ڂ�������
		if (m_nSelect == 1)
		{
			if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_START))
			{
				CManager::GetFade()->SetFade(CManager::MODE_GAME);
			}
		}

	}

	// �N���b�N
	else if (nCnt == TUTORIAL_UI_CLICK_R)
	{
		// �J�E���g�J���[�A�b�v
		m_nCntCol++;
		// �\����Ԃ�
		if (m_nCntCol % 40 == 0)
		{
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		// ��\����Ԃ�
		else if (m_nCntCol % 20 == 0)
		{
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
	// �N���b�N
	else if (nCnt == TUTORIAL_UI_CLICK_L)
	{
		// �J�E���g�J���[�A�b�v
		m_nCntCol++;
		// �\����Ԃ�
		if (m_nCntCol % 40 == 0)
		{
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		// ��\����Ԃ�
		else if (m_nCntCol % 20 == 0)
		{
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
	// �N���b�N
	else if (nCnt == TUTORIAL_UI_START)
	{
		// �J�E���g�J���[�A�b�v
		m_nCntCol++;
		// �\����Ԃ�
		if (m_nCntCol % 40 == 0)
		{
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		// ��\����Ԃ�
		else if (m_nCntCol % 20 == 0)
		{
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}
}
