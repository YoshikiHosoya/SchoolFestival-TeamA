#pragma once
//=============================================================================
// AI���� [enemyAI.h]
//=============================================================================
#ifndef _ENEMYAI_H_
#define _ENEMYAI_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"

#define MAX_RECASTTIME (120)
class CEnemy;
class CGun;

//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CEnemyAI
{
public:
	typedef enum
	{
		AI_NONE = 0,			//�������Ȃ�
		AI_STOP,				//�~�܂�
		AI_STAND,				//����
		AI_CROUCH,				//���Ⴊ��
		AI_WALK_LEFT,			//���ړ�
		AI_WALK_RIGHT,			//�E�ړ�
		AI_SHOT,				//�ˌ�
		AI_GRENADE,				//�O���l�[�h
		AI_MAX					//
	}AI_STATE;

	CEnemyAI();
	~CEnemyAI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	static CEnemyAI* CreateAI(CEnemy *pEnemy);
	AI_STATE GetAIType(void);
	bool GetShot(void);
private:
	CEnemy *pEnemyPass;			//�G�̏��̊i�[�p�H
	CGun	*m_pGun;			//�K���N���X�̃|�C���^
	AI_STATE m_AItype;			//�s���̎��
	int m_recast;
	int m_castcount;
	bool m_bShot;
	int m_random;
};

#endif
