//------------------------------------------------------------------------------
//
//�Q�[������  [game.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAME_H_
#define _GAME_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "basemode.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//�O���錾
class CMap;
class CPause;
class CScore;
class CTimer;
class CPlayer;
class CMultiNumber;

class CGame : public CBaseMode
{
public:
	//�Q�[���̏�ԑJ��
	enum STATE
	{
		STATE_NONE = -1,				//�n�܂��ĂȂ�
		STATE_READY,					//�J�n�O�̏��
		STATE_NORMAL,					//�ʏ��ԁ@�M��
		STATE_PAUSE,					//�|�[�Y���
		STATE_GAMEOVER,					//�Q�[���I�[�o�[
		STATE_GAMECLEAR,				//�Q�[���N���A

		STATE_DEBUG,
		STATE_MAX
	};

	CGame();
	~CGame();
	HRESULT Init(HWND hWnd);								//������
	void Uninit();											//�I��
	void Update();											//�X�V
	void Draw();											//�`��
	void ShowDebugInfo();									//�f�o�b�O���\�L

	void SetGamestate(STATE gamestate);						//�Q�[���̏�Ԑݒ�

	STATE GetGamestate() { return m_gamestate; };			//�Q�[���̏�Ԏ擾
	CMap *GetMap(); 										//�}�b�v���擾
	CScore *GetScore(); 									//�X�R�A�̃|�C���^
	CPlayer *GetPlayer(); 									//�v���C���[�̃|�C���^�擾z

private:
	std::unique_ptr<CMap> m_pMap;						//�}�b�v�̃|�C���^
	std::unique_ptr<CScore> m_pScore;					//�X�R�A�̃|�C���^
	std::unique_ptr<CTimer> m_pTimer;					//�^�C�}�[�̃|�C���^
	std::shared_ptr<CPause> m_pPause;					//�|�[�Y�ւ̃|�C���^
	std::shared_ptr<CPlayer> m_pPlayer;					//�v���C���[�̃|�C���^

	STATE m_gamestate;					//�Q�[���X�e�[�g
	int m_nCntState;					//�X�e�[�g�̃J�E���^
	int m_nReadyCount;					//ready�̎��̃J�E���g

	int m_nEnemyPopTime;				//�G�o���J�E���g
	int m_nEnemuPopWave;				//�G�o���̃E�F�[�u
	void EnemyRespawn();				//�G�o��
};

#endif