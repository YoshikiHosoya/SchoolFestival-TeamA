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

	/* メンバ関数 */
	CPlayer(OBJ_TYPE type);
	~CPlayer();

	HRESULT Init(void);						//初期化
	void Uninit(void);						//終了
	void Update(void);						//更新
	void Draw(void);						//描画
	void DrawWepon(void);					//武器の描画
	void DebugInfo(void);					//デバッグ情報表記
	void MoveUpdate(void);					//移動に関する更新
	void CollisionUpdate(void);				//当たり判定に関する更新
	void AttackUpdate(void);				//攻撃に関する更新
	void PadMoveUpdate(void);				//パッドによる移動
	void ReSpawn(void);						//リスポーン処理
	void DamageReaction();					//ダメージ受けた時のリアクション
	void DeathReaction();					//死亡時のリアクション
	void StateChangeReaction();				//状態が変わった時のリアクション
	DEBUG_STATE GetDebugState(void);		//STATE取得
	bool DefaultMotion(void);				//デフォルトのモーションセット
	void MapChangePlayerRespawn();			//マップ遷移時のプレイヤー設定
	void ResetPlayer();						//プレイヤー初期状態にリセット
	void State();							//ステートに応じた処理

	/* 設定 取得 関数 */
	void			SetRideFlag(bool bRide)			{ m_bRideVehicle = bRide; };	// ライドフラグの設定
	void			SetRespawnFlag(bool bRespawn)	{ m_bRespawn = bRespawn; };		// リスポーンフラグ取得
	CGun			*GetGun()						{ return  m_pGun; };			// 銃のポインタ取得
	CGrenadeFire	*GetGrenadeFire()				{ return  m_pGrenadeFire; };	// グレネード発射位置のポインタ取得
	CPlayerUI		*GetPlayerUI()					{ return  m_pPlayerUI; };		// プレイヤーUIのポインタ取得
	bool			GetRideFlag()					{ return m_bRideVehicle; };		// ライドフラグの取得
	bool			GetRespawnFlag()				{ return m_bRespawn; };			// リスポーンフラグの設定


	/* 静的メンバ関数 */

	static CPlayer *Create(TAG Tag);	// 生成
	static	void	PlayerLoad();					// プレイヤーのロード
private:
	/* 静的メンバ関数 */
	static void		SetPlayerData();				// 読み込んだデータの設定

	/* メンバ関数 */
	void Ride();									// 乗り物に乗っている時

	/* 静的メンバ変数 */
	static			PLAYER_DATA		m_PlayerData;		// プレイヤーのデータ
	static			char			*m_PlayerFileName;	// ランキングのファイル名

	/* 読み込んだデータを格納するメンバ変数 */
	static			int				m_nLife[2];			// 体力初期残機
	static			int				m_nRespawnCnt;		// リスポーンまでのカウント復活までのカウント
	static			float			m_fRunSpeed;		// 走るスピード
	static			float			m_fCrouchSpeed;		// しゃがみ歩き時のスピード
	static			float			m_fJump;			// 通常時のジャンプ
	static			float			m_fRideJump;		// 乗車中のジャンプ
	static			D3DXVECTOR3		m_pos[2];			// 初期座標

	/* メンバ変数 */
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