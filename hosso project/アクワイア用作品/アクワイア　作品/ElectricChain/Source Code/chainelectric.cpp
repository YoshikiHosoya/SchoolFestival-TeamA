//------------------------------------------------------------------------------
//
//�A���̓d��  [chainelectric.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "chainelectric.h"
#include "manager.h"
#include "renderer.h"
#include "sound.h"
#include "effectanimation3D.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CChainElectric::CChainElectric()
{
	//������
	m_pos = ZeroVector3;
	m_size = ZeroVector3;
	m_rot = ZeroVector3;
	m_col = WhiteColor;
	m_nPatternAnim = 0;
	m_nCntAnim = 0;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CChainElectric::~CChainElectric()
{
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CChainElectric::Init()
{
	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CChainElectric::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CChainElectric::Update()
{
	//���C�t��0�ɂȂ��������
	if (m_nLife-- < 0)
	{
		Release();
		return;
	}

	//�J�E���^�[��i�߂�
	m_nCntAnim++;

	//2�t���[�����Ƃ�
	if (m_nCntAnim % 1 == 0)
	{
		//�p�^�[����i�߂�
		m_nPatternAnim++;
		//�I��
		if (m_nPatternAnim >= CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x *  CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y)
		{
			Release();
			return;
		}

		//UV���W�ݒ�
		D3DXVECTOR2 UV;
		UV.x = m_nPatternAnim % (int)CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x * CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x;
		UV.y = m_nPatternAnim / (int)CTexture::GetSparateTex_UVCnt(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x * CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y;

		//���_���ւ̃|�C���^
		VERTEX_3D *pVtx;

		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		//�e�N�X�`�����W
		pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
		pVtx[1].tex = D3DXVECTOR2(UV.x + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x, UV.y);
		pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y);
		pVtx[3].tex = D3DXVECTOR2(UV.x + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x, UV.y + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y);

		//���_�f�[�^���A�����b�N
		m_pVtxBuff->Unlock();
	}
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CChainElectric::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Z�e�X�g����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF);

	//�J�����O���Ȃ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);

	//�}�g���b�N�X�v�Z
	CHossoLibrary::CalcMatrix(&m_Mtx, m_pos, m_rot);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_Mtx);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexture::GetSeparateTexture(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC));

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,					//�J�n����C���f�b�N�X(���_)
							2);					//�|���S���̖���

	//�J�����O�`�F�b�N
	CHossoLibrary::CheckCulling();

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
}
//------------------------------------------------------------------------------
//�f�o�b�O���\��
//------------------------------------------------------------------------------
void CChainElectric::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void CChainElectric::Create(D3DXVECTOR3 StartPos, D3DXVECTOR3 GoalPos, D3DXVECTOR3 size, D3DXCOLOR col, int nLife)
{
	//�ϐ��錾
	std::unique_ptr<CChainElectric> pChainElectric (new CChainElectric);

	//3D�A�j���[�V����
	if (pChainElectric)
	{
		//������
		pChainElectric->Init();

		//��������
		pChainElectric->m_pos = StartPos;
		pChainElectric->m_size = size;
		pChainElectric->m_col = col;
		pChainElectric->m_size = size;
		pChainElectric->m_nLife = nLife + 3;

		//�v�Z�p
		D3DXVECTOR3 Distance = GoalPos - StartPos;
		float fLength = D3DXVec3Length(&Distance);
		float fAngle = atan2f(Distance.x, Distance.z);

		//����
		fLength = fabs(fLength);

		//�p�x�ݒ�
		pChainElectric->m_pos = StartPos + ((GoalPos - StartPos) / 2);
		pChainElectric->m_rot = (D3DXVECTOR3(0.0f, fAngle + (D3DX_PI * 0.5f), 0.0f));

		//�T�C�Y
		pChainElectric->m_size = (D3DXVECTOR3(fLength * 2.0f, 450.0f,0.0f));

		//�X�^���G�t�F�N�g�@�K���Ƀr���r��������
		CEffectAnimation3D::Create(pChainElectric->m_pos, pChainElectric->m_size * 0.7f, CTexture::SEPARATE_TEX_EFFECT_STANING, WhiteColor,CHossoLibrary::Random_PI(), 2);

		//���Đ�
		CManager::GetSound()->Play(CSound::LABEL_SE_CHAINING_SPARK);

		//���_����
		pChainElectric->MakeVertex();

		//Scene�ŊǗ�
		pChainElectric->SetObjType(OBJTYPE_EFFECT);
		pChainElectric->AddUniqueList(std::move(pChainElectric));

	}
}

//------------------------------------------------------------------------------
//���_����
//------------------------------------------------------------------------------
void CChainElectric::MakeVertex()
{
	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̍��W
	pVtx[0].pos = D3DXVECTOR3(-m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	pVtx[1].pos = D3DXVECTOR3(m_size.x * 0.5f, m_size.y * 0.5f, m_size.z * 0.5f);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);
	pVtx[3].pos = D3DXVECTOR3(m_size.x * 0.5f, -m_size.y * 0.5f, -m_size.z * 0.5f);

	//���_�̓������W
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	//���_�̐F
	pVtx[0].col = m_col;
	pVtx[1].col = m_col;
	pVtx[2].col = m_col;
	pVtx[3].col = m_col;

	//�e�N�X�`�����W
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(0.0f + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 0.0f + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y);
	pVtx[3].tex = D3DXVECTOR2(0.0f + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).x, 0.0f + CTexture::GetSparateTex_UVSize(CTexture::SEPARATE_TEX_EFFECT_CHAINELECTRIC).y);

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}
