#pragma once
// ==============================================================
// AI�̃x�[�X [BaseAI.h]
// Author :Hanzawa
// ==============================================================
#ifndef _BASEAI_H_
#define _BASEAI_H_
#include "main.h"

//�����_�����O�N���X
class CBaseAI
{
public:
	CBaseAI();
	~CBaseAI();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
	virtual void DebugInfo() {};
private:

};
#endif