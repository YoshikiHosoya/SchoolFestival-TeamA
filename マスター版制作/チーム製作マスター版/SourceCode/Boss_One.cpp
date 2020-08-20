// =====================================================================================================================================================================
//
// �{�X1�̏��� [boss_one.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "Boss_One.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "manager.h"
#include "map.h"
#include "gun.h"

//====================================================================
//�}�N����`
//====================================================================

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
BOSS_ONE_DATA		CBoss_One::m_BossOneData = {};									// �f�[�^
int					CBoss_One::m_nLife = 0;											// �̗�
D3DXVECTOR3			CBoss_One::m_CollisionSize[POSTURETYPE_MAX] = {};				// �����蔻��̑傫��
D3DXVECTOR3			CBoss_One::m_GunShotOfsetPos[WEAPONTYPE_MAX] = {};				// �K���̃I�t�Z�b�g

// =====================================================================================================================================================================
// �e�L�X�g�t�@�C����
// =====================================================================================================================================================================
char *CBoss_One::m_BossOneFileName =
{
	"data/Load/DragonNosuke/Boss_OneData.txt" 			// �{�X�̏��
};

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CBoss_One::CBoss_One(OBJ_TYPE type) :CCharacter(type)
{
	// �{�X�̏������
	m_BossOneState = BOSS_ONE_STATE_NONE;
	m_ShotCount = 0;
	m_pCollision = nullptr;
}
// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CBoss_One::~CBoss_One()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CBoss_One::Init(void)
{
	// �L�����̏�����
	CCharacter::Init();
	// �I�t�Z�b�g�̎擾
	LoadOffset(CCharacter::CHARACTER_TYPE_BOSS_ONE);
	// �L�����N�^�[�^�C�v�̐ݒ�
	SetCharacterType(CCharacter::CHARACTER_TYPE_BOSS_ONE);
	//�d�͖���
	SetGravity(false);
	// �p�x�̐ݒ�
	SetRotDest(D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	// �̗͂̏����l
	CCharacter::SetLife(m_nLife);
	// ���[�V���������Ȃ��ݒ�
	SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	// ��C���X����
	GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_INCENDIARY))->GetRot().x += 0.6f;
	//GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x -= 1.57f;

	// ����p�̓����蔻��̐���
	m_pCollision = CCollision::Create();

	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		// �e�̐���
		m_pGun[nCnt] = CGun::Create();
		//�}�g���b�N�X�ݒ�
		m_pGun[nCnt]->SetHandMtx(GetCharacterModelPartsList(
			static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetMatrix());
		// �e�̒e�̎��
		m_pGun[nCnt]->GetTag() = TAG_ENEMY;
		// �e�̒e�̎��
		m_pGun[nCnt]->SetGunType(static_cast<CGun::GUN_TYPE>(CGun::GUNTYPE_BALKAN + nCnt));
		// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
		m_pGun[nCnt]->SetShotOffsetPos(m_GunShotOfsetPos[nCnt]);
		// �e����������ݒ�
		m_pGun[nCnt]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetRot().x)));
	}
	// �K���̃I�t�Z�b�g���W�̍X�V
	SetGunOffsetPos(D3DXVECTOR3(GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition()));
	// �K���̍��W�̍X�V
	SetGunPos();

	m_pCollision->SetPos(&m_Gun_Pos);
	m_pCollision->SetSize2D(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	// �����蔻��ݒ�
	CCharacter::GetCollision()->SetPos(&GetPosition());
	CCharacter::GetCollision()->SetSize2D(m_CollisionSize[0]);
	CCharacter::GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
// =====================================================================================================================================================================
//�I��
// =====================================================================================================================================================================
void CBoss_One::Uninit(void)
{
	for(int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		// �e�̃|�C���^
		if (m_pGun[nCnt])
		{
			delete m_pGun[nCnt];
			m_pGun[nCnt] = nullptr;
		}
	}

	// �����蔻��̍폜
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	CCharacter::Uninit();
}
// =====================================================================================================================================================================
//�X�V
// =====================================================================================================================================================================
void CBoss_One::Update(void)
{
	// �K���̍X�V
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_pGun[nCnt]->Update();
	}
	// �K���̃I�t�Z�b�g���W�̍X�V
	SetGunOffsetPos(D3DXVECTOR3(GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition()));
	// �K���̈ړ�
	//MoveGun(GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	// �K���̍��W�̍X�V
	SetGunPos();
	// �K���̓����蔻��̍��W�̍X�V
	m_pCollision->SetPos(&m_Gun_Pos);

	m_ShotCount++;
	if (m_ShotCount % 30 == 0)
	{
		m_pGun[WEAPONTYPE_FLAMETHROWER]->Shot();
	}
	if (m_ShotCount % 60 == 0)
	{
		// �e����������ݒ�
		m_pGun[WEAPONTYPE_BALKAN]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x));

		m_pGun[WEAPONTYPE_BALKAN]->Shot();
	}
	if (m_ShotCount % 120 == 0)
	{
		m_pGun[WEAPONTYPE_INCENDIARY]->Shot();
	}

	// �����蔻��
	if (CCharacter::GetCollision() != nullptr)
	{
		// ���W�̍X�V pos
		CCharacter::GetCollision()->SetPos(&GetPosition());
	}

	// �L�����N�^�[�̍X�V
	CCharacter::Update();
}
// =====================================================================================================================================================================
//�`��
// =====================================================================================================================================================================
void CBoss_One::Draw(void)
{
	CCharacter::Draw();

	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_pGun[nCnt]->Draw();
	}
}
// =====================================================================================================================================================================
//�f�o�b�O
// =====================================================================================================================================================================
void CBoss_One::DebugInfo(void)
{
	//CDebugProc::Print("");
	CCharacter::DebugInfo();
}
// =====================================================================================================================================================================
//���f���̃N���G�C�g
// =====================================================================================================================================================================
CBoss_One *CBoss_One::Create()
{
	// ���������m��
	CBoss_One*pBoss_One = new CBoss_One(OBJTYPE_BOSSONE);
	// ������
	pBoss_One->Init();
	// �l��Ԃ�
	return pBoss_One;
}

// =====================================================================================================================================================================
//
// �{�X�̏��̓ǂݍ���
//
// =====================================================================================================================================================================
void CBoss_One::Boss_One_DataLoad()
{
	FILE *pFile;					// �t�@�C���|�C���g
	char cReadText[128];			// �����Ƃ��ēǂݎ��
	char cHeadText[128];			// ��r�p
	char cDie[128];					// �s�v�ȕ���

									// �t�@�C�����J��
	pFile = fopen(m_BossOneFileName, "r");

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

															// ITEMSET��������
				if (strcmp(cHeadText, "BOSSONESET") == 0)
				{
					// END_ITEMSET������܂Ń��[�v
					while (strcmp(cHeadText, "END_BOSSONESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // �ꕶ�ǂݍ���
						sscanf(cReadText, "%s", &cHeadText);		// ��r�p�e�L�X�g�ɕ�������

																	// DELETE��������
						if (strcmp(cHeadText, "LIFE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BossOneData.nLife);	// ��r�p�e�L�X�g��DELETE����
						}
						// SPEED��������
						else if (strcmp(cHeadText, "COOLTIME") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BossOneData.nCoolTime);	// ��r�p�e�L�X�g��SPEED����
						}
						// COLLISIONSIZE��������
						else if (strcmp(cHeadText, "COLLISIONSIZE_0") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.CollisionSize[POSTURETYPE_STAND].x,
								&m_BossOneData.CollisionSize[POSTURETYPE_STAND].y,
								&m_BossOneData.CollisionSize[POSTURETYPE_STAND].z);										// ��r�p�e�L�X�g��COLLISIONSIZE����
						}
						// COLLISIONSIZE��������
						else if (strcmp(cHeadText, "COLLISIONSIZE_1") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.CollisionSize[POSTURETYPE_SQUAT].x,
								&m_BossOneData.CollisionSize[POSTURETYPE_SQUAT].y,
								&m_BossOneData.CollisionSize[POSTURETYPE_SQUAT].z);										// ��r�p�e�L�X�g��COLLISIONSIZE����
						}

						// GUNOFSET_0��������
						else if (strcmp(cHeadText, "GUNOFSET_0") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_BALKAN].x,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_BALKAN].y,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_BALKAN].z);										// ��r�p�e�L�X�g��COLLISIONSIZE����
						}
						// GUNOFSET_1��������
						else if (strcmp(cHeadText, "GUNOFSET_1") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_FLAMETHROWER].x,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_FLAMETHROWER].y,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_FLAMETHROWER].z);										// ��r�p�e�L�X�g��COLLISIONSIZE����
						}
						// GUNOFSET_2��������
						else if (strcmp(cHeadText, "GUNOFSET_2") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_INCENDIARY].x,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_INCENDIARY].y,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_INCENDIARY].z);										// ��r�p�e�L�X�g��COLLISIONSIZE����
						}
						else if (strcmp(cHeadText, "END_BOSSONESET") == 0)
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
		MessageBox(NULL, "�{�X1�̃f�[�^�ǂݍ��ݎ��s", "�x��", MB_ICONWARNING);
	}

	// �ǂݍ��񂾏��̑��
	SetBoss_OneData();
}

// =====================================================================================================================================================================
//�{�X�̓ǂݍ��񂾏��̐ݒ�
// =====================================================================================================================================================================
void CBoss_One::SetBoss_OneData()
{
	// �̗͂̐ݒ�
	m_nLife = m_BossOneData.nLife;
	// �����蔻��̐ݒ�
	for (int nCnt = 0; nCnt < POSTURETYPE_MAX; nCnt++)
	{
		m_CollisionSize[nCnt] = m_BossOneData.CollisionSize[nCnt];
	}

	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		// �K���̔��ˌ��I�t�Z�b�g�̐ݒ�
		m_GunShotOfsetPos[nCnt] = m_BossOneData.GunShotOfsetPos[nCnt];
	}
}

// =====================================================================================================================================================================
// �{�X�̃f�t�H���g���[�V����
// =====================================================================================================================================================================
bool CBoss_One::Motion(void)
{
	return false;
}

bool CBoss_One::DefaultMotion(void){return false;}
void CBoss_One::BossOneState(){}

// =====================================================================================================================================================================
//�_���[�W���󂯂����̃��A�N�V����
// =====================================================================================================================================================================
void CBoss_One::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);

	//CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
}
// =====================================================================================================================================================================
//���񂾎��̃��A�N�V����
// =====================================================================================================================================================================
void CBoss_One::DeathReaction()
{
	//���S�t���O�����Ă�
	this->SetDieFlag(true);

	CCharacter::DeathReaction();
}

// =====================================================================================================================================================================
//�X�e�[�g���ύX�����u�Ԃ̏���
// =====================================================================================================================================================================
void CBoss_One::StateChangeReaction()
{
	CCharacter::StateChangeReaction();

	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_NORMAL:
		break;

	case CHARACTER_STATE_DAMAGE:

		break;
	case CHARACTER_STATE_DAMAGE_RED:

		break;
	case CHARACTER_STATE_INVINCIBLE:

		break;
	case CHARACTER_STATE_DEATH:
		SetStateCount(60);
		break;
	}
}

//=====================================================================================================================================================================
// �G�̍s��
//=====================================================================================================================================================================
void CBoss_One::Behavior()
{

}

// =====================================================================================================================================================================
// �K���̃I�t�Z�b�g���W�̍X�V
// =====================================================================================================================================================================
void CBoss_One::SetGunOffsetPos(D3DXVECTOR3 pos)
{
	m_Gun_OffsetPos = D3DXVECTOR3(
		GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition().x,
		GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition().y,
		GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition().z);
}

// =====================================================================================================================================================================
// �K���̍��W�̍X�V
// =====================================================================================================================================================================
void CBoss_One::SetGunPos()
{
	m_Gun_Pos = m_Gun_OffsetPos + GetPosition();
}

// =====================================================================================================================================================================
// �K���̈ړ��̍X�V
// =====================================================================================================================================================================
void CBoss_One::MoveGun(D3DXVECTOR3	&PartsPos , D3DXVECTOR3 move)
{
	PartsPos.x += move.x,
	PartsPos.y += move.y,
	PartsPos.z += move.z;
}
