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
#include "game_2D.h"
#include "manager.h"
#include "Way.h"
#include "renderer.h"
#include "particle.h"
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
	pScene2D->BindTexture(CTexture::GetTexture(CTexture::TEX_PLAYER));

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

	CGame_2D *pGame2D = (CGame_2D*)CManager::GetGame();

	//��ɐi�s���Ă�Ƃ�
	if (pGame2D->GetDirection() == DIRECTION::UP)
	{
		//[D]�L�[����������
		if (CHossoLibrary::CheckMove(CHossoLibrary::RIGHT))
		{
			pGame2D->PlayerBending(DIRECTION::RIGHT);
		}
		//[A]�L�[����������
		if (CHossoLibrary::CheckMove(CHossoLibrary::LEFT))
		{
			pGame2D->PlayerBending(DIRECTION::LEFT);
		}
	}

	std::vector<std::shared_ptr<CScene>> pWayList;

	CScene::GetSceneList(OBJTYPE::OBJTYPE_WAY, pWayList);

	for (size_t nCnt = 0; nCnt < pWayList.size(); nCnt++)
	{
		if (!pWayList[nCnt])
		{
			continue;
		}

		CWay *pWay = (CWay*)pWayList[nCnt].get();

		if (pWay)
		{
			if(pWay->Collision(GetPos()))
			{
				CDebugProc::Print(CDebugProc::PLACE_LEFT, "WayPos.y >> %.2f\n", pWay->GetPos().y);

				if (pWay->CollisionPlayerHit(GetPos()))
				{
					CParticle::CreateFromText(GetPos(), ZeroVector3, CParticleParam::EFFECT_DEFAULT);
				}

			}
		}

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

