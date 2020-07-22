// =====================================================================================================================================================================
//
// ���U���gUI�̏��� [resultUI.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"			// �C���N���[�h�t�@�C��
#include "resultUI.h"
#include "debugproc.h"
#include "UIManager.h"
#include "scene2D.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
// ------- ���W ------- //
#define RESULT_UI_BG_POS (SCREEN_CENTER_POS)
#define RESULT_UI_NAME_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.5f,150.0f,0.0f))
#define RESULT_UI_1P_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,300.0f,0.0f))
#define RESULT_UI_2P_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,300.0f,0.0f))
#define RESULT_UI_EVALUATION0_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,600.0f,0.0f))
#define RESULT_UI_EVALUATION1_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,600.0f,0.0f))
#define RESULT_UI_EVALUATION2_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,600.0f,0.0f))
#define RESULT_UI_EVALUATION0_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,600.0f,0.0f))
#define RESULT_UI_EVALUATION1_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,600.0f,0.0f))
#define RESULT_UI_EVALUATION2_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,600.0f,0.0f))
#define RESULT_UI_MISSIONCOMP1_POS (SCREEN_CENTER_POS)
#define RESULT_UI_MISSIONCOMP2_POS (SCREEN_CENTER_POS)

#define RESULT_UI_PRISONERNUM_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,400.0f,0.0f))
#define RESULT_UI_PRISONERNUM_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,400.0f,0.0f))
#define RESULT_UI_BONUS_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,500.0f,0.0f))
#define RESULT_UI_BONUS_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,500.0f,0.0f))

// ------- �T�C�Y ------- //
#define RESULT_UI_BG_SIZE (SCREEN_SIZE)
#define RESULT_UI_NAME_SIZE (D3DXVECTOR3(600.0f,100.0f,0.0))
#define RESULT_UI_1P_SIZE (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define RESULT_UI_2P_SIZE (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION0_SIZE_1P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION1_SIZE_1P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION2_SIZE_1P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION0_SIZE_2P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION1_SIZE_2P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_EVALUATION2_SIZE_2P (D3DXVECTOR3(300.0f,100.0f,0.0f))
#define RESULT_UI_MISSIONCOMP1_SIZE (D3DXVECTOR3(900.0f,250.0f,0.0f))
#define RESULT_UI_MISSIONCOMP2_SIZE (D3DXVECTOR3(900.0f,250.0f,0.0f))

#define RESULT_UI_PRISONERNUM_SIZE_1P (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define RESULT_UI_PRISONERNUM_SIZE_2P (D3DXVECTOR3(100.0f,100.0f,0.0f))
#define RESULT_UI_BONUS_SIZE_1P (D3DXVECTOR3(200.0f,100.0f,0.0f))
#define RESULT_UI_BONUS_SIZE_2P (D3DXVECTOR3(200.0f,100.0f,0.0f))

#define RESULT_UI_TEX_TYPE (9)

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9		CResultUI::m_TexNum[RESULT_UI_MAX] = {};					// �o�C���h����e�N�X�`���̏��

D3DXVECTOR3				CResultUI::m_Pos[RESULT_UI_MAX] = {
	RESULT_UI_BG_POS,
	RESULT_UI_NAME_POS,
	RESULT_UI_1P_POS,
	RESULT_UI_2P_POS,
	RESULT_UI_EVALUATION0_POS_1P,
	RESULT_UI_EVALUATION1_POS_1P,
	RESULT_UI_EVALUATION2_POS_1P,
	RESULT_UI_EVALUATION0_POS_2P,
	RESULT_UI_EVALUATION1_POS_2P,
	RESULT_UI_EVALUATION2_POS_2P,
	RESULT_UI_MISSIONCOMP1_POS,
	RESULT_UI_MISSIONCOMP2_POS,
};

D3DXVECTOR3				CResultUI::m_Size[RESULT_UI_MAX] = {
	RESULT_UI_BG_SIZE,
	RESULT_UI_NAME_SIZE,
	RESULT_UI_1P_SIZE,
	RESULT_UI_2P_SIZE,
	RESULT_UI_EVALUATION0_SIZE_1P,
	RESULT_UI_EVALUATION1_SIZE_1P,
	RESULT_UI_EVALUATION2_SIZE_1P,
	RESULT_UI_EVALUATION0_SIZE_2P,
	RESULT_UI_EVALUATION1_SIZE_2P,
	RESULT_UI_EVALUATION2_SIZE_2P,
	RESULT_UI_MISSIONCOMP1_SIZE,
	RESULT_UI_MISSIONCOMP2_SIZE,
};

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CResultUI::CResultUI()
{
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		// �|�C���^�̏�����
		m_apScene2D[nCnt] = nullptr;
	}

	m_pBonusScore = nullptr;
	m_pPrisonerNum = nullptr;
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CResultUI::~CResultUI()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CResultUI::Init(void)
{
	for (int nCnt = 25; nCnt < RESULT_UI_TEX_TYPE; nCnt++)
	{
		m_TexNum[RESULT_UI_MAX] = {
			CTexture::GetTexture((CTexture::TEX_TYPE)nCnt)};	// �o�C���h����e�N�X�`���̏��

	}
	// UI���܂Ƃ߂Đ�������
	ResultUICreate();

	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CResultUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �I��
			m_apScene2D[nCnt]->Uninit();

			// �f���[�g�t���O��L���ɂ���
			SetDeleteFlag(true);
		}
	}
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CResultUI::Update(void)
{
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �X�V
			m_apScene2D[nCnt]->Update();
		}
	}

	// �`������m�F
	DrawConditions();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CResultUI::Draw(void)
{
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
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
// �^�C�g��UI�̐���
//
// =====================================================================================================================================================================
CResultUI * CResultUI::Create()
{
	//�������̊m��
	CResultUI *pResultUI = new CResultUI();

	// ������
	pResultUI->Init();

	//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
	CUIManager::AddUIList(std::move(pResultUI));

	return pResultUI;
}

// =====================================================================================================================================================================
//
// Ui���܂Ƃ߂Đ�������
//
// =====================================================================================================================================================================
void CResultUI::ResultUICreate()
{
	// �����ȊO���܂Ƃ߂Đ�������
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			// �V�[��2D�̐���
			m_apScene2D[nCnt] = CScene2D::Create(m_Pos[nCnt], m_Size[nCnt]);

			if (nCnt == RESULT_UI_EVALUATION02P)
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(RESULT_UI_EVALUATION01P)));
			}
			else if (nCnt == RESULT_UI_EVALUATION12P)
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(RESULT_UI_EVALUATION11P)));
			}
			else if (nCnt == RESULT_UI_EVALUATION22P)
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(RESULT_UI_EVALUATION21P)));
			}
			else if (nCnt >= RESULT_UI_MISSIONCOMP1)
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + 25 - 3)));
			}
			else
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + 25)));
			}
			// �ŏ��͔�\���ɂ���
			//m_apScene2D[nCnt]->SetDisp(false);
		}
	}

	// �����`�𐶐�




}

// =====================================================================================================================================================================
//
// Ui�̕`�����
//
// =====================================================================================================================================================================
void CResultUI::DrawConditions()
{
	// �`�拖���o����
	/*if ()
	{
		m_apScene2D[]->SetDisp(true);
	}*/
	// �`��֎~���o����
	/*if ()
	{
		m_apScene2D[]->SetDisp(false);
	}*/
}
