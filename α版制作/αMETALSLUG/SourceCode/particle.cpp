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
#define DEFAULT_DAMPING (0.95f)

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CParticle::CParticle()
{
	//������
	m_nLife = 1;
	m_fRadius = 1.0f;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nNumber = 1;
	m_fAlphaDamping = DEFAULT_DAMPING;
	m_fRadiusDamping = DEFAULT_DAMPING;
	m_bDeleteFlag = false;
	m_Textype = CTexture::TEX_EFFECT_PARTICLE;
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
	m_nLife--;
	m_col.a *= m_fAlphaDamping;
	m_fRadius *= m_fRadiusDamping;

	//���C�t��0�ȉ��ɂȂ�����
	if (m_nLife <= 0)
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

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexture::GetTexture(m_Textype));

	//�p�[�e�B�N���̃��X�g�̐���
	for (size_t nCnt = 0; nCnt < m_pParticleList.size(); nCnt++)
	{
		//�}�g���b�N�v�Z
		CHossoLibrary::CalcMatrix(&m_pParticleList[nCnt]->m_Mtx, m_pParticleList[nCnt]->m_pos, m_pParticleList[nCnt]->m_rot);

		//�r���{�[�h�ݒ�
		CHossoLibrary::SetBillboard(&m_pParticleList[nCnt]->m_Mtx);

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
		//�ړ�
		m_pParticleList[nCnt]->m_pos += m_pParticleList[nCnt]->m_move;

		//���_�̍��W
		pVtx[0].pos = D3DXVECTOR3(-m_fRadius, m_fRadius, 0.0f);
		pVtx[1].pos = D3DXVECTOR3(m_fRadius, m_fRadius, 0.0f);
		pVtx[2].pos = D3DXVECTOR3(-m_fRadius, -m_fRadius, 0.0f);
		pVtx[3].pos = D3DXVECTOR3(m_fRadius, -m_fRadius, 0.0f);

		//���_�̍��W
		pVtx[0].col = m_col;
		pVtx[1].col = m_col;
		pVtx[2].col = m_col;
		pVtx[3].col = m_col;

		pVtx += 4;
	}
	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	//���_ID���Z
	m_nVertexID += m_pParticleList.size();
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CParticle::Create(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col, int nNumber,float fSpeed)
{
	//�������m��
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//������
		pParticle->Init();

		//���ݒ�
		pParticle->m_nLife = nLife;
		pParticle->m_fRadius = fRadius;
		pParticle->m_nNumber = nNumber;
		pParticle->m_col = col;

		//�p�[�e�B�N���̐ݒ�
		pParticle->SetParticle(pos, fSpeed);

		//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
		CParticleManager::AddParticleList(std::move(pParticle));
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
//�p�[�e�B�N�������@�ׂ����ݒ�L
//------------------------------------------------------------------------------
void CParticle::DetailsCreate(D3DXVECTOR3 pos, int nLife, float fRadius, D3DXCOLOR col, int nNumber, float fSpeed, float fAlphaDamping, float fRadiusDamping, CTexture::TEX_TYPE textype)
{
	//�������m��
	std::unique_ptr<CParticle> pParticle(new CParticle);

	//nullcheck
	if (pParticle)
	{
		//������
		pParticle->Init();

		//���ݒ�
		pParticle->m_nLife = nLife;
		pParticle->m_fRadius = fRadius;
		pParticle->m_nNumber = nNumber;
		pParticle->m_col = col;
		pParticle->m_fAlphaDamping = fAlphaDamping;
		pParticle->m_fRadiusDamping = fRadiusDamping;
		pParticle->m_Textype = textype;

		//�p�[�e�B�N���̐ݒ�
		pParticle->SetParticle(pos, fSpeed);

		//�I�u�W�F�^�C�v�ݒ肵��Scene�ɏ��L����n��
		CParticleManager::AddParticleList(std::move(pParticle));
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
void CParticle::SetParticle(D3DXVECTOR3 &pos, float fSpeed)
{
	//�ϐ��錾
	float fAngleX, fAngleY;
	D3DXVECTOR3 move;

	//�����������
	for (int nCnt = 0; nCnt < m_nNumber; nCnt++)
	{
		//0���Z�h�~
		if(fSpeed <= 0)
		{
			move = ZeroVector3;
		}
		else
		{

			//�p�[�e�B�N���̔�ԋ����������_������
			float fLength = (float)(rand() % (int)fSpeed);

			//360�x�����_�� 3.14 - 3.14
			fAngleX = CHossoLibrary::Random_PI();
			fAngleY = CHossoLibrary::Random_PI();

			//�ړ��̕�����ݒ�
			move = D3DXVECTOR3(sinf(fAngleY) * sinf(fAngleX) * fLength,
								cosf(fAngleX) * cosf(fAngleY) * fLength,
								sinf(fAngleY) * cosf(fAngleX) * fLength);
		}

		//�p�[�e�B�N������
		std::unique_ptr<COneParticle>pOneParticle = COneParticle::Create(pos, move, ZeroVector3);

		//�z��ɒǉ�
		m_pParticleList.emplace_back(std::move(pOneParticle));

	}
}