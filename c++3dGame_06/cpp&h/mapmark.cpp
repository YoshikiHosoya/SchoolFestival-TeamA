// ----------------------------------------
//
// �}�b�v�}�[�N�����̐���[mapmark.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "mapmark.h"
#include "player.h"
#include "renderer.h"
#include "camera.h"
//#include "warp.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
//#define MARK_SIZE (10.0f)
#define MARK_SIZE (8.0f)

//#define MAPMARK_MOVESPEED_MINUS (-0.25f)
//#define MAPMARK_MOVESPEED_PLUS (0.25f)
//#define MAPMARK_MOVESPEED_MINUS (-0.50f)
//#define MAPMARK_MOVESPEED_PLUS (0.50f)
//
//#define MAPMARK_MOVESPEED_MINUS2 (-0.50f)
//#define MAPMARK_MOVESPEED_PLUS2 (0.50f)

#define MAPMARK_MOVESPEED_MINUS (-0.50f)
#define MAPMARK_MOVESPEED_PLUS (0.50f)
#define MAPMARK_MOVESPEED_MINUS2 (-0.50f)
#define MAPMARK_MOVESPEED_PLUS2 (0.50f)

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
D3DXVECTOR3 CMapMark::m_pos[TOTAL_MARK] = {};
D3DXVECTOR2 CMapMark::m_size[MAP_MARK_MAX] = {};
D3DXCOLOR CMapMark::m_col[MAP_MARK_MAX] = {};
CMapMark::MAP_MARK_TYPE CMapMark::m_type[MAP_MARK_MAX] = {};
//D3DXVECTOR3	CMapMark::m_move[TOTAL_MARK] = {};			// �ʒu���

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CMapMark::CMapMark() : CScene::CScene(ACTOR_MAPMARK, LAYER_UI)
{
	// ������
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		m_aScene_Two[nCnt] = NULL;
	}

	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nCount = 0;
	//m_pos[35] = D3DXVECTOR3(1098.0f, 297.0f, 0.0f);	// �v���C���[
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CMapMark::~CMapMark()
{
	m_pos[35] = D3DXVECTOR3(1098.0f, 285.0f, 0.0f);	// �v���C���[
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CMapMark::Init(void)
{
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		m_aScene_Two[nCnt] = new CScene_TWO;
		m_aScene_Two[nCnt]->Init();
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);

		if (nCnt >= MAX_SHARDMARK)
		{
			m_nCount++;
		}

		if (m_type[MAP_MARK_SHARD] == MAP_MARK_SHARD)
		{
			m_aScene_Two[nCnt]->SetCol(m_col[m_nCount]);
		}
		else if (m_type[MAP_MARK_PLAYER] == MAP_MARK_PLAYER)
		{
			m_aScene_Two[nCnt]->SetCol(m_col[m_nCount]);
		}
		/*else if (m_type[MAP_MARK_ENEMY] == MAP_MARK_ENEMY)
		{
			m_aScene_Two[nCnt]->SetCol(m_col[m_nCount]);
		}*/

		m_aScene_Two[nCnt]->SetSize(m_size[m_nCount]);
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CMapMark::Uninit(void)
{
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			m_aScene_Two[nCnt]->Uninit();
			delete m_aScene_Two[nCnt];
			m_aScene_Two[nCnt] = NULL;
		}
	}
}

int g_nCnt = 0;
// ----------------------------------------
// �X�V����
// ----------------------------------------
void CMapMark::Update(void)
{
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		if (m_aScene_Two[nCnt] != NULL)
		{
			// ��ނɂ���ď�����ς���
			Various(nCnt);
			// ��ނɂ���ď�����ς���
			m_aScene_Two[nCnt]->Update();
		}
	}

	//if (g_nCnt <= MAX_SHARDMARK)
	//{
	//	if (CManager::GetKeyboard()->GetKeyboardTrigger(DIK_0))
	//	{
	//		if (m_aScene_Two[g_nCnt] != NULL)
	//		{
	//			m_aScene_Two[g_nCnt]->Release();
	//			m_aScene_Two[g_nCnt] = NULL;
	//			//m_aScene_Two[g_nCnt]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	//		}
	//		g_nCnt++;
	//	}
	//}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CMapMark::Draw(void)
{
	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
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
HRESULT CMapMark::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice =
		CManager::GetRenderer()->GetDevice();

	// �ʒu�����
	D3DXVECTOR3 pos[TOTAL_MARK] =
	{
		D3DXVECTOR3(1005.0f,61.5f,0.0f),	// ����00�Z
		D3DXVECTOR3(1048.0f,61.5f,0.0f),	// ����01�Z
		D3DXVECTOR3(1151.7f,61.5f,0.0f),	// ����02�Z
		D3DXVECTOR3(1199.0f,61.5f,0.0f),	// ����03�Z

		D3DXVECTOR3(992.0f,71.5f,0.0f),		// ����04�Z
		D3DXVECTOR3(1208.0f,71.5f,0.0f),	// ����05�Z

		D3DXVECTOR3(1067.5f,89.0f,0.0f),	// ����06�Z
		D3DXVECTOR3(1133.0f,89.0f,0.0f),	// ����07�Z

		D3DXVECTOR3(1067.5f,106.5f,0.0f),	// ����08�Z
		D3DXVECTOR3(1133.0f,106.5f,0.0f),	// ����09�Z

		D3DXVECTOR3(992.0f,123.0f,0.0f),	// ����10�Z
		D3DXVECTOR3(1067.5f,123.0f,0.0f),	// ����11�Z
		D3DXVECTOR3(1208.0f,123.0f,0.0f),	// ����12�Z

		D3DXVECTOR3(1077.5f,130.0f,0.0f),	// ����13�Z
		D3DXVECTOR3(1142.0f,130.0f,0.0f),	// ����14�Z

		D3DXVECTOR3(992.0f,138.0f,0.0f),	// ����15�Z
		D3DXVECTOR3(1035.0f,138.0f,0.0f),	// ����16�Z
		D3DXVECTOR3(1165.0f,138.0f,0.0f),	// ����17�Z

		D3DXVECTOR3(1089.5f,164.0f,0.0f),	// ����18�Z
		D3DXVECTOR3(1109.5f,164.0f,0.0f),	// ����19�Z

		D3DXVECTOR3(992.0f,170.0f,0.0f),	// ����20�Z
		D3DXVECTOR3(1035.0f,170.0f,0.0f),	// ����21�Z
		D3DXVECTOR3(1077.5f,170.0f,0.0f),	// ����22�Z
		D3DXVECTOR3(1121.5f,170.0f,0.0f),	// ����23�Z
		D3DXVECTOR3(1165.0f,170.0f,0.0f),	// ����24�Z

		D3DXVECTOR3(1002.0f,180.0f,0.0f),	// ����25�Z
		D3DXVECTOR3(1045.0f,180.0f,0.0f),	// ����26�Z
		D3DXVECTOR3(1155.0f,180.0f,0.0f),	// ����27�Z
		D3DXVECTOR3(1195.0f,180.0f,0.0f),	// ����28�Z

		D3DXVECTOR3(1035.0f,190.0f,0.0f),	// ����29�Z
		D3DXVECTOR3(1077.5f,190.0f,0.0f),	// ����30�Z
		D3DXVECTOR3(1121.5f,190.0f,0.0f),	// ����31�Z
		D3DXVECTOR3(1165.0f,190.0f,0.0f),	// ����32�Z
		D3DXVECTOR3(1208.0f,190.0f,0.0f),	// ����33�Z

		D3DXVECTOR3(1089.5f,197.5f,0.0f),	// ����34�Z
		D3DXVECTOR3(1109.5f,197.5f,0.0f),	// ����35�Z

		D3DXVECTOR3(1035.0f,222.0f,0.0f),	// ����36�Z
		D3DXVECTOR3(1165.0f,222.0f,0.0f),	// ����37�Z
		D3DXVECTOR3(1208.0f,222.0f,0.0f),	// ����38�Z

		D3DXVECTOR3(1055.0f,230.0f,0.0f),	// ����39�Z
		D3DXVECTOR3(1121.5f,230.0f,0.0f),	// ����40�Z

		D3DXVECTOR3(992.0f,240.0f,0.0f),	// ����41�Z
		D3DXVECTOR3(1133.0f,240.0f,0.0f),	// ����42�Z
		D3DXVECTOR3(1208.0f,240.0f,0.0f),	// ����43�Z

		D3DXVECTOR3(1067.5f,255.0f,0.0f),	// ����44�Z
		D3DXVECTOR3(1133.0f,255.0f,0.0f),	// ����45�Z

		D3DXVECTOR3(1067.5f,272.0f,0.0f),	// ����46�Z
		D3DXVECTOR3(1133.0f,272.0f,0.0f),	// ����47�Z

		D3DXVECTOR3(992.0f,290.0f,0.0f),	// ����48�Z
		D3DXVECTOR3(1208.0f,290.0f,0.0f),	// ����49�Z

		D3DXVECTOR3(1005.0f,298.0f,0.0f),	// ����50�Z
		D3DXVECTOR3(1048.0f,298.0f,0.0f),	// ����51�Z
		D3DXVECTOR3(1155.0f,298.0f,0.0f),	// ����52�Z
		D3DXVECTOR3(1198.0f,298.0f,0.0f),	// ����53�Z

		D3DXVECTOR3(1100.0f,180.0f,0.0f),	// �v���C���[
	};
	// �T�C�Y�����
	D3DXVECTOR2 size[MAP_MARK_MAX] =
	{
		D3DXVECTOR2(MARK_SIZE,MARK_SIZE),
		D3DXVECTOR2(MARK_SIZE,MARK_SIZE),
	};
	// �F�����
	D3DXCOLOR col[MAP_MARK_MAX] =
	{
		COLOR_PURPLE,
		COLOR_BLUE,
		//COLOR_RED,
	};
	// �^�C�v�̑��
	MAP_MARK_TYPE type[MAP_MARK_MAX] =
	{
		MAP_MARK_SHARD,
		MAP_MARK_PLAYER,
	};

	for (int nCnt = 0; nCnt < MAP_MARK_MAX; nCnt++)
	{
		// �傫�� ��� �F
		m_size[nCnt] = size[nCnt];
		m_type[nCnt] = type[nCnt];
		m_col[nCnt] = col[nCnt];
	}

	for (int nCnt = 0; nCnt < TOTAL_MARK; nCnt++)
	{
		// �ʒu
		m_pos[nCnt] = pos[nCnt];
	}
	return S_OK;
}

// ----------------------------------------
// �ǂݍ��񂾏���j��
// ----------------------------------------
void CMapMark::UnLoad(void)
{
}

// ----------------------------------------
// ������3D�A�C�e���Ɠ���Id�����}�[�J�[���폜����
// ----------------------------------------
void CMapMark::ReleseMaker(int nId)
{
	if (m_aScene_Two[nId] != NULL)
	{
		m_aScene_Two[nId]->Release();
		m_aScene_Two[nId] = NULL;
	}
}

// ----------------------------------------
// ���W�̍X�V
// ----------------------------------------
void CMapMark::SetMapMaker(D3DXVECTOR3 pos)
{
	m_aScene_Two[36]->SetPosition(pos);
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CMapMark * CMapMark::Create(void)
{
	// �ϐ��錾
	CMapMark * pMapMark;
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pMapMark = new CMapMark();
	// ����������
	pMapMark->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pMapMark;
}

// ----------------------------------------
// ��ޕʂ̏���
// ----------------------------------------
void CMapMark::Various(int nCnt)
{
	CPlayer *pPlayer = NULL;

	int nValueH = 0;//�X�e�B�b�N�̉�
	int nValueV = 0;//�X�e�B�b�N�̏c

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	m_move.x = pPlayer->GetMove().x * 0.9f;
	m_move.y = pPlayer->GetMove().z * -0.9f;

	if (m_aScene_Two[nCnt] == m_aScene_Two[TOTAL_MARK-1])
	{
		m_pos[nCnt].x += (m_move.x / 22.0f);
		m_pos[nCnt].y += (m_move.y / 29.0f);
		m_aScene_Two[nCnt]->SetPosition(m_pos[nCnt]);
	}
}