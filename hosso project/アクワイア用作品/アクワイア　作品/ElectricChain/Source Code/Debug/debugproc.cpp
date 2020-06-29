//------------------------------------------------------------------------------
//
//�f�o�b�O�\�L����  [deugproc.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "debugproc.h"
#include "../scene.h"
#include "../manager.h"
#include "../renderer.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#define FONT_COLOR (D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
//------------------------------------------------------------------------------
//�ÓI�����o�ϐ��̏�����
//------------------------------------------------------------------------------
LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[CDebugProc::PLACE_MAX][MAX_DATA] = {};
RECT CDebugProc::m_rect[CDebugProc::PLACE_MAX] =
{
	{ 0 , 0 , SCREEN_WIDTH,SCREEN_HEIGHT },		//����
	{ 700, 0 , SCREEN_WIDTH,SCREEN_HEIGHT }		//�E��
};

//------------------------------------------------------------------------------
//����������
//------------------------------------------------------------------------------
HRESULT CDebugProc::Init(HWND hWnd)
{
	//�f�o�b�O�t�H���g�̐ݒ�
	D3DXCreateFont(CManager::GetRenderer()->GetDevice(),
		14, 7,	//�t�H���g�T�C�Y
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		("�l�r �S�V�b�N"),
		&m_pFont);

	return S_OK;
}

//------------------------------------------------------------------------------
//�I������
//------------------------------------------------------------------------------
void CDebugProc::Uninit()
{
	//null�`�F�b�N
	if (m_pFont)
	{	//Direct3D�I�u�W�F�N�g�̊J��
		m_pFont->Release();
		m_pFont = nullptr;
	}
}

//------------------------------------------------------------------------------
//���󂯎��
//------------------------------------------------------------------------------
void CDebugProc::Print(PLACE place, char * fmt, ...)
{
#ifdef _DEBUG

	//�ψ����p�̃��X�g
	va_list args;

	//�z��X�^�[�g
	va_start(args, fmt);

	//m_aStr�ɉ��Z
	vsprintf(m_aStr[place] + strlen(m_aStr[place]), fmt, args);

	//�z��I��
	va_end(args);
#endif //_DEBUG
}
//------------------------------------------------------------------------------
//�`��
//------------------------------------------------------------------------------
void CDebugProc::Draw(void)
{
#ifdef _DEBUG

	for (int nCnt = 0; nCnt < CDebugProc::PLACE_MAX; nCnt++)
	{
		//�e�L�X�g�`��
		m_pFont->DrawText(NULL,
			&m_aStr[nCnt][0],
			-1,
			&m_rect[nCnt],
			DT_LEFT,
			FONT_COLOR);

	}
#endif //_DEBUG
}

//------------------------------------------------------------------------------
//�z��̏�����
//------------------------------------------------------------------------------
void CDebugProc::ResetStr()
{
	for (int nCnt = 0; nCnt < CDebugProc::PLACE_MAX; nCnt++)
	{
		//�z��̏�����
		m_aStr[nCnt][0] = '\0';
	}
}
