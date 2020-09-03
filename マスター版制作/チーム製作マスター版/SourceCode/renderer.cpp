#include "main.h"
#include "scene.h"
#include "renderer.h"
#include "manager.h"
#include "BaseMode.h"
#include "fade.h"
#include "inputKeyboard.h"
//=============================================================================
// マクロ定義
//=============================================================================
#define DEFAULT_BACKCOLOR (D3DXCOLOR(0.0f,0.0f,0.0f,1.0f))
#define SCREEN_LIMIT_COMPLEMENT_VALUE (80.0f)

//プロトタイプ宣言
#ifdef _DEBUG
LPD3DXFONT			g_pFont = NULL;	 // フォントへのポインタ
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
// 初期化処理
//=============================================================================
HRESULT  CRenderer::Init(HWND hWnd, BOOL bWindow)
{
	D3DDISPLAYMODE d3ddm;			// ディスプレイモード
	m_pLight  = new CLight;
	m_pCamera = new CCamera;

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
	ZeroMemory(&m_d3dpp, sizeof(m_d3dpp));							// ワークをゼロクリア
	m_d3dpp.BackBufferWidth = SCREEN_WIDTH;						// ゲーム画面サイズ(幅)
	m_d3dpp.BackBufferHeight = SCREEN_HEIGHT;						// ゲーム画面サイズ(高さ)
	m_d3dpp.BackBufferFormat = d3ddm.Format;						// バックバッファの形式
	m_d3dpp.BackBufferCount = 1;									// バックバッファの数
	m_d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// ダブルバッファの切り替え(映像信号に同期)
	m_d3dpp.EnableAutoDepthStencil = TRUE;						// デプスバッファ(Ｚバッファ)とステンシルバッファを作成
	m_d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
	m_d3dpp.Windowed = bWindow = TRUE;							// ウィンドウモード
	m_d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// リフレッシュレート(現在の速度に合わせる)
	m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// インターバル(VSyncを待って描画)
	//m_d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// クライアント領域を直ちに更新する

																// Direct3Dデバイスの生成
																// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT,			// ディスプレイアダプタ
		D3DDEVTYPE_HAL,											// デバイスタイプ
		hWnd,													// フォーカスするウインドウへのハンドル
		D3DCREATE_HARDWARE_VERTEXPROCESSING,					// デバイス作成制御の組み合わせ
		&m_d3dpp,													// デバイスのプレゼンテーションパラメータ
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
	//レンダラーステートパラメーターの設定
	m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// 裏面(左回り)をカリングする
	m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, TRUE);						// Zバッファを使用
	m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);						// ライティングモード有効

	m_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);				// αブレンドを行う
	m_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);		// αソースカラーの指定
	m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定
																			// サンプラーステートの設定
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	m_pD3DDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	//m_pD3DDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	// テクスチャステージステートの設定
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	// アルファブレンディング処理
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);	// 最初のアルファ引数
	m_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);	// ２番目のアルファ引数

#ifdef _DEBUG
	D3DXCreateFont(m_pD3DDevice,
		0, 0,
		5, 0,
		false,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "MSEゴシック",
		&g_pFont);

	//生成
	ImGui::CreateContext();

	//デフォルトカラー設定
	ImGui::StyleColorsDark();

	//初期化
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
//終了処理
//=============================================================================
void CRenderer::Uninit(void)
{
	CScene::RereaseAll();
	if (m_pD3DDevice != NULL)
	{
		//Direct3Dオブジェクトの開放
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
//更新処理
//=============================================================================
void CRenderer::Update(void)
{
	//スクリーン座標計算
	CalcScreenPos();

#ifdef _DEBUG

	//ImGuiの更新
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
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);		//ワイヤーフレーム
	}
	else
	{
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);			//ワイヤーフレームの初期化
	}



	//Sceneで管理してる情報
	ImGui::Begin("SceneInfo");

	CDebugProc::Print_Left("FPS : [%d]\n", GetFps());

#endif // _DEBUG

	CScene::UpdateAll();
	m_pLight->UpdateLight();
	m_pCamera->UpdateCamera();
	m_pFade->UpdateFade();

#ifdef _DEBUG

	//更新と描画のグラフ
	CScene::ShowUpdateGraph();

	//レンダラー関係のデバッグ情報
	RendererDebugInfo();

	//Sceneのデバッグ情報
	CScene::DebugAll();

	//Sceneで管理してる情報 終了
	ImGui::End();	//SceneInfo

	//BaseModeで管理してるやつの情報
	ImGui::Begin("BaseMode");

	//ポインタ取得
	CBaseMode *pBase = CManager::GetBaseMode();

	//nullcheck
	if (pBase)
	{
		//デバッグ表記
		pBase->DebugCommand();
	}

	//BaseModeで管理してる情報 終了
	ImGui::End();	//BaseMode


	//ImGui　更新終了
	ImGui::EndFrame();

#endif // _DEBUG
}
//=============================================================================
//描画処理
//=============================================================================
void CRenderer::Draw(void)
{
	//バックバッファ＆Zバッファの
	m_pD3DDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), m_BackColor, 1.0f, 0);
	//Direct3Dによる描画開始
	if (SUCCEEDED(m_pD3DDevice->BeginScene()))
	{
		//GetScene()->Drow();
		m_pCamera->SetCamera();
		CScene::DrawAll();
		m_pFade->DrawFade();
#ifdef _DEBUG

		//デバッグ見るかどうか
		if (m_bShowDebug)
		{
			//デバッグ表記
			m_pDebug->Draw();

			//ImGui描画
			ImGui::Render();
			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		}

		//文字列初期化
		m_pDebug->ResetStr();

#endif // _DEBUG

	}
	//Direct3Dによる描画終了
	m_pD3DDevice->EndScene();

	//バックバッファとフロントバッファの入れ替え
	m_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}
//=============================================================================
//デバイスの取得
//=============================================================================
LPDIRECT3DDEVICE9 CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
//=============================================================================
//フェードの取得
//=============================================================================
CFADE * CRenderer::GetFade(void)
{
	return m_pFade;
}
//=============================================================================
//カメラの取得
//=============================================================================
CCamera * CRenderer::GetCamera()
{
	//nullcheck
	if (m_pCamera)
	{
		//return
		return m_pCamera;
	}
	//nullの時はnullptrを返す
	return nullptr;
}
//------------------------------------------------------------------------------
//レンダリングに関する設定
//ある程度処理を纏めておく事で簡略化
//------------------------------------------------------------------------------
void CRenderer::SetRendererCommand(RENDERER_COMMAND Command)
{
	//引数によって処理を変える
	switch (Command)
	{
		//ライティングON
	case CRenderer::RENDERER_LIGHTING_ON:
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
		break;

		//ラインティングOFF
	case CRenderer::RENDERER_LIGHTING_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
		break;

		//カリングしない
	case CRenderer::RENDERER_CULLING_NONE:
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		break;

		//裏面(左回り)をカリングする
	case CRenderer::RENDERER_CULLING_CCW:
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
		break;

		//表面(右回り)をカリングする
	case CRenderer::RENDERER_CULLING_CW:
		m_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
		break;

		//加算合成
	case CRenderer::RENDERER_ALPHABLEND_ADD:
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

		//減算合成 影とか
	case CRenderer::RENDERER_ALPHABLEND_SUB:
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		break;

		//通常合成
	case CRenderer::REDNERER_ALPHABLEND_DEFAULT:
		m_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		m_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		break;

		//Zテスト通常
	case CRenderer::RENDERER_ZTEST_DEFAULT:
		m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		break;

		//Zテスト無効
	case CRenderer::RENDERER_ZTEST_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
		break;

		//Zテスト無効&&Zライティング有効
	case CRenderer::RENDERER_ZTEST_OFF_ZWRITING_ON:
		m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_FALSE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		break;

		//Zテスト有効&&Zライティング無効
	case CRenderer::RENDERER_ZTEST_ON_ZWRITING_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
		m_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, D3DZB_FALSE);
		m_pD3DDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
		break;

		//フォグON
	case CRenderer::RENDERER_FOG_ON:
		m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, TRUE);
		break;

		//フォグOFF
	case CRenderer::RENDERER_FOG_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_FOGENABLE, FALSE);
		break;

		//ワイヤーON
	case CRenderer::RENDERER_WIRE_ON:
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		break;

		//ワイヤーOFF
	case CRenderer::RENDERER_WIRE_OFF:
		m_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		break;

	default:
		break;
	}
}
//=============================================================================
//画面遷移したときにレンダラーに関する情報をリセットする
//=============================================================================
void CRenderer::ResetRenderer()
{
	//カメラの情報リセット 初期情報入れる場合はMode側でやって
	m_pCamera->ResetCamera();

	//シーンの一時停止とか解除
	CScene::SetStopFlag(false);

	//レンダラー設定
	SetRendererCommand(CRenderer::RENDERER_LIGHTING_ON);
	SetRendererCommand(CRenderer::RENDERER_CULLING_CCW);
	SetRendererCommand(CRenderer::RENDERER_ZTEST_DEFAULT);
	SetRendererCommand(CRenderer::REDNERER_ALPHABLEND_DEFAULT);
	SetRendererCommand(CRenderer::RENDERER_WIRE_OFF);

}
//=============================================================================
//スクリーン座標をワールド座標に変換
//=============================================================================
D3DXMATRIX * CRenderer::CalcInvMtx(D3DXMATRIX *pOutInvMtx,int nScreen_Width, int nScreen_Height, D3DXMATRIX * pMtxView, D3DXMATRIX * pMtxPrj)
{
	//変数宣言　逆行列
	D3DXMATRIX InvView, InvPrj, Viewport, InvViewport;

	//逆行列を算出
	D3DXMatrixInverse(&InvView, NULL, pMtxView);
	D3DXMatrixInverse(&InvPrj, NULL, pMtxPrj);

	//初期化
	D3DXMatrixIdentity(&Viewport);

	//スクリーンの大きさを基にビューポート作成
	Viewport._11 = nScreen_Width / 2.0f; Viewport._22 = -nScreen_Height / 2.0f;
	Viewport._41 = nScreen_Width / 2.0f; Viewport._42 = nScreen_Height / 2.0f;

	//ビューポートの逆行列算出
	D3DXMatrixInverse(&InvViewport, NULL, &Viewport);

	//逆行列の計算
	*pOutInvMtx = InvViewport * InvPrj * InvView;

	//return
	return pOutInvMtx;
}
//=============================================================================
//スクリーン座標をワールド座標に変換
//=============================================================================
D3DXVECTOR3 *CRenderer::CalcScreenToWorld(D3DXVECTOR3 * pout, int nScreenPos_X, int nScreenPos_Y, float fScreenPos_Z, D3DXMATRIX * pInvMtx)
{
	//逆行列の計算でワールド座標算出
	D3DXVec3TransformCoord(pout, &D3DXVECTOR3((float)nScreenPos_X, (float)nScreenPos_Y, fScreenPos_Z), pInvMtx);

	return pout;
}
//=============================================================================
//スクリーンの中かどうか確認
//=============================================================================
bool CRenderer::CheckScreenRange(D3DXVECTOR3 const &pos)
{
	//画面の範囲内であれば描画
	//それ以外は描画しない
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
//スクリーンの中に収めるようにする
//=============================================================================
void CRenderer::ScreenLimitRange(D3DXVECTOR3 &pos)
{
	//画面の範囲内になるように描画
	CHossoLibrary::RangeLimit_Equal(pos.x, m_MinScreenPos.x + SCREEN_LIMIT_COMPLEMENT_VALUE, m_MaxScreenPos.x - SCREEN_LIMIT_COMPLEMENT_VALUE);
}
//=============================================================================
//デバイスリセット imGui用の処理含む
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
//デバイスリセット imGui用の処理含む
//=============================================================================
void CRenderer::RendererDebugInfo()
{
	ImGui::Begin("RendererInfo");

	//背景色
	//D3DXCLORではImGui対応していないのでfloat型にキャスト
	float *pCol = m_BackColor;

	//項目の大きさ設定
	ImGui::SetNextItemWidth(250);

	//色の設定
	ImGui::ColorEdit4("BackColor", pCol);

	ImGui::End();	//RendererInfo
}

//=============================================================================
//スクリーンの最少頂点と最大頂点求める
//=============================================================================
void CRenderer::CalcScreenPos()
{
	//変数宣言
	D3DXMATRIX InvMtx;
	D3DXVECTOR3 nearpos, farpos;
	float fScreenZValue = 1.0f - ((m_pCamera->GetPosV().z + m_pCamera->GetFar()) / m_pCamera->GetFar());

	//Valueが0から1の範囲に収まるように
	CHossoLibrary::RangeLimit_Equal(fScreenZValue, 0.0f, 1.0f);


	//逆行列計算
	CalcInvMtx(&InvMtx, SCREEN_WIDTH, SCREEN_HEIGHT, m_pCamera->GetViewMtxPtr(), m_pCamera->GetProjMtxPtr());

	//最小値の計算
	CalcScreenToWorld(&nearpos, 0, SCREEN_HEIGHT, 0.0f, &InvMtx);
	CalcScreenToWorld(&farpos, 0, SCREEN_HEIGHT, 1.0f, &InvMtx);
	m_MinScreenPos = nearpos + ((farpos - nearpos) * fScreenZValue);

	//最大値の計算
	CalcScreenToWorld(&nearpos, SCREEN_WIDTH, 0, 0.0f, &InvMtx);
	CalcScreenToWorld(&farpos, SCREEN_WIDTH, 0, 1.0f, &InvMtx);
	m_MaxScreenPos = nearpos + ((farpos - nearpos) * fScreenZValue);

	//debug
	CDebugProc::Print_Left("ZValue >> %.2f\n", fScreenZValue);
	CDebugProc::Print_Left("ScreenPosMin >> %.2f,%.2f,%.2f\n", m_MinScreenPos.x, m_MinScreenPos.y, m_MinScreenPos.z);
	CDebugProc::Print_Left("ScreenPosMax >> %.2f,%.2f,%.2f\n", m_MaxScreenPos.x, m_MaxScreenPos.y, m_MaxScreenPos.z);
}

