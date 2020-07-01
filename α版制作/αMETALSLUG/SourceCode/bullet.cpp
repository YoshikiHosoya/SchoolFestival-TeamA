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
#define BULLET_LIFE			(100)			// �e�̗̑�

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
	m_pCollision	= NULL;									// �����蔻��̃|�C���^
	m_nLife			= 0;				// �̗�

	// ������
	CModel::Init();

	// �����蔻�萶��
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(D3DXVECTOR3(40.0f, 40.0f, 0.0f));
	m_pCollision->SetMove(&m_move);
	m_pCollision->SetType(CCollision::OBJTYPE_PLAYERBULLET);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

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
		if (m_pCollision != nullptr)
		{
			// ����̍폜
			m_pCollision->ReleaseCollision(m_pCollision);
			m_pCollision = nullptr;
		}
		Rerease();
	}

	// �ʒu�̐ݒ�
	CModel::SetPosition(pos);

	// ------------- �����蔻�� ------------- //
	if (m_pCollision != nullptr)
	{
		// ����̍��W���X�V
		m_pCollision->SetPos(&GetPosition());

		// �v���C���[�̒e��������
		if (m_pCollision->GetObjtype() == CCollision::OBJTYPE_PLAYERBULLET)
		{
			// �����蔻�� ���肪�G�l�~�[��������
			// �G�̑�����
			for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
			{
				CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
				if (pEnemy != nullptr && m_pCollision != nullptr)
				{
					if (m_pCollision->OtherCollision2D(pEnemy->GetCollision()))
					{
						// �G�̃��C�t����
						pEnemy->CCharacter::AddDamage(10);
						if (pEnemy->CCharacter::GetLife() <= 0)
						{
							// �G�̓����蔻��̍폜
							pEnemy->DeleteCollision();
							pEnemy = nullptr;
						}

						// �e�̔���̍폜
						m_pCollision->ReleaseCollision(m_pCollision);
						m_pCollision = nullptr;
						// �e�̍폜
						Rerease();
					}
					else
					{
						CDebugProc::Print("\n�e���G�ɓ������ĂȂ���I \n");
					}
				}
			}

			// �����蔻�� ���肪��Q����������
			// ��Q���̑�����
			for (int nCntObst = 0; nCntObst < CManager::GetBaseMode()->GetMap()->GetMaxObstacle(); nCntObst++)
			{
				CObstacle *pObstacle = CManager::GetBaseMode()->GetMap()->GetObstacle(nCntObst);
				if (pObstacle != nullptr && m_pCollision != nullptr)
				{
					if (m_pCollision->Collision2D(pObstacle->GetCollision()))
					{
						// ��Q���̃��C�t����
						pObstacle->Hit(CObstacle::TYPE_BOX,10);

						if (pObstacle->GetLife() <= 0)
						{
							pObstacle->DeleteCollision();
							pObstacle = nullptr;
						}
						// �e�̔���̍폜
						m_pCollision->ReleaseCollision(m_pCollision);
						// �e�̓�����̃|�C���^��null�ɂ���
						m_pCollision = nullptr;

						// �e�̍폜
						Rerease();
					}
					else
					{
						CDebugProc::Print("\n�e����Q���ɓ������ĂȂ���I \n");
					}
				}
			}
		}

		// �G�l�~�[�̒e��������
		//else if (m_pCollision->GetObjtype() == CCollision::OBJTYPE_ENEMYBULLET)
		//{
		//	// �����蔻�� ���肪�v���C���[��������
		//	if (m_pCollision->Collision2D(CCollision::OBJTYPE_PLAYER))
		//	{
		//		// ����̍폜
		//		m_pCollision->Delete(m_pCollision);
		//		m_pCollision = NULL;
		//		// �e�̍폜
		//		Rerease();
		//		// �v���C���[�̃��C�t����
		//		//pPlayer->CCharacter::SetLife(-10);
		//	}
		//}
	}

	// �X�V
	CModel::Update();

#ifdef _DEBUG
	// �f�o�b�O�\��
	CDebugProc::Print("\n\nbullet_type %d\n\n", m_type);		// �e�̎��(�������G���j
#endif // DEBUG
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
// �e����������
//
// =====================================================================================================================================================================
void CBullet::DeleteBullet()
{
	// �e�̔���̍폜
	m_pCollision->ReleaseCollision(m_pCollision);
	m_pCollision = nullptr;
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