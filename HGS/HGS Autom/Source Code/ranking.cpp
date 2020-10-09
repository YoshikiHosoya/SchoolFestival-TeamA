//------------------------------------------------------------------------------
//
//���U���g����  [result.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "fade.h"
#include "ranking.h"
#include "sound.h"
#include "scene2D.h"
#include "multinumber.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define VERTICAL_SPACE		(70.0f)									// �c�̊Ԋu
#define WAITTIME_BASE		(180)									// �҂�����
#define ONE_SECOND			(60)									// 1�b
#define RANKINGSIZE			(D3DXVECTOR3(80.0f, 30.0f, 0.0f))		// �����L���OUI�̃T�C�Y
#define RANKING_SPACE		(10)									// �����L���O�̊Ԋu
#define RANKINGSCORESIZE	(D3DXVECTOR3(30.0f, 30.0f, 0.0f))		// �����L���O�X�R�A�T�C�Y
#define RANKINGSCOREDIGITS	(7)										// �����L���O�̌���

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
char *CRanking::m_RankingFileName =
{
	"data/Ranking/RankingData.txt" 			// �����L���O�̏��
};
char *CRanking::m_SaveScoreFileName =
{
	"data/Ranking/SaveScoreData.txt" 			// �����L���O�̏��
};


//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CRanking::CRanking()
{
	// ������
	m_nRankingScore.clear();
	m_apScene2D.clear();
	m_apRankScore.clear();
	m_nCntResult = 0;

	RankingUICreate();	// ����
	RankingScoreCreate(); // �X�R�A����
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CRanking::~CRanking()
{
	m_apScene2D.clear();
	m_apRankScore.clear();
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CRanking::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_FIXED);

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CRanking::Uninit()
{

}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CRanking::Update()
{
	//�J�E���^++
	m_nCntResult++;

	// �����L���OUI�̍X�V
	for (int nCnt = 0; nCnt < (int)RANKING_UI::RANKING_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			m_apScene2D[nCnt]->Update();
		}
	}

	//�t�F�[�h���ĂȂ���
	if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
	{
		//�����{�^���������Ƃ�
		if (CHossoLibrary::CheckAnyButton())
		{
				//�X�e�[�g�ύX
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);
		}
	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CRanking::Draw()
{
	// �����L���OUI�̕`��
	for (int nCnt = 0; nCnt < (int)RANKING_UI::RANKING_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			m_apScene2D[nCnt]->Draw();
		}
	}

}

//------------------------------------------------------------------------------
//�����L���OUI�̐���
//------------------------------------------------------------------------------
void CRanking::RankingUICreate()
{
	for (int nCnt = 0; nCnt < (int)RANKING_UI::RANKING_MAX; nCnt++)
	{
		// �����L���O�^�C�g�����S
		if (nCnt == (int)RANKING_UI::RANKING_NAME)
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 65.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f), CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_NAME));
		}

		// ����
		else
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.2f), (100.0f + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f), RANKINGSIZE, CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(CTexture::TEX_UI_RANKING_1st + nCnt - 1)));

			m_apScene2D[nCnt]->SetDisp(false);
		}
	}
}

//------------------------------------------------------------------------------
//�����L���O�X�R�A�̐���
//------------------------------------------------------------------------------
void CRanking::RankingScoreCreate()
{
	for (int nCnt = 0; nCnt < (int)RANKING_SCORE::SCORE_MAX; nCnt++)
	{
		m_nRankingScore.emplace_back(0);

		// �X�R�A�̐���
		m_apRankScore.emplace_back((CMultiNumber::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.4f), ((200.0f - 15.0f) + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f),
								RANKINGSCORESIZE,
								m_nRankingScore[nCnt],
								RANKINGSCOREDIGITS,
								CScene::OBJTYPE_UI)));
	}
}