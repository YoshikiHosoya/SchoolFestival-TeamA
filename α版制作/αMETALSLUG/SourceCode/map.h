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

// =====================================================================================================================================================================
// マップクラス
// =====================================================================================================================================================================
class CMap
{
public:
	// マップのオブジェクトの種類
	enum MAP
	{
		MAP_1,			// 1
		MAP_2,			// 2
		MAP_MAX
	};

	CMap();																	// コンストラクタ
	~CMap();																// デストラクタ

	/* 静的メンバ関数 */
	void			ModelLoad(int nCnt);									// モデルのロード
	void			EnemyLoad(int nCnt);									// 敵のロード
	void			PrisonerLoad(int nCnt);									// 捕虜のロード
	void			ObstacleLoad(int nCnt);									// 障害物のロード
	void			DebugMap();												// マップのデバッグ配置
	static	CMap	*MapCreate(int nCnt);									// マップの生成

	/* メンバ関数 */
	int				GetMaxModel();											// モデルの最大数取得
	int				GetMaxEnemy();											// 敵の最大数取得
	int				GetMaxPrisoner();										// 捕虜の最大数取得
	int				GetMaxObstacle();										// 障害物の最大数取得
	LPD3DXMESH		GetMesh(int nCnt);										// メッシュの取得
	CModel			*GetModel(int nCnt) { return m_pModel[nCnt]; };			// モデルの取得
	CEnemy			*GetEnemy(int nCnt) { return m_pEnemy[nCnt]; };			// 敵の取得
	CPrisoner		*GetPrisoner(int nCnt) { return m_pPrisoner[nCnt]; };	// 捕虜の取得
	CObstacle		*GetObstacle(int nCnt) { return m_pObstacle[nCnt]; };	// 障害物の取得

	void			UpdateDieFlag();										// 死亡フラグ確認関数

private:
	/* 静的メンバ関数 */
	void	ModelSave();													// モデルのセーブ
	void	EnemySave();													// 敵のセーブ

	/* 静的メンバ変数 */
	static char					*m_MapFileName[MAP_MAX];					// マップファイル名
	static char					*m_EnemyFileName[MAP_MAX];					// 敵ファイル名
	static char					*m_PrisonerFileName[MAP_MAX];				// 捕虜ファイル名
	static char					*m_ObstacleFileName[MAP_MAX];				// 障害物ファイル名

	/* メンバ変数 */
	std::vector<CModel*>		m_pModel;									// 可変長配列 設置するモデル
	std::vector<CEnemy*>		m_pEnemy;									// 可変長配列 設置したエネミー
	std::vector<CPrisoner*>		m_pPrisoner;								// 可変長配列 設置した捕虜
	std::vector<CObstacle*>		m_pObstacle;								// 可変長配列 設置した障害物
};
#endif