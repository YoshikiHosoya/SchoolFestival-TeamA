// ----------------------------------------
//
// �f�o�b�O�\�������̐���[debugproc.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _DEBUGPROC_H_
#define _DEBUGPROC_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "manager.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------
#define MAX_DEBUGPROC (10)

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CDebugproc
{
public:
	/* �֐� */
	CDebugproc();
	~CDebugproc();

	void Init(LPDIRECT3DDEVICE9 m_pDevice);
	void Uninit(void);
	static void Print(char* fmt,...);
	static void Draw(void);
protected:

private:
	static LPD3DXFONT m_pFont;
	static char m_aStr[10000];
};

#endif