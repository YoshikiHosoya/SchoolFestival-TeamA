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
#include "collision.h"
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
	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	if (pEnemyPass != nullptr)
	{
		m_castcount++;

		if (m_castcount == m_recast && m_bReStartFlag == false)
		{
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30�t���[�����̃��L���X�g
			m_random = (rand() % AI_MAX);				//�s���̃����_��
			m_AItype = (AI_STATE)m_random;				//�����_���̌`����AI_STATE�ɕϊ�
			m_castcount = 0;
			m_bShot = false;
		}
		else if (m_bReStartFlag == true)
		{
			m_random = (rand() % AI_MAX);				//�s���̃����_��
			m_AItype = (AI_STATE)m_random;				//�����_���̌`����AI_STATE�ɕϊ�
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30�t���[�����̃��L���X�g

			if (m_AItype != m_AItypeOld)
			{
				m_bReStartFlag = false;
				m_castcount = 0;
			}
		}
		// �}�b�v���f�������݂�����
		if (pMap != nullptr)
		{
			if (pEnemyPass->GetCharacterDirection() == CCharacter::CHARACTER_LEFT)
			{
				if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(), D3DXVECTOR3(-1.0f, -1.0f, 0.0f), pEnemyPass->GetPosition()))
				{
					m_bReStartFlag = false;
				}
				else
				{
					m_AItypeOld = m_AItype;						//�O��̍s���i�[
					m_bReStartFlag = true;
					m_castcount = 0;
				}
			}
			else if (pEnemyPass->GetCharacterDirection() == CCharacter::CHARACTER_RIGHT)
			{
				if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(), D3DXVECTOR3(1.0f, -1.0f, 0.0f), pEnemyPass->GetPosition()))
				{
					m_bReStartFlag = false;
				}
				else
				{
					m_AItypeOld = m_AItype;						//�O��̍s���i�[
					m_bReStartFlag = true;
					m_castcount = 0;
				}
			}
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
				pEnemyPass->GetMove().x -= 0.5f;
				pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
				pEnemyPass->SetCharacterDirection(CCharacter::CHARACTER_LEFT);
				break;
			case AI_WALK_RIGHT:
				pEnemyPass->GetMove().x += 0.5f;
				pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
				pEnemyPass->SetCharacterDirection(CCharacter::CHARACTER_RIGHT);
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
