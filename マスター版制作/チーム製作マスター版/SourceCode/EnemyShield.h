#pragma once
//=============================================================================
// エネミーヘッダー [Enemy.h]
//=============================================================================
#ifndef _ENEMYSHIELD_H_
#define _ENEMYSHIELD_H_
#include "main.h"
#include "Scene.h"
#include "Enemy.h"
class CModel;
class CGun;
class CEnemyAI;
//レンダリングクラス
class CEnemyShield :public CEnemy
{
public:
	CEnemyShield(OBJ_TYPE type);
	~CEnemyShield();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void DebugInfo(void);
	static CEnemyShield *Create(void);
	bool DefaultMotion(void);
	virtual void DamageReaction();
	virtual void DeathReaction();
	virtual void StateChangeReaction();

private:
	void Move(float move, float fdest);
	bool m_Attack;									//攻撃時
	float m_Angle;
	CGun	*m_pGun;								// ガンクラスのポインタ
	CEnemyAI *m_pAI;
};
#endif