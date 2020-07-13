//------------------------------------------------------------------------------
//
//�f�o�b�O�@�G�t�F�N�g�r���[���p�̏���  [Debug_EffectViewer.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Debug_ModelViewer.h"
#include "Debug_ViewerCharacter.h"
#include "../Scene.h"
#include "../manager.h"
#include "../renderer.h"
#include "../inputKeyboard.h"
#include "../camera.h"
#include "../fade.h"
#include "../meshfield.h"
#include "../model.h"


//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_CAMERA_DISTANCE (200.0f)
#define DEFAULT_CAMERA_ROT (D3DXVECTOR3(0.2f,0.0f,0.0f))
#define DEFAULT_CAMERA_POSR (D3DXVECTOR3(30.0f, 50.0f, 0.0f))

#define OFFSET_TEXT_PASS ("data/Load/SaveOffset.txt")

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CDebug_ModelViewer::CDebug_ModelViewer()
{

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CDebug_ModelViewer::~CDebug_ModelViewer()
{

}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CDebug_ModelViewer::Init()
{
	//�r���[���p�̃L�����N�^�[�쐬
	m_pViewerCharacter = CDebug_ViewerCharacter::Create();

	CManager::GetRenderer()->GetCamera()->SetCameraPosfromDistance(DEFAULT_CAMERA_POSR, DEFAULT_CAMERA_ROT, DEFAULT_CAMERA_DISTANCE);

	CMeshField::Create(ZeroVector3, D3DXVECTOR3(50.0f, 50.0f, 50.0f), INTEGER2(20, 20));

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CDebug_ModelViewer::Uninit()
{
	//�I������
	CScene::RereaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CDebug_ModelViewer::Update()
{

}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CDebug_ModelViewer::Draw()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CDebug_ModelViewer::ShowDebugInfo()
{
#ifdef _DEBUG

	//�L�����N�^�[�����
	ImGui::Begin("MotionViewer");

		//Tab
		if (ImGui::BeginTabBar("Viewer", m_bModel))
		{
			//Tab
			if (ImGui::BeginTabItem("MotionViewer"))
			{
				//���[�V�����r���[��
				m_pViewerCharacter->MotionViewer();
				ImGui::EndTabItem();
			}
			//Tab
			if (ImGui::BeginTabItem("OffsetViewer"))
			{
				//�I�t�Z�b�g�r���[��
				OffsetViewer(m_pViewerCharacter->GetCharacterModelList());
				ImGui::EndTabItem();
			}
			//TabEnd
			ImGui::EndTabBar();
		}

	ImGui::End();
#endif
}

//------------------------------------------------------------------------------
//�I�t�Z�b�g�r���[��
//------------------------------------------------------------------------------
void CDebug_ModelViewer::OffsetViewer(std::vector<CModel*> vModelList)
{
	//���f�������J��ւ���
	for (size_t nCnt = 0; nCnt < vModelList.size(); nCnt++)
	{
		//���f�����擾
		std::string aPartsName = CModel::GetModelFileName(vModelList[nCnt]->GetType(), vModelList[nCnt]->GetModelCount());

		//���̕����̕����������("data/MODEL/)
		aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

		//���̍��ڂ̘g�̑傫���ݒ�
		ImGui::SetNextItemWidth(200);

		//���ꂼ��̃I�t�Z�b�g�𒲐�
		if (ImGui::DragFloat3(aPartsName.data(), vModelList[nCnt]->GetPosition(), 0.05f, -100.0f, 100.0f))
		{

		}

		//�����s��
		ImGui::SameLine();

		//�e�ԍ� >>
		ImGui::Text("ParentIdx >>");

		//���̍��ڂ̘g�̑傫���ݒ�
		ImGui::SetNextItemWidth(20);

		//���f���ԍ�
		char aId[64];
		sprintf(aId, "[%d]", vModelList[nCnt]->GetModelCount());

		//�����s
		ImGui::SameLine();

		//�e�ԍ�
		if (ImGui::InputInt(aId, &vModelList[nCnt]->GetParentIdx(), -1, vModelList.size()))
		{
			vModelList[nCnt]->SetParent(vModelList[vModelList[nCnt]->GetParentIdx()]);
		}
	}

	//�I�t�Z�b�g�̃Z�[�u
	if (ImGui::Button("OffsetSave"))
	{
		SaveModelOffset(vModelList);
	}

	//�I�t�Z�b�g�S�ă��Z�b�g
	if (ImGui::Button("AllReset"))
	{
		//���f�������J��ւ���
		for (size_t nCnt = 0; nCnt < vModelList.size(); nCnt++)
		{
			//�O�ɂ���
			vModelList[nCnt]->SetPosition(ZeroVector3);
		}
	}
}

//------------------------------------------------------------------------------
//�I�t�Z�b�g�ۑ�
//------------------------------------------------------------------------------
HRESULT CDebug_ModelViewer::SaveModelOffset(std::vector<CModel*> vModelList)
{
	FILE *pFile;

	int nRotNum = 0;
	char cHeadtext[128];
	char cWriteText[128];

	//�t�@�C���ǂݍ���
	pFile = fopen(OFFSET_TEXT_PASS, "w");

	//nullcheck
	if (pFile != nullptr)
	{

		//�u���b�N�R�����g
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		strcpy(cHeadtext, "//Offset\n");
		strcpy(cHeadtext, "//�e�L�X�g�ɃR�s�y���Ă�������\n");

		fputs(cHeadtext, pFile);

		strcpy(cHeadtext, "//Author:Yoshiki Hosoya\n");
		fputs(cHeadtext, pFile);

		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//�u���b�N�R�����g�I��//
		//nullcheck
		if (!vModelList.empty())
		{
			for (size_t nCnt = 0; nCnt < vModelList.size(); nCnt++)
			{

				//�X�^�[�g
				sprintf(cWriteText, "%s %s%d%s", "SET_START", "---------[", nCnt, "]----------");
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//���f���̎��
				sprintf(cWriteText, "	%s %s %d", "MODEL_TYPE", &EQUAL, vModelList[nCnt]->GetType());
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//�C���f�b�N�X
				sprintf(cWriteText, "	%s %s %d", "INDEX", &EQUAL, vModelList[nCnt]->GetModelCount());
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//�e�ԍ�
				sprintf(cWriteText, "	%s %s %d", "PARENT", &EQUAL, vModelList[nCnt]->GetParentIdx());
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//���W
				sprintf(cWriteText, "	%s %s %.1f %.1f %.1f", "POS", &EQUAL,
					vModelList[nCnt]->GetPosition().x,
					vModelList[nCnt]->GetPosition().y,
					vModelList[nCnt]->GetPosition().z);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//�p�[�c�Z�b�g�I��
				fputs("SET_END", pFile);
				fputs(NEWLINE, pFile);
				fputs(NEWLINE, pFile);

			}
		}

		//�I�t�Z�b�g�ݒ�I��
		fputs("MODEL_OFFSET_END", pFile);

		//�ۑ�����
		std::cout << "Offset Save Succsess!! >> " << OFFSET_TEXT_PASS << NEWLINE;

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//�t�@�C�����J���܂���ł���
		std::cout << "Motion Save FAILED!!  Can't Open File >> " << OFFSET_TEXT_PASS << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
