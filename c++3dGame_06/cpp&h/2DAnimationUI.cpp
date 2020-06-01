// ----------------------------------------
//
// 2D�A�j���[�V���������̐���[2DAnimationUI.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "2DAnimationUI.h"

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
LPDIRECT3DTEXTURE9 C2DAnimation::m_pTexture[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
C2DAnimation::C2DAnimation() : CScene_TWO::CScene_TWO(ACTOR_ANIMATION, LAYER_UI)
{
	// �ϐ��̏�����
	m_Type = TYPE_KEY;
	m_nCntAnim = 0;
	m_nPatternAnim = 0;
	m_TexFirst = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLast = D3DXVECTOR2(0.2f, 1.0f);
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
C2DAnimation::~C2DAnimation()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void C2DAnimation::Init(void)
{
	CScene_TWO::Init();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void C2DAnimation::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void C2DAnimation::Update(void)
{
	// �A�j���[�V�����̍X�V
	SetAnim();
	// ��]�̔��f
	//CScene_TWO::SetRot(CScene_TWO::GetLengh() + 0.1f);
	CScene_TWO::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void C2DAnimation::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	// �A���t�@�e�X�g�̐ݒ�ɕύX
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// �A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);				// �A���t�@�l�̊�ݒ�(����傫���ƕ`�悷��)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// �󋵂ɉ����ăA���t�@�e�X�g�����s����(�V�s�N�Z�� > ���݂̃s�N�Z��)
	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ���C�e�B���Ooff
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`��
	CScene_TWO::Draw();

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// �A���t�@�e�X�g�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// �A���t�@�e�X�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ���C�e�B���Oon
}

// ----------------------------------------
// �e�N�X�`���[�ݒ菈��
// ----------------------------------------
void C2DAnimation::SetTexture(TYPE type)
{
	// �e�N�X�`���[�ݒ�
	CScene_TWO::BindTexture(m_pTexture[type]);
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
C2DAnimation * C2DAnimation::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, D3DXVECTOR2 texf, D3DXVECTOR2 texr, TYPE type)
{
	// �ϐ��錾
	C2DAnimation * p2DAnimation;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	p2DAnimation = new C2DAnimation();
	// ��ނ̐ݒ�
	p2DAnimation->m_Type = type;
	// ����������
	p2DAnimation->Init();
	// ���W�̐ݒ�
	p2DAnimation->SetPos(pos);
	// �傫���̐ݒ�
	p2DAnimation->SetSize(size);
	// ����̒��_���W
	p2DAnimation->m_TexFirst = texf;
	// �E���̒��_���W
	p2DAnimation->m_TexLast = texr;
	// �e�N�X�`�����W�̐ݒ�
	p2DAnimation->SetTex(texf, texr);
	// �e�N�X�`���̐ݒ�
	p2DAnimation->SetTexture(type);
	// ���������I�u�W�F�N�g��Ԃ�
	return p2DAnimation;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT C2DAnimation::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`�����̓ǂݍ���
	char cTex[TYPE_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/UI/Animation00.png",
		"data/TEXTURE/UI/Animation01.png",
		"data/TEXTURE/UI/Animation02.png"
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
void C2DAnimation::UnLoad(void)
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
void C2DAnimation::SetPos(D3DXVECTOR3 pos)
{
	CScene_TWO::SetPosition(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void C2DAnimation::SetSize(D3DXVECTOR2 size)
{
	CScene_TWO::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void C2DAnimation::SetRot(float rot)
{
	CScene_TWO::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void C2DAnimation::SetCol(D3DXCOLOR col)
{
	CScene_TWO::SetCol(col);
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void C2DAnimation::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_TWO::SetTex(first, last);
}

// ----------------------------------------
// �A�j���[�V�����̐ݒ�
// ----------------------------------------
void C2DAnimation::SetAnim(void)
{
	switch (m_Type)
	{
	case TYPE_KEY:

		m_nCntAnim++;//�J�E���^�[���Z

		// 1�t���[�����ƂɍX�V
		if (m_nCntAnim % (ONEFRAME) == 0)
		{
			// ���X�̓A�j���[�V����
			m_TexFirst.x += 0.2f;
			m_TexLast.x += 0.2f;

			// x���E�[�܂ōs����y���ŉ��i����Ȃ�������
			if (m_TexFirst.x >= 0.8f && m_TexLast.x >= 1.0f && m_TexFirst.y < 0.75f && m_TexLast.y <= 1.0f)
			{
				m_TexFirst.y += 0.25f;
				m_TexLast.y += 0.25f;
			}

			// x���E�[�܂ōs����y���ŉ��i��������
			else if (m_TexFirst.x >= 0.8f && m_TexLast.x >= 1.0f && m_TexFirst.y >= 0.75f && m_TexLast.y >= 1.0f)
			{
				m_TexFirst.y = 0.0f;
				m_TexLast.y = 0.25f;
			}

			// �e�N�X�`�����W�̍X�V
			SetTex(D3DXVECTOR2(m_TexFirst.x, m_TexFirst.y), D3DXVECTOR2(m_TexLast.x, m_TexLast.y));

			break;
		}
	default:
		break;
	}
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR2 C2DAnimation::GetSize(void)
{
	return CScene_TWO::GetSize();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 C2DAnimation::GetPos(void)
{
	return CScene_TWO::GetPosition();
}

// ----------------------------------------
// ��]�̎擾����
// ----------------------------------------
float C2DAnimation::GetRot(void)
{
	return CScene_TWO::GetLengh();
}