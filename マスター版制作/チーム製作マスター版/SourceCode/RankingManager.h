// =====================================================================================================================================================================
//
// �����L���O�}�l�[�W���[�̏��� [ranking.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _RANKINGMANAGER_H_
#define _RANKINGMANAGER_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CRankingUI;
// =====================================================================================================================================================================
// ���U���gUI�N���X
// =====================================================================================================================================================================
class CRankingManager
{
public:
	// �����L���O�̎��
	enum RANKING_STATE
	{
		RANKING_STATE_DRAW_SCORE,
		RANKING_STATE_SCORE_CALCULATION,
		RANKING_STATE_COMPARE_RANKING,
		RANKING_STATE_SORT_RANKING,
		RANKING_STATE_RANKING,
		RANKING_STATE_WAITTIME,
	};
	CRankingManager();						// �R���X�g���N�^
	~CRankingManager();						// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT					Init(void);		// ������
	void					Uninit(void);	// �I��
	void					Update(void);	// �X�V

	/* �ÓI�����o�֐� */
	static					CRankingManager	*Create();						// ����
	/* �����o�֐� */
	void					RankingUiOrder();								// Ui�̏o������
	static RANKING_STATE	GetRankingState() {return m_RankingState;};
	static void				SetRankingState(RANKING_STATE state) { m_RankingState = state; };
	static RANKING_STATE	GetRankingStateOld() { return m_RankingStateOld; };
	static void				SetRankingStateOld(RANKING_STATE state) { m_RankingStateOld = state; };

private:
	/* �ÓI�����o�ϐ� */
	static RANKING_STATE			m_RankingState;									// �����L���O���
	static RANKING_STATE			m_RankingStateOld;								// 1�O�̏��

	/* �����o�֐� */
	/* �����o�ϐ� */
	CRankingUI				*m_pRankingUI;									// �����L���OUI�̃|�C���^
};
#endif