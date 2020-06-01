//=============================================================================
//
// ���f����񏈗� [model_info.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _MODEL_INFO_H_
#define _MODEL_INFO_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �\����
//=============================================================================
// ���f�����
typedef struct
{
	LPD3DXMESH			pMesh;				// ���b�V�����ւ̃|�C���^
	LPD3DXBUFFER		pBuffMat;			// �}�e���A�����ւ̃|�C���^
	LPDIRECT3DTEXTURE9	pTexture;			// �e�N�X�`���ւ̃|�C���^
	DWORD				nNumMat;			// �}�e���A���̐�
	D3DXVECTOR3			vtxMinMaterials;	// ���f�����̈ʒu�̍ŏ��l
	D3DXVECTOR3			vtxMaxMaterials;	// ���f�����̈ʒu�̍ő�l
	D3DXVECTOR3			pos;				// �ʒu���
	D3DXVECTOR3			posDest;			// �ړI�ʒu
	D3DXVECTOR3			rot;				// ��]���
	D3DXVECTOR3			rotDest;			// �ړI��]
	D3DXVECTOR3			size;				// �T�C�Y
	D3DXVECTOR3			scal;				// �X�P�[��
	int					nParent;			// �e�ԍ�
	int					nNum;				// �e�N�X�`���̖���
} MODEL_INFO,*pMODEL_INFO;

// �I�t�Z�b�g�̏��
typedef struct
{
	D3DXVECTOR3			pos;		// �ʒu
	D3DXVECTOR3			rot;		// ��]
	int					nParent;	// �e�ԍ�
} MODEL_OFFSET;

//=============================================================================
// �N���X
//=============================================================================
class CModel_info
{
public:
	/* �֐� */
	CModel_info();
	~CModel_info();
	// �J��
	void Unload(void);
	// ���擾
	MODEL_INFO			&GetModel_info(void);	// ���f�����擾
	LPD3DXMESH			&GetMesh(void);			// ���b�V��
	LPD3DXBUFFER		&GetBuffmat(void);		// �}�e���A��
	LPDIRECT3DTEXTURE9	&GetTex(void);			// �e�N�X�`���[
	DWORD				&GetNumMat(void);		// �}�e���A����
	D3DXVECTOR3			&GetvtxMinMat(void);	// ���_���W�̍ŏ��l
	D3DXVECTOR3			&GetvtxMaxMat(void);	// ���_���W�̍ő�l
	D3DXVECTOR3			&GetPos(void);			// �ʒu
	D3DXVECTOR3			&GetRot(void);			// ��]
	int					&GetParent(void);		// �e
	// �ǂݍ���
	void Load(									// ���f�����
		LPDIRECT3DDEVICE9 pDevice,
		const char* charModel
	);
	static void ModelOffset(					// ���f���̃I�t�Z�b�g�ݒ�
		MODEL_OFFSET * pModel_offset,
		const char * file_name
	);
protected:
private:
	MODEL_INFO			m_model_info;			// ���f�����
};

#endif
