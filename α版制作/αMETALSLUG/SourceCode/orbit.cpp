//------------------------------------------------------------------------------
//
//�O�Տ���  [orbit.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "orbit.h"
#include "manager.h"
#include "renderer.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DELETE_INTERVAL (MAX_ORBIT_LENGTH / 2)	//�폜�����Ă΂�Ă��������܂ł̃C���^�[�o��
#define TRANSPARENT_VALUE (0.06f)				//a�l���Z����l

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
COrbit::COrbit()
{
	//������
	m_nLife = 1;
	m_coldefault = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_bDeleteFlag = false;
	m_pVtxBuff = nullptr;

	m_posOffset = ZeroVector3;

	for (int nCnt = 0; nCnt < MAX_ORBIT_LENGTH; nCnt++)
	{
		//������
		m_posVertex[nCnt] = ZeroVector3;
		m_col[nCnt] = m_coldefault;
	}
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
COrbit::~COrbit()
{
	//nullcheck
	if (m_pVtxBuff)
	{
		//���_�o�b�t�@�̊J��
		m_pVtxBuff->Release();
		m_pVtxBuff = nullptr;
	}
}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT COrbit::Init()
{

	//�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * MAX_ORBIT_LENGTH,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		nullptr);

	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_ORBIT_LENGTH; nCnt++)
	{
		//���_�̍��W
		pVtx[nCnt].pos = ZeroVector3;

		//�@��
		pVtx[nCnt].nor = D3DXVECTOR3(0.0f,-1.0f,0.0f);

		//���_�̐F
		pVtx[nCnt].col = m_coldefault;

		//�e�N�X�`�����W
		switch (nCnt % 2)
		{
		case 0:
			pVtx[nCnt].tex = D3DXVECTOR2(0.0f, 1.0f);
			break;
		case 1:
			pVtx[nCnt].tex = D3DXVECTOR2(1.0f, 1.0f);
			break;
		}
	}
	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void COrbit::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void COrbit::Update()
{
	//�t���O�m�F
	if (m_bDeleteFlag)
	{
		//�̗�
		m_nLife--;

		//���C�t��0�ȉ��ɂȂ�����
		if (m_nLife <= 0)
		{
			//����
			Rerease();
			return;
		}
	}

	//���_����������
	for (int nCnt = MAX_ORBIT_LENGTH - 1; nCnt >= 0; nCnt--)
	{
		//�Ō�̒��_�̓�O��菬�����Ƃ�
		if (nCnt < MAX_ORBIT_LENGTH - 2)
		{
			//2�O�̒��_�����
			m_posVertex[nCnt + 2] = m_posVertex[nCnt];
			m_col[nCnt + 2] = m_col[nCnt];

		}
	}

	//�t���O�m�F
	if (!m_bDeleteFlag)
	{
		//�O�Ս��W�ݒ�
		CalcOrbitPos();
	}
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//���݂���|���S��������
	for (int nCntVtx = 0; nCntVtx < MAX_ORBIT_LENGTH; nCntVtx++)
	{
		//���_���W�X�V
		pVtx[nCntVtx].pos = m_posVertex[nCntVtx];

		//����������
		m_col[nCntVtx].a -= TRANSPARENT_VALUE;

		//�F�����
		pVtx[nCntVtx].col = m_col[nCntVtx];
	}


	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void COrbit::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//���Z����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ALPHABLEND_ADD);

	//Z�e�X�g������Z���C�e�B���O�L��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON);

	//�J�����O����
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_NONE);

	//���C�e�B���OOFF
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_OFF);

	//�v�Z�p�ϐ�
	D3DXMATRIX mtx;

	//�}�g���b�N�X������
	D3DXMatrixIdentity(&mtx);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	//���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	//�e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, CTexture::GetTexture(CTexture::TEX_NONE));

	//�|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP,	//�v���~�e�B�u�̎��
							0,					//�J�n����C���f�b�N�X(���_)
							MAX_ORBIT_LENGTH - 2);	//�|���S���̖���
													//�J�����O����

	//�J�����O��߂�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);

	//���C�e�B���O�����ɖ߂�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);

	//Z�e�X�g�ʏ�
	CManager::GetRenderer()->SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);

	//�ʏ퍇��
	CManager::GetRenderer()->SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void COrbit::DebugInfo()
{
#ifdef _DEBUG

#endif //DEBUG
}

//------------------------------------------------------------------------------
//���W�ݒ�@�O�՗p�̂��
//------------------------------------------------------------------------------
void COrbit::SetOrbit(D3DXVECTOR3 pos01,D3DXVECTOR3 pos02)
{
	//�퓬���W�̑��
	m_posVertex[0] = pos01;
	m_posVertex[1] = pos02;

	//�F�ݒ�
	m_col[0] = m_coldefault;
	m_col[1] = m_coldefault;
}
//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
void COrbit::DeleteOrbit()
{
	//�폜�܂ł̃C���^�[�o���ݒ�
	m_nLife = DELETE_INTERVAL;

	//�t���O��true
	m_bDeleteFlag = true;
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
COrbit *COrbit::Create(D3DXMATRIX *pMtx)
{
	//�ϐ��錾
	COrbit *pOrbit = new COrbit;

	if (pOrbit)
	{
		//������
		pOrbit->Init();
		pOrbit->SetMtx(pMtx);

		//�������W�v�Z
		pOrbit->CalcOrbitPos();

		//���_���W�����ݒ�
		pOrbit->SetDefaultVtxPos();

		//�I�u�W�F�N�g�^�C�v�ݒ�
		pOrbit->SetObjType(OBJTYPE_ORBIT);

	}

	//�v���C���[��Ԃ�
	return pOrbit;
}

//------------------------------------------------------------------------------
//���W�ݒ�
//------------------------------------------------------------------------------
void COrbit::CalcOrbitPos()
{
	//���[���h�}�g���b�N�X�����ɍ��W�ݒ�
	D3DXVECTOR3 pos1 = D3DXVECTOR3(m_pParentMtx->_41, m_pParentMtx->_42, m_pParentMtx->_43);

	D3DXVECTOR3 pos2;
	D3DXVec3TransformCoord(&pos2, &m_posOffset, m_pParentMtx);

	//�O�Ղ̍��W�ݒ�
	SetOrbit(pos1, pos2);
}
//------------------------------------------------------------------------------
//�������W�ݒ�
//------------------------------------------------------------------------------
void COrbit::SetDefaultVtxPos()
{
	//���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCnt = 0; nCnt < MAX_ORBIT_LENGTH; nCnt++)
	{
		//�e�N�X�`�����W
		switch (nCnt % 2)
		{
		case 0:
			//���_�̍��W
			pVtx[nCnt].pos = m_posVertex[nCnt] = m_posVertex[0];

			break;
		case 1:
			//���_�̍��W
			pVtx[nCnt].pos = m_posVertex[nCnt] = m_posVertex[1];

			break;
		default:
			int ndata = 0;
			break;
		}
	}

	//���_�f�[�^���A�����b�N
	m_pVtxBuff->Unlock();
}
