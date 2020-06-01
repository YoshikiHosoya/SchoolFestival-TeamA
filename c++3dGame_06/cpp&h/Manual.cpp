// ----------------------------------------
//
// �}�j���A�������̐���[manual.h]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "manual.h"
#include "input.h"
#include "pause.h"
#include "manager.h"
#include "fade.h"
#include "debugproc.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define TUTORIAL_UI_ANIM (3)
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
LPDIRECT3DTEXTURE9	CManual::m_pTex[MANUAL_TYPE_MAX] = {};
D3DXVECTOR3			CManual::m_pos[MANUAL_TYPE_MAX] = {};
D3DXVECTOR2			CManual::m_size[MANUAL_TYPE_MAX] = {};

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CManual::CManual() : CScene::CScene(ACTOR_MANUAL_UI, LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
	m_fMult = 1.0f;
	m_fAdd = 0.001f;
	m_nCntCol = 0;
	m_nSelect = 0;
	m_fAnim = 0;
	m_ManualState = MANUAL_STATE_PAUSE;
	m_ManualSelect = MANUAL_SELECT_PAGE_CONTROLLER;
	m_nPauseCount = MANUAL_TYPE_MANUAL;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CManual::~CManual()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CManual::Init(void)
{
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
		if (nCnt == MANUAL_TYPE_PICTURE)
		{
			m_aScene_Two[MANUAL_TYPE_PICTURE]->SetTex(D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f), D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
		}
		m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CManual::Uninit(void)
{
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
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
void CManual::Update(void)
{
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			if (CPause::GetPause() == true)
			{


				// ��ނɂ���ď�����ς���
				m_aScene_Two[nCnt]->Update();
			}
		}
	}

	// ��ނɂ���ď�����ς���
	Various(0);

	CDebugproc::Print("�|�[�Y���̑I�� %d\n" ,m_nPauseCount);
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CManual::Draw(void)
{
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			m_aScene_Two[MANUAL_TYPE_BG]->Draw();
			m_aScene_Two[MANUAL_TYPE_PAUSEUI]->Draw();
			m_aScene_Two[MANUAL_TYPE_CROSSBUTTON]->Draw();
			m_aScene_Two[MANUAL_TYPE_ABUTTON]->Draw();

			if (m_ManualState == MANUAL_STATE_PAUSE)
			{
				m_aScene_Two[MANUAL_TYPE_MANUAL]->Draw();
				m_aScene_Two[MANUAL_TYPE_RESUME]->Draw();
				m_aScene_Two[MANUAL_TYPE_GOTITLE]->Draw();
			}

			else if (m_ManualState = MANUAL_STATE_MANUAL)
			{
				m_aScene_Two[MANUAL_TYPE_PAUSE]->Draw();
				m_aScene_Two[MANUAL_TYPE_PICTURE]->Draw();
			}
		}
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CManual::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[MANUAL_TYPE_MAX][72] =
	{
		"data/TEXTURE/MANUAL/BG00.png",
		"data/TEXTURE/MANUAL/PAUSE00.png",
		"data/TEXTURE/MANUAL/BACK00.png",
		"data/TEXTURE/MANUAL/MANUAL00.png",
		"data/TEXTURE/MANUAL/RESUME00.png",
		"data/TEXTURE/MANUAL/TITLE00.png",
		"data/TEXTURE/MANUAL/PICTURE000.png",
		"data/TEXTURE/MANUAL/CROSSBUTTON00.png",
		"data/TEXTURE/MANUAL/ABUTTON00.png",

	};
	// �ʒu�����
	D3DXVECTOR3 pos[MANUAL_TYPE_MAX] =
	{
		D3DXVECTOR3(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,200.0f,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,300,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,300,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,400,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,500,0.0f),
		D3DXVECTOR3(SCREEN_WIDTH / 2,400,0.0f),
		D3DXVECTOR3(380.0f,550,0.0f),
		D3DXVECTOR3(900.0f,550,0.0f),
	};
	// �T�C�Y�����
	D3DXVECTOR2 size[MANUAL_TYPE_MAX] =
	{
		D3DXVECTOR2(SCREEN_WIDTH / 2,SCREEN_HEIGHT / 1.5),
		D3DXVECTOR2(400.0f,100.0f),
		D3DXVECTOR2(200.0f, 50.0f),
		D3DXVECTOR2(200.0f, 50.0f),
		D3DXVECTOR2(200.0f, 50.0f),
		D3DXVECTOR2(200.0f, 50.0f),
		D3DXVECTOR2(400.0f,300.0f),
		D3DXVECTOR2(50.0f,50.0f),
		D3DXVECTOR2(50.0f,50.0f),
	};

	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
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
void CManual::UnLoad(void)
{
	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < MANUAL_TYPE_MAX; nCnt++)
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
CManual * CManual::Create(void)
{
	// �ϐ��錾
	CManual * pTutorial_ui;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pTutorial_ui = new CManual();
	// ����������
	pTutorial_ui->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pTutorial_ui;
}

// ----------------------------------------
// ��ޕʂ̏���
// ----------------------------------------
void CManual::Various(int nCnt)
{
	//
	if (m_ManualState == MANUAL_STATE_PAUSE)
	{
		// �����������Ƃ��I�����Ă����Ԃ���̂��̂ɂ���
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_DOWN))
		{
			m_nPauseCount++;

			if (m_nPauseCount > MANUAL_TYPE_GOTITLE)
			{
				m_nPauseCount = MANUAL_TYPE_MANUAL;
			}
		}
		// �����������Ƃ��I�����Ă����Ԃ���̂��̂ɂ���
		else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_UP))
		{
			m_nPauseCount--;

			if (m_nPauseCount < MANUAL_TYPE_MANUAL)
			{
				m_nPauseCount = MANUAL_TYPE_GOTITLE;
			}
		}

		// �I������Ă���UI���g�傷��
		m_aScene_Two[m_nPauseCount]->SetSize(D3DXVECTOR2(300.0f, 100.0f));

		// �I�΂�Ă��Ȃ�UI�͌��̑傫���ɖ߂�
		if (m_nPauseCount != MANUAL_TYPE_MANUAL)
		{
			m_aScene_Two[MANUAL_TYPE_MANUAL]->SetSize(D3DXVECTOR2(200.0f, 50.0f));
		}
		if (m_nPauseCount != MANUAL_TYPE_RESUME)
		{
			m_aScene_Two[MANUAL_TYPE_RESUME]->SetSize(D3DXVECTOR2(200.0f, 50.0f));
		}
		if (m_nPauseCount != MANUAL_TYPE_GOTITLE)
		{
			m_aScene_Two[MANUAL_TYPE_GOTITLE]->SetSize(D3DXVECTOR2(200.0f, 50.0f));
		}


		// ����L�[���������Ƃ�
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
		{
			if (m_nPauseCount == MANUAL_TYPE_MANUAL)
			{
				m_ManualState = MANUAL_STATE_MANUAL;
			}
			else if (m_nPauseCount == MANUAL_TYPE_RESUME)
			{
				CPause::SetPause(false);
			}
			else if (m_nPauseCount == MANUAL_TYPE_GOTITLE)
			{
				CPause::SetPause(false);
				if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
				{
					CManager::GetFade()->SetFade(CManager::MODE_TITLE);
				}
			}
		}
	}

	//
	else if (m_ManualState == MANUAL_STATE_MANUAL)
	{
		// ����L�[���������Ƃ�
		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
		{
			m_ManualState = MANUAL_STATE_PAUSE;
		}

		if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RIGHT))
		{
			m_nSelect++;
			// ���̃y�[�W��
			if(m_nSelect > MANUAL_SELECT_PAGE_ABILITY)
			{
				m_nSelect = MANUAL_SELECT_PAGE_ABILITY;
			}
			else
			{
				m_aScene_Two[MANUAL_TYPE_PICTURE]->SetTex(
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f),
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
			}
		}

		//
		else if(CManager::GetKeyboard()->GetKeyboardTrigger(DIK_LEFT))
		{
			m_nSelect--;
			// ���̃y�[�W��
			if (m_nSelect < MANUAL_SELECT_PAGE_CONTROLLER)
			{
				m_nSelect = MANUAL_SELECT_PAGE_CONTROLLER;
			}
			else
			{
				m_aScene_Two[MANUAL_TYPE_PICTURE]->SetTex(
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT, 0.0f),
					D3DXVECTOR2(m_nSelect * TUTORIAL_UI_SPLIT + TUTORIAL_UI_SPLIT, 1.0f));
			}
		}
	}

	// �{�^��
	if (m_aScene_Two[MANUAL_TYPE_CROSSBUTTON] || m_aScene_Two[MANUAL_TYPE_ABUTTON])
	{
		// �J�E���g�J���[�A�b�v
		m_nCntCol++;
		// �\����Ԃ�
		if (m_nCntCol % 80 == 0)
		{
			m_aScene_Two[MANUAL_TYPE_CROSSBUTTON]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
			m_aScene_Two[MANUAL_TYPE_ABUTTON]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
		// ��\����Ԃ�
		else if (m_nCntCol % 40 == 0)
		{
			m_aScene_Two[MANUAL_TYPE_CROSSBUTTON]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
			m_aScene_Two[MANUAL_TYPE_ABUTTON]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
		}
	}

	//	//�W���C�X�e�B�b�N �\���L�[
	//	if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_RIGHT))
	//	{
	//	}
	//	else if (CManager::GetJoy()->GetTrigger(0, CJoypad::KEY_LEFT))
	//	{
	//	}
}
