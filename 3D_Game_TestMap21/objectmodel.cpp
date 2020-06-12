// =====================================================================================================================================================================
//
// �I�u�W�F�N�g���f���̏��� [objectmodel.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "objectmodel.h"			// �C���N���[�h�t�@�C��
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "motion.h"
#include "map.h"
#include "effect.h"
#include "camera.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MODEL_FILE01				"data/OBJECT/stone0.x"						// ��
#define MODEL_FILE02				"data/OBJECT/box0.x"						// ��
#define MODEL_FILE03				"data/OBJECT/ground.L.x"					// �n�� (��
#define MODEL_FILE04				"data/OBJECT/ground.M.x"					// �n�� (��
#define MODEL_FILE05				"data/OBJECT/ground.S.x"					// �n�� (��
#define MODEL_FILE06				"data/OBJECT/geyser.x"						// �Ԍ���
#define MODEL_FILE07				"data/OBJECT/scaffold.x"					// ����
#define MODEL_FILE08				"data/OBJECT/scaffold_Hit.x"				// 2D�ł������鑫��
#define MODEL_FILE09				"data/OBJECT/scaffold_Move.x"				// ��������
#define MODEL_FILE010				"data/OBJECT/wall.x"						// ��
#define MODEL_FILE011				"data/OBJECT/ground.Half.x"					// �n�� (�n�[�t
#define MODEL_FILE012				"data/OBJECT/ground.quarter.x"				// �n�� (4/1
#define MODEL_FILE013				"data/OBJECT/signboard_fall.x"				// �Ŕ� (������
#define MODEL_FILE014				"data/OBJECT/signboard_jump.x"				// �Ŕ� (�W�����v
#define MODEL_FILE015				"data/OBJECT/signboard_gayser.x"			// �Ŕ� (�Ԍ���
#define MODEL_FILE016				"data/OBJECT/signboard_change.x"			// �Ŕ� (�J�����ؑւ�
#define MODEL_FILE017				"data/OBJECT/signboard_All_ride.x"			// �Ŕ� (2D�ł�����
#define MODEL_FILE018				"data/OBJECT/signboard_3D_ride.x"			// �Ŕ� (3D�ł������Ȃ�

#define TEXTURE_FILE01				"data/TEXTURE/stone.jpg"					// ��
#define TEXTURE_FILE02				"data/TEXTURE/box02.png"					// ��
#define TEXTURE_FILE03				"data/TEXTURE/Rock00.jpg"					// �n��
#define TEXTURE_FILE04				"data/TEXTURE/Stone00.jpg"					// �Ԍ���
#define TEXTURE_FILE05				"data/TEXTURE/hibi.jpg"						// ����
#define TEXTURE_FILE06				"data/TEXTURE/iron.jpg"						// 2D�ł������鑫��
#define TEXTURE_FILE07				"data/TEXTURE/block.png"					// ��������
#define TEXTURE_FILE08				"data/TEXTURE/fall00.png"					// �Ŕ� (������
#define TEXTURE_FILE09				"data/TEXTURE/jump00.png"					// �Ŕ� (�W�����v
#define TEXTURE_FILE10				"data/TEXTURE/gayser_caution.png"			// �Ŕ� (�Ԍ���
#define TEXTURE_FILE11				"data/TEXTURE/change.png"					// �Ŕ� (�J�����ؑւ�
#define TEXTURE_FILE12				"data/TEXTURE/ride01.png"					// �Ŕ� (2D�ł�����
#define TEXTURE_FILE13				"data/TEXTURE/ride02.png"					// �Ŕ� (3D�ł������Ȃ�

#define RESIDUAL_ERROR				(0.4f)										// �덷
#define OBJECT_MOVE_X				(0.7f)										// �ړ��I�u�W�F�N�g�̈ړ���

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
MODEL_DRAWINFO		CObjectModel::m_ModelDrawInfo[OBJECTTYPE_MAX]	= {};
LPDIRECT3DTEXTURE9	CObjectModel::m_apTexture[OBJECTTYPE_MAX]		= {};

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CObjectModel::CObjectModel():CSceneX(PRIORITY_MODEL)
{
	m_ObjectType = OBJECTTYPE_NONE;		// �I�u�W�F�N�g�̎��
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CObjectModel::~CObjectModel()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CObjectModel::Init(void)
{
	m_posOld	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);					 // �ߋ��̈ʒu
	m_move		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);					 // �ړ�
	m_VtxMin	= D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);			 // �ŏ����_
	m_VtxMax	= D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);		 // �ő咸�_

	// �ő�E�ŏ����_�̐ݒ�
	CLibrary::SetVertexObject(&m_VtxMin, &m_VtxMax, m_ModelDrawInfo[m_ObjectType].Mesh);

	// ���f���`����̐ݒ�
	SetModelDraw(&m_ModelDrawInfo[m_ObjectType]);

	// ������
	CSceneX::Init();
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CObjectModel::Uninit(void)
{
	CSceneX::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CObjectModel::Update(void)
{
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CSceneX::GetPos();

	// �ʒu�ۑ�
	m_posOld = pos;

	switch (m_ObjectType)
	{
	case CObjectModel::OBJECTTYPE_SCAFFOLD_MOVE:

		// �ړ�����
		if (pos.x <= -100.0f)
		{
			// ���]
			m_move.x *= -1;
		}
		else if (pos.x >= 100.0f)
		{
			// ���]
			m_move.x *= -1;
		}
		break;
	}

	// �ʒu�X�V
	pos += m_move;

	// �ʒu�̐ݒ�
	CSceneX::SetPos(pos);

	// �X�V
	CSceneX::Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CObjectModel::Draw(void)
{
	D3DXMATRIX			mtxWorld;

	// ���[���h�}�g���b�N�X�̌v�Z
	CLibrary::MatrixCalculation(&mtxWorld, GetRot(), GetPos());

	//�v�Z��}�g���b�N�X�ݒ�
	SetMatrix(mtxWorld);

	//���f���̕`��
	DrawModel();
}

// =====================================================================================================================================================================
//
// �I�u�W�F�N�g���f���̐���
//
// =====================================================================================================================================================================
CObjectModel * CObjectModel::Create(D3DXVECTOR3 pos, OBJECTTYPE type)
{
	// �ϐ�
	CObjectModel *pObjectModel;

	// �������̊m��
	pObjectModel = new CObjectModel;

	// �I�u�W�F�N�g�̎��
	pObjectModel->m_ObjectType = type;

	// ������
	pObjectModel->Init();

	// �ʒu�̐ݒ�
	pObjectModel->SetPos(pos);

	// �e�N�X�`���̊��蓖��
	pObjectModel->BindTexture(m_apTexture[type]);

	switch (pObjectModel->m_ObjectType)
	{
	case CObjectModel::OBJECTTYPE_SCAFFOLD_MOVE:
		// ���ړ�
		pObjectModel->m_move.x = OBJECT_MOVE_X;
		break;
	}
	// �Ԍ���̃I�u�W�F�N�g�̂Ƃ�
	if (pObjectModel->m_ObjectType == OBJECTTYPE_GAYSER)
	{
		// �Ԍ���̃G�t�F�N�g����
		CEffect::Create(pos, CEffect::EFFECTTYPE_GAYSER);
	}
	return pObjectModel;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CObjectModel::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// ���f���t�@�C����
	char *sModelFileName[OBJECTTYPE_MAX]
	{
		{ MODEL_FILE01 },		// OBJECTTYPE_STONE				( ��
		{ MODEL_FILE02 },		// OBJECTTYPE_BOX				( ��
		{ MODEL_FILE03 },		// OBJECTTYPE_GROUND_L			( �n�� (��
		{ MODEL_FILE04 },		// OBJECTTYPE_GROUND_M			( �n�� (��
		{ MODEL_FILE05 },		// OBJECTTYPE_GROUND_S			( �n�� (��
		{ MODEL_FILE06 }, 		// OBJECTTYPE_GAYSER			( �Ԍ���
		{ MODEL_FILE07 }, 		// OBJECTTYPE_SCAFFOLD			( ����
		{ MODEL_FILE08 }, 		// OBJECTTYPE_SCAFFOLD_HIT		( 2D�ł������鑫��
		{ MODEL_FILE09 }, 		// OBJECTTYPE_SCAFFOLD_MOVE		( ��������
		{ MODEL_FILE010 }, 		// OBJECTTYPE_WALL				( ��
		{ MODEL_FILE011 }, 		// OBJECTTYPE_GROUND_HALF		( �n�� (�n�[�t
		{ MODEL_FILE012 }, 		// OBJECTTYPE_GROUND_QUARTER	( �n�� (4/1
		{ MODEL_FILE013 }, 		// OBJECTTYPE_SIGNBOARD_FALL	( �Ŕ� (������
		{ MODEL_FILE014 }, 		// OBJECTTYPE_SIGNBOARD_JUMP	( �Ŕ� (�W�����v
		{ MODEL_FILE015 }, 		// OBJECTTYPE_SIGNBOARD_GAYSER	( �Ŕ� (�Ԍ���
		{ MODEL_FILE016 }, 		// OBJECTTYPE_SIGNBOARD_CHANGE	( �Ŕ� (�J�����ؑւ�
		{ MODEL_FILE017 }, 		// OBJECTTYPE_SIGNBOARD_ALL_RIDE( �Ŕ� (2D�ł�����
		{ MODEL_FILE018 }, 		// OBJECTTYPE_SIGNBOARD_3D_RIDE	( �Ŕ� (3D�ł������Ȃ�
	};

	// �e�N�X�`���t�@�C����
	char *sTextureFileName[OBJECTTYPE_MAX]
	{
		{ TEXTURE_FILE01 },		// OBJECTTYPE_STONE				( ��
		{ TEXTURE_FILE02 },		// OBJECTTYPE_BOX				( ��
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_L			( �n�� (��
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_M			( �n�� (��
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_S			( �n�� (��
		{ TEXTURE_FILE04 },		// OBJECTTYPE_GAYSER			( �Ԍ���
		{ TEXTURE_FILE05 },		// OBJECTTYPE_SCAFFOLD			( ����
		{ TEXTURE_FILE06 },		// OBJECTTYPE_SCAFFOLD_HIT		( 2D�ł������鑫��
		{ TEXTURE_FILE07 },		// OBJECTTYPE_SCAFFOLD_MOVE		( ��������
		{ TEXTURE_FILE03 },		// OBJECTTYPE_WALL				( ��
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_HALF		( �n�� (�n�[�t
		{ TEXTURE_FILE03 },		// OBJECTTYPE_GROUND_QUARTER	( �n�� (4/1
		{ TEXTURE_FILE08 },		// OBJECTTYPE_SIGNBOARD_FALL	( �Ŕ� (������
		{ TEXTURE_FILE09 },		// OBJECTTYPE_SIGNBOARD_JUMP	( �Ŕ� (�W�����v
		{ TEXTURE_FILE10 },		// OBJECTTYPE_SIGNBOARD_GAYSER	( �Ŕ� (�Ԍ���
		{ TEXTURE_FILE11 },		// OBJECTTYPE_SIGNBOARD_CHANGE	( �Ŕ� (�J�����ؑւ�
		{ TEXTURE_FILE12 },		// OBJECTTYPE_SIGNBOARD_ALL_RIDE( �Ŕ� (2D�ł�����
		{ TEXTURE_FILE13 },		// OBJECTTYPE_SIGNBOARD_3D_RIDE	( �Ŕ� (3D�ł������Ȃ�
	};

	for (int nCntObject = 0; nCntObject < OBJECTTYPE_MAX; nCntObject++)
	{
		// X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(sModelFileName[nCntObject], D3DXMESH_SYSTEMMEM, pDevice, NULL, 
			&m_ModelDrawInfo[nCntObject].BuffMat, NULL, &m_ModelDrawInfo[nCntObject].nNumMat, &m_ModelDrawInfo[nCntObject].Mesh);

		// �e�N�X�`���ǂݍ���
		D3DXCreateTextureFromFile(pDevice, sTextureFileName[nCntObject], &m_apTexture[nCntObject]);
	}

	return S_OK;
}

// =====================================================================================================================================================================
//
// �A�����[�h
//
// =====================================================================================================================================================================
void CObjectModel::Unload(void)
{
	for (int nCntTex = 0; nCntTex < CObjectModel::OBJECTTYPE_MAX; nCntTex++)
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
// �I�u�W�F�N�g�̓����蔻��
//
// =====================================================================================================================================================================
bool CObjectModel::CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize, CObjectModel **ppObjectRet)
{
	// �J�����̎擾
	CCamera *pCamera;
	pCamera = CManager::GetRenderer()->GetCamera();
	// �ʒu�̎擾
	D3DXVECTOR3 pos = CSceneX::GetPos();
	bool bLand = false;							// ���n�̔���

	// NULL�`�F�b�N
	if (ppObjectRet != NULL)
	{
		*ppObjectRet = NULL;
	}

	// �u���b�N�͈̔� ( �� )
	if ((m_VtxMin.x + pos.x < pPos->x + pSize->x &&
		m_VtxMax.x + pos.x > pPos->x - pSize->x) || 
		(pCamera->GetCameraMode() == CCamera::CAMERA_MODE_2D &&
		m_ObjectType == CObjectModel::OBJECTTYPE_SCAFFOLD_HIT))
	{
		// �u���b�N�͈̔� ( �c )
		if (m_VtxMin.z + pos.z < pPos->z + pSize->z &&
			m_VtxMax.z + pos.z > pPos->z - pSize->z)
		{
			// �u���b�N�͈̔� ( ���� )
			if (m_VtxMin.y + pos.y <= pPos->y + pSize->y &&
				m_VtxMax.y + pos.y > pPos->y)
			{
				// ��̓����蔻��
				if (pPos->y < m_VtxMax.y + pos.y &&
					pPosOld->y + RESIDUAL_ERROR >= m_VtxMax.y + m_posOld.y)
				{
					pMove->y = 0;
					pPos->y = m_VtxMax.y + pos.y;
					pPos->x += m_move.x;

					bLand = true;
					*ppObjectRet = this;
				}

				// �O�̓����蔻��
				else if (pPos->z + pSize->z > m_VtxMin.z + pos.z &&
					pPosOld->z + pSize->z < m_VtxMin.z + pos.z)
				{
					pPos->z = m_VtxMin.z + pos.z - pSize->z - RESIDUAL_ERROR;
					pMove->z = 0;
				}

				// ���̓����蔻��
				else if (pPos->z - pSize->z < m_VtxMax.z + pos.z &&
					pPosOld->z - pSize->z >= m_VtxMax.z + m_posOld.z)
				{
					pPos->z = m_VtxMax.z + pos.z + pSize->z + RESIDUAL_ERROR;
					pMove->z = 0;
				}

				// ���̓����蔻��
				else if (pPos->x + pSize->x > m_VtxMin.x + pos.x &&
					pPosOld->x + pSize->x <= m_VtxMin.x + m_posOld.x)
				{
					pPos->x = m_VtxMin.x + pos.x - pSize->x - RESIDUAL_ERROR;
					pMove->x = 0;
				}
				// �E�̓����蔻��
				else if (pPos->x - pSize->x < m_VtxMax.x + pos.x &&
					pPosOld->x - pSize->x >= m_VtxMax.x + m_posOld.x)
				{
					pPos->x = m_VtxMax.x + pos.x + pSize->x + RESIDUAL_ERROR;
					pMove->x = 0;
				}

				// ���̓����蔻��
				else if (pPos->y + pSize->y > m_VtxMin.y + pos.y &&
					pPosOld->y + pSize->y <= m_VtxMin.y + m_posOld.y)
				{
					pPos->y = m_VtxMin.y + pos.y - pSize->y - RESIDUAL_ERROR;
					pMove->y = 0;
				}
				else
				{
					pMove->y = 0.0f;
					pPos->y = m_VtxMax.y + pos.y;
					pPos->x += m_move.x;

					bLand = true;
					*ppObjectRet = this;
				}
			}
		}
	}
	return bLand;
}

// =====================================================================================================================================================================
//
// �I�u�W�F�N�g�̎�ނ̐ݒ�
//
// =====================================================================================================================================================================
void CObjectModel::SetObjectType(OBJECTTYPE type)
{
	m_ObjectType = type;

	// �ő�E�ŏ����_�̐ݒ�
	CLibrary::SetVertexObject(&m_VtxMin, &m_VtxMax, m_ModelDrawInfo[m_ObjectType].Mesh);

	// ���f���`����̐ݒ�
	SetModelDraw(&m_ModelDrawInfo[m_ObjectType]);
}