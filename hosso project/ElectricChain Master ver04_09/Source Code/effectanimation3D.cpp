//------------------------------------------------------------------------------
//
//�e�N�X�`���A�j���[�V����  [effectanimation.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "effectanimation3D.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CEffectAnimation3D::CEffectAnimation3D()
{
	//������
	m_nPatternAnim = 0;
	m_nCntAnim = 0;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CEffectAnimation3D::~CEffectAnimation3D()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CEffectAnimation3D::Init()
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
void CEffectAnimation3D::Uninit()
{
	//�I������
	CScene3D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CEffectAnimation3D::Update()
{
	//�J�E���^�[��i�߂�
	m_nCntAnim++;

	//2�t���[�����Ƃ�
	if (m_nCntAnim % m_nCntSwitch == 0)
	{
		//�p�^�[����i�߂�
		m_nPatternAnim++;

		//�p�^�[�����Ō�܂ł�������I���
		if (m_nPatternAnim >= CTexture::GetSparateTex_UVCnt(m_Type).x *  CTexture::GetSparateTex_UVCnt(m_Type).y)
		{
			Release();
			return;
		}

		//UV���W�ݒ�
		D3DXVECTOR2 UV;
		UV.x = m_nPatternAnim % (int)CTexture::GetSparateTex_UVCnt(m_Type).x * CTexture::GetSparateTex_UVSize(m_Type).x;
		UV.y = m_nPatternAnim / (int)CTexture::GetSparateTex_UVCnt(m_Type).x * CTexture::GetSparateTex_UVSize(m_Type).y;

		//�e�N�X�`���A�j���[�V��������
		SetAnimation(UV, CTexture::GetSparateTex_UVSize(m_Type));
	}

	//�^�C�v�ɉ����ē�����ς���
	switch (m_Type)
	{
		//��
	case CTexture::SEPARATE_TEX_EFFECT_SMOKE:
		//���X�Ɂ���
		GetPos().y += 2.5f;

		//���X�Ɋg��
		GetSize().x++;
		GetSize().y++;
		SetSize(GetSize());

		break;
	}

	//�X�V����
	CScene3D::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CEffectAnimation3D::Draw()
{
	//�^�C�v�ɉ����ĕ`����@��ݒ�
	//���ƓG�o���͍�������
	if (m_Type == CTexture::SEPARATE_TEX_EFFECT_SMOKE || m_Type == CTexture::SEPARATE_TEX_EFFECT_ENEMY_RESPAWN)
	{
		//���Z����
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_SUB);
	}
	else
	{
		//���Z����
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);
	}

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//�}�g���b�N�X�v�Z
	D3DXMATRIX *pMtx = CScene3D::GetMtxPtr();
	CHossoLibrary::CalcMatrix(pMtx, GetPos(), GetRot());
	CHossoLibrary::SetBillboard_XZ_Only(pMtx);

	//�`�揈��
	CScene3D::DrawSettingMtx(*pMtx);

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CEffectAnimation3D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CEffectAnimation3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::SEPARATE_TEX_TYPE type , D3DXCOLOR col, float fAngle, int nCntSwitch)
{
	//�ϐ��錾
	std::unique_ptr<CEffectAnimation3D> pEffectAnimation3D (new CEffectAnimation3D);

	//3D�A�j���[�V����
	if (pEffectAnimation3D)
	{
		//������
		pEffectAnimation3D->Init();

		//��������
		pEffectAnimation3D->BindTexture(CTexture::GetSeparateTexture(type));
		pEffectAnimation3D->m_Type = type;
		pEffectAnimation3D->SetPos(pos);
		pEffectAnimation3D->SetRot(D3DXVECTOR3(0.0f, 0.0f, fAngle));
		pEffectAnimation3D->SetSize(size);
		pEffectAnimation3D->SetVtxCol(col);
		pEffectAnimation3D->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pEffectAnimation3D->SetBboard(true);
		pEffectAnimation3D->m_nCntSwitch = nCntSwitch;

		//Scene�ŊǗ�
		pEffectAnimation3D->SetObjType(OBJTYPE_EFFECT);
		pEffectAnimation3D->AddUniqueList(std::move(pEffectAnimation3D));

	}
}
