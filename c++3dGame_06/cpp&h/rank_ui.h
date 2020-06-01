// ----------------------------------------
//
// �����N�pRANK_UI�����̐���[rank_ui.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _RANK_UI_H_
#define _RANK_UI_H_	 // �t�@�C������������߂�

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
#define MAX_RANK_UI (7)

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
class CRank_ui : public CScene
{
public:
	/* �֐� */
	CRank_ui();
	~CRank_ui();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);		// �ǂݍ���
	static void UnLoad(void);		// UnLoad����
	static CRank_ui * Create(void);	// �쐬
protected:

private:
	/* �񋓌^ */

	/* �֐� */

	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex[MAX_RANK_UI];	// �e�N�X�`���[�ݒ�
	static D3DXVECTOR3 m_pos[MAX_RANK_UI];			// �ʒu���
	static D3DXVECTOR2 m_size[MAX_RANK_UI];			// �T�C�Y���
	static int m_nSelect;							// �I��
	int	m_nCntCol;									// �J���[�J�E���g
	CScene_TWO *m_aScene_Two[MAX_RANK_UI];			// �����N�pui2D
};

#endif