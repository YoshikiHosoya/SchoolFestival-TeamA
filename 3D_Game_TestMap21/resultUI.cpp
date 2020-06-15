// =====================================================================================================================================================================
//
// ���U���gUI�̏��� [resultUI.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "resultUI.h"			// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CResultUI::m_apTexture[RESULTUITYPE::R_UI_MAX] = {};			// �擪�͌^��

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEXTURE_FILE00		"data/TEXTURE/over.png"			// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_FILE01		"data/TEXTURE/enter.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define TEXTURE_FILE02		"data/TEXTURE/maou00.png"		// �ǂݍ��ރe�N�X�`���t�@�C����

#define BG_SIZEX			(SCREEN_WIDTH / 2)				// ���W�̕�
#define BG_SIZEY			(SCREEN_HEIGHT / 2)				// ���W�̍���

#define LOGO_POSY			(200.0f)						// ���WY
#define LOGO_SIZEX			(400.0f)						// ���W�̕�
#define LOGO_SIZEY			(100.0f)						// ���W�̍���

#define ENTER_POSY			(600.0f)						// ���WY
#define ENTER_SIZEX			(200.0f)						// ���W�̕�
#define ENTER_SIZEY			(50.0f)							// ���W�̍���

#define MAOU_POSX			(1230.0f)						// ���WX
#define MAOU_POSY			(710.0f)						// ���WY
#define MAOU_SIZEX			(50.0f)							// ���W�̕�
#define MAOU_SIZEY			(10.0f)							// ���W�̍���

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CResultUI::CResultUI():CScene2D(PRIORITY_UI)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CResultUI::~CResultUI()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CResultUI::Init()
{
	for (int nCnt = 0; nCnt < RESULTUITYPE::R_UI_MAX; nCnt++)
	{
		if(m_apScene2D != NULL)
		{ 
			// �ϐ�������
			m_UV[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ�

			// �V�[��2D�̐���														// CScene2D�� = �̌`�Ő������� ( ���^�[�����s���Ȃ��Ȃ邽�� )
			m_apScene2D[nCnt] = CScene2D::Create();

			// �e�N�X�`���̊��蓖��
			m_apScene2D[nCnt]->BindTexture(m_apTexture[nCnt]);

			// ������
			m_apScene2D[nCnt]->Init();
			
			switch (nCnt)
			{
			case RESULTUITYPE::R_UI_LOGO:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(BG_SIZEX, LOGO_POSY, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(LOGO_SIZEX, LOGO_SIZEY, 0.0f));
				break;

			case RESULTUITYPE::R_UI_ENTER:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(BG_SIZEX, ENTER_POSY, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(ENTER_SIZEX, ENTER_SIZEY, 0.0f));
				break;

			case RESULTUITYPE::R_UI_MAOU:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(MAOU_POSX, MAOU_POSY, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(MAOU_SIZEX, MAOU_SIZEY, 0.0f));
				break;
			}
		}  
	}
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CResultUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < RESULTUITYPE::R_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			m_apScene2D[nCnt]->Uninit();
		}
	}
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CResultUI::Update(void)
{
	// �ϐ�
	D3DXVECTOR3 pos;

	for (int nCnt = 0; nCnt < RESULTUITYPE::R_UI_MAX; nCnt++)
	{
		// �X�V
		m_apScene2D[nCnt]->Update();
	}
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CResultUI::Draw(void)
{	
	for (int nCnt = 0; nCnt < RESULTUITYPE::R_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// ���U���gUI�̐���
//
// =====================================================================================================================================================================
CResultUI * CResultUI::Create()
{
	// �ϐ�
	CResultUI *pResultUI;

	// �������̊m��
	pResultUI = new CResultUI();

	// ������
	pResultUI->Init();

	return pResultUI;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CResultUI::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���t�@�C����
	char *sTextureFileName[R_UI_MAX]
	{
		{ TEXTURE_FILE00 },		// R_UI_LOGO		( ���S
		{ TEXTURE_FILE01 },		// R_UI_ENTER		( ENTER
		{ TEXTURE_FILE02 },		// R_UI_MAOU		( ������
	};

	for (int nCntUI = 0; nCntUI < R_UI_MAX; nCntUI++)
	{
		// �e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntUI], &m_apTexture[nCntUI]);
	}

	for (int nCnt = 0; nCnt < R_UI_MAX; nCnt++)
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
void CResultUI::Unload(void)
{
	for (int nCnt = 0; nCnt < RESULTUITYPE::R_UI_MAX; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}