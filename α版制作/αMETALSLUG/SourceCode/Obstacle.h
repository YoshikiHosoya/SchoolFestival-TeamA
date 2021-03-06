// =====================================================================================================================================================================
//
// 障害物の処理 [Obstacle.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "model.h"

// =====================================================================================================================================================================
// 障害物の情報
// =====================================================================================================================================================================
typedef struct
{
	D3DXVECTOR3			pos;			// 座標
	int					nLife;			// 体力
	D3DXVECTOR3			CollisionSize;	// 大きさ // 当たり判定に使うサイズ
}OBSTACLE_PARAM;

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
// =====================================================================================================================================================================
// 障害物クラス
// =====================================================================================================================================================================
class CObstacle : public CModel
{
public:

	// 障害物の種類
	enum OBSTACLE_TYPE
	{
		TYPE_BOX = 0,								// 木箱
		TYPE_BARREL,								// 樽
		TYPE_TREE,									// 木
		TYPE_CHEST,									// 金庫
		TYPE_SANDBAGS,								// 土嚢
		TYPE_MAX,									// 最大数
	};

	CObstacle(OBJ_TYPE type);						// コンストラクタ
	~CObstacle();									// デストラクタ

													/* メンバ関数 */
	virtual HRESULT			Init();					// 初期化
	virtual void			Uninit();				// 終了
	virtual void			Update();				// 更新
	virtual void			Draw();					// 描画
	virtual void			DebugInfo();			//デバッグ

	/* 静的メンバ関数 */
	static	CObstacle		*Create();																// 障害物の生成

	/* メンバ関数 */
	OBSTACLE_TYPE			&GetObstacleType()					{ return m_ObstacleType; };			// 障害物の種類の取得
	void					SetObstacleType(OBSTACLE_TYPE type) { m_ObstacleType = type; };			// 障害物の種類の設定
	OBSTACLE_PARAM			*GetObstacleParam(int nCnt)			{ return &m_ObstacleParam[nCnt]; };	// 弾のパラメーターの構造体の取得
	void					SetObstacleParam(CObstacle::OBSTACLE_TYPE type)
							{m_nLife = m_ObstacleParam[type].nLife;
							m_pos = m_ObstacleParam[type].pos;};									// 障害物の情報設定
	int						GetLife() { return m_nLife; };											// 体力の取得
	void					SetLife(int nLife) { m_nLife = nLife; };								// 体力の設定
	void					SetCollisionSize(D3DXVECTOR3 Size) { m_CollisionSize = Size; };			// 大きさの設定

	void					Hit(OBSTACLE_TYPE type, int nDamage);									// 障害物が壊されるときの処理
	void					Size(OBSTACLE_TYPE Type);												// 種類別に当たり判定の大きさを設定

private:
	/* メンバ関数*/
	void					CheckDie();																// 体力があるか確認
	void					AddDamage(int Damage);													// ダメージを加算する
	/* 静的メンバ変数 */
	static OBSTACLE_PARAM	m_ObstacleParam[CObstacle::TYPE_MAX];									// 弾のパラメーター
	/* メンバ変数 */
	OBSTACLE_TYPE			m_ObstacleType;															// 障害物の種類
	D3DXVECTOR3				m_pos;																	// 座標
	int						m_nLife;																// 体力
	D3DXVECTOR3				m_CollisionSize;														// 大きさ // 当たり判定に使うサイズ
};
#endif
