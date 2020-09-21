#pragma once
// =====================================================================================================================================================================
//
// モデルの処理 [Model.h]
// Author :Hanzawa
//
// =====================================================================================================================================================================
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "Scene.h"

#define MAX_ALLMODEL (130)
// =====================================================================================================================================================================
// 前方宣言
// =====================================================================================================================================================================
class CCollision;
//レンダリングクラス
class CModel : public CScene
{
public:
	/*--- モデル一覧 ---*/
	typedef enum
	{
		//===プレイヤーのモデル===
		MODEL_PLAYER_WAIST,				// プレイヤーの腰
		MODEL_PLAYER_BODY,				// プレイヤーの体
		MODEL_PLAYER_HEAD,				// プレイヤーの頭
		MODEL_PLAYER_L_SHOLDER,			// プレイヤーの左肩
		MODEL_PLAYER_R_SHOLDER,			// プレイヤーの右肩
		MODEL_PLAYER_LARM,				// プレイヤーの左腕
		MODEL_PLAYER_RARM,				// プレイヤーの右腕
		MODEL_PLAYER_LHAND,				// プレイヤーの左手
		MODEL_PLAYER_RHAND,				// プレイヤーの右手
		MODEL_PLAYER_LKNEE,				// プレイヤーの左膝
		MODEL_PLAYER_RKNEE,				// プレイヤーの右膝
		MODEL_PLAYER_LLEG,				// プレイヤーの左脚
		MODEL_PLAYER_RLEG,				// プレイヤーの右脚
		MODEL_PLAYER_LFOOT,				// プレイヤーの左足
		MODEL_PLAYER_RFOOT,				// プレイヤーの右足
		//===敵のモデル===
		//人型
		MODEL_ENEMY_HUMAN_WAIST=100,			// 腰
		MODEL_ENEMY_HUMAN_HEAD,					// 頭
		MODEL_ENEMY_HUMAN_BODY,					// 体
		MODEL_ENEMY_HUMAN_L_SHOLDER,			// 左肩
		MODEL_ENEMY_HUMAN_R_SHOLDER,			// 右肩
		MODEL_ENEMY_HUMAN_LARM,					// 左腕
		MODEL_ENEMY_HUMAN_RARM,					// 右腕
		MODEL_ENEMY_HUMAN_LHAND,				// 左手
		MODEL_ENEMY_HUMAN_RHAND,				// 右手
		MODEL_ENEMY_HUMAN_LKNEE,				// 左膝
		MODEL_ENEMY_HUMAN_RKNEE,				// 右膝
		MODEL_ENEMY_HUMAN_LLEG,					// 左脚
		MODEL_ENEMY_HUMAN_RLEG,					// 右脚
		MODEL_ENEMY_HUMAN_LFOOT,				// 左足
		MODEL_ENEMY_HUMAN_RFOOT,				// 右足

		//ヘリ
		MODEL_ENEMY_HELICOPTER_BODY,			// 胴体
		MODEL_ENEMY_HELICOPTER_PROPELLER,		// プロペラ

		//MeltyHoney(???)
		MODEL_ENEMY_MELTYHONEY_BODY,			// 胴体
		MODEL_ENEMY_MELTYHONEY_WHEEL,			// ホイール

		//Zycocca(???)
		MODEL_ENEMY_ZYCOCCA_BODY,				// 胴体
		MODEL_ENEMY_ZYCOCCA_WHEEL,				// ホイール

		//===マップのモデル===
		MODEL_MAP_TUTORIAL=200,			// チュートリアルマップ
		MODEL_MAP_STAGE1_1,				// ステージ1-1
		MODEL_MAP_STAGE1_2,				// ステージ1-2
		MODEL_MAP_STAGE1_3,				// ステージ1-3
		MODEL_MAP_STAGE1_BOSS,			// ボスステージ1
		MODEL_MAP_STAGE2_1,				// ステージ2-1
		MODEL_MAP_STAGE2_2,				// ステージ2-2
		MODEL_MAP_STAGE2_3,				// ステージ2-3
		MODEL_MAP_STAGE2_BOSS,			// ボスステージ2
		//===銃のモデル===
		MODEL_GUN_HANDGUN=300,			// ハンドガン
		MODEL_GUN_HEAVYMACHINEGUN,		// ヘビーマシンガン
		MODEL_GUN_SHOTGUN,				// ショットガン
		MODEL_GUN_LASERGUN,				// レーザーガン
		MODEL_GUN_ROCKETLAUNCHER,		// ロケットランチャー
		MODEL_GUN_FLAMESHOT,			// フレイムショット
		MODEL_GUN_TANKGUN,				// 戦車の銃
		MODEL_GUN_PLANEGUN,				// 戦闘機の銃
		MODEL_GUN_HELIGUN,				// ヘリの銃
		MODEL_GUN_BALKAN,				// バルカン
		MODEL_GUN_FLAMETHROWER,			// 火炎放射器
		MODEL_GUN_INCENDIARY,			// 焼夷弾
		MODEL_KNIFE,					// ナイフ
		//===弾のモデル===
		MODEL_BULLET_SPHERE=400,		// 丸
		MODEL_BULLET_ROCKETLAUNCHER,	// ロケットランチャー
		MODEL_BULLET_GRENADE,			// グレネード
		MODEL_BULLET_TANKGRENADE,		// 戦車のグレネード
		MODEL_BULLET_MISSILE,			// ミサイル
		//===障害物のモデル===
		OBSTACLE_TYPE_BOX=500,			// ハコ
		OBSTACLE_TYPE_BARREL,			// 樽
		OBSTACLE_TYPE_BARRELBOMB,		// 樽爆弾
		OBSTACLE_TYPE_TREE,				// 木
		OBSTACLE_TYPE_CHEST,			// 金庫
		OBSTACLE_TYPE_SANDBAGS,			// 土嚢
		OBSTACLE_TYPE_CAR,				// 車
		OBSTACLE_TYPE_MAX,				// 最大数(計算用)

		//===捕虜のモデル===
		MODEL_PRISONER_WAIST=600,		// 捕虜の腰
		MODEL_PRISONER_BODY,			// 捕虜の体
		MODEL_PRISONER_HEAD,			// 捕虜の頭
		MODEL_PRISONER_L_SHOLDER,		// 捕虜の左肩
		MODEL_PRISONER_R_SHOLDER,		// 捕虜の右肩
		MODEL_PRISONER_LARM,			// 捕虜の左腕
		MODEL_PRISONER_RARM,			// 捕虜の右腕
		MODEL_PRISONER_LHAND,			// 捕虜の左手
		MODEL_PRISONER_RHAND,			// 捕虜の右手
		MODEL_PRISONER_LKNEE,			// 捕虜の左膝
		MODEL_PRISONER_RKNEE,			// 捕虜の右膝
		MODEL_PRISONER_LLEG,			// 捕虜の左脚
		MODEL_PRISONER_RLEG,			// 捕虜の右脚
		MODEL_PRISONER_LFOOT,			// 捕虜の左足
		MODEL_PRISONER_RFOOT,			// 捕虜の右足

		//===戦車のモデル===
		MODEL_TANK_TANKBODY=700,		// 体
		MODEL_TANK_TANK_FRONTWHEEL,		// 前タイヤ
		MODEL_TANK_TANK_BACKWHEEL,		// 後タイヤ
		MODEL_TANK_TANKGUN,				// 武器
		//MODEL_TANK_TANKHEAD,
		//===戦闘機のモデル===
		MODEL_PLANE_BODY=800,			// 機体
		MODEL_PLANE_GUN,			// 武器
		//===ヘリのモデル===
		MODEL_HELIBODY=900,				// 機体
		MODEL_HELIPROPELLER,			// プロペラ
		MODEL_HELIGUN,					// 武器
		//===2面ボスのモデル===
		MODEL_BOSS_BODY=1000,			// 体
		//===ボス ドラゴンノスケのモデル===
		MODEL_BOSSONE_BODY=1100,		// 体
		MODEL_BOSSONE_HEAD,				// 頭
		MODEL_BOSSONE_KNEE_L_FRONT,		// 左前大腿
		MODEL_BOSSONE_KNEE_L_REAR,		// 左後大腿
		MODEL_BOSSONE_KNEE_R_FRONT,		// 右前大腿
		MODEL_BOSSONE_KNEE_R_REAR,		// 右後大腿
		MODEL_BOSSONE_KNEE2_L_FRONT,	// 左前大腿2
		MODEL_BOSSONE_KNEE2_L_REAR,		// 左後大腿2
		MODEL_BOSSONE_KNEE2_R_FRONT,	// 右前大腿2
		MODEL_BOSSONE_KNEE2_R_REAR,		// 右後大腿2
		MODEL_BOSSONE_LEG_L_FRONT,		// 左前下腿
		MODEL_BOSSONE_LEG_L_REAR,		// 左後下腿
		MODEL_BOSSONE_LEG_R_FRONT,		// 右前下腿
		MODEL_BOSSONE_LEG_R_REAR,		// 右後下腿
		MODEL_BOSSONE_L_VENTILATION,	// 鉄板
		MODEL_BOSSONE_R_VENTILATION,	// 鉄板
		MODEL_BOSSONE_LIGHT_L_FRONT,	// 青電気
		MODEL_BOSSONE_LIGHT_L_REAR,		// 青電気
		MODEL_BOSSONE_LIGHT_R_FRONT,	// 青電気
		MODEL_BOSSONE_LIGHT_R_REAR,		// 青電気
		MODEL_BOSSONE_GUN_BALKAN,		// バルカン
		MODEL_BOSSONE_GUN_FLAMETHROWER,	// 火炎放射器
		MODEL_BOSSONE_GUN_INCENDIARY,	// 焼夷弾
		//===盾モデル===
		MODEL_WEPON_SHIELD=1200,		// 盾
		MODEL_MAX
	}CHARA_MODEL;
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
		BOSS_ONE_MODEL,
		WEPON_MODEL,
		TYPE_MAX
	}MODEL_TYPE;

	typedef struct
	{
		LPD3DXBUFFER pBuffmat;
		DWORD nNumMat;
		LPD3DXMESH pMesh;
		LPDIRECT3DTEXTURE9 *m_pTexture;
		D3DXVECTOR3 vtxMax;
		D3DXVECTOR3 vtxMin;
		//D3DXVECTOR3 Dest;
		CHARA_MODEL ModelID;

	} MODEL;
	typedef struct
	{
		char *modelFileName;
		CHARA_MODEL FileModelID;
	}MODEL_FILE_NAME;

	CModel() {};
	CModel(OBJ_TYPE type);				// コンストラクタ
	virtual~CModel();							// デストラクタ

	/* メンバ関数 */
	HRESULT Init(void);					// 初期化処理
	void Uninit(void);					// 終了処理
	void Update(void);					// 更新処理
	void Draw(D3DXMATRIX mat);			// 描画処理
	void Draw();						// 描画処理
	virtual void DebugInfo();			// デバッグ情報

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
	void SetType(int type)					;					// モデルタイプの設定
	void SetModelConut(int nModelCount)		;					// モデルカウントの設定
	void SetParentIdx(int nParentIdx)				{ m_nParentIdx = nParentIdx; };						// 親番号設定
	void SetDieFlag(bool DieFlag)					{ m_bDieFlag = DieFlag; };							// 死亡フラグの設定
	void SetColorChangeFlag(bool ColorChangeFlag)	{ m_bColorChangeFlag = ColorChangeFlag; };			// 色変更フラグの設定
	void SetAddColor(D3DXCOLOR AddColor)			{ m_AddColor = AddColor; };							// 加算する色の設定
	void SetDisp(bool bDisp)						{ m_bDisp = bDisp; };								// 画面に描画するかどうか
	D3DXVECTOR3 &GetPosition(void)					{ return m_pos; };									// 位置の取得
	D3DXVECTOR3 *GetPositionPtr()					{ return &m_pos; };									// 位置の取得　ポインタで
	D3DXVECTOR3 &GetRot(void)						{ return m_rot; };									// 回転の取得
	D3DXVECTOR3 &GetSize(void)						{ return m_size; };									// サイズの取得
	D3DXVECTOR3 GetvtxMax(int nCnt)					{ return m_vModel[nCnt]->vtxMax;};					// 頂点情報のMAX取得
	D3DXVECTOR3 GetvtxMin(int nCnt)					{ return m_vModel[nCnt]->vtxMin; };					// 頂点情報のMIN取得
	int GetType()									{ return m_type; };									// モデルタイプの取得
	int &GetModelCount()							{ return m_modelCount; };							// モデルカウントの取得
	int &GetParentIdx()								{ return m_nParentIdx; };							// 親番号取得
	D3DXMATRIX *GetMatrix(void)						{ return &m_mtxWorld; };							// マトリックスの取得
	LPD3DXMESH GetMesh(void);																			// メッシュ取得
	CCollision *GetCollision()						{ return m_pCollision; };							// 当たり判定のポインタ取得
	bool GetDieFlag()								{ return m_bDieFlag; };								// 死亡フラグの取得
	bool GetColorChangeFlag()						{ return m_bColorChangeFlag; };						// 色変更フラグの取得
	D3DXCOLOR	GetAddColor()						{ return m_AddColor; };								// 加算する色の取得
	bool		GetDisp()							{ return m_bDisp; };								// 描画するかどうか取得
	void DeleteCollision();																				// 判定の消去
	void SetModelID(CHARA_MODEL model);
	static int GetModelID(CHARA_MODEL model);

private:
	/* メンバ関数 */
	void DrawMesh();			// 描画
	static std::vector<MODEL_FILE_NAME> m_vModelFileName;
	static std::vector<MODEL*>m_vModel;

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
	bool			m_bDisp;				// 描画するかどうか
	CCollision		*m_pCollision;			// 当たり判定情報
	CHARA_MODEL		m_modelID;
	int				m_ModelCountID;
};
#endif
