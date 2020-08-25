#pragma once
//=============================================================================
// AI���� [ShieldEnemyAI.h]
//=============================================================================
#ifndef _SHIELDENEMYAI_H_
#define _SHIELDENEMYAI_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "BaseAI.h"
class CWeakEnemy;
class CGun;
class CCollision;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CShieldEnemyAI :public CBaseAI
{
public:
	typedef enum
	{
		AI_NONE = 0,			//�������Ȃ�
		AI_STOP,				//�~�܂�
		AI_STAND,				//����
		AI_WALK_LEFT,			//���ړ�
		AI_WALK_RIGHT,			//�E�ړ�
		AI_ATTACK,				//�U��
		AI_MAX					//�s���̃}�b�N�X
	}AI_STATE;

	CShieldEnemyAI();
	~CShieldEnemyAI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void AttackUpdate(void);
	void Draw(void);
	void DebugInfo(void);
	static CShieldEnemyAI* CreateAI(CWeakEnemy *pEnemy);
	AI_STATE GetAIType(void);
	CCollision *GetCollision() { return m_pCollision; };			// �����蔻��̃|�C���^�擾

private:
	CWeakEnemy *pEnemyPass;			//�G�̏��̊i�[�p
	CGun	*m_pGun;			//�K���N���X�̃|�C���^
	AI_STATE m_AItype;			//�s���̎��
	AI_STATE m_AItypeOld;		//�O�̍s���̊i�[
	D3DXVECTOR3 m_Distance;
	float m_fDistance;
	int m_recast;
	int m_castcount;
	bool m_bAttack;
	bool m_bKnifeAttack;
	bool m_bReStartFlag;
	int m_random;
	CCollision				*m_pCollision;							//�����蔻��̃|�C���^
};

#endif
