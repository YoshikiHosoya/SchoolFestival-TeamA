// =====================================================================================================================================================================
//
// �����L���OUI�̏��� [resultUI.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"			// �C���N���[�h�t�@�C��
#include "rankingUI.h"
#include "debugproc.h"
#include "UIManager.h"
#include "scene2D.h"
#include "multinumber.h"
#include "resultui.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
RANKING_DATA	CRankingUI::m_RankingData				= {};
RANKING_SCORE_DATA	CRankingUI::m_ScoreData = {};

int				CRankingUI::m_nRankingScore[SCORE_MAX]	= {};
int				CRankingUI::m_nScore = 0;
// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CRankingUI::m_RankingFileName =
{
	"data/Load/Ranking/RankingData.txt" 			// �A�C�e���̏��
};
char *CRankingUI::m_SaveScoreFileName =
{
	"data/Load/Ranking/SaveScoreData.txt" 			// �A�C�e���̏��
};


// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define RANKINGSIZE (D3DXVECTOR3(100.0f, 50.0f, 0.0f))
#define RANKING_SPACE (10)

#define RANKINGSCORESIZE (D3DXVECTOR3(70.0f, 70.0f, 0.0f))
#define RANKINGSCOREDIGITS (7)

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CRankingUI::CRankingUI()
{
	// ������
	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = nullptr;
	}

	for (int nCnt = 0; nCnt < RANKING_NUM; nCnt++)
	{
		m_pRankScore[nCnt] = nullptr;
	}
	m_nColCnt = 0;
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CRankingUI::~CRankingUI()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CRankingUI::Init(void)
{
	// �X�R�A�̓ǂݍ���
	CRankingUI::RankingLoad();
	// �����L���O�̌v�Z
	RankingCalculation();
	// �����L���O�X�R�A�̃Z�[�u
	RankingSave();

	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			// �����L���O�^�C�g�����S
			if (nCnt == RANKING_NAME)
			{
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 65.0f, 0.0f), D3DXVECTOR3(500.0f, 50.0f, 0.0f));
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_NAME));
			}

			// ����
			else
			{
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.25f), ((200.0f - 100.0f) + (100.0f * nCnt)) + RANKING_SPACE * nCnt, 0.0f), RANKINGSIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(CTexture::TEX_UI_RANKING_1st + nCnt - 1)));
			}
		}
	}

	// �X�R�A�̐���
	for (int nCnt = 0; nCnt < RANKING_NUM; nCnt++)
	{
		// �X�R�A�̐���
		m_pRankScore[nCnt] = CMultiNumber::Create(
			D3DXVECTOR3((SCREEN_WIDTH * 0.6f), ((200.0f) + (100.0f * nCnt)) + RANKING_SPACE * nCnt+1, 0.0f),
			RANKINGSCORESIZE,
			m_nRankingScore[nCnt],
			RANKINGSCOREDIGITS,
			CScene::OBJTYPE_UI);

		// �`�拖��
		m_pRankScore[nCnt]->SetDisp(true);
	}

	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CRankingUI::Uninit(void)
{

	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
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

	for (int nCnt = 0; nCnt < RANKING_NUM; nCnt++)
	{
		if (m_pRankScore[nCnt] != nullptr)
		{
			m_pRankScore[nCnt]->Rerease();
			m_pRankScore[nCnt] = nullptr;
		}
	}

}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CRankingUI::Update(void)
{
	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �X�V
			m_apScene2D[nCnt]->Update();
		}
	}
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CRankingUI::Draw(void)
{
	for (int nCnt = 0; nCnt < RANKING_UI::RANKING_UI_MAX; nCnt++)
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
CRankingUI * CRankingUI::Create()
{
	//�������̊m��
	CRankingUI *pRankingUI = new CRankingUI();

	// ������
	pRankingUI->Init();

	//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
	CUIManager::AddUIList(std::move(pRankingUI));

	return pRankingUI;
}

// =====================================================================================================================================================================
//
// �����L���O���̓ǂݍ���
//
// =====================================================================================================================================================================
void CRankingUI::RankingLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

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

															// ITEMSET��������
				if (strcmp(cHeadText, "RANKINGSET") == 0)
				{
					// END_ITEMSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_RANKINGSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

																	// SPEED��������
						if (strcmp(cHeadText, "RANKING_1st") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_1st]);		// ��r�p�e�L�X�g��RANKIG_1st����
						}
						else if (strcmp(cHeadText, "RANKING_2nd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_2nd]);		// ��r�p�e�L�X�g��RANKIG_2nd����
						}
						else if (strcmp(cHeadText, "RANKING_3rd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_3rd]);		// ��r�p�e�L�X�g��RANKIG_3rd����
						}
						else if (strcmp(cHeadText, "RANKING_4th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_4th]);		// ��r�p�e�L�X�g��RANKIG_4th����
						}
						else if (strcmp(cHeadText, "RANKING_5th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RankingData.nRankingScore[SCORE_5th]);		// ��r�p�e�L�X�g��RANKIG_5th����
						}

						else if (strcmp(cHeadText, "END_RANKINGSET") == 0)
						{
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

	// �ǂݍ��񂾏��̑��
	SetRankingData();
}

// =====================================================================================================================================================================
//
// �����L���O�̃Z�[�u
//
// =====================================================================================================================================================================
void CRankingUI::RankingSave()
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �e���f���t�@�C���̃t�@�C�����J��
	pFile = fopen(m_RankingFileName, "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �����L���O�f�[�^�̏��\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "\n");

		fprintf(pFile, "SCRIPT\n\n");
		fprintf(pFile, "RANKINGSET\n");

		// �Z�[�u���郉���L���O�̏��
		fprintf(pFile, "	RANKING_1st	= %d\n", m_nRankingScore[SCORE_1st]);
		fprintf(pFile, "	RANKING_2nd	= %d\n", m_nRankingScore[SCORE_2nd]);
		fprintf(pFile, "	RANKING_3rd	= %d\n", m_nRankingScore[SCORE_3rd]);
		fprintf(pFile, "	RANKING_4th	= %d\n", m_nRankingScore[SCORE_4th]);
		fprintf(pFile, "	RANKING_5th	= %d\n", m_nRankingScore[SCORE_5th]);

		fprintf(pFile, "END_RANKINGSET\n\n");
		fprintf(pFile, "END_SCRIPT\n");


#ifdef _DEBUG
		// �ǂݍ��ݐ������̌��ʕ\��
		MessageBox(NULL, "�����L���O�����Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
#endif // DEBUG

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
#ifdef _DEBUG
		// �ǂݍ��ݎ��s���̌x���\��
		MessageBox(NULL, "�����L���O���̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
#endif // DEBUG
	}
}

// =====================================================================================================================================================================
//
// �����L���O���ʂ̌v�Z
//
// =====================================================================================================================================================================
void CRankingUI::RankingCalculation()
{
	// �g�[�^���X�R�A���擾�������������s�\�ȕϐ��ɂ���
	BonusScoreLoad();
	const int CurrentScore = m_nScore;
	int nCnt = SCORE_5th;

	// �擾�����X�R�A�ƃ����L���O�X�R�A��1�ʂ����r��
	// �擾�����X�R�A�̕����傫��������l������������
	for (int nRank = 0; nRank < SCORE_MAX; nRank++)
	{
		if (CurrentScore >= m_nRankingScore[nRank])
		{
			if (nRank >= SCORE_5th)
			{
				m_nRankingScore[SCORE_5th] = CurrentScore;
			}
			else
			{
				while (nRank < nCnt)
				{
					m_nRankingScore[nCnt] = m_nRankingScore[nCnt - 1];
					nCnt--;
				}
				m_nRankingScore[nRank] = CurrentScore;
				break;
			}
		}
	}
}

// =====================================================================================================================================================================
//
//
//
// =====================================================================================================================================================================
void CRankingUI::ScoreSave()
{
	// �t�@�C���|�C���g
	FILE	*pFile;

	// �e���f���t�@�C���̃t�@�C�����J��
	pFile = fopen(m_SaveScoreFileName, "w");

	// �J���Ă���Ƃ�
	if (pFile != NULL)
	{
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# �X�R�A�̏��\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "\n");

		fprintf(pFile, "SCRIPT\n\n");
		fprintf(pFile, "SCORESET\n");

		// �Z�[�u���郉���L���O�̏��
		fprintf(pFile, "	SCORE	= %d\n", CResultUI::GetTotalScore());

		fprintf(pFile, "END_SCORESET\n\n");
		fprintf(pFile, "END_SCRIPT\n");


#ifdef _DEBUG
		// �ǂݍ��ݐ������̌��ʕ\��
		MessageBox(NULL, "�X�R�A�����Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
#endif // DEBUG

		// �t�@�C�������
		fclose(pFile);
	}
	else
	{
#ifdef _DEBUG
		// �ǂݍ��ݎ��s���̌x���\��
		MessageBox(NULL, "�X�R�A���̓ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
#endif // DEBUG
	}
}

// =====================================================================================================================================================================
//
//
//
// =====================================================================================================================================================================
void CRankingUI::BonusScoreLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

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

															// ITEMSET��������
				if (strcmp(cHeadText, "SCORESET") == 0)
				{
					// END_ITEMSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_SCORESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

																	// SPEED��������
						if (strcmp(cHeadText, "SCORE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nTotalScore);		// ��r�p�e�L�X�g��RANKIG_1st����
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


	m_nScore = m_ScoreData.nTotalScore;
}

// =====================================================================================================================================================================
//
// �ǂݍ��񂾃X�R�A�̔��f
//
// =====================================================================================================================================================================
void CRankingUI::SetRankingData()
{
	// �����L���O�̃X�R�A�̏�����
	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		m_nRankingScore[nCnt] = m_RankingData.nRankingScore[nCnt];
	}
}

// =====================================================================================================================================================================
//
// �_�ŏ���
//
// =====================================================================================================================================================================
void CRankingUI::Flashing(CScene2D *m_apScene2D)
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
