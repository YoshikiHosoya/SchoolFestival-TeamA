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
	// �A�C�e���N���X�̐ÓI�ϐ��̏�����
	CItem::InitVariable();
}
//==========================================================
// ������
//==========================================================
HRESULT CGame::Init(void)
{
	m_pMap		= CMap::MapCreate();		// �}�b�v�̐���
	m_pMap->MapLoad(CMap::MAP_1);			// �}�b�v�̃��[�h
	m_pMap->WaveLoad(CMap::WAVE_1);

	m_pPlayer	= CPlayer::Create();
	m_pPlayer->SetLife(100);
	m_pPlayer->SetPosition(D3DXVECTOR3(50.0f, 100.0f, 0.0f));

	m_pPause->CreatePause();

	//�p�[�e�B�N������
	CParticleManager::Create();
	// UI����
	CUIManager::Create();
	// ���U���gui�̐���
	//CResultUI::Create();

	return S_OK;

}
//==========================================================
// �I��
//==========================================================
void CGame::Uninit(void)
{

}
//==========================================================
// �X�V
//==========================================================
void CGame::Update(void)
{
	m_nFrame++;
	m_pMap->WaveCreate(CMap::WAVE_1, CMap::ARRANGEMENT_MODEL_ENEMY, m_nFrame);

	if (m_nFrame > 700)
	{
		m_nFrame = 0;
	}
	// ���S���肪�o�Ă��邩�̊m�F
	m_pMap->UpdateDieFlag();

	// �Q�[�����[�h�����U���g��ԂɂȂ�����
	if (m_GameMode == GAME_MODE_RESULT)
	{
		// ���U���g�摜�`��
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
