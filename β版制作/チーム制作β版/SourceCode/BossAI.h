#pragma once
//=============================================================================
// AI処理 [BossAI.h]
//=============================================================================
#ifndef _BOSSAI_H_
#define _BOSSAI_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"

#define MAX_RECASTTIME (60)
class CBoss;
class CGun;
class CCollision;
//=============================================================================
// プロトタイプ宣言
//=============================================================================
class CBossAI
{
public:
	typedef enum
	{
		AI_NONE = 0,	//攻撃しない
		AI_TRACKING,		//追尾弾発射
		AI_LASER,			//レーザー発射
		AI_DIFFUSION,		//拡散射撃
		AI_CENTER,			//真ん中に戻る（初期化）
		AI_LEFT,			//左に動く
		AI_RIGHT,			//右に動く
		AI_ONPLAYER,		//自機の上
		AI_MAX				//行動の最大数
	}AI_BOSS_STATE;
	CBossAI();
	~CBossAI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateMoveAI(void);
	void UpdateAttackAI(void);
	void Draw(void);
	void DebugInfo(void);
	D3DXVECTOR3 GetTrackingShotRot(void);
	static CBossAI* CreateAI(CBoss *pBoss);
	AI_BOSS_STATE GetBossAIType(void);
	bool GetShot(void);
	void SetShot(bool shot);
	void SetRestartFlag(bool flag);
	CCollision *GetCollision() { return m_pCollision; };			// 当たり判定のポインタ取得
	void SetBossAI(AI_BOSS_STATE attack);
private:
	CBoss	*pBossPass;					//敵の情報の格納用
	AI_BOSS_STATE m_BossAItype;		//攻撃の種類
	AI_BOSS_STATE m_BossAItypeOld;	//前の攻撃の格納

	int m_recast;						//現在行動から次回行動までの時間
	int m_castcount;					//行動時間
	int m_random;						//乱数代入用
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
};

#endif
#pragma once
