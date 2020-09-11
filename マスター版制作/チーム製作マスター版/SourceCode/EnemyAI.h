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
#include "BaseAI.h"
class CEnemy;
class CGun;
class CCollision;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CEnemyAI :public CBaseAI
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
	CCollision *GetCollision() { return m_pCollision; };			// �����蔻��̃|�C���^�擾

private:
	CEnemy *pEnemyPass;			//�G�̏��̊i�[�p
	CGun	*m_pGun;			//�K���N���X�̃|�C���^
	AI_STATE m_AItype;			//�s���̎��
	AI_STATE m_AItypeOld;		//�O�̍s���̊i�[
	D3DXVECTOR3 m_Distance;
	float m_fDistance;
	int m_recast;
	int m_castcount;
	bool m_bShot;
	bool m_bReStartFlag;
	int m_random;
	bool m_bCrouch;

	CCollision				*m_pCollision;							//�����蔻��̃|�C���^
};

#endif
