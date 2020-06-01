//*************************************************************************************************************
//
// �G�f�B�b�g�E�B���h�E����[Editwindow.h]
// Author : Fujiwara Masato
//
//*************************************************************************************************************
#ifndef _STATUS_H_
#define _STATUS_H_

//-------------------------------------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//-------------------------------------------------------------------------------------------------------------
#include "main.h"
#include "Calculation.h"

//-------------------------------------------------------------------------------------------------------------
// �N���X��`
//-------------------------------------------------------------------------------------------------------------
class CStatus
{
public:
	CStatus();
	~CStatus();
	void EditWindowRegister(HINSTANCE hInstance);
	static CStatus *Create(void);
	void CreateEditWindow(HINSTANCE hInstance, int CmdShow);
	void EditWindowUnregister(void);
	static void StatusLoad(STATUS_INFO *Status);
	static void StatusSave(void);
	static HWND SetWindowEditDisabled(HWND *hWndthis, HWND hWnd, int nID, INTEGER2 pos, char* name);
	static HWND SetWindowEdit(HWND *hWndthis, HWND hWnd, int nID, INTEGER2 pos, int *nValue = NULL, float *fValue = NULL);

private:
	static WNDCLASSEX	m_wcex;
	static HWND			m_hWnd;
	static RECT			m_rect;

	STATUS_INFO			m_Status;
};















#endif