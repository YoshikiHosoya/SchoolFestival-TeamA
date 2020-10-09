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
#define RANKINGSIZE			(D3DXVECTOR3(80.0f, 50.0f, 0.0f))		// �����L���OUI�̃T�C�Y
#define PLAYER_SCORE_SIZE	(D3DXVECTOR3(70.0f, 150.0f, 0.0f))		// �v���C���[�X�R�A�̃T�C�Y

#define RANKING_GOTITLESIZE			(D3DXVECTOR3(240.0f, 100.0f, 0.0f))		// �����L���OUI�̃T�C�Y	�^�C�g����

#define RANKING_SPACE		(10)									// �����L���O�̊Ԋu
#define RANKINGSCORESIZE	(D3DXVECTOR3(40.0f, 80.0f, 0.0f))		// �����L���O�X�R�A�T�C�Y
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
	m_pPlayerScore.clear();
	m_nRankingScore.clear();
	m_apScene2D.clear();
	m_apRankScore.clear();
	m_nPlayerScore = 0;
	m_nCntResult = 0;
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

	// �X�R�A�̓ǂݍ���
	RankingDataLoad();
	// �v���C���[�̃X�R�A��ǂݍ���
	PlayerScoreLoad();
	// UI����
	RankingUICreate();
	// �X�R�A����
	RankingScoreCreate();
	// �v���C���[�X�R�A����
	PlayerScoreCreate();

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
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.75f), 65.0f, 0.0f), D3DXVECTOR3(500.0f, 100.0f, 0.0f), CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_NAME));
		}
		// �v���C���[�X�R�A
		else if (nCnt == (int)RANKING_UI::RANKING_SCORE)
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.25f), SCREEN_HEIGHT * 0.45f, 0.0f), RANKING_GOTITLESIZE, CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_SCORE));
		}
		// �^�C�g����
		else if (nCnt == (int)RANKING_UI::RANKING_GO_TITLE)
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 650.0f, 0.0f), RANKING_GOTITLESIZE, CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_GO_TITLE));
		}
		// ����
		else
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.6f), (20.0f + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f), RANKINGSIZE, CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(CTexture::TEX_UI_RANKING_1st + nCnt - 2)));
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
		m_nRankingScore.emplace_back(1000000);

		// �X�R�A�̐���
		m_apRankScore.emplace_back((CMultiNumber::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.8f), ((200.0f - 15.0f) + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f),
								RANKINGSCORESIZE,
								m_nRankingScore[nCnt],
								RANKINGSCOREDIGITS,
								CScene::OBJTYPE_UI)));
	}
}

//------------------------------------------------------------------------------
//�v���C���[�X�R�A�̐���
//------------------------------------------------------------------------------
void CRanking::PlayerScoreCreate()
{
	// �X�R�A�̐���
	m_pPlayerScore.emplace_back((CMultiNumber::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.25f), SCREEN_HEIGHT * 0.6f, 0.0f),
											PLAYER_SCORE_SIZE,
											m_nPlayerScore,
											RANKINGSCOREDIGITS,
											CScene::OBJTYPE_UI)));
}

//------------------------------------------------------------------------------
//�����L���O�̃f�[�^�̃��[�h
//------------------------------------------------------------------------------
void CRanking::RankingDataLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

	static int nRnak[(int)RANKING_SCORE::SCORE_MAX] = {};

	// �t�@�C�����J��
	pFile = fopen(m_RankingFileName, "r");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		// SCRIPT������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������
		}

		// SCRIPT��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPT������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

															// RANKINGSET��������
				if (strcmp(cHeadText, "RANKINGSET") == 0)
				{
					// END_RANKINGSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_RANKINGSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						if (strcmp(cHeadText, "RANKING_1st") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_1st]);		// ��r�p�e�L�X�g��RANKIG_1st����
						}
						else if (strcmp(cHeadText, "RANKING_2nd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_2nd]);		// ��r�p�e�L�X�g��RANKIG_2nd����
						}
						else if (strcmp(cHeadText, "RANKING_3rd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_3rd]);		// ��r�p�e�L�X�g��RANKIG_3rd����
						}
						else if (strcmp(cHeadText, "RANKING_4th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_4th]);		// ��r�p�e�L�X�g��RANKIG_4th����
						}
						else if (strcmp(cHeadText, "RANKING_5th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[(int)RANKING_SCORE::SCORE_5th]);		// ��r�p�e�L�X�g��RANKIG_5th����
						}
						else if (strcmp(cHeadText, "END_RANKINGSET") == 0)
						{
							for (int nCnt = 0; nCnt < (int)RANKING_SCORE::SCORE_MAX; nCnt++)
							{
								// �����Ƀ����L���O�̃X�R�A�f�[�^��ǉ�
								m_nRankingScore.emplace_back(nRnak[nCnt]);
							}
						}
					}
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "�����L���O�̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}

//------------------------------------------------------------------------------
//�����L���O�X�R�A�̃��[�h
//------------------------------------------------------------------------------
void CRanking::PlayerScoreLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	int nScore = 0;					// �X�R�A

	// �t�@�C�����J��
	pFile = fopen(m_SaveScoreFileName, "r");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		// SCRIPT������܂Ń��[�v
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
			sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������
		}

		// SCRIPT��������
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPT������܂Ń��[�v
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

				// SCORESET��������
				if (strcmp(cHeadText, "SCORESET") == 0)
				{
					// END_SCORESET������܂Ń��[�v
					while (strcmp(cHeadText, "END_SCORESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						if (strcmp(cHeadText, "SCORE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_nPlayerScore);
						}
					}
				}
			}
		}
		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "�X�R�A�̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}
}