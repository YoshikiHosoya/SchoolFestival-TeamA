// =====================================================================================================================================================================
//
// レンダリングの処理 [renderer.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "renderer.h"			// インクルードファイル
#include "scene.h"
#include "camera.h"
#include "light.h"
#include "debugproc.h"
#include "fade.h"
#include "map.h"

// =====================================================================================================================================================================
// 静的メンバ変数の初期化
// =====================================================================================================================================================================
CCamera		*CRenderer::m_pCamera	= NULL;
CLight		*CRenderer::m_pLight	= NULL;

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define TEXTURE_FILE		"data/TEXTURE/niq.jpg"	// 読み込むテクスチャファイル名

#define POLY_POSX			(100)			// 画像のx座標
#define POLY_POSY			(100)			// 画像のy座標
#define POLY_SIZEX			(900)			// 座標の幅
#define POLY_SIZEY			(550)			// 座標の高さ

// =====================================================================================================================================================================
//
// コンストラクタ
//
// =====================================================================================================================================================================
CRenderer::CRenderer()
{
}

// =====================================================================================================================================================================
//
// デストラクタ
//
// =====================================================================================================================================================================
CRenderer::~CRenderer()
{

}

// =====================================================================================================================================================================
//
// 初期化処理
//
// =====================================================================================================================================================================
HRESULT CRenderer::Init(HINSTANCE hInstance, HWND hWnd, bool bWindow)
{
	D3DDISPLAYMODE d3ddm;				// ディスプレイモード

	// メモリの確保
	m_pCamera	= new CCamera;
	m_pLight	= new CLight;
	m_pDebugroc = new CDebugProc;

	// Direct3Dオブジェクトの生成
	m_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (m_pD3D == NULL)
	{
		return E_FAIL;
	}

	// 現在のディスプレイモードを取得
	if (FAILED(m_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));						// ワークをゼロクリア
	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;					// ゲーム画面サイズ(高さ)
	m_d3dpp.BackBufferFormat = d3ddm.Format;					// バックバッファの形式
	m_d3dpp.BackBufferCount = 1;								// バックバッファの数
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え(映像信号に同期)
	m_d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;				// 24ビットZバッファ8ビットステンシルバッファ作成
	m_d3dpp.Windowed = bWindow;									// ウィンドウモード
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート(現在の速度に合わせる)
	////m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル(VSyncを待って描画)
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// クライアント領域を直ちに更新する

	// Direct3Dデバイスの生成
	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			// ディスプレイアダプタ
		D3DDEVTYPE_HAL,											// デバイスタイプ
		hWnd,													// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,					// デバイス作成制御の組み合わせ
		&m_d3dpp,												// デバイスのプレゼンテーションパラメータ
		&m_pD3DDevice)))										// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&m_d3dpp,
			&m_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&m_d3dpp,
				&m_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}

	// カメラの初期化
	m_pCamera->Init();
	// ライトの初期化
	m_pLight->Init();
	// デバッグ表示の初期化
	m_pDebugroc->Init();

	// フェードの生成
	m_pFade = CFade::Create();

#ifdef _DEBUG
	// デバッグ表示用フォント設定
	D3DXCreateFont(m_pD3DDevice, 18, 9, 0, 0, FALSE, SHIFTJIS_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "ＭＳ ゴシック", &m_pFont);
#endif 

	// レンダラーステートの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// カリング設定
	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αディスティネーションカラーの指定

	// テクスチャステージステートパラメータの設定
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
// 終了処理
//
// =====================================================================================================================================================================
void CRenderer::Uninit(void)
{
#ifdef _DEBUG
	if (m_pFont != NULL)
	{	// デバッグ表示用フォントの開放
		m_pFont->Release();
		m_pFont = NULL;
	}
#endif 

	if (m_pD3DDevice != NULL)
	{	// Direct3Dデバイスの開放
		m_pD3DDevice->Release();
		m_pD3DDevice = NULL;
	}
	if (m_pD3D != NULL)
	{	// Direct3Dオブジェクトの開放
		m_pD3D->Release();
		m_pD3D = NULL;
	}

	if (m_pDebugroc != NULL)
	{	// デバッグ表示の終了
		m_pDebugroc->Uninit();

		// メモリの開放
		delete m_pDebugroc;
		m_pDebugroc = NULL;
	}

	if (m_pCamera != NULL)
	{	// カメラの終了
		m_pCamera->Uninit();

		// メモリの開放
		delete m_pCamera;
		m_pCamera = NULL;
	}

	if (m_pLight != NULL)
	{	// ライトの終了
		m_pLight->Uninit();

		// メモリの開放
		delete m_pLight;
		m_pLight = NULL;
	}

	if (m_pFade != NULL)
	{	// フェードの終了
		m_pFade->Uninit();
		
		// メモリの開放
		delete m_pFade;
		m_pFade = NULL;
	}

	// ImGuiの終了
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

// =====================================================================================================================================================================
//
// 更新処理
//
// =====================================================================================================================================================================
void CRenderer::Update(void)
{
	static D3DXVECTOR3 pos;
	CManager::MODE Mode = CManager::GetMode();		// 現在のモード取得

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	// 更新
	CScene::UpdateAll();

	// ゲームのとき
	if (Mode == CManager::MODE::GAME)
	{
		// マップの更新
		CMap::MapUpdate();
	}

	// カメラ
	if (m_pCamera != NULL)
	{
		// 更新処理
		m_pCamera->Update();
	}

	// ライト
	if (m_pLight != NULL)
	{
		// 更新処理
		m_pLight->Update();
	}

	// フェードの更新
	m_pFade->Update();

	// Rendering
	ImGui::EndFrame();
}

// =====================================================================================================================================================================
//
// 描画処理
//
// =====================================================================================================================================================================
void CRenderer::Draw(void)
{	
	// バックバッファ&Zバッファ&ステンシルバッファのクリア
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_STENCIL | D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);

	// Direct3Dによる描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		// カメラの設定
		m_pCamera->SetCamera();

		// 全て描画
		CScene::DrawAll();

		// フェードの描画
		m_pFade->Draw();

#ifdef _DEBUG
		// FPS表示
		m_pDebugroc->Print("\nFPS:%d\n", GetFPSCount());

		// デバッグ表示の描画
		m_pDebugroc->Draw();

		ImGui::Render();
		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
#endif

		// Direct3Dによる描画終了
		m_pD3DDevice->EndScene();
	}

	// バックバッファとフロントバッファの入れ替え
	HRESULT result = m_pD3DDevice->Present(NULL, NULL, NULL, NULL);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && m_pD3DDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();

}

// =====================================================================================================================================================================
//
// デバイスのリセット
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