// ----------------------------------------
//
// �e���b�v�R�����g�����̐���[telopcomment.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "telopcomment.h"
#include "title.h"
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
LPDIRECT3DTEXTURE9 CTelopComment::m_pTexture[TYPE_MAX] = {};
bool CTelopComment::bEndPhase = false;
CTelopComment::PHASE CTelopComment::m_phase = PHASE_NONE;
int CTelopComment::m_nCreateCount = 0;
// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CTelopComment::CTelopComment() : CScene_TWO::CScene_TWO(ACTOR_TELOPCOMMENT, LAYER_UI)
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_size = D3DXVECTOR2(0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);
	m_nCreateCount = 0;
	bDisFlag = false;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CTelopComment::~CTelopComment()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTelopComment::Init(void)
{
	CScene_TWO::Init();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CTelopComment::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CTelopComment::Update(void)
{
	//���Ńt���O�������Ă��Ȃ�������
	if (bDisFlag == false)
	{
		// �s�����x�����Z
		Transparency(STATE_EMERGENCE);
	}
	CScene_TWO::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CTelopComment::Draw(void)
{
	CScene_TWO::Draw();
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CTelopComment::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[TYPE_MAX][72] =
	{
		"data/TEXTURE/TUTORIAL/Comment000.png",
		"data/TEXTURE/TUTORIAL/Comment001.png",
		"data/TEXTURE/TUTORIAL/Comment002.png",
		"data/TEXTURE/TUTORIAL/Comment003.png",
		"data/TEXTURE/TUTORIAL/Comment004.png",
		/*"data/TEXTURE/UI/Comment003.png",
		"data/TEXTURE/UI/Comment004.png",*/
	};

	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���[����������
		if (strcmp(TexData[nCnt], "") != 0)
		{
			D3DXCreateTextureFromFile(pDevice, TexData[nCnt], &m_pTexture[nCnt]);
		}
	}

	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CTelopComment::UnLoad(void)
{
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		// �e�N�X�`���̊J��
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CTelopComment * CTelopComment::Create(D3DXVECTOR3 pos, D3DXVECTOR2 size,TYPE type)
{
	// �ϐ��錾
	CTelopComment * pTelopComment;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pTelopComment = new CTelopComment();
	// �e�N�X�`���̐ݒ�
	pTelopComment->BindTexture(m_pTexture[type]);
	// ����������
	pTelopComment->Init();
	// ���W�̐ݒ�
	pTelopComment->SetPosition(pos);
	// �傫���̔��f
	pTelopComment->SetSize(size);
	// �����܂ł̎��Ԃ����Z�b�g����
	m_nCreateCount = 0;
	// ���������I�u�W�F�N�g��Ԃ�
	return pTelopComment;
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
void CTelopComment::CreateTelopCommnet(PHASE phase)
{
	switch (phase)
	{
	case PHASE_NONE:
		break;

	case PHASE_ONE:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_0);
		break;

	case PHASE_TWO:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_1);
		break;

	case PHASE_THREE:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_2);
		break;

	case PHASE_FOUR:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_3);
		break;

	case PHASE_FIVE:
		CTelopComment::Create(TELOP_POS, TELOP_SIZE, CTelopComment::TYPE_4);
		bEndPhase = true;
		break;

	case PHASE_END:
		bEndPhase = true;
		break;

	default:
		break;
	}
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTelopComment::Transparency(STATE state)
{
	switch (state)
	{
		// �o��
	case STATE_EMERGENCE:
		// ���X�Ƀ��l�����Z
		if (m_col.a <= 1.0f)
		{
			//���X�ɕs�����ɂ���
			m_col.a += 0.03f;
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
			m_col.a -= 0.5f;
			//�F�̍X�V
			SetCol(m_col);
		}
		// �����ɂȂ�����폜
		if (m_col.a <= 0.0f)
		{
		}
		// �폜
		Release();
		break;

	default:
		break;
	}
}

// ----------------------------------------
// ���̃t�F�C�Y��
// ----------------------------------------
void CTelopComment::SetPhase(void)
{
	// �ϐ��̏�����
	CTelopComment *pTelopComment = NULL;

	// �R�����g�̃|�C���^������
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pTelopComment = (CTelopComment *)CScene::GetActor(CScene::ACTOR_TELOPCOMMENT, CScene::LAYER_UI, nCntlayer)) break;
	}

	// ���̃t�F�C�Y�Ɉڍs
	switch (m_phase)
	{
	case PHASE_NONE:
		m_phase = PHASE_ONE;
		break;

	case PHASE_ONE:
		m_phase = PHASE_TWO;
		break;

	case PHASE_TWO:
		m_phase = PHASE_THREE;
		break;

	case PHASE_THREE:
		m_phase = PHASE_FOUR;
		break;

	case PHASE_FOUR:
		m_phase = PHASE_FIVE;
		break;

	case PHASE_FIVE:
		m_phase = PHASE_END;
		break;

	case PHASE_END:
		bEndPhase = true;
		break;

	default:
		break;
	}

	// �R�����g�����݂��Ă�����
	if (pTelopComment != NULL)
	{
		// ���Ńt���O��true�ɂ���
		pTelopComment->bDisFlag = true;
		// ���݂̃R�����g���폜
		pTelopComment->Release();
	}

	if (m_phase != PHASE_NONE)
	{
		// �R�����g�̐���
		CreateTelopCommnet(m_phase);
	}

	// �V�����t�F�C�Y�̏���
	Phase();
}

// ----------------------------------------
// �t�F�C�Y���Ƃɍs������
// ----------------------------------------
void CTelopComment::Phase(void)
{
	switch (m_phase)
	{
	case PHASE_ONE:
		break;

	case PHASE_TWO:
		break;

	case PHASE_THREE:
		break;

	case PHASE_FOUR:
		break;

	case PHASE_FIVE:
		break;

	case PHASE_END:
		// �I���t���O��true�ɂ���
		bEndPhase = true;
		break;

	default:
		break;
	}

	// �^�C�g���t���O��false�ɂ���
	CManager::GetTitle()->SetEnterflag();
}

// ----------------------------------------
// �t�F�C�Y���I���������̔�����擾
// ----------------------------------------
bool CTelopComment::GetEndPhaseFlag(void)
{
	return bEndPhase;
}

// ----------------------------------------
// ���݂̃t�F�C�Y�̎擾
// ----------------------------------------
CTelopComment::PHASE CTelopComment::GetPhase(void)
{
	return m_phase;
}
