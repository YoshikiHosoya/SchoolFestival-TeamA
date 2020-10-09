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

	static char				*m_RankingFileName;										// �����L���O�̃t�@�C����
	static char				*m_SaveScoreFileName;									// �X�R�A�̃t�@�C����

	std::vector<int>				m_nRankingScore;										// ���5�ʂ̃����L���O���
	int								m_nCntResult;											//�J�E���^
	std::vector<std::shared_ptr<CScene2D>>		m_apScene2D;						// �����L���OUI 
	std::vector<std::shared_ptr<CMultiNumber>>	m_apRankScore;					// �X�R�A��UI

};

#endif