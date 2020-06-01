//------------------------------------------------------
//�N���X�^����[main.cpp]
//Author:Fujiwara Masato
//
//--------------------------------------------------------

//--------------------------------------------------------
//
// �C���N���[�h�t�@�C��
//
//--------------------------------------------------------
#include "main.h"
#include "score.h"
#include "manager.h"
#include "scene.h"
#include "number.h"
//--------------------------------------------------------
//
// static�̏�����
//
//--------------------------------------------------------
//------------------------------------------------------
//
//	�R���X�g���N�^
//
//--------------------------------------------------------
CScore::CScore(void) :CScene(ACTOR_SCORE,LAYER_UI)
{
}
//------------------------------------------------------
//
//	�f�X�g���N�^
//
//--------------------------------------------------------
CScore::~CScore()
{
}
//------------------------------------------------------
//
//	����������
//
//------------------------------------------------------
void CScore::Init(void)
{
	for (int nCount = 0; nCount < SCORE_DIGIT; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create();
		m_apNumber[nCount]->SetNum(0);
		m_apNumber[nCount]->SetPos(D3DXVECTOR3(SCORE_POSX + nCount * SCORE_SPACE, SCORE_POSY, 0.0f), SCORE_SPACE);
	}
}
//------------------------------------------------------
//
//	�I������
//
//------------------------------------------------------
void CScore::Uninit(void)
{
	for (int nCount = 0; nCount < SCORE_DIGIT; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Uninit();
		}
	}
}
//------------------------------------------------------
//
//	�X�V����
//
//------------------------------------------------------
void CScore::Update(void)
{
	for (int nCount = 0; nCount < SCORE_DIGIT; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Update();
		}
	}
}
//------------------------------------------------------
//
//	�`�揈��
//
//------------------------------------------------------
void CScore::Draw(void)
{
	for (int nCount = 0; nCount < SCORE_DIGIT; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Draw();
		}
	}
}
//------------------------------------------------------
//
//	�X�R�A�̌v�Z����
//
//------------------------------------------------------
void CScore::AddScore(int nValue)
{
	m_nScore += nValue;

	for (int nCount = 0; nCount < SCORE_DIGIT; nCount++)
	{
		int nNumber = m_nScore % (int)powf(10.0f, 8.0f - nCount) / (int)powf(10.0f, 8.0f - 1.0f - nCount);

		m_apNumber[nCount]->SetNum(nNumber);
	}
}
//------------------------------------------------------
//
//	�|�W�V�����̐ݒ�
//
//------------------------------------------------------
void CScore::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//------------------------------------------------------
//
//	�X�R�A�擾�̐ݒ�
//
//------------------------------------------------------
int CScore::GetScore(void)
{
	return m_nScore;
}
//------------------------------------------------------
//
//	��������
//
//------------------------------------------------------
CScore *CScore::Create(void)
{
	CScore *pScore;

	pScore = new CScore;

	pScore->Init();

	return pScore;
}
