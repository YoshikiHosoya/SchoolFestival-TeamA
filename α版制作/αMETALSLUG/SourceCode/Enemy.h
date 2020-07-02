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
class CGun;
class CEnemyAI;
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
	void DebugInfo(void);
	static CEnemy *Create(void);
	bool DefaultMotion(void);

private:
	void Move(float move, float fdest);
	bool m_Attack;									//�U����
	float m_Angle;
	CGun	*m_pGun;								// �K���N���X�̃|�C���^
	CEnemyAI *m_pAI;
};
#endif