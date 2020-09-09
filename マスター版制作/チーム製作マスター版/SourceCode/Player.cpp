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
#include "GameManager.h"
#include "sound.h"
#include "ModelSet.h"
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
PLAYER_DATA		CPlayer::m_PlayerData	 = {};
int				CPlayer::m_nLife[2] = {};
float			CPlayer::m_fRunSpeed	 = 0.0f;
float			CPlayer::m_fCrouchSpeed	 = 0.0f;
float			CPlayer::m_fJump		 = 0.0f;
float			CPlayer::m_fRideJump	 = 0.0f;
D3DXVECTOR3		CPlayer::m_pos[2] = {};
bool			CPlayer::m_bTwoPPlay = false;

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
#define DEFAULT_STOCK			(3)				// 初期残機

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlayer::CPlayer(OBJ_TYPE type) :CCharacter(type)
{
	SetObjType(OBJTYPE_PLAYER);
	m_pGrenadeFire	= nullptr;
	m_pGun			= nullptr;
	m_pKnife		= nullptr;
	m_pPlayerUI		= nullptr;
	m_pVehicle		= nullptr;
	m_pPad			= nullptr;
	m_nRespawnCnt = 0;
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
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_PLAYER);
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_PLAYER);

	 // 銃の生成
	m_pGun = CGun::Create();
	// 手のポインタ設定
	m_pGun->SetHandMtx(GetModelSet()->GetCharacterModelList()[8]->GetMatrix());

	// グレネード放つ位置の生成
	m_pGrenadeFire = CGrenadeFire::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), CGrenadeFire::HAND_GRENADE);
	// 銃の弾の種類
	m_pGun->SetTag(GetTag());
	// 発射位置のオフセットの設定
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(0.0f, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));

	// ナイフの生成
	m_pKnife = CKnife::Create(GetModelSet()->GetCharacterModelList()[7]->GetMatrix(), KNIFE_COLLISOIN_SIZE, TAG::PLAYER_1);
	// 乗り物に乗り込んでいるかどうかのフラグ
	m_bRideVehicle = false;
	//腕が回転するか
	SetRotArm(true);
	// ゲームモードだった時
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		// ゲームクラスのポインタ取得
		CGame *pGame = (CGame*)CManager::GetBaseMode();
		if (pGame != nullptr)
		{
			// プレイヤーUIの生成
			m_pPlayerUI = CPlayerUI::Create(GetTag());
			// 弾の残数表示
			m_pPlayerUI->SetBulletAmmo(m_pGun->GetGunAmmo(), m_pGun->GetGunType());
			// グレネードの残数表示
			m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());
			// 残機の設定
			m_pPlayerUI->SetStockUI(DEFAULT_STOCK);

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
		//プレイヤー設定
		ResetPlayer();
	}

	//初期の向き
	SetCharacterDirection(DIRECTION::RIGHT);
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetSize2D(PLAYER_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	// ゲームオブジェクト( タグ )の設定
	GetCollision()->SetGameObject(this);

	// 試験的パッドのポインタ取得
	m_pPad = CManager::CManager::GetPad(GetTag());

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

	//ゲーム中の時
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		if (m_bRespawn == true)
		{
			//リスポーンの処理
			ReSpawn();
		}
		//ゲームオーバー中
		else if (CManager::GetGame()->GetGameManager()->GetGameState() == CGameManager::GAMESTATE::GAMEOVER ||
				CManager::GetGame()->GetGameManager()->GetGameState() == CGameManager::GAMESTATE::NONE)
		{
			//ずっと死亡
			SetLife(0);
			GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_DEAD);

		}
		//リザルト画面以外のとき
		else if (CManager::GetGame()->GetGameManager()->GetGameState() != CGameManager::GAMESTATE::RESULT)
		{
			// 乗り物に乗っていない時といない時の判定
			Ride();
		}
		else
		{
			DefaultMotion();
		}
	}
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

	char aTreeName[MAX_TEXT] = {};
	sprintf(aTreeName, "PlayerInfo [%d]", CScene::GetID());

	if (ImGui::TreeNode(aTreeName))
	{
		ImGui::Text("m_ShotRot [%.2f %.2f %.2f]", m_ShotRot.x, m_ShotRot.y, m_ShotRot.z);

		ImGui::Text("m_bAttack [%d]", m_bAttack); ImGui::SameLine();
		ImGui::Text("m_bKnifeAttack [%d]", m_bKnifeAttack);
		ImGui::Text("m_bRespawn [%d]", m_bRespawn); ImGui::SameLine();
		ImGui::Text("m_bCruch [%d]", m_bCruch);
		ImGui::Text("m_bRideVehicle [%d]", m_bRideVehicle);


		ImGui::Text("---DebugCommand---");
		ImGui::Text("[G] >> PlayerDamage");
		ImGui::Text("[F2] >> DebugTrigger(Player Fly)"); ImGui::SameLine();
		ImGui::Text("DebugTrigger [%d]", trigger);

		CCharacter::DebugInfo();

		m_pGun->DebugInfo();

		m_pGrenadeFire->DebugInfo();

		m_pKnife->DebugInfo();

		ImGui::TreePop();
	}

	if (key->GetKeyboardTrigger(DIK_G))
	{
		AddDamage(1);
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
	float Pad_X, Pad_Y;

	if (m_pPad)
	{
		//パッドの入力値を代入
		m_pPad->GetStickLeft(&Pad_X, &Pad_Y);

		Pad_X /= STICK_MAX_RANGE;//値の正規化
		Pad_Y /= STICK_MAX_RANGE;//値の正規化
	}
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

	// しゃがんでない時はW押してたら上むく
	if (key->GetKeyboardPress(DIK_W) && !m_bCruch)
	{
		SetCharacterDirection(DIRECTION::UP);
	}

	//ジャンプ
	if ((key->GetKeyboardTrigger(DIK_SPACE) || m_pPad->GetTrigger(m_pPad->JOYPADKEY_A, 1)) && GetJump() == true && m_DebugState == DEBUG_NORMAL)
	{
		GetMove().y += m_fJump;
		GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_JUMP);
	}
	//ジャンプ中はジャンプモーション
	else if (GetJump() == false && GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_JUMPSTOP)
	{
		GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_JUMP);
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
		if (GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_ATTACK01)
		{
			//移動したらウォークモーション
			if (fabsf(GetMove().x) > 0.3f)
			{
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_WALK);
				m_bCruch = false;
			}
			//Sを押したらしゃがみモーション
			else if ((key->GetKeyboardPress(DIK_S) || Pad_Y < -0.8f) && GetJump() == true)
			{
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_SQUATSTOP);
				m_bCruch = true;
			}
			//ジャンプ、しゃがみをしてなかったらニュートラル
			else
			{
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
				m_bCruch = false;
			}
		}
	}

	//ジャンプしたとき
	else if (GetModelSet()->GetMotionType() == CModelSet::PLAYER_MOTION_JUMP)
	{
		m_bCruch = false;

		//キーセットが３になったらストップモーションへ
		if (GetModelSet()->GetKeySet() == 3)
		{
			GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_JUMPSTOP);
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

	//しゃがんでいるかどうかで当たり判定の大きさ設定
	m_bCruch ?
		GetCollision()->SetSize2D(PLAYER_SIZE_CRUCH):	//しゃがみ時の当たり判定サイズ
		GetCollision()->SetSize2D(PLAYER_SIZE);			//通常時の当たり判定サイズ

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
		// ゲームオブジェクト( タグ )の設定
		GetCollision()->SetGameObject(this);

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

			// アイテムとの判定
			if (GetCollision()->ForPlayer_ItemCollision(GetTag()))
			{
			}
		}

		if (m_bRideVehicle == false)
		{
			m_pVehicle = (CVehicle*)GetCollision()->ForPlayer_VehicleCollision();

			// 乗り物との判定
			if (m_pVehicle)
			{
				// 乗り込んだ時
				m_bRideVehicle = true;
				m_pVehicle->SetTag(GetTag());
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

	if (m_pPad || key)
	{
		// 銃を撃つ or 近接攻撃
		if (key->GetKeyboardTrigger(DIK_U) || m_pPad->GetTrigger(m_pPad->JOYPADKEY_X, 1))
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
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_ATTACK01);
			}
		}
		// グレネードを投げる
		if (key->GetKeyboardTrigger(DIK_O) || m_pPad->GetTrigger(m_pPad->JOYPADKEY_Y, 1))
		{
			// グレネードの弾数が残っているとき
			if (m_pGrenadeFire->GetGrenadeAmmo() > 0)
			{
				// グレネード生成
				m_pGrenadeFire->Fire(GetShotDirection());

				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_GRENADE);
			}
		}
	}
	// 攻撃モーションから別のモーションになった時
	if (GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_ATTACK01)
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
	if (CHossoLibrary::PadMoveInput(MoveValue, GetCharacterDirection(), GetJump(), GetTag()))
	{
		//移動量計算
		Move(MoveValue.x, MoveValue.y);
	}

	D3DXVECTOR3 InputValue = ZeroVector3;

	if (m_pPad)
	{
		m_pPad->GetStickLeft(&InputValue.x, &InputValue.y);//パッドの入力値を代入

		InputValue.x /= STICK_MAX_RANGE;//値の正規化
		InputValue.y /= STICK_MAX_RANGE;//値の正規化
	}
	//ジャンプモーションじゃない時かつジャンプストップモーションじゃない時
	if (GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_JUMP &&
		GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_JUMPSTOP &&
		GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_ATTACK01)
	{
		//Sを押したらしゃがみモーション
		if (InputValue.y < -0.8f && GetJump() == true)
		{
			if (m_bCruch == false && GetModelSet()->GetMotionType() != CModelSet::PLAYER_MOTION_WALK)
			{
				GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_SQUATSTOP);
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
		GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
	}
	return true;
}
//====================================================================
//プレイヤーリスポーン処理
//====================================================================
void CPlayer::MapChangePlayerRespawn()
{
	SetState(CCharacter::CHARACTER_STATE_INVINCIBLE);

	if (GetTwoPPlayFlag())
	{
		for (int nCnt = 0; nCnt < PLAYER_NUM_MAX; nCnt++)
		{
			// プレイヤー2の配置
			SetPosition(GetPosition() + D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		}
	}
	else
	{
		SetPosition(m_pos[0]);
	}

	m_bRideVehicle = false;
	GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
}

//====================================================================
//プレイヤーリセット
//====================================================================
void CPlayer::ResetPlayer()
{
	D3DXVECTOR3 pos = D3DXVECTOR3(m_pos[0].x - 200.0f, m_pos[0].y, m_pos[0].z);
	SetPosition(pos);
	SetLife(m_nLife[0]);
	SetState(CCharacter::CHARACTER_STATE_INVINCIBLE);
	GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
	m_pGun->SetGunType(CGun::GUNTYPE_HANDGUN);
	m_pKnife->EndMeleeAttack();
	SetCharacterDirection(DIRECTION::RIGHT);
	m_pGrenadeFire->SetGrenadeAmmoDefault();
	m_bRideVehicle = false;
	m_bAttack = false;
	m_bCruch = false;
	m_bKnifeAttack = false;
	m_bRespawn = false;
}

//====================================================================
//ステートに応じた処理
//====================================================================
void CPlayer::State()
{
	//ステート切り替えた時のリアクション
	CCharacter::State();

	//Player側でオーバーライド
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_DAMAGE_FLASHING:
	case CHARACTER_STATE_INVINCIBLE:
	case CHARACTER_STATE_DEATH:
		GetCollision()->SetCanCollision(false);
		break;
	}
}

//====================================================================
//ダメージ時のリアクション
//====================================================================
void CPlayer::DamageReaction()
{
	//悲鳴
	CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_PLAYER_DAMAGE);

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
		GetModelSet()->ChangeColor(true, FlashColor);
		SetStateCount(3);
		break;

	case CHARACTER_STATE_DEATH:
		GetCollision()->SetCanCollision(false);
		SetStateCount(120);
		SetRespawnFlag(true);
		//悲鳴
		CManager::GetSound()->Play(CSound::LABEL_SE_VOICE_PLAYER_DEATH);

		GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_DEAD);
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
		//プレイヤーが乗り物から降りるとき
		if (key->GetKeyboardTrigger(DIK_SPACE)|| m_pPad->GetTrigger(m_pPad->JOYPADKEY_B,1) && GetJump() == false)
		{
			if(m_pVehicle != nullptr)
			{
				m_pVehicle->SetTag(TAG::NONE);
				m_pVehicle = nullptr;
			}
			m_bRideVehicle = false;
			GetMove().y += m_fRideJump;
			GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_JUMP);
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
		//残機が無い場合
		if (m_pPlayerUI->GetStock() <= 0)
		{
			//ゲームオーバー
			CManager::GetGame()->GetGameManager()->SetGameState(CGameManager::GAMESTATE::GAMEOVER);
		}
		else
		{
			//リセット
			m_nRespawnCnt = 0;
			m_bRespawn = false;
			m_pGun->SetGunType(CGun::GUNTYPE_HANDGUN);
			GetModelSet()->SetMotion(CModelSet::PLAYER_MOTION_NORMAL);
			SetState(CHARACTER_STATE_INVINCIBLE);
			SetLife(m_nLife[0]);
			m_pPlayerUI->SetStockUI(m_pPlayerUI->GetStock() - 1);
			m_pGrenadeFire->SetGrenadeAmmoDefault();
			m_pPlayerUI->SetGrenadeAmmo(m_pGrenadeFire->GetGrenadeAmmo());

		}
	}
}

//====================================================================
//モデルのクリエイト
//====================================================================
CPlayer *CPlayer::Create(TAG Tag)
{
	CPlayer*pPlayer;
	pPlayer = new CPlayer(OBJTYPE_PLAYER);
	pPlayer->SetTag(Tag);
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
	// 移動速度の情報を取得
	m_fRunSpeed = m_PlayerData.fRunSpeed;
	// しゃがみ時の移動速度の情報を取得
	m_fCrouchSpeed = m_PlayerData.fCrouchSpeed;
	// 通常時のジャンプ量
	m_fJump = m_PlayerData.fJump;
	// 乗り物から降りる時のジャンプ量
	m_fRideJump = m_PlayerData.fRideJump;
}
