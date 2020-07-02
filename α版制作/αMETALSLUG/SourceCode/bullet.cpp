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
// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
BULLET_PARAM	CBullet::m_BulletParam[CGun::GUNTYPE_MAX] = {};

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
	{ "data/Load/Gun/Grenade.txt" },				// グレネード
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define BULLET_LIFE				(100)			// 弾の体力

// 弾のダメージ
#define BULLET_DAMAGE_ENEMY		(10)			// エネミーへのダメージ
#define BULLET_DAMAGE_OBSTACLE	(10)			// 障害物へのダメージ
#define BULLET_DAMAGE_PLAYER	(10)			// プレイヤーへのダメージ

// 貫通させるかのフラグ
#define BULLET_PENETRATION		(false)			// 弾の判定が貫通するかどうか

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
#ifdef _DEBUG

	// 当たり判定の削除
	if (m_pCollision != nullptr)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}

#endif // _DEBUG

}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CBullet::Init()
{
	// 変数初期化
	m_move			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 移動値
	m_pCollision	= nullptr;									// 当たり判定のポインタ
	m_nLife			= 0;				// 体力

	// 初期化
	CModel::Init();

	// 当たり判定生成
	m_pCollision = CCollision::Create();
	m_pCollision->SetPos(&GetPosition());
	m_pCollision->SetSize2D(D3DXVECTOR3(40.0f, 40.0f, 0.0f));
	m_pCollision->SetMove(&m_move);
	m_pCollision->SetType(CCollision::COLLISION_PLAYERBULLET);
	m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_NORMAL);

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
	// 位置の取得
	D3DXVECTOR3 pos		= CModel::GetPosition();

	// 位置更新
	pos += m_move;

	// 体力減少												配列の[ 0 ]のところには銃の種類が入る
	m_nLife--;

	// 体力が0になったら									配列の[ 0 ]のところには銃の種類が入る
	if (m_nLife <= 0)
	{
		Rerease();
	}

	// 位置の設定
	CModel::SetPosition(pos);

	// ------------- 当たり判定 ------------- //
	if (m_pCollision != nullptr)
	{
		// 判定の座標を更新
		m_pCollision->SetPos(&GetPosition());

		// プレイヤーの弾だった時
		if (m_type == TYPE_PLAYER)
		{
			// プレイヤーの弾の判定
			if (m_pCollision->ForPlayerBulletCollision(BULLET_DAMAGE_ENEMY, BULLET_DAMAGE_OBSTACLE, BULLET_PENETRATION))
			{
				// 弾の削除
				Rerease();
			}
		}

		// エネミーの弾だった時
		else if (m_type == TYPE_ENEMY)
		{
			// エネミーの弾の判定
			if (m_pCollision->ForEnemyCollision(BULLET_DAMAGE_PLAYER, BULLET_PENETRATION))
			{
				// 弾の削除
				Rerease();
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
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置

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
								sscanf(cReadText, "%s %s %f", &cDie, &cDie, &m_BulletParam[nCnt].fPower);			// 比較用テキストにPOWERを代入
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
			MessageBox(NULL, "弾のパラメーター読み込み失敗", "警告", MB_ICONWARNING);
		}
	}
}

// =====================================================================================================================================================================
//
// 弾のパラメーター設定
//
// =====================================================================================================================================================================
void CBullet::SetBulletParam(CGun::GUN_TYPE type)
{
	m_nLife = m_BulletParam[type].nLife;	// 体力
}