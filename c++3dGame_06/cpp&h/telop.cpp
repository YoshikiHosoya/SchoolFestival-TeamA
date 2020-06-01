// ----------------------------------------
//
// �e���b�v�����̐���[telop.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "telop.h"
#include "title.h"
#include "TelopComment.h"
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
LPDIRECT3DTEXTURE9 CTelop::m_pTexture = NULL;
D3DXVECTOR3 CTelop::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
D3DXVECTOR2 CTelop::m_size = D3DXVECTOR2(0.0f, 0.0f);
D3DXCOLOR CTelop::m_Col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CTelop::CTelop() : CScene_TWO::CScene_TWO(ACTOR_TELOP, LAYER_UI)
{
	m_nCntCol = 0;
	m_nCommentCount = 0;
	m_bTelopFlag = false;
	m_bCommentFlag = false;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CTelop::~CTelop()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTelop::Init(void)
{
	CScene_TWO::Init();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CTelop::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CTelop::Update(void)
{
	// �e���b�v�����݂���ENTER���������Ƃ�
	if (CManager::GetTitle()->GetEnterflag() == true && GetTelopFlag() == true)
	{
		// �O�̃R�����g����������Ă���1�b��������
		if (m_bCommentFlag == false)
		{
			// ���̃t�F�[�Y�ֈڍs
			CTelopComment::SetPhase();
			// �N�[���^�C����������
			m_nCommentCount = 0;
			// �t���O��true�ɂ���
			m_bCommentFlag = true;
		}

		// �O�̃R�����g����������Ă���1�b��������
		else if (m_nCommentCount >= ONEMIN)
		{
			m_bCommentFlag = false;
			m_nCommentCount = 0;
		}
	}

	// �R�����g���������ꂽ��
	if (m_bCommentFlag == true)
	{
		// ���̃R�����g�𐶐��ł���܂ł̃N�[���^�C�����J�E���g
		m_nCommentCount++;
	}

	CScene_TWO::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CTelop::Draw(void)
{
	CScene_TWO::Draw();
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CTelop::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[72] =
	{
		"data/TEXTURE/UI/Telop.png"
	};
	// �ʒu�����
	D3DXVECTOR3 pos =
	{
		D3DXVECTOR3(640.0f,600,0.0f)
	};
	// �T�C�Y�����
	D3DXVECTOR2 size =
	{
		D3DXVECTOR2(600.0f,100.0f)
	};
	// �F�����
	D3DXCOLOR col =
	{
		D3DXCOLOR(1.0f,1.0f,1.0f,0.0f)
	};

	// �e�N�X�`���[����������
	if (strcmp(TexData, "") != 0)
	{
		D3DXCreateTextureFromFile(pDevice, TexData, &m_pTexture);
		m_pos = pos;
		m_size = size;
		m_Col = col;
	}

	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CTelop::UnLoad(void)
{
	// �e�N�X�`���̊J��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CTelop * CTelop::Create(void)
{
	// �ϐ��錾
	CTelop * pTelop;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pTelop = new CTelop();
	// �e�N�X�`���̐ݒ�
	pTelop->BindTexture(m_pTexture);
	// ����������
	pTelop->Init();
	// ���W�̐ݒ�
	pTelop->SetPosition(m_pos);
	// �傫���̔��f
	pTelop->SetSize(m_size);
	// �F�̐ݒ�
	pTelop->SetCol(m_Col);
	// ���������I�u�W�F�N�g��Ԃ�
	return pTelop;
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTelop::Transparency(STATE state)
{
	switch (state)
	{
		// �o��
	case STATE_EMERGENCE:
		// ���X�Ƀ��l�����Z
		if (m_Col.a <= 1.0f)
		{
			//���X�ɓ����ɂ���
			m_Col.a += 0.01f;
			//�F�̍X�V
			SetCol(m_Col);
		}

		// ���S�ɕs�����ɂȂ�����
		if (m_Col.a >= 1.0f)
		{
			// �s�����t���O��true�ɂ���
			m_bTelopFlag = true;
		}
		break;

		// ����
	case STATE_DISAPPEARANCE:
		// ���X�ɓ�����������
		if (m_Col.a >= 0.0f)
		{
			//���X�ɓ����ɂ���
			m_Col.a -= 0.01f;
			//�F�̍X�V
			SetCol(m_Col);
		}

		// ���S�ɓ����ɂȂ�����
		if (m_Col.a <= 0.0f)
		{
			// ���ł�����
			Release();
		}

		break;

	default:
		break;
	}
}

// ----------------------------------------
// �t���O�̎擾
// ----------------------------------------
bool CTelop::GetTelopFlag(void)
{
	return m_bTelopFlag;
}
