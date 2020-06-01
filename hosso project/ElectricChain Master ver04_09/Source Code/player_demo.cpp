//------------------------------------------------------------------------------
//
//デモ用のプレイヤー処理  [player_demo.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "player_demo.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "gauge_2D.h"
#include "effectanimation3D.h"
#include "game.h"
#include "sphere_explosion.h"
#include "enemy.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CPlayer_Demo::CPlayer_Demo()
{
	m_AttackInput = CPlayer_Demo::ATTACK_NONE;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CPlayer_Demo::~CPlayer_Demo()
{
	m_pTargetEnemy.reset();
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CPlayer_Demo::Init()
{
	CCharacter::Init();

	//成功
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CPlayer_Demo::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CPlayer_Demo::Update()
{
	//生きてる時
	if (GetAlive())
	{
		switch (GetNowMotion())
		{
		case CMotion::PLAYER_NEUTRAL:
		case CMotion::PLAYER_WALK:
		case CMotion::PLAYER_DASH:
			if (GetJump())
			{
				ChangeMotion(CMotion::PLAYER_AIR_NEUTRAL);
			}
			SetChainThunder(false);
			SetAttack(false);
			break;
		}

		//ダメージ受けてない時
		if (CCharacter::GetNowMotion() != CMotion::PLAYER_HIT)
		{
			//移動の入力処理
			MoveAI();

			//モーション切り替え
			MoveMotionCheck();
		}

		//雷発生状態
		if (GetChainThunder())
		{
			//雷のエフェクト
			ChainThunder();
		}
	}

	//更新
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CPlayer_Demo::Draw()
{
	CCharacter::Draw();
}

//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CPlayer_Demo::ShowDebugInfo()
{
#ifdef _DEBUG


#endif //DEBUG
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
std::shared_ptr<CPlayer_Demo> CPlayer_Demo::Create(D3DXVECTOR3 pos)
{
	//変数宣言
	std::shared_ptr<CPlayer_Demo> pPlayer_Demo = std::make_shared<CPlayer_Demo>();

	if (pPlayer_Demo)
	{
		//初期化7
		pPlayer_Demo->Init();

		//座標設定
		pPlayer_Demo->SetPos(pos);

		//パラメータ設定
		pPlayer_Demo->SetParameter(CHARACTER_PLAYER,CCharacter::PARAM_PLAYER, pPlayer_Demo);

		//オブジェクトタイプ設定
		pPlayer_Demo->SetObjType(OBJTYPE_PLAYER);

		//リストに追加
		pPlayer_Demo->AddSharedList(pPlayer_Demo);

		return pPlayer_Demo;
	}

	//生成した情報
	return nullptr;
}

//------------------------------------------------------------------------------
//移動の入力
//------------------------------------------------------------------------------
void CPlayer_Demo::MoveAI()
{
	D3DXVECTOR3 &rMove = GetMove();		//移動情報取得
	D3DXVECTOR3 &rRotdest = GetRotDest();	//回転情報取得
	D3DXVECTOR3 posDif = ZeroVector3;
	float fAngle = 0.0f;
	float fLength = 0.0f;

	//とりあえず敵の情報取得
	if (m_pTargetEnemy._Get())
	{
		if (m_pTargetEnemy._Get()->GetStan())
		{
			SetTargetEnemy();
		}
	}
	else
	{
		SetTargetEnemy();
	}

	//敵ターゲットの敵がいるとき
	if (m_pTargetEnemy._Get())
	{
		//敵との距離計測
		posDif = m_pTargetEnemy._Get()->GetPos() - GetPos();
		fAngle = atan2f(posDif.x, posDif.z);
		fLength = D3DXVec3Length(&posDif);
	}
	else
	{
		return;
	}

	if (CEnemy::GetEnemyNum() == CEnemy::GetStanEnemyNum() && !GetChainThunder())
	{
		ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
		StartChainThunder();
		SetAirAttack(true);
		m_pTargetEnemy.reset();
	}

	if (!GetAttack())
	{
		//移動速度
		float fMoveSpeed;

		//ダッシュしているか確認
		fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetDashSpeed();		//基本ダッシュで

		//ジャンプ状態の場合
		if (GetJump())
		{
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetAirSpeeed();			//空中の移動速度
		}

		//カメラ回転情報取得
		float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

		//移動
		rMove.x += sinf(fAngle) * fMoveSpeed;
		rMove.z += cosf(fAngle) * fMoveSpeed;

		rRotdest.y = D3DX_PI + fAngle;

		CHossoLibrary::CalcRotation(rRotdest.y);

		//回転処理
		CCharacter::SetRotDest(rRotdest);
	}

	//ジャンプキー
	if (CHossoLibrary::CheckJump(CHossoLibrary::TRIGGER))
	{
		if (!GetJump())
		{
			//移動情報取得
			D3DXVECTOR3 &rMove = GetMove();

			//上方向に進む
			rMove.y = GetDefaultParam(CCharacter::GetParamType())->GetJumpSpeed();

			//ジャンプに切り替え
			SetJump(true);
			ChangeMotion(CMotion::PLAYER_JUMP);
		}
	}

	//ターゲットの敵との距離が一定以下になった時
	if (fLength < 200.0f)
	{
		//乱数
		int nAttackRand = rand() % 5;

		if (nAttackRand <= 3)
		{
			//Xの入力
			m_AttackInput = CPlayer_Demo::ATTACK_X;
		}
		else
		{
			//Yの入力
			m_AttackInput = CPlayer_Demo::ATTACK_Y;
		}

		//攻撃の入力
		if (AttackInput())
		{
			//回転
			rRotdest.y = fAngle + D3DX_PI;
			SetAttack(true);
		}
	}
}
//------------------------------------------------------------------------------
//連続攻撃の次のモーションどれだ
//------------------------------------------------------------------------------
bool CPlayer_Demo::AttackInput()
{
	bool bAttack = false;	//return用
	CMotion::MOTION_TYPE NowMotion = GetNowMotion();		//現在のモーション取得

	//現在のモーションに応じて次のモーションを決める
	switch (NowMotion)
	{
	case CMotion::PLAYER_NEUTRAL:
	case CMotion::PLAYER_WALK:
	case CMotion::PLAYER_DASH:
		if (m_AttackInput == CPlayer_Demo::ATTACK_X)
		{
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_01);
			return true;
		}
		if (m_AttackInput == CPlayer_Demo::ATTACK_Y)
		{
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_01);
			return true;
		}
		if (m_AttackInput == CPlayer_Demo::ATTACK_B)
		{
			ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
			StartChainThunder();
			return true;
		}
		break;
	case CMotion::PLAYER_AIR_NEUTRAL:
	case CMotion::PLAYER_JUMP:
		if (m_AttackInput == CPlayer_Demo::ATTACK_X)
		{
			if (!GetAirAttack())
			{
				ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_01);
				SetAirAttack(true);
				SetGravity(false, 17);

				return true;
			}
		}
		if (m_AttackInput == CPlayer_Demo::ATTACK_Y)
		{
			ChangeMotion(CMotion::PLAYER_ATTACK_SLAMS);
			GetMove().y = 0.0f;
			SetGravity(false, 5);
			return true;
		}
		if (m_AttackInput == CPlayer_Demo::ATTACK_B)
		{
			if (!GetAirAttack())
			{
				ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
				StartChainThunder();
				SetAirAttack(true);
				return true;
			}
		}
		break;
	}

	//続けて攻撃できる状態か確認
	if (!ContinueAttack())
	{
		return false;
	}


	if (m_AttackInput == CPlayer_Demo::ATTACK_X)
	{
		switch (NowMotion)
		{

		case CMotion::PLAYER_LAND_ATTACK_X_01:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_02);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_X_02:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_03);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_X_03:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_04);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_X_04:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_05);
			bAttack = true;
			break;

			//空中
		case CMotion::PLAYER_AIR_ATTACK_X_01:
			ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_02);
			SetGravity(false, 17);
			bAttack = true;
			break;

		case CMotion::PLAYER_AIR_ATTACK_X_02:
			ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_03);
			SetGravity(false, 17);
			bAttack = true;
			break;

		case CMotion::PLAYER_AIR_ATTACK_X_03:
			ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_04);
			SetGravity(false, 30);
			bAttack = true;
			break;

		}
	}

	if (m_AttackInput == CPlayer_Demo::ATTACK_Y)
	{

		switch (NowMotion)
		{
		case CMotion::PLAYER_LAND_ATTACK_X_03:
		case CMotion::PLAYER_LAND_ATTACK_X_04:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_02);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_Y_01:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_SPEAR);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_Y_02:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_03);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_Y_03:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_04);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_Y_04:
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_05);
			bAttack = true;
			break;

		case CMotion::PLAYER_LAND_ATTACK_X_01:
		case CMotion::PLAYER_LAND_ATTACK_X_02:
			ChangeMotion(CMotion::PLAYER_ATTACK_UPPER);
			SetAirAttack(true);
			break;
		}
	}


	if (m_AttackInput == CPlayer_Demo::ATTACK_Y)
	{
		switch (NowMotion)
		{
		case CMotion::PLAYER_AIR_ATTACK_X_01:
		case CMotion::PLAYER_AIR_ATTACK_X_02:
		case CMotion::PLAYER_AIR_ATTACK_X_03:
		case CMotion::PLAYER_AIR_ATTACK_X_04:
			ChangeMotion(CMotion::PLAYER_ATTACK_SLAMS);
			bAttack = true;
			break;
		}
	}
	if (m_AttackInput == CPlayer_Demo::ATTACK_B)
	{
		switch (NowMotion)
		{
		case CMotion::MOTION_NONE:
			break;
		case CMotion::PLAYER_LAND_ATTACK_X_01:
		case CMotion::PLAYER_LAND_ATTACK_X_02:
		case CMotion::PLAYER_LAND_ATTACK_X_03:
		case CMotion::PLAYER_LAND_ATTACK_X_04:
		case CMotion::PLAYER_LAND_ATTACK_X_05:
		case CMotion::PLAYER_LAND_ATTACK_Y_01:
		case CMotion::PLAYER_LAND_ATTACK_Y_02:
		case CMotion::PLAYER_LAND_ATTACK_Y_03:
		case CMotion::PLAYER_LAND_ATTACK_Y_04:
		case CMotion::PLAYER_LAND_ATTACK_Y_05:
		case CMotion::PLAYER_LAND_ATTACK_Y_SPEAR:
		case CMotion::PLAYER_JUMP:
		case CMotion::PLAYER_ATTACK_UPPER:
		case CMotion::PLAYER_ATTACK_SLAMS:
		case CMotion::PLAYER_AIR_ATTACK_X_01:
		case CMotion::PLAYER_AIR_ATTACK_X_02:
		case CMotion::PLAYER_AIR_ATTACK_X_03:
		case CMotion::PLAYER_AIR_ATTACK_X_04:
			ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
			StartChainThunder();
			SetAirAttack(true);
			bAttack = true;
			break;

		}
	}
	return bAttack;
}

//------------------------------------------------------------------------------
//敵のターゲット設定
//------------------------------------------------------------------------------
void CPlayer_Demo::SetTargetEnemy()
{
	//シーンのリスト
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//シーン情報取得
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

	//配列に入ってるか
	if (!pSceneList.empty())
	{
		//要素分
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//ポインタ取得 CEnemy型にダウンキャスト
			std::shared_ptr<CEnemy> pEnemy = std::static_pointer_cast<CEnemy>(pSceneList[nCnt]);
			//nullcheck
			if (pEnemy)
			{
				//スタン状態じゃないやつ
				if (!pEnemy->GetStan())
				{
					//ターゲット設定
					m_pTargetEnemy = pEnemy;
					return;
				}
			}
		}
	}
}


