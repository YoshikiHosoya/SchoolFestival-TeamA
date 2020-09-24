// =====================================================================================================================================================================
//
// ジィ・コッカのAIの処理 [zycoccaAI.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "zycoccaAI.h"		// インクルードファイル
#include "renderer.h"
#include "WeakEnemy.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "map.h"
#include "gun.h"
#include "ModelSet.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define SHOT_COOLTIME				(230)					// 撃つまでの時間
#define MOVE_STOP_TIME				(120)					// 止まるまでの時間
#define MOVE_SPEED					(3.0f)					// 移動スピード

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CZycoccaAI::CZycoccaAI()
{
	m_pEnemyPass = nullptr;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CZycoccaAI::~CZycoccaAI()
{
	m_pEnemyPass = nullptr;
}

// =====================================================================================================================================================================
//
// 初期化処理
// 
// =====================================================================================================================================================================
HRESULT CZycoccaAI::Init(void)
{
	m_nCntShotFrame = 0;						// 撃つまでのカウント
	m_nCntMoveStopFrame = 0;					// 止まるまでのカウント
	m_StateAI = ZycoccaAI_STATE::NONE;			// AIの状態
	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
// 
// =====================================================================================================================================================================
void CZycoccaAI::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// 更新処理
// 
// =====================================================================================================================================================================
void CZycoccaAI::Update(void)
{
	// ジィ・コッカのAIの状態
	ZycoccaAIState();
}

// =====================================================================================================================================================================
//
// 描画処理
// 
// =====================================================================================================================================================================
void CZycoccaAI::Draw(void)
{
}

// =====================================================================================================================================================================
//
// デバッグ情報表記
// 
// =====================================================================================================================================================================
void CZycoccaAI::DebugInfo(void)
{
}

// =====================================================================================================================================================================
//
// AIの生成
// 
// =====================================================================================================================================================================
CZycoccaAI * CZycoccaAI::CreateAI(CWeakEnemy *pEnemy)
{
	// 変数
	CZycoccaAI	*pZycoccaAI;

	// メモリの確保
	pZycoccaAI = new CZycoccaAI();

	// 初期化
	pZycoccaAI->Init();

	// エネミーの情報
	pZycoccaAI->m_pEnemyPass = pEnemy;

	return pZycoccaAI;
}

// =====================================================================================================================================================================
//
// AIの状態取得
// 
// =====================================================================================================================================================================
CZycoccaAI::ZycoccaAI_STATE CZycoccaAI::GetAIType(void)
{
	return m_StateAI;
}

// =====================================================================================================================================================================
//
// ジィ・コッカのAIの状態
// 
// =====================================================================================================================================================================
void CZycoccaAI::ZycoccaAIState()
{
	// プレイヤーのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	// マップのポインタ取得
	CMap *pMap = CManager::GetBaseMode()->GetMap();

	// エネミーの情報が入っているとき
	if (m_pEnemyPass)
	{
		// マップモデルが存在した時
		if (pMap)
		{
			// プレイヤーが存在しているとき
			if (pPlayer)
			{
				switch (m_StateAI)
				{
				case CZycoccaAI::ZycoccaAI_STATE::NONE:
					//プレイヤーが左にいるとき
					if (m_pEnemyPass->GetPosition().x > pPlayer->GetPosition().x)
					{
						m_StateAI = ZycoccaAI_STATE::WALK_LEFT;
					}

					//プレイヤーが右にいるとき
					if (m_pEnemyPass->GetPosition().x < pPlayer->GetPosition().x)
					{
						m_StateAI = ZycoccaAI_STATE::WALK_RIGHT;
					}
					break;

				case CZycoccaAI::ZycoccaAI_STATE::STOP:
					// 動きを止めて攻撃開始
					m_pEnemyPass->SetMove(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
					m_StateAI = ZycoccaAI_STATE::ATTACK;
					break;

				case CZycoccaAI::ZycoccaAI_STATE::WALK_LEFT:

					// カウントアップ
					m_nCntMoveStopFrame++;

					//プレイヤーが左にいるとき
					if (m_pEnemyPass->GetPosition().x > pPlayer->GetPosition().x)
					{
						m_pEnemyPass->GetRotDest().y = D3DX_PI * 0.5f;
						m_pEnemyPass->SetCharacterDirection(DIRECTION::LEFT);

						// 移動
						m_pEnemyPass->GetMove().x = -MOVE_SPEED;
					}
					// 一定時間たったら止まる
					if (m_nCntMoveStopFrame > MOVE_STOP_TIME)
					{
						m_StateAI = ZycoccaAI_STATE::STOP;
					}
					break;

				case CZycoccaAI::ZycoccaAI_STATE::WALK_RIGHT:

					// カウントアップ
					m_nCntMoveStopFrame++;

					//プレイヤーが右にいるとき
					if (m_pEnemyPass->GetPosition().x < pPlayer->GetPosition().x)
					{
						m_pEnemyPass->GetRotDest().y = D3DX_PI * -0.5f;
						m_pEnemyPass->SetCharacterDirection(DIRECTION::RIGHT);

						// 移動
						m_pEnemyPass->GetMove().x = MOVE_SPEED;
					}
					// 一定時間たったら止まる
					if (m_nCntMoveStopFrame > MOVE_STOP_TIME)
					{
						m_StateAI = ZycoccaAI_STATE::STOP;
					}
					break;

				case CZycoccaAI::ZycoccaAI_STATE::ATTACK:

					// カウントアップ
					m_nCntShotFrame++;

					if (m_nCntShotFrame > SHOT_COOLTIME)
					{
						// 発射
						m_pEnemyPass->GetGunPtr()->Shot();
						m_nCntShotFrame = 0;
					}
					break;
				}
			}
		}
	}
}