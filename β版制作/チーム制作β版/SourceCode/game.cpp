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
#include "inputKeyboard.h"
#include "fade.h"
#include "map.h"
#include "pause.h"
#include "ParticleManager.h"
#include "TexAnimation3D_Collision.h"
#include "item.h"
#include "UIManager.h"
#include "Scene.h"
#include "3Dline.h"
#include "resultUI.h"
#include "ResultManager.h"

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
	// �Q�[�����[�h�̏������
	m_GameMode = GAME_MODE_NORMAL;
}
//==========================================================
// �f�X�g���N�^
//==========================================================
CGame::~CGame()
{
}
//==========================================================
// ������
//==========================================================
HRESULT CGame::Init(void)
{
	m_pMap		= CMap::MapCreate(CMap::MAP_1);	// �}�b�v�̐���
	m_pPlayer	= CPlayer::Create();
	m_pPlayer->SetLife(30);
	m_pPlayer->SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	m_pPause->CreatePause();

	// �Q�[�����[�h�̏����ݒ�
	m_GameMode = GAME_MODE_NORMAL;

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
}
//==========================================================
// �X�V
//==========================================================
void CGame::Update(void)
{
	// ���S���肪�o�Ă��邩�̊m�F
	m_pMap->UpdateDieFlag();

	// ���U���g���[�h�ł܂����U���g�}�l�[�W���[����������Ă��Ȃ�������
	if (m_GameMode == GAME_MODE_RESULT && m_pResultManager == nullptr)
	{
		// ���U���g�Ǘ��N���X�̐���
		m_pResultManager = CResultManager::Create();
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
// �̗͂̎擾
//==========================================================
void CGame::Draw(void)
{
}
//==========================================================
// �f�o�b�O���\�L
//==========================================================
void CGame::ShowDebugInfo(void)
{
	//�L�[�{�[�h���擾
	CKeyboard *key = CManager::GetInputKeyboard();

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
