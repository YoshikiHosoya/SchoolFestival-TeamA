//====================================================================
// プレイヤー処理 [player.cpp]: NORI
//====================================================================
#include "Player.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "fade.h"
#include "Xinput.h"
#include "handgun.h"
#include "heavymachinegun.h"
#include "gun.h"
#include "collision.h"
#include "BaseMode.h"
#include "manager.h"
#include "enemy.h"
#include "map.h"
#include"XInputPad.h"

CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
	m_pCollision = NULL;
}

CPlayer::~CPlayer()
{
}
//====================================================================
//初期化
//====================================================================
HRESULT CPlayer::Init(void)
{
	//キャラの初期化
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_PLAYER);
	SetCharacterType(CCharacter::CHARACTER_TYPE_PLAYER);
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	m_Attack = false;
	m_ShotRot = D3DXVECTOR3(0.0f, 0.5f, 0.0f);

	 // 銃の生成
	m_pGun = CGun::Create(CCharacter::GetMtxWorld());
	// 銃の弾の種類
	m_pGun->GetBulletType() = CGun::TYPE_PLAYER;

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(D3DXVECTOR3(50.0f, 100.0f, 0.0f));
	m_pCollision->SetMove(&GetMove());
	m_pCollision->SetType(CCollision::OBJTYPE_PLAYER);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CPlayer::Uninit(void)
{
	CCharacter::Uninit();
}
//====================================================================
//更新
//====================================================================
void CPlayer::Update(void)
{
	float rot = 0.0f;
	static bool trigger = false;
	static bool trigger2 = false;
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	//キーボード処理
	// 銃を撃つ
	if (key->GetKeyboardTrigger(DIK_P))
	{
		// 銃発射処理
		m_pGun->Shot(m_ShotRot);
	}

	// Aの処理
	if (key->GetKeyboardPress(DIK_A))
	{
		CPlayer::Move(0.5f, 0.5f);
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = 0.5f * D3DX_PI;
		SetCharacterDirection(CHARACTER_LEFT);
	}
	// Dの処理
	else if (key->GetKeyboardPress(DIK_D))
	{
		CPlayer::Move(-0.5f, -0.5f);
		m_ShotRot.x = 0.0f;
		m_ShotRot.y = -0.5f * D3DX_PI;
		SetCharacterDirection(CHARACTER_RIGHT);
	}

	else if (key->GetKeyboardPress(DIK_W))
	{
		SetCharacterDirection(CHARACTER_UP);
		m_ShotRot.y = 0.0f;
		m_ShotRot.x = 0.5f * D3DX_PI;
	}
	//ジャンプしたときの下向発射
	if (key->GetKeyboardPress(DIK_S) && GetJump() == false)
	{
		SetCharacterDirection(CHARACTER_DOWN);
		m_ShotRot.y = 0.0f;
		m_ShotRot.x = -0.5f * D3DX_PI;
	}
	if (GetCharacterDirection() == CHARACTER_DOWN && GetJump() == true)
	{
		if (GetRot().y > 1.5f)
		{
			m_ShotRot.x = 0.0f;
			m_ShotRot.y = 0.5f * D3DX_PI;
			SetCharacterDirection(CHARACTER_LEFT);
		}
		else if (GetRot().y < -1.5f)
		{
			m_ShotRot.x = 0.0f;
			m_ShotRot.y = -0.5f * D3DX_PI;
			SetCharacterDirection(CHARACTER_RIGHT);
		}
	}

	//デバッグモードの切り替え
	if (key->GetKeyboardTrigger(DIK_F2))
	{
		trigger ^= 1;
	}
	if (trigger == true)
	{
		m_DebugState = DEBUG_CREATE_MAP;
		SetGravity(false);
	}
	else
	{
		m_DebugState = DEBUG_NORMAL;
		SetGravity(true);
	}
	if (m_DebugState != DEBUG_NORMAL)
	{
	}
	//ジャンプ
	if (key->GetKeyboardTrigger(DIK_SPACE) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
	{
		GetMove().y += 27;
	}

	else if (key->GetKeyboardPress(DIK_SPACE) && m_DebugState != DEBUG_NORMAL)
	{
		GetMove().y += 2;
	}

	if (key->GetKeyboardTrigger(DIK_1))
	{
		SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	}
	if (key->GetKeyboardTrigger(DIK_2))
	{
		SetMotion(CCharacter::PLAYER_MOTION_WALK);
	}

	// 当たり判定
	if (m_pCollision != NULL)
	{
		// 座標の更新 posとposold
		m_pCollision->SetPos(&GetPosition());

		// 当たり判定 相手がエネミーだったら
		// 敵の総数分
		for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
		{
			CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
			if (pEnemy != NULL)
			{
				/*if (m_pCollision->Collision2D(pEnemy->GetCollision()))
				{
					CDebugProc::Print("\n時機が敵に当たったよ！\n");
				}
				else
				{
					CDebugProc::Print("\n時機が敵に当たってないよ！ \n");
				}*/
			}
		}

	}
	if (CHossoLibrary::PressAnyButton())
	{
		SetMotion(CCharacter::PLAYER_MOTION_WALK);
	}
	CCharacter::Update();
}
//====================================================================
//描画
//====================================================================
void CPlayer::Draw(void)
{
	CCharacter::Draw();
}
//====================================================================
//デバッグ
//====================================================================
void CPlayer::DebugInfo(void)
{
	CDebugProc::Print("プレイヤーの向き%2f", GetRot().y);
}
//====================================================================
//モデルのクリエイト
//====================================================================
CPlayer *CPlayer::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRendere()->GetDevice();
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->Init();
	return pPlayer;
}
void CPlayer::DefaultMotion(void)
{
	SetMotion(CCharacter::PLAYER_MOTION_NORMAL);
}
//====================================================================
//デバッグステータスの取得
//====================================================================
CPlayer::DEBUG_STATE CPlayer::GetDebugState(void)
{
	return m_DebugState;
}
//====================================================================
//移動
//====================================================================
void CPlayer::Move(float move, float fdest)
{
	GetMove().x += sinf(move * -D3DX_PI) * 1.0f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.0f;
	GetRotDest().y = fdest *  D3DX_PI;
}
