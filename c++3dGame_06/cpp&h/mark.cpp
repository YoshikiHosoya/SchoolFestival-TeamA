// ----------------------------------------
//
// �ڈ󏈗��̐���[mark.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "mark.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MARK_SIZE (50.0f)
#define MARKBOMCHAN_ANIMCOUNT (4)
#define MARKBOMCHAN_HORIZONANIM (1.0f/MARKBOMCHAN_ANIMCOUNT)
#define MARKHOSSAN_ANIMCOUNT (2)
#define MARKHOSSAN_HORIZONANIM (1.0f/MARKHOSSAN_ANIMCOUNT)

// ----------------------------------------
//
// �O���[�o���ϐ�
//
// ----------------------------------------

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CMark::m_pTex[MAX_MARK] = {};

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CMark::CMark()
{
}

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^����
// ----------------------------------------
CMark::CMark(CScene::ACTOR actor) : CScene::CScene(actor,LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < MAX_MARK; nCnt++)
	{
		m_nHorizonAnim[nCnt] = 0;	// �����̃A�j���[�V�����p�^�[��
		m_nVirticalAnim[nCnt] = 0;	// �����̃A�j���[�V�����p�^�[��
		m_nCntAnim[nCnt] = 0;		// �A�j���[�V�����J�E���g
		m_aScene_Two[nCnt] = NULL;
	}
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CMark::~CMark()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CMark::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_MARK; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize({ MARK_SIZE,MARK_SIZE });
		m_aScene_Two[nCnt]->Init();
		/* �\���e�N�X�`���[�ݒ� */
		// �{�������
		if (nCnt == 0)
		{
			// �\���e�N�X�`���[�ݒ�
			m_aScene_Two[nCnt]->SetTex(
				D3DXVECTOR2(0.0f, 0.0f),
				D3DXVECTOR2(0.25f, 1.0f));
			// �F�ݒ�
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(rand() % 10 / 10.0f, rand() % 10 / 10.0f, rand() % 10 / 10.0f, 1.0f));
		}
		// �كb����
		else
		{
			// �\���e�N�X�`���[�ݒ�
			m_aScene_Two[nCnt]->SetTex(
				D3DXVECTOR2(0.0f, 0.0f),
				D3DXVECTOR2(0.5f, 1.0f));
			// �F�ݒ�
			m_aScene_Two[nCnt]->SetCol(D3DXCOLOR(rand() % 10 / 10.0f, rand() % 10 / 10.0f, rand() % 10 / 10.0f, 1.0f));
		}
		m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);

	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CMark::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_MARK; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			m_aScene_Two[nCnt]->Uninit();
			delete m_aScene_Two[nCnt];
			m_aScene_Two[nCnt] = NULL;
		}
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CMark::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_MARK; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// �ʒu���̍X�V
			m_pos += (m_posGoal - m_pos) / 20;
			// �T�C�Y���̍X�V
			m_size += (m_sizeGoal - m_size) / 20;
			// �ʒu�E�T�C�Y�̐ݒ�
			SetPos(m_pos, m_size);
			// �\���e�N�X�`���[
			Animation(nCnt);
			m_aScene_Two[nCnt]->Update();
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CMark::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	// �����_�[�X�e�[�g(���Z��������)
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);


	for (int nCnt = 0; nCnt < MAX_MARK; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			m_aScene_Two[nCnt]->Draw();
		}
	}
	// �ʏ�u�����h
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CMark::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[MAX_MARK][36] =
	{
		{"data/TEXTURE/Effect/effect000.png"},	// �^�C�g���p�̔w�i
		{"data/TEXTURE/Effect/effect000.png"},		// �I����ʗp�̔w�i
	};
	// �ǂݍ���
	for (int nCnt = 0; nCnt < MAX_MARK; nCnt++)
	{
		// �e�N�X�`���[����������
		if (strcmp(TexData[nCnt], "") != 0)
		{
			D3DXCreateTextureFromFile(pDevice, TexData[nCnt], &m_pTex[nCnt]);
		}
	}

	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CMark::UnLoad(void)
{
	// �e�N�X�`���̊J��
		for (int nCnt = 0; nCnt < MAX_MARK; nCnt++)
		{
			if (m_pTex[nCnt] != NULL)
			{
				m_pTex[nCnt]->Release();
				m_pTex[nCnt] = NULL;
			}
		}
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CMark * CMark::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size, CScene::ACTOR actor)
{
	// �ϐ��錾
	CMark * pMark;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pMark = new CMark(actor);
	// ����������
	pMark->Init();
	// �ʒu���ۑ�
	pMark->m_pos = pos;
	pMark->m_posGoal = pos;
	// �T�C�Y���ۑ�
	pMark->m_size = size;
	pMark->m_sizeGoal = size;
	// �ʒu�E�T�C�Y�̐ݒ�
	pMark->SetPos(pos,size);
	// ���������I�u�W�F�N�g��Ԃ�
	return pMark;
}

// ----------------------------------------
// �A�j���[�V��������
// ----------------------------------------
void CMark::Animation(int nCnt)
{
	// �A�j���[�V�����J�E���g�A�b�v
	m_nCntAnim[nCnt]++;
	// �{�������A�j��
	if (nCnt == 0)
	{
		// 20�t���[�����A�j���[�V��������
		if (m_nCntAnim[nCnt] % 20 == 0)
		{
			// �A�j���[�V�����ω�
			m_nHorizonAnim[nCnt] = (m_nHorizonAnim[nCnt] + 1) % MARKBOMCHAN_ANIMCOUNT;
		}
		// ���_�e�N�X�`���[�ݒ�
		m_aScene_Two[nCnt]->SetTex(
			D3DXVECTOR2(m_nHorizonAnim[nCnt] * MARKBOMCHAN_HORIZONANIM, 0.0f),
			D3DXVECTOR2(m_nHorizonAnim[nCnt] * MARKBOMCHAN_HORIZONANIM + MARKBOMCHAN_HORIZONANIM, 1.0f));
	}
	// �{�������A�j��
	if (nCnt == 1)
	{
		// 20�t���[�����A�j���[�V��������
		if (m_nCntAnim[nCnt] % 40 == 0)
		{
			// �A�j���[�V�����ω�
			m_nHorizonAnim[nCnt] = (m_nHorizonAnim[nCnt] + 1) % MARKHOSSAN_ANIMCOUNT;
		}
		// ���_�e�N�X�`���[�ݒ�
		m_aScene_Two[nCnt]->SetTex(
			D3DXVECTOR2(m_nHorizonAnim[nCnt] * MARKHOSSAN_HORIZONANIM, 0.0f),
			D3DXVECTOR2(m_nHorizonAnim[nCnt] * MARKHOSSAN_HORIZONANIM + MARKHOSSAN_HORIZONANIM, 1.0f));
	}
}

// ----------------------------------------
// �ʒu�E�T�C�Y�̐ݒ菈��
// ----------------------------------------
void CMark::SetPos(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_pos = pos;
	m_size = size;
	// �ʒu�̐ݒ�
	m_aScene_Two[0]->SetPosition({ pos.x - size.x / 2,pos.y,0.0f });
	m_aScene_Two[1]->SetPosition({ pos.x + size.x / 2,pos.y,0.0f });
}

// ----------------------------------------
// �ڕW�̈ʒu�E�T�C�Y�̐ݒ菈��
// ----------------------------------------
void CMark::SetPosGoal(D3DXVECTOR3 pos, D3DXVECTOR2 size)
{
	m_posGoal = pos;
	m_sizeGoal = size;
}

// ----------------------------------------
// �ʒu���擾����
// ----------------------------------------
D3DXVECTOR3 CMark::GetPos(void)
{
	return m_pos;
}

// ----------------------------------------
// �T�C�Y���擾����
// ----------------------------------------
D3DXVECTOR2 CMark::GetSize(void)
{
	return m_size;
}