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
#include "rocketlauncher.h"
#include "flameshot.h"
#include "tankgun.h"
#include "planegun.h"
#include "Character.h"
#include "TrackingGun.h"
#include "diffusiongun.h"
#include "sound.h"
#include "particle.h"
#include "balkan.h"
#include "incendiary.h"
#include "flamethrower.h"
// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define HEAVYMACHINEGUN_SHOT_FRAME				(5)			// �w�r�[�}�V���K���̒e�̊Ԋu
#define MAX_AMMO								(999)		// �c�e���̍ő�l

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CGun::CGun()
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
	m_GunTypeOld	= GUN_TYPE::GUNTYPE_HANDGUN;					// �O��̏e�̎��
	m_nCntFrame		= 0;											// �t���[���J�E���g
	m_nCntBullet	= 0;											// �e�̃J�E���g
	m_nAmmo			= CBullet::GetBulletParam(m_GunType)->nAmmo;	// �c�e��
	m_nInterval		= 0;											// ���Ɍ����߂̃C���^�[�o��
	m_ShotPos		= ZeroVector3;									// ���ˈʒu
	m_ShotOffsetPos	= ZeroVector3;									// ���ˈʒu�̃I�t�Z�b�g
	m_ShotRot		= ZeroVector3;									// ���Ƃ��̉�]�̌���
	m_bDraw			= false;										// �`��t���O
	m_bMoveZero		= false;										// �ړ��𖳌��ɂ���t���O

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
	// �C���^�[�o���J�E���g�_�E��
	if (m_nInterval-- <= 0)
	{
		m_nInterval = 0;
	}

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
		m_nAmmo = -1;
		// �n���h�K���ɖ߂�
		m_GunType = GUN_TYPE::GUNTYPE_HANDGUN;
	}

	// �c�e���̍ő�l
	if (m_nAmmo >= MAX_AMMO)
	{
		m_nAmmo = MAX_AMMO;
	}

	//ShotPos�v�Z
	D3DXVec3TransformCoord(&m_ShotPos, &m_ShotOffsetPos, GetMatrix());

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
		CModel::Draw(*m_HasHandMtx);
	}
}


// =====================================================================================================================================================================
//
// �f�o�b�O
//
// =====================================================================================================================================================================
void CGun::DebugInfo()
{
	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "GunInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{
		ImGui::Text("m_ShotPos [%.2f %.2f %.2f]", m_ShotPos.x, m_ShotPos.y, m_ShotPos.z); ImGui::SameLine();
		ImGui::Text("m_ShotRot [%.2f %.2f %.2f]", m_ShotRot.x, m_ShotRot.y, m_ShotRot.z);

		ImGui::Text("m_GunType [%d]", m_GunType); ImGui::SameLine();
		ImGui::Text("m_nAmmo [%d]", m_nAmmo);
		ImGui::Text("m_nInterval [%d]", m_nInterval); ImGui::SameLine();
		ImGui::Text("m_nCntFrame [%d]", m_nCntFrame); ImGui::SameLine();
		ImGui::Text("m_nCntBullet [%d]", m_nCntBullet);
		ImGui::Text("m_bDraw [%d]", m_bDraw); ImGui::SameLine();
		ImGui::Text("m_bMoveZero [%d]", m_bMoveZero);

		ImGui::TreePop();
	}
}

// =====================================================================================================================================================================
//
// �e�̐���
//
// =====================================================================================================================================================================
CGun * CGun::Create()
{
	// �ϐ�
	CGun *pGun;

	// �������̊m��
	pGun = new CGun();

	// ������
	pGun->Init();

	// ���f���^�C�v�̐ݒ�
	pGun->SetType(GUN_MODEL);

	// ���f���J�E���g�̐ݒ�
	pGun->SetModelConut(MODEL_GUN_HANDGUN);

	return pGun;
}

// =====================================================================================================================================================================
//
// �}�g���b�N�X�̌v�Z��������
//
// =====================================================================================================================================================================
void CGun::NoDrawCalcMatrixOnly()
{
	CModel::NotDrawCalcMtxOnly(m_HasHandMtx);
}

// =====================================================================================================================================================================
//
// �e�̎�ނ̐ݒ�
//
// =====================================================================================================================================================================
void CGun::SetGunType(GUN_TYPE type)
{
	// �e�̃p�����[�^�[�擾
	CBullet::BULLET_PARAM *pBulletParam = CBullet::GetBulletParam(type);

	// ���f���̍����ւ�
	SetModelConut(type);

	// �O��̏e�̎�ނ�ۑ�
	m_GunTypeOld = m_GunType;

	// ��ނ̐ݒ�
	m_GunType = type;

	// �O��Ǝ�ނ��Ⴄ�Ƃ�
	if (m_GunType != m_GunTypeOld)
	{
		// �e��
		m_nAmmo = pBulletParam->nAmmo;
	}
	else
	{
		// �e�򐔕�[
		m_nAmmo += pBulletParam->nAmmo;
	}
}

// =====================================================================================================================================================================
//
// �e���̉��Z
//
// =====================================================================================================================================================================
void CGun::GunAddAmmo(GUN_TYPE type)
{
	// �e�̃p�����[�^�[�擾
	CBullet::BULLET_PARAM *pBulletParam = CBullet::GetBulletParam(type);

	m_nAmmo += pBulletParam->nAmmo;
}

// =====================================================================================================================================================================
//
// �e�̔���
//
// =====================================================================================================================================================================
void CGun::Shot()
{
	//��ʊO���甭�˕s��
	if (!CManager::GetRenderer()->CheckScreenRange(m_ShotPos))
	{
		return;
	}

	CBullet *pBullet = nullptr;


	// �C���^�[�o�����o�߂����Ƃ�
	if (m_nInterval <= 0)
	{
		// �n���h�K���Ɛ�Ԃ̏e�ȊO�̂Ƃ�
		if (m_GunType != GUNTYPE_HANDGUN && m_GunType != GUNTYPE_TANKGUN &&
			m_GunType != GUNTYPE_BALKAN && m_GunType != GUNTYPE_FLAMETHROWER &&
			m_GunType != GUNTYPE_INCENDIARY)
		{
			// �c�e�������炷
			m_nAmmo--;
		}
		m_nInterval = CBullet::GetBulletParam(m_GunType)->nInterval;

		switch (m_GunType)
		{
		case CGun::GUNTYPE_HANDGUN:
		case CGun::GUNTYPE_HANDGUN_ENEMY:

			// �n���h�K���̐���
			pBullet = CHandgun::Create(m_ShotRot,GetTag());

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_HANDGUN);

			//�m�Y���t���b�V��
			CParticle::CreateFromText(m_ShotPos, ZeroVector3, CParticleParam::EFFECT_SHOTFLASH, GetTag());

			break;

		case CGun::GUNTYPE_HEAVYMACHINEGUN:
			// �w�r�[�}�V���K���̐���
			pBullet = CHeavyMachinegun::Create(m_ShotRot);

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_MACHINEGUN);

			//�m�Y���t���b�V��
			CParticle::CreateFromText(m_ShotPos, ZeroVector3, CParticleParam::EFFECT_SHOTFLASH, GetTag());

			m_bMultiple = true;		// �t���O���I��
			break;

		case CGun::GUNTYPE_SHOTGUN:
			// �V���b�g�K���̐���
			CParticle::CreateFromText(m_ShotPos, m_ShotRot, CParticleParam::EFFECT_SHOTGUN, GetTag(), CBullet::GetBulletParam(CGun::GUNTYPE_SHOTGUN)->nPower);
			CParticle::CreateFromText(m_ShotPos, m_ShotRot, CParticleParam::EFFECT_SHOTGUN_ADDEFFECT, GetTag(), CBullet::GetBulletParam(CGun::GUNTYPE_SHOTGUN)->nPower);


			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_SHOTGUN);

			//�m�Y���t���b�V��
			CParticle::CreateFromText(m_ShotPos, ZeroVector3, CParticleParam::EFFECT_SHOTFLASH, GetTag());

			break;

		case CGun::GUNTYPE_LASERGUN:
			// ���[�U�[�K���̐���
			CParticle::CreateFromText(m_ShotPos, m_ShotRot, CParticleParam::EFFECT_LAZER, GetTag(), CBullet::GetBulletParam((int)CGun::GUNTYPE_LASERGUN)->nPower, D3DXCOLOR(0.0f, 0.0f, 0.0f, -1.0f), GetShotPosPtr());

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_LASER);

			//�m�Y���t���b�V��
			CParticle::CreateFromText(m_ShotPos, ZeroVector3, CParticleParam::EFFECT_SHOTFLASH, GetTag());

			break;

		case CGun::GUNTYPE_ROCKETLAUNCHER:
			// ���P�b�g�����`���[�̐���
			pBullet = CRocketlauncher::Create(m_ShotRot);

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_LAUNCHER);

			break;

		case CGun::GUNTYPE_FLAMESHOT:
			// �t���C���V���b�g�̐���
			pBullet = CFlameshot::Create(m_ShotRot);

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_FIRE);

			break;

		case CGun::GUNTYPE_TANKGUN:
			// ��Ԃ̏e�̐���
			pBullet = CTankGun::Create(m_ShotRot);

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_MACHINEGUN);

			//�m�Y���t���b�V��
			CParticle::CreateFromText(m_ShotPos, ZeroVector3, CParticleParam::EFFECT_SHOTFLASH, GetTag(),-1,BlueColor);		// ���~��)�v���C���[�^�O��ς����悤�ɂ���

			m_bMultiple = true;		// ���������t���O���I��
			break;

		case CGun::GUNTYPE_PLANEGUN:
			// ��Ԃ̏e�̐���
			pBullet = CPlaneGun::Create(m_ShotRot);

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_MACHINEGUN);

			//�m�Y���t���b�V��
			CParticle::CreateFromText(m_ShotPos, ZeroVector3, CParticleParam::EFFECT_SHOTFLASH, GetTag(), -1, BlueColor);	// ���~��)�v���C���[�^�O��ς����悤�ɂ���

			m_bMultiple = true;		// ���������t���O���I��
			break;
		case CGun::GUNTYPE_TRACKINGGUN:
			// �Ǐ]�e
			pBullet = CTracking::Create(m_ShotRot);
			break;
		case CGun::GUNTYPE_DIFFUSIONGUN:
			// �g�U�e
			pBullet = CDiffusion::Create(m_ShotRot);
			break;
		case CGun::GUNTYPE_BOSSLASERGUN:
			// �g�U�e
			CParticle::CreateFromText(m_ShotPos, m_ShotRot, CParticleParam::EFFECT_BOSSLAZER, GetTag(), CBullet::GetBulletParam((int)CGun::GUNTYPE_BOSSLASERGUN)->nPower, D3DXCOLOR(0.0f, 0.0f, 0.0f, -1.0f), GetShotPosPtr());
			break;

		case CGun::GUNTYPE_BALKAN:
			//
			pBullet = CBalkan::Create(m_ShotRot);
			break;
		case CGun::GUNTYPE_FLAMETHROWER:
			//
			pBullet = CFlamethrower::Create(m_ShotRot);
			break;
		case CGun::GUNTYPE_INCENDIARY:
			//
			pBullet = CIncendiary::Create(m_ShotRot);
			break;

		}
		if (pBullet)
		{
			// �ʒu�̐ݒ�
			pBullet->SetPosition(m_ShotPos);

			// �^�O�̐ݒ�
			pBullet->SetTag(GetTag());

			// �e�̃p�����[�^�[�̐ݒ�
			pBullet->SetBulletParam(m_GunType);

			// �e�̈ړ��ʂ�0�ɂ���
			if (m_bMoveZero)
			{
				pBullet->SetMove(ZeroVector3);
			}

			// �e���C���̃��A�N�V����
			pBullet->BulletReaction(m_ShotRot);
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

	float randPos_y = (float)(rand() % 10 - 3);

	if (m_nCntBullet < (CBullet::GetBulletParam(m_GunType)->nTrigger))
	{
		if (m_nCntFrame >= HEAVYMACHINEGUN_SHOT_FRAME)
		{
			// �t���[���J�E���g������
			m_nCntFrame = 0;

			// �c�e�������炷
			m_nAmmo--;

			// �w�r�[�}�V���K���̂Ƃ�
			if (m_GunType == GUNTYPE_HEAVYMACHINEGUN)
			{
				// �e�̐���
				pBullet = CHeavyMachinegun::Create(m_ShotRot);
			}
			// ��Ԃ̏e�̂Ƃ�
			if (m_GunType == GUNTYPE_TANKGUN)
			{
				// �e�̐���
				pBullet = CTankGun::Create(m_ShotRot);
			}

			// �e�̃J�E���g�A�b�v
			m_nCntBullet++;

			if (pBullet)
			{
				D3DXVec3TransformCoord(&m_ShotPos, &m_ShotOffsetPos, GetMatrix());

				// �ʒu�̐ݒ�
				pBullet->SetPosition(D3DXVECTOR3(m_ShotPos.x, m_ShotPos.y + randPos_y, m_ShotPos.z));

				// �e�̎�ނ̐ݒ�
				pBullet->SetTag(GetTag());

				// �e�̃p�����[�^�[�̐ݒ�
				pBullet->SetBulletParam(m_GunType);

				// �e�̔���
				pBullet->BulletReaction(m_ShotRot);

				//���Đ�
				CManager::GetSound()->Play(CSound::LABEL_SE_SHOT_MACHINEGUN);


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