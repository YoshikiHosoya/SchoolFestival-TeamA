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
//==========================================================
//�f�o�b�O�R�}���h
//==========================================================
void CBaseMode::DebugCommand(void)
{
#ifdef _DEBUG
	//�L�[�{�[�h�擾
	CKeyboard *key = CManager::GetInputKeyboard();

	//�g��������
	CDebugProc::Print("---------Debug Command----------\n");

	CDebugProc::Print("[F3] : �ꎞ��~\n");
	CDebugProc::Print("[F4] : �ꎞ��~����1F�����X�Vn");

	CDebugProc::Print("[Ctrl] + �e���L�[ [0] : ���݂�Mode�ɑJ��\n");
	CDebugProc::Print("[Ctrl] + �e���L�[ [1] : Title�ɑJ��\n");
	CDebugProc::Print("[Ctrl] + �e���L�[ [2] : Game�ɑJ��\n");
	CDebugProc::Print("[Ctrl] + �e���L�[ [3] : Result�ɑJ��\n");
	CDebugProc::Print("[Ctrl] + �e���L�[ [8] : EffectViewer�ɑJ��\n");
	CDebugProc::Print("[Ctrl] + �e���L�[ [9] : MotionViewer�ɑJ��\n");



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

	//Ctrl�����Ȃ���
	if (key->GetKeyboardPress(DIK_LCONTROL))
	{
		//���݂̃��[�h�Ďn��
		if (key->GetKeyboardTrigger(DIK_NUMPAD0))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CManager::GetGameState());
		}
		//�^�C�g��
		if (key->GetKeyboardTrigger(DIK_NUMPAD1))
		{
			//CManager::GetRenderer()->GetFade()->SetFade(CManager::MODE_TITLE);
		}
		//�Q�[��
		if (key->GetKeyboardTrigger(DIK_NUMPAD2))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CManager::MODE_GAME);
		}
		//���U���g
		if (key->GetKeyboardTrigger(DIK_NUMPAD3))
		{
			//CManager::GetRenderer()->GetFade()->SetFade(CManager::MODE_RESULT);
		}
		//�G�t�F�N�g�r���[��
		if (key->GetKeyboardTrigger(DIK_NUMPAD8))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CManager::MODE_DEBUG_EFFECTVIEWER);
		}
		//���[�V�����r���[��
		if (key->GetKeyboardTrigger(DIK_NUMPAD9))
		{
			CManager::GetRenderer()->GetFade()->SetFade(CManager::MODE_DEBUG_MODELVIEWER);
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
}
//==========================================================
//�����������̂�S�Ĕj��
//==========================================================
void CBaseMode::BaseUnload(void)
{
	CModel::UnLoad();
	CTexture::TexUnload();
}