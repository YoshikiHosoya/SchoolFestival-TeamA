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
#include "Character.h"
#include "BaseAI.h"
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

	void DeleteAI();

	void SetGunPtr(CGun *pGun) { m_pGun = pGun; };
	CGun *GetGunPtr() { return m_pGun; };
	void SetAIPtr(CBaseAI *pAI) { m_pAI = pAI; };
	CBaseAI *GetAIPtr() { return m_pAI; };

 private:
	CGun	*m_pGun;								// �K���N���X�̃|�C���^
	CBaseAI *m_pAI;									// AI�̃|�C���^

};
#endif