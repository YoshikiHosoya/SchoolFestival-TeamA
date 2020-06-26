//------------------------------------------------------------------------------
//
//�����̍��Տ���  [traces.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "traces.h"
#include "manager.h"
#include "renderer.h"
#include "effectanimation3D.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_LIFE	(1000)
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTraces::CTraces()
{

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTraces::~CTraces()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTraces::Init()
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
void CTraces::Uninit()
{
	//�I������
	CScene3D::Uninit();
}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTraces::Update()
{
	//���������炷
	m_nLife--;

	//�K�x�Ȋ��o��
	if (m_nLife % 25 == 0 && m_nLife > 0)
	{
		//���𔭐�
		CEffectAnimation3D::Create(GetPos(), D3DXVECTOR3(120.0f, 120.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_SMOKE, D3DXCOLOR(0.5f,0.5f,0.5f,0.15f), 0.0f, 20);
	}

	//�������O�ȉ��ɂȂ�����
	if (m_nLife <= 0)
	{
		//a�l�����炵�Ă�
		D3DXCOLOR &rCol = GetCol();
		rCol.a -= 0.01f;
		SetVtxCol(rCol);

		//a�l��0�ȉ��ɂȂ�����
		if(rCol.a <= 0)
		{
			Release();
			return;
		}
	}

	//�X�V����
	CScene3D::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTraces::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_SUB);

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//�`�揈��
	CScene3D::Draw();

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CTraces::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CTraces::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	//�������m��
	std::unique_ptr<CTraces> pTraecs (new CTraces);

	//nullcheck
	if (pTraecs)
	{
		//������
		pTraecs->Init();

		//������
		pTraecs->BindTexture(CTexture::GetTexture(CTexture::TEX_EXPLOSION_TRACE));
		pTraecs->m_nLife = DEFAULT_LIFE;
		pTraecs->SetPos(pos);
		pTraecs->SetSize(size);

		//Scene�ŊǗ�
		pTraecs->SetObjType(OBJTYPE_TRACES);
		pTraecs->AddUniqueList(std::move(pTraecs));

	}
}
