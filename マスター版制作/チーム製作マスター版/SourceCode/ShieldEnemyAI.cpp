//=============================================================================
// AI処理 [ShieldEnemyAI.cpp] Hanzawa
//=============================================================================
#include "ShieldEnemyAI.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Enemy.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "map.h"
#include "collision.h"
#include "gun.h"
#define MAX_RECASTTIME (120)
#define MAX_DISTANCE (180)
#define MAX_ATTACKDISTANCE (70)
CShieldEnemyAI::CShieldEnemyAI()
{
}

CShieldEnemyAI::~CShieldEnemyAI()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CShieldEnemyAI::Init(void)
{
	m_recast = 60;
	m_castcount = 0;
	m_bAttack = false;
	m_random = 0;
	m_AItype = AI_NONE;
	m_Distance = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_fDistance = 0.0f;
	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CShieldEnemyAI::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CShieldEnemyAI::Update(void)
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
		// マップモデルが存在した時
		if (pMap != nullptr)
		{
			m_Distance = pEnemyPass->GetPosition() - pPlayer->GetPosition();
			m_fDistance = D3DXVec2Length(&D3DXVECTOR2(m_Distance.x, m_Distance.y));
			if (m_fDistance < MAX_ATTACKDISTANCE)
			{
				m_bAttack = true;
			}
			else
			{
				m_bAttack = false;
			}					
			if (m_bAttack == false)
			{
				//プレイヤーが左にいるとき
				if (pEnemyPass->GetPosition().x > pPlayer->GetPosition().x)
				{
					pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
					pEnemyPass->SetCharacterDirection(DIRECTION::LEFT);
					//Rayの判定があるとき
					if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(),
						D3DXVECTOR3(0.0f, -1.0f, 0.0f),
						D3DXVECTOR3(pEnemyPass->GetPosition().x - 30, pEnemyPass->GetPosition().y, pEnemyPass->GetPosition().z)))
					{
						if (pEnemyPass->GetPosition().x - pPlayer->GetPosition().x > MAX_DISTANCE)
						{
							m_AItype = AI_WALK_LEFT;
						}
						else
						{
							m_AItype = AI_STOP;
						}

					}
					//Rayの判定がないとき
					else
					{
						m_AItype = AI_STOP;
					}
				}
				//プレイヤーが右にいるとき
				else if (pEnemyPass->GetPosition().x < pPlayer->GetPosition().x)
				{
					pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
					pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);
					//Rayの判定があるとき
					if (GetCollision()->RayFloorCollision(pMap, pEnemyPass->GetCharacterModelPartsList(0)->GetMatrix(),
						D3DXVECTOR3(0.0f, -1.0f, 0.0f),
						D3DXVECTOR3(pEnemyPass->GetPosition().x + 30, pEnemyPass->GetPosition().y, pEnemyPass->GetPosition().z)))
					{
						if (pEnemyPass->GetPosition().x - pPlayer->GetPosition().x < -MAX_DISTANCE)
						{
							m_AItype = AI_WALK_RIGHT;
						}
						else
						{
							m_AItype = AI_STOP;
						}

					}
					//Rayの判定がないとき
					else
					{
						m_AItype = AI_STOP;
					}
				}
			}
		}
		if (pPlayer != nullptr)
		{
			switch (m_AItype)
			{
			case AI_NONE://行動なし
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
				break;
			case AI_ATTACK://近接攻撃
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_KNIFEATTACK);
				break;
			case AI_STOP://移動しない
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_NORMAL);
				break;
			case AI_WALK_LEFT://左移動
				pEnemyPass->GetMove().x -= 1.0f;
				pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
				pEnemyPass->SetCharacterDirection(DIRECTION::LEFT);
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_WALK);
				break;
			case AI_WALK_RIGHT://右移動
				pEnemyPass->GetMove().x += 1.0f;
				pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
				pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);
				pEnemyPass->SetMotion(CCharacter::ENEMY_MOTION_WALK);
				break;
			}
		}
		AttackUpdate();
	}
}
//=============================================================================
// 攻撃更新
//=============================================================================
void CShieldEnemyAI::AttackUpdate(void)
{
	if (m_bAttack == true)
	{
		m_AItype = AI_ATTACK;
	}
	// 攻撃モーションから別のモーションになった時
	if (pEnemyPass->GetMotionType() != CCharacter::ENEMY_MOTION_KNIFEATTACK)
	{
		m_bAttack = false;
		//m_pKnife->EndMeleeAttack();
	}
}
//=============================================================================
// 描画
//=============================================================================
void CShieldEnemyAI::Draw(void)
{
}
//=============================================================================
// デバッグ
//=============================================================================
void CShieldEnemyAI::DebugInfo(void)
{
}
//=============================================================================
// AIのクリエイト
//=============================================================================
CShieldEnemyAI * CShieldEnemyAI::CreateAI(CEnemy *pEnemy)
{
	CShieldEnemyAI*pEnemyAI;
	pEnemyAI = new CShieldEnemyAI();
	pEnemyAI->Init();
	pEnemyAI->pEnemyPass = pEnemy;
	return pEnemyAI;
}
//=============================================================================
// AIのタイプ取得
//=============================================================================
CShieldEnemyAI::AI_STATE CShieldEnemyAI::GetAIType(void)
{
	return m_AItype;
}