// ----------------------------------------
//
// ��ʃX�R�A�����̐���[topscore.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "topscore.h"
#include "number.h"
#include "mark.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define TOPSCORE_SIZE (50.0f)

// ----------------------------------------
//
// �O���[�o���ϐ�
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
//CNumber * CTopscore::m_pNumber[MAX_NUMBERSCORE] = {};	// ��ʃX�R�A�\��
int CTopscore::m_nTopScore[MAX_TOPSCORE] = {};			// ��ʃX�R�A
int CTopscore::m_nMyScore = 0;							// �}�C�X�R�A
int CTopscore::m_nInRank = -1;							// �C�������N

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CTopscore::CTopscore() : CScene(ACTOR_TOPSCORE,LAYER_UI)
{
	// ��ʃX�R�A
	m_nScore = 0;
	m_pNumber[MAX_NUMBERSCORE] = {};
	m_pos = {};
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CTopscore::~CTopscore()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTopscore::Init(void)
{	
	int nTopscore = 0;
	for (int nCnt = 0; nCnt < MAX_NUMBERSCORE; nCnt++)
	{
		// ���̐���
		m_pNumber[nCnt] = CNumber::Create();
		m_pNumber[nCnt]->SetNum(nTopscore);
		m_pNumber[nCnt]->SetPos(
			m_pos + D3DXVECTOR3(100.0f + (MAX_NUMBERSCORE * TOPSCORE_SIZE) / 2 - nCnt * TOPSCORE_SIZE * 2, 0.0f, 0.0f),
			TOPSCORE_SIZE);
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CTopscore::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBERSCORE; nCnt++)
	{
		if (m_pNumber[nCnt] != NULL)
		{
			m_pNumber[nCnt]->Uninit();
			delete m_pNumber[nCnt];
			m_pNumber[nCnt] = NULL;
		}
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CTopscore::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBERSCORE; nCnt++)
	{
		m_pNumber[nCnt]->Update();
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CTopscore::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_NUMBERSCORE; nCnt++)
	{
		m_pNumber[nCnt]->Draw();
	}
}

// ----------------------------------------
// �X�R�A�̓ǂݍ��ݏ���
// ----------------------------------------
void CTopscore::Load(void)
{
	// �ϐ��錾
	FILE * pFile;

	pFile = fopen("data/TEXT/rank.txt", "r");

	// �t�@�C�����J����Ă���Ƃ�
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_TOPSCORE; nCnt++)
		{
			fscanf(pFile, "%d", &m_nTopScore[nCnt]);
		}
		fclose(pFile);
	}
	else
	{
		fclose(pFile);
	}
}

// ----------------------------------------
// �X�R�A�̃Z�[�u����
// ----------------------------------------
void CTopscore::Save(void)
{
	// �ϐ��錾
	FILE * pFile;

	pFile = fopen("data/TEXT/rank.txt", "w");

	// �t�@�C�����J����Ă���Ƃ�
	if (pFile != NULL)
	{
		for (int nCnt = 0; nCnt < MAX_TOPSCORE; nCnt++)
		{
			fprintf(pFile, "%d\n", m_nTopScore[nCnt]);
		}
		fclose(pFile);
	}
	else
	{
	}
}

// ----------------------------------------
// �X�R�A�ݒ菈��
// ----------------------------------------
void CTopscore::SetScore(int nScore)
{
	// �ϐ��錾
	int nAllScore[6];
	int nComp = nScore;
	int nCont;
	// ���̕ϐ��ɑ��
	for (int nCnt = 0; nCnt < MAX_TOPSCORE; nCnt++)
	{
		nAllScore[nCnt] = m_nTopScore[nCnt];
	}
	// �Ō�̔z��ɍ���̃X�R�A����
	nAllScore[5] = nScore;
	// ���݂̃X�R�A��ۑ�
	m_nMyScore = nScore;
	// �C�������N������
	m_nInRank = -1;

	// �����N����ւ�
	for (int nCnt = 0; nCnt < MAX_TOPSCORE; nCnt++)
	{
		for (int nCnt2 = nCnt + 1; nCnt2 < MAX_TOPSCORE + 1; nCnt2++)
		{
			// ��r
			if (nAllScore[nCnt] < nAllScore[nCnt2])
			{
				nCont = nAllScore[nCnt];
				nAllScore[nCnt] = nAllScore[nCnt2];
				nAllScore[nCnt2] = nCont;
			}
		}
	}
	// �ۑ��p�ɑ��
	for (int nCnt = 0; nCnt < MAX_TOPSCORE; nCnt++)
	{
		m_nTopScore[nCnt] = nAllScore[nCnt];
		// �����l��������
		if (m_nInRank == -1)
		{
			// my�X�R�A�����N�C��
			if (m_nMyScore == m_nTopScore[nCnt])
			{
				m_nInRank = nCnt;
			}
		}
	}
	// �Z�[�u
	Save();
}

// ----------------------------------------
// ��ʃX�R�A�ݒ菈��
// ----------------------------------------
void CTopscore::SetTopscore(int nNumber)
{
	// �ϐ��錾
	int nTopscore;
	for (int nCnt = 0; nCnt < MAX_NUMBERSCORE; nCnt++)
	{
		// ���̐���
		nTopscore = m_nTopScore[nNumber] % (int)powf(10.0f, (float)nCnt + 1.0f) / (int)powf(10.0f, (float)nCnt);
		m_pNumber[nCnt]->SetNum(nTopscore);
		m_pNumber[nCnt]->SetPos(
			m_pos + D3DXVECTOR3(0.0f +(MAX_NUMBERSCORE * TOPSCORE_SIZE) / 2 - nCnt * TOPSCORE_SIZE, 0.0f, 0.0f), 
			TOPSCORE_SIZE);
	}
	// my�X�R�A���オ������
	if (m_nInRank == nNumber)
	{
		CMark::Create(
			m_pos + D3DXVECTOR3(30.0f,0.0f,0.0f),
			D3DXVECTOR2(MAX_NUMBERSCORE * TOPSCORE_SIZE + TOPSCORE_SIZE + 20, TOPSCORE_SIZE),
			CScene::ACTOR_MARK);
	}

}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CTopscore * CTopscore::Create(D3DXVECTOR3 pos)
{
	// �ϐ��錾
	CTopscore * pTopscore;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pTopscore = new CTopscore();
	// �ʒu�����
	pTopscore->m_pos = pos;
	// ����������
	pTopscore->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pTopscore;
}