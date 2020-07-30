//=============================================================================
// AI処理 [BossAI.cpp] Hanzawa
//=============================================================================
#include "BossAI.h"
#include "renderer.h"
#include "inputKeyboard.h"
#include "Boss.h"
#include "Player.h"
#include "manager.h"
#include "BaseMode.h"
#include "collision.h"
#include "gun.h"
#define CENTER_POS		(D3DXVECTOR3(0.0f,400.0f,0.0f))
#define RIGHT_POS		(D3DXVECTOR3(300.0f,200.0f,0.0f))
#define LEFT_POS		(D3DXVECTOR3(-300.0f,200.0f,0.0f))
#define MOVE_SPEED		(0.1f)
#define MAX_RECASTTIME (60)
CBossAI::CBossAI()
{
}

CBossAI::~CBossAI()
{
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBossAI::Init(void)
{
	m_recast = 60;
	m_castcount = 0;
	m_LaserRandom = 0;
	m_bShot = false;
	m_random = 0;
	m_BossAItype = AI_NONE;
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
void CBossAI::Uninit(void)
{
}

//=============================================================================
// 更新処理
//=============================================================================
void CBossAI::Update(void)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	D3DXVECTOR3 Distance;

	if (pBossPass != nullptr || pPlayer != nullptr)
	{
		D3DXVECTOR3 MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_BossAItypeOld = m_BossAItype;	//前回の攻撃の格納
		if (m_bShot == false)
		{
		m_castcount++;
		}
		else
		{
		m_castcount = 0;
		}
		if (m_castcount == m_recast && m_bReStartFlag == false)
		{
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30フレーム分のリキャスト
			m_random = (rand() % AI_MAX);				//行動のランダム
			m_BossAItype = (AI_BOSS_STATE)m_random;				//ランダムの形式をAI_STATEに変換
			m_castcount = 0;
			m_bShot = false;
		}
		else if (m_bReStartFlag == true)
		{
			m_random = (rand() % AI_MAX);				//行動のランダム
			m_BossAItype = (AI_BOSS_STATE)m_random;				//ランダムの形式をAI_STATEに変換
			m_recast = (rand() % MAX_RECASTTIME) + 30;	//30フレーム分のリキャスト
			if (m_BossAItype != m_BossAItypeOld)
			{
				m_bReStartFlag = false;
				m_castcount = 0;
				m_AttackCnt = 0;
				m_AttackCastCnt = 0;
				m_Attacks = 0;
				m_Attack = false;
				m_bShot = false;
			}
		}
	}
	CDebugProc::Print("ボスのステート：%d\n", m_BossAItype);
	CDebugProc::Print("ボスのキャストタイム：%d\n", m_castcount);
	CDebugProc::Print("ボスのリキャストタイム：%d\n", m_recast);

	UpdateMoveAI();
	UpdateAttackAI();
}
//=============================================================================
// 移動AI更新処理
//=============================================================================
void CBossAI::UpdateMoveAI(void)
{
	D3DXVECTOR3 MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	if (pBossPass != nullptr || pPlayer != nullptr)
	{
		if (AI_CENTER == m_BossAItype) //中央
		{
			MoveVec = CENTER_POS - pBossPass->GetPosition();
			//方向の正規化
			if (m_bShot == false )
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
		}
		else if (AI_LEFT == m_BossAItype)//左
		{
			MoveVec = LEFT_POS - pBossPass->GetPosition();
			//方向の正規化
			if (m_bShot == false)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
		}
		else if (AI_RIGHT == m_BossAItype)//右
		{
			MoveVec = RIGHT_POS - pBossPass->GetPosition();
			//方向の正規化
			if (m_bShot == false)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
		}
		else if (AI_ONPLAYER == m_BossAItype)
		{
			m_MoveCnt++;
			MoveVec = pPlayer->GetPosition() - pBossPass->GetPosition();
			//方向の正規化
			if (m_bShot == false && m_MoveCnt < 30)
			{
				pBossPass->GetPosition() += D3DXVECTOR3(MoveVec.x*MOVE_SPEED,0.0f,0.0f);
			}
			else if (m_bShot == false && m_MoveCnt == 35)
			{
				m_MoveCnt = 0;
				m_BossAItype = AI_NONE;
			}
		}
	}
}
//=============================================================================
// 攻撃AI更新処理
//=============================================================================
void CBossAI::UpdateAttackAI(void)
{
	D3DXVECTOR3 MoveVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	float fAngle = 0.0f;
	if (pBossPass != nullptr || pPlayer != nullptr)
	{
		if (AI_TRACKING == m_BossAItype)//プレイヤー追従弾
		{
			m_ShotVec = pPlayer->GetPosition() - pBossPass->GetPosition();//射撃方向の計算
			D3DXVec3Normalize(&m_ShotVec, &m_ShotVec);//値の正規化
			//撃つ向きの設定
			pBossPass->GetGun()->SetShotVec(D3DXVECTOR3(m_ShotVec.x, m_ShotVec.y, m_ShotVec.z));

			m_AttackCastCnt++;
			m_bShot = true;
			if (m_AttackCastCnt == 60)//攻撃に入るまでの時間
			{
				m_Attack = true;//攻撃を可能にする
			}
			//攻撃が可能になったら
			if (m_Attack == true)
			{
				m_AttackCnt++;
				//120フレームより小さいとき射撃
				if (m_AttackCnt < 60 && m_Attacks < 3)
				{
					pBossPass->GetGun()->Shot();
				}
				else if (m_AttackCnt == 140)
				{
					m_AttackCnt = 0;
					m_Attacks++;
				}
				//120フレームかつ攻撃回数に達したら初期化
				if (m_AttackCnt > 120 && m_Attacks >= 3)
				{
					SetRestartFlag(true);
				}
			}
		}
	
		else if (AI_DIFFUSION == m_BossAItype)//拡散射撃
		{
			m_ShotVec = pPlayer->GetPosition() - pBossPass->GetPosition();//射撃方向の計算
			D3DXVec3Normalize(&m_ShotVec, &m_ShotVec);//値の正規化
			fAngle = float(rand() % 157) / 100.0f - float(rand() % 157) / 100.0f;
			//撃つ向きの設定
			pBossPass->GetGun()->SetShotVec(D3DXVECTOR3 (-sinf(fAngle)*1,
				-cosf(fAngle)*cosf(fAngle) *1,
				0.0f));

			m_AttackCastCnt++;
			m_bShot = true;
			if (m_AttackCastCnt == 60)//攻撃に入るまでの時間
			{
				m_Attack = true;//攻撃を可能にする
			}
			//攻撃が可能になったら
			if (m_Attack == true)
			{
				m_AttackCnt++;
				//120フレームより小さいとき射撃
				if (m_AttackCnt < 180)
				{
					pBossPass->GetGun()->Shot();
				}
				//120フレームになったら初期化
				else if (m_AttackCnt > 230)
				{
					SetRestartFlag(true);
				}
			}
		}
		else if (AI_LASER == m_BossAItype)//レーザー
		{
			m_ShotVec = D3DXVECTOR3(0.0f,-1.0f,0.0f);//射撃方向の計算
			//撃つ向きの設定
			pBossPass->GetGun()->SetShotVec(D3DXVECTOR3(m_ShotVec.x, m_ShotVec.y, m_ShotVec.z));
			m_AttackCastCnt++;
			m_bShot = true;
			if (m_AttackCastCnt == 60)//攻撃に入るまでの時間
			{
				m_Attack = true;//攻撃を可能にする
				m_LaserRandom = (rand() % 2);
			}
			//攻撃が可能になったら
			if (m_Attack == true)
			{
				m_AttackCnt++;
				if (m_LaserRandom == 0)
				{
					if (m_AttackCnt > 30)
					{
						pBossPass->GetPosition().x += 3;
						pBossPass->GetGun()->Shot();
					}
					else
					{
						MoveVec = LEFT_POS - pBossPass->GetPosition();
						pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
					}
				}
				else
				{
					if (m_AttackCnt > 30)
					{
						pBossPass->GetPosition().x -= 3;
						pBossPass->GetGun()->Shot();
					}
					else
					{
						MoveVec = RIGHT_POS - pBossPass->GetPosition();
						pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
					}
				}
				//180フレームになったら初期化(3秒)
				if (m_AttackCnt > 180)
				{
					SetRestartFlag(true);
				}
			}
		}
	}
	CDebugProc::Print("ボスの攻撃回数   :%d\n", m_Attacks);
}
//=============================================================================
// 描画
//=============================================================================
void CBossAI::Draw(void)
{
}
//=============================================================================
// デバッグ
//=============================================================================
void CBossAI::DebugInfo(void)
{
}
D3DXVECTOR3 CBossAI::GetTrackingShotRot(void)
{
	return m_ShotVec;
}
//=============================================================================
// AIのクリエイト
//=============================================================================
CBossAI * CBossAI::CreateAI(CBoss *pBoss)
{
	CBossAI*pBossAI;
	pBossAI = new CBossAI();
	pBossAI->Init();
	pBossAI->pBossPass = pBoss;
	return pBossAI;
}
//=============================================================================
// AIの攻撃タイプ取得
//=============================================================================
CBossAI::AI_BOSS_STATE CBossAI::GetBossAIType(void)
{
	return m_BossAItype;
}
//=============================================================================
// 
//=============================================================================
bool CBossAI::GetShot(void)
{
	return m_bShot;
}
void CBossAI::SetShot(bool shot)
{
	m_bShot = shot;
}
void CBossAI::SetRestartFlag(bool flag)
{
	m_bReStartFlag = flag;
}
//=============================================================================
// AIの行動タイプ設定
//=============================================================================
void CBossAI::SetBossAI(AI_BOSS_STATE attack)
{
	m_BossAItype = attack;
}
