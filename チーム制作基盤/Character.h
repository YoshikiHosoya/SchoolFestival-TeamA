#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

#define MAX_MODEL (11)			//モデルのパーツ数
class CModel;
//レンダリングクラス
class CCharacter :public CScene
{
public:
	typedef enum
	{
		CHARACTER_STATE_NONE,
		CHARACTER_STATE_NORMAL,
		CHARACTER_STATE_DAMAGE,
		CHARACTER_STATE_INVINCIBLE,
		CHARACTER_STATE_MAX
	}CHARACTER_STATE;
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

	CCharacter(OBJ_TYPE type);
	~CCharacter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Move(float move, float fdest);
	void AddDamage(int Damage);
	void LoadMotion(void);
	void Moation(void);
	void LoadOffset(void);
	//セッツ
	void SetPosition(D3DXVECTOR3 pos);
	void SetPotisionOld(D3DXVECTOR3 posOld);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetRotDest(D3DXVECTOR3 rotDest);
	void SetLife(int Life);
	void SetState(CHARACTER_STATE state);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	//ゲット
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetPositionOld(void);
	D3DXVECTOR3 &GetMove(void);		//※参照渡しの関数
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetRotDest(void);
	CHARACTER_STATE GetCharacterState(void);
	int GetLife(void);
	D3DXMATRIX GetMtxWorld(void);
	void RayCollision(void);
	static CCharacter *Create(void);
private:

	D3DXVECTOR3 rotBET[MAX_MODEL];					//回転の差分
	MOTION_PLAYER m_PlayerMotion[PLAYER_MOTION_MAX];//プレイヤーのモーション
	PLAYER_MOTION_STATE m_MotionState;				//モーションの変数
	int m_MotionType;								//モーションの数
	int m_MotionOld;								//前のモーション
	int m_CntKeySet;								//キーセットのカウント
	int m_Fram;										//フレーム
	static char *m_LoadFileName;					//読み込むファイル名
	std::vector<CModel*> m_vModelList;				//可変長配列 設置したモデル

	D3DXVECTOR3 m_pos;								//位置
	D3DXVECTOR3 m_posold;							//前の位置
	D3DXVECTOR3 m_move;								//移動量
	D3DXVECTOR3 m_rot;								//回転
	D3DXVECTOR3 m_rotDest;							//回転する差分
	int m_Life;										//ライフ
	int m_nStateCnt;								//ステータスのカウント
	CHARACTER_STATE m_state;						//
	D3DXMATRIX  m_mtxWorld;							//マトリックス
};
#endif