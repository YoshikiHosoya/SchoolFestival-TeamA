#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "inputKeyboard.h"
//プロトタイプ宣言
#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;	 // フォントへのポインタ
#endif		
//=============================================================================
CRenderer::CRenderer()
{
}

CRenderer::~CRenderer()
{
}
//=============================================================================
// 初期化処理
//=============================================================================
HRESULT  CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	D3DPRESENT_PARAMETERS d3dpp;	// プレゼンテーションパラメータ
	pLight  = new CLight;
	pCamera = new CCamera;
	pDebug  = new CDebugProc;
	// Direct3Dオブジェクトの生成
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);
	if (g_pD3D == NULL)
	{
		return E_FAIL;
	}
	// 現在のディスプレイモードを取得
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}
	// デバイスのプレゼンテーションパラメータの設定
	ZeroMemory(&d3dpp, sizeof(d3dpp));							// ワークをゼロクリア
	d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファの形式
	d3dpp.BackBufferCount = 1;									// バックバッファの数
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え(映像信号に同期)
	d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	d3dpp.Windowed = bWindow = TRUE;							// ウィンドウモード
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート(現在の速度に合わせる)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル(VSyncを待って描画)
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// クライアント領域を直ちに更新する

																// Direct3Dデバイスの生成
																// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			// ディスプレイアダプタ
		D3DDEVTYPE_HAL,											// デバイスタイプ
		hWnd,													// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,					// デバイス作成制御の組み合わせ
		&d3dpp,													// デバイスのプレゼンテーションパラメータ
		&g_pD3DDevice)))										// デバイスインターフェースへのポインタ
	{
		// 上記の設定が失敗したら
		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			// 上記の設定が失敗したら
			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				// 初期化失敗
				return E_FAIL;
			}
		}
	}
	//レンダラーステートパラメーターの設定
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面(左回り)をカリングする
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ライティングモード有効

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
																			// サンプラーステートの設定
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//g_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// テクスチャステージステートの設定
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

#ifdef _DEBUG
	D3DXCreateFont(g_pD3DDevice,
		0, 0,
		5, 0,
		false,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "MSEゴシック",
		&g_pFont);
#endif
	pLight->InitLight();
	pCamera->InitCamera();
	pDebug->Init();
	return S_OK;
}
//=============================================================================
//終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
	pCamera->UninitCamera();
	pDebug->Uninit();
	CScene::RereaseAll();
	if (g_pD3DDevice != NULL)
	{
		//Direct3Dオブジェクトの開放
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
}
//=============================================================================
//更新処理
//=============================================================================
void CRenderer::Update(void)
{
	static bool trigger = false;
	CKeyboard *key;
	key = CManager::GetInputKeyboard();
	if (key->GetKeyboardTrigger(DIK_F1))
	{
		trigger ^= 1;
	}
	if (trigger == true)
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		//ワイヤーフレーム	
	}
	else
	{
		g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);			//ワイヤーフレームの初期化
	}
	pLight->UpdateLight();
	pCamera->UpdateCamera();
	CScene::UpdateAll();
}
//=============================================================================
//描画処理
//=============================================================================
void CRenderer::Draw(void)
{
	//バックバッファ＆Zバッファの
	g_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), D3DCOLOR_RGBA(0, 0, 0, 0), 1.0f, 0);
	//Direct3Dによる描画開始
	if (SUCCEEDED(g_pD3DDevice->BeginScene()))
	{
		//GetScene()->Drow();
	pCamera->SetCamera();
		CScene::DrawAll();
		pDebug->Draw();
#ifdef _DEBUG
		DrawFPS();
#endif // _DEBUG

	}
	//Direct3Dによる描画終了
	g_pD3DDevice->EndScene();

	//バックバッファとフロントバッファの入れ替え
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return g_pD3DDevice;
}
//=============================================================================
//デバック表示
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

	////キャスト
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
