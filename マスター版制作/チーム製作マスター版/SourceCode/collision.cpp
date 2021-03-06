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
#include "playertank.h"
#include "BattlePlane.h"
#include "Character.h"
#include "scoremanager.h"
#include "player.h"
#include "playerui.h"
#include "shield.h"
#include "boss_One.h"
#include "ModelSet.h"
#include "bullet.h"
#include "Normal_Iten.h"
#include "Anim_Item.h"

//======================================================================================================================
//
// マクロ定義
//
//======================================================================================================================
#define MAX_RAY_LENGTH  (60)		//Rayの最大の長さ
#define RAY_FIRST_POINT (30.0f)		//Rayの始点

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
	m_Collisiontype		= COLLISIONTYPE_NORMAL;				// 当たり判定の種類
	m_ppos				= nullptr;							// 位置情報
	m_posOld			= nullptr;							// 前回の位置情報
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// サイズ情報
	m_pmove				= nullptr;							// 移動情報
	m_Debugcollision	= nullptr;							// デバッグ用当たり判定のポインタ
	m_fHeight			= 30;								// 腰の高さの初期化
	m_bCanCollision		= true;
	m_pGameObject		= nullptr;							// ゲームオブジェクト( タグ )のポインタ
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
		m_Debugcollision->Rerease();
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
#ifdef _DEBUG
	if (m_Debugcollision != nullptr)
	{
		m_Debugcollision->SetPos(m_ppos);
	}
#endif // _DEBUG
}

//======================================================================================================================
// デバッグ情報表記
//======================================================================================================================
void CCollision::ShowDebugInfo()
{
	if(ImGui::TreeNode("CollisionInfo"))
	{
		ImGui::Text("Pos >> %.2f %.2f %.2f", m_ppos->x, m_ppos->y, m_ppos->z);
		ImGui::Text("Size >> %.2f %.2f %.2f", m_size.x, m_size.y, m_size.z);
		ImGui::Text("CanCollision >> %d", m_bCanCollision);

		ImGui::TreePop();
	}

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
			CDebugcollision::COLLISIONTYPE_BOX);
	}break;

	case COLLISIONTYPE_CHARACTER: {
		m_Debugcollision = CDebugcollision::Create(
			m_ppos,
			&m_size,
			CDebugcollision::COLLISIONTYPE_BOX_CHARA);
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
	std::vector<CScene*> pSceneList;

	// プレイヤーのポインタ取得
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(m_pGameObject->GetTag());

	CScene::GetSceneList(CScene::OBJTYPE_SHIELD, pSceneList);

	//盾相手の場合
	if (!pSceneList.empty())
	{
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			CShield *pShield = (CShield*)pSceneList[nCnt];
			if (pShield)
			{
				if (this->Collision2D(pShield->GetCollision()))
				{
					pShield->AddDamage(nEnemyDamage);

					// 当たり範囲フラグをtrueにする
					bHitFlag = true;

					if (!Penetration)
					{
						return bHitFlag;
					}
				}
			}
		}
	}


	// 当たり判定 相手がドラゴンノスケだったら火炎放射器
	// 敵の総数分
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		// エネミーのポインタ取得
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);

		//判定が取れるとき
		if (pEnemy->GetCollision()->GetCanCollison())
		{
			if (pEnemy != nullptr)
			{
				if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
				{
					CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

					if (pBoss_One->GetCollision() &&
						pBoss_One->GetPostureType() == CBoss_One::POSTURETYPE_STAND &&
						pBoss_One->GetBossOneType() == CBoss_One::ATTACKTYPE_FLAMERADIATION)
					{
						//判定が取れるとき
						if (pBoss_One->GetCollision()->GetCanCollison())
						{
							// 判定関数
							if (this->OtherCollision2D(pBoss_One->GetCollision()))
							{
								if (pPlayer != nullptr)
								{
									if (pPlayer->GetPlayerUI())
									{
										pPlayer->GetPlayerUI()->SetScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_DAMAGE_BULLET));
									}
								}

								// 敵のライフ減衰
								pBoss_One->CCharacter::AddDamage(nEnemyDamage);

								// 当たり範囲フラグをtrueにする
								bHitFlag = true;

								if (Penetration == false)
								{
									return bHitFlag;
								}
							}
						}
					}

				}
			}

			if (pEnemy->GetCollision())
			{
				//判定が取れるとき
				if (pEnemy->GetCollision()->GetCanCollison())
				{
					// ドローン系の敵は別の判定
					if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_SKYDRONE)
					{
						if (this->CharCollision2D(pEnemy->GetCollision()))
						{
							if (pPlayer != nullptr)
							{
								if (pPlayer->GetPlayerUI())
								{
									pPlayer->GetPlayerUI()->SetScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_DAMAGE_BULLET));
								}
							}

							// 敵のライフ減衰
							pEnemy->CCharacter::AddDamage(nEnemyDamage);

							// 当たり範囲フラグをtrueにする
							bHitFlag = true;

							if (Penetration == false)
							{
								return bHitFlag;
							}
						}
					}
					// それ以外
					else
					{
						if (this->OtherCollision2D(pEnemy->GetCollision()))
						{
							if (pPlayer != nullptr)
							{
								if (pPlayer->GetPlayerUI())
								{
									pPlayer->GetPlayerUI()->SetScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_DAMAGE_BULLET));
								}
							}

							// 敵のライフ減衰
							pEnemy->CCharacter::AddDamage(nEnemyDamage);

							// 当たり範囲フラグをtrueにする
							bHitFlag = true;

							if (Penetration == false)
							{
								return bHitFlag;
							}
						}
						//else if (this->OtherCollision3D(pEnemy->GetCollision()))
						//{
						//	if (pPlayer != nullptr)
						//	{
						//		if (pPlayer->GetPlayerUI())
						//		{
						//			pPlayer->GetPlayerUI()->SetScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_DAMAGE_BULLET));
						//		}
						//	}

						//	// 敵のライフ減衰
						//	pEnemy->CCharacter::AddDamage(nEnemyDamage);

						//	// 当たり範囲フラグをtrueにする
						//	bHitFlag = true;

						//	if (Penetration == false)
						//	{
						//		return bHitFlag;
						//	}
						//}
					}
				}
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
			if (pObstacle->GetCollision()->GetCanCollison())
			{
				if (this->Collision2D(pObstacle->GetCollision()))
				{
					// 障害物のライフ減衰
					pObstacle->Hit(m_pGameObject->GetTag(), nObstacleDamage);

					// 敵のライフが0以下になった時
					if (pObstacle->GetLife() <= 0)
					{
						pObstacle->SetDieFlag(true);
						// ポインタをnullにする
						pObstacle = nullptr;
					}

					// 当たり範囲フラグをtrueにする
					bHitFlag = true;

					if (Penetration == false)
					{
						return bHitFlag;
					}
				}
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
			//判定が取れるとき
			if (pPrisoner->GetCollision()->GetCanCollison())
			{
				if (this->OtherCollision2D(pPrisoner->GetCollision()))
				{
					if (pPlayer != nullptr)
					{
						if (pPlayer->GetPlayerUI())
						{
							pPlayer->GetPlayerUI()->SetScore(CScoreManager::GetScorePoint(CScoreManager::SCORE_RESCUE_PRISONER));
							// 体力の加算
							pPlayer->SetLife(pPlayer->GetLife() + 1);
						}
					}

					pPrisoner->SetPlayerPtr(pPlayer);
					// 捕虜の状態変化
					pPrisoner->SetPrisonerState(CPrisoner::PRISONER_STATE_THINKING);
					// ポインタをnullにする
					pPrisoner = nullptr;
					// 当たり範囲フラグをtrueにする
					bHitFlag = true;
					if (Penetration == false)
					{
						return bHitFlag;
					}
				}
			}
		}
	}
	return bHitFlag;
}

//======================================================================================================================
// エネミーの弾が行う判定
//======================================================================================================================
bool CCollision::ForEnemyCollision(int nPlayerDamage, int nPlayerTankDamage, bool Penetration)
{
	// 判定を確認するフラグ
	bool bHitFlag = false;
	// プレイヤーのポインタ
	CPlayer *pPlayer[MAX_CONTROLLER] = {};

	for (int nCntPlayer = 0; nCntPlayer < MAX_CONTROLLER; nCntPlayer++)
	{
		pPlayer[nCntPlayer] = CManager::GetBaseMode()->GetPlayer((TAG)nCntPlayer);

		if (pPlayer[nCntPlayer] != nullptr)
		{
			if (pPlayer[nCntPlayer]->GetRideFlag())
			{
				// 当たり判定 相手がプレイヤー用戦車だったら
				for (int nCntTank = 0; nCntTank < CManager::GetBaseMode()->GetMap()->GetMaxPlayerTank(); nCntTank++)
				{
					CPlayertank *pPlayertank = CManager::GetBaseMode()->GetMap()->GetPlayertank(nCntTank);
					if (pPlayertank != nullptr)
					{
						// 判定関数
						if (this->OtherCollision2D(pPlayertank->GetCollision()))
						{
							// プレイヤーのライフ減衰
							pPlayertank->AddDamage(nPlayerTankDamage);

							// 当たり範囲フラグをtrueにする
							bHitFlag = true;
						}
						else
						{
							// 当たり範囲フラグをfalseにする
							bHitFlag = false;
						}
					}
				}
			}
			else
			{
				// 当たり判定 相手がプレイヤーだったら
				if (pPlayer[nCntPlayer] != nullptr)
				{
					if (pPlayer[nCntPlayer]->GetCollision()->GetCanCollison())
					{
						// 判定関数
						if (this->OtherCollision2D(pPlayer[nCntPlayer]->GetCollision()))
						{
							// プレイヤーのライフ減衰
							pPlayer[nCntPlayer]->CCharacter::AddDamage(nPlayerDamage);

							// 当たり範囲フラグをtrueにする
							bHitFlag = true;
						}
					}
					else
					{
						// 当たり範囲フラグをfalseにする
						bHitFlag = false;
					}
				}
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
			if (pObstacle->GetCollision()->GetCanCollison())
			{
				if (this->Collision2D(pObstacle->GetCollision()))
				{
					// 当たり範囲フラグをtrueにする
					bHitFlag = true;

					if (Penetration == false)
					{
						return bHitFlag;
					}
				}
			}
		}
	}

	return bHitFlag;
}
//======================================================================================================================
// 敵の車両との判定
// 敵の車両と被らないようにする
//======================================================================================================================
void CCollision::EnemyVehicleCollision()
{
	//相手がエネミーだったら
	// 敵の総数分
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);

		//nullcheck
		if (pEnemy != nullptr)
		{
			//nullcheck
			if (pEnemy->GetCollision())
			{
				//自分だった場合は判定しない
				if (this == pEnemy->GetCollision())
				{
					continue;
				}
				//敵の乗り物の場合
				if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER ||
					pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY ||
					pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA)
				{
					//衝突判定
					if (this->BoxCollision2D_Vehicle(pEnemy->GetCollision()))
					{
					}
				}
			}
		}
	}
}
//======================================================================================================================
// プレイヤーとエネミーで行う判定 プレイヤーの接触判定 フラグを返す
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
			if (pEnemy->GetCollision())
			{
				if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
				{
					CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

					/*if (pBoss_One->GetCollision() &&
						pBoss_One->GetPostureType() == CBoss_One::POSTURETYPE_SQUAT)
					{
						if (this->BoxCollision2D_Character(pBoss_One->GetCollision()))
						{
							return false;
						}
					}*/
					if (pBoss_One->GetCollision())
					{
						if (this->BoxCollision2D_Character(pBoss_One->CCharacter::GetCollision()))
						{
							return false;
						}
					}
				}
				else
				{
					//通常の雑魚的の時
					if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_NORMAL ||
						pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_SHIELD)
					{
						//判定が取れるとき
						if (pEnemy->GetCollision()->GetCanCollison())
						{
							if (this->CharCollision2D(pEnemy->GetCollision()))
							{
								return true;
							}
						}
					}
					//敵の乗り物の場合
					else if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER ||
						pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY ||
						pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA)
					{
						//衝突判定
						if (this->BoxCollision2D_Vehicle(pEnemy->GetCollision()))
						{
							//横から接触したプレイヤーにダメージ判定
							CManager::GetGame()->GetPlayer(m_pGameObject->GetTag())->AddDamage(1);
						}
					}
				}
			}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// プレイヤーと戦車で行う判定 プレイヤーの接触判定 ポインタを返す
//======================================================================================================================
CPlayertank * CCollision::ForPlayer_TankCollision()
{
	CPlayertank *pPlayertank = nullptr;

	// 戦車の総数分
	for (int nCntTank = 0; nCntTank < CManager::GetBaseMode()->GetMap()->GetMaxPlayerTank(); nCntTank++)
	{
		// 戦車のポインタを取得
		pPlayertank = CManager::GetBaseMode()->GetMap()->GetPlayertank(nCntTank);

		//nullcheck
		if (pPlayertank != nullptr)
		{
			//判定かのうかどうか
			if (pPlayertank->GetCollision()->GetCanCollison())
			{
				//タンクに乗る処理
				if (this->ForPlayer_VehicleCollision(pPlayertank->GetCollision()))
				{
					// 処理を行った戦車のポインタを返す
					return pPlayertank;
				}
			}
		}

		// nullだったらnullを返す
		else if (pPlayertank == nullptr)
		{
			return nullptr;
		}
	}

	// ポインタを返す
	return pPlayertank;
}

//======================================================================================================================
// プレイヤーと障害物で行う判定 プレイヤーの接触判定
//======================================================================================================================
bool CCollision::ForPlayer_ObstacleCollision()
{
	// 判定を確認するフラグ
	bool bHitFlag = false;
	//相手が障害物だったら
	// 障害物のの総数分
	for (int nCntObst = 0; nCntObst < CManager::GetBaseMode()->GetMap()->GetMaxObstacle(); nCntObst++)
	{
		CObstacle *pObstacle = CManager::GetBaseMode()->GetMap()->GetObstacle(nCntObst);
		if (pObstacle != nullptr && pObstacle->GetObstacleType() != CObstacle::TYPE_TREE && pObstacle->GetObstacleType() != CObstacle::TYPE_BOSSMAP_BRIDGE&& pObstacle->GetObstacleType() != CObstacle::TYPE_BOSSMAP_BELL)
		{
			if (this->BlockCollision2D(pObstacle->GetCollision()))
			{
				bHitFlag = true;
			}
		}

		if (pObstacle != nullptr && pObstacle->GetObstacleType() == CObstacle::TYPE_BOSSMAP_BRIDGE)
		{
			if (this->BoxCollision3D(pObstacle->GetCollision()))
			{
				bHitFlag = true;
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
			//判定が取れるとき
			if (pPrisoner->GetCollision()->GetCanCollison())
			{
				if (this->CharCollision2D(pPrisoner->GetCollision()))
				{
					bHitFlag = true;
				}
			}
		}
	}
	return bHitFlag;
}

//======================================================================================================================
// プレイヤーと捕虜で行う判定 プレイヤーの接触判定
//======================================================================================================================
CPrisoner *CCollision::ForPlayer_PrisonerCollision()
{
	CPrisoner *pPrisoner = nullptr;
	// 捕虜の総数分
	for (int nCntPriso = 0; nCntPriso < CManager::GetBaseMode()->GetMap()->GetMaxPrisoner(); nCntPriso++)
	{
		// 捕虜のポインタを取得
		pPrisoner = CManager::GetBaseMode()->GetMap()->GetPrisoner(nCntPriso);

		if (pPrisoner != nullptr)
		{
			if (this->CharCollision2D(pPrisoner->GetCollision()))
			{
				if (pPrisoner->GetPrisonerState() == CPrisoner::PRISONER_STATE_STAY)
				{
					// 処理を行った捕虜のポインタを返す
					return pPrisoner;
				}
			}
		}

		// nullだったらnullを返す
		else if (pPrisoner == nullptr)
		{
			return nullptr;
		}
	}

	// ポインタを返す
	return pPrisoner;
}

//======================================================================================================================
// プレイヤーが乗り物に乗る時の判定
//======================================================================================================================
bool CCollision::ForPlayer_VehicleCollision(CCollision * pCollision)
{
	// 判定を確認するフラグ
	bool bHitFlag = false;

	if (this->VehicleCollision(pCollision))
	{
		bHitFlag = true;
	}
	return bHitFlag;
}

//======================================================================================================================
// プレイヤーが乗り物に乗る時の判定
//======================================================================================================================
CVehicle *CCollision::ForPlayer_VehicleCollision()
{
	CPlayertank *pPlayertank = nullptr;

	// 戦車の総数分
	for (int nCntTank = 0; nCntTank < CManager::GetBaseMode()->GetMap()->GetMaxPlayerTank(); nCntTank++)
	{
		// 戦車のポインタを取得
		pPlayertank = CManager::GetBaseMode()->GetMap()->GetPlayertank(nCntTank);

		if (pPlayertank != nullptr)
		{
			if (pPlayertank->GetCollision()->GetCanCollison())
			{
				if (pPlayertank->GetRideerTag() == TAG::NONE)
				{
					if (this->VehicleCollision(pPlayertank->GetCollision()))
					{
						return pPlayertank;
					}
				}
			}
		}
	}
	return nullptr;
}

//======================================================================================================================
// 乗り物が行う判定
//======================================================================================================================
bool CCollision::ForVehicleCollision(TAG Tag)
{
	// 判定を確認するフラグ
	bool bHitFlag = false;

	// ベクター型の変数
	std::vector<CScene*> pNormalSceneList, pAnimationSceneList;

	// 指定したオブジェクトのポインタを取得
	CScene::GetSceneList(CScene::OBJTYPE_NORMALITEM, pNormalSceneList);
	CScene::GetSceneList(CScene::OBJTYPE_ANIMATIONITEM, pAnimationSceneList);

	//通常アイテムの総数分
	for (size_t nCnt = 0; nCnt < pNormalSceneList.size(); nCnt++)
	{
		CNormalItem *pItem = (CNormalItem*)pNormalSceneList[nCnt];
		if (pItem != nullptr)
		{
			if (pItem->GetCollision()->OtherCollision2D(this))
			{
				if (pItem->GetCollision()->OtherCollision2D(this))
				{
					bHitFlag = true;
					// アイテムごとの処理を通す
					pItem->HitItem(pItem->GetItemType(), Tag);
					pItem = nullptr;
				}
			}
		}
	}

	// アニメーションアイテムの総数分
	for (size_t nCnt = 0; nCnt < pAnimationSceneList.size(); nCnt++)
	{
		CAnimationItem *pItem = (CAnimationItem*)pAnimationSceneList[nCnt];
		if (pItem != nullptr)
		{
			if (pItem->GetCollision()->OtherCollision2D(this))
			{
				if (pItem->GetCollision()->OtherCollision2D(this))
				{
					bHitFlag = true;
					// アイテムごとの処理を通す
					pItem->HitItem(pItem->GetItemType(), Tag);
					pItem = nullptr;
				}
			}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// 戦車が行う判定
//======================================================================================================================
bool CCollision::ForTankCollision()
{
	// 判定を確認するフラグ
	bool bHitFlag = false;

	//相手がエネミーだったら
	// 敵の総数分
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy->GetCollision())
		{
			//判定が取れるとき
			if (pEnemy->GetCollision()->GetCanCollison())
			{
				//通常の雑魚的の時
				if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_NORMAL ||
					pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_SHIELD)
				{
					//轢く
					if (this->CharCollision2D(pEnemy->GetCollision()))
					{
						bHitFlag = true;
						pEnemy->AddDamage(1);
					}
				}
				//敵の乗り物の場合
				else if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER ||
					pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY ||
					pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA)
				{
					//衝突判定
					//めりこまないように
					if (this->BoxCollision2D_Vehicle(pEnemy->GetCollision()))
					{
					}
				}
			}
		}
	}

	return false;
}


//======================================================================================================================
// ボスが行う判定
//======================================================================================================================
void CCollision::ForBossOne_PlayerCollision()
{
	//相手がエネミーだったら
	// 敵の総数分
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			if (pEnemy->GetEnemyType() == CEnemy::ENEMY_TYPE::ENEMY_NORMAL)
			{
				CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

			}
		}
	}
}

//======================================================================================================================
// ボスが行う判定
//======================================================================================================================
bool CCollision::BossOne_PlayerCollision()
{
	// 判定を確認するフラグ
	bool bHitFlag = false;
	// プレイヤーのポインタ
	CPlayer *pPlayer[MAX_CONTROLLER] = {};

	//相手がエネミーだったら
	// 敵の総数分
	for (int nCnt = 0; nCnt < CManager::GetBaseMode()->GetMap()->GetMaxEnemy(); nCnt++)
	{
		CEnemy *pEnemy = CManager::GetBaseMode()->GetMap()->GetEnemy(nCnt);
		if (pEnemy != nullptr)
		{
			if (pEnemy->GetModelSet()->GetCharacterType() == CModelSet::CHARACTER_TYPE_BOSS_ONE)
			{
				CBoss_One *pBoss_One = (CBoss_One*)pEnemy;

				if (pBoss_One->GetCollision() &&
					pBoss_One->GetIntermediateSquat())
				{
					for (int nCntPlayer = 0; nCntPlayer < MAX_CONTROLLER; nCntPlayer++)
					{
						// プレイヤーのポインタ取得
						pPlayer[nCntPlayer] = CManager::GetBaseMode()->GetPlayer((TAG)nCntPlayer);

						if (pPlayer[nCntPlayer] != nullptr)
						{
							if (this->BlockCollision2D_Bottom(pPlayer[nCntPlayer]->GetCollision()))
							{
								// 敵のライフ減衰
								pPlayer[nCntPlayer]->CCharacter::AddDamage(1);

								bHitFlag = true;
							}
						}
					}
				}
			}
		}
	}

	return bHitFlag;
}

//======================================================================================================================
// ナイフとキャラクターの判定
//======================================================================================================================
bool CCollision::KnifeCollision(D3DXVECTOR3 Knifepos, CCollision *pCollision)
{
	// 弾を消すときに使うフラグ
	bool bHitFlag = false;

	if (pCollision != nullptr)
	{
		// X Yの範囲
		if (Knifepos.y + this->m_size.y * 0.5f >= pCollision->m_ppos->y&&
			Knifepos.y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y&&
			Knifepos.x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			Knifepos.x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)

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
// レーザーの判定
//======================================================================================================================
bool CCollision::LazerCollisionGetLength(D3DXVECTOR3 ShotPos, float &fLength)
{
	bool bHitFlag = false;								//フラグ
	float fValue = 0.0f;								//計算した値
	CShield *pShield = nullptr;							//盾のポインタ
	CObstacle *pObstacle = nullptr;						//オブジェクトのポインタ
	CEnemy *pEnemy = nullptr;						//敵のポインタ

	CGameObject *pMostNearObject = nullptr;				//一番近いオブジェクトのポインタ
	std::vector<CScene*> pSceneList = {};				//Sceneのリスト

	//盾のリスト取得
	CScene::GetSceneList(CScene::OBJTYPE_SHIELD, pSceneList);

	//当たり判定処理
	//盾相手の場合
	if (!pSceneList.empty())
	{
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//pShield型にキャスト
			pShield = (CShield*)pSceneList[nCnt];

			//nullcheck
			if (!pShield)
			{
				continue;
			}
			//判定が存在する時
			if (!pShield->GetCollision())
			{
				continue;
			}
			//判定が取れるとき
			if (!pShield->GetCollision()->GetCanCollison())
			{
				continue;
			}
			//接触してるか判定
			if (this->Collision2D(pShield->GetCollision()))
			{
				//距離を求める
				fValue = (fabsf(ShotPos.x - pShield->GetShieldPos().x) / 2) - pShield->GetCollision()->GetSize().x * 0.4f;

				//元々の長さよりも短かった場合
				if (fValue <= fLength)
				{
					//短い方を設定
					fLength = fValue;

					//ポインタ保存
					pMostNearObject = (CGameObject*)pShield;
				}
				bHitFlag = true;
			}
		}
	}


	//オブジェクトのリスト取得
	CScene::GetSceneList(CScene::OBJTYPE_OBSTACLE, pSceneList);

	//当たり判定処理
	//盾相手の場合
	if (!pSceneList.empty())
	{
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//Obstacle型にキャスト
			pObstacle = (CObstacle*)pSceneList[nCnt];

			//nullcheck
			if (!pObstacle)
			{
				continue;
			}
			//判定が存在する時
			if (!pObstacle->GetCollision())
			{
				continue;
			}
			//判定が取れるとき
			if (!pObstacle->GetCollision()->GetCanCollison())
			{
				continue;
			}
			//接触してるか判定
			if (this->Collision2D(pObstacle->GetCollision()))
			{
				//距離を求める
				fValue = (fabsf(ShotPos.x - pObstacle->GetCollision()->GetPos().x) / 2) - pObstacle->GetCollision()->GetSize().x * 0.4f;

				//元々の長さよりも短かった場合
				if (fValue <= fLength)
				{
					//短い方を設定
					fLength = fValue;

					//ポインタ保存
					pMostNearObject = (CGameObject*)pObstacle;
				}
				bHitFlag = true;
			}
		}
	}


	//オブジェクトのリスト取得
	CScene::GetSceneList(CScene::OBJTYPE_ENEMY, pSceneList);

	//当たり判定処理
	//盾相手の場合
	if (!pSceneList.empty())
	{
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//Obstacle型にキャスト
			pEnemy = (CEnemy*)pSceneList[nCnt];
			bool bHit = false;

			//nullcheck
			if (!pEnemy)
			{
				continue;
			}
			//判定が存在する時
			if (!pEnemy->GetCollision())
			{
				continue;
			}
			//判定が取れるとき
			if (!pEnemy->GetCollision()->GetCanCollison())
			{
				continue;
			}

			switch (pEnemy->GetEnemyType())
			{
			case::CEnemy::ENEMY_TYPE::ENEMY_HELICOPTER:
			case::CEnemy::ENEMY_TYPE::ENEMY_MELTYHONEY:
			case::CEnemy::ENEMY_TYPE::ENEMY_ZYCOCCA:
				bHit = this->OtherCollision2D(pEnemy->GetCollision());
				break;

			case::CEnemy::ENEMY_TYPE::ENEMY_BOSS_DRAGON_NOSUKE:
			case::CEnemy::ENEMY_TYPE::ENEMY_BOSS_SOL_DE_ROCA:
				bHit = this->CharCollision2D(pEnemy->GetCollision());
				break;
			}

			//接触してるか判定
			if (bHit)
			{
				//距離を求める
				fValue = (fabsf(ShotPos.x - pEnemy->GetCollision()->GetPos().x) / 2) - pEnemy->GetCollision()->GetSize().x * 0.4f;

				//元々の長さよりも短かった場合
				if (fValue <= fLength)
				{
					//短い方を設定
					fLength = fValue;

					//ポインタ保存
					pMostNearObject = (CGameObject*)pEnemy;
				}
				bHitFlag = true;
			}
		}
	}
	//当たってた場合
	if (bHitFlag)
	{
		//nullcheck
		if (pMostNearObject)
		{
			switch (pMostNearObject->GetTag())
			{
			case TAG::SHIELD:
				pShield = (CShield*)pMostNearObject;
				pShield->AddDamage(1);

				break;
			case TAG::OBSTACLE:
				pObstacle = (CObstacle*)pMostNearObject;
				pObstacle->Hit(pMostNearObject->GetTag(), 1);

				break;
			case TAG::ENEMY:
				pEnemy = (CEnemy*)pMostNearObject;
				pEnemy->AddDamage(1);

				break;
			default:
				break;
			}

		}
	}
	return bHitFlag;
}

//======================================================================================================================
// プレイヤーが乗り物に乗る時の判定
//======================================================================================================================
bool CCollision::VehicleCollision(CCollision * pCollision)
{
	// 変数宣言
	bool bHitFlag = false;

	// 素材のX範囲
	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
		this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	{
		// 当たり判定(上)
		if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f &&
			this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
		{
			// 素材状の上に
			//this->m_ppos->y = this->m_posOld->y;
			// 移動量の初期化
			//this->m_pmove->y = 0.0f;
			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}
	}

	// 当たっているかいないかを返す
	return bHitFlag;
}

//======================================================================================================================
// プレイヤーとアイテムで行う判定 プレイヤーの接触判定
//======================================================================================================================
bool CCollision::ForPlayer_ItemCollision(TAG Tag)
{
	// 判定を確認するフラグ
	bool bHitFlag = false;

	// ベクター型の変数
	std::vector<CScene*> pNormalSceneList, pAnimationSceneList;

	// 指定したオブジェクトのポインタを取得
	CScene::GetSceneList(CScene::OBJTYPE_NORMALITEM, pNormalSceneList);
	CScene::GetSceneList(CScene::OBJTYPE_ANIMATIONITEM, pAnimationSceneList);

	//通常アイテムの総数分
	for (size_t nCnt = 0; nCnt < pNormalSceneList.size(); nCnt++)
	{
		CNormalItem *pItem = (CNormalItem*)pNormalSceneList[nCnt];
		if (pItem != nullptr)
		{
			if (pItem->GetCollision()->OtherCollision2D(this))
			{
				bHitFlag = true;
				// アイテムごとの処理を通す
				pItem->HitItem(pItem->GetItemType(), Tag);
			}
		}
	}

	// アニメーションアイテムの総数分
	for (size_t nCnt = 0; nCnt < pAnimationSceneList.size(); nCnt++)
	{
		CAnimationItem *pItem = (CAnimationItem*)pAnimationSceneList[nCnt];
		if (pItem != nullptr)
		{
			if (pItem->GetCollision()->OtherCollision2D(this))
			{
				if (pItem->GetCollision()->OtherCollision2D(this))
				{
					bHitFlag = true;
					// アイテムごとの処理を通す
					pItem->HitItem(pItem->GetItemType(), Tag);
					pItem = nullptr;
				}
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
#ifdef _DEBUG
	if (m_Debugcollision != nullptr)
	{
		m_Debugcollision->SetSize(&m_size);
	}
#endif // _DEBUG

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
			this->m_ppos->y						<= pCollision->m_ppos->y + pCollision->m_size.y&&
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
// キャラクターとアイテム、弾の判定3D
//======================================================================================================================
bool CCollision::OtherCollision3D(CCollision * pCollision)
{
	if (pCollision != nullptr)
	{
		// X Y Zの範囲
		if (this->m_ppos->y + this->m_size.y * 0.5f >= pCollision->m_ppos->y&&
			this->m_ppos->y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f&&
			this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
			this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f
			)
		{
			// オブジェクトに当たったフラグ
			return true;
		}
		else
		{
			return false;
		}
	}

	// 当たっているかいないかを返す
	return false;
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
			}

			// 当たり判定(右)
			else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f &&
				this->m_posOld->x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
			{
				// 素材状の左に
				this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
				// 移動量の初期化
				this->m_pmove->x = 0.0f;
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
//======================================================================================================================
// ボックスコリジョン3d 橋と敵の判定
//======================================================================================================================
bool CCollision::BoxCollision3D(CCollision * pCollision)
{
	// 素材のY範囲
	//if (this->m_ppos->y + this->m_size.y > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f &&
	//	this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
	//{
	//	// 当たり判定(左)
	//	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
	//		this->m_posOld->x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
	//	{
	//		// 素材状の左に
	//		this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
	//		// 移動量の初期化
	//		this->m_pmove->x = 0.0f;
	//	}

	//	// 当たり判定(右)
	//	else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f &&
	//		this->m_posOld->x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	//	{
	//		// 素材状の左に
	//		this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
	//		// 移動量の初期化
	//		this->m_pmove->x = 0.0f;
	//	}
	//}

	// 素材のX範囲
	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
		this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	{
		// 素材のZ範囲
		if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f &&
			this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
		{
			// 当たり判定(上)
			if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f &&
				this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
			{
				// 素材状の上に
				this->m_ppos->y = this->m_posOld->y;
				// オブジェクトに当たったフラグ
				return true;
			}
		}
	}

	// 当たっているかいないかを返す
	return false;
}
//======================================================================================================================
// 板型のブロックの当たり判定処理(上の判定なし)
//======================================================================================================================
bool CCollision::BlockNotUpsideCollision2D(CCollision * pCollision)
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
	}

	// 当たっているかいないかを返す
	return bHitFlag;
}

//======================================================================================================================
// ブロックの下の判定を返す ボス用
//======================================================================================================================
bool CCollision::BlockCollision2D_Bottom(CCollision * pCollision)
{
	// 弾を消すときに使うフラグ
	bool bHitFlag = false;

	// 素材のY範囲
	if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y &&
		this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y)
	{
		// 当たり判定(左)
		if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
			this->m_posOld->x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
		{
			// 素材状の左に
			pCollision->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
			// 移動量の初期化
			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}

		// 当たり判定(右)
		else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f &&
			this->m_posOld->x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// 素材状の左に
			pCollision->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
			// オブジェクトに当たったフラグ
			//bHitFlag = true;
		}
	}

	// 素材のX範囲
	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
		this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	{
		// 当たり判定(下)
		if (this->m_posOld->y + 50.0f > pCollision->m_ppos->y + pCollision->m_size.y &&
			this->m_ppos->y + 50.0f <= pCollision->m_ppos->y + pCollision->m_size.y)
		{
			// 素材状の下に
			//this->m_ppos->y = this->m_posOld->y;
			pCollision->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}

		// 当たり判定(上)
		else if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f &&
			this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
		{
			// 素材状の左に
			pCollision->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}
	}

	// 当たっているかいないかを返す
	return bHitFlag;
}

//======================================================================================================================
// キャラクター同士のボックス判定 ボス用
//======================================================================================================================
bool CCollision::BoxCollision2D_Character(CCollision * pCollision)
{
	// 弾を消すときに使うフラグ
	bool bHitFlag = false;

	// 素材のY範囲
	if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y &&
		this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y)
	{
		// 当たり判定(左)
		if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
			this->m_posOld->x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
		{
			// 素材状の左に
			this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;
			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}

		// 当たり判定(右)
		else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f &&
			this->m_posOld->x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// 素材状の右に
			this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}
	}

	// 素材のX範囲
	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
		this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	{
		// 当たり判定(下)
		if (this->m_ppos->y + this->m_size.y > pCollision->m_ppos->y &&
			this->m_posOld->y + this->m_size.y <= pCollision->m_ppos->y)
		{
			// 素材状の下に
			this->m_ppos->y = this->m_posOld->y;
			if (m_pmove)
			{
				this->m_pmove = 0;
			}
		}

		//// 当たり判定(上)
		//else if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f &&
		//	this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
		//{
		//	// 素材状の上に
		//	this->m_ppos->y = this->m_posOld->y;
		//	// 移動量の初期化
		//	this->m_pmove->y = 0.0f;
		//	// オブジェクトに当たったフラグ
		//	bHitFlag = true;
		//}
	}

	// 当たっているかいないかを返す
	return bHitFlag;
}

//======================================================================================================================
// 敵乗り物とプレイヤーの判定
// 横から当たるとプレイヤーダメージ
// 上は弾かれる
//======================================================================================================================
bool CCollision::BoxCollision2D_Vehicle(CCollision * pCollision)
{
	// 横から衝突したときのフラグ
	bool bHitFlag = false;

	// 素材のY範囲
	if (this->m_ppos->y + this->m_size.y	> pCollision->m_ppos->y&&
		this->m_ppos->y						< pCollision->m_ppos->y + pCollision->m_size.y)
	{
		// 当たり判定(左)
		if ((this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
				this->m_posOld->x + this->m_size.x * 0.5f <= pCollision->m_posOld->x - pCollision->m_size.x * 0.5f))

		{
			// 素材状の左に
			this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;

			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}

		// 当たり判定(右)
		else if ((this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f &&
				this->m_posOld->x - this->m_size.x * 0.5f >= pCollision->m_posOld->x + pCollision->m_size.x * 0.5f))
		{
			// 素材状の左に
			this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;

			// オブジェクトに当たったフラグ
			bHitFlag = true;
		}
	}

	// 素材のX範囲
	if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f &&
		this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	{
		// 当たり判定(上)
		if (this->m_ppos->y < pCollision->m_ppos->y + pCollision->m_size.y * 0.8f &&
			this->m_posOld->y >= pCollision->m_ppos->y + pCollision->m_size.y * 0.8f)
		{
			// 素材状の上に
			// 移動量の初期化
			this->m_pmove->y = 10.0f;
			this->m_pmove->x *= -1.0f;
		}
	}

	// 当たっているかいないかを返す
	return bHitFlag;
}

//======================================================================================================================
// レイの判定
//======================================================================================================================
bool CCollision::RayBlockCollision(CMap *pMap, D3DXMATRIX *pMat)
{
	// 地形判定 変数宣言
	BOOL				bHitFlag			= false;	// 判定が出たかのフラグ
	bool				bLand				= false;	// 判定が出たかのフラグ
	float				fLandDistance		= 0;		// 距離
	DWORD				dwHitIndex			= -1;		// インデックス
	float				fHitU				= 0;		// U
	float				fHitV				= 0;		// V
	D3DXMATRIX			invmat;							// 逆行列を格納する変数
	D3DXVECTOR3			m_posAfter;						// 逆行列で出した終点情報を格納する
	D3DXVECTOR3			m_posBefore;					// 終点情報を格納する
	D3DXVECTOR3			direction;						// 変換後の位置、方向を格納する変数：
	std::vector<float>	vDistance;						// 長さの配列保存
	float				fData				= 0.0f;		// データ

	// マップモデルの最大数分繰り返す
	for (int nCnt = 0; nCnt < pMap->GetMaxModel(); nCnt++)
	{
		//	逆行列の取得
		D3DXMatrixInverse(&invmat, NULL, pMap->GetModel(nCnt)->GetMatrix());
		//	逆行列を使用し、レイ始点情報を変換　位置と向きで変換する関数が異なるので要注意
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(this->m_ppos->x, pMat->_42, this->m_ppos->z), &invmat);
		//	レイ終点情報を変換
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(this->m_ppos->x , this->m_ppos->y - 1, this->m_ppos->z), &invmat);
		//	レイ方向情報を変換
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));
		//Rayを飛ばす
		D3DXIntersect(pMap->GetMesh(nCnt), &m_posBefore, &direction, &bHitFlag, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bHitFlag == TRUE)
		{
			//長さの保存追加
			vDistance.emplace_back(fLandDistance);
		}
		else
		{
		}
	}
	// オブジェクトの最大数分繰り返す
	for (int nCnt = 0; nCnt < CManager::GetGame()->GetMap()->GetMaxObstacle(); nCnt++)
	{
		//	逆行列の取得
		D3DXMatrixInverse(&invmat, NULL, CManager::GetGame()->GetMap()->GetObstacle(nCnt)->GetMatrix());
		//	逆行列を使用し、レイ始点情報を変換　位置と向きで変換する関数が異なるので要注意
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(this->m_ppos->x, pMat->_42, this->m_ppos->z), &invmat);
		//	レイ終点情報を変換
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(this->m_ppos->x, this->m_ppos->y - 1, this->m_ppos->z), &invmat);
		//	レイ方向情報を変換
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));
		//Rayを飛ばす
		D3DXIntersect(CManager::GetGame()->GetMap()->GetObstacle(nCnt)->GetMesh(), &m_posBefore, &direction, &bHitFlag, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bHitFlag == TRUE)
		{
			//長さの保存追加
			vDistance.emplace_back(fLandDistance);
		}
		else
		{
		}
	}

	//Rayのヒットした物があったとき
	if (!vDistance.empty())
	{
		//最初の比較対象
		fData = vDistance[0];
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fData)
			{
				//比較対象が小さかったら代入
				fData = vDistance[nCnt];
			}
		}
		if (fData < m_fHeight)//Rayの長さの指定条件
		{
			this->m_ppos->y = this->m_ppos->y - fData + m_fHeight;
			bLand = true;
		}
		//Rayの判定圏内じゃなかったらジャンプできない
		else
		{
			bLand = false;
		}


	}
	//Rayに判定がなかったらジャンプできない
	else
	{
		bLand = false;
	}

	//配列を空にしておく
	vDistance.clear();

	// 判定フラグを返す
	return bLand;
}

//======================================================================================================================
// レイの判定
//======================================================================================================================
bool CCollision::RayCollision(CMap * pMap, D3DXVECTOR3 posOrigin, D3DXVECTOR3 posEndPoint)
{
	// 地形判定 変数宣言
	BOOL				bHitFlag = false;			// 判定が出たかのフラグ
	bool				bJudg = false;				// 判定が出たかのフラグ
	float				fLandDistance = 0;			// 距離
	DWORD				dwHitIndex = -1;			// インデックス
	float				fHitU = 0;					// U
	float				fHitV = 0;					// V
	D3DXMATRIX			invmat;						// 逆行列を格納する変数
	D3DXVECTOR3			direction;					// 変換後の位置、方向を格納する変数：
	std::vector<float>	vDistance;					// 長さの配列保存
	float				fData = 0.0f;				// データ
	float				fLength = D3DXVec3Length(&D3DXVECTOR3(posEndPoint - posOrigin));

													// マップモデルの最大数分繰り返す
	for (int nCnt = 0; nCnt < pMap->GetMaxModel(); nCnt++)
	{
		//	逆行列の取得
		D3DXMatrixInverse(&invmat, NULL, pMap->GetModel(nCnt)->GetMatrix());
		//	逆行列を使用し、レイ始点情報を変換　位置と向きで変換する関数が異なるので要注意
		D3DXVec3TransformCoord(&posOrigin, &posOrigin, &invmat);
		//	レイ終点情報を変換
		D3DXVec3TransformCoord(&posEndPoint, &posEndPoint, &invmat);
		//	レイ方向情報を変換
		D3DXVec3Normalize(&direction, &(posEndPoint - posOrigin));
		//Rayを飛ばす
		D3DXIntersect(pMap->GetMesh(nCnt), &posOrigin, &direction, &bHitFlag, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bHitFlag == TRUE)
		{
			//長さの保存追加
			vDistance.emplace_back(fLandDistance);
		}
		else
		{
		}
	}
	//Rayのヒットした物があったとき
	if (!vDistance.empty())
	{
		//最初の比較対象
		fData = vDistance[0];

		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fData)
			{
				//比較対象が小さかったら代入
				fData = vDistance[nCnt];
			}
		}
		if (fData < fLength + (m_size.y * 0.5f))//Rayの長さの指定条件
		{
			if (direction.y <= 0)
			{
				//始点座標 - 判定地との距離 - オブジェクトの幅
				this->m_ppos->y = posOrigin.y - fData + (m_size.y * 0.5f);
			}
			else
			{
				//始点座標 - 判定地との距離 + オブジェクトの幅
				this->m_ppos->y = posOrigin.y + fData + (m_size.y * 0.5f);
			}
			bJudg = true;
		}
		//Rayの判定圏内じゃなかったらジャンプできない
		else
		{
			bJudg = false;
		}
	}
	//Rayに判定がなかったらジャンプできない
	else
	{
		bJudg = false;
	}

	//配列を空にしておく
	vDistance.clear();

	// 判定フラグを返す
	return bJudg;
}
//======================================================================================================================
// レイの判定 始点と終点を設定して距離を返す
//======================================================================================================================
bool CCollision::RayCollisionGetLength(D3DXVECTOR3 posOrigin,D3DXVECTOR3 posEndPoint, float &fLength)
{
	// 地形判定 変数宣言
	BOOL				bHitFlag = false;			// 判定が出たかのフラグ
	bool				bJudg = false;				// 判定が出たかのフラグ
	float				fLandDistance = 0;			// 距離
	DWORD				dwHitIndex = -1;			// インデックス
	float				fHitU = 0;					// U
	float				fHitV = 0;					// V
	D3DXMATRIX			invmat;						// 逆行列を格納する変数
	D3DXVECTOR3			direction;					// 変換後の位置、方向を格納する変数：
	std::vector<float>	vDistance;					// 長さの配列保存

	//マップ情報取得
	CMap *pMap = CManager::GetBaseMode()->GetMap();

	//nullcheck
	if (!pMap)
	{
		//nullだったらリターン
		return false;
	}

	// マップモデルの最大数分繰り返す
	for (int nCnt = 0; nCnt < pMap->GetMaxModel(); nCnt++)
	{
		//初期化
		bHitFlag = false;

		//	逆行列の取得
		D3DXMatrixInverse(&invmat, NULL, pMap->GetModel(nCnt)->GetMatrix());
		//	逆行列を使用し、レイ始点情報を変換　位置と向きで変換する関数が異なるので要注意
		D3DXVec3TransformCoord(&posOrigin, &posOrigin, &invmat);
		//	レイ終点情報を変換
		D3DXVec3TransformCoord(&posEndPoint, &posEndPoint, &invmat);
		//	レイ方向情報を変換
		D3DXVec3Normalize(&direction, &(posEndPoint - posOrigin));
		//Rayを飛ばす
		D3DXIntersect(pMap->GetMesh(nCnt), &posOrigin, &direction, &bHitFlag, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);

		//なんかしらに当たっていた時
		if (bHitFlag)
		{
			//長さの保存追加
			vDistance.emplace_back(fLandDistance * 0.5f);
		}

	}
	//Rayのヒットした物があったとき
	if (!vDistance.empty())
	{
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fLength)
			{
				//比較対象が小さかったら代入
				fLength = vDistance[nCnt];
				bJudg = true;
			}
		}
	}

	//配列を空にしておく
	vDistance.clear();

	// 判定フラグを返す
	return bJudg;
}


bool CCollision::RayFloorCollision(CMap * pMap, D3DXMATRIX * pMat, D3DXVECTOR3 pdirection,D3DXVECTOR3 ppos)
{
	// 地形判定 変数宣言
	BOOL				bHitFlag = false;			// 判定が出たかのフラグ
	bool				bJudg = false;				// 判定が出たかのフラグ
	float				fLandDistance = 0;			// 距離
	DWORD				dwHitIndex = -1;			// インデックス
	float				fHitU = 0;					// U
	float				fHitV = 0;					// V
	D3DXMATRIX			invmat;						// 逆行列を格納する変数
	D3DXVECTOR3			m_posAfter;					// 逆行列で出した終点情報を格納する
	D3DXVECTOR3			m_posBefore;				// 終点情報を格納する
	D3DXVECTOR3			direction;					// 変換後の位置、方向を格納する変数：
	std::vector<float>	vDistance;					// 長さの配列保存
	float				fData = 0.0f;				// データ

													// マップモデルの最大数分繰り返す
	for (int nCnt = 0; nCnt < pMap->GetMaxModel(); nCnt++)
	{
		//	逆行列の取得
		D3DXMatrixInverse(&invmat, NULL, pMap->GetModel(nCnt)->GetMatrix());
		//	逆行列を使用し、レイ始点情報を変換　位置と向きで変換する関数が異なるので要注意
		D3DXVec3TransformCoord(&m_posBefore, &D3DXVECTOR3(ppos.x, pMat->_42, ppos.z), &invmat);
		//	レイ終点情報を変換
		D3DXVec3TransformCoord(&m_posAfter, &D3DXVECTOR3(ppos.x ,ppos.y+ pdirection.y, ppos.z), &invmat);
		//	レイ方向情報を変換
		D3DXVec3Normalize(&direction, &(m_posAfter - m_posBefore));
		//Rayを飛ばす
		D3DXIntersect(pMap->GetMesh(nCnt), &m_posBefore, &direction, &bHitFlag, &dwHitIndex, &fHitU, &fHitV, &fLandDistance, NULL, NULL);
		if (bHitFlag == TRUE)
		{
			//長さの保存追加
			vDistance.emplace_back(fLandDistance);
		}
		else
		{
		}
	}
	//Rayのヒットした物があったとき
	if (!vDistance.empty())
	{
		//最初の比較対象
		fData = vDistance[0];
		for (unsigned int nCnt = 0; vDistance.size() > nCnt; nCnt++)
		{
			if (vDistance[nCnt] < fData)
			{
				//比較対象が小さかったら代入
				fData = vDistance[nCnt];
			}
		}
		if (fData < RAY_FIRST_POINT+30)//Rayの長さの指定条件
		{
			bJudg = true;
		}
		//Rayの判定圏内じゃなかったらジャンプできない
		else
		{
			bJudg = false;
		}
	}
	//Rayに判定がなかったらジャンプできない
	else
	{
		bJudg = false;
	}
	//配列を空にしておく
	vDistance.clear();

	// 判定フラグを返す
	return bJudg;
}
