// =====================================================================================================================================================================
//
// バレットの処理 [bullet.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "bullet.h"			// インクルードファイル
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "gun.h"
#include "collision.h"
#include "Player.h"
#include "Enemy.h"
#include "map.h"
#include "Obstacle.h"
#include "prisoner.h"
#include "particle.h"
#include "sound.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CBullet::BULLET_PARAM	CBullet::m_BulletParam[CGun::GUNTYPE_MAX] = {};

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CBullet::m_BulletFileName[CGun::GUNTYPE_MAX] =
{
	{ "data/Load/Gun/HandGun.txt" },				// ハンドガン
	{ "data/Load/Gun/HeavyMachineGun.txt" },		// ヘビーマシンガン
	{ "data/Load/Gun/ShotGun.txt" },				// ショットガン
	{ "data/Load/Gun/LaserGun.txt" },				// レーザーガン
	{ "data/Load/Gun/RocketLauncher.txt" },			// ロケットランチャー
	{ "data/Load/Gun/FlameShot.txt" },				// フレイムショット
	{ "data/Load/Gun/TankGun.txt" },				// 戦車の銃
	{ "data/Load/Gun/PlaneGun.txt" },				// 戦闘機の銃
	{ "data/Load/Gun/HeliGun.txt" },				// ヘリの銃
	{ "data/Load/Gun/Balkan.txt" },					// バルカン
	{ "data/Load/Gun/Flamethrower.txt" },			// 火炎放射器
	{ "data/Load/Gun/Incendiary.txt" },				// 焼夷弾
	{ "data/Load/Gun/HandGrenade.txt" },			// 手投げグレネード
	{ "data/Load/Gun/TankGrenade.txt" },			// 戦車のグレネード
	{ "data/Load/Gun/TrackingGun.txt" },			// 追従銃
	{ "data/Load/Gun/DiffusionGun.txt" },			// 拡散銃
	{ "data/Load/Gun/BossLazerGun.txt" },			// ボスのレーザー
	{ "data/Load/Gun/HandGun_Enemy.txt" },			// 敵のハンドガン
	{ "data/Load/Gun/Missile.txt" },				// ミサイル
	{ "data/Load/Gun/FlameBullet.txt" },			// フレイムバレット
	{ "data/Load/Gun/DropBomb.txt" },				// ドロップボム
	{ "data/Load/Gun/DroneBeam.txt" },				// ドロップボム
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CBullet::CBullet(OBJ_TYPE type) :CModel(type)
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CBullet::~CBullet()
{
}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CBullet::Init()
{
	// 変数初期化
	m_move			= ZeroVector3;		// 移動値
	m_nLife			= 0;				// 体力

	// 初期化
	CModel::Init();
	return S_OK;
}

// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CBullet::Uninit(void)
{
	CModel::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CBullet::Update(void)
{
	// 体力が0になったら
	if (m_nLife-- <= 0)
	{
		//弾を消す
		Rerease();
		return;
	}

	// 位置の取得
	D3DXVECTOR3 &rPos		= CModel::GetPosition();
	// 位置更新
	rPos += m_move;

	//スクリーンの中にあるかどうか
	if (!CManager::GetRenderer()->CheckScreenRange(rPos))
	{
		//弾を消す
		Rerease();
		return;
	}

	// ------------- 当たり判定 ------------- //
	if (GetCollision() != nullptr)
	{
		// 判定の座標を更新
		GetCollision()->SetPos(&GetPosition());

		// ゲームオブジェクト( タグ )の設定
		GetCollision()->SetGameObject(this);

		// マップのポインタ取得
		CMap *pMap;
		pMap = CManager::GetBaseMode()->GetMap();

		if (pMap != nullptr)
		{
			// レイの判定
			if (GetCollision()->RayCollision(pMap, rPos - m_move, rPos))
			{

				DeleteBullet();
				return;
			}
		}

		// プレイヤーの弾だった時
		if (GetTag() == TAG::PLAYER_1 || GetTag() == TAG::PLAYER_2)
		{
			// プレイヤーの弾の判定
			if (GetCollision()->ForPlayerBulletCollision(m_BulletParam[m_GunType].nPower, m_BulletParam[m_GunType].nPower, false))
			{
				//音再生
				//敵や捕虜に当たった時に音出したい
				BulletHitSound();

				// 弾の削除
				DeleteBullet();
				return;
			}
		}

		// エネミーの弾だった時
		else if (GetTag() == TAG::ENEMY)
		{
			// エネミーの弾の判定
			if (GetCollision()->ForEnemyCollision(m_BulletParam[m_GunType].nPower, m_BulletParam[m_GunType].nPower, false))
			{
				// 弾の削除
				DeleteBullet();
				return;
			}
		}
	}

	// 更新
	CModel::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CBullet::Draw(void)
{
	// 描画
	CModel::Draw();
}

// =====================================================================================================================================================================
//
// 弾消去
//
// =====================================================================================================================================================================
void CBullet::DeleteBullet()
{
	/*switch (m_GunType)
	{
	case CGun::GUNTYPE_HANDGUN:
		break;
	case CGun::GUNTYPE_HEAVYMACHINEGUN:
		break;
	case CGun::GUNTYPE_SHOTGUN:
		break;
	case CGun::GUNTYPE_LASERGUN:
		break;
	case CGun::GUNTYPE_ROCKETLAUNCHER:
		break;
	case CGun::GUNTYPE_FLAMESHOT:
		break;
	case CGun::GUNTYPE_TANKGUN:
		break;
	case CGun::GUNTYPE_PLANEGUN:
		break;
	case CGun::GUNTYPE_HELIGUN:
		break;
	case CGun::GUNTYPE_BALKAN:
		break;
	case CGun::GUNTYPE_FLAMETHROWER:
		break;
	case CGun::GUNTYPE_INCENDIARY:
		break;
	case CGun::GUNTYPE_HANDGRENADE:
		break;
	case CGun::GUNTYPE_TANKGRENADE:
		break;
	case CGun::GUNTYPE_TRACKINGGUN:
		break;
	case CGun::GUNTYPE_DIFFUSIONGUN:
		break;
	case CGun::GUNTYPE_BOSSLASERGUN:
		break;
	case CGun::GUNTYPE_HANDGUN_ENEMY:
		break;
	case CGun::GUNTYPE_MISSILE:
		break;
	case CGun::GUNTYPE_FLAMEBULLET:
		break;
	case CGun::GUNTYPE_DROPBOMB:
		break;
	}*/

	// 今だけ↓

	// 焼夷弾以外の弾が衝突し消えるときのエフェクト
	if (m_GunType != CGun::GUNTYPE_INCENDIARY)
	{
		CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_DELETEBULLET);
	}
	// 焼夷弾が着弾したときのエフェクト ドラゴンノスケの焼夷弾
	else
	{
		//弾が当たったSE
		CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION_04);
		CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_NO_COLLISION_EXPLOSION_INCENDIARY);
	}

	// 弾の削除
	Rerease();
}

// =====================================================================================================================================================================
//
// 弾の反応
//
// =====================================================================================================================================================================
void CBullet::BulletReaction(D3DXVECTOR3 rot)
{
}


// =====================================================================================================================================================================
//
// 弾のロード
//
// =====================================================================================================================================================================
void CBullet::BulletLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	D3DXVECTOR3 pos = ZeroVector3;	// 位置

	for (int nCnt = 0; nCnt < CGun::GUNTYPE_MAX; nCnt++)
	{
		// ファイルを開く
		pFile = fopen(m_BulletFileName[nCnt], "r");

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

					// BULLETSETが来たら
					if (strcmp(cHeadText, "BULLETSET") == 0)
					{
						// END_BULLETSETが来るまでループ
						while (strcmp(cHeadText, "END_BULLETSET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
							sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

							// SPEEDが来たら
							if (strcmp(cHeadText, "SPEED") == 0)
							{
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_BulletParam[nCnt].fBulletSpeed);		// 比較用テキストにSPEEDを代入
							}
							// LIFEが来たら
							else if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nLife);			// 比較用テキストにLIFEを代入
							}
							// POWERが来たら
							else if (strcmp(cHeadText, "POWER") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nPower);			// 比較用テキストにPOWERを代入
							}
							// AMMOが来たら
							else if (strcmp(cHeadText, "AMMO") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nAmmo);			// 比較用テキストにAMMOを代入
							}
							// TRIGGERが来たら
							else if (strcmp(cHeadText, "TRIGGER") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nTrigger);			// 比較用テキストにTRIGGERを代入
							}
							// INTERVALが来たら
							else if (strcmp(cHeadText, "INTERVAL") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_BulletParam[nCnt].nInterval);		// 比較用テキストにINTERVALを代入
							}
							// COLLISIONSIZEが来たら
							else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_BulletParam[nCnt].CollisionSize.x
																				, &m_BulletParam[nCnt].CollisionSize.y
																				, &m_BulletParam[nCnt].CollisionSize.z);		// 比較用テキストにCOLLISIONSIZEを代入
							}
							else if (strcmp(cHeadText, "END_BULLETSET") == 0)
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
			// 読み込み失敗時の警告表示
			MessageBox(NULL, "弾のパラメーター読み込み失敗" ,m_BulletFileName[nCnt], MB_ICONWARNING);
		}
	}
}

// =====================================================================================================================================================================
//
// 弾の発射方向計算
//
// =====================================================================================================================================================================
void CBullet::CalcBulletMove(D3DXVECTOR3 ShotRot, int Guntype)
{
	m_move = D3DXVECTOR3(-sinf(ShotRot.z) * m_BulletParam[Guntype].fBulletSpeed, cosf(ShotRot.z) * m_BulletParam[Guntype].fBulletSpeed, 0.0f);
}

// =====================================================================================================================================================================
//
// 弾の発射方向計算
//
// =====================================================================================================================================================================
void CBullet::CalcIncendiaryMove(D3DXVECTOR3 ShotRot, float move, float move_y)
{
	m_move = D3DXVECTOR3(-sinf(ShotRot.z) * move, cosf(ShotRot.z) * move_y, 0.0f);
}

// =====================================================================================================================================================================
//
// 弾のパラメーター設定
//
// =====================================================================================================================================================================
void CBullet::SetBulletParam(CGun::GUN_TYPE type)
{
	m_nLife = m_BulletParam[type].nLife;	// 体力

	m_GunType = type;

	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetMove(&m_move);
	GetCollision()->SetSize(m_BulletParam[type].CollisionSize);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);
}

// =====================================================================================================================================================================
//
// 弾が当たった時に音再生
//
// =====================================================================================================================================================================
void CBullet::BulletHitSound()
{
	//銃の種類によって音再生
	switch (m_GunType)
	{
	case CGun::GUNTYPE_HANDGUN:
	case CGun::GUNTYPE_HEAVYMACHINEGUN:
	case CGun::GUNTYPE_TANKGUN:
	case CGun::GUNTYPE_PLANEGUN:
	case CGun::GUNTYPE_HELIGUN:
	case CGun::GUNTYPE_BALKAN:
	case CGun::GUNTYPE_TRACKINGGUN:
	case CGun::GUNTYPE_DIFFUSIONGUN:
		//弾が当たったSE
		CManager::GetSound()->Play(CSound::LABEL_SE_BULLET_HIT);
		break;


	//case CGun::GUNTYPE_INCENDIARY:
	//	//弾が当たったSE
	//	CManager::GetSound()->Play(CSound::LABEL_SE_EXPLOSION_00);
	//	break;

	default:
		break;
	}
}


