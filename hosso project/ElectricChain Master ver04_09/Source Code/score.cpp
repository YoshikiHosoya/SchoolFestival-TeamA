//------------------------------------------------------------------------------
//
//�X�R�A����  [score.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "score.h"
#include "enemy.h"
#include "multinumber.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_KILL_POS				(D3DXVECTOR3(1000.0f,650.0f,0.0f))			//�������W
#define DEFAULT_COMBO_POS				(D3DXVECTOR3(1000.0f,550.0f,0.0f))			//�������W
#define DEFAULT_CHAIN_POS				(D3DXVECTOR3(1000.0f,200.0f,0.0f))			//�������W

#define DEFAULT_KILL_NUMBER_SIZE		(D3DXVECTOR3(60.0f, 120.0f, 0.0f))			//�i���o�[�̑傫��
#define DEFAULT_COMBO_NUMBER_SIZE		(D3DXVECTOR3(35.0f, 70.0f, 0.0f))			//�i���o�[�̑傫��
#define DEFAULT_CHAIN_NUMBER_SIZE		(D3DXVECTOR3(35.0f, 70.0f, 0.0f))			//�i���o�[�̑傫��
#define RANKING_NUM						(5)											//�����L���O�̐l��

#define SCORE_DIGITS					(4)											//�X�R�A�̌���
#define SCORE_DATA						("data/SAVEDATA/score.txt")					//�X�R�A�̃e�L�X�g��
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<int> CScore::m_nRankingScoreList(5);
int CScore::m_nScore = 0;
int CScore::m_nKill = 0;
int CScore::m_nCombo = 0;

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CScore::CScore()
{
	//������
	m_nScore = 0;
	m_nKill = 0;
	m_nCombo = 0;
	m_pMultiNumberLIst.clear();
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CScore::~CScore()
{
	m_pMultiNumberLIst.clear();
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CScore::Init()
{
	//��������
	m_pMultiNumberLIst.emplace_back(CMultiNumber::Create(DEFAULT_KILL_POS, DEFAULT_KILL_NUMBER_SIZE, 0, SCORE_DIGITS, CScene::OBJTYPE_NUMBER));
	m_pMultiNumberLIst.emplace_back(CMultiNumber::Create(DEFAULT_COMBO_POS, DEFAULT_COMBO_NUMBER_SIZE, 0, SCORE_DIGITS, CScene::OBJTYPE_NUMBER));

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CScore::Uninit()
{
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CScore::Update()
{

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CScore::Draw()
{

}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::unique_ptr<CScore> CScore::Create()
{
	//�ϐ��錾
	std::unique_ptr<CScore> pScore(new CScore);

	//����������
	pScore->Init();

	//���^�[��
	return pScore;
}

//------------------------------------------------------------------------------
//�X�R�A���Z����
//------------------------------------------------------------------------------
void CScore::AddKill(int nValue)
{
	//�Â����ۑ�
	int nNumKillOld = m_nKill;

	//�l�����Z
	m_nKill += nValue;

	//50�L��������
	if (m_nKill % 50 == 0)
	{
		//�i���o�[����
		std::shared_ptr<CMultiNumber> pMultiNumber = CMultiNumber::Create(SCREEN_CENTER_POS, D3DXVECTOR3(150.0f, 300.0f, 0.0f), m_nKill,3, CScene::OBJTYPE_FRONTUI);
		pMultiNumber->Settype(CMultiNumber::TYPE_CENTER_DISAPPEAR);
	}

	//�l�̃e�N�X�`�����X�V
	if (m_pMultiNumberLIst[CScore::SCORE_KILL])
	{
		m_pMultiNumberLIst[CScore::SCORE_KILL]->SetMultiNumber(m_nKill);
		m_pMultiNumberLIst[CScore::SCORE_KILL]->SetChangeAnimation(m_nKill,nNumKillOld);
	}
}
//------------------------------------------------------------------------------
//�X�R�A���Z����
//------------------------------------------------------------------------------
void CScore::AddCombo(int nValue)
{
	//�Â����ۑ�
	int nNumComboOld = m_nCombo;

	//�l�����Z
	m_nCombo += nValue;

	//�l�̃e�N�X�`�����X�V
	if (m_pMultiNumberLIst[CScore::SCORE_COMBO])
	{
		m_pMultiNumberLIst[CScore::SCORE_COMBO]->SetMultiNumber(m_nCombo);
		m_pMultiNumberLIst[CScore::SCORE_COMBO]->SetChangeAnimation(m_nCombo, nNumComboOld);
	}
}
//------------------------------------------------------------------------------
//�`�F�C�����v�Z
//------------------------------------------------------------------------------
void CScore::SetNowChain()
{
	//�Â����ۑ�
	int nNumNowChainOld = m_nNowChain;

	//�X�^�����Ă鐔�擾
	m_nNowChain = CEnemy::GetStanEnemyNum();

	//�l�̃e�N�X�`�����X�V
	if (m_pMultiNumberLIst[CScore::SCORE_NOWCHAIN])
	{
		m_pMultiNumberLIst[CScore::SCORE_NOWCHAIN]->SetMultiNumber(m_nNumChain);
	}
}
//------------------------------------------------------------------------------
//�X�R�A���Z����
//------------------------------------------------------------------------------
void CScore::AddNumChain(int nValue)
{
	//�Â����ۑ�
	int mNumChainOld = m_nNumChain;

	//�l�����Z
	m_nNumChain += nValue;

	//�l�̃e�N�X�`�����X�V
	if (m_pMultiNumberLIst[CScore::SCORE_NUMCHAIN])
	{
		m_pMultiNumberLIst[CScore::SCORE_NUMCHAIN]->SetMultiNumber(m_nNumChain);
	}
}

//------------------------------------------------------------------------------
//�����L���O�̃X�R�A�擾
//------------------------------------------------------------------------------
int CScore::GetRankingScore(int nRank)
{
	return m_nRankingScoreList[nRank];
}

//------------------------------------------------------------------------------
// �X�R�A�ǂݍ���
//------------------------------------------------------------------------------
HRESULT CScore::LoadScore()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	// �t�@�C���J
	pFile = fopen(SCORE_DATA, "r");

	// �J����
	if (pFile != nullptr)
	{
		//5�ʂ܂�
		for (int nCnt = 0; nCnt < RANKING_NUM; nCnt++)
		{
			fscanf(pFile, "%d", &m_nRankingScoreList[nCnt]); // ���O
			std::cout << "LoadScore - " << nCnt << " - Score >> " << m_nRankingScoreList[nCnt] << NEWLINE;

		}
		// �t�@�C����
		fclose(pFile);
	}

	// �J���Ȃ�
	else
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
// �X�R�A�Z�[�u
//------------------------------------------------------------------------------
HRESULT CScore::SaveScore()
{
	//�X�R�A�v�Z
	m_nScore = m_nCombo * 50 + m_nKill * 1000;

	//�t�@�C���̃|�C���^
	FILE *pFile;

	//��ԍŌ�̂���X�R�A������������
	if (m_nScore >= m_nRankingScoreList[m_nRankingScoreList.size() - 1])
	{
		//�z��ɒǉ�
		m_nRankingScoreList.emplace_back(m_nScore);

		//���̕ϐ�
		int nData;

		//�\�[�g �~��
		for (size_t nCntSave01 = 0; nCntSave01 < m_nRankingScoreList.size(); nCntSave01++)
		{
			for (size_t nCntSave02 = nCntSave01 + 1; nCntSave02 < m_nRankingScoreList.size(); nCntSave02++)
			{
				if (m_nRankingScoreList[nCntSave01] < m_nRankingScoreList[nCntSave02])
				{
					nData = m_nRankingScoreList[nCntSave02];
					m_nRankingScoreList[nCntSave02] = m_nRankingScoreList[nCntSave01];
					m_nRankingScoreList[nCntSave01] = nData;
				}
			}
		}
		//��ԒႩ�����z�����O
		m_nRankingScoreList.pop_back();
	}

	// �t�@�C���J
	pFile = fopen(SCORE_DATA, "w");

	// �J����
	if (pFile != nullptr)
	{
		for (size_t nCnt = 0; nCnt < m_nRankingScoreList.size(); nCnt++)
		{
			fprintf(pFile, "%d\n\n", m_nRankingScoreList[nCnt]);	// �|�C���g
			std::cout << "SaveScore - " << nCnt << " - Score >> " << m_nRankingScoreList[nCnt] << NEWLINE;
		}
		// �t�@�C����
		fclose(pFile);
	}
	// �J���Ȃ�
	else
	{
		std::cout << "Score SAVEFAILED!! can't open file!" << NEWLINE;
		return E_FAIL;
	}

	return S_OK;
}