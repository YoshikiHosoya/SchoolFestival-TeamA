#pragma once
//=============================================================================
// ボスヘッダー [Boss.h]
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"
#include "Scene.h"
#include "Enemy.h"
class CModel;
class CGun;
class CBossAI;
//レンダリングクラス
class CBoss :public CEnemy
{
public:
	CBoss(OBJ_TYPE type);
	~CBoss();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	static CBoss *Create(void);
	bool DefaultMotion(void);
	void DeathReaction();
	void State();
	void StateChangeReaction();				//ステート変更処理
private:
	bool m_Attack;									//攻撃時
	float m_Angle;
	int m_AttackCnt;					//攻撃をしている時間
	int m_AttackCastCnt;				//攻撃に入るまでの時間

};
#endif