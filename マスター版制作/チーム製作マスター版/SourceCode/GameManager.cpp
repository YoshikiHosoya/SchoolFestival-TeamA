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
	m_nWaveCnt = 0;
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
	CMap::WAVE_INFO *pWaveInfo = pGame->GetMap()->GetWaveInfo(m_nNowWave);

	m_nCnt = 0;

	if (pPlayer)
	{
		if(pPlayer->GetPosition().x >= CManager::GetGame()->GetMap()->GetTransitionPos().x)
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CManager::GetGame()->GetMap()->GetTransitionMapID());
		}

		if (pPlayer->GetPosition().x >= pWaveInfo->EventPos.x)
		{
			//�E�F�[�u�J�n
			StartWave();
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
	case CGameManager::GAMESTATE::BOSSBUTTLE:
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
	CDebugProc::Print("NowWaveNum >> %d\n", m_nNowWave);

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
//�C�x���g�N���A
//------------------------------------------------------------------------------
void CGameManager::EventClear()
{
	EndWave();
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
	m_nWaveCnt = 0;
	m_nWaveEnemyNum = 0;
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
		return;
	}

	//�E�F�[�u�̃|�C���^
	CMap::WAVE_INFO *pWaveInfo = CManager::GetGame()->GetMap()->GetWaveInfo(m_nNowWave);

	m_nWaveCnt++;

	//�܂��o�ĂȂ��̂�����Ƃ�
	if (m_nWaveEnemyNum < (int)pWaveInfo->EnemyWaveInfo.size())
	{
		//�t���[�������ꏏ�ɂȂ�����
		if (pWaveInfo->EnemyWaveInfo[m_nWaveEnemyNum]->nFrame == m_nWaveCnt)
		{
			//�G����
			CManager::GetGame()->GetMap()->WaveCreate(CModel::ENEMY_MODEL, pWaveInfo->EventPos, pWaveInfo->EnemyWaveInfo[m_nWaveEnemyNum]);
			m_nWaveEnemyNum++;
			m_nWaveCnt = 0;
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
