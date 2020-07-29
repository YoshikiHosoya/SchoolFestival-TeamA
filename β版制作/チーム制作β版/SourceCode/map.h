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
class CVehicle;

// =====================================================================================================================================================================
// ウェーブの情報
// =====================================================================================================================================================================
typedef struct
{
	D3DXVECTOR3 pos;			// 頂点座標
	int			nFrame;			// フレーム
	//bool		bEvent;
} WAVE_INFO;

typedef struct
{
	std::vector<WAVE_INFO> EnemyWaveInfo;
	std::vector<WAVE_INFO> horyoWaveInfo;

} WAVE;




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

	// 小隊の種類
	enum PLATOON
	{
		PLATOON_1,								// 小隊1
		PLATOON_2,								// 小隊2
		PLATOON_3,								// 小隊3
		PLATOON_MAX
	};

	CMap();																			// コンストラクタ
	~CMap();																		// デストラクタ

	/* 静的メンバ関数 */
	static	CMap	*MapCreate();													// マップの生成

	void	MapUpdate();															// マップの更新
	void	MapLoad(MAP MapNum);													// マップのロード
	void	WaveLoad(WAVE WaveNum);													// ウェーブのロード
	void	WaveCreate(WAVE WaveNum, int ModelType, int &frame);					// ウェーブの生成

	/* メンバ関数 */
	int				GetMaxModel();													// モデルの最大数取得
	int				GetMaxEnemy();													// 敵の最大数取得
	int				GetMaxPrisoner();												// 捕虜の最大数取得
	int				GetMaxObstacle();												// 障害物の最大数取得
	int				GetMaxPlayerTank();												// 戦車の最大数取得
	int				GetMaxBattlePlane();											// 戦闘機の最大数取得
	int				GetMaxHelicopter();												// ヘリの最大数取得
	LPD3DXMESH		GetMesh(int nCnt);												// メッシュの取得
	CModel			*GetModel(int nCnt)			{ return m_pMapModel[nCnt]; };		// モデルの取得
	CEnemy			*GetEnemy(int nCnt)			{ return m_pEnemy[nCnt]; };			// 敵の取得
	CPrisoner		*GetPrisoner(int nCnt)		{ return m_pPrisoner[nCnt]; };		// 捕虜の取得
	CObstacle		*GetObstacle(int nCnt)		{ return m_pObstacle[nCnt]; };		// 障害物の取得
	CPlayertank		*GetPlayertank(int nCnt)	{ return m_pPlayerTank[nCnt]; };	// 戦車の取得
	CBattlePlane	*GetBattlePlane(int nCnt)	{ return m_pBattlePlane[nCnt]; };	// 戦闘機の取得
	CHelicopter		*GetHelicopter(int nCnt)	{ return m_pHelicopter[nCnt]; };	// ヘリコプターの取得

	void			UpdateDieFlag();												// 死亡フラグ確認関数

private:
	/* メンバ関数 */
	void			MapModelLoad();													// 配置するモデルのロード
	void			MapModelSave();													// 配置するモデルのセーブ

	void			MapModelCreate(int ModelType, int nType, 
											D3DXVECTOR3 pos, int nLife, D3DXVECTOR3 size);	// 配置するモデルの生成
	void			LoadFailureMessage(int ModelType);										// 読み込み失敗時の警告表示
	void			LoadSuccessMessage(int ModelType);										// 読み込み成功時の結果表示
	char			*WaveFileName(int ModelType);											// 各ウェーブファイル名

	void			SaveModelHeader(FILE *pFile, int ModelType);							// セーブするモデルのヘッダー
	void			SaveModelContents(FILE *pFile,int ModelType, int nCnt, int nNum);		// セーブするモデルの情報
	void			SaveWaveContents(FILE *pFile, int ModelType, int nCnt);					// セーブするウェーブの情報

	unsigned int	GetMaxMapModel(int ModelType);									// 配置するモデルの最大数取得
	void			*GetMapModel(int ModelType, int nCnt);							// 配置するモデルのポインタ

	void			AllSaveButton();														// 配置したモデルを全てセーブするボタン
	void			AllLoadButton();														// 配置したモデルを全てロードするボタン
	void			AllDeleteButton();														// 配置したモデルを全てデリートするボタン
	void			ModelDeleteButton(int nNowSelect);										// 配置するモデルをデリートするボタン
	void			ModelCreateButton();													// 配置するモデルを生成するボタン
	
	D3DXVECTOR3		GetMapModelPos(int nNowSelect);									// 選択しているモデルの位置の取得
	void			SetMapModelPos(D3DXVECTOR3 pos, int nNowSelect);				// 選択しているモデルの位置の設定
	void			SetMapModelColorChangeFlag(bool bFlag, int nNowSelect);			// 選択しているモデルの色を半透明にするフラグの設定
	void			MapModelTab();															// マップに配置するモデルのタブ
	void			MapModelSet();															// マップに配置するモデルの設置
	void			ComboBoxAll(int nNowSelect);											// 全てのコンボボックス
	bool			ObstacleComboBox(int &nType);											// 障害物のコンボボックス
	bool			EnemyComboBox(int &nType);												// 敵のコンボボックス
	bool			PrisonerComboBox(int &nType);											// 捕虜のコンボボックス
	void			SetSelectMapModelPosRDest(D3DXVECTOR3 posR);							// 選択しているモデルを注視点の目的地に設定

	/* 静的メンバ変数 */
	static char					*m_MapModelFileName[MAP_MAX];				// マップモデルファイル名

	static char					*m_EnemyWaveFileName[WAVE_MAX];				// 敵ファイル名
	static char					*m_PrisonerWaveFileName[WAVE_MAX];			// 捕虜ファイル名
	static char					*m_PlayerTankWaveFileName[WAVE_MAX];		// 戦車ファイル名
	static char					*m_BattlePlaneWaveFileName[WAVE_MAX];		// 戦闘機ファイル名
	static char					*m_HelicopterWaveFileName[WAVE_MAX];		// ヘリファイル名

	static MAP					m_MapNum;									// マップ番号
	static WAVE					m_WaveNum;									// ウェーブ番号
	static EDITOR				m_Editor;									// エディターの種類
	static ARRANGEMENT_MODEL	m_ArrangmentModel;							// 配置するモデルの種類

	/* メンバ変数 */
	std::vector<CModel*>		m_pMapModel;								// 可変長配列 設置するモデル
	std::vector<CEnemy*>		m_pEnemy;									// 可変長配列 設置したエネミー
	std::vector<CPrisoner*>		m_pPrisoner;								// 可変長配列 設置した捕虜
	std::vector<CObstacle*>		m_pObstacle;								// 可変長配列 設置した障害物
	std::vector<CPlayertank*>	m_pPlayerTank;								// 可変長配列 設置した戦車
	std::vector<CBattlePlane*>	m_pBattlePlane;								// 可変長配列 設置した戦闘機
	std::vector<CHelicopter*>	m_pHelicopter;								// 可変長配列 設置したヘリ
	std::vector<CVehicle*>		m_pVehicle;									// 可変長配列 設置した乗り物

	int							m_nOldSelect;								// 前回選択していたモノの番号
	int							m_nWaveID;									// ウェーブの出現番号
	WAVE_INFO					m_aWaveInfo[128];							// ウェーブの情報
	D3DXVECTOR3					m_WavePos;									// ウェーブの位置
};
#endif