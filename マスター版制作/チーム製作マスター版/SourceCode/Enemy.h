#pragma once
//=============================================================================
// �G�l�~�[�w�b�_�[ [Enemy.h]
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "Scene.h"
#include "Character.h"
class CModel;
class CGun;
class CEnemyAI;
//�����_�����O�N���X
class CEnemy :public CCharacter
{
public:
	CEnemy(OBJ_TYPE type);
	~CEnemy();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	void DebugInfo(void);
	static CEnemy *Create(void);
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