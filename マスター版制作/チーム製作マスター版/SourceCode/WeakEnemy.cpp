//====================================================================
// �G�l�~�[���� [enemy.cpp]: NORI
//====================================================================
#include "weakenemy.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "collision.h"
#include "debugproc.h"
#include "item.h"
#include "EnemyAI.h"
#include "gun.h"
#include "particle.h"
#include "sound.h"
#include "shield.h"
//====================================================================
//�}�N����`
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //�G�̃T�C�Y

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
	//�L�����̏�����
	CEnemy::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_ENEMY);
	SetCharacterType(CCharacter::CHARACTER_TYPE_ENEMY);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// �e�̐���
	GetGunPtr()->SetHandMtx(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());

	// �e�̒e�̎��
	GetGunPtr()->GetTag() = TAG_ENEMY;

	//������
	m_pShield = nullptr;
	m_pShield = CShield::Create();
	m_pShield->SetHandMtx(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());
	m_pShield->SetHasEnemyPtr(this);

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

	CEnemy::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CWeakEnemy::Update(void)
{
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
CWeakEnemy *CWeakEnemy::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CWeakEnemy*pWeakEnemy;
	pWeakEnemy = new CWeakEnemy(OBJTYPE_ENEMY);
	pWeakEnemy->Init();
	pWeakEnemy->SetAIPtr(CEnemyAI::CreateAI(pWeakEnemy));

	return pWeakEnemy;
}
//====================================================================
//�f�t�H���g�̃��[�V�����ݒ�
//====================================================================
bool CWeakEnemy::DefaultMotion(void)
{
	SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
	return true;
}
//====================================================================
//�_���[�W���󂯂����̃��A�N�V����
//====================================================================
void CWeakEnemy::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);

	CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
}
//====================================================================
//���񂾎��̃��A�N�V����
//====================================================================
void CWeakEnemy::DeathReaction()
{
	//���S�t���O�����Ă�
	this->SetDieFlag(true);

	CCharacter::DeathReaction();

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

	case CHARACTER_STATE_DAMAGE:

		break;
	case CHARACTER_STATE_DAMAGE_RED:

		break;
	case CHARACTER_STATE_INVINCIBLE:

		break;
	case CHARACTER_STATE_DEATH:
		SetStateCount(60);
		SetMotion(CCharacter::ENEMY_MOTION_DEAD_1);

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
