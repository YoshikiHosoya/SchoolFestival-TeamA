// ------------------------------------------
//
// ���f������ [model.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _MODEL_H_
#define _MODEL_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
// �C���N���[�h�t�@�C��
// ------------------------------------------
#include "manager.h"
#include "model_info.h"
#include "motion.h"

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CModel
{
public:
	/* �֐� */
	CModel();
	~CModel();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(
		D3DXMATRIX & mtx
	);
	// �쐬
	static CModel * Create(void);
	// �e���̐ݒ�
	void SetParent(CModel * pModel);
	// ���f���̏��n������
	void BindTexture(LPDIRECT3DTEXTURE9 p_Tex);		// �e�N�X�`���[
	void BindModel(								
		MODEL_INFO &model_info,	// ���f���̏��
		MODEL_OFFSET &offset	// ���f���̃I�t�Z�b�g
	);
	// �ʒu���ݒ�
	void SetPos(D3DXVECTOR3 &pos);
	// ���[�V�����ݒ�
	void SetMotion(KEY &key,int nMaxFrame);
	// ���f�����̎擾
	MODEL_INFO *GetModelInfo(void);
	// ���f���̏��̐ݒ�
	void SetModelInfo(CONST MODEL_INFO &ModelInfo);
protected:
private:
	MODEL_INFO	m_model_info;			// ���f�����
	D3DXMATRIX	m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXMATRIX	m_Falts;
	D3DMATERIAL9		m_matDef;						// �}�e���A���f�[�^�̃|�C���^

	D3DXVECTOR3	m_size;					// �T�C�Y
	CModel		*m_Parent;				// �e�p�[�c
	int			m_nFrame;				// �t���[��

	LPDIRECT3DTEXTURE9	pTexture[30];			// �e�N�X�`���ւ̃|�C���^
};
#endif