// ----------------------------------------
//
// �V�䏈���̐���[ceiling.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "ceiling.h"
#include "model_info.h"

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CCeiling::m_pTexture[MAX_CEILINGTEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
CLoad	*CCeiling::m_pload = NULL;							// ���[�h
CModel_info	*CCeiling::m_pmodel_info = NULL;					// ���f�����
int		CCeiling::m_nAll = 0;									// �ԍ�

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CCeiling::CCeiling() : CScene_X::CScene_X(ACTOR_WALL, LAYER_3DOBJECT)
{
	m_type = SIZE_NORMAL;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CCeiling::~CCeiling()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CCeiling::Init(void)
{
	// X�I�u�W�F�N�g����
	CScene_X::Init();
	// ���f�����ݒ�
	CScene_X::BindModel(m_pmodel_info[m_type].GetModel_info());
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MAX_CEILINGTEXTURE; nCnt++)
	{
		CScene_X::BindTexture(m_pTexture[nCnt]);
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CCeiling::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CCeiling::Update(void)
{
	CScene_X::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CCeiling::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CCeiling * CCeiling::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SIZE type)
{
	// �ϐ��錾
	CCeiling * pCeiling;		// �V�[��3D�N���X
						// �������̐���(����->��{�N���X,��->�h���N���X)
	pCeiling = new CCeiling();
	// ��ނ̐ݒ�
	pCeiling->m_type = type;
	// ����������
	pCeiling->Init();
	// ���W�̐ݒ�
	//pWall->m_pos = pos;
	pCeiling->SetPos(pos);
	// ��]�̐ݒ�
	//pWall->m_rot = rot;
	pCeiling->SetRot(rot);
	// ���������I�u�W�F�N�g��Ԃ�
	return pCeiling;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CCeiling::LoadCreate(void)
{
	// �ϐ��錾
	CCeiling * pCeiling;	// �u���b�N
					// �u���b�N
	for (int nCntWall = 0; nCntWall < m_nAll; nCntWall++)
	{
		pCeiling = CCeiling::Create(m_pload->GetInfo(nCntWall).pos,
			m_pload->GetInfo(nCntWall).rot,
			(SIZE)m_pload->GetInfo(nCntWall).nType);		// ����

	//pWall->SetPos(m_pload->GetInfo(nCntWall).pos);	// �ʒu
	//pWall->SetRot(m_pload->GetInfo(nCntWall).rot);	// ��]
	//pWall->m_pload->GetInfo(nCntWall).nType;			// ���

	/*if (m_pload->GetInfo(nCntWall).nType == 2)
	{
	if (pWall->m_pload->GetInfo(nCntWall).rot.y == 0.0f)
	{
	CCollision::Create_Single(m_pload->GetInfo(nCntWall).pos, D3DXVECTOR3(300, 300, 0));
	}
	}*/
	}
}

// ----------------------------------------
// �ǂݍ��ݏ���
// ----------------------------------------
HRESULT CCeiling::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =						// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[MAX_CEILINGTEXTURE][128] =			// �e�N�X�`���[��
	{
		"data/TEXTURE/obj_tex/Ceiling00.jpg",
		"data/TEXTURE/obj_tex/Ceiling00.jpg",
	};
	char cModelfile[TYPE_MAX][256] =				// ���f���t�@�C����
	{
		"data/MODEL/object/Ceiling.x",
		"data/MODEL/object/Ceiling.x",
	};
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MAX_CEILINGTEXTURE; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ���[�h����
	m_pload = new CLoad[TYPE_MAX];
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Ceiling_Location.txt");
	// ���f����񐶐�
	m_pmodel_info = new CModel_info[TYPE_MAX];
	// ���f���ǂݍ���
	for (int nCntModel = 0; nCntModel < TYPE_MAX; nCntModel++)
	{
		m_pmodel_info[nCntModel].Load(pDevice, cModelfile[nCntModel]);
	}
	return S_OK;
}

// ----------------------------------------
// unload����
// ----------------------------------------
void CCeiling::UnLoad(void)
{
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MAX_CEILINGTEXTURE; nCnt++)
	{
		if (m_pTexture[nCnt] != NULL)
		{
			m_pTexture[nCnt]->Release();
			m_pTexture[nCnt] = NULL;
		}
	}

	// ���f���̕`����j��
	for (int nCntModelLoad = 0; nCntModelLoad < TYPE_MAX; nCntModelLoad++)
	{
		//���f���̔j��
		m_pmodel_info[nCntModelLoad].Unload();
	}

	delete[] m_pmodel_info;
	//m_pmodel_info = NULL;
	// ���[�h�̔j��
	delete[] m_pload;
	//m_pload = NULL;
	//// ���[�h�̔j��
	//delete m_pload;
	//m_pload = NULL;
	//// ���f���̔j��
	//m_pmodel_info->Unload();
	//delete m_pmodel_info;
	//m_pmodel_info = NULL;
}

// ----------------------------------------
// �ʒu�̐ݒ菈��
// ----------------------------------------
void CCeiling::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CCeiling::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CCeiling::GetPos(void)
{
	return CScene_X::GetPos();
}