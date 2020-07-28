#pragma once
//=============================================================================
// �V�[���w�b�_�[ [Scene.h]: NORI
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

#define MAX (1000)
class CPause;
//�����_�����O�N���X
class CScene
{
public:
	typedef enum
	{
		TYPE_NONE = 0,
		OBJTYPE_FIELD,
		OBJTYPE_PLAYER,
		OBJTYPE_BULLET,
		OBJTYPE_MODEL,
		OBJTYPE_OBSTACLE,
		OBJTYPE_CREATE,
		OBJTYPE_ENEMY,
		OBJTYPE_BOSS,
		OBJTYPE_PRISONER,
		OBJTYPE_PLAYER_VEHICLE,
		OBJTYPE_ENEMY_VEHICLE,
		OBJTYPE_EFFECT,
		OBJTYPE_PARTICLE,
		OBJTYPE_ORBIT,
		OBJTYPE_EXPROSION,
		OBJTYPE_ITEM,
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
	static void ShowUpdateGraph();		//�f�o�b�O�p�@�X�V��`��ɂ����鎞�Ԃ��O���t�ŕ\�L

	void SetObjType(OBJ_TYPE type);
	static CScene *GetScene(OBJ_TYPE type);
	static void GetSceneList(OBJ_TYPE objtype, std::vector<CScene*> &rSceneList);
	OBJ_TYPE GetObjType(void);
	void Rerease(void);
	static void StopUpdate(void);
	static void SetStopFlag(bool bStop) { m_bStopFlag = bStop; };
	static void Set1FUpdate() { m_b1FUpdateFlag = true; };
protected:

private:
	OBJ_TYPE objtype;
	static std::vector<CScene*> m_pSceneList[TYPE_MAX];
	static int m_NumAll;
	static bool m_bStopFlag;			//��ʒ�~�̃t���O
	static bool m_b1FUpdateFlag;		//��ʒ�~����1F�����X�V����t���O
	bool m_bflag;

#ifdef _DEBUG
	static std::vector<int> m_fUpdateTimeList;		//�X�V�̌o�ߎ��Ԃ̃��X�g
	static std::vector<int> m_fDrawTimeList;		//�`��̌o�ߎ��ԃ��X�g
#endif //_DEBUG

};
#endif