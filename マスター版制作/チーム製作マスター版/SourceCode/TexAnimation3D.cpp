//------------------------------------------------------------------------------
//
//�e�N�X�`���A�j���[�V����3D����  [TexAnimation3D.h]
//Author:Fujiwara Masato
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "TexAnimation3D.h"
#include "manager.h"
#include "renderer.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation3D::CTexAnimation3D()
{

}
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation3D::CTexAnimation3D(OBJ_TYPE obj) : CScene3D(obj)
{

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation3D::~CTexAnimation3D()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTexAnimation3D::Init()
{
	//����������
	if (FAILED(CScene3D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CTexAnimation3D::Uninit()
{
	//�I������
	CScene3D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTexAnimation3D::Update()
{
	//�X�V����
	CScene3D::Update();

	//�e�N�X�`���A�j���[�V�����̍X�V
	if (CTexAnimationBase::UpdateAnimation())
	{
		//�e�N�X�`���A�j���[�V��������
		SetAnimation(CalcUV(), CTexture::GetSparateTex_UVSize(GetEffectTex()));
	}

	//�I���̃t���O�������Ă�����
	if (GetEndFlag())
	{
		//����
		//Rerease();
		return;
	}

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTexAnimation3D::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//�`�揈��
	CScene3D::Draw();

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CTexAnimation3D::ShowDebugInfo()
{
#ifdef _DEBUG
	//CDebugProc::Print_Left("pos %.1f %.1f %.1f", GetPosition().x, GetPosition().x, GetPosition().x);
	//CDebugProc::Print_Left("col %.1f %.1f %.1f %.1f", GetColor().r, GetColor().g, GetColor().b, GetColor().a);


#endif //_DEBUG
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CTexAnimation3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot,
	CTexture::SEPARATE_TEX_TYPE type, int nCntSwitch, CScene::OBJ_TYPE objtype, bool bLoop)
{
	//�������m��
	CTexAnimation3D *pTexAnimation = new CTexAnimation3D(objtype);

	//nullcheck
	if (pTexAnimation)
	{
		//������
		pTexAnimation->Init();

		//���������@Scene��
		pTexAnimation->SetPosition(pos);
		pTexAnimation->SetSize(size);
		pTexAnimation->SetRot(rot);
		pTexAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pTexAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		//���������@TexAnimation��
		pTexAnimation->SetLoop(bLoop);
		pTexAnimation->SetTex(type);
		pTexAnimation->SetCntSwitch(nCntSwitch);
	}
}
