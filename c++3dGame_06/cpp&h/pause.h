// ----------------------------------------
//
// �|�[�Y�����̐���[pouse.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _PAUSE_H_
#define _PAUSE_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene_two.h"
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
class CPause : public CScene
{
public:
	/* �֐� */
	CPause();
	~CPause();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);			// �ǂݍ���
	static void UnLoad(void);			// UnLoad����
	static CPause * Create(void);	// �쐬

	static void SetPause(bool bPause);	// �|�[�Y�̏�Ԑݒ�
	static bool GetPause(void);			// �|�[�Y�̏�Ԏ擾

protected:

private:
	/* �ϐ� */
	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex;		// �e�N�X�`���[�ݒ�
	static D3DXVECTOR3 m_pos;				// �ʒu���
	static D3DXVECTOR2 m_size;				// �T�C�Y���
	static bool m_bPause;					// �|�[�Y��Ԃ��ǂ���
	CScene_TWO *m_aScene_Two;				// �|�[�Y�pui2D
};

#endif
