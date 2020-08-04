//------------------------------------------------------------------------------
//
//��̐��̏���  [Debug_WorldLine.cpp]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------

#ifndef _DEBUG_WORLDLINE_H_
#define _DEBUG_WORLDLINE_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "../main.h"

//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
//�O���錾
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