// =====================================================================================================================================================================
//
// �����L���OUI�̏��� [rankingUI.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _RANKINGUI_H_
#define _RANKINGUI_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "UI.h"
#include <array>
#include "player.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define RANKING_NUM (7) //�\�����郉���L���O�f�[�^�̐�

// =====================================================================================================================================================================
// �����L���O�̃f�[�^
// =====================================================================================================================================================================
struct RUNKING_DATA
{
	int					nScore[CPlayer::PLAYER_NUM_TWO];					// �X�R�A
};

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CScene2D;
class CMultiNumber;

// =====================================================================================================================================================================
// �����L���OUI�N���X
// =====================================================================================================================================================================
class CRankingUI : CUI
{
public:
	// �����L���OUI�̎��
	enum RANKING_UI
	{
		RANKING_NAME,				// ���O���S
		RANKING_1st,				// ����1��
		RANKING_2nd,				// ����2��
		RANKING_3rd,				// ����3��
		RANKING_4th,				// ����4��
		RANKING_5th,				// ����5��
		RANKING_6th,				// ����6��
		RANKING_7th,				// ����7��
		RANKING_SCORE_1P,			// 2�l�v���C�p�\���X�R�A
		RANKING_SCORE_2P,			// 2�l�v���C�p�\���X�R�A
		RANKING_SCORE_TOTAL,		// 2�l�v���C�p�\���X�R�A
		RANKING_SCORE_THANKS,		// �V��ł���Ă��肪�Ƃ�
		RANKING_UI_MAX
	};

	// �����L���O�f�[�^
	enum RANKING_SCORE
	{
		SCORE_1st,					// ����1��
		SCORE_2nd,					// ����2��
		SCORE_3rd,					// ����3��
		SCORE_4th,					// ����4��
		SCORE_5th,					// ����5��
		SCORE_6th,					// ����6��
		SCORE_7th,					// ����7��
		SCORE_MAX
	};

	// 2�l�v���C�p�X�R�A�f�[�^
	enum PLAYER_SCORE
	{
		PLAYER_SCORE_1P,				// ����1��
		PLAYER_SCORE_2P,				// ����2��
		PLAYER_SCORE_TOTAL,				// ���v�X�R�A
		PLAYER_SCORE_MAX
	};

	// �����L���O�̕]�������N
	enum RANKING_EVALUATION
	{
		RANKING_EVALUATION_BEST,			// �ō��]�� 1
		RANKING_EVALUATION_SECONDBEDT,		// �]��	2����3��
		RANKING_EVALUATION_THIRDBEST,		// �]�� 4����7��
		RANKING_EVALUATION_NONE,			// �]������
		RANKING_EVALUATION_MAXNUM			// �ő吔
	};

	CRankingUI();							// �R���X�g���N�^
	~CRankingUI();							// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT					Init(void);		// ������
	void					Uninit(void);	// �I��
	void					Update(void);	// �X�V
	void					Draw(void);		// �`��

	/* �ÓI�����o�֐� */
	static  CRankingUI		*Create();									// �����L���OUI�̐���
	static	void			PlayerScoreSave();							// �v���C���[�̃X�R�A���f�[�u

	/* �����o�֐� */

private:
	/* �ÓI�����o�֐� */

	/* �����o�֐� */
	bool					ConfirmExistsRankingFile();					// �����L���O�t�@�C�������݂��邩�m�F
	void					RankingDataSave();							// �����L���O�̃f�[�^�̃Z�[�u
	void					RankingDataLoad();							// �����L���O�̃f�[�^�̃��[�h
	void					PlayerScoreLoad();							// �v���C���[�̃X�R�A�����[�h
	void					RankingCalculation();						// ���ʂ̌v�Z

	void					Flashing(CScene2D *m_apScene2D);			// �_�ŏ���
	void					BubbleSort(std::vector<int> &data);			// �D��x�̓���ւ� ��������0�Ԗڂ���
	bool					BubbleSort_Compare(std::vector<int> data);	// �����L���O�̒l�ƃX�R�A�̒l���r

	bool					TargetValueAdd(const int &Target,
		int &Value,
		int Add,
		CMultiNumber *pMultiNumber);			// �ڕW�̒l�ɂȂ�܂Œl���v�Z����

	bool					TargetValueSubtract(const int &Target,
		int &Value,
		int Subtract,
		CMultiNumber *pMultiNumber);			// �ڕW�̒l�ɂȂ�܂Œl���}�C�i�X�Ɍv�Z����

	void					RankUiCreate();
	void					RankScoreUiCreate();
	void					PlayerScoreUiCreate();

	void					RankingState();// �X�e�[�g���Ƃ̕]��
	void					RankingState_Draw_Score();
	void					RankingState_Score_Calculation();
	void					RankingState_Compare_Ranking();
	void					RankingState_Sort_Ranking();
	void					RankingState_Ranking();

	void					RankingEvaluation();// ���ʂ��Ƃ̕]��



	/* �ÓI�����o�ϐ� */
	static char				*m_RankingFileName;							// �����L���O�̃t�@�C����
	static char				*m_SaveScoreFileName;						// �X�R�A�̃t�@�C����

	/* �����o�ϐ� */
	std::vector<int>		m_nRankingScore;							// ���5�ʂ̃����L���O���
	std::vector<int>		m_nPlayerScore;								// �v���C���[���l�������X�R�A
	RUNKING_DATA			m_RunkingData;								// �����L���O�f�[�^�̍\���̕ϐ�
	CScene2D				*m_apScene2D[RANKING_UI_MAX];				// �V�[��2D�̃|�C���^
	CMultiNumber			*m_pRankScore[RANKING_NUM];					// �X�R�A��UI
	CMultiNumber			*m_pPlayerScore[PLAYER_SCORE_MAX];			// �X�R�A��UI
	int						m_nColCnt;									// �J���[�J�E���g
	int						m_WaitTime;
	int						m_nRankNum;
	int						m_nTimeToExplosion;
	D3DXVECTOR3				m_RankScoreMove;
	int						m_nTimeToDraw;
	int						m_nTimeToFlash;
	int						m_nTimeToFireworks;


	int						m_nDrawCount;
	bool					m_bCompleted;
	bool					m_bCompletedEnd;

	bool					m_bMoveRank[SCORE_MAX];
	float					m_fCol;
	int						m_nTimeToTransition;
	bool					m_bEvaluation[3];
	bool					m_bRankingFail;
};
#endif