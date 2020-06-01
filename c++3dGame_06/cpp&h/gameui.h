// ----------------------------------------
//
// �Q�[��UI�����̐���[game_ui.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _GAME_UI_H_
#define _GAME_UI_H_	 // �t�@�C������������߂�

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
#define MAX_GAME_UI (GAME_UI_MAX)
#define MAX_GAME_UI_TEX (6)

#define GAME_UI_SIZE_X (80)
#define GAME_UI_SIZE_Y (80)

#define ACTIONBUTTON_SIZE_X (500)
#define ACTIONBUTTON_SIZE_Y (50)


#define ABILITYPOINT (10)
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
class CGame_ui : public CScene
{
public:
	/* �֐� */
	CGame_ui();
	~CGame_ui();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);		// �ǂݍ���
	static void UnLoad(void);		// UnLoad����
	static CGame_ui * Create(void);	// �쐬
	static void SetAP(int number);						// �A�r���e�B�\�|�C���g�̉��Z���Z
	static bool GetbUse();
protected:

private:
	/* �񋓌^ */
	typedef enum
	{
		/* �^�C�g���v���C���ɂ͏o�����Ȃ�UI */
		GAME_UI_KEY0 = 0,
		GAME_UI_KEY1,
		GAME_UI_KEY2,
		GAME_UI_LOCK0,
		GAME_UI_LOCK1,
		GAME_UI_LOCK2,
		GAME_UI_ACTIONBUTTON,
		GAME_UI_MISSION0,
		GAME_UI_MISSION1,
		GAME_UI_MAP,
		GAME_UI_MAX
	} GAME_UI;

	/* �֐� */
	void ConditionalDraw(int nCnt);						// �`�����
	static void SetDrawFlag(int nCnt);					// �`�攻��
	void Various();										// ��ޕʏ���

														/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex[MAX_GAME_UI_TEX];				// �e�N�X�`���[�ݒ�
	static D3DXVECTOR3 m_pos[MAX_GAME_UI];				// �ʒu���
	static D3DXVECTOR2 m_size[MAX_GAME_UI];				// �T�C�Y���
	static bool m_bUse[MAX_GAME_UI];					// �T�C�Y���

	CScene_TWO *m_aScene_Two[MAX_GAME_UI];				// �`���[�g���A���pui2D
	int		m_nSelect;									// �I��ԍ�
	int		m_nCntCol;									// �J���[�J�E���g
	float	m_fAnim;									// �A�j���[�V����
	float	m_fMult;									// �{��
	float	m_fAdd;										// ���Z

	static int		m_nAP;								// �A�r���e�B�\�|�C���g
};

#endif