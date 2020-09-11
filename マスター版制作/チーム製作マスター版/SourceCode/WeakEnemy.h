//------------------------------------------------------------------------------
//
//�G���G����  [WeakEnemy.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _WEAKENEMY_H_
#define _WEAKENEMY_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "Enemy.h"
#include "vehicle.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
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
	bool m_Attack;									//�U����
	CShield *m_pShield;								//��
	CKnife  *m_pKnife;
};
#endif