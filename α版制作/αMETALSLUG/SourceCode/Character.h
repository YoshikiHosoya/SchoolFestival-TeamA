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
		CHARACTER_TYPE_PLAYER,			// プレイヤー
		CHARACTER_TYPE_ENEMY,			// エネミー
		CHARACTER_TYPE_PRISONER,		// 捕虜
		CHARACTER_TYPE_PLAYER_VEHICLE,	// プレイヤー用乗り物
		CHARACTER_TYPE_ENEMY_VEHICLE,	// エネミー用乗り物
		CHARACTER_TYPE_MAX
	}CHARACTER_TYPE;


	//キー要素
	typedef struct KEY
	{
		D3DXVECTOR3 pos;			//位置
		D3DXVECTOR3 rot;			//回転

		//コンストラクタ　初期化しておく
		KEY()
		{
			pos = ZeroVector3;
			rot = ZeroVector3;
		}
	}KEY;

	//キー情報
	typedef struct KEY_INFO
	{
		int nFram;					//フレーム数
		std::vector<KEY*> key;

		//コンストラクタ
		KEY_INFO()
		{
			nFram = 60;
			key = {};
		}
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
		PLAYER_MOTION_GRENADE,				//グレネード

		ENEMY_MOTION_NORMAL,				//ニュートラル
		ENEMY_MOTION_WALK,					//歩き
		ENEMY_MOTION_ATTACK01,				//通常攻撃1

		// 捕虜のモーション
		PRISONER_MOTION_STAY,				//ニュートラル
		//PRISONER_MOTION_RELEASE,			//開放された時
		//PRISONER_MOTION_RUN,				//走る
		//PRISONER_MOTION_SKIP,				//スキップをしながら走る

		CHARACTER_MOTION_MAX				//最大数
	}CHARACTER_MOTION_STATE;

	typedef enum
	{
		CHARACTER_LEFT,						//左向き
		CHARACTER_RIGHT,					//右向き
		CHARACTER_UP,						//上向き
		CHARACTER_DOWN,						//下向き
	}CHARACTER_DIRECTION;

	CCharacter() {};
	CCharacter(OBJ_TYPE type);
	~CCharacter();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	virtual bool DefaultMotion(void) = 0;

	void Move(float move, float fdest);
	void AddDamage(int Damage);
	void Moation(void);
	static void LoadMotion(void);
	void LoadOffset(CHARACTER_TYPE nType);
	void ForcedUpdate();						//強制的にモーションチェンジ
	static void CharacterUnLoad(void);
	//セッツ
	void SetPosition(D3DXVECTOR3 pos);
	void SetPotisionOld(D3DXVECTOR3 posOld);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetRotDest(D3DXVECTOR3 rotDest);
	void SetLife(int Life);
	void SetJump(bool bJump);
	void SetState(CHARACTER_STATE state);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	void SetCharacterType(CHARACTER_TYPE CharaType);
	void SetGravity(bool gravity);
	void SetCharacterDirection(CHARACTER_DIRECTION direction);
	void SetShotDirection(D3DXVECTOR3 direction);
	//モーション関連
	void SetMotion(CHARACTER_MOTION_STATE type);
	void SetMotionOldType(CHARACTER_MOTION_STATE type);
	void SetKeySet(int keyset);
	void SetFram(int fram);

	//ゲット
	D3DXVECTOR3 &GetPosition(void);				//参照渡し
	D3DXVECTOR3 &GetPositionOld(void);			//参照渡し
	D3DXVECTOR3 &GetMove(void);					//参照渡し
	D3DXVECTOR3 &GetRot(void);					//参照渡し
	D3DXVECTOR3 &GetRotDest(void);				//参照渡し
	CHARACTER_STATE GetCharacterState(void);
	D3DXMATRIX *GetMtxWorld(void);
	D3DXVECTOR3 GetShotDirection(void);
	int GetLife(void);
	bool GetJump(void);
	bool GetGravity(void);
	CHARACTER_TYPE GetCharacterType();								//キャラクターの種類取得
	std::vector<CModel*> &GetCharacterModelList();					//キャラクターのモデル取得
	CHARACTER_DIRECTION GetCharacterDirection(void);				//向きの取得
	//モーション関連
	bool &GetMotion();
	int &GetKeySet(void);											//キーセットの取得
	int &GetFram(void);												//フレームの取得
	MOTION *GetCharacterMotion(CHARACTER_MOTION_STATE type);		//キャラクターモーション情報の取得
	CHARACTER_MOTION_STATE &GetMotionType(void);					//モーションタイプの取得
	CHARACTER_MOTION_STATE GetMotionOldType(void);					//前のモーションタイプ取得

	//Rayの判定
	void RayCollision(void);

	char* GetOffsetFileName(CHARACTER_TYPE type);
	char* GetMotionFileName(CHARACTER_MOTION_STATE motionstate);

	bool GetDieFlag(){return m_bDieFlag; };								// 死亡フラグの取得
	void SetDieFlag(bool DieFlag) { m_bDieFlag = DieFlag; };			// 死亡フラグの設定

private:
	static char *m_LoadOffsetFileName[CHARACTER_TYPE_MAX];			//読み込むファイル名
	static char *m_LoadMotionFileName[CHARACTER_MOTION_MAX];		//読み込むファイル名
	std::vector<CModel*> m_vModelList;								//可変長配列 設置したモデル
	D3DXVECTOR3 m_rotBET[MAX_MODEL];
	D3DXVECTOR3 m_pos;												//位置
	D3DXVECTOR3 m_posold;											//前の位置
	D3DXVECTOR3 m_move;												//移動量
	D3DXVECTOR3 m_rot;												//回転
	D3DXVECTOR3 m_rotDest;											//回転する差分
	D3DXVECTOR3 m_ShotRot;											//撃つ向き
	D3DXVECTOR3 m_AddRot;
	D3DXMATRIX  m_mtxWorld;											//マトリックス
	CHARACTER_STATE m_state;										//
	CHARACTER_TYPE m_CharaType;										//キャラクターのタイプ
	int m_Life;														//ライフ
	int m_nStateCnt;												//ステータスのカウント
	CHARACTER_DIRECTION	m_CharacterDirection;						//キャラクターの向き
	//モーション関連の情報
	static std::vector<MOTION*>m_CharacterMotion;					//キャラクターのモーション情報
	CHARACTER_MOTION_STATE m_MotionType;							//現在のモーション
	CHARACTER_MOTION_STATE m_MotionOld;								//前のモーション
	int m_CntKeySet;												//キーセットのカウント
	int m_Fram;														//フレーム
	bool m_bJump;
	bool m_bGravity;
	bool m_bDieFlag;												// 死亡フラグ
	bool m_bMotion;													//モーションするかどうか
};
#endif