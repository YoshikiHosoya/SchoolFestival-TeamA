// ----------------------------------------
//
// �������̐���[floor.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "floor.h"
#include "game.h"
#include "scene.h"
#include "debugproc.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define FLOOR_ROTMOVE (0.01f)		// �p�x�̈ړ���
#define FLOOR_SIZE (100.0f)			// �T�C�Y
#define FLOOR_TEX "data/TEXTURE/FLOOR/floor.png"				// �e�N�X�`���[
#define FLOOR_ANGLE (D3DX_PI / 1)	// �p�Ȃ̊p�x

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
LPDIRECT3DTEXTURE9 CFloor::m_pTex = NULL;

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CFloor::CFloor() : CScene(ACTOR_FLOOR, LAYER_3DOBJECT)
{
	/* �ϐ��̏����� */
	// ��]��
	m_pVtxBuff = NULL;
	m_pIndex = NULL;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nNumberVertex = 4;
	m_nNumIndex = 4;
	m_nNumPolygon = 2;
	m_nBlock_Width = 1;
	m_nBlock_Depth = 1;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CFloor::~CFloor()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CFloor::Init(void)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���g
	WORD * pIdx;		// �C���f�b�N�X�f�[�^�ւ̃|�C���^���擾
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	D3DXVECTOR3 VecA, VecB;					// �x�N�g��
											//D3DXVECTOR3 Cross0, Cross1_2, Cross3;	// �O��
	int nCountDirect;						// �c�̃J�E���g
	int nCountWidth;						// ���̃J�E���g
	int nCntBlock = 0;
	float fYAngle;							// y�̊p�x
	float fYRadian;							// y�̃��W�A���l
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

	// �p�x�̌v�Z
	fYAngle = 0;
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
			// ���W�A���l(Y)
			fYRadian = fYAngle * nCountDirect;
			fYRadian = CCalculation::Rot_One_Limit(fYRadian);

			// ���_���W�̐ݒ�
			pVtx[0].pos =
				D3DXVECTOR3(
					m_OriginBlock.x +
					(m_size.x * nCountWidth),
					m_OriginBlock.y +
					cosf(fYRadian) * m_size.y,
					m_OriginBlock.z -
					(m_size.z * nCountDirect));
			// �J���[�̐ݒ�
			pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

			// �e�N�X�`���[�̐ݒ�
			pVtx[0].tex = D3DXVECTOR2(1.0f * nCountWidth, 1.0f * nCountDirect);

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

// ----------------------------------------
// �I������
// ----------------------------------------
void CFloor::Uninit(void)
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
void CFloor::Update(void)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���g
	int nCntBlock = 0;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CFloor::Draw(void)
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
		&m_mtxWorld,					// 2
		&mtxRot);							// 3
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
		m_pTex);

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
HRESULT CFloor::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();
	// �e�N�X�`���[�ݒ�
	D3DXCreateTextureFromFile(pDevice, FLOOR_TEX, &m_pTex);
	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CFloor::UnLoad(void)
{
	// �e�N�X�`���̊J��
	if (m_pTex != NULL)
	{
		m_pTex->Release();
		m_pTex = NULL;
	}
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CFloor * CFloor::Create(
	D3DXVECTOR3 pos,
	D3DXVECTOR3 size,
	D3DXVECTOR3 rot,
	int nWidth,
	int nDepth
)
{
	// �ϐ��錾
	CFloor * pFloor;		// �V�[��2D�N���X
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pFloor = new CFloor();
	// �ʒu���
	pFloor->m_pos = pos;
	// �T�C�Y���
	pFloor->m_size = size;
	// ��]���
	pFloor->m_rot = rot;
	// ���u���b�N
	pFloor->m_nBlock_Width = nWidth;
	// �c�u���b�N
	pFloor->m_nBlock_Depth = nDepth;
	// ����������
	pFloor->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pFloor;
}

// ----------------------------------------
// �ڂ��Ă���ʂ̍������擾
// ----------------------------------------
float CFloor::GetHeight(D3DXVECTOR3 pos)
{
	// �ϐ��錾
	VERTEX_3D *pVtx;					// ���_���ւ̃|�C���g
	D3DXVECTOR3 VecA, VecB,VecObject;	// �x�N�g��
	D3DXVECTOR3 Normal;					// �@��
	float fPos_Y = 0;					// ����
	int nCntBlock = 0;					// �u���b�N��
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	// �u���b�N���Ƃ�
	for (int nCntDepth = 0; nCntDepth < m_nBlock_Depth; nCntDepth++)
	{
		for (int nCntWidth = 0; nCntWidth < m_nBlock_Width; nCntWidth++, nCntBlock++)
		{
			// �E��̃|���S��
			if (CCalculation::CrossCollision(&pos, &pVtx[0].pos, &pVtx[1].pos, &pVtx[m_nBlock_Width + 2].pos))
			{
				// �x�N�g��
				VecA = pVtx[m_nBlock_Width + 2].pos - pVtx[1].pos;	// �x�N�g��B
				VecB = pVtx[0].pos - pVtx[1].pos;					// �x�N�g��A
				VecObject = pos - (m_pos + pVtx[1].pos);			// �I�u�W�F�N�g�܂ł̃x�N�g��
				// �����̑��
				fPos_Y = pVtx[1].pos.y;
				// �O��
				D3DXVec3Cross(&Normal, &VecA, &VecB);
				// ���K��
				D3DXVec3Normalize(&Normal, &Normal);
				// ���_�f�[�^�͈̔͂��A�����b�N
				m_pVtxBuff->Unlock();
				// ������Ԃ�
				return fPos_Y + ((-Normal.x * VecObject.x) + (-Normal.z * VecObject.z)) / Normal.y + m_pos.y;
			}
			// �����̃|���S��
			else if (CCalculation::CrossCollision(&pos, &pVtx[m_nBlock_Width + 2].pos, &pVtx[m_nBlock_Width + 1].pos, &pVtx[0].pos))
			{
				// �x�N�g��
				VecA = pVtx[0].pos - pVtx[m_nBlock_Width + 1].pos;						// �x�N�g��A
				VecB = pVtx[m_nBlock_Width + 2].pos - pVtx[m_nBlock_Width + 1].pos;		// �x�N�g��B
				VecObject = pos - (m_pos + pVtx[m_nBlock_Width + 1].pos);				// �I�u�W�F�N�g�܂ł̃x�N�g��
				// �����̑��
				fPos_Y = pVtx[m_nBlock_Width + 1].pos.y;
				// �O��
				D3DXVec3Cross(&Normal, &VecA, &VecB);
				// ���K��
				D3DXVec3Normalize(&Normal, &Normal);
				// ���_�f�[�^�͈̔͂��A�����b�N
				m_pVtxBuff->Unlock();
				// ������Ԃ�
				return fPos_Y + ((-Normal.x * VecObject.x) + (-Normal.z * VecObject.z)) / Normal.y + m_pos.y;
			}
			// ���_���̍X�V
			pVtx++;
		}
		// ���_���̍X�V
		pVtx++;

	}

	// ���_�f�[�^�͈̔͂��A�����b�N
	m_pVtxBuff->Unlock();
	// ������Ԃ�
	return 0.0f;
}