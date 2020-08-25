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

class CGameManager
{
public:

	enum class GAMESTATE
	{
		NORMAL = 0,
		WAVE,
		BOSSBUTTLE,
		RESULT,
	};

	void Update();
	void Draw();

	CGameManager();
	~CGameManager();
	void ShowDebugInfo();						//�f�o�b�O���\�L
	static std::unique_ptr<CGameManager> Create();

	GAMESTATE GetGameState() { return m_state; };
	void SetGameState(GAMESTATE state) { m_state = state; };
	void EventClear();

private:
	int			m_nCnt;							//�J�E���g
	int			m_nWaveEnemyCnt;				//�G�̃t���[���J�E���g
	int			m_nWavePrisonerCnt;				//�ߗ��̃t���[���J�E���g
	int			m_nWaveEnemyNum;				//�E�F�[�u�̓G�̃i���o�[
	int			m_nWavePrisonerNum;				//�E�F�[�u�̕ߗ��̃i���o�[

	int			m_nNowWave;				//�E�F�[�u
	CScene2D	*m_pScene2D_GoSign;		//2D�|���S���@Go�T�C��
	GAMESTATE	m_state;				//�Q�[���̏��
	int			m_nTimeCnt;				//���Ԃ̃J�E���g

	void StartWave();
	void UpdateWave();
	void EndWave();
	void UpdateGoSign();
	void UpdateTimer();
};

#endif