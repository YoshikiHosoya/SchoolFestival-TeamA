//------------------------------------------------------------------------------
//
//�����_���[����  [renderer.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#define _CRT_SECURE_NO_WARNINGS

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include <stdio.h>
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"
#include "keyboard.h"
#include "fade.h"
#include "camera.h"
#include "basemode.h"
#include "particle.h"
#include "light.h"

//------------------------------------------------------------------------------
//�}�N��
//------------------------------------------------------------------------------
#define BACK_COLOR (D3DCOLOR_RGBA(0, 0, 0, 0))
#define FOG_COLOR (D3DCOLOR_RGBA(45, 45, 45, 0))

//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
D3DXCOLOR CRenderer::m_BackColor = BACK_COLOR;

//------------------------------------------------------------------------------
//�R���X�g���N�^
//------------------------------------------------------------------------------
CRenderer::CRenderer()
{
	//������
	m_pD3D = nullptr;
	m_pD3DDevice = nullptr;
	m_pCamera = nullptr;
	m_pDebugProc = nullptr;
	m_pLight = nullptr;
	m_bDispDebugProcInfo = true;
	m_bDispImGuiInfo = true;
}
//------------------------------------------------------------------------------
//�f�X�g���N�^
//------------------------------------------------------------------------------
CRenderer::~CRenderer()
{
	if (m_pD3DDevice)
	{	//Direct3D�f�o�C�X�̊J��
		m_pD3DDevice->Release();
		m_pD3DDevice = nullptr;
	}

	if (m_pD3D)
	{	//Direct3D�I�u�W�F�N�g�̊J��
		m_pD3D->Release();
		m_pD3D = nullptr;
	}
	m_pCamera.reset();
	m_pDebugProc.reset();
	m_pLight.reset();


}
//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	m_pDebugProc.reset(new CDebugProc);
	m_pCamera.reset(new CCamera);
	m_pLight.reset(new CLight);

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
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));							// ���[�N���[���N���A
	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;							// �Q�[����ʃT�C�Y(��)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	m_d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	m_d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;						// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	m_d3dpp.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;					// �f�v�X�o�b�t�@�Ƃ���24bit���g��	�X�e���V���o�b�t�@�𗘗p����� Z�o�b�t�@��24bit �X�e���V���o�b�t�@��8bit
	m_d3dpp.Windowed = bWindow;										// �E�B���h�E���[�h
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT	;	// �C���^�[�o��(VSync��҂��ĕ`��)
																	//	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �N���C�A���g�̈�𒼂��ɍX�V����


																//�f�v�X�X�e���V���t�H�[�}�b�g��ύX
																// Direct3D�f�o�C�X�̐���
																// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,											// �f�o�C�X�^�C�v
		hWnd,													// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,					// �f�o�C�X�쐬����̑g�ݍ��킹
		&m_d3dpp,													// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
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
				//���������s
				return E_FAIL;
			}
		}
	}
	//�����_���[�X�e�[�g�ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);							// ����(�����)���J�����O����
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);									// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);									// ���C�e�B���O���[�h�L��
	m_pD3DDevice->SetRenderState(D3DRS_SPECULARENABLE, TRUE);							// �X�y�L�����[�̗L��
	m_pD3DDevice->SetRenderState(D3DRS_EMISSIVEMATERIALSOURCE, D3DMCS_MATERIAL);		// �G�~�b�V�����̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);							// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);					// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);				// ���f�X�e�B�l�[�V�����J���[�̎w��.
	m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);						// �h��Ԃ����[�h�ݒ�

	// �X�e���V���o�b�t�@�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_NOTEQUAL);
	m_pD3DDevice->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
	m_pD3DDevice->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
	m_pD3DDevice->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_REPLACE);

	// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);

	//�t�H�O�̐ݒ�
	float fStart = 1000.0f;
	float fEnd = 3500.0f;
	m_pD3DDevice->SetRenderState(D3DRS_FOGCOLOR, FOG_COLOR);					// �J���[�ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_NONE);				// ���_���[�h
	m_pD3DDevice->SetRenderState(D3DRS_FOGTABLEMODE, D3DFOG_LINEAR);			// �e�[�u�����[�h
	m_pD3DDevice->SetRenderState(D3DRS_FOGSTART, *(DWORD*)(&fStart));			// �J�n�ʒu
	m_pD3DDevice->SetRenderState(D3DRS_FOGEND, *(DWORD*)(&fEnd));				// �I���ʒu

	// �A���t�@
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);


	//�t�F�[�h�̐���
	m_pFade = CFade::Create();

	//������
	m_pDebugProc->Init(hWnd);
	m_pCamera->Init();
	m_pLight->Init();

	return S_OK;
}
//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CRenderer::Uninit()
{

}
//------------------------------------------------------------------------------
//�X�V����
//------------------------------------------------------------------------------
void CRenderer::Update()
{
#ifdef _DEBUG

	//ImGui�̍X�V
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

#endif	//DEBUG
	//�I�u�W�F�N�g�̍X�V
	CScene::UpdateAll();
	m_pCamera->Update();

	//�X�V
	m_pFade->Update();
	m_pLight->Update();

#ifdef _DEBUG

	//Scene�ŊǗ����Ă��̏��
	ImGui::Begin("SceneInfo");

	//�I�u�W�F�N�g�̍X�V
	CScene::ShowDebugInfoAll();

	//scene�֌W�̏I��
	ImGui::End();

	//BaseMode�ŊǗ����Ă��̏��
	ImGui::Begin("BaseMode");

	CBaseMode *pBase = CManager::GetBaseMode();

	//nullcheck
	if (pBase)
	{
		//�f�o�b�O�\�L
		pBase->DebugCommand();
	}

	//BaseMode�֌W�̏I��
	ImGui::End();

	//���
	ImGui::PushStyleColor(ImGuiCol_TitleBgActive, ImVec4(0.0f, 0.7f, 0.2f, 1.0f));
	ImGui::PushStyleColor(ImGuiCol_TitleBg, ImVec4(0.0f, 0.3f, 0.1f, 1.0f));

	//�����_���[�ŊǗ����Ă��̏��
	ImGui::Begin("DebugInfo");

	//Imgui�̃f�o�b�O���\��
	m_pCamera->ShowCameraInfo();
	m_pLight->ShowLightInfo();

	//�f�o�b�O�̃R�}���h
	CHossoLibrary::ShowDebugInfo();

	//�f�o�b�O
	CScene::ShowNumAll();

	//�����_���[�֌W�̏I��
	ImGui::End();

	//�|�b�v�̐F��񏉊���
	ImGui::PopStyleColor();
	ImGui::PopStyleColor();

	ImGui::EndFrame();//�X�V�����̏I����
#endif	//DEBUG
}
//------------------------------------------------------------------------------
//�`�揈��
//------------------------------------------------------------------------------
void CRenderer::Draw()
{
	//�o�b�N�o�b�t�@ & Z�o�b�t�@ & �X�e���V���o�b�t�@�̃N���A
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL), m_BackColor, 1.0f, 0);

	//Direct3D�ɂ��`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//�J�����Z�b�g
		m_pCamera->SetCamera();

		//�I�u�W�F�N�g�̕`��
		CScene::DrawAll();

		m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);						// �t�H�Ooff

		//�t�F�[�h�̕`��
		m_pFade->Draw();


#ifdef _DEBUG
		//DebugProc�̏��\�����鎞
		if (m_bDispDebugProcInfo)
		{
			//�f�o�b�O�e�L�X�g�̕\��
			CDebugProc::Draw();
		}

		//ImGui�̏��\�����鎞
		if(m_bDispImGuiInfo)
		{
			//���C���[�t���[��off�ɂ���
			SetRendererCommand(RENDERER_WIRE_OFF);

			//�ʏ�`��
			m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

			//ImGui�`��
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

		}

		//debugproc�p�̕�����J��
		CDebugProc::ResetStr();

		//���C���[�t���[���`��̎��͌��ɖ߂�
		CHossoLibrary::CheckWireMode();
#endif	//DEBUG

		//Direct3D�ɂ��`��A�I��
		m_pD3DDevice->EndScene();
	}

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	HRESULT result = m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

#ifdef _DEBUG

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && m_pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
	{
		ResetDevice();
	}
#endif	//DEBUG
}
void CRenderer::SetRendererCommand(RENDERER_COMMAND Command)
{
	switch (Command)
	{
		//���C�e�B���OON
	case CRenderer::RENDERER_LIGHTING_ON:
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		break;

		//���C���e�B���OOFF
	case CRenderer::RENDERER_LIGHTING_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		break;

		//�J�����O���Ȃ�
	case CRenderer::RENDERER_CULLING_NONE:
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		break;

		//����(�����)���J�����O����
	case CRenderer::RENDERER_CULLING_CCW:
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		break;

		//�\��(�E���)���J�����O����
	case CRenderer::RENDERER_CULLING_CW:
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		break;

		//���Z����
	case CRenderer::RENDERER_ALPHABLEND_ADD:
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

		//���Z���� �e�Ƃ�
	case CRenderer::RENDERER_ALPHABLEND_SUB:
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

		//�ʏ퍇��
	case CRenderer::REDNERER_ALPHABLEND_DEFAULT:
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;

		//Z�e�X�g�ʏ�
	case CRenderer::RENDERER_ZTEST_DEFAULT:
		m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		break;

		//Z�e�X�g����
	case CRenderer::RENDERER_ZTEST_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
		break;

		//Z�e�X�g����&&Z���C�e�B���O�L��
	case CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON:
		m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		break;

		//Z�e�X�g�L��&&Z���C�e�B���O����
	case CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
		m_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		break;

		//�t�H�OON
	case CRenderer::RENDERER_FOG_ON:
		m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
		break;

		//�t�H�OOFF
	case CRenderer::RENDERER_FOG_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		break;

		//���C���[ON
	case CRenderer::RENDERER_WIRE_ON:
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		break;

		//���C���[OFF
	case CRenderer::RENDERER_WIRE_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		break;

	default:
		break;
	}
}
//------------------------------------------------------------------------------
//���[�h���J�ڂ����Ƃ��Ƀ����_���[�Ɋւ�����̏�����������
//------------------------------------------------------------------------------
void CRenderer::ResetRenderer()
{
	//�J�����̏�񃊃Z�b�g �����������ꍇ��Mode���ł����
	m_pCamera->ResetCamera();

	//�V�[���̈ꎞ��~�Ƃ�����
	CScene::SetStop(false);

	//�����_���[�ݒ�
	SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);
	SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);
	SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);
	SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
	SetRendererCommand(CRenderer::RENDERER_WIRE_OFF);

}
//------------------------------------------------------------------------------
//�f�o�C�X���Z�b�g
//------------------------------------------------------------------------------
void CRenderer::ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = m_pD3DDevice->Reset(&m_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

//------------------------------------------------------------------------------
//�����_���[�̃f�o�b�O���ݒ�
//------------------------------------------------------------------------------
void CRenderer::RendererDebugInfo()
{
	ImGui::Begin("RendererInfo");

	//�w�i�F
	//D3DXCLOR�ł�ImGui�Ή����Ă��Ȃ��̂�float�^�ɃL���X�g
	float *pCol = m_BackColor;

	//���ڂ̑傫���ݒ�
	ImGui::SetNextItemWidth(250);

	//�F�̐ݒ�
	ImGui::ColorEdit4("BackColor", pCol);

	ImGui::End();	//RendererInfo
}