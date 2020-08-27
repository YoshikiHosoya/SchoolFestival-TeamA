// =====================================================================================================================================================================
//
// ボス1の処理 [boss_one.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _BOSS_ONE_H_
#define _BOSS_ONE_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "enemy.h"

// =====================================================================================================================================================================
// ボス1のデータ
// =====================================================================================================================================================================
typedef struct
{
	int					nLife;					// 体力
	int					nCoolTime;				// クールタイム
	D3DXVECTOR3			CollisionSize[2];		// 当たり判定のサイズ
	D3DXVECTOR3			GunShotOfsetPos[3];		// ガンのオフセット座標
} BOSS_ONE_DATA;

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CModel;
class CGun;
class CCollision;

// =====================================================================================================================================================================
// 捕虜クラス
// =====================================================================================================================================================================
class CBoss_One :public CEnemy
{
public:
	// ボス1の状態
	enum BOSS_ONE_STATE
	{
		BOSS_ONE_STATE_NONE = -1,									// 初期値 何もしない
		BOSS_ONE_STATE_STAY,										// 何もしない 待機中
		BOSS_ONE_STATE_ATTACK,										// 攻撃する
		BOSS_ONE_STATE_SHIFT_POSTURE,								// 体勢を変える
		BOSS_ONE_STATE_MAX											// 最大数
	};

	// 攻撃の種類
	enum BOSS_ONE_ATTACKTYPE
	{
		ATTACKTYPE_NONE = -1,
		ATTACKTYPE_BALKAN,											// バルカン砲
		ATTACKTYPE_FLAMERADIATION,									// 火炎放射 立ち時のみ
		ATTACKTYPE_INCENDIARY,										// 焼夷弾
		ATTACKTYPE_MAX												// 最大数
	};

	// 姿勢の種類
	enum BOSS_ONE_POSTURETYPE
	{
		POSTURETYPE_STAND,											// 起立
		POSTURETYPE_SQUAT,											// しゃがみ
		POSTURETYPE_MAX												// 最大数
	};

	// 武器の種類
	enum BOSS_ONE_WEAPONTYPE
	{
		WEAPONTYPE_BALKAN,											// バルカン
		WEAPONTYPE_FLAMETHROWER,									// 火炎放射器
		WEAPONTYPE_INCENDIARY,										// 焼夷弾
		WEAPONTYPE_MAX												// 最大数
	};

	CBoss_One(OBJ_TYPE type);										// コンストラクタ
	~CBoss_One();													// デストラクタ

	/* メンバ関数 */
	HRESULT Init(void);												// 初期化
	void	Uninit(void);											// 終了
	void	Update(void);											// 更新
	void	Draw(void);												// 描画

	/* 静的メンバ関数 */
	static	CBoss_One		*Create();								// 生成
	static	void			Boss_One_DataLoad();					// ボス情報のロード
	static	void			SetBoss_OneData();						// ボスのデータ設定

	/* メンバ関数 */
	void					DebugInfo(void);						// デバッグ
	void					Motion(void);							// ボスのパーツの動き
	bool					DefaultMotion(void);					// デフォルトモーション

	// ----- 状態の取得設定 ----- //
	BOSS_ONE_STATE			GetBossOneState()						{ return m_BossOneState; };				// ボスの状態の取得
	BOSS_ONE_ATTACKTYPE		GetBossOneType()						{ return m_AttckType; };				// ボスの攻撃の種類
	void					SetBossState(BOSS_ONE_STATE state)		{ m_BossOneState = state; };			// ボスの状態の設定
	void					SetBossType(BOSS_ONE_ATTACKTYPE type)	{ m_AttckType = type; };				// ボスの攻撃の種類の設定
	CCollision				*GetCollision()							{ return m_pCollision; };				// 当たり判定のポインタ取得

private:
	/* 静的メンバ変数 */
	static char				*m_BossOneFileName;							// ボスのファイル名
	static BOSS_ONE_DATA	m_BossOneData;								// ボスのデータ

	// ステータス用 //
	static int				m_nLife;									// 体力
	static D3DXVECTOR3		m_CollisionSize[POSTURETYPE_MAX];			// 当たり判定の大きさ
	static D3DXVECTOR3		m_GunShotOfsetPos[WEAPONTYPE_MAX];			// ガンのオフセット

	/* メンバ関数 */

	// --- 状態管理関数 ---  //
	void					BossOneStateManager();						// ボスの状態別処理
	void					BossOneAttackManager();						// ボスの攻撃管理処理

	// --- 関数 ---  //
	void					DamageReaction();							// ダメージを受けたときの反応
	void					DeathReaction();							// 死亡した時の処理
	void					StateChangeReaction();						// 状態を変える
	void					Behavior();									// 敵の行動

	void					SetShotIntervalTime(int time)	{ m_nShotIntervalTime = time; };		// インターバルの時間の設定
	void					SetShotCount(int nCount)		{ m_nShotCount = nCount; };				// ショットカウントの時間の設定
	void					SetCoolTime(int time)			{ m_nCoolTime = time;};					// ステートが切り替わるまでの時間の設定
	void					SetTriggerCount(int nCount)		{ m_nTriggerCount = nCount; };			// トリガーのカウントの設定
	void					SetBalkanRot(float fRot)		{ m_fBalkanRot = fRot; };				// バルカンの回転量の設定
	void					SetGunOffsetPos(D3DXVECTOR3 pos);										// ガンのオフセット座標の設定
	D3DXVECTOR3				GetGunOffsetPos(BOSS_ONE_WEAPONTYPE type);								// ガンのオフセット座標の取得
	void					SetGunPos();															// ガンの座標の設定
	void					MoveGun(D3DXVECTOR3 &PartsPos, D3DXVECTOR3 move);						// ガンの移動
	void					Cooltime_Decrease();													// クールタイムの減少
	void					CalcRotationBalkan(const float fTarget, float fCurrent);				// 目標と現在

	float					get_vector_length(D3DXVECTOR3 vectol);									// ベクトルの長さを計算する
	float					dot_product(D3DXVECTOR3 vl, D3DXVECTOR3 vr);							// ベクトル内積
	float					AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);							// ２つのベクトルABのなす角度θを求める

	void					SetFlameThrower(bool bOpen);// 火炎放射器の移動
	void					SetBalkan(bool bOpen);// バルカンの移動


	// --- 攻撃管理関数 ---  //
	void					ShotIncendiary();														// 焼夷弾
	void					ShotBalkan();															// バルカン
	void					ShotWarning();															// 焼夷弾の最初の爆発
	void					ShotFlameRadiation();													// フレイム火炎放射器

	void					ShotFlameManager();														// 火炎放射の管理

	void					RandomAttack();															// 攻撃方法をランダムに決める
	void					SetRotBalkan();															// バルカンの回転
	uint64_t				get_rand_range(uint64_t min_val, uint64_t max_val);						// ランダム関数 範囲

	/* メンバ変数 */
	CGun					*m_pGun[WEAPONTYPE_MAX];			// ガンクラスのポインタ
	CCollision				*m_pCollision;						// 当たり判定のポインタ
	BOSS_ONE_STATE			m_BossOneState;						// ボスのステータス
	BOSS_ONE_ATTACKTYPE		m_AttckType;						// ボスの攻撃の種類
	BOSS_ONE_ATTACKTYPE		m_AttckTypeOld;						// 1つ前の攻撃パターン
	int						m_ShotCount;						// 一発撃ってから次の弾を撃つまでの時間
	int						m_nCoolTime;						// ステートが切り替わるまでの時間
	int						m_nShotIntervalTime;				// 連続して撃つ弾の次の弾を撃つまでの時間
	D3DXVECTOR3				m_Gun_OffsetPos[WEAPONTYPE_MAX];	// ガンのオフセット座標
	D3DXVECTOR3				m_Gun_Pos[WEAPONTYPE_MAX];			// ガンの座標
	int						m_nShotCount;						// ショットした回数
	int						m_nTriggerCount;					// 何トリガー撃ったか
	bool					m_bFlame;							//
	bool					m_bBalkanRotFlag;					// 回転許可フラグ
	float					m_fBalkanRot;						// ガンの回転情報
	int						m_nBalkanAngle;						// 比較用ガンの回転情報

	int						m_nShot;
	bool					m_bBalkanGunRotFlag;					// 回転許可フラグ

	float					m_fRotTarget;
	float					m_fPartsRotVentilation;
	bool					m_bSetBossState;
	bool					m_bOpenWeapon;//
};
#endif