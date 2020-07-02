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
class CEnemy;
class CGun;

//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CEnemyAI
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
	static CEnemyAI* CreateAI(void);
	AI_STATE GetAIType(void);
private:
	CEnemy *pEnemyPass;			//敵の情報の格納用？
	CGun	*m_pGun;			//ガンクラスのポインタ
	AI_STATE m_AItype;			//行動の種類
	int m_cast;
	bool m_bShot;
};

#endif
