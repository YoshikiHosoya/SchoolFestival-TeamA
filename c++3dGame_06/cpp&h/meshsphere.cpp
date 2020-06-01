//-----------------------------------------------------------------------------
//
// ���b�V���X�t�B�A���� [meshsphere.cpp]
// Author : Fujiwara Masato
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-----------------------------------------------------------------------------
#include "meshsphere.h"
#include "game.h"
#include "manager.h"

//-----------------------------------------------------------------------------
// �ÓI�����o�ϐ��̏�����
//-----------------------------------------------------------------------------
CMeshsphere::MESHSPHERE CMeshsphere::m_aMeshSphere[MAX_MESHSPHERE] = {};
LPDIRECT3DTEXTURE9 CMeshsphere::m_pTex = NULL;

//-----------------------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------------------
CMeshsphere::CMeshsphere() :CScene(ACTOR_MESHSPHERE,LAYER_3DOBJECT)
{
}

//-----------------------------------------------------------------------------
// �f�X�g���N�^
//-----------------------------------------------------------------------------
CMeshsphere::~CMeshsphere()
{
}

//-----------------------------------------------------------------------------
// ����
//-----------------------------------------------------------------------------
CMeshsphere * CMeshsphere::create(void)
{
	CMeshsphere *pMeshsphere = new CMeshsphere;
	pMeshsphere->Init();
	return pMeshsphere;
}

//-----------------------------------------------------------------------------
// ����������
//-----------------------------------------------------------------------------
void CMeshsphere::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾


	for (int nCntSphere = 0; nCntSphere < MAX_MESHSPHERE; nCntSphere++)
	{

		// �ʒu�E��]�̏����ݒ�
		m_aMeshSphere[nCntSphere].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aMeshSphere[nCntSphere].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_aMeshSphere[nCntSphere].col = D3DXCOLOR(0.0f, 1.0f, 1.0f, 0.5f);		//�F
		m_aMeshSphere[nCntSphere].fRadius = 0.0f;
		m_aMeshSphere[nCntSphere].nHeightBlock = SEPARATE;
		m_aMeshSphere[nCntSphere].nSeparate = SEPARATE;
		m_aMeshSphere[nCntSphere].bUse = false;
		m_aMeshSphere[nCntSphere].bDisp = false;

		m_aMeshSphere[nCntSphere].nMaxVtx = (m_aMeshSphere[nCntSphere].nSeparate + 1) * (m_aMeshSphere[nCntSphere].nHeightBlock + 1);
		m_aMeshSphere[nCntSphere].nMaxIndex = (m_aMeshSphere[nCntSphere].nSeparate * 2 + 2) * m_aMeshSphere[nCntSphere].nHeightBlock + ((m_aMeshSphere[nCntSphere].nHeightBlock - 1) * 4);
		m_aMeshSphere[nCntSphere].nMaxPolygon = m_aMeshSphere[nCntSphere].nSeparate * 2 * m_aMeshSphere[nCntSphere].nHeightBlock + ((m_aMeshSphere[nCntSphere].nHeightBlock - 1) * 6);

		m_aMeshSphere[nCntSphere].fRot = (D3DX_PI * 2) / m_aMeshSphere[nCntSphere].nSeparate;
		m_aMeshSphere[nCntSphere].fRot2 = (D3DX_PI * 2) / m_aMeshSphere[nCntSphere].nHeightBlock;

		// ���_���̍쐬
		pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_aMeshSphere[nCntSphere].nMaxVtx,	//�m�ۂ���o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,
			FVF_VERTEX_3D,			//���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,
			&m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere,
			NULL);

		// �C���f�b�N�X���̍쐬
		pDevice->CreateIndexBuffer(sizeof(WORD) * m_aMeshSphere[nCntSphere].nMaxIndex,	//�m�ۂ���o�b�t�@�T�C�Y
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,				//���_�t�H�[�}�b�g
			D3DPOOL_MANAGED,
			&m_aMeshSphere[nCntSphere].pIdxBuffMeshSphere,
			NULL);



		VERTEX_3D *pVtx;

		//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

		//���_�̏��
		//�c�̌����J�E���g
		for (int nCntV = 0; nCntV < m_aMeshSphere[nCntSphere].nHeightBlock + 1; nCntV++)
		{
			//�~�̒��_��
			for (int nCntH = 0; nCntH < m_aMeshSphere[nCntSphere].nSeparate + 1; nCntH++)
			{
				//���W
				pVtx[0].pos.x = 0.0f;
				pVtx[0].pos.y = 0.0f;
				pVtx[0].pos.z = 0.0f;

				pVtx[0].nor = pVtx[0].pos;							//�@���͕K�����K��
				D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);		//���K��

				pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		//�F
				pVtx[0].tex = D3DXVECTOR2((float)nCntV, (float)nCntH);	//(�e�N�X�`����UV���W)

				pVtx++;
			}
		}

		//���_�f�[�^���A�����b�N
		m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere->Unlock();

		WORD *pIdx;
		//�C���f�b�N�X�o�b�t�@�͈̔͂����b�N���A�C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
		m_aMeshSphere[nCntSphere].pIdxBuffMeshSphere->Lock(0, 0, (void**)&pIdx, 0);

		//�C���f�b�N�X�̐ݒ�
		for (int nCntV = 0; nCntV < m_aMeshSphere[nCntSphere].nHeightBlock; nCntV++)
		{
			for (int nCntH = 0; nCntH < m_aMeshSphere[nCntSphere].nSeparate + 1; nCntH++)
			{
				pIdx[0] = (m_aMeshSphere[nCntSphere].nSeparate + 1) + nCntH + nCntV * (m_aMeshSphere[nCntSphere].nSeparate + 1);			//��񕪉� + ���i�񂾂� + (�c*���)
				pIdx[1] = nCntH + nCntV * (m_aMeshSphere[nCntSphere].nSeparate + 1);											//���i�񂾂� + (�c*���)

				pIdx += 2;
				if ((nCntH + 1) % (m_aMeshSphere[nCntSphere].nSeparate + 1) == 0 && nCntV < m_aMeshSphere[nCntSphere].nHeightBlock - 1)
				{
					//�k�ރ|���S�����̌v�Z
					pIdx[0] = nCntH + nCntV * (m_aMeshSphere[nCntSphere].nSeparate + 1);
					pIdx[1] = nCntH + nCntV * (m_aMeshSphere[nCntSphere].nSeparate + 1) + 1;
					pIdx[2] = nCntH + nCntV * (m_aMeshSphere[nCntSphere].nSeparate + 1) + 1;
					pIdx[3] = (m_aMeshSphere[nCntSphere].nSeparate + 1) + nCntH + nCntV * (m_aMeshSphere[nCntSphere].nSeparate + 1) + 1;
					pIdx += 4;

				}
			}
		}

		//�C���f�b�N�X�o�b�t�@�̃f�[�^���A�����b�N
		m_aMeshSphere[nCntSphere].pIdxBuffMeshSphere->Unlock();
	}
}

//-----------------------------------------------------------------------------
// �I������
//-----------------------------------------------------------------------------
void CMeshsphere::Uninit(void)
{
	for (int nCntSphere = 0; nCntSphere < MAX_MESHSPHERE; nCntSphere++)
	{
		// ���_�o�b�t�@�̊J��
		if (m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere != NULL)
		{
			m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere->Release();
			m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere = NULL;
		}
	}
}

//-----------------------------------------------------------------------------
// �X�V����
//-----------------------------------------------------------------------------
void CMeshsphere::Update(void)
{
	for (int nCntSphere = 0; nCntSphere < MAX_MESHSPHERE; nCntSphere++)
	{
		if (m_aMeshSphere[nCntSphere].bUse)
		{
			//CollisionSphere(nCntSphere);

			VERTEX_3D *pVtx;

			//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

			//���_�̏��
			//�c�̌����J�E���g
			for (int nCntV = 0; nCntV < m_aMeshSphere[nCntSphere].nHeightBlock + 1; nCntV++)
			{
				//�~�̒��_��
				for (int nCntH = 0; nCntH < m_aMeshSphere[nCntSphere].nSeparate + 1; nCntH++)
				{
					pVtx[0].col = m_aMeshSphere[nCntSphere].col;	//�F

					pVtx++;
				}
			}
			//���_�f�[�^���A�����b�N
			m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere->Unlock();
		}
	}
}

//-----------------------------------------------------------------------------
// �`�揈��
//-----------------------------------------------------------------------------
void CMeshsphere::Draw(void)
{
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX			mtxRot, mtxTrans;		// �v�Z�p


	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �\��(�E���)���J�����O����
	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ���C�e�B���Ooff


	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(
		0,
		m_pTex);

	for (int nCntSphere = 0; nCntSphere < MAX_MESHSPHERE; nCntSphere++)
	{
		if (m_aMeshSphere[nCntSphere].bUse)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&m_aMeshSphere[nCntSphere].mtxWorldMeshSphere);

			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, m_aMeshSphere[nCntSphere].rot.y, m_aMeshSphere[nCntSphere].rot.x, m_aMeshSphere[nCntSphere].rot.z);
			D3DXMatrixMultiply(&m_aMeshSphere[nCntSphere].mtxWorldMeshSphere, &m_aMeshSphere[nCntSphere].mtxWorldMeshSphere, &mtxRot);


			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, m_aMeshSphere[nCntSphere].pos.x, m_aMeshSphere[nCntSphere].pos.y, m_aMeshSphere[nCntSphere].pos.z);
			D3DXMatrixMultiply(&m_aMeshSphere[nCntSphere].mtxWorldMeshSphere, &m_aMeshSphere[nCntSphere].mtxWorldMeshSphere, &mtxTrans);

			// ���[���h�}�g���b�N�X�̐ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &m_aMeshSphere[nCntSphere].mtxWorldMeshSphere);

			//���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetStreamSource(0, m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere, 0, sizeof(VERTEX_3D));

			//�C���f�b�N�X�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
			pDevice->SetIndices(m_aMeshSphere[nCntSphere].pIdxBuffMeshSphere);

			//���_�t�H�[�}�b�g�̐ݒ�
			pDevice->SetFVF(FVF_VERTEX_3D);

			if (m_aMeshSphere[nCntSphere].bDisp)
			{
				// �|���S���̕`��	
				pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,			//�v���~�e�B�u�̎��
					0,
					0,
					m_aMeshSphere[nCntSphere].nMaxIndex,		//���_��
					0,
					m_aMeshSphere[nCntSphere].nMaxPolygon);	//�|���S���̖���
			}
		}
	}

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// �`��
	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ���C�e�B���Oon

																		// �����_�[�X�e�[�g(Z�e�X�g)
	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);					// Z�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);			// Z�e�X�g����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// ����
}

//-----------------------------------------------------------------------------
// �ǂݍ���
//-----------------------------------------------------------------------------
void CMeshsphere::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();

	D3DXCreateTextureFromFile(pDevice, "data/TEXTURE/00_sky.tga", &m_pTex);
}

//-----------------------------------------------------------------------------
// �ǂݍ��񂾂��̂�j��
//-----------------------------------------------------------------------------
void CMeshsphere::Unload(void)
{
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}

//-----------------------------------------------------------------------------
// �z�u
//-----------------------------------------------------------------------------
int CMeshsphere::Set(CONST D3DXVECTOR3 pos, const float fRadius)
{
	int nCntSphere;

	for (nCntSphere = 0; nCntSphere < MAX_MESHSPHERE; nCntSphere++)
	{
		if (!m_aMeshSphere[nCntSphere].bUse)
		{
			// �ʒu�E��]�̏����ݒ�
			m_aMeshSphere[nCntSphere].pos = pos;
			m_aMeshSphere[nCntSphere].fRadius = fRadius;
			m_aMeshSphere[nCntSphere].bUse = true;
			m_aMeshSphere[nCntSphere].bDisp = true;

			m_aMeshSphere[nCntSphere].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
			VERTEX_3D *pVtx;

			//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
			m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

			//���_�̏��
			//�c�̌����J�E���g
			for (int nCntV = 0; nCntV < m_aMeshSphere[nCntSphere].nHeightBlock + 1; nCntV++)
			{
				//�~�̒��_��
				for (int nCntH = 0; nCntH < m_aMeshSphere[nCntSphere].nSeparate + 1; nCntH++)
				{
					//���W
					pVtx[0].pos.x = sinf(m_aMeshSphere[nCntSphere].fRot * nCntH) * sinf(m_aMeshSphere[nCntSphere].fRot2 * nCntV * 0.5f) * m_aMeshSphere[nCntSphere].fRadius;		//�J�����݂����Ȋ�����	
					pVtx[0].pos.y = cosf(m_aMeshSphere[nCntSphere].fRot2 * nCntV * 0.5f) * m_aMeshSphere[nCntSphere].fRadius;							//����
					pVtx[0].pos.z = cosf(m_aMeshSphere[nCntSphere].fRot * nCntH) * sinf(m_aMeshSphere[nCntSphere].fRot2 * nCntV * 0.5f) * m_aMeshSphere[nCntSphere].fRadius;

					pVtx[0].nor = pVtx[0].pos;							//�@���͕K�����K��
					D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);		//���K��

					pVtx[0].tex = D3DXVECTOR2((float)nCntV, (float)nCntH);	//(�e�N�X�`����UV���W)

					pVtx[0].col = m_aMeshSphere[nCntSphere].col;		//�F

					pVtx++;
				}
			}
			//���_�f�[�^���A�����b�N
			m_aMeshSphere[nCntSphere].pVtxBuffMeshSphere->Unlock();
			break;
		}
	}
	return nCntSphere;

}

//-----------------------------------------------------------------------------
// �ʒu�̐ݒ�
//-----------------------------------------------------------------------------
void CMeshsphere::SetPosition(int nIdxCollisionSphere, D3DXVECTOR3 pos)
{
	m_aMeshSphere[nIdxCollisionSphere].pos = pos;

}

//-----------------------------------------------------------------------------
// ��������
//-----------------------------------------------------------------------------
void CMeshsphere::DeleteCollision(int nIdxCollisionSphere)
{
	m_aMeshSphere[nIdxCollisionSphere].fRadius = 0.0f;
	m_aMeshSphere[nIdxCollisionSphere].bUse = false;
	m_aMeshSphere[nIdxCollisionSphere].bDisp = false;
}

//-----------------------------------------------------------------------------
// �X�t�B�A�̔��a�̕ύX
//-----------------------------------------------------------------------------
void CMeshsphere::SetRadius(int nIdxCollisionSphere, float fRadius)
{
	m_aMeshSphere[nIdxCollisionSphere].fRadius = fRadius;
	VERTEX_3D *pVtx;

	//���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_aMeshSphere[nIdxCollisionSphere].pVtxBuffMeshSphere->Lock(0, 0, (void**)&pVtx, 0);

	//���_�̏��
	//�c�̌����J�E���g
	for (int nCntV = 0; nCntV < m_aMeshSphere[nIdxCollisionSphere].nHeightBlock + 1; nCntV++)
	{
		//�~�̒��_��
		for (int nCntH = 0; nCntH < m_aMeshSphere[nIdxCollisionSphere].nSeparate + 1; nCntH++)
		{
			//���W
			pVtx[0].pos.x = sinf(m_aMeshSphere[nIdxCollisionSphere].fRot * nCntH) * sinf(m_aMeshSphere[nIdxCollisionSphere].fRot2 * nCntV * 0.5f) * m_aMeshSphere[nIdxCollisionSphere].fRadius;		//�J�����݂����Ȋ�����	
			pVtx[0].pos.y = cosf(m_aMeshSphere[nIdxCollisionSphere].fRot2 * nCntV * 0.5f) * m_aMeshSphere[nIdxCollisionSphere].fRadius;							//����
			pVtx[0].pos.z = cosf(m_aMeshSphere[nIdxCollisionSphere].fRot * nCntH) * sinf(m_aMeshSphere[nIdxCollisionSphere].fRot2 * nCntV * 0.5f) * m_aMeshSphere[nIdxCollisionSphere].fRadius;

			pVtx++;

		}
	}
	//�C���f�b�N�X�o�b�t�@�̃f�[�^���A�����b�N
	m_aMeshSphere[nIdxCollisionSphere].pIdxBuffMeshSphere->Unlock();

}
