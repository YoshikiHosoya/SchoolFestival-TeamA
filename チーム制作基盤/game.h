#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
//構造体定義
//レンダリングクラス
class CRenderer;
class CKeyboard;
class CPlayer;
class CEnemy;
class CCreateMap;
class CGame
{
public:

	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	static CPlayer * GetPlayer(void);
	CCreateMap *GetCreateMap(void);
	static int GetHP(void);
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

};
#endif