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

	if (pEnemyPass != nullptr)
	{
		m_castcount++;

		if (m_castcount == m_recast)
		{
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30フレーム分のリキャスト
			m_random = (rand() % AI_MAX);				//行動のランダム
			m_AItype = (AI_STATE)m_random;				//ランダムの形式をAI_STATEに変換
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
				break;
			}
		}
	}
	CDebugProc::Print("エネミー乱数：%d\n", m_AItype);
	CDebugProc::Print("エネミーリキャストタイム：%d\n", m_recast);
	CDebugProc::Print("エネミーキャストタイム：%d\n", m_castcount);
	CDebugProc::Print("エネミーpositon.x：%2f\n", pEnemyPass->GetPosition().x);

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
