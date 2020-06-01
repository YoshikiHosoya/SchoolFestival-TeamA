// ----------------------------------------
//
// �������̐���[floor.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _FLOOR_H_
#define _FLOOR_H_	 // �t�@�C������������߂�

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


// ----------------------------------------
//
// �O���錾
//
// ----------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CFloor : public CScene
{
public:
	/* �֐� */
	CFloor();
	~CFloor();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static CFloor * Create(		// �쐬
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size,
		D3DXVECTOR3 rot,
		int nWidth,
		int nDepth
	);
	float GetHeight(D3DXVECTOR3 pos);								// �����擾

protected:

private:
	/* �֐� */
	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_pIndex;	// �C���f�b�N�X�o�b�t�@�̃|�C���^
	D3DXVECTOR3 m_OriginBlock;			// �����z�u
	D3DXMATRIX  m_mtxWorld;				// ���[���h�}�g���b�N�X
	D3DXVECTOR3 m_pos;					// �ʒu
	D3DXVECTOR3 m_size;					// �T�C�Y
	D3DXVECTOR3 m_rot;					// �p�x
	int	m_nNumberVertex;				// �����_��
	int m_nNumIndex;					// ���C���f�b�N�X
	int m_nNumPolygon;					// ���|���S��
	int m_nBlock_Depth;					// �c�u���b�N��
	int m_nBlock_Width;					// ���u���b�N��

};

#endif