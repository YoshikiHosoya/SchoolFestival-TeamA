// =====================================================================================================================================================================
//
// �X�R�A�}�l�[�W���[�̏��� [scoremanager.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "main.h"
#include "scoremanager.h"
#include "manager.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
int CScoreManager::m_nScore[SCORE_TYPE_MAX]		= {};
SCORE_DATA	CScoreManager::m_ScoreData			= {};

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CScoreManager::m_ScoreFileName =
{
	"data/Load/Score/ScoreData.txt" 			// �X�R�A�̏��
};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CScoreManager::CScoreManager()
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CScoreManager::~CScoreManager()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CScoreManager::Init(void)
{
	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CScoreManager::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CScoreManager::Update(void)
{
}

// =====================================================================================================================================================================
//
// �A�C�e���̏��̐ݒ�
//
// =====================================================================================================================================================================
void CScoreManager::SetScoreData()
{
	m_nScore[SCORE_ITEM_FRUIT]			 = m_ScoreData.nFruit;
	m_nScore[SCORE_ITEM_FOOD]			 = m_ScoreData.nFood;
	m_nScore[SCORE_ITEM_GCOIN]			 = m_ScoreData.nGoldCoin;
	m_nScore[SCORE_ITEM_SCOIN]			 = m_ScoreData.nSilverCoin;
	m_nScore[SCORE_ITEM_BCOIN]			 = m_ScoreData.nBronzeCoin;
	m_nScore[SCORE_ITEM_BEAR]			 = m_ScoreData.nBear;
	m_nScore[SCORE_ITEM_LETTER]			 = m_ScoreData.nLetter;
	m_nScore[SCORE_ITEM_DIAMOND]		 = m_ScoreData.nDiamond;

	m_nScore[SCORE_ITEM_ANI_BEAR]		 = m_ScoreData.nAni_Bear;
	m_nScore[SCORE_ITEM_ANI_COIN]		 = m_ScoreData.nAni_Coin;
	m_nScore[SCORE_ITEM_ANI_FOOD]		 = m_ScoreData.nAni_Food;
	m_nScore[SCORE_ITEM_ANI_LETTER]		 = m_ScoreData.nAni_Letter;
	m_nScore[SCORE_ITEM_ANI_MEDAL]		 = m_ScoreData.nAni_Jewelry;
	m_nScore[SCORE_ITEM_ANI_JEWELRY]	 = m_ScoreData.nAni_Medal;
	m_nScore[SCORE_ITEM_ANI_MONKEY]		 = m_ScoreData.nAni_Monkey;

	m_nScore[SCORE_DAMAGE_BULLET]		 = m_ScoreData.nBullet;
	m_nScore[SCORE_DAMAGE_ATTACK]		 = m_ScoreData.nAttack;
	m_nScore[SCORE_RESCUE_PRISONER]		 = m_ScoreData.nPrisoner;
	m_nScore[SCORE_BONUS]				 = m_ScoreData.nBonus;
	m_nScore[SCORE_KILLED_BOSS]			 = m_ScoreData.nBoss;
}

// =====================================================================================================================================================================
//
// �X�R�A�̃f�[�^�̓ǂݍ���
//
// =====================================================================================================================================================================
void CScoreManager::ScoreLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

									// �t�@�C�����J��
	pFile = fopen(m_ScoreFileName, "r");

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
						if (strcmp(cHeadText, "FRUIT") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nFruit);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "FOOD") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nFood);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "GCOIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nGoldCoin);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "SCOIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nSilverCoin);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "BCOIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBronzeCoin);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "BEAR") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBear);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "LETTER") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nLetter);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "DIAMOND") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nDiamond);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "ANI_BEAR") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Bear);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "ANI_COIN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Coin);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "ANI_FOOD") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Food);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "ANI_LETTER") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Letter);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "ANI_MEDAL") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Jewelry);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "ANI_JEWELRY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Medal);	// ��r�p�e�L�X�g��BEAR����
						}
						if (strcmp(cHeadText, "ANI_MONKEY") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAni_Monkey);	// ��r�p�e�L�X�g��BEAR����
						}

						// BEAR��������
						else if (strcmp(cHeadText, "BULLET") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBullet);	// ��r�p�e�L�X�g��BULLET����
						}
						// BEAR��������
						else if (strcmp(cHeadText, "ATTACK") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nAttack);	// ��r�p�e�L�X�g��ATTACK����
						}
						// BEAR��������
						else if (strcmp(cHeadText, "PRISONER") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nPrisoner);// ��r�p�e�L�X�g��PRISONER����
						}
						// BEAR��������
						else if (strcmp(cHeadText, "BONUS") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBonus);	// ��r�p�e�L�X�g��BONUS����
						}
						// BEAR��������
						else if (strcmp(cHeadText, "BOSS") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ScoreData.nBoss);	// ��r�p�e�L�X�g��BOSS����
						}
						else if (strcmp(cHeadText, "END_SCORESET") == 0)
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
		MessageBox(NULL, "�X�R�A�̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}

	// �ǂݍ��񂾏��̑��
	SetScoreData();
}
