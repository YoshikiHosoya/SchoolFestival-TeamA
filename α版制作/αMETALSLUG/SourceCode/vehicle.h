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
// 前方宣言
// =====================================================================================================================================================================
class CModel;
// =====================================================================================================================================================================
// 捕虜クラス
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

	/* 乗り物を使うキャラクターの種類 */
	typedef enum
	{
		VEHICLE_USE_TYPE_TYPE_PLAYER,						// プレイヤー用乗り物
		VEHICLE_USE_TYPE_TYPE_ENEMY,						// エネミー用乗り物
		VEHICLE_USE_TYPE_TYPE_BOSS,							// ボス用乗り物
		VEHICLE_USE_TYPE_TYPE_MAX							// 乗り物を使うキャラクターの最大数
	}VEHICLE_USE_TYPE;

	/* 乗り物の種類 */
	typedef enum
	{
		VEHICLE_TYPE_TYPE_TANK,								// 戦車
		VEHICLE_TYPE_TYPE_UNKNOWN,							// 不明
		VEHICLE_TYPE_TYPE_MAX
	}VEHICLE_TYPE;

	/* 乗り物のキー要素 */
	typedef struct KEY
	{
		D3DXVECTOR3 pos;									// 位置
		D3DXVECTOR3 rot;									// 回転

		//コンストラクタ　情報の初期化
		KEY()
		{
			pos = ZeroVector3;
			rot = ZeroVector3;
		}
	}KEY;

	/* 乗り物のキー情報 */
	typedef struct KEY_INFO
	{
		int nFram;											// フレーム数
		std::vector<KEY*> key;								// キー情報

		//コンストラクタ
		KEY_INFO()
		{
			nFram = 60;
			key = {};
		}
	}KEY_INFO;

	/* 乗り物モデルのモーション情報 */
	typedef struct
	{
		int nLoop;											// ループ
		int nNumKey;										// キー情報の数
		std::vector<KEY_INFO*> key_info;
	}VEHICLE_MOTION;

	/* 乗り物モデルのモーション */
	typedef enum
	{
		VEHICLE_MOTION_STATE_NONE = -1,						// 何もしない状態
		TANK_MOTION_NORMAL = 0,								// ニュートラル
		TANK_MOTION_MOVE,									// 移動
		TANK_MOTION_SQUAT,									// しゃがみ プレイヤー乗り込み時
		TANK_MOTION_JUMP,									// ジャンプ
		TANK_MOTION_CANNON,									// キャノン法

		VEHICLE_MOTION_MAX									// 最大数
	}VEHICLE_MOTION_STATE;








	CVehicle(OBJ_TYPE type);								// コンストラクタ
	~CVehicle();											// デストラクタ

	/* メンバ関数 */
	HRESULT Init(void);										// 初期化
	void	Uninit(void);									// 終了
	void	Update(void);									// 更新
	void	Draw(void);										// 描画

	/* 静的メンバ関数 */

	/* メンバ関数 */
	void				DebugInfo(void);					// デバッグ

private:
	/* メンバ関数 */
	/* メンバ変数 */
};
#endif
