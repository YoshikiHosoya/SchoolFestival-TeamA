// =====================================================================================================================================================================
//
// �A�C�e���̏��� [item.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "item.h"			// �C���N���[�h�t�@�C��
#include "manager.h"
#include "renderer.h"
#include "game.h"
#include "debugproc.h"
#include "player.h"
#include "fade.h"
#include "effect.h"
#include "gameUI.h"
#include "score.h"
#include "particle.h"
#include "sound.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
LPDIRECT3DTEXTURE9	CItem::m_apTexture[ITEMTYPE::ITEMTYPE_MAX]	= {};			// �e�N�X�`�����
CEffect				*CItem::m_pEffect[MAX_EFFECT]				= {};			// �G�t�F�N�g���
int					CItem::m_nID								= 0;			// �ԍ�

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEXTURE_FILE01		"data/TEXTURE/drunk.png"		// �ǂݍ��ރe�N�X�`���t�@�C����			( �X�s�[�h�A�b�v )
#define TEXTURE_FILE02		"data/TEXTURE/jewel02.png"		// �ǂݍ��ރe�N�X�`���t�@�C����			( �_�C�� )
#define TEXTURE_FILE03		"data/TEXTURE/jewel01.png"		// �ǂݍ��ރe�N�X�`���t�@�C����			( ��� )
#define TEXTURE_FILE04		"data/TEXTURE/gold.png"			// �ǂݍ��ރe�N�X�`���t�@�C����			( ���� )
#define TEXTURE_FILE05		"data/TEXTURE/key.png"			// �ǂݍ��ރe�N�X�`���t�@�C����			( �� )
#define TEXTURE_FILE06		"data/TEXTURE/Dlunker.png"		// �ǂݍ��ރe�N�X�`���t�@�C����			( 1UP )
#define TEXTURE_FILE07		"data/TEXTURE/treasure.png"		// �ǂݍ��ރe�N�X�`���t�@�C����			( ���� )
#define TEXTURE_FILE08		"data/TEXTURE/energy.png"		// �ǂݍ��ރe�N�X�`���t�@�C����			( �G�l���M�[ )

#define ITEM_SIZEX			(20 / 2)						// ���W�̕�
#define ITEM_SIZEY			(30 / 2)						// ���W�̍���

#define JUWEL_SIZEX			(30/ 2)							// ��΂̕�
#define JUWEL_SIZEY			(30 / 2)						// ��΂̍���

#define TREASURE_SIZEX		(100/ 2)						// ��̕�
#define TREASURE_SIZEY		(100 / 2)						// ��̍���

#define ENERGY_SIZEX		(40 / 2)						// �G�l���M�[�̕�
#define ENERGY_SIZEY		(50 / 2)						// �G�l���M�[�̍���

#define MAX_PARTICLE		(100)							// �p�[�e�B�N����
#define MAX_PARTICLE_SHORT	(20)							// �������p�[�e�B�N����

#define HIT_ITEM_SIZE		(10.0f)							// �A�C�e���̓����蔻��̃T�C�Y�g��

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CItem::CItem() :CScene3D(PRIORITY_ITEM)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CItem::~CItem()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CItem::Init()
{
	// �ϐ�������
	m_pos			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �ʒu
	m_size			= D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// �T�C�Y
	m_col			= D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);		// �F
	m_ItemType		= ITEMTYPE::ITEMTYPE_NONE;					// �A�C�e���̎��
	m_bHit			= false;									// �q�b�g�t���O

	// ������
	CScene3D::Init();
	//�F�̐ݒ�
	CScene3D::SetColor(m_col);
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CItem::Uninit(void)
{
	CScene3D::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CItem::Update(void)
{
	// �v���C���[�̏��擾
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CScene3D::GetPos();

	// �v���C���[�Ƃ̓����蔻��
	if (CollisionPlayer() == true)
	{
		switch (m_ItemType)
		{
		case CItem::ITEMTYPE_SPEED:			// �X�s�[�h�A�b�v
			//	�A�C�e���擾��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// �X�R�A���Z
			CScore::AddScore(100);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// �p�[�e�B�N���̐���
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_DIAMOND:		// �_�C��
			//	�A�C�e���擾��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// �X�R�A���Z
			CScore::AddScore(5000);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// �p�[�e�B�N���̐���
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_JEWEL:			// ���
			//	�A�C�e���擾��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// �X�R�A���Z
			CScore::AddScore(2000);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// �p�[�e�B�N���̐���
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_GOLD:			// ����
			//	�A�C�e���擾��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// �X�R�A���Z
			CScore::AddScore(300);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// �p�[�e�B�N���̐���
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_KEY:			// ��
			break;

		case CItem::ITEMTYPE_1UP:			// 1UP
			//	�A�C�e���擾��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// �v���C���[�̎c�@�A�b�v
			CManager::GetGame()->GetPlayer()->PlayerRecovery(1);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// �p�[�e�B�N���̐���
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			break;

		case CItem::ITEMTYPE_TREASURE:		// ����
			//	�A�C�e���擾��
			CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_ITEM);
			// �X�R�A���Z
			CScore::AddScore(10000);
			for (int nCnt = 0; nCnt < MAX_PARTICLE_SHORT; nCnt++)
			{
				// �p�[�e�B�N���̐���
				CParticle::Create(pos, CParticle::PARTICLE_BLUE);
			}
			for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
			{
				// �p�[�e�B�N���̐���
				CParticle::Create(pos, CParticle::PARTICLE_RED);
			}
			// �Q�[���I��(�N���A)
			CManager::GetGame()->SetGameMode(CGame::GAME_MODE_CLEAR);
			break;

		case CItem::ITEMTYPE_ENERGY:		// �G�l���M�[
			// �������Ă��Ȃ��Ƃ�
			if (!m_bHit)
			{
				//	�G�l���M�[�񕜉�
				CManager::GetSound()->PlaySound(CSound::SOUND_LABEL_SE_HEAL);

				for (int nCnt = 0; nCnt < MAX_PARTICLE; nCnt++)
				{
					// �p�[�e�B�N���̐���
					CParticle::Create(pos, CParticle::PARTICLE_RED);
				}
				// �ĊJ�n�_�̐ݒ�
				pPlayer->SetRestartPos(pos);
			}
			// �G�l���M�[�Q�[�W�̉�
			CGameUI::RecoveryGage();
			break;
		}
		// �������Ă�����
		m_bHit = true;
	}
	else
	{
		// �q�b�g�t���O��߂�
		m_bHit = false;
	}

	// �ʒu�̐ݒ�
	CScene3D::SetPos(pos);

	// �X�V
	CScene3D::Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CItem::Draw(void)
{	
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);						 // �A���t�@�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ALPHAREF, 30);								 // ��l���w�肷��
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);					 // ��l���傫���ƕ`�悷��

	// �`��
	CScene3D::Draw();

	// �A���t�@�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
}

// =====================================================================================================================================================================
//
// �A�C�e���̐���
//
// =====================================================================================================================================================================
CItem * CItem::Create(D3DXVECTOR3 pos, ITEMTYPE type)
{
	// �ϐ�
	CItem *pItem;

	// �������̊m��
	pItem = new CItem();

	// ������
	pItem->Init();

	// �A�C�e���̈ʒu�̐ݒ�
	pItem->SetPos(pos);
	// �A�C�e���̎�ނ̐ݒ�
	pItem->m_ItemType = type;
	// �r���{�[�h�̐ݒ�
	pItem->SetBillboard(true);

	switch (type)
	{
	case CItem::ITEMTYPE_SPEED:			// �X�s�[�h�A�b�v

		pItem->m_size = D3DXVECTOR3(ITEM_SIZEX, ITEM_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_DIAMOND:		// �_�C��

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_JEWEL:			// ���

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_GOLD:			// ����

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_KEY:			// ��

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_1UP:			// 1UP

		pItem->m_size = D3DXVECTOR3(JUWEL_SIZEX, JUWEL_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_TREASURE:		// ����

		pItem->m_size = D3DXVECTOR3(TREASURE_SIZEX, TREASURE_SIZEY, 0.0f);
		break;

	case CItem::ITEMTYPE_ENERGY:		// �G�l���M�[

		pItem->m_size = D3DXVECTOR3(ENERGY_SIZEX, ENERGY_SIZEY, 0.0f);
		break;
	}

	// �e�N�X�`���̊��蓖��
	pItem->BindTexture(m_apTexture[type]);

	// �T�C�Y�̐ݒ�
	pItem->SetSize(pItem->m_size);

	//// �G�t�F�N�g����
	//m_pEffect[m_nID] = CEffect::Create(pos, CEffect::EFFECTTYPE_ITEM);

	// �C���N�������g
	m_nID++;

	return pItem;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CItem::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// �e�N�X�`���t�@�C����
	char *sTextureFileName[ITEMTYPE_MAX]
	{
		{ TEXTURE_FILE01 },		// ITEMTYPE_SPEED		( �X�s�[�h�A�b�v
		{ TEXTURE_FILE02 },		// ITEMTYPE_DIAMOND		( �_�C��
		{ TEXTURE_FILE03 },		// ITEMTYPE_JEWEL		( ���
		{ TEXTURE_FILE04 },		// ITEMTYPE_GOLD		( ����
		{ TEXTURE_FILE05 },		// ITEMTYPE_KEY			( ��
		{ TEXTURE_FILE06 },		// ITEMTYPE_1UP			( 1UP
		{ TEXTURE_FILE07 },		// ITEMTYPE_TREASURE	( ����
		{ TEXTURE_FILE08 },		// ITEMTYPE_ENERGY		( �G�l���M�[
	};

	for (int nCntItem = 0; nCntItem < ITEMTYPE_MAX; nCntItem++)
	{
		// �e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntItem], &m_apTexture[nCntItem]);
	}

	return S_OK;
}

// =====================================================================================================================================================================
//  
// �A�����[�h
//
// =====================================================================================================================================================================
void CItem::Unload(void)
{
	for (int nCntTex = 0; nCntTex < ITEMTYPE::ITEMTYPE_MAX; nCntTex++)
	{
		// �e�N�X�`���̊J��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

// =====================================================================================================================================================================
//  
// �A�C�e���̎�ނ̐ݒ�
//
// =====================================================================================================================================================================
void CItem::SetItemType(ITEMTYPE type)
{
	m_ItemType = type;

	// �e�N�X�`���̊��蓖��
	BindTexture(m_apTexture[type]);

	// �T�C�Y�̐ݒ�
	SetSize(D3DXVECTOR3(m_size.x, m_size.y, m_size.z));
}

// =====================================================================================================================================================================
//  
// �v���C���[�Ƃ̓����蔻��
//
// =====================================================================================================================================================================
bool CItem::CollisionPlayer(void)
{
	bool bHit = false;		// �q�b�g�t���O

	CPlayer * pPlayer = CManager::GetGame()->GetPlayer();			// �v���C���[�̎擾

	if (pPlayer != NULL)
	{
		D3DXVECTOR3 posPlayer = pPlayer->GetPos();					// �v���C���[�̈ʒu�擾
		D3DXVECTOR3 sizePlayer = pPlayer->GetSize();				// �v���C���[�̃T�C�Y�擾
		D3DXVECTOR3 posItem = CScene3D::GetPos();					// �A�C�e���̈ʒu

		// �u���b�N�͈̔� ( �� )
		if (posItem.x - m_size.x - HIT_ITEM_SIZE< posPlayer.x + sizePlayer.x &&
			posItem.x + m_size.x + HIT_ITEM_SIZE> posPlayer.x - sizePlayer.x)
		{
			// �u���b�N�͈̔� ( �c )
			if (posItem.z - m_size.z - HIT_ITEM_SIZE< posPlayer.z + sizePlayer.z &&
				posItem.z + m_size.z + HIT_ITEM_SIZE> posPlayer.z - sizePlayer.z)
			{
				// �u���b�N�͈̔� ( ���� )
				if (posItem.y - m_size.y - HIT_ITEM_SIZE <= posPlayer.y + sizePlayer.y &&
					posItem.y + m_size.y + HIT_ITEM_SIZE> posPlayer.y)
				{
					// �G�l���M�[����Ȃ��Ƃ�
					if (m_ItemType != ITEMTYPE_ENERGY)
					{
						// �����[�X
						Release();
					}
					// ���������Ƃ�
					bHit = true;
				}
			}
		}
	}
	return bHit;
}