//==========================================================
// デバッグ処理：NORI
//==========================================================
//==========================================================
// インクルードファイル
//==========================================================
#include "debugproc.h"
#include "scene.h"
#include "manager.h"
#include "renderer.h"

LPD3DXFONT CDebugProc::m_pFont = NULL;
char CDebugProc::m_aStr[10000] = {};
//==========================================================
// コンストラクタ
//==========================================================
CDebugProc::CDebugProc()
{
}
//==========================================================
// デストラクタ
//==========================================================
CDebugProc::~CDebugProc()
{
}
//==========================================================
// 初期化
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
		DEFAULT_PITCH, "ＭＳ ゴシック",
		&m_pFont);
}
//==========================================================
// 終了
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
// 表示関数
//==========================================================
void CDebugProc::Print(char * fmt, ...)
{
#ifdef _DEBUG
	int number = strlen(m_aStr);
	va_list ap;
	// 可変長引数を１個の変数にまとめる
	va_start(ap, fmt);
	vsprintf(&m_aStr[number],fmt,ap);
	va_end(ap);
#endif // DEBUG

}
//==========================================================
// 描画
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
	//文字列型の先頭の初期化
	m_aStr[0] = '\0';
}
