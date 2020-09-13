// =====================================================================================================================================================================
//
// �{�X1�̏��� [boss_one.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "Boss_One.h"
#include "manager.h"
#include "basemode.h"
#include "gamemanager.h"
#include "game.h"
#include "model.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "gun.h"
#include "collision.h"
#include <random>
#include <iostream>
#include <algorithm>
#include "ModelSet.h"
#include "particle.h"

// =====================================================================================================================================================================
//�}�N����`
// =====================================================================================================================================================================
#define DIFFERENCE_POSTURE	 (POSTURE_HEIGHT_STAND - POSTURE_HEIGHT_SQUAT)	// �p���̍��W�̍����̋���
#define POSTURE_HEIGHT_STAND (150.0f)										// �ʏ��Ԃ̍��W�̍���
#define POSTURE_HEIGHT_SQUAT (50.0f)										// ���Ⴊ�ݏ�Ԃ̍��W�̍���
#define BALKAN_LENGTH		 (50.0f)										// �o���J���̉��̒���
#define PLAYER_HEADLINE		 (60.0f)										// �v���C���[�̃w�b�h���C���̍���
#define RUNAWAY_BOSSLIFE	 (250)											// �\����ԂɂȂ�̗͂̃��C��
#define COOLTIME_BASE		 (120)											// �N�[���^�C���̊
#define ATTACK_PRIORITY		 (2)											// �U���̗D��x��ۑ����Ă�������

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
BOSS_ONE_DATABASE	CBoss_One::m_BossOneData						 = {};			// �f�[�^

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
CBoss_One::CBoss_One(OBJ_TYPE type) :CEnemy(type)
{
	// �g�p����K���̏�����
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_pGun[nCnt]			 = nullptr;
		m_Gun_OffsetPos[nCnt]	 = ZeroVector3;
		m_Gun_Pos[nCnt]			 = ZeroVector3;
	}

	// �z��̏�����
	m_AIPriorityData.nPriorityData.clear();

	for (int nCnt = 0; nCnt < ATTACKTYPE_MAX; nCnt++)
	{
		m_AIPriorityData.AttackType[nCnt] = 0;
	}

	// �ϐ��̏�����
	m_BossState							 = STATE_NORMAL;
	m_BossOneActionPattern				 = ACTION_PATTERN_STAY;
	m_AttckType							 = ATTACKTYPE_NONE;
	m_AttckTypeOld[SAVE_ATTACKOLD_NUM]	 = {};
	m_PostureType						 = POSTURETYPE_STAND;
	m_AttackAIState						 = AI_STATE_GET_INFORMATION;
	m_pCollision						 = nullptr;
	m_ShotCount							 = 0;
	m_nCoolTime							 = COOLTIME_BASE;
	m_nShotIntervalTime					 = 0;
	m_nTriggerCount						 = 0;
	m_nBalkanAngle						 = 0;
	m_nFirstShotCount					 = 60;
	m_nShotCount						 = 0;
	m_fBalkanRot						 = 0.0f;
	m_fRotTarget						 = -1.57f;
	m_fPartsRotVentilation				 = 0.0f;
	m_AddMove							 = 0.0f;
	m_bFlame							 = false;
	m_bBalkanRotFlag					 = false;
	m_bOpenWeapon						 = false;
	m_bShiftPosture						 = false;
	m_bBalkanGunRotFlag					 = false;
	m_bIntermediateSquat				 = false;
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
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_BOSS_ONE);
	// �L�����N�^�[�^�C�v�̐ݒ�
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_BOSS_ONE);
	//�^�C�v�ݒ�
	CEnemy::SetEnemyType(ENEMY_TYPE::ENEMY_BOSS_DRAGON_NOSUKE);
	//�d�͖���
	SetGravity(false);
	// �{�X�̊p�x�̐ݒ�_������
	SetRotDest(D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	// ���[�V���������Ȃ��ݒ�
	GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);
	// �{�X�̏��̐ݒ�
	SetBossInfo();
	// �K���̐����Ɛݒ�
	CreateGun();
	// �����蔻��̐ݒ�
	SetCollision();
	// ��]�̍���
	m_fBalkanRotDifferencial -= D3DX_PI / 120.0f;

	return S_OK;
}
// =====================================================================================================================================================================
//
// �I��
//
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
//
// �X�V
//
// =====================================================================================================================================================================
void CBoss_One::Update(void)
{
	// �K���̍X�V
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_pGun[nCnt]->Update();
	}
	// �K���̃I�t�Z�b�g���W�̍X�V
	SetGunOffsetPos(D3DXVECTOR3(GetModelSet()->GetCharacterModelList()[21]->GetPosition()));
	// �K���̍��W�̍X�V
	SetGunPos();

	if (CCharacter::GetCharacterState() != CHARACTER_STATE_DEATH)
	{
		// �{�X�̍s���Ǘ�
		Behavior();
	}

	// ��]�̌v�Z
	CalcRotationBalkan(m_fRotTarget, GetModelSet()->GetCharacterModelList()[20]->GetRot().x);
	// ��]�ʂ̍X�V
	SetBalkanRot(GetModelSet()->GetCharacterModelList()[20]->GetRot().x);
	// �e���������p�x
	m_pGun[WEAPONTYPE_BALKAN]->SetShotRot(
		D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[20]->GetRot().x * -1.0f)));
	// �{�X�̃��[�V����
	Motion();
	// �����蔻��̍X�V
	UpdateCollision();

	// �L�����N�^�[�̍X�V
	CCharacter::Update();
}
// =====================================================================================================================================================================
//
// �`��
//
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
//
// �f�o�b�O
//
// =====================================================================================================================================================================
void CBoss_One::DebugInfo(void)
{

}
// =====================================================================================================================================================================
//
// ���f���̃N���G�C�g
//
// =====================================================================================================================================================================
CBoss_One *CBoss_One::Create()
{
	// ���������m��
	CBoss_One*pBoss_One = new CBoss_One(OBJTYPE_BOSSONE);
	// �^�O�̐ݒ�
	pBoss_One->SetTag(TAG::ENEMY);
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
}

// =====================================================================================================================================================================
//
// �{�X�̃f�t�H���g���[�V����
//
// =====================================================================================================================================================================
bool CBoss_One::DefaultMotion(void){return false;}

// =====================================================================================================================================================================
//
// �{�X�̃��[�V����
//
// =====================================================================================================================================================================
void CBoss_One::Motion(void)
{
	if (GetModelSet()->GetCharacterModelList()[14]->GetRot().x <= 0)
	{
		m_fPartsRotVentilation = 0.01f;
	}
	else if (GetModelSet()->GetCharacterModelList()[14]->GetRot().x >= (1.57f / 3.5f))
	{
		m_fPartsRotVentilation = -0.015f;
	}

	// �p�[�c����]������
	GetModelSet()->GetCharacterModelList()[14]->GetRot().x += m_fPartsRotVentilation;
	GetModelSet()->GetCharacterModelList()[15]->GetRot().x += m_fPartsRotVentilation;
}

// =====================================================================================================================================================================
//
// �_���[�W���󂯂����̃��A�N�V����
//
// =====================================================================================================================================================================
void CBoss_One::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);
	//CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
}
// =====================================================================================================================================================================
//
// ���񂾎��̃��A�N�V����
//
// =====================================================================================================================================================================
void CBoss_One::DeathReaction()
{
	//���S�t���O�����Ă�
	this->SetDieFlag(true);
	CCharacter::DeathReaction();

	//�C�x���g�N���A
	CManager::GetGame()->GetGameManager()->EventClear();

	//nullcheck
	if (CManager::GetGame())
	{
		CManager::GetGame()->GetGameManager()->SetGameState(CGameManager::GAMESTATE::RESULT);
	}
}

// =====================================================================================================================================================================
//
// �X�e�[�g���ύX�����u�Ԃ̏���
//
// =====================================================================================================================================================================
void CBoss_One::StateChangeReaction()
{
	CCharacter::StateChangeReaction();

	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_NORMAL:
		break;

	case CHARACTER_STATE_DAMAGE_FLASHING:

		break;
	case CHARACTER_STATE_DAMAGE_RED:

		break;
	case CHARACTER_STATE_INVINCIBLE:

		break;
	case CHARACTER_STATE_DEATH:
		SetStateCount(240);
		break;
	}
}
// =====================================================================================================================================================================
//
// �X�e�[�g
//
// =====================================================================================================================================================================
void CBoss_One::State()
{
	CCharacter::State();

	//�X�e�[�^�X�̏���
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_DEATH:
		//����
		if (GetCharacterStateCnt() % 3 == 0)
		{
			CParticle::CreateFromText(GetPosition() + CHossoLibrary::RandomVector3(250.0f), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION);
		}
		break;
	}
}


// =====================================================================================================================================================================
//
// �ҋ@���̍s��
//
// =====================================================================================================================================================================
void CBoss_One::StayAction()
{
	// --- �ϐ��̏����� ---  //
	m_AttckType			 = ATTACKTYPE_NONE;
	m_bShiftPosture		 = false;
	m_fRotTarget		 = -1.57f;
	m_nFirstShotCount	 = 60;
	m_fBalkanRot		 = GetModelSet()->GetCharacterModelList()[20]->GetRot().x;
	m_nBalkanAngle		 = 0;
	// �e���������񐔂����Z�b�g
	SetShotCount(0);
	// �C���^�[�o���̎��Ԃ����Z�b�g
	SetShotIntervalTime(0);
	// �g���K�[�̃J�E���g�̃��Z�b�g
	SetTriggerCount(0);

	if (m_AttckTypeOld[0] == ATTACKTYPE_BALKAN)
	{
		SetBalkan(false, m_BossState);
	}
	else if (m_AttckTypeOld[0] == ATTACKTYPE_FLAMERADIATION)
	{
		SetFlameThrower(false);
	}

	for (int nCnt = 0; nCnt < ATTACKTYPE_MAX; nCnt++)
	{
		m_AIPriorityData.AttackType[nCnt] = PRIORITY_POINT_NONE;
	}

	//
	m_AttackAIState = AI_STATE_GET_INFORMATION;
	// �z��̏�����
	m_AIPriorityData.nPriorityData.clear();

	// �N�[���^�C���̌v�Z
	Cooltime_Decrease();
}

// =====================================================================================================================================================================
//
// �N�[���^�C���̐ݒ�
//
// =====================================================================================================================================================================
void CBoss_One::SetCoolTime(int time)
{
	if (time == NULL)
	{
		switch (m_BossState)
		{
		case CBoss_One::STATE_NORMAL:
			m_nCoolTime = COOLTIME_BASE;
			break;
		case CBoss_One::STATE_RUNAWAY:
			m_nCoolTime = COOLTIME_BASE;
			break;
		}
	}
	else
	{
		m_nCoolTime = time;
	}
}

// =====================================================================================================================================================================
//
// �K���̃I�t�Z�b�g���W�̍X�V
//
// =====================================================================================================================================================================
void CBoss_One::SetGunOffsetPos(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_Gun_OffsetPos[nCnt] = GetModelSet()->GetCharacterModelList()[20 + nCnt]->GetPosition();
	}
}

// =====================================================================================================================================================================
//
// �K���̃I�t�Z�b�g���W�̎擾
//
// =====================================================================================================================================================================
D3DXVECTOR3 CBoss_One::GetGunOffsetPos(BOSS_ONE_WEAPONTYPE type)
{
	return m_Gun_OffsetPos[type];
}

// =====================================================================================================================================================================
//
// �K���̍��W�̍X�V
//
// =====================================================================================================================================================================
void CBoss_One::SetGunPos()
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_Gun_Pos[nCnt] = m_Gun_OffsetPos[nCnt] + GetPosition();
		if (nCnt == WEAPONTYPE_FLAMETHROWER)
		{
			m_Gun_Pos[nCnt].y -= 50.0f;
		}
	}
}

// =====================================================================================================================================================================
//
// �K���̈ړ��̍X�V
//
// =====================================================================================================================================================================
void CBoss_One::MoveGun(D3DXVECTOR3	&PartsPos , D3DXVECTOR3 move)
{
	PartsPos += move;
}

// =====================================================================================================================================================================
//
// �N�[���^�C���̌���
//
// =====================================================================================================================================================================
void CBoss_One::Cooltime_Decrease()
{
	// �N�[���^�C���̌���
	m_nCoolTime--;

	// �N�[���^�C����0�ȉ��ɂȂ�����
	if (m_nCoolTime <= 0)
	{
		// ��Ԃ��U���ɕς���
		SetBossAction(ACTION_PATTERN_AI_ATTACK);
	}
}

// =====================================================================================================================================================================
//
// ��]�̌v�Z
//
// =====================================================================================================================================================================
void CBoss_One::CalcRotationBalkan(const float fTarget, float fCurrent)
{
	//�ڕW�_�ƌ��݂̍����i��]�j
	float diffRot = fTarget - fCurrent;

	//3.14�̒��ߕ��̏������i��]�j
	CHossoLibrary::CalcRotation(fCurrent);
	CHossoLibrary::CalcRotation(diffRot);

	//���߂����������Ǐ]����v�Z
	GetModelSet()->GetCharacterModelList()[20]->GetRot().x += diffRot * 0.1f;
}

// =====================================================================================================================================================================
//
// �x�N�g���̒������v�Z����
//
// =====================================================================================================================================================================
float CBoss_One::get_vector_length(D3DXVECTOR3 vectol)
{
	return powf((vectol.x * vectol.x) + (vectol.y * vectol.y) + (vectol.z * vectol.z), 0.5);
}

// =====================================================================================================================================================================
//
// �x�N�g������
//
// =====================================================================================================================================================================
float CBoss_One::dot_product(D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{
	return vl.x * vr.x + vl.y * vr.y + vl.z * vr.z;
}

// =====================================================================================================================================================================
//
// �Q�̃x�N�g��AB�̂Ȃ��p�x�Ƃ����߂�
//
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
	//sita = sita * 180.0f / D3DX_PI;
	int nAngle = (int)(sita * 180.0f / D3DX_PI);

	// ���̉�]�ʂƋ��߂���]�ʂ������Ȃ�0.0f��Ԃ�
	if (m_nBalkanAngle == nAngle)
	{
		return 0.0f;
	}
	// �Ⴄ�Ȃ狁�߂��p�x�ƍ��̉�]�ʂ��v�Z����]�ʂ����߂�
	else
	{
		m_nBalkanAngle = nAngle;

		sita = D3DX_PI - sita;
		sita *= -1.0f;

		return (sita - m_fBalkanRot);
	}

	// �p�x��Ԃ�
	return sita;
}

// =====================================================================================================================================================================
//
// �ĈΒe
//
// =====================================================================================================================================================================
void CBoss_One::ShotIncendiary()
{
	// �e��3�񌂂�����
	if (m_nShotCount >= 3)
	{
		// �N�[���^�C���̐ݒ�
		SetCoolTime(NULL);
		// �{�X�̏�Ԃ�ύX
		SetBossAction(ACTION_PATTERN_STAY);
	}
	else
	{
		// 50�t���[�����Ƃɒe������
		if (m_nShotIntervalTime <= 0)
		{
			m_pGun[WEAPONTYPE_INCENDIARY]->SetShotRot(
				D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[22]->GetRot().x * -1.0f)));
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
//
// �o���J��
//
// =====================================================================================================================================================================
void CBoss_One::ShotBalkan()
{
	if (m_bOpenWeapon)
	{
		// 5�g���K�[��������_�\����ԗp
		if (m_nTriggerCount >= 5)
		{
			// �N�[���^�C���̐ݒ�
			SetCoolTime(NULL);
			// �{�X�̏�Ԃ�ύX
			SetBossAction(ACTION_PATTERN_STAY);
		}
		else
		{
			switch (m_BossState)
			{
			case CBoss_One::STATE_NORMAL:

				// �K���̌���������������]������
				SetRotBalkan(m_BossState);
				// ���e�����܂ł̎���
				m_nFirstShotCount--;
				if (m_nFirstShotCount <= 0)
				{
					if (m_nShotIntervalTime <= 0)
					{
						// �o���J��������
						m_pGun[WEAPONTYPE_BALKAN]->Shot();
						// �e���������񐔂����Z
						m_nShotCount++;
						// �C���^�[�o���̎��Ԃ�ݒ�
						SetShotIntervalTime(10);
						// 10����������
						if (m_nShotCount >= 15)
						{
							// �V���b�g�J�E���g�̏�����
							SetShotCount(0);
							// �N�[���^�C���̐ݒ�
							SetCoolTime(NULL);
							// �{�X�̏�Ԃ�ύX
							SetBossAction(ACTION_PATTERN_STAY);
						}
					}
					// �C���^�[�o���̐ݒ�
					else if (m_nShotIntervalTime >= 0)
					{
						// �C���^�[�o���̎��Ԃ�����
						m_nShotIntervalTime--;
					}
				}
				else
				{
					m_fRotTarget = -D3DX_PI / 4;
				}

				break;

			case CBoss_One::STATE_RUNAWAY:
				if (!m_bBalkanRotFlag)
				{
					// �K���̌������v���C���[�̕��֌�����
					SetRotBalkan(m_BossState);
					//
					m_bBalkanRotFlag = true;
				}


				if (m_bBalkanRotFlag)
				{
					m_nFirstShotCount--;
					if (m_nFirstShotCount <= 0)
					{
						// 30�t���[�����Ƃ�1�g���K�[����
						if (m_nShotIntervalTime <= 0)
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
								m_nTriggerCount++;
								m_bBalkanRotFlag = false;
							}
							// �C���^�[�o���̐ݒ�
							else if (m_nShotCount >= 0)
							{
								// �C���^�[�o���̎��Ԃ�ݒ�
								SetShotIntervalTime(10);
							}
						}

						if (m_bBalkanRotFlag)
						{
							// �C���^�[�o���̎��Ԃ�����
							m_nShotIntervalTime--;
						}
					}
				}
				break;
			}
		}
	}
}

// =====================================================================================================================================================================
//
// �Ή����˂̍ŏ��̔���
//
// =====================================================================================================================================================================
void CBoss_One::ShotWarning()
{
	m_pGun[WEAPONTYPE_FLAMETHROWER]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[21]->GetRot().x * -1.0f)));

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
//
// �Ή�����
//
// =====================================================================================================================================================================
void CBoss_One::ShotFlameRadiation()
{
	m_pGun[WEAPONTYPE_FLAMETHROWER]->SetShotRot(
		D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[21]->GetRot().x * -1.0f)));

	// �e��16�񌂂�����
	if (m_nShotCount >= (16 + 1))
	{
		// �N�[���^�C���̐ݒ�
		SetCoolTime(NULL);
		// �e���������񐔂����Z�b�g
		m_nShotCount = 0;
		//
		m_bFlame = false;

		// �{�X�̏�Ԃ�ύX
		SetBossAction(ACTION_PATTERN_STAY);

		m_AttckType = ATTACKTYPE_NONE;
	}
	else
	{
		// 50�t���[�����Ƃɒe������
		if (m_nShotIntervalTime <= 0)
		{
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
//
// �p���ύX
//
// =====================================================================================================================================================================
void CBoss_One::ShiftPosture()
{
	if (!m_bShiftPosture)
	{
		m_AddMove += 0.1f;
	}

	if (m_PostureType == POSTURETYPE_STAND)
	{

		// �G��
		if (GetModelSet()->GetCharacterModelList()[4]->GetRot().z >= -1.25f &&
			GetModelSet()->GetCharacterModelList()[5]->GetRot().z >= -1.25f)
		{
			GetModelSet()->GetCharacterModelList()[4]->GetRot().z -= m_AddMove;
			GetModelSet()->GetCharacterModelList()[5]->GetRot().z -= m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[4]->GetRot().z <= -1.25f &&
				GetModelSet()->GetCharacterModelList()[5]->GetRot().z <= -1.25f)
			{
				GetModelSet()->GetCharacterModelList()[4]->GetRot().z = -1.25f;
				GetModelSet()->GetCharacterModelList()[5]->GetRot().z = -1.25f;
			}
		}

		if (GetModelSet()->GetCharacterModelList()[2]->GetRot().z <= 1.25f &&
			GetModelSet()->GetCharacterModelList()[3]->GetRot().z <= 1.25f)
		{
			GetModelSet()->GetCharacterModelList()[2]->GetRot().z += m_AddMove;
			GetModelSet()->GetCharacterModelList()[3]->GetRot().z += m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[2]->GetRot().z >= 1.25f &&
				GetModelSet()->GetCharacterModelList()[3]->GetRot().z >= 1.25f)
			{
				GetModelSet()->GetCharacterModelList()[2]->GetRot().z = 1.25f;
				GetModelSet()->GetCharacterModelList()[3]->GetRot().z = 1.25f;
			}
		}


		// �G��
		if (GetModelSet()->GetCharacterModelList()[8]->GetRot().z >= -0.9f &&
			GetModelSet()->GetCharacterModelList()[9] ->GetRot().z >= -0.9f)
		{
			GetModelSet()->GetCharacterModelList()[8]->GetRot().z -= m_AddMove;
			GetModelSet()->GetCharacterModelList()[9] ->GetRot().z -= m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[8]->GetRot().z <= -0.9f &&
				GetModelSet()->GetCharacterModelList()[9] ->GetRot().z <= -0.9f)
			{
				GetModelSet()->GetCharacterModelList()[8]->GetRot().z = -0.9f;
				GetModelSet()->GetCharacterModelList()[9] ->GetRot().z = -0.9f;
			}
		}

		if (GetModelSet()->GetCharacterModelList()[6]->GetRot().z <= 0.9f &&
			GetModelSet()->GetCharacterModelList()[7] ->GetRot().z <= 0.9f)
		{
			GetModelSet()->GetCharacterModelList()[6]->GetRot().z += m_AddMove;
			GetModelSet()->GetCharacterModelList()[7] ->GetRot().z += m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[6]->GetRot().z >= 0.9f &&
				GetModelSet()->GetCharacterModelList()[7] ->GetRot().z >= 0.9f)
			{
				GetModelSet()->GetCharacterModelList()[6]->GetRot().z = 0.9f;
				GetModelSet()->GetCharacterModelList()[7] ->GetRot().z = 0.9f;
			}
		}

		m_bIntermediateSquat = true;
		// �{�f�B�[�̍���
		if (GetPosition().y >= POSTURE_HEIGHT_SQUAT)
		{
			GetPosition().y -= m_AddMove * 2;

			if (GetPosition().y <= POSTURE_HEIGHT_SQUAT)
			{
				GetPosition().y = POSTURE_HEIGHT_SQUAT;
				// �N�[���^�C���̐ݒ�
				SetCoolTime(NULL);
				//
				m_bShiftPosture = true;
				m_bIntermediateSquat = false;
				m_PostureType = POSTURETYPE_SQUAT;
				m_AddMove = 0.0f;
				// �{�X�̏�Ԃ�ύX
				SetBossAction(ACTION_PATTERN_STAY);
			}
		}
	}
	else
	{
		if (GetModelSet()->GetCharacterModelList()[2]->GetRot().z >= 0.0f &&
			GetModelSet()->GetCharacterModelList()[3]->GetRot().z >= 0.0f)
		{
			GetModelSet()->GetCharacterModelList()[2]->GetRot().z -= m_AddMove;
			GetModelSet()->GetCharacterModelList()[3]->GetRot().z -= m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[2]->GetRot().z <= 0.0f &&
				GetModelSet()->GetCharacterModelList()[3]->GetRot().z <= 0.0f)
			{
				GetModelSet()->GetCharacterModelList()[2]->GetRot().z = 0.0f;
				GetModelSet()->GetCharacterModelList()[3]->GetRot().z = 0.0f;
			}
		}

		if (GetModelSet()->GetCharacterModelList()[4]->GetRot().z <= 0.0f &&
			GetModelSet()->GetCharacterModelList()[5]->GetRot().z <= 0.0f)
		{
			GetModelSet()->GetCharacterModelList()[4]->GetRot().z += m_AddMove;
			GetModelSet()->GetCharacterModelList()[5]->GetRot().z += m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[4]->GetRot().z >= 0.0f &&
				GetModelSet()->GetCharacterModelList()[5]->GetRot().z >= 0.0f)
			{
				GetModelSet()->GetCharacterModelList()[4]->GetRot().z = 0.0f;
				GetModelSet()->GetCharacterModelList()[5]->GetRot().z = 0.0f;
			}
		}


		if (GetModelSet()->GetCharacterModelList()[7]->GetRot().z >= 0.0f &&
			GetModelSet()->GetCharacterModelList()[7]->GetRot().z >= 0.0f)
		{
			GetModelSet()->GetCharacterModelList()[6]->GetRot().z -= m_AddMove;
			GetModelSet()->GetCharacterModelList()[7]->GetRot().z -= m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[6]->GetRot().z <= 0.0f &&
				GetModelSet()->GetCharacterModelList()[7]->GetRot().z <= 0.0f)
			{
				GetModelSet()->GetCharacterModelList()[6]->GetRot().z = 0.0f;
				GetModelSet()->GetCharacterModelList()[7]->GetRot().z = 0.0f;
			}
		}

		if (GetModelSet()->GetCharacterModelList()[8]->GetRot().z <= 0.0f &&
			GetModelSet()->GetCharacterModelList()[9]->GetRot().z <= 0.0f)
		{
			GetModelSet()->GetCharacterModelList()[8]->GetRot().z += m_AddMove;
			GetModelSet()->GetCharacterModelList()[9]->GetRot().z += m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[8]->GetRot().z >= 0.0f &&
				GetModelSet()->GetCharacterModelList()[9]->GetRot().z >= 0.0f)
			{
				GetModelSet()->GetCharacterModelList()[8]->GetRot().z = 0.0f;
				GetModelSet()->GetCharacterModelList()[9]->GetRot().z = 0.0f;
			}
		}

		if (GetPosition().y <= POSTURE_HEIGHT_STAND)
		{
			m_AddMove += 0.1f;
			GetPosition().y += m_AddMove * 2;

			if (GetPosition().y >= POSTURE_HEIGHT_STAND)
			{
				GetPosition().y = POSTURE_HEIGHT_STAND;
				// �N�[���^�C���̐ݒ�
				SetCoolTime(NULL);
				//
				m_bShiftPosture = true;
				m_PostureType = POSTURETYPE_STAND;
				m_AddMove = 0.0f;
				// �{�X�̏�Ԃ�ύX
				SetBossAction(ACTION_PATTERN_STAY);
			}
		}
	}
}

// =====================================================================================================================================================================
//
// �Ή����ˊ�̈ړ�
//
// =====================================================================================================================================================================
void CBoss_One::SetFlameThrower(bool bOpen)
{
	if (bOpen)
	{
		if ((GetPosition().y + GetModelSet()->GetCharacterModelList()[21]->GetPosition().y) >= -30.0)
		{
			GetModelSet()->GetCharacterModelList()[21]->GetPosition().y -= 2.0f;

			if (GetModelSet()->GetCharacterModelList()[21]->GetPosition().y <= -30.0)
			{
				GetModelSet()->GetCharacterModelList()[21]->GetPosition().y = -30.0f;
				m_bOpenWeapon = true;
			}
		}
	}

	else if (!bOpen)
	{
		if ((GetPosition().y + GetModelSet()->GetCharacterModelList()[21]->GetPosition().y) >= 65.0f)
		{
			GetModelSet()->GetCharacterModelList()[21]->GetPosition().y += 2.0f;

			if (GetModelSet()->GetCharacterModelList()[21]->GetPosition().y >= 65.0f)
			{
				GetModelSet()->GetCharacterModelList()[21]->GetPosition().y = 65.0f;
				m_bOpenWeapon = false;
			}
		}
	}
}


// =====================================================================================================================================================================
//
// �o���J���̈ړ�
//
// =====================================================================================================================================================================
void CBoss_One::SetBalkan(bool bOpen, BOSS_ONE_STATE state)
{
	if (bOpen)
	{
		if (state == STATE_NORMAL)
		{
			//m_fRotTarget = -D3DX_PI / 4;
		}
		if ((GetPosition().z - GetModelSet()->GetCharacterModelList()[20]->GetPosition().z) >= -BALKAN_LENGTH)
		{
			GetModelSet()->GetCharacterModelList()[20]->GetPosition().z -= 4.0f;

			if (GetModelSet()->GetCharacterModelList()[20]->GetPosition().z <= -BALKAN_LENGTH)
			{
				GetModelSet()->GetCharacterModelList()[20]->GetPosition().z = -BALKAN_LENGTH;
				m_bOpenWeapon = true;
			}
		}
	}

	else if (!bOpen)
	{
		m_fRotTarget = -1.57f;
		if ((GetPosition().z - GetModelSet()->GetCharacterModelList()[20]->GetPosition().z) <= BALKAN_LENGTH)
		{
			GetModelSet()->GetCharacterModelList()[20]->GetPosition().z += 4.0f;

			if (GetModelSet()->GetCharacterModelList()[20]->GetPosition().z >= BALKAN_LENGTH)
			{
				GetModelSet()->GetCharacterModelList()[20]->GetPosition().z = BALKAN_LENGTH;
				m_bOpenWeapon = false;
			}
		}
	}
}


// =====================================================================================================================================================================
//
// �Ή����˂̍U���Ǘ�
//
// =====================================================================================================================================================================
void CBoss_One::ShotFlameManager()
{
	if (m_bOpenWeapon)
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
}

// =====================================================================================================================================================================
//
// �U�����@�������_���Ɍ��߂�
//
// =====================================================================================================================================================================
void CBoss_One::RandomAttack()
{
	// �U�����@�����߂� �f�o�b�O�p
	//m_AttckType = (BOSS_ONE_ATTACKTYPE)get_rand_range(ATTACKTYPE_BALKAN, ATTACKTYPE_SHIFTPOSTURE);

	// ���Ⴊ�ݏ�ԂōU�����Ή����˂ɂȂ����ꍇ�͂�蒼��
	do
	{
		// �U�����@�̐ݒ�
		SetAttackType((BOSS_ONE_ATTACKTYPE)get_rand_range(ATTACKTYPE_BALKAN, ATTACKTYPE_SHIFTPOSTURE));

	} while (m_PostureType == POSTURETYPE_SQUAT && m_AttckType == ATTACKTYPE_FLAMERADIATION ||
			 m_AttckTypeOld[0] == ATTACKTYPE_SHIFTPOSTURE && m_AttckType == ATTACKTYPE_SHIFTPOSTURE);
}

// =====================================================================================================================================================================
//
// �o���J���̉�]
//
// =====================================================================================================================================================================
void CBoss_One::SetRotBalkan(BOSS_ONE_STATE state)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	if(pPlayer)
	{
		switch (m_BossState)
		{
		case CBoss_One::STATE_NORMAL:
			if (m_fRotTarget >= -D3DX_PI / 4)
			{
				m_fRotTarget = -D3DX_PI / 4;
				m_fBalkanRotDifferencial *= -1.0f;
			}
			else if (m_fRotTarget <= -2.355f)
			{
				// ��]�𔽉f
				m_fRotTarget = -2.355f;
				m_fBalkanRotDifferencial *= -1.0f;
			}

			m_fRotTarget -= m_fBalkanRotDifferencial;

			break;
		case CBoss_One::STATE_RUNAWAY:

			// �v���C���[�̃|�C���^�擾
			CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
			D3DXVECTOR3 PlayerPos;

			// �v���C���[���{�X�̎˒��O��������
			if (pPlayer->GetPosition().x >= 150.0f)
			{
				// �v���C���[�̍��W���{�X�̖ڂ̑O�ɂ��邱�Ƃɂ���
				PlayerPos = D3DXVECTOR3(150.0f, pPlayer->GetPosition().y, pPlayer->GetPosition().z);
			}
			else
			{
				// �v���C���[�̍��W
				PlayerPos = pPlayer->GetPosition();
			}

			// �v���C���[�̍��W�ƃo���J���̍��W�����ԃx�N�g�������߂�
			D3DXVECTOR3 HorizontalAxis = m_Gun_Pos[WEAPONTYPE_BALKAN] - PlayerPos;
			D3DXVECTOR3 VerticalAxis = ZeroVector3;

			// �ʏ펞
			if (m_PostureType == POSTURETYPE_STAND)
			{
				VerticalAxis = D3DXVECTOR3(
					m_Gun_Pos[WEAPONTYPE_BALKAN].x - BALKAN_LENGTH, (m_Gun_Pos[WEAPONTYPE_BALKAN].y - HorizontalAxis.x - BALKAN_LENGTH - PLAYER_HEADLINE), 0.0f);
			}
			// ���Ⴊ�ݎ�
			else
			{
				VerticalAxis = D3DXVECTOR3(
					m_Gun_Pos[WEAPONTYPE_BALKAN].x - BALKAN_LENGTH - DIFFERENCE_POSTURE, (m_Gun_Pos[WEAPONTYPE_BALKAN].y - HorizontalAxis.x - BALKAN_LENGTH * 2 - PLAYER_HEADLINE * 2 - DIFFERENCE_POSTURE * 2), 0.0f);
			}

			// ��]�𔽉f
			m_fRotTarget += AngleOf2Vector(VerticalAxis, HorizontalAxis);

			break;
		}
	}

	//
	m_bBalkanGunRotFlag = true;
}


// =====================================================================================================================================================================
//
// �����蔻��̐ݒ�
//
// =====================================================================================================================================================================
void CBoss_One::SetCollision()
{
	// �K���̓����蔻��̐ݒ�
	// ����p�̓����蔻��̐���
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&m_Gun_Pos[WEAPONTYPE_FLAMETHROWER]);
	m_pCollision->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	// �����蔻��ݒ�
	CCharacter::GetCollision()->SetPos(&GetPosition());
	CCharacter::GetCollision()->SetPosOld(&GetPositionOld());
	CCharacter::GetCollision()->SetSize(m_BossOneData.CollisionSize[1]);
	CCharacter::GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
}

// =====================================================================================================================================================================
//
// ���肵���U�����@��ݒ肷��
//
// =====================================================================================================================================================================
void CBoss_One::SetAttackType(BOSS_ONE_ATTACKTYPE type)
{
	m_AttckType = type;

	// Old��0�Ԗڂ�1�Ԗڂɑ��
	m_AttckTypeOld[ATTACK_PRIORITY - 1] = m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY];
	m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] = m_AttckType;
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
//
// �����蔻��̍X�V
//
// =====================================================================================================================================================================
void CBoss_One::UpdateCollision()
{
	if (CCharacter::GetCollision() != nullptr)
	{
		// �K���̓����蔻��̍��W�̍X�V
		m_pCollision->SetPos(&m_Gun_Pos[WEAPONTYPE_FLAMETHROWER]);
		CCharacter::GetCollision()->BossOne_PlayerCollision();
		CCharacter::GetCollision()->SetPos(&GetPosition());
	}
}

// =====================================================================================================================================================================
//
// �{�X�̃X�e�[�g�Ǘ�
//
// =====================================================================================================================================================================
void CBoss_One::BossOneStateManager()
{
	switch (m_BossState)
	{
	case CBoss_One::STATE_NORMAL:
		if (this->GetLife() <= RUNAWAY_BOSSLIFE)
		{
			m_BossState = STATE_RUNAWAY;
		}
		break;
	case CBoss_One::STATE_RUNAWAY:

		break;
	}
}

// =====================================================================================================================================================================
//
// �{�X�̍s���Ǘ�
//
// =====================================================================================================================================================================
void CBoss_One::Behavior()
{
	switch (m_BossOneActionPattern)
	{
	case CBoss_One::ACTION_PATTERN_NONE:
		break;
	case CBoss_One::ACTION_PATTERN_STAY:
		// ���̍s����I��
		StayAction();
		break;

	case CBoss_One::ACTION_PATTERN_AI_ATTACK:
		// ���̍U�����@��I��
		Attack_AI();
		break;

	case CBoss_One::ACTION_PATTERN_ATTACK:
		// �{�X�̍U���Ǘ�
		BossOneAttackManager();
		break;
	case CBoss_One::ACTION_PATTERN_SHIFT_POSTURE:
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// �{�X�̍U���Ǘ�
//
// =====================================================================================================================================================================
void CBoss_One::BossOneAttackManager()
{
	// �X�e�[�g�ʍU�����@
	switch (m_AttckType)
	{
	case CBoss_One::ATTACKTYPE_BALKAN:
		SetBalkan(true, m_BossState);
		// �o���J��������
		ShotBalkan();
		break;
	case CBoss_One::ATTACKTYPE_FLAMERADIATION:
		// �Ή����ˊ���o��
		SetFlameThrower(true);
		// �Ή����˂�����
		ShotFlameManager();
		break;
	case CBoss_One::ATTACKTYPE_INCENDIARY:
		// �ĈΒe������
		ShotIncendiary();
		break;
	case CBoss_One::ATTACKTYPE_SHIFTPOSTURE:
		// �p���ύX
		ShiftPosture();
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// �{�X�̍U���Ǘ�AI
//
// =====================================================================================================================================================================
void CBoss_One::Attack_AI()
{
	switch (m_AttackAIState)
	{
		// �K�v�ȏ��̎擾
	case CBoss_One::AI_STATE_GET_INFORMATION:

		// �U���̗D��x���v�Z
		Attack_Priority();

		// ���ꂼ��̍s���̗D��x�̃A�h���X���擾
		for (int nCnt = 0; nCnt < ATTACKTYPE_MAX; nCnt++)
		{
			// �����ɍU���D��x�̒l��ǉ�
			m_AIPriorityData.nPriorityData.emplace_back(&m_AIPriorityData.AttackType[nCnt]);
		}

		m_AttackAIState = AI_STATE_AI;
		break;

		// �������ɍU����I������
	case CBoss_One::AI_STATE_AI:

		// �D��x���������ɓ���ւ�
		BubbleSort(m_AIPriorityData.nPriorityData);

		// �擪�̃A�h���X���擾����
		int *nFront = m_AIPriorityData.nPriorityData[0];
		// �擪�̎��̃A�h���X���擾����
		int *nSecond = (m_AIPriorityData.nPriorityData[1]);

		// �U���̗D��x��擪�����Ԗڂ܂ŕۑ�
		BOSS_ONE_ATTACKTYPE Attack_Priority[ATTACK_PRIORITY];

		for (int nCnt = 0, nCntPrio = 0; nCnt < ATTACKTYPE_MAX, nCntPrio < ATTACK_PRIORITY; nCnt++)
		{
			// �D��x����ԍ��������U�����@�����߂�
			if (nFront == &m_AIPriorityData.AttackType[nCnt])
			{
				Attack_Priority[nCntPrio] = (BOSS_ONE_ATTACKTYPE)nCnt;
			}
			// �D��x����Ԗڂɍ��������U�����@�����߂�
			else if (nSecond == &m_AIPriorityData.AttackType[nCnt])
			{
				Attack_Priority[nCntPrio] = (BOSS_ONE_ATTACKTYPE)nCnt;
			}
			// �ǂ��炩�ɓ��Ă͂܂��Ă�����J�E���g�����Z����
			if (nFront == &m_AIPriorityData.AttackType[nCnt] || nSecond == &m_AIPriorityData.AttackType[nCnt])
			{
				nCntPrio++;
			}
		}

		// �D��x�������s���̗D��x���ד����Ȃ烉���_���Ɍ��肷��
		if (*nFront == *nSecond)
		{
			uint64_t nRandomAttack = get_rand_range(0, 1);
			if (nRandomAttack == 0)
			{
				// ��O�̍U�����@�ƍ���̍ŗD��U�����@����������Ȃ�������
				if (m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] != Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY])
				{
					// �U�����@�̐ݒ�
					SetAttackType(Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY]);
				}
				else
				{
					// �U�����@�̐ݒ�
					SetAttackType(Attack_Priority[ATTACK_PRIORITY - 1]);
				}
			}
			else
			{
				// ��O�̍U�����@�ƍ���̍ŗD��U�����@����������Ȃ�������
				if (m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] != Attack_Priority[ATTACK_PRIORITY - 1])
				{
					// �U�����@�̐ݒ�
					SetAttackType(Attack_Priority[ATTACK_PRIORITY - 1]);
				}
				else
				{
					// �U�����@�̐ݒ�
					SetAttackType(Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY]);
				}
			}
		}
		// ��������Ȃ���
		else
		{
			// ��O�̍U�����@�ƍ���̍ŗD��U�����@����������Ȃ�������
			if (m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] != Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY])
			{
				// �U�����@�̐ݒ�
				SetAttackType(Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY]);
			}
			else
			{
				// �U�����@�̐ݒ�
				SetAttackType(Attack_Priority[ATTACK_PRIORITY - 1]);
			}
		}

		// ��Ԃ��U���ɕς���
		SetBossAction(ACTION_PATTERN_ATTACK);

		break;
	}
}

// =====================================================================================================================================================================
//
// �U���̗D��x���v�Z
//
// =====================================================================================================================================================================
void CBoss_One::Attack_Priority()
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	if (pPlayer)
	{
		// �v���C���[�ƃ{�X�̋��������߂�
		const unsigned int nDistance = (unsigned int)this->GetPosition().x - (unsigned int)pPlayer->GetPosition().x;

		// ----- �D��x�̐ݒ� ----- //

		// ----- �˒��O ----- //
		if (nDistance <= MIN_PLAYER_DISTANCE)
		{// �ŒZ�˒��͈͂������ɂ��鎞
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_THREE;
		}

		if (nDistance >= MAX_PLAYER_DISTANCE)
		{// �Œ��˒��͈͂��O���ɂ��鎞
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_NONE;
		}

		// ----- �˒��� ----- //
		if (nDistance >= MIN_PLAYER_DISTANCE && nDistance <= MAX_PLAYER_DISTANCE)
		{// �˒��͈͓��̎�
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_ONE;
		}

		if (nDistance <= MAX_PLAYER_DISTANCE && nDistance >= RANGE_CENTER)
		{// �Œ��˒��͈͂������ɂ��Ĕ͈͂̒��S���O���ɂ��鎞
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_ONE;
		}
		if (nDistance >= MIN_PLAYER_DISTANCE && nDistance <= RANGE_CENTER)
		{// �ŒZ�˒��͈͂��O���ɂ��Ĕ͈͂̒��S�������ɂ��鎞
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_ONE;
		}
		if (nDistance >= RANGE_CENTER - CENTER_RANGE && nDistance <= RANGE_CENTER + CENTER_RANGE)
		{// �͈͂̒��S������ƊO����100�������͈͂̓�����������
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_ONE;
		}
	}

	// ��O�ɊY�����Ă����ꍇ�͋����I�Ɏ��̍s���𐧌�����
	Attack_Exception();
}

// =====================================================================================================================================================================
//
// �D��x�̐��l��������
//
// =====================================================================================================================================================================
void CBoss_One::Attack_InitializeDataAll()
{
	m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			 = PRIORITY_POINT_NONE;
	m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	 = PRIORITY_POINT_NONE;
	m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		 = PRIORITY_POINT_NONE;
	m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	 = PRIORITY_POINT_NONE;
}

// =====================================================================================================================================================================
//
// �w�肵���D��x�̐��l��������
//
// =====================================================================================================================================================================
void CBoss_One::Attack_InitializeData(BOSS_ONE_ATTACKTYPE type)
{
	m_AIPriorityData.AttackType[type] = PRIORITY_POINT_NONE;
}

// =====================================================================================================================================================================
//
// �D��x�����߂�ɂ������Ă̗�O
//
// =====================================================================================================================================================================
void CBoss_One::Attack_Exception()
{
	// ���A���Ŏp���ύX�����Ȃ�
	if (m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] == ATTACKTYPE_SHIFTPOSTURE)
	{
		Attack_InitializeData(ATTACKTYPE_SHIFTPOSTURE);
	}

	// ���Ⴊ��ł�����ڂ̍s���ŋ����I�Ɏp����ύX������
	if (m_AttckTypeOld[ATTACK_PRIORITY - 1] == ATTACKTYPE_SHIFTPOSTURE)
	{
		// ���̍s�������܂��Ă���ꍇ�D��x�̐��l������������
		Attack_InitializeDataAll();
		//
		m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE] = PRIORITY_POINT_MAX;
	}

	// ���Ⴊ��ł��鎞�ɉΉ����˂��������Ȃ�
	if (m_PostureType == POSTURETYPE_SQUAT)
	{
		Attack_InitializeData(ATTACKTYPE_FLAMERADIATION);
	}
}

// =====================================================================================================================================================================
//
// �o�u���\�[�g �傫����
//
// =====================================================================================================================================================================
void CBoss_One::BubbleSort(std::vector<int*> &data)
{
	for (int nCnt = 0; nCnt < (int)data.size() - 1; nCnt++)
	{
		for (int num = (int)data.size() - 1; num > nCnt; num--)
		{
			if (*data[num - 1] < *data[num])
			{  // �傫�����t�]���Ă���ӏ����������� swap
				std::swap(data[num - 1], data[num]);
			}
		}
	}
}

// =====================================================================================================================================================================
//
// �{�X�̃X�e�[�^�X�̐ݒ�
//
// =====================================================================================================================================================================
void CBoss_One::SetBossInfo()
{
	// �̗͂̏����l
	CCharacter::SetLife(m_BossOneData.nLife);
	// �e�̌X��
	GetModelSet()->GetCharacterModelList()[22]->GetRot().x -= 1.0f;
	GetModelSet()->GetCharacterModelList()[21]->GetRot().x -= 1.57f;
}

// =====================================================================================================================================================================
//
// �K���̐����Ɛݒ�
//
// =====================================================================================================================================================================
void CBoss_One::CreateGun()
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		// �e�̐���
		m_pGun[nCnt] = CGun::Create();
		//�}�g���b�N�X�ݒ�
		m_pGun[nCnt]->SetHandMtx(GetModelSet()->GetCharacterModelList()[20 + nCnt]->GetMatrix());
		// �e�̒e�̎��
		m_pGun[nCnt]->SetTag(GetTag());
		// �e�̒e�̎��
		m_pGun[nCnt]->SetGunType(static_cast<CGun::GUN_TYPE>(CGun::GUNTYPE_BALKAN + nCnt));
		// ���ˈʒu�̃I�t�Z�b�g�̐ݒ�
		m_pGun[nCnt]->SetShotOffsetPos(m_BossOneData.GunShotOfsetPos[nCnt]);
		// �e����������ݒ�
		m_pGun[nCnt]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[20 + nCnt]->GetRot().x)));
	}
	// �K���̃I�t�Z�b�g���W�̍X�V
	SetGunOffsetPos(D3DXVECTOR3(GetModelSet()->GetCharacterModelList()[21]->GetPosition()));
	// �K���̍��W�̍X�V
	SetGunPos();
}
