// =====================================================================================================================================================================
//
// �����L���OUI�̏���[rankbg.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "rankingUI.h"
#include "ranking.h"
#include "renderer.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CRankingUI::m_apTexture[RANKINGUITYPE::RK_UI_MAX] = {};			// �擪�͌^��

// =====================================================================================================================================================================
//
// �}�N����`
//
// =====================================================================================================================================================================
#define TEXTURE_FILE01			"data/TEXTURE/rank_1.png"		// �ǂݍ��ރe�N�X�`���t�@�C����		( 1�� )
#define TEXTURE_FILE02			"data/TEXTURE/rank_2.png"		// �ǂݍ��ރe�N�X�`���t�@�C����		( 2�� )
#define TEXTURE_FILE03			"data/TEXTURE/rank_3.png"		// �ǂݍ��ރe�N�X�`���t�@�C����		( 3�� )
#define TEXTURE_FILE04			"data/TEXTURE/rank_4.png"		// �ǂݍ��ރe�N�X�`���t�@�C����		( 4�� )
#define TEXTURE_FILE05			"data/TEXTURE/rank_5.png"		// �ǂݍ��ރe�N�X�`���t�@�C����		( 5�� )
#define TEXTURE_FILE06			"data/TEXTURE/rank.png"			// �ǂݍ��ރe�N�X�`���t�@�C����		( �����L���O )
#define TEXTURE_FILE07			"data/TEXTURE/gototitle.png"	// �ǂݍ��ރe�N�X�`���t�@�C����		( Enter )

#define BG_SIZEX				(SCREEN_WIDTH / 2)				// �w�i�̕�
#define BG_SIZEY				(SCREEN_HEIGHT / 2)				// �w�i�̍���

#define RANKING_SIZEX			(600 / 2)						// �����L���O�̕�
#define RANKING_SIZEY			(80 / 2)						// �����L���O�̍���

#define ENTER_SIZEX				(300 / 2)						// Enter�̕�
#define ENTER_SIZEY				(80 / 2)						// Enter�̍���

#define RANK_NUM_POSX			(380.0f)						// �����L���O�̏��ʂ̈ʒuX
#define RANK_NUM_POSY			(180.0f)						// �����L���O�̏��ʂ̈ʒuY
#define RANK_NUM_SIZEX			(80 / 2)						// �����L���O�̏��ʂ̕�
#define RANK_NUM_SIZEY			(80 / 2)						// �����L���O�̏��ʂ̍���
#define RANK_NUM_SPACE			(90.0f)							// �����L���O�̏��ʂ̊�	

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CRankingUI::CRankingUI() :CScene2D(PRIORITY_UI)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CRankingUI::~CRankingUI()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CRankingUI::Init()
{
	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			// �ϐ�������
			m_UV[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ�

			// �V�[��2D�̐���
			m_apScene2D[nCnt] = CScene2D::Create();

			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);

			// ������
			m_apScene2D[nCnt]->Init();

			switch (nCnt)
			{
			case RANKINGUITYPE::RK_UI_RANK_1:
				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANK_2:
				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANK_3:
				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANK_4:
				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANK_5:
				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(RANK_NUM_POSX, RANK_NUM_POSY + (RANK_NUM_SPACE * nCnt), 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANK_NUM_SIZEX, RANK_NUM_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_RANKING:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(BG_SIZEX, 70.0f, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(RANKING_SIZEX, RANKING_SIZEY, 0.0f));
				break;

			case RANKINGUITYPE::RK_UI_ENTER:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(BG_SIZEX, 650.0f, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(ENTER_SIZEX, ENTER_SIZEY, 0.0f));
				break;
			}
		}
	}
}

// ================================================================================================================================================================================
//
// �I������
//
// ================================================================================================================================================================================
void CRankingUI::Uninit()
{
	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
		}
	}
}

// ================================================================================================================================================================================
//
// �X�V����
//
// ================================================================================================================================================================================
void CRankingUI::Update()
{
	// �ϐ�
	D3DXVECTOR3 pos;

	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		// �X�V
		m_apScene2D[nCnt]->Update();
	}
}

// ================================================================================================================================================================================
//
// �`�揈��
//
// ================================================================================================================================================================================
void CRankingUI::Draw()
{
	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// �����L���OUI�̐���
//
// =====================================================================================================================================================================
CRankingUI * CRankingUI::Create()
{
	// �ϐ�
	CRankingUI *pRankingUI;

	// �������̊m��
	pRankingUI = new CRankingUI();

	// ������
	pRankingUI->Init();

	return pRankingUI;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CRankingUI::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE01, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_1]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE02, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_2]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE03, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_3]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE04, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_4]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE05, &m_apTexture[RANKINGUITYPE::RK_UI_RANK_5]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE06, &m_apTexture[RANKINGUITYPE::RK_UI_RANKING]);
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE07, &m_apTexture[RANKINGUITYPE::RK_UI_ENTER]);

	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		// �G���[�`�F�b�N
		if (m_apTexture[nCnt] == NULL)
		{
			return E_FAIL;
		}
	}

	return S_OK;
}

// =====================================================================================================================================================================
//
// �A�����[�h
//
// =====================================================================================================================================================================
void CRankingUI::Unload(void)
{
	for (int nCnt = 0; nCnt < RANKINGUITYPE::RK_UI_MAX; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCnt])
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

