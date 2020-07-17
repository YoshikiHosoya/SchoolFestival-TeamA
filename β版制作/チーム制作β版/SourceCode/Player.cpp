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
#include "grenadefire.h"
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
#include "playerUI.h"
#include "playertank.h"
#include "battleplane.h"

//====================================================================
//マクロ定義
//====================================================================
#define PLAYER_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f)) //敵のサイズ
// 貫通させるかのフラグ
#define ATTACK_PENETRATION		(true)			// プレイヤーの判定が貫通するかどうか
#define ATTACK_DAMAGE_ENEMY		(50)			// エネミーへのダメージ
#define SHOT_BULLET_POS_Y		(-15.0f)		// 弾の発射位置Y
#define SHOT_BULLET_POS_Z		(-5.0f)			// 弾の発射位置Z

CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
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
	m_bAttack = false;
	m_bKnifeAttack = false;
	m_bCruch = false;
	 // 銃の生成
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_RHAND)->GetMatrix());
	// グレネード放つ位置の生成
	m_pGrenadeFire = CGrenadeFire::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
	// 銃の弾の種類
	m_pGun->GetTag() = TAG_PLAYER;
	// 発射位置のオフセットの設定
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(0.0f, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));

	// ナイフの生成
	m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
	// プレイヤーUIの生成
	m_pPlayerUI = CPlayerUI::Create();
	// 乗り物に乗り込んでいるかどうかのフラグ
	m_bRideVehicle = false;

	// 弾の残数表示
	m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
	// グレネードの残数表示
	m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
	//初期の向き
	SetCharacterDirection(CHARACTER_RIGHT);
	//リスポーン時のカウント
	m_nRespawnCnt = 0;
	//プレイヤーの状態ステータス
	m_PlayerState = PLAYER_STATE_NORMAL;

	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(PLAYER_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
//====================================================================
//終了
//====================================================================
void CPlayer::Uninit(void)
{
	// 銃のポインタ
	if (m_pGun)
	{
		m_pGun->Rerease();
		m_pGun = nullptr;
	}

	// ナイフのポインタ
	if (m_pKnife)
	{
		m_pKnife->Rerease();
		m_pKnife = nullptr;
	}

	// グレネード発射位置のポインタ
	if (m_pGrenadeFire)
	{
		m_pGrenadeFire->Rerease();
		m_pGrenadeFire = nullptr;
	}

	// プレイヤUIのポインタ
	if (m_pPlayerUI)
	{
		m_pPlayerUI->Uninit();
		m_pPlayerUI = nullptr;
	}

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

	// 特定のボタンを押した時に歩きモーションに変更
	if (CHossoLibrary::PressAnyButton())
	{
		//SetMotion(CCharacter::PLAYER_MOTION_WALK);
	}
	// 乗り物に乗っていない時といない時の判定
	Ride();

	CollisionUpdate();
	if (m_bRespawn == true)
	{
		ReSpawn();
	}
	// 体力UIの設定
	m_pPlayerUI->SetLifeUI(GetLife());
	CCharacter::Update();

	CDebugProc::Print("時機のライフ %d\n",GetLife());
	if (m_bAttack == true)
	{
		CDebugProc::Print("攻撃可能\n");
	}
	else
	{
		CDebugProc::Print("攻撃不可能\n");
	}
	if (m_bKnifeAttack == true)
	{
		CDebugProc::Print("攻撃ちゅううう\n");
	}
	else
	{
		CDebugProc::Print("攻撃してないで\n");
	}
}
//====================================================================
//描画
//====================================================================
void CPlayer::Draw(void)
{
	// 乗り物に乗っていたら描画しない またはライフが0でflagが立ったら
	if (m_bRideVehicle == false )
	{
		CCharacter::Draw();
	}
}
//====================================================================
//デバッグ
//====================================================================
void CPlayer::DebugInfo(void)
{
	static bool trigger = false;
	static bool trigger2 = false;
	CKeyboard *key;
	key = CManager::GetInputKeyboard();

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

}
//====================================================================
//移動関連
//====================================================================
void CPlayer::MoveUpdate(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	if (m_bRespawn == false)
	{
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

		//ジャンプ
		if (key->GetKeyboardTrigger(DIK_SPACE) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
		{
			GetMove().y += 27;
			SetMotion(PLAYER_MOTION_JUMP);
		}
		else if (GetJump() == false && GetMove().y < 0 && GetMotionType() != PLAYER_MOTION_JUMPSTOP)
		{
			SetMotion(PLAYER_MOTION_JUMP);
		}
		else if (key->GetKeyboardPress(DIK_SPACE) && m_DebugState != DEBUG_NORMAL)
		{
			GetMove().y += 2;
		}
		//ジャンプモーションじゃない時
		if (GetMotionType() != PLAYER_MOTION_JUMP)
		{
			//ジャンプストップモーションじゃない時
			if (GetMotionType() != PLAYER_MOTION_JUMPSTOP)
			{
				if (GetMotionType() != PLAYER_MOTION_ATTACK01)
				{
					//移動したらウォークモーション
					if (GetMove().x > 0.2f || GetMove().x < -0.2f)
					{
						SetMotion(PLAYER_MOTION_WALK);
						m_bCruch = false;
					}
					//移動してない時かつしゃがみストップじゃない時
					else if (GetMotionType() != PLAYER_MOTION_SQUATSTOP&& m_bCruch == false)
					{
						SetMotion(PLAYER_MOTION_NORMAL);
					}
					//Sを押したらしゃがみモーション
					if (key->GetKeyboardPress(DIK_S) && GetJump() == true)
					{
						if (m_bCruch == false && GetMotionType() != PLAYER_MOTION_WALK)
						{
							SetMotion(PLAYER_MOTION_SQUATSTOP);
							m_bCruch = true;
						}
					}
					else if (GetJump() == true && GetMotionType() != PLAYER_MOTION_WALK)
					{
						m_bCruch = false;
						SetMotion(PLAYER_MOTION_NORMAL);
					}
				}
			}
			//ジャンプ、しゃがみをしてなかったらニュートラル
			else if (GetJump() == true && m_bCruch == false && GetMotionType() != PLAYER_MOTION_ATTACK01)
			{
				SetMotion(PLAYER_MOTION_NORMAL);
			}
		}
		//ジャンプしたとき
		else if (GetMotionType() == PLAYER_MOTION_JUMP)
		{
			m_bCruch = false;
			//キーセットが３になったらストップモーションへ
			if (GetKeySet() == 3)
			{
				SetMotion(PLAYER_MOTION_JUMPSTOP);
			}
		}

		//ジャンプしたときの下向発射
		if (key->GetKeyboardPress(DIK_S) && GetJump() == false)
		{
			SetCharacterDirection(CHARACTER_DOWN);
		}
	}
}
//====================================================================
//当たり判定関連
//====================================================================
void CPlayer::CollisionUpdate(void)
{
	// 当たり判定
	if (GetCollision() != nullptr)
	{
		// 座標の更新 posとposold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());

		// 乗り物に乗っている時に乗り物以外の判定をしない
		if (m_bRideVehicle == false)
		{
			// エネミーととの判定
			if (GetCollision()->ForPlayer_EnemyCollision(ATTACK_PENETRATION) == true||
				GetCollision()->ForPlayer_PrisonerCollision(ATTACK_PENETRATION) == true)
			{
				m_bAttack = true;
			}
			else
			{
				m_bAttack = false;
			}

			// 障害物との判定
			//if (GetCollision()->ForPlayer_ObstacleCollision())
			//{
			//	// ジャンプフラグを可能にする
			//	CCharacter::SetJump(true);
			//}

			// アイテムとの判定
			if (GetCollision()->ForPlayer_ItemCollision())
			{
			}
		}

		if (m_bRideVehicle == false)
		{
			// 乗り物との判定
			if (GetCollision()->ForPlayer_VehicleCollision())
			{
				// 乗り込んだ時
				m_bRideVehicle = true;
			}
			else
			{
				// 乗っていないとき
				m_bRideVehicle = false;
			}
		}
	}

	// 銃の描画フラグの設定
	m_pGun->SetDrawFlag(m_bRideVehicle);
}
//====================================================================
//攻撃関連
//====================================================================
void CPlayer::AttackUpdate(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	if (m_bRespawn == false)
	{
		// 銃を撃つ or 近接攻撃
		if (key->GetKeyboardTrigger(DIK_P))
		{
			// 銃を撃てる状態だった時
			if (m_bAttack == false && m_bKnifeAttack == false)
			{
				// 銃発射処理
				m_pGun->Shot();
			}

			// 近接攻撃をする状態だった時
			if (m_bAttack == true && m_bKnifeAttack == false)
			{
				// 近接攻撃
				m_bKnifeAttack = true;
				m_pKnife->StartMeleeAttack();
				SetMotion(CCharacter::PLAYER_MOTION_ATTACK01);
			}
		}
		// グレネードを投げる
		if (key->GetKeyboardTrigger(DIK_O))
		{
			// グレネードの弾数が残っているとき
			if (m_pGrenadeFire->GetGrenadeAmmo() > 0)
			{
				// グレネード生成
				m_pGrenadeFire->Fire(GetShotDirection());

				SetMotion(CCharacter::PLAYER_MOTION_GRENADE);
			}
		}

		// 攻撃モーションから別のモーションになった時
		if (GetMotionType() != CCharacter::PLAYER_MOTION_ATTACK01)
		{
			m_bKnifeAttack = false;
			m_pKnife->EndMeleeAttack();
		}
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
	if (GetJump() == true)
	{
	SetMotion(CCharacter::PLAYER_MOTION_NORMAL);
	}
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
	GetMove().x += sinf(move * -D3DX_PI) * 1.3f;
	GetMove().z += cosf(move * -D3DX_PI) * 1.3f;
	GetRotDest().y = fdest *  D3DX_PI;
}

//====================================================================
// 乗り物に乗っている時
//====================================================================
void CPlayer::Ride()
{
	// 乗り物に乗っていない時に更新する
	if (m_bRideVehicle == false)
	{
		MoveUpdate();
		AttackUpdate();

		// 弾を撃つ方向を設定
		m_pGun->SetShotRot(GetShotDirection());
		// 弾の残数表示
		m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
		// グレネードの残数表示
		m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
	}
	else
	{
		CPlayertank *pPlayertank = nullptr;
		pPlayertank = this->GetCollision()->ForPlayer_TankCollision();

		CBattlePlane *pBattlePlane = nullptr;
		pBattlePlane = this->GetCollision()->ForPlayer_PlaneCollision();

		// 戦車に乗っている時
		if (pPlayertank != nullptr)
		{
			// プレイヤーの座標を戦車の座標に合わせる
			this->SetPosition(pPlayertank->GetPosition());

			// 弾の残数表示
			m_pPlayerUI->SetBulletAmmo(pPlayertank->GetGun()->GetGunAmmo(), pPlayertank->GetGun()->GetGunType());
			// グレネードの残数表示
			m_pPlayerUI->SetGrenadeAmmo(pPlayertank->GetGrenadeFire()->GetGrenadeAmmo());
		}

		// 戦闘機に乗っている時
		else if (pBattlePlane != nullptr)
		{
			// プレイヤーの座標を戦闘機の座標に合わせる
			this->SetPosition(pBattlePlane->GetPosition());

			// 弾の残数表示
			m_pPlayerUI->SetBulletAmmo(pBattlePlane->GetGun()->GetGunAmmo(), pBattlePlane->GetGun()->GetGunType());
		}

		// 乗り物に乗っている時にジャンプして戦車から降りる
		CKeyboard *key = CManager::GetInputKeyboard();
		if (key->GetKeyboardTrigger(DIK_SPACE) && GetJump() == false)
		{
			m_bRideVehicle = false;
			GetMove().y += 40;
			SetMotion(PLAYER_MOTION_JUMP);

			// 無敵判定
		}
	}
}
//====================================================================
//リスポーン
//====================================================================
void CPlayer::ReSpawn(void)
{
	m_nRespawnCnt++;
	m_PlayerState = PLAYER_STATE_RESPAWN;

	if (m_nRespawnCnt == 120)
	{
		m_nRespawnCnt = 0;
		m_bRespawn = false;
		m_pGun->SetGunType(CGun::GUNTYPE_HANDGUN);
		SetLife(10);
	}
}
