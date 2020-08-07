// =====================================================================================================================================================================
//
// プレイヤーの処理 [player.h]
// Author :
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

// =====================================================================================================================================================================
// プレイヤークラス
// =====================================================================================================================================================================
class CPlayer :public CCharacter
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

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void DebugInfo(void);
	void MoveUpdate(void);
	void CollisionUpdate(void);
	void AttackUpdate(void);
	void PadMoveUpdate(void);
	void ReSpawn(void);
	void DamageReaction();
	void DeathReaction();
	void StateChangeReaction();
	DEBUG_STATE GetDebugState(void);
	bool DefaultMotion(void);
	void MapChangePlayerRespawn();

	/* 設定 取得 関数 */
	CGun			*GetGun()						{ return  m_pGun; };			// 銃のポインタ取得
	CGrenadeFire	*GetGrenadeFire()				{ return  m_pGrenadeFire; };	// グレネード発射位置のポインタ取得
	CPlayerUI		*GetPlayerUI()					{ return  m_pPlayerUI; };		// プレイヤーUIのポインタ取得
	void			SetRideFlag(bool bRide)			{ m_bRideVehicle = bRide; };	// ライドフラグの設定
	bool			GetRideFlag()					{ return m_bRideVehicle; };		// ライドフラグの取得
	void			SetRespawnFlag(bool bRespawn)	{ m_bRespawn = bRespawn; };		// リスポーンフラグ取得
	bool			GetRespawnFlag()				{ return m_bRespawn; };			// リスポーンフラグの設定

	/* 静的メンバ関数 */
	static CPlayer *Create(void);					// 生成
	static	void	PlayerLoad();					// プレイヤーのロード
private:
	/* 静的メンバ関数 */
	static void		SetPlayerData();				// 読み込んだデータの設定

	/* メンバ関数 */
	void Move(float move, float fdest);				//
	void Ride();									//

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
	static			D3DXVECTOR3						m_pos[2];				// 初期座標

	/* メンバ変数 */
	D3DXVECTOR3		m_ShotRot;							//撃つ向き
	DEBUG_STATE		m_DebugState;						// デバッグのステータス
	bool			m_bAttack;							// 近接攻撃できるかどうか
	bool			m_bKnifeAttack;						// 攻撃をしているかどうか
	bool			m_bRespawn;							// リスポーンフラグ
	float			m_Angle;							// アングル
	bool			m_bCruch;							// クラッチ
	WORD			Oldstate;							// コントローラーの1frame前のステート
	CGun			*m_pGun;							// ガンクラスのポインタ
	CGrenadeFire	*m_pGrenadeFire;					// グレネード発射クラスのポインタ
	CPlayerUI		*m_pPlayerUI;						// プレイヤーUIのポインタ
	CKnife			*m_pKnife;							// ナイフのポインタ
	bool			m_bRideVehicle;						// 乗り物に乗り込んでいるかどうかのフラグ
};
#endif