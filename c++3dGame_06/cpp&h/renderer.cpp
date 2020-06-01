// ------------------------------------------
//
// �����_�����O�����̐���[renderer.cpp]
// Author : Fujiwara Masato
//
// ------------------------------------------
#include "renderer.h"
#include "scene.h"
#include "scene_load.h"
#include "fade.h"
#include "title.h"
#include "tutorial.h"
#include "game.h"
#include "ranking.h"
#include "debugproc.h"
#include "camera.h"
#include "light.h"
#include "pointlight.h"

CCamera * CRenderer::m_pCamera = NULL;
// ------------------------------------------
//
// �}�N���֐�
//
// ------------------------------------------

// ------------------------------------------
//
// �v���g�^�C�v�錾
//
// ------------------------------------------

// ------------------------------------------
//
// �ÓI�ϐ��錾
//
// ------------------------------------------
#ifdef _DEBUG
CDebugproc * CRenderer::m_debugproc = NULL;
#endif

// ------------------------------------------
// �R���X�g���N�^
// ------------------------------------------
CRenderer::CRenderer()
{
	m_pD3D = NULL;
	m_pDevice = NULL;
}

// ------------------------------------------
// �f�X�g���N�^
// ------------------------------------------
CRenderer::~CRenderer()
{
}

// ------------------------------------------
// ����������
// ------------------------------------------
HRESULT CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	// �ϐ��錾
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// Direct3D�I�u�W�F�N�g�̐���
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp));								// ���[�N���[���N���A
	d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;							// �Q�[����ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;							// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;										// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;						// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;		// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��(VSync��҂��ĕ`��)
	// d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �N���C�A���g�̈�𒼂��ɍX�V����

	// Direct3D�f�o�C�X�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,	// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,									// �f�o�C�X�^�C�v
		hWnd,											// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,			// �f�o�C�X�쐬����̑g�ݍ��킹
		&d3dpp,											// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&m_pDevice)))									// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&m_pDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&m_pDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �����_���[�X�e�[�g�̐ݒ�
	m_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

#ifdef _DEBUG
	m_debugproc = new CDebugproc;
	// �f�o�b�O�\��������
	m_debugproc->Init(m_pDevice);
#endif
	// �V�[���̓ǂݍ���
	CScene_load::LoadAll();
	// �J�����̐���
	m_pCamera = CCamera::Create();
	// ���C�g�̐���
	m_pLight = CLight::Create();
	// �|�C���g���C�g�̐���
	//m_pPointLight = CPointLight::Create();
	return S_OK;
}

// ------------------------------------------
// �I������
// ------------------------------------------
void CRenderer::Uninit(void)
{
	// �ǂݍ��񂾂��̂�j�����鏈��
	CScene_load::UnLoadAll();
	// �V�[���e�q�̃����[�X����
	CScene::ReleaseAll();
	// �J�����̔j��
	m_pCamera->Uninit();
	// ���C�g�̔j��
	m_pLight->Uninit();
	// �|�C���g���C�g�̔j��
	//m_pPointLight->Uninit();
	// �f�o�C�X�̔j��
	if (m_pDevice != NULL)
	{
		m_pDevice->Release();
		m_pDevice = NULL;
	}

	// D3D�I�u�W�F�N�g�̔j��
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
#ifdef _DEBUG
	// �f�o�b�O�\��
	if (m_debugproc != NULL)
	{
		m_debugproc->Uninit();
		delete m_debugproc;
		m_debugproc = NULL;
	}

#endif // _DEBUG
}

// ------------------------------------------
// �X�V����
// ------------------------------------------
void CRenderer::Update(void)
{
	// �J�����̐���
	m_pCamera->Update();
	// ���C�g�̐���
	//m_pLight->Update();
	// �|�C���g���C�g�̍X�V
	//m_pPointLight->Update();

	// �|�[�Y���ȊO
	if (CGame::GetState() != CGame::STATE_PAUSE)
	{
		// �V�[��
		CScene::UpdateAll();
	}
#ifdef _DEBUG
	// FPS�\��
	DrawFPS();

#endif // _DEBUG

}

// -----------------------
// �`�揈��
// --------------------------
void CRenderer::Draw(void)
{
	// �o�b�N�o�b�t�@��Z�o�b�t�@�̃N���A
	m_pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),
		D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��J�n
	if (SUCCEEDED(m_pDevice->BeginScene()))
	{
		// �J�����̐���
		m_pCamera->Set();
		// �V�[��
		CScene::DrawAll();
		// �O�̃��[�h�I��
		switch (CManager::GetMode())
		{
			// �^�C�g��
		case CManager::MODE_TITLE:
			CManager::GetTitle()->Draw();
			break;
			// �Q�[��
		case CManager::MODE_GAME:
			CManager::GetGame()->Draw();
			break;
			// �Q�[��
			// �����L���O
		/*case CManager::MODE_RANKING:
			CManager::GetRanking()->Draw();
			break;*/
		default:
			break;
		}

		CManager::GetFade()->Draw();

#ifdef _DEBUG
		// �f�o�b�O�\���̕`��
		CDebugproc::Draw();
#endif
		// Direct3D�ɂ��`��I��
		m_pDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt���[�g�o�b�t�@�̓���ւ�
	m_pDevice->Present(NULL, NULL, NULL, NULL);
}

// ------------------------------------------
// �f�o�C�X�擾����
// ------------------------------------------
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pDevice;
}

// ------------------------------------------
// �J�����擾����
// ------------------------------------------
CCamera * CRenderer::GetCamera(void)
{
	return m_pCamera;
}

// ------------------------------------------
// ���C�g�擾����
// ------------------------------------------
CLight * CRenderer::GetLight(void)
{
	return m_pLight;
}

#if _DEBUG
// ------------------------------------------
// FPS�`�揈��
// ------------------------------------------
void CRenderer::DrawFPS(void)
{
	int nCntFPS = GetFPS();

	CDebugproc::Print("FPS:%d\n",nCntFPS);
}
#endif // _DEBUG