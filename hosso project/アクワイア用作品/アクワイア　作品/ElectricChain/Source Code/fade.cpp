//------------------------------------------------------------------------------
//
// �t�F�[�h���� [fade.cpp]
// Author : Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "fade.h"
#include "renderer.h"
#include "manager.h"
//------------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------------
#define	TEXTURE_FADE	"data/TEXTURE/other/Fade.png"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define FADE_COLOR	(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f))
#define FADE_SPEED	(0.06f)
//------------------------------------------------------------------------------
// �R���X�g���N�^
//------------------------------------------------------------------------------
CFade::CFade()
{
	m_colorFade = ZeroColor;
	m_pTextureFade = nullptr;
	m_pVtxBuffFade = nullptr;
	m_fadestate = CFade::FADE_NONE;
	m_modeNext = CManager::MODE_NONE;
}

//------------------------------------------------------------------------------
// �f�X�g���N�^
//------------------------------------------------------------------------------
CFade::~CFade()
{
}

//------------------------------------------------------------------------------
// ������
//------------------------------------------------------------------------------
void CFade::Init()
{
	//�f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	//������
	m_fadestate = FADE_NONE;	//�t�F�[�h���
	m_colorFade = ZeroColor;	// ������ʁi�����j

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FADE,		// �t�@�C���̖��O
		&m_pTextureFade);	// �ǂݍ��ރ������[

	// ���_���̐ݒ�
	VERTEX_2D *pVtx;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	pDevice->CreateVertexBuffer(sizeof(VERTEX_2D) * 4,	//�m�ۂ���o�b�t�@�T�C�Y
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,			//���_�t�H�[�}�b�g
		D3DPOOL_MANAGED,
		&m_pVtxBuffFade,
		NULL);

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuffFade->Unlock();
}
//------------------------------------------------------------------------------
// �I��
//------------------------------------------------------------------------------
void CFade::Uninit()
{
	// �e�N�X�`���̊J��
	if (m_pTextureFade != NULL)
	{
		m_pTextureFade->Release();
		m_pTextureFade = NULL;
	}

	// ���_�o�b�t�@�̊J��
	if (m_pVtxBuffFade != NULL)
	{
		m_pVtxBuffFade->Release();
		m_pVtxBuffFade = NULL;
	}
}
//------------------------------------------------------------------------------
// �X�V
//------------------------------------------------------------------------------
void CFade::Update()
{

	UpdateMode();
}
//------------------------------------------------------------------------------
// �`��
//------------------------------------------------------------------------------
void CFade::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, m_pVtxBuffFade, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, NULL);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

//------------------------------------------------------------------------------
// ���[�h�̃t�F�[�h�Z�b�g
//------------------------------------------------------------------------------
void CFade::SetModeFade(CManager::MODE modenext)
{
	//�t�F�[�h�̏�Ԃ�NONE�̎�
	if (m_fadestate == FADE_NONE)
	{
		m_fadestate = FADE_OUT;			//�t�F�[�h�A�E�g�̏�Ԃɂ���
		m_modeNext = modenext;
		m_colorFade = FADE_COLOR;	//�t�F�[�h���鎞�̉�ʂ̐F
	}
}

//------------------------------------------------------------------------------
// �t�F�[�h�擾
//------------------------------------------------------------------------------
CFade::FADESTATE CFade::GetFade(void)
{
	return m_fadestate;
}

//------------------------------------------------------------------------------
// ��������
//------------------------------------------------------------------------------
std::unique_ptr<CFade> CFade::Create()
{
	//�������m��
	std::unique_ptr<CFade> pFade(new CFade);

	//������
	pFade->Init();

	//���^�[��
	return pFade;
}

//------------------------------------------------------------------------------
// ���[�h�p�A�b�v�f�[�g
//------------------------------------------------------------------------------
void CFade::UpdateMode()
{
	//���_�o�b�t�@
	VERTEX_2D *pVtx;

	//�t�F�[�h�C����
	if (m_fadestate == FADE_IN)
	{
		//a�l�����炷
		m_colorFade.a -= FADE_SPEED;

		if (m_colorFade.a <= 0.0f)
		{
			//a�l��0��
			m_colorFade.a = 0.0f;

			//�t�F�[�h����
			m_fadestate = FADE_NONE;
		}
	}
	//�t�F�[�h�A�E�g��
	else if (m_fadestate == FADE_OUT)
	{
		//�����x�𑝂₷
		m_colorFade.a += FADE_SPEED;

		//a�l��1�𒴂�����
		if (m_colorFade.a > 1.0f)
		{
			//a�l��1�ɂ���
			m_colorFade.a = 1.0f;

			//�t�F�[�h�C��
			m_fadestate = FADE_IN;

			//���̃��[�h��NONE�ȊO�̎�
			if (m_modeNext != CManager::MODE_NONE)
			{
				//���̃��[�h�ɂ���
				CManager::SetMode(m_modeNext);
			}
			else
			{

			}
		}
	}

	// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
	m_pVtxBuffFade->Lock(0, 0, (void**)&pVtx, 0);

	// ���_�J���[�̐ݒ�
	pVtx[0].col = m_colorFade;
	pVtx[1].col = m_colorFade;
	pVtx[2].col = m_colorFade;
	pVtx[3].col = m_colorFade;

	// ���_�f�[�^���A�����b�N����
	m_pVtxBuffFade->Unlock();
}