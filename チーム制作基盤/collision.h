//=============================================================================
//
// Collisionヘッダー処理の説明[collision.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _COLLISION_H_
#define _COLLISION_H_	 // ファイル名を基準を決める

//=============================================================================
//
// インクルードファイル
//
//=============================================================================
#include "main.h"

//=============================================================================
//
// マクロ定義
//
//=============================================================================

//=============================================================================
//
// 前方宣言
//
//=============================================================================
class CDebugcollision;

//=============================================================================
//
// クラス
//
//=============================================================================
class CCollision
{
public:
	// オブジェクトの種類
	typedef enum
	{
		OBJTYPE_PLAYERBULLET = 0,			// プレイヤー弾
		OBJTYPE_ENEMYBULLET,				// 敵弾
		OBJTYPE_PLAYER,						// プレイヤー
		OBJTYPE_ENEMY,						// エネミー
		OBJTYPE_ITEM,						// アイテム
		OBJTYPE_OTHER,						// その他
		OBJTYPE_MAX
	} OBJTYPE;

	/* メンバ関数 */
	CCollision();
	~CCollision();
	void Init(void);
	void Uninit(void);
	void Update(void);

	/* 静的メンバ関数 */
	static void UpdateAll(void);				// 当たり判定更新
	static void Delete(CCollision *pColl);		// 当たり判定削除
	static void DeleteAll(void);				// 全ての当たり判定削除
	static CCollision * Create(void);			// 当たり判定の生成

	/* メンバ関数 */
	void SetPos(D3DXVECTOR3 *pos);				// 座標の設定
	void SetSize(D3DXVECTOR3 size);				// サイズの設定
	void SetSize2D(D3DXVECTOR3 size);			// 2D用サイズの設定
	void SetMove(D3DXVECTOR3 *move);			// 移動量の設定
	void SetType(OBJTYPE type);					// タイプの設定
	bool Collision(OBJTYPE objtype);			// 箱型の当たり判定
	bool Collision2D(CCollision *pCollision);	// 板型の当たり判定
	bool GetHitFlag() {return m_bHitFlag;}		// 判定の結果を返す
	OBJTYPE GetObjtype() {return m_objtype;};	// 誰の当たり判定なのかを返す

protected:
private:
	/* メンバ変数 */
	OBJTYPE				m_objtype;				// タイプ
	D3DXVECTOR3			*m_ppos;				// 位置情報のポインタ
	D3DXVECTOR3			m_posOld;				// 前回の位置情報
	D3DXVECTOR3			m_size;					// サイズ情報
	D3DXVECTOR3			*m_pmove;				// 移動情報のポインタ
	static CCollision	*m_pTop;				// 先頭オブジェクトへのポインタ
	static CCollision	*m_pCur;				// 現在オブジェクトへのポインタ
	CCollision			*m_pNext;				// 次のオブジェクトへのポインタ
	CCollision			*m_pPrey;				// 前のオブジェクトへのポインタ
	CDebugcollision		*m_Debugcollision;		// デバッグ用当たり判定のポインタ
	bool				m_bDeadFlag;			// 死亡フラグ
	bool				m_bHitFlag;				// 当たり判定に触れかどうか
};

#endif