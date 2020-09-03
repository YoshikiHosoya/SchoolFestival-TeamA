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
class CMap;
class CPrisoner;
class CEnemy;
class CPlayertank;
class CBattlePlane;
class CPlayer;

//=============================================================================
//
// クラス
//
//=============================================================================
class CCollision
{
public:
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
	void ShowDebugInfo();

	/* 静的メンバ関数 */
	static CCollision * Create();

	/* メンバ関数 */

	void SetPos(D3DXVECTOR3 *pos);													// 座標の設定
	void SetPosOld(D3DXVECTOR3 *posold);											// 1フレーム前の座標の設定
	void SetSize(D3DXVECTOR3 size);													// サイズの設定
	void SetSize2D(D3DXVECTOR3 size);												// 2D用サイズの設定
	void SetMove(D3DXVECTOR3 *move);												// 移動量の設定
	void SetTime(int nTime) { m_nCollisionTime = nTime; };							// 継続時間の設定
	void SetCanCollision(bool bCollision) { m_bCanCollision = bCollision; };		//当たり判定可能かどうか設定
	void SetGameObject(CGameObject *GameObject) { m_pGameObject = GameObject; };	// ゲームオブジェクト( タグ )の設定
	bool GetCanCollison() { return m_bCanCollision; };								// 当たり判定できるかどうか取得
	int	 GetTime() { return m_nCollisionTime; };									// 継続時間の設定
	void SetHeight(float height);													// Rayの高さ設定
	bool Collision2D(CCollision *pCollision);										// 板型の当たり判定
	bool CharCollision2D(CCollision *pCollision);									// キャラクター用板型の当たり判定
	bool OtherCollision2D(CCollision *pCollision);									// 板型の当たり判定
	bool BlockCollision2D(CCollision *pCollision);									// 板型ブロックの当たり判定
	bool BlockNotUpsideCollision2D(CCollision *pCollision);							// 板型ブロックの当たり判定

	// 代用
	bool BlockCollision2D_Bottom(CCollision *pCollision);
	bool BoxCollision2D_Character(CCollision *pCollision);// キャラクター同士

	bool RayBlockCollision(CMap *pMap, D3DXMATRIX *pMat);				// Rayの判定 キャラクター
	bool RayCollision(CMap *pMap);										// Rayの判定 弾など
	bool RayFloorCollision(CMap *pMap, D3DXMATRIX *pMat,D3DXVECTOR3 pdirection,D3DXVECTOR3 ppos);// Rayの判定 前方の床

	void DeCollisionCreate(COLLISIONTYPE collisiontype)	;				// デバッグ用当たり判定の生成
	bool ForPlayerBulletCollision(int nEnemyDamage,
							int nObstacleDamage,
							bool Penetration);							// プレイヤーの弾が行う判定 ダメージ量 貫通するかどうか

	bool ForEnemyCollision(int nPlayerDamage,
		int nPlayerTankDamage,
		bool Penetration);												// エネミーの弾が行う判定 ダメージ量 貫通するかどうか

	bool ForPlayer_EnemyCollision(bool Penetration);					// プレイヤーとエネミーが行う判定 ダメージ量 貫通するかどうか

	bool ForPlayer_ObstacleCollision();									// プレイヤーと障害物が行う判定 ダメージ量 貫通するかどうか

	bool ForPlayer_PrisonerCollision(bool Penetration);					// プレイヤーと捕虜が行う判定 ダメージ量 貫通するかどうか

	bool ForPlayer_ItemCollision(TAG Tag);				// プレイヤーと捕虜が行う判定 ダメージ量 貫通するかどうか

	CPrisoner		*ForPlayer_PrisonerCollision();						// プレイヤーと捕虜の接触判定 捕虜の状態変更
	CEnemy			*ForPlayer_EnemyCollision();						// プレイヤーとエネミーの接触判定
	CPlayertank		*ForPlayer_TankCollision();							// プレイヤーと戦車の接触判定
	CBattlePlane	*ForPlayer_PlaneCollision();						// プレイヤーと戦闘機の接触判定

	bool ForPlayer_VehicleCollision(CCollision * pCollision);	// プレイヤーと乗り物が行う判定
	void *ForPlayer_VehicleCollision();							// プレイヤーと乗り物が行う判定
	bool ForVehicleCollision();									// 乗り物が行う判定
	bool ForTankCollision();									// 戦車が行う判定

	void ForBossOne_PlayerCollision();
	bool BossOne_PlayerCollision();								// ボスが行う判定

	bool KnifeCollision(D3DXVECTOR3 Knifepos,
		CCollision *pCollision);						// ナイフとキャラクターの判定

	bool VehicleCollision(CCollision *pCollision);		// プレイヤーが乗り物に乗る時の判定

protected:
private:
	/* メンバ変数 */
	COLLISIONTYPE		m_Collisiontype;				// 当たり判定のタイプ
	D3DXVECTOR3			*m_ppos;						// 位置情報のポインタ
	D3DXVECTOR3			*m_posOld;						// 前回の位置情報
	D3DXVECTOR3			m_size;							// サイズ情報
	D3DXVECTOR3			*m_pmove;						// 移動情報のポインタ
	CDebugcollision		*m_Debugcollision;				// デバッグ用当たり判定のポインタ
	bool				m_bDeadFlag;					// 死亡フラグ
	bool				m_bCanCollision;				// 判定をとるかどうか
	int					m_nCollisionTime;				// 当たり判定が持続する時間
	float				m_fHeight;

	CGameObject			*m_pGameObject;					// ゲームオブジェクト( タグ )のポインタ
};

#endif