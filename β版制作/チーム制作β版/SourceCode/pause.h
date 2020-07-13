#pragma once
//=============================================================================
// ポーズ処理 [pause.h]
//=============================================================================
#ifndef _Pause_H_
#define _Pause_H_
//=============================================================================
// インクルードファイル
//=============================================================================
#include "main.h"
#include "scene.h"

//==========================
// プロトタイプ宣言
//==========================
class CPause :public CScene
{
public:
	typedef enum
	{
		STATE_NONE,
		STATE_GAME,
		STATE_PAUSE,
	}PAUSE_STATE;

	CPause(OBJ_TYPE type);
	~CPause();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	static void SetPause(PAUSE_STATE state);
	static PAUSE_STATE GetPause(void);
	static CPause* CreatePause(void);

private:
	static PAUSE_STATE m_state;
};

#endif
