//------------------------------------------------------------------------------
//
//基準の線の処理  [Debug_WorldLine.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

#ifndef _DEBUG_WORLDLINE_H_
#define _DEBUG_WORLDLINE_H_
//------------------------------------------------------------------------------
//インクルード
//------------------------------------------------------------------------------
#include "../main.h"

//------------------------------------------------------------------------------
//クラス定義
//------------------------------------------------------------------------------
//前方宣言
class C3DLine;

class CDebug_WorldLine
{
public:
	CDebug_WorldLine();
	~CDebug_WorldLine();

	enum LINE_AXIS
	{
		AXIS_X = 0,
		AXIS_Y,
		AXIS_Z,
		AXIS_MAX
	};

	static CDebug_WorldLine *Create(D3DXVECTOR3 &pos);
	void SetPosOrigin(D3DXVECTOR3 &pos);

private:

	C3DLine *m_pLine[AXIS_MAX];
	D3DXVECTOR3 m_Pos;

};

#endif