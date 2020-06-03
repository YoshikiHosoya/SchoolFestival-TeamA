//=====================================================
//Author : Hnazawa
//[main.cpp]�E�B���h�E�\������
//=====================================================
#define _CRT_SECURE_NO_WARNINGS				// �x������
#include "main.h"
#include "renderer.h"
#include "scene.h"
#include "manager.h"
//�}�N����`
#define CLASS_NAME		"WindowClass"		//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME		"MagicKnight"		//�L���v�V����

//�v���g�^�C�v�錾
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int g_nCountFPS;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int Cmdshow)
{
	WNDCLASSEX wcex =
	{
		//WNDCLASSEX�̃������T�C�Y
		sizeof(WNDCLASSEX),
		//�\������E�B���h�E�̃X�^�C����ݒ�
		CS_CLASSDC,
		//�E�B���h�E�v���V�[�W���̃A�h���X
		WindowProc,
		//�ʏ�͂��Ȃ��̂łO
		0,0,
		//Uindows�̈����̃C���X�^���X�n���h���w��
		hInstance,
		//�^�X�N�o�[�Ɏg�p����A�C�R�����w��
		LoadIcon(NULL,IDI_APPLICATION),
		//�g�p����}�E�X�J�[�\��
		LoadCursor(NULL,IDC_ARROW),
		//�E�B���h�E�N���C�A���g�̈�̐F�w��
		(HBRUSH)(COLOR_WINDOW + 1),
		//�E�B���h�E�N���X�̖��O
		NULL,CLASS_NAME,
		//�������A�C�R���̎w��
		LoadIcon(NULL,IDI_APPLICATION)
	};
	// �E�B���h�E�n���h���i���ʎq�j
	HWND hWnd;
	//���b�Z�[�W���i�[����ϐ�
	MSG msg;
	//�E�B���h�E�̃N���X�̓o�^
	RegisterClassEx(&wcex);
	RECT rect = { 0, 0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	//�E�B���h�E�̐���
	//�g���E�B���h�E�X�^�C��
	hWnd = CreateWindowEx(0,			//�g���E�B���h�E�X�^�C��
		CLASS_NAME,						//�E�B���h�E�N���X��
		WINDOW_NAME,					//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			//�E�B���h�E�̃X�^�C��
		CW_USEDEFAULT,					//�E�B���h�E����X���W
		CW_USEDEFAULT,					//�E�B���h�E����Y���W
		(rect.right - rect.left),		//�E�B���h�E�̕�
		(rect.bottom - rect.top),		//�E�B���h�E�̍���
		NULL,							//�e�E�B���h�E�̃n���h��
		NULL,							//���j���[�������͎q�E�B���h�EID
		hInstance,						//�C���X�^���X�n���h��
		NULL);							//�E�B���h�E�쐬�f�[�^
	//�E�B���h�E�̕\��
	//�w�肳�ꂽ�E�B���h�E�̕\���ݒ�
	ShowWindow(hWnd, Cmdshow);

	DWORD dwCurrentTime;			//���ݎ���
	DWORD dwExeclastTime;			//�Ō�ɏ�����������
	DWORD dwFrameCount;
	DWORD dwFPSLastTime;
	//�ϐ��錾
	CManager*pManager;
	//�������m��
	pManager = new CManager;
	//�}�E�X�J�[�\��������
	ShowCursor(TRUE);
	//����������
	if (FAILED(pManager->Init(hInstance, hWnd, TRUE)))
	{
		return -1;
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, Cmdshow);
	//�E�B���h�E�̃N���C�A���g�̈�X�V
	UpdateWindow(hWnd);
	//����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0;
	dwExeclastTime = timeGetTime();	//���ݎ��Ԃ��擾
	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v�i���b�Z�[�W�L���[���烁�b�Z�[�W���擾�j
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{		//Window����
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{	//���b�Z�[�W�̖|��
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{		//DirectX�̏���
			dwCurrentTime = timeGetTime();
			if ((dwCurrentTime - dwFPSLastTime) >= 500)// 1/60�b���Ǝ��s
			{
#ifdef _DEBUG
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
#endif // _DEBUG

				dwFPSLastTime = dwCurrentTime;//�����������Ԃ�ۑ�
				dwFrameCount = 0;
			}
			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))// 1/60�b���Ǝ��s
			{
				dwExeclastTime = dwCurrentTime;//�����������Ԃ�ۑ�
											   //�X�V����
				pManager->Update();
				//�`�揈��
				pManager->Draw();
				//�X�V����
				dwFrameCount++;
			}
		}
	}

	//�I������
	pManager->Uninit();
	delete pManager;
	////for (int nCnt = 0; nCnt < MAX; nCnt++)
	//{
	//	CScene::RereaseAll();
	//}
	pManager = NULL;
	//����\��߂�
	timeBeginPeriod(1);
	//�E�B���h�E�N���X�̓o�^������:
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}

//ImGui�p�@���ꂪ�Ȃ��ƃ}�E�X����ł��Ȃ�
extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//�E�B���h�E�v���V�[�W���֐�
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
			//[ESC]�L�[�������ꂽ
		case VK_ESCAPE:
			//nID = MessageBox(hWnd, "�`�j���z�j���W�H", "�m�F", MB_YESNO);
			//{
			//	if (nID == IDYES)
			//	{
			//�E�B���h�E��j���iWM_DESTROY�𔭐��j
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
	case WM_DESTROY://�I��
					//WM_QUIT���b�Z�[�W��Ԃ�
		PostQuitMessage(0);
		break;
	}
	//����̏������
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int GetFps(void)
{
	return g_nCountFPS;
}
