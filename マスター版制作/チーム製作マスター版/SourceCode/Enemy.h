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
class CEnemyAI;
//レンダリングクラス
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

	//Set関数
	void SetGunPtr(CGun *pGun)			{ m_pGun = pGun; };
	void SetAIPtr(CBaseAI *pAI)			{ m_pAI = pAI; };
	void SetEventFlag(bool bFlag)		{ m_bEventFlag = bFlag; };

	//Get関数
	CGun *GetGunPtr()					{ return m_pGun; };
	CBaseAI *GetAIPtr()					{ return m_pAI; };
	bool GetEventFlag()					{ return m_bEventFlag; };

	bool m_bEventFlag;								// イベントフラグ

 private:
	CGun	*m_pGun;								// ガンクラスのポインタ
	CBaseAI *m_pAI;									// AIのポインタ

};
#endif