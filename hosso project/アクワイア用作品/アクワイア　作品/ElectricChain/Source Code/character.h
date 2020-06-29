//------------------------------------------------------------------------------
//
//�L�����N�^�[����  [character.h]
//Author:Yoshiki Hosoya
//
//------------------------------------------------------------------------------
#ifndef _CHARACTER_H_
#define _CHARACTER_H_
//------------------------------------------------------------------------------
//�C���N���[�h
//------------------------------------------------------------------------------
#include "main.h"
#include "scene.h"
#include "motion.h"
//------------------------------------------------------------------------------
//�N���X��`
//------------------------------------------------------------------------------
class CModelCharacter;
class CCollision;

//�����p�����[�^�̃N���X
class CDefaultParam
{
public:
	//�R���X�g���N�^
	CDefaultParam()
	{
		//������
		m_nMaxLife = 0;
		m_fMoveSpeed = 0.0f;
		m_fDashSpeed = 0.0f;
		m_fJumpSpeed = 0.0f;
		m_fAirSpeed = 0.0f;
		m_nInvincibleTime = 0;
	}

	void SetMaxLife(int nLife)								{ m_nMaxLife = nLife; };							//���C�t
	void SetMoveSpeed(float fMoveSpeed)						{ m_fMoveSpeed = fMoveSpeed; };						//�ړ����x
	void SetDashSpeed(float fDashSpeed)						{ m_fDashSpeed = fDashSpeed; };						//�_�b�V�����x
	void SetJumpSpeed(float fJumpSpeed)						{ m_fJumpSpeed = fJumpSpeed; };						//�W�����v���x
	void SetAirSpeed(float fAirSpeed)						{ m_fAirSpeed = fAirSpeed; };						//�󒆈ړ����x
	void SetInvincinbleTime(int nInvincinbleTime)			{ m_nInvincibleTime = nInvincinbleTime; };			//���G����

	int	GetMaxLife()				{ return m_nMaxLife; };					//�ő僉�C�t�擾
	float GetMoveSpeed()			{ return m_fMoveSpeed; };				//�ړ����x�擾
	float GetDashSpeed()			{ return m_fDashSpeed; };				//�_�b�V�����x�擾
	float GetJumpSpeed()			{ return m_fJumpSpeed; };				//�W�����v���x�擾
	float GetAirSpeeed()			{ return m_fAirSpeed; };				//�W�����v���x�擾
	int	GetInvincibleTime()			{ return m_nInvincibleTime; };			//���G���Ԏ擾

private:
	int m_nMaxLife;															//�ő�HP
	float m_fMoveSpeed;														//�ړ����x
	float m_fDashSpeed;														//�_�b�V�����x
	float m_fJumpSpeed;														//�W�����v���x
	float m_fAirSpeed;														//�_�b�V�����x
	int m_nInvincibleTime;													//���G����
};

//�L�����N�^�[�̃N���X
class CCharacter : public CScene
{
public:

	//�p�����[�^
	enum PARAM_TYPE
	{
		PARAM_PLAYER = 0,		//�v���C���[
		PARAM_ENEMY,			//�G
		PARAM_ENEMY_GREEN,		//�΂̓G�@�f����
		PARAM_ENEMY_BLACK,		//���̓G�@���G
		PARAM_MAX
	};

	//���
	enum STATE
	{
		STATE_NONE = -1,		//none
		STATE_NORMAL,			//�ʏ���
		STATE_DAMAGE,			//��_���[�W��
		STATE_STAN,				//�X�^����
		STATE_DEATH,			//���S
	};

	CCharacter();
	~CCharacter();

	virtual HRESULT Init();									//������
	virtual void Uninit();									//�I��
	virtual void Update();									//�X�V
	virtual void Draw();									//�`��
	virtual void ShowDebugInfo();							//�f�o�b�O���\�L
	virtual void DamageAction() = 0;						//�_���[�W�󂯂����̃��A�N�V����
	virtual void DeathAction() = 0;							//���S���̃��A�N�V����
	virtual void AttackTurning() = 0;						//�U�����ɐ��񂷂�
	virtual void SetState(STATE nextstate);					//�X�e�[�g�ύX����

	bool ApplyDamage(int nDamage, int nBlueDamage);								//�_���[�W����
	void KnockBack(float fKnockBack_Front, float fKockBack_Up,float fAngle);	//�m�b�N�o�b�N

	//Set�֐�
	void SetPos(D3DXVECTOR3 const &pos)						{ m_pos = pos; };									//���W�ݒ�
	void SetMove(D3DXVECTOR3 const &move)					{ m_move = move; };									//�ړ��ݒ�
	void SetRot(D3DXVECTOR3 const &rot)						{ m_rot = rot; }; 									//��]�ݒ�
	void SetRotDest(D3DXVECTOR3 const &rotdest)				{ m_rotDest = rotdest; };							//��]�̌����ݒ�
	void SetLife(int nLife)									{ m_nLife = nLife; };								//���C�t
	void SetBlueLife(int nBlueLife)							{ m_nBlueLife = nBlueLife; };						//�̃��C�t
	void SetAttack(bool bAttack)							{ m_bAttack = bAttack; };							//�U�����Ă���
	void SetJump(bool bJump)								{ m_bJump = bJump; };								//�W�����v���
	void SetJumpInterval(bool bJumpInterval)				{ m_bJumpInterval = bJumpInterval; };				//�W�����v�̃C���^�[�o��
	void SetAirAttack(bool bAirAttack)						{ m_bAirAttack = bAirAttack; };						//�󒆍U��������
	void SetContinueAttack	(bool bContinueAttack)			{ m_bContinueAttack = bContinueAttack; };			//�����čU���ł��邩
	void SetInvincible(bool bInvincible)					{ m_bInvincible = bInvincible; };					//���G���Ԃ��ǂ���
	void SetAlive(bool bAlive)								{ m_bAlive = bAlive; };								//�����Ă邩�ǂ���
	void SetCntState(int nCntState)							{ m_nCntState = nCntState; };						//�J�E���g�X�e�[�g�ݒ�
	void SetChangeMotion(bool bChangeMotion)				{ m_bChangeMotion = bChangeMotion; };				//���[�V�����ύX������

	void SetGravity(bool bGravity, int nCntGravity) { m_bGravity = bGravity; m_nCntGravity = nCntGravity; };	//�d�͂����邩
	void SetParameter(MODEL_TYPE modeltype, PARAM_TYPE m_Paramtype,std::shared_ptr<CCharacter> MyPtr);			//�p�����[�^�ݒ�

	static HRESULT LoadDefaultParam();					//�����p�����[�^�ǂݍ���

	//Get�֐�
	D3DXVECTOR3		 &GetPos()								{ return m_pos; };									//���W�擾
	D3DXVECTOR3		 &GetMove()								{ return m_move; };									//�ړ��擾
	D3DXVECTOR3		 &GetRot()								{ return m_rot; };									//��]�擾
	D3DXVECTOR3		 &GetRotDest()							{ return m_rotDest; };								//��]�̌����擾
	D3DXMATRIX		*GetMtx()								{ return &m_mtxWorld; };							//���[���h�}�g���b�N�X�擾
	CCollision		*GetCollision()							{ return m_pCollision.get(); };						//�R���W����   �̃|�C���^�擾
	int				GetLife()								{ return m_nLife; };								//���C�t�擾
	int				GetBlueLife()							{ return m_nBlueLife; };							//�u���[���C�t�擾
	int				GetCntState()							{ return m_nCntState; };							//�J�E���g�X�e�[�g�擾
	PARAM_TYPE		GetParamType()							{ return m_Paramtype; };							//�p�����[�^�̎�ގ擾
	MODEL_TYPE		GetModelType()							{ return m_modeltype; };							//���f���̎�ގ擾
	bool			&GetJump()								{ return m_bJump; };								//�W�����v���Ă��邩�ǂ����̎擾
	bool			GetJumpInterval()						{ return m_bJumpInterval; };						//�W�����v�̃C���^�[�o��
	bool			GetAttack()								{ return m_bAttack; };								//�U�����Ă邩�ǂ����擾
	bool			GetInvincible()							{ return m_bInvincible; };							//���G���ǂ����擾
	bool			GetGravity()							{ return m_bGravity; };								//�d�͂����邩�ǂ���
	bool			GetAirAttack()							{ return m_bAirAttack; };							//�󒆍U��
	bool			GetContinueAttack()						{ return m_bContinueAttack; };						//�����čU���ł��邩
	bool			GetChangeMotion()						{ return m_bChangeMotion; };						//���[�V�����ύX�������ǂ���
	bool			GetAlive()								{ return m_bAlive; };								//�����Ă������ǂ���
	CDefaultParam	*GetDefaultParam(PARAM_TYPE type)		{ return m_DefaultParam[type].get(); };				//�����p�����[�^�擾
	STATE			GetState()								{ return m_State; };								//��Ԏ擾
	CModelCharacter	*GetModelCharacterPtr()					{ return m_pModelCharacter.get(); };				//���f���L�����N�^�[���擾

	D3DXVECTOR3		 GetCenterPos()							{ return m_pos + D3DXVECTOR3(0.0f,m_fCenterPosOffset,0.0f); };		//�L�����N�^�[�̒��S���W�擾�@�G�t�F�N�g�Ƃ��̔�����
	CMotion::MOTION_TYPE GetNowMotion();																						//���݂̃��[�V�����擾 �C���N���[�h����ĂȂ�����C�����C���s��
protected:

	void ShowCharacterInfo();								//�L�����N�^�[���\��
	void ChangeMotion(CMotion::MOTION_TYPE nextmotion);		//���[�V�����؂�ւ�
	bool ContinueAttack();									//�A���U��
	virtual void Collision();								//�����蔻��n�̏���
private:
	D3DXVECTOR3 m_pos;										//���W
	D3DXVECTOR3 m_posOld;									//1F�O�̍��W
	D3DXVECTOR3 m_move;										//�ړ�����
	D3DXVECTOR3 m_rot;										//���݂̉�]
	D3DXVECTOR3 m_rotDest;									//��]�̖ړI�n
	D3DXVECTOR3 m_rotDif;									//��]�̍���
	D3DXMATRIX m_mtxWorld;									//���[���h�}�g���b�N�X
	std::unique_ptr<CModelCharacter> m_pModelCharacter;		//���f���̃|�C���^
	std::unique_ptr<CCollision> m_pCollision;				//�R���W�����̃|�C���^
	MODEL_TYPE m_modeltype;									//���f���̎��
	PARAM_TYPE m_Paramtype;									//�p�����[�^�̎��
	STATE m_State;											//�L�����N�^�[�̏��

	bool m_bJump;											//�W�����v���Ă��邩�ǂ���
	bool m_bJumpInterval;									//�A���W�����v�h�~�@���n���Ă��班���C���^�[�o����݂���p
	bool m_bAttack;											//�U�����Ă邩
	bool m_bInvincible;										//���G��Ԃ��ǂ���
	bool m_bGravity;										//�d�͂����邩�ǂ���
	bool m_bAirAttack;										//�󒆍U��������
	bool m_bContinueAttack;									//�����čU���ł��邩
	bool m_bChangeMotion;									//���̃t���[�����Ƀ��[�V������ύX�������ǂ���
	bool m_bAlive;											//�����Ă邩

	int m_nLife;											//HP
	int m_nBlueLife;										//��HP
	int m_nCntState;										//��ԑJ�ڂ̃J�E���^
	int m_nCntGravity;										//���d�͏�Ԃ̃J�E���^
	int m_nCntJumpInterval;									//���n���Ă���ăW�����v�܂ł̃C���^�[�o��

	float m_fCenterPosOffset;								//�̂̒��S�̍����܂ł̃I�t�Z�b�g

	void Move();											//�ړ��֐�
	void Rot();												//��]�֐�
	void State();											//��Ԃɉ���������

	static std::vector<std::string>	m_aParamFileName;						//�p�����[�^�p�̃t�@�C����
	static std::vector<std::unique_ptr<CDefaultParam>> m_DefaultParam;		//�����p�����[�^
};
#endif