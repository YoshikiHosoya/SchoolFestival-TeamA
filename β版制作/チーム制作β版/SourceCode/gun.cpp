// =====================================================================================================================================================================
//
// �K���̏��� [gun.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "gun.h"			// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "handgun.h"
#include "heavymachinegun.h"
#include "shotgun.h"
#include "lasergun.h"
#include "rocketlauncher.h"
#include "flameshot.h"
#include "tankturret.h"
#include "Character.h"
#include "TexAnimation3D.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define HEAVYMACHINEGUN_SHOT_FRAME				(3)			// �w�r�[�}�V���K���̒e�̊Ԋu

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CGun::CGun(OBJ_TYPE type) :CModel(type)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CGun::~CGun()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CGun::Init()
{
	m_bMultiple		= false;										// �t���O���I�t
	m_GunType		= GUN_TYPE::GUNTYPE_HANDGUN;					// �n���h�K���ɐݒ�
	m_nCntFrame		= 0;											// �t���[���J�E���g
	m_nCntBullet	= 0;											// �e�̃J�E���g
	m_nAmmo			= CBullet::GetBulletParam(m_GunType)->nAmmo;	// �c�e��
	m_nInterval		= 0;											// ���Ɍ����߂̃C���^�[�o��
	m_ShotPos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���ˈʒu
	m_ShotOffsetPos	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���ˈʒu�̃I�t�Z�b�g
	m_ShotRot		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���Ƃ��̉�]�̌���
	m_bDraw			= false;										// �`��t���O

	// ������
	CModel::Init();

	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CGun::Uninit(void)
{
	// �I��
	CModel::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CGun::Update(void)
{
	// �C���^�[�o���J�E���g�A�b�v
	m_nInterval++;

	// �������t���O���I���̂Ƃ�
	if (m_bMultiple)
	{
		// �t���[���J�E���g�A�b�v
		m_nCntFrame++;

		// ������������
		MultipleShot();
	}

	// �e�򂪖����Ȃ����Ƃ�
	if (m_nAmmo <= 0)
	{
		// �e�򐔂�0�ɂ���
		m_nAmmo = 0;
		// �n���h�K���ɖ߂�
		m_GunType = GUN_TYPE::GUNTYPE_HANDGUN;
	}

	// �X�V
	CModel::Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CGun::Draw(void)
{
	// ��蕨�ɏ���Ă�����`�悵�Ȃ�
	if (m_bDraw == false)
	{
		// �`��
		CModel::Draw(*m_mtx);
	}
}
// =====================================================================================================================================================================
//
// �f�o�b�O
//
// =====================================================================================================================================================================
void CGun::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// �e�̐���
//
// =====================================================================================================================================================================
CGun * CGun::Create(D3DXMATRIX *mtx)
{
	// �ϐ�
	CGun *pGun;

	// �������̊m��
	pGun = new CGun(OBJTYPE_MODEL);

	// ������
	pGun->Init();

	// �}�g���b�N�X���
	pGun->m_mtx = mtx;

	// ���f���^�C�v�̐ݒ�
	pGun->SetType(GUN_MODEL);

	// ���f���J�E���g�̐ݒ�
	pGun->SetModelConut(MODEL_GUN_HANDGUN);

	return pGun;
}

// =====================================================================================================================================================================
//
// �e�̎�ނ̐ݒ�
//
// =====================================================================================================================================================================
void CGun::SetGunType(GUN_TYPE type)
{
	BULLET_PARAM *pBulletParam = CBullet::GetBulletParam(type);

	// ���f���̍����ւ�
	SetModelConut(type);

	// ��ނ̐ݒ�
	m_GunType = type;

	// �e��
	m_nAmmo = pBulletParam->nAmmo;
}

// =====================================================================================================================================================================
//
// �e�̔���
//
// =====================================================================================================================================================================
void CGun::Shot()
{
	CBullet *pBullet = nullptr;

	// �n���h�K���Ɛ�ԖC��ȊO�̂Ƃ�
	if (m_GunType != GUNTYPE_HANDGUN && m_GunType != GUNTYPE_TANKTURRET)
	{
		// �c�e�������炷
		m_nAmmo--;
	}

	// �C���^�[�o�����o�߂����Ƃ�
	if (m_nInterval >= CBullet::GetBulletParam(m_GunType)->nInterval)
	{
		m_nInterval = 0;

		switch (m_GunType)
		{
		case CGun::GUNTYPE_HANDGUN:
			// �n���h�K���̐���
			pBullet = CHandgun::Create(m_ShotRot);
			break;

		case CGun::GUNTYPE_HEAVYMACHINEGUN:
			// �w�r�[�}�V���K���̐���
			pBullet = CHeavyMachinegun::Create(m_ShotRot);
			m_bMultiple = true;		// �t���O���I��
			break;

		case CGun::GUNTYPE_SHOTGUN:
			// �V���b�g�K���̐���
			pBullet = CShotgun::Create(m_ShotRot);
			break;

		case CGun::GUNTYPE_LASERGUN:
			// ���[�U�[�K���̐���
			pBullet = CLasergun::Create(m_ShotRot);
			break;

		case CGun::GUNTYPE_ROCKETLAUNCHER:
			// ���P�b�g�����`���[�̐���
			pBullet = CRocketlauncher::Create(m_ShotRot);
			break;

		case CGun::GUNTYPE_FLAMESHOT:
			// �t���C���V���b�g�̐���
			pBullet = CFlameshot::Create(m_ShotRot);
			m_bMultiple = true;		// �t���O���I��
			break;

		case CGun::GUNTYPE_TANKTURRET:
			// ��ԖC��̐���
			pBullet = CTankTurret::Create(m_ShotRot);
			m_bMultiple = true;		// �t���O���I��
			break;
		}
		if (pBullet)
		{
			D3DXVec3TransformCoord(&m_ShotPos, &m_ShotOffsetPos, GetMatrix());

			// �ʒu�̐ݒ�
			pBullet->SetPosition(m_ShotPos);

			// �^�O�̐ݒ�
			pBullet->SetTag(m_Tag);

			// �e�̃p�����[�^�[�̐ݒ�
			pBullet->SetBulletParam(m_GunType);

			// �e���C���̃��A�N�V����
			pBullet->BulletReaction(m_ShotRot);

			//�m�Y���t���b�V��
			CTexAnimation3D::Create(m_ShotPos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
				CTexture::SEPARATE_TEX_EFFECT_SHOTFLASH, 1, CScene::OBJTYPE_EFFECT);
		}
	}
}

// =====================================================================================================================================================================
//
// ������������
//
// =====================================================================================================================================================================
void CGun::MultipleShot()
{
	CBullet *pBullet = nullptr;

	float randPos_y = (float)(rand() % 10 - 5);

	if (m_nCntBullet < CBullet::GetBulletParam(m_GunType)->nTrigger)
	{
		if (m_nCntFrame >= HEAVYMACHINEGUN_SHOT_FRAME)
		{
			// �t���[���J�E���g������
			m_nCntFrame = 0;

			// �w�r�[�}�V���K���̂Ƃ�
			if (m_GunType == GUNTYPE_HEAVYMACHINEGUN)
			{
				// �e�̐���
				pBullet = CHeavyMachinegun::Create(m_ShotRot);
			}
			// �t���C���V���b�g�̂Ƃ�
			if (m_GunType == GUNTYPE_FLAMESHOT)
			{
				// �e�̐���
				pBullet = CFlameshot::Create(m_ShotRot);
			}
			// ��ԖC��̂Ƃ�
			if (m_GunType == GUNTYPE_TANKTURRET)
			{
				// �e�̐���
				pBullet = CTankTurret::Create(m_ShotRot);
			}

			// �e�̃J�E���g�A�b�v
			m_nCntBullet++;

			if (pBullet)
			{
				D3DXVec3TransformCoord(&m_ShotPos, &m_ShotOffsetPos, GetMatrix());

				// �ʒu�̐ݒ�
				pBullet->SetPosition(D3DXVECTOR3(m_ShotPos.x, m_ShotPos.y + randPos_y, m_ShotPos.z));

				// �e�̎�ނ̐ݒ�
				pBullet->SetTag(m_Tag);

				// �e�̃p�����[�^�[�̐ݒ�
				pBullet->SetBulletParam(m_GunType);

				// �e�̔���
				pBullet->BulletReaction(m_ShotRot);

				//�m�Y���t���b�V��
				CTexAnimation3D::Create(m_ShotPos, D3DXVECTOR3(30.0f, 30.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f),
					CTexture::SEPARATE_TEX_EFFECT_SHOTFLASH, 1, CScene::OBJTYPE_EFFECT);

			}
		}
	}
	else
	{
		// �t���[���J�E���g������
		m_nCntBullet = 0;

		// �������t���O���I�t
		m_bMultiple = false;
	}
}