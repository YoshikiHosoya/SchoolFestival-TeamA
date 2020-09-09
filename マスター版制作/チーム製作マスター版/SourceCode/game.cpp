// =====================================================================================================================================================================
//
// �Q�[���̏��� [game.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#include "game.h"
#include "manager.h"
#include "renderer.h"
#include "player.h"
#include "playerui.h"
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "pause.h"
#include "ParticleManager.h"
#include "item.h"
#include "UIManager.h"
#include "Scene.h"
#include "3Dline.h"
#include "resultUI.h"
#include "Boss.h"
#include "GameManager.h"
#include "ResultManager.h"
#include "shield.h"
#include "title.h"
#include "ModelSet.h"
// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define _CRT_SECURE_NO_WARNINGS // �x������

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
int			CGame::m_Counter	= 0;

CPlayer		*CGame::m_pPlayer[MAX_CONTROLLER] = {};
CMap		*CGame::m_pMap		= nullptr;

//==========================================================
// �R���X�g���N�^
//==========================================================
CGame::CGame()
{

}
//==========================================================
// �f�X�g���N�^
//==========================================================
CGame::~CGame()
{
	m_pGameManager = nullptr;

	for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
	{
		if (m_pPlayer[nCnt])
		{
			m_pPlayer[nCnt] = nullptr;
		}
	}
}
//==========================================================
// ������
//==========================================================
HRESULT CGame::Init(void)
{
	m_nFrame = 0;
	m_nCntNum = 0;

	m_pMap		= CMap::MapCreate();		// �}�b�v�̐���
	m_pMap->MapLoad(CMap::MAP_1_1);			// �}�b�v�̃��[�h

	m_pPlayer[(int)TAG::PLAYER_1] = CPlayer::Create(TAG::PLAYER_1);
	// �����I�v���C���[2�̔z�u

	if (CPlayer::GetTwoPPlayFlag() && !m_pPlayer[(int)TAG::PLAYER_2])
	{
		// �v���C���[2�̔z�u
		m_pPlayer[(int)TAG::PLAYER_2] = CPlayer::Create(TAG::PLAYER_2);
		m_pPlayer[(int)TAG::PLAYER_2]->SetPosition(m_pPlayer[(int)TAG::PLAYER_2]->GetPosition() + D3DXVECTOR3(100.0f, 0.0f, 0.0f));
		m_pPlayer[(int)TAG::PLAYER_2]->GetModelSet()->ChangeColor(true, D3DXCOLOR(0.5f, -0.5f, 1.0f, 0.0f));
	}

	//�Q�[���̐i�s�Ǘ��N���X�쐬
	m_pGameManager = CGameManager::Create();
	m_pGameManager->SetGameState(CGameManager::GAMESTATE::NORMAL);

	//�p�[�e�B�N������
	CParticleManager::Create();

	// UI����
	CUIManager::Create();

	return S_OK;
}
//==========================================================
// �I��
//==========================================================
void CGame::Uninit(void)
{

	// �A�C�e���N���X�̐ÓI�ϐ��̏�����
	CItem::InitVariable();
	// �X�R�A�̌v�Z
	CResultUI::TotalScoreCalculation();

	if (m_pResultManager != nullptr)
	{
		// ���U���g�}�l�W���[�̔j��
		delete m_pResultManager;
		m_pResultManager = nullptr;
	}

	if (m_pGameManager)
	{
		// �Q�[���}�l�[�W���[�̃������J��
		m_pGameManager.reset();
		m_pGameManager = nullptr;
	}

	if (m_pMap)
	{
		// �}�b�v�̔j��
		delete m_pMap;
		m_pMap = nullptr;
	}
}
//==========================================================
// �X�V
//==========================================================
void CGame::Update(void)
{
	if (m_pMap)
	{
		// ���S���肪�o�Ă��邩�̊m�F
		m_pMap->UpdateDieFlag();
	}

	//nullcheck
	if (m_pGameManager)
	{
		//�Q�[���̐i�s�Ǘ��̍X�V
		m_pGameManager->Update();
	}

	// ���U���g�}�l�[�W���[�N���X���������ꂽ��
	if (m_pResultManager != nullptr)
	{
		// ���U���g�}�l�[�W���[�X�V
		m_pResultManager->Update();
	}
}
//==========================================================
// �v���C���[�擾
//==========================================================
CPlayer * CGame::GetPlayer(TAG Tag)
{
	return m_pPlayer[(int)Tag];
}
//==========================================================
// �}�b�v�擾
//==========================================================
CMap * CGame::GetMap(void)
{
	if (m_pMap)
	{
		return m_pMap;
	}
	return nullptr;
}

//==========================================================
// �X�e�[�g�ύX���̃��A�N�V����
//==========================================================
void CGame::StateChangeReaction()
{
	//�X�e�[�g�ɂ���ď������ς��
	switch (m_pGameManager->GetGameState())
	{
	case CGameManager::GAMESTATE::NORMAL:
		//nullcheck
		if (m_pResultManager)
		{
			// ���U���g�Ǘ��N���X�̔j��
			delete m_pResultManager;
			m_pResultManager = nullptr;
		}
		break;

	case CGameManager::GAMESTATE::RESULT:
		//nullcheck
		if (m_pResultManager)
		{
			// ���U���g�Ǘ��N���X�j��
			delete m_pResultManager;
			m_pResultManager = nullptr;

		}

		// ���U���g�Ǘ��N���X�̐���
		for (int nCnt = 0; nCnt < MAX_CONTROLLER; nCnt++)
		{
			if (m_pPlayer[nCnt])
			{
				m_pPlayer[nCnt]->SetState(CPlayer::CHARACTER_STATE_INVINCIBLE);
			}
		}

		m_pResultManager = CResultManager::Create();

		break;

	case CGameManager::GAMESTATE::GAMEOVER:
		break;

	case CGameManager::GAMESTATE::PAUSE:
		break;

	default:

		break;
	}
}

//==========================================================
// �̗͂̎擾
//==========================================================
void CGame::Draw(void)
{
	m_pGameManager->Draw();
}
//==========================================================
// �f�o�b�O���\�L
//==========================================================
void CGame::ShowDebugInfo(void)
{
	//�L�[�{�[�h���擾
	CKeyboard *key = CManager::GetInputKeyboard();

	m_pGameManager->ShowDebugInfo();

	if (m_pMap)
	{
		m_pMap->ShowDebugInfo();
	}

	// �f�o�b�O�p�����蔻��
	DebugCollision(key);
	// �f�o�b�O�p�A�C�e��
	DebugItem(key);
}

//==========================================================
// �f�o�b�O�p�����蔻��̉���on off
//==========================================================
void CGame::DebugCollision(CKeyboard *key)
{
	//�g��������
	CDebugProc::Print_Right("\n---------Debug Collision----------\n");
	CDebugProc::Print_Right("[Ctrl] + �e���L�[ [5] : �����蔻��̃��C���̕\����\��\n");


	if (C3DLine::GetDrawFlag())
	{
		CDebugProc::Print_Right("�f�o�b�O�p�����蔻�胉�C����`�悵�Ă��܂�\n");
	}
	else
	{
		CDebugProc::Print_Right("�f�o�b�O�p�����蔻�胉�C����`�悵�Ă��܂���\n");
	}

	//�{�X�}�b�v
	if (key->GetKeyboardTrigger(DIK_F7))
	{
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CMap::MAP_1_BOSS);
	}
	if (key->GetKeyboardTrigger(DIK_F8))
	{
		CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, CMap::MAP_2_BOSS);
	}

	// �����蔻�胉�C���̕\����\��
	if (key->GetKeyboardPress(DIK_LCONTROL))
	{// Ctrl + 5
		if (key->GetKeyboardTrigger(DIK_NUMPAD5))
		{
			if (C3DLine::GetDrawFlag())
			{// �\�����Ȃ��\��
				C3DLine::SetDrawFlag(false);
			}
			else
			{// ��\���Ȃ�\��
				C3DLine::SetDrawFlag(true);
			}
		}

		if (key->GetKeyboardTrigger(DIK_8))
		{
			if (m_pMap->GetMapNum() - 1 > 0)
			{
				CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, (CMap::MAP)(m_pMap->GetMapNum() - 1));
			}
		}
		if (key->GetKeyboardTrigger(DIK_9))
		{
			if (m_pMap->GetMapNum() + 1 < CMap::MAP_MAX)
			{
				CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MAPMOVE, (CMap::MAP)(m_pMap->GetMapNum() + 1));
			}
		}
		if (key->GetKeyboardTrigger(DIK_0))
		{
			//�^�C�}�[����

			m_pPlayer[(int)TAG::PLAYER_1]->GetPlayerUI()->DecrementTime();
		}
	}
}

//==========================================================
// �f�o�b�O�p�A�C�e��
//==========================================================
void CGame::DebugItem(CKeyboard *key)
{
	// �f�o�b�O�p�A�C�e���R�}���h
	CItem::DebugItemCommand(key);
}
