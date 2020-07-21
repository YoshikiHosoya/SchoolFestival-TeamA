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
#include "../manager.h"
#include "../renderer.h"
#include "../game.h"
#include "../camera.h"
#include "../inputKeyboard.h"
#include "../model.h"
#include "../gun.h"
#include "../knife.h"

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

	//�I�t�Z�b�g�ݒ�
	CCharacter::LoadOffset(CCharacter::CHARACTER_TYPE_PRISONER);

	//������
	SetRotDest(ZeroVector3);

	////�e�̐���
	//m_pGun = CGun::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_RHAND)->GetMatrix());

	////�i�C�t�̐���
	//m_pKnife = CKnife::Create(GetCharacterModelPartsList(CModel::MODEL_PLAYER_LHAND)->GetMatrix());
	//m_pKnife->SetPosition(D3DXVECTOR3(6.0f, 0.0f, 0.0f));

	////�i�C�tON���
	//m_pKnife->StartMeleeAttack();

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

	if (GetPosition().y <= 0.0f)
	{
		GetPosition().y = 0.0f;
	}
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
void CDebug_ViewerCharacter::DebugInfo()
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
	}

	//�����������
	return pCharacter;
}

//------------------------------------------------------------------------------
//�R���{�{�b�N�X
//------------------------------------------------------------------------------
bool CDebug_ViewerCharacter::ShowMotionComboBox(CCharacter::CHARACTER_MOTION_STATE &motiontype)
{
	bool bChange = false;

#ifdef _DEBUG

	//�t�@�C����
	FILENAME_LIST aFileName = {};

	//for
	for (int nCnt = 0; nCnt < CCharacter::CHARACTER_MOTION_MAX; nCnt++)
	{
		//�z��ɒǉ�
		aFileName.emplace_back(CCharacter::GetMotionFileName((CCharacter::CHARACTER_MOTION_STATE)nCnt));
	}

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
				motiontype = (CCharacter::CHARACTER_MOTION_STATE)nCnt;
				bChange = true;
			}
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
void CDebug_ViewerCharacter::MotionViewer()
{
	//�L�[�{�[�h�̃|�C���^
	CKeyboard *pKeyboard = CManager::GetInputKeyboard();

	//���݂̃L�[
	int &nNowKey = CCharacter::GetKeySet();
	int &nNowFrame = CCharacter::GetFram();

	//���[�V�����Ɋւ�����
	CCharacter::CHARACTER_MOTION_STATE &NowMotionType = GetMotionType();
	CCharacter::MOTION *pMotionInfo = CCharacter::GetCharacterMotion(NowMotionType);

	//�U���n�̏�񂪕ς�������ǂ���
	bool bChangeAttackInfo = false;
	bool bChangeNowKey = false;

	//�R�s�y�p�̃L�[
	static CCharacter::CHARACTER_MOTION_STATE CopyMotionType = CHARACTER_MOTION_STATE_NONE;
	static int nCopyKey = -1;

	int *pLoop = &pMotionInfo->nLoop;

	////�v���C���[���W���Z�b�g
	//if (ImGui::Button("PlayerPosReset"))
	//{
	//	SetPos(ZeroVector3);
	//}

	//���[�V�����̃R���{�{�b�N�X
	if (ShowMotionComboBox(NowMotionType))
	{
		ResetKey();
		SetMotion(NowMotionType);
		ForcedUpdate();
		pMotionInfo = CCharacter::GetCharacterMotion(NowMotionType);
	}

	//���[�V�������X�^�[�g
	if (ImGui::Button("ReStart") || pKeyboard->GetKeyboardTrigger(DIK_RETURN))
	{
		ResetKey();
		SetMotion(NowMotionType);
		ForcedUpdate();
		pMotionInfo = CCharacter::GetCharacterMotion(NowMotionType);
		GetMotion() = true;
	}

	//Widget�̑傫���ݒ�
	ImGui::PushItemWidth(100);

	////���[�V�����X�g�b�v
	//if (ImGui::Checkbox("bMotionStop", &pModelCharacter->GetMotionStop()))
	//{

	//}

	//���[�v
	if (ImGui::Checkbox("bLoop", (bool*)pLoop))
	{

	}

	//���s
	ImGui::Separator();

	//�PF�O�̃L�[�t���[��
	int nNumKeyOld = pMotionInfo->nNumKey;

	ImGui::Text("NowKey : %d / ", nNowKey);

	ImGui::SameLine();

	//�L�[��
	if (ImGui::InputInt("NumKey", &pMotionInfo->nNumKey))
	{
		//�͈͓��ɏC������
		CHossoLibrary::RangeLimit_Equal_Int(pMotionInfo->nNumKey, 0, 30);

		//�L�[������
		ResetKey();

		//�L�[������������������
		pMotionInfo->nNumKey > nNumKeyOld ?
			AddKeyInfo(pMotionInfo) :			//�v�f�̒ǉ��@����
			PopbackKeyInfo(pMotionInfo);		//�v�f�̍폜�@����
	}

	ImGui::Text("NowFrame : %d / ", nNowFrame);

	//�����s
	ImGui::SameLine();

	//�t���[����
	if (ImGui::InputInt("MaxFrame", &pMotionInfo->key_info[nNowKey]->nFram))
	{
		nNowFrame = 0;
	}

	//���s
	ImGui::Separator();
	//���_�̍�������
	if (ImGui::DragFloat("OriginHeight", &pMotionInfo->key_info[nNowKey]->fHeight, 0.05f, -100.0f, 100.0f))
	{
		//���[�V���������ύX
		ForcedUpdate();
	}

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
		CopyMotionPaste(NowMotionType, nNowKey, CopyMotionType, nCopyKey);

		//���[�V���������ύX
		ForcedUpdate();

	}

	//�R�s�[���̃��[�V�����ƃL�[
	ImGui::Text("CopyMotion [%d] CopyKey [%d]", CopyMotionType, nCopyKey);

	//���݂̃L�[�ɕύX����������
	if (bChangeNowKey)
	{
		//�͈͓��Ɏ��߂�
		CHossoLibrary::RangeLimit_Equal_Int(nNowKey, 0, pMotionInfo->nNumKey - 1);

		nNowFrame = 0;

		//���[�V���������ύX
		ForcedUpdate();
	}

	//���s
	ImGui::Separator();
	//�p�[�c��]
	if (ImGui::TreeNode("PartsRot"))
	{
		std::vector<CModel*> vModelList = GetCharacterModelList();

		//���f�������J��ւ���
		for (size_t nCnt = 0; nCnt < vModelList.size(); nCnt++)
		{
			//���f�����擾
			std::string aPartsName = CModel::GetModelFileName(vModelList[nCnt]->GetType(), nCnt);

			//���̕����̕����������("data/MODEL/character/)
			aPartsName.erase(aPartsName.begin(), aPartsName.begin() + 19);

			//���̍��ڂ̘g�̑傫���ݒ�
			ImGui::SetNextItemWidth(250);

			//���ꂼ��̉�]�ʂ𒲐�
			if (ImGui::DragFloat3(aPartsName.data(), pMotionInfo->key_info[nNowKey]->key[nCnt]->rot, 0.01f, -3.14f, 3.14f))
			{
				//���[�V���������ύX
				ForcedUpdate();
			}
		}

		//��]�ʃ��Z�b�g
		if (ImGui::Button("AllReset"))
		{
			//���f�������J��ւ���
			for (size_t nCnt = 0; nCnt < pMotionInfo->key_info[nNowKey]->key.size(); nCnt++)
			{
				//���[�V���������ύX
				pMotionInfo->key_info[nNowKey]->key[nCnt]->rot = ZeroVector3;
				ForcedUpdate();
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
		SaveMotion(NowMotionType);
	}

	//Widget�̑傫�������I��
	ImGui::PopItemWidth();
}

//------------------------------------------------------------------------------
//�L�[�ǉ�
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::AddKeyInfo(CCharacter::MOTION *pMotion)
{
	KEY *pKey;						//���̃|�C���^
	KEY_INFO *pKeyInfo;				//���̃|�C���^

	//�������m��
	pKeyInfo = new KEY_INFO;

	//�z��ɒǉ�
	pMotion->key_info.emplace_back(pKeyInfo);

	//�L�[�����ǉ�
	//�L�����N�^�̃��f������
	for (size_t nCnt = 0; nCnt < GetCharacterModelList().size(); nCnt++)
	{
		//�������m��
		pKey = new KEY;

		//�z��ɒǉ�
		pMotion->key_info[pMotion->nNumKey - 1]->key.emplace_back(pKey);
	}
}
//------------------------------------------------------------------------------
//�L�[����
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::PopbackKeyInfo(CCharacter::MOTION *pMotion)
{
	pMotion->key_info.pop_back();
}

//------------------------------------------------------------------------------
//�L�[���Z�b�g
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::ResetKey()
{
	//���݂̃L�[
	CCharacter::GetKeySet() = 0;
	CCharacter::GetFram() = 0;

}

//------------------------------------------------------------------------------
//�R�s�[�������[�V�����y�[�X�g
//------------------------------------------------------------------------------
void CDebug_ViewerCharacter::CopyMotionPaste(CCharacter::CHARACTER_MOTION_STATE NowMotion, int nNowKey ,CCharacter::CHARACTER_MOTION_STATE CopyMotionType,int nCopyKey)
{
	//�͈͊O����Ȃ����ǂ���
	if (CopyMotionType != CCharacter::CHARACTER_MOTION_STATE_NONE && nCopyKey != -1)
	{
		CCharacter::MOTION *pCopyMotion = CCharacter::GetCharacterMotion(CopyMotionType);
		CCharacter::MOTION *pNowMotion = CCharacter::GetCharacterMotion(NowMotion);

		//�R�s�[
		for (size_t nCnt = 0; nCnt < GetCharacterModelList().size(); nCnt++)
		{
			pNowMotion->key_info[nNowKey]->key[nCnt]->rot = pCopyMotion->key_info[nCopyKey]->key[nCnt]->rot;
		}
	}
}

//------------------------------------------------------------------------------
//���[�V�����̕ۑ�
//------------------------------------------------------------------------------
HRESULT CDebug_ViewerCharacter::SaveMotion(CCharacter::CHARACTER_MOTION_STATE motiontype)
{
	FILE *pFile;

	int nRotNum = 0;
	char cHeadtext[128];
	char cWriteText[128];

	//�t�@�C���ǂݍ���
	pFile = fopen(GetMotionFileName(motiontype), "w");
	//pFile = fopen("test.txt", "w");

	CCharacter::MOTION *pMotionInfo = CCharacter::GetCharacterMotion(motiontype);

	//nullcheck
	if (pFile && pMotionInfo)
	{
		//�u���b�N�R�����g
		fputs(COMMENT02, pFile);
		fputs(COMMENT01, pFile);

		fputs("//Motion\n", pFile);
		fputs("//���[�V�����Ɋւ�����\n", pFile);
		fputs("//Author:Yoshiki Hosoya\n", pFile);


		fputs(COMMENT01, pFile);
		fputs(COMMENT02, pFile);
		fputs(NEWLINE, pFile);

		//�u���b�N�R�����g�I��//

		//�X�N���v�g
		strcpy(cHeadtext, "SCRIPT");
		fputs(cHeadtext, pFile);
		fputs(NEWLINE, pFile);

		//���s
		fputs(NEWLINE, pFile);

		//���[�v
		strcpy(cHeadtext, "LOOP");
		sprintf(cWriteText, "	%s %s %d		%s", "LOOP", &EQUAL, pMotionInfo->nLoop, "//���[�v���邩�ǂ���");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);

		//�L�[��
		strcpy(cHeadtext, "NUM_KEY");
		sprintf(cWriteText, "	%s %s %d		%s", "NUM_KEY", &EQUAL, pMotionInfo->nNumKey, "//�L�[��");
		fputs(cWriteText, pFile);
		fputs(NEWLINE, pFile);
		fputs(NEWLINE, pFile);

		//nullcheck
		if (!pMotionInfo->key_info.empty())
		{
			for (int nCnt = 0; nCnt < pMotionInfo->nNumKey; nCnt++)
			{
				//�L�[�Z�b�g
				sprintf(cWriteText, "	KEYSET		//---< KEY : %d / %d >---", nCnt, pMotionInfo->nNumKey);
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//�t���[����
				sprintf(cWriteText, "		%s %s %d		%s", "FRAME", &EQUAL, pMotionInfo->key_info[nCnt]->nFram, "//�t���[����");
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				//����
				sprintf(cWriteText, "		%s %s %.2f		%s", "HEIGHT", &EQUAL, pMotionInfo->key_info[nCnt]->fHeight, "//���_�̍���");
				fputs(cWriteText, pFile);
				fputs(NEWLINE, pFile);

				fputs(NEWLINE, pFile);

				for (size_t nCntParts = 0; nCntParts < pMotionInfo->key_info[nCnt]->key.size(); nCntParts++)
				{
					//�L�[
					sprintf(cWriteText, "		KEY [%d] = %.3f %.3f %.3f", nCntParts, pMotionInfo->key_info[nCnt]->key[nCntParts]->rot.x,
						pMotionInfo->key_info[nCnt]->key[nCntParts]->rot.y, pMotionInfo->key_info[nCnt]->key[nCntParts]->rot.z);
					fputs(cWriteText, pFile);
					fputs(NEWLINE, pFile);

				}
				//�L�[�Z�b�g�I��
				fputs("	END_KEYSET", pFile);
				fputs(NEWLINE, pFile);
				fputs(NEWLINE, pFile);
			}

		}

		//�L�[�Z�b�g�I��
		fputs("END_SCRIPT", pFile);
		fputs(NEWLINE, pFile);

		//�ۑ�����
		std::cout << "Motion Save Succsess!! >>" << GetMotionFileName(motiontype) << NEWLINE;

		//�t�@�C�������
		fclose(pFile);
	}
	else
	{
		//�t�@�C�����J���܂���ł���
		std::cout << "Motion Save FAILED!!  Can't Open File. SavePlaceData()" << NEWLINE;
		return E_FAIL;
	}
	return S_OK;
}
