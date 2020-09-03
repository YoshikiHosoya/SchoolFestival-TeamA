// =====================================================================================================================================================================
//
// �v���C���[UI�̏��� [playerUI.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "main.h"			// �C���N���[�h�t�@�C��
#include "playerUI.h"
#include "debugproc.h"
#include "bullet.h"
#include "gun.h"
#include "multinumber.h"
#include "UIManager.h"
#include "playergetscoreui.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define PLAYER_MAX_LIFE						(5)															// �̗͂�\������ő吔

#define PLAYER_UI_FRAME_POS					(D3DXVECTOR3(305.0f + m_PLAYER_2_UI_FramePos, 65.0f, 0.0f))	// �g�̈ʒu
#define PLAYER_UI_FRAME_SIZE				(D3DXVECTOR3(80.0f, 45.0f, 0.0f))						// �g�̃T�C�Y
#define PLAYER_UI_STOCK_LETTER_POS			(D3DXVECTOR3(140.0f + m_PLAYER_2_UI_ScorePos, 90.0f, 0.0f))	// �c�@( ���� )�̈ʒu
#define PLAYER_UI_STOCK_LETTER_SIZE			(D3DXVECTOR3(30.0f, 25.0f, 0.0f))						// �c�@( ���� )�̃T�C�Y
#define PLAYER_UI_BULLET_AMMO_LETTER_POS	(D3DXVECTOR3(270.0f + m_PLAYER_2_UI_FramePos, 50.0f, 0.0f))	// �c�e��( ���� )�̈ʒu
#define PLAYER_UI_BULLET_AMMO_LETTER_SIZE	(D3DXVECTOR3(30.0f, 25.0f, 0.0f))						// �c�e��( ���� )�̃T�C�Y
#define PLAYER_UI_GRENADE_AMMO_LETTER_POS	(D3DXVECTOR3(340.0f + m_PLAYER_2_UI_FramePos, 50.0f, 0.0f))	// �O���l�[�h�̎c��( ���� )�̈ʒu
#define PLAYER_UI_GRENADE_AMMO_LETTER_SIZE	(D3DXVECTOR3(30.0f, 25.0f, 0.0f))						// �O���l�[�h�̎c��( ���� )�̃T�C�Y
#define PLAYER_UI_LIFE_ICON_POS				(D3DXVECTOR3(130.0f + m_PLAYER_2_UI_LifePos, 650.0f, 0.0f))	// �̗̓A�C�R���̈ʒu
#define PLAYER_UI_LIFE_ICON_SIZE			(D3DXVECTOR3(80.0f, 80.0f, 0.0f))						// �̗̓A�C�R���̃T�C�Y
#define PLAYER_UI_INFINITY_AMMO_POS			(D3DXVECTOR3(270.0f + m_PLAYER_2_UI_FramePos, 80.0f, 0.0f))	// �e�������̈ʒu
#define PLAYER_UI_INFINITY_AMMO_SIZE		(D3DXVECTOR3(40.0f, 40.0f, 0.0f))						// �e�������̃T�C�Y

#define PLAYER_UI_NUM_SCORE_POS				(D3DXVECTOR3(120.0f + m_PLAYER_2_UI_ScorePos, 50.0f, 0.0f))	// �X�R�A�̈ʒu
#define PLAYER_UI_NUM_SCORE_SIZE			(D3DXVECTOR3(25.0f, 25.0f, 0.0f))						// �X�R�A�̃T�C�Y
#define PLAYER_UI_NUM_BULLET_AMMO_POS		(D3DXVECTOR3(275.0f + m_PLAYER_2_UI_FramePos, 80.0f, 0.0f))	// �c�e���̈ʒu
#define PLAYER_UI_NUM_BULLET_AMMO_SIZE		(D3DXVECTOR3(20.0f, 20.0f, 0.0f))						// �c�e���̃T�C�Y
#define PLAYER_UI_NUM_GRENADE_AMMO_POS		(D3DXVECTOR3(340.0f + m_PLAYER_2_UI_FramePos, 80.0f, 0.0f))	// �O���l�[�h�̎c���̈ʒu
#define PLAYER_UI_NUM_GRENADE_AMMO_SIZE		(D3DXVECTOR3(20.0f, 20.0f, 0.0f))						// �O���l�[�h�̎c���̃T�C�Y
#define PLAYER_UI_NUM_LIFE_POS				(D3DXVECTOR3(180.0f + m_PLAYER_2_UI_LifePos, 650.0f, 0.0f))	// �̗͂̈ʒu
#define PLAYER_UI_NUM_LIFE_SIZE				(D3DXVECTOR3(25.0f, 25.0f, 0.0f))						// �̗͂̃T�C�Y
#define PLAYER_UI_NUM_STOCK_POS				(D3DXVECTOR3(200.0f + m_PLAYER_2_UI_ScorePos, 90.0f, 0.0f))	// �c�@�̈ʒu
#define PLAYER_UI_NUM_STOCK_SIZE			(D3DXVECTOR3(20.0f, 20.0f, 0.0f))						// �c�@�̃T�C�Y
#define PLAYER_UI_NUM_TIME_POS				(D3DXVECTOR3((SCREEN_WIDTH * 0.5f), 50.0f, 0.0f))		// �c�莞�Ԃ̈ʒu
#define PLAYER_UI_NUM_TIME_SIZE				(D3DXVECTOR3(50.0f, 50.0f, 0.0f))						// �c�莞�Ԃ̃T�C�Y

#define PLAYER_2_UI_FRAME_POS				(650.0f)						// �v���C���[2�̘g�̈ʒu ( �v���C��1�̈ʒu�ɉ��Z )
#define PLAYER_2_UI_SCORE_POS				(1020.0f)						// �v���C���[2�̃X�R�A�̈ʒu ( �V )
#define PLAYER_2_UI_LIFE_POS				(950.0f)						// �v���C���[2�̗̑͂̈ʒu ( �V )

#define DEFAULT_TIME						(60)								// �f�t�H���g�̃^�C�}�[
// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPlayerUI::CPlayerUI()
{
	// ������
	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		m_apScene2D[nCnt] = nullptr;
	}

	m_pPGSUI = nullptr;

	// �ϐ�������
	m_nScore = 0;							// �X�R�A
	m_nBulletAmmo = 0;						// �e�̎c�e��
	m_nGrenadeAmmo = 0;						// �O���l�[�h�̎c�e��
	m_nLife = 0;							// �̗�
	m_nStock = 0;							// �c�@�̐�
	m_nTime = DEFAULT_TIME;					// �c�莞��
	m_PLAYER_2_UI_FramePos = 0;					// �v���C���[2�̘g�̈ʒu
	m_PLAYER_2_UI_ScorePos = 0;					// �v���C���[2�̃X�R�A�̈ʒu
	m_PLAYER_2_UI_LifePos = 0;					// �v���C���[2�̗̑͂̈ʒu
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CPlayerUI::~CPlayerUI()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CPlayerUI::Init(void)
{
	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CPlayerUI::Uninit(void)
{
	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �I��
			delete m_apScene2D[nCnt];
			m_apScene2D[nCnt] = nullptr;

			// �f���[�g�t���O��L���ɂ���
			SetDeleteFlag(true);
		}
	}

	if (m_pScore != nullptr)
	{
		m_pScore->Rerease();
		m_pScore = nullptr;
	}
	if (m_pBulletAmmo != nullptr)
	{
		m_pBulletAmmo->Rerease();
		m_pBulletAmmo = nullptr;
	}
	if (m_pGrenadeAmmo != nullptr)
	{
		m_pGrenadeAmmo->Rerease();
		m_pGrenadeAmmo = nullptr;
	}
	if (m_pLife != nullptr)
	{
		m_pLife->Rerease();
		m_pLife = nullptr;
	}
	if (m_pStock != nullptr)
	{
		m_pStock->Rerease();
		m_pStock = nullptr;
	}
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CPlayerUI::Update(void)
{
	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
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
void CPlayerUI::Draw(void)
{
	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (m_apScene2D[nCnt])
		{
			// �`��
			m_apScene2D[nCnt]->Draw();
		}
	}
}

// =====================================================================================================================================================================
//
// �v���C���[UI�̐���
//
// =====================================================================================================================================================================
CPlayerUI * CPlayerUI::Create(TAG Tag)
{
	//�������̊m��
	CPlayerUI *pPlayerUI = new CPlayerUI();

	// ������
	pPlayerUI->Init();

	// �v���C���[UI�̐���
	pPlayerUI->PlayerUICreate(Tag);

	//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
	CUIManager::AddUIList(std::move(pPlayerUI));

	return pPlayerUI;
}

// =====================================================================================================================================================================
//
// �X�R�A�̐ݒ�
//
// =====================================================================================================================================================================
void CPlayerUI::SetScore(int nScore)
{
	// �X�R�A���Z
	m_nScore += nScore;

	// �X�R�A�̐ݒ�
	m_pScore->SetMultiNumber(m_nScore);
}

// =====================================================================================================================================================================
//
// �A�C�e���̃X�R�A�̐ݒ�
//
// =====================================================================================================================================================================
void CPlayerUI::SetItemScore(int nScore)
{
	// �X�R�A���Z
	m_nScore += nScore;

	// �X�R�A�̐ݒ�
	m_pScore->SetMultiNumber(m_nScore);

	// �\���X�R�A�̐���
	m_pPGSUI = CPlayerGSUI::Create(nScore);
}

// =====================================================================================================================================================================
//
// �c�e���̐ݒ�
//
// =====================================================================================================================================================================
void CPlayerUI::SetBulletAmmo(int nBulletAmmo, CGun::GUN_TYPE GunType)
{
	// �n���h�K���Ɛ�Ԃ̏e�ȊO�̂Ƃ�
	if (CGun::GUN_TYPE::GUNTYPE_HANDGUN != GunType && CGun::GUN_TYPE::GUNTYPE_TANKGUN != GunType)
	{
		// �e��������UI��\��
		m_apScene2D[INFINITY_AMMO]->SetDisp(false);
		// �c�e���̕\��
		m_pBulletAmmo->SetDisp(true);
		// �c�e�����Z
		m_nBulletAmmo = nBulletAmmo;
		// �c�e���̐ݒ�
		m_pBulletAmmo->SetMultiNumber(m_nBulletAmmo);
	}
	// �n���h�K���Ɛ�Ԃ̏e�̂Ƃ�
	else
	{
		// �c�e���̔�\��
		m_pBulletAmmo->SetDisp(false);
		// �e��������UI�\��
		m_apScene2D[INFINITY_AMMO]->SetDisp(true);
	}
}

// =====================================================================================================================================================================
//
// �O���l�[�h�̎c���̐ݒ�
//
// =====================================================================================================================================================================
void CPlayerUI::SetGrenadeAmmo(int nGrenadeAmmo)
{
	// �O���l�[�h�̎c�����Z
	m_nGrenadeAmmo = nGrenadeAmmo;

	// �O���l�[�h�̎c���̐ݒ�
	m_pGrenadeAmmo->SetMultiNumber(m_nGrenadeAmmo);
}

// =====================================================================================================================================================================
//
// �̗�UI�̐ݒ�
//
// =====================================================================================================================================================================
void CPlayerUI::SetLifeUI(int nLife)
{
	m_nLife = nLife;

	if (m_nLife <= PLAYER_MAX_LIFE)
	{
		// �̗͂̎c���̔�\��
		m_pLife->SetDisp(false);

		// �e�N�X�`���̕�����
		D3DXVECTOR2 UVsize = D3DXVECTOR2(CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE).x * m_nLife, CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE).y);
		// �A�j���[�V�����̐ݒ�
		m_apScene2D[LIFE_ICON]->SetAnimation(CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_UI_LIFE), UVsize);
		// �T�C�Y�̐ݒ�
		m_apScene2D[LIFE_ICON]->SetSize(D3DXVECTOR3(20.0f * m_nLife, 20.0f, 0.0f));
	}
	else if (m_nLife <= 0)
	{
		// �̗͂�0��
		m_nLife = 0;
		// �̗͂̎c���̔�\��
		m_pLife->SetDisp(false);
	}
	else
	{
		// �e�N�X�`���̕�����
		D3DXVECTOR2 UVsize = D3DXVECTOR2(CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE).x * 1, CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE).y);
		// �A�j���[�V�����̐ݒ�
		m_apScene2D[LIFE_ICON]->SetAnimation(CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_UI_LIFE), UVsize);
		// �T�C�Y�̐ݒ�
		m_apScene2D[LIFE_ICON]->SetSize(D3DXVECTOR3(20.0f * 1, 20.0f, 0.0f));
		// �̗͂̎c���̕\��
		m_pLife->SetDisp(true);
		// �̗͂̎c���̐ݒ�
		m_pLife->SetMultiNumber(m_nLife);
	}
}

// =====================================================================================================================================================================
//
// �c�@�̐��̐ݒ�
//
// =====================================================================================================================================================================
void CPlayerUI::SetStockUI(int nStock)
{
	// �c�@���Z
	m_nStock = nStock;

	//0�ȉ��ɂȂ�Ȃ��悤�ɐݒ�
	CHossoLibrary::RangeLimit_Equal(m_nStock, 0, 9);

	// �c�@�̐ݒ�
	m_pStock->SetMultiNumber(m_nStock);
}

// =====================================================================================================================================================================
//
// �c�莞�Ԃ̐ݒ�
//
// =====================================================================================================================================================================
void CPlayerUI::SetTimeUI(int nTime)
{
	// �c�莞�Ԃ̐ݒ�
	m_nTime = nTime;

	//�\���̐ؑ�
	m_pTime->SetMultiNumber(m_nTime);

}

// =====================================================================================================================================================================
//
// �c�莞�Ԃ̌���
//
// =====================================================================================================================================================================
void CPlayerUI::DecrementTime()
{
	m_nTime--;

	//0�ȉ��ɂȂ�Ȃ��悤�ɂ���
	CHossoLibrary::RangeLimit_Equal(m_nTime, 0, DEFAULT_TIME);

	if (m_nTime <= 10)
	{
		//��
		m_pTime->SetCol(RedColor);
	}
	else
	{
		//��
		m_pTime->SetCol(WhiteColor);
	}


	// �X�R�A�̐ݒ�
	m_pTime->SetMultiNumber(m_nTime);
}
// =====================================================================================================================================================================
//
// ���Ԃ̃��Z�b�g
//
// =====================================================================================================================================================================
void CPlayerUI::ResetTime()
{
	//��
	m_pTime->SetCol(WhiteColor);

	//���ԃ��Z�b�g
	SetTimeUI(DEFAULT_TIME);
}
// =====================================================================================================================================================================
//
// �v���C���[UI�̐���
//
// =====================================================================================================================================================================
void CPlayerUI::PlayerUICreate(TAG Tag)
{
	// �v���C���[2��UI�̈ʒu
	if (Tag == TAG::PLAYER_2)
	{
		m_PLAYER_2_UI_FramePos	= PLAYER_2_UI_FRAME_POS;
		m_PLAYER_2_UI_ScorePos	= PLAYER_2_UI_SCORE_POS;
		m_PLAYER_2_UI_LifePos	= PLAYER_2_UI_LIFE_POS;
	}

	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			switch (nCnt)
			{
				// �g
			case PLAYER_UI::FRAME:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_FRAME_POS, PLAYER_UI_FRAME_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_FRAME));
				break;

				// �c�@		( ���� )
			case PLAYER_UI::STOCK_LETTER:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_STOCK_LETTER_POS, PLAYER_UI_STOCK_LETTER_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_REMAIN));
				break;

				// �c�e�� ( ���� )
			case PLAYER_UI::BULLET_AMMO_LETTER:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_BULLET_AMMO_LETTER_POS, PLAYER_UI_BULLET_AMMO_LETTER_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_ARMS));
				break;

				// �O���l�[�h�̎c�� ( ���� )
			case PLAYER_UI::GRENADE_AMMO_LETTER:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_GRENADE_AMMO_LETTER_POS, PLAYER_UI_GRENADE_AMMO_LETTER_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_BOMB));
				break;

				// �̗̓A�C�R��
			case PLAYER_UI::LIFE_ICON:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_LIFE_ICON_POS, PLAYER_UI_LIFE_ICON_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_LIFE));
				// �A�j���[�V�����̐ݒ�
				m_apScene2D[nCnt]->SetAnimation(CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_UI_LIFE), CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE));
				break;

				// �e������
			case PLAYER_UI::INFINITY_AMMO:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(PLAYER_UI_INFINITY_AMMO_POS, PLAYER_UI_INFINITY_AMMO_SIZE);
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_INFINITY));
				break;
			}
		}
	}

	// �X�R�A�̐���
	m_pScore = CMultiNumber::Create(PLAYER_UI_NUM_SCORE_POS, PLAYER_UI_NUM_SCORE_SIZE, m_nScore, 8, CScene::OBJTYPE_UI);
	// �c�e���̐���
	m_pBulletAmmo = CMultiNumber::Create(PLAYER_UI_NUM_BULLET_AMMO_POS, PLAYER_UI_NUM_BULLET_AMMO_SIZE, m_nBulletAmmo, 3, CScene::OBJTYPE_UI);
	// �O���l�[�h�̎c���̐���
	m_pGrenadeAmmo = CMultiNumber::Create(PLAYER_UI_NUM_GRENADE_AMMO_POS, PLAYER_UI_NUM_GRENADE_AMMO_SIZE, m_nGrenadeAmmo, 2, CScene::OBJTYPE_UI);
	// �̗͂̎c���̐���
	m_pLife = CMultiNumber::Create(PLAYER_UI_NUM_LIFE_POS, PLAYER_UI_NUM_LIFE_SIZE, m_nLife, 2, CScene::OBJTYPE_UI);
	// �c�@�̐���
	m_pStock = CMultiNumber::Create(PLAYER_UI_NUM_STOCK_POS, PLAYER_UI_NUM_STOCK_SIZE, m_nStock, 2, CScene::OBJTYPE_UI);
	// �c�莞�Ԃ̐���
	if (Tag == TAG::PLAYER_1)
	{
		m_pTime = CMultiNumber::Create(PLAYER_UI_NUM_TIME_POS, PLAYER_UI_NUM_TIME_SIZE, m_nTime, 2, CScene::OBJTYPE_UI);
	}
}
