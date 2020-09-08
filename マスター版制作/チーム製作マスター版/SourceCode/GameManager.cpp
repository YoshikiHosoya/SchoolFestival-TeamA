//------------------------------------------------------------------------------
//
//�Q�[���̐i�s�Ǘ�  [GameManager.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "GameManager.h"
#include "scene2D.h"
#include "map.h"
#include "fade.h"
#include "Player.h"
#include "Playerui.h"
#include "game.h"
#include "camera.h"
#include "map.h"
#include "sound.h"
#include "pause.h"
#include "XInputPad.h"

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define GO_SIGN_POS (D3DXVECTOR3(1180.0f,200.0f,0.0f))
#define GO_SIGN_SIZE (D3DXVECTOR3(80.0f,60.0f,0.0f))
#define GAMEOVER_SIZE (D3DXVECTOR3(450.0f, 150.0f, 0.0f))

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CGameManager::CGameManager()
{
	m_nCnt = 0;
	m_nTimeCnt = 0;
	m_nNowWave = 0;
	m_nWaveEnemyCnt = 0;
	m_nWavePrisonerCnt = 0;
	m_nWaveEnemyNum = 0;
	m_nWavePrisonerNum = 0;
	m_pPause = nullptr;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CGameManager::~CGameManager()
{

}

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
void CGameManager::Update()
{
	// ���ꂼ��̃|�C���^�擾
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1);
	CGame *pGame = (CGame*)CManager::GetBaseMode();

	m_nCnt++;

	//nullcheck
	if (pPlayer)
	{
		//����̍��W�𒴂�����
		if(pPlayer->GetPosition().x >= CManager::GetGame()->GetMap()->GetTransitionPos().x)
		{
			//�}�b�v�J��
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CManager::GetGame()->GetMap()->GetTransitionMapID());
		}
	}

	//�|�[�Y
	PauseSet();

	//state�ɉ���������
	switch (m_state)
	{
		//�ʏ킩�E�F�[�u��Ԃ̂Ƃ�
	case CGameManager::GAMESTATE::NORMAL:
		//GoSign�X�V
		UpdateGoSign();

		//�܂��E�F�[�u���c���Ă��鎞
		if (m_nNowWave <= CMap::WAVE::WAVE_MAX)
		{
			//���̃E�F�[�u�̏��擾
			CMap::WAVE_INFO *pWaveInfo = pGame->GetMap()->GetWaveInfo(m_nNowWave);

			//nullcheck
			if (pWaveInfo)
			{
				//���݂̃}�b�v�ԍ��ƃC�x���g����������}�b�v�ԍ��������Ă��邩�ǂ���
				if (pWaveInfo->EventBeginMapNum == CManager::GetGame()->GetMap()->GetMapNum())
				{
					//����̍��W�𒴂�����
					if (pPlayer->GetPosition().x >= pWaveInfo->EventPos.x && pPlayer->GetCharacterState() != CCharacter::CHARACTER_STATE::CHARACTER_STATE_DEATH)
					{
						//�E�F�[�u�J�n
						StartWave();
					}
				}
			}
		}

	case CGameManager::GAMESTATE::WAVE:

		//�^�C�}�[�X�V
		UpdateTimer();

		//�E�F�[�u�̎�
		if (m_state == CGameManager::GAMESTATE::WAVE)
		{
			//�E�F�[�u�̍X�V
			UpdateWave();

			//GoSign��\��
			m_pScene2D_GoSign->SetDisp(false);
			m_nCnt = 0;

		}
		break;

	case CGameManager::GAMESTATE::RESULT:

		break;

	case CGameManager::GAMESTATE::GAMEOVER:
		UpdateGameover();

		break;

	case CGameManager::GAMESTATE::PAUSE:
		// �|�[�Y
		if (m_pPause)
		{
			m_pPause->Update();
		}
		break;

	default:
		break;

	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CGameManager::Draw()
{
}

//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CGameManager::ShowDebugInfo()
{
#ifdef _DEBUG
	CDebugProc::Print_Left("------ GameManager ----------\n");

	CDebugProc::Print_Left("NowWaveNum >> %d\n", m_nNowWave);
	CDebugProc::Print_Left("GameState >> %d\n", m_state);
	CDebugProc::Print_Left("m_nCnt >> %d\n", m_nCnt);
	CDebugProc::Print_Left("m_nWavePrisonerCnt >> %d\n", m_nWavePrisonerCnt);
	CDebugProc::Print_Left("m_nWaveEnemyCnt >> %d\n", m_nWaveEnemyCnt);

	CDebugProc::Print_Left("m_nWaveEnemyNum >> %d\n", m_nWaveEnemyNum);
	CDebugProc::Print_Left("m_nWavePrisonerNum >> %d\n", m_nWavePrisonerNum);
#endif
}

//------------------------------------------------------------------------------
//��������
//------------------------------------------------------------------------------
std::unique_ptr<CGameManager> CGameManager::Create()
{
	//�������m��
	std::unique_ptr<CGameManager> pGameManager(new CGameManager);

	//nullcheck
	if (pGameManager)
	{
		//Go�T�C������
		pGameManager->m_pScene2D_GoSign = CScene2D::CreateSceneManagement(GO_SIGN_POS, GO_SIGN_SIZE,CScene::OBJTYPE_UI);
		pGameManager->m_pScene2D_GoSign->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_GAME_GO));
		pGameManager->m_pScene2D_GoSign->SetColor(WhiteColor);
		return pGameManager;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�X�e�[�g�؂�ւ�
//------------------------------------------------------------------------------
void CGameManager::SetGameState(GAMESTATE state)
{
	//�X�e�[�g���؂�ւ������
	if (m_state != state)
	{
		// �O��̏�Ԃ�ۑ�
		m_stateOld = m_state;

		m_state = state;
		m_nCnt = 0;

		switch (m_state)
		{
		case CGameManager::GAMESTATE::GAMEOVER:
			//�Q�[���I�[�o�[�\������Ă��Ȃ���
			if (!m_pScene2D_GameOver)
			{
				//�Q�[���I�[�o�[UI����
				m_pScene2D_GameOver = CScene2D::CreateSceneManagement(SCREEN_CENTER_POS, GAMEOVER_SIZE, CScene::OBJTYPE_UI);
				m_pScene2D_GameOver->BindTexture(CTexture::GetTexture(CTexture::TEX_UI_GAME_GAMEOVER));

				m_nCnt = 0;
			}
			break;
		case CGameManager::GAMESTATE::PAUSE:
			if (!m_pPause)
			{
				// �|�[�Y�̐���
				m_pPause = CPause::Create();
			}
			break;
		}
		if (m_state != GAMESTATE::PAUSE)
		{
			// �|�[�Y�̔j��
			if (m_pPause)
			{
				delete m_pPause;
				m_pPause = nullptr;
			}
		}
	}

	//�Q�[���̃X�e�[�g�؂�ւ�������̏���
	CManager::GetGame()->StateChangeReaction();
}
//------------------------------------------------------------------------------
//�C�x���g�N���A
//------------------------------------------------------------------------------
void CGameManager::EventClear()
{
	EndWave();
}

//------------------------------------------------------------------------------
//�}�b�v�J�ڎ��ɃE�F�[�u�Đݒ�
//------------------------------------------------------------------------------
void CGameManager::MapTransitionWaveSet(int nNextID)
{
	EndWave();

	//���̃}�b�v�ԍ��ɍ��킹�Č��݂̃E�F�[�u�ԍ������킹��
	switch (nNextID)
	{

	case CMap::MAP_1_1:
		m_nNowWave = CMap::WAVE::WAVE_1_1_1;

			break;
	case CMap::MAP_1_2:
		m_nNowWave = CMap::WAVE::WAVE_1_2_1;

		break;
	case CMap::MAP_1_3:
		m_nNowWave = CMap::WAVE::WAVE_1_3_1;

		break;
	case CMap::MAP_1_BOSS:
		m_nNowWave = CMap::WAVE::WAVE_1_BOSS;

		//�{�X�}�b�v�ɑJ�ڂ����疳�����ŃE�F�[�u�J�n
		StartWave();

		break;
	case CMap::MAP_2_1:
		m_nNowWave = CMap::WAVE::WAVE_2_1_1;

		break;
	case CMap::MAP_2_2:
		m_nNowWave = CMap::WAVE::WAVE_2_2_1;

		break;
	case CMap::MAP_2_3:
		m_nNowWave = CMap::WAVE::WAVE_2_3_1;

		break;
	case CMap::MAP_2_BOSS:
		m_nNowWave = CMap::WAVE::WAVE_2_BOSS;

		//�{�X�}�b�v�ɑJ�ڂ����疳�����ŃE�F�[�u�J�n
		StartWave();

	default:
		break;
	}
}

//------------------------------------------------------------------------------
//�E�F�[�u�J�n
//------------------------------------------------------------------------------
void CGameManager::StartWave()
{
	m_state = CGameManager::GAMESTATE::WAVE;
	CManager::GetRenderer()->GetCamera()->SetCameraStopMove(true);
}

//------------------------------------------------------------------------------
//�E�F�[�u�̏I��
//------------------------------------------------------------------------------
void CGameManager::EndWave()
{
	m_state = CGameManager::GAMESTATE::NORMAL;
	m_nCnt = 0;
	CManager::GetRenderer()->GetCamera()->SetCameraStopMove(false);
	m_nWaveEnemyCnt = 0;
	m_nWaveEnemyNum = 0;
	m_nWavePrisonerCnt = 0;
	m_nWavePrisonerNum = 0;
	m_nNowWave++;
}

//------------------------------------------------------------------------------
//�E�F�[�u�̍X�V
//------------------------------------------------------------------------------
void CGameManager::UpdateWave()
{
	if (m_nNowWave >= CMap::WAVE::WAVE_MAX)
	{
		EndWave();
		return;
	}

	//�E�F�[�u�̃|�C���^
	CMap::WAVE_INFO *pWaveInfo = CManager::GetGame()->GetMap()->GetWaveInfo(m_nNowWave);


	//�܂��o�ĂȂ��̂�����Ƃ�
	//�G
	if (m_nWaveEnemyNum < (int)pWaveInfo->EnemyWaveInfo.size())
	{
		m_nWaveEnemyCnt++;
		//�t���[�������ꏏ�ɂȂ�����
		if (pWaveInfo->EnemyWaveInfo[m_nWaveEnemyNum]->nFrame <= m_nWaveEnemyCnt)
		{
			//�G����
			CManager::GetGame()->GetMap()->WaveCreate(CMap::ARRANGEMENT_MODEL_ENEMY, pWaveInfo->EventPos, pWaveInfo->EnemyWaveInfo[m_nWaveEnemyNum]);
			m_nWaveEnemyNum++;
			m_nWaveEnemyCnt = 0;
		}
	}

	//�܂��o�ĂȂ��̂�����Ƃ�
	//�ߗ�
	if (m_nWavePrisonerNum < (int)pWaveInfo->PrisonerWaveInfo.size())
	{
		m_nWavePrisonerCnt++;
		//�t���[�������ꏏ�ɂȂ�����
		if (pWaveInfo->PrisonerWaveInfo[m_nWavePrisonerNum]->nFrame <= m_nWavePrisonerCnt)
		{
			//�G����
			CManager::GetGame()->GetMap()->WaveCreate(CMap::ARRANGEMENT_MODEL_PRISONER, pWaveInfo->EventPos, pWaveInfo->PrisonerWaveInfo[m_nWavePrisonerNum]);
			m_nWavePrisonerNum++;
			m_nWavePrisonerCnt = 0;
		}
	}
}

//------------------------------------------------------------------------------
//GoSign
//------------------------------------------------------------------------------
void CGameManager::UpdateGoSign()
{
	//nullcehck
	if (m_pScene2D_GoSign)
	{
		if (m_nCnt <= 300)
		{
			if (m_nCnt % 40 == 0)
			{
				//�_��
				m_pScene2D_GoSign->SetDisp(m_pScene2D_GoSign->GetDisp() ^ 1);
				if (m_pScene2D_GoSign->GetDisp())
				{
					CManager::GetSound()->Play(CSound::LABEL_SE_GO_SIGN);
				}
			}
		}
		else if (m_nCnt >= 600)
		{
			//�J�E���g0�ɂ���
			m_nCnt = 0;
		}
		else
		{
			//��\��
			m_pScene2D_GoSign->SetDisp(false);
		}
	}
}
//------------------------------------------------------------------------------
//�^�C�}�[�X�V
//------------------------------------------------------------------------------
void CGameManager::UpdateTimer()
{
	// �J�E���g���Z
	m_nTimeCnt++;

	// 5�b�o�߂�����
	if (m_nTimeCnt >= 300)
	{
		if (CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1)->GetPlayerUI())
		{
			// �^�C�}�[�̒l����������
			CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1)->GetPlayerUI()->DecrementTime();

			// �^�C����0�ȉ��ɂȂ�����
			if (CManager::GetBaseMode()->GetPlayer(TAG::PLAYER_1)->GetPlayerUI()->GetTime() <= 0)
			{
				//�Q�[���I�[�o�[
				SetGameState(CGameManager::GAMESTATE::GAMEOVER);
			}
		}

		// �^�C�}�[�J�E���g�����Z�b�g����
		m_nTimeCnt = 0;
	}
}
//------------------------------------------------------------------------------
//�Q�[���I�[�o�[�̍X�V
//------------------------------------------------------------------------------
void CGameManager::UpdateGameover()
{
	m_nCnt++;

	//�J�E���g��������x�ɂȂ�����
	if (m_nCnt >= 300)
	{
		//�^�C�g���ɑJ��
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE::MODE_TITLE);
		SetGameState(CGameManager::GAMESTATE::NONE);
	}
}

//------------------------------------------------------------------------------
//�|�[�Y
//------------------------------------------------------------------------------
void CGameManager::PauseSet()
{
	// �ϐ�
	CKeyboard	*pKeyboard = CManager::GetInputKeyboard();
	CXInputPad	*pXinputPad[MAX_CONTROLLER] = {};

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		// �Q�[���p�b�h�̎擾
		pXinputPad[nCnt] = CManager::GetPad((TAG)nCnt);

		// �|�[�Y�{�^�����������Ƃ�
		if (pKeyboard->GetKeyboardTrigger(DIK_L) || pXinputPad[nCnt]->GetTrigger(CXInputPad::JOYPADKEY_START, 1))
		{
			if (m_state != GAMESTATE::PAUSE)
			{
				SetGameState(GAMESTATE::PAUSE);
				// �|�[�Y�Ŏ~�߂�ݒ�
				CScene::StopUpdate();
			}
		}
	}
}