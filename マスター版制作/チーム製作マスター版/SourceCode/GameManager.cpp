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
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
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
	CPlayer *pPlayer = CManager::GetBaseMode()->GetPlayer();
	CGame *pGame = (CGame*)CManager::GetBaseMode();

	m_nCnt = 0;

	//nullcheck
	if (pPlayer)
	{

		//����̍��W�𒴂�����
		if(pPlayer->GetPosition().x >= CManager::GetGame()->GetMap()->GetTransitionPos().x)
		{
			//�}�b�v�J��
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CManager::GetGame()->GetMap()->GetTransitionMapID());
		}

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
					if (pPlayer->GetPosition().x >= pWaveInfo->EventPos.x)
					{
						//�E�F�[�u�J�n
						StartWave();
					}
				}
			}
		}
	}

	//state�ɉ���������
	switch (m_state)
	{
	case CGameManager::GAMESTATE::NORMAL:
		break;
	case CGameManager::GAMESTATE::WAVE:
		UpdateWave();
		break;
	default:
		break;

	}

	//GoSign�X�V
	UpdateGoSign();

	//�^�C�}�[�X�V
	UpdateTimer();
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
	CDebugProc::Print("------ GameManager ----------\n");

	CDebugProc::Print("NowWaveNum >> %d\n", m_nNowWave);
	CDebugProc::Print("GameState >> %d\n", m_state);
	CDebugProc::Print("m_nWaveEnemyNum >> %d\n", m_nWaveEnemyNum);
	CDebugProc::Print("m_nWavePrisonerNum >> %d\n", m_nWavePrisonerNum);


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
		////Go�T�C������
		//pGameManager->m_pScene2D_GoSign = CScene2D::CreateSceneManagement(D3DXVECTOR3(1000.0f, 300.0f, 0.0f), D3DXVECTOR3(200.0f, 120.0f,0.0f),CScene::OBJTYPE_UI);
		//pGameManager->m_pScene2D_GoSign->BindTexture(CTexture::GetTexture(CTexture::TEX_ITEM_MEDAL));
		//pGameManager->m_pScene2D_GoSign->SetColor(WhiteColor);

		return pGameManager;
	}
	return nullptr;
}
//------------------------------------------------------------------------------
//�X�e�[�g�؂�ւ�
//------------------------------------------------------------------------------
void CGameManager::SetGameState(GAMESTATE state)
{
	m_state = state;

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

	m_nWaveEnemyCnt++;
	m_nWavePrisonerCnt++;

	//�܂��o�ĂȂ��̂�����Ƃ�
	//�G
	if (m_nWaveEnemyNum < (int)pWaveInfo->EnemyWaveInfo.size())
	{
		//�t���[�������ꏏ�ɂȂ�����
		if (pWaveInfo->EnemyWaveInfo[m_nWaveEnemyNum]->nFrame == m_nWaveEnemyCnt)
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
		//�t���[�������ꏏ�ɂȂ�����
		if (pWaveInfo->PrisonerWaveInfo[m_nWavePrisonerNum]->nFrame == m_nWavePrisonerCnt)
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
	if (m_pScene2D_GoSign)
	{
		if (CManager::GetGame()->GetMap()->GetMapNum() == CMap::MAP_1_1)
		{
			if (m_nCnt % 40 == 0)
			{
				m_pScene2D_GoSign->SetDisp(m_pScene2D_GoSign->GetDisp() ^ 1);
			}
		}
	}
}
//------------------------------------------------------------------------------
//�^�C�}�[�X�V
//------------------------------------------------------------------------------
void CGameManager::UpdateTimer()
{
	// �Q�[�����[�h�Ńv���C����\�ȃ^�C�~���O�̎�
	if (m_state != CGameManager::GAMESTATE::RESULT)
	{
		// �J�E���g���Z
		m_nTimeCnt++;
	}

	// 5�b�o�߂�����
	if (m_nTimeCnt >= 300)
	{
		if (CManager::GetBaseMode()->GetPlayer()->GetPlayerUI())
		{
			// �̗͂�0���傫��������
			if (CManager::GetBaseMode()->GetPlayer()->GetPlayerUI()->GetTime() > 0)
			{
				// �^�C�}�[�̒l����������
				CManager::GetBaseMode()->GetPlayer()->GetPlayerUI()->DecrementTime();
			}
			// �^�C�}�[��0�ȉ��ɂȂ�����
			else
			{
			}
		}

		// �^�C�}�[�J�E���g�����Z�b�g����
		m_nTimeCnt = 0;
	}
}
