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

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define PLAYER_MAX_LIFE		(5)

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPlayerUI::CPlayerUI()
{
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
	// �ϐ�������
	m_nScore		= 0;							// �X�R�A
	m_nBulletAmmo	= 0;							// �e�̎c�e��
	m_nGrenadeAmmo	= 0;							// �O���l�[�h�̎c�e��
	m_nLife			= 0;							// �̗�

	for (int nCnt = 0; nCnt < PLAYER_UI::PLAYER_UI_MAX; nCnt++)
	{
		if (!m_apScene2D[nCnt])
		{
			switch (nCnt)
			{
			// �g
			case PLAYER_UI::FRAME:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(225.0f, 65.0f, 0.0f), D3DXVECTOR3(70.0f, 35.0f, 0.0f));
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_FRAME));
				break;

			// �c�@		( ���� )
			case PLAYER_UI::REMAIN_LETTER:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(100.0f, 80.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_REMAIN));
				break;

			// �e�̎c�� ( ���� )
			case PLAYER_UI::BULLET_AMMO_LETTER:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(200.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_ARMS));
				break;

			// �O���l�[�h�̎c�� ( ���� )
			case PLAYER_UI::GRENADE_AMMO_LETTER:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(250.0f, 50.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_BOMB));
				break;

			// �̗̓A�C�R��
			case PLAYER_UI::LIFE_ICON:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(100.0f, 650.0f, 0.0f), D3DXVECTOR3(20.0f, 20.0f, 0.0f));
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_UI_LIFE));

				// �A�j���[�V�����̐ݒ�
				m_apScene2D[LIFE_ICON]->SetAnimation(CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_UI_LIFE), CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_UI_LIFE));

				break;

				// �e������
			case PLAYER_UI::INFINITY_AMMO:
				// �V�[��2D�̐���
				m_apScene2D[nCnt] = CScene2D::Create(D3DXVECTOR3(200.0f, 80.0f, 0.0f), D3DXVECTOR3(30.0f, 30.0f, 0.0f));
				// �e�N�X�`���̊��蓖��
				m_apScene2D[nCnt]->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_INFINITY));
				break;
			}
		}
	}
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
			m_apScene2D[nCnt]->Uninit();
		}
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
CPlayerUI * CPlayerUI::Create()
{
	//�������m��
	CPlayerUI *pPlayerUI = new CPlayerUI();

	// �������̊m��
	pPlayerUI = new CPlayerUI();

	// ������
	pPlayerUI->Init();

	// �X�R�A�̐���
	pPlayerUI->m_pScore = CMultiNumber::Create(D3DXVECTOR3(80.0f, 50.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), pPlayerUI->m_nScore, 8, CScene::OBJTYPE_UI);
	// �e�̎c���̐���
	pPlayerUI->m_pBulletAmmo = CMultiNumber::Create(D3DXVECTOR3(200.0f, 80.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), pPlayerUI->m_nBulletAmmo, 3, CScene::OBJTYPE_UI);
	// �O���l�[�h�̎c���̐���
	pPlayerUI->m_pGrenadeAmmo = CMultiNumber::Create(D3DXVECTOR3(250.0f, 80.0f, 0.0f), D3DXVECTOR3(10.0f, 10.0f, 0.0f), pPlayerUI->m_nGrenadeAmmo, 2, CScene::OBJTYPE_UI);
	// �̗͂̎c���̐���
	pPlayerUI->m_pLife = CMultiNumber::Create(D3DXVECTOR3(150.0f, 650.0f, 0.0f), D3DXVECTOR3(15.0f, 15.0f, 0.0f), pPlayerUI->m_nLife, 2, CScene::OBJTYPE_UI);

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
// �e�̎c���̐ݒ�
//
// =====================================================================================================================================================================
void CPlayerUI::SetBulletAmmo(int nBulletAmmo, CGun::GUN_TYPE GunType)
{
	// �n���h�K���ȊO�̂Ƃ�
	if (CGun::GUN_TYPE::GUNTYPE_HANDGUN != GunType)
	{
		// �e��������UI��\��
		m_apScene2D[INFINITY_AMMO]->SetDisp(false);
		// �e�̎c���̕\��
		m_pBulletAmmo->SetDisp(true);
		// �e�̎c�����Z
		m_nBulletAmmo = nBulletAmmo;
		// �e�̎c���̐ݒ�
		m_pBulletAmmo->SetMultiNumber(m_nBulletAmmo);
	}
	// �n���h�K���̂Ƃ�
	else
	{
		// �e�̎c���̔�\��
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
		// �̗͂̎c���̕\��
		m_pLife->SetDisp(true);
		// �̗͂̎c���̐ݒ�
		m_pLife->SetMultiNumber(m_nLife);
	}
}