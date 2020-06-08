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
//==========================================================
//�f�o�b�O�R�}���h
//==========================================================
void CBaseMode::DebugCommand(void)
{
	//�L�[�{�[�h�擾
	CKeyboard *key = CManager::GetInputKeyboard();

	//���݂̃��[�h�Ďn��
	if (key->GetKeyboardTrigger(DIK_NUMPAD0))
	{
		CManager::GetRendere()->GetFade()->SetFade(CManager::GetGameState());
	}
	//�^�C�g��
	if (key->GetKeyboardTrigger(DIK_NUMPAD1))
	{
		CManager::GetRendere()->GetFade()->SetFade(CManager::MODE_TITLE);
	}
}
//==========================================================
//�g���e�N�X�`���⃂�f���̓ǂݍ���
//==========================================================
void CBaseMode::BaseLoad(HWND hWnd)
{
	//�e�N�X�`�����[�h
	CTexture::TexLoad(hWnd);
	CModel::LoadModel();
	CCharacter::LoadMotion();
}
//==========================================================
//�����������̂�S�Ĕj��
//==========================================================
void CBaseMode::BaseUnload(void)
{
	CModel::UnLoad();
	CTexture::TexUnload();
}
