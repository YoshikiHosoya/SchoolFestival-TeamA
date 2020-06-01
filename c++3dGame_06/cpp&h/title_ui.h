// ----------------------------------------
//
// �^�C�g��UI�����̐���[title_ui.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TITLE_UI_H_
#define _TITLE_UI_H_	 // �t�@�C������������߂�

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
class CMark;
class CSelectMark;

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CTitle_ui : public CScene
{
public:
	/* �� */
	typedef enum
	{
		TITLESELECT_NEWGAME = 0,	//1�߂�I��
	} TITLESELECT;

	/* �֐� */
	CTitle_ui();
	~CTitle_ui();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);			// �ǂݍ���
	static void UnLoad(void);			// UnLoad����
	static CTitle_ui * Create(void);	// �쐬
	static bool GetFlag(void);			// �t���O�̏��Ńt���O�̎擾
	void SetTitleModeDown(void);			// �^�C�g�����[�h��ݒ�
	void SetTitleModeUp(void);			// �^�C�g�����[�h��ݒ�
	void TitleMode(void);				// �I�����ꂽ���[�h�̏���
	TITLESELECT GetSelect(void);

protected:

private:
	/* �񋓌^ */
	typedef enum
	{
		TITLE_UI_NAME = 0,		// �^�C�g�����S
		TITLE_UI_NEWGAME,		// newgame���S
		TITLE_UI_MAX
	} TITLE_UI;

	/* �֐� */
	void Various(int nCnt);								// ��ޕʏ���
	void Transparency(int nCnt);						// ������

	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex[TITLE_UI_MAX];		// �e�N�X�`���[�ݒ�
	static D3DXVECTOR3 m_pos[TITLE_UI_MAX];				// �ʒu���
	static D3DXVECTOR2 m_size[TITLE_UI_MAX];			// �T�C�Y���
	static TITLE_UI m_type[TITLE_UI_MAX];				// ui�̎��
	TITLESELECT m_Select;
	float	m_fMult;									// �{��
	float	m_fAdd;										// ���Z
	D3DXCOLOR m_Col;									// �J���[
	static bool	m_bUse;									// �^�C�g��UI�����݂��Ă��邩�ǂ���
	bool m_bCol_a;										//
	CScene_TWO *m_aScene_Two[TITLE_UI_MAX];				// �|�[�Y�pui2D
	static CSelectMark *m_pSelectMark;					//�ڈ�
};

#endif