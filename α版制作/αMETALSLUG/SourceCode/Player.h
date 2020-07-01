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
class CCollision;
class CPrisoner;

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
	DEBUG_STATE GetDebugState(void);
	static CPlayer *Create(void);
	bool DefaultMotion(void);
private:
	void Move(float move, float fdest);
		DEBUG_STATE m_DebugState;						//デバッグのステータス
		bool m_Attack;									//攻撃時
		float m_Angle;
		WORD Oldstate;									//コントローラーの1frame前のステート
		CGun	*m_pGun;								// ガンクラスのポインタ
		D3DXVECTOR3 m_ShotRot;							//撃つ向き
		CCollision					*m_pCollision;		// 当たり判定情報
		bool						m_bCloseRangeAttack;// 近接攻撃フラグ
		CPrisoner					*m_pPrisoner;		// 捕虜のポインタを保存する変数

};
#endif