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
class CPlayer;

// =====================================================================================================================================================================
// 乗り物のパラメーター
// =====================================================================================================================================================================
typedef struct
{
}VEHICLE_PARAM;

// =====================================================================================================================================================================
// 乗り物クラス
// =====================================================================================================================================================================
class CVehicle
{
public:
	/* 乗り物の種類 */
	typedef enum
	{
		VEHICLE_TYPE_TANK,									// 戦車
		VEHICLE_TYPE_PLANE,									// 戦闘機
		VEHICLE_TYPE_HELICOPTER,							// ヘリコプター
		VEHICLE_TYPE_MAX									// 乗り物の最大数
	}VEHICLE_TYPE;

	/* 戦車の挙動 */
	typedef enum
	{
		VEHICLE_BEHAVIOR_NORMAL = 0,						// 通常状態
		VEHICLE_BEHAVIOR_MOVE,								// 移動
		VEHICLE_BEHAVIOR_SQUAT,								// しゃがみ プレイヤー乗り込み時
		VEHICLE_BEHAVIOR_JUMP,								// ジャンプ
		VEHICLE_BEHAVIOR_CANNON,							// キャノン法
		VEHICLE_BEHAVIOR_MAX								// 最大数
	}VEHICLE_BEHAVIOR_STATE;

	/* モデルパーツの回転種類 */
	typedef enum
	{
		MODEL_ROT_TYPE_NONE = 0,							// 無回転
		MODEL_ROT_TYPE_ALWAYS,								// 条件無しで常に回転している
		MODEL_ROT_TYPE_MOVING,								// 移動している時のみ
		MODEL_ROT_TYPE_OPERATION,							// 銃口を操作している時のみ
	}PARTS_ROT_TYPE;

	/* メンバ関数 */
	CVehicle();								// コンストラクタ
	~CVehicle();											// デストラクタ

	//virtual void			SetPlayerTank(CPlayer *pPlayer)	{ m_pPlayer = pPlayer; };	//プレイヤーのポインタ設定
	//CPlayer					*GetPlayer(void)				{return m_pPlayer; };
	void SetRideerTag(TAG tag) { m_RideerTag = tag; };
	TAG GetRideerTag(void) { return m_RideerTag; };
	void					VehiclePartsRotCondition(
							CModel *pModel,
							PARTS_ROT_TYPE type,
							D3DXVECTOR3 move,
							D3DXVECTOR3 rot,
							DIRECTION direction);			// パーツを回転させるための条件

	/* パラメータ設定関数 */
	void SetBehaviorState	(VEHICLE_BEHAVIOR_STATE state)			{ m_Behaviorstate = state; };			// 乗り物の状態の設定
	void SetVehicleType		(VEHICLE_TYPE CharaType)				{ m_VehicleType = CharaType; };			// 乗り物の種類の設定

	/* パラメータ取得関数 */
	VEHICLE_TYPE			GetVehicleType()						{ return m_VehicleType; };				// キャラクターの種類取得
	char					*GetOffsetFileName(VEHICLE_TYPE type)	{ return m_LoadOffsetFileName[type]; }; // オフセットのファイル名取得

	/* 静的メンバ関数 */

	/* メンバ関数 */
	void					DebugInfo(void);						// デバッグ用関数

protected:

private:
	/* メンバ関数 */
	void					WheelRot(CModel *pModel, D3DXVECTOR3 move);										// 車輪モデルの回転処理
	void					GunRot(CModel *pModel, D3DXVECTOR3 shotrot,DIRECTION direction);					// 銃モデルの回転処理
	void					VehiclePartsRot(
											CModel *pModel,
											float fRot);			// 種類や条件ごとのパーツの回転処理
	void					VehiclePartsRotLimit(
												CModel *pModel,
												float fRot);		// 種類や条件ごとのパーツの回転処理 回転上限
	/* 静的メンバ変数 */
	static char *m_LoadOffsetFileName[VEHICLE_TYPE_MAX];			// 読み込むオフセットファイル名

	/* メンバ変数 */
	//std::vector<CModel*>	m_vModelList;							// 可変長配列 設置したモデル
	VEHICLE_BEHAVIOR_STATE	m_Behaviorstate;						// 乗り物の行動状態
	VEHICLE_TYPE			m_VehicleType;							// キャラクターのタイプ
	PARTS_ROT_TYPE			m_RotType;								// パーツが回転する種類
	int						m_nGravityCnt;							// 重力用カウント
	CPlayer				*m_pPlayer;							// プレイヤーのポインタ
	TAG	m_RideerTag;

};
#endif
