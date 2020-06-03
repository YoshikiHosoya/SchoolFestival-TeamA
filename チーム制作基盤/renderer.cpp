#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "inputKeyboard.h"
//�v���g�^�C�v�錾
#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;	 // �t�H���g�ւ̃|�C���^
#endif
//=============================================================================
CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
}
//=============================================================================
// ����������
//=============================================================================
HRESULT  CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// �f�B�X�v���C���[�h
	pLight  = new CLight;
	pCamera = new CCamera;
	pDebug  = new CDebugProc;
	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));							// ���[�N���[���N���A
	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;						// �Q�[����ʃT�C�Y(��)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// �Q�[����ʃT�C�Y(����)
	m_d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	m_d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�(�f���M���ɓ���)
	m_d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@(�y�o�b�t�@)�ƃX�e���V���o�b�t�@���쐬
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	m_d3dpp.Windowed = bWindow = TRUE;							// �E�B���h�E���[�h
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g(���݂̑��x�ɍ��킹��)
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��(VSync��҂��ĕ`��)
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �N���C�A���g�̈�𒼂��ɍX�V����

																// Direct3D�f�o�C�X�̐���
																// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			// �f�B�X�v���C�A�_�v�^
		D3DDEVTYPE_HAL,											// �f�o�C�X�^�C�v
		hWnd,													// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
		D3DCREATE_HARDWARE_VERTEXPROCESSING,					// �f�o�C�X�쐬����̑g�ݍ��킹
		&m_d3dpp,													// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
		&g_pD3DDevice)))										// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
	{
		// ��L�̐ݒ肪���s������
		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_d3dpp,
			&g_pD3DDevice)))
		{
			// ��L�̐ݒ肪���s������
			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&m_d3dpp,
				&g_pD3DDevice)))
			{
				// ���������s
				return E_FAIL;
			}
		}
	}
	//�����_���[�X�e�[�g�p�����[�^�[�̐ݒ�
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ����(�����)���J�����O����
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
																			// �T���v���[�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

#ifdef _DEBUG
	D3DXCreateFont(g_pD3DDevice,
		0, 0,
		5, 0,
		false,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "MSE�S�V�b�N",
		&g_pFont);
#endif
	pLight->InitLight();
	pCamera->InitCamera();
	pDebug->Init();

	//����
	ImGui::CreateContext();

	//�f�t�H���g�J���[�ݒ�
	ImGui::StyleColorsDark();

	//������
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(g_pD3DDevice);
	return S_OK;
}
//=============================================================================
//�I������
//=============================================================================
void CRenderer::Uninit(void)
{
	pCamera->UninitCamera();
	pDebug->Uninit();
	CScene::RereaseAll();
	if (g_pD3DDevice != NULL)
	{
		//Direct3D�I�u�W�F�N�g�̊J��
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
#ifdef _DEBUG
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}
#endif // _DEBUG

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}
//=============================================================================
//�X�V����
//=============================================================================
void CRenderer::Update(void)
{
	//ImGui�̍X�V
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool trigger = false;
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	if (key->GetKeyboardTrigger(DIK_F1))
	{
		trigger ^= 1;
	}
	if (trigger == true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		//���C���[�t���[��
	}
	else
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);			//���C���[�t���[���̏�����
	}


	//Scene�ŊǗ����Ă���
	ImGui::Begin("SceneInfo");

	pLight->UpdateLight();
	pCamera->UpdateCamera();
	CScene::UpdateAll();

	//Scene�ŊǗ����Ă��� �I��
	ImGui::End();	//SceneInfo


	//ImGui�@�X�V�I��
	ImGui::EndFrame();

}
//=============================================================================
//�`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	//�o�b�N�o�b�t�@��Z�o�b�t�@��
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//Direct3D�ɂ��`��J�n
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//GetScene()->Drow();
	pCamera->SetCamera();
		CScene::DrawAll();
		pDebug->Draw();
#ifdef _DEBUG
		DrawFPS();

		//ImGui�`��
		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

#endif // _DEBUG

	}
	//Direct3D�ɂ��`��I��
	g_pD3DDevice->EndScene();

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//�f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================================================
//�f�o�C�X���Z�b�g imGui�p�̏����܂�
//=============================================================================
void CRenderer::ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();
	HRESULT hr = g_pD3DDevice->Reset(&m_d3dpp);
	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);
	ImGui_ImplDX9_CreateDeviceObjects();
}

//=============================================================================
//�f�o�b�N�\��
//=============================================================================
#ifdef _DEBUG
void CRenderer::DrawFPS(void)
{
	//CMouse *mouse;
	//mouse = CManager::GetMouse();
	//D3DXVECTOR3 mousePos;
	//if (mouse != NULL)
	//{
	//	mousePos.x = (float)mouse->GetMouseX();
	//	mousePos.y = (float)mouse->GetMouseY();
	//	mousePos.z = 0.0f;
	//}

	////�L���X�g
	//CScene *pScene;
	//pScene = CScene::GetScene(0, CScene3D::OBJTYPE_PLAYER);
	//if (pScene != NULL)
	//{
	//	D3DXVECTOR3 posPlayer = ((CPlayer*)pScene)->GetPosition();
	//	int lifePlayer = ((CPlayer*)pScene)->GetLife();
	//	int nCountFPS = GetFps();
	//	//	D3DXVECTOR3 pos = { 0.0f,0.0f,0.0f };

	//	RECT rect = { 0,300,1280,720 };
	//	char aStr[256];

	//	sprintf(&aStr[0], "FPS:%d\n\nHP:%d\nPOS.x:%f\nPOS.y:%f\nMouse.x:%f\nMouse.y:%f\n", nCountFPS, lifePlayer, posPlayer.x, posPlayer.y, mousePos.x, mousePos.y);
	//	g_pFont->DrawText(NULL,
	//		&aStr[0],
	//		-1,
	//		&rect,
	//		DT_LEFT,
	//		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//}
}
#endif // _DEBUG
