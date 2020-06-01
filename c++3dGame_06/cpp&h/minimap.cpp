// ----------------------------------------
//
// �~�j�}�b�v�����̐���[minimap.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "minimap.h"
#include "debugproc.h"
#include "player.h"
#include "enemy.h"
#include "3ditem.h"
#include "input.h"
#include "camera.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAP_UI_ANIM (2)
#define MAP_UI_SPLIT (1.0f / MAP_UI_ANIM)

#define MAP_TEX_X0 (0.4f)
#define MAP_TEX_Y0 (0.4f)
#define MAP_TEX_X1 (1.0f)
#define MAP_TEX_Y1 (1.0f)

#define MAP_MOVESPEED (0.001f)
#define MAP_ZERO (0.0000f)

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9	CMinimap::m_pTexture[MINIMAP_UI_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
CLoad2D				*CMinimap::m_pload2D = NULL;						// ���[�h
int					CMinimap::m_nAll = 0;							// �ԍ�
// ----------------------------------------
// �R���X�g���N�^
// ----------------------------------------
CMinimap::CMinimap() : CScene_TWO::CScene_TWO(ACTOR_MAP_UI, LAYER_UI)
{
	m_fMult = 0.0f;									// �{��
	m_fAdd = 0.0f;									// ���Z
	m_nRange = 0;									// �`�悷�镝
	m_state = MINIMAP_STATE_NORMAL;
	m_type = MINIMAP_UI_MAP;
	m_rot = 0.0f;
	m_TexFirst = D3DXVECTOR2(MAP_TEX_X0, MAP_TEX_Y0);
	m_TexLast = D3DXVECTOR2(MAP_TEX_X1, MAP_TEX_Y1);
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_TexFirstMove = D3DXVECTOR2(0.0f, 0.0f);
	m_TexLastMove = D3DXVECTOR2(0.0f, 0.0f);
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CMinimap::~CMinimap()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CMinimap::Init(void)
{
	// �V�[��3D�̏�����
	CScene_TWO::Init();
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CMinimap::Uninit(void)
{
	CScene_TWO::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CMinimap::Update(void)
{
	CScene_TWO::Update();

	if (m_type == MINIMAP_UI_MAP || m_type == MINIMAP_UI_SHARD_POS || m_type == MINIMAP_UI_PLAYER_POS)
	{
		MAP_MOVE();
	}

	if (m_type == MINIMAP_UI_PLAYER_POS)
	{
		CScene_TWO::SetRot(m_rot);
	}
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CMinimap::Draw(void)
{
	if(m_type == MINIMAP_UI_ENEMY_POS)
	{
		// �ϐ��錾
		LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
			CManager::GetRenderer()->GetDevice();

		// ���C�e�B���O���[�h����
		pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		//Z�o�b�t�@�@�L���@����
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
		// �����_�[�X�e�[�g(���Z��������)
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		// ����(�����)���J�����O����
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		// �`��
		CScene_TWO::Draw();

		//�A���t�@�e�X�g�߂�
		pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
		//Z�o�b�t�@�@�L���@����
		pDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
		// ���C�e�B���O���[�h�L��
		pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		// ����(�����)���J�����O����
		pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

		// �����_�[�X�e�[�g(�ʏ�u�����h����)
		pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
		pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	//�}�b�v�̃e�N�X�`�����W���Ɍ��Ђ���������`��
	/*if ()
	{
		CScene_TWO::Draw();
	}*/

	//[�G]���̌��ʂ��������Ă��ă}�b�v�̃e�N�X�`�����W���ɓG����������`��
	/*if ()
	{
		CScene_TWO::Draw();
	}*/

	else
	{
		CScene_TWO::Draw();
	}
}

// ----------------------------------------
// �e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CMinimap::SetTexture(MINIMAP_UI_TYPE type)
{
	// �ݒ�
	CScene_TWO::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}


// ----------------------------------------
// �쐬����
// ----------------------------------------
CMinimap * CMinimap::Create(void)
{
	// �ϐ��錾
	CMinimap * pMinimap;		// �V�[��3D�N���X
						// �������̐���(����->��{�N���X,��->�h���N���X)
	pMinimap = new CMinimap();
	// ����������
	pMinimap->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pMinimap;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CMinimap::LoadCreate(void)
{
	// �ϐ��錾
	CMinimap * pMiniMap;	// �~�j�}�b�v

	for (int nCntMap = 0; nCntMap < m_nAll; nCntMap++)
	{
		pMiniMap = CMinimap::Create();						// ����
		if (nCntMap != 1)
		{
			pMiniMap->SetTexture((MINIMAP_UI_TYPE)m_pload2D->GetInfo(nCntMap).nType);
		}
		pMiniMap->m_type = (MINIMAP_UI_TYPE)m_pload2D->GetInfo(nCntMap).nType;
		pMiniMap->SetPos(m_pload2D->GetInfo(nCntMap).pos);		// �ʒu
		pMiniMap->SetRot(m_pload2D->GetInfo(nCntMap).rot);		// ��]
		if (pMiniMap->m_type == MINIMAP_UI_SHARD_POS ||
			pMiniMap->m_type == MINIMAP_UI_ENEMY_POS ||
			pMiniMap->m_type == MINIMAP_UI_PLAYER_POS)
		{
			pMiniMap->SetCol(m_pload2D->GetInfo(nCntMap).col);		// �F
		}
		pMiniMap->SetSize(m_pload2D->GetInfo(nCntMap).size);	// �T�C�Y

		if (pMiniMap->m_type == MINIMAP_UI_MAP)
		{
			pMiniMap->SetTex(D3DXVECTOR2(pMiniMap->m_TexFirst), D3DXVECTOR2(pMiniMap->m_TexLast));
		}
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���4
// ----------------------------------------
HRESULT CMinimap::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[MINIMAP_UI_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/MAP/Map.png",				//�}�b�v�̉摜
		"",										//�摜�Ȃ�
		"data/TEXTURE/Effect/effect000.jpg",	//�G�̍��W (�G�t�F�N�g)
		"data/TEXTURE/MAP/0Arrows.png",		//�����̍��W (��Ɠ���)
		"data/TEXTURE/MAP/MapFrame.png",		//�}�b�v�̊O�g
		"data/TEXTURE/MAP/Map_Mission00.png",	//�~�b�V�����̕\��(���)
		"data/TEXTURE/MAP/Map_Mission01.png"	//�~�b�V�����̕\��(���)
	};

	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MINIMAP_UI_MAX; nCnt++)
	{
		if (strcmp(cTex[nCnt], "") != 0)
		{
			D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
		}

		/*if (strcmp(cTex[MINIMAP_UI_PLAYER_POS], "") == 0)
		{
			m_pTexture[MINIMAP_UI_PLAYER_POS] = m_pTexture[MINIMAP_UI_ENEMY_POS];
		}*/
	}

	// ���[�h����
	m_pload2D = new CLoad2D;
	// ���[�h�ǂݍ���
	m_nAll = m_pload2D->Load("data/LOAD/MAP/MiniMap.txt");

	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CMinimap::UnLoad(void)
{
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MINIMAP_UI_MAX; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}
	// ���[�h�̔j��
	delete m_pload2D;
	m_pload2D = NULL;
}

// ----------------------------------------
// �^�C�v�ɂ���ď�����ς���
// ----------------------------------------
void CMinimap::Various(int nCnt)
{
}


// ----------------------------------------
// ���[�h�擾
// ----------------------------------------
CLoad2D * CMinimap::GetLoad(void)
{
	return m_pload2D;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CMinimap::SetPos(D3DXVECTOR3 pos)
{
	CScene_TWO::SetPosition(pos);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CMinimap::SetRot(float rot)
{
	CScene_TWO::SetRot(rot);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CMinimap::SetSize(D3DXVECTOR2 size)
{
	CScene_TWO::SetSize(size);
}

// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CMinimap::SetCol(D3DXCOLOR col)
{
	CScene_TWO::SetCol(col);
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CMinimap::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
	CScene_TWO::SetTex(first, last);
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR2 CMinimap::GetSize(void)
{
	return CScene_TWO::GetSize();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CMinimap::GetPos(void)
{
	return CScene_TWO::GetPosition();
}

// ----------------------------------------
// �e�N�X�`�����W�̌��E�ݒ�
// ----------------------------------------
void CMinimap::TexRange(void)
{
	if (m_TexFirst.x <= 0.0)
	{
		m_TexFirst.x = 0.0f;
	}

	else if (m_TexFirst.y <= 0.0)
	{
		m_TexFirst.y = 0.0f;
	}

	else if (m_TexLast.x >= 1.0)
	{
		m_TexLast.x = 1.0;
	}

	else if (m_TexLast.y >= 1.0)
	{
		m_TexLast.y = 1.0;
	}
}

// ----------------------------------------
// �}�b�v�̃e�N�X�`�����W�̈ړ�
// ----------------------------------------
void CMinimap::MAP_MOVE(void)
{
	CPlayer *pPlayer = NULL;	// �v���C���[

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	float fRot;
	fRot = CManager::GetRenderer()->GetCamera()->GetRot().y;	// ��]���擾

	// �}�b�v�̈ړ� //
	// ----------------------------------------
	// ���ړ�
	// ----------------------------------------
	if (CManager::GetKeyboard()->GetKeyboardPress(DIK_A))
	{//A�������Ă��鎞
		if (pPlayer->GetbCollL() == false)
		{//�v���C���[�̍����̓����蔻�肪false��������
			if (pPlayer->GetbCollB() == false)
			{//�v���C���[�̉����̓����蔻�肪false��������
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
				{// ��
					m_TexFirst.x += sinf(D3DX_PI * 0.25f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * 0.25f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * 0.25f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * 0.25f - fRot) * MAP_MOVESPEED;

					m_rot = 0.785f;

					//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, -MAP_MOVESPEED);
					//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, -MAP_MOVESPEED);
				}
			}

			else if (pPlayer->GetbCollB() == true)
			{//�v���C���[�̉����̓����蔻�肪true��������
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
				{// ��
					m_TexFirst.x += sinf(D3DX_PI * 0.5f + fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * 0.5f + fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * 0.5f + fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * 0.5f + fRot) * MAP_MOVESPEED;

					m_rot = 0.785f;

					//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, -MAP_ZERO);
					//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, -MAP_ZERO);
				}
			}

			if (pPlayer->GetbCollF() == false)
			{//�v���C���[�̉����̓����蔻�肪false��������
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
				{// ��O
					m_TexFirst.x += sinf(D3DX_PI * -0.25f + fRot) * -MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * -0.25f + fRot) * -MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * -0.25f + fRot) * -MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * -0.25f + fRot) * -MAP_MOVESPEED;

					m_rot = 2.355f;

					//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, MAP_MOVESPEED);
					//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, MAP_MOVESPEED);
				}
			}

			else if (pPlayer->GetbCollF() == true)
			{//�v���C���[�̉����̓����蔻�肪true��������
				// ��O
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
				{
					m_TexFirst.x += sinf(D3DX_PI * 0.5f + fRot) * -MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * 0.5f + fRot) * -MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * 0.5f + fRot) * -MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * 0.5f + fRot) * -MAP_MOVESPEED;

					m_rot = 2.355f;

					//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, MAP_ZERO);
					//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, MAP_ZERO);
				}
			}
		}

		else if (pPlayer->GetbCollL() == true)
		{//�v���C���[�̍����̓����蔻�肪true��������
			if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
			{// ��
				//m_TexFirst += D3DXVECTOR2(-0.0f,-MAP_MOVESPEED);
				//m_TexLast += D3DXVECTOR2(-0.0f,-MAP_MOVESPEED);

				m_TexFirst.x += sinf(D3DX_PI * -1.0f + fRot) * -MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -1.0f + fRot) * -MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -1.0f + fRot) * -MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -1.0f + fRot) * -MAP_MOVESPEED;

				m_rot = 0.785f;
			}
			else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
			{// ��O
				//m_TexFirst += D3DXVECTOR2(-0.0f, MAP_MOVESPEED);
				//m_TexLast += D3DXVECTOR2(-0.0f, MAP_MOVESPEED);

				m_TexFirst.x += sinf(D3DX_PI * -0.0f + fRot) * -MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -0.0f + fRot) * -MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -0.0f + fRot) * -MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -0.0f + fRot) * -MAP_MOVESPEED;

				m_rot = 2.355f;
			}
		}

		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_A) &&
			CManager::GetKeyboard()->GetKeyboardPress(DIK_W) == false &&
			CManager::GetKeyboard()->GetKeyboardPress(DIK_S) == false)
		{// ��
			if (pPlayer->GetbCollL() == false)
			{//�v���C���[�̍����̓����蔻�肪false��������
				//m_TexFirst.x += sinf(D3DX_PI * 0.25f + fRot) * MAP_MOVESPEED;
				//m_TexLast.y += cosf(D3DX_PI * 0.25f + fRot) * MAP_MOVESPEED;

				m_TexFirst.x += sinf(D3DX_PI * -0.5f + fRot) * -MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -0.5f + fRot) * -MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -0.5f + fRot) * -MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -0.5f + fRot) * -MAP_MOVESPEED;

				m_rot = D3DX_PI / 2;

				//m_TexFirst += D3DXVECTOR2(-MAP_MOVESPEED, 0.0f);
				//m_TexLast += D3DXVECTOR2(-MAP_MOVESPEED, 0.0f);
			}
		}
	}

	// ----------------------------------------
	// �E�ړ�
	// ----------------------------------------
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_D))
	{
		if (pPlayer->GetbCollR() == false)
		{
			if (pPlayer->GetbCollB() == false)
			{
				// ��
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
				{
					//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, -MAP_MOVESPEED);
					//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, -MAP_MOVESPEED);

					m_TexFirst.x += sinf(D3DX_PI * -0.25f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * -0.25f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * -0.25f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * -0.25f - fRot) * MAP_MOVESPEED;

					m_rot = -0.785f;
				}
			}

			else if (pPlayer->GetbCollB() == true)
			{
				// ��
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
				{
					//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, -MAP_ZERO);
					//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, -MAP_ZERO);

					m_TexFirst.x += sinf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;

					m_rot = -0.785f;
				}
			}

			if (pPlayer->GetbCollF() == false)
			{
				// ��O
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
				{
					//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, MAP_MOVESPEED);
					//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, MAP_MOVESPEED);

					m_TexFirst.x += sinf(D3DX_PI * -0.75f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * -0.75f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * -0.75f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * -0.75f - fRot) * MAP_MOVESPEED;


					m_rot = -2.355f;
				}
			}

			else if (pPlayer->GetbCollF() == true)
			{
				// ��O
				if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
				{
					//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, MAP_ZERO);
					//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, MAP_ZERO);

					m_TexFirst.x += sinf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;
					m_TexLast.y += cosf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;

					m_TexFirst.y += cosf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;
					m_TexLast.x += sinf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;

					m_rot = -2.355f;
				}
			}
		}

		else if (pPlayer->GetbCollR() == true)
		{
			// ��
			if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
			{
				//m_TexLast += D3DXVECTOR2(0.0f, -MAP_MOVESPEED);
				//m_TexFirst += D3DXVECTOR2(0.0f, -MAP_MOVESPEED);

				m_TexFirst.x += sinf(D3DX_PI * -0.0f - fRot) * MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -0.0f - fRot) * MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -0.0f - fRot) * MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -0.0f - fRot) * MAP_MOVESPEED;

				m_rot = -0.785f;
			}


			// ��O
			else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
			{
				//m_TexLast += D3DXVECTOR2(0.0f, MAP_MOVESPEED);
				//m_TexFirst += D3DXVECTOR2(0.0f, MAP_MOVESPEED);

				m_TexFirst.x += sinf(D3DX_PI * -1.0f - fRot) * MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -1.0f - fRot) * MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -1.0f - fRot) * MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -1.0f - fRot) * MAP_MOVESPEED;


				m_rot = -2.355f;
			}
		}

		// �E
		if (CManager::GetKeyboard()->GetKeyboardPress(DIK_D) &&
			CManager::GetKeyboard()->GetKeyboardPress(DIK_W) == false &&
			CManager::GetKeyboard()->GetKeyboardPress(DIK_S) == false)
		{
			if (pPlayer->GetbCollR() == false)
			{
				//m_TexLast += D3DXVECTOR2(MAP_MOVESPEED, 0.0f);
				//m_TexFirst += D3DXVECTOR2(MAP_MOVESPEED, 0.0f);

				m_TexFirst.x += sinf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;
				m_TexLast.y += cosf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;

				m_TexFirst.y += cosf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;
				m_TexLast.x += sinf(D3DX_PI * -0.5f - fRot) * MAP_MOVESPEED;

				m_rot = -D3DX_PI / 2;
			}
		}
	}

	// ----------------------------------------
	// ���ړ�
	// ----------------------------------------
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_W))
	{
		if (pPlayer->GetbCollB() == false)
		{
			//m_TexFirst += D3DXVECTOR2(0.0f, -MAP_MOVESPEED);
			//m_TexLast += D3DXVECTOR2(0.0f, -MAP_MOVESPEED);

			m_TexFirst.x += sinf(D3DX_PI * 0.0f - fRot) * MAP_MOVESPEED;
			m_TexLast.y += cosf(D3DX_PI * 0.0f - fRot) * MAP_MOVESPEED;

			m_TexFirst.y += cosf(D3DX_PI * 0.0f - fRot) * MAP_MOVESPEED;
			m_TexLast.x += sinf(D3DX_PI * 0.0f - fRot) * MAP_MOVESPEED;

			m_rot = -0.0f;
		}
	}

	// ----------------------------------------
	// ��O�ړ�
	// ----------------------------------------
	else if (CManager::GetKeyboard()->GetKeyboardPress(DIK_S))
	{
		if (pPlayer->GetbCollF() == false)
		{
			//m_TexLast += D3DXVECTOR2(0.0f, MAP_MOVESPEED);
			//m_TexFirst += D3DXVECTOR2(0.0f, MAP_MOVESPEED);

			m_TexFirst.x += sinf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;
			m_TexLast.y += cosf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;

			m_TexFirst.y += cosf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;
			m_TexLast.x += sinf(D3DX_PI * 1.0f - fRot) * MAP_MOVESPEED;

			m_rot = -D3DX_PI;
		}
	}

	//�}�b�v�̕`����E�ݒ�
	//TexRange();

	if (m_type == MINIMAP_UI_MAP)
	{
		//�e�N�X�`�����W�̍X�V
		CScene_TWO::SetTex(m_TexFirst, m_TexLast);
	}
}

// ----------------------------------------
// �s�v�ȃ}�b�vUI�̍폜
// ----------------------------------------
void CMinimap::ExceptUI(void)
{
}
