#pragma once
//------------------------------------------------------------------------------
//
//�G�̃X�[�p�[�N���X  [Enemy.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "Scene.h"
#include "Character.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModel;
class CGun;
class CEnemyAI;
//�����_�����O�N���X
class CEnemy :public CCharacter
{
public:
	CEnemy() {};
	CEnemy(OBJ_TYPE type);
	~CEnemy();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void DebugInfo(void);
	virtual bool DefaultMotion(void);
	virtual void DamageReaction();
	virtual void DeathReaction();
	virtual void StateChangeReaction();

	void SetGunPtr(CGun *pGun) { m_pGun = pGun; };
	CGun *GetGunPtr() { return m_pGun; };

 private:
	CGun	*m_pGun;								// �K���N���X�̃|�C���^

};
#endif