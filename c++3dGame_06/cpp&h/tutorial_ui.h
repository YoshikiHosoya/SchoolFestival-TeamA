// ----------------------------------------
//
// �`���[�g���A��UI�����̐���[tutorial_ui.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _TUTORIAL_UI_H_
#define _TUTORIAL_UI_H_	 // �t�@�C������������߂�

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
class CTutorial_ui : public CScene
{
public:
	/* �֐� */
	CTutorial_ui();
	~CTutorial_ui();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);		// �ǂݍ���
	static void UnLoad(void);		// UnLoad����
	static CTutorial_ui * Create(void);	// �쐬
protected:

private:
	/* �񋓌^ */
	typedef enum
	{
		/* �^�C�g���v���C���ɂ͏o�����Ȃ�UI */
		TUTORIAL_UI_MANUAL = 0,
		TUTORIAL_UI_CLICK_R,
		TUTORIAL_UI_CLICK_L,
		TUTORIAL_UI_START,
		TUTORIAL_UI_MAX
	} TUTORIAL_UI;

	typedef enum
	{
		/* �^�C�g���v���C���ɂ͏o�����Ȃ�UI */
		TUTORIAL_STATE_FIRST = 0,
		TUTORIAL_STATE_SECOND,
		TUTORIAL_STATE_MAX
	} TUTORIAL_STATE;
	/* �֐� */
	void Various(int nCnt);											// ��ޕʏ���
																	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex[TUTORIAL_UI_MAX];	// �e�N�X�`���[�ݒ�
	static D3DXVECTOR3 m_pos[TUTORIAL_UI_MAX];			// �ʒu���
	static D3DXVECTOR2 m_size[TUTORIAL_UI_MAX];			// �T�C�Y���

	CScene_TWO *m_aScene_Two[TUTORIAL_UI_MAX];			// �`���[�g���A���pui2D
	TUTORIAL_STATE m_TutorialState;
	int		m_nSelect;									// �I��ԍ�
	int		m_nCntCol;									// �J���[�J�E���g
	float	m_fAnim;									// �A�j���[�V����
	float	m_fMult;									// �{��
	float	m_fAdd;										// ���Z
};

#endif