//====================================================================
// �{�X���� [Boss.cpp]: NORI
//====================================================================
#include "Boss.h"
#include "inputKeyboard.h"
#include "GameManager.h"
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
#include "ModelSet.h"
//====================================================================
//�}�N����`
//====================================================================
#define BOSS_SIZE			(D3DXVECTOR3(50.0f,75.0f,0.0f)) //�G�̃T�C�Y
#define BOSS_LIFE			(450)

//====================================================================
//�R���X�g���N�^
//====================================================================
CBoss::CBoss(OBJ_TYPE type) :CEnemy(type)
{
	SetObjType(OBJTYPE_BOSS);
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
	CEnemy::Init();
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_BOSS);
	GetModelSet()->SetMotion(CModelSet::BOSS_MOTION_NORMAL);

	CCharacter::SetLife(BOSS_LIFE);
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_BOSS);

	//�^�C�v�ݒ�
	CEnemy::SetEnemyType(ENEMY_TYPE::ENEMY_BOSS_SOL_DE_ROCA);

	m_Attack = false;
	m_AttackCastCnt = 0;
	m_AttackCnt = 0;
	SetRotDest(D3DXVECTOR3(0.0f, 0.0f*D3DX_PI, 0.0f));
	//�d�͖���
	SetGravity(false);

	// �e�̐���
	GetGunPtr()->SetHandMtx(GetModelSet()->GetCharacterModelList()[0]->GetMatrix());
	GetGunPtr()->SetGunType(CGun::GUNTYPE_TRACKINGGUN);

	// �e�̒e�̎��
	GetGunPtr()->SetTag(TAG::ENEMY);

	//�e��`�悵�Ȃ�
	GetGunPtr()->SetDisp(false);

	// �����蔻�萶��
	GetCollision()->SetSize2D(BOSS_SIZE);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
	return S_OK;
}
//====================================================================
//�I��
//====================================================================
void CBoss::Uninit(void)
{
	CEnemy::Uninit();
}
//====================================================================
//�X�V
//====================================================================
void CBoss::Update(void)
{
	CEnemy::Update();
}
//====================================================================
//�`��
//====================================================================
void CBoss::Draw(void)
{
	CEnemy::Draw();

	//�K���̃}�g���b�N�X�̌v�Z����
	GetGunPtr()->NoDrawCalcMatrixOnly();

}
//====================================================================
//�f�o�b�O
//====================================================================
void CBoss::DebugInfo(void)
{
	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "BossInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{

		ImGui::Text("m_Attack [%d]", m_Attack);
		ImGui::Text("m_AttackCnt [%d]", m_AttackCnt); ImGui::SameLine();
		ImGui::Text("m_AttackCastCnt [%d]", m_AttackCastCnt);

		CEnemy::DebugInfo();

		ImGui::TreePop();
	}

	CDebugProc::Print_Left("BossLife >> %d\n", GetLife());
}
//====================================================================
//���f���̃N���G�C�g
//====================================================================
CBoss *CBoss::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CBoss*pBoss;
	pBoss = new CBoss(OBJTYPE_BOSS);
	// �^�O�̐ݒ�
	pBoss->SetTag(TAG::ENEMY);
	pBoss->Init();
	pBoss->SetAIPtr(CBossAI::CreateAI(pBoss));
	return pBoss;
}
//====================================================================
//�{�X�̃f�t�H���g���[�V����
//====================================================================
bool CBoss::DefaultMotion(void)
{
	GetModelSet()->SetMotion(CModelSet::BOSS_MOTION_NORMAL);
	return true;
}
//====================================================================
//���S���̃��A�N�V����
//====================================================================
void CBoss::DeathReaction()
{
	CCharacter::DeathReaction();

	//�C�x���g�N���A
	CManager::GetGame()->GetGameManager()->EventClear();

	//nullcheck
	if(CManager::GetGame())
	{
		CManager::GetGame()->GetGameManager()->SetGameState(CGameManager::GAMESTATE::RESULT);
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
		if (GetCharacterStateCnt() % 3 == 0)
		{
			CParticle::CreateFromText(GetPosition() + CHossoLibrary::RandomVector3(250.0f), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION);
		}
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
		CEnemy::DeleteAI();
		break;
	}
}