#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"

#define MAX_ALLMODEL (100)
// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CCollision;
//レンダリングクラス
class CModel : public CScene
{
public:
	/*--- プレイヤーのパーツモデル ---*/
	typedef enum
	{
		MODEL_PLAYER_WAIST,			//プレイヤーの腰
		MODEL_PLAYER_BODY,			//プレイヤーの体
		MODEL_PLAYER_HEAD,			//プレイヤーの頭
		MODEL_PLAYER_L_SHOLDER,		//プレイヤーの左肩
		MODEL_PLAYER_R_SHOLDER,		//プレイヤーの右肩
		MODEL_PLAYER_LARM,			//プレイヤーの左腕
		MODEL_PLAYER_RARM,			//プレイヤーの右腕
		MODEL_PLAYER_LHAND,			//プレイヤーの左手
		MODEL_PLAYER_RHAND,			//プレイヤーの右手
		MODEL_PLAYER_LKNEE,			//プレイヤーの左膝
		MODEL_PLAYER_RKNEE,			//プレイヤーの右膝
		MODEL_PLAYER_LLEG,			//プレイヤーの左脚
		MODEL_PLAYER_RLEG,			//プレイヤーの右脚
		MODEL_PLAYER_LFOOT,			//プレイヤーの左足
		MODEL_PLAYER_RFOOT,			//プレイヤーの右足
		MODEL_PLAYER_MAX
	}CHARA_MODEL;

	/*--- 捕虜のパーツモデル ---*/
	typedef enum
	{
		MODEL_PRISONER_WAIST,			//捕虜の腰
		MODEL_PRISONER_BODY,			//捕虜の体
		MODEL_PRISONER_HEAD,			//捕虜の頭
		MODEL_PRISONER_L_SHOLDER,		//捕虜の左肩
		MODEL_PRISONER_R_SHOLDER,		//捕虜の右肩
		MODEL_PRISONER_LARM,			//捕虜の左腕
		MODEL_PRISONER_RARM,			//捕虜の右腕
		MODEL_PRISONER_LHAND,			//捕虜の左手
		MODEL_PRISONER_RHAND,			//捕虜の右手
		MODEL_PRISONER_LKNEE,			//捕虜の左膝
		MODEL_PRISONER_RKNEE,			//捕虜の右膝
		MODEL_PRISONER_LLEG,			//捕虜の左脚
		MODEL_PRISONER_RLEG,			//捕虜の右脚
		MODEL_PRISONER_LFOOT,			//捕虜の左足
		MODEL_PRISONER_RFOOT,			//捕虜の右足
		MODEL_PRISONER_MAX
	}PRISONER_MODEL;

	typedef enum
	{
		MODEL_MAP_TUTORIAL,			//チュートリアルマップ
		MODEL_MAP_STAGE1_1,			//ステージ1-1
		MODEL_MAP_STAGE1_2,			//ステージ1-2
		MODEL_MAP_STAGE1_3,			//ステージ1-3
		MODEL_MAP_STAGE1_BOSS,		//ボスステージ1
		MODEL_MAP_MAX
	}MAP_MODEL;
	/*--- 敵のパーツモデル ---*/
	typedef enum
	{
		MODEL_ENEMY_WAIST,		//腰
		MODEL_ENEMY_HEAD,		//頭
		MODEL_ENEMY_BODY,		//体
		MODEL_ENEMY_L_SHOLDER,	//左肩
		MODEL_ENEMY_R_SHOLDER,	//右肩
		MODEL_ENEMY_LARM,		//左腕
		MODEL_ENEMY_RARM,		//右腕
		MODEL_ENEMY_LHAND,		//左手
		MODEL_ENEMY_RHAND,		//右手
		MODEL_ENEMY_LKNEE,		//左膝
		MODEL_ENEMY_RKNEE,		//右膝
		MODEL_ENEMY_LLEG,		//左脚
		MODEL_ENEMY_RLEG,		//右脚
		MODEL_ENEMY_LFOOT,		//左足
		MODEL_ENEMY_RFOOT,		//右足
		MODEL_ENEMY_MAX
	}ENEMY_PARTS_MODEL;
	/*--- 銃のモデル ---*/
	typedef enum
	{
		MODEL_GUN_HANDGUN,				// ハンドガン
		MODEL_GUN_HEAVYMACHINEGUN,		// ヘビーマシンガン
		MODEL_GUN_SHOTGUN,				// ショットガン
		MODEL_GUN_LASERGUN,				// レーザーガン
		MODEL_GUN_ROCKETLAUNCHER,		// ロケットランチャー
		MODEL_GUN_FLAMESHOT,			// フレイムショット
		MODEL_GUN_TANKGUN,				// 戦車の銃
		MODEL_GUN_PLANEGUN,				// 戦闘機の銃
		MODEL_GUN_HELIGUN,				// ヘリの銃
		MODEL_KNIFE,					// ナイフ
		MODEL_GUN_MAX
	}GUN_MODEL;
	/*--- 弾のモデル ---*/
	typedef enum
	{
		MODEL_BULLET_SPHERE,			// 丸
		MODEL_BULLET_ROCKETLAUNCHER,	// ロケットランチャー
		MODEL_BULLET_GRENADE,			// グレネード
		MODEL_BULLET_MAX
	}BULLET_MODEL;

	typedef enum
	{
		//===戦車のモデル===
		MODEL_TANK_TANKBODY,		// 体
		MODEL_TANK_TANK_FRONTWHEEL,	// 前タイヤ
		MODEL_TANK_TANK_BACKWHEEL,	// 後タイヤ
		MODEL_TANK_TANKGUN,			// 武器
		MODEL_TANK_MAX
	}TANK_PARTS_MODEL;

	// モデルの種類
	typedef enum
	{
		//===戦闘機のモデル===
		MODEL_PLANE_BODY,			// 機体
		MODEL_PLANE_GUN,			// 武器
		MODEL_PLANE_MAX
	}PLANE_PARTS_MODEL;

	// モデルの種類
	typedef enum
	{
		//===ヘリのモデル===
		MODEL_HELIBODY,				// 機体
		MODEL_HELIPROPELLER,		// プロペラ
		MODEL_HELIGUN,				// 武器
		MODEL_HELI_MAX
	}HELI_PARTS_MODEL;

	// モデルの種類
	typedef enum
	{
		//===ボスのモデル===
		MODEL_BOSS_BODY,			// 体
		MODEL_BOSS_MAX
	}BOSS_PARTS_MODEL;

	//全モデルの種類
	typedef enum
	{
		PLAYER_MODEL,
		ENEMY_MODEL,
		MAP_MODEL,
		GUN_MODEL,
		BULLET_MODEL,
		OBSTACLE_MODEL,
		PRISONER_MODEL,
		TANK_MODEL,
		PLANE_MODEL,
		HELI_MODEL,
		BOSS_MODEL,
		TYPE_MAX
	}MODEL_TYPE;

	// 障害物の種類
	typedef enum
	{
		OBSTACLE_TYPE_BOX = 0,								// ハコ
		OBSTACLE_TYPE_BARREL,								// 樽
		OBSTACLE_TYPE_TREE,									// 木
		OBSTACLE_TYPE_CHEST,								// 金庫
		OBSTACLE_TYPE_SANDBAGS,								// 土嚢
		OBSTACLE_TYPE_MAX,									// 障害物
	}OBSTACLE_TYPE;

	typedef struct
	{
		LPD3DXBUFFER pBuffmat;
		DWORD nNumMat;
		LPD3DXMESH pMesh;
		LPDIRECT3DTEXTURE9 *m_pTexture;
		D3DXVECTOR3 vtxMax;
		D3DXVECTOR3 vtxMin;
		//D3DXVECTOR3 Dest;
	} MODEL;

	CModel() {};
	CModel(OBJ_TYPE type);				// コンストラクタ
	~CModel();							// デストラクタ

	/* メンバ関数 */
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(D3DXMATRIX mat);			// 描画処理
	void Draw();						// 描画処理
	void DebugInfo();					// デバッグ情報

	/* 静的メンバ関数 */
	static void LoadModel(void);									// モデルのロード
	static void UnLoad(void);										// モデルの開放
	static CModel *Create(int type, int modelCount);				// モデルのクリエイト
	static CModel *CreateSceneManagement(int type, int modelCount);	// モデルのクリエイト(シーンで管理する)
	static char* GetModelFileName(int nType, int nModelCount);		// モデルのファイル名取得

	void NotDrawCalcMtxOnly(D3DXMATRIX *pParentMtx);				// 描画せずにマトリックスの計算だけする

	/* メンバ関数 */
	void SetParent(CModel *pModel)					{ m_pParent = pModel; };							// 親の設定
	void SetPosition(D3DXVECTOR3 pos)				{ m_pos = pos; };									// モデルのオフセット指定
	void SetRot(D3DXVECTOR3 rot)					{ m_rot = rot; };									// 回転の設定
	void SetSize(D3DXVECTOR3 size)					{ m_size = size; };									// サイズの設定
	void SetType(int type)							{ m_type = type; };									// モデルタイプの設定
	void SetModelConut(int nModelCount)				{ m_modelCount = nModelCount; };					// モデルカウントの設定
	void SetParentIdx(int nParentIdx)				{ m_nParentIdx = nParentIdx; };						// 親番号設定
	void SetDieFlag(bool DieFlag)					{ m_bDieFlag = DieFlag; };							// 死亡フラグの設定
	void SetColorChangeFlag(bool ColorChangeFlag)	{ m_bColorChangeFlag = ColorChangeFlag; };			// 色変更フラグの設定
	void SetAddColor(D3DXCOLOR AddColor)			{ m_AddColor = AddColor; };							// 加算する色の設定
	D3DXVECTOR3 &GetPosition(void)					{ return m_pos; };									// 位置の取得
	D3DXVECTOR3 &GetRot(void)						{ return m_rot; };									// 回転の取得
	D3DXVECTOR3 &GetSize(void)						{ return m_size; };									// サイズの取得
	D3DXVECTOR3 GetvtxMax(int nCnt)					{ return m_Model[MODEL_TYPE::MAP_MODEL][nCnt].vtxMax;};			// 頂点情報のMAX取得
	D3DXVECTOR3 GetvtxMin(int nCnt)					{ return m_Model[MODEL_TYPE::MAP_MODEL][nCnt].vtxMin; };		// 頂点情報のMIN取得
	int GetType()									{ return m_type; };									// モデルタイプの取得
	int &GetModelCount()							{ return m_modelCount; };							// モデルカウントの取得
	int &GetParentIdx()								{ return m_nParentIdx; };							// 親番号取得
	D3DXMATRIX *GetMatrix(void)						{ return &m_mtxWorld; };							// マトリックスの取得
	LPD3DXMESH GetMesh(void)						{ return m_Model[m_type][m_modelCount].pMesh; };	// メッシュ取得
	CCollision *GetCollision()						{ return m_pCollision; };							// 当たり判定のポインタ取得
	bool GetDieFlag()								{ return m_bDieFlag; };								// 死亡フラグの取得
	bool GetColorChangeFlag()						{ return m_bColorChangeFlag; };						// 色変更フラグの取得
	D3DXCOLOR	GetAddColor()						{ return m_AddColor; };								// 加算する色の取得

private:
	/* メンバ関数 */
	void DrawMesh();			// 描画

	static MODEL m_Model[TYPE_MAX][MAX_ALLMODEL];
	static char *m_PlayerFileName[MODEL_PLAYER_MAX];
	static char *m_EnemyFileName[MODEL_ENEMY_MAX];
	static char *m_GunFileName[MODEL_GUN_MAX];
	static char *m_BulletFileName[MODEL_BULLET_MAX];
	static char *m_MapFileName[MODEL_MAP_MAX];
	static char *m_ObstacleFileName[OBSTACLE_TYPE_MAX];
	static char *m_PrisonerFileName[MODEL_PRISONER_MAX];
	static char *m_TankFileName[MODEL_TANK_MAX];
	static char *m_PlaneFileName[MODEL_PLANE_MAX];
	static char *m_HeliFileName[MODEL_HELI_MAX];
	static char *m_BossFileName[MODEL_BOSS_MAX];

	D3DXVECTOR3		m_pos;					//位置
	D3DXVECTOR3		m_size;					//サイズ
	D3DXVECTOR3		m_posold;				//位置
	D3DXVECTOR3		m_move;					//移動量
	D3DXVECTOR3		m_rot;					//回転
	D3DXCOLOR		m_col;					//カラー
	D3DXCOLOR		m_AddColor;				//加算する色
	D3DXMATRIX		m_mtxWorld;				//マトリックス
	D3DXMATRIX		m_mtxparent;
	CModel			*m_pParent;				//親のポインタ
	int				m_modelCount;			//モデルの種類
	int				m_type;
	int				m_nIdxModelpalent;		//親のインデックス
	int				m_nParentIdx;			//親番号
	bool			m_bDieFlag;				// 死亡フラグ
	bool			m_bColorChangeFlag;		// 色変更フラグ
	CCollision		*m_pCollision;			// 当たり判定情報
};
#endif
