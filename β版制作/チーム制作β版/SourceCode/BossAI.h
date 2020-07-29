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

#define MAX_RECASTTIME (120)
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
		AI_ATTACK_NONE = 0,	//攻撃しない
		AI_TRACKING,		//追尾弾発射
		AI_LASER,			//レーザー発射
		AI_DIFFUSION,		//拡散射撃
		AI_ATTACK_MAX				//行動の最大数
	}AI_STATE_ATTACK;

	typedef enum
	{
		AI_MOVE_NONE = 0,	//移動しない
		AI_CENTER,			//真ん中に戻る（初期化）
		AI_LEFT,			//左に動く
		AI_RIGHT,			//右に動く
		AI_MOVE_MAX				//行動の最大数
	}AI_STATE_MOVE;

	CBossAI();
	~CBossAI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	D3DXVECTOR3 GetTrackingShotRot(void);
	static CBossAI* CreateAI(CBoss *pBoss);
	AI_STATE_ATTACK GetAITypeAttack(void);
	bool GetShot(void);
	CCollision *GetCollision() { return m_pCollision; };			// 当たり判定のポインタ取得

private:
	CBoss	*pBossPass;					//敵の情報の格納用
	CGun	*m_pGun;					//ガンクラスのポインタ
	AI_STATE_ATTACK m_AItypeAttack;		//攻撃の種類
	AI_STATE_ATTACK m_AItypeAttackOld;	//前の攻撃の格納

	AI_STATE_MOVE m_AItypeMove;			//移動の種類
	AI_STATE_MOVE m_AItypeMoveOld;		//前の移動の格納

	int m_recast;						//現在行動から次回行動までの時間
	int m_castcount;					//行動時間
	bool m_bShot;						//射撃しているか
	bool m_bReStartFlag;				//前回とは異なる行動をするフラグ
	int m_random;						//乱数代入用
	CCollision	*m_pCollision;			//当たり判定のポインタ
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_ShotVec;

};

#endif
#pragma once
