#pragma once
//=============================================================================
// シーンヘッダー [Scene.h]: NORI
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

#define MAX (1000)
//レンダリングクラス
class CScene
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		OBJTYPE_FIELD,
		OBJTYPE_PLAYER,
		OBJTYPE_BULLET,
		OBJTYPE_PARTICLE,
		OBJTYPE_MODEL,
		OBJTYPE_CREATE,
		OBJTYPE_ENEMY,
		OBJTYPE_SCORE,
		OBJTYPE_ORBIT,
		OBJTYPE_EXPROSION,
		OBJTYPE_UI,
		OBJTYPE_NUMBER,
		OBJTYPE_SKILLSLOT,
		TYPE_MAX
	}OBJ_TYPE;
	CScene() {};
	CScene(OBJ_TYPE type);
	virtual ~CScene();
	virtual HRESULT Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;
	virtual void Draw(void) = 0;
	static void UpdateAll(void);
	static void RereaseAll(void);
	static void DrawAll(void);
	static int GetAll(void);
	static CScene *GetTop(void);
	CScene *GetNext(void);
	void SetObjType(OBJ_TYPE type);
	static CScene *GetScene(OBJ_TYPE type);
	OBJ_TYPE GetObjType(void);
	void Rerease(void);
	void Delete(void);
protected:

private:
	OBJ_TYPE objtype;
	static CScene *m_pScene[TYPE_MAX][MAX];
	static int m_NumAll;
	int m_bId;
	int n_Id;
	bool m_flag;
	static CScene *m_pTop;	//先頭オブジェクトへのポインタ
	static CScene *m_pCur;	//現在オブジェクトへのポインタ
	CScene *m_pPrev;		//前のオブジェクトへのポインタ
	CScene *m_pNext;		//次のオブジェクトへのポインタ
};
#endif