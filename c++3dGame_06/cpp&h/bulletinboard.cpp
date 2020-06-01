// ----------------------------------------
//
// �f�������̐���[bulletinboard.h]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "bulletinboard.h"
#include "debugproc.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define BULLETINBOARD_COLLISION_SIZE (30.0f)

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CBulletinBoard::m_pTexture[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
CLoad	*CBulletinBoard::m_pload = NULL;								// ���[�h
int		CBulletinBoard::m_nAll = 0;									// �ԍ�

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CBulletinBoard::CBulletinBoard()
{
	// �ϐ��̏�����
	m_Type = TYPE_A;
	m_fLengh = 0;
	m_fAngle = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nCntAnim = 0;
	m_TexFirst = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLast = D3DXVECTOR2(0.2f, 1.0f);
	m_TexFirstSign = m_TexFirst;
	m_TexLastSign = m_TexLast;
}

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CBulletinBoard::CBulletinBoard(ACTOR actor, LAYER layer) : CScene_THREE::CScene_THREE(actor, layer)
{
	// �ϐ��̏�����
	m_fLengh = 0;
	m_fAngle = 0;
	m_Type = TYPE_A;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nCntAnim = 0;
	m_TexFirst = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLast = D3DXVECTOR2(0.2f, 1.0f);
	m_TexFirstSign = m_TexFirst;
	m_TexLastSign = m_TexLast;
}


// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CBulletinBoard::~CBulletinBoard()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CBulletinBoard::Init(void)
{
	// �V�[��3D�̏�����
	CScene_THREE::Init();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CBulletinBoard::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CBulletinBoard::Update(void)
{
	// ��������s�����ɂ���
	Transparency(STATE_EMERGENCE);

	// �A�j���[�V�����̍X�V
	SetAnim();

	CScene_THREE::Update();

	// �e�N�X�`�����W�̊m�F
	CDebugproc::Print("�e�N�X�`�����W : %.2f,%.2f \n", m_TexFirst.x, m_TexLast.x);
	CDebugproc::Print("�e�N�X�`�����W : %.2f,%.2f \n", m_TexFirstSign.x, m_TexLastSign.x);
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CBulletinBoard::Draw(void)
{
	// �`����@�̕ύX
	//if (m_col.a <= 1.0f)
	//{
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

		// �`��
		CScene_THREE::Draw();

		//�A���t�@�e�X�g�߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//Z�o�b�t�@�@�L���@����
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
		// ���C�e�B���O���[�h�L��
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

		// �����_�[�X�e�[�g(�ʏ�u�����h����)
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	//}

	//else
	//{
	//	// �ϐ��錾
	//	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
	//		CManager::GetRenderer()->GetDevice();
	//	// �A���t�@�e�X�g�̐ݒ�ɕύX
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// �A���t�@�e�X�g�L��
	//	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);				// �A���t�@�l�̊�ݒ�(����傫���ƕ`�悷��)
	//	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// �󋵂ɉ����ăA���t�@�e�X�g�����s����(�V�s�N�Z�� > ���݂̃s�N�Z��)
	//	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ���C�e�B���Ooff

	//	// �`��
	//	CScene_THREE::Draw();
	//	// �A���t�@�e�X�g�̐ݒ��߂�
	//	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// �A���t�@�e�X�g����
	//	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ���C�e�B���Oon
	//}
}

// ----------------------------------------
// �e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CBulletinBoard::SetTexture(TYPE type)
{
	// �ݒ�
	CScene_THREE::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CBulletinBoard * CBulletinBoard::Create(void)
{
	// �ϐ��錾
	CBulletinBoard * pBulletinBoard;		// �V�[��3D�N���X
						// �������̐���(����->��{�N���X,��->�h���N���X)
	pBulletinBoard = new CBulletinBoard(ACTOR_BULLETINBOARD, LAYER_3DOBJECT);
	// ����������
	pBulletinBoard->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pBulletinBoard;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CBulletinBoard::LoadCreate(void)
{
	// �ϐ��錾
	CBulletinBoard * pBulletinBoard;
	// �ǂݍ��񂾐�����
	for (int nCntItem = 0; nCntItem < m_nAll; nCntItem++)
	{
		// ����
		pBulletinBoard = CBulletinBoard::Create();
		// �e�N�X�`���[��ݒ�
		pBulletinBoard->SetTexture((TYPE)m_pload->GetInfo(nCntItem).nType);
		// �^�C�v��ݒ�
		pBulletinBoard->m_Type = (TYPE)m_pload->GetInfo(nCntItem).nType;
		// ���W��ݒ�
		pBulletinBoard->SetPos(m_pload->GetInfo(nCntItem).pos);
		// ��]��ݒ�
		pBulletinBoard->SetRot(m_pload->GetInfo(nCntItem).rot);
		// �傫����ݒ�
		pBulletinBoard->SetSize(m_pload->GetInfo(nCntItem).size);
		// �F����ݒ�
		pBulletinBoard->m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
		// �F��ݒ�
		pBulletinBoard->SetCol(pBulletinBoard->m_col);
		// �e�N�X�`�����W��ݒ�
		pBulletinBoard->SetTex(D3DXVECTOR2(0.0f, 0.0f), D3DXVECTOR2(0.2f, 1.0f));
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CBulletinBoard::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/TUTORIAL/Board000.png",
		"data/TEXTURE/obj_tex/Board01.png",
		"data/TEXTURE/obj_tex/Board02.png"
	};

	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ���[�h����
	m_pload = new CLoad;
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Board_Location.txt");

	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CBulletinBoard::UnLoad(void)
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
	// ���[�h�̔j��
	delete m_pload;
	m_pload = NULL;
}

// ----------------------------------------
// �A�j���[�V�����̐ݒ�
// ----------------------------------------
void CBulletinBoard::SetAnim(void)
{
	//�J�E���^�[���Z
	m_nCntAnim++;

	// �t���[�����ƂɍX�V
	if (m_nCntAnim % (ONEMIN * 2) == 0)
	{
		// ���X�̓A�j���[�V����
		m_TexFirst.x += 0.2f;
		m_TexLast.x += 0.2f;
	}

	// �ڕW�̃e�N�X�`�����W�ɂȂ�܂ŉ��Z
	else if (m_TexFirstSign.x < m_TexFirst.x && m_TexLastSign.x < m_TexLast.x)
	{
		// �e�N�X�`�����W���Z
		m_TexFirstSign.x += 0.005f;
		m_TexLastSign.x += 0.005f;

		// �ڕW�𒴂�����ڕW�̍��W�����������Ȃ��悤�ɂ���
		if (m_TexFirst.x <= m_TexFirstSign.x)
		{
			m_TexFirstSign.x = m_TexFirst.x;
		}
		// �ڕW�𒴂�����ڕW�̍��W�����������Ȃ��悤�ɂ���
		if (m_TexLast.x <= m_TexLastSign.x)
		{
			m_TexLastSign.x = m_TexLast.x;
		}
	}

	// �e�N�X�`�����W�̍X�V
	SetTex(D3DXVECTOR2(m_TexFirstSign.x, m_TexFirstSign.y), D3DXVECTOR2(m_TexLastSign.x, m_TexLastSign.y));
}


// ----------------------------------------
// ���[�h�擾
// ----------------------------------------
CLoad * CBulletinBoard::GetLoad(void)
{
	return m_pload;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CBulletinBoard::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CBulletinBoard::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CBulletinBoard::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CBulletinBoard::SetCol(D3DXCOLOR col)
{
	CScene_THREE::SetCol(col);
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CBulletinBoard::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_THREE::SetTex(first, last);
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CBulletinBoard::Transparency(STATE state)
{
	switch (state)
	{
		// �o��
	case STATE_EMERGENCE:
		// ���X�Ƀ��l�����Z
		if (m_col.a <= 1.0f)
		{
			//���X�ɓ����ɂ���
			m_col.a += 0.01f;
			//�F�̍X�V
			SetCol(m_col);
		}
		break;

		// ����
	case STATE_DISAPPEARANCE:
		// ���X�ɓ�����������
		if (m_col.a >= 0.0f)
		{
			//���X�ɓ����ɂ���
			m_col.a -= 0.01f;
			//�F�̍X�V
			SetCol(m_col);
		}
		if (m_col.a <= 0.0f)
		{
			Release();
		}
		break;

	default:
		break;
	}
}


// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR3 CBulletinBoard::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// ��]�̎擾����
// ----------------------------------------
D3DXVECTOR3 CBulletinBoard::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CBulletinBoard::GetPos(void)
{
	return CScene_THREE::GetPos();
}
