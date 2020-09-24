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
#include "gun.h"
#include "ModelSet.h"
#define MAX_RECASTTIME (120)
#define MAX_DISTANCE (400)
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
	m_AItype = AI_NONE;
	m_Distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = 0.0f;

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
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

	if (pEnemyPass != nullptr)
	{
		//�U���ł��鋗���̌v�Z
		if (pPlayer)
		{
			m_Distance = pEnemyPass->GetPosition() - pPlayer->GetPosition();
		}
		m_fDistance = D3DXVec2Length(&D3DXVECTOR2(m_Distance.x, m_Distance.y));

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
			m_recast = (rand() % MAX_RECASTTIME) + 50;	//50�t���[�����̃��L���X�g

			if (m_AItype != m_AItypeOld)
			{
				m_bReStartFlag = false;
				m_castcount = 0;
			}
		}
		//�R���痎���Ȃ��悤�ɂ��鏈��
		if (pMap != nullptr)	// �}�b�v���f�������݂�����
		{
			//if (pEnemyPass->GetCharacterDirection() == DIRECTION::LEFT)
			//{
			//	if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(),
			//		D3DXVECTOR3(0.0f, -1.0f, 0.0f),
			//		D3DXVECTOR3(pEnemyPass->GetPosition().x-30, pEnemyPass->GetPosition().y, pEnemyPass->GetPosition().z)))
			//	{
			//		m_bReStartFlag = false;
			//	}
			//	else
			//	{
			//		m_AItypeOld = m_AItype;						//�O��̍s���i�[
			//		m_bReStartFlag = true;
			//		m_castcount = 0;
			//	}
			//}
			//else if (pEnemyPass->GetCharacterDirection() == DIRECTION::RIGHT)
			//{
			//	if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(),
			//		D3DXVECTOR3(0.0f, -1.0f, 0.0f),
			//		D3DXVECTOR3(pEnemyPass->GetPosition().x+30, pEnemyPass->GetPosition().y, pEnemyPass->GetPosition().z)))
			//	{
			//		m_bReStartFlag = false;
			//	}
			//	else
			//	{
			//		m_AItypeOld = m_AItype;						//�O��̍s���i�[
			//		m_bReStartFlag = true;
			//		m_castcount = 0;
			//	}
			//}
		}
		//���Ⴊ�ݏ�Ԃɐݒ�i�ړ��ȊO��AI�ɂȂ��Ă����Ⴊ�݂��p�����邽�߁j
		if (m_bCrouch == true)
		{
			pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_SQUAT);
		}
		if (pPlayer)
		{
			//�v���C���[���͈͊O�̉E�ɂ���Ƃ�
			if (pEnemyPass->GetPosition().x - pPlayer->GetPosition().x > MAX_DISTANCE)
			{
				m_AItype = AI_WALK_LEFT;
			}
			//�v���C���[���͈͊O�̍��ɂ���Ƃ�
			else if (pEnemyPass->GetPosition().x - pPlayer->GetPosition().x < -MAX_DISTANCE)
			{
				m_AItype = AI_WALK_RIGHT;
			}
		}

		if (pPlayer != nullptr)
		{
			switch (m_AItype)
			{
			case AI_NONE:
				pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
				break;
			case AI_STOP:
				pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
				break;
			case AI_STAND:
				m_bCrouch = false;
				pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
				break;
			case AI_CROUCH:
				m_bCrouch = true;
				break;
			case AI_WALK_LEFT:
				m_bCrouch = false;
				pEnemyPass->GetMove().x -= 1.0f;
				pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
				pEnemyPass->SetCharacterDirection(DIRECTION::LEFT);
				pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_WALK);
				break;
			case AI_WALK_RIGHT:
				m_bCrouch = false;
				pEnemyPass->GetMove().x += 1.0f;
				pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
				pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);
				pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_WALK);
				break;
			case AI_SHOT:
				pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
				//�v���C���[�̂�������Ɍ����Ă��邼�@�C������I
				if (pEnemyPass->GetPosition().x > pPlayer->GetPosition().x)
				{
					pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
					pEnemyPass->SetCharacterDirection(DIRECTION::LEFT);
				}
				else
				{
					pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
					pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);
				}
				if (m_castcount % 30 == 0)
				{
					m_bShot = true;
					pEnemyPass->GetGunPtr()->Shot();
				}
				else
				{
					m_bShot = false;
				}

				break;
			case AI_GRENADE:
				pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
				break;
			}
		}
	}
}
//=============================================================================
// �`��
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
