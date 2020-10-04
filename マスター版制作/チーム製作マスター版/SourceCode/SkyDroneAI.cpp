// =====================================================================================================================================================================
//
// skydroneのAIの処理 [skydroneAI.cpp]
// Author : FujiwaraMasato
//
// =====================================================================================================================================================================
#include "skydroneAI.h"		// インクルードファイル
#include "renderer.h"
#include "WeakEnemy.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "map.h"
#include "gun.h"
#include "ModelSet.h"
#include "texture.h"
#include "particle.h"
#include "enemy.h"
#include "boss_one.h"

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
CSkyDroneAI::CSkyDroneAI()
{
	m_pEnemyPass = nullptr;
	m_nRotCnt = 0;
	m_nWorkTime = 0;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CSkyDroneAI::~CSkyDroneAI()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CSkyDroneAI::Init(void)
{
	m_nCntShotFrame = 0;						// 撃つまでのカウント
	m_nCntMoveStopFrame = 0;					// 止まるまでのカウント
	m_StateAI = DRONEAI_STATE::APPEARANCE;		// AIの状態
	m_LeaveState = DRONEAI_LEAVESTATE::FIRST;
	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CSkyDroneAI::Uninit(void)
{
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CSkyDroneAI::Update(void)
{
	// ドローンのAIの状態
	SkyDroneAIState();

	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		// エネミーのポインタ取得
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);

		if (pEnemy != nullptr)
		{
			if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
			{
				CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

				if (pBoss_One->GetCharacterState() == CBoss_One::CHARACTER_STATE_DEATH)
				{
					m_pEnemyPass->SetDieFlag(true);
				}
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CSkyDroneAI::Draw(void)
{
}

// =====================================================================================================================================================================
//
// デバッグ情報表記
//
// =====================================================================================================================================================================
void CSkyDroneAI::DebugInfo(void)
{
}

// =====================================================================================================================================================================
//
// AIの生成
//
// =====================================================================================================================================================================
CSkyDroneAI * CSkyDroneAI::CreateAI(CWeakEnemy *pEnemy)
{
	// 変数
	CSkyDroneAI	*pSkyDroneAI;

	// メモリの確保
	pSkyDroneAI = new CSkyDroneAI();

	// 初期化
	pSkyDroneAI->Init();

	// エネミーの情報
	pSkyDroneAI->m_pEnemyPass = pEnemy;

	return pSkyDroneAI;
}

// =====================================================================================================================================================================
//
// AIの状態取得
//
// =====================================================================================================================================================================
CSkyDroneAI::DRONEAI_STATE CSkyDroneAI::GetAIType(void)
{
	return m_StateAI;
}

// =====================================================================================================================================================================
//
// ドローンのAIの状態
//
// =====================================================================================================================================================================
void CSkyDroneAI::SkyDroneAIState()
{
	if (m_StateAI == DRONEAI_STATE::STOP ||
		m_StateAI == DRONEAI_STATE::MOVEROT)
	{
		// 活動開始から加算
		m_nWorkTime++;
	}

	// プレイヤーのポインタ取得
	CPlayer *pPlayer[MAX_CONTROLLER];

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		pPlayer[nCnt] = CManager::GetBaseMode()->GetPlayer((TAG)nCnt);
	}

	switch (m_StateAI)
	{
	case CSkyDroneAI::DRONEAI_STATE::APPEARANCE:

		if (m_pEnemyPass->GetPosition().y >= 400.0f)
		{
			m_pEnemyPass->GetPosition().y -= 1.5f;
 			if (m_pEnemyPass->GetPosition().y <= 400.0f)
			{
				m_pEnemyPass->GetPosition().y = 400.0f;
				m_StateAI = DRONEAI_STATE::STOP;
			}

			m_pEnemyPass->SetPosition(m_pEnemyPass->GetPosition());
		}

		break;
	case CSkyDroneAI::DRONEAI_STATE::STOP:

		if (m_nWorkTime >= 30)
		{
			m_StateAI = DRONEAI_STATE::MOVEROT;
		}

		break;
	case CSkyDroneAI::DRONEAI_STATE::MOVEROT:
		// 左右移動
		float temp;
		m_nAngle += 2;

		temp = cosf(m_nAngle*D3DX_PI / 200);
		m_pEnemyPass->GetPosition().x += temp *3.0f;

		if (m_nWorkTime >= (180 + 300))
		{
			m_nAngle = 0;
			m_StateAI = DRONEAI_STATE::LEAVE;
		}
		break;

	case CSkyDroneAI::DRONEAI_STATE::LEAVE:

		// 左右移動
		float Temp;
		m_nAngle += 2;
		Temp = sinf(m_nAngle*D3DX_PI / 200);
		m_pEnemyPass->GetPosition().y += Temp *5.0f;

		if (m_nAngle >= 240)
		{
			m_pEnemyPass->SetDieFlag(true);
		}

		break;
	default:
		break;
	}

	// 通常行動時にのみ攻撃
	if (m_StateAI != DRONEAI_STATE::APPEARANCE &&
		m_StateAI != DRONEAI_STATE::STOP &&
		m_StateAI != DRONEAI_STATE::LEAVE)
	{
		// カウントアップ
		m_nCntShotFrame++;

		// 2人プレイの時
		if (CPlayer::GetTwoPPlayFlag())
		{
			// 二秒ごとに弾を撃つ
			if (m_nCntShotFrame >= 100)
			{
				if (m_nCntShotFrame > 100)
				{
					if (CHossoLibrary::Random(10) >= 0)
					{
						if (pPlayer[0])
						{
							D3DXVECTOR3 RandPos = pPlayer[0]->GetPosition();

							RandPos.x += CHossoLibrary::Random(150.0f);

							//射撃方向の計算
							D3DXVECTOR3 ShotVec = RandPos - m_pEnemyPass->GetPosition();
							//値の正規化
							D3DXVec3Normalize(&ShotVec, &ShotVec);
							//撃つ向きの設定
							m_pEnemyPass->GetGunPtr()->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, atan2f(-ShotVec.x, ShotVec.y)));
						}
					}
					else
					{
						if (pPlayer[1])
						{
							D3DXVECTOR3 RandPos = pPlayer[1]->GetPosition();

							RandPos.x += CHossoLibrary::Random(150.0f);

							//射撃方向の計算
							D3DXVECTOR3 ShotVec = RandPos - m_pEnemyPass->GetPosition();
							//値の正規化
							D3DXVec3Normalize(&ShotVec, &ShotVec);
							//撃つ向きの設定
							m_pEnemyPass->GetGunPtr()->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, atan2f(-ShotVec.x, ShotVec.y)));
						}
					}

					// 発射
					m_pEnemyPass->GetGunPtr()->Shot();
					m_nCntShotFrame = 0;
				}
				else
				{
					//パーティクル発生 軌跡みたいな
					CParticle::CreateFromText(m_pEnemyPass->GetPosition(), m_pEnemyPass->GetRot(), CParticleParam::EFFECT_CHARGE);
				}
			}
		}
		// 1人プレイの時
		else
		{
			// 二秒ごとに弾を撃つ
			if (m_nCntShotFrame >= 120)
			{
				if (m_nCntShotFrame > 120)
				{
					if (pPlayer[0])
					{
						D3DXVECTOR3 RandPos = pPlayer[0]->GetPosition();

						RandPos.x += CHossoLibrary::Random(150.0f);

						//射撃方向の計算
						D3DXVECTOR3 ShotVec = RandPos - m_pEnemyPass->GetPosition();
						//値の正規化
						D3DXVec3Normalize(&ShotVec, &ShotVec);
						//撃つ向きの設定
						m_pEnemyPass->GetGunPtr()->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, atan2f(-ShotVec.x, ShotVec.y)));
					}

					// 発射
					m_pEnemyPass->GetGunPtr()->Shot();
					m_nCntShotFrame = 0;
				}
				else
				{
					//パーティクル発生 軌跡みたいな
					CParticle::CreateFromText(m_pEnemyPass->GetPosition(), m_pEnemyPass->GetRot(), CParticleParam::EFFECT_CHARGE);
				}
			}
		}
	}
}