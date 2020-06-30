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
		OBJTYPE_PRISONER,					// 捕虜
		OBJTYPE_ITEM,						// アイテム
		OBJTYPE_OBSTACLE,					// 障害物
		OBJTYPE_OTHER,						// その他
		OBJTYPE_MAX
	} OBJTYPE;

	// 当たり判定の主な種類
	typedef enum
	{
		// 範囲判定
		COLLISIONTYPE_NORMAL = 0,			// 中心点を原点にする判定
		COLLISIONTYPE_CHARACTER,			// 足元を原点にする判定
		COLLISIONTYPE_OTHER,				// 中心点を原点とするオブジェクトと足元を原点にするオブジェクトで判定
		// ブロック判定
		COLLISIONTYPE_BLOCK,				// 中心点を原点とするブロックと足元が原点のオブジェクトで判定
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;



	/* メンバ関数 */
	CCollision();
	~CCollision();
	void Init(void);
	void Uninit(void);
	void Update(void);

	/* 静的メンバ関数 */
	static void ReleaseCollision(CCollision *pColl);	// 当たり判定削除
	static CCollision * Create(void);					// 当たり判定の生成

	/* メンバ関数 */
	void SetPos(D3DXVECTOR3 *pos);						// 座標の設定
	void SetPosOld(D3DXVECTOR3 *posold);				// 1フレーム前の座標の設定
	void SetSize(D3DXVECTOR3 size);						// サイズの設定
	void SetSize2D(D3DXVECTOR3 size);					// 2D用サイズの設定
	void SetMove(D3DXVECTOR3 *move);					// 移動量の設定
	void SetType(OBJTYPE type);							// タイプの設定
	bool Collision(OBJTYPE objtype);					// 箱型の当たり判定
	bool Collision2D(CCollision *pCollision);			// 板型の当たり判定
	bool CharCollision2D(CCollision *pCollision);		// キャラクター用板型の当たり判定
	bool OtherCollision2D(CCollision *pCollision);		// 板型の当たり判定
	bool BlockCollision2D(CCollision *pCollision);		// 板型ブロックの当たり判定
	OBJTYPE GetObjtype() {return m_objtype;};			// 誰の当たり判定なのかを返す
	void DeCollisionCreate(COLLISIONTYPE collisiontype);// デバッグ用当たり判定の生成

protected:
private:
	/* メンバ変数 */
	OBJTYPE				m_objtype;						// タイプ
	COLLISIONTYPE		m_Collisiontype;				// 当たり判定のタイプ
	D3DXVECTOR3			*m_ppos;						// 位置情報のポインタ
	D3DXVECTOR3			*m_posOld;						// 前回の位置情報
	D3DXVECTOR3			m_size;							// サイズ情報
	D3DXVECTOR3			*m_pmove;						// 移動情報のポインタ
	CDebugcollision		*m_Debugcollision;				// デバッグ用当たり判定のポインタ
	bool				m_bDeadFlag;					// 死亡フラグ
	bool				m_bHitFlag;						// 当たり判定に触れかどうか
	CCollision			*m_pCollision;					// 当たり判定のポインタ
};

#endif