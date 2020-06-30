//------------------------------------------------------------------------------
//
//キャラクター処理  [character.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "character.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "game.h"
#include "modelcharacter.h"
#include "effectanimation3D.h"
#include "collision.h"
#include "motion.h"
#include "camera.h"
#include "enemy.h"
#include "meshfield.h"
#include "model_object.h"
#include "Map.h"
#include "option.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CDefaultParam>> CCharacter::m_DefaultParam = {};
std::vector<std::string> CCharacter::m_aParamFileName =
{
	{ "data/SAVEDATA/Woman/Param.txt" },
	{ "data/SAVEDATA/Armor/Param_Normal.txt" },
	{ "data/SAVEDATA/Armor/Param_Green.txt" },
	{ "data/SAVEDATA/Armor/Param_Black.txt" },

};

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define INERTIA	(0.2f)			//摩擦
#define AIR_INERTIA (0.05f)		//空中時の摩擦
#define GRAVITY (0.7f)			//重力
//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CCharacter::CCharacter()
{
	m_pModelCharacter = nullptr;
	m_pos = ZeroVector3;
	m_posOld = ZeroVector3;
	m_move = ZeroVector3;
	m_rot = ZeroVector3;
	m_rotDest = ZeroVector3;
	m_rotDif = ZeroVector3;
	m_nLife = 1;
	m_bAttack = false;
	m_bAirAttack = false;
	m_bContinueAttack = false;
	m_bJump = false;
	m_bChangeMotion = false;
	m_bInvincible = false;
	m_bGravity = true;
	m_bAlive = true;
	m_nCntState = 0;
	m_State = STATE_NORMAL;
	m_fCenterPosOffset = 0.0f;
	D3DXMatrixIdentity(&m_mtxWorld);

}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CCharacter::~CCharacter()
{
	if (m_pModelCharacter)
	{
		m_pModelCharacter.reset();
	}
	if (m_pCollision)
	{
		m_pCollision.reset();
	}
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CCharacter::Init()
{
	//コリジョン生成
	m_pCollision = CCollision::Create(GetMtx(), CCollision::COLLISION_CHARACTER);

	//判定の情報設定
	m_pCollision->SetCollisionInfo(30.0f, 100.0f);

	//成功
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CCharacter::Uninit()
{

}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CCharacter::Update()
{
	//前回の座標保存
	m_posOld = m_pos;

	//モーション変更したかどうか　リセット
	m_bChangeMotion = false;

	//移動処理
	Move();

	//回転処理
	Rot();

	//ワールドマトリックスの計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);

	//当たり判定
	Collision();

	//ステートに応じた処理
	State();

	//攻撃状態の時
	if (m_bAttack)
	{
		//移動するキーかチェック
		if (m_pModelCharacter->CheckMoveKey())
		{
			//プレイヤーのMoveに加算
			//向いてる方に移動
			m_move.x = -sinf(m_rotDest.y) * CMotion::GetAttackInfo(GetNowMotion())->fMoveFront;
			m_move.z = -cosf(m_rotDest.y) * CMotion::GetAttackInfo(GetNowMotion())->fMoveFront;

			//上下の移動
			m_move.y = CMotion::GetAttackInfo(GetNowMotion())->fMoveUp;

			//音再生
			CManager::GetSound()->Play(CSound::LABEL_SE_SWING);

			if (COption::GetAutoRotation())
			{
				switch (GetNowMotion())
				{
				case CMotion::PLAYER_LAND_ATTACK_Y_SPEAR:
				case CMotion::PLAYER_LAND_ATTACK_Y_05:
				case CMotion::PLAYER_AIR_ATTACK_X_04:
				case CMotion::PLAYER_LAND_ATTACK_X_05:
					//カメラの回転量取得
					D3DXVECTOR3 &CameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot();

					//現在向いている方向設定
					CameraRot.y = GetRotDest().y + D3DX_PI;

					//3.14に収める
					CHossoLibrary::CalcRotation(CameraRot.y);

					//カメラ回転
					CManager::GetRenderer()->GetCamera()->SetCameraRot(CameraRot);
				}
			}
		}
	}


	//モデルの動きの更新
	m_pModelCharacter->Update();

	//ワールドマトリックスの計算
	CHossoLibrary::CalcMatrix(&m_mtxWorld, m_pos, m_rot);
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CCharacter::Draw()
{
	//モデルの描画
	m_pModelCharacter->Draw();
}
//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CCharacter::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//ダメージ処理
//------------------------------------------------------------------------------
bool CCharacter::ApplyDamage(int nDamage, int nBlueDamage)
{
	//ダメージがある場合はダメージ加算
	if (nDamage > 0)
	{
		//青ダメージと加算
		m_nLife = m_nBlueLife - nDamage;
	}
	else
	{
		//青ダメージ
		m_nBlueLife -= nBlueDamage;
	}

	//青HPがHPより多い時
	if (m_nBlueLife > m_nLife)
	{
		m_nBlueLife = m_nLife;

	}

	//ステート変更
	SetState(CCharacter::STATE_DAMAGE);

	//ダメージを受けた時のリアクション
	//派生クラスがオーバーライドして使用
	DamageAction();

	//ライフが0以下の場合
	if (m_nLife <= 0)
	{
		//死亡状態
		SetState(CCharacter::STATE_DEATH);
		return true;
	}

	return false;
}
//------------------------------------------------------------------------------
//ノックバック
//------------------------------------------------------------------------------
void CCharacter::KnockBack(float fKnockBack_Front, float fKockBack_Up, float fAngle)
{
	//プレイヤーのMoveに加算
	//向いてる方に移動
	m_move.x = sinf(fAngle) * -fKnockBack_Front;
	m_move.z = cosf(fAngle) * -fKnockBack_Front;

	//上下の移動
	m_move.y = fKockBack_Up;
}

//------------------------------------------------------------------------------
//モデル設定
//------------------------------------------------------------------------------
void CCharacter::SetParameter(MODEL_TYPE modeltype, PARAM_TYPE Paramtype, std::shared_ptr<CCharacter> MyPtr)
{
	//モデルキャラクター生成
	m_pModelCharacter = CModelCharacter::Create(modeltype);

	//マトリックス設定
	m_pModelCharacter->SetCharacterMtx(&m_mtxWorld);

	//自分のポインタ設定
	m_pModelCharacter->SetCharacterPtr(MyPtr);

	//パラメータタイプ設定
	m_Paramtype = Paramtype;
	m_modeltype = modeltype;

	//敵の種類で敵のパラメータ設定
	switch (m_Paramtype)
	{
	case CCharacter::PARAM_ENEMY:
		break;
	case CCharacter::PARAM_ENEMY_GREEN:
		m_pModelCharacter->SetPartsMaterialCol(CSceneX::MAT_ENEMY_GREEN);
		break;
	case CCharacter::PARAM_ENEMY_BLACK:
		m_pModelCharacter->SetPartsMaterialCol(CSceneX::MAT_ENEMY_BLACK);
		break;
	}

	//パラメータ設定
	m_nBlueLife = m_nLife = m_DefaultParam[m_Paramtype]->GetMaxLife();

	//腰の高さ取得　エフェクトとかの発生源
	m_fCenterPosOffset = m_pModelCharacter->GetWaistHeight();
}

//------------------------------------------------------------------------------
//ステート設定
//------------------------------------------------------------------------------
void CCharacter::SetState(STATE nextstate)
{
	m_State = nextstate;
	switch (nextstate)
	{
	case CCharacter::STATE_NORMAL:
		//無敵状態
		m_bInvincible = false;
		break;
	case CCharacter::STATE_DAMAGE:
		//無敵時間設定
		m_nCntState = m_DefaultParam[m_Paramtype]->GetInvincibleTime();

		//無敵状態
		m_bInvincible = true;
		break;
	case CCharacter::STATE_STAN:
		break;
	case CCharacter::STATE_DEATH:
		//死亡状態
		SetAlive(false);
		break;
	}
}
//------------------------------------------------------------------------------
//現在のモーション取得
//------------------------------------------------------------------------------
CMotion::MOTION_TYPE CCharacter::GetNowMotion()
{
	return m_pModelCharacter->GetMotion();
}

//------------------------------------------------------------------------------
//キャラクター情報表示
//------------------------------------------------------------------------------
void CCharacter::ShowCharacterInfo()
{
#ifdef _DEBUG
	//キャラクター情報情報
	if (ImGui::TreeNode("CharacterInfo"))
	{
		ImGui::Text("pos %.2f,%.2f,,%.2f", m_pos.x, m_pos.y, m_pos.z);
		ImGui::Text("move %.2f,%.2f,,%.2f", m_move.x, m_move.y, m_move.z);
		ImGui::Text("rot %.2f,%.2f,,%.2f", m_rot.x, m_rot.y, m_rot.z);

		ImGui::Text("dest %.2f,%.2f,,%.2f", m_rotDest.x, m_rotDest.y, m_rotDest.z);
		ImGui::Text("dif %.2f,%.2f,,%.2f", m_rotDif.x, m_rotDif.y, m_rotDif.z);

		ImGui::Text("MaxLife %d : Life %d", m_DefaultParam[m_Paramtype]->GetMaxLife(),m_nLife);
		ImGui::Text("BlueLife %d", m_nBlueLife);

		ImGui::Text("bAttack [%d] bAirAttack [%d] bContinueAttack [%d]", m_bAttack, m_bAirAttack,m_bContinueAttack);
		ImGui::Text("bJump [%d] bInvincible [%d]", m_bJump, m_bInvincible);
		ImGui::Text("State [%d] nCntState [%d]", m_State, m_nCntState);

		m_pModelCharacter->ShowModelCharacterInfo();

		ImGui::TreePop();
	}
#endif //DEBUG
}
//------------------------------------------------------------------------------
//モーション切り替え
//------------------------------------------------------------------------------
void CCharacter::ChangeMotion(CMotion::MOTION_TYPE nextmotion)
{
	//モーションが切り替わった時
	if (GetNowMotion() != nextmotion)
	{
		//モーション変更した
		m_bChangeMotion = true;

		//モーション切り替え
		m_pModelCharacter->SetMotion(nextmotion);
	}
}

//------------------------------------------------------------------------------
//モーション切り替え
//------------------------------------------------------------------------------
bool CCharacter::ContinueAttack()
{
	//最終キーだった場合
	if (m_pModelCharacter->GetKey() + 1 == CMotion::GetNumKey(m_pModelCharacter->GetMotion()))
	{
		return true;
	}
	return false;
}
//------------------------------------------------------------------------------
//移動処理
//------------------------------------------------------------------------------
void CCharacter::Move()
{
	if(m_bGravity)
	{
		//重力加算
		m_move.y -= GRAVITY;
	}
	else
	{
		//無重力カウンタが０以下になった時
		if (m_nCntGravity-- <= 0)
		{
			m_bGravity = true;
		}
	}

	//移動量加算
	m_pos += m_move;

	//空中時
	if (m_bJump)
	{
		//慣性
		m_move.x += (0 - m_move.x) * AIR_INERTIA;
		m_move.z += (0 - m_move.z) * AIR_INERTIA;
	}
	//それ以外
	else
	{
		//慣性
		m_move.x += (0 - m_move.x) * INERTIA;
		m_move.z += (0 - m_move.z) * INERTIA;
	}
}
//------------------------------------------------------------------------------
//回転処理
//------------------------------------------------------------------------------
void CCharacter::Rot()
{
	//回転の差分を求める
	m_rotDif.y = m_rotDest.y - m_rot.y;

	//3.14以内にする
	CHossoLibrary::CalcRotation(m_rotDif.y);

	//モデルの回転させる
	m_rot.y += m_rotDif.y * 0.3f;

	//3.14以内にする
	CHossoLibrary::CalcRotation(m_rot.y);
}

//------------------------------------------------------------------------------
//当たり判定
//------------------------------------------------------------------------------
void CCharacter::Collision()
{
	bool bJump = true;

	//フィールドのサイズ取得
	D3DXVECTOR3 FieldSize = CMap::GetFieldSize() * 0.5f;

	//フィールド外に出れないようにする
	CHossoLibrary::RangeLimit_Equal_Float(m_pos.x, -FieldSize.x, FieldSize.x);
	CHossoLibrary::RangeLimit_Equal_Float(m_pos.z, -FieldSize.z, FieldSize.z);

	//範囲から出ないようにする
	if (m_pos.y < 0)
	{
		//↓方向の力を消す
		m_move.y = 0;

		//0の位置に合わす
		m_pos.y = 0;

		//ジャンプ状態解除
		bJump = false;
		m_bAirAttack = false;
		m_bContinueAttack = false;

	}

	//Sceneのリスト
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//シーン情報取得
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);
	//配列に入ってるか
	if (!pSceneList.empty())
	{
		//要素分
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//ポインタ取得 CMeshField型にキャスト
			CEnemy *pEnemy = ((CEnemy*)pSceneList[nCnt].get());

			//nullcheck
			if (pEnemy && pEnemy != this)
			{
				//判定後の座標
				D3DXVECTOR3 CollisionAfterPos = pEnemy->GetPos();

				//キャラクターの判定　敵
				if (m_pCollision->CollisionCharacter(pEnemy->GetCollision(), &CollisionAfterPos))
				{
					//座標移動
					pEnemy->SetPos(CollisionAfterPos);
				}
			}
		}
	}

	//ジャンプ状態がtrueからfalseになった時
	if (m_bJump == true && bJump == false && m_modeltype == MODEL_PLAYER)
	{
		//音再生
		CManager::GetSound()->Play(CSound::LABEL_SE_LANDING);
	}

	//ジャンプ状態設定
	m_bJump = bJump;
}
//------------------------------------------------------------------------------
//状態に応じた処理
//------------------------------------------------------------------------------
void CCharacter::State()
{
	switch (m_State)
	{
	case CCharacter::STATE_NONE:
		break;
	case CCharacter::STATE_NORMAL:
		break;
	case CCharacter::STATE_DAMAGE:
		m_nCntState--;
		if (m_nCntState < 0)
		{
			//通常状態に戻す
			SetState(CCharacter::STATE_NORMAL);
			m_bInvincible = false;

			//ニュートラルに戻す
			m_pModelCharacter->ResetMotion();
			m_pModelCharacter->SetDefaultMotion();
		}
		break;
		//スタン中
	case CCharacter::STATE_STAN:

		//カウントダウン
		m_nCntState--;

		//15Fに一回
		if (m_nCntState % 15 == 0)
		{
			//
			CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(80.0f, 120.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_STANING,D3DXCOLOR(0.4f,0.4f,1.0f,1.0f), CHossoLibrary::Random_PI(), 2);
		}

		break;

		//死亡
	case CCharacter::STATE_DEATH:

		//カウントダウン
		m_nCntState--;

		//カウンタが0になったら
		if (m_nCntState < 0)
		{
			//死亡時のリアクション
			//派生クラスがオーバーライドして使用
			DeathAction();
			SetState(STATE_NONE);
		}
		break;
	default:
		break;
	}
}

//------------------------------------------------------------------------------
//パラメータ取得
//------------------------------------------------------------------------------
HRESULT CCharacter::LoadDefaultParam()
{
	//変数宣言
	FILE *pFile;			//ファイルのポインタ
	char cReadText[MAX_TEXT];
	char cHeadText[MAX_TEXT];
	char cDieText[MAX_TEXT];
	int nLife = 0;
	float fMoveSpeed = 0.0f;
	float fJumpSpeed = 0.0f;
	float fDashSpeed = 0.0f;
	float fAirSpeed = 0.0f;
	int nInvincinbleTime = 0;

	for (size_t nCnt = 0; nCnt < m_aParamFileName.size(); nCnt++)
	{
		//ファイルを開く
		pFile = fopen(m_aParamFileName[nCnt].data(), "r");

		//ファイルがあった場合
		if (pFile)
		{

			std::unique_ptr<CDefaultParam> pParam(new CDefaultParam);

			//パラメータの配列追加
			m_DefaultParam.emplace_back(std::move(pParam));

			std::cout << "new DefaultParam - " << nCnt << NEWLINE;

			//スクリプトがくるまで
			while (strcmp(cHeadText, "SCRIPT") != 0)
			{
				fgets(cReadText, sizeof(cReadText), pFile);
				sscanf(cReadText, "%s", &cHeadText);
			}
			//スクリプトだったら
			if (strcmp(cHeadText, "SCRIPT") == 0)
			{
				//エンドスクリプトが来る前ループ
				while (strcmp(cHeadText, "END_SCRIPT") != 0)
				{
					fgets(cReadText, sizeof(cReadText), pFile);
					sscanf(cReadText, "%s", &cHeadText);
					//改行
					if (strcmp(cHeadText, "\n") == 0)
					{
					}
					//キャラクターセットだったら
					else if (strcmp(cHeadText, "PARAMSET") == 0)
					{
						//エンドキャラクターセットがくるまでループ
						while (strcmp(cHeadText, "END_PARAMSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile);
							sscanf(cReadText, "%s", &cHeadText);
							//最大HP
							if (strcmp(cHeadText, "MAX_LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nLife);
								std::cout << "m_DefaultParam - " << nCnt  << " MAX_LIFE >> " << nLife << NEWLINE;
								m_DefaultParam[nCnt]->SetMaxLife(nLife);
							}
							//移動速度
							if (strcmp(cHeadText, "MOVE_SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &fMoveSpeed);
								std::cout << "m_DefaultParam - " << nCnt << " MOVE_SPEED >> " << fMoveSpeed << NEWLINE;
								m_DefaultParam[nCnt]->SetMoveSpeed(fMoveSpeed);
							}
							//ダッシュ速度
							if (strcmp(cHeadText, "DASH_SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &fDashSpeed);
								std::cout << "m_DefaultParam - " << nCnt << " DASH_SPEED >> " << fDashSpeed << NEWLINE;
								m_DefaultParam[nCnt]->SetDashSpeed(fDashSpeed);
							}
							//ジャンプ力
							if (strcmp(cHeadText, "JUMP_SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &fJumpSpeed);
								std::cout << "m_DefaultParam - " << nCnt << " JUMP_SPEED >> " << fJumpSpeed << NEWLINE;
								m_DefaultParam[nCnt]->SetJumpSpeed(fJumpSpeed);
							}
							//空中の移動速度
							if (strcmp(cHeadText, "AIR_SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDieText, &cDieText, &fAirSpeed);
								std::cout << "m_DefaultParam - " << nCnt << " AIR_SPEED >> " << fAirSpeed << NEWLINE;
								m_DefaultParam[nCnt]->SetAirSpeed(fAirSpeed);
							}
							//無敵時間
							if (strcmp(cHeadText, "INVINCIBLE_TIME") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDieText, &cDieText, &nInvincinbleTime);
								std::cout << "m_DefaultParam - " << nCnt << " INVINCIBLE_TIME >> " << nInvincinbleTime << NEWLINE;
								m_DefaultParam[nCnt]->SetInvincinbleTime(nInvincinbleTime);
							}
							//終了
							if (strcmp(cHeadText, "END_PARAMSET") == 0)
							{
								std::cout << "LoadSuccess!" << "LoadDefaultParam() - " << nCnt << NEWLINE;
								std::cout << NEWLINE;
								break;
							}
						}
					}
				}
			}
			fclose(pFile);
		}

		//開けなかった時
		else
		{
			std::cout << "LoadFailed!!  Can't Open File." << "LoadDefaultParam() - " << nCnt << NEWLINE;

		}
	}
	return S_OK;
}