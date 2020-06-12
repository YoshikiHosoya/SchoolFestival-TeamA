// =====================================================================================================================================================================
//
// �p�[�e�B�N���̏��� [particle.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "particle.h"			// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "player.h"
#include "fade.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CParticle::m_apTexture[PARTICLETYPE::PARTICLE_MAX]	= {};				// �擪�͌^��
INTEGER2			CParticle::m_UVcut									= INTEGER2(0, 0);
D3DXVECTOR2			CParticle::m_UVsize									= D3DXVECTOR2(0.0f, 0.0f);

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEXTURE_FILE01		"data/TEXTURE/ef_anim01.png"	// �ǂݍ��ރe�N�X�`���t�@�C����			( ���@�� )
#define TEXTURE_FILE02		"data/TEXTURE/ef_anim02.png"	// �ǂݍ��ރe�N�X�`���t�@�C����		( ���@�� )

#define EFFECT_SIZEX		(20 / 2)						// ���W�̕�
#define EFFECT_SIZEY		(20 / 2)						// ���W�̍���

#define ITEM_EFFECT_SIZEX	(10 / 2)						// ���W�̕�
#define ITEM_EFFECT_SIZEY	(10 / 2)						// ���W�̍���

#define SUB_COL				(1.0f)							// �F�̌���
#define SUB_RADIUS			(1.0f)							// ���a�̌���

#define ANIM_SPD			(5)								// �A�j���[�V�����̑���

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CParticle::CParticle() :CScene3D(PRIORITY_EFFECT)
{
	// �ϐ�������
	m_size	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �T�C�Y
	m_move	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ړ�
	m_col	= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F
	m_type	= PARTICLETYPE::PARTICLE_NONE;				// �p�[�e�B�N���̎��
	m_nCntAnim		= 0;								// �J�E���^�[�A�j���[�V����
	m_nPatternAnim	= 0;								// �p�^�[���A�j���[�V����

	m_nSpeed	= 0;								// ����
	m_fRot		= 0.0f;								// ��]
	m_fAngle	= 0.0f;								// �p�x
	m_fLength	= 0;								// ����
	m_fRadius	= 0;								// ���a

}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CParticle::~CParticle()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CParticle::Init()
{
	// ������
	CScene3D::Init();
	
	//�F�̐ݒ�
	CScene3D::SetColor(m_col);

	// �p�[�e�B�N���̎�ޕʐݒ�
	switch (m_type)
	{
	case CParticle::PARTICLE_RED:
		m_size = D3DXVECTOR3(EFFECT_SIZEX, EFFECT_SIZEY, 0.0f);	// �T�C�Y�̐ݒ�
		m_UVcut = INTEGER2(8, 1);								// �A�j���[�V�����̕�����
		break;

	case CParticle::PARTICLE_BLUE:
		m_size = D3DXVECTOR3(ITEM_EFFECT_SIZEX, ITEM_EFFECT_SIZEY, 0.0f);	// �T�C�Y�̐ݒ�
		m_UVcut = INTEGER2(8, 1);								// �A�j���[�V�����̕�����

		break;
	}

	// �A�j���[�V�����̖���
	m_UVsize = D3DXVECTOR2(1.0f / m_UVcut.x, 1.0f / m_UVcut.y);

	// �e�N�X�`���̊��蓖��
	BindTexture(m_apTexture[m_type]);

	// �T�C�Y�̐ݒ�
	SetSize(m_size);

	// �A�j���[�V��������
	D3DXVECTOR2 UV;
	UV.x = m_nPatternAnim % m_UVcut.x * m_UVsize.x;
	UV.y = m_nPatternAnim / m_UVcut.x * m_UVsize.y;

	// �A�j���[�V�����̐ݒ�
	CScene3D::SetAnim(m_UVsize, UV);
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CParticle::Uninit(void)
{
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CParticle::Update(void)
{
	// �F�̐ݒ�
	static D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f,1.0f);
	float *fcol = col;

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CScene3D::GetPos();

	// �J�E���g�A�b�v
	m_nCntAnim++;
	m_fRadius += 1.0f;

	// �ʒu�X�V
	pos += m_move;

	//// �v���C���[�Ƃ̓����蔻��
	//if (CollisionPlayer() == true)
	//{
	//}

	// �����ύX
	if (m_nCntAnim % ANIM_SPD == 0)
	{
		// �p�^�[���J�E���g�A�b�v
		m_nPatternAnim++;

		// �A�j���[�V��������
		D3DXVECTOR2 UV;
		UV.x = m_nPatternAnim % m_UVcut.x * m_UVsize.x;
		UV.y = m_nPatternAnim / m_UVcut.x * m_UVsize.y;

		// �A�j���[�V�����̐ݒ�
		CScene3D::SetAnim(m_UVsize, UV);

		// �I��
		if (m_nPatternAnim >= (m_UVcut.x * m_UVcut.y))
		{
			Release();
			return;
		}

	}
	else
	{
		// �ʒu�̐ݒ�
		CScene3D::SetPos(pos);

		// �X�V
		CScene3D::Update();

		//// ���a�̐ݒ�
		//CScene3D::SetRadius(m_fRadius);

	}
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CParticle::Draw(void)
{	
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);						// �e�X�g���p�X����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// �`��
	CScene3D::Draw();

	// �����_�[�X�e�[�g(�ʏ�u�����h����)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);								// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);							// �f�t�H���g�ɖ߂�
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

// =====================================================================================================================================================================
//
// �p�[�e�B�N���̐���
//
// =====================================================================================================================================================================
CParticle * CParticle::Create(D3DXVECTOR3 pos, PARTICLETYPE type)
{
	// �ϐ�
	CParticle *pParticle;

	// �������̊m��
	pParticle = new CParticle();

	// �p�[�e�B�N���̎�ނ̐ݒ�
	pParticle->m_type = type;

	// ������
	pParticle->Init();

	// ��ޕ�
	if (pParticle->m_type != CParticle::PARTICLE_RED)
	{
		// �������~�̃p�[�e�B�N��
		pParticle->ParticleCircleShort();
	}
	else
	{
		// �~�̃p�[�e�B�N��
		pParticle->ParticleCircle();
	}

	// �p�[�e�B�N���̈ʒu�̐ݒ�
	pParticle->SetPos(pos);

	// �e�N�X�`���̊��蓖��
	pParticle->BindTexture(m_apTexture[type]);

	// �r���{�[�h�̐ݒ�
	pParticle->SetBillboard(true);

	return pParticle;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CParticle::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���t�@�C����
	char *sTextureFileName[PARTICLE_MAX]
	{
		{ TEXTURE_FILE01 },		// PARTICLE_AURA				( �I�[��
		{ TEXTURE_FILE02 },		// PARTICLE_GAYSER			( �Ԍ���
	};

	for (int nCntParticle = 0; nCntParticle < PARTICLE_MAX; nCntParticle++)
	{
		// �e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntParticle], &m_apTexture[nCntParticle]);
	}

	return S_OK;
}

// =====================================================================================================================================================================
//  
// �A�����[�h
//
// =====================================================================================================================================================================
void CParticle::Unload(void)
{
	for (int nCntTex = 0; nCntTex < PARTICLETYPE::PARTICLE_MAX; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//  
// �v���C���[�Ƃ̓����蔻��
//
// =====================================================================================================================================================================
bool CParticle::CollisionPlayer(void)
{
	CPlayer * pPlayer		= CManager::GetGame()->GetPlayer();		// �v���C���[�̎擾
	D3DXVECTOR3 posPlayer	= pPlayer->GetPos();					// �v���C���[�̈ʒu�擾
	D3DXVECTOR3 posParticle	= GetPos();								// �p�[�e�B�N���̈ʒu

	float x = posParticle.x - posPlayer.x;
	float y = posParticle.y - posPlayer.y;
	float z = posParticle.z - posPlayer.z;
	float fDistancec = (float)sqrt(x * x + y * y + z * z);

	// �͈͓��ɓ������Ƃ�
	if (fDistancec <= 20.0f + EFFECT_SIZEX)
	{
		Release();
		return true;
	}
	return false;
}

// =====================================================================================================================================================================
//
// �~�̃p�[�e�B�N��
//
// =====================================================================================================================================================================
void CParticle::ParticleCircle(void)
{
	// �����_��(�~)
	m_fRot = rand() % 314 * 0.01f - rand() % 314 * 0.01f;
	m_nSpeed = rand() % 7 - 4;

	m_move.x += sinf(D3DX_PI * m_fRot) * m_nSpeed;
	m_move.y += cosf(D3DX_PI * m_fRot) * m_nSpeed;
	m_move.z += (m_move.x - m_move.y) / 2;
}

// =====================================================================================================================================================================
//
// �������~�̃p�[�e�B�N��
//
// =====================================================================================================================================================================
void CParticle::ParticleCircleShort(void)
{
	// �����_��(�~)
	m_fRot = rand() % 314 * 0.01f - rand() % 314 * 0.01f;
	m_nSpeed = rand() % 4 - 1;

	m_move.x += sinf(D3DX_PI * m_fRot) * m_nSpeed;
	m_move.y += cosf(D3DX_PI * m_fRot) * m_nSpeed;
	m_move.z += (m_move.x - m_move.y) / 2;
}