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
class CShield;
class CBoss_One;
// =====================================================================================================================================================================
// マップクラス
// =====================================================================================================================================================================
class CMap
{
public:
	// ----------- 構造体 -----------
	// ウェーブのパラメーター
	typedef struct
	{
		int			nType;			// 種類
		int			nItemType;		// 確定ドロップするアイテムのタイプ
		D3DXVECTOR3	pos;			// 位置
		int			nFrame;			// フレーム
		bool		bEvent;			// イベントフラグ
	} WAVE_PARAM;

	// ウェーブの情報
	typedef struct
	{
		std::vector<WAVE_PARAM*> EnemyWaveInfo;			// 敵のウェーブのパラメーター
		std::vector<WAVE_PARAM*> PrisonerWaveInfo;		// 捕虜のウェーブパラメーター
		D3DXVECTOR3 EventPos;							// イベントが起きる位置
	} WAVE_INFO;

	// マップの種類
	enum MAP
	{
		MAP_TUTORIAL,		// チュートリアル
		MAP_1_1,			// 1_1
		MAP_1_2,			// 1_2
		MAP_1_3,			// 1_3
		MAP_1_BOSS,			// 1_BOSS
		MAP_MAX
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
		ARRANGEMENT_MODEL_BOSS,					// ボス
		ARRANGEMENT_MODEL_BOSS_ONE,				// ボス1
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
	static	CMap	*MapCreate();													// マップの生成

	/* メンバ関数 */
	void			MapUpdate();													// マップの更新
	void			MapLoad(MAP MapNum);											// マップのロード
	void			WaveLoad(WAVE WaveNum);											// ウェーブのロード
	void			UpdateDieFlag();												// 死亡フラグ確認関数
	void			AllDelete();													// 配置しているモデルを全て破棄
	void			WaveCreate(int nModelType, int nType, int nItemType, D3DXVECTOR3 pos);	// Waveの生成

	int				GetMaxModel();													// モデルの最大数取得
	int				GetMaxEnemy();													// 敵の最大数取得
	int				GetMaxPrisoner();												// 捕虜の最大数取得
	int				GetMaxObstacle();												// 障害物の最大数取得
	int				GetMaxPlayerTank();												// 戦車の最大数取得
	int				GetMaxBattlePlane();											// 戦闘機の最大数取得
	int				GetMaxHelicopter();												// ヘリの最大数取得

	// 仮 今だけ
	int				GetMaxBoss_One();												//

	MAP				GetMapNum() { return m_MapNum; };								// マップ番号取得
	LPD3DXMESH		GetMesh(int nCnt);												// メッシュの取得
	CModel			*GetModel(int nCnt) { return m_pMapModel[nCnt]; };				// モデルの取得
	CEnemy			*GetEnemy(int nCnt) { return m_pEnemy[nCnt]; };					// 敵の取得
	CPrisoner		*GetPrisoner(int nCnt) { return m_pPrisoner[nCnt]; };			// 捕虜の取得
	CObstacle		*GetObstacle(int nCnt) { return m_pObstacle[nCnt]; };			// 障害物の取得
	CPlayertank		*GetPlayertank(int nCnt) { return m_pPlayerTank[nCnt]; };		// 戦車の取得
	CBattlePlane	*GetBattlePlane(int nCnt) { return m_pBattlePlane[nCnt]; };		// 戦闘機の取得
	CHelicopter		*GetHelicopter(int nCnt) { return m_pHelicopter[nCnt]; };		// ヘリコプターの取得
	CBoss_One		*GetBoss_One(int nCnt) { return m_pBoss_One[nCnt]; };			// ボス1の取得

	WAVE_INFO		GetWaveInfo(int nWaveNum) { return m_aWaveInfo[nWaveNum]; };	// ウェーブ情報の取得
	D3DXVECTOR3		GetTransitionPos() { return m_TransitionPos; };					// 遷移するための位置の取得
	int				GetTransitionMapID() { return m_TransitionMapID; }				// 次に遷移するためのマップ番号の取得
	CShield			*GetShield(int nCnt) { return m_pShield[nCnt]; };				// shieldの取得
private:
	/* メンバ関数 */
	void			MapModelLoad();																// 配置するモデルのロード
	void			MapModelSave();																// 配置するモデルのセーブ

	void			MapModelCreate(int ModelType, int nType, D3DXVECTOR3 pos, int nItemType);	// 配置するモデルの生成
	void			LoadSuccessMessage(int ModelType);											// 読み込み成功時の結果表示

	void			SaveModelHeader(FILE *pFile, int ModelType);								// セーブするモデルのヘッダー
	void			SaveModelContents(FILE *pFile, int ModelType, int nCnt, int nNum);			// セーブするモデルの情報
	void			SaveBGContents(FILE *pFile);												// セーブする背景の情報

	size_t			GetMaxMapModel(int ModelType);												// 配置するモデルの最大数取得
	void			*GetMapModel(int ModelType, int nCnt);										// 配置するモデルのポインタ

	void			ModelDelete(int nNowSelect);												// 配置するモデルをデリート
	void			ModelCreat();																// 配置するモデルを生成

	D3DXVECTOR3		GetMapModelPos(int nNowSelect);												// 選択しているモデルの位置の取得
	void			SetMapModelPos(D3DXVECTOR3 pos, int nNowSelect);							// 選択しているモデルの位置の設定
	void			SetMapModelColorChangeFlag(bool bFlag, int nNowSelect);						// 選択しているモデルの色を半透明にするフラグの設定
	void			MapModelTab();																// マップに配置するモデルのタブ
	void			MapModelSet();																// マップに配置するモデルの設置
	void			ComboBoxAll(int nNowSelect);												// 全てのコンボボックス
	void			MapComboBox(int &nSelectType, int nNowSelect);								// マップのコンボボックス
	void			MapTypeComboBox();															// マップの種類のコンボボックス
	void			ObstacleTypeComboBox(int &nSelectType, int nNowSelect);						// 障害物の種類のコンボボックス
	void			EnemyTypeComboBox(int &nSelectType, int nNowSelect);						// 敵の種類のコンボボックス
	void			PrisonerDropTypeComboBox(int &nSelectType, int nNowSelect);					// 捕虜のドロップタイプのコンボボックス
	void			PrisonerItemTypeComboBox(int &nSelectType, int nNowSelect);					// 捕虜のアイテムタイプのコンボボックス
	void			SetSelectMapModelPosRDest(D3DXVECTOR3 posR);								// 選択しているモデルを注視点の目的地に設定

	/* 静的メンバ変数 */
	static char					*m_MapModelFileName[MAP_MAX];				// マップモデルファイル名
	static char					*m_WaveFileName[WAVE_MAX];					// ウェーブファイル名

	static MAP					m_MapNum;									// マップ番号
	static WAVE					m_WaveNum;									// ウェーブ番号
	static ARRANGEMENT_MODEL	m_ArrangmentModel;							// 配置するモデルの種類
	static WAVE_INFO			m_aWaveInfo[WAVE_MAX];						// ウェーブの情報

	/* メンバ変数 */
	std::vector<CModel*>		m_pMapModel;								// 可変長配列 設置するマップモデル
	std::vector<CEnemy*>		m_pEnemy;									// 可変長配列 設置したエネミー
	std::vector<CPrisoner*>		m_pPrisoner;								// 可変長配列 設置した捕虜
	std::vector<CObstacle*>		m_pObstacle;								// 可変長配列 設置した障害物
	std::vector<CPlayertank*>	m_pPlayerTank;								// 可変長配列 設置した戦車
	std::vector<CBattlePlane*>	m_pBattlePlane;								// 可変長配列 設置した戦闘機
	std::vector<CHelicopter*>	m_pHelicopter;								// 可変長配列 設置したヘリ
	std::vector<CVehicle*>		m_pVehicle;									// 可変長配列 設置した乗り物
	std::vector<CShield*>		m_pShield;
	// 仮 今だけ
	std::vector<CBoss_One*>		m_pBoss_One;								// 可変長配列 設置したボス1

	int							m_nOldSelect;								// 前回選択していたモノの番号
	D3DXVECTOR3					m_WavePos;									// ウェーブの位置
	D3DXVECTOR3					m_TransitionPos;							// 遷移する位置
	D3DXVECTOR3					m_CameraPos;								// カメラの位置
	int							m_TransitionMapID;							// 次に遷移するマップの番号
	int							m_nBGTexID;									// 背景のテクスチャ番号
	bool						m_bCameraFollowing;							// カメラを追従するフラグ
	bool						m_bMapExclusion;							// マップモデル以外適用するフラグ
};

#endif