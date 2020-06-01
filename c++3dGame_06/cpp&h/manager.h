// ------------------------------------------
//
// �}�l�[�W���[�����̐���[manager.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _MANAGER_H_
#define _MANAGER_H_	 // �t�@�C������������߂�

// ------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ------------------------------------------
/* ��{ */
#include "main.h"
#include "Calculation.h"

/* �`�� */
#include "renderer.h"

/* ���̓f�o�C�X */
#include "keyboard.h"
#include "joypad.h"
#include "mouse.h"

/* �T�E���h */
#include "sound.h"

// ------------------------------------------
//
// �}�N���֐�
//
// ------------------------------------------
#define ONEPLAYER_STAGE (5)
#define DOUBLEPLAYER_STAGE (5)

#define ONEMIN			(60)		// 1��
#define HALF			(0.5f)		// ����
#define ONE				(1.0f)		// 1
#define ONEFRAME		(6)			// 1�t���[��

#define COLOR_RED		(D3DXCOLOR(1.0f,0.0f,0.0f,1.0f))	// �ԐF
#define COLOR_GREEN		(D3DXCOLOR(0.0f,1.0f,0.0f,1.0f))	// �ΐF
#define COLOR_BLUE		(D3DXCOLOR(0.0f,0.0f,1.0f,1.0f))	// �F
#define COLOR_PURPLE	(D3DXCOLOR(1.0f,0.0f,1.0f,1.0f))	// ���F
#define COLOR_YELLOW	(D3DXCOLOR(0.0f,1.0f,1.0f,1.0f))	// ���F
#define COLOR_WATER		(D3DXCOLOR(1.0f,1.0f,0.0f,1.0f))	// ���F
#define COLOR_BLACK		(D3DXCOLOR(1.0f,1.0f,1.0f,1.0f))	// ���F
#define COLOR_WHITE		(D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))	// ���F

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------
class CFade;		// ��ʑJ��
class CTitle;		// �^�C�g��
class CTutorial;	// �`���[�g���A��
class CGame;		// �Q�[��
//class CRanking;		// �����L���O

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CManager
{
public:
	/* �񋓌^ */
	// ���[�h
	typedef enum
	{
		MODE_GAME = 0,
		MODE_TITLE,
		//MODE_RANKING,
		MODE_MAX
	} MODE;
	// �v���C�ԍ�
	typedef enum
	{
		PLAYER_1 = 0,
		PLAYER_2,
		PLAYER_MAX
	} PLAYER;
	/* �֐� */
	CManager();
	~CManager();
	HRESULT  Init(HWND hWnd, BOOL bWindow, HINSTANCE hInstance);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetMode(MODE mode);				// ���[�h�ݒ�
	static CRenderer * GetRenderer(void);		// �����_�����O�̎擾
	static CKeyboard * GetKeyboard(void);		// �L�[�{�[�h�̎擾
	static CJoypad * GetJoy(void);				// �W���C�p�b�h�̎擾
	static CMouse * GetMouse(void);				// �}�E�X�̎擾
	static CSound * GetSound(void);				// �T�E���h�̎擾
	static CFade * GetFade(void);				// ��ʑJ�ڂ̎擾
	static CGame * GetGame(void);				// �Q�[���̎擾
	static CTutorial * GetTutorial(void);		// �`���[�g���A���擾
	static CTitle * GetTitle(void);				// �^�C�g���̎擾
	//static CRanking * GetRanking(void);			// �����L���O�̎擾
	static MODE GetMode(void);					// ���[�h�̎擾
protected:

private:
	// �Q�[���Ɍ������Ȃ�����
	static CRenderer * m_renderer;			// �����_�����O
	static CSound * m_sound;				// �T�E���h

	// ���̓f�o�C�X
	static CKeyboard * m_keyboard;			// �L�[�{�[�h
	static CJoypad * m_joypad;				// �W���C�p�b�h
	static CMouse * m_mouse;				// �}�E�X

	// ���
	static CFade * m_fade;					// ��ʑJ��
	static CTitle * m_title;				// �^�C�g��
	static CGame * m_game;					// �Q�[��
	static CTutorial * m_tutorial;			// �`���[�g���A��
	//static CRanking * m_ranking;			// �����L���O

	static MODE m_mode;						// ���[�h
	static bool	m_bWire;						// ���C���[���[�h
};

#endif // !_MANAGER_H_