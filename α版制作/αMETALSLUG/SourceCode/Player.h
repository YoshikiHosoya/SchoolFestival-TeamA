#pragma once
//=============================================================================
// プレイヤーヘッダー [player.h]
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "Scene.h"
#include "Character.h"
class CModel;
class CMeshOrbit;
class CParticle;
class CUI;
class CGun;
class CGrenadeFire;
class CPrisoner;
class CKnife;
class CPlayerUI;

//レンダリングクラス
class CPlayer :public CCharacter
{
public:
	typedef enum
	{
		DEBUG_NORMAL = 0,			//通常
		DEBUG_CREATE_MAP,			//マップ作成
		DEBUG_CREATE_ENEMY,			//エネミー作成
		DEBUG_MAX					//最大数
	}DEBUG_STATE;

	CPlayer(OBJ_TYPE type);
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	void MoveUpdate(void);
	void CollisionUpdate(void);
	void AttackUpdate(void);
	DEBUG_STATE GetDebugState(void);
	static CPlayer *Create(void);
	bool DefaultMotion(void);
	CGun			*GetGun() { return  m_pGun; };					// 銃のポインタ取得
	CGrenadeFire	*GetGrenadeFire() { return  m_pGrenadeFire; };	// グレネード発射位置のポインタ取得
	CPlayerUI		*GetPlayerUI() { return  m_pPlayerUI; };		// プレイヤーUIのポインタ取得

private:
	void Move(float move, float fdest);
		DEBUG_STATE m_DebugState;						//デバッグのステータス
		bool m_bAttack_Enemy;							//攻撃時
		bool m_bAttack_Prisoner;						//攻撃時
		float m_Angle;
		WORD Oldstate;											//コントローラーの1frame前のステート
		CGun			*m_pGun;								// ガンクラスのポインタ
		CGrenadeFire	*m_pGrenadeFire;						// グレネード発射クラスのポインタ
		CPlayerUI		*m_pPlayerUI;							// プレイヤーUIのポインタ
		CKnife			*m_pKnife;
};
#endif