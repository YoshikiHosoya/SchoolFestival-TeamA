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
	void PadMoveUpdate(void);
	void ReSpawn(void);
	void DamageReaction();
	void DeathReaction();
	void StateChangeReaction();
	DEBUG_STATE GetDebugState(void);
	static CPlayer *Create(void);
	bool DefaultMotion(void);
	void MapChangePlayerRespawn();

	CGun			*GetGun() { return  m_pGun; };					// 銃のポインタ取得
	CGrenadeFire	*GetGrenadeFire() { return  m_pGrenadeFire; };	// グレネード発射位置のポインタ取得
	CPlayerUI		*GetPlayerUI() { return  m_pPlayerUI; };		// プレイヤーUIのポインタ取得

	void			SetRideFlag(bool bRide)			{ m_bRideVehicle = bRide; };	// ライドフラグの設定
	bool			GetRideFlag()					{ return m_bRideVehicle; };		// ライドフラグの取得

	void			SetRespawnFlag(bool bRespawn)	{ m_bRespawn = bRespawn; };
	bool			GetRespawnFlag()				{ return m_bRespawn; };
private:
	void Move(float move, float fdest);
	void Ride();

		DEBUG_STATE m_DebugState;						//デバッグのステータス
		bool m_bAttack;									//近接攻撃できるかどうか
		bool m_bKnifeAttack;							//攻撃をしているかどうか
		bool m_bRespawn;
		float m_Angle;
		bool m_bCruch;
		WORD Oldstate;											//コントローラーの1frame前のステート
		CGun			*m_pGun;								// ガンクラスのポインタ
		CGrenadeFire	*m_pGrenadeFire;						// グレネード発射クラスのポインタ
		CPlayerUI		*m_pPlayerUI;							// プレイヤーUIのポインタ
		CKnife			*m_pKnife;								// ナイフのポインタ
		bool			m_bRideVehicle;							// 乗り物に乗り込んでいるかどうかのフラグ
		int m_nRespawnCnt;
};
#endif