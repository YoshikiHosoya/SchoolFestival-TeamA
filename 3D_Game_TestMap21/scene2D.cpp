// =====================================================================================================================================================================
//
// �V�[��2D�̏��� [scene2D.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "scene2D.h"			// �C���N���[�h�t�@�C��
#include "renderer.h"
#include "manager.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEX_POSX			(640)			// �摜��x���W
#define TEX_POSY			(360)			// �摜��y���W
#define TEX_SIZEX			(300 / 2)		// ���W�̕�
#define TEX_SIZEY			(220 / 2)		// ���W�̍���

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CScene2D::CScene2D()
{
}

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CScene2D::CScene2D(CScene::PRIORITY Priority) :CScene(Priority)
{

}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CScene2D::~CScene2D()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CScene2D::Init(void)
{
	// ������
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �ʒu
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);								// ��]

	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,					// �����_���Y�ꂪ��
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	VERTEX_2D *pVtx;		// ���_���ւ̃|�C���^

							// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

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
void CScene2D::Uninit(void)
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
void CScene2D::Update(void)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	pVtx[0].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y - m_size.y, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - m_size.x, m_pos.y + m_size.y, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + m_size.x, m_pos.y + m_size.y, 0.0f);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CScene2D::Draw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

// =====================================================================================================================================================================
//
// �A�j���[�V�����̐ݒ�
//
// =====================================================================================================================================================================
void CScene2D::SetAnim(D3DXVECTOR2 UVsize, D3DXVECTOR2 UV)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

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
// ���a�̐ݒ�
//
// =====================================================================================================================================================================
void CScene2D::SetRadius(float fRadius)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y - fRadius, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(m_pos.x - fRadius, m_pos.y + fRadius, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(m_pos.x + fRadius, m_pos.y + fRadius, 0.0f);

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// ��]�̐ݒ�
//
// =====================================================================================================================================================================
void CScene2D::SetRotation(float fAngle, float fLength, float fRot)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�̐ݒ�
	pVtx[0].pos.x = m_pos.x + sinf(-D3DX_PI + fAngle - fRot)	* fLength;
	pVtx[0].pos.y = m_pos.y + cosf(-D3DX_PI + fAngle - fRot)	* fLength;
	pVtx[0].pos.z = 0.0f;

	pVtx[1].pos.x = m_pos.x + sinf(D3DX_PI - fAngle - fRot)	* fLength;
	pVtx[1].pos.y = m_pos.y + cosf(D3DX_PI - fAngle - fRot)	* fLength;
	pVtx[1].pos.z = 0.0f;

	pVtx[2].pos.x = m_pos.x + sinf(-fAngle - fRot)			* fLength;
	pVtx[2].pos.y = m_pos.y + cosf(-fAngle - fRot)			* fLength;
	pVtx[2].pos.z = 0.0f;

	pVtx[3].pos.x = m_pos.x + sinf(fAngle - fRot)			* fLength;
	pVtx[3].pos.y = m_pos.y + cosf(fAngle - fRot)			* fLength;
	pVtx[3].pos.z = 0.0f;

	// ���_�f�[�^�̃A�����b�N
	m_pVtxBuff->Unlock();
}

// =====================================================================================================================================================================
//
// �F�̐ݒ�
//
// =====================================================================================================================================================================
void CScene2D::SetCol(D3DXCOLOR col)
{
	// ���_���ւ̃|�C���^
	VERTEX_2D *pVtx;

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
// �摜�̑��
//
// =====================================================================================================================================================================
void CScene2D::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;
}

// =====================================================================================================================================================================
//
// 2D�|���S���̐���
//
// =====================================================================================================================================================================
CScene2D * CScene2D::Create()
{
	// �ϐ�
	CScene2D *pScene2D;

	// �������̊m��
	pScene2D = new CScene2D(CScene::PRIORITY_UI);

	return pScene2D;
}