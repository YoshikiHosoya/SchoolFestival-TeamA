//------------------------------------------------------------------------------
//
//�^�C�g������  [title.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "manager.h"
#include "renderer.h"
#include "camera.h"
#include "scene.h"
#include "fade.h"
#include "title.h"
#include "Map.h"
#include "UI.h"
#include "effectanimation2D.h"
#include "sound.h"
#include "backthunder.h"
#include "keyboard.h"
//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define DEMOPLAY_FADE_COUNT		(1000)		//�f���v���C�ɍs���܂ł̃J�E���^
#define TITLEUI_APPEAR_COUNT	(120)		//�^�C�g����UI���\�������܂ł̃J�E���^
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CTitle::CTitle()
{
	m_pBlack.reset();
	m_nCntState = DEMOPLAY_FADE_COUNT;
	m_titlestate = STATE_START;

}

//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CTitle::~CTitle()
{
	m_pBlack.reset();
}

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CTitle::Init(HWND hWnd)
{
	//�J�������W�ݒ�
	CManager::GetRenderer()->GetCamera()->SetCameraPos(ZeroVector3, D3DXVECTOR3(0.0f, 200.0f, -600.0f));
	CManager::GetRenderer()->GetCamera()->SetState(CCamera::CAMERA_TITLE);

	//�u���b�N�A�E�g
	m_pBlack = CScene2D::Create_Shared(SCREEN_CENTER_POS, SCREEN_SIZE, CScene::OBJTYPE_2DUI);
	m_pBlack->SetVtxCol(BlackColor);

	//�ŏ��̓d��
	CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_TITLESPARK, 0.0f, 2,CScene::OBJTYPE_2DEFFECT);

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CTitle::Uninit()
{
	//�I������
	CScene::ReleaseAll();
}

//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CTitle::Update()
{
	//�J�E���g�_�E��
	m_nCntState--;

	//�^�C�g���̊J�n�̎��i�ŏ��̃r���r���̊ԁj
	if (m_titlestate == STATE_START)
	{
		//�����{�^��
		if (CHossoLibrary::CheckAnyButton())
		{
			//UI�ł�Ƃ��܂ŃX�L�b�v
			m_nCntState = DEMOPLAY_FADE_COUNT - TITLEUI_APPEAR_COUNT;

		}

		//���Ԋu
		if (m_nCntState % 15 == 0)
		{
			//�d��
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_SPARKING);

			//�d���ȃG�t�F�N�g
			CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(SCREEN_WIDTH, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_TITLESPARK, 0.0f, 2, CScene::CScene::OBJTYPE_2DEFFECT);
		}
		if (m_nCntState == DEMOPLAY_FADE_COUNT - TITLEUI_APPEAR_COUNT)
		{
			//����~
			CManager::GetSound()->Stop(CSound::LABEL_SE_TITLE_SPARKING);

			//���Đ�
			CManager::GetSound()->Play(CSound::LABEL_SE_TITLE_EXPLOSION);

			//���w�i����
			m_pBlack->Release();

			//���܂ŏo���Ă��G�t�F�N�g�O�i
			CScene::ReleaseSpecificObject(CScene::OBJTYPE_2DEFFECT);

			//���ŗ����Ƃ�
			CBackThunder::Create();

			//UI�z�u
			CUI::LoadPlace(CUI::SCENE_TITLE);

			//�����̓d��
			CEffectAnimation2D::Create(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f), D3DXVECTOR3(1500.0f, 1000.0f, 0.0f), CTexture::SEPARATE_TEX_EFFECT_SPARKEXPLOSION, 0.0f, 2,CScene::CScene::OBJTYPE_2DEFFECT);

			//�X�e�[�g�؂�ւ�
			m_titlestate = CTitle::STATE_NORMAL;
		}
	}

	//�ʏ��Ԃ̂Ƃ�
	if (m_titlestate == STATE_NORMAL)
	{
		//�t�F�[�h���ĂȂ���
		if (CManager::GetRenderer()->GetFade()->GetFade() == CFade::FADE_NONE)
		{
			//������x���Ԃ�������
			if (m_nCntState < 0)
			{
				//�f���v���C
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_DEMOPLAY);
			}

			//�Ȃ񂩃{�^�������ꂽ�Ƃ�
			if (CHossoLibrary::CheckAnyButton() && m_nCntState < DEMOPLAY_FADE_COUNT - TITLEUI_APPEAR_COUNT - 10)
			{
				//�`���[�g���A���ɑJ��
				CManager::GetRenderer()->GetFade()->SetModeFade(CManager::MODE_TUTORIAL);
				CManager::GetSound()->Play(CSound::LABEL_SE_DECISION);

			}
		}
	}
}

//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CTitle::Draw()
{
}
