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
class CCollision;
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
	static CEnemy *Create(void);
	void DefaultMotion(void);
	void DeleteCollision(void);
	CCollision *GetCollision() { return m_pCollision; }; // 当たり判定

private:
	void Move(float move, float fdest);
	bool m_Attack;									//攻撃時
	float m_Angle;
	CCollision					*m_pCollision;		// 当たり判定情報
};
#endif