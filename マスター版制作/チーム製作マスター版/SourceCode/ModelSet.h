#pragma once
// =====================================================================================================================================================================
//
// モデルの設定処理 [ModelSet.h]
// Author :Hanzawa
//
// =====================================================================================================================================================================
#ifndef _MODELSET_H_
#define _MODELSET_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

#define MAX_MODEL (20)			//モデルのパーツ数
class CModel;
//レンダリングクラス
class CModelSet
{
public:
	typedef enum
	{
		CHARACTER_STATE_NONE,
		CHARACTER_STATE_NORMAL,
		CHARACTER_STATE_ITEMGET_FLASH,
		CHARACTER_STATE_DAMAGE_FLASHING,
		CHARACTER_STATE_DAMAGE_RED,
		CHARACTER_STATE_DEATH,
		CHARACTER_STATE_INVINCIBLE,

	}CHARACTER_STATE;

	typedef enum
	{
		CHARACTER_TYPE_PLAYER,			// プレイヤー
		CHARACTER_TYPE_ENEMY,			// エネミー
		CHARACTER_TYPE_PRISONER,		// 捕虜
		CHARACTER_TYPE_BOSS,			// ボス
		CHARACTER_TYPE_BOSS_ONE,		// ボス
		CHARACTER_TYPE_TANK,			// 戦車
		CHARACTER_TYPE_PLANE,			// 戦闘機
		CHARACTER_TYPE_HELICOPTER,		// ヘリコプター

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
		float fHeight;					//高さ
										//コンストラクタ
		KEY_INFO()
		{
			nFram = 60;
			fHeight = 0.0f;
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
		// プレイヤーのモーション
		CHARACTER_MOTION_STATE_NONE = -1,	//何もしないモーションステート
		PLAYER_MOTION_NORMAL = 0,			//ニュートラル
		PLAYER_MOTION_WALK,					//歩き
		PLAYER_MOTION_ATTACK01,				//通常攻撃1
		PLAYER_MOTION_GRENADE,				//グレネード
		PLAYER_MOTION_JUMP,					//ジャンプ
		PLAYER_MOTION_JUMPSTOP,				//ジャンプしている状態
		PLAYER_MOTION_SHOOT,				//撃つ
		PLAYER_MOTION_SQUAT,				//しゃがむ
		PLAYER_MOTION_SQUATSTOP,			//しゃがんでる状態
		PLAYER_MOTION_DEAD,					//死んだ

		// 敵のモーション
		ENEMY_MOTION_NORMAL,				//ニュートラル
		ENEMY_MOTION_WALK,					//歩き
		ENEMY_MOTION_SQUAT,					//通常攻撃1
		ENEMY_MOTION_DEAD_1,				//死んだ
		ENEMY_MOTION_DEAD_2,				//死んだ2
		ENEMY_MOTION_GRENADE,				//グレネード
		ENEMY_MOTION_JUMPATTACK,			//近接攻撃
		ENEMY_MOTION_KNIFEATTACK,			//近接攻撃2

		// ソル・デ・ロカのモーション
		BOSS_MOTION_NORMAL,					//ニュートラル

		// 捕虜のモーション
		PRISONER_MOTION_STAY,				//ニュートラル
		PRISONER_MOTION_RELEASE,			//立ってる
		PRISONER_MOTION_RUN,				//走る
		PRISONER_MOTION_SALUTE,				//敬礼
		PRISONER_MOTION_FALL,				//落下
		PRISONER_MOTION_SKIP,				//スキップをしながら走る
		CHARACTER_MOTION_MAX				//最大数
	}CHARACTER_MOTION_STATE;

	CModelSet();
	~CModelSet();
	HRESULT Init(void);
	void Uninit(void);
	bool Motion();							//モーション処理
	static void LoadMotion(void);
	void LoadOffset(CHARACTER_TYPE nType);
	void ForcedUpdate();						//強制的にモーションチェンジ
	static void CharacterUnLoad(void);
	static CModelSet *CreateModelSet(void);
	//セッツ
	void SetStateCount(int nCntState);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	void SetCharacterType(CHARACTER_TYPE CharaType);

	//モーション関連
	void SetMotion(CHARACTER_MOTION_STATE type);
	void SetMotionOldType(CHARACTER_MOTION_STATE type);
	void SetKeySet(int keyset);
	void SetFram(int fram);
	void SetUseMotion(bool use);
	//ゲット
	CHARACTER_STATE GetCharacterState(void);
	CHARACTER_TYPE GetCharacterType();								//キャラクターの種類取得
	D3DXVECTOR3 &GetRot(void);
	std::vector<CModel*> &GetCharacterModelList();					//キャラクターのモデル取得
	//モーション関連
	bool &GetMotion();
	int &GetKeySet(void);											//キーセットの取得
	int &GetFram(void);												//フレームの取得
	int GetCharacterStateCnt() { return m_nStateCnt; };				// キャラクターのステートのカウント
	float GetHeightBet(void);
	char* GetOffsetFileName(CHARACTER_TYPE type);
	char* GetMotionFileName(CHARACTER_MOTION_STATE motionstate);
	MOTION *GetCharacterMotion(CHARACTER_MOTION_STATE type);		//キャラクターモーション情報の取得
	CHARACTER_MOTION_STATE &GetMotionType(void);					//モーションタイプの取得
	CHARACTER_MOTION_STATE GetMotionOldType(void);					//前のモーションタイプ取得

	void ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor);									// 色変更
	void SetAllModelDisp(bool bDisp);								//点滅の切り替え

private:
	static char *m_LoadOffsetFileName[CHARACTER_TYPE_MAX];			//読み込むファイル名
	static char *m_LoadMotionFileName[CHARACTER_MOTION_MAX];		//読み込むファイル名
	std::vector<CModel*> m_vModelList;								//可変長配列 設置したモデル
	D3DXVECTOR3 m_rotBET[MAX_MODEL];
	float m_HeightBet;
	D3DXVECTOR3 m_rot;												//回転
	D3DXVECTOR3 m_rotDest;											//回転する差分
	D3DXVECTOR3 m_ShotRotDest;										//撃つ向きの決定地　ヘビーマシンガン用
	D3DXVECTOR3 m_AddHeadRot;
	D3DXVECTOR3 m_AddArmRot;
	D3DXMATRIX  m_mtxWorld;											//マトリックス
	CHARACTER_STATE m_state;										//
	CHARACTER_TYPE m_CharaType;										//キャラクターのタイプ
	int m_nStateCnt;												//ステータスのカウント
	bool m_bMotion;													//モーションするかどうか
	bool m_bFall;													//モーションするかどうか
	bool m_bDraw;													//描画するかどうか
	DIRECTION	m_CharacterDirection;								//キャラクターの向き
	DIRECTION	m_CharacterDirectionOld;							//1F前のキャラクターの向き

																	//モーション関連の情報
	static std::vector<MOTION*>m_CharacterMotion;					//キャラクターのモーション情報
	CHARACTER_MOTION_STATE m_MotionType;							//現在のモーション
	CHARACTER_MOTION_STATE m_MotionOld;								//前のモーション
	int m_CntKeySet;												//キーセットのカウント
	int m_Fram;														//フレーム

	void CalcRotation();											//回転の計算
};
#endif