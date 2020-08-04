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
#include "game.h"
#include "basemode.h"
#include "manager.h"
#include "multinumber.h"
#include "player.h"
#include "playerui.h"
#include "resultmanager.h"
#include "rankingui.h"
#include "scoremanager.h"
#include <iostream>
#include <mutex>
#include <thread>
// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
// ------- ���W ------- //
#define RESULT_UI_BG_POS (SCREEN_CENTER_POS)
#define RESULT_UI_NAME_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.5f,80.0f,0.0f))
#define RESULT_UI_1P_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,200.0f,0.0f))
#define RESULT_UI_2P_POS (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,200.0f,0.0f))
#define RESULT_UI_EVALUATION0_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,650.0f,0.0f))
#define RESULT_UI_EVALUATION1_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,650.0f,0.0f))
#define RESULT_UI_EVALUATION2_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,650.0f,0.0f))
#define RESULT_UI_EVALUATION0_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,650.0f,0.0f))
#define RESULT_UI_EVALUATION1_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,650.0f,0.0f))
#define RESULT_UI_EVALUATION2_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,650.0f,0.0f))
#define RESULT_UI_MISSIONCOMP1_POS (SCREEN_CENTER_POS)
#define RESULT_UI_MISSIONCOMP2_POS (SCREEN_CENTER_POS)

#define RESULT_UI_PRISONERNUM_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,350.0f,0.0f))
#define RESULT_UI_PRISONERNUM_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,350.0f,0.0f))
#define RESULT_UI_BONUS_POS_1P (D3DXVECTOR3(SCREEN_WIDTH * 0.25f,500.0f,0.0f))
#define RESULT_UI_BONUS_POS_2P (D3DXVECTOR3(SCREEN_WIDTH * 0.75f,500.0f,0.0f))

// ------- �T�C�Y ------- //
#define RESULT_UI_BG_SIZE (SCREEN_SIZE)
#define RESULT_UI_NAME_SIZE (D3DXVECTOR3(600.0f,50.0f,0.0))
#define RESULT_UI_1P_SIZE (D3DXVECTOR3(80.0f,60.0f,0.0f))
#define RESULT_UI_2P_SIZE (D3DXVECTOR3(80.0f,60.0f,0.0f))
#define RESULT_UI_EVALUATION0_SIZE_1P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION1_SIZE_1P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION2_SIZE_1P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION0_SIZE_2P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION1_SIZE_2P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_EVALUATION2_SIZE_2P (D3DXVECTOR3(300.0f,40.0f,0.0f))
#define RESULT_UI_MISSIONCOMP1_SIZE (D3DXVECTOR3(500.0f,200.0f,0.0f))
#define RESULT_UI_MISSIONCOMP2_SIZE (D3DXVECTOR3(500.0f,200.0f,0.0f))

#define RESULT_UI_PRISONERNUM_SIZE_1P (D3DXVECTOR3(70.0f,70.0f,0.0f))
#define RESULT_UI_PRISONERNUM_SIZE_2P (D3DXVECTOR3(70.0f,70.0f,0.0f))
#define RESULT_UI_BONUS_SIZE_1P (D3DXVECTOR3(80.0f,80.0f,0.0f))
#define RESULT_UI_BONUS_SIZE_2P (D3DXVECTOR3(80.0f,80.0f,0.0f))

// ------- ���� ------- //
#define RESULT_UI_PRISONERNUM_DIGIT (2)
#define RESULT_UI_BONUS_DIGIT (6)

// ------- �ǉ����_ ------- //
#define RESULT_UI_CONVERSION (1000)

#define RESULT_UI_TEX_TYPE (9)

// ��x����������ʂ�
#define CALL_ONCE(src)     \
     do     \
     {     \
          static bool initialized = false;     \
          if (!initialized)     \
          {     \
               src;     \
               initialized = true;     \
          }     \
     }     \
     while (0)

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

int				CResultUI::m_nTotalScore = 0;
int				CResultUI::m_nBonusScore = 0;
int				CResultUI::m_PlayerScore = 0;

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

	for (int nCnt = 0; nCnt < 3; nCnt++)
	{
		m_bUseUIFlag[nCnt] = false;
		m_bUse_One[nCnt] = false;
	}

	m_pBonusScore = nullptr;
	m_pPrisonerNum = nullptr;
	m_nPrisonerNum = 0;
	m_nBonusScore = 0;
	m_bPrisonerNum = false;
	m_bBonusScore = false;
	m_bEvaluation = false;
	m_nWaitTime = 0;
	m_bWaitFlag = false;
	m_nColCnt = 0;
	m_nTotalScore = 0;
	m_PlayerScore = 0;
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
	// �Q�[���N���X�̃|�C���^�擾
	CGame *pGame = (CGame*)CManager::GetBaseMode();
	if (pGame->GetPlayer()->GetPlayerUI() != nullptr)
	{
		// �X�R�A�̎擾
		m_PlayerScore = pGame->GetPlayer()->GetPlayerUI()->GetScore();
	}

	// UI���܂Ƃ߂Đ�������
	ResultUICreate();
	// ���l��ݒ�
	m_apScene2D[RESULT_UI_BG]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.6f));
	// �o���t���O��0�Ԗڂ�����
	m_bUseUIFlag[0] = true;
	// �҂����Ԃ̐ݒ�
	SetWaitTime(120);

	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CResultUI::Uninit(void)
{
	// ui�̉��
	for (int nCnt = 0; nCnt < RESULT_UI::RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �I��
			m_apScene2D[nCnt]->Rerease();
			m_apScene2D[nCnt] = nullptr;

			// �f���[�g�t���O��L���ɂ���
			SetDeleteFlag(true);
		}
	}

	// �i���o�[�`�̉��
	if (m_pBonusScore != nullptr)
	{
		m_pBonusScore->Rerease();
		m_pBonusScore = nullptr;
	}
	if (m_pPrisonerNum != nullptr)
	{
		m_pPrisonerNum->Rerease();
		m_pPrisonerNum = nullptr;
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

	// �Q�[�����[�h��������
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �Q�[���N���X�̃|�C���^�擾
		CGame *pGame = (CGame*)CManager::GetBaseMode();
		if (pGame != nullptr && pGame->GetResultManager() != nullptr)
		{
			// �`������m�F
			DrawConditions(pGame->GetResultManager()->GetResultState());
			// �҂����Ԃ̐ݒ�
			ResultUiOrder(m_bUseUIFlag[0], m_bUseUIFlag[1], m_bUseUIFlag[2]);
			// �������Ƃ̏���
			Conditions();
		}
	}
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

			if (nCnt == RESULT_UI_EVALUATION01P)
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + CTexture::TEX_UI_RESULT_GOOD-3)));
			}
			else if (nCnt == RESULT_UI_EVALUATION11P)
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + CTexture::TEX_UI_RESULT_GREATE)));
			}
			else if (nCnt == RESULT_UI_EVALUATION21P)
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + CTexture::TEX_UI_RESULT_NOPRISONER)));
			}

			else if (nCnt >= RESULT_UI_MISSIONCOMP1)
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(CTexture::TEX_UI_RESULT_MISSION1COMPLETE)));
			}
			else
			{
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(nCnt + CTexture::TEX_UI_RESULT_BG)));
			}
		}
	}

	// �c��̕ߗ��̐��pUI
	m_pPrisonerNum = CMultiNumber::Create(
		RESULT_UI_PRISONERNUM_POS_1P,
		RESULT_UI_PRISONERNUM_SIZE_1P,
		m_nPrisonerNum,
		RESULT_UI_PRISONERNUM_DIGIT,
		CScene::OBJTYPE_UI);

	// �ǉ����_�pUI
	m_pBonusScore = CMultiNumber::Create(
		RESULT_UI_BONUS_POS_1P,
		RESULT_UI_BONUS_SIZE_1P,
		m_nBonusScore,
		RESULT_UI_BONUS_DIGIT,
		CScene::OBJTYPE_UI);
}

// =====================================================================================================================================================================
//
// �S�ĕ`�悳����
//
// =====================================================================================================================================================================
void CResultUI::AllDraw()
{
	for (int nCnt = 0; nCnt < RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != nullptr)
		{
			m_apScene2D[nCnt]->SetDisp(true);
		}
	}

	if (m_pPrisonerNum != nullptr && m_pBonusScore != nullptr)
	{
		m_pPrisonerNum->SetDisp(true);
		m_pBonusScore->SetDisp(true);
	}
}
// =====================================================================================================================================================================
//
// �S�ĕ`�悳���Ȃ�
//
// =====================================================================================================================================================================
void CResultUI::AllNotDraw()
{
	for (int nCnt = 0; nCnt < RESULT_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt] != nullptr)
		{
			m_apScene2D[nCnt]->SetDisp(false);
		}
	}

	if (m_pPrisonerNum != nullptr && m_pBonusScore != nullptr)
	{
		m_pPrisonerNum->SetDisp(false);
		m_pBonusScore->SetDisp(false);
	}
}

// =====================================================================================================================================================================
//
// 0�Ԗڂ̃��U���g�ŕ\������UI�̐ݒ�
//
// =====================================================================================================================================================================
void CResultUI::Result0Draw()
{
	// �`�悷��񋓌^���w��
	if (m_apScene2D[RESULT_UI_BG] != nullptr &&
		m_apScene2D[RESULT_UI_NAME] != nullptr &&
		m_apScene2D[RESULT_UI_1P] != nullptr)
	{
		m_apScene2D[RESULT_UI_BG]->SetDisp(true);
		m_apScene2D[RESULT_UI_NAME]->SetDisp(true);
		m_apScene2D[RESULT_UI_1P]->SetDisp(true);
	}
}

// =====================================================================================================================================================================
//
// 1�Ԗڂ̃��U���g�ŕ\������UI�̐ݒ�
//
// =====================================================================================================================================================================
void CResultUI::Result1Draw()
{
	// �`�悷��񋓌^���w��
	if (m_apScene2D[RESULT_UI_MISSIONCOMP1] != nullptr)
	{
		//AllNotDraw();
		for (int nCnt = 0; nCnt < RESULT_UI_MAX; nCnt++)
		{
			if (m_apScene2D[nCnt] != nullptr)
			{
				m_apScene2D[nCnt]->SetDisp(false);
			}
		}

		if (m_pPrisonerNum != nullptr && m_pBonusScore != nullptr)
		{
			m_pPrisonerNum->SetDisp(false);
			m_pBonusScore->SetDisp(false);
		}


		m_apScene2D[RESULT_UI_MISSIONCOMP1]->SetDisp(true);

		Flashing(m_apScene2D[RESULT_UI_MISSIONCOMP1]);


		// �Q�[�����[�h��������
		if (CManager::GetMode() == CManager::MODE_GAME)
		{
			// �Q�[���N���X�̃|�C���^�擾
			CGame *pGame = (CGame*)CManager::GetBaseMode();
			if (pGame != nullptr && pGame->GetResultManager() != nullptr)
			{
				if (pGame->GetResultManager()->GetResultState() == CResultManager::RESULT_STATE_1)
				{
					// ���U���g���[�h�����̃��[�h�Ɉڍs���邽�߂̃t���O��true�ɂ���
					pGame->GetResultManager()->SetNextFlag(true);
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// �}���`�i���o�[�ɒl����
//
// =====================================================================================================================================================================
void CResultUI::ScoreCal()
{
	// �v���C���[�̃|�C���^���擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	if (pPlayer != nullptr)
	{
		// ��ƂȂ�v���C���[�̎c�@���̒l
		const int nReferenceValue_PrisonerNum = pPlayer->GetLife();
		// ��ƂȂ�ǉ����_�̒l
		const int nReferenceValue_BonusScore = pPlayer->GetLife() * CScoreManager::GetScorePoint(CScoreManager::SCORE_BONUS);

		// �`�拖���o���珈����ʂ�
		if (m_bPrisonerNum)
		{
			// �����̕`�拖��
			if (m_pPrisonerNum != nullptr)
			{
				m_pPrisonerNum->SetDisp(true);
			}
			// �ڕW�̒l�ɂȂ�܂Œl���v�Z
			TargetValue(nReferenceValue_PrisonerNum, m_nPrisonerNum, 1, m_pPrisonerNum);
		}
		// �`�拖���o���珈����ʂ�
		if (m_bBonusScore)
		{
			// �����̕`�拖��
			if (m_pBonusScore != nullptr)
			{
				m_pBonusScore->SetDisp(true);
			}
			// �ڕW�̒l�ɂȂ�܂Œl���v�Z
			TargetValue(nReferenceValue_BonusScore, m_nBonusScore, 100, m_pBonusScore);
		}
	}
}

// =====================================================================================================================================================================
//
// �����ɂ���ď�����i�߂�
//
// =====================================================================================================================================================================
void CResultUI::Conditions()
{
	// �Q�[�����[�h��������
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// �Q�[���N���X�̃|�C���^�擾
		CGame *pGame = (CGame*)CManager::GetBaseMode();
		if (pGame != nullptr && pGame->GetResultManager() != nullptr)
		{
			if (pGame->GetResultManager()->GetResultState() == CResultManager::RESULT_STATE_0)
			{
				// �}���`�i���o�[�ɒl����
				ScoreCal();

				// �`�拖���o����
				if (m_bEvaluation == true)
				{
					// �ߗ��̐��ɂ���Č��ʂ��ς��
					// �����ɂ���ĕ`�悷�� �]��
					if (m_apScene2D[RESULT_UI_EVALUATION01P] != nullptr)
					{
						m_apScene2D[RESULT_UI_EVALUATION01P]->SetDisp(true);

						Flashing(m_apScene2D[RESULT_UI_EVALUATION01P]);
					}

					// ���U���g���[�h�����̃��[�h�Ɉڍs���邽�߂̃t���O��true�ɂ���
					pGame->GetResultManager()->SetNextFlag(true);
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// �ڕW�̒l�ɂȂ�܂Œl���v�Z
//
// =====================================================================================================================================================================
void CResultUI::TargetValue(const int &Target, int &Value, int Add , CMultiNumber *pMultiNumber)
{
	// �ڕW�l���l��������������
	if (Target > Value)
	{
		// �l�����Z
		Value += Add;

		// �l���ڕW�l�𒴂�����
		if (Target < Value)
		{
			// �l�ɖڕW�l�̒l����
			Value = Target;
		}

		// �}���`�i���o�[�ɒl����
		pMultiNumber->SetMultiNumber((int)Value);
	}

	else
	{
		if (pMultiNumber == m_pPrisonerNum)
		{
			// �o���t���O��1�Ԗڂ�����
			m_bUseUIFlag[1] = true;
		}
		if (pMultiNumber == m_pBonusScore)
		{
			// �o���t���O��2�Ԗڂ�����
			m_bUseUIFlag[2] = true;
		}
	}
}

// =====================================================================================================================================================================
//
// �҂����Ԃ��I��������Ɍ��ʂ�Ԃ�
//
// =====================================================================================================================================================================
void CResultUI::WaitTime(int nTime ,bool &bFlag, bool &bUse)
{
	//static std::once_flag flag;
	//std::call_once(flag, SetWaitTime(nTime));

	// 1�x����������ʂ�
	//CALL_ONCE(SetWaitTime(nTime));

	// �ҋ@���Ԃ�����������
	m_nWaitTime--;

	//���Ԃ�0�ȉ��ɂȂ�����
	if (m_nWaitTime <= 0)
	{
		// �t���O��true�ɂ���
		if (!bFlag)
		{
			bFlag = true;
			bUse = true;
		}
		SetWaitTime(nTime);
	}
}

// =====================================================================================================================================================================
//
// ���U���gUI�̕\������
//
// =====================================================================================================================================================================
void CResultUI::ResultUiOrder(bool bUse0, bool bUse1, bool bUse2)
{
	if (bUse0)
	{
		// �҂����Ԃ̐ݒ�
		if (m_bUse_One[0] == false)
		{
			WaitTime(120, m_bPrisonerNum, m_bUse_One[0]);
		}
	}
	if (bUse1)
	{
		// �҂����Ԃ̐ݒ�
		if (m_bUse_One[1] == false)
		{
			WaitTime(120, m_bBonusScore, m_bUse_One[1]);
		}
	}
	if (bUse2)
	{
		// �҂����Ԃ̐ݒ�
		if (m_bUse_One[2] == false)
		{
			WaitTime(120, m_bEvaluation, m_bUse_One[2]);
		}
	}
}

// =====================================================================================================================================================================
//
// Ui�̕`�����
//
// =====================================================================================================================================================================
void CResultUI::DrawConditions(CResultManager::RESULT_STATE state)
{
	// ��x�S�Ẵ��U���gUI���\���ɂ��Ă��玟�ɕ\������UI�����߂�
	AllNotDraw();

	switch (state)
	{
	case CResultManager::RESULT_STATE_0:
		// ���U���g0�p��UI��\��
		Result0Draw();
		break;

	case CResultManager::RESULT_STATE_1:
		// ���U���g1�p��UI��\��
		Result1Draw();
		break;
	}
}

// =====================================================================================================================================================================
//
// �_�ŏ���
//
// =====================================================================================================================================================================
void CResultUI::Flashing(CScene2D *m_apScene2D)
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

// =====================================================================================================================================================================
//
// �g�[�^���X�R�A�v�Z����
//
// =====================================================================================================================================================================
void CResultUI::TotalScoreCalculation()
{
	// �Q�[���X�R�A�ƃ{�[�i�X�X�R�A�̌v�Z
	m_nTotalScore = m_nBonusScore + m_PlayerScore;
	CRankingUI::ScoreSave();
}
