// =====================================================================================================================================================================
//
// プレイヤーの戦車処理 [playertank.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "playertank.h"
#include "player.h"
#include "inputKeyboard.h"
#include "model.h"
#include "game.h"
#include "Xinput.h"
#include "gun.h"
#include "collision.h"
#include "BaseMode.h"
#include "manager.h"
#include "enemy.h"
#include "map.h"
#include "XInputPad.h"
#include "Obstacle.h"
#include "prisoner.h"
#include "grenadefire.h"
#include "sound.h"
#include "ModelSet.h"
#include "Character.h"
#include "particle.h"
//====================================================================
//マクロ定義
//====================================================================
#define PLAYERTANK_SIZE			(D3DXVECTOR3(90.0f,65.0f,90.0f)) // プレイヤーの判定のサイズ
#define PLAYERTANK_JUMP			(35.0f)				// 戦車が飛ぶ移動量
#define SHOT_BULLET_POS_X		(0.0f)			// 弾の発射位置X
#define SHOT_BULLET_POS_Y		(40.0f)				// 弾の発射位置Y
#define SHOT_BULLET_POS_Z		(0.0f)			// 弾の発射位置Z
#define PLAYERTANK_LIFE			(3)			// タンクのＨＰ
// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlayertank::CPlayertank(OBJ_TYPE type) :CCharacter(type)
{
	// オブジェクトの設定
	SetObjType(OBJTYPE_PLAYER_VEHICLE);
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CPlayertank::~CPlayertank()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CPlayertank::Init(void)
{
	// 乗り物の初期設定
	CCharacter::Init();

	//ライフ設定
	CCharacter::SetMaxLife(PLAYERTANK_LIFE);
	// オフセットの読み込み
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_TANK);
	// 乗り物のタイプの設定
	//SetVehicleType(CVehicle::VEHICLE_TYPE_TANK);
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_TANK);
	// 銃の生成
	m_pGun = CGun::Create();
	// グレネード放つ位置の生成
	m_pGrenadeFire = CGrenadeFire::Create();
	m_pGrenadeFire->SetGrenadeType(CGrenadeFire::TANK_GRENADE);
	m_pGrenadeFire->SetMtx(GetModelSet()->GetCharacterModelList()[0]->GetMatrix());

	// マトリックス設定
	//m_pGun->SetHandMtx(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKGUN)->GetMatrix());
	m_pGun->SetHandMtx(GetModelSet()->GetCharacterModelList()[3]->GetMatrix());
	// 銃の弾の種類
	m_pGun->SetTag(TAG::PLAYER_1);		// 仮止め)プレイヤー1、2どちらか入れる 変数?
	// 銃の弾の種類
	m_pGun->SetGunType(CGun::GUNTYPE_TANKGUN);
	// 発射位置のオフセットの設定
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(SHOT_BULLET_POS_X, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));
	// 地面についているかのフラグ
	m_bLand = true;
	//タグの初期化
	CVehicle::SetRideerTag(TAG::NONE);
	//初期化
	CCharacter::GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize(PLAYERTANK_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	return S_OK;
}

//====================================================================
//
// 終了
//
//====================================================================
void CPlayertank::Uninit(void)
{
	// 銃のポインタ
	if (m_pGun)
	{
		delete m_pGun;
		m_pGun = nullptr;
	}

	// グレネード発射位置のポインタ
	if (m_pGrenadeFire)
	{
		m_pGrenadeFire->Rerease();
		m_pGrenadeFire = nullptr;
	}

	CCharacter::Uninit();
}
//====================================================================
//
// 更新
//
//====================================================================
void CPlayertank::Update(void)
{
	// キー情報の取得
	CKeyboard *key = CManager::GetInputKeyboard();

	// 乗り物クラスの更新
	CCharacter::Update();

	//カウントアップ
	m_nCnt++;

	if (CVehicle::GetRideerTag() != TAG::NONE)
	{
		if (GetCharacterState() != CCharacter::CHARACTER_STATE_DEATH)
		{
			//自傷
			if (key->GetKeyboardTrigger(DIK_G))
			{
				AddDamage(1);
			}

			// 戦車が弾を撃つ処理
			Shot(key, GetRideerTag());

			// 戦車を操作する処理
			Operation(key, GetRideerTag());

			// 戦車の操作
			PadInput(GetRideerTag());

			// パーツの回転処理
			VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[1], MODEL_ROT_TYPE_MOVING,CCharacter::GetMove(),CCharacter::GetShotDirection(),CCharacter::GetCharacterDirection());
			VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[2], MODEL_ROT_TYPE_MOVING, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());
			VehiclePartsRotCondition(GetModelSet()->GetCharacterModelList()[3], MODEL_ROT_TYPE_OPERATION, CCharacter::GetMove(), CCharacter::GetShotDirection(), CCharacter::GetCharacterDirection());

			// 乗り物の判定
			GetCollision()->ForVehicleCollision();
			// 戦車の判定
			GetCollision()->ForTankCollision();

			//乗り物のSE
			TankSE();
		}
	}

	m_pGun->Update();


}
//====================================================================
//
// 描画
//
//====================================================================
void CPlayertank::Draw(void)
{
	//ガンのマトリックスの計算だけ
	m_pGun->NoDrawCalcMatrixOnly();
	GetModelSet();
	CCharacter::Draw();
}
//====================================================================
// デフォルトのモーション（使用なし）
//====================================================================
bool CPlayertank::DefaultMotion(void)
{
	return false;
}

//====================================================================
// デフォルトのモーション（使用なし）
//====================================================================
void CPlayertank::StateChangeReaction()
{
	CCharacter::StateChangeReaction();

	//ステータスの処理
	switch (GetCharacterState())
	{
	case CHARACTER_STATE_DEATH:
		SetStateCount(240);

		break;
	}
}

//====================================================================
// 死亡時のリアクション
//====================================================================
void CPlayertank::DeathReaction()
{
	//死亡フラグ
	SetDieFlag(true);

	//爆発発生
	CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_DANGERBOX);

	//プレイヤーが乗っていた場合
	if (GetRideerTag() == TAG::PLAYER_1 || GetRideerTag() == TAG::PLAYER_1)
	{
		//プレイヤーのポインタ取得
		CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(GetRideerTag());

		pPlayer->SetRideFlag(false);

		pPlayer->AddDamage(999);
	}
}

//====================================================================
// デバッグ
//====================================================================
void CPlayertank::DebugInfo(void)
{
	CCharacter::DebugInfo();

	//debug
	CDebugProc::Print_Left("PlayerTankLife >> %d", GetLife());

}

//====================================================================
// 戦車モデルのクリエイト
//====================================================================
CPlayertank *CPlayertank::Create(void)
{
	// メモリの確保
	CPlayertank *pPlayertank = new CPlayertank(OBJTYPE_PLAYER_VEHICLE);
	// 初期化
	pPlayertank->Init();
	// ポインタを返す
	return pPlayertank;
}

//====================================================================
// 弾を打つ処理
//====================================================================
void CPlayertank::Shot(CKeyboard *key, TAG Tag)
{
	CXInputPad *pXInput = CManager::GetPad(Tag);

	// 弾を撃つ方向を設定
	// モデルの回転の向きと弾の発射方向の計算の回転を合わせる
	m_pGun->SetShotRot(D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[3]->GetRot().x)));

	// マシンガンを撃つ
	if (key->GetKeyboardTrigger(DIK_U) || pXInput->GetTrigger(CXInputPad::JOYPADKEY_X, 1))
	{
		// ガンのモデルの発射口から弾を生成
		m_pGun->Shot();
	}
	// グレネードを撃つ
	if (key->GetKeyboardTrigger(DIK_O) || pXInput->GetTrigger(CXInputPad::JOYPADKEY_Y, 1))
	{
		// グレネードの弾数が残っているとき
		if (m_pGrenadeFire->GetGrenadeAmmo() > 0)
		{
			// グレネード生成
			m_pGrenadeFire->Fire(GetShotDirection());
		}
	}
}

//====================================================================
// パッドの入力
//====================================================================
void CPlayertank::PadInput(TAG Tag)
{
	D3DXVECTOR3 MoveValue = ZeroVector3;

	if (CHossoLibrary::PadMoveInput(MoveValue, CCharacter::GetCharacterDirection(), false, Tag))
	{
		CCharacter::Move(MoveValue.x, -0.5f);
	}

}
//====================================================================
// 戦車の効果音
//====================================================================
void CPlayertank::TankSE()
{
	//一定周期
	if (m_nCnt % 10 == 1)
	{
		//エンジン音再生
		CManager::GetSound()->Play(CSound::LABEL_SE_TANK_ENGINE);

		//横移動しててジャンプしてない時
		if (fabsf(GetMove().x) >= 1.0f && !GetJump())
		{
			//音再生
			CManager::GetSound()->Play(CSound::LABEL_SE_TANK_CATERPILLAR);
		}
	}
}
//====================================================================
// ステートに応じた処理
//====================================================================
void CPlayertank::State()
{
	CCharacter::State();

	//ステータスの処理
	switch (GetCharacterState())
	{
	case CHARACTER_STATE_DEATH:
		if (m_nCnt % 4 < 2)
		{
			CCharacter::GetModelSet()->ChangeColor(true, D3DXCOLOR(1.0f, 1.0f, 0.0f, 1.0f));
		}
		else
		{
			CCharacter::GetModelSet()->ChangeColor(true, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		}

		//当たり判定けす
		GetCollision()->SetCanCollision(false);
		 
		break;
	}
}

//====================================================================
// 操作処理
//====================================================================
void CPlayertank::Operation(CKeyboard * key, TAG Tag)
{
	CXInputPad *pXInput = CManager::GetPad(Tag);

	// 上を向く
	if (key->GetKeyboardPress(DIK_W))
	{
		SetCharacterDirection(DIRECTION::UP);
	}
	// 上を向く
	else if (key->GetKeyboardPress(DIK_S))
	{
		SetCharacterDirection(DIRECTION::DOWN);
	}

	// 左に動かせる
	if (key->GetKeyboardPress(DIK_A))
	{
		if (m_bLand == true)
		{
			CCharacter::Move(0.5f, -0.5f);
		}
		else if(m_bLand == false)
		{
			CCharacter::Move(0.5f, -0.5f);
		}

		// 上を向く
		if (key->GetKeyboardPress(DIK_W))
		{
			SetCharacterDirection(DIRECTION::UP);
		}

		// 下を向く
		else if (key->GetKeyboardPress(DIK_S))
		{
			SetCharacterDirection(DIRECTION::DOWN);
		}

		// 左を向く
		else
		{
			SetCharacterDirection(DIRECTION::LEFT);
		}
	}

	// 右に動かせる
	else if (key->GetKeyboardPress(DIK_D))
	{
		if (m_bLand == true)
		{
			CCharacter::Move(-0.5f, -0.5f);
		}
		else if (m_bLand == false)
		{
			CCharacter::Move(-0.5f, -0.5f);
		}
		// 上を向く
		if (key->GetKeyboardPress(DIK_W))
		{
			SetCharacterDirection(DIRECTION::UP);
		}

		// 下を向く
		else if (key->GetKeyboardPress(DIK_S))
		{
			SetCharacterDirection(DIRECTION::DOWN);
		}

		// 右を向く
		else
		{
			SetCharacterDirection(DIRECTION::RIGHT);
		}
	}

	// ジャンプ処理
	if (key->GetKeyboardTrigger(DIK_UP) || pXInput->GetTrigger(CXInputPad::JOYPADKEY_A, 1))
	{
		// 1回ジャンプさせる
		Jump();
	}
}

//====================================================================
// ジャンプ処理
//====================================================================
void CPlayertank::Jump()
{
	if (GetJump() == false)
	{
		GetMove().y += PLAYERTANK_JUMP;
	}

	// ジャンプフラグをtrueにしジャンプできなくする
	SetJump(true);
}

//====================================================================
// 当たり判定
//====================================================================
void CPlayertank::Collision()
{
	// 当たり判定
	if (GetCollision() != nullptr)
	{
		// 座標の更新 posとposold
		GetCollision()->SetPos(&GetPosition());
		GetCollision()->SetPosOld(&GetPositionOld());

		 //障害物との判定
		if (GetCollision()->ForPlayer_ObstacleCollision())
		{
			// ジャンプフラグを可能にする
			CCharacter::SetJump(true);
		}
	}

	// マップのポインタ取得
	CMap *pMap;
	pMap = CManager::GetBaseMode()->GetMap();

	// マップモデルが存在した時
	if (pMap != nullptr)
	{
		// レイの判定
		if (GetCollision()->RayBlockCollision(pMap, GetMtxWorld()))
		{
			// ジャンプすることを承認する
			SetJump(false);

			m_bLand = true;
			// マップモデルの斜面の角度に車体を傾ける
			//
		}
		else
		{
			m_bLand = false;
			// ジャンプすることを承認しない
			SetJump(true);

		}
	}
}
