// =====================================================================================================================================================================
//
// プレイヤーの処理 [player.cpp]
// Author : NORI
//
// =====================================================================================================================================================================
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
#include "resultmanager.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
PLAYER_DATA		CPlayer::m_PlayerData	 = {};
int				CPlayer::m_nLife[2] = {};
int				CPlayer::m_nRespawnCnt	 = 0;
float			CPlayer::m_fRunSpeed	 = 0.0f;
float			CPlayer::m_fCrouchSpeed	 = 0.0f;
float			CPlayer::m_fJump		 = 0.0f;
float			CPlayer::m_fRideJump	 = 0.0f;
D3DXVECTOR3		CPlayer::m_pos[2] = {};
// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CPlayer::m_PlayerFileName =
{
	"data/Load/Player/PlayerData.txt" 			// プレイヤーの情報
};

//====================================================================
//マクロ定義
//====================================================================
#define PLAYER_SIZE			(D3DXVECTOR3(40.0f,70.0f,0.0f)) //プレイヤーのサイズ
#define PLAYER_SIZE_CRUCH	(D3DXVECTOR3(40.0f,30.0f,0.0f)) //しゃがんだ時のサイズ
// 貫通させるかのフラグ
#define ATTACK_PENETRATION		(true)			// プレイヤーの判定が貫通するかどうか
#define SHOT_BULLET_POS_Y		(-15.0f)		// 弾の発射位置Y
#define SHOT_BULLET_POS_Z		(-5.0f)			// 弾の発射位置Z
#define KNIFE_COLLISOIN_SIZE	(D3DXVECTOR3(80.0f,80.0f,0.0f))
#define RESPAWN_INTERVAL		(120)

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPlayer::~CPlayer()
{
}
//====================================================================
//初期化
//====================================================================
HRESULT CPlayer::Init(void)
{
	// 読み込んだ情報の代入
	SetPlayerData();

	//キャラの初期化
	CCharacter::Init();
	LoadOffset(CCharacter::CHARACTER_TYPE_PLAYER);
	SetCharacterType(CCharacter::CHARACTER_TYPE_PLAYER);
	m_bAttack = false;
	m_bKnifeAttack = false;

	 // 銃の生成
	m_pGun = CGun::Create();
	// 手のポインタ設定
	m_pGun->SetHandMtx(GetCharacterModelPartsList(CModel::MODEL_PLAYER_RHAND)->GetMatrix());

	// グレネード放つ位置の生成
	m_pGrenadeFire = CGrenadeFire::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix(), CGrenadeFire::HAND_GRENADE);
	// 銃の弾の種類
	m_pGun->GetTag() = TAG_PLAYER;
	// 発射位置のオフセットの設定
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(0.0f, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));

	// ナイフの生成
	m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix(), KNIFE_COLLISOIN_SIZE, TAG::TAG_PLAYER);
	// 乗り物に乗り込んでいるかどうかのフラグ
	m_bRideVehicle = false;

	// ゲームモードだった時
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// ゲームクラスのポインタ取得
		CGame *pGame = (CGame*)CManager::GetBaseMode();
		if (pGame != nullptr)
		{
			// プレイヤーUIの生成
			m_pPlayerUI = CPlayerUI::Create();
			// 弾の残数表示
			m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
			// グレネードの残数表示
			m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
		}
	}

	// チュートリアルモードだった時
	if (CManager::GetMode() == CManager::MODE_TUTORIAL)
	{
		SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));
		SetLife(5);
	}
	// ゲームモードだった時
	else if(CManager::GetMode() == CManager::MODE_GAME)
	{
		SetPosition(m_pos[0]);
		SetLife(m_nLife[0]);
	}

	//初期の向き
	SetCharacterDirection(DIRECTION::RIGHT);
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
		delete m_pGun;
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

	CheckDrawRange();

	m_pGun->Update();

	//リスポーン状態かどうか
	if (m_bRespawn == true)
	{
		//リスポーンの処理
		ReSpawn();
	}
	//通常状態のとき
	else
	{
		// 乗り物に乗っていない時といない時の判定
		Ride();
	}
	//当たり判定処理
	CollisionUpdate();
	// 体力UIの設定
	if (m_pPlayerUI)
	{
		m_pPlayerUI->SetLifeUI(GetLife());
	}
	if (m_pGun->GetGunType() == m_pGun->GUNTYPE_HEAVYMACHINEGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_HEAVYMACHINEGUN);
	}

	CCharacter::Update();

	//スクリーンの範囲内から出ないように制限
	CManager::GetRenderer()->ScreenLimitRange(GetPosition());
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
	DrawWepon();
	m_pGun->Draw();

}
//====================================================================
//武器の見た目変更
//====================================================================
void CPlayer::DrawWepon(void)
{
	//ハンドガン
	if (m_pGun->GetGunType() == m_pGun->GUNTYPE_HANDGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_HANDGUN);
	}
	//ヘビーマシンガン
	else if (m_pGun->GetGunType() == m_pGun->GUNTYPE_HEAVYMACHINEGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_HEAVYMACHINEGUN);
	}
	//ショットガン
	else if (m_pGun->GetGunType() == m_pGun->GUNTYPE_SHOTGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_SHOTGUN);
	}
	//フレイム
	else if (m_pGun->GetGunType() == m_pGun->GUNTYPE_FLAMESHOT)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_FLAMESHOT);
	}
	//レーザー
	else if (m_pGun->GetGunType() == m_pGun->GUNTYPE_LASERGUN)
	{
		m_pGun->SetModelConut(m_pGun->GUNTYPE_LASERGUN);
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

	CDebugProc::Print("pos %f,%f,%f\n", GetPosition().x, GetPosition().y, GetPosition().z);
	CDebugProc::Print("ShotRot >> %.2f %.2f %.2f\n", GetShotDirection().x, GetShotDirection().y, GetShotDirection().z);
	CDebugProc::Print("PlayerState >> %d\n", GetCharacterState());
	CDebugProc::Print("Direction >> %d\n", GetCharacterDirection());
	CDebugProc::Print("DirectionOld >> %d\n", GetCharacterDirectionOld());

	CDebugProc::Print("座標------------------------------------------%f,%f,%f\n", m_pos[0].x, m_pos[0].y, m_pos[0].z);

	CDebugProc::Print("時機のライフ %d\n", GetLife());
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

	// 特定のボタンを押した時に歩きモーションに変更
	if (CHossoLibrary::PressAnyButton())
	{
		//SetMotion(CCharacter::PLAYER_MOTION_WALK);
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

}
//====================================================================
//移動関連
//====================================================================
void CPlayer::MoveUpdate(void)
{
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	CXInputPad *pad;
	pad = CManager::GetPad();
	float Pad_X, Pad_Y;
	pad->GetStickLeft(&Pad_X, &Pad_Y);//パッドの入力値を代入
	Pad_X /= STICK_MAX_RANGE;//値の正規化
	Pad_Y /= STICK_MAX_RANGE;//値の正規化
		// Aの処理
	if (key->GetKeyboardPress(DIK_A))
	{
		CPlayer::Move(m_fRunSpeed, 0.5f);
		SetCharacterDirection(DIRECTION::LEFT);

	}

	// Dの処理
	else if (key->GetKeyboardPress(DIK_D))
	{
		CPlayer::Move(-m_fRunSpeed, -0.5f);

		SetCharacterDirection(DIRECTION::RIGHT);
	}

	// W押してたら上むく
	if (key->GetKeyboardPress(DIK_W))
	{
		SetCharacterDirection(DIRECTION::UP);
	}

	//ジャンプ
	if ((key->GetKeyboardTrigger(DIK_SPACE) || pad->GetTrigger(pad->JOYPADKEY_A, 1)) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
	{
		GetMove().y += m_fJump;
		SetMotion(PLAYER_MOTION_JUMP);
	}
	//ジャンプ中はジャンプモーション
	else if (GetJump() == false && GetMotionType() != PLAYER_MOTION_JUMPSTOP)
	{
		SetMotion(PLAYER_MOTION_JUMP);
	}

	//デバッグ用
	else if (key->GetKeyboardPress(DIK_SPACE) && m_DebugState != DEBUG_NORMAL)
	{
		GetMove().y += 2;
	}

	//ジャンプしてない時
	if (GetJump())
	{
		//攻撃してない時
		if (GetMotionType() != PLAYER_MOTION_ATTACK01)
		{
			//移動したらウォークモーション
			if (fabsf(GetMove().x) > 0.3f)
			{
				SetMotion(PLAYER_MOTION_WALK);
				m_bCruch = false;
			}
			//Sを押したらしゃがみモーション
			else if ((key->GetKeyboardPress(DIK_S) || Pad_Y < -0.8f) && GetJump() == true)
			{
				SetMotion(PLAYER_MOTION_SQUATSTOP);
				GetCollision()->SetSize2D(PLAYER_SIZE_CRUCH);
				m_bCruch = true;
			}
			//ジャンプ、しゃがみをしてなかったらニュートラル
			else
			{
				SetMotion(PLAYER_MOTION_NORMAL);
				GetCollision()->SetSize2D(PLAYER_SIZE);
				m_bCruch = false;
			}
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
		SetCharacterDirection(DIRECTION::DOWN);
	}

	//上も下も入力されていない時は正面を向く
	if (!(key->GetKeyboardPress(DIK_S) || key->GetKeyboardPress(DIK_W) || fabsf(Pad_Y) > 0.8f))
	{
		//正面を向く
		ResetCharacterDirection();
	}

	PadMoveUpdate();//パッドの更新

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
			CPrisoner *pPrisoner = GetCollision()->ForPlayer_PrisonerCollision();
			// エネミーととの判定
			if (GetCollision()->ForPlayer_EnemyCollision(ATTACK_PENETRATION) == true||
				GetCollision()->ForPlayer_PrisonerCollision(ATTACK_PENETRATION) == true)
			{
				if (pPrisoner != nullptr)
				{
					m_bAttack = true;
				}
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
	CXInputPad *pad;
	pad = CManager::GetPad();

	// 銃を撃つ or 近接攻撃
	if (key->GetKeyboardTrigger(DIK_P) || pad->GetTrigger(pad->JOYPADKEY_X, 1))
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
	if (key->GetKeyboardTrigger(DIK_O) || pad->GetTrigger(pad->JOYPADKEY_Y, 1))
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
//====================================================================
//パッドの移動関連更新
//====================================================================
void CPlayer::PadMoveUpdate(void)
{
	//移動量
	D3DXVECTOR3 MoveValue = ZeroVector3;

	//パッドによる入力処理
	if (CHossoLibrary::PadMoveInput(MoveValue, GetCharacterDirection(), GetJump()))
	{
		//移動量計算
		Move(MoveValue.x, MoveValue.y);
	}

	CXInputPad *pad = CManager::GetPad();
	D3DXVECTOR3 InputValue = ZeroVector3;
	pad->GetStickLeft(&InputValue.x, &InputValue.y);//パッドの入力値を代入

	InputValue.x /= STICK_MAX_RANGE;//値の正規化
	InputValue.y /= STICK_MAX_RANGE;//値の正規化

	//ジャンプモーションじゃない時かつジャンプストップモーションじゃない時

	if (GetMotionType() != PLAYER_MOTION_JUMP && GetMotionType() != PLAYER_MOTION_JUMPSTOP && GetMotionType() != PLAYER_MOTION_ATTACK01)
	{
		//Sを押したらしゃがみモーション
		if (InputValue.y < -0.8f && GetJump() == true)
		{
			if (m_bCruch == false && GetMotionType() != PLAYER_MOTION_WALK)
			{
				SetMotion(PLAYER_MOTION_SQUATSTOP);
				m_bCruch = true;
			}
		}

	}
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
//プレイヤーリスポーン処理
//====================================================================
void CPlayer::MapChangePlayerRespawn()
{
	SetState(CCharacter::CHARACTER_STATE_INVINCIBLE);
	SetPosition(ZeroVector3);
	m_bRideVehicle = false;
	m_pKnife->EndMeleeAttack();
}

//====================================================================
//ダメージ時のリアクション
//====================================================================
void CPlayer::DamageReaction()
{
	CCharacter::DamageReaction();
}

//====================================================================
//死亡時のリアクション
//====================================================================
void CPlayer::DeathReaction()
{
	CCharacter::DeathReaction();

}
//====================================================================
//ステートが切り替わった時のリアクション
//====================================================================
void CPlayer::StateChangeReaction()
{
	//ステート切り替えた時のリアクション
	CCharacter::StateChangeReaction();

	//Player側でオーバーライド
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_NORMAL:

		break;

	case CHARACTER_STATE_DAMAGE_FLASHING:


		break;
	case CHARACTER_STATE_INVINCIBLE:

		break;
	case CHARACTER_STATE_ITEMGET_FLASH:
		ChangeColor(true, FlashColor);
		SetStateCount(3);
		break;
	case CHARACTER_STATE_DEATH:
		SetRespawnFlag(true);
		SetMotion(CCharacter::PLAYER_MOTION_DEAD);
		break;
	}
}
//====================================================================
//デバッグステータスの取得
//====================================================================
CPlayer::DEBUG_STATE CPlayer::GetDebugState(void)
{
	return m_DebugState;
}

//====================================================================
// 乗り物に乗っている時
//====================================================================
void CPlayer::Ride()
{
	// 乗り物に乗っていない時に更新する
	if (m_bRideVehicle == false)
	{
		//移動の更新
		MoveUpdate();

		//攻撃の更新
		AttackUpdate();


		//ヘビーマシンガンのとき
		if (m_pGun->GetGunType() == CGun::GUNTYPE_HEAVYMACHINEGUN)
		{
			//左から右　あるいは右から左に方向転換した時
			if ((CCharacter::GetCharacterDirection() == DIRECTION::LEFT && CCharacter::GetCharacterDirectionOld() == DIRECTION::RIGHT) ||
				(CCharacter::GetCharacterDirection() == DIRECTION::RIGHT && CCharacter::GetCharacterDirectionOld() == DIRECTION::LEFT))
			{
				//射角設定
				m_ShotRot = GetShotDirection();
			}
			else
			{
				//斜め方向にも弾を撃てるようにすこしゆっくり回転させる
				D3DXVECTOR3 ShotRotDif = GetShotDirection() - m_ShotRot;

				//3.14以内に抑える
				CHossoLibrary::CalcRotation(ShotRotDif.z);

				//徐々に回転
				m_ShotRot += ShotRotDif * 0.15f;
			}
		}
		//それ以外のとき
		else
		{
			//射角設定
			m_ShotRot = GetShotDirection();
		}

		// 弾を撃つ方向を設定
		m_pGun->SetShotRot(m_ShotRot);


		if (m_pGun->GetGunType() != m_pGun->GUNTYPE_HEAVYMACHINEGUN)
		{

		}

		//nullcheck
		if (m_pPlayerUI)
		{
			// 弾の残数表示
			m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
			// グレネードの残数表示
			m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
		}
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
			//スクリーンの範囲内から出ないように制限
			CManager::GetRenderer()->ScreenLimitRange(pPlayertank->GetPosition());

			// プレイヤーの座標を戦車の座標に合わせる
			this->SetPosition(pPlayertank->GetPosition());

			if (m_pPlayerUI)
			{
				// 弾の残数表示
				m_pPlayerUI->SetBulletAmmo(pPlayertank->GetGun()->GetGunAmmo(), pPlayertank->GetGun()->GetGunType());
				// グレネードの残数表示
				m_pPlayerUI->SetGrenadeAmmo(pPlayertank->GetGrenadeFire()->GetGrenadeAmmo());
			}
		}

		// 戦闘機に乗っている時
		else if (pBattlePlane != nullptr)
		{
			//スクリーンの範囲内から出ないように制限
			CManager::GetRenderer()->ScreenLimitRange(pBattlePlane->GetPosition());

			// プレイヤーの座標を戦闘機の座標に合わせる
			this->SetPosition(pBattlePlane->GetPosition());

			if (m_pPlayerUI)
			{
				// 弾の残数表示
				m_pPlayerUI->SetBulletAmmo(pBattlePlane->GetGun()->GetGunAmmo(), pBattlePlane->GetGun()->GetGunType());
			}
		}

		// 乗り物に乗っている時にジャンプして戦車から降りる
		CKeyboard *key = CManager::GetInputKeyboard();
		CXInputPad *pad = CManager::GetPad();
		//プレイヤーが乗り物から降りるとき
		if (key->GetKeyboardTrigger(DIK_SPACE)|| pad->GetTrigger(pad->JOYPADKEY_B,1) && GetJump() == false)
		{
			m_bRideVehicle = false;
			GetMove().y += m_fRideJump;
			SetMotion(PLAYER_MOTION_JUMP);
		}
	}
}
//====================================================================
//リスポーン
//====================================================================
void CPlayer::ReSpawn(void)
{
	m_nRespawnCnt++;

	if (m_nRespawnCnt >= RESPAWN_INTERVAL)
	{
		m_nRespawnCnt = 0;
		m_bRespawn = false;
		m_pGun->SetGunType(CGun::GUNTYPE_HANDGUN);
		SetMotion(CCharacter::PLAYER_MOTION_NORMAL);
		SetState(CHARACTER_STATE_INVINCIBLE);
		SetLife(m_nLife[0]);
	}
}

//====================================================================
//モデルのクリエイト
//====================================================================
CPlayer *CPlayer::Create(void)
{
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->Init();
	return pPlayer;
}

//====================================================================
//プレイヤーのデータの読み込み
//====================================================================
void CPlayer::PlayerLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

	// ファイルを開く
	pFile = fopen(m_PlayerFileName, "r");

	// 開いているとき
	if (pFile != NULL)
	{
		// SCRIPTが来るまでループ
		while (strcmp(cHeadText, "SCRIPT") != 0)
		{
			fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
			sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入
		}

		// SCRIPTが来たら
		if (strcmp(cHeadText, "SCRIPT") == 0)
		{
			// END_SCRIPTが来るまでループ
			while (strcmp(cHeadText, "END_SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
				sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

															// ITEMSETが来たら
				if (strcmp(cHeadText, "PLAYERSET") == 0)
				{
					// END_ITEMSETが来るまでループ
					while (strcmp(cHeadText, "END_PLAYERSET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

																	// SPEEDが来たら
						if (strcmp(cHeadText, "LIFE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerData.nLife);			// 比較用テキストにLIFEを代入
						}
						else if (strcmp(cHeadText, "RESPAEN") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_PlayerData.nRespawnCnt);		// 比較用テキストにRESPAENを代入
						}
						else if (strcmp(cHeadText, "RUNSPEED") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PlayerData.fRunSpeed);		// 比較用テキストにRUNSPEEDを代入
						}
						else if (strcmp(cHeadText, "CROUCHSPEED") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PlayerData.fCrouchSpeed);	// 比較用テキストにCROUCHSPEEDを代入
						}
						else if (strcmp(cHeadText, "RIDEJUMP") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PlayerData.fRideJump);		// 比較用テキストにRIDEJUMPを代入
						}
						else if (strcmp(cHeadText, "JUMP") == 0)
						{
							sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_PlayerData.fJump);			// 比較用テキストにJUMPを代入
						}
						else if (strcmp(cHeadText, "POS") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_PlayerData.pos.x,
								&m_PlayerData.pos.y,
								&m_PlayerData.pos.z);													// 比較用テキストにPOSを代入
						}

						else if (strcmp(cHeadText, "END_PLAYERSET") == 0)
						{
						}
					}
				}
			}
		}
		// ファイルを閉じる
		fclose(pFile);
	}
	else
	{
		MessageBox(NULL, "プレイヤーのデータ読み込み失敗", "警告", MB_ICONWARNING);
	}
}

//====================================================================
//プレイヤーのデータの設定
//====================================================================
void CPlayer::SetPlayerData()
{
	// 体力の情報を取得
	m_nLife[0] = m_PlayerData.nLife;
	// 初期座標の情報を取得
	m_pos[0] = m_PlayerData.pos;
	// 復活時間の情報を取得
	m_nRespawnCnt = m_PlayerData.nRespawnCnt;
	// 移動速度の情報を取得
	m_fRunSpeed = m_PlayerData.fRunSpeed;
	// しゃがみ時の移動速度の情報を取得
	m_fCrouchSpeed = m_PlayerData.fCrouchSpeed;
	// 通常時のジャンプ量
	m_fJump = m_PlayerData.fJump;
	// 乗り物から降りる時のジャンプ量
	m_fRideJump = m_PlayerData.fRideJump;
}
