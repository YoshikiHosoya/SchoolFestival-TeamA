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
#include "hosso/Debug_ModelViewer.h"
#include "MeltyHoneyAI.h"
//====================================================================
//�}�N����`
//====================================================================
#define ENEMY_HUMAN_COLLISIONSIZE				(D3DXVECTOR3(50.0f,75.0f,50.0f))			//�G�̓����蔻��T�C�Y
#define ENEMY_HELICOPTER_COLLISIONSIZE			(D3DXVECTOR3(350.0f,150.0f,350.0f))		//�G�̓����蔻��T�C�Y
#define ENEMY_MELTYHONEY_COLLISIONSIZE			(D3DXVECTOR3(250.0f,200.0f,250.0f))		//�G�̓����蔻��T�C�Y
#define ENEMY_ZYCOCCA_COLLISIONSIZE				(D3DXVECTOR3(110.0f,95.0f,110.0f))		//�G�̓����蔻��T�C�Y

#define ENEMY_HUMAN_LIFE						(1)										//���C�t
#define ENEMY_HELICOPTER_LIFE					(20)									//���C�t
#define ENEMY_MELTYHONEY_LIFE					(50)									//���C�t
#define ENEMY_ZYCOCCA_LIFE						(20)									//���C�t


#define KNIFE_COLLISOIN_SIZE	(D3DXVECTOR3(40.0f,60.0f,0.0f))
//====================================================================
//�R���X�g���N�^
//====================================================================
CWeakEnemy::CWeakEnemy(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_ENEMY);
}

//====================================================================
//�f�X�g���N�^
//====================================================================
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// �G�̃^�C�v�ݒ�
	switch (GetEnemyType())
	{
	case CWeakEnemy::ENEMY_TYPE::ENEMY_NORMAL:
		//�I�t�Z�b�g�ݒ�
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_HUMAN);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_HUMAN);

		SetAIPtr(CEnemyAI::CreateAI(this));

		// �e�̐���
		GetGunPtr()->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());
		// �e�̒e�̎��
		GetGunPtr()->SetDisp(true);
		GetGunPtr()->SetGunTypeOnly(CGun::GUNTYPE_HANDGUN_ENEMY);

		// �i�C�t�̐���
		m_pKnife = CKnife::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), KNIFE_COLLISOIN_SIZE, TAG::ENEMY);
		//�r����]���邩
		SetRotArm(true);

		// �����蔻�萶��
		GetCollision()->SetSize(ENEMY_HUMAN_COLLISIONSIZE);

		//HP�ݒ�
		CCharacter::SetLife(ENEMY_HUMAN_LIFE);

		break;
	case CWeakEnemy::ENEMY_TYPE::ENEMY_SHIELD:
		//�I�t�Z�b�g�ݒ�
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_HUMAN);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_HUMAN);

		//AI�̒ǉ�
		SetAIPtr(CShieldEnemyAI::CreateAI(this));

		//������
		m_pShield = nullptr;
		m_pShield = CShield::Create();
		m_pShield->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());
		m_pShield->SetHasEnemyPtr(this);

		// �e�̒e�̎��
		GetGunPtr()->SetDisp(false);

		// �i�C�t�̐���
		m_pKnife = CKnife::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), KNIFE_COLLISOIN_SIZE, TAG::ENEMY);
		//�r����]���邩
		SetRotArm(true);

		//HP�ݒ�
		CCharacter::SetLife(ENEMY_HUMAN_LIFE);

		// �����蔻�萶��
		GetCollision()->SetSize(ENEMY_HUMAN_COLLISIONSIZE);
		break;

	case CWeakEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:
		//�I�t�Z�b�g�ݒ�
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_HELICOPTER);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_HELICOPTER);

		//���[�V����off
		CCharacter::GetModelSet()->SetUseMotion(false);
		CCharacter::GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);

		//�d�͖���
		CCharacter::SetGravity(false);

		// �����蔻�萶��
		GetCollision()->SetSize(ENEMY_HELICOPTER_COLLISIONSIZE);

		//HP�ݒ�
		CCharacter::SetLife(ENEMY_HELICOPTER_LIFE);

		break;

	case CWeakEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
		//�I�t�Z�b�g�ݒ�
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_MELTYHONEY);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_MELTYHONEY);
		//AI�̒ǉ�
		SetAIPtr(CMeltyhoney::CreateAI(this));
		// �e�̐���
		GetGunPtr()->SetHandMtx(GetModelSet()->GetCharacterModelList()[0]->GetMatrix());
		// �e�̒e�̎��
		GetGunPtr()->SetDisp(true);
		GetGunPtr()->SetGunTypeOnly(CGun::GUNTYPE_MISSILE);
		//���[�V����off
		CCharacter::GetModelSet()->SetUseMotion(false);
		CCharacter::GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);

		// �����蔻�萶��
		GetCollision()->SetSize(ENEMY_MELTYHONEY_COLLISIONSIZE);

		//HP�ݒ�
		CCharacter::SetLife(ENEMY_MELTYHONEY_LIFE);

		break;

	case CWeakEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
		//�I�t�Z�b�g�ݒ�
		GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_ENEMY_ZYCOCCA);
		GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_ENEMY_ZYCOCCA);

		//���[�V����off
		CCharacter::GetModelSet()->SetUseMotion(false);
		CCharacter::GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);

		// �����蔻�萶��
		GetCollision()->SetSize(ENEMY_ZYCOCCA_COLLISIONSIZE);

		//HP�ݒ�
		CCharacter::SetLife(ENEMY_ZYCOCCA_LIFE);


		break;

	default:
		break;
	}

	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

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

	//�X�V
	UpdateVehicle();

	//debug
	//CCharacter::GetMove().x += 1.0f;

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
	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "WeakEnemyInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{
		ImGui::Text("m_Attack [%d]", m_Attack);

		CEnemy::DebugInfo();

		if (m_pShield)
		{
			m_pShield->DebugInfo();
		}

		if (m_pKnife)
		{
			m_pKnife->DebugInfo();
		}

		ImGui::TreePop();
	}

	//�I�t�Z�b�g�r���[��
	if (GetEnemyType() == CWeakEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA)
	{
		CDebug_ModelViewer::OffsetViewer(CCharacter::GetModelSet()->GetCharacterModelList());
	}

}
//====================================================================
//��蕨�̍X�V
//====================================================================
void CWeakEnemy::UpdateVehicle()
{
	switch (GetEnemyType())
	{
	case CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
		//�ԗւ̉�]����
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[1], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[2], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[3], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[4], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());

		break;

	case CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:
		//�v���y���̉�]
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[1], MODEL_ROT_TYPE_ALWAYS, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());

		break;

	case CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
		//�ԗւ̉�]����
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[1], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());
		VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[2], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());

		break;
	default:
		break;
	}
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CWeakEnemy *CWeakEnemy::Create(ENEMY_TYPE type)
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
	bool bContinue = false;
	switch (GetEnemyType())
	{
	case CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
	case CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
	case CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:

		GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);
		bContinue = false;

		break;
	case CEnemy::ENEMY_TYPE::ENEMY_NORMAL:
	case CEnemy::ENEMY_TYPE::ENEMY_SHIELD:

		GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
		bContinue = true;

		break;
	}
	return bContinue;
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

		switch (GetEnemyType())
		{
		case CEnemy::ENEMY_TYPE::ENEMY_NORMAL:
		case CEnemy::ENEMY_TYPE::ENEMY_SHIELD:
			//�ߖ�
			CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_ENEMY_DEATH);

			GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_DEAD_1);

			//���̃G�t�F�N�g
			CParticle::CreateFromText(GetPosition(), GetShotDirection(), CParticleParam::EFFECT_BLOOD);

			if (m_pKnife)
			{
				m_pKnife->EndMeleeAttack();
			}

			break;

		case CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
		case CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
		case CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:
			CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION);
			SetStateCount(1);

			break;
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
