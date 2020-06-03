#ifndef _MANAGER_H_
#define _MANAGER_H_
#include "main.h"
//構造体定義
//レンダリングクラス
class CRenderer;
class CKeyboard;
class CPlayer;
class CSceneX;
class CCreateMap;
class CModel;
class CParticle;
class CEnemy;
class CGame;
class CManager
{
public:
	typedef enum
	{
		MODE_NONE,
		MODE_TITLE,
		MODE_GAME,
		MODE_GAME2,
		MODE_GAME3,
		MODE_RESULT,
		MODE_PAUSE,
		MODE_CLEAR,
		MODE_TUTORIAL,
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
	static GAME_MODE m_mode;
	static CCreateMap *GetCreateMap(void);
	static CGame *GetGame(void);
private:
	static CKeyboard *m_pInputKeyboard;
	static CRenderer *m_pRendere;
	static CSceneX *m_SceneX;
	static CCreateMap *m_CreateMap;
	static CParticle *m_Particle;
	static CModel *m_Model;
	static CGame *m_pGame;

};
#endif
