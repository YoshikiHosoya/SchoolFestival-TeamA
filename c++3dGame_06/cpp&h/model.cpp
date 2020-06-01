//=============================================================================
//
// ���f������ [player.cpp]
// Author : Fujiwara Masato
//
//=============================================================================
#include "model.h"

//=============================================================================
// �}�N����`
//=============================================================================

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CModel::CModel()
{
	m_model_info.pMesh = NULL;
	m_model_info.pBuffMat = NULL;
	m_model_info.pTexture = NULL;
	m_model_info.nNumMat = 0;
	m_model_info.vtxMinMaterials = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.vtxMaxMaterials = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_model_info.nParent = 0;
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_nFrame = 0;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CModel::~CModel()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CModel::Init(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();

	// ������
	m_size = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CModel::Uninit(void)
{
	// �e�N�X�`���[�̊J��
	if (m_model_info.pTexture != NULL)
	{
		m_model_info.pTexture->Release();
		m_model_info.pTexture = NULL;
	}
	// �e�N�X�`���[�̊J��
	for (int nCntTex = 0; nCntTex < 30; nCntTex++)
	{
		if (pTexture[nCntTex] != NULL)
		{
			pTexture[nCntTex]->Release();
			pTexture[nCntTex] = NULL;
		}
	}
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CModel::Update(void)
{
	// ���f�����̃��[�V��������
	m_model_info.pos += (m_model_info.posDest - m_model_info.pos) / (float)m_nFrame;
	m_model_info.rot += (m_model_info.rotDest - m_model_info.rot) / (float)m_nFrame;
}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CModel::Draw(
	D3DXMATRIX & mtx
)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX			mtxRot, mtxTrans ,mtxScal;	// �v�Z�p�}�g���b�N�X
	D3DXMATERIAL		*pMat;						// ���݂̃}�e���A���ۑ�



	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	m_Falts = m_mtxWorld;

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScal,
		m_model_info.scal.x,
		m_model_info.scal.y,
		m_model_info.scal.z);

	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��]�s��)
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld, &mtxScal);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScal,
		1.0f,
		1.0f,
		1.0f);

	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��]�s��)
	D3DXMatrixMultiply(&m_Falts,
		&m_Falts, &mtxScal);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_model_info.rot.y,
		m_model_info.rot.x,
		m_model_info.rot.z);

	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��]�s��)
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld, &mtxRot);

	D3DXMatrixMultiply(&m_Falts,
		&m_Falts, &mtxRot);

	// �ʒu�𔽉f //
	// ���s�ړ��s��쐬(�I�t�Z�b�g)
	D3DXMatrixTranslation(&mtxTrans,	// �����̓��ꕨ
		m_model_info.pos.x,
		m_model_info.pos.y,
		m_model_info.pos.z);

	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:�ړ��s��)
	D3DXMatrixMultiply(&m_mtxWorld,	// 1
		&m_mtxWorld,				// 2
		&mtxTrans);					// 3

	D3DXMatrixMultiply(&m_Falts,
		&m_Falts, &mtxTrans);

		// �e���������Ă���Ƃ�
	if (m_Parent != NULL)
	{
		// �e�Ǝq�̍s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��[�e]�s��)
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			&m_Parent->m_mtxWorld);
	}
	// ���ׂĂ̐e�̏ꍇ
	else
	{
		// �e�Ǝq�̍s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��[�e]�s��)
		D3DXMatrixMultiply(&m_mtxWorld,
			&m_mtxWorld,
			&mtx);

		/*
		D3DXMatrixMultiply(&m_Falts,
			&m_Falts,
			&mtx);
			*/
	}
	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&m_matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_model_info.pBuffMat->GetBufferPointer();
	// �e�N�X�`���[�ݒ�
	pDevice->SetTexture(0, NULL);

	// �J�E���g�}�e���A��
	for (int nCntMat = 0; nCntMat < (int)m_model_info.nNumMat; nCntMat++, pMat++)
	{
		// �e�N�X�`���[�ݒ�
		if (pTexture[nCntMat] != NULL)
		{
			pDevice->SetTexture(0, pTexture[nCntMat]);
		}

		// �}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat->MatD3D);
		// �`��
		m_model_info.pMesh->DrawSubset(nCntMat);
	}
	// �}�e���A�����f�t�H���g�ɖ߂�
	pDevice->SetMaterial(&m_matDef);

	//���_�t�H�[�}�b�g�̐ݒ�
	//pDevice->SetFVF(FVF_VERTEX_3D);
}

// ----------------------------------------
// ��������
// ----------------------------------------
CModel * CModel::Create()
{
	// �ϐ��錾
	CModel * pModel;	// ���f��
	// �������m��
	pModel = new CModel();
	// ������
	pModel->Init();
	// ����Ԃ�
	return pModel;
}

// ----------------------------------------
// �e�p�[�c�̐ݒ菈��
// ----------------------------------------
void CModel::SetParent(CModel * pModel)
{
	m_Parent = pModel;
}

// ----------------------------------------
// �e�N�X�`��
// ----------------------------------------
void CModel::BindTexture(LPDIRECT3DTEXTURE9 p_Tex)
{
	m_model_info.pTexture = p_Tex;
}

// ----------------------------------------
// ���f���̏��n������
// ----------------------------------------
void CModel::BindModel(
	MODEL_INFO &model_info,
	MODEL_OFFSET &offset	// ���f���̃I�t�Z�b�g
)
{
	// ���f�����̎擾
	m_model_info = model_info;
	// ���f���̃I�t�Z�b�g
	m_model_info.pos = offset.pos;
	m_model_info.rot = offset.rot;
	m_model_info.posDest = offset.pos;
	m_model_info.rotDest = offset.rot;
	m_model_info.nParent = offset.nParent;
	m_model_info.nParent = m_model_info.nParent;

	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();
	D3DXMATERIAL		*pMat;					// ���݂̃}�e���A���ۑ�

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_model_info.pBuffMat->GetBufferPointer();
	// �J�E���g�}�e���A��
	for (int nCntMat = 0; nCntMat < (int)m_model_info.nNumMat; nCntMat++, pMat++)
	{
		if (pMat->pTextureFilename != "")
		{
			D3DXCreateTextureFromFile(pDevice, pMat->pTextureFilename, &pTexture[nCntMat]);
		}
	}
}

// ----------------------------------------
// ���f���̈ʒu�ݒ菈��
// ----------------------------------------
void CModel::SetPos(D3DXVECTOR3 &pos)
{
	m_model_info.pos = pos;
}

// ----------------------------------------
// ���[�V�����̐ݒ菈��
// ----------------------------------------
void CModel::SetMotion(
	KEY &key,
	int nMaxFrame
)
{
	m_model_info.posDest = key.pos;
	m_model_info.rotDest = key.rot;
	m_nFrame = nMaxFrame;
}

// ----------------------------------------
// ���f�����̎擾
// ----------------------------------------
MODEL_INFO *CModel::GetModelInfo(void)
{
	return &m_model_info;
}

// ----------------------------------------
// ���f�����̐ݒ�
// ---------------------------------------
void CModel::SetModelInfo(CONST MODEL_INFO &ModelInfo)
{
	m_model_info = ModelInfo;
}
