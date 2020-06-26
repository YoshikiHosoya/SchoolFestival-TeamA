//------------------------------------------------------------------------------
//
//�G�t�F�N�g�A�j���[�V����2D����  [effectanimation2D.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "effectanimation2D.h"
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
CEffectAnimation2D::CEffectAnimation2D()
{
	//������
	m_nPatternAnim = 0;
	m_nCntAnim = 0;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CEffectAnimation2D::~CEffectAnimation2D()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CEffectAnimation2D::Init()
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
void CEffectAnimation2D::Uninit()
{
	//�I������
	CScene2D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CEffectAnimation2D::Update()
{
	//�J�E���^�[��i�߂�
	m_nCntAnim++;

	//2�t���[�����Ƃ�
	if (m_nCntAnim % m_nCntSwitch == 0)
	{
		//�p�^�[����i�߂�
		m_nPatternAnim++;

		//�Ō�̃p�^�[���܂Ői�񂾎�
		if (m_nPatternAnim >= CTexture::GetSparateTex_UVCnt(m_Type).x *  CTexture::GetSparateTex_UVCnt(m_Type).y)
		{
			//�J��
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

	//�X�V����
	CScene2D::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CEffectAnimation2D::Draw()
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
void CEffectAnimation2D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CEffectAnimation2D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, CTexture::SEPARATE_TEX_TYPE type, float fAngle, int nCntSwitch, OBJTYPE objtype)
{
	//�������m��
	std::unique_ptr<CEffectAnimation2D> pEffectAnimation(new CEffectAnimation2D);

	//nullcheck
	if (pEffectAnimation)
	{
		//������
		pEffectAnimation->Init();

		//������
		pEffectAnimation->m_Type = type;
		pEffectAnimation->BindTexture(CTexture::GetSeparateTexture(type));
		pEffectAnimation->SetPos(pos);
		pEffectAnimation->SetSize(size);
		pEffectAnimation->SetAnimation(ZeroVector2, CTexture::GetSparateTex_UVSize(type));
		pEffectAnimation->SetAngle(fAngle);
		pEffectAnimation->m_nCntSwitch = nCntSwitch;

		//�I�u�W�F�^�C�v�ǉ�����Scene�ɒǉ�
		pEffectAnimation->SetObjType(objtype);
		pEffectAnimation->AddUniqueList(std::move(pEffectAnimation));
	}
}
