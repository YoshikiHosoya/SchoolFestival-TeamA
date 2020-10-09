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
//------------------------------------------------------------------------------
//�ÓI�ϐ��̏�����
//------------------------------------------------------------------------------
std::vector<std::unique_ptr<CScene>> CScene::m_UniqueSceneList[CScene::OBJTYPE_MAX] = {};
std::vector<std::shared_ptr<CScene>> CScene::m_SharedSceneList[CScene::OBJTYPE_MAX] = {};
std::vector<int> CScene::m_fUpdateTimeList(CScene::OBJTYPE_MAX);
std::vector<int> CScene::m_fDrawTimeList(CScene::OBJTYPE_MAX);

bool CScene::m_bStop = false;
bool CScene::m_b1FAction = false;

int CScene::m_nNumAll = 0;
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
	//���݂̎��Ԃ�ۑ�
	DWORD nBeforeUpdateTime = timeGetTime();

	//Stop��Ԃ���Ȃ��� ��1F�A�N�V������true�̎�
	if (!m_bStop || m_b1FAction)
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
			//�z��̒l����������
			//���݂̎��� - �O��̍X�V���I���������
			m_fUpdateTimeList[nCntObjType] = timeGetTime() - nBeforeUpdateTime;

			//�X�V�̎��Ԃ�ۑ�
			nBeforeUpdateTime = timeGetTime();

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
	//���݂̎��Ԃ�ۑ�
	int nBeforeUpdateTime = timeGetTime();

	for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
	{
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

		//�z��̒l����������
		//���݂̎��� - �O��̍X�V���I���������
		m_fDrawTimeList[nCntObjType] = timeGetTime() - nBeforeUpdateTime;

		//�X�V�̎��Ԃ�ۑ�
		nBeforeUpdateTime = timeGetTime();
	}
}
//------------------------------------------------------------------------------
//�f�o�b�O�p�̏��\��
//------------------------------------------------------------------------------
void CScene::ShowDebugInfoAll()
{
#ifdef _DEBUG

	//�O���t�p�̔z��
	std::vector<float> OutputDataList(OBJTYPE_MAX);

	//�X�V�ƕ`��ɂ��������t���[��
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "FPS_IntervalCount >> %d\n", GetFPSInterval());

	for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
	{
		//���X�g�ɒǉ�
		OutputDataList[nCntObjType] = (m_fUpdateTimeList[nCntObjType]) / (float)GetFPSInterval();
	}

	//�X�V�̃O���t����
	ImGui::PlotHistogram("Update!", OutputDataList.data(), OutputDataList.size(), 0, NULL, 0.0f, 1.0f, ImVec2(0, 100));

	for (int nCntObjType = 0; nCntObjType < OBJTYPE_MAX; nCntObjType++)
	{
		//���X�g�ɒǉ�
		OutputDataList[nCntObjType] = (m_fDrawTimeList[nCntObjType]) / (float)GetFPSInterval();
	}

	//�`��Ɋւ���O���t
	ImGui::PlotHistogram("Renderer", OutputDataList.data(), OutputDataList.size(), 0, NULL, 0.0f, 1.0f, ImVec2(0, 100));

	//�z��N���A
	OutputDataList.clear();

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

#endif	//_DEBUG
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
