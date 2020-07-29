// =====================================================================================================================================================================
//
// 捕虜の処理 [prisoner.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _PRISONER_H_
#define _PRISONER_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "Character.h"

// =====================================================================================================================================================================
// 捕虜のデータ
// =====================================================================================================================================================================
typedef struct
{
	int					nDeleteTime;	// 消滅するまでの時間
	float				fMoveSpeed;		// 移動速度
	D3DXVECTOR3			CollisionSize;	// 当たり判定のサイズ
}PRISONER_DATA;

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CModel;
// =====================================================================================================================================================================
// 捕虜クラス
// =====================================================================================================================================================================
class CPrisoner :public CCharacter
{
public:
	// 捕虜の状態
	enum PRISONER_STATE
	{
		PRISONER_STATE_STAY,									// 縛られている初期状態
		PRISONER_STATE_DROPITEM,								// アイテムを落とす
		PRISONER_STATE_RUN,										// 走って消える
		PRISONER_STATE_MAX										// 最大数
	};

	// 捕虜の種類
	enum PRISONER_ITEM_DROPTYPE
	{
		PRISONER_ITEM_DROPTYPE_DESIGNATE_ONE,					// ドロップするアイテムを１種類指定する
		PRISONER_ITEM_DROPTYPE_DESIGNATE_RANGE,					// ドロップするアイテムの種類を指定する - 武器系かスコア系か
		PRISONER_ITEM_DROPTYPE_ALL,								// 全てのアイテムからランダムでドロップさせる
		PRISONER_ITEM_DROPTYPE_MAX								// 最大数
	};

	CPrisoner(OBJ_TYPE type);									// コンストラクタ
	~CPrisoner();												// デストラクタ

	/* メンバ関数 */
	HRESULT Init(void);											// 初期化
	void	Uninit(void);										// 終了
	void	Update(void);										// 更新
	void	Draw(void);											// 描画

	/* 静的メンバ関数 */
	static CPrisoner	*Create();								// 生成
	static	void		PrisonerLoad();							// 捕虜情報のロード
	static	void		SetPrisonerData();						// 捕虜のデータ設定

	/* メンバ関数 */
	void				DebugInfo(void);						// デバッグ
	bool				DefaultMotion(void);					// デフォルトモーション

	PRISONER_STATE		GetPrisonerState()
	{
		return m_PrisonerState;
	};															// 捕虜の状態の取得

	PRISONER_ITEM_DROPTYPE		GetPrisonerDropType()
	{
		return m_PrisonerDropType;
	};															// 捕虜の種類

	void				SetPrisonerState(PRISONER_STATE state)
	{
		m_PrisonerState = state;
	};															// 捕虜の状態の設定

	void				SetPrisonerType(PRISONER_ITEM_DROPTYPE type)
	{
		m_PrisonerDropType = type;
	};															// 捕虜の種類の設定

private:
	/* 静的メンバ変数 */
	static char				*m_PrisonerFileName;				// 捕虜のファイル名
	static PRISONER_DATA	m_PrisonerData;						// 捕虜のデータ
	static int				m_nDeleteTime;						// 捕虜が消滅するまでの時間
	static float			m_fMoveSpeed;						// 移動速度
	static D3DXVECTOR3		m_CollisionSize;					// 当たり判定の大きさ

	/* メンバ関数 */
	void					PrisonerState();					// 捕虜の状態別処理
	void					PrisonerDropType();					// 捕虜のタイプ別処理

	/* メンバ変数 */
	PRISONER_STATE			m_PrisonerState;					// デバッグのステータス
	PRISONER_ITEM_DROPTYPE	m_PrisonerDropType;					// 捕虜の種類
	void					Move(float move, float fdest);		// 捕虜の移動
	int						m_nDieCount;						// 捕虜が消滅するまでのカウント
	bool					m_bUse;								// ポインタを使用できるかどうか
};
#endif