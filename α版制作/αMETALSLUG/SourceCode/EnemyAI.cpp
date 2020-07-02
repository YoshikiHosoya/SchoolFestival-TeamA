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
	m_cast = 0;
	m_bShot = false;
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
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			if (pPlayer != nullptr)
			{
				if (m_bShot == true)
				{
					CDebugProc::Print("エネミーショット：実行\n");
					m_cast++;
					m_AItype = AI_NONE;
					if (m_cast == 120)
					{
						m_cast = 0;
						m_bShot = false;
					}
				}
				CDebugProc::Print("エネミーショット：静止\n");
				if (pEnemy->GetPosition().x > pPlayer->GetPosition().x)
				{
					pEnemy->SetRot(D3DXVECTOR3(0.0f, 0.5f*  D3DX_PI, 0.0f));
					if (m_bShot == false)
					{
						m_AItype = AI_SHOT;
						m_bShot = true;
					}
				}
				else
				{
					pEnemy->SetRot(D3DXVECTOR3(0.0f, -0.5f*  D3DX_PI, 0.0f));
					m_AItype = AI_STOP;
				}

			}
		}
	}
	CDebugProc::Print("エネミーショットキャストタイム：%d\n",m_cast);

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
CEnemyAI * CEnemyAI::CreateAI(void)
{
	CEnemyAI*pEnemyAI;
	pEnemyAI = new CEnemyAI();
	pEnemyAI->Init();
	return pEnemyAI;
}
//=============================================================================
// AIのタイプ取得
//=============================================================================
CEnemyAI::AI_STATE CEnemyAI::GetAIType(void)
{
	return m_AItype;
}
