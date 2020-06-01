//■■■■■■■■■■■■■■■■■■■■■■■■■■
//■　　　main.cpp からの分岐点になるﾎﾆｬｼﾞ			■
//■■■■■■■■■■■■■■■■■■■■■■■■■■
#define _CRT_SECURE_NO_WARNINGS // 警告除去
#include "main.h"
#include "scene.h"
#include "renderer.h"
//プロトタイプ宣言
//グローバル変数　何番目の表示↓　↓表示の最高数
CScene*CScene::m_pScene[TYPE_MAX][MAX] = {};
int CScene::m_NumAll = 0;
CScene*CScene::m_pTop = NULL;
CScene*CScene::m_pCur = NULL;
//===================================================
CScene::CScene(OBJ_TYPE type)
{
	m_flag = false;

	if (m_pCur != NULL)
	{
		m_pPrev = m_pCur;
		m_pCur->m_pNext = this;
	}
	m_pCur = this;
	if (m_pTop == NULL)
	{
		m_pTop = this;
	}
}
//===================================================
CScene::~CScene()
{
}
//===================================================
void CScene::UpdateAll(void)
{
	CScene *pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Update();
		pScene = pSceneNext;
	}
	pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Delete();
		pScene = pSceneNext;
	}
}
//===================================================
void CScene::RereaseAll(void)
{
	CScene *pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Rerease();
		pScene = pSceneNext;
	}
}
//===================================================
void CScene::DrowAll(void)
{
	CScene *pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Drow();
		pScene = pSceneNext;
	}
}
//===================================================
int  CScene::GetAll(void)
{
	return m_NumAll;
}

CScene * CScene::GetTop(void)
{
	return m_pTop;
}

CScene * CScene::GetNext(void)
{
	return m_pNext;
}

void CScene::SetObjType(OBJ_TYPE type)
{
	objtype = type;
}

CScene *CScene::GetScene(OBJ_TYPE type)
{
	CScene *pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		if (pScene->GetObjType() == type)
		{
			return pScene;
		}
		pScene = pSceneNext;
	}
	return NULL;
}

CScene::OBJ_TYPE CScene::GetObjType(void)
{
	return objtype;
}

void CScene::Rerease(void)
{
	m_flag = true;
}
void CScene::Delete(void)
{
	int type = objtype;
	if (m_flag == true)
	{
		if (this == m_pTop && this == m_pCur)
		{
			m_pTop = m_pCur= NULL;
		}
		else if (this == m_pTop)
		{
			m_pTop = this->m_pNext;
		}
		else if (this == m_pCur)
		{
			m_pCur= this->m_pPrev;
			m_pCur->m_pNext = NULL;
		}
		else
		{
			this->m_pNext->m_pPrev= this->m_pPrev;
			this->m_pPrev->m_pNext= this->m_pNext;
		}

		Uninit();
		delete this;
		m_NumAll--;
	}
}
