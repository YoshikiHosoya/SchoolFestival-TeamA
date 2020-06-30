//------------------------------------------------------------------------------
//
//エネミー処理  [enemy.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
#include "gauge_3D.h"
#include "sphere_explosion.h"
#include "game.h"
#include "particle.h"
#include "player.h"
#include "sound.h"
#include "score.h"
#include "effectanimation3D.h"
#include "frontUI.h"
#include "chainelectric.h"
//------------------------------------------------------------------------------
//静的メンバ変数の初期化
//------------------------------------------------------------------------------
int CEnemy::m_nNumEnemy = 0;
int CEnemy::m_nNumStanEnemy = 0;
bool CEnemy::m_bChain = false;

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------
#define KNOCK_BACK_SPEED (25.0f)			//ノックバックの量
#define MAX_ONE_CHAIN (3)					//１Fあたりの連鎖でつながる最大数
#define ENEMY_PLAYER_FOUND_RANGE (800.0f)	//プレイヤーを見つける距離
#define ENEMY_ATTACK_RANGE (250.0f)			//プレイヤーに攻撃する距離

//------------------------------------------------------------------------------
//コンストラクタ
//------------------------------------------------------------------------------
CEnemy::CEnemy()
{
	m_bStan = false;
	m_bContact = false;
	m_bChain = false;
	m_AIMove = AI_NEUTRAL;
	m_enemytype = CEnemy::TYPE_NORMAL;
	m_nNumEnemy++;
	m_fMoveAngle = 0.0f;
	m_nCntAIMove = rand() % 1000;
}

//------------------------------------------------------------------------------
//デストラクタ
//------------------------------------------------------------------------------
CEnemy::~CEnemy()
{
	m_pGauge = nullptr;
	m_nNumEnemy--;
	m_nNumStanEnemy--;
}
//------------------------------------------------------------------------------
//初期化処理
//------------------------------------------------------------------------------
HRESULT CEnemy::Init()
{
	CCharacter::Init();

	//成功
	return S_OK;
}
//------------------------------------------------------------------------------
//終了処理
//------------------------------------------------------------------------------
void CEnemy::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//更新処理
//------------------------------------------------------------------------------
void CEnemy::Update()
{
	//連鎖状態false
	m_bChain = false;

	//生きているとき
	if (GetAlive())
	{
		//現在のモーション
		switch (GetNowMotion())
		{
			//ニュートラルか歩いているとき
		case CMotion::ENEMY_ARMOR_NEUTRAL:
		case CMotion::ENEMY_ARMOR_WALK:

			//攻撃状態解除
			SetAttack(false);
			break;
		}

		//被弾時
		if (GetState() == CCharacter::STATE_DAMAGE)
		{

		}
		//スタン状態であるなら
		else if (m_bStan)
		{
			//スタンモーション
			ChangeMotion(CMotion::ENEMY_ARMOR_STAN);
			SetState(CCharacter::STATE_STAN);
		}
		else
		{
			//ゲーム時
			if (CManager::GetMode() == CManager::MODE_GAME)
			{
				//ゲームクリア時
				if (CManager::GetGame()->GetGamestate() == CGame::STATE_GAMECLEAR)
				{
					//ニュートラルにしとく
					ChangeMotion(CMotion::ENEMY_ARMOR_NEUTRAL);
				}
				else
				{
					//AIで移動
					AIMove();
				}
			}
			//デモプレイ時
			if (CManager::GetMode() == CManager::MODE_DEMOPLAY)
			{
				//AIで移動
				AIMove();
			}
		}
	}
	//更新
	CCharacter::Update();

	//ゲージ用のマトリックス設定
	m_pGauge->SetMtx(*GetMtx());
}
//------------------------------------------------------------------------------
//描画処理
//------------------------------------------------------------------------------
void CEnemy::Draw()
{
	CCharacter::Draw();
}

//------------------------------------------------------------------------------
//デバッグ情報表記
//------------------------------------------------------------------------------
void CEnemy::ShowDebugInfo()
{
#ifdef _DEBUG
	//プレイヤー情報情報
	if (ImGui::TreeNode("EnemyInfo"))
	{
		//キャラクター情報表示
		ShowCharacterInfo();

		ImGui::TreePop();
	}
#endif //DEBUG
}
//------------------------------------------------------------------------------
//ダメージ受けた時の処理
//------------------------------------------------------------------------------
void CEnemy::DamageAction()
{
	//ゲージ更新
	m_pGauge->SetLife(GetLife(), GetBlueLife());

	//音再生
	CManager::GetSound()->Play(CSound::LABEL_SE_SLASH);

	//青HPが0以下になった時
	if (GetBlueLife() <= 0)
	{
		//まだスタンしてなかった時
		if (!m_bStan)
		{
			//スタン開始
			StartStan();

			//ヒットエフェクト　スタンがわかりやすいように
			CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(350.0f, 350.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_STAN, D3DXCOLOR(0.2f, 0.4f, 1.0f, 0.8f), 0.0f, 2);
			CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(350.0f, 350.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_STANING, D3DXCOLOR(0.1f, 0.3f, 1.0f, 1.0f), 0.0f, 3);

			//超吹っ飛ぶ
			HyperKnockBack();

			//スタン状態
			SetState(CCharacter::STATE_STAN);

			//音再生
			CManager::GetSound()->Play(CSound::LABEL_SE_SLASH_STAN);
		}
	}

	//テクスチャアニメーションの生成
	CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(300.0f, 300.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_SLASH, WhiteColor, CHossoLibrary::Random_PI(), 5);
	CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(150.0f, 150.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_SPARK, WhiteColor, CHossoLibrary::Random_PI(), 1);

	//被弾モーション
	ChangeMotion(CMotion::ENEMY_ARMOR_HIT);

	//ゲーム時
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		//コンボ加算
		CManager::GetGame()->GetScore()->AddCombo(1);
	}
}
//------------------------------------------------------------------------------
//死亡時のリアクション
//------------------------------------------------------------------------------
void CEnemy::DeathAction()
{
	//爆発エフェクト
	CSphere_Explosion::Create(GetCenterPos(), 120.0f, 150);
	CParticle::Create(GetCenterPos(), 60, 450.0f, OrangeColor, 2,1.0f);

	//キル数加算
	if (CManager::GetMode() == CManager::MODE_GAME)
	{
		CManager::GetGame()->GetScore()->AddKill(1);
	}

	//連鎖爆発処理
	ChainExplosion(GetPos());

	//開放
	Release();
}
//------------------------------------------------------------------------------
//攻撃時に旋回
//------------------------------------------------------------------------------
void CEnemy::AttackTurning()
{
}
//------------------------------------------------------------------------------
//当たり判定系
//------------------------------------------------------------------------------
void CEnemy::Collision()
{
	CCharacter::Collision();
}

//------------------------------------------------------------------------------
//生成処理
//------------------------------------------------------------------------------
std::shared_ptr<CEnemy> CEnemy::Create(D3DXVECTOR3 pos, ENEMY_TYPE enemytype)
{
	//変数宣言
	std::shared_ptr<CEnemy> pEnemy = std::make_shared<CEnemy>();

	//nullcheck
	if (pEnemy)
	{
		//初期化7
		pEnemy->Init();

		//座標設定
		pEnemy->SetPos(pos);

		//敵の種類設定
		pEnemy->m_enemytype = enemytype;

		switch (enemytype)
		{
		case CEnemy::TYPE_NORMAL:
			//パラメータ設定
			pEnemy->SetParameter(MODEL_TYPE::MODEL_ENEMY, CCharacter::PARAM_ENEMY, pEnemy);
			break;

		case CEnemy::TYPE_TUTORIAL_STANING:
			//パラメータ設定
			pEnemy->SetParameter(MODEL_TYPE::MODEL_ENEMY, CCharacter::PARAM_ENEMY, pEnemy);
			break;

		case CEnemy::TYPE_SPEEDY:
			//パラメータ設定
			pEnemy->SetParameter(MODEL_TYPE::MODEL_ENEMY, CCharacter::PARAM_ENEMY, pEnemy);

			break;
		case CEnemy::TYPE_STRONG:
			//パラメータ設定
			pEnemy->SetParameter(MODEL_TYPE::MODEL_ENEMY, CCharacter::PARAM_ENEMY, pEnemy);

			break;
		}

		//ワールドマトリックスの計算
		CHossoLibrary::CalcMatrix(pEnemy->GetMtx(), pEnemy->GetPos(), pEnemy->GetRot());

		//ゲージ生成
		pEnemy->m_pGauge = CGauge_3D::Create(pEnemy->GetPos(), D3DXVECTOR3(50.0f, 4.0f, 0.0f), D3DXVECTOR3(0.0f, 110.0f, 0.0f), pEnemy->GetDefaultParam(PARAM_ENEMY)->GetMaxLife(), *pEnemy->GetMtx());

		if (enemytype == CEnemy::TYPE_TUTORIAL_STANING)
		{
			//青のライフを0にしてスタン状態にしておく
			pEnemy->SetBlueLife(0);
			pEnemy->m_pGauge->SetLife(pEnemy->GetLife(), pEnemy->GetBlueLife());
			pEnemy->StartStan();
		}

		//エフェクト生成
		CEffectAnimation3D::Create(pEnemy->GetCenterPos(), D3DXVECTOR3(350.0f, 350.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_ENEMY_RESPAWN, WhiteColor, 0.0f, 2);

		//オブジェクトタイプ設定
		pEnemy->SetObjType(OBJTYPE_ENEMY);

		//リストに追加
		pEnemy->AddSharedList(pEnemy);

		//生成した情報
		return pEnemy;
	}

	//失敗
	return nullptr;
}
//------------------------------------------------------------------------------
//連鎖爆発
//------------------------------------------------------------------------------
void CEnemy::ChainExplosion(D3DXVECTOR3 pos)
{
	//まだチェインしてない時
	if (!m_bChain)
	{
		//カウント
		int nCnt = 0;

		//Sceneのリスト
		std::vector<std::shared_ptr<CScene>> pSceneList;

		//敵のリスト取得
		CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

		//nullcheck
		if (!pSceneList.empty())
		{
			//要素分
			for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
			{
				//ポインタ取得 CEnemy型にキャスト
				CEnemy *pEnemy = ((CEnemy*)pSceneList[nCnt].get());

				//nullcheck
				if (pEnemy)
				{
					//スタン状態で生きている時
					if (pEnemy->GetStan() && pEnemy->GetAlive())
					{
						//連鎖した
						m_bChain = true;

						//ダメージ処理 スタン状態だからこれだけで爆発する
						pEnemy->ApplyDamage(1, 0);

						////電撃生成
						CChainElectric::Create(pos, pEnemy->GetPos(), D3DXVECTOR3(200.0f, 50.0f, 0.0f), WhiteColor, pEnemy->GetCntState());

						//カウンタ++
						nCnt++;

						//1Fに爆発できる量超えたらreturn
						if (nCnt > MAX_ONE_CHAIN)
						{
							return;
						}
					}
				}
			}
		}
	}
}
//------------------------------------------------------------------------------
//ステート変更処理
//------------------------------------------------------------------------------
void CEnemy::SetState(STATE nextstate)
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
	case CCharacter::STATE_DEATH:

		//ヒットエフェクト
		CEffectAnimation3D::Create(GetCenterPos(), D3DXVECTOR3(400.0f, 400.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_HIT_STAN, D3DXCOLOR(0.8f,0.8f,0.3f,0.8f), 0.0f,3);

		//爆発までのカウント
		SetCntState(rand() % 15 + 7);
		break;
	}
}
//------------------------------------------------------------------------------
//static系の情報初期化
//------------------------------------------------------------------------------
void CEnemy::ResetEnemyStaticInfo()
{
	m_nNumEnemy = 0;
	m_nNumStanEnemy = 0;
	m_bChain = false;
}

//------------------------------------------------------------------------------
//超吹っ飛ぶ
//------------------------------------------------------------------------------
void CEnemy::HyperKnockBack()
{
	//プレイヤーのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	//移動量
	D3DXVECTOR3 &rMove = GetMove();

	//nullcheck
	if (!pPlayer)
	{
		//nullだったら処理しない
		return;
	}

	//たまに吹っ飛ばないやつ生成
	if (rand() % 15 == 0)
	{
		return;
	}

	//変数宣言
	D3DXVECTOR3 Distance = GetPos() - pPlayer->GetPos();				//プレイヤーと自分の差分
	float fLength = fabsf(D3DXVec3Length(&Distance));					//プレイヤーとの距離
	float fAngle = atan2f(Distance.x, Distance.z);

	float fKnockBackSpeed = KNOCK_BACK_SPEED + rand() % 80;

	//移動処理
	rMove.x = sinf(fAngle) * fKnockBackSpeed;
	rMove.y = float(rand() % 15 + 2.0f);
	rMove.z = cosf(fAngle) * fKnockBackSpeed;
}
//------------------------------------------------------------------------------
//AIで移動
//------------------------------------------------------------------------------
void CEnemy::AIMove()
{
	//プレイヤーのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();

	//nullcheck
	if (!pPlayer)
	{
		//nullだったら処理しない
		m_AIMove = CEnemy::AI_NEUTRAL;
		return;
	}

	//プレイヤーが死亡していた時
	if (!pPlayer->GetAlive())
	{
		//その場にニュートラル
		m_AIMove = CEnemy::AI_NEUTRAL;
		return;
	}

	//変数宣言
	D3DXVECTOR3 Distance = GetPos() - pPlayer->GetPos();				//プレイヤーと自分の差分
	float fLength = fabsf(D3DXVec3Length(&Distance));					//プレイヤーとの距離
	float fAngle = atan2f(Distance.x, Distance.z);

	//AIのカウント
	m_nCntAIMove++;

	//一定内の時
	if (fLength <= ENEMY_PLAYER_FOUND_RANGE)
	{
		//ニュートラルか移動してる時
		if (m_AIMove == AI_NEUTRAL || m_AIMove == AI_PLAYER_FOLLOWING)
		{
			//プレイヤーの方を向く
			SetRotDest(D3DXVECTOR3(0.0f, fAngle, 0.0f));
		}

		//ある程度距離あって攻撃していない時
		if (fLength <= ENEMY_PLAYER_FOUND_RANGE && fLength > ENEMY_ATTACK_RANGE && !GetAttack())
		{
			//プレイヤーの方に来る
			m_AIMove = CEnemy::AI_PLAYER_FOLLOWING;
		}
		//攻撃可能距離
		else if (fLength <= ENEMY_ATTACK_RANGE)
		{
			//攻撃してない時
			if (!GetAttack())
			{
				//ニュートラル
				m_AIMove = CEnemy::AI_NEUTRAL;
				ChangeMotion(CMotion::ENEMY_ARMOR_NEUTRAL);
			}

			//50Fに一回
			if (m_nCntAIMove % 50 == 0)
			{
				//確立で
				if (rand() % 5 == 0)
				{
					//攻撃
					m_AIMove = CEnemy::AI_ATTACK;
					ChangeMotion(CMotion::ENEMY_ARMOR_ATTACK01);
					SetAttack(true);
				}
			}
		}
	}
	//遠い時
	else
	{
		//移動してない時
		if (m_AIMove != CEnemy::AI_RANDOM_MOVE)
		{
			//ニュートラル
			m_AIMove = CEnemy::AI_NEUTRAL;
		}
	}

	//移動量
	D3DXVECTOR3 &rMove = GetMove();

	//移動速度
	float fMoveSpeed = 0.0f;

	//AIの移動状態で処理を変える
	switch (m_AIMove)
	{
	case CEnemy::AI_NEUTRAL:
		ChangeMotion(CMotion::ENEMY_ARMOR_NEUTRAL);

		//一定周期
		if (m_nCntAIMove % 150 == 0)
		{
			//確立で歩き出す
			if (rand() % 2 == 0)
			{
				//ニュートラル
				m_AIMove = CEnemy::AI_RANDOM_MOVE;
				break;
			}
		}
		break;

	case CEnemy::AI_RANDOM_MOVE:
		//歩くモーション
		ChangeMotion(CMotion::ENEMY_ARMOR_WALK);

		//移動速度設定
		fMoveSpeed = CCharacter::GetDefaultParam(CCharacter::GetParamType())->GetMoveSpeed();

		//ある程度時間たった時に方向転換
		if (m_nCntAIMove % 120 == 0)
		{
			//たまにニュートラルになる
			if (rand() % 3 == 0)
			{
				//ニュートラル
				m_AIMove = CEnemy::AI_NEUTRAL;
				break;
			}
			//移動先の角度設定
			m_fMoveAngle = CHossoLibrary::Random_PI();
		}
		//移動方向を向く
		SetRotDest(D3DXVECTOR3(0.0f, m_fMoveAngle, 0.0f));
		break;

		//移動
	case CEnemy::AI_PLAYER_FOLLOWING:

		//スピードはパラメータから引っ張ってくる
		fMoveSpeed = CCharacter::GetDefaultParam(CCharacter::GetParamType())->GetDashSpeed();

		//歩くモーション
		ChangeMotion(CMotion::ENEMY_ARMOR_WALK);

		//方向設定
		m_fMoveAngle = fAngle;

		break;
	case CEnemy::AI_ATTACK:
		break;
	}

	//移動処理
	rMove.x -= sinf(m_fMoveAngle) * fMoveSpeed;
	rMove.z -= cosf(m_fMoveAngle) * fMoveSpeed;
}

//------------------------------------------------------------------------------
//スタン開始
//------------------------------------------------------------------------------
void CEnemy::StartStan()
{
	//スタン敵総数加算
	m_nNumStanEnemy++;

	//スタン状態true
	m_bStan = true;

	//HPゲージ点滅
	m_pGauge->SetFlash(true);

	//スタンモーション
	ChangeMotion(CMotion::ENEMY_ARMOR_STAN);

	//全員スタンしたとき
	if (GetEnemyNum() == GetStanEnemyNum())
	{
		CFrontUI::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 550.0f, 0.0f), D3DXVECTOR3(550.0f, 150.0f, 0.0f), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), CFrontUI::PUSH_B);
	}
}
