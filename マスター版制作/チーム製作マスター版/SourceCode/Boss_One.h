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
#include "Character.h"

// =====================================================================================================================================================================
// ボス1のデータ
// =====================================================================================================================================================================
typedef struct
{
	int					nLife;				// 体力
	int					nCoolTime;			// クールタイム
	D3DXVECTOR3			CollisionSize[2];	// 当たり判定のサイズ
	D3DXVECTOR3			GunShotOfsetPos[3];		// ガンのオフセット座標
} BOSS_ONE_DATA;

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CModel;
class CGun;

// =====================================================================================================================================================================
// 捕虜クラス
// =====================================================================================================================================================================
class CBoss_One :public CCharacter
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
		ATTACKTYPE_BALKAN,											// バルカン砲
		ATTACKTYPE_FLAMETHROWER,									// 火炎放射 立ち時のみ
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
	static CBoss_One		*Create();								// 生成
	static	void			Boss_One_DataLoad();					// ボス情報のロード
	static	void			SetBoss_OneData();						// ボスのデータ設定

	/* メンバ関数 */
	void					DebugInfo(void);						// デバッグ
	bool					Motion(void);							// デフォルトモーション
	bool					DefaultMotion(void);

	// ----- 状態の取得設定 ----- //
	BOSS_ONE_STATE			GetBossOneState()						{ return m_BossOneState; };				// ボスの状態の取得
	BOSS_ONE_ATTACKTYPE		GetPrisonerDropType()					{ return m_BossOneType; };				// ボスの種類
	void					SetBossState(BOSS_ONE_STATE state)		{ m_BossOneState = state; };			// ボスの状態の設定
	void					SetBossType(BOSS_ONE_ATTACKTYPE type)	{ m_BossOneType = type; };				// ボスの種類の設定
private:
	/* 静的メンバ変数 */
	static char				*m_BossOneFileName;					// ボスのファイル名
	static BOSS_ONE_DATA	m_BossOneData;						// ボスのデータ

	// ステータス用 //
	static int				m_nLife;							// 体力
	static D3DXVECTOR3		m_CollisionSize[POSTURETYPE_MAX];	// 当たり判定の大きさ
	static D3DXVECTOR3		m_GunShotOfsetPos[WEAPONTYPE_MAX];	// ガンのオフセット

	/* メンバ関数 */
	void					BossOneState();						// ボスの状態別処理
	void					DamageReaction();
	void					DeathReaction();
	void					StateChangeReaction();
	void					Behavior();							// 敵の行動

	void					SetStateTime(int time)
	{
		m_StateTime = time;
	};															// ステートが切り替わるまでの時間の設定

	/* メンバ変数 */
	BOSS_ONE_STATE			m_BossOneState;						// デバッグのステータス
	BOSS_ONE_ATTACKTYPE		m_BossOneType;						// ボスの種類
	int						m_ShotCount;						// 一発撃ってから次の弾を撃つまでの時間

	int						m_StateTime;						// ステートが切り替わるまでの時間
	CGun					*m_pGun[WEAPONTYPE_MAX];			// ガンクラスのポインタ
};
#endif