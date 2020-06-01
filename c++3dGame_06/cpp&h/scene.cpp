// ----------------------------------------
//
// �V�[�������̐���[scene.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene.h"
#include "pause.h"
//#include "enemy.h"
// ----------------------------------------
//
// �O���[�o���ϐ�
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
CScene * CScene::m_pTop[LAYER_MAX] = {};					// �擪�I�u�W�F�N�g�ւ̃|�C���^
CScene * CScene::m_pCur[LAYER_MAX] = {};					// ���݃I�u�W�F�N�g�ւ̃|�C���^
int CScene::m_nMaxLayer[LAYER_MAX] = {};					// ���C���[�̍ő吔

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CScene::CScene()
{
}

// ----------------------------------------
// �I�[�o�[���[�h�R���X�g���N�^
// ----------------------------------------
CScene::CScene(ACTOR actor, LAYER layer)
{
	/* ���݂̓z */
	if (m_pCur[layer] != NULL)
	{
		// �O�̃I�u�W�F�N�g�̃|�C���^
		this->m_pPrey = m_pCur[layer];
		// ���̃I�u�W�F�N�g�̃|�C���^
		m_pCur[layer]->m_pNext = this;
	}

	// ���݂̃|�C���^
	m_pCur[layer] = this;

	// �擪�I�u�W�F�N�g�̃|�C���^
	if (m_pTop[layer] == NULL)
	{
		m_pTop[layer] = this;
	}
	/* �ߋ��̓z */
	// �`�揇�ݒ�
	m_layer = layer;
	// �I�u�W�F�N�g���ݒ�
	m_nActor = actor;
	// �t���O
	m_bDeadFrag = false;
	// ���C���[�A�b�v
	m_nMaxLayer[layer]++;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CScene::~CScene()
{
}

// ----------------------------------------
// �V�[���e�q�����[�X����
// ----------------------------------------
void CScene::ReleaseAll(void)
{
	/* ���݂̓z */
	// �ϐ��錾
	CScene * pScene = NULL;
	CScene *pSceneNext;	// ���̃V�[��
	for (int nCnt = 0; nCnt < LAYER_MAX; nCnt++)
	{
		// �擪�|�C���g���i�[
		pScene = m_pTop[nCnt];
		while (pScene != NULL)
		{
			pSceneNext = pScene->m_pNext;
			pScene->Release();
			pScene->Uninit();
			delete pScene;
			pScene = NULL;
			pScene = pSceneNext;
		}
		// �擪�|�C���g���i�[
		m_pTop[nCnt] = NULL;
		// ���݂̃I�u�W�F�N�g��NULL
		m_pCur[nCnt] = NULL;
	}
}

// ----------------------------------------
// �V�[���e�q�X�V����
// ----------------------------------------
void CScene::UpdateAll(void)
{
	// �ϐ��錾
	CScene * pScene = NULL;
	CScene *pSceneNext;	// ���̃V�[��
	for (int nCnt = 0; nCnt < LAYER_MAX; nCnt++)
	{
		// �擪�|�C���g���i�[
		pScene = m_pTop[nCnt];
		while (pScene != NULL)
		{
			// ���̃|�C���^����
			pSceneNext = pScene->m_pNext;
			// �|�[�YUI�ȊO
			if (pScene->m_nActor != ACTOR_MANUAL_UI)
			{
				// �|�[�Y��Ԃ̎�
				if (CPause::GetPause() == false)
				{
					pScene->Update();
				}
			}
			// �|�[�YUI
			else
			{
				// �|�[�Y��Ԃ̎�
				if (CPause::GetPause() == true)
				{
					pScene->Update();
				}
			}

			/*if (CPause::GetPause() == false)
			{
				ShowCursor(false);
			}
			else if (CPause::GetPause() == true)
			{
				ShowCursor(true);
			}*/



			pScene = pSceneNext;
		}
	}
	// �t���O�����������̂����ׂă����[�X
	DeadFragAll();
}

// ----------------------------------------
// �V�[���e�q�`�揈��
// ----------------------------------------
void CScene::DrawAll(void)
{
	/* ���݂̓z */
	// �ϐ��錾
	CScene * pScene = NULL;
	CScene *pSceneNext;	// ���̃V�[��
	for (int nCnt = 0; nCnt < LAYER_MAX; nCnt++)
	{
		// �擪�|�C���g���i�[
		pScene = m_pTop[nCnt];
		while (pScene != NULL)
		{
			// ���̃|�C���^���i�[
			pSceneNext = pScene->m_pNext;

			// �}�j���A��UI�ȊO
			if (pScene->m_nActor != ACTOR_MANUAL_UI && pScene->m_nActor != ACTOR_PLAYER)
			{
				pScene->Draw();
			}
			/*if (CEnemy::GetEndFlag() == false)
			{
			}*/
			// �|�[�YUI
			else
			{
				// �|�[�Y��Ԃ̎�
				if (CPause::GetPause() == true)
				{
					pScene->Draw();
				}
			}
			pScene = pSceneNext;
		}
	}
}

// ----------------------------------------
// �V�[���̎擾
// ----------------------------------------
CScene *CScene::GetActor(ACTOR actor, LAYER layer, int nCntScene)
{
	// �ϐ��錾
	CScene * pScene = NULL;
	CScene *pSceneNext;	// ���̃V�[��
	int nCnt = 0;
	// �擪�|�C���g���i�[
	pScene = m_pTop[layer];
	// �J�E���g
	for (int nCnt = 0; nCnt < nCntScene; nCnt++)
	{
		// ���̃|�C���^���i�[
		if (pScene != NULL)
		{
			pSceneNext = pScene->m_pNext;
			pScene = pSceneNext;
		}
	}
	// �V�[������Ԃ�
	if (pScene != NULL)
	{
		if (pScene->m_nActor == actor) return pScene;
		else return NULL;
	}
	else return NULL;
}

// ----------------------------------------
// ���C���[�̍ő吔�̎擾
// ----------------------------------------
int CScene::GetMaxLayer(LAYER layer)
{
	return m_nMaxLayer[layer];
}

// ----------------------------------------
// �I�u�W�F�N�g�̔j��
// ----------------------------------------
void CScene::Release(void)
{
	// ���S�t���O��������
	m_bDeadFrag = true;
}

// ----------------------------------------
// ���S�t���O�����������̂������[�X����
// ----------------------------------------
void CScene::DeadFragAll(void)
{
	// �ϐ��錾
	CScene * pScene;	// �V�[��
	CScene *pSceneNext;	// ���̃V�[��

	for (int nCnt = 0; nCnt < LAYER_MAX; nCnt++)
	{
		// �擪�|�C���g���i�[
		pScene = m_pTop[nCnt];
		while (pScene != NULL)
		{
			// ���̃|�C���^����
			pSceneNext = pScene->m_pNext;
			// ���S�t���O�������Ă���Ƃ�
			if (pScene->m_bDeadFrag == true)
			{
				// �擪�ƌ��݂̃I�u�W�F�N�g�̃|�C���^�������ꍇ
				if (pScene == m_pTop[nCnt] && pScene == m_pCur[nCnt])
				{
					m_pTop[nCnt] = NULL;
					m_pCur[nCnt] = NULL;
				}
				// �擪�I�u�W�F�N�g�̃|�C���^�̕ύX
				else if (pScene == m_pTop[nCnt])
				{
					m_pTop[nCnt] = pSceneNext;
					m_pTop[nCnt]->m_pPrey = NULL;
				}
				// ���݂̃I�u�W�F�N�g�̃|�C���^�̕ύX
				else if (pScene == m_pCur[nCnt])
				{
					m_pCur[nCnt] = pScene->m_pPrey;
					m_pCur[nCnt]->m_pNext = NULL;
				}
				// �Ԃ̃R�l�N�g
				else
				{
					// �O��̎��̏�����
					pScene->m_pPrey->m_pNext = pSceneNext;
					// ���̑O��̏�����
					pSceneNext->m_pPrey = pScene->m_pPrey;
				}
				// ���C���[�_�E��
				m_nMaxLayer[nCnt]--;

				pScene->Uninit();
				delete pScene;
				pScene = NULL;
			}
			pScene = pSceneNext;
		}
	}
}
