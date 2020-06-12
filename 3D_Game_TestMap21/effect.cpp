// =====================================================================================================================================================================
//
// �G�t�F�N�g�̏��� [effect.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "effect.h"			// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "player.h"
#include "fade.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CEffect::m_apTexture[EFFECTTYPE::EFFECTTYPE_MAX]	= {};				// �擪�͌^��

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEXTURE_FILE01		"data/TEXTURE/aura.png"			// �ǂݍ��ރe�N�X�`���t�@�C����			( �I�[�� )
#define TEXTURE_FILE02		"data/TEXTURE/gayser.png"		// �ǂݍ��ރe�N�X�`���t�@�C����			( �Ԍ��� )
#define TEXTURE_FILE03		"data/TEXTURE/effect.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����			( �A�C�e�� )

#define EFFECT_SIZEX		(200 / 2)						// ���W�̕�
#define EFFECT_SIZEY		(200 / 2)						// ���W�̍���

#define GAYSER_SIZEX		(50 / 2)						// �Ԍ���̕�
#define GAYSER_SIZEY		(100 / 2)						// �Ԍ���̍���

#define SUB_COL				(1.0f)							// �F�̌���
#define SUB_RADIUS			(1.0f)							// ���a�̌���

#define AURA_ANIM_SPD		(3)								// �A�j���[�V�����̑���			( �I�[�� )
#define GAYSER_ANIM_SPD		(2)								// �A�j���[�V�����̑���			( �Ԍ��� )

#define MAX_SYZE_Y_GAYSER	(150.0f)						// �Ԍ���̍����̍ő�

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CEffect::CEffect() :CScene3D(PRIORITY_EFFECT)
{
	// �ϐ�������
	m_size					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �T�C�Y
	m_move					= D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �ړ�
	m_col					= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	// �F
	m_type					= EFFECTTYPE::EFFECTTYPE_NONE;			// �G�t�F�N�g�̎��
	m_nCntAnim				= 0;									// �J�E���^�[�A�j���[�V����
	m_nPatternAnim			= 0;									// �p�^�[���A�j���[�V����
	m_fRadius				= 0.0f;									// ���a
	m_bDamage				= false;								// �_���[�W�t���O
	m_bAction				= false;								// �A�N�V�����t���O
	m_nCntFrame				= 0;									// �t���[���J�E���g
	m_bAdditiveSynthesis	= false;								// ���Z��������t���O
	m_UVcut					= INTEGER2(0, 0);						// UV�T�C�Y
	m_UVsize				= D3DXVECTOR2(0.0f, 0.0f);				// ������
	m_nAnimSpeed			= 0;									// �A�j���[�V�����X�s�[�h
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CEffect::~CEffect()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CEffect::Init()
{
	// ������
	CScene3D::Init();
	
	// �G�t�F�N�g�̎�ޕʐݒ�
	switch (m_type)
	{
	case CEffect::EFFECTTYPE_AURA:
		m_size = D3DXVECTOR3(EFFECT_SIZEX, EFFECT_SIZEY, 0.0f);	// �T�C�Y�̐ݒ�
		m_UVcut = INTEGER2(5, 2);								// �A�j���[�V�����̕�����
		m_nAnimSpeed = AURA_ANIM_SPD;							// �A�j���[�V�����̃X�s�[�h
		break;

	case CEffect::EFFECTTYPE_GAYSER:
		m_size = D3DXVECTOR3(GAYSER_SIZEX, 0.0f, 20.0f);		// �T�C�Y�̐ݒ�
		m_UVcut = INTEGER2(3, 1);								// �A�j���[�V�����̕�����
		m_nAnimSpeed = GAYSER_ANIM_SPD;							// �A�j���[�V�����̃X�s�[�h
		break;

	case CEffect::EFFECTTYPE_ITEM:
		m_size = D3DXVECTOR3(17, 17, 17);// �T�C�Y�̐ݒ�
		m_UVcut = INTEGER2(1, 1);								// �A�j���[�V�����̕�����
		m_nAnimSpeed = 2;										// �A�j���[�V�����̃X�s�[�h
		m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.3f);				// �F
		break;
	}

	//�F�̐ݒ�
	CScene3D::SetColor(m_col);

	// �A�j���[�V�����̖���
	m_UVsize = D3DXVECTOR2(1.0f / m_UVcut.x, 1.0f / m_UVcut.y);

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
void CEffect::Uninit(void)
{
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CEffect::Update(void)
{
	// �F�̐ݒ�
	static D3DXCOLOR col = D3DXCOLOR(0.5f, 0.1f, 1.0f,1.0f);
	float *fcol = col;

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CScene3D::GetPos();

	// �J�E���g�A�b�v
	m_nCntAnim++;
	m_nCntFrame++;

	// �v���C���[�Ƃ̓����蔻��
	if (CollisionEffect() == true)
	{
		CScene3D::SetColor(col);

		if (m_type == EFFECTTYPE_GAYSER)
		{
			// �v���C���[�_���[�W
			CManager::GetGame()->GetPlayer()->PlayerDamage(1);

			// �v���C���[�����S��Ԃ�
			CPlayer::SetPlayerState(CPlayer::PLAYERSTATE_DEATH);
		}
	}
	else
	{
		// �F�̐ݒ�
		CScene3D::SetColor(m_col);
	}

	// �G�t�F�N�g�̐ݒ�
	EffectConfig(m_type);

	// �����ύX
	if (m_nCntAnim % m_nAnimSpeed == 0)
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
			m_nPatternAnim = 0;
			return;
		}
	}
	else
	{
		// �ʒu�̐ݒ�
		CScene3D::SetPos(pos);

		// �Ԍ���̂Ƃ�
		if (m_type == EFFECTTYPE_GAYSER)
		{
			// �T�C�Y�̐ݒ�
			CScene3D::SetScaling(m_size);
		}
		else
		{
			// �X�V
			CScene3D::Update();
		}
	}
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CEffect::Draw(void)
{	
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);						// �e�X�g���p�X����
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���Z���������邩�ǂ���
	if (m_bAdditiveSynthesis)
	{
		// �����_�[�X�e�[�g(���Z��������)
		pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	}

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
// �G�t�F�N�g�̐���
//
// =====================================================================================================================================================================
CEffect * CEffect::Create(D3DXVECTOR3 pos, EFFECTTYPE type)
{
	// �ϐ�
	CEffect *pEffect;

	// �������̊m��
	pEffect = new CEffect();

	// �G�t�F�N�g�̎�ނ̐ݒ�
	pEffect->m_type = type;

	// ������
	pEffect->Init();

	// �G�t�F�N�g�̈ʒu�̐ݒ�
	pEffect->SetPos(pos);

	// �e�N�X�`���̊��蓖��
	pEffect->BindTexture(m_apTexture[type]);

	// �r���{�[�h�̐ݒ�
	pEffect->SetBillboard(true);

	return pEffect;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CEffect::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���t�@�C����
	char *sTextureFileName[EFFECTTYPE_MAX]
	{
		{ TEXTURE_FILE01 },		// EFFECTTYPE_AURA				( �I�[��
		{ TEXTURE_FILE02 },		// EFFECTTYPE_GAYSER			( �Ԍ���
		{ TEXTURE_FILE03 },		// EFFECTTYPE_GAYSER			( �A�C�e��
	};

	for (int nCntEfect = 0; nCntEfect < EFFECTTYPE_MAX; nCntEfect++)
	{
		// �e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntEfect], &m_apTexture[nCntEfect]);
	}

	return S_OK;
}

// =====================================================================================================================================================================
//  
// �A�����[�h
//
// =====================================================================================================================================================================
void CEffect::Unload(void)
{
	for (int nCntTex = 0; nCntTex < EFFECTTYPE::EFFECTTYPE_MAX; nCntTex++)
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
bool CEffect::CollisionEffect(void)
{
	bool bHit = false;		// �q�b�g�t���O

	CPlayer * pPlayer = CManager::GetGame()->GetPlayer();		// �v���C���[�̎擾

	if (pPlayer != NULL)
	{
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();				// �v���C���[�̈ʒu�擾
		D3DXVECTOR3 posOldPlayer = pPlayer->GetOldPos();		// �v���C���[�̉ߋ��ʒu�擾
		D3DXVECTOR3 sizePlayer = pPlayer->GetSize();			// �v���C���[�̃T�C�Y�擾
		D3DXVECTOR3 posEffect = GetPos();						// �G�t�F�N�g�̈ʒu

		// �u���b�N�͈̔� ( �� )
		if (posEffect.x - m_size.x < posPlayer.x + sizePlayer.x &&
			posEffect.x + m_size.x > posPlayer.x - sizePlayer.x)
		{
			// �u���b�N�͈̔� ( �c )
			if (posEffect.z - m_size.z < posPlayer.z + sizePlayer.z &&
				posEffect.z + m_size.z > posPlayer.z - sizePlayer.z)
			{
				// �u���b�N�͈̔� ( ���� )
				if (posEffect.y - m_size.y <= posPlayer.y + sizePlayer.y &&
					posEffect.y + m_size.y > posPlayer.y)
				{
					bHit = true;
				}
			}
		}
	}
	return bHit;
}

// =====================================================================================================================================================================
//  
// �G�t�F�N�g�̐ݒ�
//
// =====================================================================================================================================================================
void CEffect::EffectConfig(EFFECTTYPE type)
{
	switch (type)
	{
	case CEffect::EFFECTTYPE_AURA:		// �I�[��
		// ���Z��������
		m_bAdditiveSynthesis = true;
		break;

	case CEffect::EFFECTTYPE_GAYSER:	// �Ԍ���
		// ���Z��������
		m_bAdditiveSynthesis = true;

		if (m_nCntFrame % 180 == 0)
		{
			// �N��������
			if (m_bAction)
			{
				// �@�\��~
				m_bAction = false;	
			}
			else
			{
				// �N������
				m_bAction = true;
				// ���l��߂�
				m_col.a = 1.0f;
			}
			m_nCntFrame = 0;
		}

		if (m_bAction)
		{
			// �T�C�Y���c�ɐL�΂�
			m_size.y += 2.0f;

			// �Ԍ���̔��a���ő��
			if (m_size.y >= MAX_SYZE_Y_GAYSER)
			{
				m_size.y = MAX_SYZE_Y_GAYSER;
			}
		}
		else
		{
			// ���l����
			m_col.a -= 0.1f;

			if (m_col.a <= 0.0f)
			{
				// �o�Ă��Ȃ���Ԃ�
				m_size.y = 0.0f;
			}
		}
		break;

	case CEffect::EFFECTTYPE_ITEM:		// �A�C�e��
		// ���Z��������
		m_bAdditiveSynthesis = true;
		break;
	}
}
