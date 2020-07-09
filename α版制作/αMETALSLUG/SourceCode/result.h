#pragma once
#ifndef _RESULT_H_
#define _RESULT_H_
#include "main.h"
#include "BaseMode.h"
//構造体定義
//レンダリングクラス
class CRenderer;
class CKeyboard;
class CPlayer;
class CPause;
class CMap;

class CResult :public CBaseMode
{
public:

	CResult();
	~CResult();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	CPlayer * GetPlayer(void);
	CMap *GetMap(void);

	void Draw(void);							//描画
	void ShowDebugInfo(void);					//デバッグ情報表記

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static CPlayer	*m_pPlayer;
	static CMap		*m_pMap;
	static int m_Counter;
	CPause *m_pPause;
};
#endif