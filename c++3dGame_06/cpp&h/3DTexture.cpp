// ----------------------------------------
//
// 3dtexture�����̐���[3dtexture.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "3dtexture.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 C3DTexture::m_pTexture[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
C3DTexture::C3DTexture() : CScene_THREE::CScene_THREE(ACTOR_3DTEXTURE, LAYER_3DOBJECT)
{
	// �ϐ��̏�����
	m_Type = TYPE_EFFECT_000;
	m_bBillboard = false;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
C3DTexture::~C3DTexture()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void C3DTexture::Init(void)
{
	// �V�[��3D�̏�����
	CScene_THREE::Init();
	CScene_THREE::SetBillboard(m_bBillboard);				// �r���{�[�h
}

// ----------------------------------------
// �I������
// ----------------------------------------
void C3DTexture::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void C3DTexture::Update(void)
{
	if (m_Type == TYPE_EFFECT_000)
	{

	}
	CScene_THREE::SetRot(CScene_THREE::GetRot() + D3DXVECTOR3(0.0f, 0.01f, 0.0f));
	CScene_THREE::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void C3DTexture::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice;					// �f�o�C�X�̃|�C���^

	pDevice = CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

													// ���C�e�B���O���[�h����
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	//Z�o�b�t�@�@�L���@����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);

	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	// ����(�����)���J�����O����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	CScene_THREE::Draw();

	//�A���t�@�e�X�g�߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//Z�o�b�t�@�@�L���@����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
	// ���C�e�B���O���[�h�L��
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	// ����(�����)���J�����O����
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

// ----------------------------------------
// �e�N�X�`���[�ݒ菈��
// ----------------------------------------
void C3DTexture::SetTexture(TYPE type)
{
	// �ݒ�
	CScene_THREE::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
C3DTexture * C3DTexture::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size,D3DXCOLOR col,TYPE type,  bool bBillboard)
{
	// �ϐ��錾
	C3DTexture * p3DTexture;		// �V�[��3D�N���X
											// �������̐���(����->��{�N���X,��->�h���N���X)
	p3DTexture = new C3DTexture();
	// ��ނ̐ݒ�
	p3DTexture->m_Type = type;
	// �r���{�[�h�̂����邩�ǂ���
	p3DTexture->m_bBillboard = bBillboard;
	// ����������
	p3DTexture->Init();
	// ���W�̐ݒ�
	p3DTexture->SetPos(pos);
	// ��]�̐ݒ�
	p3DTexture->SetRot(rot);
	// �傫���̐ݒ�
	p3DTexture->SetSize(size);
	// �F�̐ݒ�
	p3DTexture->SetCol(col);
	// �e�N�X�`���̐ݒ�
	p3DTexture->SetTexture(type);
	// ���������I�u�W�F�N�g��Ԃ�
	return p3DTexture;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT C3DTexture::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/Effect/Effect002.jpg",
		"data/TEXTURE/Effect/Effect0002.jpg",
	};

	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}

	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void C3DTexture::UnLoad(void)
{
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void C3DTexture::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void C3DTexture::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void C3DTexture::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void C3DTexture::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void C3DTexture::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_THREE::SetTex(first, last);
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR3 C3DTexture::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// ��]�̎擾����
// ----------------------------------------
D3DXVECTOR3 C3DTexture::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 C3DTexture::GetPos(void)
{
	return CScene_THREE::GetPos();
}
