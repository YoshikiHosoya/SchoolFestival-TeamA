// =====================================================================================================================================================================
//
// �����_�����O�̏��� [renderer.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "renderer.h"			// �C���N���[�h�t�@�C��
#include "scene.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "fade.h"
#include "map.h"

// =====================================================================================================================================================================
// �ÓI�����o�ϐ��̏�����
// =====================================================================================================================================================================
CCamera		*CRenderer::m_pCamera	= NULL;
CLight		*CRenderer::m_pLight	= NULL;

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define TEXTURE_FILE		"data/TEXTURE/niq.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����

#define POLY_POSX			(100)			// �摜��x���W
#define POLY_POSY			(100)			// �摜��y���W
#define POLY_SIZEX			(900)			// ���W�̕�
#define POLY_SIZEY			(550)			// ���W�̍���

// =====================================================================================================================================================================
//
// �R���X�g���N�^
//
// =====================================================================================================================================================================
CRenderer::CRenderer()
{
}

// =====================================================================================================================================================================
//
// �f�X�g���N�^
//
// =====================================================================================================================================================================
CRenderer::~CRenderer()
{

}

// =====================================================================================================================================================================
//
// ����������
//
// =====================================================================================================================================================================
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	D3DDISPLAYMODE d3ddm;				// �f�B�X�v���C���[�h

	// �������̊m��
	m_pCamera	= new CCamera;
	m_pLight	= new CLight;
	m_pDebugroc = new CDebugProc;

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
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));						// ���[�N���[���N���A
	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;					// �Q�[����ʃT�C�Y(����)
	m_d3dpp.BackBufferFormat = d3ddm.Format;					// �o�b�N�o�b�t�@�̌`��
	m_d3dpp.BackBufferCount = 1;								// �o�b�N�o�b�t�@�̐�
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	m_d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// 24�r�b�gZ�o�b�t�@8�r�b�g�X�e���V���o�b�t�@�쐬
	m_d3dpp.Windowed = bWindow;									// �E�B���h�E���[�h
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
	////m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��(VSync��҂��ĕ`��)
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �N���C�A���g�̈�𒼂��ɍX�V����

	// Direct3D�f�o�C�X�̐���
	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,											// �f�o�C�X�^�C�v
		hWnd,													// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,					// �f�o�C�X�쐬����̑g�ݍ��킹
		&m_d3dpp,												// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&m_pD3DDevice)))										// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_d3dpp,
			&m_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&m_d3dpp,
				&m_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}

	// �J�����̏�����
	m_pCamera->Init();
	// ���C�g�̏�����
	m_pLight->Init();
	// �f�o�b�O�\���̏�����
	m_pDebugroc->Init();

	// �t�F�[�h�̐���
	m_pFade = CFade::Create();

#ifdef _DEBUG
	// �f�o�b�O�\���p�t�H���g�ݒ�
	D3DXCreateFont(m_pD3DDevice, 18, 9, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "�l�r �S�V�b�N", &m_pFont);
#endif 

	// �����_���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// �J�����O�ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�B�X�e�B�l�[�V�����J���[�̎w��

	// �e�N�X�`���X�e�[�W�X�e�[�g�p�����[�^�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(m_pD3DDevice);
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	return S_OK;
}

// =====================================================================================================================================================================
//
// �I������
//
// =====================================================================================================================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	if (m_pFont != NULL)
	{	// �f�o�b�O�\���p�t�H���g�̊J��
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif 

	if (m_pD3DDevice != NULL)
	{	// Direct3D�f�o�C�X�̊J��
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	if (m_pD3D != NULL)
	{	// Direct3D�I�u�W�F�N�g�̊J��
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	if (m_pDebugroc != NULL)
	{	// �f�o�b�O�\���̏I��
		m_pDebugroc->Uninit();

		// �������̊J��
		delete m_pDebugroc;
		m_pDebugroc = NULL;
	}

	if (m_pCamera != NULL)
	{	// �J�����̏I��
		m_pCamera->Uninit();

		// �������̊J��
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if (m_pLight != NULL)
	{	// ���C�g�̏I��
		m_pLight->Uninit();

		// �������̊J��
		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pFade != NULL)
	{	// �t�F�[�h�̏I��
		m_pFade->Uninit();
		
		// �������̊J��
		delete m_pFade;
		m_pFade = NULL;
	}

	// ImGui�̏I��
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

// =====================================================================================================================================================================
//
// �X�V����
//
// =====================================================================================================================================================================
void CRenderer::Update(void)
{
	static D3DXVECTOR3 pos;
	CManager::MODE Mode = CManager::GetMode();		// ���݂̃��[�h�擾

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// �X�V
	CScene::UpdateAll();

	// �Q�[���̂Ƃ�
	if (Mode == CManager::MODE::GAME)
	{
		// �}�b�v�̍X�V
		CMap::MapUpdate();
	}

	// �J����
	if (m_pCamera != NULL)
	{
		// �X�V����
		m_pCamera->Update();
	}

	// ���C�g
	if (m_pLight != NULL)
	{
		// �X�V����
		m_pLight->Update();
	}

	// �t�F�[�h�̍X�V
	m_pFade->Update();

	// Rendering
	ImGui::EndFrame();
}

// =====================================================================================================================================================================
//
// �`�揈��
//
// =====================================================================================================================================================================
void CRenderer::Draw(void)
{	
	// �o�b�N�o�b�t�@&Z�o�b�t�@&�X�e���V���o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3D�ɂ��`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// �J�����̐ݒ�
		m_pCamera->SetCamera();

		// �S�ĕ`��
		CScene::DrawAll();

		// �t�F�[�h�̕`��
		m_pFade->Draw();

#ifdef _DEBUG
		// FPS�\��
		m_pDebugroc->Print("\nFPS:%d\n", GetFPSCount());

		// �f�o�b�O�\���̕`��
		m_pDebugroc->Draw();

		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
#endif

		// Direct3D�ɂ��`��I��
		m_pD3DDevice->EndScene();
	}

	// �o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	HRESULT result = m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && m_pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();

}

// =====================================================================================================================================================================
//
// �f�o�C�X�̃��Z�b�g
//
// =====================================================================================================================================================================
void CRenderer::ResetDevice(void)
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = m_pD3DDevice->Reset(&m_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}