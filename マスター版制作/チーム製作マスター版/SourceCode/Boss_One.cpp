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
	m_BossOneState = BOSS_ONE_STATE_NONE;
	m_ShotCount = 0;
	m_pCollision = nullptr;
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

	m_ShotCount++;
	if (m_ShotCount % 30 == 0)
	{
		m_pGun[WEAPONTYPE_FLAMETHROWER]->Shot();
	}
	if (m_ShotCount % 60 == 0)
	{
		// 弾を撃つ方向を設定
		m_pGun[WEAPONTYPE_BALKAN]->SetShotRot(
			D3DXVECTOR3(0.0f, 0.0f, (GetCharacterModelPartsList(CModel::MODEL_BOSSONE_GUN_BALKAN))->GetRot().x));

		m_pGun[WEAPONTYPE_BALKAN]->Shot();
	}
	if (m_ShotCount % 120 == 0)
	{
		m_pGun[WEAPONTYPE_INCENDIARY]->Shot();
	}

	// 当たり判定
	if (CCharacter::GetCollision() != nullptr)
	{
		// 座標の更新 pos
		CCharacter::GetCollision()->SetPos(&GetPosition());
	}

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
void CBoss_One::BossOneState(){}

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
