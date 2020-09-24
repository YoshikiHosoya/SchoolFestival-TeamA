#pragma once
//------------------------------------------------------------------------------
//
//敵のスーパークラス  [Enemy.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _ENEMY_H_
#define _ENEMY_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "Character.h"
#include "BaseAI.h"
//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CModel;
class CGun;
class CGrenadeFire;
class CEnemyAI;
//レンダリングクラス
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

	//Set関数
	void SetGunPtr(CGun *pGun)					{ m_pGun = pGun; };
	void SetAIPtr(CBaseAI *pAI)					{ m_pAI = pAI; };
	void SetEventFlag(bool bFlag)				{ m_bEventFlag = bFlag; };
	void SetEnemyType(ENEMY_TYPE type)			{ m_type = type; };				// 雑魚敵の種類の設定

	//Get関数
	CGun				*GetGunPtr()			{ return m_pGun; };
	CGrenadeFire		*GetGrenadeFirePtr()	{ return m_pGrenadeFire; };		// グレネード発射クラスのポインタ取得
	CBaseAI				*GetAIPtr()				{ return m_pAI; };
	bool				GetEventFlag()			{ return m_bEventFlag; };
	ENEMY_TYPE			GetEnemyType()			{ return m_type; };				// 雑魚敵の種類の取得


 private:
	CGun			*m_pGun;								// ガンクラスのポインタ
	CGrenadeFire	*m_pGrenadeFire;						// グレネード発射クラスのポインタ
	CBaseAI			*m_pAI;									// AIのポインタ
	ENEMY_TYPE		m_type;							//敵のタイプ
	bool m_bEventFlag;								// イベントフラグ

};
#endif