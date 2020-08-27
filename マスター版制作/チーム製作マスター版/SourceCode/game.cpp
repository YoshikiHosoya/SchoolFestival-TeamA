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
// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define _CRT_SECURE_NO_WARNINGS // �x������

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
int			CGame::m_Counter	= 0;
CPlayer		*CGame::m_pPlayer	= nullptr;
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

	m_pPlayer	= CPlayer::Create();

	for (int nCnt = 0; nCnt < CMap::WAVE_MAX; nCnt++)
	{
		m_pMap->WaveLoad((CMap::WAVE)nCnt);
	}

	m_pPause->CreatePause();

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
	//�L�[�{�[�h���擾
	CKeyboard *key = CManager::GetInputKeyboard();

	// ���S���肪�o�Ă��邩�̊m�F
	m_pMap->UpdateDieFlag();

	//�Q�[���̐i�s�Ǘ��̍X�V
	m_pGameManager->Update();

	// ���U���g���[�h�ł܂����U���g�}�l�[�W���[����������Ă��Ȃ�������
	if (m_pGameManager->GetGameState() == CGameManager::GAMESTATE::RESULT && m_pResultManager == nullptr)
	{

	}
	else
	{
		// ���U���g�}�l�[�W���[�N���X���������ꂽ��
		if (m_pResultManager != nullptr)
		{
			// ���U���g�}�l�[�W���[�X�V
			m_pResultManager->Update();
		}
	}

 }
//==========================================================
// �v���C���[�擾
//==========================================================
CPlayer * CGame::GetPlayer(void)
{
	return m_pPlayer;
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
		m_pResultManager = CResultManager::Create();
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
	CDebugProc::Print("\n---------Debug Collision----------\n");
	CDebugProc::Print("[Ctrl] + �e���L�[ [5] : �����蔻��̃��C���̕\����\��\n");

	if (C3DLine::GetDrawFlag())
	{
		CDebugProc::Print("�f�o�b�O�p�����蔻�胉�C����`�悵�Ă��܂�\n");
	}
	else
	{
		CDebugProc::Print("�f�o�b�O�p�����蔻�胉�C����`�悵�Ă��܂���\n");
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
