//=============================================================================
//
// モデル処理 [player.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

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
#define PLAYERCOLLISION_SIZE (60.0f)

//=============================================================================
// 前方宣言
//=============================================================================

//=============================================================================
// クラス
//=============================================================================
class CPlayer : public CScene
{
public:
	// ---------モーションタイプ---------- //
	typedef enum
	{
		MOTIONTYPE_WAIT = 0,
		MOTIONTYPE_JUMP,
		MOTIONTYPE_LANDING,
		MOTIONTYPE_LANDING_FAIL1,
		MOTIONTYPE_LANDING_FAIL2,
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	typedef enum
	{
		PLAYER_STATE_NORMAL = 0,
		PLAYER_STATE_DAMAGE,
		PLAYER_STATE_DIE
	} PLAYER_STATE;

	// ---------モデル情報---------- //
	typedef enum
	{
		PLAYERTYPE_00_RION_BODY = 0,
		PLAYERTYPE_01_RION_HEAD,
		PLAYERTYPE_MAX
	} PLAYERTYPE;

	typedef enum
	{
		COLLISION_LOCATION_LEFT = 0,	//左
		COLLISION_LOCATION_RIGHT,		//右
		COLLISION_LOCATION_BACK,		//奥
		COLLISION_LOCATION_FRONT,		//表
		COLLISION_LOCATION_MAX
	} COLLISION_LOCATION;

	/* 関数 */
	CPlayer();
	~CPlayer();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPos(void);				// 位置取得
	D3DXVECTOR3 GetRot(void);				// 回転取得
	static CPlayer * Create();				// 作成
	static void Load(void);					// 読み込み
	static void UnLoad(void);				// UnLoadする
	// 制限区域
	void Restriction(void);

	bool GetbCol(void);
	D3DXVECTOR3 GetMove(void);

	void SetAbilityPoint(void);
	bool GetAbilityFlag(void);

protected:
private:
	/* 関数 */
	void Move(void);				// 移動
	void Ability(void);				// 能力

	/* 変数 */
	static CModel_info			*m_pModel_info;						// モデル情報の保存
	static MODEL_OFFSET			*m_pModel_offset;					// モデルの初期配置
	static MOTION				*m_pMotion;							// モーション情報の保存
	CModel 						*m_pModel[PLAYERTYPE_MAX] = {};		// モデル
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
	// 当たり判定
	CCollision					*m_pCollision;						// 当たり判定情報

	bool						m_bRun;

	int							m_nAbilityPoint;					// 能力を使うためのポイント
	int							m_nCoolTime;
	bool						m_bAbilityFlag;
};
#endif
