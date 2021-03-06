// =====================================================================================================================================================================
//
// 焼夷弾の処理 [Incendiary.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "incendiary.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "texture.h"
#include "particle.h"
#include "player.h"
#include "boss_one.h"
#include "BaseMode.h"
#include "map.h"
#include "enemy.h"
#include "ModelSet.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define INCENDIARY_GRAVITY				(0.15f)								// 焼夷弾の重力
#define INCENDIARY_GRAVITY_BASE			(1.0f)								// 焼夷弾の重力
#define MAX_FIRING_RANGE				(800.0f)							// ボスの最大射程
#define MIN_FIRING_RANGE				(300.0f)							// ボスの最低射程
#define ATTENUATION_RATE				(100.0f)							// 移動量の減衰割合
#define MIN_SPEED						(-3.5f)								// 最も遅い移動速度の基準
#define MAX_SPEED_BASE					(10.0f)								// 射程外(奥)の際の速さの基準値
#define MIN_SPEED_BASE					(4.0f)								// 射程外(前)の際の速さの基準値

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CIncendiary::CIncendiary(OBJ_TYPE type) :CBullet(type)
{
	SetObjType(OBJTYPE_BULLET);

	m_TargetPos				= ZeroVector3;
	m_PosOld = ZeroVector3;
	m_fSpeed				= 0.0f;
	m_fGravityRate			= 0.0f;
	m_fRatio				= 0.0f;
	m_fMoveAttenuationRate	= 0.0f;
	m_fVelocityBase			= 0.0f;
	m_fMoveResistance		= 0.0f;
	m_nEffectCreateCnt		= 0;
	m_bEffectCreateFlag		= false;
	m_nSavePosCount = 0;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CIncendiary::~CIncendiary()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CIncendiary::Init()
{
	// 初期化
	CBullet::Init();

	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CIncendiary::Uninit(void)
{
	// 終了
	CBullet::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CIncendiary::Update(void)
{
	// 焼夷弾本体のエフェクト
	CParticle::CreateFromText(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CParticleParam::EFFECT_INCENDIARY, CBullet::GetTag());

	//パーティクル発生 軌跡みたいな
	CParticle::CreateFromText(GetPosition(), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CParticleParam::EFFECT_SMOKERED, CBullet::GetTag());

	// 移動量の減衰
	VelocityAttenuation();

	// 更新
	CBullet::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CIncendiary::Draw(void)
{
	// 描画
	CBullet::Draw();
}

// =====================================================================================================================================================================
//
// 弾を消す処理
//
// =====================================================================================================================================================================
void CIncendiary::DeleteBullet()
{
	CBullet::DeleteBullet();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CIncendiary::BulletReaction(D3DXVECTOR3 rot)
{
}

// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CIncendiary::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 移動量の減衰
//
// =====================================================================================================================================================================
void CIncendiary::VelocityAttenuation()
{
	CBoss_One *pBoss_One = nullptr;

	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		// エネミーのポインタ取得
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
			{
				pBoss_One = (CBoss_One*)pEnemy;
			}
		}
	}

	if (pBoss_One)
	{
		// 現在の弾の移動量を取得
		float fMove_x = m_fVelocityBase;

		// 弾の移動量が0より小さい時(左向きに弾を撃つため - になっている)
		if (GetMove().x <= 0)
		{
			if (pBoss_One->GetPostureType() == CBoss_One::POSTURETYPE_STAND)
			{
				// 移動量が基準値より大きい時
				if (GetMove().x <= MIN_SPEED)
				{
					// 速度減衰
					m_fMoveResistance = fMove_x / (180.0f * m_fRatio);
				}
				//移動量が基準値を下回った時
				else if (GetMove().x >= MIN_SPEED)
				{
					// 速度減衰
					m_fMoveResistance = fMove_x / 75.0f;
				}
			}
			else
			{
				// 移動量が規定値を下回った時
				if (GetMove().y >= -6.0f)
				{
					// 速度減衰
					m_fMoveResistance = fMove_x / (270.0f * m_fRatio);
				}
				//移動量が基準値を下回った時
				else if (GetMove().y <= -6.0)
				{
					// 速度減衰
					m_fMoveResistance = fMove_x / 45.0f;
				}
			}

			// 重力
			m_fGravityRate = (m_fRatio / (INCENDIARY_GRAVITY_BASE));
		}
	}

	// 射程範囲より前側にいた際の重力
	if (m_fSpeed <= MIN_SPEED_BASE)
	{
		// 移動量が最低値を下回ったら常に最低値にする
		if (GetMove().x >= -1.0f)
		{
			m_fMoveResistance = 0.00f;
			GetMove().x = -1.0f;
		}
		// 通常時
		else
		{
			GetMove().x -= m_fMoveResistance / (0.5f * m_fRatio);
		}
		// 重力
		GetMove().y -= 0.15f;
	}
	// 通常時
	else
	{
		// 移動量が最低値を下回ったら常に最低値にする
		if (GetMove().x >= -2.0f)
		{
			m_fMoveResistance = 0.00f;
			GetMove().x = -2.0f;
		}
		// 通常時
		else
		{
			GetMove().x -= m_fMoveResistance;
		}
		// 重力
		GetMove().y -= INCENDIARY_GRAVITY * (m_fGravityRate * 0.7f);
	}
}

// =====================================================================================================================================================================
//
// 焼夷弾の生成
//
// =====================================================================================================================================================================
CIncendiary * CIncendiary::Create(D3DXVECTOR3 rot)
{
	// 変数
	CIncendiary *pIncendiary;

	// メモリの確保
	pIncendiary = new CIncendiary(OBJTYPE_BULLET);

	// 焼夷弾のパラメーター取得
	BULLET_PARAM *pBulletParam = pIncendiary->GetBulletParam(CGun::GUNTYPE_INCENDIARY);

	// 初期化
	pIncendiary->Init();

	// 弾の基準となる速度を取得
	pIncendiary->m_fSpeed = pIncendiary->GetBulletParam(CGun::GUNTYPE_INCENDIARY)->fBulletSpeed;

	// プレイヤーのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	// nullチェック
	if (pPlayer != nullptr)
	{
		// 目的座標の取得
		pIncendiary->m_TargetPos = pPlayer->GetPosition();
		// 初速を求める
		pIncendiary->CalcBulletSpeed(pIncendiary->m_TargetPos);
	}

	// 弾の移動量計算
	pIncendiary->CalcIncendiaryMove(rot, pIncendiary->m_fSpeed, pIncendiary->m_fSpeed);

	//基準となる弾の速さを設定する
	pIncendiary->m_fVelocityBase = pIncendiary->GetMove().x;

	// モデルタイプの設定
	pIncendiary->SetType(BULLET_MODEL);

	// モデルカウントの設定
	pIncendiary->SetModelID(MODEL_BULLET_SPHERE);

	return pIncendiary;
}

// =====================================================================================================================================================================
//
// 焼夷弾の初速を求める
//
// =====================================================================================================================================================================
void CIncendiary::CalcBulletSpeed(D3DXVECTOR3 Target)
{
	// プレイヤーとボスの距離
	float fDistance = 0.0f;

	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);

		if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
		{
			if (pEnemy != nullptr)
			{
				//死亡してない時
				if (pEnemy->GetCharacterState() != CCharacter::CHARACTER_STATE_DEATH)
				{
					// プレイヤーとボスの距離を求める
					fDistance = pEnemy->GetPosition().x - Target.x;
				}
			}
		}
	}

	// 射程外(奥)なら基準の速度のまま
	if (fDistance > MAX_FIRING_RANGE)
	{
		// 距離の割合を求める
		m_fRatio = MAX_FIRING_RANGE / MAX_FIRING_RANGE;
		m_fSpeed = MAX_SPEED_BASE;
	}

	// 射程外(前)だったら自分の前に弾が落ちるようにする
	else if (fDistance <= MIN_FIRING_RANGE)
	{
		// 距離の割合を求める
		m_fRatio = MAX_FIRING_RANGE / MIN_FIRING_RANGE;
		m_fSpeed = MIN_SPEED_BASE;
	}

	// 射程内なら距離から速度の割合を求める
	else
	{
		// 距離の割合を求める
		m_fRatio = MAX_FIRING_RANGE / fDistance;
		// 速度の割合を求める
		m_fSpeed = m_fSpeed / m_fRatio;
	}
}
