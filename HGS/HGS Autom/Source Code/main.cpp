//------------------------------------------------------------------------------
//
//���C������  [main.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#define _CRTDBG_MAP_ALLOC

//------------------------------------------------------------------------------
//�C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "main.h"
#include "manager.h"
//------------------------------------------------------------------------------
//�}�N����`
//------------------------------------------------------------------------------
#define CLASS_NAME		("WindowClass")			//�E�B���h�E�N���X�̖��O
#define WINDOW_NAME		("Electric Chain")		//�E�B���h�E�̖��O�i�L���v�V�����\���j
#define WINDOW_MODE		(TRUE)					//�E�B���h�E���[�h���ǂ��� (FALSE�Ńt���X�N���[���j
#define WINDOW_POS		(INTEGER2(230,50))		//�E�B���h�E�̍���̍��W
//------------------------------------------------------------------------------
//�v���g�^�C�v�錾
//------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMSG, WPARAM wParam, LPARAM lParam);

//�f�o�b�O�p
#ifdef _DEBUG
int	g_nCountFPS = 0;
int	g_nCountInterval = 0;
void DispConsol();
#endif

//------------------------------------------------------------------------------
//
//���C���֐�
//
//------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR lpCmdLine, int CmdShow)
{
	//CRT���C�u�������g���ă������[���[�N�`�F�b�N
	_CrtDumpMemoryLeaks();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

	//_CrtSetBreakAlloc(8768);

	CManager *pManager;
	pManager = new CManager;

	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),									//WNDCLASSEX�̃������T�C�Y���w��
		CS_CLASSDC,											//�\������E�B���h�E�̃X�^�C����ݒ�
		WindowProc,											//�E�B���h�E�v���V�[�W���̃A�h���X(�֐���)���w��
		0,													//�ʏ�͎g�p���Ȃ��̂�0
		0,													//�ʏ�͎g�p���Ȃ��̂�0
		hInstance,											//windows�̈����̃C���X�^���X�n���h���w��
		LoadIcon(hInstance,MAKEINTRESOURCE(IDI_SWORDICON)),		//�^�X�N�o�[�Ɏg�p�҂̃A�C�R���ݒ�
		LoadCursor(NULL,IDC_ARROW),							//�g�p����}�E�X�J�[�\���w��
		(HBRUSH)(COLOR_WINDOW + 1),							//�E�B���h�E�N���C�A���g�̈�̐F�w��
		NULL,												//���j���[���w��
		CLASS_NAME,											//�E�B���h�E�N���X�̖��O
		LoadIcon(NULL,MAKEINTRESOURCE(IDI_SWORDICON))			//�������A�C�R���̎w��
	};

	HWND hWnd;				//�E�B���h�E�n���h��
	MSG msg;				//���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime;	//���ݎ���
	DWORD dwExeclastTime;	//�Ō�ɏ�����������
	DWORD dwFrameCount;		//�`��񐔂��J�E���g
	DWORD dwFPSLastTime;	//JPS���Ō�ɑ��肵������

	//�E�B���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	RECT rect = { 0 , 0 , SCREEN_WIDTH,SCREEN_HEIGHT };

	//�w�肳�ꂽ�N���C�A���g�̈���m�ۂ���ׂ̌v�Z���s��
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);

	//�E�B���h�E�̐���
	hWnd = CreateWindowEx(0,			//�g���E�B���h�E�X�^�C��
		CLASS_NAME,						//�E�B���h�E�N���X��
		WINDOW_NAME,					//�E�B���h�E�̖��O
		WS_OVERLAPPEDWINDOW,			//�E�B���h�E�X�^�C��
		WINDOW_POS.x,					//�E�B���h�E�����X���W
		WINDOW_POS.y,					//�E�B���h�E�����Y���W
		(rect.right - rect.left),		//�E�B���h�E�̕�
		(rect.bottom - rect.top),		//�E�B���h�E�̍��� �E�B���h�E�̃o�[�̕��̏C��
		NULL,							//�e�E�B���h�E�̃n���h��
		NULL,						    //���j���[�������͎q�E�B���h�EID
		hInstance,						//�C���X�^���X�n���h��
		NULL);							//�E�B���h�E�쐬�f�[�^

#ifdef _DEBUG
	DispConsol();
#endif
	//�����������i�E�B���h�E�̐�����ɍs���j
	if (FAILED(pManager->Init(hInstance, hWnd, WINDOW_MODE)))
	{
		MessageBox(hWnd, "���������s�@�I�����܂�", "Manager", MB_OK | MB_ICONHAND);
		return -1;
	}

	//�E�B���h�E�̕\��
	ShowWindow(hWnd, CmdShow);

	//����\�̐ݒ�
	timeBeginPeriod(1);

	//������
	dwCurrentTime = 0;

	//���ݎ��Ԃ��擾�@(�N�����Ă���̎���)
	dwExeclastTime = timeGetTime();

	//������
	dwFrameCount = 0;

	//���ݎ��Ԃ��擾
	dwFPSLastTime = timeGetTime();

	//���b�Z�[�W���[�v(���b�Z�[�W�L���[����̃��b�Z�[�W�擾)
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0) //���b�Z�[�W���擾���Ȃ������ꍇ0��Ԃ�
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			else
			{
				//���b�Z�[�W�̖|��Ƒ��o
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{	//directX�̏���
			dwCurrentTime = timeGetTime();

			//�O��̃^�C�����炠����x��������
			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{
#ifdef _DEBUG
				//FPS�̌v�Z
				g_nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);
#endif
				//FPS�v�Z�������̎��Ԃ̕ۑ�
				dwFPSLastTime = dwCurrentTime;

				//�J�E���g���Z�b�g
				dwFrameCount = 0;
			}

			//60�b��1��ʉ�
			if ((dwCurrentTime - dwExeclastTime) >= (1000 / 60))
			{
				//�Ō�ɍX�V�������Ԃ�ۑ�
				dwExeclastTime = dwCurrentTime;

#ifdef DEBUG

				DWORD StartTime = timeGetTime();
#endif // DEBUG

				//�X�V����
				pManager->Update();

				//�`�揈��
				pManager->Draw();

#ifdef DEBUG
				DWORD EndTime = timeGetTime();

				g_nCountInterval = EndTime - StartTime;
#endif // DEBUG

				//�񐔂��J�E���g
				dwFrameCount++;

			}
		}
	}

	//NULL�`�F�b�N
	if (pManager != NULL)
	{
		//�I������
		pManager->Uninit();

		//�������J��
		delete pManager;
		pManager = NULL;
	}

	//�E�B���h�E�N���X�̓o�^������
	UnregisterClass(CLASS_NAME, wcex.hInstance);
	return (int)msg.wParam;

}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

//------------------------------------------------------------------------------
//�E�B���h�E�v���V�[�W���֐�
//------------------------------------------------------------------------------
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	switch (uMsg)
	{
	case WM_DESTROY:	 //�E�B���h�E�j�����b�Z�[�W
		//WM_QUIT ���b�Z�[�W��Ԃ�
		PostQuitMessage(0);
		break;

	case WM_KEYDOWN:	//�L�[�����ꂽ�ۂ̃��b�Z�[�W
		//�L�[�����݂�
		switch (wParam)
		{
		case VK_ESCAPE:	//ESC�L�[�������ꂽ�ۂ̃��b�Z�[�W
			//WM_DESTROY�𔭐�
			DestroyWindow(hWnd);
			break;
		}
		break;

	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);  //�K��̏������
}

//�f�o�b�O�p
#ifdef _DEBUG
//------------------------------------------------------------------------------
//�R���\�[����ʏo��
//------------------------------------------------------------------------------
void DispConsol()
{
	//�ϐ��錾
	FILE *pFile = NULL;					//�t�@�C���̃|�C���^
	char aConsoleWindowTitle[512];		//�R���\�[���E�B���h�E�̃^�C�g��
	HWND ConsoleWindow;					//�R���\�[���E�B���h�E
	RECT WindowRect;					//�E�B���h�E�̑傫��

	//�R���R�[�����J��
	AllocConsole();

	//�o�͐�ɐݒ�
	freopen_s(&pFile, "CONOUT$", "w", stdout);

	// �R���\�[���E�C���h�E�̃^�C�g�����擾
	GetConsoleTitle(aConsoleWindowTitle, sizeof(aConsoleWindowTitle));

	// �^�C�g������E�C���h�E���������ăE�C���h�E�n���h�����擾
	ConsoleWindow = FindWindow(NULL, aConsoleWindowTitle);

	// ���݂̃E�C���h�E��Rect���擾
	GetWindowRect(ConsoleWindow, &WindowRect);

	// �E�C���h�E�̍��W�ݒ�
	MoveWindow(ConsoleWindow, 0, 0, WindowRect.right - WindowRect.left, WindowRect.bottom - WindowRect.top, TRUE);
}

//------------------------------------------------------------------------------
//FPS���擾����
//------------------------------------------------------------------------------
int GetFPS(void)
{
	return g_nCountFPS;
}

//------------------------------------------------------------------------------
//FPS���擾����
//------------------------------------------------------------------------------
int GetFPSInterval(void)
{
	return g_nCountInterval;
}

#endif
