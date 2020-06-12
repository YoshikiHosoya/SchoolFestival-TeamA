// =====================================================================================================================================================================
//
// DirectX�̏��� [main.cpp]
// Author : Sato Yoshiki
//
// =====================================================================================================================================================================
#include "main.h"			// �C���N���[�h�t�@�C��
#include "renderer.h"
#include "scene.h"
#include "scene2D.h"
#include "manager.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define CLASS_NAME		"WindowCLASS"			// �E�B���h�E�N���X�̖��O
#define WINDOW_NAME		"Dlunker"				// �L���v�V����

// =====================================================================================================================================================================
// �v���g�^�C�v�錾
// =====================================================================================================================================================================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT nMsg, WPARAM wParam, LPARAM lParam);

// =====================================================================================================================================================================
// �O���[�o���ϐ�
// =====================================================================================================================================================================
int			g_nFPSCount				= 0;

// =====================================================================================================================================================================
//
// ���C���֐�
//
// =====================================================================================================================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int nCmdShow)
{
	// ���������[�N���o
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	//_CrtSetBreakAlloc(151);

		// �ϐ�
	CManager *pManager;

	// �}�l�[�W���[�̐���
	pManager = new CManager;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),					// WNDCLASSEX�̃������T�C�Y�w��
		CS_CLASSDC,							// �\������E�B���h�E�̃X�^�C���ݒ�
		WindowProc,							// �E�B���h�E�v���V�[�W���̃A�h���X(�֐���)�w��
		0,									// �ʏ�͎g�p���Ȃ��̂�0�w��
		0,									// �ʏ�͎g�p���Ȃ��̂�0�w��
		hInstance,							// Windows�̈����̃C���X�^���X�n���h���w��
		LoadIcon(NULL, IDI_APPLICATION),	// �^�X�N�o�[�Ɏg�p����A�C�R���w��
		LoadCursor(NULL, IDC_ARROW),		// �g�p����}�E�X�J�[�\���w�� (�ύX���p)
		(HBRUSH)(COLOR_WINDOW + 1),			// �E�B���h�E�N���C�A���g�̈�̐F�w��
		NULL,								// ���j���[���w��
		CLASS_NAME,							// �E�B���h�E�N���X�̖��O
		LoadIcon(NULL, IDI_APPLICATION)		// �������A�C�R���̎w�� (�ύX���邱�Ƃ�����)
	};

	HWND hWnd;	// �E�B���h�E�n���h��(���ʎq)
	MSG msg;	// ���b�Z�[�W���i�[����ϐ�

	DWORD dwCurrentTime;					// ���ݎ���
	DWORD dwExeClastTime;					// �Ō�ɏ�����������

	DWORD dwFrameCount;						// �`��񐔂��J�E���g
	DWORD dwFPSLastTime;					// FPS���Ō�ɑ��肵������

	RECT rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
	HWND hDeskWnd = GetDesktopWindow(); //���̊֐��Ńf�X�N�g�b�v�̃n���h�����擾

	// �N���C�A���g�̈���m�ۂ��邽�߂ɕK�v�ȃE�B���h�E���W���v�Z
	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_SYSMENU | WS_CAPTION, FALSE);

	// �E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�B���h�E�̐���
	hWnd = CreateWindowEx(0,				// �g���E�B���h�E�X�^�C��
		CLASS_NAME,							// �E�B���h�E�N���X��
		WINDOW_NAME,						// �E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,				// �E�B���h�E�X�^�C��
		CW_USEDEFAULT,						// �E�B���h�E����x���W
		CW_USEDEFAULT,						// �E�B���h�E����y���W
		(rect.right - rect.left),			// �E�B���h�E�̕�
		(rect.bottom - rect.top),			// �E�B���h�E�̍���
		NULL,								// �e�E�B���h�E�̃n���h��
		NULL,								// ���j���[�������͎q�E�B���h�E��ID
		hInstance,							// �C���X�^���X�n���h��
		NULL);								// �E�B���h�E�쐬�f�[�^

	// ����������			 
	if (FAILED(pManager->Init(hInstance, hWnd, FALSE)))
	{
		return -1;
	}

	// �E�B���h�E�̕\��
	ShowWindow(hWnd, nCmdShow);				// �w�肳�ꂽ�E�B���h�E�̕\���ݒ�
	UpdateWindow(hWnd);						// �E�B���h�E�̃N���C�A���g�̈�X�V

	dwCurrentTime = 0;
	dwExeClastTime = timeGetTime();			// ���ݎ��Ԃ��擾

	dwFrameCount = 0;
	dwFPSLastTime = timeGetTime();			// ���ݎ��Ԃ��擾

	// ����\��ݒ�
	timeBeginPeriod(1);

	// ���b�Z�[�W���[�v (���b�Z�[�W�L���[���烁�b�Z�[�W���擾)
	while (1)
	{	// ���b�Z�[�W���擾���Ȃ������ꍇ0��Ԃ�
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{	// Window����
			if (msg.message == WM_QUIT)
			{	// WM_QUIT���b�Z�[�W�������Ă�����I��
				break;
			}
			else
			{	// ���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	// DirectX�̏���
			dwCurrentTime = timeGetTime();							// �V�X�e�����Ԏ擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
#ifdef _DEBUG
				g_nFPSCount = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);			// FPS�𑪒�
#endif

				dwFPSLastTime = dwCurrentTime;						// FPS�𑪒肵��������ۑ�
				dwFrameCount = 0;									// �J�E���g���N���A
			}

			if ((dwCurrentTime - dwExeClastTime) >= (1000 / 60))	// 1 / 60�b���ƂɎ��s
			{
				dwExeClastTime = dwCurrentTime;						// �����������Ԃŕۑ�

				// �X�V����
				pManager->Update();

				// �`�揈��
				pManager->Draw();

				// �J�E���g�A�b�v	
				dwFrameCount++;
			}
		}
	}

	if (pManager != NULL)
	{
		// �I������
		pManager->Uninit();

		// �������̊J��
		delete pManager;
		pManager = NULL;
	}

	// ����\��߂�
	timeEndPeriod(1);

	// �E�B���h�E�N���X�̓o�^����										��[ �o�^��������� ]
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return(int)msg.wParam;
}
// =====================================================================================================================================================================
//
// �E�B���h�E�̃v���V�[�W���֐�
//
// =====================================================================================================================================================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:	// �E�B���h�E�j�����b�Z�[�W
		// WM_QUIT���b�Z�[�W��Ԃ�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	// �L�[�������ꂽ�ۂ̃��b�Z�[�W
		switch (wParam)
		{
		case VK_ESCAPE:	// [ESC]�L�[�������ꂽ
			// �E�B���h�E��j�� (WM_DESTROY�𔭐�)
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
	return DefWindowProc(hWnd, uMsg, wParam, lParam);// ����̏������    ���u �K�{ �v
}

// =====================================================================================================================================================================
//
// FPS�̎擾
//
// =====================================================================================================================================================================
int  GetFPSCount(void)
{
	return g_nFPSCount;
}
