// =====================================================================================================================================================================
//
// �V�[��3D�̏��� [scene3D.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "scene3D.h"			// �C���N���[�h�t�@�C��
#include "renderer.h"
#include "manager.h"
#include "debugproc.h"
#include "player.h"
#include "game.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CScene3D::CScene3D(PRIORITY Priority) : CScene(Priority)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CScene3D::~CScene3D()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CScene3D::Init(void)
{
	// ������
	m_pos				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �ʒu
	m_size				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �ʒu
	m_rot				= D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// ��]
	m_fSlope			= 0.0f;															// �Ζ�
	m_bBillboard		= false;														// �r���{�[�h�t���O
	m_bBothSideCulling	= false;														// ���ʃJ�����O�t���O

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();
	
	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 4,					// �����_���Y�ꂪ��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_3D *pVtx;		// ���_���ւ̃|�C���^

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CScene3D::Uninit(void)
{
	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuff != NULL)
	{
		m_pVtxBuff->Release();
		m_pVtxBuff = NULL;
	}
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CScene3D::Update(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(- m_size.x, + m_size.y, + m_size.z);
	pVtx[1].pos = D3DXVECTOR3(+ m_size.x, + m_size.y, + m_size.z);
	pVtx[2].pos = D3DXVECTOR3(- m_size.x, - m_size.y, - m_size.z);
	pVtx[3].pos = D3DXVECTOR3(+ m_size.x, - m_size.y, - m_size.z);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CScene3D::Draw(void)
{	
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();
	D3DXMATRIX			mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̌v�Z
	CLibrary::MatrixCalculation(&m_mtxWorld, m_rot, m_pos);

	// �r���{�[�h�̂Ƃ�
	if (m_bBillboard)
	{
		CLibrary::BillboardMatrixCalculation(&m_mtxWorld);
	}

	// ���ʃJ�����O����Ƃ�
	if (m_bBothSideCulling)
	{
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);	// ���ʃJ�����O�ݒ�
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);
	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_3D));
	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);
	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);	// ���ʃJ�����O�ݒ�
}

// =====================================================================================================================================================================
//
// �摜�̐ݒ�
//
// =====================================================================================================================================================================
void CScene3D::SetTexture(char TexName[])
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TexName, &m_pTexture);
}

// =====================================================================================================================================================================
//
// ���a�̐ݒ�
//
// =====================================================================================================================================================================
void CScene3D::SetRadius(float fRadius)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y + fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y + fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y - fRadius, 0.0f);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();

}

// =====================================================================================================================================================================
//
// �g�k�̐ݒ�
//
// =====================================================================================================================================================================
void CScene3D::SetScaling(D3DXVECTOR3 size)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-size.x, +size.y, +0.0f);
	pVtx[1].pos = D3DXVECTOR3(+size.x, +size.y, +0.0f);
	pVtx[2].pos = D3DXVECTOR3(-size.x, 0.0f, -0.0f);
	pVtx[3].pos = D3DXVECTOR3(+size.x, 0.0f, -0.0f);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// �A�j���[�V�����̐ݒ�
//
// =====================================================================================================================================================================
void CScene3D::SetAnim(D3DXVECTOR2 UVsize, D3DXVECTOR2 UV)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(UV.x, UV.y);
	pVtx[1].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y);
	pVtx[2].tex = D3DXVECTOR2(UV.x, UV.y + UVsize.y);
	pVtx[3].tex = D3DXVECTOR2(UV.x + UVsize.x, UV.y + UVsize.y);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// �F�̐ݒ�
//
// =====================================================================================================================================================================
void CScene3D::SetColor(D3DXCOLOR col)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(col);
	pVtx[1].col = D3DXCOLOR(col);
	pVtx[2].col = D3DXCOLOR(col);
	pVtx[3].col = D3DXCOLOR(col);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// �e�N�X�`���̕����ݒ�
//
// =====================================================================================================================================================================
void CScene3D::SetTexSeparate(int nSeparate)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f * nSeparate, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f * nSeparate);
	pVtx[3].tex = D3DXVECTOR2(1.0f * nSeparate, 1.0f * nSeparate);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// �摜�̑��
//
// =====================================================================================================================================================================
void CScene3D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

// =====================================================================================================================================================================
//
// �����̎擾
//
// =====================================================================================================================================================================
bool CScene3D::GetHeight(D3DXVECTOR3 &pos)
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	bool bLand = false;

	CPlayer * pPlayer = CManager::GetGame()->GetPlayer();			// �v���C���[�̎擾

	if (pPlayer != NULL)
	{
		D3DXVECTOR3 sizePlayer		= pPlayer->GetSize();			// �v���C���[�̃T�C�Y�擾
		D3DXVECTOR3 posOldPlayer	= pPlayer->GetOldPos();			// �v���C���[�̉ߋ��̈ʒu�擾

		if (m_fSlope < 0)
		{
			m_fSlope *= -1;
		}

		// �v���C���[���ォ����Ƃ�
		if (posOldPlayer.y > pos.y || posOldPlayer.y == pos.y)
		{
			// �u���b�N�͈̔� ( �� )
			if (m_pos.x - m_size.x < pos.x + sizePlayer.x &&
				m_pos.x + m_size.x > pos.x - sizePlayer.x)
			{
				// �u���b�N�͈̔� ( �c )
				if (m_pos.z - m_size.z < pos.z + sizePlayer.z &&
					m_pos.z + m_size.z > pos.z - sizePlayer.z)
				{
					// �u���b�N�͈̔� ( ���� )
					if (m_pos.y - m_fSlope <= pos.y &&
						m_pos.y + m_fSlope > pos.y)
					{

						// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
						m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

						// �x�N�g��
						D3DXVECTOR3 vec1_0 = pVtx[0].pos - pVtx[1].pos;					// ��
						D3DXVECTOR3 vec0_2 = pVtx[2].pos - pVtx[0].pos;					// ��
						D3DXVECTOR3 vec2_1 = pVtx[1].pos - pVtx[2].pos;					// �E�΂ߏ�
						D3DXVECTOR3 vec1_2 = pVtx[2].pos - pVtx[1].pos;					// ���΂߉�
						D3DXVECTOR3 vec2_3 = pVtx[3].pos - pVtx[2].pos;					// �E
						D3DXVECTOR3 vec3_1 = pVtx[1].pos - pVtx[3].pos;					// ��

						// ���_���烂�f���ւ̃x�N�g��
						D3DXVECTOR3 vec0_X = pos - m_pos - pVtx[0].pos;
						D3DXVECTOR3 vec1_X = pos - m_pos - pVtx[1].pos;
						D3DXVECTOR3 vec2_X = pos - m_pos - pVtx[2].pos;
						D3DXVECTOR3 vec3_X = pos - m_pos - pVtx[3].pos;

						// �@��	(��
						D3DXVECTOR3 nor1_0_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						D3DXVECTOR3 nor0_2_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						D3DXVECTOR3 nor2_1_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						// �@��	(�E
						D3DXVECTOR3 nor2_3_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						D3DXVECTOR3 nor3_1_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
						D3DXVECTOR3 nor1_2_X = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

						// �O��	(��
						D3DXVec3Cross(&nor1_0_X, &vec0_X, &vec1_0);
						D3DXVec3Cross(&nor0_2_X, &vec2_X, &vec0_2);
						D3DXVec3Cross(&nor2_1_X, &vec1_X, &vec2_1);
						// �O��	(�E
						D3DXVec3Cross(&nor2_3_X, &vec3_X, &vec2_3);
						D3DXVec3Cross(&nor3_1_X, &vec1_X, &vec3_1);
						D3DXVec3Cross(&nor1_2_X, &vec2_X, &vec1_2);

						CDebugProc::Print("nor1_0_X: %.1f, %.1f, %.1f \n", nor1_0_X.x, nor1_0_X.y, nor1_0_X.z);
						CDebugProc::Print("nor0_2_X: %.1f, %.1f, %.1f \n", nor0_2_X.x, nor0_2_X.y, nor0_2_X.z);
						CDebugProc::Print("nor2_1_X: %.1f, %.1f, %.1f \n", nor2_1_X.x, nor2_1_X.y, nor2_1_X.z);
						CDebugProc::Print("nor2_3_X: %.1f, %.1f, %.1f \n", nor2_3_X.x, nor2_3_X.y, nor2_3_X.z);
						CDebugProc::Print("nor3_1_X: %.1f, %.1f, %.1f \n", nor3_1_X.x, nor3_1_X.y, nor3_1_X.z);
						CDebugProc::Print("nor1_2_X: %.1f, %.1f, %.1f \n\n", nor1_2_X.x, nor1_2_X.y, nor1_2_X.z);

						if (nor1_0_X.y >= 0 && nor0_2_X.y >= 0 && nor2_1_X.y >= 0)
						{
							// ���f���̍����v�Z
							pos.y = m_pos.y + pVtx[0].pos.y + (-pVtx[0].nor.x * (vec0_X.x) - pVtx[0].nor.z * (vec0_X.z)) / pVtx[0].nor.y;
							bLand = true;
						}
						if (nor2_3_X.y >= 0 && nor3_1_X.y >= 0 && nor1_2_X.y >= 0)
						{
							// ���f���̍����v�Z
							pos.y = m_pos.y + pVtx[3].pos.y + (-pVtx[3].nor.x * (vec3_X.x) - pVtx[3].nor.z * (vec3_X.z)) / pVtx[3].nor.y;
							bLand = true;
						}
						// ���_�f�[�^�̃A�����b�N
						m_pVtxBuff->Unlock();
					}
				}
			}
		}
		else
		{
			bLand = false;
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// ��̎Ζʂ̐ݒ�
//
// =====================================================================================================================================================================
void CScene3D::SetSlope(float Slope)
{
	m_fSlope = Slope;

	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(-m_size.x, +Slope, +m_size.z);
	pVtx[1].pos = D3DXVECTOR3(+m_size.x, +Slope, +m_size.z);
	pVtx[2].pos = D3DXVECTOR3(-m_size.x, -Slope, -m_size.z);
	pVtx[3].pos = D3DXVECTOR3(+m_size.x, -Slope, -m_size.z);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// �@���̐ݒ�
//
// =====================================================================================================================================================================
void CScene3D::SetNormal()
{
	// ���_���ւ̃|�C���^
	VERTEX_3D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// �x�N�g��
	m_vec2_0 = pVtx[0].pos - pVtx[2].pos;
	m_vec1_2 = pVtx[1].pos - pVtx[2].pos;
	m_vec2_3 = pVtx[3].pos - pVtx[2].pos;

	// �@��
	m_nor1_2_0	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nor1_2_3	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nor1_2	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �O��
	D3DXVec3Cross(&m_nor1_2_0, &m_vec2_0, &m_vec1_2);
	D3DXVec3Cross(&m_nor1_2_3, &m_vec1_2, &m_vec2_3);

	// ���K��
	D3DXVec3Normalize(&m_nor1_2_0, &m_nor1_2_0);
	D3DXVec3Normalize(&m_nor1_2_3, &m_nor1_2_3);

	// �@���̉��Z
	m_nor1_2 = (m_nor1_2_3 + m_nor1_2_0) / 2;
	// ���K��
	D3DXVec3Normalize(&m_nor1_2, &m_nor1_2);

	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = m_nor1_2_0;
	pVtx[1].nor = m_nor1_2;
	pVtx[2].nor = m_nor1_2;
	pVtx[3].nor = m_nor1_2_3;

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// 3D�|���S���̐���
//
// =====================================================================================================================================================================
CScene3D * CScene3D::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size)
{
	// �ϐ�
	CScene3D *pScene3D;

	// �������̊m��
	pScene3D = new CScene3D(CScene::PRIORITY_MODEL);

	// ������
	pScene3D->Init();

	// �ʒu�̐ݒ�
	pScene3D->SetPos(pos);

	// �T�C�Y�̐ݒ�
	pScene3D->SetSize(size);

	return pScene3D;
}