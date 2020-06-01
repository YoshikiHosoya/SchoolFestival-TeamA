//=============================================================================
//
// タイトル用敵モデル処理 [titleenemy.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _TITLEENEMY_H_
#define _TITLEENEMY_H_

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

//=============================================================================
// クラス
//=============================================================================
class CTitleEnemy : public CScene
{
public:
	// ---------モーションタイプ---------- //
	typedef enum
	{
		MOTIONTYPE_TITLE_ENEMY_WAIT = 0,		//待機モーション
		MOTIONTYPE_TITLE_ENEMY_RUN,				//移動モーション(走り)
		MOTIONTYPE_TITLE_ENEMY_KILLCAMERA,		//プレイヤーを捕まえた時
		MOTIONTYPE_TITLE_ENEMY_MAX
	} MOTIONTYPE_TITLE_ENEMY;

	typedef enum
	{
		ENEMY_STATE_LEVEL1 = 0,	//通常時
		ENEMY_STATE_LEVEL2		//強化時
	} TITLE_ENEMY_STATE;

	// ---------モデル情報---------- //
	typedef enum
	{//J = JOINT R = RIGHT L = LEFT
		TITLE_ENEMYTYPE_00_BODY = 0,		// [体]			00
		TITLE_ENEMYTYPE_01_HEAD,			// [頭]			01
		TITLE_ENEMYTYPE_02_ARM_L,			// [左腕]		02
		TITLE_ENEMYTYPE_03_ARM_R,			// [右腕]		03
		TITLE_ENEMYTYPE_04_LEG_L,			// [左足]		04
		TITLE_ENEMYTYPE_05_LEG_R,			// [右足]		05
		TITLE_ENEMYTYPE_MAX				//合計パーツ数
	} TITLE_ENEMYTYPE;

	/* 関数 */
	CTitleEnemy();
	~CTitleEnemy();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	D3DXVECTOR3 GetPos(void);		// 位置取得
	D3DXVECTOR3 GetRot(void);		// 回転取得
	static CTitleEnemy * Create();	// 作成
	static void Load(void);			// 読み込み
	static void UnLoad(void);		// UnLoadする
	void ReleaseTEne(void);			// 削除
	void SetMotion(void);			// モーション

protected:
private:
	/* 関数 */
	/* 変数 */
	static CLoad				*m_pload;							// ロード
	static CModel_info			*m_pModel_info;						// モデル情報の保存
	static MODEL_OFFSET			*m_pModel_offset;					// モデルの初期配置
	static MOTION				*m_pMotion;							// モーション情報の保存

	CModel 						*m_pModel[TITLE_ENEMYTYPE_MAX] = {};		// モデル

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
	CCollision					*m_pCollision;						// 当たり判定情報
};
#endif
