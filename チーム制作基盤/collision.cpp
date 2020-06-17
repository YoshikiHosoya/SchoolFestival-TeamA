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
CCollision * CCollision::m_pTop = NULL;	// 先頭オブジェクトへのポインタ
CCollision * CCollision::m_pCur = NULL;	// 現在オブジェクトへのポインタ

// ----------------------------------------
// コンストラクタ
// ----------------------------------------
CCollision::CCollision()
{
	m_objtype			= OBJTYPE_PLAYER;					// タイプの初期化
	m_ppos				= NULL;								// 位置情報
	m_posOld			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 前回の位置情報
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// サイズ情報
	m_pmove				= NULL;								// 移動情報
	m_Debugcollision	= NULL;								// デバッグ用当たり判定のポインタ
	m_bHitFlag			= false;							// 当たっているかどうか

	/* 現在のポインタ */
	if (m_pCur != NULL)
	{
		// 前のオブジェクトのポインタ
		this->m_pPrey = m_pCur;
		// 次のオブジェクトのポインタ
		m_pCur->m_pNext = this;
	}
	// 現在のポインタ
	m_pCur = this;

	// 先頭オブジェクトのポインタ
	if (m_pTop == NULL)
	{
		m_pTop = this;
	}
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
	// オブジェクトタイプがプレイヤーだったら当たり判定を持たせる
	m_posOld = *m_ppos;
}

// ----------------------------------------
// 当たり判定全体の更新
// ----------------------------------------
void CCollision::UpdateAll(void)
{
	// 変数宣言
	CCollision * pCollision = NULL;
	CCollision *pCollisionNext = NULL;	// 次のシーン
	// 先頭ポイントを格納
	pCollision = m_pTop;
	while (pCollision != NULL)
	{
		// 次のポインタを代入
		pCollisionNext = pCollision->m_pNext;
		pCollision->Update();
		pCollision = pCollisionNext;
	}
}

// ----------------------------------------
// 当たり判定削除
// ----------------------------------------
void CCollision::Delete(CCollision *pColl)
{
	// 変数宣言
	CCollision * pCollision;	// シーン
	CCollision *pCollisionNext;	// 次のシーン
	// 先頭ポイントを格納
	pCollision = m_pTop;
	while (pCollision != NULL)
	{
		// 次のポインタを代入
		pCollisionNext = pCollision->m_pNext;
		if (pColl == pCollision)
		{
			// 先頭と現在のオブジェクトのポインタが同じ場合
			if (pCollision == m_pTop && pCollision == m_pCur)
			{
				m_pTop = NULL;
				m_pCur = NULL;
			}
			// 先頭オブジェクトのポインタの変更
			else if (pCollision == m_pTop)
			{
				m_pTop = pCollisionNext;
				m_pTop->m_pPrey = NULL;
			}
			// 現在のオブジェクトのポインタの変更
			else if (pCollision == m_pCur)
			{
				m_pCur = pCollision->m_pPrey;
				m_pCur->m_pNext = NULL;
			}
			// 間のコネクト
			else
			{
				// 前回の次の情報を代入
				pCollision->m_pPrey->m_pNext = pCollisionNext;
				// 次の前回の情報を代入
				pCollisionNext->m_pPrey = pCollision->m_pPrey;
			}
			// レイヤーダウン
			delete pCollision;
			pCollision = NULL;
		}
		pCollision = pCollisionNext;
	}
}

// ----------------------------------------
// 当たり判定全部削除
// ----------------------------------------
void CCollision::DeleteAll(void)
{
	// 変数宣言
	CCollision * pCollision;	// シーン
	CCollision *pCollisionNext;	// 次のシーン

	// 先頭ポイントを格納
	pCollision = m_pTop;
	while (pCollision != NULL)
	{
		// 次のポインタを代入
		pCollisionNext = pCollision->m_pNext;
		// 先頭と現在のオブジェクトのポインタが同じ場合
		if (pCollision == m_pTop && pCollision == m_pCur)
		{
			m_pTop = NULL;
			m_pCur = NULL;
		}
		// 先頭オブジェクトのポインタの変更
		else if (pCollision == m_pTop)
		{
			m_pTop = pCollisionNext;
			m_pTop->m_pPrey = NULL;
		}
		// 現在のオブジェクトのポインタの変更
		else if (pCollision == m_pCur)
		{
			m_pCur = pCollision->m_pPrey;
			m_pCur->m_pNext = NULL;
		}
		// 間のコネクト
		else
		{
			// 前回の次の情報を代入
			pCollision->m_pPrey->m_pNext = pCollisionNext;
			// 次の前回の情報を代入
			pCollisionNext->m_pPrey = pCollision->m_pPrey;
		}
		// レイヤーダウン
		delete pCollision;
		pCollision = NULL;
		pCollision = pCollisionNext;
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
	return pCollision;
}

// ----------------------------------------
// 位置設定処理
// ----------------------------------------
void CCollision::SetPos(D3DXVECTOR3 * pos)
{
	m_ppos = pos;
	m_posOld = *pos;

#ifdef _DEBUG
	if (m_Debugcollision != NULL)
	{
		m_Debugcollision->SetPos(m_ppos);
	}
#endif // _DEBUG
}

// ----------------------------------------
// サイズ設定処理
// ----------------------------------------
void CCollision::SetSize(D3DXVECTOR3 size)
{
	m_size = size;
#ifdef _DEBUG
	// デバッグ用のラインを生成
	m_Debugcollision = CDebugcollision::Create(m_ppos, &m_size, CDebugcollision::COLLISIONTYPE_BOX);
#endif // _DEBUG
}

// ----------------------------------------
// 2dサイズ設定処理
// ----------------------------------------
void CCollision::SetSize2D(D3DXVECTOR3 size)
{
	m_size = size;
#ifdef _DEBUG
	CDebugcollision::Create(m_ppos, &m_size, CDebugcollision::COLLISIONTYPE_BOARD);
#endif
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
	// 変数宣言
	CCollision * pCollision = NULL;
	CCollision *pCollisionNext;	// 次のシーン
	// 先頭ポイントを格納
	pCollision = m_pTop;

	while (pCollision != NULL)
	{
		// 次のポインタを代入
		pCollisionNext = pCollision->m_pNext;

		if (pCollision != this && pCollision->m_objtype == objtype)
		{
			// 素材のY範囲
			if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
				this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
			{
				// 素材のZ範囲
				if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
					this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
				{
					// 当たり判定(左)
					if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
						this->m_posOld.x + this->m_size.x * 0.5f <= pCollision->m_ppos->x - pCollision->m_size.x * 0.5f)
					{
						// 素材状の左に
						this->m_ppos->x = pCollision->m_ppos->x - pCollision->m_size.x * 0.5f - this->m_size.x * 0.5f;

						// 移動量の初期化
						this->m_pmove->x = 0.0f;

						// オブジェクトに当たったフラグ
						m_bHitFlag = true;
					}

					// 当たり判定(右)
					else if (this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f&&
						m_posOld.x - this->m_size.x * 0.5f >= pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
					{
						// 素材状の左に
						this->m_ppos->x = pCollision->m_ppos->x + pCollision->m_size.x * 0.5f + this->m_size.x * 0.5f;
						// 移動量の初期化
						this->m_pmove->x = 0.0f;
						// オブジェクトに当たったフラグ
						m_bHitFlag = true;
					}
				}

				// 素材のX範囲
				if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
					this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
				{
					// 当たり判定(手前)
					if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
						m_posOld.z + this->m_size.z * 0.5f <= pCollision->m_ppos->z - pCollision->m_size.z * 0.5f)
					{
						// 素材状の左に
						this->m_ppos->z = pCollision->m_ppos->z - pCollision->m_size.z * 0.5f - this->m_size.z * 0.5f;
						// 移動量の初期化
						this->m_pmove->z = 0.0f;
						// オブジェクトに当たったフラグ
						m_bHitFlag = true;
					}

					// 当たり判定(奥)
					else if (this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f&&
						m_posOld.z - this->m_size.z * 0.5f >= pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
					{
						// 素材状の左に
						this->m_ppos->z = pCollision->m_ppos->z +
							pCollision->m_size.z * 0.5f +
							this->m_size.z * 0.5f + 0.1f;
						// 移動量の初期化
						this->m_pmove->z = 0.0f;
						// オブジェクトに当たったフラグ
						m_bHitFlag = true;
					}
				}
			}

			// 素材のZ範囲
			if (this->m_ppos->z + this->m_size.z * 0.5f > pCollision->m_ppos->z - pCollision->m_size.z * 0.5f&&
				this->m_ppos->z - this->m_size.z * 0.5f < pCollision->m_ppos->z + pCollision->m_size.z * 0.5f)
			{
				// 素材のX範囲
				if (this->m_ppos->x + this->m_size.x * 0.5f > pCollision->m_ppos->x - pCollision->m_size.x * 0.5f&&
					this->m_ppos->x - this->m_size.x * 0.5f < pCollision->m_ppos->x + pCollision->m_size.x * 0.5f)
				{
					// 当たり判定(下)
					if (this->m_ppos->y + this->m_size.y * 0.5f > pCollision->m_ppos->y - pCollision->m_size.y * 0.5f&&
						m_posOld.y + this->m_size.y * 0.5f <= pCollision->m_ppos->y - pCollision->m_size.y * 0.5f)
					{
						// 素材状の左に
						this->m_ppos->y = this->m_posOld.y;
						// 移動量の初期化
						this->m_pmove->y = 0.0f;
						// オブジェクトに当たったフラグ
						m_bHitFlag = true;
					}

					// 当たり判定(上)
					else if (this->m_ppos->y - this->m_size.y * 0.5f < pCollision->m_ppos->y + pCollision->m_size.y * 0.5f&&
						m_posOld.y - this->m_size.y * 0.5f >= pCollision->m_ppos->y + pCollision->m_size.y * 0.5f)
					{
						// 素材状の左に
						this->m_ppos->y = pCollision->m_ppos->y + pCollision->m_size.y * 0.5f + this->m_size.y * 0.5f;
						// 移動量の初期化
						this->m_pmove->y = 0.0f;
						// オブジェクトに当たったフラグ
						m_bHitFlag = true;
					}
				}
			}
		}
		pCollision = pCollisionNext;
	}
	// 当たっているかいないかを返す
	return m_bHitFlag;
}
