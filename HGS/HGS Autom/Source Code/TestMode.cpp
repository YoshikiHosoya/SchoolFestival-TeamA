//------------------------------------------------------------------------------
//
//�e�X�g���[�h����  [testMode.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "testMode.h"
#include "manager.h"
#include "renderer.h"
#include "fade.h"
#include "camera.h"
#include "Map.h"
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEFAULT_PLAYER_POS	(D3DXVECTOR3(0.0f, 0.0f, -800.0f))		//�v���C���[�̏������W
//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTestMode::CTestMode()
{

}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTestMode::~CTestMode()
{


}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTestMode::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_DEBUG);

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CTestMode::Uninit()
{
	//�I������
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTestMode::Update()
{

}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTestMode::Draw()
{

}
//------------------------------------------------------------------------------
//�f�o�b�O���\�L
//------------------------------------------------------------------------------
void CTestMode::ShowDebugInfo()
{
#ifdef _DEBUG

#endif //_DEBUG
}