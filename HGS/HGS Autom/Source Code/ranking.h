//------------------------------------------------------------------------------
//
//�����L���O����  [ranking.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _RANKING_H_
#define _RANKING_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "basemode.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CMultiNumber;
class CScene2D;

class CRanking : public CBaseMode
{
public:

	// �����L���OUI�̎��
	enum class RANKING_UI
	{
		NONE = -1,
		RANKING_NAME,				// ���O���S
		RANKING_SCORE,				// �v���C���[�X�R�A
		RANKING_1st,				// ����1��
		RANKING_2nd,				// ����2��
		RANKING_3rd,				// ����3��
		RANKING_4th,				// ����4��
		RANKING_5th,				// ����5��
		RANKING_GO_TITLE,			// �^�C�g����
		RANKING_MAX,
	};

	// �����L���O�f�[�^
	enum class RANKING_SCORE
	{
		NONE = -1,
		SCORE_1st,					// ����1��
		SCORE_2nd,					// ����2��
		SCORE_3rd,					// ����3��
		SCORE_4th,					// ����4��
		SCORE_5th,					// ����5��
		SCORE_MAX,
	};

	CRanking();
	~CRanking();

	HRESULT Init(HWND hWnd);			//������
	void Uninit();						//�I��
	void Update();						//�X�V
	void Draw();						//�`��
	void ShowDebugInfo() {};			//�f�o�b�O���\�L

	CPlayer* GetPlayer() { return nullptr; };		//�v���C���[�擾����

private:
	void					RankingUICreate();										// �����L���OUI�̐���
	void					RankingScoreCreate();									// �����L���O�X�R�A�̐���
	void					PlayerScoreCreate();									// �v���C���[�X�R�A�̐���
	void					RankingDataLoad();										// �����L���O�̃f�[�^�̃��[�h
	void					RankingCalculation();									// ���ʂ̌v�Z
	void					BubbleSort(std::vector<int> &data);						// �D��x�̓���ւ� ��������0�Ԗڂ���
	void					RankingDataSave();										// �����L���O�̃f�[�^�̃Z�[�u

	static char				*m_RankingFileName;										// �����L���O�̃t�@�C����

	std::vector<int>							m_nRankingScore;					// ���5�ʂ̃����L���O���
	std::vector<std::shared_ptr<CMultiNumber>>	m_pPlayerScore;						// �X�R�A��UI
	std::vector<std::shared_ptr<CScene2D>>		m_apScene2D;						// �����L���OUI 
	std::vector<std::shared_ptr<CMultiNumber>>	m_apRankScore;						// �X�R�A��UI
	int											m_nCntResult;						// �J�E���^

};

#endif