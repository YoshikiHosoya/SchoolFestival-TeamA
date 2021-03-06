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

//====================================================================
//マクロ定義
//====================================================================
#define PLAYERTANK_SIZE			(D3DXVECTOR3(90.0f,65.0f,0.0f)) // プレイヤーの判定のサイズ
#define PLAYERTANK_JUMP			(60.0f)				// 戦車が飛ぶ移動量
#define SHOT_BULLET_POS_X		(0.0f)			// 弾の発射位置X
#define SHOT_BULLET_POS_Y		(40.0f)				// 弾の発射位置Y
#define SHOT_BULLET_POS_Z		(0.0f)			// 弾の発射位置Z

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CPlayertank::CPlayertank(OBJ_TYPE type) :CVehicle(type)
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
	CVehicle::Init();
	// オフセットの読み込み
	LoadOffset(CVehicle::VEHICLE_TYPE_TANK);
	// 乗り物のタイプの設定
	SetVehicleType(CVehicle::VEHICLE_TYPE_TANK);
	// 銃の生成
	m_pGun = CGun::Create(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKGUN)->GetMatrix());
	// グレネード放つ位置の生成
	m_pGrenadeFire = CGrenadeFire::Create(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKBODY)->GetMatrix());
	// 銃の弾の種類
	m_pGun->GetTag() = TAG_PLAYER;
	// 銃の弾の種類
	m_pGun->SetGunType(CGun::GUNTYPE_TANKGUN);
	// 発射位置のオフセットの設定
	m_pGun->SetShotOffsetPos(D3DXVECTOR3(SHOT_BULLET_POS_X, SHOT_BULLET_POS_Y, SHOT_BULLET_POS_Z));
	// 地面についているかのフラグ
	m_bLand = true;
	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetPosOld(&GetPositionOld());
	GetCollision()->SetSize2D(PLAYERTANK_SIZE);
	GetCollision()->SetMove(&GetMove());
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

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

	// プレイヤーのポインタを取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	if (pPlayer != nullptr)
	{
		pPlayer->SetRideFlag(false);
	}

	CVehicle::Uninit();
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

	// プレイヤーのポインタを取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	if (pPlayer != nullptr)
	{
		// 乗り物に乗っている時
		if (pPlayer->GetRideFlag())
		{
			// 戦車が弾を撃つ処理
			Shot(key);

			// 戦車を操作する処理
			Operation(key);

			// 戦車の操作
			PadInput();

			// パーツの回転処理
			VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_TANK_TANK_FRONTWHEEL), MODEL_ROT_TYPE_MOVING);
			VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_TANK_TANK_BACKWHEEL), MODEL_ROT_TYPE_MOVING);
			VehiclePartsRotCondition(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKGUN), MODEL_ROT_TYPE_OPERATION);

			// 乗り物の判定
			GetCollision()->ForVehicleCollision();
			// 戦車の判定
			GetCollision()->ForTankCollision();
		}
	}

	// 判定をまとめて行う
	Collision();

	m_pGun->Update();


	// 乗り物クラスの更新
	CVehicle::Update();
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

	CVehicle::Draw();
}

//====================================================================
// デバッグ
//====================================================================
void CPlayertank::DebugInfo(void)
{
	CVehicle::DebugInfo();
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
void CPlayertank::Shot(CKeyboard *key)
{
	CXInputPad *pXInput = CManager::GetPad();

	// マシンガンを撃つ
	if (key->GetKeyboardTrigger(DIK_P) || pXInput->GetTrigger(CXInputPad::JOYPADKEY_X, 1))
	{
		// ガンのモデルの発射口から弾を生成
		m_pGun->Shot();
	}
	// 弾を撃つ方向を設定
	m_pGun->SetShotRot(GetVehicleModelPartsList(CModel::MODEL_TANK_TANKGUN)->GetRot());

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
void CPlayertank::PadInput()
{
	D3DXVECTOR3 MoveValue = ZeroVector3;

	if (CHossoLibrary::PadMoveInput(MoveValue, GetVehicleDirection(), false))
	{
		Move(MoveValue.x, -0.5f);
	}

}

//====================================================================
// 操作処理
//====================================================================
void CPlayertank::Operation(CKeyboard * key)
{
	CXInputPad *pXInput = CManager::GetPad();

	// 上を向く
	if (key->GetKeyboardPress(DIK_W))
	{
		SetVehicleDirection(DIRECTION::UP);
	}
	// 上を向く
	else if (key->GetKeyboardPress(DIK_S))
	{
		SetVehicleDirection(DIRECTION::DOWN);
	}

	// 左に動かせる
	if (key->GetKeyboardPress(DIK_A))
	{
		if (m_bLand == true)
		{
			CVehicle::Move(0.5f, -0.5f);
		}
		else if(m_bLand == false)
		{
			CVehicle::Move(0.3f, -0.5f);
		}

		// 上を向く
		if (key->GetKeyboardPress(DIK_W))
		{
			SetVehicleDirection(DIRECTION::UP);
		}

		// 下を向く
		else if (key->GetKeyboardPress(DIK_S))
		{
			SetVehicleDirection(DIRECTION::DOWN);
		}

		// 左を向く
		else
		{
			SetVehicleDirection(DIRECTION::LEFT);
		}
	}

	// 右に動かせる
	else if (key->GetKeyboardPress(DIK_D))
	{
		if (m_bLand == true)
		{
			CVehicle::Move(-0.5f, -0.5f);
		}
		else if (m_bLand == false)
		{
			CVehicle::Move(-0.3f, -0.5f);
		}
		// 上を向く
		if (key->GetKeyboardPress(DIK_W))
		{
			SetVehicleDirection(DIRECTION::UP);
		}

		// 下を向く
		else if (key->GetKeyboardPress(DIK_S))
		{
			SetVehicleDirection(DIRECTION::DOWN);
		}

		// 右を向く
		else
		{
			SetVehicleDirection(DIRECTION::RIGHT);
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

		// 障害物との判定
		//if (GetCollision()->ForPlayer_ObstacleCollision())
		//{
		//	// ジャンプフラグを可能にする
		//	CVehicle::SetJump(true);
		//}
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
