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
	CMap *GetMap(void);

	void Draw(void);							//�`��
	void ShowDebugInfo(void);					//�f�o�b�O���\�L

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static CPlayer	*m_pPlayer;
	static CMap		*m_pMap;
	static int m_Counter;
	CPause *m_pPause;
};
#endif