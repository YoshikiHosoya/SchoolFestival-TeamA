//==========================================================
// �f�o�b�O�����FNORI
//==========================================================
//==========================================================
// �C���N���[�h�t�@�C��
//==========================================================
#include "debugproc.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"

LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[10000] = {};
//==========================================================
// �R���X�g���N�^
//==========================================================
CDebugProc::CDebugProc()
{
}
//==========================================================
// �f�X�g���N�^
//==========================================================
CDebugProc::~CDebugProc()
{
}
//==========================================================
// ������
//==========================================================
void CDebugProc::Init(void)
{

	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();

	D3DXCreateFont(pDevice,
		12, 6,
		0, 0,
		false,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH, "�l�r �S�V�b�N",
		&m_pFont);
}
//==========================================================
// �I��
//==========================================================
void CDebugProc::Uninit(void)
{

	if (m_pFont != NULL)
	{
		m_pFont->Release();
		m_pFont = NULL;
	}

}
//==========================================================
// �\���֐�
//==========================================================
void CDebugProc::Print(char * fmt, ...)
{
#ifdef _DEBUG
	int number = strlen(m_aStr);
	va_list ap;
	// �ϒ��������P�̕ϐ��ɂ܂Ƃ߂�
	va_start(ap, fmt);
	vsprintf(&m_aStr[number],fmt,ap);
	va_end(ap);
#endif // DEBUG

}
//==========================================================
// �`��
//==========================================================
void CDebugProc::Draw(void)
{

	RECT rect = { 0,0,1280,720 };
	m_pFont->DrawText(NULL,
		&m_aStr[0],
		-1,
		&rect,
		DT_LEFT,
		D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	//������^�̐擪�̏�����
	m_aStr[0] = '\0';
}
