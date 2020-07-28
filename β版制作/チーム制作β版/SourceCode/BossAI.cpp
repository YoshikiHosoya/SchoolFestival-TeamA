//=============================================================================
// AI���� [BossAI.cpp] Hanzawa
//=============================================================================
#include "BossAI.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Boss.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "collision.h"
#define CENTER_POS		(D3DXVECTOR3(0.0f,400.0f,0.0f))
#define RIGHT_POS		(D3DXVECTOR3(300.0f,200.0f,0.0f))
#define LEFT_POS		(D3DXVECTOR3(-300.0f,200.0f,0.0f))
#define MOVE_SPEED		(0.1f)
CBossAI::CBossAI()
{
}

CBossAI::~CBossAI()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CBossAI::Init(void)
{
	m_recast = 60;
	m_castcount = 0;
	m_bShot = false;
	m_random = 0;
	m_AItypeAttack = AI_ATTACK_NONE;
	m_AItypeMove = AI_MOVE_NONE;
	m_ShotVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CBossAI::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CBossAI::Update(void)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	D3DXVECTOR3 Distance;

	if (pBossPass != nullptr || pPlayer != nullptr)
	{
		D3DXVECTOR3 MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		CKeyboard *key;
		key = CManager::GetInputKeyboard();
		if (key->GetKeyboardTrigger(DIK_8))
		{
			m_AItypeMove = AI_CENTER;
		}
		if (key->GetKeyboardTrigger(DIK_7))
		{
			m_AItypeMove = AI_LEFT;
		}
		if (key->GetKeyboardTrigger(DIK_9))
		{
			m_AItypeMove = AI_RIGHT;
		}
		if (key->GetKeyboardTrigger(DIK_0))
		{
			m_AItypeMove = AI_MOVE_NONE;
			m_AItypeAttack = AI_ATTACK_NONE;
		}
		if (key->GetKeyboardTrigger(DIK_B))
		{
			m_AItypeAttack = AI_TRACKING;
		}
			m_AItypeAttackOld = m_AItypeAttack;	//�O��̍U���̊i�[
		m_AItypeMoveOld = m_AItypeMove;		//�O��̈ړ��̊i�[
		//�ړ��֘A
		switch (m_AItypeMove)
		{
		case AI_CENTER: //����
			MoveVec = CENTER_POS - pBossPass->GetPosition();
			//�����̐��K��
			if (pBossPass->GetPosition() != CENTER_POS)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
			else if (pBossPass->GetPosition() == CENTER_POS)
			{
				m_AItypeMove = AI_MOVE_NONE;
			}
			break;
		case AI_LEFT://��
			MoveVec = LEFT_POS - pBossPass->GetPosition();
			//�����̐��K��
			if (pBossPass->GetPosition() != LEFT_POS)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
			else if (pBossPass->GetPosition() == LEFT_POS)
			{
				m_AItypeMove = AI_MOVE_NONE;
			}
			break;
		case AI_RIGHT://�E
			MoveVec = RIGHT_POS - pBossPass->GetPosition();
			//�����̐��K��
			if (pBossPass->GetPosition() != RIGHT_POS)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
			else if (pBossPass->GetPosition() == RIGHT_POS)
			{
				m_AItypeMove = AI_MOVE_NONE;
			}
			break;
		}
		//�U���֘A
		switch (m_AItypeAttack)
		{
		case AI_TRACKING://�v���C���[�Ǐ]�e
			Distance = pPlayer->GetPosition()-pBossPass->GetPosition() ;//�ˌ������̌v�Z
			//D3DXVec3Normalize(&Distance, &Distance);//�l�̐��K��
			m_ShotVec = D3DXVECTOR3(atan2f(Distance.y, Distance.z), atan2f(-Distance.x, -Distance.z), atan2f(Distance.x, Distance.z));		//�����p�x�����߂�


			//pBossPass->GetPosition() += m_ShotVec;
			CDebugProc::Print("�{�X�ˌ�����X�F%2f\n�{�X�ˌ�����Y�F%2f\n", m_ShotVec.y, m_ShotVec.z);
			break;
		case AI_DIFFUSION://�g�U�ˌ�

			break;
		case AI_LASER://���[�U�[
			break;
		}
	}
	CDebugProc::Print("�{�X�̈ړ��X�e�[�g�F%d\n", m_AItypeMove);
}
//=============================================================================
// �^�C�g�����
//=============================================================================
void CBossAI::Draw(void)
{
}
//=============================================================================
// �f�o�b�O
//=============================================================================
void CBossAI::DebugInfo(void)
{
}
D3DXVECTOR3 CBossAI::GetTrackingShotRot(void)
{
	return m_ShotVec;
}
//=============================================================================
// AI�̃N���G�C�g
//=============================================================================
CBossAI * CBossAI::CreateAI(CBoss *pBoss)
{
	CBossAI*pBossAI;
	pBossAI = new CBossAI();
	pBossAI->Init();
	pBossAI->pBossPass = pBoss;
	return pBossAI;
}
//=============================================================================
// AI�̍U���^�C�v�擾
//=============================================================================
CBossAI::AI_STATE_ATTACK CBossAI::GetAITypeAttack(void)
{
	return m_AItypeAttack;
}

bool CBossAI::GetShot(void)
{
	return m_bShot;
}
