// ----------------------------------------
//
// �V�[�������̐���[scene_two.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_two.h"
#include "manager.h"

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CScene_TWO::CScene_TWO()
{
	// �ϐ��̏�����
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_rot = 0;
	m_fLengh = 0;
	m_fAngle = 0;
	m_texrot = 0;
}

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CScene_TWO::CScene_TWO(ACTOR actor, LAYER layer) : CScene::CScene(actor,layer)
{
	// �ϐ��̏�����
	m_pTexture = NULL;
	m_pVtxBuff = NULL;
	m_pos = D3DXVECTOR3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0.0f);
	m_rot = 0;
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_fLengh = 0;
	m_fAngle = 0;
	m_texrot = 0;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CScene_TWO::~CScene_TWO()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CScene_TWO::Init(void)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;				// ���_���
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&m_pVtxBuff,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	// �O�p�֐����g���΂߂̒��������߂�
	m_fLengh = sqrtf((m_size.x / 2) * (m_size.x / 2) + (m_size.y / 2) * (m_size.y / 2));
	m_fAngle = atan2f((m_size.x / 2),(m_size.y / 2));

	// ���_���W
	pVtx[0].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, cosf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, cosf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + m_rot) * m_fLengh, cosf(-m_fAngle + m_rot) * m_fLengh, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle + m_rot) * m_fLengh, cosf(m_fAngle + m_rot) * m_fLengh, 0.0f);
	// ���_�̑傫��
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
	// ���_�J���[
	pVtx[0].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[1].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[2].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	pVtx[3].col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	// ���_�e�N�X�`���[
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CScene_TWO::Uninit(void)
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
void CScene_TWO::Update(void)
{
	// �O�p�֐����g���΂߂̒��������߂�
	m_fLengh = sqrtf((m_size.x / 2) * (m_size.x / 2) + (m_size.y / 2) * (m_size.y / 2));
	m_fAngle = atan2f((m_size.x / 2), (m_size.y / 2));
	/*
	float s = atanf(m_fLengh);
	float b = sinf(m_rot - D3DX_PI / 2 - D3DX_PI / 4);
	float c = sqrtf(1 * 1 + 2 * 2);
	D3DXVECTOR3 d = D3DXVECTOR3(sinf(m_rot - D3DX_PI / 2 - D3DX_PI / 4) * m_fLengh, cosf(m_rot - D3DX_PI / 2 - D3DX_PI / 4) * m_fLengh, 0.0f);
	*/

	// �ϐ��錾
	VERTEX_2D *pVtx;				// ���_���

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
 	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// ���_���W
	pVtx[0].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, cosf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, cosf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + m_rot) * m_fLengh, cosf(-m_fAngle + m_rot) * m_fLengh, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle + m_rot) * m_fLengh, cosf(m_fAngle + m_rot) * m_fLengh, 0.0f);
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CScene_TWO::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();


	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(
		0,
		m_pVtxBuff,
		0,
		sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);
	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, m_pTexture);

	// �|���S���`��
	pDevice->DrawPrimitive(
		D3DPT_TRIANGLESTRIP,
		0,
		2);
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CScene_TWO * CScene_TWO::Create()
{
	// �ϐ��錾
	CScene_TWO * pScene_Two;		// �V�[��2D�N���X

	// �������̐���(����->��{�N���X,��->�h���N���X)
	pScene_Two = new CScene_TWO(ACTOR_SCENE_TWO,LAYER_UI);

	// ����������
	pScene_Two->Init();

	// ���������I�u�W�F�N�g��Ԃ�
	return pScene_Two;
}

// ----------------------------------------
// ��������
// ----------------------------------------
void CScene_TWO::SetLengh(D3DXVECTOR2 dist)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;				// ���_���

	// �O�p�֐����g���΂߂̒��������߂�
	m_fLengh = sqrtf((dist.x) * (dist.x) + (dist.y) * (dist.y));
	m_fAngle = atan2f((dist.x), (dist.y));

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	// ���_���W
	pVtx[0].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, cosf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, cosf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(sinf(-D3DX_PI / 2 + m_rot) * dist.x, cosf(-D3DX_PI / 2 + m_rot) * dist.x, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(sinf(D3DX_PI / 2 + m_rot) * dist.x, cosf(D3DX_PI / 2 + m_rot) * dist.x, 0.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();

}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CScene_TWO::SetSize(D3DXVECTOR2 size)
{
	m_size = size;
	// �O�p�֐����g���΂߂̒��������߂�
	m_fLengh = sqrtf((m_size.x) * (m_size.x) + (m_size.y) * (m_size.y));
	m_fAngle = atan2f((m_size.x), (m_size.y));
}

// ----------------------------------------
// �ʒu���ݒ菈��
// ----------------------------------------
void CScene_TWO::SetPosition(D3DXVECTOR3 pos)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;	// ���_���
	// �ʒu���̑��
	m_pos = pos;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// ���_���W
	pVtx[0].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, cosf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, cosf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + m_rot) * m_fLengh, cosf(-m_fAngle + m_rot) * m_fLengh, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle + m_rot) * m_fLengh, cosf(m_fAngle + m_rot) * m_fLengh, 0.0f);
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �Q�[�W�T�C�Y�ݒ菈��
// ----------------------------------------
void CScene_TWO::SetGaugeSize(D3DXVECTOR2 size)
{
	m_size = size;
	// �O�p�֐����g���΂߂̒��������߂�
	m_fLengh = sqrtf((m_size.x) * (m_size.x) + (m_size.y) * (m_size.y));
	m_fAngle = atan2f((m_size.x), (m_size.y));

	// �ϐ��錾
	VERTEX_2D *pVtx;				// ���_���

									// �O�p�֐����g���΂߂̒��������߂�

									// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	// ���_���W
	pVtx[0].pos = m_pos + D3DXVECTOR3(0.0f, cosf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, cosf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(0.0f, cosf(-m_fAngle + m_rot) * m_fLengh, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle + m_rot) * m_fLengh, cosf(m_fAngle + m_rot) * m_fLengh, 0.0f);

	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// ��]���擾����
// ----------------------------------------
void CScene_TWO::SetRot(float frot)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;	// ���_���
						// ��]���̑��
	m_rot = frot;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// ���_���W
	pVtx[0].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, cosf(m_fAngle - D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[1].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, cosf(-m_fAngle + D3DX_PI + m_rot) * m_fLengh, 0.0f);
	pVtx[2].pos = m_pos + D3DXVECTOR3(sinf(-m_fAngle + m_rot) * m_fLengh, cosf(-m_fAngle + m_rot) * m_fLengh, 0.0f);
	pVtx[3].pos = m_pos + D3DXVECTOR3(sinf(m_fAngle + m_rot) * m_fLengh, cosf(m_fAngle + m_rot) * m_fLengh, 0.0f);
	// �A�����b�N
	m_pVtxBuff->Unlock();

}

// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CScene_TWO::SetCol(D3DXCOLOR col)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;	// ���_���

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// ���_�J���[
	pVtx[0].col = col;
	pVtx[1].col = col;
	pVtx[2].col = col;
	pVtx[3].col = col;
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CScene_TWO::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	// �ϐ��錾
	VERTEX_2D *pVtx;	// ���_���

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);
	// ���_�e�N�X�`���[
	pVtx[0].tex = D3DXVECTOR2(first.x, first.y);
	pVtx[1].tex = D3DXVECTOR2(last.x, first.y);
	pVtx[2].tex = D3DXVECTOR2(first.x, last.y);
	pVtx[3].tex = D3DXVECTOR2(last.x, last.y);
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �\���e�N�X�`���[���W��]
// ----------------------------------------
void CScene_TWO::SetRotTex(float frot)
{
	// �O�p�֐����g���΂߂̒��������߂�
	m_fLengh = sqrtf((m_size.x / 2) * (m_size.x / 2) + (m_size.y / 2) * (m_size.y / 2));
	m_fAngle = atan2f((m_size.x / 2), (m_size.y / 2));

	// �ϐ��錾
	VERTEX_2D *pVtx;	// ���_���
						// ��]���̑��
	m_texrot = frot;
	//m_rot = frot;
	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^
	m_pVtxBuff->Lock(
		0,
		0,
		(void **)&pVtx,
		0);

	D3DXVECTOR2 pos = D3DXVECTOR2(m_pos.x,m_pos.y);

	pVtx[0].tex = pos + D3DXVECTOR2(sinf(m_fAngle - D3DX_PI + m_texrot) * m_fLengh, cosf(m_fAngle - D3DX_PI + m_texrot) * m_fLengh);
	pVtx[1].tex = pos + D3DXVECTOR2(sinf(-m_fAngle + D3DX_PI + m_texrot) * m_fLengh, cosf(-m_fAngle + D3DX_PI + m_texrot) * m_fLengh);
	pVtx[2].tex = pos + D3DXVECTOR2(sinf(-m_fAngle + m_texrot) * m_fLengh, cosf(-m_fAngle + m_texrot) * m_fLengh);
	pVtx[3].tex = pos + D3DXVECTOR2(sinf(m_fAngle + m_texrot) * m_fLengh, cosf(m_fAngle + m_texrot) * m_fLengh);
	// �A�����b�N
	m_pVtxBuff->Unlock();
}

// ----------------------------------------
// �T�C�Y���擾����
// ----------------------------------------
D3DXVECTOR2 CScene_TWO::GetSize(void)
{
	return m_size;
}

// ----------------------------------------
// �ʒu���擾����
// ----------------------------------------
D3DXVECTOR3 CScene_TWO::GetPosition(void)
{
	return m_pos;
}

// ----------------------------------------
// �������擾����
// ----------------------------------------
float CScene_TWO::GetLengh(void)
{
	return m_fLengh;
}

// ----------------------------------------
// �e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CScene_TWO::BindTexture(LPDIRECT3DTEXTURE9 p_Tex)
{
	m_pTexture = p_Tex;
}
