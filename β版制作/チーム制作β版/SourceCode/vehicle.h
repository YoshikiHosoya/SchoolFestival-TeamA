// =====================================================================================================================================================================
//
// 乗り物の処理 [vehicle.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _VEHICLE_H_
#define _VEHICLE_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define MAX_VEHICLE_MODEL (20)			// 乗り物モデルのパーツ数

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CModel;
class CCollision;

// =====================================================================================================================================================================
// 乗り物のパラメーター
// =====================================================================================================================================================================
typedef struct
{
}VEHICLE_PARAM;

// =====================================================================================================================================================================
// 乗り物クラス
// =====================================================================================================================================================================
class CVehicle :public CScene
{
public:
	/* 乗り物の状態 */
	typedef enum
	{
		VEHICLE_STATE_NORMAL = 0,							// 通常状態
		VEHICLE_STATE_DAMAGE,								// ダメージを受けたとき
		VEHICLE_STATE_INVINCIBLE,							// 無敵 乗り降りする際の無敵判定
		VEHICLE_STATE_BREAK,								// 破壊されるとき
		VEHICLE_STATE_MAX
	}VEHICLE_STATE;

	/* 乗り物の種類 */
	typedef enum
	{
		VEHICLE_TYPE_TANK,									// 戦車
		VEHICLE_TYPE_MAX									// 乗り物の最大数
	}VEHICLE_TYPE;

	/* 乗り物を使うキャラクターの種類 */
	//typedef enum
	//{
	//	VEHICLE_USE_TYPE_TYPE_PLAYER,						// プレイヤー用乗り物
	//	VEHICLE_USE_TYPE_TYPE_ENEMY,						// エネミー用乗り物
	//	VEHICLE_USE_TYPE_TYPE_BOSS,							// ボス用乗り物
	//	VEHICLE_USE_TYPE_TYPE_MAX							// 乗り物を使うキャラクターの最大数
	//}VEHICLE_USE_TYPE;

	/* 乗り物モデルのモーション */
	typedef enum
	{
		VEHICLE_BEHAVIOR_NORMAL = 0,						// 通常状態
		VEHICLE_BEHAVIOR_MOVE,								// 移動
		VEHICLE_BEHAVIOR_SQUAT,								// しゃがみ プレイヤー乗り込み時
		VEHICLE_BEHAVIOR_JUMP,								// ジャンプ
		VEHICLE_BEHAVIOR_CANNON,							// キャノン法
		VEHICLE_BEHAVIOR_MAX								// 最大数
	}VEHICLE_BEHAVIOR_STATE;

	/* 乗り物モデルの向き */
	typedef enum
	{
		VEHICLE_LEFT,										//左向き
		VEHICLE_RIGHT,										//右向き
		VEHICLE_UP,											//上向き
		VEHICLE_DOWN,										//下向き
	}VEHICLE_DIRECTION;

	/* モデルパーツの回転種類 */
	typedef enum
	{
		MODEL_ROT_TYPE_NONE = 0,							// 無回転
		MODEL_ROT_TYPE_ALWAYS,								// 条件無しで常に回転している
		MODEL_ROT_TYPE_MOVING,								// 移動している時のみ
		MODEL_ROT_TYPE_OPERATION,							// 銃口を操作している時のみ
	}PARTS_ROT_TYPE;

	/* メンバ関数 */
	CVehicle(OBJ_TYPE type);								// コンストラクタ
	~CVehicle();											// デストラクタ
	HRESULT Init(void);										// 初期化
	void	Uninit(void);									// 終了
	void	Update(void);									// 更新
	void	Draw(void);										// 描画

	void AddDamage			(int Damage);					// ダメージ計算
	void Move				(float move, float fdest);		// 移動
	void					VehiclePartsRotCondition(
							CModel *pModel,
							PARTS_ROT_TYPE type);			// パーツを回転させるための条件

	/* オフセット読み込み関数 */
	void LoadOffset			(VEHICLE_TYPE nType);			// オフセットの読み込み

	/* パラメータ設定関数 */
	void SetPosition		(D3DXVECTOR3 pos)						{ m_pos = pos; };						// 座標の設定
	void SetPotisionOld		(D3DXVECTOR3 posOld)					{ m_posOld = posOld; };					// 一フレーム前の座標の設定
	void SetMove			(D3DXVECTOR3 move)						{ m_move = move; };						// 移動量の設定
	void SetRot				(D3DXVECTOR3 rot)						{ m_rot = rot; };						// 回転量の設定
	void SetRotDest			(D3DXVECTOR3 rotDest)					{ m_rotDest = rotDest; };				// 回転量の設定
	void SetLife			(int nLife)								{ m_nLife = nLife; };					// 体力の設定
	void SetJump			(bool bJump)							{ m_bJump = bJump; };					// ジャンプフラグの設定
	void SetState			(VEHICLE_STATE state)					{ m_state = state; };					// 乗り物の状態の設定
	void SetBehaviorState	(VEHICLE_BEHAVIOR_STATE state)			{ m_Behaviorstate = state; };			// 乗り物の状態の設定
	void SetMtxWorld		(D3DXMATRIX mtxWorld)					{ m_mtxWorld = mtxWorld; };				// ワールドマトリックスの設定
	void SetVehicleType		(VEHICLE_TYPE CharaType)				{ m_VehicleType = CharaType; };			// 乗り物の種類の設定
	void SetGravity			(bool gravity)							{ m_bGravity = gravity; };//			// 重力の設定
	void SetVehicleDirection(VEHICLE_DIRECTION direction)			{ m_VehicleDirection = direction; };	// 乗り物の向きの設定
	void SetShotDirection	(D3DXVECTOR3 direction)					{ m_ShotRot = direction; };				// 弾を撃つ方向の設定
	void SetDieFlag			(bool DieFlag)							{ m_bDieFlag = DieFlag; };				// 死亡フラグの設定

	/* パラメータ取得関数 */
	D3DXVECTOR3				&GetPosition()							{ return m_pos; };						// 座標の取得
	D3DXVECTOR3				&GetPositionOld()						{ return m_posOld; };					// 1フレーム前の座標の取得
	D3DXVECTOR3				&GetMove()								{ return m_move; };						// 移動量の取得
	D3DXVECTOR3				&GetRot()								{ return m_rot; };						// 回転量の取得
	D3DXVECTOR3				&GetRotDest()							{ return m_rotDest; };					// 回転量の取得
	VEHICLE_STATE			GetVehicleState()						{ return m_state; };					// 乗り物の状態を取得
	D3DXMATRIX				*GetMtxWorld()							{ return &m_mtxWorld; };				// ワールドマトリックスの取得
	D3DXVECTOR3				GetShotDirection()						{ return m_ShotRot; };					// 弾を撃つ方向の取得
	int						GetLife()								{ return m_nLife; };					// 体力の取得
	bool					GetJump()								{ return m_bJump; };					// ジャンプフラグの取得
	bool					GetGravity()							{ return m_bGravity; };					// 重力の取得
	VEHICLE_TYPE			GetVehicleType()						{ return m_VehicleType; };				// キャラクターの種類取得
	std::vector<CModel*>	&GetVehicleModelList()					{ return m_vModelList; };				// キャラクターのモデル取得
	CModel					*GetVehicleModelPartsList(int nCnt)		{ return m_vModelList[nCnt]; };			// キャラクターのモデルパーツ取得
	VEHICLE_DIRECTION		GetVehicleDirection()					{ return m_VehicleDirection; };			// 向きの取得
	char					*GetOffsetFileName(VEHICLE_TYPE type)	{ return m_LoadOffsetFileName[type]; }; // オフセットのファイル名取得
	bool					GetDieFlag()							{ return m_bDieFlag; };					// 死亡フラグの取得
	CCollision				*GetCollision()							{ return m_pCollision; };				// 当たり判定のポインタ取得

	/* 静的メンバ関数 */

	/* メンバ関数 */
	void					DebugInfo(void);						// デバッグ用関数

protected:

private:
	/* メンバ関数 */
	virtual void			Inertia();								// 慣性処理
	void					Gravity();								// 重力処理
	void					Rot();									// 回転量計算
	void					State();								// 状態別処理
	void					ShotDirection();						// 弾を撃つ方向の計算
	void					WheelRot(CModel *pModel);				// 車輪モデルの回転処理
	void					GunRot(CModel *pModel);					// 銃モデルの回転処理
	void					VehiclePartsRot(
											CModel *pModel,
											float fRot);			// 種類や条件ごとのパーツの回転処理
	void					VehiclePartsRotLimit(
												CModel *pModel,
												float fRot);		// 種類や条件ごとのパーツの回転処理 回転上限


	/* 静的メンバ変数 */
	static char *m_LoadOffsetFileName[VEHICLE_TYPE_MAX];			// 読み込むオフセットファイル名

	/* メンバ変数 */
	std::vector<CModel*>	m_vModelList;							// 可変長配列 設置したモデル
	D3DXVECTOR3				m_rotBET[MAX_VEHICLE_MODEL];			// 回転
	D3DXVECTOR3				m_pos;									// 位置
	D3DXVECTOR3				m_posOld;								// 前の位置
	D3DXVECTOR3				m_move;									// 移動量
	D3DXVECTOR3				m_rot;									// 回転
	D3DXVECTOR3				m_rotDest;								// 回転する差分
	D3DXVECTOR3				m_ShotRot;								// 撃つ向き
	D3DXVECTOR3				m_AddRot;								// 回転量を加算
	D3DXMATRIX				m_mtxWorld;								// マトリックス
	VEHICLE_STATE			m_state;								// 乗り物の状態
	VEHICLE_BEHAVIOR_STATE	m_Behaviorstate;						// 乗り物の行動状態
	VEHICLE_TYPE			m_VehicleType;							// キャラクターのタイプ
	int						m_nLife;								// 体力
	int						m_nStateCnt;							// 状態のカウント
	VEHICLE_DIRECTION		m_VehicleDirection;						// キャラクターの向き
	PARTS_ROT_TYPE			m_RotType;								// パーツが回転する種類
	bool					m_bJump;								// ジャンプフラグ
	bool					m_bGravity;								// 重力をかけるかのフラグ
	bool					m_bDieFlag;								// 死亡フラグ
	CCollision				*m_pCollision;							// 当たり判定のポインタ
};
#endif
