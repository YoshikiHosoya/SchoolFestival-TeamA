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

	typedef enum
	{
		MODEL_PRISONER_HEAD,			//捕虜の頭
		MODEL_PRISONER_BODY,			//捕虜の体
		MODEL_PRISONER_LARM,			//捕虜の左腕
		MODEL_PRISONER_RARM,			//捕虜の右腕
		MODEL_PRISONER_LHAND,			//捕虜の左手
		MODEL_PRISONER_RHAND,			//捕虜の右手
		MODEL_PRISONER_LLEG,			//捕虜の左脚
		MODEL_PRISONER_RLEG,			//捕虜の右脚
		MODEL_PRISONER_LFOOT,			//捕虜の左足
		MODEL_PRISONER_RFOOT,			//捕虜の右足
		MODEL_PRISONER_MAX
	}PRISONER_MODEL;

	typedef enum
	{
		MODEL_MAP_BLOCK,			//マップの武器
		MODEL_MAP_ICESWORD,			//マップの武器
		MODEL_MAP_MAX
	}CREATE_MAP_MODEL;
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
		MODEL_TANK_TANKHEAD,		// 頭
		MODEL_TANK_TANKBODY,		// 体
		MODEL_TANK_TANK_FRONTWHEEL,	// 前タイヤ
		MODEL_TANK_TANK_BACKWHEEL,	// 後タイヤ
		MODEL_TANK_TANKGUN,			// 武器
		MODEL_TANK_MAX
	}TANK_PARTS_MODEL;

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

	CModel(OBJ_TYPE type);
	~CModel();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(D3DXMATRIX mat);
	void Draw();
	void DebugInfo();
	void SetParent(CModel *pModel);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetType(int type)				{ m_type = type; };					// モデルタイプの設定
	void SetModelConut(int nModelCount) { m_modelCount = nModelCount; };	// モデルカウントの設定
	void SetParentIdx(int nParentIdx)	{ m_nParentIdx = nParentIdx; };		// 親番号設定
	int GetType()						{ return m_type; };					// モデルタイプの取得
	int &GetModelCount()				{ return m_modelCount; };			// モデルカウントの取得
	int &GetParentIdx()					{ return m_nParentIdx; };			// 親番号取得
	LPD3DXMESH GetMesh(void);
	D3DXMATRIX *GetMatrix(void);
	static void LoadModel(void);
	static void UnLoad(void);
	D3DXVECTOR3 &GetPosition(void);
	D3DXVECTOR3 &GetRot(void);
	D3DXVECTOR3 &GetSize(void);
	D3DXVECTOR3 GetvtxMax(int nCnt);
	D3DXVECTOR3 GetvtxMin(int nCnt);
	static CModel *Create(int type, int modelCount);
	static CModel *CreateSceneManagement(int type, int modelCount);
	D3DXVECTOR3 *GetPosptr() { return &m_pos; };

	static char* GetModelFileName(int nType, int nModelCount);
	bool GetDieFlag() { return m_bDieFlag; };							// 死亡フラグの取得
	void SetDieFlag(bool DieFlag) { m_bDieFlag = DieFlag; };			// 死亡フラグの設定

	CCollision *GetCollision() { return m_pCollision; };				// 当たり判定のポインタ取得
private:

	static MODEL m_Model[TYPE_MAX][MAX_ALLMODEL];
	static char *m_PlayerFileName[MODEL_PLAYER_MAX];
	static char *m_EnemyFileName[MODEL_ENEMY_MAX];
	static char *m_GunFileName[MODEL_GUN_MAX];
	static char *m_BulletFileName[MODEL_BULLET_MAX];
	static char *m_MapFileName[MODEL_MAP_MAX];
	static char *m_ObstacleFileName[OBSTACLE_TYPE_MAX];
	static char *m_PrisonerFileName[MODEL_PRISONER_MAX];
	static char *m_TankFileName[MODEL_TANK_MAX];


	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_size;					//サイズ
	D3DXVECTOR3 m_posold;				//位置
	D3DXVECTOR3 m_move;					//移動量
	D3DXVECTOR3 m_rot;					//回転
	D3DXCOLOR m_col;					//カラー
	D3DXMATRIX m_mtxWorld;				//マトリックス
	D3DXMATRIX m_mtxparent;
	CModel *m_pParent;					//親のポインタ
	int m_modelCount;					//モデルの種類
	int m_type;
	int m_nIdxModelpalent;				//親のインデックス
	int m_nParentIdx;					//親番号
	bool m_bDieFlag;					// 死亡フラグ
	CCollision				*m_pCollision;			// 当たり判定情報
};
#endif
