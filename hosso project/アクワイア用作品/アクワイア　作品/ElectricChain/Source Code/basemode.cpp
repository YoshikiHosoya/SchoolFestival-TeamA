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
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "keyboard.h"

//-----------------------------------------------------------------------------
//�f�o�b�O�R�}���h
//-----------------------------------------------------------------------------
void CBaseMode::DebugCommand()
{
	//�L�[�{�[�h�擾
	CKeyboard *pKeyboard = CManager::GetKeyboard();

	//�f�o�b�O�e�L�X�g
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "[F1] : �f�o�b�O��� on/off\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "[F3] : �ꎞ��~ �|�[�Y�ƕ��p����ƃo�O��on/off\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "[F4] : �ꎞ��~����1�R�}����\n");

	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "�e���L�[ [0] : ���݂�Mode�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "�e���L�[ [1] : Title�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "�e���L�[ [2] : Tutorial�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "�e���L�[ [3] : Game�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "�e���L�[ [4] : Result�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "�e���L�[ [5] : Ranking�ɑJ��\n");
	CDebugProc::Print(CDebugProc::PLACE_RIGHT, "�e���L�[ [9] : ���[�V�����r���[���N��\n");

	//�f�o�b�O���\����\��
	if (pKeyboard->GetTrigger(DIK_F1))
	{
		CManager::GetRenderer()->SetDispDebugInfo(CManager::GetRenderer()->CheckShoeDebugInfo() ^ 1);
	}

	//�����
	if (pKeyboard->GetTrigger(DIK_F2))
	{

	}

	//�ꎞ��~
	if (pKeyboard->GetTrigger(DIK_F3))
	{
		CScene::SetStop(CScene::CheckStop() ^ 1);
	}

	//1F�����X�V
	if (pKeyboard->GetTrigger(DIK_F4))
	{
		CScene::Set1FAction();
	}

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
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_GAME);
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
	//���[�V�����r���[��
	if (pKeyboard->GetTrigger(DIK_NUMPAD9))
	{
		CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_DEBUG_MOTION_VIEWER);
	}

	//�I�[�o�[���C�h
	ShowDebugInfo();

}
//-----------------------------------------------------------------------------
//�g���e�N�X�`���⃂�f���̓ǂݍ���
//-----------------------------------------------------------------------------
void CBaseMode::BaseLoad(HWND hWnd)
{
	//�e�N�X�`�����[�h
	CTexture::TexLoad(hWnd);

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

	//�X�R�A�ǂݍ���
	if (FAILED(CScore::LoadScore()))
	{
		//���s
		MessageBox(hWnd, "�X�R�A�ǂݍ��ݎ��s", "CScore", MB_OK | MB_ICONHAND);
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
