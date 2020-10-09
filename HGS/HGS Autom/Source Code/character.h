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

	//���
	enum STATE
	{
		STATE_NONE = -1,		//none
		STATE_NORMAL,			//�ʏ���
		STATE_DAMAGE,			//��_���[�W��
	};

	enum PARAM
	{
		PARAM_PLAYER,
		PARAM_MAX,
	};

	CCharacter();
	virtual ~CCharacter();

	virtual HRESULT Init() = 0;									//������
	virtual void Uninit() = 0;									//�I��
	virtual void Update() = 0;									//�X�V
	virtual void Draw() = 0;									//�`��
	virtual void ShowDebugInfo();								//�f�o�b�O���\�L
	virtual void SetState(STATE nextstate);						//�X�e�[�g�ύX����
	void SetParam(PARAM param);									//�p�����[�^�ݒ�
	bool ApplyDamage(int nDamage, int nBlueDamage);				//�_���[�W����

	//Set�֐�
	void SetPos(D3DXVECTOR3 const &pos)						{ m_pos = pos; };												//���W�ݒ�
	void SetMove(D3DXVECTOR3 const &move)					{ m_move = move; };												//�ړ��ݒ�
	void SetRot(D3DXVECTOR3 const &rot)						{ m_rot = rot; }; 												//��]�ݒ�
	void SetLife(int nLife)									{ m_nLife = nLife; };											//���C�t
	void SetAttack(bool bAttack)							{ m_bAttack = bAttack; };										//�U�����Ă���
	void SetJump(bool bJump)								{ m_bJump = bJump; };											//�W�����v���
	void SetInvincible(bool bInvincible)					{ m_bInvincible = bInvincible; };								//���G���Ԃ��ǂ���
	void SetAlive(bool bAlive)								{ m_bAlive = bAlive; };											//�����Ă邩�ǂ���
	void SetCntState(int nCntState)							{ m_nCntState = nCntState; };									//�J�E���g�X�e�[�g�ݒ�
	void SetGravity(bool bGravity)							{ m_bGravity = bGravity; };										//�O���r�e�B�ݒ�

	static HRESULT LoadDefaultParam();																						//�����p�����[�^�ǂݍ���
	static CDefaultParam *GetDefaultParam(int nChara)		{ return m_DefaultParam[nChara].get(); };						//�����p�����[�^�擾

	//Get�֐�
	D3DXVECTOR3		 &GetPos()								{ return m_pos; };									//���W�擾
	D3DXVECTOR3		 &GetMove()								{ return m_move; };									//�ړ��擾
	D3DXVECTOR3		 &GetRot()								{ return m_rot; };									//��]�擾
	CCollision		*GetCollision()							{ return m_pCollision.get(); };						//�R���W����   �̃|�C���^�擾
	int				GetLife()								{ return m_nLife; };								//���C�t�擾
	int				GetCntState()							{ return m_nCntState; };							//�J�E���g�X�e�[�g�擾
	bool			&GetJump()								{ return m_bJump; };								//�W�����v���Ă��邩�ǂ����̎擾
	bool			GetAttack()								{ return m_bAttack; };								//�U�����Ă邩�ǂ����擾
	bool			GetInvincible()							{ return m_bInvincible; };							//���G���ǂ����擾
	bool			GetGravity()							{ return m_bGravity; };								//�d�͂����邩�ǂ���
	bool			GetAlive()								{ return m_bAlive; };								//�����Ă������ǂ���
	STATE			GetState()								{ return m_State; };								//��Ԏ擾
	PARAM			GetParam()								{ return m_Param; };								//�p�����[�^�擾

protected:
	void ShowCharacterInfo();								//�L�����N�^�[���\��

	//�������z�֐��@�p���悪�I�[�o�[���C�h����
	virtual void State() = 0;								//��Ԃɉ���������
	virtual void Collision() = 0;							//�����蔻��n�̏���
	virtual void Move() = 0;								//�ړ��֐�
	virtual void Rot() = 0;									//��]�֐�
	virtual void DamageAction() = 0;						//�_���[�W�󂯂����̃��A�N�V����
	virtual void DeathAction() = 0;							//���S���̃��A�N�V����

private:
	D3DXVECTOR3 m_pos;										//���W
	D3DXVECTOR3 m_posOld;									//1F�O�̍��W
	D3DXVECTOR3 m_move;										//�ړ�����
	D3DXVECTOR3 m_rot;										//���݂̉�]
	std::unique_ptr<CCollision> m_pCollision;				//�R���W�����̃|�C���^
	STATE m_State;											//�L�����N�^�[�̏��
	PARAM m_Param;											//�L�����N�^�[�̃p�����[�^�̎��

	bool m_bJump;											//�W�����v���Ă��邩�ǂ���
	bool m_bAttack;											//�U�����Ă邩
	bool m_bInvincible;										//���G��Ԃ��ǂ���
	bool m_bGravity;										//�d�͂����邩�ǂ���
	bool m_bAlive;											//�����Ă邩

	int m_nLife;											//HP
	int m_nCntState;										//��ԑJ�ڂ̃J�E���^

	static std::vector<std::string>	m_aParamFileName;						//�p�����[�^�p�̃t�@�C����
	static std::vector<std::unique_ptr<CDefaultParam>> m_DefaultParam;		//�����p�����[�^
};
#endif