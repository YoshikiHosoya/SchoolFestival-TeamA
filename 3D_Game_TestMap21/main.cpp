// =====================================================================================================================================================================
//
// DirectXの処理 [main.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "main.h"			// インクルードファイル
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"

// =====================================================================================================================================================================
// マクロ定義
// =====================================================================================================================================================================
#define CLASS_NAME		"WindowCLASS"			// ウィンドウクラスの名前
#define WINDOW_NAME		"Dlunker"				// キャプション

// =====================================================================================================================================================================
// プロトタイプ宣言
// =====================================================================================================================================================================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

// =====================================================================================================================================================================
// グローバル変数
// =====================================================================================================================================================================
int			g_nFPSCount				= 0;

// =====================================================================================================================================================================
//
// メイン関数
//
// =====================================================================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	// メモリリーク検出
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	//_CrtSetBreakAlloc(151);

		// 変数
	CManager *pManager;

	// マネージャーの生成
	pManager = new CManager;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSEXのメモリサイズ指定
		CS_CLASSDC,							// 表示するウィンドウのスタイル設定
		WindowProc,							// ウィンドウプロシージャのアドレス(関数名)指定
		0,									// 通常は使用しないので0指定
		0,									// 通常は使用しないので0指定
		hInstance,							// Windowsの引数のインスタンスハンドル指定
		LoadIcon(NULL, IDI_APPLICATION),	// タスクバーに使用するアイコン指定
		LoadCursor(NULL, IDC_ARROW),		// 使用するマウスカーソル指定 (変更無用)
		(HBRUSH)(COLOR_WINDOW + 1),			// ウィンドウクライアント領域の色指定
		NULL,								// メニューを指定
		CLASS_NAME,							// ウィンドウクラスの名前
		LoadIcon(NULL, IDI_APPLICATION)		// 小さいアイコンの指定 (変更することもある)
	};

	HWND hWnd;	// ウィンドウハンドル(識別子)
	MSG msg;	// メッセージを格納する変数

	DWORD dwCurrentTime;					// 現在時間
	DWORD dwExeClastTime;					// 最後に処理した時間

	DWORD dwFrameCount;						// 描画回数をカウント
	DWORD dwFPSLastTime;					// FPSを最後に測定した時刻

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hDeskWnd = GetDesktopWindow(); //この関数でデスクトップのハンドルを取得

	// クライアント領域を確保するために必要なウィンドウ座標を計算
	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, FALSE);

	// ウィンドウクラスの登録
	RegisterClassEx(&wcex);

	// ウィンドウの生成
	hWnd = CreateWindowEx(0,				// 拡張ウィンドウスタイル
		CLASS_NAME,							// ウィンドウクラス名
		WINDOW_NAME,						// ウィンドウの名前
		WS_OVERLAPPEDWINDOW,				// ウィンドウスタイル
		CW_USEDEFAULT,						// ウィンドウ左上x座標
		CW_USEDEFAULT,						// ウィンドウ左上y座標
		(rect.right - rect.left),			// ウィンドウの幅
		(rect.bottom - rect.top),			// ウィンドウの高さ
		NULL,								// 親ウィンドウのハンドル
		NULL,								// メニューもしくは子ウィンドウのID
		hInstance,							// インスタンスハンドル
		NULL);								// ウィンドウ作成データ

	// 初期化処理			 
	if (FAILED(pManager->Init(hInstance, hWnd, FALSE)))
	{
		return -1;
	}

	// ウィンドウの表示
	ShowWindow(hWnd, nCmdShow);				// 指定されたウィンドウの表示設定
	UpdateWindow(hWnd);						// ウィンドウのクライアント領域更新

	dwCurrentTime = 0;
	dwExeClastTime = timeGetTime();			// 現在時間を取得

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();			// 現在時間を取得

	// 分解能を設定
	timeBeginPeriod(1);

	// メッセージループ (メッセージキューからメッセージを取得)
	while (1)
	{	// メッセージを取得しなかった場合0を返す
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	// Window処理
			if (msg.message == WM_QUIT)
			{	// WM_QUITメッセージが送られてきたら終了
				break;
			}
			else
			{	// メッセージの翻訳と送出
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	// DirectXの処理
			dwCurrentTime = timeGetTime();							// システム時間取得

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
#ifdef _DEBUG
				g_nFPSCount = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);			// FPSを測定
#endif

				dwFPSLastTime = dwCurrentTime;						// FPSを測定した時刻を保存
				dwFrameCount = 0;									// カウントをクリア
			}

			if ((dwCurrentTime - dwExeClastTime) >= (1000 / 60))	// 1 / 60秒ごとに実行
			{
				dwExeClastTime = dwCurrentTime;						// 処理した時間で保存

				// 更新処理
				pManager->Update();

				// 描画処理
				pManager->Draw();

				// カウントアップ	
				dwFrameCount++;
			}
		}
	}

	if (pManager != NULL)
	{
		// 終了処理
		pManager->Uninit();

		// メモリの開放
		delete pManager;
		pManager = NULL;
	}

	// 分解能を戻す
	timeEndPeriod(1);

	// ウィンドウクラスの登録解除										←[ 登録したら解除 ]
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}
// =====================================================================================================================================================================
//
// ウィンドウのプロシージャ関数
//
// =====================================================================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:	// ウィンドウ破棄メッセージ
		// WM_QUITメッセージを返す
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// キーが押された際のメッセージ
		switch (wParam)
		{
		case VK_ESCAPE:	// [ESC]キーが押された
			// ウィンドウを破棄 (WM_DESTROYを発生)
			DestroyWindow(hWnd);
			break;
		}
		break;

	case WM_ACTIVATEAPP:
		// XInputEnable is implemented by XInput 1.3 and 1.4, but not 9.1.0
		if (wParam == TRUE)
		{
			// App is now active, so re-enable XInput
			XInputEnable(TRUE);
		}
		else
		{
			// App is now inactive, so disable XInput to prevent
			// user input from effecting application and to 
			// disable rumble. 
			XInputEnable(FALSE);
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);// 既定の処理を提供    ←「 必須 」
}

// =====================================================================================================================================================================
//
// FPSの取得
//
// =====================================================================================================================================================================
int  GetFPSCount(void)
{
	return g_nFPSCount;
}
