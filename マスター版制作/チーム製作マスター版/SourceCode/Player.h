// =====================================================================================================================================================================
//
// プレイヤーの処理 [player.h]
// Author :Hanzawa
//
// =====================================================================================================================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_
// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "Character.h"

// =====================================================================================================================================================================
// プレイヤーのデータ
// =====================================================================================================================================================================
typedef struct
{
	int				nLife;			// 体力
	int				nRespawnCnt;	// リスポーンまでのカウント
	float			fRunSpeed;		// 走るスピード
	float			fCrouchSpeed;	// しゃがみ歩き時のスピード
	float			fJump;			// 通常時のジャンプ
	float			fRideJump;		// 乗車中のジャンプ
	D3DXVECTOR3		pos;			// 初期座標
}PLAYER_DATA;

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CModel;
class CMeshOrbit;
class CParticle;
class CUI;
class CGun;
class CGrenadeFire;
class CPrisoner;
class CKnife;
class CPlayerUI;
class CVehicle;

// =====================================================================================================================================================================
// プレイヤークラス
// =====================================================================================================================================================================
class CPlayer :public CCharacter, public CGameObject
{
public:
	// デバッグ時のステート
	typedef enum
	{
		DEBUG_NORMAL = 0,			//通常
		DEBUG_CREATE_MAP,			//マップ作成
		DEBUG_CREATE_ENEMY,			//エネミー作成
		DEBUG_MAX					//最大数
	}DEBUG_STATE;

	// プレイヤーの人数
	enum PLAYER_NUM
	{
		PLAYER_NUM_NONE,
		PLAYER_NUM_ONE = 1,						// 1人プレイ選択
		PLAYER_NUM_TWO = 2,						// 2人プレイ選択
		PLAYER_NUM_MAX = 2						// 最大数
	};

	/* メンバ関数 */
	CPlayer() {};
	CPlayer(OBJ_TYPE type);
	virtual ~CPlayer();

	virtual HRESULT Init(void) override;				//初期化
	virtual void Uninit(void) override;					//終了
	virtual void Update(void) override;					//更新
	virtual void Draw(void) override;					//描画
	virtual void DebugInfo(void) override;				//デバッグ情報表記

	void DrawWepon(void);								//武器の描画
	void MoveUpdate(void);								//移動に関する更新
	void CollisionUpdate(void);							//当たり判定に関する更新
	void AttackUpdate(void);							//攻撃に関する更新
	void PadMoveUpdate(void);							//パッドによる移動
	void ReSpawn(void);									//リスポーン処理

	void DamageReaction() override;						//ダメージ受けた時のリアクション
	void DeathReaction() override;						//死亡時のリアクション
	void StateChangeReaction() override;				//状態が変わった時のリアクション
	bool DefaultMotion(void) override;					//デフォルトのモーションセット
	void State() override;								//ステートに応じた処理

	DEBUG_STATE GetDebugState(void);					//STATE取得
	void MapChangePlayerRespawn();						//マップ遷移時のプレイヤー設定
	void ResetPlayer();									//プレイヤー初期状態にリセット

	/* 設定 取得 関数 */
	void			SetRideFlag(bool bRide)			{ m_bRideVehicle = bRide; };	// ライドフラグの設定
	void			SetRespawnFlag(bool bRespawn)	{ m_bRespawn = bRespawn; };		// リスポーンフラグ取得
	static			void SetTwoPPlayFlag(bool flag)	{ m_bTwoPPlay = flag; };	// 2人プレイなのかの設定
	CGun			*GetGun()						{ return  m_pGun; };			// 銃のポインタ取得
	CGrenadeFire	*GetGrenadeFire()				{ return  m_pGrenadeFire; };	// グレネード発射位置のポインタ取得
	CPlayerUI		*GetPlayerUI()					{ return  m_pPlayerUI; };		// プレイヤーUIのポインタ取得
	bool			GetRideFlag()					{ return m_bRideVehicle; };		// ライドフラグの取得
	bool			GetRespawnFlag()				{ return m_bRespawn; };			// リスポーンフラグの設定
	static			bool GetTwoPPlayFlag()			{ return m_bTwoPPlay; };		// 2人プレイしているかのフラグの取得

	/* 静的メンバ関数 */

	static CPlayer *Create(TAG Tag);	// 生成
	static	void	PlayerLoad();					// プレイヤーのロード
private:
	/* 静的メンバ関数 */

	/* メンバ関数 */
	void Ride();									// 乗り物に乗っている時

	/* 静的メンバ変数 */
	static			PLAYER_DATA		m_PlayerData;		// プレイヤーのデータ
	static			char			*m_PlayerFileName;	// ランキングのファイル名
	static			bool			m_bTwoPPlay;		// 2人プレイしているかどうか

	/* メンバ変数 */
	int				m_nRespawnCnt;						// リスポーンまでのカウント復活までのカウント
	D3DXVECTOR3		m_ShotRot;							//撃つ向き
	DEBUG_STATE		m_DebugState;						// デバッグのステータス
	bool			m_bAttack;							// 近接攻撃できるかどうか
	bool			m_bKnifeAttack;						// 攻撃をしているかどうか
	bool			m_bRespawn;							// リスポーンフラグ
	bool			m_bCruch;							// クラッチ
	bool			m_bRideVehicle;						// 乗り物に乗り込んでいるかどうかのフラグ

	WORD			Oldstate;							// コントローラーの1frame前のステート
	CGun			*m_pGun;							// ガンクラスのポインタ
	CGrenadeFire	*m_pGrenadeFire;					// グレネード発射クラスのポインタ
	CPlayerUI		*m_pPlayerUI;						// プレイヤーUIのポインタ
	CKnife			*m_pKnife;							// ナイフのポインタ

	CVehicle		*m_pVehicle;						// 乗り物クラスのポインタ
	CXInputPad		*m_pPad;							// パッドのポインタ
};
#endif