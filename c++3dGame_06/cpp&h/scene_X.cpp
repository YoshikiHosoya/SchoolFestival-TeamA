// ----------------------------------------
//
// X�V�[�������̐���[scene_X.cpp]
// Author : Fujiwara Masato
//
// ----------------------------------------

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_X.h"
#include "manager.h"
#include "debugproc.h"
#include "scene_three.h"
#include "game.h"
#include "floor.h"
#include "wall.h"
// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define OBJECT_COLLISIONSIZE (120.0)	// �����蔻��̑傫��

// ----------------------------------------
//
// �ÓI�ϐ��錾
//
// ----------------------------------------

// ----------------------------------------
// �R���X�g���N�^����
// ----------------------------------------
CScene_X::CScene_X()
{
	m_model_info.pMesh = NULL;									// ���b�V�����ւ̃|�C���^
	m_model_info.pBuffMat = NULL;									// �}�e���A�����ւ̃|�C���^
	m_model_info.nNumMat = NULL;									// �}�e���A���̐�
	m_model_info.pTexture = NULL;
	m_model_info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_model_info.posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����ʒu
	m_model_info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���݉�]��
	m_model_info.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �L�[�Ԃ̉�]��
	m_model_info.nParent = 0;								// �e���f���̃C���f�b�N�X
	m_model_info.nNum = 0;
	m_nCount = 0;
}

// ----------------------------------------
// �C�j�V�����C�U�R���X�g���N�^
// ----------------------------------------
CScene_X::CScene_X(ACTOR actor, LAYER layer) : CScene::CScene(actor,layer)
{
	m_model_info.pMesh = NULL;									// ���b�V�����ւ̃|�C���^
	m_model_info.pBuffMat = NULL;									// �}�e���A�����ւ̃|�C���^
	m_model_info.nNumMat = NULL;									// �}�e���A���̐�
	m_model_info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_model_info.posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����ʒu
	m_model_info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���݉�]��
	m_model_info.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �L�[�Ԃ̉�]��
	m_model_info.nParent = 0;								// �e���f���̃C���f�b�N�X
	m_model_info.nNum = 0;
	m_nCount = 0;
}

// ----------------------------------------
// �f�X�g���N�^����
// ----------------------------------------
CScene_X::~CScene_X()
{
}

// ----------------------------------------
// ����������
// ----------------------------------------
void CScene_X::Init(void)
{
	m_model_info.pMesh = NULL;									// ���b�V�����ւ̃|�C���^
	m_model_info.pBuffMat = NULL;									// �}�e���A�����ւ̃|�C���^
	m_model_info.nNumMat = NULL;									// �}�e���A���̐�
	m_model_info.pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// �ʒu
	m_model_info.posDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// �����ʒu
	m_model_info.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);				// ���݉�]��
	m_model_info.rotDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �L�[�Ԃ̉�]��
	m_model_info.nParent = 0;								// �e���f���̃C���f�b�N�X
	m_model_info.size = D3DXVECTOR3(100.0f, 100.0f, 100.0f);
	//m_model_info.nNum = 0;
}

// ----------------------------------------
// �I������
// ----------------------------------------
void CScene_X::Uninit(void)
{
	/*
	// ���b�V���̊J��
	if (m_model_info.pMesh != NULL)
	{
		m_model_info.pMesh->Release();
		m_model_info.pMesh = NULL;
	}

	// �}�e���A���̊J��
	if (m_model_info.pBuffMat != NULL)
	{
		m_model_info.pBuffMat->Release();
		m_model_info.pBuffMat = NULL;
	}

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
	*/
}

// ----------------------------------------
// �X�V����
// ----------------------------------------
void CScene_X::Update(void)
{

}

// ----------------------------------------
// �`�揈��
// ----------------------------------------
void CScene_X::Draw(void)
{
	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX			mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X
	D3DXMATERIAL		*pMat;					// ���݂̃}�e���A���ۑ�
	D3DMATERIAL9		matDef;					// �}�e���A���f�[�^�̃|�C���^

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_mtxWorld);

	// ��]�𔽉f
	// �X�P�[���𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot,
		m_model_info.rot.y,
		m_model_info.rot.x,
		m_model_info.rot.z);

	// �s��̐�(1:���[���h�s�� = 2:���[���h�s�� * 3:��]�s��)
	D3DXMatrixMultiply(&m_mtxWorld,
		&m_mtxWorld, &mtxRot);


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

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_model_info.pBuffMat->GetBufferPointer();

	/*for (int nCount = 0; nCount < m_model_info.nNum; nCount++)
	{
		pDevice->SetTexture(nCount, m_model_info.pTexture[nCount]);
	}*/

	//pDevice->SetTexture(0, m_model_info.pTexture);
	// �e�N�X�`���[�ݒ�
	pDevice->SetTexture(0, NULL);

	//for (int nCntTexture = 0; nCntTexture < 2; nCntTexture++)
	//{
	//	// �e�N�X�`���[�ݒ�
	//	if (pTexture[nCntTexture] != NULL)
	//	{
	//		pDevice->SetTexture(nCntTexture, pTexture[nCntTexture]);
	//	}
	//}

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
	pDevice->SetMaterial(&matDef);
}

// ----------------------------------------
// �쐬����
// ----------------------------------------
CScene_X * CScene_X::Create()
{
	// �ϐ��錾
	CScene_X * pScene_Two;		// �V�[��3D�N���X

	// �������̐���(����->��{�N���X,��->�h���N���X)
	pScene_Two = new CScene_X();

	// ����������
	pScene_Two->Init();

	// ���������I�u�W�F�N�g��Ԃ�
	return pScene_Two;
}

// ----------------------------------------
// �ʒu�ݒ菈��
// ----------------------------------------
void CScene_X::SetPos(D3DXVECTOR3 pos)
{
	m_model_info.pos = pos;
}

// ----------------------------------------
// ��]�ݒ菈��
// ----------------------------------------
void CScene_X::SetRot(D3DXVECTOR3 rot)
{
	m_model_info.rot = rot;
}

// ----------------------------------------
// �T�C�Y�ݒ菈��
// ----------------------------------------
void CScene_X::SetSize(D3DXVECTOR3 size)
{
	m_model_info.size = size;
	/*
	// �����蔻�萶��
	CCollision *pCollision;
	pCollision = CCollision::Create();
	pCollision->SetPos(&m_model_info.pos);
	pCollision->SetSize(D3DXVECTOR3(OBJECT_COLLISIONSIZE, OBJECT_COLLISIONSIZE, OBJECT_COLLISIONSIZE));
	pCollision->SetMove(NULL);
	pCollision->SetType(CCollision::TYPE_WAIT);
	*/
}

// ----------------------------------------
// �J���[�ݒ菈��
// ----------------------------------------
void CScene_X::SetColor(D3DXCOLOR col)
{
}

// ----------------------------------------
// �ʒu�擾����
// ----------------------------------------
D3DXVECTOR3 CScene_X::GetPos(void)
{
	return m_model_info.pos;
}

// ----------------------------------------
// ��]�擾����
// ----------------------------------------
D3DXVECTOR3 CScene_X::GetRot(void)
{
	return m_model_info.rot;
}

// ----------------------------------------
// �e�N�X�`���[�ݒ菈��
// ----------------------------------------
void CScene_X::BindTexture(LPDIRECT3DTEXTURE9 p_Tex)
{
	//for (int nCount = 0; nCount < 2; nCount++)
	//{
		//m_model_info.pTexture[nCount] = p_Tex[nCount];
	if (pTexture[m_nCount] == NULL)
	{
		pTexture[m_nCount] = p_Tex;
	}
	else if (pTexture[m_nCount] != NULL)
	{
		m_nCount++;
		pTexture[m_nCount] = p_Tex;
	}
	//}
}

// ----------------------------------------
// ���f���ݒ�
// ----------------------------------------
void CScene_X::BindModel(MODEL_INFO const &model_info)
{
	m_model_info = model_info;

	// �ϐ��錾
	LPDIRECT3DDEVICE9	pDevice = CManager::GetRenderer()->GetDevice();

	D3DXMATRIX			mtxRot, mtxTrans;		// �v�Z�p�}�g���b�N�X
	D3DXMATERIAL		*pMat;					// ���݂̃}�e���A���ۑ�
	// �}�e���A�����ɑ΂���|�C���^���擾
	pMat = (D3DXMATERIAL*)m_model_info.pBuffMat->GetBufferPointer();
	// �J�E���g�}�e���A��
	/*for (int nCntMat = 0; nCntMat < (int)m_model_info.nNumMat; nCntMat++, pMat++)
	{
		if (pMat->pTextureFilename != "")
		{
			D3DXCreateTextureFromFile(pDevice, pMat->pTextureFilename, &pTexture[nCntMat]);
		}
	}*/
}
