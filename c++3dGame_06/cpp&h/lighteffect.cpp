// ----------------------------------------
//
// ���C�g�G�t�F�N�g�����̐���[lighteffect.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "lighteffect.h"

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
LPDIRECT3DTEXTURE9 CLightEffect::m_pTexture[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
int		CLightEffect::m_nAll = 0;									// �ԍ�

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CLightEffect::CLightEffect() : CScene_THREE::CScene_THREE(ACTOR_3DLIGHTEFFECT, LAYER_EFFECT)
{
	// �ϐ��̏�����
	m_fLengh = 0;
	m_fAngle = 0;
	m_type = TYPE_S_LIGHT;
	m_bBillboard = false;
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	//�G�t�F�N�g����������邽�тɍ��v�������Z
	m_nAll++;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CLightEffect::~CLightEffect()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CLightEffect::Init(void)
{
	// �V�[��3D�̏�����
	CScene_THREE::Init();
	if (m_bBillboard == true)
	{
		CScene_THREE::SetBillboard(true);				// �r���{�[�h
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CLightEffect::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CLightEffect::Update(void)
{
	Transparency();
	CScene_THREE::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CLightEffect::Draw(void)
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
// ��������
// ----------------------------------------
CLightEffect * CLightEffect::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 size, D3DXCOLOR col, TYPE type, bool bBill)
{
	// �ϐ��錾
	CLightEffect * pLightEffect;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pLightEffect = new CLightEffect();
	// ���
	pLightEffect->m_type = type;
	//�e�N�X�`���̐ݒ�
	pLightEffect->SetTexure(type);
	// �r���{�[�h
	pLightEffect->m_bBillboard = bBill;
	// ����������
	pLightEffect->Init();
	// ���W
	pLightEffect->m_pos = pos;
	pLightEffect->SetPos(pLightEffect->m_pos);
	// ��]
	pLightEffect->m_rot = rot;
	pLightEffect->SetRot(pLightEffect->m_rot);
	// �傫��
	pLightEffect->m_size = size;
	pLightEffect->SetSize(pLightEffect->m_size);
	// �F
	pLightEffect->m_col = col;
	pLightEffect->SetCol(pLightEffect->m_col);

	// ���������I�u�W�F�N�g��Ԃ�
	return pLightEffect;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CLightEffect::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/Effect/effect002.bmp",
		"data/TEXTURE/Effect/effect000.jpg",
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
void CLightEffect::UnLoad(void)
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
// �w�肳�ꂽ��ނ̃��C�g���폜
// ----------------------------------------
void CLightEffect::ReleaseLight(TYPE type)
{
	CLightEffect *pLightEffect[5] = {};
	for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_EFFECT); nCntLayer++)
	{
		pLightEffect[nCntLayer] = (CLightEffect*)CScene::GetActor(CScene::ACTOR_3DLIGHTEFFECT,CScene::LAYER_EFFECT, nCntLayer);
	}

	for (int nCnt = 0; nCnt < 5; nCnt++)
	{
		if (pLightEffect[nCnt] != NULL)
		{
			if (pLightEffect[nCnt]->m_type == type)
			{
				pLightEffect[nCnt]->Release();
				m_nAll--;
			}
		}
	}
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CLightEffect::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CLightEffect::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CLightEffect::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CLightEffect::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CLightEffect::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
}

// ----------------------------------------
// �e�N�X�`���̐ݒ�
// ----------------------------------------
void CLightEffect::SetTexure(TYPE type)
{
	// �ݒ�
	CScene_THREE::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}

// ----------------------------------------
// ����
// ----------------------------------------
void CLightEffect::Transparency(void)
{
	if (m_type == TYPE_S_LIGHT)
	{
		// ���X�Ƀ��l�����Z
		if (m_col.a <= 1.0f)
		{
			//���X�ɓ����ɂ���
			m_col.a += 0.01f;
			//�F�̍X�V
			SetCol(m_col);
		}
	}
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR3 CLightEffect::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// ��]�̎擾����
// ----------------------------------------
D3DXVECTOR3 CLightEffect::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CLightEffect::GetPos(void)
{
	return CScene_THREE::GetPos();
}