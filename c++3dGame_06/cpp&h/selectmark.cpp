// ----------------------------------------
//
// �󏈗��̐���[selectmark.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "selectmark.h"

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
LPDIRECT3DTEXTURE9 CSelectMark::m_pTexture[MARK_MAX] = {};		// �e�N�X�`���ւ̃|�C���^

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CSelectMark::CSelectMark() : CScene_TWO::CScene_TWO(ACTOR_MARK, LAYER_UI)
{
	// �ϐ��̏�����
	m_fLengh = 0;
	m_fAngle = 0;
	m_type = MARK_ARROW;
	m_pos = D3DXVECTOR3(0.0f, 0.0f,0.0f);
	m_frot = 0.0f;
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_nSelectCount = 0;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CSelectMark::~CSelectMark()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CSelectMark::Init(void)
{
	// �V�[��3D�̏�����
	CScene_TWO::Init();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CSelectMark::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CSelectMark::Update(void)
{
	CScene_TWO::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CSelectMark::Draw(void)
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

	CScene_TWO::Draw();

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
// ��������
// ----------------------------------------
CSelectMark * CSelectMark::Create(D3DXVECTOR3 pos, float rot, D3DXVECTOR2 size, D3DXCOLOR col, MARK type)
{
	// �ϐ��錾
	CSelectMark * pSelectMark;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pSelectMark = new CSelectMark();
	// ���
	pSelectMark->m_type = type;
	//�e�N�X�`���̐ݒ�
	pSelectMark->SetTexure(type);
	// ����������
	pSelectMark->Init();
	// ���W
	pSelectMark->m_pos = pos;
	pSelectMark->SetPos(pSelectMark->m_pos);
	// ��]
	pSelectMark->m_frot = rot;
	pSelectMark->SetRot(pSelectMark->m_frot);
	// �傫��
	pSelectMark->m_size = size;
	pSelectMark->SetSize(pSelectMark->m_size);
	// �F
	pSelectMark->m_col = col;
	pSelectMark->SetCol(pSelectMark->m_col);

	// ���������I�u�W�F�N�g��Ԃ�
	return pSelectMark;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CSelectMark::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[MARK_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/Effect/.png",
		"data/TEXTURE/Effect/.jpg",
	};

	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MARK_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CSelectMark::UnLoad(void)
{
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MARK_MAX; nCnt++)
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
void CSelectMark::SetPos(D3DXVECTOR3 pos)
{
	CScene_TWO::SetPosition(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CSelectMark::SetSize(D3DXVECTOR2 size)
{
	CScene_TWO::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CSelectMark::SetRot(float rot)
{
	CScene_TWO::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CSelectMark::SetCol(D3DXCOLOR col)
{
	CScene_TWO::SetCol(col);
}

// ----------------------------------------
// �e�N�X�`���̐ݒ�
// ----------------------------------------
void CSelectMark::SetTexure(MARK type)
{
	// �ݒ�
	CScene_TWO::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}

// ----------------------------------------
// �J�E���g�ݒ�
// ----------------------------------------
void CSelectMark::SetCount(int nCnt)
{
	m_nSelectCount = nCnt;
}

// ----------------------------------------
// �J�E���g�ݒ�
// ----------------------------------------
void CSelectMark::CalculationCount(int nCnt)
{
	m_nSelectCount += nCnt;
}

// ----------------------------------------
// �J�E���g�����Z�b�g
// ----------------------------------------
void CSelectMark::ResetCount(void)
{
	m_nSelectCount = 0;
}

// ----------------------------------------
// �}�[�N�̍폜
// ----------------------------------------
void CSelectMark::ReleaseSelMark(void)
{
	Release();
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CSelectMark::Transparency(void)
{
	//�����x����Ȃ�������
	if (m_col.a > 0.0f)
	{
		//���X�ɓ����ɂ���
		m_col.a -= 0.005f;
		//�F�̍X�V
		SetCol(m_col);
	}

	//�����x��0�ȉ��ɂȂ�����폜
	if (m_col.a <= 0.0f)
	{
		Release();
	}
}

// ----------------------------------------
// �J�E���g�擾
// ----------------------------------------
int CSelectMark::GetCount(void)
{
	return m_nSelectCount;
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR2 CSelectMark::GetSize(void)
{
	return CScene_TWO::GetSize();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CSelectMark::GetPos(void)
{
	return CScene_TWO::GetPosition();
}