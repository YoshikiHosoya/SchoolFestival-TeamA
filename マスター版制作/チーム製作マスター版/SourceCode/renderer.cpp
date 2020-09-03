#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "BaseMode.h"
#include "fade.h"
#include "inputKeyboard.h"
//=============================================================================
// �}�N����`
//=============================================================================
#define DEFAULT_BACKCOLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define SCREEN_LIMIT_COMPLEMENT_VALUE (80.0f)

//�v���g�^�C�v�錾
#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;	 // �t�H���g�ւ̃|�C���^
#endif
//=============================================================================
CRenderer::CRenderer()
{
	m_bShowDebug = true;
	m_BackColor = DEFAULT_BACKCOLOR;
	m_MaxScreenPos = ZeroVector3;
	m_MinScreenPos = ZeroVector3;
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
	m_pLight  = new CLight;
	m_pCamera = new CCamera;

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
	//m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �N���C�A���g�̈�𒼂��ɍX�V����

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
				// ���������s
				return E_FAIL;
			}
		}
	}
	//�����_���[�X�e�[�g�p�����[�^�[�̐ݒ�
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ����(�����)���J�����O����
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Z�o�b�t�@���g�p
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ���C�e�B���O���[�h�L��

	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// ���u�����h���s��
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// ���\�[�X�J���[�̎w��
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��
																			// �T���v���[�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// �A���t�@�u�����f�B���O����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// �ŏ��̃A���t�@����
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// �Q�Ԗڂ̃A���t�@����

#ifdef _DEBUG
	D3DXCreateFont(m_pD3DDevice,
		0, 0,
		5, 0,
		false,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "MSE�S�V�b�N",
		&g_pFont);

	//����
	ImGui::CreateContext();

	//�f�t�H���g�J���[�ݒ�
	ImGui::StyleColorsDark();

	//������
	ImGui_ImplWin32_Init(hWnd);
	ImGui_ImplDX9_Init(m_pD3DDevice);

	//DebugProc
	m_pDebug = new CDebugProc;
	m_pDebug->Init();
#endif

	m_pLight->InitLight();
	m_pCamera->InitCamera();
	m_pFade = CFADE::CreateFade();

	return S_OK;
}
//=============================================================================
//�I������
//=============================================================================
void CRenderer::Uninit(void)
{
	CScene::RereaseAll();
	if (m_pD3DDevice != NULL)
	{
		//Direct3D�I�u�W�F�N�g�̊J��
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	if (m_pD3D != NULL)
	{
		m_pD3D->Release();
		m_pD3D = NULL;
	}
	if (m_pCamera != nullptr)
	{
		m_pCamera->UninitCamera();
		delete m_pCamera;
		m_pCamera = nullptr;
	}
	if (m_pFade != nullptr)
	{
		m_pFade->UninitFade();
		delete m_pFade;
		m_pFade = nullptr;
	}
	if (m_pDebug != nullptr)
	{
		m_pDebug->Uninit();
		delete m_pDebug;
		m_pDebug = nullptr;
	}
	if (m_pLight != nullptr)
	{
		m_pLight->UninitLight();
		delete m_pLight;
		m_pLight = nullptr;
	}
#ifdef _DEBUG
	if (g_pFont != NULL)
	{
		g_pFont->Release();
		g_pFont = NULL;
	}

	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
#endif // _DEBUG
}
//=============================================================================
//�X�V����
//=============================================================================
void CRenderer::Update(void)
{
	//�X�N���[�����W�v�Z
	CalcScreenPos();

#ifdef _DEBUG

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
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		//���C���[�t���[��
	}
	else
	{
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);			//���C���[�t���[���̏�����
	}



	//Scene�ŊǗ����Ă���
	ImGui::Begin("SceneInfo");

	CDebugProc::Print_Left("FPS : [%d]\n", GetFps());

#endif // _DEBUG

	CScene::UpdateAll();
	m_pLight->UpdateLight();
	m_pCamera->UpdateCamera();
	m_pFade->UpdateFade();

#ifdef _DEBUG

	//�X�V�ƕ`��̃O���t
	CScene::ShowUpdateGraph();

	//�����_���[�֌W�̃f�o�b�O���
	RendererDebugInfo();

	//Scene�̃f�o�b�O���
	CScene::DebugAll();

	//Scene�ŊǗ����Ă��� �I��
	ImGui::End();	//SceneInfo

	//BaseMode�ŊǗ����Ă��̏��
	ImGui::Begin("BaseMode");

	//�|�C���^�擾
	CBaseMode *pBase = CManager::GetBaseMode();

	//nullcheck
	if (pBase)
	{
		//�f�o�b�O�\�L
		pBase->DebugCommand();
	}

	//BaseMode�ŊǗ����Ă��� �I��
	ImGui::End();	//BaseMode


	//ImGui�@�X�V�I��
	ImGui::EndFrame();

#endif // _DEBUG
}
//=============================================================================
//�`�揈��
//=============================================================================
void CRenderer::Draw(void)
{
	//�o�b�N�o�b�t�@��Z�o�b�t�@��
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), m_BackColor, 1.0f, 0);
	//Direct3D�ɂ��`��J�n
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//GetScene()->Drow();
		m_pCamera->SetCamera();
		CScene::DrawAll();
		m_pFade->DrawFade();
#ifdef _DEBUG

		//�f�o�b�O���邩�ǂ���
		if (m_bShowDebug)
		{
			//�f�o�b�O�\�L
			m_pDebug->Draw();

			//ImGui�`��
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		}

		//�����񏉊���
		m_pDebug->ResetStr();

#endif // _DEBUG

	}
	//Direct3D�ɂ��`��I��
	m_pD3DDevice->EndScene();

	//�o�b�N�o�b�t�@�ƃt�����g�o�b�t�@�̓���ւ�
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//�f�o�C�X�̎擾
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
//=============================================================================
//�t�F�[�h�̎擾
//=============================================================================
CFADE * CRenderer::GetFade(void)
{
	return m_pFade;
}
//=============================================================================
//�J�����̎擾
//=============================================================================
CCamera * CRenderer::GetCamera()
{
	//nullcheck
	if (m_pCamera)
	{
		//return
		return m_pCamera;
	}
	//null�̎���nullptr��Ԃ�
	return nullptr;
}
//------------------------------------------------------------------------------
//�����_�����O�Ɋւ���ݒ�
//������x������Z�߂Ă������Ŋȗ���
//------------------------------------------------------------------------------
void CRenderer::SetRendererCommand(RENDERER_COMMAND Command)
{
	//�����ɂ���ď�����ς���
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
//=============================================================================
//��ʑJ�ڂ����Ƃ��Ƀ����_���[�Ɋւ���������Z�b�g����
//=============================================================================
void CRenderer::ResetRenderer()
{
	//�J�����̏�񃊃Z�b�g �����������ꍇ��Mode���ł����
	m_pCamera->ResetCamera();

	//�V�[���̈ꎞ��~�Ƃ�����
	CScene::SetStopFlag(false);

	//�����_���[�ݒ�
	SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);
	SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);
	SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);
	SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
	SetRendererCommand(CRenderer::RENDERER_WIRE_OFF);

}
//=============================================================================
//�X�N���[�����W�����[���h���W�ɕϊ�
//=============================================================================
D3DXMATRIX * CRenderer::CalcInvMtx(D3DXMATRIX *pOutInvMtx,int nScreen_Width, int nScreen_Height, D3DXMATRIX * pMtxView, D3DXMATRIX * pMtxPrj)
{
	//�ϐ��錾�@�t�s��
	D3DXMATRIX InvView, InvPrj, Viewport, InvViewport;

	//�t�s����Z�o
	D3DXMatrixInverse(&InvView, NULL, pMtxView);
	D3DXMatrixInverse(&InvPrj, NULL, pMtxPrj);

	//������
	D3DXMatrixIdentity(&Viewport);

	//�X�N���[���̑傫������Ƀr���[�|�[�g�쐬
	Viewport._11 = nScreen_Width / 2.0f; Viewport._22 = -nScreen_Height / 2.0f;
	Viewport._41 = nScreen_Width / 2.0f; Viewport._42 = nScreen_Height / 2.0f;

	//�r���[�|�[�g�̋t�s��Z�o
	D3DXMatrixInverse(&InvViewport, NULL, &Viewport);

	//�t�s��̌v�Z
	*pOutInvMtx = InvViewport * InvPrj * InvView;

	//return
	return pOutInvMtx;
}
//=============================================================================
//�X�N���[�����W�����[���h���W�ɕϊ�
//=============================================================================
D3DXVECTOR3 *CRenderer::CalcScreenToWorld(D3DXVECTOR3 * pout, int nScreenPos_X, int nScreenPos_Y, float fScreenPos_Z, D3DXMATRIX * pInvMtx)
{
	//�t�s��̌v�Z�Ń��[���h���W�Z�o
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3((float)nScreenPos_X, (float)nScreenPos_Y, fScreenPos_Z), pInvMtx);

	return pout;
}
//=============================================================================
//�X�N���[���̒����ǂ����m�F
//=============================================================================
bool CRenderer::CheckScreenRange(D3DXVECTOR3 const &pos)
{
	//��ʂ͈͓̔��ł���Ε`��
	//����ȊO�͕`�悵�Ȃ�
	if (pos.x > m_MinScreenPos.x - SCREEN_LIMIT_COMPLEMENT_VALUE &&
		pos.x < m_MaxScreenPos.x + SCREEN_LIMIT_COMPLEMENT_VALUE &&
		pos.y > m_MinScreenPos.y - SCREEN_LIMIT_COMPLEMENT_VALUE &&
		pos.y < m_MaxScreenPos.y + SCREEN_LIMIT_COMPLEMENT_VALUE)
	{
		return true;
	}
	else
	{
		return  false;
	}
}
//=============================================================================
//�X�N���[���̒��Ɏ��߂�悤�ɂ���
//=============================================================================
void CRenderer::ScreenLimitRange(D3DXVECTOR3 &pos)
{
	//��ʂ͈͓̔��ɂȂ�悤�ɕ`��
	CHossoLibrary::RangeLimit_Equal(pos.x, m_MinScreenPos.x + SCREEN_LIMIT_COMPLEMENT_VALUE, m_MaxScreenPos.x - SCREEN_LIMIT_COMPLEMENT_VALUE);
}
//=============================================================================
//�f�o�C�X���Z�b�g imGui�p�̏����܂�
//=============================================================================
void CRenderer::ResetDevice()
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	HRESULT hr = m_pD3DDevice->Reset(&m_d3dpp);

	if (hr == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

//=============================================================================
//�f�o�C�X���Z�b�g imGui�p�̏����܂�
//=============================================================================
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

//=============================================================================
//�X�N���[���̍ŏ����_�ƍő咸�_���߂�
//=============================================================================
void CRenderer::CalcScreenPos()
{
	//�ϐ��錾
	D3DXMATRIX InvMtx;
	D3DXVECTOR3 nearpos, farpos;
	float fScreenZValue = 1.0f - ((m_pCamera->GetPosV().z + m_pCamera->GetFar()) / m_pCamera->GetFar());

	//Value��0����1�͈̔͂Ɏ��܂�悤��
	CHossoLibrary::RangeLimit_Equal(fScreenZValue, 0.0f, 1.0f);


	//�t�s��v�Z
	CalcInvMtx(&InvMtx, SCREEN_WIDTH, SCREEN_HEIGHT, m_pCamera->GetViewMtxPtr(), m_pCamera->GetProjMtxPtr());

	//�ŏ��l�̌v�Z
	CalcScreenToWorld(&nearpos, 0, SCREEN_HEIGHT, 0.0f, &InvMtx);
	CalcScreenToWorld(&farpos, 0, SCREEN_HEIGHT, 1.0f, &InvMtx);
	m_MinScreenPos = nearpos + ((farpos - nearpos) * fScreenZValue);

	//�ő�l�̌v�Z
	CalcScreenToWorld(&nearpos, SCREEN_WIDTH, 0, 0.0f, &InvMtx);
	CalcScreenToWorld(&farpos, SCREEN_WIDTH, 0, 1.0f, &InvMtx);
	m_MaxScreenPos = nearpos + ((farpos - nearpos) * fScreenZValue);

	//debug
	CDebugProc::Print_Left("ZValue >> %.2f\n", fScreenZValue);
	CDebugProc::Print_Left("ScreenPosMin >> %.2f,%.2f,%.2f\n", m_MinScreenPos.x, m_MinScreenPos.y, m_MinScreenPos.z);
	CDebugProc::Print_Left("ScreenPosMax >> %.2f,%.2f,%.2f\n", m_MaxScreenPos.x, m_MaxScreenPos.y, m_MaxScreenPos.z);
}

