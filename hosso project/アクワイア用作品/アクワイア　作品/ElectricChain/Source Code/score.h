//------------------------------------------------------------------------------
//
//�X�R�A����  [score.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _SCORE_H_
#define _SCORE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------

//�O���錾
class CMultiNumber;

class CScore
{
public:
	enum SCORE_TYPE
	{
		SCORE_KILL = 0,
		SCORE_COMBO,
		SCORE_NOWCHAIN,

		SCORE_NUMCHAIN,		//�g�����킩�炎
		SCORE_MAX
	};

	CScore();
	~CScore();
	HRESULT Init();													//������
	void Uninit();													//�I��
	void Update();													//�X�V
	void Draw();													//�`��
	static std::unique_ptr<CScore> Create();						//��������

	static int GetRankingScore(int nRank);							//�����L���O�̃X�R�A�擾
	static HRESULT LoadScore();										//�X�R�A���[�h
	HRESULT SaveScore();											//�X�R�A���[�h

	//Add�֐�
	void AddKill(int nValue);										//�L����
	void AddCombo(int nValue);										//�R���{��
	void AddNumChain(int nValue);									//�`�F�C����

	void SetNowChain();

	//Get�֐�
	int GetNowChainNum()	{ return m_nNowChain; };				//���݂̃`�F�C����
	int GetNumChainNum()	{ return m_nNumChain;};					//�`�F�C������
	static int GetScore()	{ return m_nScore; };					//�X�R�A�擾
	static int GetCombo()	{ return m_nCombo; };					//�R���{���擾
	static int GetKill()	{ return m_nKill; };					//�L�����擾

private:
	std::vector<std::shared_ptr<CMultiNumber>> m_pMultiNumberLIst;	//�i���o�[�̃|�C���^�̃��X�g
	static std::vector<int> m_nRankingScoreList;					//�����L���O�p�̃X�R�A
	static int m_nScore;											//�ŏI�I�ȃX�R�A
	static int m_nKill;												//�L����
	static int m_nCombo;											//�R���{��

	int m_nNowChain;												//���݂̃`�F�C����
	int m_nNumChain;												//�`�F�C����
};

#endif