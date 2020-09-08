//------------------------------------------------------------------------------
//
//�Q�[���̐i�s�Ǘ�  [GameManager.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CScene2D;
class CPause;

class CGameManager
{
public:

	enum class GAMESTATE
	{
		NONE = 0,
		NORMAL,
		WAVE,
		RESULT,
		GAMEOVER,
		PAUSE,
	};

	void Update();
	void Draw();

	CGameManager();
	~CGameManager();
	void ShowDebugInfo();						//�f�o�b�O���\�L
	static std::unique_ptr<CGameManager> Create();

	GAMESTATE GetGameState() { return m_state; };				//�X�e�[�g�擾
	GAMESTATE GetGameStateOld() { return m_stateOld; };			//�O��̃X�e�[�g�擾
	void SetGameState(GAMESTATE state);	//�X�e�[�g�ݒ�
	void EventClear();											//�C�x���g�N���A
	void MapTransitionWaveSet(int nNextID);						//�}�b�v�J�ڎ��ɃE�F�[�u�ݒ�

private:
	int			m_nCnt;							//�J�E���g
	int			m_nWaveEnemyCnt;				//�G�̃t���[���J�E���g
	int			m_nWavePrisonerCnt;				//�ߗ��̃t���[���J�E���g
	int			m_nWaveEnemyNum;				//�E�F�[�u�̓G�̃i���o�[
	int			m_nWavePrisonerNum;				//�E�F�[�u�̕ߗ��̃i���o�[

	int			m_nNowWave;				//�E�F�[�u
	CScene2D	*m_pScene2D_GoSign;		//2D�|���S���@Go�T�C��
	CScene2D	*m_pScene2D_GameOver;	//2D�|���S���@�Q�[���I�[�o�[
	CPause		*m_pPause;				//�|�[�Y

	GAMESTATE	m_state;				//�Q�[���̏��
	GAMESTATE	m_stateOld;				//�O��̃Q�[���̏��

	int			m_nTimeCnt;				//���Ԃ̃J�E���g

	void StartWave();
	void UpdateWave();
	void EndWave();
	void UpdateGoSign();
	void UpdateTimer();
	void UpdateGameover();
	void PauseSet();					// �|�[�Y
};

#endif