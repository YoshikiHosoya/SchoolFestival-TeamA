//======================================================================================================================
//
// Collision処理の説明[calculation.cpp]
// Author : Fujiwara Masato
//
//======================================================================================================================

//======================================================================================================================
//
// インクルードファイル
//
//======================================================================================================================
#include "Collision.h"
#ifdef _DEBUG
#include "debugcollision.h"
#include "debugproc.h"
#endif // _DEBUG
#include "manager.h"
#include "game.h"
#include "scene.h"


// 当たり判定のため
#include "Player.h"
#include "Enemy.h"
#include "map.h"
#include "Obstacle.h"
#include "prisoner.h"
#include "item.h"

//======================================================================================================================
//
// マクロ定義
//
//======================================================================================================================

//======================================================================================================================
//
// 静的変数
//
//======================================================================================================================

//======================================================================================================================
// コンストラクタ
//======================================================================================================================
CCollision::CCollision()
{
	m_objtype			= COLLISION_PLAYERBULLET;				// タイプの初期化
	m_Collisiontype		= COLLISIONTYPE_NORMAL;				// 当たり判定の種類
	m_ppos				= nullptr;							// 位置情報
	m_posOld			= nullptr;							// 前回の位置情報
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// サイズ情報
	m_pmove				= nullptr;							// 移動情報
	m_Debugcollision	= nullptr;							// デバッグ用当たり判定のポインタ
}

//======================================================================================================================
// デストラクタ
//======================================================================================================================
CCollision::~CCollision()
{
#ifdef _DEBUG

	// デバッグ用判定の削除
	if (m_Debugcollision != nullptr)
	{
		m_Debugcollision->DeleteDeCollision();
		//delete m_Debugcollision;
		m_Debugcollision = nullptr;
	}

#endif // _DEBUG

}

//======================================================================================================================
// 初期化処理
//======================================================================================================================
void CCollision::Init(void)
{
}

//======================================================================================================================
// 終了処理
//======================================================================================================================
void CCollision::Uninit(void)
{
}

//======================================================================================================================
// 更新処理
//======================================================================================================================
void CCollision::Update(void)
{
//#ifdef _DEBUG
//	if (m_Debugcollision != nullptr)
//	{
//		m_Debugcollision->SetPos(m_ppos);
//	}
//#endif // _DEBUG
}

//======================================================================================================================
// 生成処理
//======================================================================================================================
CCollision * CCollision::Create(void)
{
	// 変数宣言
	CCollision * pCollision;	// 当たり判定
	// メモリ確保
	pCollision = new CCollision;
	// 初期化
	pCollision->Init();
	// ポインタを返す
	return pCollision;
}

//======================================================================================================================
// デバッグ用当たり判定生成処理
//======================================================================================================================
void CCollision::DeCollisionCreate(COLLISIONTYPE collisiontype)
{
#ifdef _DEBUG
	switch (collisiontype)
	{
	case COLLISIONTYPE_NORMAL:{
		m_Debugcollision = CDebugcollision::Create(
			m_ppos,
			&m_size,
			CDebugcollision::COLLISIONTYPE_BOARD);
	}break;

	case COLLISIONTYPE_CHARACTER: {
		m_Debugcollision = CDebugcollision::Create(
			m_ppos,
			&m_size,
			CDebugcollision::COLLISIONTYPE_BOARDCHARA);
	}break;

	default:
		break;
	}
#endif //DEBUG
}

//======================================================================================================================
// プレイヤーの弾が行う判定
//======================================================================================================================
bool CCollision::ForPlayerBulletCollision(int nEnemyDamage, int nObstacleDamage, bool Penetration)
{
	// 弾を消すときに使うフラグ
	bool bHitFlag = false;

	// 当たり判定 相手がエネミーだったら
	// 敵の総数分
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		// エネミーのポインタ取得
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			// 判定関数
			if (this->OtherCollision2D(pEnemy->GetCollision()))
			{
				// 敵のライフ減衰
				pEnemy->CCharacter::AddDamage(nEnemyDamage);

				// 敵のライフが0以下になった時
				if (pEnemy->CCharacter::GetLife() <= 0)
				{
					pEnemy = nullptr;
				}

				// 当たり範囲フラグをtrueにする
				bHitFlag = true;
			}
			else
			{
				// 当たり範囲フラグをfalseにする
				bHitFlag = false;

				CDebugProc::Print("\n弾が敵に当たってないよ！ \n");
			}
		}
	}

	// 当たり判定 相手が障害物だったら
	// 障害物の総数分
	for (int nCntObst = 0; nCntObst < CManager::GetBaseMode()->GetMap()->GetMaxObstacle(); nCntObst++)
	{
		CObstacle *pObstacle = CManager::GetBaseMode()->GetMap()->GetObstacle(nCntObst);
		if (pObstacle != nullptr)
		{
			if (this->Collision2D(pObstacle->GetCollision()))
			{
				// 障害物のライフ減衰
				pObstacle->Hit(CObstacle::TYPE_BOX, nObstacleDamage);

				// 敵のライフが0以下になった時
				if (pObstacle->GetLife() <= 0)
				{
					// ポインタをnullにする
					pObstacle = nullptr;
				}

				// 当たり範囲フラグをtrueにする
				bHitFlag = true;
			}
			else
			{
				// 当たり範囲フラグをfalseにする
				bHitFlag = false;

				CDebugProc::Print("\n弾が障害物に当たってないよ！ \n");
			}
		}
	}

	// 当たり判定 相手が捕虜だったら
	// 捕虜の総数分
	for (int nCntPriso = 0; nCntPriso < CManager::GetBaseMode()->GetMap()->GetMaxPrisoner(); nCntPriso++)
	{
		CPrisoner *pPrisoner = CManager::GetBaseMode()->GetMap()->GetPrisoner(nCntPriso);
		if (pPrisoner != nullptr)
		{
			if (pPrisoner->GetPrisonerState() == CPrisoner::PRISONER_STATE_STAY)
			{
				if (this->OtherCollision2D(pPrisoner->GetCollision()))
				{
					// 捕虜の状態変化
					pPrisoner->SetPrisonerState(CPrisoner::PRISONER_STATE_DROPITEM);
					// ポインタをnullにする
					pPrisoner = nullptr;
					// 当たり範囲フラグをtrueにする
					bHitFlag = true;
				}
				else
				{
					// 当たり範囲フラグをfalseにする
					bHitFlag = false;;

					CDebugProc::Print("\n弾が捕虜に当たってないよ！ \n");
				}
			}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// エネミーの弾が行う判定
//======================================================================================================================
bool CCollision::ForEnemyCollision(int nPlayerDamage, bool Penetration)
{
	// 判定を確認するフラグ
	bool bHitFlag = false;

		// 当たり判定 相手がプレイヤーだったら
		// エネミーのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
		if (pPlayer != nullptr)
		{
			// 判定関数
			if (this->OtherCollision2D(pPlayer->GetCollision()))
			{
				// プレイヤーのライフ減衰
				pPlayer->CCharacter::AddDamage(nPlayerDamage);

				// プレイヤーのライフが0以下になった時
				if (pPlayer->CCharacter::GetLife() <= 0)
				{
					// ポインタをnullにする
					pPlayer = nullptr;
				}

				// 当たり範囲フラグをtrueにする
				bHitFlag = true;
			}
			else
			{
				// 当たり範囲フラグをfalseにする
				bHitFlag = false;

				CDebugProc::Print("\n弾が敵に当たってないよ！ \n");
			}
		}

	return bHitFlag;
}

//======================================================================================================================
// プレイヤーとエネミーで行う判定 プレイヤーの接触判定
//======================================================================================================================
bool CCollision::ForPlayer_EnemyCollision(bool Penetration)
{
	// 判定を確認するフラグ
	bool bHitFlag = false;

	//相手がエネミーだったら
	// 敵の総数分
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			if (this->CharCollision2D(pEnemy->GetCollision()))
			{
				bHitFlag = true;
				CDebugProc::Print("\n時機が敵に当たったよ！\n");
			}
			else
			{
				bHitFlag = false;
				CDebugProc::Print("\n時機が敵に当たってないよ！ \n");
			}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// プレイヤーと障害物で行う判定 プレイヤーの接触判定
//======================================================================================================================
bool CCollision::ForPlayer_ObstacleCollision(bool Penetration)
{
	// 判定を確認するフラグ
	bool bHitFlag = false;
	//相手が障害物だったら
	// 障害物のの総数分
	for (int nCntObst = 0; nCntObst < CManager::GetBaseMode()->GetMap()->GetMaxObstacle(); nCntObst++)
	{
		CObstacle *pObstacle = CManager::GetBaseMode()->GetMap()->GetObstacle(nCntObst);
		if (pObstacle != nullptr)
		{
			if (this->BlockCollision2D(pObstacle->GetCollision()))
			{
				bHitFlag = true;
				CDebugProc::Print("\n時機が障害物に当たったよ！\n");
			}
			else
			{
				bHitFlag = false;
				CDebugProc::Print("\n時機が障害物に当たってないよ！ \n");
			}
		}
	}
	return bHitFlag;
}

//======================================================================================================================
// プレイヤーと捕虜で行う判定 プレイヤーの接触判定
//======================================================================================================================
bool CCollision::ForPlayer_PrisonerCollision(bool Penetration)
{
	// 判定を確認するフラグ
	bool bHitFlag = false;

	// 捕虜の総数分
	for (int nCntPriso = 0; nCntPriso < CManager::GetBaseMode()->GetMap()->GetMaxPrisoner(); nCntPriso++)
	{
		CPrisoner *pPrisoner = CManager::GetBaseMode()->GetMap()->GetPrisoner(nCntPriso);
		if (pPrisoner != nullptr)
		{
			if (this->CharCollision2D(pPrisoner->GetCollision()))
			{
				bHitFlag = true;
				CDebugProc::Print("\n時機が捕虜に当たったよ！\n");
			}
			else
			{
				bHitFlag = false;
				CDebugProc::Print("\n時機が捕虜に当たってないよ！ \n");
			}
		}
	}
	return bHitFlag;
}

//======================================================================================================================
// プレイヤーとアイテムで行う判定 プレイヤーの接触判定
//======================================================================================================================
bool CCollision::ForPlayer_ItemCollision(bool Penetration)
{
	// 判定を確認するフラグ
	bool bHitFlag = false;


	//相手がアイテムだったら
	// ベクター型の変数
	std::vector<CScene*> SceneList;

	// 指定したオブジェクトのポインタを取得
	CScene::GetSceneList(CScene::OBJTYPE_ITEM, SceneList);

	//アイテムの総数分
	for (size_t nCnt = 0; nCnt < SceneList.size(); nCnt++)
	{
		CItem *pItem = (CItem*)SceneList[nCnt];
		if (pItem != nullptr)
		{
			if (this->OtherCollision2D(pItem->GetCollision()))
			{
				bHitFlag = true;
				// アイテムごとの処理を通す
				pItem->HitItem(pItem->GetItemType());
				pItem = nullptr;
			}
			else
			{
				bHitFlag = false;
			}
		}
	}
	return bHitFlag;
}

//======================================================================================================================
// 位置設定処理
//======================================================================================================================
void CCollision::SetPos(D3DXVECTOR3 * pos)
{
	m_ppos = pos;

#ifdef _DEBUG
	if (m_Debugcollision != nullptr)
	{
		m_Debugcollision->SetPos(m_ppos);
	}
#endif // _DEBUG
}

//======================================================================================================================
// 1フレーム前の位置設定処理
//======================================================================================================================
void CCollision::SetPosOld(D3DXVECTOR3 * posold)
{
	m_posOld = posold;
}

//======================================================================================================================
// サイズ設定処理
//======================================================================================================================
void CCollision::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

//======================================================================================================================
// 2dサイズ設定処理
//======================================================================================================================
void CCollision::SetSize2D(D3DXVECTOR3 size)
{
	m_size = size;
}

//======================================================================================================================
// 移動設定処理
//======================================================================================================================
void CCollision::SetMove(D3DXVECTOR3 * move)
{
	m_pmove = move;
}

//======================================================================================================================
// タイプ設定処理
//======================================================================================================================
void CCollision::SetType(COLLISION type)
{
	m_objtype = type;
}

//======================================================================================================================
// 板型の当たり判定処理
//======================================================================================================================
bool CCollision::Collision2D(CCollision *pCollision)
{
	// 変数宣言
	bool bHitFlag = false;

	if (pCollision != nullptr)
	{
		// X Yの範囲
		if (this->m_ppos->y + this->m_size.y * 0.5f >= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
			this->m_ppos->y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}

		else
		{
			bHitFlag = false;
		}
	}

	// 当たっているかいないかを返す
	return bHitFlag;
}

//======================================================================================================================
// キャラクター用板型の当たり判定処理
//======================================================================================================================
bool CCollision::CharCollision2D(CCollision * pCollision)
{
	// 変数宣言
	bool bHitFlag = false;

	if (pCollision != nullptr)
	{
		// X Yの範囲
		if (this->m_ppos->y + this->m_size.y >= pCollision->m_ppos->y&&
			this->m_ppos->y <= pCollision->m_ppos->y + pCollision->m_size.y&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}

		else
		{
			bHitFlag = false;
		}
	}

	// 当たっているかいないかを返す
	return bHitFlag;
}

//======================================================================================================================
// キャラクターとアイテム、弾の判定
//======================================================================================================================
bool CCollision::OtherCollision2D(CCollision * pCollision)
{
	// 弾を消すときに使うフラグ
	bool bHitFlag = false;

	if (pCollision != nullptr)
	{
		// X Yの範囲
		if (this->m_ppos->y + this->m_size.y * 0.5f >= pCollision->m_ppos->y&&
			this->m_ppos->y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)

		{
			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}

		else
		{
			bHitFlag = false;
		}
	}

	// 当たっているかいないかを返す
	return bHitFlag;
}

//======================================================================================================================
// 板型のブロックの当たり判定処理
//======================================================================================================================
bool CCollision::BlockCollision2D(CCollision * pCollision)
{
	// 弾を消すときに使うフラグ
	bool bHitFlag = false;

		// 素材のY範囲
		if (this->m_ppos->y + this->m_size.y > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f &&
			this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
		{
			// 当たり判定(左)
			if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
				this->m_posOld->x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
			{
				// 素材状の左に
				this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
				// 移動量の初期化
				this->m_pmove->x = 0.0f;
				// オブジェクトに当たったフラグ
				bHitFlag = true;
			}

			// 当たり判定(右)
			else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f &&
				this->m_posOld->x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
			{
				// 素材状の左に
				this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
				// 移動量の初期化
				this->m_pmove->x = 0.0f;
				// オブジェクトに当たったフラグ
				bHitFlag = true;
			}
		}

		// 素材のX範囲
		if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// 当たり判定(下)
			if (this->m_ppos->y + this->m_size.y > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f &&
				this->m_posOld->y + this->m_size.y <= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f)
			{
				// 素材状の下に
				this->m_ppos->y = this->m_posOld->y;
				// 移動量の初期化
				this->m_pmove->y = 0.0f;
				// オブジェクトに当たったフラグ
				bHitFlag = true;
			}

			// 当たり判定(上)
			else if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f &&
				this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
			{
				// 素材状の上に
				this->m_ppos->y = this->m_posOld->y;
				// 移動量の初期化
				this->m_pmove->y = 0.0f;
				// オブジェクトに当たったフラグ
				bHitFlag = true;
			}
		}

	// 当たっているかいないかを返す
	return bHitFlag;
}