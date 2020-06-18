#pragma once
#ifndef _GAME_H_
#define _GAME_H_
#include "main.h"
#include "BaseMode.h"
//�\���̒�`
//�����_�����O�N���X
class CRenderer;
class CKeyboard;
class CPlayer;
class CEnemy;
class CPause;
class CMap;

class CGame :public CBaseMode
{
public:

	CGame();
	~CGame();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	CPlayer * GetPlayer(void);
	CEnemy * GetEnemy (void);
	CMap *GetMap(void);
	static int GetHP(void);

	void Draw(void);							//�`��
	void ShowDebugInfo(void);					//�f�o�b�O���\�L

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static CPlayer	*m_pPlayer;
	static CEnemy	*m_pEnemy;
	static CMap		*m_pMap;
	static int m_Counter;
	static int MP;
	static int HP;
	static int MPPotion;
	static int HPPotion;
	CPause *m_pPause;
};
#endif