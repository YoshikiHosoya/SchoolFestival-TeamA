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

//debug
#ifdef _DEBUG
std::vector<int> CScene::m_fUpdateTimeList(CScene::TYPE_MAX);
std::vector<int> CScene::m_fDrawTimeList(CScene::TYPE_MAX);
#endif // _DEBUG
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
#ifdef _DEBUG
			//�X�V����O�̎��Ԃ�ۑ�
			DWORD dwBeforeUpdateTime = timeGetTime();
#endif // _DEBUG
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
#ifdef _DEBUG
			//�z��̒l����������
			//���݂̎��� - �O��̍X�V���I���������
			m_fUpdateTimeList[nCntObjtype] = timeGetTime() - dwBeforeUpdateTime;
#endif // _DEBUG
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
#ifdef _DEBUG
		//�X�V����O�̎��Ԃ�ۑ�
		DWORD dwBeforeUpdateTime = timeGetTime();
#endif // _DEBUG

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
#ifdef _DEBUG
		//���݂̎��� - �O��̍X�V���I���������
		m_fDrawTimeList[nCntObjtype] = timeGetTime() - dwBeforeUpdateTime;
#endif // _DEBUG
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
//�f�o�b�O�X�V��`��ɂ����鎞�Ԃ�\�L
//==========================================================
void CScene::ShowUpdateGraph()
{
#ifdef _DEBUG

	//�O���t�p�̃E�B���h�E
	ImGui::Begin("Gragh");

	//�o�͗p�̔z��
	std::vector<float> OutputDataList(TYPE_MAX);

	//CDebugProc::Print("FPS_IntervalCount >> %d\n", GetFPSInterval());
	CDebugProc::Print("FPS >> %d\n", GetFps());

	//�X�V�̃O���t
	if (ImGui::TreeNode("Update_Graph"))
	{
		//�o�͗p�̃f�[�^�Ɍv�Z
		for (int nCntObjType = 0; nCntObjType < TYPE_MAX; nCntObjType++)
		{
			//�X�V�ɂ����������� / �S���̍X�V�ƕ`��ɂ�����������
			OutputDataList[nCntObjType] = (float)m_fUpdateTimeList[nCntObjType];
		}

		//�q�X�g�O���t����
		ImGui::PlotHistogram("Update (mSec)", OutputDataList.data(), OutputDataList.size(), 0, NULL, 0.0f, 16.0f, ImVec2(0, 100));

		//�c���[�I��
		ImGui::TreePop();

	}

	//�X�V�̃O���t
	if (ImGui::TreeNode("Draw_Graph"))
	{
		//�o�͗p�̃f�[�^�Ɍv�Z
		for (int nCntObjType = 0; nCntObjType < TYPE_MAX; nCntObjType++)
		{
			//�`��ɂ����������� / �S���̍X�V�ƕ`��ɂ�����������
			OutputDataList[nCntObjType] = (float)m_fDrawTimeList[nCntObjType];
		}

		//�q�X�g�O���t����
		ImGui::PlotHistogram("Renderer (mSec)", OutputDataList.data(), OutputDataList.size(), 0, NULL, 0.0f, 16.0f, ImVec2(0, 100));

		//�c���[�I��
		ImGui::TreePop();
	}
	//�z��̊J��
	OutputDataList.clear();

	//
	ImGui::End();

#endif // _DEBUG
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
//�V�[���̔z��擾
//==========================================================
void CScene::GetSceneList(OBJ_TYPE objtype, std::vector<CScene*>& rSceneList)
{
	rSceneList = m_pSceneList[objtype];
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