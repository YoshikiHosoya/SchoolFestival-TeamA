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
#include "XInputPad.h"
#include "item.h"
#include "Obstacle.h"
#include "grenade.h"
#include "prisoner.h"
#include "Knife.h"
//====================================================================
//マクロ定義
//====================================================================
#define PLAYER_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f)) //敵のサイズ
// 貫通させるかのフラグ
#define ATTACK_PENETRATION		(true)			// プレイヤーの判定が貫通するかどうか


CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
	m_pCollision = nullptr;
	m_bCloseRangeAttack = false;
	m_pPrisoner = nullptr;
}

CPlayer::~CPlayer()
{
#ifdef _DEBUG

	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
#endif // _DEBUG

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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_Attack = false;
	 // 銃の生成
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_RHAND)->GetMatrix());
	// 銃の弾の種類
	m_pGun->GetBulletType() = CGun::TYPE_PLAYER;
	// ナイフの生成
	m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(PLAYER_SIZE);
	m_pCollision->SetMove(&GetMove());
	m_pCollision->SetType(CCollision::COLLISION_PLAYER);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

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
		if (m_bCloseRangeAttack != true)
		{// 銃発射処理
			m_pGun->Shot(GetShotDirection());
		}
		else
		{// 近接攻撃
			// 捕虜の状態変化
			//if (m_pPrisoner->GetPrisonerState() == CPrisoner::PRISONER_STATE_STAY)
			//{
			//	m_pPrisoner->SetPrisonerState(CPrisoner::PRISONER_STATE_DROPITEM);
			//}

			//// 捕虜の当たり判定削除
			//if (m_pPrisoner->GetCollision() != nullptr)
			//{
			//}
			SetMotion(CCharacter::PLAYER_MOTION_ATTACK01);
			m_pKnife->StartMeleeAttack();
			m_Attack = true;

		}
		//// 銃発射処理
		//m_pGun->Shot(GetShotDirection());
	}
	// グレネードを投げる
	if (key->GetKeyboardTrigger(DIK_O))
	{
		// グレネード生成
		CGrenade::Create(GetShotDirection() , GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
		SetMotion(CCharacter::PLAYER_MOTION_GRENADE);
	}
	if (key->GetKeyboardPress(DIK_W))
	{
		SetCharacterDirection(CHARACTER_UP);
	}

	// Aの処理
	if (key->GetKeyboardPress(DIK_A))
	{
		CPlayer::Move(0.5f, 0.5f);
		if (key->GetKeyboardPress(DIK_W))
		{
			SetCharacterDirection(CHARACTER_UP);
		}
		else
		{
		SetCharacterDirection(CHARACTER_LEFT);
		}
	}
	// Dの処理
	else if (key->GetKeyboardPress(DIK_D))
	{
		CPlayer::Move(-0.5f, -0.5f);
		if (key->GetKeyboardPress(DIK_W))
		{
			SetCharacterDirection(CHARACTER_UP);
		}
		else
		{
		SetCharacterDirection(CHARACTER_RIGHT);
		}
	}


	//ジャンプしたときの下向発射
	if (key->GetKeyboardPress(DIK_S) && GetJump() == false)
	{
		SetCharacterDirection(CHARACTER_DOWN);
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
	if (m_pCollision != nullptr)
	{
		// 座標の更新 posとposold
		m_pCollision->SetPos(&GetPosition());
		m_pCollision->SetPosOld(&GetPositionOld());

		// エネミーとの判定
		if (m_pCollision->ForPlayer_EnemyCollision(ATTACK_PENETRATION))
		{
			CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
			if (pEnemy != nullptr)
			{
				if (m_pCollision->CharCollision2D(pEnemy->GetCollision()))
				{
					CDebugProc::Print("\n時機が敵に当たったよ！\n");
					m_bCloseRangeAttack = true;
				}
				else
				{
					CDebugProc::Print("\n時機が敵に当たってないよ！ \n");
					m_bCloseRangeAttack = false;
				}
			}
		}
			// 近接攻撃可能にする
			m_bCloseRangeAttack = true;
		}
		else
		{
			// 近接攻撃が無効になる
			m_bCloseRangeAttack = false;
		}

		// 障害物との判定
		if (m_pCollision->ForPlayer_ObstacleCollision(false))
		{
			// ジャンプフラグを可能にする
			CCharacter::SetJump(true);
		}
			CObstacle *pObstacle = CManager::GetBaseMode()->GetMap()->GetObstacle(nCntObst);
			if (pObstacle != nullptr)
			{
				if (m_pCollision->BlockCollision2D(pObstacle->GetCollision()))
				{
					CCharacter::SetJump(false);
					CDebugProc::Print("\n時機が障害物に当たったよ！\n");

				}
				else
				{
					CDebugProc::Print("\n時機が障害物に当たってないよ！ \n");
				}
			}
		}

		// 捕虜との判定
		if (m_pCollision->ForPlayer_PrisonerCollision(ATTACK_PENETRATION))
		{
			// 近接攻撃を可能にする
			m_bCloseRangeAttack = true;
		}
		else
		{
			// 近接攻撃が無効になる
			m_bCloseRangeAttack = false;
		}

		// アイテムとの判定
		if (m_pCollision->ForPlayer_ItemCollision(false))
		{

		}
	}
	if (GetMotionType() != CCharacter::PLAYER_MOTION_ATTACK01)
	{
		m_Attack = false;
		if (m_Attack == false)
		{
			m_pKnife->EndMeleeAttack();
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
	if (m_bCloseRangeAttack == true)
	{
		CDebugProc::Print("近接攻撃：可能\n");
	}
	else
	{
		CDebugProc::Print("近接攻撃：不可能\n");
	}
	if (m_Attack == true)
	{
		CDebugProc::Print("攻撃中\n");
	}
	else
	{
		CDebugProc::Print("攻撃してない\n");
	}
}
//====================================================================
//モデルのクリエイト
//====================================================================
CPlayer *CPlayer::Create(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->Init();
	return pPlayer;
}
//====================================================================
//デフォルトモーションに戻る
//====================================================================
bool CPlayer::DefaultMotion(void)
{
	SetMotion(CCharacter::PLAYER_MOTION_NORMAL);
	return true;
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
	SetMotion(PLAYER_MOTION_WALK);
}
