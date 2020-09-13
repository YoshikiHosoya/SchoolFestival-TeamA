#pragma once
//=============================================================================
// AI処理 [enemyAI.h]
//=============================================================================
#ifndef _ENEMYAI_H_
#define _ENEMYAI_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "BaseAI.h"
class CEnemy;
class CGun;
class CCollision;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CEnemyAI :public CBaseAI
{
public:
	typedef enum
	{
		AI_NONE = 0,			//何もしない
		AI_STOP,				//止まる
		AI_STAND,				//立つ
		AI_CROUCH,				//しゃがむ
		AI_WALK_LEFT,			//左移動
		AI_WALK_RIGHT,			//右移動
		AI_SHOT,				//射撃
		AI_GRENADE,				//グレネード
		AI_MAX					//
	}AI_STATE;

	CEnemyAI();
	~CEnemyAI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	static CEnemyAI* CreateAI(CEnemy *pEnemy);
	AI_STATE GetAIType(void);
	bool GetShot(void);
	CCollision *GetCollision() { return m_pCollision; };			// 当たり判定のポインタ取得

private:
	CEnemy *pEnemyPass;			//敵の情報の格納用
	CGun	*m_pGun;			//ガンクラスのポインタ
	AI_STATE m_AItype;			//行動の種類
	AI_STATE m_AItypeOld;		//前の行動の格納
	D3DXVECTOR3 m_Distance;
	float m_fDistance;
	int m_recast;
	int m_castcount;
	bool m_bShot;
	bool m_bReStartFlag;
	int m_random;
	bool m_bCrouch;

	CCollision				*m_pCollision;							//当たり判定のポインタ
};

#endif
