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
#include "object.h"
#include "model_info.h"

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
CLoad			*CObject::m_pload = NULL;							// ���[�h
CModel_info		*CObject::m_pmodel_info = NULL;					// ���f�����
int				CObject::m_nAll = 0;									// �ԍ�

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CObject::CObject() : CScene_X::CScene_X(ACTOR_BLOCK, LAYER_3DOBJECT)
{
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CObject::~CObject()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CObject::Init(void)
{
	// X�I�u�W�F�N�g����
	CScene_X::Init();
	// ���f�����ݒ�
	CScene_X::BindModel(m_pmodel_info->GetModel_info());
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CObject::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CObject::Update(void)
{
	CScene_X::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CObject::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CObject * CObject::Create(void)
{
	// �ϐ��錾
	CObject * pObject;		// �V�[��3D�N���X
							// �������̐���(����->��{�N���X,��->�h���N���X)
	pObject = new CObject();
	// ����������
	pObject->Init();
	// ���������I�u�W�F�N�g��Ԃ�
	return pObject;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CObject::LoadCreate(void)
{
	// �ϐ��錾
	CObject * pObject;	// �u���b�N
						// �u���b�N
	for (int nCntBlock = 0; nCntBlock < m_nAll; nCntBlock++)
	{
		pObject = CObject::Create();					// ����
		pObject->SetPos(m_pload->GetInfo(nCntBlock).pos);	// �ʒu
		pObject->SetRot(m_pload->GetInfo(nCntBlock).rot);	// ��]
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CObject::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();

	char cModelfile[OBJ_TYPE_MAX][128] =			// ���f���t�@�C����
	{
		"data/MODEL/object/elevator.x",
	};

	// ���[�h����
	m_pload = new CLoad;
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/obj_Location.txt");
	// ���f����񐶐�
	m_pmodel_info = new CModel_info;
	// ���f���ǂݍ���
	m_pmodel_info->Load(pDevice, cModelfile[0]);
	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CObject::UnLoad(void)
{
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
void CObject::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CObject::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CObject::GetPos(void)
{
	return CScene_X::GetPos();
}