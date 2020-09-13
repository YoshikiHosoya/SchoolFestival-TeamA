// =====================================================================================================================================================================
//
// ボス1の処理 [boss_one.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "Boss_One.h"
#include "manager.h"
#include "basemode.h"
#include "gamemanager.h"
#include "game.h"
#include "model.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "map.h"
#include "gun.h"
#include "collision.h"
#include <random>
#include <iostream>
#include <algorithm>
#include "ModelSet.h"
#include "particle.h"

// =====================================================================================================================================================================
//マクロ定義
// =====================================================================================================================================================================
#define DIFFERENCE_POSTURE	 (POSTURE_HEIGHT_STAND - POSTURE_HEIGHT_SQUAT)	// 姿勢の座標の差分の距離
#define POSTURE_HEIGHT_STAND (150.0f)										// 通常状態の座標の高さ
#define POSTURE_HEIGHT_SQUAT (50.0f)										// しゃがみ状態の座標の高さ
#define BALKAN_LENGTH		 (50.0f)										// バルカンの横の長さ
#define PLAYER_HEADLINE		 (60.0f)										// プレイヤーのヘッドラインの高さ
#define RUNAWAY_BOSSLIFE	 (250)											// 暴走状態になる体力のライン
#define COOLTIME_BASE		 (120)											// クールタイムの基準
#define ATTACK_PRIORITY		 (2)											// 攻撃の優先度を保存しておく総数

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
BOSS_ONE_DATABASE	CBoss_One::m_BossOneData						 = {};			// データ

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CBoss_One::m_BossOneFileName =
{
	"data/Load/DragonNosuke/Boss_OneData.txt" 			// ボスの情報
};

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CBoss_One::CBoss_One(OBJ_TYPE type) :CEnemy(type)
{
	// 使用するガンの初期化
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_pGun[nCnt]			 = nullptr;
		m_Gun_OffsetPos[nCnt]	 = ZeroVector3;
		m_Gun_Pos[nCnt]			 = ZeroVector3;
	}

	// 配列の初期化
	m_AIPriorityData.nPriorityData.clear();

	for (int nCnt = 0; nCnt < ATTACKTYPE_MAX; nCnt++)
	{
		m_AIPriorityData.AttackType[nCnt] = 0;
	}

	// 変数の初期化
	m_BossState							 = STATE_NORMAL;
	m_BossOneActionPattern				 = ACTION_PATTERN_STAY;
	m_AttckType							 = ATTACKTYPE_NONE;
	m_AttckTypeOld[SAVE_ATTACKOLD_NUM]	 = {};
	m_PostureType						 = POSTURETYPE_STAND;
	m_AttackAIState						 = AI_STATE_GET_INFORMATION;
	m_pCollision						 = nullptr;
	m_ShotCount							 = 0;
	m_nCoolTime							 = COOLTIME_BASE;
	m_nShotIntervalTime					 = 0;
	m_nTriggerCount						 = 0;
	m_nBalkanAngle						 = 0;
	m_nFirstShotCount					 = 60;
	m_nShotCount						 = 0;
	m_fBalkanRot						 = 0.0f;
	m_fRotTarget						 = -1.57f;
	m_fPartsRotVentilation				 = 0.0f;
	m_AddMove							 = 0.0f;
	m_bFlame							 = false;
	m_bBalkanRotFlag					 = false;
	m_bOpenWeapon						 = false;
	m_bShiftPosture						 = false;
	m_bBalkanGunRotFlag					 = false;
	m_bIntermediateSquat				 = false;
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CBoss_One::~CBoss_One()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CBoss_One::Init(void)
{
	// キャラの初期化
	CCharacter::Init();
	// オフセットの取得
	GetModelSet()->LoadOffset(CModelSet::CHARACTER_TYPE_BOSS_ONE);
	// キャラクタータイプの設定
	GetModelSet()->SetCharacterType(CModelSet::CHARACTER_TYPE_BOSS_ONE);
	//タイプ設定
	CEnemy::SetEnemyType(ENEMY_TYPE::ENEMY_BOSS_DRAGON_NOSUKE);
	//重力無し
	SetGravity(false);
	// ボスの角度の設定_左向き
	SetRotDest(D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	// モーションさせない設定
	GetModelSet()->SetMotion(CModelSet::CHARACTER_MOTION_STATE_NONE);
	// ボスの情報の設定
	SetBossInfo();
	// ガンの生成と設定
	CreateGun();
	// 当たり判定の設定
	SetCollision();
	// 回転の差分
	m_fBalkanRotDifferencial -= D3DX_PI / 120.0f;

	return S_OK;
}
// =====================================================================================================================================================================
//
// 終了
//
// =====================================================================================================================================================================
void CBoss_One::Uninit(void)
{
	for(int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		// 銃のポインタ
		if (m_pGun[nCnt])
		{
			delete m_pGun[nCnt];
			m_pGun[nCnt] = nullptr;
		}
	}

	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}

	CCharacter::Uninit();
}
// =====================================================================================================================================================================
//
// 更新
//
// =====================================================================================================================================================================
void CBoss_One::Update(void)
{
	// ガンの更新
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_pGun[nCnt]->Update();
	}
	// ガンのオフセット座標の更新
	SetGunOffsetPos(D3DXVECTOR3(GetModelSet()->GetCharacterModelList()[21]->GetPosition()));
	// ガンの座標の更新
	SetGunPos();

	if (CCharacter::GetCharacterState() != CHARACTER_STATE_DEATH)
	{
		// ボスの行動管理
		Behavior();
	}

	// 回転の計算
	CalcRotationBalkan(m_fRotTarget, GetModelSet()->GetCharacterModelList()[20]->GetRot().x);
	// 回転量の更新
	SetBalkanRot(GetModelSet()->GetCharacterModelList()[20]->GetRot().x);
	// 弾が向かう角度
	m_pGun[WEAPONTYPE_BALKAN]->SetShotRot(
		D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[20]->GetRot().x * -1.0f)));
	// ボスのモーション
	Motion();
	// 当たり判定の更新
	UpdateCollision();

	// キャラクターの更新
	CCharacter::Update();
}
// =====================================================================================================================================================================
//
// 描画
//
// =====================================================================================================================================================================
void CBoss_One::Draw(void)
{
	CCharacter::Draw();

	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_pGun[nCnt]->Draw();
	}
}
// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CBoss_One::DebugInfo(void)
{

}
// =====================================================================================================================================================================
//
// モデルのクリエイト
//
// =====================================================================================================================================================================
CBoss_One *CBoss_One::Create()
{
	// メモリを確保
	CBoss_One*pBoss_One = new CBoss_One(OBJTYPE_BOSSONE);
	// タグの設定
	pBoss_One->SetTag(TAG::ENEMY);
	// 初期化
	pBoss_One->Init();
	// 値を返す
	return pBoss_One;
}

// =====================================================================================================================================================================
//
// ボスの情報の読み込み
//
// =====================================================================================================================================================================
void CBoss_One::Boss_One_DataLoad()
{
	FILE *pFile;					// ファイルポイント
	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字

									// ファイルを開く
	pFile = fopen(m_BossOneFileName, "r");

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
				if (strcmp(cHeadText, "BOSSONESET") == 0)
				{
					// END_ITEMSETが来るまでループ
					while (strcmp(cHeadText, "END_BOSSONESET") != 0)
					{
						fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
						sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

																	// DELETEが来たら
						if (strcmp(cHeadText, "LIFE") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BossOneData.nLife);	// 比較用テキストにDELETEを代入
						}
						// SPEEDが来たら
						else if (strcmp(cHeadText, "COOLTIME") == 0)
						{
							sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BossOneData.nCoolTime);	// 比較用テキストにSPEEDを代入
						}
						// COLLISIONSIZEが来たら
						else if (strcmp(cHeadText, "COLLISIONSIZE_0") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.CollisionSize[POSTURETYPE_STAND].x,
								&m_BossOneData.CollisionSize[POSTURETYPE_STAND].y,
								&m_BossOneData.CollisionSize[POSTURETYPE_STAND].z);										// 比較用テキストにCOLLISIONSIZEを代入
						}
						// COLLISIONSIZEが来たら
						else if (strcmp(cHeadText, "COLLISIONSIZE_1") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.CollisionSize[POSTURETYPE_SQUAT].x,
								&m_BossOneData.CollisionSize[POSTURETYPE_SQUAT].y,
								&m_BossOneData.CollisionSize[POSTURETYPE_SQUAT].z);										// 比較用テキストにCOLLISIONSIZEを代入
						}

						// GUNOFSET_0が来たら
						else if (strcmp(cHeadText, "GUNOFSET_0") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_BALKAN].x,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_BALKAN].y,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_BALKAN].z);										// 比較用テキストにCOLLISIONSIZEを代入
						}
						// GUNOFSET_1が来たら
						else if (strcmp(cHeadText, "GUNOFSET_1") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_FLAMETHROWER].x,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_FLAMETHROWER].y,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_FLAMETHROWER].z);										// 比較用テキストにCOLLISIONSIZEを代入
						}
						// GUNOFSET_2が来たら
						else if (strcmp(cHeadText, "GUNOFSET_2") == 0)
						{
							sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_INCENDIARY].x,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_INCENDIARY].y,
								&m_BossOneData.GunShotOfsetPos[WEAPONTYPE_INCENDIARY].z);										// 比較用テキストにCOLLISIONSIZEを代入
						}
						else if (strcmp(cHeadText, "END_BOSSONESET") == 0)
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
		MessageBox(NULL, "ボス1のデータ読み込み失敗", "警告", MB_ICONWARNING);
	}
}

// =====================================================================================================================================================================
//
// ボスのデフォルトモーション
//
// =====================================================================================================================================================================
bool CBoss_One::DefaultMotion(void){return false;}

// =====================================================================================================================================================================
//
// ボスのモーション
//
// =====================================================================================================================================================================
void CBoss_One::Motion(void)
{
	if (GetModelSet()->GetCharacterModelList()[14]->GetRot().x <= 0)
	{
		m_fPartsRotVentilation = 0.01f;
	}
	else if (GetModelSet()->GetCharacterModelList()[14]->GetRot().x >= (1.57f / 3.5f))
	{
		m_fPartsRotVentilation = -0.015f;
	}

	// パーツを回転させる
	GetModelSet()->GetCharacterModelList()[14]->GetRot().x += m_fPartsRotVentilation;
	GetModelSet()->GetCharacterModelList()[15]->GetRot().x += m_fPartsRotVentilation;
}

// =====================================================================================================================================================================
//
// ダメージを受けた時のリアクション
//
// =====================================================================================================================================================================
void CBoss_One::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);
	//CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
}
// =====================================================================================================================================================================
//
// 死んだ時のリアクション
//
// =====================================================================================================================================================================
void CBoss_One::DeathReaction()
{
	//死亡フラグをたてる
	this->SetDieFlag(true);
	CCharacter::DeathReaction();

	//イベントクリア
	CManager::GetGame()->GetGameManager()->EventClear();

	//nullcheck
	if (CManager::GetGame())
	{
		CManager::GetGame()->GetGameManager()->SetGameState(CGameManager::GAMESTATE::RESULT);
	}
}

// =====================================================================================================================================================================
//
// ステートが変更した瞬間の処理
//
// =====================================================================================================================================================================
void CBoss_One::StateChangeReaction()
{
	CCharacter::StateChangeReaction();

	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_NORMAL:
		break;

	case CHARACTER_STATE_DAMAGE_FLASHING:

		break;
	case CHARACTER_STATE_DAMAGE_RED:

		break;
	case CHARACTER_STATE_INVINCIBLE:

		break;
	case CHARACTER_STATE_DEATH:
		SetStateCount(240);
		break;
	}
}
// =====================================================================================================================================================================
//
// ステート
//
// =====================================================================================================================================================================
void CBoss_One::State()
{
	CCharacter::State();

	//ステータスの処理
	switch (CCharacter::GetCharacterState())
	{
	case CHARACTER_STATE_DEATH:
		//爆発
		if (GetCharacterStateCnt() % 3 == 0)
		{
			CParticle::CreateFromText(GetPosition() + CHossoLibrary::RandomVector3(250.0f), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION);
		}
		break;
	}
}


// =====================================================================================================================================================================
//
// 待機時の行動
//
// =====================================================================================================================================================================
void CBoss_One::StayAction()
{
	// --- 変数の初期化 ---  //
	m_AttckType			 = ATTACKTYPE_NONE;
	m_bShiftPosture		 = false;
	m_fRotTarget		 = -1.57f;
	m_nFirstShotCount	 = 60;
	m_fBalkanRot		 = GetModelSet()->GetCharacterModelList()[20]->GetRot().x;
	m_nBalkanAngle		 = 0;
	// 弾を撃った回数をリセット
	SetShotCount(0);
	// インターバルの時間をリセット
	SetShotIntervalTime(0);
	// トリガーのカウントのリセット
	SetTriggerCount(0);

	if (m_AttckTypeOld[0] == ATTACKTYPE_BALKAN)
	{
		SetBalkan(false, m_BossState);
	}
	else if (m_AttckTypeOld[0] == ATTACKTYPE_FLAMERADIATION)
	{
		SetFlameThrower(false);
	}

	for (int nCnt = 0; nCnt < ATTACKTYPE_MAX; nCnt++)
	{
		m_AIPriorityData.AttackType[nCnt] = PRIORITY_POINT_NONE;
	}

	//
	m_AttackAIState = AI_STATE_GET_INFORMATION;
	// 配列の初期化
	m_AIPriorityData.nPriorityData.clear();

	// クールタイムの計算
	Cooltime_Decrease();
}

// =====================================================================================================================================================================
//
// クールタイムの設定
//
// =====================================================================================================================================================================
void CBoss_One::SetCoolTime(int time)
{
	if (time == NULL)
	{
		switch (m_BossState)
		{
		case CBoss_One::STATE_NORMAL:
			m_nCoolTime = COOLTIME_BASE;
			break;
		case CBoss_One::STATE_RUNAWAY:
			m_nCoolTime = COOLTIME_BASE;
			break;
		}
	}
	else
	{
		m_nCoolTime = time;
	}
}

// =====================================================================================================================================================================
//
// ガンのオフセット座標の更新
//
// =====================================================================================================================================================================
void CBoss_One::SetGunOffsetPos(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_Gun_OffsetPos[nCnt] = GetModelSet()->GetCharacterModelList()[20 + nCnt]->GetPosition();
	}
}

// =====================================================================================================================================================================
//
// ガンのオフセット座標の取得
//
// =====================================================================================================================================================================
D3DXVECTOR3 CBoss_One::GetGunOffsetPos(BOSS_ONE_WEAPONTYPE type)
{
	return m_Gun_OffsetPos[type];
}

// =====================================================================================================================================================================
//
// ガンの座標の更新
//
// =====================================================================================================================================================================
void CBoss_One::SetGunPos()
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_Gun_Pos[nCnt] = m_Gun_OffsetPos[nCnt] + GetPosition();
		if (nCnt == WEAPONTYPE_FLAMETHROWER)
		{
			m_Gun_Pos[nCnt].y -= 50.0f;
		}
	}
}

// =====================================================================================================================================================================
//
// ガンの移動の更新
//
// =====================================================================================================================================================================
void CBoss_One::MoveGun(D3DXVECTOR3	&PartsPos , D3DXVECTOR3 move)
{
	PartsPos += move;
}

// =====================================================================================================================================================================
//
// クールタイムの減少
//
// =====================================================================================================================================================================
void CBoss_One::Cooltime_Decrease()
{
	// クールタイムの減少
	m_nCoolTime--;

	// クールタイムが0以下になった時
	if (m_nCoolTime <= 0)
	{
		// 状態を攻撃に変える
		SetBossAction(ACTION_PATTERN_AI_ATTACK);
	}
}

// =====================================================================================================================================================================
//
// 回転の計算
//
// =====================================================================================================================================================================
void CBoss_One::CalcRotationBalkan(const float fTarget, float fCurrent)
{
	//目標点と現在の差分（回転）
	float diffRot = fTarget - fCurrent;

	//3.14の超過分の初期化（回転）
	CHossoLibrary::CalcRotation(fCurrent);
	CHossoLibrary::CalcRotation(diffRot);

	//求めた差分だけ追従する計算
	GetModelSet()->GetCharacterModelList()[20]->GetRot().x += diffRot * 0.1f;
}

// =====================================================================================================================================================================
//
// ベクトルの長さを計算する
//
// =====================================================================================================================================================================
float CBoss_One::get_vector_length(D3DXVECTOR3 vectol)
{
	return powf((vectol.x * vectol.x) + (vectol.y * vectol.y) + (vectol.z * vectol.z), 0.5);
}

// =====================================================================================================================================================================
//
// ベクトル内積
//
// =====================================================================================================================================================================
float CBoss_One::dot_product(D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{
	return vl.x * vr.x + vl.y * vr.y + vl.z * vr.z;
}

// =====================================================================================================================================================================
//
// ２つのベクトルABのなす角度θを求める
//
// =====================================================================================================================================================================
float CBoss_One::AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B)
{
	//　※ベクトルの長さが0だと答えが出ませんので注意してください。

	//ベクトルAとBの長さを計算する
	float length_A = get_vector_length(A);
	float length_B = get_vector_length(B);

	//内積とベクトル長さを使ってcosθを求める
	float cos_sita = dot_product(A, B) / (length_A * length_B);

	//cosθからθを求める
	float sita = acos(cos_sita);

	//ラジアンでなく0～180の角度でほしい場合はコメント外す
	//sita = sita * 180.0f / D3DX_PI;
	int nAngle = (int)(sita * 180.0f / D3DX_PI);

	// 今の回転量と求めた回転量が同じなら0.0fを返す
	if (m_nBalkanAngle == nAngle)
	{
		return 0.0f;
	}
	// 違うなら求めた角度と今の回転量を計算し回転量を求める
	else
	{
		m_nBalkanAngle = nAngle;

		sita = D3DX_PI - sita;
		sita *= -1.0f;

		return (sita - m_fBalkanRot);
	}

	// 角度を返す
	return sita;
}

// =====================================================================================================================================================================
//
// 焼夷弾
//
// =====================================================================================================================================================================
void CBoss_One::ShotIncendiary()
{
	// 弾を3回撃った時
	if (m_nShotCount >= 3)
	{
		// クールタイムの設定
		SetCoolTime(NULL);
		// ボスの状態を変更
		SetBossAction(ACTION_PATTERN_STAY);
	}
	else
	{
		// 50フレームごとに弾を撃つ
		if (m_nShotIntervalTime <= 0)
		{
			m_pGun[WEAPONTYPE_INCENDIARY]->SetShotRot(
				D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[22]->GetRot().x * -1.0f)));
			// 焼夷弾を撃つ
			m_pGun[WEAPONTYPE_INCENDIARY]->Shot();
			// インターバルの時間を設定
			SetShotIntervalTime(50);
			// 弾を撃った回数を加算
			m_nShotCount++;
		}

		// インターバルの時間を減少
		m_nShotIntervalTime--;
	}
}

// =====================================================================================================================================================================
//
// バルカン
//
// =====================================================================================================================================================================
void CBoss_One::ShotBalkan()
{
	if (m_bOpenWeapon)
	{
		// 5トリガー撃った時_暴走状態用
		if (m_nTriggerCount >= 5)
		{
			// クールタイムの設定
			SetCoolTime(NULL);
			// ボスの状態を変更
			SetBossAction(ACTION_PATTERN_STAY);
		}
		else
		{
			switch (m_BossState)
			{
			case CBoss_One::STATE_NORMAL:

				// ガンの向きを往復させ回転させる
				SetRotBalkan(m_BossState);
				// 初弾を撃つまでの時間
				m_nFirstShotCount--;
				if (m_nFirstShotCount <= 0)
				{
					if (m_nShotIntervalTime <= 0)
					{
						// バルカンを撃つ
						m_pGun[WEAPONTYPE_BALKAN]->Shot();
						// 弾を撃った回数を加算
						m_nShotCount++;
						// インターバルの時間を設定
						SetShotIntervalTime(10);
						// 10発撃った時
						if (m_nShotCount >= 15)
						{
							// ショットカウントの初期化
							SetShotCount(0);
							// クールタイムの設定
							SetCoolTime(NULL);
							// ボスの状態を変更
							SetBossAction(ACTION_PATTERN_STAY);
						}
					}
					// インターバルの設定
					else if (m_nShotIntervalTime >= 0)
					{
						// インターバルの時間を減少
						m_nShotIntervalTime--;
					}
				}
				else
				{
					m_fRotTarget = -D3DX_PI / 4;
				}

				break;

			case CBoss_One::STATE_RUNAWAY:
				if (!m_bBalkanRotFlag)
				{
					// ガンの向きをプレイヤーの方へ向ける
					SetRotBalkan(m_BossState);
					//
					m_bBalkanRotFlag = true;
				}


				if (m_bBalkanRotFlag)
				{
					m_nFirstShotCount--;
					if (m_nFirstShotCount <= 0)
					{
						// 30フレームごとに1トリガー撃つ
						if (m_nShotIntervalTime <= 0)
						{
							// バルカンを撃つ
							m_pGun[WEAPONTYPE_BALKAN]->Shot();
							// 弾を撃った回数を加算
							m_nShotCount++;
							// 1トリガー撃った時
							if (m_nShotCount >= 3)
							{
								// インターバルの時間を設定
								SetShotIntervalTime(30);
								// ショットカウントの初期化
								SetShotCount(0);
								// 何トリガー撃ったかのカウントを加算
								m_nTriggerCount++;
								m_bBalkanRotFlag = false;
							}
							// インターバルの設定
							else if (m_nShotCount >= 0)
							{
								// インターバルの時間を設定
								SetShotIntervalTime(10);
							}
						}

						if (m_bBalkanRotFlag)
						{
							// インターバルの時間を減少
							m_nShotIntervalTime--;
						}
					}
				}
				break;
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 火炎放射の最初の爆発
//
// =====================================================================================================================================================================
void CBoss_One::ShotWarning()
{
	m_pGun[WEAPONTYPE_FLAMETHROWER]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[21]->GetRot().x * -1.0f)));

	// 弾を7回撃った時
	if (m_nShotCount >= 7)
	{
		// 撃ち終わったら弾を動かせるようにする
		m_pGun[WEAPONTYPE_FLAMETHROWER]->SetMoveZero(false);
		// クールタイムの設定
		SetCoolTime(30);
		// 弾を撃った回数をリセット
		m_nShotCount = 0;
		// 火炎放射を撃つ
		m_bFlame = true;
	}
	else
	{
		// 10フレームごとに弾を撃つ
		if (m_nShotIntervalTime <= 0)
		{
			// 弾の動きを止める
			m_pGun[WEAPONTYPE_FLAMETHROWER]->SetMoveZero(true);
			// 火炎放射を撃つ
			m_pGun[WEAPONTYPE_FLAMETHROWER]->Shot();
			// インターバルの時間を設定
			SetShotIntervalTime(10);
			// 弾を撃った回数を加算
			m_nShotCount++;
		}

		// インターバルの時間を減少
		m_nShotIntervalTime--;
	}
}

// =====================================================================================================================================================================
//
// 火炎放射
//
// =====================================================================================================================================================================
void CBoss_One::ShotFlameRadiation()
{
	m_pGun[WEAPONTYPE_FLAMETHROWER]->SetShotRot(
		D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[21]->GetRot().x * -1.0f)));

	// 弾を16回撃った時
	if (m_nShotCount >= (16 + 1))
	{
		// クールタイムの設定
		SetCoolTime(NULL);
		// 弾を撃った回数をリセット
		m_nShotCount = 0;
		//
		m_bFlame = false;

		// ボスの状態を変更
		SetBossAction(ACTION_PATTERN_STAY);

		m_AttckType = ATTACKTYPE_NONE;
	}
	else
	{
		// 50フレームごとに弾を撃つ
		if (m_nShotIntervalTime <= 0)
		{
			// 火炎放射を撃つ
			m_pGun[WEAPONTYPE_FLAMETHROWER]->Shot();
			// インターバルの時間を設定
			SetShotIntervalTime(10);
			// 弾を撃った回数を加算
			m_nShotCount++;
		}

		// インターバルの時間を減少
		m_nShotIntervalTime--;
	}
}

// =====================================================================================================================================================================
//
// 姿勢変更
//
// =====================================================================================================================================================================
void CBoss_One::ShiftPosture()
{
	if (!m_bShiftPosture)
	{
		m_AddMove += 0.1f;
	}

	if (m_PostureType == POSTURETYPE_STAND)
	{

		// 膝上
		if (GetModelSet()->GetCharacterModelList()[4]->GetRot().z >= -1.25f &&
			GetModelSet()->GetCharacterModelList()[5]->GetRot().z >= -1.25f)
		{
			GetModelSet()->GetCharacterModelList()[4]->GetRot().z -= m_AddMove;
			GetModelSet()->GetCharacterModelList()[5]->GetRot().z -= m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[4]->GetRot().z <= -1.25f &&
				GetModelSet()->GetCharacterModelList()[5]->GetRot().z <= -1.25f)
			{
				GetModelSet()->GetCharacterModelList()[4]->GetRot().z = -1.25f;
				GetModelSet()->GetCharacterModelList()[5]->GetRot().z = -1.25f;
			}
		}

		if (GetModelSet()->GetCharacterModelList()[2]->GetRot().z <= 1.25f &&
			GetModelSet()->GetCharacterModelList()[3]->GetRot().z <= 1.25f)
		{
			GetModelSet()->GetCharacterModelList()[2]->GetRot().z += m_AddMove;
			GetModelSet()->GetCharacterModelList()[3]->GetRot().z += m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[2]->GetRot().z >= 1.25f &&
				GetModelSet()->GetCharacterModelList()[3]->GetRot().z >= 1.25f)
			{
				GetModelSet()->GetCharacterModelList()[2]->GetRot().z = 1.25f;
				GetModelSet()->GetCharacterModelList()[3]->GetRot().z = 1.25f;
			}
		}


		// 膝下
		if (GetModelSet()->GetCharacterModelList()[8]->GetRot().z >= -0.9f &&
			GetModelSet()->GetCharacterModelList()[9] ->GetRot().z >= -0.9f)
		{
			GetModelSet()->GetCharacterModelList()[8]->GetRot().z -= m_AddMove;
			GetModelSet()->GetCharacterModelList()[9] ->GetRot().z -= m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[8]->GetRot().z <= -0.9f &&
				GetModelSet()->GetCharacterModelList()[9] ->GetRot().z <= -0.9f)
			{
				GetModelSet()->GetCharacterModelList()[8]->GetRot().z = -0.9f;
				GetModelSet()->GetCharacterModelList()[9] ->GetRot().z = -0.9f;
			}
		}

		if (GetModelSet()->GetCharacterModelList()[6]->GetRot().z <= 0.9f &&
			GetModelSet()->GetCharacterModelList()[7] ->GetRot().z <= 0.9f)
		{
			GetModelSet()->GetCharacterModelList()[6]->GetRot().z += m_AddMove;
			GetModelSet()->GetCharacterModelList()[7] ->GetRot().z += m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[6]->GetRot().z >= 0.9f &&
				GetModelSet()->GetCharacterModelList()[7] ->GetRot().z >= 0.9f)
			{
				GetModelSet()->GetCharacterModelList()[6]->GetRot().z = 0.9f;
				GetModelSet()->GetCharacterModelList()[7] ->GetRot().z = 0.9f;
			}
		}

		m_bIntermediateSquat = true;
		// ボディーの高さ
		if (GetPosition().y >= POSTURE_HEIGHT_SQUAT)
		{
			GetPosition().y -= m_AddMove * 2;

			if (GetPosition().y <= POSTURE_HEIGHT_SQUAT)
			{
				GetPosition().y = POSTURE_HEIGHT_SQUAT;
				// クールタイムの設定
				SetCoolTime(NULL);
				//
				m_bShiftPosture = true;
				m_bIntermediateSquat = false;
				m_PostureType = POSTURETYPE_SQUAT;
				m_AddMove = 0.0f;
				// ボスの状態を変更
				SetBossAction(ACTION_PATTERN_STAY);
			}
		}
	}
	else
	{
		if (GetModelSet()->GetCharacterModelList()[2]->GetRot().z >= 0.0f &&
			GetModelSet()->GetCharacterModelList()[3]->GetRot().z >= 0.0f)
		{
			GetModelSet()->GetCharacterModelList()[2]->GetRot().z -= m_AddMove;
			GetModelSet()->GetCharacterModelList()[3]->GetRot().z -= m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[2]->GetRot().z <= 0.0f &&
				GetModelSet()->GetCharacterModelList()[3]->GetRot().z <= 0.0f)
			{
				GetModelSet()->GetCharacterModelList()[2]->GetRot().z = 0.0f;
				GetModelSet()->GetCharacterModelList()[3]->GetRot().z = 0.0f;
			}
		}

		if (GetModelSet()->GetCharacterModelList()[4]->GetRot().z <= 0.0f &&
			GetModelSet()->GetCharacterModelList()[5]->GetRot().z <= 0.0f)
		{
			GetModelSet()->GetCharacterModelList()[4]->GetRot().z += m_AddMove;
			GetModelSet()->GetCharacterModelList()[5]->GetRot().z += m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[4]->GetRot().z >= 0.0f &&
				GetModelSet()->GetCharacterModelList()[5]->GetRot().z >= 0.0f)
			{
				GetModelSet()->GetCharacterModelList()[4]->GetRot().z = 0.0f;
				GetModelSet()->GetCharacterModelList()[5]->GetRot().z = 0.0f;
			}
		}


		if (GetModelSet()->GetCharacterModelList()[7]->GetRot().z >= 0.0f &&
			GetModelSet()->GetCharacterModelList()[7]->GetRot().z >= 0.0f)
		{
			GetModelSet()->GetCharacterModelList()[6]->GetRot().z -= m_AddMove;
			GetModelSet()->GetCharacterModelList()[7]->GetRot().z -= m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[6]->GetRot().z <= 0.0f &&
				GetModelSet()->GetCharacterModelList()[7]->GetRot().z <= 0.0f)
			{
				GetModelSet()->GetCharacterModelList()[6]->GetRot().z = 0.0f;
				GetModelSet()->GetCharacterModelList()[7]->GetRot().z = 0.0f;
			}
		}

		if (GetModelSet()->GetCharacterModelList()[8]->GetRot().z <= 0.0f &&
			GetModelSet()->GetCharacterModelList()[9]->GetRot().z <= 0.0f)
		{
			GetModelSet()->GetCharacterModelList()[8]->GetRot().z += m_AddMove;
			GetModelSet()->GetCharacterModelList()[9]->GetRot().z += m_AddMove;

			if (GetModelSet()->GetCharacterModelList()[8]->GetRot().z >= 0.0f &&
				GetModelSet()->GetCharacterModelList()[9]->GetRot().z >= 0.0f)
			{
				GetModelSet()->GetCharacterModelList()[8]->GetRot().z = 0.0f;
				GetModelSet()->GetCharacterModelList()[9]->GetRot().z = 0.0f;
			}
		}

		if (GetPosition().y <= POSTURE_HEIGHT_STAND)
		{
			m_AddMove += 0.1f;
			GetPosition().y += m_AddMove * 2;

			if (GetPosition().y >= POSTURE_HEIGHT_STAND)
			{
				GetPosition().y = POSTURE_HEIGHT_STAND;
				// クールタイムの設定
				SetCoolTime(NULL);
				//
				m_bShiftPosture = true;
				m_PostureType = POSTURETYPE_STAND;
				m_AddMove = 0.0f;
				// ボスの状態を変更
				SetBossAction(ACTION_PATTERN_STAY);
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 火炎放射器の移動
//
// =====================================================================================================================================================================
void CBoss_One::SetFlameThrower(bool bOpen)
{
	if (bOpen)
	{
		if ((GetPosition().y + GetModelSet()->GetCharacterModelList()[21]->GetPosition().y) >= -30.0)
		{
			GetModelSet()->GetCharacterModelList()[21]->GetPosition().y -= 2.0f;

			if (GetModelSet()->GetCharacterModelList()[21]->GetPosition().y <= -30.0)
			{
				GetModelSet()->GetCharacterModelList()[21]->GetPosition().y = -30.0f;
				m_bOpenWeapon = true;
			}
		}
	}

	else if (!bOpen)
	{
		if ((GetPosition().y + GetModelSet()->GetCharacterModelList()[21]->GetPosition().y) >= 65.0f)
		{
			GetModelSet()->GetCharacterModelList()[21]->GetPosition().y += 2.0f;

			if (GetModelSet()->GetCharacterModelList()[21]->GetPosition().y >= 65.0f)
			{
				GetModelSet()->GetCharacterModelList()[21]->GetPosition().y = 65.0f;
				m_bOpenWeapon = false;
			}
		}
	}
}


// =====================================================================================================================================================================
//
// バルカンの移動
//
// =====================================================================================================================================================================
void CBoss_One::SetBalkan(bool bOpen, BOSS_ONE_STATE state)
{
	if (bOpen)
	{
		if (state == STATE_NORMAL)
		{
			//m_fRotTarget = -D3DX_PI / 4;
		}
		if ((GetPosition().z - GetModelSet()->GetCharacterModelList()[20]->GetPosition().z) >= -BALKAN_LENGTH)
		{
			GetModelSet()->GetCharacterModelList()[20]->GetPosition().z -= 4.0f;

			if (GetModelSet()->GetCharacterModelList()[20]->GetPosition().z <= -BALKAN_LENGTH)
			{
				GetModelSet()->GetCharacterModelList()[20]->GetPosition().z = -BALKAN_LENGTH;
				m_bOpenWeapon = true;
			}
		}
	}

	else if (!bOpen)
	{
		m_fRotTarget = -1.57f;
		if ((GetPosition().z - GetModelSet()->GetCharacterModelList()[20]->GetPosition().z) <= BALKAN_LENGTH)
		{
			GetModelSet()->GetCharacterModelList()[20]->GetPosition().z += 4.0f;

			if (GetModelSet()->GetCharacterModelList()[20]->GetPosition().z >= BALKAN_LENGTH)
			{
				GetModelSet()->GetCharacterModelList()[20]->GetPosition().z = BALKAN_LENGTH;
				m_bOpenWeapon = false;
			}
		}
	}
}


// =====================================================================================================================================================================
//
// 火炎放射の攻撃管理
//
// =====================================================================================================================================================================
void CBoss_One::ShotFlameManager()
{
	if (m_bOpenWeapon)
	{
		if (!m_bFlame)
		{
			ShotWarning();
		}
		else
		{
			// クールタイムをマイナス
			m_nCoolTime--;
			if (m_nCoolTime <= 0)
			{
				ShotFlameRadiation();
			}
		}
	}
}

// =====================================================================================================================================================================
//
// 攻撃方法をランダムに決める
//
// =====================================================================================================================================================================
void CBoss_One::RandomAttack()
{
	// 攻撃方法を決める デバッグ用
	//m_AttckType = (BOSS_ONE_ATTACKTYPE)get_rand_range(ATTACKTYPE_BALKAN, ATTACKTYPE_SHIFTPOSTURE);

	// しゃがみ状態で攻撃が火炎放射になった場合はやり直し
	do
	{
		// 攻撃方法の設定
		SetAttackType((BOSS_ONE_ATTACKTYPE)get_rand_range(ATTACKTYPE_BALKAN, ATTACKTYPE_SHIFTPOSTURE));

	} while (m_PostureType == POSTURETYPE_SQUAT && m_AttckType == ATTACKTYPE_FLAMERADIATION ||
			 m_AttckTypeOld[0] == ATTACKTYPE_SHIFTPOSTURE && m_AttckType == ATTACKTYPE_SHIFTPOSTURE);
}

// =====================================================================================================================================================================
//
// バルカンの回転
//
// =====================================================================================================================================================================
void CBoss_One::SetRotBalkan(BOSS_ONE_STATE state)
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	if(pPlayer)
	{
		switch (m_BossState)
		{
		case CBoss_One::STATE_NORMAL:
			if (m_fRotTarget >= -D3DX_PI / 4)
			{
				m_fRotTarget = -D3DX_PI / 4;
				m_fBalkanRotDifferencial *= -1.0f;
			}
			else if (m_fRotTarget <= -2.355f)
			{
				// 回転を反映
				m_fRotTarget = -2.355f;
				m_fBalkanRotDifferencial *= -1.0f;
			}

			m_fRotTarget -= m_fBalkanRotDifferencial;

			break;
		case CBoss_One::STATE_RUNAWAY:

			// プレイヤーのポインタ取得
			CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
			D3DXVECTOR3 PlayerPos;

			// プレイヤーがボスの射程外だった時
			if (pPlayer->GetPosition().x >= 150.0f)
			{
				// プレイヤーの座標をボスの目の前にいることにする
				PlayerPos = D3DXVECTOR3(150.0f, pPlayer->GetPosition().y, pPlayer->GetPosition().z);
			}
			else
			{
				// プレイヤーの座標
				PlayerPos = pPlayer->GetPosition();
			}

			// プレイヤーの座標とバルカンの座標を結ぶベクトルを求める
			D3DXVECTOR3 HorizontalAxis = m_Gun_Pos[WEAPONTYPE_BALKAN] - PlayerPos;
			D3DXVECTOR3 VerticalAxis = ZeroVector3;

			// 通常時
			if (m_PostureType == POSTURETYPE_STAND)
			{
				VerticalAxis = D3DXVECTOR3(
					m_Gun_Pos[WEAPONTYPE_BALKAN].x - BALKAN_LENGTH, (m_Gun_Pos[WEAPONTYPE_BALKAN].y - HorizontalAxis.x - BALKAN_LENGTH - PLAYER_HEADLINE), 0.0f);
			}
			// しゃがみ時
			else
			{
				VerticalAxis = D3DXVECTOR3(
					m_Gun_Pos[WEAPONTYPE_BALKAN].x - BALKAN_LENGTH - DIFFERENCE_POSTURE, (m_Gun_Pos[WEAPONTYPE_BALKAN].y - HorizontalAxis.x - BALKAN_LENGTH * 2 - PLAYER_HEADLINE * 2 - DIFFERENCE_POSTURE * 2), 0.0f);
			}

			// 回転を反映
			m_fRotTarget += AngleOf2Vector(VerticalAxis, HorizontalAxis);

			break;
		}
	}

	//
	m_bBalkanGunRotFlag = true;
}


// =====================================================================================================================================================================
//
// 当たり判定の設定
//
// =====================================================================================================================================================================
void CBoss_One::SetCollision()
{
	// ガンの当たり判定の設定
	// 武器用の当たり判定の生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&m_Gun_Pos[WEAPONTYPE_FLAMETHROWER]);
	m_pCollision->SetSize(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

	// 当たり判定設定
	CCharacter::GetCollision()->SetPos(&GetPosition());
	CCharacter::GetCollision()->SetPosOld(&GetPositionOld());
	CCharacter::GetCollision()->SetSize(m_BossOneData.CollisionSize[1]);
	CCharacter::GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
}

// =====================================================================================================================================================================
//
// 決定した攻撃方法を設定する
//
// =====================================================================================================================================================================
void CBoss_One::SetAttackType(BOSS_ONE_ATTACKTYPE type)
{
	m_AttckType = type;

	// Oldの0番目を1番目に代入
	m_AttckTypeOld[ATTACK_PRIORITY - 1] = m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY];
	m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] = m_AttckType;
}

// =====================================================================================================================================================================
//
// ランダム生成
//
// =====================================================================================================================================================================
uint64_t CBoss_One::get_rand_range(uint64_t min_val, uint64_t max_val)
{
	// メルセンヌ・ツイスター法による擬似乱数生成器を、
	// ハードウェア乱数をシードにして初期化
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());

	// 乱数生成器
	static std::mt19937_64 mt64(seed_gen());

	// [min_val, max_val] の一様分布整数 (int) の分布生成器
	std::uniform_int_distribution<uint64_t> get_rand_uni_int(min_val, max_val);

	// 乱数を生成
	return get_rand_uni_int(mt64);
}

// =====================================================================================================================================================================
//
// 当たり判定の更新
//
// =====================================================================================================================================================================
void CBoss_One::UpdateCollision()
{
	if (CCharacter::GetCollision() != nullptr)
	{
		// ガンの当たり判定の座標の更新
		m_pCollision->SetPos(&m_Gun_Pos[WEAPONTYPE_FLAMETHROWER]);
		CCharacter::GetCollision()->BossOne_PlayerCollision();
		CCharacter::GetCollision()->SetPos(&GetPosition());
	}
}

// =====================================================================================================================================================================
//
// ボスのステート管理
//
// =====================================================================================================================================================================
void CBoss_One::BossOneStateManager()
{
	switch (m_BossState)
	{
	case CBoss_One::STATE_NORMAL:
		if (this->GetLife() <= RUNAWAY_BOSSLIFE)
		{
			m_BossState = STATE_RUNAWAY;
		}
		break;
	case CBoss_One::STATE_RUNAWAY:

		break;
	}
}

// =====================================================================================================================================================================
//
// ボスの行動管理
//
// =====================================================================================================================================================================
void CBoss_One::Behavior()
{
	switch (m_BossOneActionPattern)
	{
	case CBoss_One::ACTION_PATTERN_NONE:
		break;
	case CBoss_One::ACTION_PATTERN_STAY:
		// 次の行動を選択
		StayAction();
		break;

	case CBoss_One::ACTION_PATTERN_AI_ATTACK:
		// 次の攻撃方法を選択
		Attack_AI();
		break;

	case CBoss_One::ACTION_PATTERN_ATTACK:
		// ボスの攻撃管理
		BossOneAttackManager();
		break;
	case CBoss_One::ACTION_PATTERN_SHIFT_POSTURE:
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// ボスの攻撃管理
//
// =====================================================================================================================================================================
void CBoss_One::BossOneAttackManager()
{
	// ステート別攻撃方法
	switch (m_AttckType)
	{
	case CBoss_One::ATTACKTYPE_BALKAN:
		SetBalkan(true, m_BossState);
		// バルカンを撃つ
		ShotBalkan();
		break;
	case CBoss_One::ATTACKTYPE_FLAMERADIATION:
		// 火炎放射器を出す
		SetFlameThrower(true);
		// 火炎放射を撃つ
		ShotFlameManager();
		break;
	case CBoss_One::ATTACKTYPE_INCENDIARY:
		// 焼夷弾を撃つ
		ShotIncendiary();
		break;
	case CBoss_One::ATTACKTYPE_SHIFTPOSTURE:
		// 姿勢変更
		ShiftPosture();
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
//
// ボスの攻撃管理AI
//
// =====================================================================================================================================================================
void CBoss_One::Attack_AI()
{
	switch (m_AttackAIState)
	{
		// 必要な情報の取得
	case CBoss_One::AI_STATE_GET_INFORMATION:

		// 攻撃の優先度を計算
		Attack_Priority();

		// それぞれの行動の優先度のアドレスを取得
		for (int nCnt = 0; nCnt < ATTACKTYPE_MAX; nCnt++)
		{
			// 末尾に攻撃優先度の値を追加
			m_AIPriorityData.nPriorityData.emplace_back(&m_AIPriorityData.AttackType[nCnt]);
		}

		m_AttackAIState = AI_STATE_AI;
		break;

		// 情報を元に攻撃を選択する
	case CBoss_One::AI_STATE_AI:

		// 優先度が高い順に入れ替え
		BubbleSort(m_AIPriorityData.nPriorityData);

		// 先頭のアドレスを取得する
		int *nFront = m_AIPriorityData.nPriorityData[0];
		// 先頭の次のアドレスを取得する
		int *nSecond = (m_AIPriorityData.nPriorityData[1]);

		// 攻撃の優先度を先頭から二番目まで保存
		BOSS_ONE_ATTACKTYPE Attack_Priority[ATTACK_PRIORITY];

		for (int nCnt = 0, nCntPrio = 0; nCnt < ATTACKTYPE_MAX, nCntPrio < ATTACK_PRIORITY; nCnt++)
		{
			// 優先度が一番高かった攻撃方法を求める
			if (nFront == &m_AIPriorityData.AttackType[nCnt])
			{
				Attack_Priority[nCntPrio] = (BOSS_ONE_ATTACKTYPE)nCnt;
			}
			// 優先度が二番目に高かった攻撃方法を求める
			else if (nSecond == &m_AIPriorityData.AttackType[nCnt])
			{
				Attack_Priority[nCntPrio] = (BOSS_ONE_ATTACKTYPE)nCnt;
			}
			// どちらかに当てはまっていたらカウントを加算する
			if (nFront == &m_AIPriorityData.AttackType[nCnt] || nSecond == &m_AIPriorityData.AttackType[nCnt])
			{
				nCntPrio++;
			}
		}

		// 優先度が高い行動の優先度を比べ同じならランダムに決定する
		if (*nFront == *nSecond)
		{
			uint64_t nRandomAttack = get_rand_range(0, 1);
			if (nRandomAttack == 0)
			{
				// 一つ前の攻撃方法と今回の最優先攻撃方法が同じじゃなかった時
				if (m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] != Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY])
				{
					// 攻撃方法の設定
					SetAttackType(Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY]);
				}
				else
				{
					// 攻撃方法の設定
					SetAttackType(Attack_Priority[ATTACK_PRIORITY - 1]);
				}
			}
			else
			{
				// 一つ前の攻撃方法と今回の最優先攻撃方法が同じじゃなかった時
				if (m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] != Attack_Priority[ATTACK_PRIORITY - 1])
				{
					// 攻撃方法の設定
					SetAttackType(Attack_Priority[ATTACK_PRIORITY - 1]);
				}
				else
				{
					// 攻撃方法の設定
					SetAttackType(Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY]);
				}
			}
		}
		// 同じじゃない時
		else
		{
			// 一つ前の攻撃方法と今回の最優先攻撃方法が同じじゃなかった時
			if (m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] != Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY])
			{
				// 攻撃方法の設定
				SetAttackType(Attack_Priority[ATTACK_PRIORITY - ATTACK_PRIORITY]);
			}
			else
			{
				// 攻撃方法の設定
				SetAttackType(Attack_Priority[ATTACK_PRIORITY - 1]);
			}
		}

		// 状態を攻撃に変える
		SetBossAction(ACTION_PATTERN_ATTACK);

		break;
	}
}

// =====================================================================================================================================================================
//
// 攻撃の優先度を計算
//
// =====================================================================================================================================================================
void CBoss_One::Attack_Priority()
{
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);

	if (pPlayer)
	{
		// プレイヤーとボスの距離を求める
		const unsigned int nDistance = (unsigned int)this->GetPosition().x - (unsigned int)pPlayer->GetPosition().x;

		// ----- 優先度の設定 ----- //

		// ----- 射程外 ----- //
		if (nDistance <= MIN_PLAYER_DISTANCE)
		{// 最短射程範囲より内側にいる時
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_THREE;
		}

		if (nDistance >= MAX_PLAYER_DISTANCE)
		{// 最長射程範囲より外側にいる時
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_NONE;
		}

		// ----- 射程内 ----- //
		if (nDistance >= MIN_PLAYER_DISTANCE && nDistance <= MAX_PLAYER_DISTANCE)
		{// 射程範囲内の時
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_ONE;
		}

		if (nDistance <= MAX_PLAYER_DISTANCE && nDistance >= RANGE_CENTER)
		{// 最長射程範囲より内側にいて範囲の中心より外側にいる時
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_ONE;
		}
		if (nDistance >= MIN_PLAYER_DISTANCE && nDistance <= RANGE_CENTER)
		{// 最短射程範囲より外側にいて範囲の中心より内側にいる時
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_ONE;
		}
		if (nDistance >= RANGE_CENTER - CENTER_RANGE && nDistance <= RANGE_CENTER + CENTER_RANGE)
		{// 範囲の中心から内と外側に100加えた範囲の内側だった時
			m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	+= PRIORITY_POINT_ONE;
			m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		+= PRIORITY_POINT_TWO;
			m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	+= PRIORITY_POINT_ONE;
		}
	}

	// 例外に該当していた場合は強制的に次の行動を制限する
	Attack_Exception();
}

// =====================================================================================================================================================================
//
// 優先度の数値を初期化
//
// =====================================================================================================================================================================
void CBoss_One::Attack_InitializeDataAll()
{
	m_AIPriorityData.AttackType[ATTACKTYPE_BALKAN]			 = PRIORITY_POINT_NONE;
	m_AIPriorityData.AttackType[ATTACKTYPE_FLAMERADIATION]	 = PRIORITY_POINT_NONE;
	m_AIPriorityData.AttackType[ATTACKTYPE_INCENDIARY]		 = PRIORITY_POINT_NONE;
	m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE]	 = PRIORITY_POINT_NONE;
}

// =====================================================================================================================================================================
//
// 指定した優先度の数値を初期化
//
// =====================================================================================================================================================================
void CBoss_One::Attack_InitializeData(BOSS_ONE_ATTACKTYPE type)
{
	m_AIPriorityData.AttackType[type] = PRIORITY_POINT_NONE;
}

// =====================================================================================================================================================================
//
// 優先度を決めるにあたっての例外
//
// =====================================================================================================================================================================
void CBoss_One::Attack_Exception()
{
	// 二回連続で姿勢変更をしない
	if (m_AttckTypeOld[ATTACK_PRIORITY - ATTACK_PRIORITY] == ATTACKTYPE_SHIFTPOSTURE)
	{
		Attack_InitializeData(ATTACKTYPE_SHIFTPOSTURE);
	}

	// しゃがんでから二回目の行動で強制的に姿勢を変更させる
	if (m_AttckTypeOld[ATTACK_PRIORITY - 1] == ATTACKTYPE_SHIFTPOSTURE)
	{
		// 次の行動が決まっている場合優先度の数値を初期化する
		Attack_InitializeDataAll();
		//
		m_AIPriorityData.AttackType[ATTACKTYPE_SHIFTPOSTURE] = PRIORITY_POINT_MAX;
	}

	// しゃがんでいる時に火炎放射を撃たせない
	if (m_PostureType == POSTURETYPE_SQUAT)
	{
		Attack_InitializeData(ATTACKTYPE_FLAMERADIATION);
	}
}

// =====================================================================================================================================================================
//
// バブルソート 大きい順
//
// =====================================================================================================================================================================
void CBoss_One::BubbleSort(std::vector<int*> &data)
{
	for (int nCnt = 0; nCnt < (int)data.size() - 1; nCnt++)
	{
		for (int num = (int)data.size() - 1; num > nCnt; num--)
		{
			if (*data[num - 1] < *data[num])
			{  // 大きさが逆転している箇所があったら swap
				std::swap(data[num - 1], data[num]);
			}
		}
	}
}

// =====================================================================================================================================================================
//
// ボスのステータスの設定
//
// =====================================================================================================================================================================
void CBoss_One::SetBossInfo()
{
	// 体力の初期値
	CCharacter::SetLife(m_BossOneData.nLife);
	// 銃の傾き
	GetModelSet()->GetCharacterModelList()[22]->GetRot().x -= 1.0f;
	GetModelSet()->GetCharacterModelList()[21]->GetRot().x -= 1.57f;
}

// =====================================================================================================================================================================
//
// ガンの生成と設定
//
// =====================================================================================================================================================================
void CBoss_One::CreateGun()
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		// 銃の生成
		m_pGun[nCnt] = CGun::Create();
		//マトリックス設定
		m_pGun[nCnt]->SetHandMtx(GetModelSet()->GetCharacterModelList()[20 + nCnt]->GetMatrix());
		// 銃の弾の種類
		m_pGun[nCnt]->SetTag(GetTag());
		// 銃の弾の種類
		m_pGun[nCnt]->SetGunType(static_cast<CGun::GUN_TYPE>(CGun::GUNTYPE_BALKAN + nCnt));
		// 発射位置のオフセットの設定
		m_pGun[nCnt]->SetShotOffsetPos(m_BossOneData.GunShotOfsetPos[nCnt]);
		// 弾を撃つ方向を設定
		m_pGun[nCnt]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetModelSet()->GetCharacterModelList()[20 + nCnt]->GetRot().x)));
	}
	// ガンのオフセット座標の更新
	SetGunOffsetPos(D3DXVECTOR3(GetModelSet()->GetCharacterModelList()[21]->GetPosition()));
	// ガンの座標の更新
	SetGunPos();
}
