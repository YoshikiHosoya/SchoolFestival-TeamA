// ----------------------------------------
//
// �S�[�������̐���[goal.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _GOAL_H_
#define _GOAL_H_	 // �t�@�C������������߂�

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
class CGoal : public CScene
{
public:
	/* �֐� */
	CGoal();
	~CGoal();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);
	static void UnLoad(void);
	static CGoal * Create(		// �쐬
		D3DXVECTOR3 pos
	);
protected:

private:
	/* �֐� */
	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex;
	D3DXVECTOR3 m_pos;					// �ʒu
};

#endif