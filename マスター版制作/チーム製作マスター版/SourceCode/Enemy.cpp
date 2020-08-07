//====================================================================
// �G�l�~�[���� [enemy.cpp]: NORI
//====================================================================
#include "Enemy.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "Xinput.h"
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

CEnemy::CEnemy(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_ENEMY);
	m_pGun = nullptr;
}

CEnemy::~CEnemy()
{


}
//====================================================================
//������
//====================================================================
HRESULT CEnemy::Init(void)
{
	//�L�����̏�����
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_ENEMY);
	SetCharacterType(CCharacter::CHARACTER_TYPE_ENEMY);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;

	// �e�̐���
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_ENEMY_RHAND)->GetMatrix());
	// �e�̒e�̎��
	m_pGun->GetTag() = TAG_ENEMY;
	// �����蔻�萶��
	GetCollision()->SetPos(GetPositionPtr());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(ENEMY_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	CCharacter::SetLife(1);
	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CEnemy::Uninit(void)
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

	CCharacter::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CEnemy::Update(void)
{
	//�`��͈͓̔����`�F�b�N
	CheckDrawRange();

	if (!GetDraw())
	{
		return;
	}

	//���S���Ă��Ȃ���
	if (CCharacter::GetCharacterState() != CCharacter::CHARACTER_STATE_DEATH)
	{
		CKeyboard *key;
		key = CManager::GetInputKeyboard();
		if (GetCollision() != nullptr)
		{
			if (GetCollision() != nullptr)
			{

				//���W�̍X�V
				GetCollision()->SetPos(&GetPosition());
			}
			//�̗͂�0�ȉ��ɂȂ�����
			if (this->GetLife() <= 0)
			{
			}
			else
			{
				// �e����������ݒ�
				m_pGun->SetShotRot(GetShotDirection());
			}
			//AI�֘A����
			if (m_pAI != nullptr)
			{
				if (m_pAI->GetAIType() == m_pAI->AI_SHOT && m_pAI->GetShot() == true)
				{
					m_pGun->Shot();
				}

				m_pAI->Update();
			}
		}
	}
	CCharacter::Update();

	m_pGun->Update();


}
//====================================================================
//�`��
//====================================================================
void CEnemy::Draw(void)
{
	CCharacter::Draw();

	m_pGun->Draw();

}
//====================================================================
//�f�o�b�O
//====================================================================
void CEnemy::DebugInfo(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

	if (key->GetKeyboardTrigger(DIK_8))
	{
		SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
	}
	if (key->GetKeyboardTrigger(DIK_9))
	{
		SetMotion(CCharacter::ENEMY_MOTION_WALK);
	}
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CEnemy *CEnemy::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CEnemy*pEnemy;
	pEnemy = new CEnemy(OBJTYPE_ENEMY);
	pEnemy->Init();
	pEnemy->m_pAI = CEnemyAI::CreateAI(pEnemy);
	return pEnemy;
}
//====================================================================
//�f�t�H���g�̃��[�V�����ݒ�
//====================================================================
bool CEnemy::DefaultMotion(void)
{
	SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
	return true;
}
//====================================================================
//�_���[�W���󂯂����̃��A�N�V����
//====================================================================
void CEnemy::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);

	CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
}
//====================================================================
//���񂾎��̃��A�N�V����
//====================================================================
void CEnemy::DeathReaction()
{
	//���S�t���O�����Ă�
	this->SetDieFlag(true);

	CCharacter::DeathReaction();

}
//====================================================================
//�X�e�[�g���ύX�����u�Ԃ̏���
//====================================================================
void CEnemy::StateChangeReaction()
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
void CEnemy::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	//m_rotDest.y = fdest *  D3DX_PI;
}
