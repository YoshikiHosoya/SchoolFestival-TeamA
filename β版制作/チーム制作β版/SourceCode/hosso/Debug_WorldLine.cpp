//-----------------------------------------------------------------------------
//
//��̐��̏���  [Debug_WorldLine.cpp]
// Author : Yoshiki Hosoya
//
//-----------------------------------------------------------------------------
#include "../manager.h"
#include "../renderer.h"
#include "../3Dline.h"
#include "Debug_WorldLine.h"
//-----------------------------------------------------------------------------
//�}�N��
//-----------------------------------------------------------------------------
#define AXIS_X_OFFSET (D3DXVECTOR3(1500.0f,0.0f,0.0f))
#define AXIS_Y_OFFSET (D3DXVECTOR3(0.0f,1500.0f,0.0f))
#define AXIS_Z_OFFSET (D3DXVECTOR3(0.0f,0.0f,1500.0f))

//-----------------------------------------------------------------------------
//�R���X�g���N�^
//-----------------------------------------------------------------------------
CDebug_WorldLine::CDebug_WorldLine()
{
}
//-----------------------------------------------------------------------------
//�f�X�g���N�^
//-----------------------------------------------------------------------------
CDebug_WorldLine::~CDebug_WorldLine()
{
}
//-----------------------------------------------------------------------------
//����
//-----------------------------------------------------------------------------
CDebug_WorldLine *CDebug_WorldLine::Create(D3DXVECTOR3 &pos)
{
	CDebug_WorldLine *pWorldLine = new CDebug_WorldLine;

	if(pWorldLine)
	{
		pWorldLine->m_Pos = pos;

		pWorldLine->m_pLine[AXIS_X] = C3DLine::Create(pos, ZeroVector3, AXIS_X_OFFSET, -AXIS_X_OFFSET, RedColor);
		pWorldLine->m_pLine[AXIS_Y] = C3DLine::Create(pos, ZeroVector3, AXIS_Y_OFFSET, -AXIS_Y_OFFSET, GreenColor);
		pWorldLine->m_pLine[AXIS_Z] = C3DLine::Create(pos, ZeroVector3, AXIS_Z_OFFSET, -AXIS_Z_OFFSET, BlueColor);

		pWorldLine->SetPosOrigin(pos);

		return pWorldLine;
	}
	return nullptr;
}

//-----------------------------------------------------------------------------
//���_�̍��W�ݒ�
//-----------------------------------------------------------------------------
void CDebug_WorldLine::SetPosOrigin(D3DXVECTOR3 & pos)
{
	m_pLine[AXIS_X]->SetPosColi(pos);
	m_pLine[AXIS_Y]->SetPosColi(pos);
	m_pLine[AXIS_Z]->SetPosColi(pos);
}
