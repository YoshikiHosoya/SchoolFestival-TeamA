//------------------------------------------------------------------------------
//
//��  [way.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "way.h"
#include "manager.h"
#include "game.h"
#include "game_2D.h"
#include "renderer.h"
#include "sound.h"
#include "particle.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CWay::CWay()
{

}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CWay::~CWay()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CWay::Init()
{
	CScene2D::Init();

	//����
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CWay::Uninit()
{
	CScene2D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CWay::Update()
{
	CScene2D::Update();

	CGame_2D *pGame2D = (CGame_2D*)CManager::GetGame();

	//�ʏ펞�ȊO�͏I���
	if (pGame2D->GetGamestate() != CGame::STATE_NORMAL)
	{
		return;
	}

	switch (pGame2D->GetDirection())
	{
	case DIRECTION::UP:
		CScene2D::GetPos().y += pGame2D->GetSpeed();

		break;
	case DIRECTION::LEFT:
		CScene2D::GetPos().x += 100.0f;

		break;
	case DIRECTION::RIGHT:
		CScene2D::GetPos().x -= 100.0f;

		break;
	default:
		break;
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CWay::Draw()
{
	CScene2D::Draw();


}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CWay::ShowDebugInfo()
{
#ifdef _DEBUG
	//�v���C���[�����
	if (ImGui::TreeNode("Way"))
	{

		ImGui::TreePop();
	}
#endif //DEBUG
}


//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::shared_ptr<CWay> CWay::Create(D3DXVECTOR3 pos, WAY_TYPE waytype)
{
	//�ϐ��錾
	std::shared_ptr<CWay> pWay = std::make_shared<CWay>();


	if (pWay)
	{
		pWay->SetPos(pos);
		pWay->SetSize(D3DXVECTOR3(400.0f, 400.0f, 0.0f));
		//������
		pWay->Init();

		pWay->m_waytype = waytype;

		pWay->BindTexture(CTexture::GetTexture(((CTexture::TEX_TYPE)(int)(CTexture::TEX_WAY_UP + (CTexture::TEX_TYPE)(pWay->m_waytype)))));

		pWay->SetObjType(OBJTYPE_WAY);


		pWay->AddSharedList(pWay);

		return pWay;
	}

	//�����������
	return nullptr;
}

//------------------------------------------------------------------------------
//�����蔻�菈��
//------------------------------------------------------------------------------
bool CWay::Collision(D3DXVECTOR3 pos)
{
	// X Y�͈̔�
	if (this->GetPos().y + this->GetSize().y * 0.5f >=	pos.y &&
		this->GetPos().y - this->GetSize().y * 0.5f <=	pos.y)
	{
		return true;
	}
	return false;
}

//------------------------------------------------------------------------------
//�����蔻�菈��
//------------------------------------------------------------------------------
bool CWay::CollisionPlayerHit(D3DXVECTOR3 pos)
{
	switch (m_waytype)
	{
	case CWay::UP:
		// X Y�͈̔�
		if (this->GetPos().x + this->GetSize().x * 0.5f <= pos.x ||
			this->GetPos().x - this->GetSize().x * 0.5f >= pos.x)
		{
			return true;
		}
		break;
	case CWay::RIGHT_01:
	case CWay::LEFT_02:
		if(this->GetPos().x - this->GetSize().x * 0.5f >= pos.x)
		{
			return true;
		}
		break;
	case CWay::LEFT_01:
	case CWay::RIGHT_02:
		if (this->GetPos().x + this->GetSize().x * 0.5f <= pos.x)
		{
			return true;
		}
		break;
	}

	return false;
}

//------------------------------------------------------------------------------
//�����蔻��@�^�C�}�[�ǉ�
//------------------------------------------------------------------------------
bool CWay::CollisionPlayerAddTimer(D3DXVECTOR3 pos)
{
	float fDistance = 400.0f;

	fDistance = fabsf(this->GetPos().y - pos.y);

	CGame_2D *pGame2D = (CGame_2D*)CManager::GetGame();

	//���Đ�
	CManager::GetSound()->Play(CSound::LABEL_SE_ADDTIME);


	if (fDistance >= 110)
	{
		pGame2D->AddTimer(2);
		printf("AddTimer 2\n");
		//���Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_PERFECT);

		CParticle::CreateFromText(pos, ZeroVector3, CParticleParam::EFFECT_CROSS, TAG::NONE,0,CHossoLibrary::RandomColor());
		CParticle::CreateFromText(pos, ZeroVector3, CParticleParam::EFFECT_CIRCLE, TAG::NONE, 0, CHossoLibrary::RandomColor());
		CParticle::CreateFromText(pos, ZeroVector3, CParticleParam::EFFECT_STAR, TAG::NONE, 0, CHossoLibrary::RandomColor());
		CParticle::CreateFromText(pos, ZeroVector3, CParticleParam::EFFECT_SQUARE, TAG::NONE, 0, CHossoLibrary::RandomColor());
		CParticle::CreateFromText(pos, ZeroVector3, CParticleParam::EFFECT_TRIANGLE, TAG::NONE, 0, CHossoLibrary::RandomColor());

		return true;
	}
	else if (fDistance >= 80)
	{
		pGame2D->AddTimer(1);
		printf("AddTimer 1\n");
		//���Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_GREAT);

		return true;

	}
	else
	{
		//���Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_GOOD);

	}
	return false;

}
