//=====================================================
//Author : Hnazawa
//[main.cpp]ウィンドウ表示処理
//=====================================================
#define _CRT_SECURE_NO_WARNINGS				// 警告除去
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
//マクロ定義
#define CLASS_NAME		"WindowClass"		//ウィンドウクラスの名前
#define WINDOW_NAME		"MagicKnight"		//キャプション

//プロトタイプ宣言
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int g_nCountFPS;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int Cmdshow)
{
	WNDCLASSEX wcex =
	{
		//WNDCLASSEXのメモリサイズ
		sizeof(WNDCLASSEX),
		//表示するウィンドウのスタイルを設定
		CS_CLASSDC,
		//ウィンドウプロシージャのアドレス
		WindowProc,
		//通常はしないので０
		0,0,
		//Uindowsの引数のインスタンスハンドル指定
		hInstance,
		//タスクバーに使用するアイコンを指定
		LoadIcon(NULL,IDI_APPLICATION),
		//使用するマウスカーソル
		LoadCursor(NULL,IDC_ARROW),
		//ウィンドウクライアント領域の色指定
		(HBRUSH)(COLOR_WINDOW + 1),
		//ウィンドウクラスの名前
		NULL,CLASS_NAME,
		//小さいアイコンの指定
		LoadIcon(NULL,IDI_APPLICATION)
	};
	// ウィンドウハンドル（識別子）
	HWND hWnd;
	//メッセージを格納する変数
	MSG msg;
	//ウィンドウのクラスの登録
	RegisterClassEx(&wcex);
	RECT rect = { 0, 0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	//ウィンドウの生成
	//拡張ウィンドウスタイル
	hWnd = CreateWindowEx(0,			//拡張ウィンドウスタイル
		CLASS_NAME,						//ウィンドウクラス名
		WINDOW_NAME,					//ウィンドウの名前
		WS_OVERLAPPEDWINDOW,			//ウィンドウのスタイル
		CW_USEDEFAULT,					//ウィンドウ左上X座標
		CW_USEDEFAULT,					//ウィンドウ左上Y座標
		(rect.right - rect.left),		//ウィンドウの幅
		(rect.bottom - rect.top),		//ウィンドウの高さ
		NULL,							//親ウィンドウのハンドル
		NULL,							//メニューもしくは子ウィンドウID
		hInstance,						//インスタンスハンドル
		NULL);							//ウィンドウ作成データ
	//ウィンドウの表示
	//指定されたウィンドウの表示設定
	ShowWindow(hWnd, Cmdshow);

	DWORD dwCurrentTime;			//現在時間
	DWORD dwExeclastTime;			//最後に処理した時間
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;
	//変数宣言
	CManager*pManager;
	//メモリ確保
	pManager = new CManager;
	//マウスカーソルを消す
	ShowCursor(TRUE);
	//初期化処理
	if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//ウィンドウの表示
	ShowWindow(hWnd, Cmdshow);
	//ウィンドウのクライアント領域更新
	UpdateWindow(hWnd);
	//分解能を設定
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExeclastTime = timeGetTime();	//現在時間を取得
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//メッセージループ（メッセージキューからメッセージを取得）
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{		//Window処理
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{	//メッセージの翻訳
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{		//DirectXの処理
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)// 1/60秒ごと実行
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
#endif // _DEBUG

				dwFPSLastTime = dwCurrentTime;//処理した時間を保存
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))// 1/60秒ごと実行
			{
				dwExeclastTime = dwCurrentTime;//処理した時間を保存
											   //更新処理
				pManager->Update();
				//描画処理
				pManager->Draw();
				//更新処理
				dwFrameCount++;
			}
		}
	}

	//終了処理
	pManager->Uninit();
	delete pManager;
	////for (int nCnt = 0; nCnt < MAX; nCnt++)
	//{
	//	CScene::RereaseAll();
	//}
	pManager = NULL;
	//分解能を戻す
	timeBeginPeriod(1);
	//ウィンドウクラスの登録を解除:
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}

//ImGui用　これがないとマウス操作できない
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//ウィンドウプロシージャ関数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
	{
		return true;
	}
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
			//[ESC]キーがおされた
		case VK_ESCAPE:
			//nID = MessageBox(hWnd, "チニャホニャジ？", "確認", MB_YESNO);
			//{
			//	if (nID == IDYES)
			//	{
			//ウィンドウを破棄（WM_DESTROYを発生）
			DestroyWindow(hWnd);

			//}
			//if (nID == IDNO)
			//{
			//	break;
			//}
			//}
			break;
		}

	case WM_CLOSE:
		break;
	case WM_DESTROY://終了
					//WM_QUITメッセージを返す
		PostQuitMessage(0);
		break;
	}
	//既定の処理を提供
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int GetFps(void)
{
	return g_nCountFPS;
}
