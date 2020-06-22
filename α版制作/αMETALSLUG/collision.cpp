//=============================================================================
//
// Collision処理の説明[calculation.cpp]
// Author : Fujiwara Masato
//
//=============================================================================

//=============================================================================
//
// インクルードファイル
//
//=============================================================================
#include "Collision.h"
#ifdef _DEBUG
#include "debugcollision.h"
#endif // _DEBUG

//=============================================================================
//
// マクロ定義
//
//=============================================================================

//=============================================================================
//
// 静的変数
//
//=============================================================================

// ----------------------------------------
// コンストラクタ
// ----------------------------------------
CCollision::CCollision()
{
	m_objtype			= OBJTYPE_PLAYERBULLET;				// タイプの初期化
	m_Collisiontype		= COLLISIONTYPE_NORMAL;				// 当たり判定の種類
	m_ppos				= nullptr;							// 位置情報
	m_posOld			= nullptr;							// 前回の位置情報
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// サイズ情報
	m_pmove				= nullptr;							// 移動情報
	m_Debugcollision	= nullptr;							// デバッグ用当たり判定のポインタ
	m_bHitFlag			= false;							// 当たっているかどうか
	m_pCollision		= nullptr;							// 当たり判定のポインタ
}

// ----------------------------------------
// デストラクタ
// ----------------------------------------
CCollision::~CCollision()
{
}

// ----------------------------------------
// 初期化処理
// ----------------------------------------
void CCollision::Init(void)
{
}

// ----------------------------------------
// 終了処理
// ----------------------------------------
void CCollision::Uninit(void)
{
}

// ----------------------------------------
// 更新処理
// ----------------------------------------
void CCollision::Update(void)
{
//#ifdef _DEBUG
//	if (m_Debugcollision != nullptr)
//	{
//		m_Debugcollision->SetPos(m_ppos);
//	}
//#endif // _DEBUG
}

// ----------------------------------------
// 当たり判定削除
// ----------------------------------------
void CCollision::ReleaseCollision(CCollision *pColl)
{
#ifdef _DEBUG
	if (pColl->m_pCollision->m_Debugcollision != nullptr)
	{
		// デバック用判定削除
		pColl->m_pCollision->m_Debugcollision->DeleteDeCollision(pColl->m_pCollision->m_Debugcollision);
	}
#endif // _DEBUG

	if (pColl->m_pCollision == pColl)
	{
		delete pColl->m_pCollision;
		pColl->m_pCollision = nullptr;
	}
}

// ----------------------------------------
// 生成処理
// ----------------------------------------
CCollision * CCollision::Create(void)
{
	// 変数宣言
	CCollision * pCollision;	// 当たり判定
	// メモリ確保
	pCollision = new CCollision;
	// 初期化
	pCollision->Init();
	// ポインタ情報を代入
	pCollision->m_pCollision = pCollision;
	return pCollision;
}

// ----------------------------------------
// デバッグ用当たり判定生成処理
// ----------------------------------------
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

// ----------------------------------------
// 位置設定処理
// ----------------------------------------
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

// ----------------------------------------
// 1フレーム前の位置設定処理
// ----------------------------------------
void CCollision::SetPosOld(D3DXVECTOR3 * posold)
{
	m_posOld = posold;
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CCollision::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
}

// ----------------------------------------
// 2dサイズ設定処理
// ----------------------------------------
void CCollision::SetSize2D(D3DXVECTOR3 size)
{
	m_size = size;
}

// ----------------------------------------
// 移動設定処理
// ----------------------------------------
void CCollision::SetMove(D3DXVECTOR3 * move)
{
	m_pmove = move;
}

// ----------------------------------------
// タイプ設定処理
// ----------------------------------------
void CCollision::SetType(OBJTYPE type)
{
	m_objtype = type;
}

// ----------------------------------------
// 箱型の当たり判定処理
// ----------------------------------------
bool CCollision::Collision(OBJTYPE objtype)
{
	//// 変数宣言
	//CCollision * pCollision = NULL;
	//CCollision *pCollisionNext;	// 次のシーン
	//// 先頭ポイントを格納
	//pCollision = m_pTop;

	//while (pCollision != NULL)
	//{
	//	// 次のポインタを代入
	//	pCollisionNext = pCollision->m_pNext;

	//	if (pCollision != this && pCollision->m_objtype == objtype)
	//	{
	//		// 素材のY範囲
	//		if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
	//			this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
	//		{
	//			// 素材のZ範囲
	//			if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
	//				this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
	//			{
	//				// 当たり判定(左)
	//				if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
	//					this->m_posOld.x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
	//				{
	//					// 素材状の左に
	//					//this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;

	//					// 移動量の初期化
	//					//this->m_pmove->x = 0.0f;

	//					// オブジェクトに当たったフラグ
	//					m_bHitFlag = true;
	//				}

	//				// 当たり判定(右)
	//				else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f&&
	//					m_posOld.x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	//				{
	//					// 素材状の左に
	//					//this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
	//					// 移動量の初期化
	//					//this->m_pmove->x = 0.0f;
	//					// オブジェクトに当たったフラグ
	//					m_bHitFlag = true;
	//				}
	//			}

	//			// 素材のX範囲
	//			if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
	//				this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	//			{
	//				// 当たり判定(手前)
	//				if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
	//					m_posOld.z + this->m_size.z * 0.5f <= pCollision->m_ppos->z - pCollision->m_size.z * 0.5f)
	//				{
	//					// 素材状の左に
	//					//this->m_ppos->z = pCollision->m_ppos->z - pCollision->m_size.z * 0.5f - this->m_size.z * 0.5f;
	//					// 移動量の初期化
	//					//this->m_pmove->z = 0.0f;
	//					// オブジェクトに当たったフラグ
	//					m_bHitFlag = true;
	//				}

	//				// 当たり判定(奥)
	//				else if (this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f&&
	//					m_posOld.z - this->m_size.z * 0.5f >= pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
	//				{
	//					// 素材状の左に
	//					//this->m_ppos->z = pCollision->m_ppos->z +
	//						//pCollision->m_size.z * 0.5f +
	//						//this->m_size.z * 0.5f + 0.1f;
	//					// 移動量の初期化
	//					//this->m_pmove->z = 0.0f;
	//					// オブジェクトに当たったフラグ
	//					m_bHitFlag = true;
	//				}
	//			}
	//		}

	//		// 素材のZ範囲
	//		if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
	//			this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
	//		{
	//			// 素材のX範囲
	//			if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
	//				this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
	//			{
	//				// 当たり判定(下)
	//				if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
	//					m_posOld.y + this->m_size.y * 0.5f <= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f)
	//				{
	//					// 素材状の左に
	//					//this->m_ppos->y = this->m_posOld.y;
	//					// 移動量の初期化
	//					//this->m_pmove->y = 0.0f;
	//					// オブジェクトに当たったフラグ
	//					m_bHitFlag = true;
	//				}

	//				// 当たり判定(上)
	//				else if (this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
	//					m_posOld.y - this->m_size.y * 0.5f >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
	//				{
	//					// 素材状の左に
	//					//this->m_ppos->y = pCollision->m_ppos->y + pCollision->m_size.y * 0.5f + this->m_size.y * 0.5f;
	//					// 移動量の初期化
	//					//this->m_pmove->y = 0.0f;
	//					// オブジェクトに当たったフラグ
	//					m_bHitFlag = true;
	//				}
	//			}
	//		}
	//	}
	//	pCollision = pCollisionNext;
	//}
	// 当たっているかいないかを返す
	return m_bHitFlag;
}

// ----------------------------------------
// 板型の当たり判定処理
// ----------------------------------------
bool CCollision::Collision2D(CCollision *pCollision)
{
	// 変数宣言

	if (pCollision != nullptr)
	{
		// X Yの範囲
		if (this->m_ppos->y + this->m_size.y * 0.5f >= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
			this->m_ppos->y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// オブジェクトに当たったフラグ
			m_bHitFlag = true;
		}

		else
		{
			m_bHitFlag = false;
		}
	}

	// 当たっているかいないかを返す
	return m_bHitFlag;
}

// ----------------------------------------
// キャラクター用板型の当たり判定処理
// ----------------------------------------
bool CCollision::CharCollision2D(CCollision * pCollision)
{
	if (pCollision != nullptr)
	{
		// X Yの範囲
		if (this->m_ppos->y + this->m_size.y >= pCollision->m_ppos->y&&
			this->m_ppos->y <= pCollision->m_ppos->y + pCollision->m_size.y&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
		{
			// オブジェクトに当たったフラグ
			m_bHitFlag = true;
		}

		else
		{
			m_bHitFlag = false;
		}
	}

	// 当たっているかいないかを返す
	return m_bHitFlag;
}

// ----------------------------------------
// キャラクターとアイテム、弾の判定
// ----------------------------------------
bool CCollision::OtherCollision2D(CCollision * pCollision)
{
	if (pCollision != nullptr)
	{
		// X Yの範囲
		if (this->m_ppos->y + this->m_size.y * 0.5f >= pCollision->m_ppos->y&&
			this->m_ppos->y - this->m_size.y * 0.5f <= pCollision->m_ppos->y + pCollision->m_size.y&&
			this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
			this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)

		{
			// オブジェクトに当たったフラグ
			m_bHitFlag = true;
		}

		else
		{
			m_bHitFlag = false;
		}
	}

	// 当たっているかいないかを返す
	return m_bHitFlag;
}
