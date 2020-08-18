//------------------------------------------------------------------------------
//
//雑魚敵処理  [WeakEnemy.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _WEAKENEMY_H_
#define _WEAKENEMY_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "Enemy.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CWeakEnemy :public CEnemy
{
public:
	CWeakEnemy() {};
	CWeakEnemy(OBJ_TYPE type);
	~CWeakEnemy();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void DebugInfo(void);
	static CWeakEnemy *Create(void);
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