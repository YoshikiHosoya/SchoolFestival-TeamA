// ----------------------------------------
//
// �A�C�e�������̐���[item.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "item.h"
#include "player.h"
#include "score.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define ITEMCOLLISION_SIZE (30.0f)

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CItem::m_pTexture[TYPE_MAX] = {};		// �e�N�X�`���ւ̃|�C���^
CLoad	*CItem::m_pload = NULL;								// ���[�h
int		CItem::m_nAll = 0;									// �ԍ�
int		CItem::m_nRotCntAll = 0;							// ��]��
int		CItem::m_nJumpCntAll = 0;							// �W�����v��

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CItem::CItem()
{
	// �ϐ��̏�����
	m_Type = TYPE_ROT;
	m_fLengh = 0;
	m_fAngle = 0;
	m_bBillboard = false;
}

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CItem::CItem(ACTOR actor, LAYER layer) : CScene_THREE::CScene_THREE(actor,layer)
{
	// �ϐ��̏�����
	m_fLengh = 0;
	m_fAngle = 0;
	m_bBillboard = false;
	m_Type = TYPE_ROT;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CItem::~CItem()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CItem::Init(void)
{
	// �V�[��3D�̏�����
	CScene_THREE::Init();
	CScene_THREE::SetBillboard(true);				// �r���{�[�h
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CItem::Uninit(void)
{
	CScene_THREE::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CItem::Update(void)
{
	// �ϐ��錾
	CPlayer *pPlayer = NULL;	// �v���C���[
	CScore *pScore = NULL;	// �X�R�A
	// ���擾
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}
	// ���擾
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_UI); nCntlayer++)
	{
		if (pScore = (CScore *)CScene::GetActor(CScene::ACTOR_SCORE, CScene::LAYER_UI, nCntlayer)) break;
	}

	// �A�C�e���̎擾
	if (CCalculation::Collision_Circle(
		GetPos(),					// �����̈ʒu
		ITEMCOLLISION_SIZE, 		// �����̔��a
		pPlayer->GetPos(), 			// ����̈ʒu
		PLAYERCOLLISION_SIZE))		// ����̔��a
	{
		if (m_Type == TYPE_ROT)
		{
			// SE��炷
			//CManager::GetSound()->PlaySound(CSound::LABEL_SE_8);
			//pPlayer->AddRot();					// ��]���A�b�v
		}
		else if (m_Type == TYPE_JUMP)
		{
			// SE��炷
			//CManager::GetSound()->PlaySound(CSound::LABEL_SE_8);
			//pPlayer->AddJump();					// �W�����v���A�b�v
		}
		else if (m_Type == TYPE_COIN)
		{
			// SE��炷
			//CManager::GetSound()->PlaySound(CSound::LABEL_SE_7);
		}
		Release();
	}
	CScene_THREE::SetRot(CScene_THREE::GetRot() + D3DXVECTOR3(0.0f,0.1f,0.0f));
	CScene_THREE::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CItem::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	// �A���t�@�e�X�g�̐ݒ�ɕύX
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);		// �A���t�@�e�X�g�L��
	pDevice->SetRenderState(D3DRS_ALPHAREF, 200);				// �A���t�@�l�̊�ݒ�(����傫���ƕ`�悷��)
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);	// �󋵂ɉ����ăA���t�@�e�X�g�����s����(�V�s�N�Z�� > ���݂̃s�N�Z��)
	pDevice->SetRenderState(D3DRS_LIGHTING, false);				// ���C�e�B���Ooff
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// �`��
	CScene_THREE::Draw();
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// �A���t�@�e�X�g�̐ݒ��߂�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);		// �A���t�@�e�X�g����
	pDevice->SetRenderState(D3DRS_LIGHTING, true);				// ���C�e�B���Oon
}

// ----------------------------------------
// �e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CItem::SetTexture(TYPE type)
{
	// �ݒ�
	CScene_THREE::BindTexture(m_pTexture[type]);	// �e�N�X�`���[
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CItem * CItem::Create(bool bBillboard)
{
	// �ϐ��錾
	CItem * pItem;		// �V�[��3D�N���X
	// �������̐���(����->��{�N���X,��->�h���N���X)
	pItem = new CItem(ACTOR_ITEM,LAYER_3DOBJECT);
	// �r���{�[�h�̂����邩�ǂ���
	pItem->m_bBillboard = bBillboard;
	// ����������
	pItem->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pItem;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CItem::LoadCreate(void)
{
	// �ϐ��錾
	CItem * pItem;	// �u���b�N
						// �u���b�N
	for (int nCntItem = 0; nCntItem < m_nAll; nCntItem++)
	{
		pItem = CItem::Create(true);						// ����
		pItem->SetTexture((TYPE)m_pload->GetInfo(nCntItem).nType);
		pItem->m_Type = (TYPE)m_pload->GetInfo(nCntItem).nType;
		pItem->SetPos(m_pload->GetInfo(nCntItem).pos);		// �ʒu
		pItem->SetRot(m_pload->GetInfo(nCntItem).rot);		// ��]
		pItem->SetSize(m_pload->GetInfo(nCntItem).size);	// �T�C�Y
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CItem::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[TYPE_MAX][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/UI/RotationUP000.png",
		"data/TEXTURE/UI/JumpUP.png",
		"data/TEXTURE/UI/COIN.png"
	};

	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < TYPE_MAX; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ���[�h����
	m_pload = new CLoad;
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/billboard.txt");

	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CItem::UnLoad(void)
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
// ���[�h�擾
// ----------------------------------------
CLoad * CItem::GetLoad(void)
{
	return m_pload;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CItem::SetPos(D3DXVECTOR3 pos)
{
	CScene_THREE::SetPos(pos);
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CItem::SetSize(D3DXVECTOR3 size)
{
	CScene_THREE::SetSize(size);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CItem::SetRot(D3DXVECTOR3 rot)
{
	CScene_THREE::SetRot(rot);
}
// ----------------------------------------
// �F�̐ݒ菈��
// ----------------------------------------
void CItem::SetCol(D3DXCOLOR col)
{
}

// ----------------------------------------
// �\���e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CItem::SetTex(D3DXVECTOR2 first, D3DXVECTOR2 last)
{
}

// ----------------------------------------
// �T�C�Y�̎擾����
// ----------------------------------------
D3DXVECTOR3 CItem::GetSize(void)
{
	return CScene_THREE::GetSize();
}

// ----------------------------------------
// ��]�̎擾����
// ----------------------------------------
D3DXVECTOR3 CItem::GetRot(void)
{
	return CScene_THREE::GetRot();
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CItem::GetPos(void)
{
	return CScene_THREE::GetPos();
}
