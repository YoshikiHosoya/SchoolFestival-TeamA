#pragma once
#ifndef _CREATEMAP_H_
#define _CREATEMAP_H_
#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "model.h"
#include "Scene.h"
#include "inputKeyboard.h"
class CModel;
//レンダリングクラス
class CCreateMap:public CScene
{
public:
	CCreateMap(OBJ_TYPE type);
	 ~CCreateMap();
	 typedef struct
	 {
		 D3DXVECTOR3 pos;
		 D3DXVECTOR3 rot;
	 }LOAD_MODEL;
	 typedef enum
	 {
		 LOOAD_MAP_TUTORIAL,		//チュートリアルマップ
		 LOOAD_MAP_GAME01,			//ゲーム01マップ
		 LOOAD_MAP_GAME02,			//ゲーム02マップ
		 LOOAD_MAP_GAME03,			//ゲーム03マップ
		 LOOAD_MAP_MAX
	 }CREATE_MAP_MODEL;

	HRESULT Init(void);
	void Uninit(void) ;
	void Update(void) ;
	void Draw(void);
	void Save(void);
	void Load(int type);
	bool Collision(void);
	//bool CollisionModel(D3DXVECTOR3 *size , D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move);
	int GetMaxModel(void);
	static CCreateMap * Create(int type);
	D3DXVECTOR3 GetPosition(void);
	LPD3DXMESH GetMesh(int nCnt);
	CModel*GetModel(int nCnt);
private:
	std::vector<CModel*> m_vec;			//可変長配列 設置したモデル
	std::vector<CModel*> m_map;			//可変長配列 設置するモデル
	std::vector<CEnemy*> m_Enemy;		//可変長配列 設置したエネミー

	static char *m_LoadFileName[LOOAD_MAP_MAX];
	D3DXVECTOR3 m_pos;					//位置
	D3DXVECTOR3 m_move;					//移動量
	D3DXVECTOR3 m_rot;					//回転
	D3DXCOLOR m_col;					//カラー
	D3DXMATRIX m_mtxWorld;				//マトリックス
	D3DXMATRIX m_mtxRot;				//回転マトリックス
	CCreateMap *m_pParent;				//親のポインタ
	CPlayer *m_Player;
	LPDIRECT3DTEXTURE9 m_pTexture;
	LPD3DXMESH pMesh;
	int m_nIdxModelpalent;				//親のインデックス
	int m_nIdx;							//モデルのインデックス
	int m_type;
	int m_max;
	bool set;
};
#endif