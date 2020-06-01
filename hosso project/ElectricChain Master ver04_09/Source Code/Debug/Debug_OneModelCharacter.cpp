//------------------------------------------------------------------------------
//
//�L�����N�^�[����  [character.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "Debug_OneModelCharacter.h"
#include "../modelinfo.h"
#include "../manager.h"
#include "../renderer.h"
#include "../camera.h"
#include "../modelcharacter.h"
#include "../collision.h"
#include "../meshfield.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define MOVESPEED (10.0f)

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
Debug_OneModelCharacter::Debug_OneModelCharacter()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
Debug_OneModelCharacter::~Debug_OneModelCharacter()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT Debug_OneModelCharacter::Init()
{
	CModel_Object::Init();

	CSceneX::BindModelInfo(CModelInfo::GetModelInfo(CModelInfo::MODEL_MAPOBJECT_HEAD));


	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::Uninit()
{
	CModel_Object::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::Update()
{
	CModel_Object::Update();

	//�J������]���擾
	float fCameraRot = CManager::GetRenderer()->GetCamera()->GetCameraRot().y;

	//���W�擾
	D3DXVECTOR3 &rPos = GetPos();

	if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT))
	{
		if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
		{
			//����
			rPos.x += sinf(-D3DX_PI * 0.75f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(-D3DX_PI * 0.75f - fCameraRot) * MOVESPEED;

		}
		else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			//����
			rPos.x += sinf(-D3DX_PI * 0.25f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(-D3DX_PI * 0.25f - fCameraRot) * MOVESPEED;

		}
		else
		{
			//��
			rPos.x += sinf(-D3DX_PI * 0.5f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(-D3DX_PI * 0.5f - fCameraRot) * MOVESPEED;

		}
	}
	else if (CHossoLibrary::CheckMove(CHossoLibrary::RIGHT))
	{
		if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
		{
			//�E��
			rPos.x += sinf(D3DX_PI * 0.75f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(D3DX_PI * 0.75f - fCameraRot) * MOVESPEED;

		}
		else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			//�E��
			rPos.x += sinf(D3DX_PI * 0.25f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(D3DX_PI * 0.25f - fCameraRot) * MOVESPEED;

		}
		else
		{
			//�E
			rPos.x += sinf(D3DX_PI * 0.5f - fCameraRot) * MOVESPEED;
			rPos.z -= cosf(D3DX_PI * 0.5f - fCameraRot) * MOVESPEED;


		}
	}
	else if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
	{
		//��
		rPos.x += sinf(D3DX_PI * 1.0f - fCameraRot) * MOVESPEED;
		rPos.z -= cosf(D3DX_PI * 1.0f - fCameraRot) * MOVESPEED;


	}
	else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
	{
		//��
		rPos.x += sinf(D3DX_PI * 0 - fCameraRot) * MOVESPEED;
		rPos.z -= cosf(D3DX_PI * 0 - fCameraRot) * MOVESPEED;

	}

	//�d��
	rPos.y -= 50.0f;

	//Scene�̃��X�g
	std::vector<std::shared_ptr<CScene>> pSceneList;

	//�V�[�����擾
	CScene::GetSceneList(CScene::OBJTYPE_MESHFIELD, pSceneList);
	//�z��ɓ����Ă邩
	if (!pSceneList.empty())
	{
		//�v�f��
		for (size_t nCnt = 0; nCnt < pSceneList.size(); nCnt++)
		{
			//�|�C���^�擾 CMeshField�^�ɃL���X�g
			CMeshField *pMeshField = ((CMeshField*)pSceneList[nCnt].get());

			//nullcheck
			if (pMeshField)
			{
				//�����擾
				pMeshField->GetHeight(GetPos());
			}
		}
	}


}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::Draw()
{
	CModel_Object::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
void Debug_OneModelCharacter::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�������m��
	std::shared_ptr<Debug_OneModelCharacter> pOneModelChara(new Debug_OneModelCharacter);

	//nullcheck
	if (pOneModelChara)
	{
		//������
		pOneModelChara->Init();

		//���ݒ�
		pOneModelChara->SetPos(pos);
		pOneModelChara->SetRot(rot);

		//�I�u�W�F�N�g�^�C�v�ݒ�
		pOneModelChara->SetObjType(OBJTYPE_MAPOBJECT);
		pOneModelChara->AddSharedList(pOneModelChara);
	}
}