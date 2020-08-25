//------------------------------------------------------------------------------
//
//雑魚敵処理  [WeakEnemy.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _WEAKENEMY_H_
#define _WEAKENEMY_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "main.h"
#include "Enemy.h"

//------------------------------------------------------------------------------
//マクロ
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
class CShield;
class CKnife;
class CWeakEnemy :public CEnemy
{
public:
	CWeakEnemy() {};
	CWeakEnemy(OBJ_TYPE type);
	~CWeakEnemy();

	enum class WEAKENEMY_TYPE
	{
		ENEMY_NORMAL,
		ENEMY_SHIELD
	};

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
	bool m_Attack;									//攻撃時
	float m_Angle;
	CShield *m_pShield;								//盾
	CKnife  *m_pKnife;
	WEAKENEMY_TYPE m_type;							//敵のタイプ
};
#endif