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
//====================================================================
//�}�N����`
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //�G�̃T�C�Y

CWeakEnemy::CWeakEnemy(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_ENEMY);
	m_pGun = nullptr;
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
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());
	// �e�̒e�̎��
	m_pGun->GetTag() = TAG_ENEMY;

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
	// �e�̉��
	if (m_pGun != nullptr)
	{
		// �e�̍폜
		delete m_pGun;
		m_pGun = nullptr;
	}
	if (m_pAI != nullptr)
	{
		delete m_pAI;
		m_pAI = nullptr;
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
		//�`��͈͊O�Ȃ�`�悵�Ȃ�
		return;
	}

	//���S���Ă��Ȃ���
	if (CCharacter::GetCharacterState() != CCharacter::CHARACTER_STATE_DEATH)
	{
		if (GetCollision() != nullptr)
		{

			// �e����������ݒ�
			m_pGun->SetShotRot(GetShotDirection());
			//AI�֘A����
			if (m_pAI)
			{
				if (m_pAI->GetAIType() == m_pAI->AI_SHOT && m_pAI->GetShot() == true)
				{
					m_pGun->Shot();
				}

				m_pAI->Update();
			}
			if (m_pGun)
			{
				m_pGun->Update();
			}
		}
	}
	CEnemy::Update();
}
//====================================================================
//�`��
//====================================================================
void CWeakEnemy::Draw(void)
{
	CEnemy::Draw();

	m_pGun->Draw();

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
	pWeakEnemy->m_pAI = CEnemyAI::CreateAI(pWeakEnemy);
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

		break;
	}
}
//====================================================================
//�ړ�
//====================================================================
void CWeakEnemy::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 3.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 3.0f;
	//m_rotDest.y = fdest *  D3DX_PI;
}
