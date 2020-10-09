//------------------------------------------------------------------------------
//
//�v���C���[2D����  [player_2D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "player_2D.h"
#include "manager.h"
#include "renderer.h"
#include "Pad_XInput.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CPlayer_2D::CPlayer_2D()
{
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CPlayer_2D::~CPlayer_2D()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CPlayer_2D::Init()
{
	CCharacter_2D::Init();

	//�������m��
	std::unique_ptr<CScene2D> pScene2D = CScene2D::Create_SelfManagement(GetPos(), D3DXVECTOR3(50.0f, 50.0f, 0.0f));

	//�e�N�X�`���ݒ�
	pScene2D->BindTexture(CTexture::GetTexture(CTexture::SEPARATE_TEX_PLAYER));

	//Scene2D�Z�b�g
	SetScene2D(std::move(pScene2D));

	//�d�͖���
	CCharacter::SetGravity(false);

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CPlayer_2D::Uninit()
{
	CCharacter_2D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CPlayer_2D::Update()
{
	//�ړ�����
	MoveInput();

	//�X�V
	CCharacter_2D::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CPlayer_2D::Draw()
{
	CCharacter_2D::Draw();
}

//------------------------------------------------------------------------------
//�ړ��̓���
//------------------------------------------------------------------------------
void CPlayer_2D::MoveInput()
{
	//�Q�[���p�b�h�̏��擾
	CPad_XInput *pGamePad = CManager::GetXInput();

	//�ϐ��錾
	float joypadX, joypadY;

	//�W���C�p�b�h�̈ړ�����
	pGamePad->GetStickLeft(&joypadX, &joypadY);

	if (joypadX != 0 || joypadY != 0)
	{
		GetMove().x += joypadX * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed() / 32768.0f;
		GetMove().y -= joypadY * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed() / 32768.0f;
	}

	//[D]�L�[����������
	if (CHossoLibrary::CheckMove(CHossoLibrary::RIGHT))
	{
		//[W]�L�[����������
		if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
		{
			//�E��Ɉړ�
			GetMove().x += sinf(D3DX_PI * 0.75f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(D3DX_PI * 0.75f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();

		}
		//[S]�L�[����������
		else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			//�E���Ɉړ�
			GetMove().x += sinf(D3DX_PI * 0.25f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(D3DX_PI * 0.25f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		}
		else
		{
			//�E�Ɉړ�
			GetMove().x += sinf(D3DX_PI * 0.5f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(D3DX_PI * 0.5f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();

		}
	}
	//[A]�L�[����������
	else if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT))
	{
		//[W]�L�[����������
		if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
		{
			//����Ɉړ�
			GetMove().x += sinf(-D3DX_PI * 0.75f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(-D3DX_PI * 0.75f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		}
		//[S]�L�[����������
		else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
		{
			//�����Ɉړ�
			GetMove().x += sinf(-D3DX_PI * 0.25f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(-D3DX_PI * 0.25f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		}
		else
		{
			//���Ɉړ�
			GetMove().x += sinf(-D3DX_PI * 0.5f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
			GetMove().y += cosf(-D3DX_PI * 0.5f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();

		}
	}
	//[W]�L�[����������
	else if (CHossoLibrary::CheckMove(CHossoLibrary::UP))
	{
		//��Ɉړ�
		GetMove().x += sinf(D3DX_PI * 1.0f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		GetMove().y += cosf(D3DX_PI * 1.0f) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
	}
	//[S]�L�[����������
	else if (CHossoLibrary::CheckMove(CHossoLibrary::DOWN))
	{
		//���Ɉړ�
		GetMove().x += sinf(D3DX_PI * 0) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
		GetMove().y += cosf(D3DX_PI * 0) * CCharacter::GetDefaultParam(GetParam())->GetMoveSpeed();
	}
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CPlayer_2D::ShowDebugInfo()
{
#ifdef _DEBUG
	//�v���C���[�����
	if (ImGui::TreeNode("PlayerInfo"))
	{
		//�L�����N�^�[���\��
		ShowCharacterInfo();

		ImGui::TreePop();
	}
#endif //DEBUG
}

//------------------------------------------------------------------------------
//�_���[�W�󂯂���̏���
//------------------------------------------------------------------------------
void CPlayer_2D::DamageAction()
{

}
//------------------------------------------------------------------------------
//���S���̏���
//------------------------------------------------------------------------------
void CPlayer_2D::DeathAction()
{
	////�Q�[���I��
	//CManager::GetGame()->SetGamestate(CGame::STATE_GAMECLEAR);
}
//------------------------------------------------------------------------------
//�X�e�[�g�ύX����
//------------------------------------------------------------------------------
void CPlayer_2D::SetState(STATE nextstate)
{
	CCharacter_2D::SetState(nextstate);
	switch (nextstate)
	{
	case CCharacter::STATE_NORMAL:
		break;
	}
}


//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::shared_ptr<CPlayer_2D> CPlayer_2D::Create(D3DXVECTOR3 pos)
{
	//�ϐ��錾
	std::shared_ptr<CPlayer_2D> pPlayer = std::make_shared<CPlayer_2D>();


	if (pPlayer)
	{
		//������
		pPlayer->Init();

		//���W�ݒ�
		pPlayer->SetPos(pos);

		//�I�u�W�F�N�g�^�C�v�ݒ�
		pPlayer->SetObjType(OBJTYPE_PLAYER);

		//���X�g�ɒǉ�
		pPlayer->AddSharedList(pPlayer);

		return pPlayer;
	}

	//�����������
	return nullptr;
}

