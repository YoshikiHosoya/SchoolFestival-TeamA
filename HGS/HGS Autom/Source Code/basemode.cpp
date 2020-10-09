//-----------------------------------------------------------------------------
//
// ���[�h�̋K��N���X [basemode.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "basemode.h"
#include "modelcharacter.h"
#include "character.h"
#include "particle.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "keyboard.h"
#include "sound.h"
#include "modelinfo.h"
//-----------------------------------------------------------------------------
//�f�o�b�O�R�}���h
//-----------------------------------------------------------------------------
void CBaseMode::DebugCommand()
{
	//�L�[�{�[�h�擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//�g��������
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "--------------------Debug Command--------------------\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[F3] : �ꎞ��~\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[F4] : �ꎞ��~����1F�����X�V\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[F5] : DebugProc�\�L on/off\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[F6] : ImGui�\�L on/off\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[F8] : �~���[�g on/off\n");

	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[Ctrl] + �e���L�[ [0] : ���݂�Mode�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[Ctrl] + �e���L�[ [1] : Title�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[Ctrl] + �e���L�[ [2] : Tutorial�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[Ctrl] + �e���L�[ [3] : 2DGame�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[Ctrl] + �e���L�[ [4] : Result�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[Ctrl] + �e���L�[ [5] : Ranking�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_LEFT, "[Ctrl] + �e���L�[ [8] : EffectViewer�ɑJ��\n");
	//CDebugProc::Print(CDebugProc::PLACE_LEFT, "[Ctrl] + �e���L�[ [9] : MotionViewer�ɑJ��\n");


	//�ꎞ��~
	if (pKeyboard->GetTrigger(DIK_F3))
	{
		CScene::SetStop(CScene::GetStop() ^ 1);
	}

	//1F�����X�V
	if (pKeyboard->GetTrigger(DIK_F4))
	{
		CScene::Set1FAction();
	}

	//�f�o�b�O�\�Lon/off
	if (pKeyboard->GetTrigger(DIK_F5))
	{
		CManager::GetRenderer()->SetDispDebugProcInfo(CManager::GetRenderer()->CheckShowDebugProcInfo() ^ 1);
	}

	//ImGui�\�Lon/off
	if (pKeyboard->GetTrigger(DIK_F6))
	{
		CManager::GetRenderer()->SetDispImGuiInfo(CManager::GetRenderer()->CheckShowImGuiInfo() ^ 1);
	}

	//�~���[�g�\�Lon/off
	if (pKeyboard->GetTrigger(DIK_F8))
	{
		CManager::GetSound()->SetMute(CManager::GetSound()->GetMute() ^ 1);
	}

	//Ctrl�����Ȃ���
	if (pKeyboard->GetPress(DIK_LCONTROL))
	{
		//���݂̃��[�h�Ďn��
		if (pKeyboard->GetTrigger(DIK_NUMPAD0))
		{
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::GetMode());
		}
		//�^�C�g��
		if (pKeyboard->GetTrigger(DIK_NUMPAD1))
		{
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
		}
		//�`���[�g���A��
		if (pKeyboard->GetTrigger(DIK_NUMPAD2))
		{
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TUTORIAL);
		}
		//�Q�[��
		if (pKeyboard->GetTrigger(DIK_NUMPAD3))
		{
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_2DGAME);
		}
		//���U���g
		if (pKeyboard->GetTrigger(DIK_NUMPAD4))
		{
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RESULT);
		}
		//�����L���O
		if (pKeyboard->GetTrigger(DIK_NUMPAD5))
		{
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_RANKING);
		}

		//�G�t�F�N�g�r���[��
		if (pKeyboard->GetTrigger(DIK_NUMPAD8))
		{
			CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_EFFECTVIEWER);
		}
		////���[�V�����r���[��
		//if (pKeyboard->GetTrigger(DIK_NUMPAD9))
		//{
		//	CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TITLE);
		//}
	}

	//�f�o�b�O���\�L
	//�I�[�o�[���C�h�p�@���ꂼ��̃��[�h�ŏ���
	ShowDebugInfo();
}
//-----------------------------------------------------------------------------
//�g���e�N�X�`���⃂�f���̓ǂݍ���
//-----------------------------------------------------------------------------
void CBaseMode::BaseLoad(HWND hWnd)
{
	//�e�N�X�`�����[�h
	CTexture::TexLoad(hWnd);
	CModelInfo::ModelLoad(hWnd);

	//���f���ǂݍ���
	if (FAILED(CModelCharacter::Load()))
	{
		//���s
		MessageBox(hWnd, "���f�����ǂݍ��ݎ��s", "CModelCharacter", MB_OK | MB_ICONHAND);
	}

	//���[�V�����ǂݍ���
	if (FAILED(CMotion::Load()))
	{
		//���s
		MessageBox(hWnd, "���[�V�����ǂݍ��ݎ��s", "CMotion", MB_OK | MB_ICONHAND);
	}

	//�L�����N�^�[�̏����p�����[�^�ǂݍ���
	if (FAILED(CCharacter::LoadDefaultParam()))
	{
		//���s
		MessageBox(hWnd, "�p�����[�^�ǂݍ��ݎ��s", "CCharacter", MB_OK | MB_ICONHAND);
	}

	//�p�[�e�B�N���̃e�N�X�`���ƒ��_�m��
	if (FAILED(CParticle::MakeVertex()))
	{
		//���s
		MessageBox(hWnd, "�e�N�X�`���ǂݍ��ݎ��s", "CParticle", MB_OK | MB_ICONHAND);
	}
	//�p�[�e�B�N���̃e�N�X�`���ƒ��_�m��
	if (FAILED(CParticleParam::LoadParticleDefaultParam()))
	{
		//���s
		MessageBox(hWnd, "�e�N�X�`���ǂݍ��ݎ��s", "CParticle", MB_OK | MB_ICONHAND);
	}
}

//-----------------------------------------------------------------------------
//�����������̂�S�Ĕj��
//----------------------------------------------------------------------------
void CBaseMode::BaseUnload()
{
	//�e�N�X�`���j��
	CTexture::TexUnload();

	//���f���Ɋւ������
	CModelCharacter::UnLoad();
	CMotion::UnLoad();

	//�p�[�e�B�N���̒��_���J��
	CParticle::ReleaseVertex();

}
