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
int CScene::m_NumAll = 0;
bool CScene::m_bStopFlag = false;
bool CScene::m_b1FUpdateFlag = false;
std::vector<CScene*> CScene::m_pSceneList[TYPE_MAX] = {};
//==========================================================
//�R���X�g���N�^
//==========================================================
CScene::CScene(OBJ_TYPE type)
{
	// �I�u�W�F�N�g�^�C�v�̃`�F�b�N
	if (type != TYPE_NONE)
	{
		m_bflag = false;

		m_pSceneList[type].emplace_back(this);
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
	//�X�g�b�v�̃t���O�m�F
	if (!m_bStopFlag || m_b1FUpdateFlag)
	{
		//OBJTYPE����
		for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
		{
			//�z�񂪋󂩂ǂ���
			if (!m_pSceneList[nCntObjtype].empty())
			{
				//Scene�̔z��̑傫����
				for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
				{
					//nullcheck
					if (m_pSceneList[nCntObjtype][nCnt])
					{
						//�X�V����
						m_pSceneList[nCntObjtype][nCnt]->Update();
					}
				}
			}
		}
	}

	//OBJTYPE����
	for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
	{
		//�z�񂪋󂩂ǂ���
		if (!m_pSceneList[nCntObjtype].empty())
		{
			//Scene�̔z��̑傫����
			for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
			{
				//�t���O�`�F�b�N
				if (m_pSceneList[nCntObjtype][nCnt]->m_bflag)
				{
					//�I������
					m_pSceneList[nCntObjtype][nCnt]->Uninit();
					//�������J��
					delete m_pSceneList[nCntObjtype][nCnt];
					m_pSceneList[nCntObjtype][nCnt] = nullptr;

					//�z�񂩂�폜
					m_pSceneList[nCntObjtype].erase(m_pSceneList[nCntObjtype].begin() + nCnt);

					//�z��ł��ꂽ���C��
					nCnt--;

				}
			}
		}
	}

	m_b1FUpdateFlag = false;
}
//==========================================================
//���ׂĂ̏���
//==========================================================
void CScene::RereaseAll(void)
{
	//OBJTYPE����
	for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
	{
		//�z�񂪋󂩂ǂ���
		if (!m_pSceneList[nCntObjtype].empty())
		{
			//Scene�̔z��̑傫����
			for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
			{
				//nullcheck
				if (m_pSceneList[nCntObjtype][nCnt])
				{
					//�I������
					m_pSceneList[nCntObjtype][nCnt]->Uninit();

					//�������J��
					delete m_pSceneList[nCntObjtype][nCnt];
					m_pSceneList[nCntObjtype][nCnt] = nullptr;
				}
			}
			//�z�����ɂ���
			m_pSceneList[nCntObjtype].clear();
		}
	}
	//�z�����ɂ���
	m_pSceneList->clear();
}
//==========================================================
//���ׂĂ̕`��
//==========================================================
void CScene::DrawAll(void)
{
	//OBJTYPE����
	for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
	{
		//�z�񂪋󂩂ǂ���
		if (!m_pSceneList[nCntObjtype].empty())
		{
			//Scene�̔z��̑傫����
			for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
			{
				//nullcheck
				if (m_pSceneList[nCntObjtype][nCnt])
				{
					//�`��
					m_pSceneList[nCntObjtype][nCnt]->Draw();
				}
			}
		}
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
	//OBJTYPE����
	for (int nCntObjtype = 0; nCntObjtype < TYPE_MAX; nCntObjtype++)
	{
		//�z�񂪋󂩂ǂ���
		if (!m_pSceneList[nCntObjtype].empty())
		{
			//Scene�̔z��̑傫����
			for (size_t nCnt = 0; nCnt < m_pSceneList[nCntObjtype].size(); nCnt++)
			{
				//nullcheck
				if (m_pSceneList[nCntObjtype][nCnt])
				{
					//�X�V����
					m_pSceneList[nCntObjtype][nCnt]->DebugInfo();
				}
			}
		}
	}
#endif
}

//==========================================================
//�X�g�b�v�̏�Ԏ擾
//==========================================================
bool &CScene::GetStopFlag(void)
{
	return m_bStopFlag;
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
	m_bflag = true;
}

//==========================================================
//�X�g�b�v�̕ύX
//==========================================================
void CScene::StopUpdate(void)
{
	m_bStopFlag ^= 1;
}
