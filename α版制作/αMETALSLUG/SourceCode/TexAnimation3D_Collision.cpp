//------------------------------------------------------------------------------
//
//�����蔻��t���e�N�X�`���A�j���[�V����3D����  [TexAnimation3D_Collision.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "TexAnimation3D_Collision.h"
#include "manager.h"
#include "renderer.h"
#include "collision.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::CTexAnimation3D_Collision()
{

}
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::CTexAnimation3D_Collision(OBJ_TYPE obj) : CTexAnimation3D(obj)
{

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation3D_Collision::~CTexAnimation3D_Collision()
{
	if(m_pCollision)
	{
		delete m_pCollision;
		m_pCollision = nullptr;
	}
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTexAnimation3D_Collision::Init()
{
	//����������
	if (FAILED(CTexAnimation3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Uninit()
{
	//�I������
	CTexAnimation3D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Update()
{
	//�X�V����
	CTexAnimation3D::Update();

	Collision();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Draw()
{
	//�`�揈��
	CTexAnimation3D::Draw();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CTexAnimation3D_Collision::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type, int nCntSwitch, CScene::OBJ_TYPE objtype, bool bPlayer)
{
	//�������m��
	CTexAnimation3D_Collision *pEffectAnimation = new CTexAnimation3D_Collision(objtype);

	//nullcheck
	if (pEffectAnimation)
	{
		//������
		pEffectAnimation->Init();

		//���������@Scene��
		pEffectAnimation->SetPosition(pos);
		pEffectAnimation->SetSize(size);
		pEffectAnimation->SetRot(rot);
		pEffectAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pEffectAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pEffectAnimation->m_bPlayer = bPlayer;

		//���������@TexAnimation��
		pEffectAnimation->SetTex(type);
		pEffectAnimation->SetCntSwitch(nCntSwitch);

		pEffectAnimation->m_pCollision = CCollision::Create();
		pEffectAnimation->m_pCollision->SetPos(pEffectAnimation->GetPosPtr());
		pEffectAnimation->m_pCollision->SetSize(size);
		pEffectAnimation->m_pCollision->DeCollisionCreate(CCollision::COLLISIONTYPE_BLOCK);
	}
}

//------------------------------------------------------------------------------
//�����蔻�菈��
//------------------------------------------------------------------------------
bool CTexAnimation3D_Collision::Collision()
{
	//nullcheck
	if (m_pCollision)
	{
		//�v���C���[�̍U���������ꍇ
		if (m_bPlayer)
		{
			//�����蔻��
			m_pCollision->ForPlayerBulletCollision(1, 1, true);
		}
	}



	return false;
}
