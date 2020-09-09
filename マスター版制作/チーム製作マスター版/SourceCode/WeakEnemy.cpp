//====================================================================
// �G�l�~�[���� [enemy.cpp]: NORI
//====================================================================
#include "weakenemy.h"
#include "Enemy.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "collision.h"
#include "debugproc.h"
#include "ShieldEnemyAI.h"
#include "EnemyAI.h"
#include "gun.h"
#include "particle.h"
#include "sound.h"
#include "shield.h"
#include "Knife.h"
#include "item.h"
#include "ModelSet.h"
//====================================================================
//�}�N����`
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //�G�̃T�C�Y
#define KNIFE_COLLISOIN_SIZE	(D3DXVECTOR3(40.0f,60.0f,0.0f))

CWeakEnemy::CWeakEnemy(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_ENEMY);
}

CWeakEnemy::~CWeakEnemy()
{
}
//====================================================================
//������
//====================================================================
HRESULT CWeakEnemy::Init(void)
{
	// �L�����̏�����
	CEnemy::Init();
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY);
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// �e�̐���
	GetGunPtr()->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());
	// �e�̒e�̎��
	GetGunPtr()->SetTag(TAG::ENEMY);

	GetGunPtr()->SetGunTypeOnly(CGun::GUNTYPE_HANDGUN_ENEMY);
	// �i�C�t�̐���

	m_pKnife = CKnife::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), KNIFE_COLLISOIN_SIZE,TAG::ENEMY);
	//�r����]���邩
	SetRotArm(true);

	// �G�̃^�C�v�ݒ�
	switch (GetEnemyType())
	{
	case CWeakEnemy::WEAKENEMY_TYPE::ENEMY_NORMAL:
		SetAIPtr(CEnemyAI::CreateAI(this));
		break;
	case CWeakEnemy::WEAKENEMY_TYPE::ENEMY_SHIELD:
		//AI�̒ǉ�
		SetAIPtr(CShieldEnemyAI::CreateAI(this));
		//������
		m_pShield = nullptr;
		m_pShield = CShield::Create();
		m_pShield->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());
		m_pShield->SetHasEnemyPtr(this);
		break;
	default:
		break;
	}


	// �����蔻�萶��
	GetCollision()->SetSize2D(ENEMY_SIZE);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	CCharacter::SetLife(1);
	
	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CWeakEnemy::Uninit(void)
{
	if (m_pShield)
	{
		m_pShield->Rerease();
		m_pShield = nullptr;
	}
	if (m_pKnife)
	{
		m_pKnife->Rerease();
		m_pKnife = nullptr;
	}

	CEnemy::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CWeakEnemy::Update(void)
{
	//�`��͈͓̔����`�F�b�N
	if (!CheckDrawRange())
	{
		//��ʂ̍��[��荶�ɍs�����ꍇ�͎��S����
		if (CManager::GetRenderer()->GetMinScreenPos().x > GetPosition().x)
		{
			//���S
			DeathReaction();
		}
		return;
	}
	CEnemy::Update();
}
//====================================================================
//�`��
//====================================================================
void CWeakEnemy::Draw(void)
{
	CEnemy::Draw();

}
//====================================================================
//�f�o�b�O
//====================================================================
void CWeakEnemy::DebugInfo(void)
{

}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CWeakEnemy *CWeakEnemy::Create(WEAKENEMY_TYPE type)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CWeakEnemy*pWeakEnemy;
	pWeakEnemy = new CWeakEnemy(OBJTYPE_ENEMY);
	pWeakEnemy->SetEnemyType(type);
	// �^�O�̐ݒ�
	pWeakEnemy->SetTag(TAG::ENEMY);
	pWeakEnemy->Init();


	return pWeakEnemy;
}
//====================================================================
//�f�t�H���g�̃��[�V�����ݒ�
//====================================================================
bool CWeakEnemy::DefaultMotion(void)
{
	GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
	return true;
}
//====================================================================
//�_���[�W���󂯂����̃��A�N�V����
//====================================================================
void CWeakEnemy::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);
}
//====================================================================
//���񂾎��̃��A�N�V����
//====================================================================
void CWeakEnemy::DeathReaction()
{
	if (CHossoLibrary::Random(10) <= 1)
	{
		// �����_���Ȋm���ŃA�C�e�����h���b�v����
		if (CItem::DropRate())
		{
			//�A�C�e���𐶐�
			CItem::DropCreate(GetPosition(),
				CItem::ITEMDROP_CHARGE,
				CItem::ITEMDROP_PATTERN_DESIGNATE,
				CItem::ITEMTYPE_NONE);
		}
	}

	CEnemy::DeathReaction();

}
//====================================================================
//�X�e�[�g���ύX�����u�Ԃ̏���
//====================================================================
void CWeakEnemy::StateChangeReaction()
{

	CCharacter::StateChangeReaction();

	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_NORMAL:
		break;

	case CHARACTER_STATE_DAMAGE_RED:

		break;
	case CHARACTER_STATE_DEATH:
		SetStateCount(60);
		m_pKnife->EndMeleeAttack();
		GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_DEAD_1);

		switch (GetEnemyType())
		{
		case CEnemy::WEAKENEMY_TYPE::ENEMY_NORMAL:
		case CEnemy::WEAKENEMY_TYPE::ENEMY_SHIELD:
			//�ߖ�
			CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_ENEMY_DEATH);

			//���̃G�t�F�N�g
			CParticle::CreateFromText(GetPosition(), GetShotDirection(), CParticleParam::EFFECT_BLOOD);
		default:
			break;
		}

		if (m_pShield)
		{
			//���j��
			ShieldBreak();
		}

		break;
	}
}
//====================================================================
//�c�j��
//====================================================================
void CWeakEnemy::ShieldBreak()
{
	//nullcheck
	if (m_pShield)
	{
		//�V�[���h������΂�����
		m_pShield->AwayShield();

		//null
		m_pShield = nullptr;

	}
}
