//------------------------------------------------------------------------------
//
//�L�����N�^�[����  [character.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "debug_character.h"
#include "../modelinfo.h"
#include "../manager.h"
#include "../renderer.h"
#include "../sound.h"
#include "../game.h"
#include "../camera.h"
#include "../modelcharacter.h"
#include "../motion.h"
#include "../collision.h"
#include "../keyboard.h"
#include "../meshfield.h"
#include "../modelparts.h"
#include "../modelparts_weapon.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CDebug_Character::CDebug_Character()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CDebug_Character::~CDebug_Character()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CDebug_Character::Init()
{
	CCharacter::Init();

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CDebug_Character::Uninit()
{
	CCharacter::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CDebug_Character::Update()
{
	CCharacter::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CDebug_Character::Draw()
{
	CCharacter::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CDebug_Character::ShowDebugInfo()
{
#ifdef _DEBUG
	static bool bMotion = true;

	//�L�����N�^�[�����
	if (ImGui::Begin("MotionViewer"))
	{
		if (ImGui::BeginTabBar("Viewer", bMotion))
		{
			if (ImGui::BeginTabItem("MotionViewer"))
			{
				MotionViewer();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("OffsetViewer"))
			{
				OffsetViewer();
				ImGui::EndTabItem();
			}

			ImGui::EndTabBar();
		}

		ImGui::End();

	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::shared_ptr<CDebug_Character> CDebug_Character::Create(CHARACTER_TYPE chara, CCharacter::PARAM_TYPE paramtype)
{
	//�ϐ��錾
	std::shared_ptr<CDebug_Character> pCharacter = std::make_shared<CDebug_Character>();

	if (pCharacter)
	{
		//������7
		pCharacter->Init();

		//�p�����[�^�ݒ�
		pCharacter->SetParameter(chara, paramtype,pCharacter);

		//�I�u�W�F�N�g�^�C�v�ݒ�
		pCharacter->SetObjType(OBJTYPE_PLAYER);

		//���X�g�ɒǉ�
		pCharacter->AddSharedList(pCharacter);
	}

	//�����������
	return pCharacter;
}

//------------------------------------------------------------------------------
//�R���{�{�b�N�X
//------------------------------------------------------------------------------
bool CDebug_Character::ShowMotionComboBox(CMotion::MOTION_TYPE &motiontype)
{
	bool bChange = false;

#ifdef _DEBUG

	std::vector<std::string > &aFileName = CMotion::GetFileName();

	//combo�J�n
	if (ImGui::BeginCombo("MotionName", aFileName[motiontype].data()))
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < aFileName.size(); nCnt++)
		{

			//�I��ԍ��������Ă邩�ǂ���
			bool is_selected = (aFileName[motiontype] == aFileName[nCnt]);

			//�I�����ꂽ���̏���
			if (ImGui::Selectable(aFileName[nCnt].data(), is_selected))
			{
				//���݂̑I�����ڐݒ�
				motiontype = (CMotion::MOTION_TYPE)nCnt;
				bChange = true;
			}

			////
			//if (is_selected)
			//{
			//	//�X�N���[���̏����ʒu�ݒ�
			//	ImGui::SetItemDefaultFocus();
			//}
		}
		//combo�I��
		ImGui::EndCombo();

	}
#endif //DEBUG
	return bChange;
}
//------------------------------------------------------------------------------
//���[�V�����r���[��
//------------------------------------------------------------------------------
void CDebug_Character::MotionViewer()
{
	//�L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//���f���L�����N�^�[�̃|�C���^
	CModelCharacter *pModelCharacter = GetModelCharacterPtr();

	//���݂̃L�[
	int &nNowKey = pModelCharacter->GetKey();

	//���[�V�����Ɋւ�����
	CMotion::MOTION_TYPE &NowMotionType = pModelCharacter->GetMotion();
	CMotion::MOTION_INFO *MotionInfo = CMotion::GetMotion(NowMotionType);

	//�U���n�̏�񂪕ς�������ǂ���
	bool bChangeAttackInfo = false;
	bool bChangeNowKey = false;

	//�R�s�y�p�̃L�[
	static CMotion::MOTION_TYPE CopyMotionType = CMotion::MOTION_NONE;
	static int nCopyKey = -1;



	//�v���C���[���W���Z�b�g
	if (ImGui::Button("PlayerPosReset"))
	{
		SetPos(ZeroVector3);
	}

	//���[�V�����̃R���{�{�b�N�X
	if (ShowMotionComboBox(NowMotionType))
	{
		nNowKey = 0;
		SetAttack(false);
		ChangeMotion(NowMotionType);
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
		MotionInfo = CMotion::GetMotion(NowMotionType);

	}

	//���s���Ȃ�
	ImGui::SameLine();

	//���[�V�������X�^�[�g
	if (ImGui::Button("ReStart") || pKeyboard->GetTrigger(DIK_RETURN))
	{
		nNowKey = 0;
		SetAttack(false);
		pModelCharacter->SetMotionStop(false);
		ChangeMotion(NowMotionType);
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
		MotionInfo = CMotion::GetMotion(NowMotionType);
	}

	//Widget�̑傫���ݒ�
	ImGui::PushItemWidth(100);

	//���[�v
	if (ImGui::Checkbox("bMotionStop", &pModelCharacter->GetMotionStop()))
	{

	}

	//���[�v
	if (ImGui::Checkbox("bLoop", &MotionInfo->bLoop))
	{

	}

	//�U�����邩�ǂ���
	ImGui::Text("bAttack %d", (int)MotionInfo->bAttack);

	//���s
	ImGui::Separator();

	//�U���̃��[�V������������
	if (MotionInfo->bAttack)
	{
		if (ImGui::TreeNode("AttackInfo"))
		{

			//�O�Ղ̐F�@float�^�ɃL���X�g
			float *rCol = MotionInfo->pAttackInfo->orbitcol;

			ImGui::SetNextItemWidth(250.0f);

			//�F�̐ݒ�
			if (ImGui::ColorEdit4("OrbitColor", rCol)) { bChangeAttackInfo = true; };

			//�U���Ɋւ�����
			if (ImGui::DragInt("AttackValue", &MotionInfo->pAttackInfo->nAttack, 0.3f, 0, 100))
			{
				bChangeAttackInfo = true;
			}
			if (ImGui::DragInt("BlueAttackValue", &MotionInfo->pAttackInfo->nBlueAttack, 0.3f, 0, 100))
			{
				bChangeAttackInfo = true;
			}
			if (ImGui::DragFloat("CollisionLength", &MotionInfo->pAttackInfo->fLength, 0.1f, 0.0f, 200.0f))
			{
				bChangeAttackInfo = true;
			}
			if (ImGui::DragFloat("CollisionRadius", &MotionInfo->pAttackInfo->fRadius, 0.1f, 0.0f, 50.0f))
			{
				bChangeAttackInfo = true;
			}

			//�U���Ɋւ����񂪕ς������
			if (bChangeAttackInfo)
			{
				//�U���̏��X�V
				pModelCharacter->UpdateAttackInfo();
			}

			//�J�n�̃L�[
			if (ImGui::InputInt("CollisionStartKey", &MotionInfo->pAttackInfo->nStartCollisonKey))
			{
				//�͈͓��ɏC������
				CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->pAttackInfo->nStartCollisonKey, 0, MotionInfo->pAttackInfo->nEndCollisionKey);

			}
			//�I���̃L�[
			if (ImGui::InputInt("CollisionEndKEy", &MotionInfo->pAttackInfo->nEndCollisionKey))
			{
				//�͈͓��ɏC������
				CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->pAttackInfo->nEndCollisionKey, MotionInfo->pAttackInfo->nStartCollisonKey, MotionInfo->nNumKey);
			}

			//�ړ����x
			if (ImGui::DragFloat("MoveFront", &MotionInfo->pAttackInfo->fMoveFront, 0.02f, 0.0f, 30.0f))
			{

			}
			ImGui::SameLine();
			//�ړ����x
			if (ImGui::DragFloat("MoveUp", &MotionInfo->pAttackInfo->fMoveUp, 0.02f, -30.0f, 30.0f))
			{

			}
			ImGui::SameLine();
			//�ړ����x
			if (ImGui::InputInt("MoveKey", &MotionInfo->pAttackInfo->nMoveKey))
			{
				//�͈͓��ɏC������
				CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->pAttackInfo->nMoveKey, 0, MotionInfo->nNumKey);
			}

			//�m�b�N�o�b�N
			if (ImGui::DragFloat("KnockBack_Front", &MotionInfo->pAttackInfo->fKnockBack_Front, 0.02f, 0.0f, 30.0f))
			{

			}
			ImGui::SameLine();
			//�m�b�N�o�b�N
			if (ImGui::DragFloat("KnockBack_Up", &MotionInfo->pAttackInfo->fKnockBack_Up, 0.02f, -30.0f, 30.0f))
			{

			}
			ImGui::TreePop();
		}
		//���s
		ImGui::Separator();
	}

	//�PF�O�̃L�[�t���[��
	int nNumKeyOld = MotionInfo->nNumKey;

	//�L�[��
	if (ImGui::InputInt("NumKey", &MotionInfo->nNumKey))
	{
		//�͈͓��ɏC������
		CHossoLibrary::RangeLimit_Equal_Int(MotionInfo->nNumKey, 0, 100);

		//�L�[������������������
		MotionInfo->nNumKey > nNumKeyOld ?
			CMotion::AddKeyInfo(NowMotionType, pModelCharacter->GetType()) :			//�v�f�̒ǉ��@����
			CMotion::PopbackKeyInfo(NowMotionType);										//�v�f�̍폜�@����
	}

	//�t���[����
	if (ImGui::InputInt("MaxFrame", &MotionInfo->pKeyInfoList[nNowKey]->nFrame))
	{

	}

	//���s
	ImGui::Separator();
	//���_�̍�������
	if (ImGui::DragFloat("OriginHeight", &MotionInfo->pKeyInfoList[nNowKey]->fOriginHeight, 0.05f, -70.0f, 70.0f))
	{
		//���[�V���������ύX
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
	}


	//���݂̃L�[
	if (ImGui::InputInt("NowKey", &nNowKey))
	{
		bChangeNowKey = true;
	}

	//�L�[�{�[�h�́����ł����݂̃L�[�ς�����
	if (pKeyboard->GetTrigger(DIK_LEFT))
	{
		bChangeNowKey = true;
		nNowKey--;
	}

	if (pKeyboard->GetTrigger(DIK_RIGHT))
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
		CMotion::MotionCopy(NowMotionType, nNowKey, CopyMotionType, nCopyKey);

		//���[�V���������ύX
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);

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
		//�L�[�`�F�b�N
		pModelCharacter->KeyCheck();

		//���[�V���������ύX
		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
	}

	//���s
	ImGui::Separator();
	//�p�[�c��]
	if (ImGui::TreeNode("PartsRot"))
	{

		////���f�������J��ւ���
		//for (int nCnt = 0; nCnt < pModelCharacter->GetModelNum(pModelCharacter->GetType()); nCnt++)
		//{
		//	//���f�����擾
		//	//std::string aPartsName = CModelCharacter::GetModelName(pModelCharacter->GetType(), nCnt).data();

		//	//���̕����̕����������("data/MODEL/)
		//	aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

		//	//���̍��ڂ̘g�̑傫���ݒ�
		//	ImGui::SetNextItemWidth(250);

		//	//���ꂼ��̉�]�ʂ𒲐�
		//	if (ImGui::DragFloat3(aPartsName.data(), MotionInfo->pKeyInfoList[nNowKey]->pKeyList[nCnt]->rotDest, 0.01f, -3.14f, 3.14f))
		//	{
		//		//���[�V���������ύX
		//		pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
		//	}
		//}

		//��]�ʃ��Z�b�g
		if (ImGui::Button("AllReset"))
		{
			//���f�������J��ւ���
			for (int nCnt = 0; nCnt < pModelCharacter->GetModelNum(pModelCharacter->GetType()); nCnt++)
			{
				//���[�V���������ύX
				MotionInfo->pKeyInfoList[nNowKey]->pKeyList[nCnt]->rotDest = ZeroVector3;
				pModelCharacter->ForcedUpdate(NowMotionType, nNowKey);
			}
		}
		//tree
		ImGui::TreePop();
	}

	//���s
	ImGui::Separator();

	//���[�V�����̕ۑ�
	if (ImGui::Button("MotionSave"))
	{
		CMotion::SaveMotion(NowMotionType);
	}

	//Widget�̑傫�������I��
	ImGui::PopItemWidth();

}
//------------------------------------------------------------------------------
//�I�t�Z�b�g�̐ݒ�
//------------------------------------------------------------------------------
void CDebug_Character::OffsetViewer()
{
	//���f���L�����N�^�[�̃|�C���^
	CModelCharacter *pModelCharacter = GetModelCharacterPtr();

	CModelParts *pModelParts;

	////���f�������J��ւ���
	//for (int nCnt = 0; nCnt < pModelCharacter->GetModelNum(pModelCharacter->GetType()); nCnt++)
	//{
	//	//���f�����擾
	//	std::string aPartsName = CModelCharacter::GetModelName(pModelCharacter->GetType(), nCnt).data();

	//	//���̕����̕����������("data/MODEL/)
	//	aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 11);

	//	//���̍��ڂ̘g�̑傫���ݒ�
	//	ImGui::SetNextItemWidth(250);

	//	//���f���p�[�c�̃|�C���^�擾
	//	pModelParts = pModelCharacter->GetPartsPtr(nCnt);

	//	//���ꂼ��̉�]�ʂ𒲐�
	//	if (ImGui::DragFloat3(aPartsName.data(), pModelParts->GetPos(), 0.05f, -100.0f, 100.0f))
	//	{

	//	}
	//}

	if(ImGui::Button("OffsetSave"))
	{
		pModelCharacter->SaveModelOffset();
	}
}
