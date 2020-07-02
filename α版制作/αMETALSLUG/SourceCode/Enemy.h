#pragma once
//=============================================================================
// エネミーヘッダー [Enemy.h]
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "Scene.h"
#include "Character.h"
class CModel;
class CGun;
class CEnemyAI;
//レンダリングクラス
class CEnemy :public CCharacter
{
public:
	CEnemy(OBJ_TYPE type);
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	static CEnemy *Create(void);
	bool DefaultMotion(void);

private:
	void Move(float move, float fdest);
	bool m_Attack;									//攻撃時
	float m_Angle;
	CGun	*m_pGun;								// ガンクラスのポインタ
	CEnemyAI *m_pAI;
};
#endif