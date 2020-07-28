#pragma once
//=============================================================================
// �{�X�w�b�_�[ [Boss.h]
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"
#include "Scene.h"
#include "Character.h"
class CModel;
class CGun;
class CBossAI;
//�����_�����O�N���X
class CBoss :public CCharacter
{
public:
	CBoss(OBJ_TYPE type);
	~CBoss();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	static CBoss *Create(void);
	bool DefaultMotion(void);

private:
	void Move(float move, float fdest);
	bool m_Attack;									//�U����
	float m_Angle;
	CGun	*m_pGun;								// �K���N���X�̃|�C���^
	CBossAI *m_pAI;
};
#endif