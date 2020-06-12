// =====================================================================================================================================================================
//
// �p�[�c���f���̏��� [partsmodel.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "partsmodel.h"			// �C���N���[�h�t�@�C��
#include "debugproc.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "motion.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MODEL_FILE00				"data/MODEL/body.x"							// �ǂݍ��ރv���C���[�t�@�C����			 ��
#define MODEL_FILE01				"data/MODEL/waist.x"						// �ǂݍ��ރv���C���[�t�@�C����			 ��
#define MODEL_FILE02				"data/MODEL/head.x"							// �ǂݍ��ރv���C���[�t�@�C����			 ��
#define MODEL_FILE03				"data/MODEL/arm.R.x"						// �ǂݍ��ރv���C���[�t�@�C����			 �E�r
#define MODEL_FILE04				"data/MODEL/hand.R.x"						// �ǂݍ��ރv���C���[�t�@�C����			 �E��
#define MODEL_FILE05				"data/MODEL/arm.L.x"						// �ǂݍ��ރv���C���[�t�@�C����			 ���r
#define MODEL_FILE06				"data/MODEL/hand.L.x"						// �ǂݍ��ރv���C���[�t�@�C����			 ����
#define MODEL_FILE07				"data/MODEL/thigh.R.x"						// �ǂݍ��ރv���C���[�t�@�C����			 �E��
#define MODEL_FILE08				"data/MODEL/leg.R.x"						// �ǂݍ��ރv���C���[�t�@�C����			 �E�r
#define MODEL_FILE09				"data/MODEL/foot.R.x"						// �ǂݍ��ރv���C���[�t�@�C����			 �E����
#define MODEL_FILE010				"data/MODEL/thigh.L.x"						// �ǂݍ��ރv���C���[�t�@�C����			 ����
#define MODEL_FILE011				"data/MODEL/leg.L.x"						// �ǂݍ��ރv���C���[�t�@�C����			 ���r
#define MODEL_FILE012				"data/MODEL/foot.L.x"						// �ǂݍ��ރv���C���[�t�@�C����			 ������

#define SPEED				(1.0f)						// �ړ����x

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
MODEL_DRAWINFO		CPartsModel::m_ModelDrawInfo[PLAYER_PARTS] = {};

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CPartsModel::CPartsModel()
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CPartsModel::~CPartsModel()
{
}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
void CPartsModel::Init(void)
{
	m_nFrame	= 0;

	CSceneX::Init();
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CPartsModel::Uninit(void)
{
	CSceneX::Uninit();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CPartsModel::Update(void)
{
	D3DXVECTOR3 rot = GetRot();

	// �X�V ( ���� )
	rot += m_Rot1F;

	// ��]�̐ݒ�
	CSceneX::SetRot(rot);

	// �e�̃}�g���b�N�X���擾
	m_pParentMatrix = GetMatrix();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CPartsModel::Draw(void)
{
	D3DXMATRIX			mtxWorld;

	// ���[���h�}�g���b�N�X�̌v�Z
	CLibrary::MatrixCalculation(&mtxWorld, GetRot(), GetPos());

	// �e�̈ʒu������
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, m_pParentMatrix);

	//�v�Z��}�g���b�N�X�ݒ�
	SetMatrix(mtxWorld);

	//���f���̕`��
	DrawModel();
}

// =====================================================================================================================================================================
//
// �p�[�c���f���̐���
//
// =====================================================================================================================================================================
CPartsModel * CPartsModel::Create()
{
	// �ϐ�
	CPartsModel *pPartsModel;

	// �������̊m��
	pPartsModel = new CPartsModel;

	// ������
	pPartsModel->Init();

	return pPartsModel;
}

// =====================================================================================================================================================================
//
// �C���f�b�N�X�̐ݒ�
//
// =====================================================================================================================================================================
void CPartsModel::SetIndex(int nIndex)
{
	m_nIndex = nIndex;

	// ���f���`����̐ݒ�
	SetModelDraw(&m_ModelDrawInfo[m_nIndex]);
}

// =====================================================================================================================================================================
//
// �v���C���[�̃��[�V����
//
// =====================================================================================================================================================================
void CPartsModel::SetMotionPlayer(int nMotion, int nKeySet)
{
	int nMotionFrame	= CMotion::GetMotionFrame(nMotion, nKeySet);
	D3DXVECTOR3	rotDest	= CMotion::GetMotionRotDest(nMotion, nKeySet, m_nIndex);
	D3DXVECTOR3 rot		= GetRot();

	//���� ( ���� )
	m_Rot1F = (rotDest - rot) / (float)nMotionFrame;
}

// =====================================================================================================================================================================
//
// ���[�h
//
// =====================================================================================================================================================================
HRESULT CPartsModel::Load(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = *CManager::GetRenderer()->GetDevice();

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(MODEL_FILE00, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[0].BuffMat, NULL, &m_ModelDrawInfo[0].nNumMat, &m_ModelDrawInfo[0].Mesh);			// ��
	D3DXLoadMeshFromX(MODEL_FILE01, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[1].BuffMat, NULL, &m_ModelDrawInfo[1].nNumMat, &m_ModelDrawInfo[1].Mesh);			// ��
	D3DXLoadMeshFromX(MODEL_FILE02, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[2].BuffMat, NULL, &m_ModelDrawInfo[2].nNumMat, &m_ModelDrawInfo[2].Mesh);			// ��
	D3DXLoadMeshFromX(MODEL_FILE03, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[3].BuffMat, NULL, &m_ModelDrawInfo[3].nNumMat, &m_ModelDrawInfo[3].Mesh);			// �E�r
	D3DXLoadMeshFromX(MODEL_FILE04, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[4].BuffMat, NULL, &m_ModelDrawInfo[4].nNumMat, &m_ModelDrawInfo[4].Mesh);			// �E��
	D3DXLoadMeshFromX(MODEL_FILE05, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[5].BuffMat, NULL, &m_ModelDrawInfo[5].nNumMat, &m_ModelDrawInfo[5].Mesh);			// ���r
	D3DXLoadMeshFromX(MODEL_FILE06, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[6].BuffMat, NULL, &m_ModelDrawInfo[6].nNumMat, &m_ModelDrawInfo[6].Mesh);			// ����
	D3DXLoadMeshFromX(MODEL_FILE07, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[7].BuffMat, NULL, &m_ModelDrawInfo[7].nNumMat, &m_ModelDrawInfo[7].Mesh);			// �E��
	D3DXLoadMeshFromX(MODEL_FILE08, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[8].BuffMat, NULL, &m_ModelDrawInfo[8].nNumMat, &m_ModelDrawInfo[8].Mesh);			// �E�r
	D3DXLoadMeshFromX(MODEL_FILE09, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[9].BuffMat, NULL, &m_ModelDrawInfo[9].nNumMat, &m_ModelDrawInfo[9].Mesh);			// �E����
	D3DXLoadMeshFromX(MODEL_FILE010, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[10].BuffMat, NULL, &m_ModelDrawInfo[10].nNumMat, &m_ModelDrawInfo[10].Mesh);		// ����
	D3DXLoadMeshFromX(MODEL_FILE011, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[11].BuffMat, NULL, &m_ModelDrawInfo[11].nNumMat, &m_ModelDrawInfo[11].Mesh);		// ���r
	D3DXLoadMeshFromX(MODEL_FILE012, D3DXMESH_SYSTEMMEM, pDevice, NULL, &m_ModelDrawInfo[12].BuffMat, NULL, &m_ModelDrawInfo[12].nNumMat, &m_ModelDrawInfo[12].Mesh);		// ������

	return S_OK;
}

// =====================================================================================================================================================================
//
// �A�����[�h
//
// =====================================================================================================================================================================
void CPartsModel::Unload(void)
{

}