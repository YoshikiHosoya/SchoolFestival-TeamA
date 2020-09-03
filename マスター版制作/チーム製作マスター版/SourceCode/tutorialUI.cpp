// =====================================================================================================================================================================
//
// �`���[�g���A��ui�̏��� [tutorialui.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "tutorial.h"
#include "manager.h"
#include "renderer.h"
#include "UIManager.h"
#include "tutorialUI.h"
#include "tutorialmanager.h"
#include "scene2D.h"
#include "debugproc.h"
// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define _CRT_SECURE_NO_WARNINGS // �x������

// �e�N�X�`���̎��
#define TUTORIAL_UI_TEXTURE		(TUTORIAL_UI)

// UI�̍��W
#define TUTORIAL_UI_NAME_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,80.0f,0.0f))
#define TUTORIAL_UI_ORDER_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f,200.0f,0.0f))

// UI�̑傫��
#define TUTORIAL_UI_NAME_SIZE	(D3DXVECTOR3(SCREEN_WIDTH * 0.45f,50.0f,0.0f))
#define TUTORIAL_UI_ORDER_SIZE	(D3DXVECTOR3(SCREEN_WIDTH * 0.4f,50.0f,0.0f))

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9		CTutorialUI::m_TexNum[UI_MAX] = {};					// �o�C���h����e�N�X�`���̏��

D3DXVECTOR3				CTutorialUI::m_Pos[UI_MAX] = {
	TUTORIAL_UI_NAME_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
	TUTORIAL_UI_ORDER_POS,
};

D3DXVECTOR3				CTutorialUI::m_Size[UI_MAX] = {
	TUTORIAL_UI_NAME_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
	TUTORIAL_UI_ORDER_SIZE,
};

// =====================================================================================================================================================================
// �R���X�g���N�^
// =====================================================================================================================================================================
CTutorialUI::CTutorialUI()
{
	// ������
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = nullptr;
	}

	m_nColCnt = 0;
}

// =====================================================================================================================================================================
// �f�X�g���N�^
// =====================================================================================================================================================================
CTutorialUI::~CTutorialUI()
{
}

// =====================================================================================================================================================================
// ������
// =====================================================================================================================================================================
HRESULT CTutorialUI::Init(void)
{
	// �e�N�X�`���̎擾
	for (int nCntNum = 0 ,nCnt = CTexture::TEX_UI_TUTORIAL_NAME; nCntNum < UI_MAX; nCntNum++,nCnt++)
	{
		m_TexNum[nCntNum] = CTexture::GetTexture((CTexture::TEX_TYPE)nCnt);	// �o�C���h����e�N�X�`���̏��
	}

	// UI�̐���
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			// �V�[��2D�̐���
			m_apScene2D[nCnt] = CScene2D::Create(m_Pos[nCnt], m_Size[nCnt]);
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(m_TexNum[nCnt]);

			if (nCnt != UI_NAME)
			{
				m_apScene2D[nCnt]->SetDisp(false);
			}
		}
	}

	return S_OK;
}

// =====================================================================================================================================================================
// �I��
// =====================================================================================================================================================================
void CTutorialUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �I��
			m_apScene2D[nCnt]->Uninit();
			delete m_apScene2D[nCnt];
			m_apScene2D[nCnt] = nullptr;

			// �f���[�g�t���O��L���ɂ���
			SetDeleteFlag(true);
		}
	}
}

// =====================================================================================================================================================================
// �X�V
// =====================================================================================================================================================================
void CTutorialUI::Update(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			if (m_apScene2D[nCnt]->GetDisp())
			{
				// �X�V
				m_apScene2D[nCnt]->Update();
			}

			CDebugProc::Print_Left("TutorialUI %d,%d\n", m_apScene2D[nCnt]->GetDisp(), nCnt);
		}
	}
}

// =====================================================================================================================================================================
// �`�揈��
// =====================================================================================================================================================================
void CTutorialUI::Draw(void)
{
	for (int nCnt = 0; nCnt < TUTORIAL_UI::UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �`��
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// �`���[�g���A��UI�̐���
//
// =====================================================================================================================================================================
CTutorialUI * CTutorialUI::Create()
{
	//�������̊m��
	CTutorialUI *pTutorialUI = new CTutorialUI();

	// ������
	pTutorialUI->Init();

	//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
	CUIManager::AddUIList(std::move(pTutorialUI));

	return pTutorialUI;
}

// =====================================================================================================================================================================
//
// �I������ui��`�悵1�ڂ�ui���\���ɂ���
//
// =====================================================================================================================================================================
void CTutorialUI::SetDrawDisp(TUTORIAL_UI ui)
{
	// �ŏ���1��ڂ͉�����\���ɂ��Ȃ�
	if (ui == UI_ORDERFIRST)
	{
		// �����̔ԍ���ui��\��������
		if (m_apScene2D[ui])
		{
			m_apScene2D[ui]->SetDisp(true);
		}
	}
	else
	{
		// null����Ȃ�������
		if (m_apScene2D[ui - 1])
		{
			// 1�X�e�[�g�O�Ɏg���Ă���ui���\���ɂ���
			m_apScene2D[ui - 1]->SetDisp(false);

			// �����̔ԍ���ui��\��������
			if (m_apScene2D[ui])
			{
				m_apScene2D[ui]->SetDisp(true);
			}
		}
	}
}

// =====================================================================================================================================================================
//
// ���g���Ă���ui�̎�ނ̎擾
//
// =====================================================================================================================================================================
CTutorialUI::TUTORIAL_UI CTutorialUI::GetTutorialUiType()
{
	int nFlaseCnt = 0;
	for (int nCnt = UI_ORDERFIRST,nCntArray = UI_ORDERFINAL; nCnt < TUTORIAL_UI::UI_MAX; nCnt++, nCntArray--)
	{
		if (m_apScene2D[nCntArray]->GetDisp() == true)
		{
			// �`�悳��Ă���ui�̔ԍ���񋓌^�ɕϊ����ϐ��ɑ��
			return m_TutorialUiType = static_cast<TUTORIAL_UI>(nCntArray+1);
		}

		// �z��̒l�S�Ă�false��������1�Ԗڂ�true�ɂ���
		else if (m_apScene2D[nCnt]->GetDisp() == false)
		{
			nFlaseCnt++;
		}
	}

	if (nFlaseCnt >= UI_ORDERFINAL)
	{
		// ��ԍŏ������͂��ׂ�false�Ȃ̂ň�Ԗڂ�ui�̔ԍ�����
		return m_TutorialUiType = static_cast<TUTORIAL_UI>(UI_ORDERFIRST);
	}

	return m_TutorialUiType;
}

// =====================================================================================================================================================================
//
// �_�ŏ���
//
// =====================================================================================================================================================================
void CTutorialUI::Flashing(CScene2D *m_apScene2D)
{
	// �J�E���g���Z
	m_nColCnt++;
	// �]�肪0�̎������ɂ���
	if (m_nColCnt % 60 == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// �]�肪0�̎��ʏ��Ԃɂ���
	else if (m_nColCnt % 30 == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}
