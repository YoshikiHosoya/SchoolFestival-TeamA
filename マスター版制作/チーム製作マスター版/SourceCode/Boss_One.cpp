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
#include "player.h"
#include <random>

//====================================================================
//�}�N����`
//====================================================================

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
BOSS_ONE_DATA		CBoss_One::m_BossOneData						 = {};			// �f�[�^
int					CBoss_One::m_nLife								 = 0;			// �̗�
D3DXVECTOR3			CBoss_One::m_CollisionSize[POSTURETYPE_MAX]		 = {};			// �����蔻��̑傫��
D3DXVECTOR3			CBoss_One::m_GunShotOfsetPos[WEAPONTYPE_MAX]	 = {};			// �K���̃I�t�Z�b�g

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
	m_BossOneState			 = BOSS_ONE_STATE_STAY;
	m_AttckType				 = ATTACKTYPE_NONE;
	m_ShotCount				 = 0;
	m_pCollision			 = nullptr;
	m_nCoolTime				 = 120;
	m_nShotIntervalTime		 = 0;
	m_nTrrigerCount			 = 0;
	m_bFlame				 = false;
	m_bBalkanRotFlag		 = false;
	m_fBalkanRot			 = 0.0f;
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
	// �{�X�̊p�x�̐ݒ�
	SetRotDest(D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	// �̗͂̏����l
	CCharacter::SetLife(m_nLife);
	// ���[�V���������Ȃ��ݒ�
	SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	// �e���X����
	GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_INCENDIARY))->GetRot().x += 0.6f;
	//CalcRotationBalkan(-1.57f, GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x);
	GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x = 0.0f;
	GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetRot().x -= 1.57f;
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
	// �K���̓����蔻��̐ݒ�
	m_pCollision->SetPos(&m_Gun_Pos[WEAPONTYPE_FLAMETHROWER]);
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
	m_pCollision->SetPos(&m_Gun_Pos[WEAPONTYPE_FLAMETHROWER]);

	// �{�X�̏�Ԃ��Ƃ̏���
	BossOneStateManager();

	// �����蔻��
	if (CCharacter::GetCollision() != nullptr)
	{
		// ���W�̍X�V pos
		CCharacter::GetCollision()->SetPos(&GetPosition());
	}

	// �f�o�b�O�p�����̌v�Z
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	float fDist = this->GetPosition().x - pPlayer->GetPosition().x;

	CDebugProc::Print("�{�X�ƃv���C���[�̋��� --- x --- %f\n", fDist);
	CDebugProc::Print("�{�X�̃X�e�[�g %d\n", m_BossOneState);

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
bool CBoss_One::Motion(void){return false;}
bool CBoss_One::DefaultMotion(void){return false;}

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
	// �K���̌X�������ɖ߂�
	//CalcRotationBalkan(-1.57f, GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x);
	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x = 0.0f;
	m_fBalkanRot = GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x;
	// �e���������񐔂����Z�b�g
	SetShotCount(0);
	// �C���^�[�o���̎��Ԃ����Z�b�g
	SetShotIntervalTime(0);
	// �g���K�[�̃J�E���g�̃��Z�b�g
	SetTriggerCount(0);
	// �N�[���^�C���̌v�Z
	Cooltime_Decrease();
	// �U�����@�������_���Ɍ��߂�
	RandomAttack();
}

// =====================================================================================================================================================================
// �K���̃I�t�Z�b�g���W�̍X�V
// =====================================================================================================================================================================
void CBoss_One::SetGunOffsetPos(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_Gun_OffsetPos[nCnt] = D3DXVECTOR3(
			GetCharacterModelPartsList(static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetPosition().x,
			GetCharacterModelPartsList(static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetPosition().y,
			GetCharacterModelPartsList(static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetPosition().z);
	}
}

// =====================================================================================================================================================================
// �K���̃I�t�Z�b�g���W�̎擾
// =====================================================================================================================================================================
D3DXVECTOR3 CBoss_One::GetGunOffsetPos(BOSS_ONE_WEAPONTYPE type)
{
	return m_Gun_OffsetPos[type];
}

// =====================================================================================================================================================================
// �K���̍��W�̍X�V
// =====================================================================================================================================================================
void CBoss_One::SetGunPos()
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_Gun_Pos[nCnt] = m_Gun_OffsetPos[nCnt] + GetPosition();
	}
}

// =====================================================================================================================================================================
// �K���̈ړ��̍X�V
// =====================================================================================================================================================================
void CBoss_One::MoveGun(D3DXVECTOR3	&PartsPos , D3DXVECTOR3 move)
{
	PartsPos += move;
}

// =====================================================================================================================================================================
// �N�[���^�C���̌���
// =====================================================================================================================================================================
void CBoss_One::Cooltime_Decrease()
{
	// �N�[���^�C���̌���
	m_nCoolTime--;

	// �N�[���^�C����0�ȉ��ɂȂ�����
	if (m_nCoolTime <= 0)
	{
		// ��Ԃ��U���ɕς���
		SetBossState(BOSS_ONE_STATE_ATTACK);
	}
}

// =====================================================================================================================================================================
// ��]�̌v�Z
// =====================================================================================================================================================================
void CBoss_One::CalcRotationBalkan(const float fTarget, float fCurrent)
{
	float fcurrent = fCurrent;
	//�ڕW�_�ƌ��݂̍����i��]�j
	float diffRot = fTarget - fcurrent;

	//3.14�̒��ߕ��̏������i��]�j
	CHossoLibrary::CalcRotation(fcurrent);
	CHossoLibrary::CalcRotation(diffRot);

	//���߂����������Ǐ]����v�Z
	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x += diffRot * 0.2f;
}

// =====================================================================================================================================================================
// �x�N�g���̒������v�Z����
// =====================================================================================================================================================================
float CBoss_One::get_vector_length(D3DXVECTOR3 vectol)
{
	return powf((vectol.x * vectol.x) + (vectol.y * vectol.y) + (vectol.z * vectol.z), 0.5);
}

// =====================================================================================================================================================================
// �x�N�g������
// =====================================================================================================================================================================
float CBoss_One::dot_product(D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{
	return vl.x * vr.x + vl.y * vr.y + vl.z * vr.z;
}

// =====================================================================================================================================================================
// �Q�̃x�N�g��AB�̂Ȃ��p�x�Ƃ����߂�
// =====================================================================================================================================================================
float CBoss_One::AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B)
{
	//�@���x�N�g���̒�����0���Ɠ������o�܂���̂Œ��ӂ��Ă��������B

	//�x�N�g��A��B�̒������v�Z����
	float length_A = get_vector_length(A);
	float length_B = get_vector_length(B);

	//���ςƃx�N�g���������g����cos�Ƃ����߂�
	float cos_sita = dot_product(A, B) / (length_A * length_B);

	//cos�Ƃ���Ƃ����߂�
	float sita = acos(cos_sita);

	//���W�A���łȂ�0�`180�̊p�x�łق����ꍇ�̓R�����g�O��
	sita = sita * 180.0f / D3DX_PI;

	// ���̉�]�ʂƋ��߂���]�ʂ������Ȃ�0.0f��Ԃ�
	if (m_fBalkanRot == sita)
	{
		return 0.0f;
	}
	// �Ⴄ�Ȃ狁�߂��p�x�ƍ��̉�]�ʂ��v�Z����]�ʂ����߂�
	else
	{
		return (sita - m_fBalkanRot);
	}

	// �p�x��Ԃ�
	return sita;
}

// =====================================================================================================================================================================
// �ĈΒe
// =====================================================================================================================================================================
void CBoss_One::ShotIncendiary()
{
	// �e��3�񌂂�����
	if (m_nShotCount >= 3)
	{
		// �N�[���^�C���̐ݒ�
		SetCoolTime(120);
		// �{�X�̏�Ԃ�ύX
		m_BossOneState = BOSS_ONE_STATE_STAY;
	}
	else
	{
		// 50�t���[�����Ƃɒe������
		if (m_nShotIntervalTime <= 0)
		{
			// �ĈΒe������
			m_pGun[WEAPONTYPE_INCENDIARY]->Shot();
			// �C���^�[�o���̎��Ԃ�ݒ�
			SetShotIntervalTime(50);
			// �e���������񐔂����Z
			m_nShotCount++;
		}

		// �C���^�[�o���̎��Ԃ�����
		m_nShotIntervalTime--;
	}
}

// =====================================================================================================================================================================
// �o���J��
// =====================================================================================================================================================================
void CBoss_One::ShotBalkan()
{
	// �e��2�񌂂�����
	if (m_nTrrigerCount >= 2)
	{
		// �N�[���^�C���̐ݒ�
		SetCoolTime(120);
		// �K���̌X�������ɖ߂�
		//CalcRotationBalkan(-1.57f, GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x);
		// �{�X�̏�Ԃ�ύX
		m_BossOneState = BOSS_ONE_STATE_STAY;
	}
	else
	{
		if (!m_bBalkanRotFlag)
		{
			// �K���̌������v���C���[�̕��֌�����
			//SetRotBalkan();
			// �v���C���[�̃|�C���^�擾
			CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
			// ���W�������Ȃ̂ō��W����ɏグ��
			D3DXVECTOR3 PlayerPos = D3DXVECTOR3(pPlayer->GetPosition().x, pPlayer->GetPosition().y + 40, pPlayer->GetPosition().z);
			// �v���C���[�̍��W�ƃo���J���̍��W�����ԃx�N�g�������߂�
			D3DXVECTOR3 vectol = PlayerPos - m_Gun_Pos[WEAPONTYPE_BALKAN];
			D3DXVECTOR3 vec = D3DXVECTOR3(vectol.x, m_Gun_Pos[WEAPONTYPE_BALKAN].y, 0.0f);

			// ��]�𔽉f
			GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x += AngleOf2Vector(vectol, vec);
			// ��]�ʂ̍X�V
			SetBalkanRot(GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x);

			// �e�̌����̐ݒ�
			m_pGun[WEAPONTYPE_BALKAN]->SetShotRot(
				D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x * -1.0f));

			m_bBalkanRotFlag = true;
		}

		// 30�t���[�����Ƃ�1�g���K�[����
		if (m_nShotIntervalTime <= 0)
		{
			if (m_bBalkanRotFlag)
			{
				// �o���J��������
				m_pGun[WEAPONTYPE_BALKAN]->Shot();
				// �e���������񐔂����Z
				m_nShotCount++;
				// 1�g���K�[��������
				if (m_nShotCount >= 3)
				{
					// �C���^�[�o���̎��Ԃ�ݒ�
					SetShotIntervalTime(30);
					// �V���b�g�J�E���g�̏�����
					SetShotCount(0);
					// ���g���K�[���������̃J�E���g�����Z
					m_nTrrigerCount++;

					m_bBalkanRotFlag = false;
				}
				// �C���^�[�o���̐ݒ�
				else if (m_nShotCount >= 0)
				{
					// �C���^�[�o���̎��Ԃ�ݒ�
					SetShotIntervalTime(10);
				}
			}
		}

		// �C���^�[�o���̎��Ԃ�����
		m_nShotIntervalTime--;
	}
}

// =====================================================================================================================================================================
// �ĈΒe�̍ŏ��̔���
// =====================================================================================================================================================================
void CBoss_One::ShotWarning()
{
	m_pGun[WEAPONTYPE_FLAMETHROWER]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetRot().x * -1.0f));

	// �e��7�񌂂�����
	if (m_nShotCount >= 7)
	{
		// �����I�������e�𓮂�����悤�ɂ���
		m_pGun[WEAPONTYPE_FLAMETHROWER]->SetMoveZero(false);
		// �N�[���^�C���̐ݒ�
		SetCoolTime(30);
		// �e���������񐔂����Z�b�g
		m_nShotCount = 0;
		// �Ή����˂�����
		m_bFlame = true;
	}
	else
	{
		// 10�t���[�����Ƃɒe������
		if (m_nShotIntervalTime <= 0)
		{
			// �e�̓������~�߂�
			m_pGun[WEAPONTYPE_FLAMETHROWER]->SetMoveZero(true);
			// �Ή����˂�����
			m_pGun[WEAPONTYPE_FLAMETHROWER]->Shot();
			// �C���^�[�o���̎��Ԃ�ݒ�
			SetShotIntervalTime(10);
			// �e���������񐔂����Z
			m_nShotCount++;
		}

		// �C���^�[�o���̎��Ԃ�����
		m_nShotIntervalTime--;
	}
}

// =====================================================================================================================================================================
// �t���C���Ή�����
// =====================================================================================================================================================================
void CBoss_One::ShotFlameRadiation()
{
	m_pGun[WEAPONTYPE_FLAMETHROWER]->SetShotRot(
		D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetRot().x * -1.0f));

	// �e��7�񌂂�����
	if (m_nShotCount >= (16 + 1))
	{
		// �N�[���^�C���̐ݒ�
		SetCoolTime(120);
		// �e���������񐔂����Z�b�g
		m_nShotCount = 0;
		//
		m_bFlame = false;
		// �{�X�̏�Ԃ�ύX
		m_BossOneState = BOSS_ONE_STATE_STAY;
	}
	else
	{
		// 50�t���[�����Ƃɒe������
		if (m_nShotIntervalTime <= 0)
		{
			// �ĈΒe������
			m_pGun[WEAPONTYPE_FLAMETHROWER]->Shot();
			// �C���^�[�o���̎��Ԃ�ݒ�
			SetShotIntervalTime(10);
			// �e���������񐔂����Z
			m_nShotCount++;
		}

		// �C���^�[�o���̎��Ԃ�����
		m_nShotIntervalTime--;
	}
}

// =====================================================================================================================================================================
// �Ή����˂̍U���Ǘ�
// =====================================================================================================================================================================
void CBoss_One::ShotFlameManager()
{
	if (!m_bFlame)
	{
		ShotWarning();
	}
	else
	{
		// �N�[���^�C�����}�C�i�X
		m_nCoolTime--;
		if (m_nCoolTime <= 0)
		{
			ShotFlameRadiation();
		}
	}
}

// =====================================================================================================================================================================
// �U�����@�������_���Ɍ��߂�
// =====================================================================================================================================================================
void CBoss_One::RandomAttack()
{
	// �U�����@�����߂�
	//m_AttckType = (BOSS_ONE_ATTACKTYPE)get_rand_range(ATTACKTYPE_BALKAN, ATTACKTYPE_INCENDIARY);
	m_AttckType = ATTACKTYPE_BALKAN;

	// �U���p�^�[���̕ۑ�
	m_AttckTypeOld = m_AttckType;
}

// =====================================================================================================================================================================
// �o���J���̉�]
// =====================================================================================================================================================================
void CBoss_One::SetRotBalkan()
{
	// �v���C���[�̃|�C���^�擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	// ���W�������Ȃ̂ō��W����ɏグ��
	D3DXVECTOR3 PlayerPos = D3DXVECTOR3(pPlayer->GetPosition().x, pPlayer->GetPosition().y + 50, pPlayer->GetPosition().z);
	// �v���C���[�̍��W�ƃo���J���̍��W�����ԃx�N�g�������߂�
	D3DXVECTOR3 vectol = PlayerPos - m_Gun_Pos[WEAPONTYPE_BALKAN];
	// ���K��
	D3DXVec3Normalize(&vectol, &vectol);
	// ��]�̌v�Z
	CalcRotationBalkan(vectol.x, GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x);
}

// =====================================================================================================================================================================
//
// �����_������
//
// =====================================================================================================================================================================
uint64_t CBoss_One::get_rand_range(uint64_t min_val, uint64_t max_val)
{
	// �����Z���k�E�c�C�X�^�[�@�ɂ��[��������������A
	// �n�[�h�E�F�A�������V�[�h�ɂ��ď�����
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// ����������
	static std::mt19937_64 mt64(seed_gen());

	// [min_val, max_val] �̈�l���z���� (int) �̕��z������
	std::uniform_int_distribution<uint64_t> get_rand_uni_int(min_val, max_val);

	// �����𐶐�
	return get_rand_uni_int(mt64);
}

// =====================================================================================================================================================================
// �{�X�̃X�e�[�g���Ƃ̏���
// =====================================================================================================================================================================
void CBoss_One::BossOneStateManager()
{
	switch (m_BossOneState)
	{
	case CBoss_One::BOSS_ONE_STATE_NONE:
		break;
	case CBoss_One::BOSS_ONE_STATE_STAY:
		// ���̍s����I��
		Behavior();
		break;
	case CBoss_One::BOSS_ONE_STATE_ATTACK:
		// �{�X�̍U���Ǘ�
		BossOneAttackManager();
		break;
	case CBoss_One::BOSS_ONE_STATE_SHIFT_POSTURE:
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
// �{�X�̍U���Ǘ�
// =====================================================================================================================================================================
void CBoss_One::BossOneAttackManager()
{
	// �X�e�[�g�ʍU�����@
	switch (m_AttckType)
	{
	case CBoss_One::ATTACKTYPE_BALKAN:
		// �o���J��������
		ShotBalkan();
		break;
	case CBoss_One::ATTACKTYPE_FLAMERADIATION:
		// �Ή����˂�����
		ShotFlameManager();
		break;
	case CBoss_One::ATTACKTYPE_INCENDIARY:
		// �ĈΒe������
		ShotIncendiary();
		break;
	default:
		break;
	}
}
