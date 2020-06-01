// ------------------------------------------
//
// �Q�[���w�b�_�[���� [game.h]
// Author : Fujiwara Masato
//
// ------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ------------------------------------------
#include "main.h"
#include "pause.h"

// ------------------------------------------
//
// �}�N����`
//
// ------------------------------------------

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------
class CPause;
class CPlayer;
class CGauge;
class CTime;

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CGame
{
public:
	/* �񋓌^ */
	typedef enum
	{
		STATE_NORMAL,
		STATE_START,
		STATE_CLEAR,
		STATE_GAMEOVER,
		STATE_PAUSE,
		STATE_MAX
	} STATE;
	/* �֐� */
	CGame();
	~CGame();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	static STATE GetState(void);					// ��Ԃ̎擾
	static int GetStage(void);						// �X�e�[�W�擾
	static void SetState(STATE state);				// ��Ԑݒ�

protected:
private:
	static CPlayer	*m_pPlayer;
	static STATE m_state;	// ���
	static int m_nStage;	// �X�e�[�W
	CPause	*m_pPause;	// �|�[�Y�̏��
	int m_Shard;
};
#endif
