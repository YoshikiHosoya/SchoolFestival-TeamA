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
class CEnemy :public CCharacter, public CGameObject
{
public:

	enum class WEAKENEMY_TYPE
	{
		ENEMY_NORMAL,
		ENEMY_SHIELD
	};

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

	//Set�֐�
	void SetGunPtr(CGun *pGun)				{ m_pGun = pGun; };
	void SetAIPtr(CBaseAI *pAI)				{ m_pAI = pAI; };
	void SetEventFlag(bool bFlag)			{ m_bEventFlag = bFlag; };
	void SetEnemyType(WEAKENEMY_TYPE type)	{ m_type = type; };				// �G���G�̎�ނ̐ݒ�

	//Get�֐�
	CGun				*GetGunPtr()		{ return m_pGun; };
	CBaseAI				*GetAIPtr()			{ return m_pAI; };
	bool				GetEventFlag()		{ return m_bEventFlag; };
	WEAKENEMY_TYPE		GetEnemyType()		{ return m_type; };				// �G���G�̎�ނ̎擾

	bool m_bEventFlag;								// �C�x���g�t���O

 private:
	CGun			*m_pGun;								// �K���N���X�̃|�C���^
	CBaseAI			*m_pAI;									// AI�̃|�C���^
	WEAKENEMY_TYPE	m_type;							//�G�̃^�C�v

};
#endif