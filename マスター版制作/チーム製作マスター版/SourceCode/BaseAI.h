#pragma once
// ==============================================================
// AIのベース [BaseAI.h]
// Author :Hanzawa
// ==============================================================
#ifndef _BASEAI_H_
#define _BASEAI_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

//レンダリングクラス
class CBaseAI
{
public:
	CBaseAI();
	~CBaseAI();
	virtual HRESULT Init(void);
	virtual void Uninit(void);
	virtual void Update(void);
private:

};
#endif