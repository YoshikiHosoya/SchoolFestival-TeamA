#pragma once
//=============================================================================
// AI���� [BossAI.h]
//=============================================================================
#ifndef _BOSSAI_H_
#define _BOSSAI_H_
//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "main.h"
#include "scene.h"

#define MAX_RECASTTIME (60)
class CBoss;
class CGun;
class CCollision;
//=============================================================================
// �v���g�^�C�v�錾
//=============================================================================
class CBossAI
{
public:
	typedef enum
	{
		AI_NONE = 0,	//�U�����Ȃ�
		AI_TRACKING,		//�ǔ��e����
		AI_LASER,			//���[�U�[����
		AI_DIFFUSION,		//�g�U�ˌ�
		AI_CENTER,			//�^�񒆂ɖ߂�i�������j
		AI_LEFT,			//���ɓ���
		AI_RIGHT,			//�E�ɓ���
		AI_ONPLAYER,		//���@�̏�
		AI_MAX				//�s���̍ő吔
	}AI_BOSS_STATE;
	CBossAI();
	~CBossAI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void UpdateMoveAI(void);
	void UpdateAttackAI(void);
	void Draw(void);
	void DebugInfo(void);
	D3DXVECTOR3 GetTrackingShotRot(void);
	static CBossAI* CreateAI(CBoss *pBoss);
	AI_BOSS_STATE GetBossAIType(void);
	bool GetShot(void);
	void SetShot(bool shot);
	void SetRestartFlag(bool flag);
	CCollision *GetCollision() { return m_pCollision; };			// �����蔻��̃|�C���^�擾
	void SetBossAI(AI_BOSS_STATE attack);
private:
	CBoss	*pBossPass;					//�G�̏��̊i�[�p
	AI_BOSS_STATE m_BossAItype;		//�U���̎��
	AI_BOSS_STATE m_BossAItypeOld;	//�O�̍U���̊i�[

	int m_recast;						//���ݍs�����玟��s���܂ł̎���
	int m_castcount;					//�s������
	int m_random;						//��������p
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
};

#endif
#pragma once
