//------------------------------------------------------------------------------
//
//�e�N�X�`���A�j���[�V����2D����  [TexAnimation2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "TexAnimation2D.h"
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
CTexAnimation2D::CTexAnimation2D()
{

}
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation2D::CTexAnimation2D(OBJ_TYPE obj) : CScene2D(obj)
{

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTexAnimation2D::~CTexAnimation2D()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTexAnimation2D::Init()
{
	//����������
	if (FAILED(CScene2D::Init()))
	{
		return E_FAIL;
	}
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CTexAnimation2D::Uninit()
{
	//�I������
	CScene2D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTexAnimation2D::Update()
{
	//�X�V����
	CScene2D::Update();

	//�e�N�X�`���A�j���[�V�����̍X�V
	if (CTexAnimationBase::UpdateAnimation())
	{
		//�e�N�X�`���A�j���[�V��������
		SetAnimation(CalcUV(GetPatternAnim(), GetEffectTex()), CTexture::GetSparateTex_UVSize(GetEffectTex()));
	}

	//�I���̃t���O�������Ă�����
	if (GetEndFlag())
	{
		//����
		Rerease();
		return;
	}

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTexAnimation2D::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//�`�揈��
	CScene2D::Draw();

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CTexAnimation2D::ShowDebugInfo()
{
#ifdef _DEBUG
	CDebugProc::Print("pos %.1f %.1f %.1f", GetPosition().x, GetPosition().x, GetPosition().x);
	CDebugProc::Print("col %.1f %.1f %.1f %.1f", GetColor().r, GetColor().g, GetColor().b, GetColor().a);


#endif //_DEBUG
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CTexAnimation2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, D3DXVECTOR3 rot, CTexture::SEPARATE_TEX_TYPE type, int nCntSwitch, CScene::OBJ_TYPE objtype)
{
	//�������m��
	CTexAnimation2D *pTexAnimation = new CTexAnimation2D(objtype);

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
		pTexAnimation->SetTex(type);
		pTexAnimation->SetCntSwitch(nCntSwitch);
	}
}
