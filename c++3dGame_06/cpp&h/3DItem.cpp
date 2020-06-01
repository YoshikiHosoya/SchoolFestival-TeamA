// ----------------------------------------
//
// 3D�A�C�e�������̐���[3ditem.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "3ditem.h"
#include "model_info.h"
#include "debugproc.h"
#include "player.h"
#include "3dparticle.h"
#include "mapmark.h"
#include "gameui.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define ITEMCOLLISION_3D_SIZE (200.0f)

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 C3DItem::m_pTexture[1] = {};			// �e�N�X�`���ւ̃|�C���^
CLoad			*C3DItem::m_pload = NULL;				// ���[�h
CModel_info		*C3DItem::m_pmodel_info = NULL;			// ���f�����
int				C3DItem::m_nAll = 0;					// �ԍ�
int				C3DItem::m_nShardNum = 0;				//���Ђ̑���
// ----------------------------------------
// �R���X�g���N�^
// ----------------------------------------
C3DItem::C3DItem()
{
	m_Type = TYPE_SHARD;
	//m_nTotal3DItem = 0; //3D�A�C�e���̑���
	//m_nTotal3DItem = m_pload->GetShard();
	m_bShard = false;
	m_ID.nId = 0;
}

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
C3DItem::C3DItem(ACTOR actor, LAYER layer) : CScene_X::CScene_X(actor, layer)
{
	m_Type = TYPE_SHARD;
	//m_nShardNum = m_pload->GetShard();
}

//C3DItem::C3DItem() : CScene_X::CScene_X(ACTOR_3DITEM, LAYER_3DOBJECT)
//{
//	m_Type = TYPE_SHARD;
//	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// ���݉�]��
//	m_nTotal3DItem = 0; //3D�A�C�e���̑���
//}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
C3DItem::~C3DItem()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void C3DItem::Init(void)
{
	// X�I�u�W�F�N�g����
	CScene_X::Init();
	// ���f�����ݒ�
	CScene_X::BindModel(m_pmodel_info->GetModel_info());
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		CScene_X::BindTexture(m_pTexture[nCnt]);
	}

	/*if (m_ID.nId == 0)
	{
		m_ID.nId += 1;
	}*/
}

// ----------------------------------------
// �I������
// ----------------------------------------
void C3DItem::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void C3DItem::Update(void)
{
	CPlayer *pPlayer = NULL;	// �v���C���[
	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	// �A�C�e���̎擾
	if (CCalculation::Collision_Circle(
		D3DXVECTOR3(GetPos().x, GetPos().y + 100, GetPos().z),
		// �����̈ʒu
		ITEMCOLLISION_3D_SIZE, 		// �����̔��a
		D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y - 100, pPlayer->GetPos().z), 			// ����̈ʒu
		PLAYERCOLLISION_SIZE))		// ����̔��a
	{
		if (m_Type == TYPE_SHARD)
		{
			// SE��炷
			//CManager::GetSound()->PlaySound(CSound::LABEL_SE_8);
			Except3DItem();					// 3D�A�C�e���̑����}�C�i�X

			CMapMark *pMapMark = NULL;

			for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_UI); nCntlayer++)
			{
				if (pMapMark = (CMapMark *)CScene::GetActor(CScene::ACTOR_MAPMARK, CScene::LAYER_UI, nCntlayer)) break;
			}

			pMapMark->ReleseMaker((this->m_ID.nId));

			//C3DParticle::Create(C3DParticle::OFFSET_ID_EXPLOSION, GetPos());
			C3DParticle::Create(C3DParticle::OFFSET_ID_EXPLOSIONWAVE, GetPos());
			CGame_ui::SetAP(1);
		}
		Release();
	}

	// ��]���
	if (m_pmodel_info->GetModel_info().rot.y > 6.28)
	{
		m_pmodel_info->GetModel_info().rot.y = 0;
	}

	//3D�A�C�e���̉�]��
	m_pmodel_info->GetModel_info().rot.y += 0.000314f;

	//��]�̔��f
	SetRot(m_pmodel_info->GetModel_info().rot);

	CScene_X::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void C3DItem::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
C3DItem * C3DItem::Create(void)
{
	// �ϐ��錾
	C3DItem * p3DItem;		// �V�[��3D�N���X
							// �������̐���(����->��{�N���X,��->�h���N���X)
	p3DItem = new C3DItem(ACTOR_3DITEM, LAYER_3DOBJECT);
	//p3DItem = new C3DItem();
	// ����������
	p3DItem->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return p3DItem;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void C3DItem::LoadCreate(void)
{
	// �ϐ��錾
	C3DItem * p3DItem;

	m_nShardNum = m_nAll;

	for (int nCntItem = 0; nCntItem < m_nAll; nCntItem++)
	{
		p3DItem = C3DItem::Create();						// ����
		p3DItem->SetPos(m_pload->GetInfo(nCntItem).pos);	// �ʒu
		p3DItem->SetRot(m_pload->GetInfo(nCntItem).rot);	// ��]
		// Id�̐ݒ�
		p3DItem->m_ID.nId = (nCntItem);
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���4
// ----------------------------------------
HRESULT C3DItem::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[1][128] =							// �e�N�X�`���[��
	{
		"data/TEXTURE/obj_tex/Item00.png",
	};
	char cModelfile[TYPE_MAX][128] =			// ���f���t�@�C����
	{
		"data/MODEL/object/Shard00.x",
	};
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < 1; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ���[�h����
	m_pload = new CLoad;
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/3DItem00.txt");
	// ���f����񐶐�
	m_pmodel_info = new CModel_info;
	// ���f���ǂݍ���
	m_pmodel_info->Load(pDevice, cModelfile[0]);
	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void C3DItem::UnLoad(void)
{
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < 1; nCnt++)
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
	// ���f���̔j��
	m_pmodel_info->Unload();
	delete m_pmodel_info;
	m_pmodel_info = NULL;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void C3DItem::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void C3DItem::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 C3DItem::GetPos(void)
{
	return CScene_X::GetPos();
}

// ----------------------------------------
// ���Ђ̌��݂̐�
// ----------------------------------------
int C3DItem::GetShardNum(void)
{
	return m_nShardNum;
}

// ----------------------------------------
// ���Ђ̃t���O
// ----------------------------------------
bool C3DItem::ShardFlag(void)
{
	return m_bShard;
}

// ----------------------------------------
// 3D�A�C�e���̑���
// ----------------------------------------
void C3DItem::Except3DItem(void)
{
	//3D�A�C�e���̑��������炷
	m_nShardNum--;
}


