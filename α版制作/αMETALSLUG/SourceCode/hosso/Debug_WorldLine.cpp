//-----------------------------------------------------------------------------
//
//テクスチャ管理  [texture.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "../texture.h"
#include "../manager.h"
#include "../renderer.h"
#include "../3Dline.h"
#include "Debug_WorldLine.h"
//-----------------------------------------------------------------------------
//マクロ
//-----------------------------------------------------------------------------
#define AXIS_X_OFFSET (D3DXVECTOR3(10000.0f,0.0f,0.0f))
#define AXIS_Y_OFFSET (D3DXVECTOR3(0.0f,10000.0f,0.0f))
#define AXIS_Z_OFFSET (D3DXVECTOR3(0.0f,0.0f,10000.0f))

//-----------------------------------------------------------------------------
//コンストラクタ
//-----------------------------------------------------------------------------
CDebug_WorldLine::CDebug_WorldLine()
{
}
//-----------------------------------------------------------------------------
//デストラクタ
//-----------------------------------------------------------------------------
CDebug_WorldLine::~CDebug_WorldLine()
{
}
//-----------------------------------------------------------------------------
//生成
//-----------------------------------------------------------------------------
CDebug_WorldLine *CDebug_WorldLine::Create(D3DXVECTOR3 &pos)
{
	CDebug_WorldLine *pWorldLine = new CDebug_WorldLine;

	if(pWorldLine)
	{
		pWorldLine->m_Pos = pos;

		pWorldLine->m_pLine[AXIS_X] = C3DLine::Create(pos, ZeroVector3, AXIS_X_OFFSET, -AXIS_X_OFFSET, WhiteColor);
		pWorldLine->m_pLine[AXIS_Y] = C3DLine::Create(pos, ZeroVector3, AXIS_Y_OFFSET, -AXIS_Y_OFFSET, WhiteColor);
		pWorldLine->m_pLine[AXIS_Z] = C3DLine::Create(pos, ZeroVector3, AXIS_Z_OFFSET, -AXIS_Z_OFFSET, WhiteColor);

		pWorldLine->SetPosOrigin(pos);

		return pWorldLine;
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
//原点の座標設定
//-----------------------------------------------------------------------------
void CDebug_WorldLine::SetPosOrigin(D3DXVECTOR3 & pos)
{
	m_pLine[AXIS_X]->SetPosColi(pos);
	m_pLine[AXIS_Y]->SetPosColi(pos);
	m_pLine[AXIS_Z]->SetPosColi(pos);
}
