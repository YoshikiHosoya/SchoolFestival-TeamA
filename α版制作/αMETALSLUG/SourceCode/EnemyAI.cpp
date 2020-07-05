//=============================================================================
// AI���� [EnemyAI.cpp] Hanzawa
//=============================================================================
#include "EnemyAI.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Enemy.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "map.h"
CEnemyAI::CEnemyAI()
{
}

CEnemyAI::~CEnemyAI()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CEnemyAI::Init(void)
{
	m_recast = 60;
	m_castcount = 0;
	m_bShot = false;
	m_random = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CEnemyAI::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CEnemyAI::Update(void)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	if (pEnemyPass != nullptr)
	{
		m_castcount++;

		if (m_castcount == m_recast)
		{
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30�t���[�����̃��L���X�g
			m_random = (rand() % AI_MAX);				//�s���̃����_��
			m_AItype = (AI_STATE)m_random;				//�����_���̌`����AI_STATE�ɕϊ�
			m_castcount = 0;
			m_bShot = false;
		}
		if (m_castcount % 30 == 0)
		{
			m_bShot = true;
		}
		else
		{
			m_bShot = false;
		}
		if (pPlayer != nullptr)
		{

			switch (m_AItype)
			{
			case AI_NONE:
				break;
			case AI_STOP:
				break;
			case AI_STAND:
				break;
			case AI_CROUCH:
				break;
			case AI_WALK_LEFT:
				pEnemyPass->GetMove().x -= 0.2f;
				pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
				break;
			case AI_WALK_RIGHT:
				pEnemyPass->GetMove().x += 0.2f;
				pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
				break;
			case AI_SHOT:
				//�v���C���[�̂�������Ɍ����Ă��邼�@�C������I
				if (pEnemyPass->GetPosition().x > pPlayer->GetPosition().x)
				{
					pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
					pEnemyPass->SetCharacterDirection(CCharacter::CHARACTER_LEFT);
				}
				else
				{
					pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
					pEnemyPass->SetCharacterDirection(CCharacter::CHARACTER_RIGHT);
				}
				break;
			case AI_GRENADE:
				break;
			}
		}
	}
	CDebugProc::Print("�G�l�~�[�����F%d\n", m_AItype);
	CDebugProc::Print("�G�l�~�[���L���X�g�^�C���F%d\n", m_recast);
	CDebugProc::Print("�G�l�~�[�L���X�g�^�C���F%d\n", m_castcount);
	CDebugProc::Print("�G�l�~�[positon.x�F%2f\n", pEnemyPass->GetPosition().x);

}
//=============================================================================
// �^�C�g�����
//=============================================================================
void CEnemyAI::Draw(void)
{
}
//=============================================================================
// �f�o�b�O
//=============================================================================
void CEnemyAI::DebugInfo(void)
{
}
//=============================================================================
// AI�̃N���G�C�g
//=============================================================================
CEnemyAI * CEnemyAI::CreateAI(CEnemy *pEnemy)
{
	CEnemyAI*pEnemyAI;
	pEnemyAI = new CEnemyAI();
	pEnemyAI->Init();
	pEnemyAI->pEnemyPass = pEnemy;
	return pEnemyAI;
}
//=============================================================================
// AI�̃^�C�v�擾
//=============================================================================
CEnemyAI::AI_STATE CEnemyAI::GetAIType(void)
{
	return m_AItype;
}

bool CEnemyAI::GetShot(void)
{
	return m_bShot;
}
