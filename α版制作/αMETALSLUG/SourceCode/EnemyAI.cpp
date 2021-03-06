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
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	// マップのポインタ取得
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

	if (pEnemyPass != nullptr)
	{
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
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30フレーム分のリキャスト

			if (m_AItype != m_AItypeOld)
			{
				m_bReStartFlag = false;
				m_castcount = 0;
			}
		}
		// マップモデルが存在した時
		if (pMap != nullptr)
		{
			if (pEnemyPass->GetCharacterDirection() == CCharacter::CHARACTER_LEFT)
			{
				if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(),
					D3DXVECTOR3(0.0f, -1.0f, 0.0f),
					D3DXVECTOR3(pEnemyPass->GetPosition().x-30, pEnemyPass->GetPosition().y, pEnemyPass->GetPosition().z)))
				{
					m_bReStartFlag = false;
				}
				else
				{
					m_AItypeOld = m_AItype;						//前回の行動格納
					m_bReStartFlag = true;
					m_castcount = 0;
				}
			}
			else if (pEnemyPass->GetCharacterDirection() == CCharacter::CHARACTER_RIGHT)
			{
				if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(), 
					D3DXVECTOR3(0.0f, -1.0f, 0.0f),
					D3DXVECTOR3(pEnemyPass->GetPosition().x+30, pEnemyPass->GetPosition().y, pEnemyPass->GetPosition().z)))
				{
					m_bReStartFlag = false;
				}
				else
				{
					m_AItypeOld = m_AItype;						//前回の行動格納
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
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
				break;
			case AI_STOP:
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
				break;
			case AI_STAND:
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
				break;
			case AI_CROUCH:
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_SQUAT);
				break;
			case AI_WALK_LEFT:
				pEnemyPass->GetMove().x -= 0.5f;
				pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
				pEnemyPass->SetCharacterDirection(CCharacter::CHARACTER_LEFT);
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_WALK);
				break;
			case AI_WALK_RIGHT:
				pEnemyPass->GetMove().x += 0.5f;
				pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
				pEnemyPass->SetCharacterDirection(CCharacter::CHARACTER_RIGHT);
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_WALK);
				break;
			case AI_SHOT:
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
				//プレイヤーのいる方向に撃ってくるぞ　気をつけろ！
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
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
				break;
			}
		}
	}
}
//=============================================================================
// タイトル画面
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
