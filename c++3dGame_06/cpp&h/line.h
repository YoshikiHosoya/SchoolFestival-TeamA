// ----------------------------------------
//
// �������̐���[line.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _LINE_H_
#define _LINE_H_	 // �t�@�C������������߂�

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
#define MAX_LINE (10)

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
class CLine : public CScene
{
public:
	/* �֐� */
	CLine();
	~CLine();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetPos(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);			// �ʒu�ݒ�
	static CLine * Create(D3DXVECTOR3 pos1,D3DXVECTOR3 pos2);	// �쐬
	static HRESULT Load(void);									// �ǂݍ���
	static void UnLoad(void);									// �ǂݍ��񂾏���j��
protected:

private:
	static LPDIRECT3DTEXTURE9 m_pTex;
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;	// ���_�o�b�t�@�ւ̃|�C���^
};

#endif