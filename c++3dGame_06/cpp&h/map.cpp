// ----------------------------------------
//
// �}�b�v�����̐���[map.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "map.h"
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
LPDIRECT3DTEXTURE9 CMap::m_pTex[MAP_UI_MAX] = {};
D3DXVECTOR3 CMap::m_pos[MAP_UI_MAX] = {};
D3DXVECTOR2 CMap::m_size[MAP_UI_MAX] = {};
CMap::MAP_UI_TYPE CMap::m_type[MAP_UI_MAX] = {};
// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CMap::CMap() : CScene::CScene(ACTOR_MAP, LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CMap::~CMap()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CMap::Init(void)
{
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->SetSize(m_size[nCnt]);
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
		m_aScene_Two[nCnt]->BindTexture(m_pTex[nCnt]);
	}

	CMapMark::Create();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CMap::Uninit(void)
{
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
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
void CMap::Update(void)
{
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// ��ނɂ���ď�����ς���
			m_aScene_Two[nCnt]->Update();
		}
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CMap::Draw(void)
{
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// ��ނɂ���ď�����ς���
			m_aScene_Two[nCnt]->Draw();
		}
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CMap::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���[�����
	char TexData[MAP_UI_MAX][72] =
	{
		"data/TEXTURE/MAP/Map000.png",
		"data/TEXTURE/MAP/Frame.png",
		"data/TEXTURE/MAP/Map_Mission00.png",
	};
	// �ʒu�����
	D3DXVECTOR3 pos[MAP_UI_MAX] =
	{
		D3DXVECTOR3(1100.0f,180,0.0f),
		D3DXVECTOR3(1100.0f,350.0f,0.0f),
		D3DXVECTOR3(1100.0f,350.0f,0.0f),
	};
	// �T�C�Y�����
	D3DXVECTOR2 size[MAP_UI_MAX] =
	{
		D3DXVECTOR2(248.8f,260.8f),
		D3DXVECTOR2(250.0f,50.0f),
		D3DXVECTOR2(250.0f,30.0f),
	};
	//
	MAP_UI_TYPE type[MAP_UI_MAX] =
	{
		MAP_UI_MAP,
		MAP_UI_FRAME,
		MAP_UI_MISSION00,
	};

	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
	{
		// �e�N�X�`���[����������
		if (strcmp(TexData[nCnt], "") != 0)
		{
			/* �e�N�X�`���[�̃��[�h */
			D3DXCreateTextureFromFile(pDevice, TexData[nCnt], &m_pTex[nCnt]);
			/* �ʒu�E�T�C�Y�� �^�C�v�̃��[�h */
			m_pos[nCnt] = pos[nCnt];
			m_size[nCnt] = size[nCnt];
			m_type[nCnt] = type[nCnt];
		}
	}
	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CMap::UnLoad(void)
{
	// �e�N�X�`���̊J��
	for (int nCnt = 0; nCnt < MAP_UI_MAX; nCnt++)
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
CMap * CMap::Create(void)
{
	// �ϐ��錾
	CMap * pMap;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pMap = new CMap();
	// ����������
	pMap->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pMap;
}
