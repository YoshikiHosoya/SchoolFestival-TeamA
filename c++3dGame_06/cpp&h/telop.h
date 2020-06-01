// ----------------------------------------
//
// �e���b�v�����̐���[telop.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TELOP_H_
#define _TELOP_H_	 // �t�@�C������������߂�

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
class CTelop : public CScene_TWO
{
public:

	typedef enum
	{
		STATE_EMERGENCE = 0,				// �o��
		STATE_DISAPPEARANCE					// ����
	} STATE;

	/* �֐� */
	CTelop();
	~CTelop();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);				// �ǂݍ���
	static void UnLoad(void);				// UnLoad����
	static CTelop * Create(void);			// �쐬
	void Transparency(STATE state);			// ������
	bool GetTelopFlag(void);				// �t���O�̎擾

protected:

private:

	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTexture;	// �e�N�X�`���[�ݒ�
	static D3DXVECTOR3 m_pos;				// ���W
	static D3DXVECTOR2 m_size;				// �傫��
	static D3DXCOLOR m_Col;					// �J���[

	int		m_nCntCol;						// �J���[�J�E���g
	bool	m_bTelopFlag;					// ���S�ɏo���������̃t���O
	bool	m_bCommentFlag;					// �R�����g���������ꂽ����true
	int		m_nCommentCount;				// ���̃R�����g�Ɉڍs�ł���܂ł̃J�E���g
};

#endif