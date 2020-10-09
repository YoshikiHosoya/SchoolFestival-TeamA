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
#include "game.h"
#include "bg.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define VERTICAL_SPACE		(70.0f)									// �c�̊Ԋu
#define WAITTIME_BASE		(180)									// �҂�����
#define ONE_SECOND			(60)									// 1�b
#define RANKINGSIZE			(D3DXVECTOR3(80.0f, 50.0f, 0.0f))		// �����L���OUI�̃T�C�Y
#define PLAYER_SCORE_SIZE	(D3DXVECTOR3(70.0f, 150.0f, 0.0f))		// �v���C���[�X�R�A�̃T�C�Y

#define RANKING_GOTITLESIZE			(D3DXVECTOR3(800.0f, 300.0f, 0.0f))		// �����L���OUI�̃T�C�Y	�^�C�g����

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

	// �w�i�̐���
	CBg::Create(60);
	// �X�R�A�̓ǂݍ���
	RankingDataLoad();
	// UI����
	RankingUICreate();
	// �X�R�A����
	RankingScoreCreate();
	// �����L���O�̌v�Z
	RankingCalculation();
	// �v���C���[�X�R�A����
	PlayerScoreCreate();

	// �X�R�A�̏�������
	RankingDataSave();

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
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.75f), 90.0f, 0.0f), D3DXVECTOR3(700.0f, 200.0f, 0.0f), CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_NAME));
		}
		// �v���C���[�X�R�A
		else if (nCnt == (int)RANKING_UI::RANKING_SCORE)
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.25f), SCREEN_HEIGHT * 0.35f, 0.0f), RANKING_GOTITLESIZE, CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_RANKING_SCORE));
		}
		// �^�C�g����
		else if (nCnt == (int)RANKING_UI::RANKING_GO_TITLE)
		{
			// �V�[��2D�̐���
			m_apScene2D.emplace_back(CScene2D::Create_Shared(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 650.0f, 0.0f), D3DXVECTOR3(500.0f, 200.0f, 0.0f), CScene::OBJTYPE_UI));
			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_ENTER));
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
	m_pPlayerScore.emplace_back((CMultiNumber::Create(D3DXVECTOR3((SCREEN_WIDTH * 0.2f), SCREEN_HEIGHT * 0.6f, 0.0f),
											PLAYER_SCORE_SIZE,
											CGame::GetScore(),
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
//�����L���O�̃f�[�^�̌v�Z
//------------------------------------------------------------------------------
void CRanking::RankingCalculation()
{
	// �����Ƀv���C���[�̃X�R�A�f�[�^��ǉ�
	m_nRankingScore.emplace_back(CGame::GetScore());
	// �X�R�A��傫�����ɓ���ւ���
	BubbleSort(m_nRankingScore);

	for (int nCnt = 0; nCnt < (int)m_nRankingScore.size(); nCnt++)
	{
		if (m_nRankingScore[nCnt] == CGame::GetScore())
		{
			m_apRankScore[nCnt]->Settype(CMultiNumber::TYPE_FLASHING);
		}
		// �}���`�i���o�[�ɒl����
		m_apRankScore[nCnt]->SetMultiNumber((int)m_nRankingScore[nCnt]);
	}
}

//------------------------------------------------------------------------------
//�o�u���\�[�g
//------------------------------------------------------------------------------
void CRanking::BubbleSort(std::vector<int>& data)
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

//------------------------------------------------------------------------------
//�����L���O�Z�[�u
//------------------------------------------------------------------------------
void CRanking::RankingDataSave()
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
		fprintf(pFile, "	RANKING_1st	= %d\n", m_nRankingScore[(int)RANKING_SCORE::SCORE_1st]);
		fprintf(pFile, "	RANKING_2nd	= %d\n", m_nRankingScore[(int)RANKING_SCORE::SCORE_2nd]);
		fprintf(pFile, "	RANKING_3rd	= %d\n", m_nRankingScore[(int)RANKING_SCORE::SCORE_3rd]);
		fprintf(pFile, "	RANKING_4th	= %d\n", m_nRankingScore[(int)RANKING_SCORE::SCORE_4th]);
		fprintf(pFile, "	RANKING_5th	= %d\n", m_nRankingScore[(int)RANKING_SCORE::SCORE_5th]);


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