// =====================================================================================================================================================================
//
// �X�e���V���V���h�E�̏��� [stencilshadow.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "stencilshadow.h"			// �C���N���[�h�t�@�C��
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "map.h"
#include "camera.h"
#include "player.h"
#include "game.h"
#include "scene2Dnew.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MODEL_FILE01				"data/OBJECT/stensileshadow.x"				// �~��

#define TEXTURE_FILE01				"data/TEXTURE/ston.jpg"						// �~��

#define RESIDUAL_ERROR				(0.4f)										// �덷
#define OBJECT_MOVE_X				(0.7f)										// �ړ��I�u�W�F�N�g�̈ړ���

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
MODEL_DRAWINFO		CStencilShadow::m_ModelDrawInfo	= {};
LPDIRECT3DTEXTURE9	CStencilShadow::m_pTexture		= {};
CScene2Dnew			*CStencilShadow::m_pScene2Dnew = {};

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CStencilShadow::CStencilShadow():CSceneX(PRIORITY_MODEL)
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CStencilShadow::~CStencilShadow()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CStencilShadow::Init(void)
{
	m_posOld	= D3DXVECTOR3(0.0f, 0.0f, 0.0f);					 // �ߋ��̈ʒu
	m_move		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);					 // �ړ�
	m_VtxMin	= D3DXVECTOR3(1000.0f, 1000.0f, 1000.0f);			 // �ŏ����_
	m_VtxMax	= D3DXVECTOR3(-1000.0f, -1000.0f, -1000.0f);		 // �ő咸�_

	// �ő�E�ŏ����_�̐ݒ�
	CLibrary::SetVertexObject(&m_VtxMin, &m_VtxMax, m_ModelDrawInfo.Mesh);

	// ���f���`����̐ݒ�
	SetModelDraw(&m_ModelDrawInfo);

	//m_pScene2Dnew = CScene2Dnew::Create();
	//m_pScene2Dnew->Init();
	//m_pScene2Dnew->SetCol(D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	//m_pScene2Dnew->SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));
	//m_pScene2Dnew->SetSize(D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f));

	// ������
	CSceneX::Init();
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CStencilShadow::Uninit(void)
{
	CSceneX::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CStencilShadow::Update(void)
{
	// �v���C���[�̏��擾
	CPlayer *pPlayer = CManager::GetGame()->GetPlayer();

	// �ʒu�̎擾
	D3DXVECTOR3 pos = CSceneX::GetPos();

	// �v���C���[�̈ʒu�ɍ��킹��
	pos = pPlayer->GetOldPos();

	// �ʒu�ۑ�
	m_posOld = pos;

	// �ʒu�X�V
	pos += m_move;

	// �ʒu�̐ݒ�
	CSceneX::SetPos(pos);

	// �X�V
	CSceneX::Update();

	//m_pScene2Dnew->Update();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CStencilShadow::Draw(void)
{
	D3DXMATRIX			mtxWorld;
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();	// �f�o�C�X�̎擾

	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);					// �X�e���V���o�b�t�@��L���ɂ���

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0);					// �F����0��
	pDevice->SetRenderState(D3DRS_STENCILREF, 0);						// �X�e���V���Q�ƒl(0)

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���̑Ώ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_ZERO);	// �X�e���V��Z�e�X�g���ɍ��i���Ă���
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_INCR);	// �X�e���V���e�X�g�ɍ��i�AZ�e�X�g�ɕs���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// �X�e���V���e�X�g�ɕs���i

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);				// �\�ʃJ�����O�ݒ�
	//���f���̕`��
	DrawModel();

	pDevice->SetRenderState(D3DRS_STENCILREF, 1);						// �X�e���V���Q�ƒl(1)

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���̑Ώ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_INCR);	// �X�e���V��Z�e�X�g���ɍ��i���Ă���
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_ZERO);	// �X�e���V���e�X�g�ɍ��i�AZ�e�X�g�ɕs���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// �X�e���V���e�X�g�ɕs���i

	// ���[���h�}�g���b�N�X�̌v�Z
	CLibrary::MatrixCalculation(&mtxWorld, GetRot(), GetPos());

	//�v�Z��}�g���b�N�X�ݒ�
	SetMatrix(mtxWorld);

	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʃJ�����O�ݒ�
	//���f���̕`��
	DrawModel();

	pDevice->SetRenderState(D3DRS_COLORWRITEENABLE, 0xf);				// �F���f�t�H���g�l�ɖ߂�
	pDevice->SetRenderState(D3DRS_STENCILREF, 2);						// �X�e���V���Q�ƒl(2)

	pDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL);			// �X�e���V���̑Ώ�
	pDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILCAPS_KEEP);	// �X�e���V��Z�e�X�g���ɍ��i���Ă���
	pDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILCAPS_KEEP);	// �X�e���V���e�X�g�ɍ��i�AZ�e�X�g�ɕs���i
	pDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILCAPS_ZERO);	// �X�e���V���e�X�g�ɕs���i

	//���f���̕`��
	DrawModel();

	//m_pScene2Dnew->Draw();

	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);			// �X�e���V���o�b�t�@�𖳌��ɂ���
}

// =====================================================================================================================================================================
//
// �X�e���V���V���h�E�̐���
//
// =====================================================================================================================================================================
CStencilShadow * CStencilShadow::Create()
{
	// �ϐ�
	CStencilShadow *pStencilShadow;

	// �������̊m��
	pStencilShadow = new CStencilShadow;

	// ������
	pStencilShadow->Init();

	// �e�N�X�`���̊��蓖��
	pStencilShadow->BindTexture(m_pTexture);

	return pStencilShadow;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CStencilShadow::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_FILE01, D3DXMESH_SYSTEMMEM, pDevice, NULL,
		&m_ModelDrawInfo.BuffMat, NULL, &m_ModelDrawInfo.nNumMat, &m_ModelDrawInfo.Mesh);

	// �e�N�X�`���ǂݍ���
	D3DXCreateTextureFromFile(pDevice, TEXTURE_FILE01, &m_pTexture);

	return S_OK;
}

// =====================================================================================================================================================================
//
// �A�����[�h
//
// =====================================================================================================================================================================
void CStencilShadow::Unload(void)
{
		// �e�N�X�`���̊J��
		if (m_pTexture != NULL)
		{
			m_pTexture->Release();
			m_pTexture = NULL;
		}
}

//// =====================================================================================================================================================================
////
//// �I�u�W�F�N�g�̓����蔻��
////
//// =====================================================================================================================================================================
//bool CStencilShadow::CollisionObject(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 *pSize, CObjectModel **ppObjectRet)
//{
//	// �J�����̎擾
//	CCamera *pCamera;
//	pCamera = CManager::GetRenderer()->GetCamera();
//	// �ʒu�̎擾
//	D3DXVECTOR3 pos = CSceneX::GetPos();
//	bool bLand = false;							// ���n�̔���
//
//	// NULL�`�F�b�N
//	if (ppObjectRet != NULL)
//	{
//		*ppObjectRet = NULL;
//	}
//
//	// �u���b�N�͈̔� ( �� )
//	if ((m_VtxMin.x + pos.x < pPos->x + pSize->x &&
//		m_VtxMax.x + pos.x > pPos->x - pSize->x) || 
//		(pCamera->GetCameraMode() == CCamera::CAMERA_MODE_2D &&
//		m_ObjectType == CObjectModel::OBJECTTYPE_SCAFFOLD_HIT))
//	{
//		// �u���b�N�͈̔� ( �c )
//		if (m_VtxMin.z + pos.z < pPos->z + pSize->z &&
//			m_VtxMax.z + pos.z > pPos->z - pSize->z)
//		{
//			// �u���b�N�͈̔� ( ���� )
//			if (m_VtxMin.y + pos.y <= pPos->y + pSize->y &&
//				m_VtxMax.y + pos.y > pPos->y)
//			{
//				// ��̓����蔻��
//				if (pPos->y < m_VtxMax.y + pos.y &&
//					pPosOld->y + RESIDUAL_ERROR >= m_VtxMax.y + m_posOld.y)
//				{
//					pMove->y = 0;
//					pPos->y = m_VtxMax.y + pos.y;
//					pPos->x += m_move.x;
//
//					bLand = true;
//					*ppObjectRet = this;
//				}
//
//				// �O�̓����蔻��
//				else if (pPos->z + pSize->z > m_VtxMin.z + pos.z &&
//					pPosOld->z + pSize->z < m_VtxMin.z + pos.z)
//				{
//					pPos->z = m_VtxMin.z + pos.z - pSize->z - RESIDUAL_ERROR;
//					pMove->z = 0;
//				}
//
//				// ���̓����蔻��
//				else if (pPos->z - pSize->z < m_VtxMax.z + pos.z &&
//					pPosOld->z - pSize->z >= m_VtxMax.z + m_posOld.z)
//				{
//					pPos->z = m_VtxMax.z + pos.z + pSize->z + RESIDUAL_ERROR;
//					pMove->z = 0;
//				}
//
//				// ���̓����蔻��
//				else if (pPos->x + pSize->x > m_VtxMin.x + pos.x &&
//					pPosOld->x + pSize->x <= m_VtxMin.x + m_posOld.x)
//				{
//					pPos->x = m_VtxMin.x + pos.x - pSize->x - RESIDUAL_ERROR;
//					pMove->x = 0;
//				}
//				// �E�̓����蔻��
//				else if (pPos->x - pSize->x < m_VtxMax.x + pos.x &&
//					pPosOld->x - pSize->x >= m_VtxMax.x + m_posOld.x)
//				{
//					pPos->x = m_VtxMax.x + pos.x + pSize->x + RESIDUAL_ERROR;
//					pMove->x = 0;
//				}
//
//				// ���̓����蔻��
//				else if (pPos->y + pSize->y > m_VtxMin.y + pos.y &&
//					pPosOld->y + pSize->y <= m_VtxMin.y + m_posOld.y)
//				{
//					pPos->y = m_VtxMin.y + pos.y - pSize->y - RESIDUAL_ERROR;
//					pMove->y = 0;
//				}
//				else
//				{
//					pMove->y = 0.0f;
//					pPos->y = m_VtxMax.y + pos.y;
//					pPos->x += m_move.x;
//
//					bLand = true;
//					*ppObjectRet = this;
//				}
//			}
//		}
//	}
//	return bLand;
//}