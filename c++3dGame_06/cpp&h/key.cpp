// ----------------------------------------
//
// �������̐���[key.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "key.h"
#include "model_info.h"
#include "player.h"
#include "gate.h"
// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
CModel_info	*CKey::m_pmodel_info = NULL;					// ���f�����
D3DXVECTOR3 CKey::m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
bool CKey::m_bGet = false;
// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CKey::CKey() : CScene_X::CScene_X(ACTOR_X, LAYER_3DOBJECT)
{
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CKey::~CKey()
{
	m_bGet = false;
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CKey::Init(void)
{
	// X�I�u�W�F�N�g����
	CScene_X::Init();
	// ���f�����ݒ�
	CScene_X::BindModel(m_pmodel_info->GetModel_info());
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CKey::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CKey::Update(void)
{
	CPlayer *pPlayer = NULL;	// �v���C���[

	for (int nCntlayer = 0; nCntlayer < CScene::GetMaxLayer(CScene::LAYER_3DOBJECT); nCntlayer++)
	{
		if (pPlayer = (CPlayer *)CScene::GetActor(CScene::ACTOR_PLAYER, CScene::LAYER_3DOBJECT, nCntlayer)) break;
	}

	SetRot(GetRot() + D3DXVECTOR3(0.0, 0.03f,0.0f));

	// �A�C�e���̎擾
	if (CCalculation::Collision_Circle(
		D3DXVECTOR3(GetPos().x, GetPos().y + 100, GetPos().z),
		// �����̈ʒu
		200.0f, 		// �����̔��a
		D3DXVECTOR3(pPlayer->GetPos().x, pPlayer->GetPos().y - 100, pPlayer->GetPos().z), 			// ����̈ʒu
		PLAYERCOLLISION_SIZE))		// ����̔��a
	{
		CGate::LoadCreate();
		m_bGet = true;
		Release();
	}

	CScene_X::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CKey::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CKey * CKey::Create(void)
{
	// �ϐ��錾
	CKey * pKey;		// �V�[��3D�N���X
						// �������̐���(����->��{�N���X,��->�h���N���X)
	pKey = new CKey();
	// ����������
	pKey->Init();
	// ���W�ݒ�
	pKey->SetPos(m_pos);
	// ���������I�u�W�F�N�g��Ԃ�
	return pKey;
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CKey::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cModelfile[1][128] =			// ���f���t�@�C����
	{
		"data/MODEL/object/key.x",
	};
	D3DXVECTOR3 pos =
	{
		D3DXVECTOR3(0.0f, 150, 1200.0f)
	};

	m_pos = pos;

	// ���f����񐶐�
	m_pmodel_info = new CModel_info;
	// ���f���ǂݍ���
	m_pmodel_info->Load(pDevice, cModelfile[0]);
	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CKey::UnLoad(void)
{
	// ���f���̔j��
	m_pmodel_info->Unload();
	delete m_pmodel_info;
	m_pmodel_info = NULL;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CKey::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CKey::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CKey::GetPos(void)
{
	return CScene_X::GetPos();
}

// ----------------------------------------
// �v���C���[���J�M����ɓ��ꂽ���ǂ����̃t���O���擾
// ----------------------------------------
bool CKey::bGetFlag(void)
{
	return m_bGet;
}
