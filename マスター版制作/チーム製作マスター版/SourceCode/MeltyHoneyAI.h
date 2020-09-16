#pragma once
#pragma once
//=============================================================================
// AI処理 [BossAI.h]
//=============================================================================
#ifndef _MELTYHONEYMK2AIAI_H_
#define _MELTYHONEYMK2AIAI_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"
#include "BaseAI.h"
class CGun;
class CWeakEnemy;
class CCollision;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CMeltyhoney :public CBaseAI
{
public:
	typedef enum
	{
		AI_NONE = 0,		//攻撃しない
		AI_SHOT,			//追尾弾発射
		AI_LEFT,
		AI_RIGHT,
		AI_STOP,
		AI_MAX				//行動の最大数
	}AI_STATE;
	CMeltyhoney();
	~CMeltyhoney();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateMoveAI(void);
	void UpdateAttackAI(void);
	void Draw(void);
	void DebugInfo(void);
	static CMeltyhoney* CreateAI(CWeakEnemy *pEnemy);

	void SetShot(bool shot)					{ m_bShot = shot; };
	void SetRestartFlag(bool flag)			{ m_bReStartFlag = flag; };
	void SetAI(AI_STATE attack)				{ m_AItype = attack; };

	bool GetShot(void)						{ return m_bShot; };
	AI_STATE GetMeltyHoneyAIType(void)		{ return m_AItype; };
	CCollision *GetCollision()				{ return m_pCollision; };	// 当たり判定のポインタ取得
private:
	CWeakEnemy *pEnemy;					//敵の情報の格納用
	AI_STATE m_AItype;			//攻撃の種類
	AI_STATE m_AItypeOld;		//前の攻撃の格納

	int m_recast;						//現在行動から次回行動までの時間
	int m_castcount;					//行動時間
	int m_AttackCnt;					//攻撃をしている時間
	int m_AttackCastCnt;				//攻撃に入るまでの時間
	int m_MoveCnt;						//移動している時間
	int m_LaserRandom;					//レーザーの右左の乱数代入
	int m_Attacks;						//何回攻撃するか
	bool m_bShot;						//攻撃可能状態
	bool m_bReStartFlag;				//前回とは異なる行動をするフラグ
	bool m_Attack;						//攻撃状態

	CCollision	*m_pCollision;			//当たり判定のポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_ShotVec;
	CWeakEnemy *pEnemyPass;				//敵の情報の格納用
	D3DXVECTOR3 m_Distance;
	float m_fDistance;

};

#endif
#pragma once
