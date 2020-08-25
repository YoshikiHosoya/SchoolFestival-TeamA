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
BOSS_ONE_DATA		CBoss_One::m_BossOneData						 = {};			// データ
int					CBoss_One::m_nLife								 = 0;			// 体力
D3DXVECTOR3			CBoss_One::m_CollisionSize[POSTURETYPE_MAX]		 = {};			// 当たり判定の大きさ
D3DXVECTOR3			CBoss_One::m_GunShotOfsetPos[WEAPONTYPE_MAX]	 = {};			// ガンのオフセット

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
	m_BossOneState			 = BOSS_ONE_STATE_STAY;
	m_AttckType				 = ATTACKTYPE_NONE;
	m_ShotCount				 = 0;
	m_pCollision			 = nullptr;
	m_nCoolTime				 = 120;
	m_nShotIntervalTime		 = 0;
	m_nTrrigerCount			 = 0;
	m_bFlame				 = false;
	m_bBalkanRotFlag		 = false;
	m_fBalkanRot			 = 0.0f;
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
	// ボスの角度の設定
	SetRotDest(D3DXVECTOR3(0.0f, 1.57f, 0.0f));
	// 体力の初期値
	CCharacter::SetLife(m_nLife);
	// モーションさせない設定
	SetMotion(CCharacter::CHARACTER_MOTION_STATE_NONE);
	// 銃を傾ける
	GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_INCENDIARY))->GetRot().x += 0.6f;
	//CalcRotationBalkan(-1.57f, GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x);
	GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x = 0.0f;
	GetCharacterModelPartsList((CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetRot().x -= 1.57f;
	// 武器用の当たり判定の生成
	m_pCollision = CCollision::Create();

	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		// 銃の生成
		m_pGun[nCnt] = CGun::Create();
		//マトリックス設定
		m_pGun[nCnt]->SetHandMtx(GetCharacterModelPartsList(
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
	m_pCollision->SetPos(&m_Gun_Pos[WEAPONTYPE_FLAMETHROWER]);
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
	m_pCollision->SetPos(&m_Gun_Pos[WEAPONTYPE_FLAMETHROWER]);

	// ボスの状態ごとの処理
	BossOneStateManager();

	// 当たり判定
	if (CCharacter::GetCollision() != nullptr)
	{
		// 座標の更新 pos
		CCharacter::GetCollision()->SetPos(&GetPosition());
	}

	// デバッグ用距離の計算
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
bool CBoss_One::Motion(void){return false;}
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
	// ガンの傾きを元に戻す
	//CalcRotationBalkan(-1.57f, GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x);
	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x = 0.0f;
	m_fBalkanRot = GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x;
	// 弾を撃った回数をリセット
	SetShotCount(0);
	// インターバルの時間をリセット
	SetShotIntervalTime(0);
	// トリガーのカウントのリセット
	SetTriggerCount(0);
	// クールタイムの計算
	Cooltime_Decrease();
	// 攻撃方法をランダムに決める
	RandomAttack();
}

// =====================================================================================================================================================================
// ガンのオフセット座標の更新
// =====================================================================================================================================================================
void CBoss_One::SetGunOffsetPos(D3DXVECTOR3 pos)
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_Gun_OffsetPos[nCnt] = D3DXVECTOR3(
			GetCharacterModelPartsList(static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetPosition().x,
			GetCharacterModelPartsList(static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetPosition().y,
			GetCharacterModelPartsList(static_cast<CModel::BOSSONE_PARTS_MODEL>(CModel::MODEL_BOSSONE_GUN_BALKAN + nCnt))->GetPosition().z);
	}
}

// =====================================================================================================================================================================
// ガンのオフセット座標の取得
// =====================================================================================================================================================================
D3DXVECTOR3 CBoss_One::GetGunOffsetPos(BOSS_ONE_WEAPONTYPE type)
{
	return m_Gun_OffsetPos[type];
}

// =====================================================================================================================================================================
// ガンの座標の更新
// =====================================================================================================================================================================
void CBoss_One::SetGunPos()
{
	for (int nCnt = 0; nCnt < WEAPONTYPE_MAX; nCnt++)
	{
		m_Gun_Pos[nCnt] = m_Gun_OffsetPos[nCnt] + GetPosition();
	}
}

// =====================================================================================================================================================================
// ガンの移動の更新
// =====================================================================================================================================================================
void CBoss_One::MoveGun(D3DXVECTOR3	&PartsPos , D3DXVECTOR3 move)
{
	PartsPos += move;
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
// 回転の計算
// =====================================================================================================================================================================
void CBoss_One::CalcRotationBalkan(const float fTarget, float fCurrent)
{
	float fcurrent = fCurrent;
	//目標点と現在の差分（回転）
	float diffRot = fTarget - fcurrent;

	//3.14の超過分の初期化（回転）
	CHossoLibrary::CalcRotation(fcurrent);
	CHossoLibrary::CalcRotation(diffRot);

	//求めた差分だけ追従する計算
	GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x += diffRot * 0.2f;
}

// =====================================================================================================================================================================
// ベクトルの長さを計算する
// =====================================================================================================================================================================
float CBoss_One::get_vector_length(D3DXVECTOR3 vectol)
{
	return powf((vectol.x * vectol.x) + (vectol.y * vectol.y) + (vectol.z * vectol.z), 0.5);
}

// =====================================================================================================================================================================
// ベクトル内積
// =====================================================================================================================================================================
float CBoss_One::dot_product(D3DXVECTOR3 vl, D3DXVECTOR3 vr)
{
	return vl.x * vr.x + vl.y * vr.y + vl.z * vr.z;
}

// =====================================================================================================================================================================
// ２つのベクトルABのなす角度θを求める
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
	sita = sita * 180.0f / D3DX_PI;

	// 今の回転量と求めた回転量が同じなら0.0fを返す
	if (m_fBalkanRot == sita)
	{
		return 0.0f;
	}
	// 違うなら求めた角度と今の回転量を計算し回転量を求める
	else
	{
		return (sita - m_fBalkanRot);
	}

	// 角度を返す
	return sita;
}

// =====================================================================================================================================================================
// 焼夷弾
// =====================================================================================================================================================================
void CBoss_One::ShotIncendiary()
{
	// 弾を3回撃った時
	if (m_nShotCount >= 3)
	{
		// クールタイムの設定
		SetCoolTime(120);
		// ボスの状態を変更
		m_BossOneState = BOSS_ONE_STATE_STAY;
	}
	else
	{
		// 50フレームごとに弾を撃つ
		if (m_nShotIntervalTime <= 0)
		{
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
// バルカン
// =====================================================================================================================================================================
void CBoss_One::ShotBalkan()
{
	// 弾を2回撃った時
	if (m_nTrrigerCount >= 2)
	{
		// クールタイムの設定
		SetCoolTime(120);
		// ガンの傾きを元に戻す
		//CalcRotationBalkan(-1.57f, GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x);
		// ボスの状態を変更
		m_BossOneState = BOSS_ONE_STATE_STAY;
	}
	else
	{
		if (!m_bBalkanRotFlag)
		{
			// ガンの向きをプレイヤーの方へ向ける
			//SetRotBalkan();
			// プレイヤーのポインタ取得
			CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
			// 座標が足元なので座標を上に上げる
			D3DXVECTOR3 PlayerPos = D3DXVECTOR3(pPlayer->GetPosition().x, pPlayer->GetPosition().y + 40, pPlayer->GetPosition().z);
			// プレイヤーの座標とバルカンの座標を結ぶベクトルを求める
			D3DXVECTOR3 vectol = PlayerPos - m_Gun_Pos[WEAPONTYPE_BALKAN];
			D3DXVECTOR3 vec = D3DXVECTOR3(vectol.x, m_Gun_Pos[WEAPONTYPE_BALKAN].y, 0.0f);

			// 回転を反映
			GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x += AngleOf2Vector(vectol, vec);
			// 回転量の更新
			SetBalkanRot(GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x);

			// 弾の向きの設定
			m_pGun[WEAPONTYPE_BALKAN]->SetShotRot(
				D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x * -1.0f));

			m_bBalkanRotFlag = true;
		}

		// 30フレームごとに1トリガー撃つ
		if (m_nShotIntervalTime <= 0)
		{
			if (m_bBalkanRotFlag)
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
					m_nTrrigerCount++;

					m_bBalkanRotFlag = false;
				}
				// インターバルの設定
				else if (m_nShotCount >= 0)
				{
					// インターバルの時間を設定
					SetShotIntervalTime(10);
				}
			}
		}

		// インターバルの時間を減少
		m_nShotIntervalTime--;
	}
}

// =====================================================================================================================================================================
// 焼夷弾の最初の爆発
// =====================================================================================================================================================================
void CBoss_One::ShotWarning()
{
	m_pGun[WEAPONTYPE_FLAMETHROWER]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetRot().x * -1.0f));

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
// フレイム火炎放射
// =====================================================================================================================================================================
void CBoss_One::ShotFlameRadiation()
{
	m_pGun[WEAPONTYPE_FLAMETHROWER]->SetShotRot(
		D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_FLAMETHROWER))->GetRot().x * -1.0f));

	// 弾を7回撃った時
	if (m_nShotCount >= (16 + 1))
	{
		// クールタイムの設定
		SetCoolTime(120);
		// 弾を撃った回数をリセット
		m_nShotCount = 0;
		//
		m_bFlame = false;
		// ボスの状態を変更
		m_BossOneState = BOSS_ONE_STATE_STAY;
	}
	else
	{
		// 50フレームごとに弾を撃つ
		if (m_nShotIntervalTime <= 0)
		{
			// 焼夷弾を撃つ
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
// 火炎放射の攻撃管理
// =====================================================================================================================================================================
void CBoss_One::ShotFlameManager()
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

// =====================================================================================================================================================================
// 攻撃方法をランダムに決める
// =====================================================================================================================================================================
void CBoss_One::RandomAttack()
{
	// 攻撃方法を決める
	//m_AttckType = (BOSS_ONE_ATTACKTYPE)get_rand_range(ATTACKTYPE_BALKAN, ATTACKTYPE_INCENDIARY);
	m_AttckType = ATTACKTYPE_BALKAN;

	// 攻撃パターンの保存
	m_AttckTypeOld = m_AttckType;
}

// =====================================================================================================================================================================
// バルカンの回転
// =====================================================================================================================================================================
void CBoss_One::SetRotBalkan()
{
	// プレイヤーのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	// 座標が足元なので座標を上に上げる
	D3DXVECTOR3 PlayerPos = D3DXVECTOR3(pPlayer->GetPosition().x, pPlayer->GetPosition().y + 50, pPlayer->GetPosition().z);
	// プレイヤーの座標とバルカンの座標を結ぶベクトルを求める
	D3DXVECTOR3 vectol = PlayerPos - m_Gun_Pos[WEAPONTYPE_BALKAN];
	// 正規化
	D3DXVec3Normalize(&vectol, &vectol);
	// 回転の計算
	CalcRotationBalkan(vectol.x, GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN)->GetRot().x);
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
		// 次の行動を選択
		Behavior();
		break;
	case CBoss_One::BOSS_ONE_STATE_ATTACK:
		// ボスの攻撃管理
		BossOneAttackManager();
		break;
	case CBoss_One::BOSS_ONE_STATE_SHIFT_POSTURE:
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
		// バルカンを撃つ
		ShotBalkan();
		break;
	case CBoss_One::ATTACKTYPE_FLAMERADIATION:
		// 火炎放射を撃つ
		ShotFlameManager();
		break;
	case CBoss_One::ATTACKTYPE_INCENDIARY:
		// 焼夷弾を撃つ
		ShotIncendiary();
		break;
	default:
		break;
	}
}
