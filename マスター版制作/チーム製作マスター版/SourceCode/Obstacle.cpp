// =====================================================================================================================================================================
//
// 障害物の処理 [Obstacle.cpp]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "Obstacle.h"
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "collision.h"
#include "particle.h"
#include "ModelSet.h"
#include "Character.h"
#include "model.h"
#include "item.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
OBSTACLE_PARAM	CObstacle::m_ObstacleParam[CObstacle::TYPE_MAX] = {};

// =====================================================================================================================================================================
// テキストファイル名
// =====================================================================================================================================================================
char *CObstacle::m_ObstacleFileName[CObstacle::TYPE_MAX] =
{
	{ "data/Load/Obstacle/Box.txt" },				// 木箱
	{ "data/Load/Obstacle/Barrel.txt" },			// 樽
	{ "data/Load/Obstacle/BarrelBomb.txt" },		// 爆弾樽
	{ "data/Load/Obstacle/Tree.txt" },				// 木
	{ "data/Load/Obstacle/Chest.txt" },				// 金庫
	{ "data/Load/Obstacle/Sandbags.txt" },			// 土嚢
	{ "data/Load/Obstacle/Car.txt" },				// 車
};

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CObstacle::CObstacle(OBJ_TYPE type) :CModel(type)
{
	// 変数の初期化
	m_nLife = 0;
	// タグ設定
	CGameObject::SetTag(TAG::OBSTACLE);
}
// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CObstacle::~CObstacle()
{
}
// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CObstacle::Init()
{
	// 初期化
	CModel::Init();

	// 情報の設定
	SetObstacleParam(TYPE_BOX);

	// 当たり判定生成
	GetCollision()->SetPos(&GetPosition());
	GetCollision()->SetGameObject(this);

	return S_OK;
}
// =====================================================================================================================================================================
//
// 終了処理
//
// =====================================================================================================================================================================
void CObstacle::Uninit(void)
{
	// 終了
	CModel::Uninit();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CObstacle::Update(void)
{
	if (GetCollision() != nullptr)
	{
		//座標の更新
		GetCollision()->SetPos(&GetPosition());
	}
	// 更新
	CModel::Update();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CObstacle::Draw(void)
{
	// 描画
	CModel::Draw();
}
// =====================================================================================================================================================================
//
// デバッグ
//
// =====================================================================================================================================================================
void CObstacle::DebugInfo()
{
}

// =====================================================================================================================================================================
//
// 銃の生成
//
// =====================================================================================================================================================================
CObstacle * CObstacle::Create()
{
	// 変数
	CObstacle *pObstacle;

	// メモリの確保
	pObstacle = new CObstacle(OBJTYPE_OBSTACLE);

	// 初期化
	pObstacle->Init();

	// モデルタイプの設定
	pObstacle->SetType(OBSTACLE_MODEL);

	return pObstacle;
}

// =====================================================================================================================================================================
//
// 障害物が壊されるときの処理
//
// =====================================================================================================================================================================
void CObstacle::ObstacleLoad()
{
	// ファイルポイント
	FILE *pFile;

	char cReadText[128];			// 文字として読み取る
	char cHeadText[128];			// 比較用
	char cDie[128];					// 不要な文字
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	for (int nCnt = 0; nCnt < CObstacle::TYPE_MAX; nCnt++)
	{
		// ファイルを開く
		pFile = fopen(m_ObstacleFileName[nCnt], "r");

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

					// OBSTACLESETが来たら
					if (strcmp(cHeadText, "OBSTACLESET") == 0)
					{
						// END_OBSTACLESETが来るまでループ
						while (strcmp(cHeadText, "END_OBSTACLESET") != 0)
						{
							fgets(cReadText, sizeof(cReadText), pFile); // 一文読み込み
							sscanf(cReadText, "%s", &cHeadText);		// 比較用テキストに文字を代入

							// LIFEが来たら
							if (strcmp(cHeadText, "LIFE") == 0)
							{
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &m_ObstacleParam[nCnt].nLife);			// 比較用テキストにLIFEを代入
							}
							// COLLISIONSIZEが来たら
							else if (strcmp(cHeadText, "COLLISIONSIZE") == 0)
							{
								sscanf(cReadText, "%s %s %f %f %f", &cDie, &cDie, &m_ObstacleParam[nCnt].CollisionSize.x
									, &m_ObstacleParam[nCnt].CollisionSize.y
									, &m_ObstacleParam[nCnt].CollisionSize.z);		// 比較用テキストにCOLLISIONSIZEを代入
							}
							else if (strcmp(cHeadText, "END_OBSTACLESET") == 0)
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
			MessageBox(NULL, "障害物のパラメーター読み込み失敗", "警告", MB_ICONWARNING);
		}
	}
}

// =====================================================================================================================================================================
//
// 障害物が壊されるときの処理
//
// =====================================================================================================================================================================
void CObstacle::Hit(OBSTACLE_TYPE type,int nDamage)
{
	switch (type)
	{
	case CObstacle::TYPE_BOX:
	case CObstacle::TYPE_BARREL:
	case CObstacle::TYPE_BARRELBOMB:
	case CObstacle::TYPE_TREE:
	case CObstacle::TYPE_CHEST:
	case CObstacle::TYPE_SANDBAGS:
	case CObstacle::TYPE_CAR:

		// 体力を減算する
		this->AddDamage(nDamage);
		// 削除する
		this->CheckDie();

		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
// 種類ごとのドロップ
// =====================================================================================================================================================================
void CObstacle::DropItem()
{
	switch (m_ObstacleType)
	{
	case CObstacle::TYPE_BOX:
		CItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_BARREL:
		CItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_BARRELBOMB:
		// 爆発する
		break;
	case CObstacle::TYPE_TREE:
		CItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_FREEFALL);
		break;
	case CObstacle::TYPE_CHEST:
		CItem::DropItem(GetPosition(), true, CItem::ITEMTYPE_GOLDCOIN);
		break;
	case CObstacle::TYPE_SANDBAGS:
		break;
	case CObstacle::TYPE_CAR:
		CItem::DropItem_Multiple(GetPosition(), CItem::LIST_COIN, CItem::BEHAVIOR_BURSTS);
		break;

	default:
		break;
	}
}

// =====================================================================================================================================================================
// 障害物を破壊するか決める処理
// =====================================================================================================================================================================
void CObstacle::CheckDie()
{
	if (this->m_nLife <= 0)
	{
		if (!this->GetDieFlag())
		{
			// アイテムをドロップする
			DropItem();
		}
		// 体力が0以下なら削除する
		this->SetDieFlag(true);
		//爆発発生
		CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_OBJECTBREAK);
	}
}
//====================================================================
// ダメージを受けた時の処理
//====================================================================
void CObstacle::AddDamage(int nDamage)
{
	this->m_nLife -= nDamage;
	this->SetLife(m_nLife);
}

//====================================================================
// サイズの設定
//====================================================================
void CObstacle::SetCollisionSize(CObstacle::OBSTACLE_TYPE type)
{
	// 当たり判定の大きさを設定
	GetCollision()->SetSize(m_ObstacleParam[type].CollisionSize);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
};

