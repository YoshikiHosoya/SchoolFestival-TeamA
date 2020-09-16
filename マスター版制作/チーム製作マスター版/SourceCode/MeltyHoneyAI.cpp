//=============================================================================
// AI���� [BossAI.cpp] Hanzawa
//=============================================================================
#include "MeltyHoneyAI.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Boss.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "collision.h"
#include "gun.h"
#include "particle.h"
#include "sound.h"
#include "WeakEnemy.h"
#include "ModelSet.h"
#define MOVE_SPEED		(0.5f)
#define MAX_RECASTTIME (60)
CMeltyhoney::CMeltyhoney()
{
}

CMeltyhoney::~CMeltyhoney()
{
}

//=============================================================================
// ����������
//=============================================================================
HRESULT CMeltyhoney::Init(void)
{
	m_recast = 60;
	m_castcount = 0;
	m_LaserRandom = 0;
	m_bShot = false;
	m_AItype = AI_NONE;
	m_ShotVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Attack = false;
	m_AttackCastCnt = 0;
	m_AttackCnt = 0;
	m_MoveCnt = 0;
	m_Attacks = 0;
	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CMeltyhoney::Uninit(void)
{
}

//=============================================================================
// �X�V����
//=============================================================================
void CMeltyhoney::Update(void)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	// �}�b�v�̃|�C���^�擾
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	m_castcount++;
	if (pEnemyPass != nullptr)
	{
		// �}�b�v���f�������݂�����
		if (pMap != nullptr)
		{
			if (pPlayer != nullptr)
			{
				pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);
				//�U���ł��鋗���̌v�Z
				m_Distance = pEnemyPass->GetPosition() - pPlayer->GetPosition();
				m_fDistance = D3DXVec2Length(&D3DXVECTOR2(m_Distance.x, m_Distance.y));
				//���̋����܂ňړ�
				if (m_fDistance > 200)
				{
					m_AItype = AI_RIGHT;
				}
				else
				{
					m_AItype = AI_LEFT;
				}
				//�˒����Ȃ�ˌ�
				if (m_fDistance < 200)
				{
					m_AItype = AI_SHOT;
				}
				switch (m_AItype)
				{
				case AI_NONE:
					pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
					break;
				case AI_STOP:
					pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
					break;
				case AI_LEFT:
					pEnemyPass->GetMove().x -= MOVE_SPEED;
					pEnemyPass->SetCharacterDirection(DIRECTION::LEFT);
					pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
					pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_WALK);
					break;
				case AI_RIGHT:
					pEnemyPass->GetMove().x += MOVE_SPEED;
					pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);
					pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
					pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_WALK);
					break;
				case AI_SHOT:
					pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_NORMAL);
					m_AttackCnt++;
					//120�t���[����菬�����Ƃ��ˌ�
					if (m_AttackCnt < 60 && m_Attacks < 3 && m_AttackCnt % 10 == 0)
					{
						pEnemyPass->GetGunPtr()->Shot();
					}
					else if (m_AttackCnt == 120)
					{
						m_AttackCnt = 0;
						m_Attacks++;
					}
					//60�t���[�����U���񐔂ɒB�����珉����
					if (m_AttackCnt > 60 && m_Attacks >= 3)
					{
						m_AttackCnt = 0;
						m_Attacks = 0;
					}
					break;
				}
			}
		}
	}
	UpdateMoveAI();
	UpdateAttackAI();
}
//=============================================================================
// �ړ�AI�X�V����
//=============================================================================
void CMeltyhoney::UpdateMoveAI(void)
{
}
//=============================================================================
// �U��AI�X�V����
//=============================================================================
void CMeltyhoney::UpdateAttackAI(void)
{
}
//=============================================================================
// �`��
//=============================================================================
void CMeltyhoney::Draw(void)
{
}
//=============================================================================
// �f�o�b�O
//=============================================================================
void CMeltyhoney::DebugInfo(void)
{
}

//=============================================================================
// AI�̃N���G�C�g
//=============================================================================
CMeltyhoney * CMeltyhoney::CreateAI(CWeakEnemy *pEnemy)
{
	CMeltyhoney*pMeltyhoneyAI;
	pMeltyhoneyAI = new CMeltyhoney();
	pMeltyhoneyAI->Init();
	pMeltyhoneyAI->pEnemyPass = pEnemy;

	return pMeltyhoneyAI;
}
