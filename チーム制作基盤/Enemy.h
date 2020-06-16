#pragma once
//=============================================================================
// �G�l�~�[�w�b�_�[ [Enemy.h]
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "Scene.h"
#include "Character.h"
class CModel;
//�����_�����O�N���X
class CEnemy :public CCharacter
{
public:
	CEnemy(OBJ_TYPE type);
	~CEnemy();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CEnemy *Create(void);
	void DefaultMotion(void);

private:
	void Move(float move, float fdest);
	bool m_Attack;									//�U����
	float m_Angle;
};
#endif