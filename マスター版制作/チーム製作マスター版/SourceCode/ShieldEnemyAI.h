#pragma once
//=============================================================================
// AI処理 [ShieldEnemyAI.h]
//=============================================================================
#ifndef _SHIELDENEMYAI_H_
#define _SHIELDENEMYAI_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "BaseAI.h"
class CWeakEnemy;
class CGun;
class CCollision;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CShieldEnemyAI :public CBaseAI
{
public:
	typedef enum
	{
		AI_NONE = 0,			//何もしない
		AI_STOP,				//止まる
		AI_STAND,				//立つ
		AI_WALK_LEFT,			//左移動
		AI_WALK_RIGHT,			//右移動
		AI_ATTACK,				//攻撃
		AI_MAX					//行動のマックス
	}AI_STATE;

	CShieldEnemyAI();
	~CShieldEnemyAI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void AttackUpdate(void);
	void Draw(void);
	void DebugInfo(void);
	static CShieldEnemyAI* CreateAI(CWeakEnemy *pEnemy);
	AI_STATE GetAIType(void);
	CCollision *GetCollision() { return m_pCollision; };			// 当たり判定のポインタ取得

private:
	CWeakEnemy *pEnemyPass;			//敵の情報の格納用
	CGun	*m_pGun;			//ガンクラスのポインタ
	AI_STATE m_AItype;			//行動の種類
	AI_STATE m_AItypeOld;		//前の行動の格納
	D3DXVECTOR3 m_Distance;
	float m_fDistance;
	int m_recast;
	int m_castcount;
	bool m_bAttack;
	bool m_bKnifeAttack;
	bool m_bReStartFlag;
	int m_random;
	CCollision				*m_pCollision;							//当たり判定のポインタ
};

#endif
