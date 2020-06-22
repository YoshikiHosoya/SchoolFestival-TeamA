//==========================================================
// �V�[������ [Scene.cpp]: NORI
//==========================================================
//==========================================================
// �C���N���[�h�t�@�C��
//==========================================================
#include "scene.h"
#include "renderer.h"
#include "pause.h"
#include "inputKeyboard.h"

//�v���g�^�C�v�錾
//�O���[�o���ϐ��@���Ԗڂ̕\�����@���\���̍ō���
CScene*CScene::m_pScene[TYPE_MAX][MAX] = {};
int CScene::m_NumAll = 0;
CScene*CScene::m_pTop = NULL;
CScene*CScene::m_pCur = NULL;
bool CScene::m_stopflag = false;
//==========================================================
//�R���X�g���N�^
//==========================================================
CScene::CScene(OBJ_TYPE type)
{
	// �I�u�W�F�N�g�^�C�v�̃`�F�b�N
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
//�f�X�g���N�^
//==========================================================
CScene::~CScene()
{
}
//==========================================================
//���ׂĂ̍X�V
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
//���ׂĂ̏���
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
//���ׂĂ̕`��
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
//���ׂĂ̎擾
//==========================================================
int  CScene::GetAll(void)
{
	return m_NumAll;
}
//==========================================================
//�f�o�b�O���̕\��
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
//�ŏ��̎擾
//==========================================================
CScene * CScene::GetTop(void)
{
	return m_pTop;
}
//==========================================================
//�X�g�b�v�̏�Ԏ擾
//==========================================================
bool &CScene::GetStopFlag(void)
{
	return m_stopflag;
}
//==========================================================
//���̎擾
//==========================================================
CScene * CScene::GetNext(void)
{
	return m_pNext;
}
//==========================================================
//�I�u�W�F�N�g�̐ݒ�
//==========================================================
void CScene::SetObjType(OBJ_TYPE type)
{
	objtype = type;
}
//==========================================================
//�V�[���̎擾
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
//�I�u�W�F�N�g�^�C�v�̎擾
//==========================================================
CScene::OBJ_TYPE CScene::GetObjType(void)
{
	return objtype;
}
//==========================================================
//�����̃t���O
//==========================================================
void CScene::Rerease(void)
{
	m_flag = true;
}
//==========================================================
//����
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
//�X�g�b�v�̕ύX
//==========================================================
void CScene::StopUpdate(void)
{
	m_stopflag ^= 1;
}
