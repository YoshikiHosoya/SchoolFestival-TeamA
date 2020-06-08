#pragma once
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

#define MAX_MODEL (20)			//モデルのパーツ数
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
	typedef enum
	{
		CHARACTER_TYPE_PLAYER,
		CHARACTER_TYPE_ENEMY,
		CHARACTER_TYPE_NPC,
		CHARACTER_TYPE_MAX
	}CHARACTER_TYPE;

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
		std::vector<KEY*> key;
	}KEY_INFO;
	//モデルのモーション
	typedef struct
	{
		int nLoop;					//ループ
		int nNumKey;				//キー情報の数
		std::vector<KEY_INFO*> key_info;
	}MOTION;
	typedef enum
	{
		CHARACTER_MOTION_STATE_NONE = -1,	//何もしないモーションステート
		PLAYER_MOTION_NORMAL = 0,			//ニュートラル
		PLAYER_MOTION_WALK,					//歩き
		PLAYER_MOTION_ATTACK01,				//通常攻撃1

		ENEMY_MOTION_NORMAL,				//ニュートラル
		ENEMY_MOTION_WALK,					//歩き
		ENEMY_MOTION_ATTACK01,				//通常攻撃1

		CHARACTER_MOTION_MAX				//最大数
	}CHARACTER_MOTION_STATE;

	CCharacter() {};
	CCharacter(OBJ_TYPE type);
	~CCharacter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void Move(float move, float fdest);
	void AddDamage(int Damage);
	void Moation(void);
	static void LoadMotion(void);
	void LoadOffset(CHARACTER_TYPE nType);
	virtual void DefaultMotion(void) = 0;
	//セッツ
	void SetPosition(D3DXVECTOR3 pos);
	void SetPotisionOld(D3DXVECTOR3 posOld);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetRotDest(D3DXVECTOR3 rotDest);
	void SetLife(int Life);
	void SetState(CHARACTER_STATE state);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	void SetMotion(CHARACTER_MOTION_STATE type);
	void SetMotionOldType(CHARACTER_MOTION_STATE type);
	void SetKeySet(int keyset);
	void SetFram(int fram);

	//ゲット
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetPositionOld(void);
	D3DXVECTOR3 &GetMove(void);		//※参照渡しの関数
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetRotDest(void);
	CHARACTER_STATE GetCharacterState(void);
	int GetLife(void);
	D3DXMATRIX GetMtxWorld(void);
	MOTION *GetCharacterMotion(CHARACTER_MOTION_STATE type);//キャラクターモーション情報の取得
	CHARACTER_MOTION_STATE GetMotionType(void);				//モーションタイプの取得
	CHARACTER_MOTION_STATE GetMotionOldType(void);			//前のモーションタイプ取得
	int GetKeySet(void);									//キーセットの取得
	int GetFram(void);										//フレームの取得


	void RayCollision(void);
private:
	static std::vector<MOTION*>m_CharacterMotion;			//キャラクターのモーション情報
	//CHARACTER_MOTION_STATE m_MotionState;					//モーションの変数
	CHARACTER_MOTION_STATE m_MotionType;					//モーションの数
	CHARACTER_MOTION_STATE m_MotionOld;						//前のモーション
	int m_CntKeySet;										//キーセットのカウント
	int m_Fram;												//フレーム
	static char *m_LoadOffsetFileName[CHARACTER_TYPE_MAX];	//読み込むファイル名
	static char *m_LoadMotionFileName[CHARACTER_MOTION_MAX];//読み込むファイル名
	std::vector<CModel*> m_vModelList;						//可変長配列 設置したモデル
	D3DXVECTOR3 m_rotBET[MAX_MODEL];
	D3DXVECTOR3 m_pos;										//位置
	D3DXVECTOR3 m_posold;									//前の位置
	D3DXVECTOR3 m_move;										//移動量
	D3DXVECTOR3 m_rot;										//回転
	D3DXVECTOR3 m_rotDest;									//回転する差分
	int m_Life;												//ライフ
	int m_nStateCnt;										//ステータスのカウント
	CHARACTER_STATE m_state;								//
	D3DXMATRIX  m_mtxWorld;									//マトリックス
	CHARACTER_TYPE m_nType;									//キャラクターのタイプ


};
#endif