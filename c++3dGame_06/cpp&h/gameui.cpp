// ----------------------------------------
//
// �|�[�Y�pui�����̐���[tutorial_ui.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
/* �`�� */
#include "gameui.h"
#include "player.h"
#include "key.h"
#include "mapmark.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

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
LPDIRECT3DTEXTURE9	CGame_ui::m_pTex[MAX_GAME_UI_TEX] = {};
D3DXVECTOR3			CGame_ui::m_pos[MAX_GAME_UI]  = {};
D3DXVECTOR2			CGame_ui::m_size[MAX_GAME_UI] = {};
bool				CGame_ui::m_bUse[MAX_GAME_UI] = {};
int					CGame_ui::m_nAP = 0;
// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CGame_ui::CGame_ui() : CScene::CScene(ACTOR_GAME_UI, LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
	m_fMult = 1.0f;
	m_fAdd = 0.001f;
	m_nCntCol = 0;
	m_nSelect = 0;
	m_fAnim = 0;
	//m_nAP = 0;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CGame_ui::~CGame_ui()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CGame_ui::Init(void)
{
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		if (nCnt == GAME_UI_KEY0 || nCnt == GAME_UI_KEY1 || nCnt == GAME_UI_KEY2)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[0]);
		}
		else if (nCnt == GAME_UI_LOCK0 || nCnt == GAME_UI_LOCK1 || nCnt == GAME_UI_LOCK2)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[1]);
		}
		else if (nCnt == GAME_UI_ACTIONBUTTON)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[2]);
		}
		else if (nCnt == GAME_UI_MISSION0)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[3]);
		}
		else if (nCnt == GAME_UI_MISSION1)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[4]);
		}
		else if (nCnt == GAME_UI_MAP)
		{
			m_aScene_Two[nCnt]->BindTexture(m_pTex[5]);
		}

		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
	}

	CMapMark::Create();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CGame_ui::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
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
void CGame_ui::Update(void)
{
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// ��ނɂ���ď�����ς���
			m_aScene_Two[nCnt]->Update();
		}
	}

	// ��ނɂ���ď�����ς���
	Various();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CGame_ui::Draw(void)
{
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// �`�����
			ConditionalDraw(nCnt);
		}
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CGame_ui::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =		// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[MAX_GAME_UI_TEX][72] =
	{
		"data/TEXTURE/GAME/key.png",
		"data/TEXTURE/GAME/lock.png",
		"data/TEXTURE/GAME/ActionButton000.png",
		"data/TEXTURE/GAME/Mission000.png",
		"data/TEXTURE/GAME/Mission001.png",
		"data/TEXTURE/GAME/Map000.png",
	};
	// �ʒu�����
	D3DXVECTOR3 pos[MAX_GAME_UI] =
	{
		D3DXVECTOR3(1040.0f,450,0.0f),
		D3DXVECTOR3(1120.0f,450,0.0f),
		D3DXVECTOR3(1200.0f,450,0.0f),
		D3DXVECTOR3(1040.0f,450,0.0f),
		D3DXVECTOR3(1120.0f,450,0.0f),
		D3DXVECTOR3(1200.0f,450,0.0f),
		D3DXVECTOR3(640.0f,650.0f,0.0f),
		D3DXVECTOR3(1100.0f,350.0f,0.0f),
		D3DXVECTOR3(1100.0f,350.0f,0.0f),
		D3DXVECTOR3(1100.0f,180,0.0f),
	};
	// �T�C�Y�����
	D3DXVECTOR2 size[MAX_GAME_UI] =
	{
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(GAME_UI_SIZE_X,GAME_UI_SIZE_Y),
		D3DXVECTOR2(ACTIONBUTTON_SIZE_X,ACTIONBUTTON_SIZE_Y),
		D3DXVECTOR2(250.0f,30.0f),
		D3DXVECTOR2(250.0f,30.0f),
		D3DXVECTOR2(248.8f,260.8f),
	};

	// �����`��t���O���
	bool flag[MAX_GAME_UI] =
	{
		false,
		false,
		false,
		true,
		true,
		true,
		false,
		true,
		false,
		true,
	};


	for (int nTexCnt = 0; nTexCnt < MAX_GAME_UI_TEX; nTexCnt++)
	{
		/* �e�N�X�`���[�̃��[�h */
		D3DXCreateTextureFromFile(pDevice, TexData[nTexCnt], &m_pTex[nTexCnt]);
	}
	for (int nCnt = 0; nCnt < MAX_GAME_UI; nCnt++)
	{
		/* �ʒu�E�T�C�Y�̃��[�h */
		m_pos[nCnt]  = pos[nCnt];
		m_size[nCnt] = size[nCnt];
		m_bUse[nCnt] = flag[nCnt];
	}
	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CGame_ui::UnLoad(void)
{
	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < MAX_GAME_UI_TEX; nCnt++)
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
CGame_ui * CGame_ui::Create(void)
{
	// �ϐ��錾
	CGame_ui * pGame_ui;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pGame_ui = new CGame_ui();
	// ����������
	pGame_ui->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pGame_ui;
}

// ----------------------------------------
// �`�悷�邽�߂̏���
// ----------------------------------------
void CGame_ui::ConditionalDraw(int nCnt)
{
	if (m_bUse[nCnt] == true)
	{
		// ��ނɂ���ď�����ς���
		m_aScene_Two[nCnt]->Draw();
	}
}

// ----------------------------------------
// �`��t���O��ύX���鏈��
// ----------------------------------------
void CGame_ui::SetDrawFlag(int nCnt)
{
	m_bUse[nCnt] = false;
}

// ----------------------------------------
// ��ޕʂ̏���
// ----------------------------------------
void CGame_ui::Various()
{
	for (int nCntAP = 0; nCntAP < 3; nCntAP++)
	{
		if (m_nAP >= ABILITYPOINT * (nCntAP + 1))
		{
			m_bUse[nCntAP] = true;
			m_bUse[nCntAP + 3] = false;
		}
		else if (m_nAP <= ABILITYPOINT * (nCntAP + 1))
		{
			m_bUse[nCntAP] = false;
			m_bUse[nCntAP + 3] = true;
		}
	}

	// �����擾������
	if (CKey::bGetFlag())
	{
		m_bUse[GAME_UI_MISSION0] = false;
		m_bUse[GAME_UI_MISSION1] = true;
	}

	CPlayer *pPlayer = NULL;	// �v���C���[
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}
	if (m_bUse[0] == true && pPlayer->GetAbilityFlag() != true)
	{
		m_bUse[GAME_UI_ACTIONBUTTON] = true;
	}
	else if (m_bUse[0] == false || pPlayer->GetAbilityFlag() == true)
	{
		m_bUse[GAME_UI_ACTIONBUTTON] = false;
	}

}

// ----------------------------------------
// AP�̌v�Z
// ----------------------------------------
void CGame_ui::SetAP(int number)
{
	if (m_nAP < (ABILITYPOINT*3))
	{
		m_nAP += number;
	}
}

// ----------------------------------------
// �t���O�̎擾
// ----------------------------------------
bool CGame_ui::GetbUse(void)
{
	return m_bUse[0];
}
