//==========================================================
// シーン処理 [Scene.cpp]: NORI
//==========================================================
//==========================================================
// インクルードファイル
//==========================================================
#include "scene.h"
#include "renderer.h"
#include "pause.h"
#include "inputKeyboard.h"

//プロトタイプ宣言
//グローバル変数　何番目の表示↓　↓表示の最高数
CScene*CScene::m_pScene[TYPE_MAX][MAX] = {};
int CScene::m_NumAll = 0;
CScene*CScene::m_pTop = NULL;
CScene*CScene::m_pCur = NULL;
bool CScene::m_stopflag = false;
//==========================================================
//コンストラクタ
//==========================================================
CScene::CScene(OBJ_TYPE type)
{
	// オブジェクトタイプのチェック
	if (type != TYPE_NONE)
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
	else
	{
		return;
	}
}
//==========================================================
//デストラクタ
//==========================================================
CScene::~CScene()
{
}
//==========================================================
//すべての更新
//==========================================================
void CScene::UpdateAll(void)
{
	CScene *pScene = m_pTop;
	if (m_stopflag == false)
	{
		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;
			pScene->Update();
			pScene = pSceneNext;
		}
	}
	pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Delete();
		pScene = pSceneNext;
	}
}
//==========================================================
//すべての消去
//==========================================================
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
//==========================================================
//すべての描画
//==========================================================
void CScene::DrawAll(void)
{
	CScene *pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Draw();
		pScene = pSceneNext;
	}
}
//==========================================================
//すべての取得
//==========================================================
int  CScene::GetAll(void)
{
	return m_NumAll;
}
//==========================================================
//デバッグ情報の表示
//==========================================================
void CScene::DebugAll(void)
{
#ifdef _DEBUG
	CScene *pScene = m_pTop;
	if (m_stopflag == false)
	{
		while (pScene)
		{
			CScene *pSceneNext = pScene->m_pNext;
			pScene->DebugInfo();
			pScene = pSceneNext;
		}
	}
	pScene = m_pTop;
	while (pScene)
	{
		CScene *pSceneNext = pScene->m_pNext;
		pScene->Delete();
		pScene = pSceneNext;
	}
#endif
}
//==========================================================
//最初の取得
//==========================================================
CScene * CScene::GetTop(void)
{
	return m_pTop;
}
//==========================================================
//ストップの状態取得
//==========================================================
bool &CScene::GetStopFlag(void)
{
	return m_stopflag;
}
//==========================================================
//次の取得
//==========================================================
CScene * CScene::GetNext(void)
{
	return m_pNext;
}
//==========================================================
//オブジェクトの設定
//==========================================================
void CScene::SetObjType(OBJ_TYPE type)
{
	objtype = type;
}
//==========================================================
//シーンの取得
//==========================================================
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
//==========================================================
//オブジェクトタイプの取得
//==========================================================
CScene::OBJ_TYPE CScene::GetObjType(void)
{
	return objtype;
}
//==========================================================
//消去のフラグ
//==========================================================
void CScene::Rerease(void)
{
	m_flag = true;
}
//==========================================================
//消去
//==========================================================
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
//==========================================================
//ストップの変更
//==========================================================
void CScene::StopUpdate(void)
{
	m_stopflag ^= 1;
}
