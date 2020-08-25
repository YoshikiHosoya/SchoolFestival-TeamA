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

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CShield;
class CKnife;
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
	static CWeakEnemy *Create(WEAKENEMY_TYPE type);
	bool DefaultMotion(void);
	virtual void DamageReaction();
	virtual void DeathReaction();
	virtual void StateChangeReaction();
	void ShieldBreak();
	CKnife *GetKnifePtr() { return m_pKnife; };

private:
	bool m_Attack;									//�U����
	float m_Angle;
	CShield *m_pShield;								//��
	CKnife  *m_pKnife;
};
#endif