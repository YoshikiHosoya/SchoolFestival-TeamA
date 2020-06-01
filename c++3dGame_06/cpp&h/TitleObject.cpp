// ----------------------------------------
//
// �I�u�W�F�N�g�����̐���[object.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "titleobject.h"
#include "model_info.h"
#include "debugproc.h"
// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
CLoad			*CTitleObject::m_pload = NULL;							// ���[�h
CModel_info		*CTitleObject::m_pmodel_info = NULL;					// ���f�����
int				CTitleObject::m_nAll = 0;								// �ԍ�

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CTitleObject::CTitleObject() : CScene_X::CScene_X(ACTOR_BLOCK, LAYER_3DOBJECT)
{
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CTitleObject::~CTitleObject()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CTitleObject::Init(void)
{
	// X�I�u�W�F�N�g����
	CScene_X::Init();

	//CTitleObject *pTitleObject[MAX_TITLEOBJ] = {};	// 3D�A�C�e��
	//int nCount = 0;

	//for (int nCntLayer = 0; nCntLayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntLayer++)
	//{
	//	if ((CTitleObject *)CScene::GetActor(CScene::ACTOR_BLOCK, CScene::LAYER_3DOBJECT, nCntLayer))
	//	{
	//		pTitleObject[nCount] = (CTitleObject*)CScene::GetActor(CScene::ACTOR_BLOCK, CScene::LAYER_3DOBJECT, nCntLayer);

	//		pTitleObject[nCount]->BindModel(m_pmodel_info[nCount].GetModel_info());

	//		nCount++;
	//	}
	//}

	//for (int nCntModel = 0; nCntModel < MAX_TITLEOBJ; nCntModel++)
	//{
	//	// ���f�����ݒ�
	//	pTitleObject[nCntModel]->BindModel(m_pmodel_info[nCntModel].GetModel_info());
	//}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CTitleObject::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CTitleObject::Update(void)
{
	CDebugproc::Print("���W		: %.2f,%.2f,%.2f\n", GetPos().x, GetPos().y, GetPos().z);
	/*D3DXVECTOR3 pos = D3DXVECTOR3(0,0,-2000);
	SetPos(pos);*/
	CScene_X::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CTitleObject::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CTitleObject * CTitleObject::Create(void)
{
	// �ϐ��錾
	CTitleObject * pObject;		// �V�[��3D�N���X
							// �������̐���(����->��{�N���X,��->�h���N���X)
	pObject = new CTitleObject();
	// ����������
	pObject->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pObject;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CTitleObject::LoadCreate(void)
{
	// �ϐ��錾
	CTitleObject * pObject;	// �u���b�N
	for (int nCntModel = 0; nCntModel < m_nAll; nCntModel++)
	{
		pObject = CTitleObject::Create();					// ����
		pObject->BindModel(m_pmodel_info[nCntModel].GetModel_info());
		pObject->SetPos(m_pload->GetInfo(nCntModel).pos);	// �ʒu
		pObject->SetRot(m_pload->GetInfo(nCntModel).rot);	// ��]
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CTitleObject::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	char cModelfile[MAX_TITLEOBJ][128] =			// ���f���t�@�C����
	{
		"data/MODEL/object/stage.x",
		"data/MODEL/object/curtain.x"
	};

	// ���[�h����
	m_pload = new CLoad[MAX_TITLEOBJ];
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Tit_obj_Location.txt");
	// ���f����񐶐�
	m_pmodel_info = new CModel_info[MAX_TITLEOBJ];
	// ���f���ǂݍ���
	for (int nCntModel = 0; nCntModel < MAX_TITLEOBJ; nCntModel++)
	{
		m_pmodel_info[nCntModel].Load(pDevice, cModelfile[nCntModel]);
	}
	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CTitleObject::UnLoad(void)
{
	// ���f���̕`����j��
	for (int nCntModelLoad = 0; nCntModelLoad < MAX_TITLEOBJ; nCntModelLoad++)
	{
		//���f���̔j��
		m_pmodel_info[nCntModelLoad].Unload();
	}

	delete[] m_pmodel_info;
	//m_pmodel_info = NULL;
	// ���[�h�̔j��
	delete[] m_pload;
	//m_pload = NULL;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CTitleObject::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CTitleObject::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CTitleObject::GetPos(void)
{
	return CScene_X::GetPos();
}