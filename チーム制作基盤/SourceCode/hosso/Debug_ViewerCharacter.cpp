//------------------------------------------------------------------------------
//
//debug �r���[���p�̃L�����N�^�[����  [Debug_ViewerCharacter.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Debug_ViewerCharacter.h"
#include "../../manager.h"
#include "../../renderer.h"
#include "../../game.h"
#include "../../camera.h"
#include "../../inputKeyboard.h"
#include "../../model.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CDebug_ViewerCharacter::CDebug_ViewerCharacter()
{
}

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CDebug_ViewerCharacter::CDebug_ViewerCharacter(OBJ_TYPE type) : CCharacter(type)
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CDebug_ViewerCharacter::~CDebug_ViewerCharacter()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CDebug_ViewerCharacter::Init()
{
	CCharacter::Init();

	CCharacter::LoadOffset(CCharacter::CHARACTER_TYPE_PLAYER);

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::Update()
{
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::Draw()
{
	CCharacter::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::ShowDebugInfo()
{
#ifdef _DEBUG
	static bool bMotion = true;
#endif //DEBUG
}

//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
CDebug_ViewerCharacter* CDebug_ViewerCharacter::Create()
{
	//�ϐ��錾
	CDebug_ViewerCharacter *pCharacter = new CDebug_ViewerCharacter(OBJTYPE_PLAYER);

	if (pCharacter)
	{
		//������7
		pCharacter->Init();

		////�I�u�W�F�N�g�^�C�v�ݒ�
		pCharacter->SetObjType(OBJTYPE_PLAYER);
	}

	//�����������
	return pCharacter;
}

//------------------------------------------------------------------------------
//�R���{�{�b�N�X
//------------------------------------------------------------------------------
bool CDebug_ViewerCharacter::ShowMotionComboBox(CCharacter::MOTION &motiontype)
{
	bool bChange = false;

#ifdef _DEBUG

	//std::vector<std::string > &aFileName = CMotion::GetFileName();

	////combo�J�n
	//if (ImGui::BeginCombo("MotionName", aFileName[motiontype].data()))
	//{
	//	//�v�f���J��Ԃ�
	//	for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
	//	{

	//		//�I��ԍ��������Ă邩�ǂ���
	//		bool is_selected = (aFileName[motiontype] == aFileName[nCnt]);

	//		//�I�����ꂽ���̏���
	//		if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
	//		{
	//			//���݂̑I�����ڐݒ�
	//			motiontype = (CMotion::MOTION_TYPE)nCnt;
	//			bChange = true;
	//		}

	//		////
	//		//if (is_selected)
	//		//{
	//		//	//�X�N���[���̏����ʒu�ݒ�
	//		//	ImGui::SetItemDefaultFocus();
	//		//}
	//	}
	//	//combo�I��
	//	ImGui::EndCombo();

	//}
#endif //DEBUG
	return bChange;
}
//------------------------------------------------------------------------------
//���[�V�����r���[��
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::MotionViewer()
{
	//�L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//���݂̃L�[
	int &nNowKey = CCharacter::GetKeySet();
	int &nNowFrame = CCharacter::GetFram();

	//���[�V�����Ɋւ�����
	CCharacter::CHARACTER_MOTION_STATE &NowMotionType = GetMotionType();
	CCharacter::MOTION *MotionInfo = CCharacter::GetCharacterMotion(NowMotionType);

	//�U���n�̏�񂪕ς�������ǂ���
	bool bChangeAttackInfo = false;
	bool bChangeNowKey = false;

	//�R�s�y�p�̃L�[
	static CCharacter::CHARACTER_MOTION_STATE CopyMotionType = CHARACTER_MOTION_STATE_NONE;
	static int nCopyKey = -1;



	////�v���C���[���W���Z�b�g
	//if (ImGui::Button("PlayerPosReset"))
	//{
	//	SetPos(ZeroVector3);
	//}

	////���[�V�����̃R���{�{�b�N�X
	//if (ShowMotionComboBox(NowMotionType))
	//{
	//	nNowKey = 0;
	//	SetAttack(false);
	//	ChangeMotion(NowMotionType);
	//	pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
	//	MotionInfo = CMotion::GetMotion(NowMotionType);
	//}

	//���[�V�������X�^�[�g
	if (ImGui::Button("ReStart") || pKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		nNowKey = 0;
		SetMotion(NowMotionType);
		ForcedUpdate();
		MotionInfo = CCharacter::GetCharacterMotion(NowMotionType);
	}

	//Widget�̑傫���ݒ�
	ImGui::PushItemWidth(100);

	////���[�V�����X�g�b�v
	//if (ImGui::Checkbox("bMotionStop", &pModelCharacter->GetMotionStop()))
	//{

	//}

	//���[�v
	//if (ImGui::Checkbox("bLoop", (bool*)MotionInfo->nLoop))
	//{

	//}

	//���s
	ImGui::Separator();

	//�PF�O�̃L�[�t���[��
	int nNumKeyOld = MotionInfo->nNumKey;

	ImGui::Text("NowKey : %d / ", nNowKey);

	ImGui::SameLine();

	//�L�[��
	if (ImGui::InputInt("NumKey", &MotionInfo->nNumKey))
	{
		//�͈͓��ɏC������
		CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->nNumKey, 0, 100);

		////�L�[������������������
		//MotionInfo->nNumKey > nNumKeyOld ?
		//	CMotion::AddKeyInfo(NowMotionType, pModelCharacter->GetType()) :			//�v�f�̒ǉ��@����
		//	CMotion::PopbackKeyInfo(NowMotionType);										//�v�f�̍폜�@����
	}

	ImGui::Text("NowFrame : %d / ", nNowFrame);

	ImGui::SameLine();


	//�t���[����
	if (ImGui::InputInt("MaxFrame", &MotionInfo->key_info[nNowKey]->nFram))
	{

	}

	////���s
	//ImGui::Separator();
	////���_�̍�������
	//if (ImGui::DragFloat("OriginHeight", &MotionInfo->pKeyInfoList[nNowKey]->fOriginHeight, 0.05f, -70.0f, 70.0f))
	//{
	//	//���[�V���������ύX
	//	pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
	//}




	//�L�[�{�[�h�́����ł����݂̃L�[�ς�����
	if (pKeyboard->GetKeyboardTrigger(DIK_LEFT))
	{
		bChangeNowKey = true;
		nNowKey--;
	}

	if (pKeyboard->GetKeyboardTrigger(DIK_RIGHT))
	{
		bChangeNowKey = true;
		nNowKey++;
	}

	//���[�V�����̕ۑ�
	if (ImGui::Button("Copy"))
	{
		//�R�s�[�̃L�[�ƃ��[�V������ۑ�
		nCopyKey = nNowKey;
		CopyMotionType = NowMotionType;
	}

	//���s���Ȃ�
	ImGui::SameLine();

	//���[�V�����̕ۑ�
	if (ImGui::Button("Paste"))
	{
		//�R�s�[�����̂��͂��
		//MotionCopy(NowMotionType, nNowKey, CopyMotionType, nCopyKey);

		//���[�V���������ύX
		ForcedUpdate();

	}

	//�R�s�[���̃��[�V�����ƃL�[
	ImGui::Text("CopyMotion [%d] CopyKey [%d]", CopyMotionType, nCopyKey);

	//���݂̃L�[�ɕύX����������
	if (bChangeNowKey)
	{
		//0�ȉ��͂O
		if (nNowKey < 0)
		{
			nNowKey = 0;
		}
		////�L�[�`�F�b�N
		//pModelCharacter->KeyCheck();

		//���[�V���������ύX
		ForcedUpdate();
	}

	//���s
	ImGui::Separator();
	//�p�[�c��]
	if (ImGui::TreeNode("PartsRot"))
	{

		//���f�������J��ւ���
		for (size_t nCnt = 0; nCnt < MotionInfo->key_info[nNowKey]->key.size(); nCnt++)
		{
			//���f�����擾
			//std::string aPartsName = CModelCharacter::GetModelName(pModelCharacter->GetType(), nCnt).data();

			////���̕����̕����������("data/MODEL/)
			//aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

			//���̍��ڂ̘g�̑傫���ݒ�
			ImGui::SetNextItemWidth(250);

			////���ꂼ��̉�]�ʂ𒲐�
			//if (ImGui::DragFloat3(aPartsName.data(), MotionInfo->key_info[nNowKey]->key[nCnt]->rot, 0.01f, -3.14f, 3.14f))
			//{
			//	//���[�V���������ύX
			//	ForcedUpdate();
			//}
		}

		//��]�ʃ��Z�b�g
		if (ImGui::Button("AllReset"))
		{
			//���f�������J��ւ���
			for (size_t nCnt = 0; nCnt < MotionInfo->key_info[nNowKey]->key.size(); nCnt++)
			{
				//���[�V���������ύX
				MotionInfo->key_info[nNowKey]->key[nCnt]->rot = ZeroVector3;
				ForcedUpdate();
			}
		}
		//tree
		ImGui::TreePop();
	}

	//���s
	ImGui::Separator();

	////���[�V�����̕ۑ�
	//if (ImGui::Button("MotionSave"))
	//{
	//	CMotion::SaveMotion(NowMotionType);
	//}

	//Widget�̑傫�������I��
	ImGui::PopItemWidth();
}
//------------------------------------------------------------------------------
//�I�t�Z�b�g�̐ݒ�
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::OffsetViewer()
{
	CModel * pModel;

	std::vector<CModel*> vModelList = GetCharacterModelList();

	//���f�������J��ւ���
	for (size_t nCnt = 0; nCnt < vModelList.size(); nCnt++)
	{
		//���f�����擾
		std::string aPartsName = CModel::GetModelFileName(vModelList[nCnt]->GetType(), nCnt);

		//���̕����̕����������("data/MODEL/)
		aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

		//���̍��ڂ̘g�̑傫���ݒ�
		ImGui::SetNextItemWidth(250);

		//���f���p�[�c�̃|�C���^�擾
		pModel = GetCharacterModelList()[nCnt];

		//���ꂼ��̃I�t�Z�b�g�𒲐�
		if (ImGui::DragFloat3(aPartsName.data(), pModel->GetPosition(), 0.05f, -100.0f, 100.0f))
		{

		}
	}

	//if(ImGui::Button("OffsetSave"))
	//{
	//	pModelCharacter->SaveModelOffset();
	//}
}
