// =====================================================================================================================================================================
//
// マップの処理 [map.h]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#ifndef _MAP_H_
#define _MAP_H_

// =====================================================================================================================================================================
// インクルードファイル
// =====================================================================================================================================================================
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Scene.h"
#include "inputKeyboard.h"

// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CModel;
class CEnemy;
class CPrisoner;
class CObstacle;
class CPlayertank;
class CBattlePlane;

// =====================================================================================================================================================================
// マップクラス
// =====================================================================================================================================================================
class CMap
{
public:
	// マップの種類
	enum MAP
	{
		MAP_1,			// 1
		MAP_2,			// 2
		MAP_MAX
	};

	// マップに配置するモデルの種類
	enum MAP_MODEL_TYPE
	{
		MAP_MODEL_TYPE_ENEMY,					// 敵
		MAP_MODEL_TYPE_OBSTACLE,				// 障害物
		MAP_MODEL_TYPE_PRISONER,				// 捕虜
		MAP_MODEL_TYPE_PLAYERTANK,				// プレイヤー用の戦車
		MAP_MODEL_TYPE_MAX
	};

	CMap();																	// コンストラクタ
	~CMap();																// デストラクタ

	/* 静的メンバ関数 */
	static	CMap	*MapCreate(MAP MapNum);									// マップの生成
	void	MapUpdate();											// マップの更新

	/* メンバ関数 */
	int				GetMaxModel();												// モデルの最大数取得
	int				GetMaxEnemy();												// 敵の最大数取得
	int				GetMaxPrisoner();											// 捕虜の最大数取得
	int				GetMaxObstacle();											// 障害物の最大数取得
	int				GetMaxPlayerTank();											// 戦車の最大数取得
	int				GetMaxBattlePlane();										// 戦闘機の最大数取得
	LPD3DXMESH		GetMesh(int nCnt);											// メッシュの取得
	CModel			*GetModel(int nCnt) { return m_pModel[nCnt]; };				// モデルの取得
	CEnemy			*GetEnemy(int nCnt) { return m_pEnemy[nCnt]; };				// 敵の取得
	CPrisoner		*GetPrisoner(int nCnt) { return m_pPrisoner[nCnt]; };		// 捕虜の取得
	CObstacle		*GetObstacle(int nCnt) { return m_pObstacle[nCnt]; };		// 障害物の取得
	CPlayertank		*GetPlayertank(int nCnt) { return m_pPlayerTank[nCnt]; };	// 戦車の取得
	CBattlePlane	*GetBattlePlane(int nCnt) { return m_pBattlePlane[nCnt]; };	// 戦闘機の取得

	void			UpdateDieFlag();										// 死亡フラグ確認関数

private:
	/* メンバ関数 */
	void			ModelLoad(MAP MapNum);									// モデルのロード
	void			EnemyLoad(MAP MapNum);									// 敵のロード
	void			PrisonerLoad(MAP MapNum);								// 捕虜のロード
	void			ObstacleLoad(MAP MapNum);								// 障害物のロード
	void			PlayerTankLoad(MAP MapNum);								// プレイヤー用の戦車のロード
	void			BattlePlaneLoad(MAP MapNum);							// 戦闘機のロード
	void			ModelSave(MAP MapNum);									// モデルのセーブ
	void			EnemySave(MAP MapNum);									// 敵のセーブ
	void			PrisonerSave(MAP MapNum);								// 捕虜のセーブ
	void			ObstacleSave(MAP MapNum);								// 障害物のセーブ
	void			PlayerTankSave(MAP MapNum);								// 戦車のセーブ
	void			BattlePlaneSave(MAP MapNum);							// 戦闘機のセーブ
	void			AllSaveButton();										// 配置したモデルを全てセーブするボタン
	void			MapModelTab();											// マップに配置するモデルのタブ
	void			MapModelSet();											// マップに配置するモデルの設置
	void			ObstacleSet();											// 障害物の設置
	void			EnemySet();												// 敵の設置
	void			PlayerTankSet();										// 戦車の設置
	void			BattlePlaneSet();										// 戦闘機の設置
	bool			ObstacleComboBox(int &nType);							// 障害物のコンボボックス
	void			PrisonerSet();											// 捕虜の設置
	bool			EnemyComboBox(int &nType);								// 敵のコンボボックス
	bool			PrisonerComboBox(int &nType);							// 捕虜のコンボボックス
	bool			PlayerTankComboBox(int &nType);							// 戦車のコンボボックス
	bool			BattlePlaneComboBox(int &nType);						// 戦闘機のコンボボックス

	/* 静的メンバ変数 */
	static char					*m_MapFileName[MAP_MAX];					// マップファイル名
	static char					*m_EnemyFileName[MAP_MAX];					// 敵ファイル名
	static char					*m_PrisonerFileName[MAP_MAX];				// 捕虜ファイル名
	static char					*m_ObstacleFileName[MAP_MAX];				// 障害物ファイル名
	static char					*m_PlayerTankFileName[MAP_MAX];				// 戦車ファイル名
	static char					*m_BattlePlaneFileName[MAP_MAX];			// 戦闘機ファイル名
	static MAP					m_MapNum;									// マップ番号

	/* メンバ変数 */
	std::vector<CModel*>		m_pModel;									// 可変長配列 設置するモデル
	std::vector<CEnemy*>		m_pEnemy;									// 可変長配列 設置したエネミー
	std::vector<CPrisoner*>		m_pPrisoner;								// 可変長配列 設置した捕虜
	std::vector<CObstacle*>		m_pObstacle;								// 可変長配列 設置した障害物
	std::vector<CPlayertank*>	m_pPlayerTank;								// 可変長配列 設置した戦車
	std::vector<CBattlePlane*>	m_pBattlePlane;								// 可変長配列 設置した戦闘機
	int							m_nOldSelect;								// 前回選択していたモノの番号
};
#endif