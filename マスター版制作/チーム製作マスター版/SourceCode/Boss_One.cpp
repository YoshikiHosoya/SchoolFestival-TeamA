// =====================================================================================================================================================================
//
// ボス1の処理 [boss_one.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "Boss_One.h"
#include "model.h"
#include "collision.h"
#include "game.h"
#include "manager.h"
#include "map.h"
#include "gun.h"
#include "player.h"
#include <random>

//====================================================================
//マクロ定義
//====================================================================

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
BOSS_ONE_DATA		CBoss_One::m_BossOneData = {};									// データ
int					CBoss_One::m_nLife = 0;											// 体力
D3DXVECTOR3			CBoss_One::m_CollisionSize[POSTURETYPE_MAX] = {};				// 当たり判定の大きさ
D3DXVECTOR3			CBoss_One::m_GunShotOfsetPos[WEAPONTYPE_MAX] = {};				// ガンのオフセット

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
CBoss_One::CBoss_One(OBJ_TYPE type) :CCharacter(type)
{
	// ボスの初期状態
	m_BossOneState = BOSS_ONE_STATE_STAY;
	m_AttckType = ATTACKTYPE_NONE;
	m_ShotCount = 0;
	m_pCollision = nullptr;
	m_nCoolTime = 0;
	m_nShotIntervalTime = 0;
	m_nShotCount_Incendiary = 0;
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
	LoadOffset(CCharacter::CHARACTER_TYPE_BOSS_ONE);
	// キャラクタータイプの設定
	SetCharacterType(CCharacter::CHARACTER_TYPE_BOSS_ONE);
	//重力無し
	SetGravity(false);
	// 角度の設定
	SetRotDest(D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	// 体力の初期値
	CCharacter::SetLife(m_nLife);
	// モーションさせない設定
	SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	// 大砲を傾ける
	GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_INCENDIARY))->GetRot().x += 0.6f;
	//GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x -= 1.57f;
	GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x -= 1.0f;

	// 武器用の当たり判定の生成
	m_pCollision = CCollision::Create();

	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		// 銃の生成
		m_pGun[nCnt] = CGun::Create(GetCharacterModelPartsList(
			static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetMatrix());
		// 銃の弾の種類
		m_pGun[nCnt]->GetTag() = TAG_ENEMY;
		// 銃の弾の種類
		m_pGun[nCnt]->SetGunType(static_cast<CGun::GUN_TYPE>(CGun::GUNTYPE_BALKAN + nCnt));
		// 発射位置のオフセットの設定
		m_pGun[nCnt]->SetShotOffsetPos(m_GunShotOfsetPos[nCnt]);
		// 弾を撃つ方向を設定
		m_pGun[nCnt]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetRot().x)));
	}
	// ガンのオフセット座標の更新
	SetGunOffsetPos(D3DXVECTOR3(GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition()));
	// ガンの座標の更新
	SetGunPos();

	// ガンの当たり判定の設定
	m_pCollision->SetPos(&m_Gun_Pos);
	m_pCollision->SetSize2D(D3DXVECTOR3(100.0f, 100.0f, 0.0f));
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	// 当たり判定設定
	CCharacter::GetCollision()->SetPos(&GetPosition());
	CCharacter::GetCollision()->SetSize2D(m_CollisionSize[0]);
	CCharacter::GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);

	return S_OK;
}
// =====================================================================================================================================================================
//終了
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
//更新
// =====================================================================================================================================================================
void CBoss_One::Update(void)
{
	// ガンの更新
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_pGun[nCnt]->Update();
	}
	// ガンのオフセット座標の更新
	SetGunOffsetPos(D3DXVECTOR3(GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition()));
	// ガンの移動
	//MoveGun(GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition(), D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	// ガンの座標の更新
	SetGunPos();
	// ガンの当たり判定の座標の更新
	m_pCollision->SetPos(&m_Gun_Pos);

	//	//m_pGun[WEAPONTYPE_FLAMETHROWER]->Shot();
	//	// 弾を撃つ方向を設定

	// 攻撃状態だった時
	if (m_BossOneState == BOSS_ONE_STATE_ATTACK)
	{

	}

	// ボスの状態ごとの処理
	BossOneStateManager();
	// ボスの攻撃管理
	BossOneAttackManager();

	// 当たり判定
	if (CCharacter::GetCollision() != nullptr)
	{
		// 座標の更新 pos
		CCharacter::GetCollision()->SetPos(&GetPosition());
	}

	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	float fDist = this->GetPosition().x - pPlayer->GetPosition().x;

	CDebugProc::Print("ボスとプレイヤーの距離 --- x --- %f\n", fDist);
	CDebugProc::Print("ボスのステート %d\n", m_BossOneState);

	// キャラクターの更新
	CCharacter::Update();
}
// =====================================================================================================================================================================
//描画
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
//デバッグ
// =====================================================================================================================================================================
void CBoss_One::DebugInfo(void)
{
	//CDebugProc::Print("");
	CCharacter::DebugInfo();
}
// =====================================================================================================================================================================
//モデルのクリエイト
// =====================================================================================================================================================================
CBoss_One *CBoss_One::Create()
{
	// メモリを確保
	CBoss_One*pBoss_One = new CBoss_One(OBJTYPE_BOSSONE);
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

	// 読み込んだ情報の代入
	SetBoss_OneData();
}

// =====================================================================================================================================================================
//ボスの読み込んだ情報の設定
// =====================================================================================================================================================================
void CBoss_One::SetBoss_OneData()
{
	// 体力の設定
	m_nLife = m_BossOneData.nLife;
	// 当たり判定の設定
	for (int nCnt = 0; nCnt < POSTURETYPE_MAX; nCnt++)
	{
		m_CollisionSize[nCnt] = m_BossOneData.CollisionSize[nCnt];
	}

	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		// ガンの発射口オフセットの設定
		m_GunShotOfsetPos[nCnt] = m_BossOneData.GunShotOfsetPos[nCnt];
	}
}

// =====================================================================================================================================================================
// ボスのデフォルトモーション
// =====================================================================================================================================================================
bool CBoss_One::Motion(void)
{
	return false;
}

bool CBoss_One::DefaultMotion(void){return false;}

// =====================================================================================================================================================================
//ダメージを受けた時のリアクション
// =====================================================================================================================================================================
void CBoss_One::DamageReaction()
{
	SetState(CCharacter::CHARACTER_STATE_DAMAGE_RED);

	//CManager::GetSound()->Play(CSound::LABEL_SE_HIT);
}
// =====================================================================================================================================================================
//死んだ時のリアクション
// =====================================================================================================================================================================
void CBoss_One::DeathReaction()
{
	//死亡フラグをたてる
	this->SetDieFlag(true);

	CCharacter::DeathReaction();
}

// =====================================================================================================================================================================
//ステートが変更した瞬間の処理
// =====================================================================================================================================================================
void CBoss_One::StateChangeReaction()
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
		SetStateCount(60);
		break;
	}
}

//=====================================================================================================================================================================
// 敵の行動
//=====================================================================================================================================================================
void CBoss_One::Behavior()
{

}

// =====================================================================================================================================================================
// ガンのオフセット座標の更新
// =====================================================================================================================================================================
void CBoss_One::SetGunOffsetPos(D3DXVECTOR3 pos)
{
	m_Gun_OffsetPos = D3DXVECTOR3(
		GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition().x,
		GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition().y,
		GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetPosition().z);
}

// =====================================================================================================================================================================
// ガンの座標の更新
// =====================================================================================================================================================================
void CBoss_One::SetGunPos()
{
	m_Gun_Pos = m_Gun_OffsetPos + GetPosition();
}

// =====================================================================================================================================================================
// ガンの移動の更新
// =====================================================================================================================================================================
void CBoss_One::MoveGun(D3DXVECTOR3	&PartsPos , D3DXVECTOR3 move)
{
	PartsPos.x += move.x,
	PartsPos.y += move.y,
	PartsPos.z += move.z;
}

// =====================================================================================================================================================================
// クールタイムの減少
// =====================================================================================================================================================================
void CBoss_One::Cooltime_Decrease()
{
	// クールタイムの減少
	m_nCoolTime--;

	// クールタイムが0以下になった時
	if (m_nCoolTime <= 0)
	{
		// 状態を攻撃に変える
		SetBossState(BOSS_ONE_STATE_ATTACK);
	}
}

// =====================================================================================================================================================================
// 焼夷弾
// =====================================================================================================================================================================
void CBoss_One::ShotIncendiary()
{
	// 50フレームごとに弾を撃つ
	if (m_nShotIntervalTime <= 0)
	{
		// 焼夷弾を撃つ
		m_pGun[WEAPONTYPE_INCENDIARY]->Shot();
		// インターバルの時間を設定
		SetShotIntervalTime(50);
		// 弾を撃った回数を加算
		m_nShotCount_Incendiary++;
	}

	// インターバルの時間を減少
	m_nShotIntervalTime--;

	// 弾を3回撃った時
	if (m_nShotCount_Incendiary >= 3)
	{
		// クールタイムの設定
		SetCoolTime(120);
		// 弾を撃った回数をリセット
		m_nShotCount_Incendiary = 0;
		// ボスの状態を変更
		m_BossOneState = BOSS_ONE_STATE_STAY;
	}
}

// =====================================================================================================================================================================
// バルカン
// =====================================================================================================================================================================
void CBoss_One::ShotBalkan()
{
	// 60フレームごとに弾を撃つ
	if (m_nShotIntervalTime <= 0)
	{
		// バルカンを撃つ
		m_pGun[WEAPONTYPE_BALKAN]->Shot();
		// インターバルの時間を設定
		SetShotIntervalTime(60);
	}

	// インターバルの時間を減少
	m_nShotIntervalTime--;

	// 弾を2回撃った時
	if (m_nShotCount_Incendiary >= 2)
	{
		// クールタイムの設定
		SetCoolTime(120);
		// 弾を撃った回数をリセット
		m_nShotCount_Incendiary = 0;
		// ボスの状態を変更
		m_BossOneState = BOSS_ONE_STATE_STAY;
	}
}

// =====================================================================================================================================================================
// フレイム火炎放射器
// =====================================================================================================================================================================
void CBoss_One::ShotFlameRadiation()
{
	// 7回_数フレーム空けて動かない爆発を生成する
	// 16初_弾を撃つ 数フレームごと 弾一発につきエフェクト一つ

	//// 30フレームごとに弾を撃つ
	//if (m_nShotIntervalTime <= 0)
	//{
	//	// 火炎放射を撃つ
	//	m_pGun[WEAPONTYPE_FLAMETHROWER]->Shot();
	//	// インターバルの時間を設定
	//	SetShotIntervalTime(60);
	//	// 弾を撃った回数を加算
	//	m_nShotCount_Incendiary++;
	//}

	//// インターバルの時間を減少
	//m_nShotIntervalTime--;

	//// 弾を2回撃った時
	//if (m_nShotCount_Incendiary >= 2)
	//{
	//	// クールタイムの設定
	//	SetCoolTime(120);
	//	// 弾を撃った回数をリセット
	//	m_nShotCount_Incendiary = 0;
	//	// ボスの状態を変更
	//	m_BossOneState = BOSS_ONE_STATE_STAY;
	//}
}

// =====================================================================================================================================================================
// 攻撃方法をランダムに決める
// =====================================================================================================================================================================
void CBoss_One::RandomAttack()
{
	// 攻撃方法を決める
	m_AttckType = (BOSS_ONE_ATTACKTYPE)get_rand_range(ATTACKTYPE_BALKAN, ATTACKTYPE_INCENDIARY);
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
// ボスのステートごとの処理
// =====================================================================================================================================================================
void CBoss_One::BossOneStateManager()
{
	switch (m_BossOneState)
	{
	case CBoss_One::BOSS_ONE_STATE_NONE:
		break;
	case CBoss_One::BOSS_ONE_STATE_STAY:
		Cooltime_Decrease();
		// 攻撃方法をランダムに決める
		RandomAttack();
		break;
	case CBoss_One::BOSS_ONE_STATE_ATTACK:
		// ボスの攻撃管理
		BossOneAttackManager();
		break;
	case CBoss_One::BOSS_ONE_STATE_SHIFT_POSTURE:
		break;
	case CBoss_One::BOSS_ONE_STATE_MAX:
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
// ボスの攻撃管理
// =====================================================================================================================================================================
void CBoss_One::BossOneAttackManager()
{
	// ステート別攻撃方法
	switch (m_AttckType)
	{
	case CBoss_One::ATTACKTYPE_BALKAN:
		m_pGun[WEAPONTYPE_BALKAN]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x * -1.0f));
		ShotBalkan();
		break;
	case CBoss_One::ATTACKTYPE_FLAMERADIATION:
		ShotFlameRadiation();
		break;
	case CBoss_One::ATTACKTYPE_INCENDIARY:
		ShotIncendiary();
		break;
	default:
		break;
	}
}
