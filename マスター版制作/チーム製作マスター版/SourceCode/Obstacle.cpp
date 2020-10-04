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
#include "Normal_Iten.h"
#include "Anim_Item.h"
#include "map.h"
#include "sound.h"

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
	{ "data/Load/Obstacle/Balloon.txt" },			// 風船
	{ "data/Load/Obstacle/PresentBox01.txt" },		// プレゼント
	{ "data/Load/Obstacle/PresentBox00.txt" },		// プレゼント レア
	{ "data/Load/Obstacle/Bridge.txt" },			// 橋
	{ "data/Load/Obstacle/Bell.txt" },				// 鐘
	{ "data/Load/Obstacle/Cage.txt" },				// 檻
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
	m_pBalloon = nullptr;
	m_BalloonMove = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
	m_fGravity = -5.0f;
	m_bGravity = false;
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

	CMap *pMap = CManager::GetBaseMode()->GetMap();

	D3DXVECTOR3 ofsetpos = D3DXVECTOR3(GetPosition().x, GetPosition().y + 70.0f, GetPosition().z);
	if (this->m_ObstacleType == TYPE_PRESENTBOX)
	{
		m_pBalloon = pMap->PresentCreate(ofsetpos, TYPE_BALLOON);
		GetCollision()->SetCanCollision(false);
	}
	else if (this->m_ObstacleType == TYPE_PRESENTBOX_RARE)
	{
		m_pBalloon = pMap->PresentCreate(ofsetpos, TYPE_BALLOON);
		GetCollision()->SetCanCollision(false);
	}

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
	D3DXVECTOR3 posold = GetPosition();
	if (m_pBalloon && m_pBalloon->GetObstacleType() == TYPE_BALLOON && m_pBalloon->m_nLife <= 0)
	{
		m_bBreakBalloon = true;
	}

	if (GetCollision() != nullptr)
	{
		//座標の更新
		GetCollision()->SetPos(&GetPosition());

		if (this->m_ObstacleType == TYPE_PRESENTBOX ||
			this->m_ObstacleType == TYPE_PRESENTBOX_RARE)
		{
			if (m_bBreakBalloon)
			{
				// マップのポインタ取得
				CMap *pMap = CManager::GetBaseMode()->GetMap();

				// マップモデルが存在した時して当たり判定が存在する時
				if (pMap && GetCollision())
				{
					// 障害物の判定とレイの判定
					if (GetCollision()->RayBlockCollision(pMap, (this->GetMatrix())))
					{
						GetPosition().y -= 15.0f;
					}
					else
					{
					}

					// 障害物の判定とレイの判定
					//if (GetCollision()->RayCollision(pMap, posold, GetPosition()))
					//{
					//	//GetPosition().y += m_fGravity;
					//}
					//else
					//{
					//	//GetPosition().y += m_fGravity;
					//}
				}
			}
		}
	}

	// 風船が割れたら風船の持ち主の当たり判定を可能にする
	if (this->m_ObstacleType == TYPE_PRESENTBOX ||
		this->m_ObstacleType == TYPE_PRESENTBOX_RARE)
	{
		if (m_pBalloon && m_pBalloon->GetDieFlag())
		{
			GetCollision()->SetCanCollision(true);
			m_pBalloon = nullptr;
		}
		else if (m_pBalloon && !m_pBalloon->GetDieFlag())
		{
			m_pBalloon->GetPosition() += m_BalloonMove;
			GetPosition().x = m_pBalloon->GetPosition().x;
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
// 障害物の生成
//
// =====================================================================================================================================================================
CObstacle * CObstacle::Create(OBSTACLE_TYPE Type)
{
	// 変数
	CObstacle *pObstacle;

	// メモリの確保
	pObstacle = new CObstacle(OBJTYPE_OBSTACLE);

	// タグ設定
	pObstacle->SetTag(TAG::OBSTACLE);

	pObstacle->SetObstacleType(Type);

	// 初期化
	pObstacle->Init();

	// モデルタイプの設定
	pObstacle->SetType(OBSTACLE_MODEL);

	return pObstacle;
}

// =====================================================================================================================================================================
//
// 障害物の生成
//
// =====================================================================================================================================================================
CObstacle * CObstacle::Create_Editor()
{
	// 変数
	CObstacle *pObstacle;

	// メモリの確保
	pObstacle = new CObstacle(OBJTYPE_OBSTACLE);

	// タグ設定
	pObstacle->SetTag(TAG::OBSTACLE);

	// 初期化
	pObstacle->Init();

	// モデルタイプの設定
	pObstacle->SetType(OBSTACLE_MODEL);

	return pObstacle;
}

// =====================================================================================================================================================================
//
// プレゼントの生成
//
// =====================================================================================================================================================================
CObstacle * CObstacle::Create_Present(D3DXVECTOR3 pos, CObstacle::OBSTACLE_TYPE Type)
{
	// 変数
	CObstacle *pObstacle;

	// メモリの確保
	pObstacle = new CObstacle(OBJTYPE_OBSTACLE);

	// タグ設定
	pObstacle->SetTag(TAG::OBSTACLE);

	pObstacle->SetObstacleType(Type);

	pObstacle->SetPosition(pos);

	// 初期化
	pObstacle->Init();

	// モデルタイプの設定
	pObstacle->SetType(OBSTACLE_MODEL);

	return pObstacle;
}

// =====================================================================================================================================================================
//
// パラメーターの読み込み
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
							// breakが来たら
							else if (strcmp(cHeadText, "BBREAK") == 0)
							{
								int nBreak;
								sscanf(cReadText, "%s %s %d", &cDie, &cDie, &nBreak);
								m_ObstacleParam[nCnt].bBreak = nBreak ? false : true;
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
void CObstacle::Hit(TAG tag,int nDamage)
{
	switch (m_ObstacleType)
	{
	case CObstacle::TYPE_BOX:
	case CObstacle::TYPE_BARREL:
	case CObstacle::TYPE_BARRELBOMB:
	case CObstacle::TYPE_TREE:
	case CObstacle::TYPE_CHEST:
	case CObstacle::TYPE_SANDBAGS:
	case CObstacle::TYPE_CAR:
	case CObstacle::TYPE_BALLOON:
	case CObstacle::TYPE_PRESENTBOX:
	case CObstacle::TYPE_PRESENTBOX_RARE:
	case CObstacle::TYPE_BOSSMAP_CAGE:
		// 体力を減算する
		this->AddDamage(nDamage);
		// 削除する
		this->CheckDie(tag);
		break;

	case CObstacle::TYPE_BOSSMAP_BELL:
		CManager::GetSound()->Play(CSound::LABEL_SE_HIT_BELL);
		// 体力を減算する
		this->AddDamage(nDamage);
		// 削除する
		this->CheckDie(tag);
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
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_BARREL:
		CAnimationItem::DropItem_Multiple(GetPosition(), CItem::LIST_ANI_NORMAL, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_BARRELBOMB:
		// 爆発する
		break;
	case CObstacle::TYPE_TREE:
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_FREEFALL);
		break;
	case CObstacle::TYPE_CHEST:
		CNormalItem::DropItem(GetPosition(), true, CItem::ITEMTYPE_GOLDCOIN);
		break;
	case CObstacle::TYPE_SANDBAGS:
		break;
	case CObstacle::TYPE_CAR:
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_COIN, CItem::BEHAVIOR_BURSTS);
		break;

	case CObstacle::TYPE_BALLOON:
		break;
	case CObstacle::TYPE_PRESENTBOX:
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_FOOD, CItem::BEHAVIOR_BURSTS);
		break;
	case CObstacle::TYPE_PRESENTBOX_RARE:
		CNormalItem::DropItem_Multiple(GetPosition(), CItem::LIST_RARE, CItem::BEHAVIOR_BURSTS);
		break;

	case CObstacle::TYPE_BOSSMAP_BELL:
		CAnimationItem::DropItem_Multiple(GetPosition(), CItem::LIST_ANI_RARE, CItem::BEHAVIOR_FULLBURSTS);
		break;
	case CObstacle::TYPE_BOSSMAP_CAGE:
		CAnimationItem::DropItem(GetPosition(), true, CItem::ANIM_ITEMTYPE_DANCEMONKEY);
		break;
	default:
		break;
	}
}

// =====================================================================================================================================================================
// 障害物を破壊するか決める処理
// =====================================================================================================================================================================
void CObstacle::CheckDie(TAG tag)
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

		//判定不可にする
		GetCollision()->SetCanCollision(false);

		switch (m_ObstacleType)
		{
		case CObstacle::TYPE_BOX:
		case CObstacle::TYPE_BARREL:
		case CObstacle::TYPE_TREE:
		case CObstacle::TYPE_CHEST:
		case CObstacle::TYPE_SANDBAGS:
		case CObstacle::TYPE_CAR:
		case CObstacle::TYPE_BALLOON:
		case CObstacle::TYPE_PRESENTBOX:
		case CObstacle::TYPE_PRESENTBOX_RARE:
		case CObstacle::TYPE_BOSSMAP_BELL:
		case CObstacle::TYPE_BOSSMAP_CAGE:

			//爆発発生
			CParticle::CreateFromText(GetPosition(), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_OBJECTBREAK);
			break;

			//爆発箱
		case CObstacle::TYPE_BARRELBOMB:
			//デカい爆発発生
			CParticle::CreateFromText(GetPosition() - D3DXVECTOR3(0.0f,GetSize().y * 0.5f,0.0f), ZeroVector3, CParticleParam::EFFECT_EXPLOSION_DANGERBOX,tag);
			break;

		}
	}
}
//====================================================================
// ダメージを受けた時の処理
//====================================================================
void CObstacle::AddDamage(int nDamage)
{
	this->SetLife(this->m_nLife -= nDamage);
}

//====================================================================
// パラメーターの設定
//====================================================================
void CObstacle::SetObstacleParam(CObstacle::OBSTACLE_TYPE type)
{
	m_nLife = m_ObstacleParam[type].nLife;
	SetSize(m_ObstacleParam[type].CollisionSize);
}

//====================================================================
// サイズの設定
//====================================================================
void CObstacle::SetCollisionSize(CObstacle::OBSTACLE_TYPE type)
{
	// 当たり判定の大きさを設定
	GetCollision()->SetSize(m_ObstacleParam[type].CollisionSize);
	GetCollision()->DeCollisionCreate(CCollision::COLLISIONTYPE_CHARACTER);
	// 情報の設定
	SetObstacleParam(type);

	if (type == OBSTACLE_TYPE_BRIDGE-500)
	{
		GetCollision()->SetCanCollision(false);
	}
};

