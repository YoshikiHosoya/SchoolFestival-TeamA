//------------------------------------------------------------------------------
//
//プレイヤー処理  [player.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "player.h"
#include "keyboard.h"
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "sound.h"
#include "gauge_2D.h"
#include "effectanimation3D.h"
#include "game.h"
#include "sphere_explosion.h"
#include "effectanimation2D.h"
#include "modelcharacter.h"
#include "enemy.h"
#include "frontUI.h"
#include "circle_effect.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
bool CPlayer::m_bClearedAlive = true;
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CPlayer::CPlayer()
{
	m_nCntChainThunder = 0;
	m_bChainThunder = false;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CPlayer::~CPlayer()
{
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CPlayer::Init()
{
	//初期化
	CCharacter::Init();

	switch (CManager::GetMode())
	{
		//ゲームかチュートリアル開始時には生存状態にしておく
	case CManager::MODE_GAME:
	case CManager::MODE_TUTORIAL:
		m_bClearedAlive = true;
	}

	//成功
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CPlayer::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CPlayer::Update()
{
	//リザルトのときはモーション固定　移動もできないように
	if (CManager::GetMode() == CManager::MODE_RESULT)
	{
		//ゲームクリア時に生きていた時
		if (m_bClearedAlive)
		{
			//まだ雷撃ってない時
			if (!m_bChainThunder)
			{
				//雷を撃つ
				StartChainThunder();
			}
			//雷撃ってる状態のとき
			else if (m_bChainThunder)
			{
				//雷のエフェクト処理
				ChainThunder();

				//現在ニュートラルの時
				if (GetNowMotion() == CMotion::PLAYER_NEUTRAL)
				{
					//リザルト用のモーションセット
					ChangeMotion(CMotion::PLAYER_RESULT);
				}
			}
		}
		//ゲームクリア時に死んでいた時
		else
		{
			//倒れておく
			ChangeMotion(CMotion::PLAYER_DEATH);
		}
	}

	//生きてる時
	else if (GetAlive())
	{
		//現在のモーション
		switch (GetNowMotion())
		{
			//ニュートラルか歩くかダッシュ中の時
		case CMotion::PLAYER_NEUTRAL:
		case CMotion::PLAYER_WALK:
		case CMotion::PLAYER_DASH:

			//ジャンプ中
			if (GetJump())
			{
				//空中のニュートラル状態
				ChangeMotion(CMotion::PLAYER_AIR_NEUTRAL);
			}
			//連鎖爆発状態解除
			m_bChainThunder = false;
			SetAttack(false);
			break;
		}

		//ダメージ受けてない時
		if (CCharacter::GetNowMotion() != CMotion::PLAYER_HIT)
		{
			//gameのとき
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				//ゲームクリア中は入力できないようにする
				if (CManager::GetGame()->GetGamestate() == CGame::STATE_GAMECLEAR)
				{
					//ニュートラルモーション
					ChangeMotion(CMotion::PLAYER_NEUTRAL);
				}
				else
				{
					//移動の入力処理
					MoveInput();
				}
			}
			else
			{
				//移動の入力処理
				MoveInput();
			}
		}

		//雷撃ってる状態のとき
		if(m_bChainThunder)
		{
			//雷のエフェクト処理
			ChainThunder();
		}
	}

	//更新
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CPlayer::Draw()
{
	CCharacter::Draw();
}

//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CPlayer::ShowDebugInfo()
{
#ifdef _DEBUG
	//プレイヤー情報情報
	if (ImGui::TreeNode("PlayerInfo"))
	{
		//キャラクター情報表示
		ShowCharacterInfo();

		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//ダメージ受けた後の処理
//------------------------------------------------------------------------------
void CPlayer::DamageAction()
{
	//音再生
	CManager::GetSound()->Play(CSound::LABEL_SE_SLASH_PLAYER);

	//周り赤く
	CFrontUI::Create(SCREEN_CENTER_POS, SCREEN_SIZE, WhiteColor, CFrontUI::PLAYER_HIT);

	//nullcheck
	if (m_pGauge)
	{
		//ゲージ更新
		m_pGauge->SetLife(GetLife(), GetBlueLife());
	}

	//被弾モーション
	ChangeMotion(CMotion::PLAYER_HIT);
}
//------------------------------------------------------------------------------
//死亡時の処理
//------------------------------------------------------------------------------
void CPlayer::DeathAction()
{
	//ゲーム終了
	CManager::GetGame()->SetGamestate(CGame::STATE_GAMECLEAR);
	m_bClearedAlive = false;
}
//------------------------------------------------------------------------------
//ステート変更処理
//------------------------------------------------------------------------------
void CPlayer::SetState(STATE nextstate)
{
	CCharacter::SetState(nextstate);
	switch (nextstate)
	{
	case CCharacter::STATE_NORMAL:
		break;
	case CCharacter::STATE_DAMAGE:
		break;
	case CCharacter::STATE_STAN:
		break;
		//死亡時
	case CCharacter::STATE_DEATH:
		//ゲーム終了を表示するまでのカウント
		SetCntState(240);

		//死亡モーション
		ChangeMotion(CMotion::PLAYER_DEATH);
		break;
	}
}
//------------------------------------------------------------------------------
//連鎖開始
//------------------------------------------------------------------------------
void CPlayer::StartChainThunder()
{
	//無重力設定
	SetGravity(false, 50);

	//移動量を全部消す
	GetMove() = ZeroVector3;

	//モーション変更と雷発生状態開始
	ChangeMotion(CMotion::PLAYER_ATTACK_THUNDER);
	m_bChainThunder = true;
	m_nCntChainThunder = 0;
}

//------------------------------------------------------------------------------
//攻撃時の旋回
//------------------------------------------------------------------------------
void CPlayer::AttackTurning()
{
	//カメラ回転情報取得
	float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

	//現在の回転の決定地取得
	D3DXVECTOR3 &rRotdest = GetRotDest();

	//スティックで入力された時
	if (!CHossoLibrary::Check3DMoveStick(ZeroVector3, 1.0f, fCameraRot, rRotdest.y))
	{
		//なんかしらのキーが入力された場合
		if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT) || CHossoLibrary::CheckMove(CHossoLibrary::RIGHT) ||
			CHossoLibrary::CheckMove(CHossoLibrary::UP) || CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT))
			{
				if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
				{
					rRotdest.y = D3DX_PI * 0.75f + fCameraRot;
				}
				else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
				{
					rRotdest.y = D3DX_PI * 0.25f + fCameraRot;
				}
				else
				{
					rRotdest.y = D3DX_PI * 0.5f + fCameraRot;
				}
			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::RIGHT))
			{
				if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
				{
					rRotdest.y = -D3DX_PI * 0.75f + fCameraRot;
				}
				else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
				{
					rRotdest.y = -D3DX_PI * 0.25f + fCameraRot;
				}
				else
				{
					rRotdest.y = -D3DX_PI * 0.5f + fCameraRot;
				}
			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
			{
				rRotdest.y = -D3DX_PI * 1.0f + fCameraRot;

			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
			{
				rRotdest.y = fCameraRot;
			}
		}
	}
}
//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
std::shared_ptr<CPlayer> CPlayer::Create(D3DXVECTOR3 pos)
{
	//変数宣言
	std::shared_ptr<CPlayer> pPlayer = std::make_shared<CPlayer>();

	if (pPlayer)
	{
		//初期化7
		pPlayer->Init();

		//座標設定
		pPlayer->SetPos(pos);

		//パラメータ設定
		pPlayer->SetParameter(MODEL_TYPE::MODEL_PLAYER,CCharacter::PARAM_PLAYER,pPlayer);

		//オブジェクトタイプ設定
		pPlayer->SetObjType(OBJTYPE_PLAYER);

		//リストに追加
		pPlayer->AddSharedList(pPlayer);

		//ゲームの時だけ
		if(CManager::GetMode() == CManager::MODE_GAME)
		{
			//HPゲージ生成
			pPlayer->m_pGauge = CGauge_2D::Create(D3DXVECTOR3(250.0f, 680.0f, 0.0f), D3DXVECTOR3(200.0f, 20.0f, 0.0f), pPlayer->GetLife());
		}

		return pPlayer;
	}

	//生成した情報
	return nullptr;
}

//------------------------------------------------------------------------------
//移動の入力
//------------------------------------------------------------------------------
void CPlayer::MoveInput()
{
	D3DXVECTOR3 &rMove = GetMove();		//移動情報取得
	D3DXVECTOR3 &rRotdest = GetRotDest();	//回転情報取得

	if (!GetAttack())
	{
		//移動速度
		float fMoveSpeed;

		//ダッシュしているか確認
		CHossoLibrary::CheckDash(CHossoLibrary::PRESS) ?
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetDashSpeed() :		//歩く速度
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetMoveSpeed();			//ダッシュ速度

		//ジャンプ状態の場合
		if (GetJump())
		{
			fMoveSpeed = GetDefaultParam(CCharacter::GetParamType())->GetAirSpeeed();			//空中の移動速度
		}

		//カメラ回転情報取得
		float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

		//JoyStickによる入力
		//入力がなかった場合はキーボードから取得
		if (!CHossoLibrary::Check3DMoveStick(rMove, fMoveSpeed, fCameraRot, rRotdest.y))
		{
			if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT))
			{
				if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
				{
					//左上
					rMove.x += sinf(-D3DX_PI * 0.75f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(-D3DX_PI * 0.75f - fCameraRot) * fMoveSpeed;

					rRotdest.y = D3DX_PI * 0.75f + fCameraRot;
				}
				else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
				{
					//左下
					rMove.x += sinf(-D3DX_PI * 0.25f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(-D3DX_PI * 0.25f - fCameraRot) * fMoveSpeed;

					rRotdest.y = D3DX_PI * 0.25f + fCameraRot;
				}
				else
				{
					//左
					rMove.x += sinf(-D3DX_PI * 0.5f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(-D3DX_PI * 0.5f - fCameraRot) * fMoveSpeed;

					rRotdest.y = D3DX_PI * 0.5f + fCameraRot;
				}
			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::RIGHT))
			{
				if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
				{
					//右上
					rMove.x += sinf(D3DX_PI * 0.75f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(D3DX_PI * 0.75f - fCameraRot) * fMoveSpeed;

					rRotdest.y = -D3DX_PI * 0.75f + fCameraRot;
				}
				else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
				{
					//右下
					rMove.x += sinf(D3DX_PI * 0.25f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(D3DX_PI * 0.25f - fCameraRot) * fMoveSpeed;

					rRotdest.y = -D3DX_PI * 0.25f + fCameraRot;
				}
				else
				{
					//右
					rMove.x += sinf(D3DX_PI * 0.5f - fCameraRot) * fMoveSpeed;
					rMove.z -= cosf(D3DX_PI * 0.5f - fCameraRot) * fMoveSpeed;

					rRotdest.y = -D3DX_PI * 0.5f + fCameraRot;

				}
			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
			{
				//上
				rMove.x += sinf(D3DX_PI * 1.0f - fCameraRot) * fMoveSpeed;
				rMove.z -= cosf(D3DX_PI * 1.0f - fCameraRot) * fMoveSpeed;

				rRotdest.y = -D3DX_PI * 1.0f + fCameraRot;

			}
			else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
			{
				//下
				rMove.x += sinf(D3DX_PI * 0 - fCameraRot) * fMoveSpeed;
				rMove.z -= cosf(D3DX_PI * 0 - fCameraRot) * fMoveSpeed;

				rRotdest.y = fCameraRot;
			}
		}
		//回転処理
		CCharacter::SetRotDest(rRotdest);
	}

	//ジャンプキー
	if (CHossoLibrary::CheckJump(CHossoLibrary::TRIGGER))
	{
		//まだジャンプしていない&&雷発生していない時
		if (!GetJump() && !m_bChainThunder)
		{
			//移動情報取得
			D3DXVECTOR3 &rMove = GetMove();

			//上方向に進む
			rMove.y = GetDefaultParam(CCharacter::GetParamType())->GetJumpSpeed();

			//ジャンプに切り替え
			SetJump(true);
			ChangeMotion(CMotion::PLAYER_JUMP);

			//音再生
			CManager::GetSound()->Play(CSound::LABEL_SE_JUMP);
		}
	}
	//攻撃の入力
	if (AttackInput())
	{
		//回転
		AttackTurning();
		SetAttack(true);
	}

	//カメラリセット
	if (CHossoLibrary::CheckCameraReset(CHossoLibrary::TRIGGER))
	{
		//カメラの回転量取得
		D3DXVECTOR3 &CameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot();

		//現在向いている方向設定
		CameraRot.y = GetRotDest().y + D3DX_PI;

		//3.14に収める
		CHossoLibrary::CalcRotation(CameraRot.y);

		//カメラ回転
		CManager::GetRenderer()->GetCamera()->SetCameraRot(CameraRot);

	}

	//移動に応じてモーション確認
	MoveMotionCheck();
}

//------------------------------------------------------------------------------
//連鎖のときのエフェクト
//------------------------------------------------------------------------------
void CPlayer::ChainThunder()
{
	//雷用のカウンタ++
	m_nCntChainThunder++;

	//カウンタの数値でアクション
	switch (m_nCntChainThunder)
	{

	case 10:
		//自分の方に寄ってくる感じの円
		CCircle_Effect::Create(GetPos(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 19, 400.0f, 600.0f, 8, -20.0f, -30.0f, -0.05f);
		CCircle_Effect::Create(GetPos(), D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f), 19, 800.0f, 1200.0f, 8, -40.0f, -60.0f, -0.05f);

		break;

	case 25:
		//落雷
		CEffectAnimation3D::Create(GetPos() + D3DXVECTOR3(0.0f, 300.0f, 0.0f), D3DXVECTOR3(1500.0f, 1500.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_CHAINTHUNDER, WhiteColor, 0.0f, 2);

		//音再生
		CManager::GetSound()->Play(CSound::LABEL_SE_START_CHAIN);

		break;

	case 30:
		//フラッシュ
		CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 0.0f, 0.0f), D3DXVECTOR3(2000.0f, 2000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_FLASH, 0.0f, 5, CScene::OBJTYPE_BACK);

		break;

	case 40:
		//雷バチンなやつ
		CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(250.0f, 250.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_SPARKEXPLOSION, WhiteColor, 0.0f, 2);

		//スフィアの爆発
		CSphere_Explosion::Create(GetCenterPos(), 50.0f, 100);

		//連鎖爆発開始
		CEnemy::ChainExplosion(GetPos());

		break;

	default:
		break;
	}
}


//------------------------------------------------------------------------------
//連続攻撃の次のモーションどれだ
//------------------------------------------------------------------------------
bool CPlayer::AttackInput()
{
	bool bAttack = false;
	CMotion::MOTION_TYPE NowMotion = GetNowMotion();

	//現在のモーションに応じて次の動きを決める
	switch (NowMotion)
	{
		//地面に足がついているとき
	case CMotion::PLAYER_NEUTRAL:
	case CMotion::PLAYER_WALK:
	case CMotion::PLAYER_DASH:

		//Xボタン
		if (CHossoLibrary::CheckAttack_X(CHossoLibrary::TRIGGER))
		{
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_X_01);
			return true;
		}

		//Yボタン
		if (CHossoLibrary::CheckAttack_Y(CHossoLibrary::TRIGGER))
		{
			ChangeMotion(CMotion::PLAYER_LAND_ATTACK_Y_01);
			return true;
		}

		//Bボタン
		if (CHossoLibrary::CheckAttack_B(CHossoLibrary::TRIGGER))
		{
			StartChainThunder();
			return true;
		}
		break;

		//空中にいる時
	case CMotion::PLAYER_AIR_NEUTRAL:
	case CMotion::PLAYER_JUMP:

		//Xボタン
		if (CHossoLibrary::CheckAttack_X(CHossoLibrary::TRIGGER))
		{
			if (!GetAirAttack())
			{
				ChangeMotion(CMotion::PLAYER_AIR_ATTACK_X_01);
				SetAirAttack(true);
				SetGravity(false, 17);

				return true;
			}
		}

		//Yボタン
		if (CHossoLibrary::CheckAttack_Y(CHossoLibrary::TRIGGER))
		{
			ChangeMotion(CMotion::PLAYER_ATTACK_SLAMS);
			GetMove().y = 0.0f;
			SetGravity(false, 5);
			return true;
		}

		//Bボタン
		if (CHossoLibrary::CheckAttack_B(CHossoLibrary::TRIGGER))
		{
			if (!GetAirAttack())
			{
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

	//Xボタン
	if (CHossoLibrary::CheckAttack_X(CHossoLibrary::TRIGGER))
	{
		switch (NowMotion)
		{
			//地上攻撃の時
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

			//空中攻撃の時
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

	//Yボタン
	if (CHossoLibrary::CheckAttack_Y(CHossoLibrary::TRIGGER))
	{
		//Xボタンの進行具合で切り替える
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

	//Yボタン
	if (CHossoLibrary::CheckAttack_Y(CHossoLibrary::TRIGGER))
	{
		//空中攻撃の間
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

	//Bボタン
	if (CHossoLibrary::CheckAttack_B(CHossoLibrary::TRIGGER))
	{
		switch (NowMotion)
		{
			//どの攻撃からもつながるように
		case CMotion::MOTION_NONE:
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
			StartChainThunder();
			SetAirAttack(true);
			bAttack = true;
			break;

		}
	}
	return bAttack;
}

//------------------------------------------------------------------------------
//移動速度を基にモーション切り替え
//------------------------------------------------------------------------------
void CPlayer::MoveMotionCheck()
{
	//移動情報取得
	D3DXVECTOR3 &rMove = GetMove();

	//移動速度の絶対値
	float fMoveSpeed = fabsf(D3DXVec2Length(&D3DXVECTOR2(rMove.x, rMove.z)));

	//まだ攻撃してなかった場合
	if (!GetAttack() && !GetJump())
	{
		//移動速度でモーション変更
		if (fMoveSpeed > 1.0f)
		{
			//移動速度が高い時
			if (fMoveSpeed > 6.0f)
			{
				//走るモーション
				ChangeMotion(CMotion::PLAYER_DASH);
			}
			//ある程度の速度の時
			else
			{
				//歩くモーション
				ChangeMotion(CMotion::PLAYER_WALK);
			}

			//足が地につくタイミング
			if (CCharacter::GetModelCharacterPtr()->GetKey() % 2 == 1 && CCharacter::GetModelCharacterPtr()->GetFrame() == 0)
			{
				//足音を鳴らす
				CManager::GetSound()->Play(CSound::LABEL_SE_WALK);

			}
		}
		else
		{
			//ニュートラル
			ChangeMotion(CMotion::PLAYER_NEUTRAL);
		}
	}
}


