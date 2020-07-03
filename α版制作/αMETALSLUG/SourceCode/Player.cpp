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
#define ATTACK_DAMAGE_ENEMY		(50)			// エネミーへのダメージ

CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
	m_pPrisoner = nullptr;
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
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();
	m_bAttack_Enemy = false;
	m_bAttack_Prisoner = false;
	 // 銃の生成
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_RHAND)->GetMatrix());
	// 銃の弾の種類
	m_pGun->GetBulletType() = CGun::TYPE_PLAYER;
	// ナイフの生成
	m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());

	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(PLAYER_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->SetType(CCollision::COLLISION_PLAYER);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

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
	// 銃を撃つ or 近接攻撃
	if (key->GetKeyboardTrigger(DIK_P))
	{

		CPrisoner	*pPrisoner = GetCollision()->ForPlayer_PrisonerCollision();

		// ポインタがnullじゃなかった時
		if (pPrisoner != nullptr)
		{
			// 銃を撃てる状態だった時
			if (m_bAttack_Enemy == false && m_bAttack_Prisoner == false)
			{// 銃発射処理
				m_pGun->Shot(GetShotDirection());
			}
			// 捕虜が判定可能な状態だった時
			else if (pPrisoner->GetPrisonerState() != CPrisoner::PRISONER_STATE_STAY)
			{
				m_pGun->Shot(GetShotDirection());
			}
		}
		// 捕虜がいない時は通常通り弾を撃つ
		else
		{
			m_pGun->Shot(GetShotDirection());
		}

		// 近接攻撃をする状態だった時
		if (m_bAttack_Enemy == true)
		{// 近接攻撃
		 // エネミーとの接触判定 捕虜の状態を変える
			CEnemy		*pEnemy		= GetCollision()->ForPlayer_EnemyCollision();

			if (pEnemy != nullptr)
			{
				// 近接攻撃
				SetMotion(CCharacter::PLAYER_MOTION_ATTACK01);
				m_pKnife->StartMeleeAttack();
				// エネミーへダメージ
				pEnemy->AddDamage(ATTACK_DAMAGE_ENEMY);
			}
		}

		// 近接判定が出ている時は近接攻撃をする
		if (m_bAttack_Prisoner == true)
		{// 近接攻撃
		 // 捕虜との接触判定 捕虜の状態を変える
			CPrisoner	*pPrisoner = GetCollision()->ForPlayer_PrisonerCollision();

			// ポインタがnullじゃなかった時
			if (pPrisoner != nullptr)
			{
				// 捕虜が判定可能な状態だった時
				if (pPrisoner->GetPrisonerState() == CPrisoner::PRISONER_STATE_STAY)
				{
					// 近接攻撃
					SetMotion(CCharacter::PLAYER_MOTION_ATTACK01);
					// ナイフ処理
					m_pKnife->StartMeleeAttack();
					// 捕虜の状態をアイテムを落とす状態にする
					pPrisoner->SetPrisonerState(CPrisoner::PRISONER_STATE_DROPITEM);
					// この捕虜のポインタは取得できないようにする
					pPrisoner->SetPrisonerUseFlag(true);
				}
			}
		}
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
	if (GetCollision() != nullptr)
	{
		// 座標の更新 posとposold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());

		// エネミーととの判定
		if (GetCollision()->ForPlayer_EnemyCollision(ATTACK_PENETRATION))
		{
			// 近接攻撃可能にする
			m_bAttack_Enemy = true;
		}
		else
		{
			// 近接攻撃が無効になる
			m_bAttack_Enemy = false;
		}

		// 捕虜との判定
		if (GetCollision()->ForPlayer_PrisonerCollision(ATTACK_PENETRATION) == true)
		{
			// 近接攻撃可能にする
			m_bAttack_Prisoner = true;
		}
		else
		{
			// 近接攻撃が無効になる
			m_bAttack_Prisoner = false;
		}



		// 障害物との判定
		if (GetCollision()->ForPlayer_ObstacleCollision())
		{
			// ジャンプフラグを可能にする
			CCharacter::SetJump(true);
		}

		// アイテムとの判定
		if (GetCollision()->ForPlayer_ItemCollision())
		{
		}
	}

	// マップのポインタ取得
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// マップモデルが存在した時
	if (pMap != nullptr)
	{
		// レイの判定
		if (GetCollision()->RayBlockCollision(pMap))
		{
			// ジャンプすることを承認する
			SetJump(true);
		}
		else
		{
			// ジャンプすることを承認しない
			SetJump(false);
		}
	}

	// 攻撃モーションから別のモーションになった時
	if (GetMotionType() != CCharacter::PLAYER_MOTION_ATTACK01)
	{
		if (m_bAttack_Enemy == false && m_bAttack_Prisoner == false)
		{
			m_pKnife->EndMeleeAttack();
		}
	}

	// 特定のボタンを押した時に歩きモーションに変更
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
