//=============================================================================
//
// 敵モデル処理 [enemy.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// インクルードファイル
//=============================================================================
#include "scene.h"
#include "model.h"
#include "motion.h"

//=============================================================================
// マクロ定義
//=============================================================================

//=============================================================================
// 前方宣言
//=============================================================================
class CFloarTile;
//=============================================================================
// クラス
//=============================================================================
class CEnemy : public CScene
{
public:
	// ---------モーションタイプ---------- //
	typedef enum
	{
		MOTIONTYPE_ENEMY_WAIT = 0,		//待機モーション
		MOTIONTYPE_ENEMY_TUTORIAL,		//説明モーション
		MOTIONTYPE_ENEMY_RUN,			//移動モーション(走り)
		MOTIONTYPE_ENEMY_KILLCAMERA,	//プレイヤーを捕まえた時
		MOTIONTYPE_ENEMY_MAX
	} MOTIONTYPE_ENEMY;

	typedef enum
	{
		ENEMY_STATE_LEVEL1 = 0,	//通常時
		ENEMY_STATE_LEVEL2		//強化時
	} ENEMY_STATE;

	// ---------モデル情報---------- //
	typedef enum
	{//J = JOINT R = RIGHT L = LEFT
		ENEMYTYPE_00_BODY = 0,		// [体]			00
		ENEMYTYPE_01_HEAD,			// [頭]			01
		ENEMYTYPE_02_ARM_L,			// [左腕]		02
		ENEMYTYPE_03_ARM_R,			// [右腕]		03
		ENEMYTYPE_04_LEG_L,			// [左足]		04
		ENEMYTYPE_05_LEG_R,			// [右足]		05
		ENEMYTYPE_MAX				//合計パーツ数
	} ENEMYTYPE;

	typedef enum
	{
		ROT_FORWARD = 0,	// 前方
		ROT_BACKWARD,		// 後方
		ROT_LEFT,			// 左
		ROT_RIGHT			// 右
	} ROT;

	/* 関数 */
	CEnemy();
	~CEnemy();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetRot(D3DXVECTOR3 rot, ROT rotstate);			// 回転更新
	void StopMove(void);			//
	D3DXVECTOR3 GetPos(void);		// 位置取得
	D3DXVECTOR3 GetRot(void);		// 回転取得
	ROT GetEnemyROT(void);			// 敵の現在の回転方向
	static CEnemy * Create();		// 作成
	static void Load(void);			// 読み込み
	static void UnLoad(void);		// UnLoadする

	// ステータス上昇
	void AddLevel(void);
	// 敵の行動AI
	void EnemyAI(void);
	// 床との判定
	void EnemyColi(void);
	// 進行方向の決定
	void Direction(void);
	// 後方を求める
	void SeekBackwards(void);

	static bool GetEndFlag(void);	// フラグの取得
	static void SetFreezeFlag(void);

protected:
private:
	/* 関数 */
	void Move(void);				// 移動
	void Rot(ROT rot);				// 回転
	void Motion(void);				// モーション
	void RotInertia(void);			// 回転慣性
	static void SetEndFlag(void);	// 捕まえた時フラグをtrue

	/* 変数 */
	static CLoad				*m_pload;							// ロード
	static CModel_info			*m_pModel_info;						// モデル情報の保存
	static MODEL_OFFSET			*m_pModel_offset;					// モデルの初期配置
	static MOTION				*m_pMotion;							// モーション情報の保存

	static bool					m_bFreeze;							//

	CModel 						*m_pModel[ENEMYTYPE_MAX] = {};		// モデル
	D3DXMATRIX					m_mtxWorld;							// 行列
	D3DXVECTOR3					m_pos;								// 位置
	D3DXVECTOR3					m_posold;							// 前の位置
	D3DXVECTOR3					m_move;								// 移動量
	D3DXVECTOR3					m_rot;								// 現在回転量
	D3DXVECTOR3					m_rotLast;							// 向きたい方向
	D3DXVECTOR3					m_rotbetween;						// 回転の差分
	D3DXVECTOR3					m_size;								// モデルのサイズ
	int							m_nMaxModel;						// 最大モデル数
	int							m_nMotiontype;						// モーションタイプ
	int							m_nMotiontypeOld;					// 前回のモーションタイプ
	int							m_nMaxMotion;						// 最大モーション数
	int							m_keyinfoCnt;						// キー情報のカウント
	int							m_nFrame;							// フレームカウント
	bool						m_bStopMove;						// 動きを止める
	bool						m_bJudg;
	bool						m_bProcessing;
	CFloarTile					*m_pFloarTile;
	CFloarTile					*m_pFloarTile_One;
	bool						m_bUse;
	int							m_nResult;							// ランダム結果
	int							m_nCount;
	static	bool				m_bCaught;							// プレイヤーを捕まえた時のフラグ
	bool						m_bForward;							// 前方
	bool						m_bBackward;						// 後方
	bool						m_bLeft;								// 左
	bool						m_bRight;							// 右
	ROT							m_RotState;							// 現在向いている方向
	ROT							m_RotCurrentB;						// 現在の後方
	ROT							m_RotPossible;						// 進行できる方向
	int							m_nDirectionCnt;					// 進行できる方向の数
	bool						m_bStopFlag;
	int							m_FreezeCnt;

};
#endif

