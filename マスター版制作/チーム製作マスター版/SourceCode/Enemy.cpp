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
#include "GameManager.h"
//====================================================================
//�}�N����`
//====================================================================
#define ENEMY_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //�G�̃T�C�Y

CEnemy::CEnemy(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_ENEMY);
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

	//�K���̃|�C���^����
	m_pGun = CGun::Create();

	//�C�x���g�̃t���O
	m_bEventFlag = false;

	// �����蔻�萶��
	GetCollision()->SetPos(GetPositionPtr());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(ENEMY_SIZE);
	GetCollision()->SetMove(&GetMove());

	CCharacter::SetLife(1);

	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CEnemy::Uninit(void)
{
	if (m_pAI != nullptr)
	{
		delete m_pAI;
		m_pAI = nullptr;
	}
	// �e�̉��
	if (m_pGun != nullptr)
	{
		// �e�̍폜
		delete m_pGun;
		m_pGun = nullptr;
	}

	CCharacter::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CEnemy::Update(void)
{
	//���S���Ă��Ȃ���
	if (CCharacter::GetCharacterState() != CCharacter::CHARACTER_STATE_DEATH)
	{
		// �e����������ݒ�
		GetGunPtr()->SetShotRot(GetShotDirection());

		//AI�֘A����
		if (m_pAI)
		{
			m_pAI->Update();
		}
		if (m_pGun)
		{
			m_pGun->Update();
		}
	}

	//�L�����N�^�[�̍X�V
	CCharacter::Update();
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
	m_pAI->DebugInfo();
	m_pGun->DebugInfo();
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
}
//====================================================================
//���񂾎��̃��A�N�V����
//====================================================================
void CEnemy::DeathReaction()
{
	//���S�t���O�����Ă�
	this->SetDieFlag(true);

	//���S���A�N�V����
	CCharacter::DeathReaction();

	//�t���O�������Ă��鎞
	if (m_bEventFlag)
	{
		//�C�x���g�N���A
		CManager::GetGame()->GetGameManager()->EventClear();
	}
}
//====================================================================
//�X�e�[�g���ύX�����u�Ԃ̏���
//====================================================================
void CEnemy::StateChangeReaction()
{

}
//====================================================================
//AI����
//====================================================================
void CEnemy::DeleteAI()
{
	if (m_pAI != nullptr)
	{
		delete m_pAI;
		m_pAI = nullptr;
	}
}
