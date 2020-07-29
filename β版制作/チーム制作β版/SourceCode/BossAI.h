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

#define MAX_RECASTTIME (120)
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
		AI_ATTACK_NONE = 0,	//�U�����Ȃ�
		AI_TRACKING,		//�ǔ��e����
		AI_LASER,			//���[�U�[����
		AI_DIFFUSION,		//�g�U�ˌ�
		AI_ATTACK_MAX				//�s���̍ő吔
	}AI_STATE_ATTACK;

	typedef enum
	{
		AI_MOVE_NONE = 0,	//�ړ����Ȃ�
		AI_CENTER,			//�^�񒆂ɖ߂�i�������j
		AI_LEFT,			//���ɓ���
		AI_RIGHT,			//�E�ɓ���
		AI_MOVE_MAX				//�s���̍ő吔
	}AI_STATE_MOVE;

	CBossAI();
	~CBossAI();
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void DebugInfo(void);
	D3DXVECTOR3 GetTrackingShotRot(void);
	static CBossAI* CreateAI(CBoss *pBoss);
	AI_STATE_ATTACK GetAITypeAttack(void);
	bool GetShot(void);
	CCollision *GetCollision() { return m_pCollision; };			// �����蔻��̃|�C���^�擾

private:
	CBoss	*pBossPass;					//�G�̏��̊i�[�p
	CGun	*m_pGun;					//�K���N���X�̃|�C���^
	AI_STATE_ATTACK m_AItypeAttack;		//�U���̎��
	AI_STATE_ATTACK m_AItypeAttackOld;	//�O�̍U���̊i�[

	AI_STATE_MOVE m_AItypeMove;			//�ړ��̎��
	AI_STATE_MOVE m_AItypeMoveOld;		//�O�̈ړ��̊i�[

	int m_recast;						//���ݍs�����玟��s���܂ł̎���
	int m_castcount;					//�s������
	bool m_bShot;						//�ˌ����Ă��邩
	bool m_bReStartFlag;				//�O��Ƃ͈قȂ�s��������t���O
	int m_random;						//��������p
	CCollision	*m_pCollision;			//�����蔻��̃|�C���^
	D3DXVECTOR3 m_pos;
	D3DXVECTOR3 m_ShotVec;

};

#endif
#pragma once
