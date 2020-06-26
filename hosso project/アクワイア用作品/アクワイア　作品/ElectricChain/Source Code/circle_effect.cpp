//------------------------------------------------------------------------------
//
//�~�̃G�t�F�N�g����  [circle_effect.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "renderer.h"
#include "manager.h"
#include "circle_effect.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define BLOCK_NUM			(INTEGER2(8,8))						//���b�V���̃u���b�N��
#define EXPLOSION_DAMAGE	(35)									//�����_���[�W
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CCircle_Effect::CCircle_Effect()
{
	//������
	m_nLife = 0;
	m_fAlphaDampingValue = 0.0f;
	m_fRadiusAddValue = 0.0f;
	m_fWidthAddValue = 0.0f;
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CCircle_Effect::~CCircle_Effect()
{

}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CCircle_Effect::Init()
{
	CMeshCircle::Init();

	return S_OK;

}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CCircle_Effect::Uninit()
{
	CMeshCircle::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CCircle_Effect::Update()
{
	//���C�t��0�ɂȂ��������
	if (m_nLife-- <= 0)
	{
		Release();
	}

	//��]
	GetRot().y += 0.1f;

	//�g�k
	GetRadius() += m_fRadiusAddValue;
	GetWidth() += m_fWidthAddValue;

	//���_�Đݒ�
	ResetVtx(ZeroVector3);

	//�F���擾
	D3DXCOLOR rCol = GetCol();
	rCol.a -= m_fAlphaDampingValue;

	//a�l��0�ɂȂ�����I��
	if (rCol.a < 0)
	{
		Release();
		return;
	}
	//�F�ݒ�
	SetCol(rCol);

	//�X�t�B�A�X�V
	CMeshCircle::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CCircle_Effect::Draw()
{
	//���C�e�B���OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//���ʕ`��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF);

	//�`��
	CMeshCircle::Draw();

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

	//�J�����O�����ɖ߂�
	CHossoLibrary::CheckCulling();

	//�����ɖ߂�
	CHossoLibrary::CheckLighting();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CCircle_Effect::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}
//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::shared_ptr<CCircle_Effect> CCircle_Effect::Create(D3DXVECTOR3 const pos, D3DXCOLOR col, int const nLife, float const fRadius, float const fWidth, int const nSeparate,
														float const fRaidiusAddValue, float const fWidthAddValue, float const fAlphaDanpingValue)
{
	//�������m��
	std::shared_ptr<CCircle_Effect> pCircleEffect(new CCircle_Effect);

	//nullcheck
	if (pCircleEffect)
	{
		//�������@���ݒ�
		pCircleEffect->Init();
		pCircleEffect->SetPos(pos);
		pCircleEffect->SetBlockNum(BLOCK_NUM);
		pCircleEffect->SetRadius(fRadius);
		pCircleEffect->SetWidth(fWidth);
		pCircleEffect->SetBlockNum(INTEGER2(nSeparate, 2));
		pCircleEffect->m_fAlphaDampingValue = fAlphaDanpingValue;
		pCircleEffect->m_fWidthAddValue = fWidthAddValue;
		pCircleEffect->m_fRadiusAddValue = fRaidiusAddValue;
		pCircleEffect->m_nLife = nLife;

		//���_�ݒ�
		pCircleEffect->MakeVertex();
		pCircleEffect->SetNormal();

		//�F�ݒ�
		pCircleEffect->SetCol(col);

		//�p�x�����_��
		pCircleEffect->GetRot().y = CHossoLibrary::Random_PI();

		//�}�g���b�N�X�̌v�Z�@����F�ł����g��Ȃ�
		CHossoLibrary::CalcMatrix(pCircleEffect->GetMtx(), pCircleEffect->GetPos(), pCircleEffect->GetRot());

		//�e�N�X�`������t��
		pCircleEffect->BindTexture(CTexture::GetTexture(CTexture::TEX_SPHEREEXPLOISON));

		//�V�[���ɒǉ�
		pCircleEffect->SetObjType(OBJTYPE_EFFECT_SPHERE);
		pCircleEffect->AddSharedList(pCircleEffect);

		//���_�X�V
		pCircleEffect->Update();
	}

	return pCircleEffect;
}