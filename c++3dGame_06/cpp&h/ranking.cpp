// ------------------------------------------
//
// �����L���O���� [ranking.cpp]
// Author : Fujiwara Masato
//
// ------------------------------------------
#include "ranking.h"
/* �`�� */
#include "tlybg.h"
#include "rank_ui.h"
//#include "topscore.h"
#include "fade.h"

// ------------------------------------------
//
// �}�N����`
//
// ------------------------------------------

// ------------------------------------------
//
// �ÓI�ϐ��錾
//
// ------------------------------------------

// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CRanking::CRanking()
{
	m_CntChange = 0;
}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CRanking::~CRanking()
{
}

// ------------------------------------------
// ������
// ------------------------------------------
void CRanking::Init(void)
{
	/* �쐬 */
	// �w�i
	CTlyBg::Create(CManager::MODE_RANKING);
	// �����N�pui
	CRank_ui::Create();
	// �J�E���g�J��
	m_CntChange = 0;
}

// ------------------------------------------
// �I��
// ------------------------------------------
void CRanking::Uninit(void)
{
	CScene::ReleaseAll();
}

// ------------------------------------------
// �X�V
// ------------------------------------------
void CRanking::Update(void)
{
	// �J�E���g�J�ڃA�b�v
	m_CntChange++;
	if (m_CntChange >= INTERVAL_TIME)
	{
		// ��ʑJ�ڂ̏�Ԃ��J�ڂ��Ă��Ȃ���Ԃ�������
		if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
		{
			//CTopscore::SetScore(0);
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}
	}
	// ���[�h�̐ݒ�
	else if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_RETURN))
	{
		// �G���^�[��
		//CManager::GetSound()->PlaySound(CSound::LABEL_SE_1);
		// ��ʑJ�ڂ̏�Ԃ��J�ڂ��Ă��Ȃ���Ԃ�������
		if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
		{
			//CTopscore::SetScore(0);
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}
	}

	//�W���C�X�e�B�b�N
	// ���[�h�̐ݒ�
	else if (CManager::GetJoy()->GetPress(0, CJoypad::KEY_A)||
		CManager::GetJoy()->GetPress(0, CJoypad::KEY_B))
	{
		// �G���^�[��
		//CManager::GetSound()->PlaySound(CSound::LABEL_SE_1);
		// ��ʑJ�ڂ̏�Ԃ��J�ڂ��Ă��Ȃ���Ԃ�������
		if (CManager::GetFade()->GetFade() == CFade::FADE_NONE)
		{
			//CTopscore::SetScore(0);
			CManager::GetFade()->SetFade(CManager::MODE_TITLE);
		}
	}
}

// ------------------------------------------
// �`��
// ------------------------------------------
void CRanking::Draw(void)
{
}
