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
#define CENTER_POS		(D3DXVECTOR3(0.0f,400.0f,0.0f))
#define RIGHT_POS		(D3DXVECTOR3(300.0f,200.0f,0.0f))
#define LEFT_POS		(D3DXVECTOR3(-300.0f,200.0f,0.0f))
#define MOVE_SPEED		(0.1f)
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
	m_bShot = false;
	m_random = 0;
	m_AItypeAttack = AI_ATTACK_NONE;
	m_AItypeMove = AI_MOVE_NONE;
	m_ShotVec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

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
		CKeyboard *key;
		key = CManager::GetInputKeyboard();
		if (key->GetKeyboardTrigger(DIK_8))
		{
			m_AItypeMove = AI_CENTER;
		}
		if (key->GetKeyboardTrigger(DIK_7))
		{
			m_AItypeMove = AI_LEFT;
		}
		if (key->GetKeyboardTrigger(DIK_9))
		{
			m_AItypeMove = AI_RIGHT;
		}
		if (key->GetKeyboardTrigger(DIK_0))
		{
			m_AItypeMove = AI_MOVE_NONE;
			m_AItypeAttack = AI_ATTACK_NONE;
		}
		if (key->GetKeyboardTrigger(DIK_B))
		{
			m_AItypeAttack = AI_TRACKING;
		}
			m_AItypeAttackOld = m_AItypeAttack;	//前回の攻撃の格納
		m_AItypeMoveOld = m_AItypeMove;		//前回の移動の格納
		//移動関連
		switch (m_AItypeMove)
		{
		case AI_CENTER: //中央
			MoveVec = CENTER_POS - pBossPass->GetPosition();
			//方向の正規化
			if (pBossPass->GetPosition() != CENTER_POS)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
			else if (pBossPass->GetPosition() == CENTER_POS)
			{
				m_AItypeMove = AI_MOVE_NONE;
			}
			break;
		case AI_LEFT://左
			MoveVec = LEFT_POS - pBossPass->GetPosition();
			//方向の正規化
			if (pBossPass->GetPosition() != LEFT_POS)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
			else if (pBossPass->GetPosition() == LEFT_POS)
			{
				m_AItypeMove = AI_MOVE_NONE;
			}
			break;
		case AI_RIGHT://右
			MoveVec = RIGHT_POS - pBossPass->GetPosition();
			//方向の正規化
			if (pBossPass->GetPosition() != RIGHT_POS)
			{
				pBossPass->GetPosition() += MoveVec*MOVE_SPEED;
			}
			else if (pBossPass->GetPosition() == RIGHT_POS)
			{
				m_AItypeMove = AI_MOVE_NONE;
			}
			break;
		}
		//攻撃関連
		switch (m_AItypeAttack)
		{
		case AI_TRACKING://プレイヤー追従弾
			Distance = pPlayer->GetPosition()-pBossPass->GetPosition() ;//射撃方向の計算
			//D3DXVec3Normalize(&Distance, &Distance);//値の正規化
			m_ShotVec = D3DXVECTOR3(atan2f(Distance.y, Distance.z), atan2f(-Distance.x, -Distance.z), atan2f(Distance.x, Distance.z));		//初期角度を求める


			//pBossPass->GetPosition() += m_ShotVec;
			CDebugProc::Print("ボス射撃向きX：%2f\nボス射撃向きY：%2f\n", m_ShotVec.y, m_ShotVec.z);
			break;
		case AI_DIFFUSION://拡散射撃

			break;
		case AI_LASER://レーザー
			break;
		}
	}
	CDebugProc::Print("ボスの移動ステート：%d\n", m_AItypeMove);
}
//=============================================================================
// タイトル画面
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
CBossAI::AI_STATE_ATTACK CBossAI::GetAITypeAttack(void)
{
	return m_AItypeAttack;
}

bool CBossAI::GetShot(void)
{
	return m_bShot;
}
