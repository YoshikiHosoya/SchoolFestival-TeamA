#pragma once
// =====================================================================================================================================================================
//
// �L�����N�^�[�̏��� [Character.h]
// Author :Hanzawa
//
// =====================================================================================================================================================================
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

#define MAX_MODEL (20)			//���f���̃p�[�c��
class CModel;
class CCollision;
class CModelSet;
//�����_�����O�N���X
class CCharacter :public CScene
{
public:
	typedef enum
	{
		CHARACTER_STATE_NONE,
		CHARACTER_STATE_NORMAL,
		CHARACTER_STATE_ITEMGET_FLASH,
		CHARACTER_STATE_DAMAGE_FLASHING,
		CHARACTER_STATE_DAMAGE_RED,
		CHARACTER_STATE_DEATH,
		CHARACTER_STATE_INVINCIBLE,
	}CHARACTER_STATE;

	CCharacter() {};
	CCharacter(OBJ_TYPE type);
	~CCharacter();
	virtual HRESULT Init(void) override;			//������
	virtual void Uninit(void) override;				//�I��
	virtual void Update(void) override;				//�X�V
	virtual void Draw(void) override;				//�`��
	virtual void DebugInfo(void) override;			//�f�o�b�O�p�֐�
	virtual bool DefaultMotion(void) = 0;			//�f�t�H���g�̃��[�V�����Z�b�g
	virtual void DamageReaction();					//�_���[�W���̃��A�N�V����
	virtual void DeathReaction();					//���S�̃��A�N�V����
	virtual void State();							//�X�e�[�g�ɉ���������
	virtual void StateChangeReaction();				//�X�e�[�g�ύX����

	void Move(float move, float fdest, float fSpeed = 4.0f);
	void AddDamage(int Damage);
	void ForcedUpdate();						//�����I�Ƀ��[�V�����`�F���W
	void ResetCharacterDirection();				//��]�ʂ���Ɍ�����ݒ肵�Ȃ���

	//�Z�b�c
	void SetPosition(D3DXVECTOR3 pos);
	void SetPotisionOld(D3DXVECTOR3 posOld);
	void SetMove(D3DXVECTOR3 move);
	void SetRot(D3DXVECTOR3 rot);
	void SetRotDest(D3DXVECTOR3 rotDest);
	void SetLife(int Life);
	void SetJump(bool bJump);
	void SetState(CHARACTER_STATE state);
	void SetStateCount(int nCntState);
	void SetMtxWorld(D3DXMATRIX mtxWorld);
	void SetGravity(bool gravity);
	void SetCharacterDirection(DIRECTION direction);
	void SetShotDirection(D3DXVECTOR3 direction);
	void SetRotArm(bool use);
	void SetArmCalculation(int nCnt);
	//�Q�b�g
	D3DXVECTOR3 &GetPosition(void);				//�|�W�V����
	D3DXVECTOR3 &GetPositionOld(void);			//�O�̃|�W�V����
	D3DXVECTOR3 &GetMove(void);					//�ړ�
	D3DXVECTOR3 &GetRot(void);					//��]
	D3DXVECTOR3 &GetRotDest(void);				//��]�̍���
	D3DXVECTOR3 GetShotDirection(void);
	D3DXMATRIX *GetMtxWorld(void);
	CHARACTER_STATE GetCharacterState(void);
	CModelSet *GetModelSet(void);
	int &GetLife(void);
	bool GetJump(void);
	bool GetGravity(void);
	float GetHeightBet(void);
	DIRECTION &GetCharacterDirection(void);							//�����̎擾
	DIRECTION &GetCharacterDirectionOld(void);						//1F�O�̌����̎擾

	//���[�V�����֘A
	void SetDieFlag(bool DieFlag)					{ m_bDieFlag = DieFlag; };					// ���S�t���O�̐ݒ�
	void SetFallFlag(bool bFall)					{ m_bFall = bFall; };						// �����t���O�̐ݒ�

	D3DXVECTOR3 *GetPositionPtr()					{ return &m_pos; };							//���W�̃|�C���^�擾
	bool GetDieFlag()								{ return m_bDieFlag; };						// ���S�t���O�̎擾
	bool GetDraw()									{ return m_bDraw; };						// �`�悷�邩�ǂ����擾
	bool GetFallFlag()								{ return m_bFall; };						// �����t���O�̎擾
	int GetCharacterStateCnt()						{ return m_nStateCnt; };					// �L�����N�^�[�̃X�e�[�g�̃J�E���g

	//void ChangeColor(bool ColorChangeFlag, D3DXCOLOR AddColor);									// �F�ύX
	bool CheckDrawRange();


	CCollision *GetCollision() { return m_pCollision; };			// �����蔻��̃|�C���^�擾
	virtual void Collision();										//�����蔻�菈��

private:
	D3DXVECTOR3 m_rotBET[MAX_MODEL];
	float m_HeightBet;
	D3DXVECTOR3 m_pos;												//�ʒu
	D3DXVECTOR3 m_posfall;											//�������ʒu
	D3DXVECTOR3 m_posold;											//�O�̈ʒu
	D3DXVECTOR3 m_move;												//�ړ���
	D3DXVECTOR3 m_rot;												//��]
	D3DXVECTOR3 m_rotDest;											//��]���鍷��
	D3DXVECTOR3 m_ShotRotDest;										//�������̌���n�@�w�r�[�}�V���K���p
	D3DXVECTOR3 m_AddHeadRot;
	D3DXVECTOR3 m_AddArmRot;
	D3DXMATRIX  m_mtxWorld;											//�}�g���b�N�X
	CHARACTER_STATE m_state;										//

	int m_Life;														//���C�t
	int m_nStateCnt;												//�X�e�[�^�X�̃J�E���g
	bool m_bGravity;												//�d�͂��������Ă��邩
	bool m_bCanJump;												//�W�����v���Ă��邩�ǂ���
	bool m_bDieFlag;												// ���S�t���O
	bool m_bMotion;													//���[�V�������邩�ǂ���
	bool m_bFall;													//���[�V�������邩�ǂ���
	bool m_bDraw;													//�`�悷�邩�ǂ���
	bool m_bRotArm;
	DIRECTION	m_CharacterDirection;								//�L�����N�^�[�̌���
	DIRECTION	m_CharacterDirectionOld;							//1F�O�̃L�����N�^�[�̌���

	//���[�V�����֘A�̏��
	CCollision				*m_pCollision;							//�����蔻��̃|�C���^
	CModelSet *m_pModelSet;											//���f���̏��

	void CalcShotDirection();										//���������߂�
	void CalcMove();												//�ړ��̌v�Z
	void CalcRotation();											//��]�̌v�Z
};
#endif