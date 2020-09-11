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
#include "vehicle.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CShield;
class CKnife;
class CWeakEnemy :public CEnemy , public CVehicle
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
	void UpdateVehicle();
	static CWeakEnemy *Create(ENEMY_TYPE type);
	bool DefaultMotion(void);
	virtual void DamageReaction();
	virtual void DeathReaction();
	virtual void StateChangeReaction();
	void ShieldBreak();
	CKnife *GetKnifePtr() { return m_pKnife; };

private:
	bool m_Attack;									//攻撃時
	CShield *m_pShield;								//盾
	CKnife  *m_pKnife;
};
#endif