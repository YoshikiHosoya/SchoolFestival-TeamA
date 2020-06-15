// =====================================================================================================================================================================
//
// ��̏��� [slope.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "slope.h"						// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"
#include "debugproc.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9 CSlope::m_pTexture = NULL;

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEXTURE_FILE00		"data/TEXTURE/Rock00.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define SLOPE_SYZE_X		(30)						// 1�u���b�N�̉��̃T�C�Y
#define SLOPE_SYZE_Y		(100)						// 1�u���b�N�̏c�̃T�C�Y

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CSlope::CSlope() : CScene3D(PRIORITY_MODEL)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CSlope::~CSlope()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CSlope::Init(void)
{
	m_size		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	 // �T�C�Y
	m_fSlope	= 0.0f;							 //	�X��

	// ������
	CScene3D::Init();
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CSlope::Uninit(void)
{
	// �I��
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CSlope::Update(void)
{
	// �X�V
	CScene3D::SetSlope(m_fSlope);
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CSlope::Draw(void)
{
	// �`��
	CScene3D::Draw();
}

// =====================================================================================================================================================================
//
// ��̐���
//
// =====================================================================================================================================================================
CSlope * CSlope::Create(D3DXVECTOR3 pos, float Slope)
{
	// �ϐ�
	CSlope *pSlope;

	// �������̊m��
	pSlope = new CSlope();

	// ������
	pSlope->Init();

	// ���ʃJ�����O�̐ݒ�
	pSlope->SetBothSideCulling(true);

	// �ʒu�̐ݒ�
	pSlope->SetPos(D3DXVECTOR3(pos.x, pos.y, pos.z));

	// �T�C�Y
	pSlope->m_size = D3DXVECTOR3(SLOPE_SYZE_X, 0.0f, SLOPE_SYZE_Y);

	// �T�C�Y�̐ݒ�
	pSlope->SetSize(pSlope->m_size);

	// �Ζ�
	pSlope->m_fSlope = Slope;

	// �Ζʂ̊p�x�̐ݒ�
	pSlope->SetSlope(pSlope->m_fSlope);

	// �@���̐ݒ�
	pSlope->SetNormal();

	// �e�N�X�`���̊��蓖��
	pSlope->BindTexture(m_pTexture);

	// �e�N�X�`���̕����ݒ�
	pSlope->SetTexSeparate(5);

	return pSlope;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CSlope::Load(void)
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
void CSlope::Unload(void)
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
// �Ζʂ̃T�C�Y�̐ݒ�
//
// =====================================================================================================================================================================
void CSlope::SetSlopSize(float Slope)
{
	m_fSlope = Slope;

	// �Ζʂ̊p�x�̐ݒ�
	SetSlope(m_fSlope);
}