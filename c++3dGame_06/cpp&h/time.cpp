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
#include "time.h"
#include "manager.h"
#include "scene.h"
#include "number.h"

//--------------------------------------------------------
//
// �}�N����`
//
//--------------------------------------------------------
#define TIME_UP_MAX (60 * 60 * 2)

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
CTime::CTime(void) :CScene(ACTOR_TIME,LAYER_UI)
{
	m_nTime = TIME_UP_MAX;
	m_bTimeOver = false;
	m_nTime = TIME_UP_MAX;
}
//------------------------------------------------------
//
//	�f�X�g���N�^
//
//--------------------------------------------------------
CTime::~CTime()
{
}
//------------------------------------------------------
//
//	����������
//
//------------------------------------------------------
void CTime::Init(void)
{
	int nNumber;

	for (int nCount = 0; nCount < TIME_DIGIT; nCount++)
	{
		m_apNumber[nCount] = CNumber::Create();
		m_apNumber[nCount]->SetPos(D3DXVECTOR3(TIME_POSX + nCount * TIME_SPACE, TIME_POSY, 0.0f), TIME_SPACE);
		nNumber = (int)(m_nTime / 60) % (int)powf(10.0f, (float)(TIME_DIGIT - nCount)) / (int)powf(10.0f, TIME_DIGIT - 1.0f - nCount);

		m_apNumber[nCount]->SetNum(nNumber);
	}
}
//------------------------------------------------------
//
//	�I������
//
//------------------------------------------------------
void CTime::Uninit(void)
{
	for (int nCount = 0; nCount < TIME_DIGIT; nCount++)
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
void CTime::Update(void)
{
	DecreasesTime();

	int nNumber;

	for (int nCount = 0; nCount < TIME_DIGIT; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Update();

			nNumber = int((m_nTime / 60) % (int)powf(10.0f, (float)(TIME_DIGIT - nCount)) / (int)powf(10.0f, TIME_DIGIT - 1.0f - nCount));

			m_apNumber[nCount]->SetNum(nNumber);
		}
	}
}
//------------------------------------------------------
//
//	�`�揈��
//
//------------------------------------------------------
void CTime::Draw(void)
{
	for (int nCount = 0; nCount < TIME_DIGIT; nCount++)
	{
		if (m_apNumber[nCount] != NULL)
		{
			m_apNumber[nCount]->Draw();
		}
	}
}
//------------------------------------------------------
//
//	�|�W�V�����̐ݒ�
//
//------------------------------------------------------
void CTime::SetPosition(D3DXVECTOR3 pos)
{
	m_pos = pos;
}
//------------------------------------------------------
//
//	���Ԍ�������
//
//------------------------------------------------------
void CTime::DecreasesTime()
{
	m_nTime--;

	if (m_nTime <= 0)
	{
		m_nTime = 0;
		m_bTimeOver = true;
	}
}
//------------------------------------------------------
//
//	�^�C���I�[�o�[�t���O�̎擾
//
//------------------------------------------------------
bool CTime::GetTimeOverFlag(void)
{
	return m_bTimeOver;
}
//------------------------------------------------------
//
//	��������
//
//------------------------------------------------------
CTime *CTime::Create(void)
{
	CTime *pTime;

	pTime = new CTime;

	pTime->Init();

	return pTime;
}
