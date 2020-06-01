#pragma once
#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"
#define MAX_MODEL (11)			//モデルのパーツ数
#define MAX_RAY_LENGTH (35)		//Rayの最大の長さ
#define RAY_FIRST_POINT (40.0f)	//Rayの始点
class CModel;
class CCreateMap;
class CMeshOrbit;
class CParticle;
class CUI;
//レンダリングクラス
class CPlayer :public CScene
{
public:
	//キー要素
	typedef struct
	{
		D3DXVECTOR3 pos;			//位置
		D3DXVECTOR3 rot;			//回転
	}KEY;
	//キー情報
	typedef struct
	{
		int nFram;					//フレーム数
		KEY key[MAX_MODEL];			//パーツ数
	}KEY_INFO;
	//プレイヤーのモーション
	typedef struct
	{
		int nLoop;					//ループ
		int nNumKey;				//キー情報の数
		KEY_INFO key_info[10];		//キーが何セットあるか
		int Collision_nParts;		//パーツ番号
		D3DXVECTOR3 CollisionOfset;	//オフセット
		float CollisionRadius;		//円の半径
		int CollisionStartFram;		//開始フレーム
		int CollisionEndFram;		//終了フレーム
		int Collision_Damage;		//ダメージ数
	}MOTION_PLAYER;
	typedef enum
	{
		PLAYER_MOTION_NORMAL = 0,	//ニュートラル
		PLAYER_MOTION_WALK,			//歩き
		PLAYER_MOTION_ATTACK01,		//通常攻撃1
		PLAYER_MOTION_ATTACK02,		//通常攻撃2
		PLAYER_MOTION_ATTACK03,		//通常攻撃3
		PLAYER_MOTION_SKILL01,		//スキル1
		PLAYER_MOTION_SKILL02,		//スキル1
		PLAYER_MOTION_SKILL03,		//スキル3
		PLAYER_MOTION_ROWLING,		//回避
		PLAYER_MOTION_DAMAGE,		//ダメージ
		PLAYER_MOTION_MAX			//最大数
	}PLAYER_MOTION_STATE;
	typedef enum
	{
		DEBUG_NORMAL = 0,			//通常
		DEBUG_CREATE_MAP,			//マップ作成
		DEBUG_CREATE_ENEMY,			//エネミー作成
		DEBUG_MAX					//最大数
	}DEBUG_STATE;
	typedef enum
	{
		PLAYER_STATE_NONE,
		PLAYER_STATE_NORMAL,
		PLAYER_STATE_DAMAGE,
		PLAYER_STATE_INVINCIBLE,
		PLAYER_STATE_MAX
	}PLAYER_STATE;

	CPlayer(OBJ_TYPE type);
	~CPlayer();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Drow(void);
	void Move(float move, float fdest);
	void LoadMotion(void);
	void Moation(void);
	void HitPlayer(int Damage);
	void SetLife(int Life);
	void SetPosition(D3DXVECTOR3 pos);
	void CollisionModel(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetPositionOld(void);
	D3DXVECTOR3 GetMove(void);
	D3DXVECTOR3 GetOffset(int nCnt);
	DEBUG_STATE GetDebugState(void);
	PLAYER_STATE GetPlayerState(void);
	int GetWeponType(void);
	int GetLife(void);
	static CPlayer *Create(void);
private:
		D3DXVECTOR3 m_pos;								//位置
		D3DXVECTOR3 m_posold;							//前の位置
		D3DXVECTOR3 m_move;								//移動量
		D3DXVECTOR3 m_rot;								//回転
		D3DXVECTOR3 posBET[MAX_MODEL];					//座標の差分
		D3DXVECTOR3 rotBET[MAX_MODEL];					//回転の差分
		D3DXVECTOR3 pos[MAX_MODEL];						//位置の格納用
		D3DXVECTOR3 rot[MAX_MODEL];						//回転の格納用
		D3DXVECTOR3 Dest;								//回転する差分
		D3DXVECTOR3 m_size;								//
		D3DXVECTOR3 m_vecAxis;							//回転軸
		D3DXVECTOR3 m_aOffset[10];
		CModel *m_Model[MAX_MODEL];						//モデル
		CModel *m_WeponModel[3];						//武器モデル
		CCreateMap *m_CreateMap;
		MOTION_PLAYER m_PlayerMotion[PLAYER_MOTION_MAX];//プレイヤーのモーション
		PLAYER_MOTION_STATE m_MotionState;				//モーションの変数
		DEBUG_STATE m_DebugState;						//デバッグのステータス
		int m_Type;										//タイプ
		int m_WeponType;								//武器の種類
		int m_MotionType;								//モーションの数
		int m_MotionOld;								//前のモーション
		int m_CntKeySet;								//キーセットのカウント
		int m_Fram;										//フレーム
		int m_CntState;									//ステータスのカウント
		int m_nCnt;										//全体のカウント
		int m_Life;										//ライフ
		int m_nStateCnt;								//ステータスのカウント
		float m_Angle;
		bool m_Attack;									//攻撃時
		PLAYER_STATE m_state;							//
		LPDIRECT3DTEXTURE9 m_pTexture;					//テクスチャ
		D3DXMATRIX  m_mtxWorld;							//マトリックス
		D3DXMATRIX m_mtxRot;							//回転マトリックス
		float m_fValueRot;								//回転角（回転量
		XINPUT_STATE state;
		XINPUT_VIBRATION vibration;
		WORD Oldstate;
};
#endif