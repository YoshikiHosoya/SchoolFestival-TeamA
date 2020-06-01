//------------------------------------------------------------------------------
//
//2D�Q�[�W����  [gauge_2D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "gauge_2D.h"	
#include "scene2D.h"
#include "manager.h"
#include "renderer.h"

//------------------------------------------------------------------------------
//�}�N����`
//------------------------------------------------------------------------------
#define INTERVAL	(10)

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CGauge_2D::CGauge_2D()
{

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CGauge_2D::~CGauge_2D()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CGauge_2D::Init()
{

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CGauge_2D::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CGauge_2D::Update()
{
	//�Q�[�W�̍X�V
	CGauge::Update();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CGauge_2D::Draw()
{
	//���C�e�B���OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//nullcheck
	if (!m_pScene2DList.empty())
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pScene2DList.size(); nCnt++)
		{
			//�`��
			m_pScene2DList[nCnt]->Draw();
		}
	}

	//���C�e�B���O�����ɖ߂�
	CHossoLibrary::CheckLighting();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CGauge_2D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif // _DEBUG
}

//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::shared_ptr<CGauge_2D> CGauge_2D::Create(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & gaugeSize, int const nMaxLife)
{
	//�ϐ��錾
	std::shared_ptr<CGauge_2D> pGauge = std::make_shared<CGauge_2D>();

	if (pGauge)
	{
		//������7
		pGauge->Init();

		//�Q�[�W�쐬
		pGauge->MakeGauge(pos, gaugeSize);
		pGauge->SetMaxLife(nMaxLife);

		pGauge->SetObjType(OBJTYPE_2DGAUGE);
		pGauge->AddSharedList(pGauge);

		//return
		return pGauge;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�Q�[�W�X�V
//------------------------------------------------------------------------------
void CGauge_2D::UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag)
{
	m_pScene2DList[CGauge::GAUGE_FLAME]->UpdateGauge(0.0f);
	m_pScene2DList[CGauge::GAUGE_GREEN]->UpdateGauge(GreenMag);
	m_pScene2DList[CGauge::GAUGE_RED]->UpdateGauge(RedMag);
	m_pScene2DList[CGauge::GAUGE_BLUE]->UpdateGauge(BlueMag);
}
//------------------------------------------------------------------------------
//���W�ݒ�
//------------------------------------------------------------------------------
void CGauge_2D::SetPos(D3DXVECTOR3 const & pos)
{
	//nullcheck
	if (!m_pScene2DList.empty())
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pScene2DList.size(); nCnt++)
		{
			//���W�ݒ�
			m_pScene2DList[nCnt]->SetPos(pos);
		}
	}
}

//------------------------------------------------------------------------------
//�Q�[�W
//------------------------------------------------------------------------------
void CGauge_2D::MakeGauge(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	//�v�f���J��Ԃ�
	for (int nCnt = 0; nCnt < CGauge::GAUGE_MAX; nCnt++)
	{
		//3D�|���S������
		m_pScene2DList.emplace_back(CScene2D::Create_SelfManagement(pos , size));
	}

	m_pScene2DList[CGauge::GAUGE_FLAME]->SetVtxCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pScene2DList[CGauge::GAUGE_RED]->SetVtxCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_pScene2DList[CGauge::GAUGE_BLUE]->SetVtxCol(D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f));
	m_pScene2DList[CGauge::GAUGE_GREEN]->SetVtxCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

}
