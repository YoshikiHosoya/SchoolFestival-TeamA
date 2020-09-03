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
// マクロ定義
// =====================================================================================================================================================================
#define MIN_PLAYER_DISTANCE (300)										// 符号なし整数 プレイヤーと判定する最短距離
#define MAX_PLAYER_DISTANCE (800)										// 符号なし整数 プレイヤーと判定する最長距離
#define RANGE_CENTER ((MAX_PLAYER_DISTANCE - MIN_PLAYER_DISTANCE) - 50)	// 符号なし整数 プレイヤーと判定する射程範囲の中心
#define CENTER_RANGE (100)												// 符号なし整数 プレイヤーと判定する射程範囲の中心
#define SAVE_ATTACKOLD_NUM (2)											// 保存しておく過去の攻撃方法の数

// =====================================================================================================================================================================
// ボスのデータベース
// =====================================================================================================================================================================
struct BOSS_ONE_DATABASE
{
	int					nLife;					// 体力
	int					nCoolTime;				// クールタイム
	D3DXVECTOR3			CollisionSize[2];		// 当たり判定のサイズ
	D3DXVECTOR3			GunShotOfsetPos[3];		// ガンのオフセット座標







};

// =====================================================================================================================================================================
// ボスのAIデータ
// =====================================================================================================================================================================
typedef struct
{
	std::vector<int *> nPriorityData;			// 優先度を格納する変数
	int AttackType[4];							// 優先度
} BOSS_ONE_AI_PRIORITY;

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
	// ボスの状態
	enum BOSS_ONE_STATE
	{
		STATE_NORMAL,												// 通常状態
		STATE_RUNAWAY, 												// 暴走状態
		STATE_MAX													// 最大数
	};

	// ボスの攻撃用AIの状態
	enum BOSS_ONE_ATTACK_AI_STATE
	{
		AI_STATE_GET_INFORMATION,									// 情報の取得
		AI_STATE_AI, 												// 情報を元に攻撃方法を選択する
		AI_STATE_MAX												// 最大数
	};

	// ボスの行動パターン
	enum BOSS_ONE_ACTION_PATTERN
	{
		ACTION_PATTERN_NONE = -1,									// 初期値 何もしない
		ACTION_PATTERN_STAY,										// 何もしない 待機中
		ACTION_PATTERN_AI_ATTACK,									// 次の攻撃方法を考える
		ACTION_PATTERN_ATTACK,										// 攻撃する
		ACTION_PATTERN_SHIFT_POSTURE,								// 体勢を変える
		ACTION_PATTERN_MAX											// 最大数
	};

	// 攻撃の種類
	enum BOSS_ONE_ATTACKTYPE
	{
		ATTACKTYPE_NONE = -1,
		ATTACKTYPE_BALKAN,											// バルカン砲
		ATTACKTYPE_FLAMERADIATION,									// 火炎放射 立ち時のみ
		ATTACKTYPE_INCENDIARY,										// 焼夷弾
		ATTACKTYPE_SHIFTPOSTURE,									// 姿勢変更
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

	// 優先度のポイント
	enum BOSS_ONE_PRIORITY_POINT
	{// 高いほど優先度が上がる
		PRIORITY_POINT_MINUS = -1,									// -1
		PRIORITY_POINT_NONE,										// 0
		PRIORITY_POINT_ONE,											// 1
		PRIORITY_POINT_TWO,											// 2
		PRIORITY_POINT_THREE,										// 3
		PRIORITY_POINT_MAX = 100,									// 最優先
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

	/* メンバ関数 */
	void					DebugInfo(void);						// デバッグ
	void					Motion(void);							// ボスのパーツの動き
	bool					DefaultMotion(void);					// デフォルトモーション

	// ----- 状態の取得設定 ----- //
	BOSS_ONE_STATE			GetBossState()									{ return m_BossState; };				// ボスの状態の取得
	BOSS_ONE_ACTION_PATTERN	GetBossOneActionPattern()						{ return m_BossOneActionPattern; };		// ボスの攻撃パターンの取得
	BOSS_ONE_ATTACKTYPE		GetBossOneType()								{ return m_AttckType; };				// ボスの攻撃の種類
	CCollision				*GetCollision()									{ return m_pCollision; };				// 当たり判定のポインタ取得
	BOSS_ONE_POSTURETYPE	GetPostureType()								{ return m_PostureType; };				// ボスの姿勢情報の取得
	bool					GetIntermediateSquat()							{ return m_bIntermediateSquat; };		// しゃがみ途中ならtrueを返す

	// ----- 状態の設定 ----- //
	void					SetBossState(BOSS_ONE_STATE state)				{ m_BossState = state; };				// ボスの状態の設定
	void					SetBossAction(BOSS_ONE_ACTION_PATTERN pattern)	{ m_BossOneActionPattern = pattern; };	// ボスの攻撃パターンの設定
	void					SetBossType(BOSS_ONE_ATTACKTYPE type)			{ m_AttckType = type; };				// ボスの攻撃の種類の設定
private:
	/* 静的メンバ変数 */
	static char				*m_BossOneFileName;									// ボスのファイル名
	static BOSS_ONE_DATABASE m_BossOneData;										// ボスのデータ

	// ステータス用 //
	//static int				m_nLife;											// 体力
	//static D3DXVECTOR3		m_CollisionSize[POSTURETYPE_MAX];					// 当たり判定の大きさ
	//static D3DXVECTOR3		m_GunShotOfsetPos[WEAPONTYPE_MAX];					// ガンのオフセット

	/* メンバ関数 */

	// --- 状態管理関数 ---  //
	void					BossOneStateManager();								// ボスの状態管理処理
	void					Behavior();											// ボスの行動別処理
	void					BossOneAttackManager();								// ボスの攻撃管理処理

	// --- 攻撃用AI関連 ---  //
	void					Attack_AI();										// ボスの攻撃用AI
	void					Attack_Priority();									// 攻撃の優先度を計算
	void					Attack_InitializeDataAll();							// 優先度の数値を初期化
	void					Attack_InitializeData(BOSS_ONE_ATTACKTYPE type);	// 指定した行動の優先度を初期化
	void					Attack_Exception();									// 優先度を決めるにあたっての例外

	// --- 関数 ---  //
	void					DamageReaction();									// ダメージを受けたときの反応
	void					DeathReaction();									// 死亡した時の処理
	void					StateChangeReaction();								// 状態を変える
	void					StayAction();										// 待機時の行動
	void					BubbleSort(std::vector<int*> &data);				// 優先度の入れ替え 高い順に0番目から

	// --- 設定関数 ---  //
	void					SetShotIntervalTime(int time)	{ m_nShotIntervalTime = time; };		// インターバルの時間の設定
	void					SetShotCount(int nCount)		{ m_nShotCount = nCount; };				// ショットカウントの時間の設定
	void					SetCoolTime(int time);													// ステートが切り替わるまでの時間の設定
	void					SetTriggerCount(int nCount)		{ m_nTriggerCount = nCount; };			// トリガーのカウントの設定
	void					SetBalkanRot(float fRot)		{ m_fBalkanRot = fRot; };				// バルカンの回転量の設定
	void					SetGunOffsetPos(D3DXVECTOR3 pos);										// ガンのオフセット座標の設定
	void					SetGunPos();															// ガンの座標の設定
	void					SetFlameThrower(bool bOpen);											// 火炎放射器の移動
	void					SetBalkan(bool bOpen, BOSS_ONE_STATE state);							// バルカンの移動
	void					SetRotBalkan(BOSS_ONE_STATE state);										// バルカンの回転
	void					SetCollision();															// 当たり判定の設定
	void					SetAttackType(BOSS_ONE_ATTACKTYPE type);								// 決定した攻撃方法を設定する

	void					SetBossInfo();															// ボスの情報の設定
	void					CreateGun();															// ガンの生成と初期設定

	// --- 取得関数 ---  //
	D3DXVECTOR3				GetGunOffsetPos(BOSS_ONE_WEAPONTYPE type);								// ガンのオフセット座標の取得

	// --- ガンの座標の設定 ---  //
	void					MoveGun(D3DXVECTOR3 &PartsPos, D3DXVECTOR3 move);						// ガンの移動
	void					CalcRotationBalkan(const float fTarget, float fCurrent);				// 目標と現在
	float					get_vector_length(D3DXVECTOR3 vectol);									// ベクトルの長さを計算する
	float					dot_product(D3DXVECTOR3 vl, D3DXVECTOR3 vr);							// ベクトル内積
	float					AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);							// ２つのベクトルABのなす角度θを求める

	// --- その他 ---  //
	void					Cooltime_Decrease();													// クールタイムの減少
	uint64_t				get_rand_range(uint64_t min_val, uint64_t max_val);						// ランダム関数 範囲
	void					UpdateCollision();														// 当たり判定の更新

	// --- 攻撃管理関数 ---  //
	void					ShotIncendiary();														// 焼夷弾
	void					ShotBalkan();															// バルカン
	void					ShotWarning();															// 焼夷弾の最初の爆発
	void					ShotFlameRadiation();													// フレイム火炎放射器
	void					ShiftPosture();															// 姿勢変更
	void					ShotFlameManager();														// 火炎放射の管理
	void					RandomAttack();															// 攻撃方法をランダムに決める

	/* メンバ変数 */
	CGun						*m_pGun[WEAPONTYPE_MAX];						// ガンクラスのポインタ
	CCollision					*m_pCollision;									// 当たり判定のポインタ
	BOSS_ONE_STATE				m_BossState;									// ボスの状態
	BOSS_ONE_ACTION_PATTERN		m_BossOneActionPattern;							// ボスの行動パターン
	BOSS_ONE_ATTACKTYPE			m_AttckType;									// ボスの攻撃の種類
	BOSS_ONE_ATTACKTYPE			m_AttckTypeOld[SAVE_ATTACKOLD_NUM];				// 1つ前の攻撃パターン
	BOSS_ONE_POSTURETYPE		m_PostureType;									// 姿勢
	BOSS_ONE_ATTACK_AI_STATE	m_AttackAIState;								// 攻撃AIの状態
	BOSS_ONE_AI_PRIORITY		m_AIPriorityData;								// aiの優先度の情報

	D3DXVECTOR3					m_Gun_OffsetPos[WEAPONTYPE_MAX];				// ガンのオフセット座標
	D3DXVECTOR3					m_Gun_Pos[WEAPONTYPE_MAX];						// ガンの座標

	int							m_ShotCount;									// 一発撃ってから次の弾を撃つまでの時間
	int							m_nCoolTime;									// ステートが切り替わるまでの時間
	int							m_nShotIntervalTime;							// 連続して撃つ弾の次の弾を撃つまでの時間
	int							m_nShotCount;									// ショットした回数
	int							m_nTriggerCount;								// 何トリガー撃ったか
	int							m_nBalkanAngle;									// 比較用ガンの回転情報
	int							m_nFirstShotCount;								// 初弾を撃つまでの時間
	float						m_fRotTarget;									// 回転目標
	float						m_fBalkanRot;									// ガンの回転情報
	float						m_fPartsRotVentilation;							// ボスの装甲パーツの回転用
	float						m_AddMove;										// 移動量の加算用
	float						m_fBalkanRotDifferencial;						// 回転の差分用
	bool						m_bOpenWeapon;									// バルカンと火炎放射器を出しているかどうか
	bool						m_bShiftPosture;								// 姿勢を変えるフラグ
	bool						m_bBalkanGunRotFlag;							// 回転許可フラグ
	bool						m_bFlame;										// 火炎放射を発射する許可
	bool						m_bBalkanRotFlag;								// 回転許可フラグ
	bool						m_bIntermediateSquat;							// しゃがみ途中かどうかのフラグ
};
#endif