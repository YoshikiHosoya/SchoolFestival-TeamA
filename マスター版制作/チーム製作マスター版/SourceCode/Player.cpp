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
#define PLAYER_SIZE			(D3DXVECTOR3(50.0f,65.0f,0.0f)) //プレイヤーのサイズ
#define PLAYER_SIZE_CRUCH	(D3DXVECTOR3(50.0f,34.0f,0.0f)) //しゃがんだ時のサイズ
// 貫通させるかのフラグ
#define ATTACK_PENETRATION		(true)			// プレイヤーの判定が貫通するかどうか
#define ATTACK_DAMAGE_ENEMY		(50)			// エネミーへのダメージ
#define SHOT_BULLET_POS_Y		(-15.0f)		// 弾の発射位置Y
#define SHOT_BULLET_POS_Z		(-5.0f)			// 弾の発射位置Z

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
	m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_RHAND)->GetMatrix());
	// グレネード放つ位置の生成
	m_pGrenadeFire = CGrenadeFire::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
	// 銃の弾の種類
	m_pGun->GetTag() = TAG_PLAYER;
	// 発射位置のオフセットの設定
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(0.0f, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));

	// ナイフの生成
	m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
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

	m_pGun->Update();

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
	if (m_pPlayerUI)
	{
		m_pPlayerUI->SetLifeUI(GetLife());
	}

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
	PadMoveUpdate();//パッドの更新
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

	m_pGun->Draw();

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
	CXInputPad *pad;
	pad = CManager::GetPad();
	float x, y;
	pad->GetStickLeft(&x, &y);//パッドの入力値を代入
	x /= STICK_MAX_RANGE;//値の正規化
	y /= STICK_MAX_RANGE;//値の正規化

	if (m_bRespawn == false)
	{
		if (key->GetKeyboardPress(DIK_W))
		{
			SetCharacterDirection(DIRECTION::UP);
		}

		// Aの処理
		if (key->GetKeyboardPress(DIK_A))
		{
			CPlayer::Move(m_fRunSpeed, 0.5f);
			if (key->GetKeyboardPress(DIK_W))
			{
				SetCharacterDirection(DIRECTION::UP);
			}
			else
			{
				SetCharacterDirection(DIRECTION::LEFT);
			}
		}
		// Dの処理
		else if (key->GetKeyboardPress(DIK_D))
		{
			CPlayer::Move(-m_fRunSpeed, -0.5f);
			if (key->GetKeyboardPress(DIK_W))
			{
				SetCharacterDirection(DIRECTION::UP);
			}
			else
			{
				SetCharacterDirection(DIRECTION::RIGHT);
			}
		}

		//ジャンプ
		if ((key->GetKeyboardTrigger(DIK_SPACE)|| pad->GetTrigger(pad->JOYPADKEY_A, 1)) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
		{
			GetMove().y += m_fJump;
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
					//しゃがんでない時
					else if (m_bCruch == false)
					{
						SetMotion(PLAYER_MOTION_NORMAL);
						GetCollision()->SetSize2D(PLAYER_SIZE_CRUCH);
					}
					//Sを押したらしゃがみモーション
					if (key->GetKeyboardPress(DIK_S)|| y < -0.6f && GetJump() == true)
					{
						if (m_bCruch == false && GetMotionType() != PLAYER_MOTION_WALK)
						{
							SetMotion(PLAYER_MOTION_SQUATSTOP);
							GetCollision()->SetSize2D(PLAYER_SIZE_CRUCH);
							m_bCruch = true;
						}
					}
					else if (GetJump() == true && GetMotionType() != PLAYER_MOTION_WALK && y > -0.6f)
					{
						m_bCruch = false;
						SetMotion(PLAYER_MOTION_NORMAL);
						GetCollision()->SetSize2D(PLAYER_SIZE);
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
			SetCharacterDirection(DIRECTION::DOWN);
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
	if (m_bRespawn == false)
	{
		// 銃を撃つ or 近接攻撃
		if (key->GetKeyboardTrigger(DIK_P)|| pad->GetTrigger(pad->JOYPADKEY_X,1))
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
		if (key->GetKeyboardTrigger(DIK_O)|| pad->GetTrigger(pad->JOYPADKEY_Y, 1))
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
//パッドの移動関連更新
//====================================================================
void CPlayer::PadMoveUpdate(void)
{
	D3DXVECTOR3 MoveValue = ZeroVector3;
	if (m_bRespawn == false)
	{

		if (CHossoLibrary::PadMoveInput(MoveValue, GetCharacterDirection(), GetJump()))
		{
			Move(MoveValue.x, MoveValue.y);
		}

		CXInputPad *pad = CManager::GetPad();
		D3DXVECTOR3 InputValue = ZeroVector3;
		pad->GetStickLeft(&InputValue.x, &InputValue.y);//パッドの入力値を代入

		InputValue.x /= STICK_MAX_RANGE;//値の正規化
		InputValue.y /= STICK_MAX_RANGE;//値の正規化

		//ジャンプモーションじゃない時
		if (GetMotionType() != PLAYER_MOTION_JUMP)
		{
			//ジャンプストップモーションじゃない時
			if (GetMotionType() != PLAYER_MOTION_JUMPSTOP)
			{
				if (GetMotionType() != PLAYER_MOTION_ATTACK01)
				{
					//Sを押したらしゃがみモーション
					if (InputValue.y < -0.6f && GetJump() == true)
					{
						if (m_bCruch == false && GetMotionType() != PLAYER_MOTION_WALK)
						{
							SetMotion(PLAYER_MOTION_SQUATSTOP);
							m_bCruch = true;
						}
					}
				}
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
	CCharacter::StateChangeReaction();

	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_NORMAL:

		break;

	case CHARACTER_STATE_DAMAGE:


		break;
	case CHARACTER_STATE_DAMAGE_RED:


		break;
	case CHARACTER_STATE_INVINCIBLE:


		break;
	case CHARACTER_STATE_DEATH:
		SetRespawnFlag(true);

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
		if (m_pGun->GetGunType() != m_pGun->GUNTYPE_HEAVYMACHINEGUN)
		{
		// 弾を撃つ方向を設定
			m_pGun->SetShotRot(GetShotDirection());
		}
		else
		{
		// 弾を撃つ方向を設定
		m_pGun->SetShotRot(GetAddShotRot());
		CDebugProc::Print("射撃方向値:%2f\n", GetAddShotRot().z);
		}
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
	SetState(CHARACTER_STATE_INVINCIBLE);

	if (m_nRespawnCnt == m_nRespawnCnt)
	{
		m_nRespawnCnt = 0;
		m_bRespawn = false;
		m_pGun->SetGunType(CGun::GUNTYPE_HANDGUN);
		SetState(CHARACTER_STATE_NORMAL);
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
