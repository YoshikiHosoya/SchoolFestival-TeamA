//------------------------------------------------------------------------------
//
//�V�[������  [scene.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "scene.h"
#include "scene2D.h"
#include "particle.h"
#include "shader.h"
//------------------------------------------------------------------------------
//�ÓI�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CScene>> CScene::m_UniqueSceneList[CScene::OBJTYPE_MAX] = {};
std::vector<std::shared_ptr<CScene>> CScene::m_SharedSceneList[CScene::OBJTYPE_MAX] = {};
bool CScene::m_bStop = false;
bool CScene::m_b1FAction = false;
int CScene::m_nNumAll = 0;

//debug
#ifdef _DEBUG
std::vector<int> CScene::m_fUpdateTimeList(CScene::OBJTYPE_MAX);
std::vector<int> CScene::m_fDrawTimeList(CScene::OBJTYPE_MAX);
#endif // _DEBUG

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CScene::CScene()
{
	//������
	m_bDeadFlag = false;
	m_objtype = OBJTYPE_NONE;
	m_nNumAll++;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CScene::~CScene()
{
	//�S�̐����Z
	m_nNumAll--;
}

//------------------------------------------------------------------------------
//�������J��
//------------------------------------------------------------------------------
void CScene::ReleaseAll()
{
	for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
	{
		//�v�f�����J��Ԃ�
		for (size_t nCntElement = 0; nCntElement < m_UniqueSceneList[nCntObjType].size(); nCntElement++)
		{
			//nullcheck
			if (m_UniqueSceneList[nCntObjType][nCntElement])
			{
				//�X�V����
				m_UniqueSceneList[nCntObjType][nCntElement]->Uninit();
			}
		}
		//�v�f�����J��Ԃ�
		for (size_t nCntElement = 0; nCntElement < m_SharedSceneList[nCntObjType].size(); nCntElement++)
		{
			//nullcheck
			if (m_SharedSceneList[nCntObjType][nCntElement])
			{
				//�X�V����
				m_SharedSceneList[nCntObjType][nCntElement]->Uninit();
			}
		}
		//�S�v�f�폜
		m_UniqueSceneList[nCntObjType].clear();
		m_SharedSceneList[nCntObjType].clear();
	}
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CScene::UpdateAll()
{
	//Stop��Ԃ���Ȃ��� ��1F�A�N�V������true�̎�
	if (!m_bStop || m_b1FAction)
	{
		for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
		{
#ifdef _DEBUG

			//�X�V����O�̎��Ԃ�ۑ�
			DWORD nBeforeUpdateTime = timeGetTime();
#endif // _DEBUG

			//�v�f�����J��Ԃ�
			for (size_t nCntElement = 0; nCntElement < m_UniqueSceneList[nCntObjType].size(); nCntElement++)
			{
				//nullcheck
				if (m_UniqueSceneList[nCntObjType][nCntElement])
				{
					//�X�V����
					m_UniqueSceneList[nCntObjType][nCntElement]->Update();
				}
			}
			//�v�f�����J��Ԃ�
			for (size_t nCntElement = 0; nCntElement < m_SharedSceneList[nCntObjType].size(); nCntElement++)
			{
				//nullcheck
				if (m_SharedSceneList[nCntObjType][nCntElement])
				{
					//�X�V����
					m_SharedSceneList[nCntObjType][nCntElement]->Update();
				}
			}

#ifdef _DEBUG
			//�z��̒l����������
			//���݂̎��� - �O��̍X�V���I���������
			m_fUpdateTimeList[nCntObjType] = timeGetTime() - nBeforeUpdateTime;
#endif // _DEBUG
		}

		for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
		{
			//�v�f�����J��Ԃ�
			for (size_t nCntElement = 0; nCntElement < m_UniqueSceneList[nCntObjType].size(); nCntElement++)
			{
				//nullcheck
				if (m_UniqueSceneList[nCntObjType][nCntElement])
				{
					//�t���O�o���Ă邩�m�F
					if (m_UniqueSceneList[nCntObjType][nCntElement]->m_bDeadFlag)
					{
						//�v�f�̍폜
						m_UniqueSceneList[nCntObjType][nCntElement]->Uninit();
						m_UniqueSceneList[nCntObjType].erase(m_UniqueSceneList[nCntObjType].begin() + nCntElement);
					}
				}
			}
			//�v�f�����J��Ԃ�
			for (size_t nCntElement = 0; nCntElement < m_SharedSceneList[nCntObjType].size(); nCntElement++)
			{
				//nullcheck
				if (m_SharedSceneList[nCntObjType][nCntElement])
				{
					//�t���O�o���Ă邩�m�F
					if (m_SharedSceneList[nCntObjType][nCntElement]->m_bDeadFlag)
					{
						//�v�f�̍폜
						m_SharedSceneList[nCntObjType][nCntElement]->Uninit();
						m_SharedSceneList[nCntObjType].erase(m_SharedSceneList[nCntObjType].begin() + nCntElement);
					}
				}
			}
		}

#ifdef _DEBUG
		//�X�V����O�̎��Ԃ�ۑ�
		DWORD nBeforeUpdateTime = timeGetTime();
#endif // _DEBUG

		//�p�[�e�B�N���X�V
		CParticle::UpdateAllParticle();

#ifdef _DEBUG

		//�z��̒l����������
		//���݂̎��� - �O��̍X�V���I���������
		//�p�[�e�B�N���̏��
		m_fUpdateTimeList[OBJTYPE_EFFECT_PARTICLE] = timeGetTime() - nBeforeUpdateTime;
#endif // _DEBUG

		CShader::UpdateStaticParam();

	}
	//�p�[�e�B�N���̒��_ID���Z�b�g
	CParticle::ResetVertexID();

	//1F�X�V�̎�
	m_b1FAction = false;
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CScene::DrawAll()
{
	for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
	{
#ifdef _DEBUG
		//�X�V����O�̎��Ԃ�ۑ�
		DWORD nBeforeUpdateTime = timeGetTime();
#endif // _DEBUG

		//�v�f�����J��Ԃ�
		for (size_t nCntElement = 0; nCntElement < m_UniqueSceneList[nCntObjType].size(); nCntElement++)
		{
			//nullcheck
			if (m_UniqueSceneList[nCntObjType][nCntElement])
			{
				//�`�揈��
				m_UniqueSceneList[nCntObjType][nCntElement]->Draw();
			}
		}
		//�v�f�����J��Ԃ�
		for (size_t nCntElement = 0; nCntElement < m_SharedSceneList[nCntObjType].size(); nCntElement++)
		{
			//nullcheck
			if (m_SharedSceneList[nCntObjType][nCntElement])
			{
				//�`�揈��
				m_SharedSceneList[nCntObjType][nCntElement]->Draw();
			}
		}
#ifdef _DEBUG
		//�z��̒l����������
		//���݂̎��� - �O��̍X�V���I���������
		//�p�[�e�B�N���̏��
		m_fDrawTimeList[nCntObjType] = timeGetTime() - nBeforeUpdateTime;
#endif // _DEBUG
	}
}
//------------------------------------------------------------------------------
//�f�o�b�O�p�̏��\��
//------------------------------------------------------------------------------
void CScene::ShowDebugInfoAll()
{
	for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
	{
		//�v�f�����J��Ԃ�
		for (size_t nCntElement = 0; nCntElement < m_UniqueSceneList[nCntObjType].size(); nCntElement++)
		{
			//nullcheck
			if (m_UniqueSceneList[nCntObjType][nCntElement])
			{
				//�f�o�b�O���\�L
				m_UniqueSceneList[nCntObjType][nCntElement]->ShowDebugInfo();
			}
		}
		//�v�f�����J��Ԃ�
		for (size_t nCntElement = 0; nCntElement < m_SharedSceneList[nCntObjType].size(); nCntElement++)
		{
			//nullcheck
			if (m_SharedSceneList[nCntObjType][nCntElement])
			{
				//�f�o�b�O�\�L
				m_SharedSceneList[nCntObjType][nCntElement]->ShowDebugInfo();
			}
		}
	}
}

//----------------------------------------------------------------------------
//����̃I�u�W�F�N�g�^�C�v�̂��̂����ׂď���
//----------------------------------------------------------------------------
void CScene::ReleaseSpecificObject(OBJTYPE objtype)
{
	//�v�f�����J��Ԃ�
	for (size_t nCntElement = 0; nCntElement < m_UniqueSceneList[objtype].size(); nCntElement++)
	{
		//nullcheck
		if (m_UniqueSceneList[objtype][nCntElement])
		{
			//�X�V����
			m_UniqueSceneList[objtype][nCntElement]->Uninit();
		}
	}
	//�v�f�����J��Ԃ�
	for (size_t nCntElement = 0; nCntElement < m_SharedSceneList[objtype].size(); nCntElement++)
	{
		//nullcheck
		if (m_SharedSceneList[objtype][nCntElement])
		{
			//�X�V����
			m_SharedSceneList[objtype][nCntElement]->Uninit();
		}
	}
	//�S�v�f�폜
	m_UniqueSceneList[objtype].clear();
	m_SharedSceneList[objtype].clear();
}

//----------------------------------------------------------------------------
//�V�[�����擾 �z�񂲂Ɠn��
//----------------------------------------------------------------------------
void CScene::GetSceneList(OBJTYPE objtype, std::vector<std::shared_ptr<CScene>> &SceneList)
{
	SceneList = m_SharedSceneList[objtype];
}
//----------------------------------------------------------------------------
//���ꂼ��̕`�搔�\��
//----------------------------------------------------------------------------
void CScene::ShowNumAll()
{
#ifdef _DEBUG
	if (ImGui::TreeNode("Scene_NumAll"))
	{
		for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
		{
			ImGui::Text("NumAll [%d] -> [%d]", nCntObjType, m_SharedSceneList[nCntObjType].size() + m_UniqueSceneList[nCntObjType].size());
		}
		ImGui::TreePop();
	}
#endif // _DEBUG
}

//----------------------------------------------------------------------------
//�X�V�ƕ`��̃O���t�\�L
//----------------------------------------------------------------------------
void CScene::ShowUpdateGraph()
{
#ifdef _DEBUG
	//�o�͗p�̔z��
	std::vector<float> OutputDataList(OBJTYPE_MAX);

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "FPS_IntervalCount >> %d\n", GetFPSInterval());
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "FPS >> %d\n", GetFPS());

	//�X�V�̃O���t
	if (ImGui::TreeNode("Update_Graph"))
	{
		//�o�͗p�̃f�[�^�Ɍv�Z
		for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
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
		for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
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
#endif // _DEBUG
}


//----------------------------------------------------------------------------
//1F�����X�V
//----------------------------------------------------------------------------
void CScene::Set1FAction()
{
	m_b1FAction = true;
}
