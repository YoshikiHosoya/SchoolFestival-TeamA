// =====================================================================================================================================================================
//
// �Q�[��UI�̏��� [resultUI.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "gameUI.h"			// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "game.h"
#include "keyboard.h"
#include "player.h"
#include "sound.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CGameUI::m_apTexture[GAMEUITYPE::G_UI_MAX]	= {};						// �e�N�X�`��
CNumber				*CGameUI::m_apNumber[LIFE_DIGIT]			= {};						// �i���o�[�̃|�C���^
D3DXVECTOR2			CGameUI::m_UVsize							= D3DXVECTOR2(0.1f, 1.0f);	// UV�T�C�Y
bool				CGameUI::m_bGageDecrease					= true;						// �Q�[�W�̌���

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEXTURE_FILE00		"data/TEXTURE/Dlunker.png"			// �ǂݍ��ރe�N�X�`���t�@�C����	( �A�C�R�� )
#define TEXTURE_FILE01		"data/TEXTURE/min.png"				// �ǂݍ��ރe�N�X�`���t�@�C����	( MIN )
#define TEXTURE_FILE02		"data/TEXTURE/max.png"				// �ǂݍ��ރe�N�X�`���t�@�C����	( MAX )
#define TEXTURE_FILE03		"data/TEXTURE/gage.png"				// �ǂݍ��ރe�N�X�`���t�@�C����	( �Q�[�W )
#define TEXTURE_FILE04		"data/TEXTURE/towa00.png"			// �ǂݍ��ރe�N�X�`���t�@�C����	( �O�p )		triangle

#define ICON_POSX			(250.0f)							// �A�C�R���̍��WX
#define ICON_POSY			(50.0f)								// �A�C�R���̍��WY
#define ICON_SIZEX			(60.0f / 2)							// �A�C�R���̕�
#define ICON_SIZEY			(60.0f / 2)							// �A�C�R���̍���

#define STOP_MIN_POSX		(440.0f)							// MIN�̍��WX
#define START_MAX_POSX		(840.0f)							// MAX�̍��WX
#define MIN_MAX_POSY		(30.0f)								// MIN��MAX�̍��WY
#define MIN_MAX_SIZEX		(60.0f / 2)							// MIN��MAX�̕�
#define MIN_MAX_SIZEY		(40.0f / 2)							// MIN��MAX�̍���

#define GAGE_POSX			(640.0f)							// �Q�[�W�̍��WX
#define GAGE_POSY			(60.0f)								// �Q�[�W�̍��WY
#define GAGE_SIZEX			(200.0f)							// �Q�[�W�̕�
#define GAGE_SIZEY			(10.0f)								// �Q�[�W�̍���
#define GAGE_RECOVERY_SPEED	(50)								// �Q�[�W�̉񕜂��鑬��

#define TRIANGLE_POSX		(GAGE_POSX + GAGE_SIZEX)			// �O�p�̍��WX
#define TRIANGLE_MOVEX		(-0.02f)							// �O�p�̈ړ�
#define TRIANGLE_SIZEX		(15.0f)								// �O�p�̕�
#define TRIANGLE_SIZEY		(15.0f)								// �O�p�̍���

#define LIFE_POSX			(300.0f)							// �̗͂̍��WX
#define LIFE_POSY			(50.0f)								// �̗͂̍��WY
#define LIFE_SIZEX			(15.0f)								// �̗͂̕�
#define LIFE_SIZEY			(20.0f)								// �̗͂̍���
#define LIFE_SPACE			(25.0f)								// �̗͂̊Ԋu

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CGameUI::CGameUI():CScene2D(PRIORITY_UI)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CGameUI::~CGameUI()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CGameUI::Init()
{
	m_fTriangleMoveX	= 0.0f;			// �O�p�̉��ړ�
	m_bGageDecrease		= true;			// �Q�[�W���������Ă��邩

	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		// ������
		m_aCol[nCnt] = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);		// �F

		if (m_apScene2D != NULL)
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
			case GAMEUITYPE::G_UI_ICON:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(ICON_POSX, ICON_POSY, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(ICON_SIZEX, ICON_SIZEY, 0.0f));
				// �F�̐ݒ�
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;

			case GAMEUITYPE::G_UI_STOP_MIN:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(STOP_MIN_POSX, MIN_MAX_POSY, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(MIN_MAX_SIZEX, MIN_MAX_SIZEY, 0.0f));
				// �F�̐ݒ�
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;

			case GAMEUITYPE::G_UI_START_MAX:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(START_MAX_POSX, MIN_MAX_POSY, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(MIN_MAX_SIZEX, MIN_MAX_SIZEY, 0.0f));
				// �F�̐ݒ�
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;

			case GAMEUITYPE::G_UI_GAGE:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(GAGE_POSX, GAGE_POSY, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(GAGE_SIZEX, GAGE_SIZEY, 0.0f));
				// �F�̐ݒ�
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;

			case GAMEUITYPE::G_UI_TRIANGLE:

				//�ʒu�̐ݒ�
				m_apScene2D[nCnt]->SetPos(D3DXVECTOR3(TRIANGLE_POSX, GAGE_POSY, 0.0f));
				// �T�C�Y�̐ݒ�
				m_apScene2D[nCnt]->SetSize(D3DXVECTOR3(TRIANGLE_SIZEX, TRIANGLE_SIZEY, 0.0f));
				// �F�̐ݒ�
				m_apScene2D[nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
				break;
			}
		}
	}
	for (int nCnt = 0; nCnt < LIFE_DIGIT; nCnt++)
	{
		if (m_apNumber != NULL)
		{
			// �V�[��2D�̐���
			m_apNumber[nCnt] = CNumber::Create();

			// ������
			m_apNumber[nCnt]->Init();

			//�ʒu�̐ݒ�
			m_apNumber[nCnt]->SetPos(D3DXVECTOR3(LIFE_POSX + nCnt * LIFE_SPACE, LIFE_POSY, 0.0f));

			// �T�C�Y�̐ݒ�
			m_apNumber[nCnt]->SetSize(D3DXVECTOR3(LIFE_SIZEX, LIFE_SIZEY, 0.0f));

			// �A�j���[�V�����̐ݒ�
			m_apNumber[nCnt]->SetAnim(D3DXVECTOR2(0.1f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
		}
	}
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CGameUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			// �I��
			m_apScene2D[nCnt]->Uninit();
		}
	}
	for (int nCnt = 0; nCnt < LIFE_DIGIT; nCnt++)
	{
		if (m_apNumber != NULL)
		{
			m_apNumber[nCnt]->Release();
			m_apNumber[nCnt] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CGameUI::Update(void)
{
	// �ϐ�
	D3DXVECTOR3 pos;

	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			// �O�p�̈ړ�
			MoveTriangle();
			// �X�V
			m_apScene2D[nCnt]->Update();
		}
	}
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CGameUI::Draw(void)
{	
	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		if (m_apScene2D != NULL)
		{
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// �̗͂̐ݒ�
//
// =====================================================================================================================================================================
void CGameUI::SetLife(int nLife)
{
	// �ϐ��錾
	int nNumber = 0;

	for (int nCntScore = 0; nCntScore < LIFE_DIGIT; nCntScore++)
	{
		// �����v�Z
		nNumber = nLife % (int)pow(10.0f, LIFE_DIGIT - nCntScore) / (int)pow(10.0f, (LIFE_DIGIT - nCntScore - 1));

		// �A�j���[�V�����̐ݒ�
		m_apNumber[nCntScore]->SetAnim(m_UVsize, D3DXVECTOR2(nNumber * 0.1f, 0.0f));
	}
}

// =====================================================================================================================================================================
//
// �Q�[��UI�̐���
//
// =====================================================================================================================================================================
CGameUI * CGameUI::Create()
{
	// �ϐ�
	CGameUI *pGameUI;

	// �������̊m��
	pGameUI = new CGameUI();

	// ������
	pGameUI->Init();

	return pGameUI;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CGameUI::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���t�@�C����
	char *sTextureFileName[G_UI_MAX]
	{
		{ TEXTURE_FILE00 },		// G_UI_ICON			( �A�C�R��
		{ TEXTURE_FILE01 },		// G_UI_STOP_MIN		( MIN
		{ TEXTURE_FILE02 },		// G_UI_START_MAX		( MAX
		{ TEXTURE_FILE03 },		// G_UI_GAGE			( �Q�[�W
		{ TEXTURE_FILE04 },		// G_UI_TRIANGLE		( �O�p
	};

	for (int nCntUI = 0; nCntUI < G_UI_MAX; nCntUI++)
	{
		// �e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntUI], &m_apTexture[nCntUI]);
	}

	for (int nCnt = 0; nCnt < G_UI_MAX; nCnt++)
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
void CGameUI::Unload(void)
{
	for (int nCnt = 0; nCnt < GAMEUITYPE::G_UI_MAX; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCnt] != NULL)
		{
			m_apTexture[nCnt]->Release();
			m_apTexture[nCnt] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//
// �Q�[�W����
//
// =====================================================================================================================================================================
void CGameUI::RecoveryGage(void)
{
	//	�Q�[�W�̉񕜉�
	CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_GAGE);

	m_bGageDecrease = false;		// �Q�[�W���񕜂�����
}

// =====================================================================================================================================================================
//
// �O�p�̈ړ�����
//
// =====================================================================================================================================================================
void CGameUI::MoveTriangle(void)
{
	// �v���C���[�̏��擾
	CPlayer *pPlayer;
	pPlayer = CManager::GetGame()->GetPlayer();

	// �ʒu�̎擾
	D3DXVECTOR3 pos	= m_apScene2D[G_UI_TRIANGLE]->GetPos();

	// �Q�[�W���������Ă��邩
	if (m_bGageDecrease)
	{
		m_fTriangleMoveX = TRIANGLE_MOVEX;		// �O�p�̈ړ��l
	}
	else
	{
		m_fTriangleMoveX = -TRIANGLE_MOVEX * GAGE_RECOVERY_SPEED;	// �ő�l�܂ŉ�

		// �ő�l�܂ŉ񕜂����Ƃ�
		if (pos.x >= START_MAX_POSX)
		{
			m_fTriangleMoveX = 0.0f;		// �ړ����~�߂�
			m_bGageDecrease = true;		// �Q�[�W������������
		}
	}

	// MIN�ɒB�����Ƃ�
	if (pos.x <= STOP_MIN_POSX)
	{
		m_fTriangleMoveX = 0.0f;		// �ړ����~�߂�

		// �v���C���[�Ƀ_���[�W
		pPlayer->PlayerDamage(1);
		// �v���C���[�����񂾏�Ԃ�
		pPlayer->SetPlayerState(CPlayer::PLAYERSTATE_DEATH);
		// �Q�[�W��
		m_fTriangleMoveX = -TRIANGLE_MOVEX * GAGE_RECOVERY_SPEED;	// �ő�l�܂ŉ�
	}

	// �ʒu�X�V
	pos.x += m_fTriangleMoveX;

	// �ʒu�̐ݒ�
	m_apScene2D[G_UI_TRIANGLE]->SetPos(pos);
}