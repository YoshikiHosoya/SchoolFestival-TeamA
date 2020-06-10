#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "BaseMode.h"
//構造体定義
//レンダリングクラス
class CRenderer;
class CKeyboard;
class CPlayer;
class CEnemy;
class CCreateMap;
class CPause;
class CGame :public CBaseMode
{
public:

	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	CPlayer * GetPlayer(void);
	CCreateMap *GetCreateMap(void);
	static int GetHP(void);
	void Draw(void);							//描画
	void ShowDebugInfo(void);					//デバッグ情報表記

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static CPlayer *m_pPlayer;
	static CEnemy *m_pEnemy;
	CCreateMap *m_pCreateMap;
	static int m_Counter;
	static int MP;
	static int HP;
	static int MPPotion;
	static int HPPotion;
	CPause *m_pPause;
};
#endif