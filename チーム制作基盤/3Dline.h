// ----------------------------------------
//
// 3D�������̐���[3Dline.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _3DLINE_H_
#define _3DLINE_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class C3DLine : public CScene
{
public:
	/* �����o�֐� */
	C3DLine(OBJ_TYPE type);
	~C3DLine();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void Draw(void);
	virtual void SetPos(						// �ʒu�ݒ�
		D3DXVECTOR3 &pos1,
		D3DXVECTOR3 &pos2
	);

	void SetPosColi(							// �f�o�b�N����p�ʒu�ݒ�
		D3DXVECTOR3 &pos1
	);

	void SetCol(								// �F�ݒ�
		D3DXCOLOR &col
	);

	/* �ÓI�����o�֐� */
	static C3DLine * Create(					// �쐬
		D3DXVECTOR3 &pos,
		D3DXVECTOR3 &rot,
		D3DXVECTOR3 &pos1,
		D3DXVECTOR3 &pos2,
		D3DXCOLOR	&col
	);
protected:

private:
	/* �����o�ϐ� */
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX					m_mtxWorld;		// ���[���h�}�g���b�N�X
	D3DXVECTOR3					m_pos;			// �ʒu
	D3DXVECTOR3					m_rot;			// ��]
	D3DXCOLOR					m_col;			// �F
};

#endif