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
#include "TexAnimation3D.h"
// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
BULLET_PARAM	CBullet::m_BulletParam[CGun::GUNTYPE_MAX] = {};

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
	{ "data/Load/Gun/Grenade.txt" },				// �O���l�[�h
};

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define BULLET_LIFE				(100)			// �e�̗̑�

// �e�̃_���[�W
#define BULLET_DAMAGE_ENEMY		(10)			// �G�l�~�[�ւ̃_���[�W
#define BULLET_DAMAGE_OBSTACLE	(10)			// ��Q���ւ̃_���[�W
#define BULLET_DAMAGE_PLAYER	(10)			// �v���C���[�ւ̃_���[�W

// �ђʂ����邩�̃t���O
#define BULLET_PENETRATION		(false)			// �e�̔��肪�ђʂ��邩�ǂ���

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
	m_move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ��l
	m_nLife			= 0;				// �̗�

	// ������
	CModel::Init();

	// �����蔻�萶��
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(D3DXVECTOR3(40.0f, 40.0f, 0.0f));
	GetCollision()->SetMove(&m_move);
	GetCollision()->SetType(CCollision::COLLISION_PLAYERBULLET);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

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
	// �ʒu�̎擾
	D3DXVECTOR3 pos		= CModel::GetPosition();

	// �ʒu�X�V
	pos += m_move;

	// �̗͌���												�z���[ 0 ]�̂Ƃ���ɂ͏e�̎�ނ�����
	m_nLife--;

	// �̗͂�0�ɂȂ�����									�z���[ 0 ]�̂Ƃ���ɂ͏e�̎�ނ�����
	if (m_nLife <= 0)
	{
		Rerease();
	}

	// �ʒu�̐ݒ�
	CModel::SetPosition(pos);

	// ------------- �����蔻�� ------------- //
	if (GetCollision() != nullptr)
	{
		// ����̍��W���X�V
		GetCollision()->SetPos(&GetPosition());

		// �v���C���[�̒e��������
		if (m_type == TYPE_PLAYER)
		{
			// �v���C���[�̒e�̔���
			if (GetCollision()->ForPlayerBulletCollision(BULLET_DAMAGE_ENEMY, BULLET_DAMAGE_OBSTACLE, BULLET_PENETRATION))
			{
				// �e�̍폜
				DeleteBullet();
			}
		}

		// �G�l�~�[�̒e��������
		else if (m_type == TYPE_ENEMY)
		{
			// �G�l�~�[�̒e�̔���
			if (GetCollision()->ForEnemyCollision(BULLET_DAMAGE_PLAYER, BULLET_PENETRATION))
			{
				// �e�̍폜
				DeleteBullet();
			}
		}
	}

	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// �}�b�v���f�������݂�����
	if (pMap != nullptr)
	{
		// ���C�̔���
		if (GetCollision()->RayCollision(pMap))
		{
			DeleteBullet();
		}
		else
		{
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
	CTexAnimation3D::Create(GetPosition(), D3DXVECTOR3(15.0f, 15.0f, 0.0f), ZeroVector3, CTexture::SEPARATE_TEX_EFFECT_HITEFFECT, 1, OBJTYPE_EFFECT);

	// �e�̍폜
	Rerease();
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
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu

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
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_BulletParam[nCnt].fPower);			// ��r�p�e�L�X�g��POWER����
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
			MessageBox(NULL, "�e�̃p�����[�^�[�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
		}
	}
}

// =====================================================================================================================================================================
//
// �e�̃p�����[�^�[�ݒ�
//
// =====================================================================================================================================================================
void CBullet::SetBulletParam(CGun::GUN_TYPE type)
{
	m_nLife = m_BulletParam[type].nLife;	// �̗�
}