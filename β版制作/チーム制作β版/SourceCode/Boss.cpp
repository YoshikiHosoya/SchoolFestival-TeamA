//====================================================================
// �{�X���� [Boss.cpp]: NORI
//====================================================================
#include "Boss.h"
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
#include "BossAI.h"
//====================================================================
//�}�N����`
//====================================================================
#define BOSS_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //�G�̃T�C�Y
#define BOSS_LIFE			(1500)


//====================================================================
//�R���X�g���N�^
//====================================================================
CBoss::CBoss(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_BOSS);
	m_pGun = nullptr;
}
//====================================================================
//�f�X�g���N�^
//====================================================================
CBoss::~CBoss()
{


}
//====================================================================
//������
//====================================================================
HRESULT CBoss::Init(void)
{
	//�L�����̏�����
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_BOSS);
	SetPosition(D3DXVECTOR3(0.0f, 300.0f, 0.0f));
	SetMotion(CCharacter::BOSS_MOTION_NORMAL);

	CCharacter::SetLife(BOSS_LIFE);
	SetCharacterType(CCharacter::CHARACTER_TYPE_BOSS);

	m_Attack = false;
	m_AttackCastCnt = 0;
	m_AttackCnt = 0;
	SetRotDest(D3DXVECTOR3(0.0f, 0.0f*D3DX_PI, 0.0f));
	//�d�͖���
	SetGravity(false);

	// �e�̐���
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_BOSS_BODY)->GetMatrix());
	m_pGun->SetGunType(CGun::GUNTYPE_TRACKINGGUN);

	// �e�̒e�̎��
	m_pGun->GetTag() = TAG_ENEMY;

	// �����蔻�萶��
	GetCollision()->SetPos(GetPositionPtr());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(BOSS_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CBoss::Uninit(void)
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
void CBoss::Update(void)
{
	//AI�֘A����
	if (m_pAI != nullptr)
	{
		m_pAI->Update();
	}
	CCharacter::Update();

	m_pGun->Update();

}
//====================================================================
//�`��
//====================================================================
void CBoss::Draw(void)
{
	CCharacter::Draw();

	//�K���̃}�g���b�N�X�̌v�Z����
	m_pGun->NoDrawCalcMatrixOnly();

}
//====================================================================
//�f�o�b�O
//====================================================================
void CBoss::DebugInfo(void)
{

}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CBoss *CBoss::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CBoss*pBoss;
	pBoss = new CBoss(OBJTYPE_BOSS);
	pBoss->Init();
	pBoss->m_pAI = CBossAI::CreateAI(pBoss);
	return pBoss;
}
//====================================================================
//�{�X�̃f�t�H���g���[�V����
//====================================================================
bool CBoss::DefaultMotion(void)
{
	SetMotion(CCharacter::BOSS_MOTION_NORMAL);
	return true;
}
//====================================================================
//���S���̃��A�N�V����
//====================================================================
void CBoss::DeathReaction()
{
	CCharacter::DeathReaction();

	//nullcheck
	if(CManager::GetGame())
	{
		CManager::GetGame()->SetGameMode(CGame::GAME_MODE_RESULT);
	}

	SetDieFlag(true);
}
//====================================================================
//�X�e�[�g�ɉ���������
//====================================================================
void CBoss::State()
{
	CCharacter::State();

	//�X�e�[�^�X�̏���
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_DEATH:
		//����
		CParticle::CreateFromText(GetPosition() + CHossoLibrary::RandomVector3(150.0f), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION);
		break;
	}
}
//====================================================================
//�X�e�[�g�؂�ւ����̃��A�N�V����
//====================================================================
void CBoss::StateChangeReaction()
{
	CCharacter::StateChangeReaction();

	//�X�e�[�^�X�̏���
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_DEATH:
 		SetStateCount(300);

		if (m_pAI != nullptr)
		{
			delete m_pAI;
			m_pAI = nullptr;
		}
		break;
	}
}
//====================================================================
//�{�X�̏e�̎擾
//====================================================================
CGun *CBoss::GetGun(void)
{
	return m_pGun;
}
//====================================================================
//�ړ�
//====================================================================
void CBoss::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	//m_rotDest.y = fdest *  D3DX_PI;
}
