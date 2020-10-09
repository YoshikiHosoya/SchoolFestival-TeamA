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
	virtual HRESULT Init(HWND hWnd) = 0;								//������
	virtual void Uninit() = 0;											//�I��
	virtual void Update() = 0;											//�X�V
	virtual void Draw() = 0;											//�`��
	virtual void ShowDebugInfo() = 0;									//�f�o�b�O���\�L

	virtual void SetGamestate(STATE gamestate);									//�Q�[���̏�Ԑݒ�

	STATE GetGamestate() { return m_gamestate; };						//�Q�[���̏�Ԏ擾
	CPlayer *GetPlayer(); 												//�v���C���[�̃|�C���^�擾
	static int GetScore() { return m_nScore; };							//�X�R�A�擾
	static void SetScore(int nScore) { m_nScore = nScore; };
protected:
	void SetPlayerPtr(std::shared_ptr<CPlayer> pPlayer) { m_pPlayer = pPlayer; };
private:
	std::shared_ptr<CPlayer> m_pPlayer;					//�v���C���[�̃|�C���^

	STATE m_gamestate;									//�Q�[���X�e�[�g
	int m_nCntState;									//�X�e�[�g�̃J�E���^
	static int m_nScore;
};

#endif