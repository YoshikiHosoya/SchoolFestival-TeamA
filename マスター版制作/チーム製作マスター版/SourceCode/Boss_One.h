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
#include "Enemy.h"

// =====================================================================================================================================================================
// ボス1のデータ
// =====================================================================================================================================================================
typedef struct
{
	int					nLife;			// 体力
	int					nCoolTime;		// クールタイム
	D3DXVECTOR3			CollisionSize;	// 当たり判定のサイズ
} BOSS_ONE_DATA;

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CModel;

// =====================================================================================================================================================================
// 捕虜クラス
// =====================================================================================================================================================================
class CBoss_One :public CEnemy
{
public:
	// ボス1の状態
	enum BOSS_ONE_STATE
	{
		BOSS_ONE_STATE_NONE = -1,								//
		BOSS_ONE_STATE_STAY,									//
		BOSS_ONE_STATE_MAX										// 最大数
	};

	// 攻撃の種類
	enum BOSS_ONE_ATTACKTYPE
	{
		ATTACKTYPE_BULLET,										//
		ATTACKTYPE_MAX											// 最大数
	};

	CBoss_One(OBJ_TYPE type);									// コンストラクタ
	~CBoss_One();												// デストラクタ
	/* メンバ関数 */
	HRESULT Init(void);											// 初期化
	void	Uninit(void);										// 終了
	void	Update(void);										// 更新
	void	Draw(void);											// 描画

	/* 静的メンバ関数 */
	static CBoss_One	*Create();								// 生成
	static	void		Boss_One_DataLoad();					// 捕虜情報のロード
	static	void		SetBoss_OneData();						// 捕虜のデータ設定

	/* メンバ関数 */
	void				DebugInfo(void);						// デバッグ
	bool				Motion(void);							// デフォルトモーション
	bool				DefaultMotion(void);

	BOSS_ONE_STATE				GetBossOneState()
	{
		return m_BossOneState;
	};									// 捕虜の状態の取得

	BOSS_ONE_ATTACKTYPE		GetPrisonerDropType()
	{
		return m_BossOneType;
	};								// 捕虜の種類

	void						SetPrisonerState(BOSS_ONE_STATE state)
	{
		m_BossOneState = state;
	};									// 捕虜の状態の設定

	void				SetPrisonerType(BOSS_ONE_ATTACKTYPE type)
	{
		m_BossOneType = type;
	};								// 捕虜の種類の設定
private:
	/* 静的メンバ変数 */
	static char				*m_BossOneFileName;				// 捕虜のファイル名
	static BOSS_ONE_DATA	m_BossOneData;						// 捕虜のデータ
	static int				m_nDeleteTime;						// 捕虜が消滅するまでの時間
	static float			m_fMoveSpeed;						// 移動速度
	static D3DXVECTOR3		m_CollisionSize;					// 当たり判定の大きさ

	/* メンバ関数 */
	void					BossOneState();					// 捕虜の状態別処理
	void					SetStateTime(int time)
	{
		m_StateTime = time;
	};				// ステートが切り替わるまでの時間の設定

	/* メンバ変数 */
	BOSS_ONE_STATE			m_BossOneState;						// デバッグのステータス
	BOSS_ONE_ATTACKTYPE		m_BossOneType;						// 捕虜の種類

	int						m_nDieCount;						// 捕虜が消滅するまでのカウント
	bool					m_bUse;								// ポインタを使用できるかどうか
	int						m_StateTime;						// ステートが切り替わるまでの時間
};
#endif