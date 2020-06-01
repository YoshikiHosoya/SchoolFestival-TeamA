// ----------------------------------------
//
// �u���b�N�����̐���[block.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "wall.h"
#include "model_info.h"

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------
LPDIRECT3DTEXTURE9 CWall::m_pTexture[MAX_WALLTEXTURE] = {};		// �e�N�X�`���ւ̃|�C���^
CLoad	*CWall::m_pload = NULL;							// ���[�h
CModel_info	*CWall::m_pmodel_info = NULL;					// ���f�����
int		CWall::m_nAll = 0;									// �ԍ�

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CWall::CWall() : CScene_X::CScene_X(ACTOR_WALL, LAYER_3DOBJECT)
{
	m_type = SIZE_I;
	//m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	//m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CWall::~CWall()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CWall::Init(void)
{
	// X�I�u�W�F�N�g����
	CScene_X::Init();
	// ���f�����ݒ�
	CScene_X::BindModel(m_pmodel_info[m_type].GetModel_info());
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MAX_WALLTEXTURE; nCnt++)
	{
		CScene_X::BindTexture(m_pTexture[nCnt]);
	}
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CWall::Uninit(void)
{
	CScene_X::Uninit();
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CWall::Update(void)
{
	CScene_X::Update();
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CWall::Draw(void)
{
	CScene_X::Draw();
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CWall * CWall::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SIZE type)
{
	// �ϐ��錾
	CWall * pWall;		// �V�[��3D�N���X
						// �������̐���(����->��{�N���X,��->�h���N���X)
	pWall = new CWall();
	// ��ނ̐ݒ�
	pWall->m_type = type;
	// ����������
	pWall->Init();
	// ���W�̐ݒ�
	//pWall->m_pos = pos;
	pWall->SetPos(pos);
	// ��]�̐ݒ�
	//pWall->m_rot = rot;
	pWall->SetRot(rot);
	// ���������I�u�W�F�N�g��Ԃ�
	return pWall;
}

// ----------------------------------------
// �ǂݍ��ݍ쐬����
// ----------------------------------------
void CWall::LoadCreate(void)
{
	// �ϐ��錾
	CWall * pWall;	// �u���b�N
					// �u���b�N
	for (int nCntWall = 0; nCntWall < m_nAll; nCntWall++)
	{
		pWall = CWall::Create(m_pload->GetInfo(nCntWall).pos,
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
HRESULT CWall::Load(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9 pDevice =					// �f�o�C�X�̎擾
		CManager::GetRenderer()->GetDevice();
	char cTex[MAX_WALLTEXTURE][128] =					// �e�N�X�`���[��
	{
		"data/TEXTURE/obj_tex/WallPattern00.jpg",
		"data/TEXTURE/obj_tex/wall.jpg",
	};
	char cModelfile[TYPE_MAX][256] =			// ���f���t�@�C����
	{
		"data/MODEL/object/Wall_001.x",
		"data/MODEL/object/Wall_002.x",
		"data/MODEL/object/Wall_003.x",
		"data/MODEL/object/Wall_004.x",
		"data/MODEL/object/Wall_005.x",
		"data/MODEL/object/Wall_006.x",
		"data/MODEL/object/Wall_007.x",
		"data/MODEL/object/Wall_008.x",
		"data/MODEL/object/Wall_009.x",
		"data/MODEL/object/Wall_010.x",
		"data/MODEL/object/Wall_015.x",
		"data/MODEL/object/Wall_021.x",
	};
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MAX_WALLTEXTURE; nCnt++)
	{
		D3DXCreateTextureFromFile(pDevice, cTex[nCnt], &m_pTexture[nCnt]);
	}
	// ���[�h����
	m_pload = new CLoad[TYPE_MAX];
	// ���[�h�ǂݍ���
	m_nAll = m_pload->Load("data/LOAD/OBJECT/Wall_Location.txt");
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
void CWall::UnLoad(void)
{
	// �e�N�X�`���[�ݒ�
	for (int nCnt = 0; nCnt < MAX_WALLTEXTURE; nCnt++)
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
void CWall::SetPos(D3DXVECTOR3 pos)
{
	CScene_X::SetPos(pos);
}

// ----------------------------------------
// ��]�̐ݒ菈��
// ----------------------------------------
void CWall::SetRot(D3DXVECTOR3 rot)
{
	CScene_X::SetRot(rot);
}

// ----------------------------------------
// �ʒu�̎擾����
// ----------------------------------------
D3DXVECTOR3 CWall::GetPos(void)
{
	return CScene_X::GetPos();
}