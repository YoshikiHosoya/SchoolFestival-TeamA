// =====================================================================================================================================================================
//
// ���b�V���t�B�[���h���� [meshfield.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "meshfield.h"						// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9 CMeshField::m_pTexture = NULL;

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEXTURE_FILE00		"data/TEXTURE/stone.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define POLY_VTX_X			(POLY_X + 1)				// �|���S���̒��_��	( �� )
#define POLY_VTX_Z			(POLY_Z + 1)				// �|���S���̒��_��	( �c )

#define MAX_RAISE			(5.0f)						// ���
#define WAVE_ANGLE			(10.0f)						// �g�̊p�x

#define WAVE_WIDTH			(240.0f)					// �g�̉�����
#define WAVE_HEIGHT			(3.0f)						// �g�̍�����

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CMeshField::CMeshField()
{
}

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CMeshField::CMeshField(PRIORITY Priority) : CScene(Priority)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CMeshField::~CMeshField()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CMeshField::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �v�Z��
	m_nNumVertex		= POLY_VTX_X * POLY_VTX_Z;							// �����_��
	m_nNumPolygon		= POLY_X * POLY_Z * 2 + 4 * (POLY_Z - 1);			// ���|���S����
	m_nNumIndex			= POLY_VTX_X * 2 * POLY_Z + 2 * (POLY_Z - 1);		// ���C���f�b�N�X��

	// �ʒu�E��]�̏����ݒ�
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nSize				= INTEGER2(100, 100);

	// �@��������
	for (int nCnt = 0; nCnt < MAX_NOR; nCnt++)
	{
		m_aNor[nCnt] = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	// ���_���̍쐬
	MakeVertex(pDevice);
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CMeshField::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{			 
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}

	// �C���f�b�N�X�o�b�t�@�̊J��
	if (m_pIdxBuff != NULL)
	{	   
		m_pIdxBuff->Release();
		m_pIdxBuff = NULL;
	}
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CMeshField::Update(void)
{
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CMeshField::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾
	D3DXMATRIX		mtxRot, mtxTrans;			// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̌v�Z
	CLibrary::MatrixCalculation(&m_mtxWorld, m_rot, m_pos);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetIndices(m_pIdxBuff);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);
}

// =====================================================================================================================================================================
//
// ���b�V���t�B�[���h�̐���
//
// =====================================================================================================================================================================
CMeshField * CMeshField::Create(void)
{
	// �ϐ�
	CMeshField *pMeshField;

	// �������̊m��
	pMeshField = new CMeshField(CScene::PRIORITY_MODEL);

	// ������
	pMeshField->Init();

	return pMeshField;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CMeshField::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE00, &m_pTexture);

	return S_OK;
}

// =====================================================================================================================================================================
//
// �A�����[�h
//
// =====================================================================================================================================================================
void CMeshField::Unload(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture= NULL;
	}
}

// =====================================================================================================================================================================
//
// �����̎擾
//
// =====================================================================================================================================================================
float CMeshField::GetHeight(D3DXVECTOR3 pos)
{
	VERTEX_3D	*pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntExclusion = 0;			// ���O����J�E���g
	int nCntNor = 0;
	int nCntVtx = 0;

	// �u���b�N����
	for (int nCnt = 0; nCnt < (POLY_X * POLY_Z); nCnt++)
	{
		if (nCntVtx == POLY_X + (POLY_VTX_X * nCntExclusion))
		{
			// �J�E���g�A�b�v
			nCntExclusion++;
			nCntVtx++;
			pVtx++;
		}

		// �x�N�g��	(��
		D3DXVECTOR3 vecUp		= pVtx[0].pos - pVtx[POLY_VTX_X].pos ;			// ��
		D3DXVECTOR3 vecDUnder	= pVtx[POLY_VTX_X + 1].pos - pVtx[0].pos;		// �΂߉�
		D3DXVECTOR3 vecLeft		= pVtx[POLY_VTX_X].pos - pVtx[POLY_VTX_X + 1].pos;		// ��

		// �x�N�g��	(�E
		D3DXVECTOR3 vecUnder	= pVtx[POLY_VTX_X + 1].pos - pVtx[1].pos;		// ��
		D3DXVECTOR3 vecDUp		= pVtx[0].pos - pVtx[POLY_VTX_X + 1].pos;			// �΂ߏ�
		D3DXVECTOR3 vecRight	= pVtx[1].pos - pVtx[0].pos;		// �E
								
		// �@��	(�E
		D3DXVECTOR3 norRight0;
		D3DXVECTOR3 norRight1;
		D3DXVECTOR3 norRight2;
		// �@��	(��
		D3DXVECTOR3 norLeft0;
		D3DXVECTOR3 norLeft1;
		D3DXVECTOR3 norLeft2;

		// �v���C���[�ւ̃x�N�g��
		D3DXVECTOR3 vecP0 = pos - m_pos - pVtx[0].pos;
		D3DXVECTOR3 vecP1 = pos - m_pos - pVtx[1].pos;
		D3DXVECTOR3 vecP2 = pos - m_pos - pVtx[POLY_VTX_X].pos;
		D3DXVECTOR3 vecP3 = pos - m_pos - pVtx[POLY_VTX_X + 1].pos;

		// �O��	(�E
		D3DXVec3Cross(&norRight0, &vecUnder, &vecP3);
		D3DXVec3Cross(&norRight1, &vecDUp, &vecP0);
		D3DXVec3Cross(&norRight2, &vecRight, &vecP1);

		// �O��	(��
		D3DXVec3Cross(&norLeft0, &vecUp, &vecP0);
		D3DXVec3Cross(&norLeft1, &vecDUnder, &vecP3);
		D3DXVec3Cross(&norLeft2, &vecLeft, &vecP2);


		CDebugProc::Print("\n\n NorRight0 %.2f\n", norRight0.y);
		CDebugProc::Print(" NorRight1 %.2f\n", norRight1.y);
		CDebugProc::Print(" NorRight2 %.2f\n", norRight2.y);

		CDebugProc::Print("\n\n NorLeft0 %.2f\n", norLeft0.y);
		CDebugProc::Print(" NorLeft1 %.2f\n", norLeft1.y);
		CDebugProc::Print(" NorLeft2 %.2f\n", norLeft2.y);

		// �E�ɏ���Ă���Ƃ�
		if (norRight0.y >= 0 && norRight1.y >= 0 && norRight2.y >= 0)
		{
			// ���f���̍����v�Z
			pos.y = m_pos.y + pVtx[1].pos.y + (-m_aNor[nCntNor + 1].x * (vecP1.x) - m_aNor[nCntNor + 1].z * (vecP1.z)) / m_aNor[nCntNor + 1].y;

			// ���_�f�[�^���A�����b�N����
			m_pVtxBuff->Unlock();

			return pos.y;
		}

		// ���ɏ���Ă���Ƃ�
		if (norLeft0.y >= 0 && norLeft1.y >= 0 && norLeft2.y >= 0)
		{
			// ���f���̍����v�Z
			pos.y =m_pos.y + pVtx[POLY_VTX_X].pos.y + (-m_aNor[nCntNor].x * (vecP2.x) - m_aNor[nCntNor].z * (vecP2.z)) / m_aNor[nCntNor].y;

			// ���_�f�[�^���A�����b�N����
			m_pVtxBuff->Unlock();

			return pos.y;
		}

		// 2�i�߂�
		nCntNor += 2;
		// �J�E���g�A�b�v
		pVtx++;
		nCntVtx++;
	}
	
	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	return pos.y;
}

// =====================================================================================================================================================================
//
// �摜�̑��
//
// =====================================================================================================================================================================
void CMeshField::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

// =====================================================================================================================================================================
//
// ���_���̍쐬
//
// =====================================================================================================================================================================
void CMeshField::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	int nCntZ = 0;
	int nCntX = 0;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * m_nNumVertex,					// �����_���Y�ꂪ��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
	pDevice->CreateIndexBuffer(sizeof(WORD) * m_nNumIndex,					// ���C���f�b�N�X���Y�ꂪ��
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIdxBuff,
		NULL);

	VERTEX_3D	*pVtx;

	// ===================================================
	// ���_���̐ݒ�
	// ===================================================

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntZ = 0; nCntZ < POLY_VTX_Z; nCntZ++)
	{
		for (nCntX = 0; nCntX < POLY_VTX_X; nCntX++)
		{
			// ���_���W�̐ݒ�
			pVtx[0].pos = D3DXVECTOR3(-((float)m_nSize.x * POLY_X / 2) + (float)m_nSize.x * nCntX,
				0.0f,
				((float)m_nSize.y * POLY_Z / 2) - (float)m_nSize.y * nCntZ);

			// ���_�J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`�����W�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCntX, 1.0f * nCntZ);
			pVtx++;
		}
	}
	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	// ===================================================
	// �����I �@���v�Z
	// ===================================================

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	int nCntExclusion = 0;			// ���O����J�E���g
	int nCntNor = 0;
	int nCntVtx = 0;

	// �u���b�N����
	for (int nCnt = 0; nCnt < (POLY_X * POLY_Z); nCnt++)
	{
		if (nCntVtx == POLY_X + (POLY_VTX_X * nCntExclusion))
		{
			// �J�E���g�A�b�v
			nCntExclusion++;
			nCntVtx++;
			pVtx++;
		}
			D3DXVECTOR3 vecU = {};			// ��
			D3DXVECTOR3 vecD = {};			// �΂�
			D3DXVECTOR3 vecR = {};			// �E

			// �x�N�g��
			vecU = pVtx[POLY_VTX_X].pos		- pVtx[0].pos;
			vecD = pVtx[POLY_VTX_X + 1].pos	- pVtx[0].pos;
			vecR = pVtx[1].pos				- pVtx[0].pos;

			// �O��
			D3DXVec3Cross(&m_aNor[nCntNor], &vecD, &vecU);
			D3DXVec3Cross(&m_aNor[nCntNor + 1], &vecR, &vecD);

			// ���K��
			D3DXVec3Normalize(&m_aNor[nCntNor], &m_aNor[nCntNor]);
			D3DXVec3Normalize(&m_aNor[nCntNor + 1], &m_aNor[nCntNor + 1]);

			// ���_�ɖ@�����Z
			// ����
			pVtx[0].nor += m_aNor[nCntNor] + m_aNor[nCntNor + 1];
			// �E��
			pVtx[1].nor += m_aNor[nCntNor + 1];
			// ����
			pVtx[POLY_VTX_X].nor += m_aNor[nCntNor];
			// �E��
			pVtx[POLY_VTX_X + 1].nor += m_aNor[nCntNor] + m_aNor[nCntNor + 1];

			// 2�i�߂�
			nCntNor += 2;
			// �J�E���g�A�b�v
			pVtx++;
			nCntVtx++;

	}
	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
	
	// ===================================================
	// ���_�@������
	// ===================================================

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	for (nCntZ = 0; nCntZ < POLY_VTX_Z; nCntZ++)
	{
		for (nCntX = 0; nCntX < POLY_VTX_X; nCntX++)
		{
			// === ����[ ===
			if (nCntZ == 0 && nCntX == 0)
			{
				pVtx[0].nor = pVtx[0].nor / 2;
			}
			// === �E��[ ===
			else if (nCntZ == 0 && nCntX == POLY_X)
			{
				pVtx[0].nor;
			}
			// === �����[ ===
			else if (nCntZ == POLY_Z && nCntX == 0)
			{
				pVtx[0].nor;
			}
			// === �E���[ ===
			else if (nCntZ == POLY_Z && nCntX == POLY_X)
			{
				pVtx[0].nor = pVtx[0].nor / 2;
			}
			// === ��[ ===
			else if (nCntZ == 0 && nCntX > 0 && nCntX < POLY_X)
			{
				pVtx[0].nor = pVtx[0].nor / 3;
			}
			// === ���[ ===
			else if (nCntZ == POLY_Z && nCntX > 0 && nCntX < POLY_X)
			{
				pVtx[0].nor = pVtx[0].nor / 3;
			}
			// === ���[ ===
			else if (nCntZ > 0 && nCntZ < POLY_Z && nCntX == 0)
			{
				pVtx[0].nor = pVtx[0].nor / 3;
			}
			// === �E�[ ===
			else if (nCntZ > 0 && nCntZ < POLY_Z && nCntX == POLY_X)
			{
				pVtx[0].nor = pVtx[0].nor / 3;
			}
			// === �� ===
			else
			{
				pVtx[0].nor = pVtx[0].nor / 6;
			}
			pVtx++;
		}
	}

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();

	WORD	*pIdx;

	// ===================================================
	// �C���f�b�N�X���̐ݒ�
	// ===================================================

	// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A�C���f�b�N�X�o�b�t�@�ւ̃|�C���^���擾
	m_pIdxBuff->Lock(0, 0, (void**)&pIdx, 0);

	for (nCntZ = 0; nCntZ < POLY_Z; nCntZ++)
	{
		// �ʏ�C���f�b�N�X
		for (nCntX = 0; nCntX < POLY_VTX_X; nCntX++)
		{
			pIdx[0] = POLY_VTX_X + nCntX + (nCntZ * POLY_VTX_X);
			pIdx[1] = nCntX + (nCntZ * POLY_VTX_X);
		
			pIdx += 2;

			// �k�ރ|���S���̌v�Z
			if (nCntX == POLY_X && nCntZ != (POLY_Z - 1))
			{
				pIdx[0] = nCntX + (nCntZ * POLY_VTX_X);
				pIdx[1] = POLY_VTX_X + nCntX + 1 + (nCntZ * POLY_VTX_X);

				pIdx += 2;
			}
		}
	}
	// �C���f�b�N�X�f�[�^���A�����b�N����
	m_pIdxBuff->Unlock();
}