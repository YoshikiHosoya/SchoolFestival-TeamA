//=============================================================================
// AI処理 [EnemyAI.cpp] Hanzawa
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
// 初期化処理
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
// 終了処理
//=============================================================================
void CEnemyAI::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CEnemyAI::Update(void)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	// マップのポインタ取得
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

	if (pEnemyPass != nullptr)
	{
		//攻撃できる距離の計算
		if (pPlayer)
		{
			m_Distance = pEnemyPass->GetPosition() - pPlayer->GetPosition();
		}
		m_fDistance = D3DXVec2Length(&D3DXVECTOR2(m_Distance.x, m_Distance.y));

		m_castcount++;

		if (m_castcount == m_recast && m_bReStartFlag == false)
		{
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30フレーム分のリキャスト
			m_random = (rand() % AI_MAX);				//行動のランダム
			m_AItype = (AI_STATE)m_random;				//ランダムの形式をAI_STATEに変換
			m_castcount = 0;
			m_bShot = false;
		}
		else if (m_bReStartFlag == true)
		{
			m_random = (rand() % AI_MAX);				//行動のランダム
			m_AItype = (AI_STATE)m_random;				//ランダムの形式をAI_STATEに変換
			m_recast = (rand() % MAX_RECASTTIME) + 50;	//50フレーム分のリキャスト

			if (m_AItype != m_AItypeOld)
			{
				m_bReStartFlag = false;
				m_castcount = 0;
			}
		}
		//崖から落ちないようにする処理
		if (pMap != nullptr)	// マップモデルが存在した時
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
			//		m_AItypeOld = m_AItype;						//前回の行動格納
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
			//		m_AItypeOld = m_AItype;						//前回の行動格納
			//		m_bReStartFlag = true;
			//		m_castcount = 0;
			//	}
			//}
		}
		//しゃがみ状態に設定（移動以外のAIになってもしゃがみを継続するため）
		if (m_bCrouch == true)
		{
			pEnemyPass->GetModelSet()->SetMotion(CModelSet::ENEMY_MOTION_SQUAT);
		}
		if (pPlayer)
		{
			//プレイヤーが範囲外の右にいるとき
			if (pEnemyPass->GetPosition().x - pPlayer->GetPosition().x > MAX_DISTANCE)
			{
				m_AItype = AI_WALK_LEFT;
			}
			//プレイヤーが範囲外の左にいるとき
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
				//プレイヤーのいる方向に撃ってくるぞ　気をつけろ！
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
// 描画
//=============================================================================
void CEnemyAI::Draw(void)
{
}
//=============================================================================
// デバッグ
//=============================================================================
void CEnemyAI::DebugInfo(void)
{
}
//=============================================================================
// AIのクリエイト
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
// AIのタイプ取得
//=============================================================================
CEnemyAI::AI_STATE CEnemyAI::GetAIType(void)
{
	return m_AItype;
}

bool CEnemyAI::GetShot(void)
{
	return m_bShot;
}
