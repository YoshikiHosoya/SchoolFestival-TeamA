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
class CHelicopter;

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

	// エディターの種類
	enum EDITOR
	{
		EDITOR_MAP,			// マップエディター
		EDITOR_WAVE,		// ウェーブエディター
		EDITOR_PLATOON,		// 小隊エディター
		EDITOR_MAX
	};

	// 配置するモデルの種類
	enum ARRANGEMENT_MODEL
	{
		ARRANGEMENT_MODEL_MAP,					// マップ
		ARRANGEMENT_MODEL_ENEMY,				// 敵
		ARRANGEMENT_MODEL_PRISONER,				// 捕虜
		ARRANGEMENT_MODEL_OBSTACLE,				// 障害物
		ARRANGEMENT_MODEL_TANK,					// 戦車
		ARRANGEMENT_MODEL_BATTLEPLANE,			// 戦闘機
		ARRANGEMENT_MODEL_HELICOPTER,			// ヘリコプター
		ARRANGEMENT_MODEL_MAX
	};

	// ウェーブの種類
	enum WAVE
	{
		WAVE_1,									// ウェーブ1
		WAVE_2,									// ウェーブ2
		WAVE_3,									// ウェーブ3
		WAVE_MAX
	};
	CMap();																			// コンストラクタ
	~CMap();																		// デストラクタ

	/* 静的メンバ関数 */
	static	CMap	*MapCreate(MAP MapNum);											// マップの生成
	void	MapUpdate();															// マップの更新

	/* メンバ関数 */
	int				GetMaxModel();													// モデルの最大数取得
	int				GetMaxEnemy();													// 敵の最大数取得
	int				GetMaxPrisoner();												// 捕虜の最大数取得
	int				GetMaxObstacle();												// 障害物の最大数取得
	int				GetMaxPlayerTank();												// 戦車の最大数取得
	int				GetMaxBattlePlane();											// 戦闘機の最大数取得
	int				GetMaxHelicopter();												// ヘリの最大数取得
	LPD3DXMESH		GetMesh(int nCnt);												// メッシュの取得
	CModel			*GetModel(int nCnt)			{ return m_pModel[nCnt]; };			// モデルの取得
	CEnemy			*GetEnemy(int nCnt)			{ return m_pEnemy[nCnt]; };			// 敵の取得
	CPrisoner		*GetPrisoner(int nCnt)		{ return m_pPrisoner[nCnt]; };		// 捕虜の取得
	CObstacle		*GetObstacle(int nCnt)		{ return m_pObstacle[nCnt]; };		// 障害物の取得
	CPlayertank		*GetPlayertank(int nCnt)	{ return m_pPlayerTank[nCnt]; };	// 戦車の取得
	CBattlePlane	*GetBattlePlane(int nCnt)	{ return m_pBattlePlane[nCnt]; };	// 戦闘機の取得
	CHelicopter		*GetHelicopter(int nCnt)	{ return m_pHelicopter[nCnt]; };	// ヘリコプターの取得

	void			UpdateDieFlag();												// 死亡フラグ確認関数

private:
	/* メンバ関数 */
	void			ArrangementModelLoad();													// 配置するモデルのロード
	void			ArrangementModelCreate(int ModelType, int nType, 
											D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 size);	// 配置するモデルの生成
	void			LoadFailureMessage(int ModelType);										// 読み込み失敗時の警告表示
	void			LoadSuccessMessage(int ModelType);										// 読み込み成功時の結果表示

	char			*ArrangementModelFileName(int ModelType);								// 配置するモデルファイル名(初期配置)

	void			SaveModelHeader(FILE *pFile, int ModelType);							// セーブするモデルのヘッダー
	void			SaveModelContents(FILE *pFile,int ModelType, int nCnt);					// セーブするモデルの情報

	unsigned int	GetMaxArrangementModel(int ModelType);									// 配置するモデルの最大数取得
	void			*GetArrangementModel(int ModelType, int nCnt);							// 配置するモデルのポインタ
	void			ArrangementModelSave(int ModelType);									// 配置するモデルのセーブ

	void			AllSaveButton();														// 配置したモデルを全てセーブするボタン
	void			MapModelTab();															// マップに配置するモデルのタブ
	void			ObstacleSet();															// 障害物の設置
	void			EnemySet();																// 敵の設置
	void			PlayerTankSet();														// 戦車の設置
	void			BattlePlaneSet();														// 戦闘機の設置
	void			HelicopterSet();														// ヘリの設置
	bool			ObstacleComboBox(int &nType);											// 障害物のコンボボックス
	void			PrisonerSet();															// 捕虜の設置
	bool			EnemyComboBox(int &nType);												// 敵のコンボボックス
	bool			PrisonerComboBox(int &nType);											// 捕虜のコンボボックス
	void			SetSelectMapModelPosRDest(D3DXVECTOR3 posR);							// 選択しているモデルを注視点の目的地に設定

	/* 静的メンバ変数 */
	static char					*m_MapFileName[MAP_MAX];					// マップファイル名
	static char					*m_EnemyFileName[MAP_MAX];					// 敵ファイル名
	static char					*m_PrisonerFileName[MAP_MAX];				// 捕虜ファイル名
	static char					*m_ObstacleFileName[MAP_MAX];				// 障害物ファイル名
	static char					*m_PlayerTankFileName[MAP_MAX];				// 戦車ファイル名
	static char					*m_BattlePlaneFileName[MAP_MAX];			// 戦闘機ファイル名
	static char					*m_HelicopterFileName[MAP_MAX];				// ヘリファイル名
	static MAP					m_MapNum;									// マップ番号
	static EDITOR				m_Editor;									// エディターの種類
	static int					m_ArrangmentModel;							// 配置するモデルの種類

	/* メンバ変数 */
	std::vector<CModel*>		m_pModel;									// 可変長配列 設置するモデル
	std::vector<CEnemy*>		m_pEnemy;									// 可変長配列 設置したエネミー
	std::vector<CPrisoner*>		m_pPrisoner;								// 可変長配列 設置した捕虜
	std::vector<CObstacle*>		m_pObstacle;								// 可変長配列 設置した障害物
	std::vector<CPlayertank*>	m_pPlayerTank;								// 可変長配列 設置した戦車
	std::vector<CBattlePlane*>	m_pBattlePlane;								// 可変長配列 設置した戦闘機
	std::vector<CHelicopter*>	m_pHelicopter;								// 可変長配列 設置したヘリ
	int							m_nOldSelect;								// 前回選択していたモノの番号
};
#endif