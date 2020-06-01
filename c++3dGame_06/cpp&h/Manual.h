// ----------------------------------------
//
// �}�j���A�������̐���[manual.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _MANUAL_H_
#define _MANUAL_H_	 // �t�@�C������������߂�

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
class CManual : public CScene
{
public:
	/* �֐� */
	CManual();
	~CManual();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static HRESULT Load(void);		// �ǂݍ���
	static void UnLoad(void);		// UnLoad����
	static CManual * Create(void);	// �쐬
protected:

private:
	/* �񋓌^ */
	typedef enum
	{
		MANUAL_STATE_PAUSE = 0,	// �ʏ�̃|�[�Y���
		MANUAL_STATE_MANUAL,	// �V�ѕ���\������
	} MANUAL_STATE;

	typedef enum
	{
		MANUAL_SELECT_PAGE_CONTROLLER = 0,	// �������
		MANUAL_SELECT_PAGE_ITEM,			// �A�C�e������
		MANUAL_SELECT_PAGE_ABILITY,			// �v���C���[�̔\�͐���
	} MANUAL_SELECT;

	typedef enum
	{
		MANUAL_TYPE_BG = 0,		// pause���̔w�i
		MANUAL_TYPE_PAUSEUI,	// pause�̕���
		MANUAL_TYPE_PAUSE,		// pause�̕��� pause��ʂփ��[�h�ύX
		MANUAL_TYPE_MANUAL,		// �V�ѕ� ���� �V�ѕ��փ��[�h�ύX
		MANUAL_TYPE_RESUME,		// ������ �̕��� �|�[�Y������
		MANUAL_TYPE_GOTITLE,	// �^�C�g���� �̕��� �^�C�g���։�ʑJ��
		MANUAL_TYPE_PICTURE,	// �V�ѕ����������摜
		MANUAL_TYPE_CROSSBUTTON,// �\���{�^��
		MANUAL_TYPE_ABUTTON,	// A�{�^�� ����{�^��
		MANUAL_TYPE_MAX,
	} MANUAL_TYPE;

	/* �֐� */
	void Various(int nCnt);											// ��ޕʏ���
																	/* �ϐ� */
	static LPDIRECT3DTEXTURE9 m_pTex[MANUAL_TYPE_MAX];	// �e�N�X�`���[�ݒ�
	static D3DXVECTOR3 m_pos[MANUAL_TYPE_MAX];			// �ʒu���
	static D3DXVECTOR2 m_size[MANUAL_TYPE_MAX];			// �T�C�Y���

	CScene_TWO *m_aScene_Two[MANUAL_TYPE_MAX];			// �`���[�g���A���pui2D
	MANUAL_STATE m_ManualState;
	MANUAL_SELECT m_ManualSelect;
	int		m_nSelect;									// �I��ԍ�
	int		m_nPauseCount;								// �I��ԍ�
	int		m_nCntCol;									// �J���[�J�E���g
	float	m_fAnim;									// �A�j���[�V����
	float	m_fMult;									// �{��
	float	m_fAdd;										// ���Z
};

#endif