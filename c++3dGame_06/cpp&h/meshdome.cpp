// ----------------------------------------
//
// ���b�V���h�[�������̐���[meshdome.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "meshdome.h"
#include "game.h"
#include "scene.h"
#include "debugproc.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MESHDOME_ROTMOVE (0.01f)				// �p�x�̈ړ���
#define MESHDOME_SIZE (100.0f)					// �T�C�Y

// ----------------------------------------
//
// �O���[�o���ϐ�
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CMeshdome::m_pTex[TYPE_MAX] = {};

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CMeshdome::CMeshdome() : CScene(ACTOR_MESHDOME, LAYER_3DOBJECT)
{
	/* �ϐ��̏����� */
	// ��]��
	m_pVtxBuff = NULL;
	m_pIndex = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nNumberVertex = 4;
	m_nNumIndex = 4;
	m_nNumPolygon = 2;
	m_nBlock_Width = 1;
	m_nBlock_Depth = 1;
	m_type = TYPE_NORMAL;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CMeshdome::~CMeshdome()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CMeshdome::Init(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 VecA, VecB;					// �x�N�g��
	D3DXVECTOR3 Cross[2000];				// �O��
	// �u���b�N�`��̌��_�̏����ݒ�
	m_OriginBlock = D3DXVECTOR3(
		m_size.x * -0.5f * m_nBlock_Width,
		0.0f,
		m_size.z * 0.5f * m_nBlock_Depth);
	// �����_���E�C���f�b�N�X�E�|���S���̏����ݒ�(�v�Z)
	m_nNumberVertex =
		(m_nBlock_Depth + 1) * (m_nBlock_Width + 1);
	m_nNumIndex =
		(m_nBlock_Width + 1) * 2 * m_nBlock_Depth +
		2 * (m_nBlock_Depth - 1);
	m_nNumPolygon =
		m_nBlock_Depth * m_nBlock_Width * 2 +
		4 * (m_nBlock_Depth - 1);

	// ���_���W�̐���
	MakeVertex(pDevice);
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CMeshdome::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CMeshdome::Update(void)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���g
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// �ϐ��錾
	int nCountDirect;
	int nCountWidth;

			//���_�ݒ� //
			//�s���[�v
	for (nCountDirect = 0; nCountDirect < m_nBlock_Depth + 1; nCountDirect++)
	{
		// �񃋁[�v
		for (nCountWidth = 0; nCountWidth < m_nBlock_Width + 1; nCountWidth++)
		{
			// �e�N�X�`���[�̐ݒ�
			pVtx[0].tex = pVtx[0].tex +
				D3DXVECTOR2(
					1.0f / m_nBlock_Width * 0.1f,
					0.0f);
			// �F�ݒ�
			pVtx[0].col = m_col;

			// �|�C���g���킹
			pVtx++;
		}
	}
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CMeshdome::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// ��]�E�ʒu�̌v�Z�p�ϐ�
	D3DXMATRIX mtxRot, mtxTrans;

	// ���[���h�}�g���b�N�X�̏�����(�P�ʍs��ɂ��邽��)
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f //
	// ���[�s�b�`���[���ɂ���]�s��쐬(y,x,z)
	D3DXMatrixRotationYawPitchRoll(&mtxRot,	// �����̓��ꕨ
		m_rot.y, m_rot.x, m_rot.z);			// ���ꂼ��̉�]��
	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��]�s��)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,				// 2
		&mtxRot);					// 3
	// ���s�ړ��s��쐬(�I�t�Z�b�g)
	D3DXMatrixTranslation(&mtxTrans,// �����̓��ꕨ
		m_pos.x, m_pos.y, m_pos.z);	// ���ꂼ��̈ړ���
	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:�ړ��s��)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,				// 2
		&mtxTrans);					// 3

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@���f�[�^�X�g���[����ݒ�
	pDevice->SetIndices(
		m_pIndex);

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(
		0,
		m_pTex[m_type]);

	// �|���S���̕`��
	pDevice->DrawIndexedPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		0,
		m_nNumberVertex,
		0,
		m_nNumPolygon);
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CMeshdome::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���[��
	char cTex[TYPE_MAX][128] =
	{
		"data/TEXTURE/Effect/effect05.png",
		"data/TEXTURE/Effect/effect05.png",
		"data/TEXTURE/Effect/effect06.png",
		"data/TEXTURE/Effect/effect06.png",
	};

	// �e�N�X�`���[�ݒ�
	for (int nCntTex = 0; nCntTex < TYPE_MAX; nCntTex++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCntTex], &m_pTex[nCntTex]);
	}

	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CMeshdome::UnLoad(void)
{
	// �e�N�X�`���̊J��
	for (int nCntTex = 0; nCntTex < TYPE_MAX; nCntTex++)
	{
		if (m_pTex[nCntTex] != NULL)
		{
			m_pTex[nCntTex]->Release();
			m_pTex[nCntTex] = NULL;
		}
	}
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CMeshdome * CMeshdome::Create(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 size,
	D3DXVECTOR3 rot,
	D3DXCOLOR	col,
	int nWidth,
	int nDepth,
	TYPE type
)
{
	// �ϐ��錾
	CMeshdome * pMeshdome;		// �V�[��2D�N���X
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pMeshdome = new CMeshdome();
	// �ʒu���
	pMeshdome->m_pos = pos;
	// �T�C�Y���
	pMeshdome->m_size = size;
	// ��]���
	pMeshdome->m_rot = rot;
	// �F���
	pMeshdome->m_col = col;
	// ���u���b�N
	pMeshdome->m_nBlock_Width = nWidth;
	// �c�u���b�N
	pMeshdome->m_nBlock_Depth = nDepth;
	// �^�C�v
	pMeshdome->m_type = type;
	// ����������
	pMeshdome->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pMeshdome;
}

// ----------------------------------------
// �F���ݒ�
// ----------------------------------------
void CMeshdome::SetCol(D3DXCOLOR col)
{
	m_col = col;
}

// ----------------------------------------
// ���_���W�̐���
// ----------------------------------------
void CMeshdome::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;			// ���_���ւ̃|�C���g
	WORD * pIdx;				// �C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	D3DXVECTOR3 VecA, VecB;		// �x�N�g��
	int nCountDirect;			// �c�̃J�E���g
	int nCountWidth;			// ���̃J�E���g
	int nCntBlock = 0;
	float fAngle;				// y�̊p�x
	float fRadian;				// y�̃��W�A���l
	D3DXVECTOR3 Cross[2000];	// �O��

	// �p�x�̌v�Z
	fAngle = D3DX_PI * 2 / m_nBlock_Width;

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * m_nNumberVertex,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// �C���f�b�N�X�o�b�t�@�̐���
	pDevice->CreateIndexBuffer(sizeof(WORD) *
		m_nNumIndex,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIndex,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	//���_�ݒ� //
	//�s���[�v
	for (nCountDirect = 0; nCountDirect < m_nBlock_Depth + 1; nCountDirect++)
	{
		// �񃋁[�v
		for (nCountWidth = 0; nCountWidth < m_nBlock_Width + 1; nCountWidth++)
		{
			// ���W�A���l
			fRadian = fAngle * nCountWidth;
			fRadian = CCalculation::Rot_One_Limit(fRadian);
			// ���_���W�̐ݒ�
			pVtx[0].pos =
				D3DXVECTOR3(
					(sinf(fRadian) * m_size.x),
					m_size.y * nCountDirect,
					(cosf(fRadian) * m_size.z));
			// �@���x�N�g���̐ݒ�
			//pVtx[0].nor = pVtx[0].pos;
			//D3DXVec3Normalize(&pVtx[0].nor, &pVtx[0].nor);

			// �J���[�̐ݒ�
			pVtx[0].col = m_col;

			// �e�N�X�`���[�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(
				1.0f / m_nBlock_Width * nCountWidth,
				1.0f / m_nBlock_Depth * (m_nBlock_Depth - nCountDirect)
			);

			// �|�C���g���킹
			pVtx++;
		}
	}
	pVtx -= m_nNumberVertex;
	// �|���S�����Ƃ̖@���̐ݒ�
	for (int nCntDepth = 0; nCntDepth < m_nBlock_Depth; nCntDepth++, nCntBlock++)
	{
		for (int nCntWidth = 0; nCntWidth < m_nBlock_Width; nCntWidth++, nCntBlock++)
		{
			// �x�N�g��
			VecA = pVtx[nCntBlock + m_nBlock_Width + 2].pos - pVtx[nCntBlock].pos;
			VecB = pVtx[nCntBlock + m_nBlock_Width + 1].pos - pVtx[nCntBlock].pos;
			// �O�όv�Z
			Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2] = CCalculation::Cross_product(VecA, VecB);
			// ���K��
			D3DXVec3Normalize(&Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2], &Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2]);
			// �x�N�g��
			VecA = pVtx[nCntBlock + 1].pos - pVtx[nCntBlock].pos;
			VecB = pVtx[nCntBlock + m_nBlock_Width + 2].pos - pVtx[nCntBlock].pos;
			// �O�όv�Z
			Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2 + 1] = CCalculation::Cross_product(VecA, VecB);
			// ���K��
			D3DXVec3Normalize(&Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2 + 1], &Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2 + 1]);
			// ����
			pVtx[nCntBlock].nor += Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2] + Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2 + 1];
			// �E��
			pVtx[nCntBlock + 1].nor += Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2 + 1];
			// ����
			pVtx[nCntBlock + m_nBlock_Width + 1].nor += Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2];
			// �E��
			pVtx[nCntBlock + m_nBlock_Width + 2].nor += Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2] + Cross[nCntWidth * 2 + nCntDepth * m_nBlock_Width * 2 + 1];
		}
	}
	nCntBlock = 0;
	// ���_�@���̐ݒ�
	for (int nCntDepth = 0; nCntDepth < m_nBlock_Depth + 1; nCntDepth++, nCntBlock++)
	{
		for (int nCntWidth = 0; nCntWidth < m_nBlock_Width + 1; nCntWidth++, nCntBlock++)
		{
			// �ŏ�
			if (nCntDepth == 0 && nCntWidth == 0)
			{
				pVtx[0].nor /= 2;
			}
			// �Ō�
			else if (nCntDepth == m_nBlock_Depth && nCntWidth == m_nBlock_Width)
			{
				pVtx[0].nor /= 2;
			}
			// 1�s�̗�̍Ō�
			else if (nCntDepth == 0 && nCntWidth == m_nBlock_Width)
			{
			}
			// �Ō�s�̗�̍ŏ�
			else if (nCntDepth == m_nBlock_Depth && nCntWidth == 0)
			{
			}
			// �ŏ��̍s�܂��͍Ō�̍s
			else if (nCntDepth == 0 || nCntDepth == m_nBlock_Depth)
			{
				pVtx[0].nor /= 3;
			}
			// �ŏ��̗�܂��͍Ō�̗�
			else if (nCntWidth == 0 || nCntWidth == m_nBlock_Width)
			{
				pVtx[0].nor /= 3;
			}
			// ����ȊO
			else
			{
				pVtx[0].nor /= 6;
			}
			pVtx++;
		}
	}

	// �A�����b�N
	m_pVtxBuff->Unlock();

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pIndex->Lock(0, 0, (void **)&pIdx, 0);

	// �c�u���b�N��
	for (nCountDirect = 0; nCountDirect < m_nBlock_Depth; nCountDirect++)
	{
		// �Q��ڂ̃��[�v�ȍ~
		if (nCountDirect >= 1)
		{
			// �k�ރ|���S�����̒��_�ǉ�
			pIdx[0] = nCountDirect * (m_nBlock_Width + 1) + m_nBlock_Width + 1;

			// �C���f�b�N�X�̃|�C���g���킹
			pIdx++;
		}

		// ���u���b�N�̒��_��
		for (nCountWidth = 0; nCountWidth < m_nBlock_Width + 1; nCountWidth++)
		{
			// �`�揇�Ԃ̃C���f�b�N�X
			pIdx[0] = nCountDirect * (m_nBlock_Width + 1) + nCountWidth + m_nBlock_Width + 1;
			pIdx[1] = nCountDirect * (m_nBlock_Width + 1) + nCountWidth;

			// �C���f�b�N�X�̃|�C���g���킹
			pIdx += 2;
		}

		// �k�ރ|���S�������K�v������ꍇ
		if (nCountDirect < m_nBlock_Depth - 1)
		{
			// �k�ރ|���S�����̒��_�ǉ�
			pIdx[0] = nCountDirect * (m_nBlock_Width + 1) + m_nBlock_Width;
			// �C���f�b�N�X�̃|�C���g���킹
			pIdx++;
		}
	}

	// �A�����b�N
	m_pIndex->Unlock();
}
