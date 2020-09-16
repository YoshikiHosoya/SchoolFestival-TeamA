#pragma once
#pragma once
//=============================================================================
// AI���� [BossAI.h]
//=============================================================================
#ifndef _MELTYHONEYMK2AIAI_H_
#define _MELTYHONEYMK2AIAI_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"
#include "BaseAI.h"
class CGun;
class CWeakEnemy;
class CCollision;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CMeltyhoney :public CBaseAI
{
public:
	typedef enum
	{
		AI_NONE = 0,		//�U�����Ȃ�
		AI_SHOT,			//�ǔ��e����
		AI_LEFT,
		AI_RIGHT,
		AI_STOP,
		AI_MAX				//�s���̍ő吔
	}AI_STATE;
	CMeltyhoney();
	~CMeltyhoney();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateMoveAI(void);
	void UpdateAttackAI(void);
	void Draw(void);
	void DebugInfo(void);
	static CMeltyhoney* CreateAI(CWeakEnemy *pEnemy);

	void SetShot(bool shot)					{ m_bShot = shot; };
	void SetRestartFlag(bool flag)			{ m_bReStartFlag = flag; };
	void SetAI(AI_STATE attack)				{ m_AItype = attack; };

	bool GetShot(void)						{ return m_bShot; };
	AI_STATE GetMeltyHoneyAIType(void)		{ return m_AItype; };
	CCollision *GetCollision()				{ return m_pCollision; };	// �����蔻��̃|�C���^�擾
private:
	CWeakEnemy *pEnemy;					//�G�̏��̊i�[�p
	AI_STATE m_AItype;			//�U���̎��
	AI_STATE m_AItypeOld;		//�O�̍U���̊i�[

	int m_recast;						//���ݍs�����玟��s���܂ł̎���
	int m_castcount;					//�s������
	int m_AttackCnt;					//�U�������Ă��鎞��
	int m_AttackCastCnt;				//�U���ɓ���܂ł̎���
	int m_MoveCnt;						//�ړ����Ă��鎞��
	int m_LaserRandom;					//���[�U�[�̉E���̗������
	int m_Attacks;						//����U�����邩
	bool m_bShot;						//�U���\���
	bool m_bReStartFlag;				//�O��Ƃ͈قȂ�s��������t���O
	bool m_Attack;						//�U�����

	CCollision	*m_pCollision;			//�����蔻��̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_ShotVec;
	CWeakEnemy *pEnemyPass;				//�G�̏��̊i�[�p
	D3DXVECTOR3 m_Distance;
	float m_fDistance;

};

#endif
#pragma once
