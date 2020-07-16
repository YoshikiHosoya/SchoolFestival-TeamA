//------------------------------------------------------------------------------
//
//�p�[�e�B�N������  [praticle.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "ParticleManager.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
LPDIRECT3DVERTEXBUFFER9 CParticle::m_pVtxBuff = nullptr;
int CParticle::m_nVertexID = 0;
int COneParticle::nNumParticleAll = 0;

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define PARAMATER_SAVE_FILENAME ("data/Load/EffectParamater/SaveParamater.txt")

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CParticle::CParticle()
{
	//������
	m_bDeleteFlag = false;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CParticle::~CParticle()
{
	//���X�g�̊J��
	m_pParticleList.clear();
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CParticle::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CParticle::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CParticle::Update()
{
	//���C�t�����炷
	m_pParticleParam->UpdateParam();

	if (m_pParticleParam->GetAnimation())
	{
		//�A�j���[�V�����X�V����
		UpdateAnimation();
	}

	//���C�t��0�ȉ��ɂȂ��������A�j���[�V�������I��������
	if (m_pParticleParam->GetLife() <= 0 || CTexAnimationBase::GetEndFlag())
	{
		//����
		m_bDeleteFlag = true;
		return;
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CParticle::Draw()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���C�e�B���OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	if (m_pParticleParam->GetAlphaBlend())
	{
		//���Z����
		CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);
	}

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	m_pParticleParam->GetAnimation() ?
		pDevice->SetTexture(0, CTexture::GetSeparateTexture(m_pParticleParam->GetSeparateTex())) :
		pDevice->SetTexture(0, CTexture::GetTexture(m_pParticleParam->GetTex()));

	//�p�[�e�B�N���̃��X�g�̐���
	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//�}�g���b�N�v�Z
		CHossoLibrary::CalcMatrixAndBillboard(&m_pParticleList[nCnt]->m_Mtx, m_pParticleList[nCnt]->m_pos, m_pParticleList[nCnt]->m_rot);

		//�r���{�[�h�ݒ�
		//CHossoLibrary::SetBillboard(&m_pParticleList[nCnt]->m_Mtx);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &m_pParticleList[nCnt]->m_Mtx);

		//�|���S���`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
			(4 * m_nVertexID) + nCnt * 4,					//�J�n����C���f�b�N�X(���_) (�O��܂ł̕��Ŏg�������_) + ���ݎg����
			2);												//�|���S���̖���
	}

	//���_ID���Z
	m_nVertexID += m_pParticleList.size();

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

	//���C�e�B���OON
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);

}

//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CParticle::ShowDebugInfo()
{

#ifdef _DEBUG

#endif // _DEBUG
}

//------------------------------------------------------------------------------
//���_�X�V
//------------------------------------------------------------------------------
void CParticle::UpdateVertex()
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_ID���i�߂�
	pVtx += (4 * m_nVertexID);

	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//�d�͂�������ꍇ
		if (m_pParticleParam->GetGravity())
		{
			//�������ɗ͂����Z
			m_pParticleList[nCnt]->m_move.y -= m_pParticleParam->GetGravityPower();
		}
		//�ړ�
		m_pParticleList[nCnt]->m_pos += m_pParticleList[nCnt]->m_move;

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x,  m_pParticleParam->GetSize().y, 0.0f);
		pVtx[1].pos = D3DXVECTOR3( m_pParticleParam->GetSize().x,  m_pParticleParam->GetSize().y, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_pParticleParam->GetSize().x, -m_pParticleParam->GetSize().y, 0.0f);
		pVtx[3].pos = D3DXVECTOR3( m_pParticleParam->GetSize().x, -m_pParticleParam->GetSize().y, 0.0f);

		//���_�̍��W
		pVtx[0].col = m_pParticleParam->GetCol();
		pVtx[1].col = m_pParticleParam->GetCol();
		pVtx[2].col = m_pParticleParam->GetCol();
		pVtx[3].col = m_pParticleParam->GetCol();

		//�A�j���[�V�������鎞��UV�v�Z
		if (m_pParticleParam->GetAnimation())
		{
			D3DXVECTOR2 UV = CTexAnimationBase::CalcUV();
			D3DXVECTOR2 UVsize = CTexture::GetSparateTex_UVSize(CTexAnimationBase::GetEffectTex());

			//�e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
			pVtx[1].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y);
			pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + UVsize.y);
			pVtx[3].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y + UVsize.y);
		}
		//�A�j���[�V�������ĂȂ����͒ʏ�
		else
		{
			//�e�N�X�`�����W
			pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}


		pVtx += 4;
	}
	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	//���_ID���Z
	m_nVertexID += m_pParticleList.size();
}

//------------------------------------------------------------------------------
//����
//�p�[�e�B�N���̃N���X��p���Đ���
//------------------------------------------------------------------------------
void CParticle::CreateFromParam(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CParticleParam *pInputParam)
{
	//�������m��
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//������
		pParticle->Init();

		//�p�[�e�B�N���̃p�����[�^�̃������m��
		CParticleParam *pParam = new CParticleParam;

		//nullcheck
		if (pParam)
		{
			//���ݒ�
			//Uniqueptr���g���ƃI�y���[�^�ł��Ȃ��������畁�ʂ̃|�C���^���m�ŃI�y���[�^
			*pParam = pInputParam;

			//�����o�̃|�C���^�Ɋi�[
			pParticle->m_pParticleParam.reset(std::move(pParam));

			//�p�[�e�B�N���̐ݒ�
			pParticle->SetParticle(pos, rot, pParam);

			//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}

//------------------------------------------------------------------------------
//�e�N�X�`���j��
//------------------------------------------------------------------------------
void CParticle::ReleaseVertex()
{
	//nullcheck
	if (m_pVtxBuff)
	{
		//�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}

//------------------------------------------------------------------------------
//���_ID���Z�b�g
//------------------------------------------------------------------------------
void CParticle::ResetVertexID()
{
	m_nVertexID = 0;
}

//------------------------------------------------------------------------------
//�e�L�X�g�������Ƀp�[�e�B�N���쐬
//------------------------------------------------------------------------------
void CParticle::CreateFromText(D3DXVECTOR3 pos, D3DXVECTOR3 rot, CParticleParam::PARTICLE_TEXT type)
{
	//�������m��
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//������
		pParticle->Init();

		//�p�[�e�B�N���̃p�����[�^�̃������m��
		CParticleParam *pParam = new CParticleParam;

		//nullcheck
		if (pParam)
		{
			//���ݒ�
			//Uniqueptr���g���ƃI�y���[�^�ł��Ȃ��������畁�ʂ̃|�C���^���m�ŃI�y���[�^
			*pParam = *CParticleParam::GetDefaultParam(type);

			//�����o�̃|�C���^�Ɋi�[
			pParticle->m_pParticleParam.reset(std::move(pParam));

			//�p�[�e�B�N���̐ݒ�
			pParticle->SetParticle(pos, rot, pParam);

			//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
			CParticleManager::AddParticleList(std::move(pParticle));
		}
	}
}
//------------------------------------------------------------------------------
//���_�o�b�t�@�m��
//------------------------------------------------------------------------------
HRESULT CParticle::MakeVertex()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_PARTICLE * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	//���_��񏉊���
	ResetVertex();

	return S_OK;
}
//------------------------------------------------------------------------------
//���_��񏉊���
//------------------------------------------------------------------------------
void CParticle::ResetVertex()
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
	{
		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		//���_�̓������W
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		//���_�̐F
		pVtx[0].col = WhiteColor;
		pVtx[1].col = WhiteColor;
		pVtx[2].col = WhiteColor;
		pVtx[3].col = WhiteColor;

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		pVtx += 4;
	}
	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}
//------------------------------------------------------------------------------
//�p�[�e�B�N���ݒ�
//------------------------------------------------------------------------------
void CParticle::SetParticle(D3DXVECTOR3 const & pos, D3DXVECTOR3 const & rot, CParticleParam * pParam)
{
	//�ϐ��錾
	float fAngleX, fAngleY;
	D3DXVECTOR3 move;
	float fSpeed;

	//�����������
	for (int nCnt = 0; nCnt < pParam->GetNumber(); nCnt++)
	{
		//0���Z�h�~
		if (pParam->GetSpeed() <= 0)
		{
			move = ZeroVector3;
		}
		else
		{
			pParam->GetSpeedRandom() ?
				fSpeed = float(rand() % 1000 / 1000.0f) * pParam->GetSpeed() :
				fSpeed = pParam->GetSpeed();

			//�p�[�e�B�N���̔�ԋ����������_������
			switch (pParam->GetShape())
			{
			case CParticleParam::SHAPE_SPHERE:

				//360�x�����_�� 3.14 - 3.14
				fAngleX = CHossoLibrary::Random_PI();
				fAngleY = CHossoLibrary::Random_PI();

				//�ړ��̕�����ݒ�
				move = D3DXVECTOR3(sinf(fAngleY) * sinf(fAngleX) * fSpeed,
					sinf(fAngleY) * cosf(fAngleX) * fSpeed,
					cosf(fAngleY) * cosf(fAngleX) * fSpeed);
				break;
			case CParticleParam::SHAPE_CIRCLE_XY:
				//360�x�����_�� 3.14 - 3.14
				fAngleX = CHossoLibrary::Random_PI();
				fAngleY = CHossoLibrary::Random_PI();

				//�ړ��̕�����ݒ�
				move = D3DXVECTOR3(sinf(fAngleX) *  fSpeed,
					cosf(fAngleX) * fSpeed,
					0.0f);
				break;

			case CParticleParam::SHAPE_CONE:
				//�ړ��̕�����ݒ�
				//���_�̖ړI�n�̌v�Z
				fAngleX = pParam->GetRot().x + CHossoLibrary::Random(pParam->GetRange());
				fAngleY = pParam->GetRot().y + CHossoLibrary::Random(pParam->GetRange());

				move = D3DXVECTOR3(-sinf(fAngleY) * cosf(fAngleX) * fSpeed,
					sinf(fAngleX) * fSpeed,
					-cosf(fAngleY) * cosf(fAngleX) * fSpeed);


				break;
			case CParticleParam::SHAPE_LINE:
				//�ړ��̕�����ݒ�
				//���_�̖ړI�n�̌v�Z
				fAngleX = pParam->GetRot().x;
				fAngleY = pParam->GetRot().y;

				fAngleX += rot.x;
				fAngleY += rot.y;

				move = D3DXVECTOR3(-sinf(fAngleY) * cosf(fAngleX) * fSpeed,
					sinf(fAngleX) * fSpeed,
					-cosf(fAngleY) * cosf(fAngleX) * fSpeed);

				break;
			default:
				break;
			}
		}

		if (pParam->GetType() == CParticleParam::EFFECT_LAZER)
		{
			std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, D3DXVECTOR3(0.0f, 0.0f, rot.x));
			//�z��ɒǉ�
			m_pParticleList.emplace_back(std::move(pOneParticle));
		}
		else
		{

			//�p�[�e�B�N������
			std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, D3DXVECTOR3(rot));
			//�z��ɒǉ�
			m_pParticleList.emplace_back(std::move(pOneParticle));
		}
	}

	//�A�j���[�V�����̃p�����[�^�ݒ�
	SetAnimationParam();

	//���_�̍X�V
	UpdateVertex();
}

//------------------------------------------------------------------------------
//�A�j���[�V�����Ɋւ�����ݒ�
//------------------------------------------------------------------------------
void CParticle::SetAnimationParam()
{
	CTexAnimationBase::SetLife(m_pParticleParam->GetLife());
	CTexAnimationBase::SetTex(m_pParticleParam->GetSeparateTex());
	CTexAnimationBase::SetLoop(m_pParticleParam->GetAnimationLoop());
	CTexAnimationBase::SetCntSwitch(m_pParticleParam->GetAnimationCntSwitch());

}
