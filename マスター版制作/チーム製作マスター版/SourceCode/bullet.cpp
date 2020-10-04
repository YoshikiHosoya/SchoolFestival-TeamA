// =====================================================================================================================================================================
//
// �o���b�g�̏��� [bullet.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "bullet.h"			// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "gun.h"
#include "collision.h"
#include "Player.h"
#include "Enemy.h"
#include "map.h"
#include "Obstacle.h"
#include "prisoner.h"
#include "particle.h"
#include "sound.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CBullet::BULLET_PARAM	CBullet::m_BulletParam[CGun::GUNTYPE_MAX] = {};

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CBullet::m_BulletFileName[CGun::GUNTYPE_MAX] =
{
	{ "data/Load/Gun/HandGun.txt" },				// �n���h�K��
	{ "data/Load/Gun/HeavyMachineGun.txt" },		// �w�r�[�}�V���K��
	{ "data/Load/Gun/ShotGun.txt" },				// �V���b�g�K��
	{ "data/Load/Gun/LaserGun.txt" },				// ���[�U�[�K��
	{ "data/Load/Gun/RocketLauncher.txt" },			// ���P�b�g�����`���[
	{ "data/Load/Gun/FlameShot.txt" },				// �t���C���V���b�g
	{ "data/Load/Gun/TankGun.txt" },				// ��Ԃ̏e
	{ "data/Load/Gun/PlaneGun.txt" },				// �퓬�@�̏e
	{ "data/Load/Gun/HeliGun.txt" },				// �w���̏e
	{ "data/Load/Gun/Balkan.txt" },					// �o���J��
	{ "data/Load/Gun/Flamethrower.txt" },			// �Ή����ˊ�
	{ "data/Load/Gun/Incendiary.txt" },				// �ĈΒe
	{ "data/Load/Gun/HandGrenade.txt" },			// �蓊���O���l�[�h
	{ "data/Load/Gun/TankGrenade.txt" },			// ��Ԃ̃O���l�[�h
	{ "data/Load/Gun/TrackingGun.txt" },			// �Ǐ]�e
	{ "data/Load/Gun/DiffusionGun.txt" },			// �g�U�e
	{ "data/Load/Gun/BossLazerGun.txt" },			// �{�X�̃��[�U�[
	{ "data/Load/Gun/HandGun_Enemy.txt" },			// �G�̃n���h�K��
	{ "data/Load/Gun/Missile.txt" },				// �~�T�C��
	{ "data/Load/Gun/FlameBullet.txt" },			// �t���C���o���b�g
	{ "data/Load/Gun/DropBomb.txt" },				// �h���b�v�{��
	{ "data/Load/Gun/DroneBeam.txt" },				// �h���b�v�{��
};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CBullet::CBullet(OBJ_TYPE type) :CModel(type)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CBullet::~CBullet()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CBullet::Init()
{
	// �ϐ�������
	m_move			= ZeroVector3;		// �ړ��l
	m_nLife			= 0;				// �̗�

	// ������
	CModel::Init();
	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CBullet::Uninit(void)
{
	CModel::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CBullet::Update(void)
{
	// �̗͂�0�ɂȂ�����
	if (m_nLife-- <= 0)
	{
		//�e������
		Rerease();
		return;
	}

	// �ʒu�̎擾
	D3DXVECTOR3 &rPos		= CModel::GetPosition();
	// �ʒu�X�V
	rPos += m_move;

	//�X�N���[���̒��ɂ��邩�ǂ���
	if (!CManager::GetRenderer()->CheckScreenRange(rPos))
	{
		//�e������
		Rerease();
		return;
	}

	// ------------- �����蔻�� ------------- //
	if (GetCollision() != nullptr)
	{
		// ����̍��W���X�V
		GetCollision()->SetPos(&GetPosition());

		// �Q�[���I�u�W�F�N�g( �^�O )�̐ݒ�
		GetCollision()->SetGameObject(this);

		// �}�b�v�̃|�C���^�擾
		CMap *pMap;
		pMap = CManager::GetBaseMode()->GetMap();

		if (pMap != nullptr)
		{
			// ���C�̔���
			if (GetCollision()->RayCollision(pMap, rPos - m_move, rPos))
			{

				DeleteBullet();
				return;
			}
		}

		// �v���C���[�̒e��������
		if (GetTag() == TAG::PLAYER_1 || GetTag() == TAG::PLAYER_2)
		{
			// �v���C���[�̒e�̔���
			if (GetCollision()->ForPlayerBulletCollision(m_BulletParam[m_GunType].nPower, m_BulletParam[m_GunType].nPower, false))
			{
				//���Đ�
				//�G��ߗ��ɓ����������ɉ��o������
				BulletHitSound();

				// �e�̍폜
				DeleteBullet();
				return;
			}
		}

		// �G�l�~�[�̒e��������
		else if (GetTag() == TAG::ENEMY)
		{
			// �G�l�~�[�̒e�̔���
			if (GetCollision()->ForEnemyCollision(m_BulletParam[m_GunType].nPower, m_BulletParam[m_GunType].nPower, false))
			{
				// �e�̍폜
				DeleteBullet();
				return;
			}
		}
	}

	// �X�V
	CModel::Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CBullet::Draw(void)
{
	// �`��
	CModel::Draw();
}

// =====================================================================================================================================================================
//
// �e����
//
// =====================================================================================================================================================================
void CBullet::DeleteBullet()
{
	/*switch (m_GunType)
	{
	case CGun::GUNTYPE_HANDGUN:
		break;
	case CGun::GUNTYPE_HEAVYMACHINEGUN:
		break;
	case CGun::GUNTYPE_SHOTGUN:
		break;
	case CGun::GUNTYPE_LASERGUN:
		break;
	case CGun::GUNTYPE_ROCKETLAUNCHER:
		break;
	case CGun::GUNTYPE_FLAMESHOT:
		break;
	case CGun::GUNTYPE_TANKGUN:
		break;
	case CGun::GUNTYPE_PLANEGUN:
		break;
	case CGun::GUNTYPE_HELIGUN:
		break;
	case CGun::GUNTYPE_BALKAN:
		break;
	case CGun::GUNTYPE_FLAMETHROWER:
		break;
	case CGun::GUNTYPE_INCENDIARY:
		break;
	case CGun::GUNTYPE_HANDGRENADE:
		break;
	case CGun::GUNTYPE_TANKGRENADE:
		break;
	case CGun::GUNTYPE_TRACKINGGUN:
		break;
	case CGun::GUNTYPE_DIFFUSIONGUN:
		break;
	case CGun::GUNTYPE_BOSSLASERGUN:
		break;
	case CGun::GUNTYPE_HANDGUN_ENEMY:
		break;
	case CGun::GUNTYPE_MISSILE:
		break;
	case CGun::GUNTYPE_FLAMEBULLET:
		break;
	case CGun::GUNTYPE_DROPBOMB:
		break;
	}*/

	// ��������

	// �ĈΒe�ȊO�̒e���Փ˂�������Ƃ��̃G�t�F�N�g
	if (m_GunType != CGun::GUNTYPE_INCENDIARY)
	{
		CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_DELETEBULLET);
	}
	// �ĈΒe�����e�����Ƃ��̃G�t�F�N�g �h���S���m�X�P�̏ĈΒe
	else
	{
		//�e����������SE
		CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION_04);
		CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION_INCENDIARY);
	}

	// �e�̍폜
	Rerease();
}

// =====================================================================================================================================================================
//
// �e�̔���
//
// =====================================================================================================================================================================
void CBullet::BulletReaction(D3DXVECTOR3 rot)
{
}


// =====================================================================================================================================================================
//
// �e�̃��[�h
//
// =====================================================================================================================================================================
void CBullet::BulletLoad()
{
	// �t�@�C���|�C���g
	FILE *pFile;

	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���
	D3DXVECTOR3 pos = ZeroVector3;	// �ʒu

	for (int nCnt = 0; nCnt < CGun::GUNTYPE_MAX; nCnt++)
	{
		// �t�@�C�����J��
		pFile = fopen(m_BulletFileName[nCnt], "r");

		// �J���Ă���Ƃ�
		if (pFile != NULL)
		{
			// SCRIPT������܂Ń��[�v
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
				sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������
			}

			// SCRIPT��������
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				// END_SCRIPT������܂Ń��[�v
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
					sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

					// BULLETSET��������
					if (strcmp(cHeadText, "BULLETSET") == 0)
					{
						// END_BULLETSET������܂Ń��[�v
						while (strcmp(cHeadText, "END_BULLETSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
							sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

							// SPEED��������
							if (strcmp(cHeadText, "SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_BulletParam[nCnt].fBulletSpeed);		// ��r�p�e�L�X�g��SPEED����
							}
							// LIFE��������
							else if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nLife);			// ��r�p�e�L�X�g��LIFE����
							}
							// POWER��������
							else if (strcmp(cHeadText, "POWER") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nPower);			// ��r�p�e�L�X�g��POWER����
							}
							// AMMO��������
							else if (strcmp(cHeadText, "AMMO") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nAmmo);			// ��r�p�e�L�X�g��AMMO����
							}
							// TRIGGER��������
							else if (strcmp(cHeadText, "TRIGGER") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nTrigger);			// ��r�p�e�L�X�g��TRIGGER����
							}
							// INTERVAL��������
							else if (strcmp(cHeadText, "INTERVAL") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nInterval);		// ��r�p�e�L�X�g��INTERVAL����
							}
							// COLLISIONSIZE��������
							else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_BulletParam[nCnt].CollisionSize.x
																				, &m_BulletParam[nCnt].CollisionSize.y
																				, &m_BulletParam[nCnt].CollisionSize.z);		// ��r�p�e�L�X�g��COLLISIONSIZE����
							}
							else if (strcmp(cHeadText, "END_BULLETSET") == 0)
							{
							}
						}
					}
				}
			}
			// �t�@�C�������
			fclose(pFile);
		}
		else
		{
			// �ǂݍ��ݎ��s���̌x���\��
			MessageBox(NULL, "�e�̃p�����[�^�[�ǂݍ��ݎ��s" ,m_BulletFileName[nCnt], MB_ICONWARNING);
		}
	}
}

// =====================================================================================================================================================================
//
// �e�̔��˕����v�Z
//
// =====================================================================================================================================================================
void CBullet::CalcBulletMove(D3DXVECTOR3 ShotRot, int Guntype)
{
	m_move = D3DXVECTOR3(-sinf(ShotRot.z) * m_BulletParam[Guntype].fBulletSpeed, cosf(ShotRot.z) * m_BulletParam[Guntype].fBulletSpeed, 0.0f);
}

// =====================================================================================================================================================================
//
// �e�̔��˕����v�Z
//
// =====================================================================================================================================================================
void CBullet::CalcIncendiaryMove(D3DXVECTOR3 ShotRot, float move, float move_y)
{
	m_move = D3DXVECTOR3(-sinf(ShotRot.z) * move, cosf(ShotRot.z) * move_y, 0.0f);
}

// =====================================================================================================================================================================
//
// �e�̃p�����[�^�[�ݒ�
//
// =====================================================================================================================================================================
void CBullet::SetBulletParam(CGun::GUN_TYPE type)
{
	m_nLife = m_BulletParam[type].nLife;	// �̗�

	m_GunType = type;

	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetMove(&m_move);
	GetCollision()->SetSize(m_BulletParam[type].CollisionSize);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
}

// =====================================================================================================================================================================
//
// �e�������������ɉ��Đ�
//
// =====================================================================================================================================================================
void CBullet::BulletHitSound()
{
	//�e�̎�ނɂ���ĉ��Đ�
	switch (m_GunType)
	{
	case CGun::GUNTYPE_HANDGUN:
	case CGun::GUNTYPE_HEAVYMACHINEGUN:
	case CGun::GUNTYPE_TANKGUN:
	case CGun::GUNTYPE_PLANEGUN:
	case CGun::GUNTYPE_HELIGUN:
	case CGun::GUNTYPE_BALKAN:
	case CGun::GUNTYPE_TRACKINGGUN:
	case CGun::GUNTYPE_DIFFUSIONGUN:
		//�e����������SE
		CManager::GetSound()->Play(CSound::LABEL_SE_BULLET_HIT);
		break;


	//case CGun::GUNTYPE_INCENDIARY:
	//	//�e����������SE
	//	CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION_00);
	//	break;

	default:
		break;
	}
}


