#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_
#include "main.h"
#include "manager.h"
#include "renderer.h"
#define MAX_ALLMODEL (100)
//レンダリングクラス
class CModel
{
public:
	typedef enum
	{
		MODEL_PLAYER_HEAD,			//プレイヤーの頭
		MODEL_PLAYER_BODY,			//プレイヤーの体
		MODEL_PLAYER_LARM,			//プレイヤーの左腕
		MODEL_PLAYER_RARM,			//プレイヤーの右腕
		MODEL_PLAYER_LHAND,			//プレイヤーの左手
		MODEL_PLAYER_RHAND,			//プレイヤーの右手
		MODEL_PLAYER_LLEG,			//プレイヤーの左脚
		MODEL_PLAYER_RLEG,			//プレイヤーの右脚
		MODEL_PLAYER_LFOOT,			//プレイヤーの左足
		MODEL_PLAYER_RFOOT,			//プレイヤーの右足
		MODEL_PLAYER_FIRESWORD,		//プレイヤーの武器
		MODEL_PLAYER_ICESWORD,		//プレイヤーの武器
		MODEL_PLAYER_THUNDERSWORD,	//プレイヤーの武器
		MODEL_PLAYER_BALL,			//たま
		MODEL_PLAYER_MAX
	}CHARA_MODEL;
	typedef enum
	{
		MODEL_MAP_BLOCK,		//マップの武器
		MODEL_MAP_ICESWORD,			//マップの武器
		MODEL_MAP_MPPOTION,		//マップの武器
		MODEL_MAP_HPPOTION,				//
		MODEL_MAP_PORTAL,				//
		MODEL_MAP_BLOCK02,
		MODEL_MAP_MAX
	}CREATE_MAP_MODEL;
	typedef enum
	{
		//===[炎]===
		MODEL_ENEMY_HEAD_01,		//頭
		MODEL_ENEMY_BODY_01,		//体
		MODEL_ENEMY_LARM_01,		//左腕
		MODEL_ENEMY_RARM_01,		//右腕
		MODEL_ENEMY_LHAND_01,		//左手
		MODEL_ENEMY_RHAND_01,		//右手
		MODEL_ENEMY_LLEG_01,		//左脚
		MODEL_ENEMY_RLEG_01,		//右脚
		MODEL_ENEMY_LFOOT_01,		//左足
		MODEL_ENEMY_RFOOT_01,		//右足
		MODEL_ENEMY_WEPON_01,		//武器
		//===[闇]===
		MODEL_ENEMY_HEAD_02,		//頭
		MODEL_ENEMY_CHIN,			//顎
		MODEL_ENEMY_BODY_02,		//体
		MODEL_ENEMY_LARM_02,		//左腕
		MODEL_ENEMY_RARM_02,		//右腕
		MODEL_ENEMY_LHAND_02,		//左手
		MODEL_ENEMY_RHAND_02,		//右手
		MODEL_ENEMY_LLEG_02,		//左脚
		MODEL_ENEMY_RLEG_02,		//右脚
		MODEL_ENEMY_LFOOT_02,		//左足
		MODEL_ENEMY_RFOOT_02,		//右足
		MODEL_ENEMY_WEPON_02,		//武器
		//===[氷]===
		MODEL_ENEMY_HEAD_03,		//頭
		MODEL_ENEMY_BODY_03,		//体
		MODEL_ENEMY_LARM_03,		//左腕
		MODEL_ENEMY_RARM_03,		//右腕
		MODEL_ENEMY_LHAND_03,		//左手
		MODEL_ENEMY_RHAND_03,		//右手
		MODEL_ENEMY_LEG_03,			//脚
		MODEL_ENEMY_WEPON_03,		//武器
		//===[BOSS]===
		MODEL_BOSS_HEAD,		//頭
		MODEL_BOSS_BODY,		//体
		MODEL_BOSS_LARM,		//左腕
		MODEL_BOSS_RARM,		//右腕
		MODEL_BOSS_LHAND,		//左手
		MODEL_BOSS_RHAND,		//右手
		MODEL_BOSS_LFOOT,		//足
		MODEL_BOSS_RFOOT,		//足
		MODEL_BOSS_LEG,			//脚
		MODEL_BOSS_WEPON01,		//武器
		MODEL_BOSS_WEPON02,		//武器
		MODEL_ENEMY_MAX
	}ENEMY_PARTS_MODEL;
	typedef enum
	{
		PLAYER_MODEL,
		ENEMY_MODEL,
		MAP_MODEL,
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
	} MODEL;

	CModel();
	~CModel();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Drow(D3DXMATRIX mat);
	void SetParent(CModel *pModel);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRot(D3DXVECTOR3 rot);
	void SetSize(D3DXVECTOR3 size);
	void SetType(int type);
	int GetType(void);
	LPD3DXMESH GetMesh(void);
	D3DXMATRIX *GetMatrix(void);
	static void LoadModel(void);
	static void UnLoad(void);
	D3DXVECTOR3 GetPosition(void);
	D3DXVECTOR3 GetRot(void);
	D3DXVECTOR3 GetvtxMax(int nCnt);
	D3DXVECTOR3 GetvtxMin(int nCnt);
	static CModel *Create(int type, int modelCount);
private:

	static MODEL m_Model[TYPE_MAX][MAX_ALLMODEL];
	static char *m_PlayerFileName[MODEL_PLAYER_MAX];
	static char *m_EnemyFileName[MODEL_ENEMY_MAX];
	static char *m_MapFileName[MODEL_MAP_MAX];

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
	int m_nIdxModelpalzajient;				//親のインデックス
	int m_nIdx;							//モデルのインデックス
};
#endif