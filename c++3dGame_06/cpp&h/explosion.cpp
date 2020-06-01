// ----------------------------------------
//
// �����G�t�F�N�g������[explosion.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "explosion.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define TEX_X_SMO (0.1f)
#define TEX_X_EXP (0.1428f)
// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CExplosion::m_pTexture[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
D3DXVECTOR2 CExplosion::m_Tex[TYPE_MAX] = {};

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CExplosion::CExplosion() : CScene_THREE::CScene_THREE(ACTOR_EXPLOSION, LAYER_3DPARTICLE)
{
	// �ϐ��̏�����
	m_fLengh = 0;
	m_fAngle = 0;
	m_Type = TYPE_SMOKE;
	m_bBillboard = false;
	m_nCntAnim = 0;
	m_nPatternAnim = 0;
	m_TexFirst = D3DXVECTOR2(0.0f, 0.0f);
	m_TexFirstSMO = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLast = D3DXVECTOR2(TEX_X_EXP, 1.0f);
	m_TexLastSMO = D3DXVECTOR2(TEX_X_SMO, 1.0f);
	m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_Size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CExplosion::~CExplosion()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CExplosion::Init(void)
{
	// �V�[��3D�̏�����
	CScene_THREE::Init();
	//if (m_Type == TYPE_P_LIGHT)
	//{
	//	CScene_THREE::SetBillboard(true);				// �r���{�[�h
	//}

	/*if (m_Type == TYPE_EXPLOSION)
	{
		SetCol(D3DXCOLOR(0.1f, 0.0f, 1.0f, 1.0f));
	}*/

}

// ----------------------------------------
// �I������
// ----------------------------------------
void CExplosion::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CExplosion::Update(void)
{
	SetAnim();
	CScene_THREE::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CExplosion::Draw(void)
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
void CExplosion::SetTexture(TYPE type)
{
	// �ݒ�
	CScene_THREE::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CExplosion * CExplosion::Create(D3DXVECTOR3 pos, D3DXVECTOR3 size, TYPE type)
{
	// �ϐ��錾
	CExplosion * pExplosion;		// �V�[��3D�N���X
										// �������̐���(����->��{�N���X,��->�h���N���X)
	pExplosion = new CExplosion();
	//�^�C�v�ݒ�
	pExplosion->m_Type = type;
	// ����������
	pExplosion->Init();
	//���W�ݒ�
	pExplosion->SetPos(pos);
	//�T�C�Y�ݒ�
	pExplosion->m_Size = size;
	pExplosion->SetSize(size);
	//�e�N�X�`���ݒ�
	pExplosion->SetTexture(type);
	//�e�N�X�`�����W�̐ݒ�
	//pExplosion->SetTex(pExplosion->m_TexFirst, pExplosion->m_TexLast);
	if (pExplosion->m_Type == TYPE_EXPLOSION)
	{
		pExplosion->SetTex(pExplosion->m_TexFirst, pExplosion->m_TexLast);
	}
	else if (pExplosion->m_Type == TYPE_SMOKE)
	{
		pExplosion->SetTex(pExplosion->m_TexFirstSMO, pExplosion->m_TexLastSMO);
	}
	// ���������I�u�W�F�N�g��Ԃ�
	return pExplosion;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CExplosion::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/Effect/Explosion00.png",
		"data/TEXTURE/Effect/Explosion01.png",
	};

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���[����������
		if (strcmp(cTex[nCnt], "") != 0)
		{
			/* �e�N�X�`���[�̃��[�h */
			D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
			/* �ʒu�E�T�C�Y�̃��[�h */
			//m_Tex[nCnt] = tex[nCnt];
		}
	}

	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CExplosion::UnLoad(void)
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
void CExplosion::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CExplosion::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CExplosion::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CExplosion::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CExplosion::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_THREE::SetTex(first, last);
}

// ----------------------------------------
// �A�j���[�V�����̐ݒ�
// ----------------------------------------
void CExplosion::SetAnim(void)
{
	switch (m_Type)
	{
	case TYPE_SMOKE:
		m_nCntAnim++;//�J�E���^�[���Z
		if (m_nCntAnim % 7 == 0)
		{
			if (m_TexFirstSMO.x < 1.0f - TEX_X_SMO)
			{
				m_TexFirstSMO.x += TEX_X_SMO;
				m_TexLastSMO.x += TEX_X_SMO;

				if (m_nCntAnim <= 18)
				{
					//�傫�����Z
					m_Size += D3DXVECTOR3(200.0f, 200.0f, 0.0f);
					SetSize(D3DXVECTOR3(m_Size));
				}
			}

			else if(m_TexFirstSMO.x >= 1.0f - TEX_X_SMO)
			{
				if (m_nCntAnim >= 78)
				{
					//�����x�����Z
					m_Col.a -= 0.06f;
				}
				SetCol(m_Col);

				//�����Ȃ��Ȃ�����폜
				if (m_Col.a <= 0.0f)
				{
					Release();
					m_nCntAnim = 0;
				}
			}

			SetTex(D3DXVECTOR2(m_TexFirstSMO.x, m_TexFirstSMO.y), D3DXVECTOR2(m_TexLastSMO.x, m_TexLastSMO.y));
		}
		break;

	case TYPE_EXPLOSION:
		m_nCntAnim++;//�J�E���^�[���Z
		SetCol(D3DXCOLOR(0.2f, 0.0f, 1.0f, 1.0f));
		if (m_nCntAnim % 6 == 0)
		{
			if (m_TexFirst.x < 1.0f - TEX_X_EXP)
			{
				m_TexFirst.x += TEX_X_EXP;
				m_TexLast.x	 += TEX_X_EXP;
			}

			else if (m_TexFirst.x >= 1.0f - TEX_X_EXP)
			{
				Release();
			}

			SetTex(D3DXVECTOR2(m_TexFirst.x, m_TexFirst.y), D3DXVECTOR2(m_TexLast.x, m_TexLast.y));

			if (m_nCntAnim >= 18)
			{
				CExplosion::Create(D3DXVECTOR3(0.000f, 500.000f, - 1700.000f), D3DXVECTOR3(400.0f,400.0f,0.0f), CExplosion::TYPE_SMOKE);
				m_nCntAnim = 0;
			}

		}
		break;

	default:
		break;
	}
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR3 CExplosion::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// ��]�̎擾����
// ----------------------------------------
D3DXVECTOR3 CExplosion::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CExplosion::GetPos(void)
{
	return CScene_THREE::GetPos();
}
