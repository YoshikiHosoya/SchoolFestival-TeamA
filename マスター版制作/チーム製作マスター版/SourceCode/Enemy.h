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
class CGrenadeFire;
class CEnemyAI;
//�����_�����O�N���X
class CEnemy :public CCharacter, public CGameObject
{
public:

	enum class ENEMY_TYPE
	{
		ENEMY_NORMAL,
		ENEMY_SHIELD,
		ENEMY_HELICOPTER,
		ENEMY_MELTYHONEY,
		ENEMY_ZYCOCCA,
		ENEMY_SKYDRONE,
		ENEMY_WALLDRONE,
		ENEMY_BOSS_DRAGON_NOSUKE,
		ENEMY_BOSS_SOL_DE_ROCA,

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
	void SetGunPtr(CGun *pGun)					{ m_pGun = pGun; };
	void SetAIPtr(CBaseAI *pAI)					{ m_pAI = pAI; };
	void SetEventFlag(bool bFlag)				{ m_bEventFlag = bFlag; };
	void SetEnemyType(ENEMY_TYPE type)			{ m_type = type; };				// �G���G�̎�ނ̐ݒ�

	//Get�֐�
	CGun				*GetGunPtr()			{ return m_pGun; };
	CGrenadeFire		*GetGrenadeFirePtr()	{ return m_pGrenadeFire; };		// �O���l�[�h���˃N���X�̃|�C���^�擾
	CBaseAI				*GetAIPtr()				{ return m_pAI; };
	bool				GetEventFlag()			{ return m_bEventFlag; };
	ENEMY_TYPE			GetEnemyType()			{ return m_type; };				// �G���G�̎�ނ̎擾


 private:
	CGun			*m_pGun;								// �K���N���X�̃|�C���^
	CGrenadeFire	*m_pGrenadeFire;						// �O���l�[�h���˃N���X�̃|�C���^
	CBaseAI			*m_pAI;									// AI�̃|�C���^
	ENEMY_TYPE		m_type;							//�G�̃^�C�v
	bool m_bEventFlag;								// �C�x���g�t���O

};
#endif