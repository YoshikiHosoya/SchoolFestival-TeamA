#pragma once
//=============================================================================
// シーンヘッダー [Scene.h]: NORI
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

#define MAX (1000)
class CPause;
//レンダリングクラス
class CScene
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		OBJTYPE_BG,
		OBJTYPE_FIELD_NOCOLLIISION,
		OBJTYPE_FIELD,
		OBJTYPE_MODEL,
		OBJTYPE_PLAYER,
		OBJTYPE_BULLET,
		OBJTYPE_OBSTACLE,
		OBJTYPE_CREATE,
		OBJTYPE_ENEMY,
		OBJTYPE_SHIELD,
		OBJTYPE_KNIFE,
		OBJTYPE_BOSS,
		OBJTYPE_BOSSONE,
		OBJTYPE_PRISONER,
		OBJTYPE_PLAYER_VEHICLE,
		OBJTYPE_ENEMY_VEHICLE,
		OBJTYPE_EFFECT,
		OBJTYPE_PARTICLE,
		OBJTYPE_ORBIT,
		OBJTYPE_EXPROSION,
		OBJTYPE_NORMALITEM,
		OBJTYPE_ANIMATIONITEM,
		OBJTYPE_DEBUG3DLINE,
		OBJTYPE_DEBUGCOLLISION,
		OBJTYPE_SCORE,
		OBJTYPE_UI,
		OBJTYPE_NUMBER,
		OBJTYPE_SKILLSLOT,
		OBJTYPE_PAUSE,
		OBJTYPE_AI,
		TYPE_MAX
	}OBJ_TYPE;


	CScene() {};
	CScene(OBJ_TYPE type);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	virtual void DebugInfo(void) = 0;
	static void UpdateAll(void);
	static void RereaseAll(void);
	static void DrawAll(void);
	static int GetAll(void);
	static void DebugAll(void);
	static bool &GetStopFlag(void);
	static void ShowUpdateGraph();		//デバッグ用　更新や描画にかかる時間をグラフで表記
	static void MapChangeRelease();		//マップ遷移時に残っているモノを消去

	void SetObjType(OBJ_TYPE type);
	static CScene *GetScene(OBJ_TYPE type);
	static void GetSceneList(OBJ_TYPE objtype, std::vector<CScene*> &rSceneList);
	OBJ_TYPE GetObjType(void);
	void Rerease(void);
	int GetID() { return nID; };
	static void StopUpdate(void);
	static void SetStopFlag(bool bStop) { m_bStopFlag = bStop; };
	static void Set1FUpdate() { m_b1FUpdateFlag = true; };
protected:

private:
	OBJ_TYPE objtype;
	static std::vector<CScene*> m_pSceneList[TYPE_MAX];
	static int m_NumAll;
	static bool m_bStopFlag;			//画面停止のフラグ
	static bool m_b1FUpdateFlag;		//画面停止中に1Fだけ更新するフラグ
	bool m_bflag;
	int nID;

#ifdef _DEBUG
	static std::vector<int> m_fUpdateTimeList;		//更新の経過時間のリスト
	static std::vector<int> m_fDrawTimeList;		//描画の経過時間リスト
#endif //_DEBUG

};
#endif