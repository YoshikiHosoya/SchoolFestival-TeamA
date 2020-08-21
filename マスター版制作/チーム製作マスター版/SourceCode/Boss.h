#pragma once
//=============================================================================
// �{�X�w�b�_�[ [Boss.h]
//=============================================================================
#ifndef _BOSS_H_
#define _BOSS_H_
#include "main.h"
#include "Scene.h"
#include "Enemy.h"
class CModel;
class CGun;
class CBossAI;
//�����_�����O�N���X
class CBoss :public CEnemy
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
	void DeathReaction();
	void State();
	void StateChangeReaction();				//�X�e�[�g�ύX����
private:
	bool m_Attack;									//�U����
	float m_Angle;
	int m_AttackCnt;					//�U�������Ă��鎞��
	int m_AttackCastCnt;				//�U���ɓ���܂ł̎���

};
#endif