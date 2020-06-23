#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
//構造体定義
//レンダリングクラス
class CRenderer;
class CKeyboard;
class CParticle;
class CGame;
class CBaseMode;
class CMouse;
class CXInputPad;
class CManager
{
public:
	typedef enum
	{
		MODE_NONE,
		MODE_TITLE,
		MODE_GAME,
		MODE_RESULT,
		MODE_PAUSE,
		MODE_CLEAR,
		MODE_TUTORIAL,

		MODE_DEBUG_MODELVIEWER,		//デバッグ用モデルビューワ
		MODE_MAX,
	}GAME_MODE;

	CManager();
	~CManager();
	HRESULT Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static void SetGameMode(GAME_MODE mode);
	static GAME_MODE GetGameState(void);
	static CRenderer *GetRendere(void);
	static CKeyboard *GetInputKeyboard(void);
	static CBaseMode *GetBaseMode(void);
	static CMouse *GetMouse();
	static CXInputPad *GetPad(void);
private:
	static GAME_MODE m_mode;
	static CKeyboard *m_pInputKeyboard;
	static CMouse *m_pMouse;
	static CRenderer *m_pRendere;
	static CParticle *m_Particle;
	static CBaseMode *m_pBaseMode;
	static CXInputPad *m_pPad;
};
#endif
