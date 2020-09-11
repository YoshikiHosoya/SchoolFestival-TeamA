// =====================================================================================================================================================================
//
// �����L���OUI�̏��� [resultUI.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"			// �C���N���[�h�t�@�C��
#include "rankingUI.h"
#include "debugproc.h"
#include "UIManager.h"
#include "scene2D.h"
#include "multinumber.h"
#include "resultui.h"
#include "sound.h"
#include "rankingmanager.h"
#include "particle.h"
#include "ParticleManager.h"
#include "fade.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CRankingUI::m_RankingFileName =
{
	"data/Load/Ranking/RankingData.txt" 			// �����L���O�̏��
};
char *CRankingUI::m_SaveScoreFileName =
{
	"data/Load/Ranking/SaveScoreData.txt" 			// �����L���O�̏��
};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define RANKINGSIZE (D3DXVECTOR3(80.0f, 30.0f, 0.0f))
#define RANKING_SPACE (10)
#define RANKINGSCORESIZE (D3DXVECTOR3(30.0f, 30.0f, 0.0f))
#define RANKINGSCOREDIGITS (7)
#define VERTICAL_SPACE (70.0f)
#define WAITTIME_BASE (180)
#define ONE_SECOND (60)

#define ONE_HUNDRED (100)
#define ONE_THOUSAND (1000)
#define TEN_THOUSAND (10000)
#define HUNDRED_THOUSAND (100000)
#define MILLION (1000000)

#define OUTSIDE_SCREEN (D3DXVECTOR3(0.0f, 1000.0f, 0.0f))

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CRankingUI::CRankingUI()
{
	// ������
	m_apScene2D[RANKING_UI_MAX]			 = {};
	m_pRankScore[SCORE_MAX]				 = {};
	m_pPlayerScore[PLAYER_SCORE_MAX]	 = {};
	m_bMoveRank[SCORE_MAX] = {};
	m_bEvaluation[3] = {};

	m_nRankingScore.clear();
	m_nPlayerScore.clear();

	m_WaitTime				= WAITTIME_BASE;
	m_nTimeToExplosion		= WAITTIME_BASE;
	m_nTimeToFireworks		= WAITTIME_BASE;
	m_nTimeToFlash			= ONE_SECOND;
	m_nTimeToDraw			= ONE_SECOND;
	m_RankScoreMove			= ZeroVector3;
	m_RankScoreMove			= ZeroVector3;
	m_nRankNum				= 0;
	m_nDrawCount			= 0;
	m_nTimeToTransition		= 0;
	m_nColCnt				= 0;
	m_fCol					= 0.0f;
	m_bCompleted			= false;
	m_bCompletedEnd			= false;
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
	//�p�[�e�B�N������
	CParticleManager::Create();
	// �X�R�A�̓ǂݍ���
	CRankingUI::RankingDataLoad();
	// �v���C���[�̃X�R�A��ǂݍ���
	PlayerScoreLoad();
	// ��{�I�ȃ����L���Oui
	RankUiCreate();
	// �v���C���[�̊l���X�R�A�\��
	PlayerScoreUiCreate();

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

	// �����L���O�̃X�e�[�g���Ƃ̏���
	RankingState();
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
void CRankingUI::RankingDataLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

	static int nRnak[SCORE_MAX] = {};

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
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[SCORE_1st]);		// ��r�p�e�L�X�g��RANKIG_1st����
						}
						else if (strcmp(cHeadText, "RANKING_2nd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[SCORE_2nd]);		// ��r�p�e�L�X�g��RANKIG_2nd����
						}
						else if (strcmp(cHeadText, "RANKING_3rd") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[SCORE_3rd]);		// ��r�p�e�L�X�g��RANKIG_3rd����
						}
						else if (strcmp(cHeadText, "RANKING_4th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[SCORE_4th]);		// ��r�p�e�L�X�g��RANKIG_4th����
						}
						else if (strcmp(cHeadText, "RANKING_5th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[SCORE_5th]);		// ��r�p�e�L�X�g��RANKIG_5th����
						}
						else if (strcmp(cHeadText, "RANKING_6th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[SCORE_6th]);		// ��r�p�e�L�X�g��RANKIG_5th����
						}
						else if (strcmp(cHeadText, "RANKING_7th") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nRnak[SCORE_7th]);		// ��r�p�e�L�X�g��RANKIG_5th����
						}
						else if (strcmp(cHeadText, "END_RANKINGSET") == 0)
						{
							for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
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

// =====================================================================================================================================================================
//
// �����L���O�̃Z�[�u
//
// =====================================================================================================================================================================
void CRankingUI::RankingDataSave()
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
		fprintf(pFile, "	RANKING_6th	= %d\n", m_nRankingScore[SCORE_6th]);
		fprintf(pFile, "	RANKING_7th	= %d\n", m_nRankingScore[SCORE_7th]);


		fprintf(pFile, "END_RANKINGSET\n\n");
		fprintf(pFile, "END_SCRIPT\n");


#ifdef _DEBUG
		// �ǂݍ��ݐ������̌��ʕ\��
		//MessageBox(NULL, "�����L���O�����Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
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
	// �����Ƀv���C���[�̃X�R�A�f�[�^��ǉ�
	m_nRankingScore.emplace_back(m_RunkingData.nScore[PLAYER_SCORE_1P] + m_RunkingData.nScore[PLAYER_SCORE_2P]);
	// �X�R�A��傫�����ɓ���ւ���
	BubbleSort(m_nRankingScore);

	for (int nCnt = 0; nCnt < (int)m_nRankingScore.size() - 1; nCnt++)
	{
		// �}���`�i���o�[�ɒl����
		m_pRankScore[nCnt]->SetMultiNumber((int)m_nRankingScore[nCnt]);
	}
}

// =====================================================================================================================================================================
//
// �v���C���[�̃X�R�A��ۑ�
//
// =====================================================================================================================================================================
void CRankingUI::PlayerScoreSave()
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
		fprintf(pFile, "	SCORE_ONE	= %d\n", CResultUI::GetTotalScore(PLAYER_SCORE_1P));
		fprintf(pFile, "	SCORE_TWO	= %d\n", CResultUI::GetTotalScore(PLAYER_SCORE_2P));

		fprintf(pFile, "END_SCORESET\n\n");
		fprintf(pFile, "END_SCRIPT\n");


#ifdef _DEBUG
		// �ǂݍ��ݐ������̌��ʕ\��
		//MessageBox(NULL, "�X�R�A�����Z�[�u���܂���", "����", MB_OK | MB_ICONINFORMATION);
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
// �v���C���[�̃X�R�A�擾
//
// =====================================================================================================================================================================
void CRankingUI::PlayerScoreLoad()
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

				// SCORESET��������
				if (strcmp(cHeadText, "SCORESET") == 0)
				{
					// END_SCORESET������܂Ń��[�v
					while (strcmp(cHeadText, "END_SCORESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

						if (strcmp(cHeadText, "SCORE_ONE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RunkingData.nScore[PLAYER_SCORE_1P]);
						}

						if (CPlayer::GetTwoPPlayFlag())
						{
							if (strcmp(cHeadText, "SCORE_TWO") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_RunkingData.nScore[PLAYER_SCORE_2P]);
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
		MessageBox(NULL, "�X�R�A�̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}

	m_nPlayerScore.emplace_back(m_RunkingData.nScore[PLAYER_SCORE_1P]);
	m_nPlayerScore.emplace_back(m_RunkingData.nScore[PLAYER_SCORE_2P]);
	m_nPlayerScore.emplace_back(0);
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
	if (m_nColCnt % ONE_SECOND == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}
	// �]�肪0�̎��ʏ��Ԃɂ���
	else if (m_nColCnt % (ONE_SECOND / 2) == 0)
	{
		m_apScene2D->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	}
}

// =====================================================================================================================================================================
//
// �o�u���\�[�g �傫����
//
// =====================================================================================================================================================================
void CRankingUI::BubbleSort(std::vector<int> &data)
{
	for (int nCnt = 0; nCnt < (int)data.size() - 1; nCnt++)
	{
		for (int num = (int)data.size() - 1; num > nCnt; num--)
		{
			if (data[num - 1] <= data[num])
			{  // �傫�����t�]���Ă���ӏ����������� swap
				std::swap(data[num - 1], data[num]);
			}
		}
	}

	// �������폜
	data.pop_back();
}

// =====================================================================================================================================================================
//
// �����L���O�X�R�A�ƃv���C���[�̃X�R�A���r
//
// =====================================================================================================================================================================
bool CRankingUI::BubbleSort_Compare(std::vector<int> data)
{
	bool bRankIn = false;
	for (int nCnt = 0; nCnt < (int)data.size() - 1; nCnt++)
	{
		if (data[nCnt] <= m_nPlayerScore[PLAYER_SCORE_TOTAL])
		{  // �����L���O�X�R�A�̕���������������
			m_nRankNum = nCnt;
			return bRankIn = true;
		}
	}
	return bRankIn;
}

// =====================================================================================================================================================================
//
// �ڕW�̒l�ɂȂ�܂Œl���v�Z
//
// =====================================================================================================================================================================
bool CRankingUI::TargetValueAdd(const int &Target, int &Value, int Add, CMultiNumber *pMultiNumber)
{
	bool bEnd = false;
	// �ڕW�l���l��������������
	if (Target > Value)
	{
		// �l�����Z
		Value += Add;

		//���̍Đ��@ĩ���
		CManager::GetSound()->Play(CSound::LABEL_SE_ADD_SCORE00);

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
		return true;
	}

	return bEnd;
}

// =====================================================================================================================================================================
//
// �ڕW�̒l�ɂȂ�܂Œl���v�Z
//
// =====================================================================================================================================================================
bool CRankingUI::TargetValueSubtract(const int & Target, int & Value, int Subtract, CMultiNumber * pMultiNumber)
{
	bool bEnd = false;
	// �ڕW�l���l���傫����
	if (Target < Value)
	{
		// �l�����Z
		Value -= Subtract;

		//���̍Đ��@ĩ���
		CManager::GetSound()->Play(CSound::LABEL_SE_ADD_SCORE00);

		// �l���ڕW�l�𒴂�����
		if (Target > Value)
		{
			// �l�ɖڕW�l�̒l����
			Value = Target;
		}

		// �}���`�i���o�[�ɒl����
		pMultiNumber->SetMultiNumber((int)Value);
	}

	else
	{
		return true;
	}

	return bEnd;
}

// =====================================================================================================================================================================
//
// �����L���Oui�̐���
//
// =====================================================================================================================================================================
void CRankingUI::RankUiCreate()
{
	for (int nCnt = 0; nCnt < RANKING_UI_MAX - 3; nCnt++)
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
			m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.2f), (100.0f + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f), RANKINGSIZE);
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(CTexture::TEX_UI_RANKING_1st + nCnt - 1)));

			m_apScene2D[nCnt]->SetDisp(false);
		}
	}

	// �V�[��2D�̐���
	m_apScene2D[RANKING_SCORE_THANKS] = CScene2D::Create(D3DXVECTOR3(1000.0f, 650.0f, 0.0f), D3DXVECTOR3(240.0f, 60.0f, 0.0f));
	// �e�N�X�`���̊��蓖��
	m_apScene2D[RANKING_SCORE_THANKS]->BindTexture(CTexture::GetTexture((CTexture::TEX_TYPE)(CTexture::TEX_UI_RANKING_THANKS)));
	// ��\���ɂ��Ă���
	m_apScene2D[RANKING_SCORE_THANKS]->SetDisp(false);
}

// =====================================================================================================================================================================
//
// �����L���O�X�R�Aui�̐���
//
// =====================================================================================================================================================================
void CRankingUI::RankScoreUiCreate()
{
	// �X�R�A�̐���
	for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
	{
		// �X�R�A�̐���
		m_pRankScore[nCnt] = CMultiNumber::Create(
			D3DXVECTOR3((SCREEN_WIDTH * 0.4f), ((200.0f - 15.0f) + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f),
			RANKINGSCORESIZE,
			m_nRankingScore[nCnt],
			RANKINGSCOREDIGITS,
			CScene::OBJTYPE_UI);
	}
}

// =====================================================================================================================================================================
//
// �v���C���[�̃X�R�Aui����
//
// =====================================================================================================================================================================
void CRankingUI::PlayerScoreUiCreate()
{
	//if (CPlayer::GetTwoPPlayFlag())
	//{
		D3DXVECTOR3 pos[3];
		pos[0] = D3DXVECTOR3(150.0f, 300.0f, 0.0f);
		pos[1] = D3DXVECTOR3(650.0f, 300.0f, 0.0f);
		pos[2] = D3DXVECTOR3(300.0f, 500.0f, 0.0f);

		CTexture::TEX_TYPE type[3];
		type[0] = CTexture::TEX_UI_GAME_PLAYER_1P;
		type[1] = CTexture::TEX_UI_GAME_PLAYER_2P;
		type[2] = CTexture::TEX_UI_RANKING_TOTAL;

		D3DXVECTOR3 size[3];
		size[0] = D3DXVECTOR3(50.0f, 30.0f, 0.0f);
		size[1] = D3DXVECTOR3(50.0f, 30.0f, 0.0f);
		size[2] = D3DXVECTOR3(80.0f, 30.0f, 0.0f);

		for (int nCnt = 0; nCnt < 3; nCnt++)
		{
			// �V�[��2D�̐���
			m_apScene2D[RANKING_SCORE_1P + nCnt] = CScene2D::Create(D3DXVECTOR3(pos[nCnt]), size[nCnt]);
			// �e�N�X�`���̊��蓖��
			m_apScene2D[RANKING_SCORE_1P + nCnt]->BindTexture(CTexture::GetTexture(type[nCnt]));
			if (!CPlayer::GetTwoPPlayFlag())
			{
				/*m_apScene2D[PLAYER_SCORE_1P]->SetDisp(false);
				m_apScene2D[PLAYER_SCORE_2P]->SetDisp(false);*/
			}
		}

		pos[0] = D3DXVECTOR3(0.0f, -1000.0f, 0.0f);
		pos[1] = D3DXVECTOR3(0.0f, -1000.0f, 0.0f);
		pos[2] = D3DXVECTOR3(0.0f, -1000.0f, 0.0f);

		// �v���C���[�X�R�A�̐���
		for (int nCnt = 0; nCnt < PLAYER_SCORE_MAX; nCnt++)
		{
			if (nCnt != PLAYER_SCORE_TOTAL)
			{
				// �X�R�A�̐���
				m_pPlayerScore[nCnt] = CMultiNumber::Create(
					pos[nCnt],
					RANKINGSCORESIZE,
					m_nPlayerScore[nCnt],
					RANKINGSCOREDIGITS,
					CScene::OBJTYPE_UI);
			}
			else
			{
				// �X�R�A�̐���
				m_pPlayerScore[PLAYER_SCORE_TOTAL] = CMultiNumber::Create(
					pos[PLAYER_SCORE_TOTAL],
					RANKINGSCORESIZE,
					0,
					RANKINGSCOREDIGITS,
					CScene::OBJTYPE_UI);
			}
		}
	//}
}

// =====================================================================================================================================================================
//
// �����L���O�X�e�[�g���Ƃ̏���
//
// =====================================================================================================================================================================
void CRankingUI::RankingState()
{
	// �����L���O�̃X�e�[�g���Ƃ̏���
	switch (CRankingManager::GetRankingState())
	{
	case CRankingManager::RANKING_STATE_DRAW_SCORE:
		RankingState_Draw_Score();
		break;

	case CRankingManager::RANKING_STATE_SCORE_CALCULATION:
		RankingState_Score_Calculation();
		break;

	case CRankingManager::RANKING_STATE_COMPARE_RANKING:
		RankingState_Compare_Ranking();
		break;

	case CRankingManager::RANKING_STATE_SORT_RANKING:
		RankingState_Sort_Ranking();
		break;

	case CRankingManager::RANKING_STATE_RANKING:
		RankingState_Ranking();
		break;
	}
}

// =====================================================================================================================================================================
//
// �����L���O�X�e�[�gRANKING_STATE_DRAW_SCORE�̎�
//
// =====================================================================================================================================================================
void CRankingUI::RankingState_Draw_Score()
{
	if (CPlayer::GetTwoPPlayFlag())
	{
		D3DXVECTOR3 pos[3];
		pos[0] = D3DXVECTOR3(300.0f, 300.0f, 0.0f);
		pos[1] = D3DXVECTOR3(800.0f, 300.0f, 0.0f);
		pos[2] = D3DXVECTOR3(500.0f, 500.0f, 0.0f);

		m_nTimeToDraw--;

		if (m_nDrawCount >= PLAYER_SCORE_MAX)
		{
			CRankingManager::SetRankingState(CRankingManager::RANKING_STATE_SCORE_CALCULATION);
		}
		else
		{
			if (m_nTimeToDraw <= 0)
			{
				m_pPlayerScore[m_nDrawCount]->SetPos(pos[m_nDrawCount]);
				m_nTimeToDraw = ONE_SECOND;
				m_nDrawCount++;
			}
		}
	}
	else
	{
		for (int nCnt = 0; nCnt < 2; nCnt++)
		{
			m_apScene2D[nCnt + RANKING_SCORE_1P]->SetDisp(false);
		}

		D3DXVECTOR3 pos;
		pos = D3DXVECTOR3(500.0f, 500.0f, 0.0f);

		m_nTimeToDraw--;

		if (m_nTimeToDraw <= 0)
		{
			m_pPlayerScore[PLAYER_SCORE_TOTAL]->SetPos(pos);
			m_nPlayerScore[PLAYER_SCORE_TOTAL] = 0;
			CRankingManager::SetRankingState(CRankingManager::RANKING_STATE_SCORE_CALCULATION);
		}
	}
}

// =====================================================================================================================================================================
//
// �����L���O�X�e�[�gRANKING_STATE_SCORE_CALCULATION�̎�
//
// =====================================================================================================================================================================
void CRankingUI::RankingState_Score_Calculation()
{
	if (CPlayer::GetTwoPPlayFlag())
	{
		// 1P
		if (m_nPlayerScore[PLAYER_SCORE_1P] >= MILLION)
		{
			TargetValueSubtract(0, m_nPlayerScore[PLAYER_SCORE_1P], HUNDRED_THOUSAND, m_pPlayerScore[PLAYER_SCORE_1P]);
		}
		else if (m_nPlayerScore[PLAYER_SCORE_1P] >= HUNDRED_THOUSAND)
		{
			TargetValueSubtract(0, m_nPlayerScore[PLAYER_SCORE_1P], TEN_THOUSAND, m_pPlayerScore[PLAYER_SCORE_1P]);
		}
		else
		{
			TargetValueSubtract(0, m_nPlayerScore[PLAYER_SCORE_1P], ONE_THOUSAND, m_pPlayerScore[PLAYER_SCORE_1P]);
		}

		// 2P
		if (m_nPlayerScore[PLAYER_SCORE_2P] <= MILLION)
		{
			TargetValueSubtract(0, m_nPlayerScore[PLAYER_SCORE_2P], HUNDRED_THOUSAND, m_pPlayerScore[PLAYER_SCORE_2P]);
		}
		else if (m_nPlayerScore[PLAYER_SCORE_2P] <= HUNDRED_THOUSAND)
		{
			TargetValueSubtract(0, m_nPlayerScore[PLAYER_SCORE_2P], TEN_THOUSAND, m_pPlayerScore[PLAYER_SCORE_2P]);
		}
		else
		{
			TargetValueSubtract(0, m_nPlayerScore[PLAYER_SCORE_1P], ONE_THOUSAND, m_pPlayerScore[PLAYER_SCORE_1P]);
		}

		int nAdd = ONE_THOUSAND;
		if (m_RunkingData.nScore[PLAYER_SCORE_1P] + m_RunkingData.nScore[PLAYER_SCORE_2P] >= HUNDRED_THOUSAND)
		{
			nAdd = TEN_THOUSAND;
		}
		else if (m_RunkingData.nScore[PLAYER_SCORE_1P] + m_RunkingData.nScore[PLAYER_SCORE_2P] >= MILLION)
		{
			nAdd = HUNDRED_THOUSAND;
		}

		if (TargetValueAdd(m_RunkingData.nScore[PLAYER_SCORE_1P] + m_RunkingData.nScore[PLAYER_SCORE_2P],
			m_nPlayerScore[PLAYER_SCORE_TOTAL], nAdd, m_pPlayerScore[PLAYER_SCORE_TOTAL]))
		{
			m_pPlayerScore[PLAYER_SCORE_TOTAL]->Settype(CMultiNumber::TYPE_FLASHING);
			m_WaitTime--;
			if (m_WaitTime <= 0)
			{
				for (int nCnt = 0; nCnt < PLAYER_SCORE_MAX; nCnt++)
				{
					m_pPlayerScore[nCnt]->SetDisp(false);
				}
				for (int nCnt = 0; nCnt < 2; nCnt++)
				{
					m_apScene2D[nCnt + RANKING_SCORE_1P]->SetDisp(false);
				}

				for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
				{
					m_apScene2D[nCnt + RANKING_1st]->SetDisp(true);
				}

				m_WaitTime = ONE_SECOND;

				m_pPlayerScore[PLAYER_SCORE_TOTAL]->Settype(CMultiNumber::TYPE_NORMAL);
				m_apScene2D[RANKING_SCORE_TOTAL]->SetPosition(D3DXVECTOR3(1000.0f, 350.0f, 0.0f));
				m_pPlayerScore[PLAYER_SCORE_TOTAL]->SetPos(D3DXVECTOR3(1000.0f, 400.0f, 0.0f));
				m_pPlayerScore[PLAYER_SCORE_TOTAL]->SetDisp(true);
				RankScoreUiCreate();

				for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
				{
					m_pRankScore[nCnt]->SetPos(D3DXVECTOR3((SCREEN_WIDTH * 0.4f), 1000.0f, 0.0f));
					m_pRankScore[nCnt]->SetDisp(true);
				}
				CRankingManager::SetRankingState(CRankingManager::RANKING_STATE_COMPARE_RANKING);
			}
		}
	}
	else
	{
		int nAdd = ONE_THOUSAND;
		if (m_RunkingData.nScore[PLAYER_SCORE_1P] >= HUNDRED_THOUSAND)
		{
			nAdd = TEN_THOUSAND;
		}
		else if (m_RunkingData.nScore[PLAYER_SCORE_1P] >= MILLION)
		{
			nAdd = HUNDRED_THOUSAND;
		}

		if (TargetValueAdd(m_RunkingData.nScore[PLAYER_SCORE_1P],
			m_nPlayerScore[PLAYER_SCORE_TOTAL], nAdd, m_pPlayerScore[PLAYER_SCORE_TOTAL]))
		{
			m_pPlayerScore[PLAYER_SCORE_TOTAL]->Settype(CMultiNumber::TYPE_FLASHING);
			m_WaitTime--;
			if (m_WaitTime <= 0)
			{
				for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
				{
					m_apScene2D[nCnt + RANKING_1st]->SetDisp(true);
				}

				m_WaitTime = 120;

				m_pPlayerScore[PLAYER_SCORE_TOTAL]->Settype(CMultiNumber::TYPE_NORMAL);
				m_apScene2D[RANKING_SCORE_TOTAL]->SetPosition(D3DXVECTOR3(1000.0f, 350.0f, 0.0f));
				m_pPlayerScore[PLAYER_SCORE_TOTAL]->SetPos(D3DXVECTOR3(1000.0f, 400.0f, 0.0f));
				m_pPlayerScore[PLAYER_SCORE_TOTAL]->SetDisp(true);
				RankScoreUiCreate();

				for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
				{
					m_pRankScore[nCnt]->SetPos(D3DXVECTOR3((SCREEN_WIDTH * 0.4f), 1000.0f, 0.0f));
					m_pRankScore[nCnt]->SetDisp(true);
				}
				CRankingManager::SetRankingState(CRankingManager::RANKING_STATE_COMPARE_RANKING);
			}
		}
	}
}

// =====================================================================================================================================================================
//
// �����L���O�X�e�[�gRANKING_STATE_COMPARE_RANKING�̎�
//
// =====================================================================================================================================================================
void CRankingUI::RankingState_Compare_Ranking()
{
	if (!m_bCompleted)
	{
		for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
		{
			m_pRankScore[nCnt]->SetPos(D3DXVECTOR3(
				m_pRankScore[nCnt]->GetPos().x,
				m_pRankScore[nCnt]->GetPos().y - m_RankScoreMove.y,
				m_pRankScore[nCnt]->GetPos().z));


			if (m_pRankScore[nCnt]->GetPos().y <= ((200.0f - 15.0f) + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt)
			{
				m_pRankScore[nCnt]->SetPos(D3DXVECTOR3(m_pRankScore[nCnt]->GetPos().x, ((200.0f - 15.0f) + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f));

				if (nCnt == SCORE_1st)
				{
					m_bCompleted = true;
					m_RankScoreMove = ZeroVector3;
				}
			}
		}
	}

	if (m_bCompleted)
	{
		m_WaitTime--;

		if (m_WaitTime <= 0)
		{
			if (BubbleSort_Compare(m_nRankingScore))
			{
				m_nTimeToFlash--;
				if (m_nTimeToFlash <= 0)
				{
					m_nTimeToExplosion--;
					if (m_nTimeToExplosion <= 0)
					{
						m_pRankScore[m_nRankNum]->Settype(CMultiNumber::TYPE_NORMAL);
						// ��ʊO��
						m_pRankScore[m_nRankNum]->SetPos(OUTSIDE_SCREEN);
					}
					else
					{
						//����
						if (m_nTimeToExplosion % 3 == 0)
						{
							CParticle::CreateFromText(
								D3DXVECTOR3(
									(m_pRankScore[m_nRankNum]->GetPos().x) + CHossoLibrary::RandomVector3(100.0f).x,
									(SCREEN_HEIGHT - m_pRankScore[m_nRankNum]->GetPos().y) + CHossoLibrary::RandomVector3(100.0f).y,
									0.0f),
								ZeroVector3,
								CParticleParam::EFFECT_NO_COLLISION_EXPLOSION_RANK);
						}
					}
				}
				else
				{
					m_pRankScore[m_nRankNum]->Settype(CMultiNumber::TYPE_FLASHING);
				}
			}
			else
			{
				m_nTimeToFlash--;
				if (m_nTimeToFlash <= 0)
				{
					m_nTimeToExplosion--;
					if (m_nTimeToExplosion <= 0)
					{
						// ��ʊO��
						m_pPlayerScore[PLAYER_SCORE_TOTAL]->SetPos(OUTSIDE_SCREEN);
						m_pPlayerScore[PLAYER_SCORE_TOTAL]->Settype(CMultiNumber::TYPE_NORMAL);
					}
					else
					{
						//����
						if (m_nTimeToExplosion % 3 == 0)
						{
							CParticle::CreateFromText(m_pPlayerScore[PLAYER_SCORE_TOTAL]->GetPos() + CHossoLibrary::RandomVector3(100.0f),
								ZeroVector3,
								CParticleParam::EFFECT_NO_COLLISION_EXPLOSION_RANK);
						}
					}
				}
				else
				{
					m_pPlayerScore[PLAYER_SCORE_TOTAL]->Settype(CMultiNumber::TYPE_FLASHING);
				}
			}

			if (m_nTimeToExplosion <= 0)
			{
				if (!m_bCompletedEnd)
				{
					for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
					{
						m_pRankScore[nCnt]->SetPos(D3DXVECTOR3(
							m_pRankScore[nCnt]->GetPos().x,
							m_pRankScore[nCnt]->GetPos().y + m_RankScoreMove.y,
							m_pRankScore[nCnt]->GetPos().z));


						if (m_pRankScore[nCnt]->GetPos().y >= 900.0f)
						{
							m_pRankScore[nCnt]->SetPos(D3DXVECTOR3(m_pRankScore[nCnt]->GetPos().x, 900.0f, 0.0f));

							if (nCnt == SCORE_1st)
							{
								m_bCompletedEnd = true;
							}
						}
					}
					m_RankScoreMove.y += 0.75f;
				}


				if (m_bCompletedEnd)
				{
					CRankingManager::SetRankingState(CRankingManager::RANKING_STATE_SORT_RANKING);
				}
			}

		}
	}
	else
	{
		m_RankScoreMove.y += 0.05f;
	}
}

// =====================================================================================================================================================================
//
// �����L���O�X�e�[�gRANKING_STATE_SORT_RANKING�̎�
//
// =====================================================================================================================================================================
void CRankingUI::RankingState_Sort_Ranking()
{
	// �X�R�A����ʊO�Ɉړ�
	m_pPlayerScore[PLAYER_SCORE_TOTAL]->SetPos(OUTSIDE_SCREEN);

	// �����L���O�v�Z
	RankingCalculation();
	for (int nCnt = 0; nCnt < PLAYER_SCORE_MAX; nCnt++)
	{
		m_apScene2D[nCnt + RANKING_SCORE_1P]->SetDisp(false);
	}
	m_bCompletedEnd = false;
	// �����L���O�X�R�A�̃Z�[�u
	RankingDataSave();
	m_WaitTime = ONE_SECOND*4;
	CRankingManager::SetRankingState(CRankingManager::RANKING_STATE_RANKING);
}

// =====================================================================================================================================================================
//
// �����L���O�X�e�[�gRANKING_STATE_RANKING�̎�
//
// =====================================================================================================================================================================
void CRankingUI::RankingState_Ranking()
{
	if (!m_bCompletedEnd)
	{
		for (int nCnt = 0; nCnt < RANKING_NUM; nCnt++)
		{
			m_pRankScore[nCnt]->SetPos(D3DXVECTOR3(1400.0f, ((200.0f - 15.0f) + (VERTICAL_SPACE * nCnt)) + RANKING_SPACE * nCnt, 0.0f));
			m_pRankScore[nCnt]->SetDisp(true);
			if (nCnt >=  RANKING_NUM-1)
			{
				m_bCompletedEnd = true;
			}
		}
	}

	if (m_bCompletedEnd)
	{
		m_bMoveRank[SCORE_7th] = true;

		for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
		{
			if (m_bMoveRank[nCnt])
			{
				m_pRankScore[nCnt]->SetPos(D3DXVECTOR3(
					m_pRankScore[nCnt]->GetPos().x + m_RankScoreMove.x,
					m_pRankScore[nCnt]->GetPos().y,
					m_pRankScore[nCnt]->GetPos().z));
			}

			if (m_pRankScore[nCnt]->GetPos().x <= SCREEN_WIDTH * 0.5f)
			{
				m_pRankScore[nCnt]->SetPos(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, m_pRankScore[nCnt]->GetPos().y, 0.0f));

				if (nCnt != SCORE_1st)
				{
					m_bMoveRank[nCnt - 1] = true;
				}
				else
				{
					for (int nCnt = 0; nCnt < SCORE_MAX; nCnt++)
					{
						if (m_nRankingScore[m_nRankNum] == m_nPlayerScore[PLAYER_SCORE_TOTAL])
						{
							m_pRankScore[m_nRankNum]->Settype(CMultiNumber::TYPE_FLASHING);

							// 1�ʂ�������
							if (m_nRankNum == SCORE_1st)
							{
								m_bEvaluation[RANKING_EVALUATION_BEST] = true;
							}
							// 2�ʂ���3�ʂ�������
							else if (m_nRankNum >= SCORE_2nd && m_nRankNum <= SCORE_3rd)
							{
								m_bEvaluation[RANKING_EVALUATION_SECONDBEDT] = true;
							}
							// 4�ʂ���7�ʂ�������
							else if (m_nRankNum >= SCORE_4th && m_nRankNum <= SCORE_7th)
							{
								m_bEvaluation[RANKING_EVALUATION_THIRDBEST] = true;
							}
							// 4�ʂ���7�ʂ�������
							else
							{
								m_bEvaluation[RANKING_EVALUATION_NONE] = true;
							}
						}
					}

					m_WaitTime--;
					if (m_WaitTime <= 0)
					{
						m_apScene2D[RANKING_SCORE_THANKS]->SetDisp(true);
					}
				}
			}
		}

		m_RankScoreMove.x -= 0.25f;
	}

	// ���ʂ��Ƃ̕]��
	RankingEvaluation();

	// �Ō��ui���`�悳�ꂽ��
	if (m_apScene2D[RANKING_SCORE_THANKS]->GetDisp())
	{
		if (m_apScene2D[RANKING_SCORE_THANKS]->GetColor().a <= 0.0f)
		{
			m_fCol += 0.02f;
		}
		if (m_apScene2D[RANKING_SCORE_THANKS]->GetColor().a >= 1.0f)
		{
			m_fCol -= 0.02f;
		}

		m_apScene2D[RANKING_SCORE_THANKS]->SetColor(D3DXCOLOR(
			m_apScene2D[RANKING_SCORE_THANKS]->GetColor().r,
			m_apScene2D[RANKING_SCORE_THANKS]->GetColor().g,
			m_apScene2D[RANKING_SCORE_THANKS]->GetColor().b,
			m_apScene2D[RANKING_SCORE_THANKS]->GetColor().a + m_fCol));

		m_nTimeToTransition++;

		if (m_nTimeToTransition >= WAITTIME_BASE)
		{
			// �Q�[�����[�h�֏�ԑJ��
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_TITLE);
		}
	}
}

// =====================================================================================================================================================================
//
// ���ʂ��Ƃ̕]��
//
// =====================================================================================================================================================================
void CRankingUI::RankingEvaluation()
{
	if (m_bEvaluation[RANKING_EVALUATION_BEST])
	{
		m_nTimeToFireworks--;
		// �ԉ�
		if (m_nTimeToFireworks % 3 == 0)
		{
			CParticle::CreateFromText(SCREEN_CENTER_POS + CHossoLibrary::RandomVector3(SCREEN_WIDTH * 0.5f),
				ZeroVector3,
				CParticleParam::EFFECT_NO_COLLISION_FIREWORKS1);
		}
		if (m_nTimeToFireworks % 4 == 0)
		{
			CParticle::CreateFromText(SCREEN_CENTER_POS + CHossoLibrary::RandomVector3(SCREEN_WIDTH * 0.5f),
				ZeroVector3,
				CParticleParam::EFFECT_NO_COLLISION_FIREWORKS2);
		}
		if (m_nTimeToFireworks % 5 == 0)
		{
			CParticle::CreateFromText(SCREEN_CENTER_POS + CHossoLibrary::RandomVector3(SCREEN_WIDTH * 0.5f),
				ZeroVector3,
				CParticleParam::EFFECT_NO_COLLISION_FIREWORKS3);
		}
	}
	if (m_bEvaluation[RANKING_EVALUATION_SECONDBEDT])
	{
		m_nTimeToFireworks--;
		// �ԉ�
		if (m_nTimeToFireworks % 20 == 0)
		{
			CParticle::CreateFromText(SCREEN_CENTER_POS + CHossoLibrary::RandomVector3(SCREEN_WIDTH * 0.5f),
				ZeroVector3,
				CParticleParam::EFFECT_NO_COLLISION_FIREWORKS1);
		}
		if (m_nTimeToFireworks % 30 == 0)
		{
			CParticle::CreateFromText(SCREEN_CENTER_POS + CHossoLibrary::RandomVector3(SCREEN_WIDTH * 0.5f),
				ZeroVector3,
				CParticleParam::EFFECT_NO_COLLISION_FIREWORKS2);
		}
	}

	if (m_bEvaluation[RANKING_EVALUATION_THIRDBEST])
	{
		m_nTimeToFireworks--;
		// �ԉ�
		if (m_nTimeToFireworks % 60 == 0)
		{
			CParticle::CreateFromText(SCREEN_CENTER_POS + CHossoLibrary::RandomVector3(SCREEN_WIDTH * 0.5f),
				ZeroVector3,
				CParticleParam::EFFECT_NO_COLLISION_FIREWORKS1);
		}
	}
}
