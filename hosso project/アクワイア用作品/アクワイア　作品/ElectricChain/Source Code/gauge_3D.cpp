//------------------------------------------------------------------------------
//
//3D�Q�[�W����  [gauge_3D.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "gauge_3D.h"	
#include "scene3D.h"
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
CGauge_3D::CGauge_3D()
{
	m_bFlashing = false;
	m_offset = ZeroVector3;
	m_nCntFlash = 0;
	m_pScene3DList.clear();
}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CGauge_3D::~CGauge_3D()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CGauge_3D::Init()
{

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CGauge_3D::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CGauge_3D::Update()
{
	//�Q�[�W�̍X�V
	CGauge::Update();

	//���C�t��0�ɂȂ�����_�ŏI��
	if (GetLife() <= 0)
	{
		m_bFlashing = false;
	}

	//�_�ŏ��
	if (m_bFlashing)
	{
		//�J�E���^
		m_nCntFlash++;

		//�F�擾���ē_�ł�����
		D3DXCOLOR &rCol = m_pScene3DList[CGauge::GAUGE_BLUE]->GetCol();
		m_nCntFlash % 20 < 10 ?
			rCol.a -= 0.1f :
			rCol.a += 0.1f;

		//�͈͓��ɗ}����
		CHossoLibrary::RangeLimit_Equal_Float(rCol.a, 0.0f, 1.0f);

		//�F�ݒ�
		m_pScene3DList[CGauge::GAUGE_BLUE]->SetVtxCol(rCol);
	}

	//nullcheck
	if (!m_pScene3DList.empty())
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pScene3DList.size(); nCnt++)
		{
			//�X�V
			m_pScene3DList[nCnt]->Update();
		}
	}

}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CGauge_3D::Draw()
{
	//�r���{�[�h�ݒ�
	CHossoLibrary::SetBillboard(&m_Mtx);

	//���C�e�B���OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//nullcheck
	if (!m_pScene3DList.empty())
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pScene3DList.size(); nCnt++)
		{
			if (m_bFlashing && nCnt == CGauge::GAUGE_RED)
			{

			}
			else
			{
				//�`��
				m_pScene3DList[nCnt]->DrawSettingMtx(m_Mtx);
			}
		}
	}

	//���C�e�B���O�����ɖ߂�
	CHossoLibrary::CheckLighting();
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CGauge_3D::ShowDebugInfo()
{
#ifdef _DEBUG

#endif // _DEBUG
}

//------------------------------------------------------------------------------
//����
//------------------------------------------------------------------------------
std::shared_ptr<CGauge_3D> CGauge_3D::Create(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & gaugeSize, D3DXVECTOR3 const & offset, int const nMaxLife,D3DXMATRIX mtx)
{
	//�ϐ��錾
	std::shared_ptr<CGauge_3D> pGauge = std::make_shared<CGauge_3D>();

	if (pGauge)
	{
		//������7
		pGauge->Init();

		//�Q�[�W�쐬
		pGauge->m_offset = offset;
		pGauge->MakeGauge(pos, gaugeSize);
		pGauge->SetMaxLife(nMaxLife);
		pGauge->m_Mtx = mtx;
		pGauge->SetObjType(OBJTYPE_3DGAUGE);
		pGauge->AddSharedList(pGauge);

		//return
		return pGauge;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�Q�[�W�X�V
//------------------------------------------------------------------------------
void CGauge_3D::UpdateGaugeMag(float GreenMag, float RedMag, float BlueMag)
{
	//�Q�[�W�X�V
	m_pScene3DList[CGauge::GAUGE_GREEN]->UpdateGauge(GreenMag);
	m_pScene3DList[CGauge::GAUGE_RED]->UpdateGauge(RedMag);
	m_pScene3DList[CGauge::GAUGE_BLUE]->UpdateGauge(BlueMag);

}
//------------------------------------------------------------------------------
//���W�ݒ�
//------------------------------------------------------------------------------
void CGauge_3D::SetPos(D3DXVECTOR3 const & pos)
{
	//nullcheck
	if (!m_pScene3DList.empty())
	{
		//�v�f���J��Ԃ�
		for (size_t nCnt = 0; nCnt < m_pScene3DList.size(); nCnt++)
		{
			//���W�ݒ�
			m_pScene3DList[nCnt]->SetPos(pos + m_offset);
		}
	}
}

//------------------------------------------------------------------------------
//�Q�[�W
//------------------------------------------------------------------------------
void CGauge_3D::SetMtx(D3DXMATRIX mtx)
{
	//�}�g���b�N�X���
	m_Mtx = mtx;

	//�v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxTrans;

	//�}�g���b�N�X�v�Z
	D3DXMatrixTranslation(&mtxTrans, m_offset.x, m_offset.y, m_offset.z);
	D3DXMatrixMultiply(&m_Mtx, &m_Mtx, &mtxTrans);
}


//------------------------------------------------------------------------------
//�Q�[�W
//------------------------------------------------------------------------------
void CGauge_3D::MakeGauge(D3DXVECTOR3 pos,D3DXVECTOR3 size)
{
	//�v�f���J��Ԃ�
	for (int nCnt = 0; nCnt < CGauge::GAUGE_MAX; nCnt++)
	{
		//3D�|���S������
		m_pScene3DList.emplace_back(CScene3D::Create_SelfManagement(pos + m_offset, size));
		m_pScene3DList[nCnt]->SetBboard(true);
	}

	//�Q�[�W�̐F�ݒ�
	m_pScene3DList[CGauge::GAUGE_FLAME]->SetVtxCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	m_pScene3DList[CGauge::GAUGE_BLUE]->SetVtxCol(D3DXCOLOR(0.2f, 0.2f, 1.0f, 1.0f));
	m_pScene3DList[CGauge::GAUGE_RED]->SetVtxCol(D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	m_pScene3DList[CGauge::GAUGE_GREEN]->SetVtxCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));

}
