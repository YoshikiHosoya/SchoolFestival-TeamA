//==========================================================
// �x�[�X���[�h�N���X [basemode.cpp]
//==========================================================
#include "basemode.h"
#include "character.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "inputKeyboard.h"
#include "model.h"
#include "bullet.h"
#include "Obstacle.h"
#include "particle.h"
#include "item.h"
#include "prisoner.h"
#include "sound.h"
#include "scoremanager.h"
#include "player.h"
#include "boss_one.h"
#include "grenade.h"
#include "map.h"

//==========================================================
//�f�o�b�O�R�}���h
//==========================================================
void CBaseMode::DebugCommand(void)
{
#ifdef _DEBUG
	//�L�[�{�[�h�擾
	CKeyboard *key = CManager::GetInputKeyboard();

	//�g��������
	CDebugProc::Print_Right("---------Debug Command----------\n");
	CDebugProc::Print_Right("[F3] : �ꎞ��~\n");
	CDebugProc::Print_Right("[F4] : �ꎞ��~����1F�����X�V\n");
	CDebugProc::Print_Right("[F5] : �f�o�b�O�\�L on/off\n");
	CDebugProc::Print_Right("[F6] : �~���[�g on/off\n");

	CDebugProc::Print_Right("[Ctrl] + �e���L�[ [0] : ���݂�Mode�ɑJ��\n");
	CDebugProc::Print_Right("[Ctrl] + �e���L�[ [1] : Title�ɑJ��\n");
	CDebugProc::Print_Right("[Ctrl] + �e���L�[ [2] : Game�ɑJ��\n");
	CDebugProc::Print_Right("[Ctrl] + �e���L�[ [4] : Ranking�ɑJ��\n");
	CDebugProc::Print_Right("[Ctrl] + �e���L�[ [7] : MapEditor�ɑJ��\n");
	CDebugProc::Print_Right("[Ctrl] + �e���L�[ [8] : EffectViewer�ɑJ��\n");
	CDebugProc::Print_Right("[Ctrl] + �e���L�[ [9] : MotionViewer�ɑJ��\n");


	//�ꎞ��~
	if (key->GetKeyboardTrigger(DIK_F3))
	{
		CScene::StopUpdate();
	}

	//1F�����X�V
	if (key->GetKeyboardTrigger(DIK_F4))
	{
		CScene::Set1FUpdate();
	}

	//�f�o�b�O�\�Lon/off
	if (key->GetKeyboardTrigger(DIK_F5))
	{
		CManager::GetRenderer()->SetShowDebug();
	}

	//�~���[�g�\�Lon/off
	if (key->GetKeyboardTrigger(DIK_F6))
	{
		CManager::GetSound()->SetMute(CManager::GetSound()->GetMute() ^ 1);
	}

	//Ctrl�����Ȃ���
	if (key->GetKeyboardPress(DIK_LCONTROL))
	{
		//���݂̃��[�h�Ďn��
		if (key->GetKeyboardTrigger(DIK_NUMPAD0))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::GetMode());
		}
		//�^�C�g��
		if (key->GetKeyboardTrigger(DIK_NUMPAD1))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_TITLE);
		}
		//�Q�[��
		if (key->GetKeyboardTrigger(DIK_NUMPAD2))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_GAME);
		}
		//���U���g
		if (key->GetKeyboardTrigger(DIK_NUMPAD4))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_RANKING);
		}
		//�}�b�v�G�f�B�^�[
		if (key->GetKeyboardTrigger(DIK_NUMPAD7))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_DEBUG_MAPEDITOR);
		}
		//�G�t�F�N�g�r���[��
		if (key->GetKeyboardTrigger(DIK_NUMPAD8))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_DEBUG_EFFECTVIEWER);
		}
		//���[�V�����r���[��
		if (key->GetKeyboardTrigger(DIK_NUMPAD9))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CFADE::FADETYPE::FADETYPE_MODE, CManager::MODE_DEBUG_MODELVIEWER);
		}
	}

	//�f�o�b�O���\�L
	//�I�[�o�[���C�h�p�@���ꂼ��̃��[�h�ŏ���
	ShowDebugInfo();

#endif //_DEBUG
}
//==========================================================
//�g���e�N�X�`���⃂�f���̓ǂݍ���
//==========================================================
void CBaseMode::BaseLoad(HWND hWnd)
{
	//�e�N�X�`�����[�h
	CTexture::TexLoad(hWnd);
	//���f�����[�h
	CModel::LoadModel();
	//���[�V�������[�h
	CCharacter::LoadMotion();
	//�e�̃p�����[�^�[���[�h
	CBullet::BulletLoad();
	//�O���l�[�h�̃p�����[�^�[���[�h
	CGrenade::GrenadePramLoad();
	//��Q���̃p�����[�^�[���[�h
	CObstacle::ObstacleLoad();
	//�p�[�e�B�N���̃p�����[�^���[�h
	CParticleParam::LoadParticleDefaultParam();
	// �A�C�e���̃f�[�^�̃��[�h
	CItem::ItemLoad();
	// �ߗ��̃f�[�^�̓ǂݍ���
	CPrisoner::PrisonerLoad();
	// �X�R�A�̃f�[�^�̓ǂݍ���
	CScoreManager::ScoreLoad();
	// �v���C���[�̃f�[�^�̓ǂݍ���
	CPlayer::PlayerLoad();
	// �{�X1�̃f�[�^�̓ǂݍ��� �h���S���m�X�P
	CBoss_One::Boss_One_DataLoad();
	// �E�F�[�u���ǂݍ���
	CMap::WaveLoad();
}
//==========================================================
//�����������̂�S�Ĕj��
//==========================================================
void CBaseMode::BaseUnload(void)
{
	CModel::UnLoad();
	CTexture::TexUnload();
	CCharacter::CharacterUnLoad();
	CMap::WaveUnLoad();

}