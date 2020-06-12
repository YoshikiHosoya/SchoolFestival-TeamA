// =====================================================================================================================================================================
//
// ���b�V���V�����_�[���� [meshcylinder.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "meshcylinder.h"						// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CMeshCylinder::m_pTexture		= NULL;

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
CMeshCylinder::CMeshCylinder()
{
}

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CMeshCylinder::CMeshCylinder(PRIORITY Priority) : CScene(Priority)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CMeshCylinder::~CMeshCylinder()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CMeshCylinder::Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	// �v�Z��
	m_nNumVertex		= POLY_VTX_X * POLY_VTX_Z;							// �����_��
	m_nNumPolygon		= POLY_X * POLY_Z * 2 + 4 * (POLY_Z - 1);			// ���|���S����
	m_nNumIndex			= POLY_VTX_X * 2 * POLY_Z + 2 * (POLY_Z - 1);		// ���C���f�b�N�X��

	// �ʒu�E��]�̏����ݒ�
	m_pos				= D3DXVECTOR3(0.0f, -20.0f, 0.0f);
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col				= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nSize				= INTEGER2(10, 10);

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
void CMeshCylinder::Uninit(void)
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
void CMeshCylinder::Update(void)
{
	float fPosDown = 20.0f;

	// �v���C���[�̏��擾
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();

	// �v���C���[�̈ʒu�ɍ��킹��
	m_pos = D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y - fPosDown, pPlayer->GetPos().z);
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CMeshCylinder::Draw(void)
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

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);					// �X�e���V���o�b�t�@��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�e�X�gon
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);					// ZBuffer��������off
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);				// Z�������@

	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);					//�@���C�e�B���Ooff




	pDevice->SetRenderState(D3DRS_STENCILREF, 0);						// �X�e���V���Q�ƒl(0)
	//pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);					// �F����0��
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���̑Ώ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_ZERO);	// �X�e���V��Z�e�X�g���ɍ��i���Ă���
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_INCR);	// �X�e���V���e�X�g�ɍ��i�AZ�e�X�g�ɕs���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// �X�e���V���e�X�g�ɕs���i

	SetCylinderCol(D3DXCOLOR(1, 0, 0, 1));

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);				// �\�ʃJ�����O�ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);	// �|���S���̕`��



	pDevice->SetRenderState(D3DRS_STENCILREF, 1);						// �X�e���V���Q�ƒl(1)
	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���̑Ώ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_INCR);	// �X�e���V��Z�e�X�g���ɍ��i���Ă���
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_ZERO);	// �X�e���V���e�X�g�ɍ��i�AZ�e�X�g�ɕs���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// �X�e���V���e�X�g�ɕs���i

	SetCylinderCol(D3DXCOLOR(0, 0, 1, 1));


	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʃJ�����O�ݒ�
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);	// �|���S���̕`��




	//pDevice->SetRenderState(D3DRS_STENCILREF, 2);						// �X�e���V���Q�ƒl(2)
	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);				// �F���f�t�H���g�l�ɖ߂�
	//pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���̑Ώ�
	//pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_KEEP);	// �X�e���V��Z�e�X�g���ɍ��i���Ă���
	//pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_KEEP);	// �X�e���V���e�X�g�ɍ��i�AZ�e�X�g�ɕs���i
	//pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_KEEP);	// �X�e���V���e�X�g�ɕs���i

	//pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_nNumVertex, 0, m_nNumPolygon);	// �|���S���̕`��


	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);					// Z�o�b�t�@�������݋֎~


	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);				// �X�e���V���o�b�t�@�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);					// A�o�b�t�@�������݋֎~

}

// =====================================================================================================================================================================
//
// ���b�V���V�����_�[�̐���
//
// =====================================================================================================================================================================
CMeshCylinder * CMeshCylinder::Create(void)
{
	// �ϐ�
	CMeshCylinder *pMeshCylinder;

	// �������̊m��
	pMeshCylinder = new CMeshCylinder(CScene::PRIORITY_MODEL);

	// ������
	pMeshCylinder->Init();

	return pMeshCylinder;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CMeshCylinder::Load(void)
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
void CMeshCylinder::Unload(void)
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
// �摜�̑��
//
// =====================================================================================================================================================================
void CMeshCylinder::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

// =====================================================================================================================================================================
//
// ���_���̍쐬
//
// =====================================================================================================================================================================
void CMeshCylinder::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
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
	// �~���̏���
	// ===================================================

	int nCountDirect	= 0;			// �c�̃J�E���g
	int nCountWidth		= 0;			// ���̃J�E���g
	float fAngle		= 0.0f;			// �p�x
	float fRadian		= 0.0f;			// ���W�A���l
	float fHeight		= 70.0f;		// ����

	// �p�x�̌v�Z
	fAngle = D3DX_PI * 2 / POLY_X;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�s���[�v
	for (nCountDirect = 0; nCountDirect < POLY_VTX_Z; nCountDirect++)
	{
		// �񃋁[�v
		for (nCountWidth = 0; nCountWidth < POLY_VTX_X; nCountWidth++)
		{
			// ���W�A���l
			fRadian = fAngle * nCountWidth;

			// ��]���̍�����������
			if (fRadian < -D3DX_PI)
			{
				fRadian += D3DX_PI * 2;
			}
			if (fRadian > D3DX_PI)
			{
				fRadian += -D3DX_PI * 2;
			}
			

			pVtx[0].pos = D3DXVECTOR3((sinf(fRadian) * (float)m_nSize.x), fHeight * nCountDirect, (cosf(fRadian) * (float)m_nSize.y));

			// �J���[�̐ݒ�
			pVtx[0].col = m_col;

			// �e�N�X�`���[�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(
				1.0f / POLY_X * nCountWidth,
				1.0f / POLY_Z * (POLY_Z - nCountDirect));

			// �|�C���g���킹
			pVtx++;
		}
	}
	pVtx -= m_nNumVertex;

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


// =====================================================================================================================================================================
//
// ���_�F�ύX
//
// =====================================================================================================================================================================
void CMeshCylinder::SetCylinderCol(D3DXCOLOR col)
{

	//�F�ύX
	m_col = col;

	VERTEX_3D	*pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//�s���[�v
	for (int nCountDirect = 0; nCountDirect < POLY_VTX_Z; nCountDirect++)
	{
		// �񃋁[�v
		for (int nCountWidth = 0; nCountWidth < POLY_VTX_X; nCountWidth++)
		{
			// �J���[�̐ݒ�
			pVtx[nCountDirect *POLY_VTX_Z + nCountWidth].col = m_col;

		}
	}

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuff->Unlock();
}

