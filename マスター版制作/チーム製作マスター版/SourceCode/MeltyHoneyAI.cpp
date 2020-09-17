//=============================================================================
// AI処理 [BossAI.cpp] Hanzawa
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
// 初期化処理
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
// 終了処理
//=============================================================================
void CMeltyhoney::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CMeltyhoney::Update(void)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	// マップのポインタ取得
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	m_castcount++;
	if (pEnemyPass != nullptr)
	{
		// マップモデルが存在した時
		if (pMap != nullptr)
		{
			if (pPlayer != nullptr)
			{
				pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);
				//攻撃できる距離の計算
				m_Distance = pEnemyPass->GetPosition() - pPlayer->GetPosition();
				m_fDistance = D3DXVec2Length(&D3DXVECTOR2(m_Distance.x, m_Distance.y));
				//この距離まで移動
				if (m_fDistance > 200)
				{
					m_AItype = AI_RIGHT;
				}
				else
				{
					m_AItype = AI_LEFT;
				}
				//射程内なら射撃
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
					//120フレームより小さいとき射撃
					if (m_AttackCnt < 60 && m_Attacks < 3 && m_AttackCnt % 10 == 0)
					{
						pEnemyPass->GetGunPtr()->Shot();
					}
					else if (m_AttackCnt == 120)
					{
						m_AttackCnt = 0;
						m_Attacks++;
					}
					//60フレームかつ攻撃回数に達したら初期化
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
// 移動AI更新処理
//=============================================================================
void CMeltyhoney::UpdateMoveAI(void)
{
}
//=============================================================================
// 攻撃AI更新処理
//=============================================================================
void CMeltyhoney::UpdateAttackAI(void)
{
}
//=============================================================================
// 描画
//=============================================================================
void CMeltyhoney::Draw(void)
{
}
//=============================================================================
// デバッグ
//=============================================================================
void CMeltyhoney::DebugInfo(void)
{
}

//=============================================================================
// AIのクリエイト
//=============================================================================
CMeltyhoney * CMeltyhoney::CreateAI(CWeakEnemy *pEnemy)
{
	CMeltyhoney*pMeltyhoneyAI;
	pMeltyhoneyAI = new CMeltyhoney();
	pMeltyhoneyAI->Init();
	pMeltyhoneyAI->pEnemyPass = pEnemy;

	return pMeltyhoneyAI;
}
