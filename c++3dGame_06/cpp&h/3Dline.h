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
#define MAX_3DLINE (10)

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
	/* �֐� */
	C3DLine();
	~C3DLine();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(			// �ʒu�ݒ�
		D3DXVECTOR3 &pos1,
		D3DXVECTOR3 &pos2
	);

	void SetCol(			// �F�ݒ�
		D3DXCOLOR &col
	);

	static C3DLine * Create(	// �쐬
		D3DXVECTOR3 &pos,
		D3DXVECTOR3 &rot,
		D3DXVECTOR3 &pos1,
		D3DXVECTOR3 &pos2,
		D3DXCOLOR	&col
	);
	static HRESULT Load(void);									// �ǂݍ���
	static void UnLoad(void);									// �ǂݍ��񂾏���j��
protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX  m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_rot;					// ��]
	D3DXCOLOR	m_col;
};

#endif