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
	bool m_Attack;									//�U����
	float m_Angle;
	CGun	*m_pGun;								// �K���N���X�̃|�C���^
	CEnemyAI *m_pAI;
};
#endif