// =====================================================================================================================================================================
//
// ��蕨�̏��� [vehicle.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _VEHICLE_H_
#define _VEHICLE_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "manager.h"
#include "renderer.h"

// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MAX_VEHICLE_MODEL (20)			// ��蕨���f���̃p�[�c��

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModel;
class CCollision;

// =====================================================================================================================================================================
// ��蕨�̃p�����[�^�[
// =====================================================================================================================================================================
typedef struct
{
}VEHICLE_PARAM;

// =====================================================================================================================================================================
// ��蕨�N���X
// =====================================================================================================================================================================
class CVehicle :public CScene
{
public:
	/* ��蕨�̏�� */
	typedef enum
	{
		VEHICLE_STATE_NORMAL = 0,							// �ʏ���
		VEHICLE_STATE_DAMAGE,								// �_���[�W���󂯂��Ƃ�
		VEHICLE_STATE_INVINCIBLE,							// ���G ���~�肷��ۂ̖��G����
		VEHICLE_STATE_BREAK,								// �j�󂳂��Ƃ�
		VEHICLE_STATE_MAX
	}VEHICLE_STATE;

	/* ��蕨�̎�� */
	typedef enum
	{
		VEHICLE_TYPE_TANK,									// ���
		VEHICLE_TYPE_MAX									// ��蕨�̍ő吔
	}VEHICLE_TYPE;

	/* ��蕨���g���L�����N�^�[�̎�� */
	//typedef enum
	//{
	//	VEHICLE_USE_TYPE_TYPE_PLAYER,						// �v���C���[�p��蕨
	//	VEHICLE_USE_TYPE_TYPE_ENEMY,						// �G�l�~�[�p��蕨
	//	VEHICLE_USE_TYPE_TYPE_BOSS,							// �{�X�p��蕨
	//	VEHICLE_USE_TYPE_TYPE_MAX							// ��蕨���g���L�����N�^�[�̍ő吔
	//}VEHICLE_USE_TYPE;

	/* ��蕨���f���̃��[�V���� */
	typedef enum
	{
		VEHICLE_BEHAVIOR_NORMAL = 0,						// �ʏ���
		VEHICLE_BEHAVIOR_MOVE,								// �ړ�
		VEHICLE_BEHAVIOR_SQUAT,								// ���Ⴊ�� �v���C���[��荞�ݎ�
		VEHICLE_BEHAVIOR_JUMP,								// �W�����v
		VEHICLE_BEHAVIOR_CANNON,							// �L���m���@
		VEHICLE_BEHAVIOR_MAX								// �ő吔
	}VEHICLE_BEHAVIOR_STATE;

	/* ��蕨���f���̌��� */
	typedef enum
	{
		VEHICLE_LEFT,										//������
		VEHICLE_RIGHT,										//�E����
		VEHICLE_UP,											//�����
		VEHICLE_DOWN,										//������
	}VEHICLE_DIRECTION;

	/* ���f���p�[�c�̉�]��� */
	typedef enum
	{
		MODEL_ROT_TYPE_NONE = 0,							// ����]
		MODEL_ROT_TYPE_ALWAYS,								// ���������ŏ�ɉ�]���Ă���
		MODEL_ROT_TYPE_MOVING,								// �ړ����Ă��鎞�̂�
		MODEL_ROT_TYPE_OPERATION,							// �e���𑀍삵�Ă��鎞�̂�
	}PARTS_ROT_TYPE;

	/* �����o�֐� */
	CVehicle(OBJ_TYPE type);								// �R���X�g���N�^
	~CVehicle();											// �f�X�g���N�^
	HRESULT Init(void);										// ������
	void	Uninit(void);									// �I��
	void	Update(void);									// �X�V
	void	Draw(void);										// �`��

	void AddDamage			(int Damage);					// �_���[�W�v�Z
	void Move				(float move, float fdest);		// �ړ�
	void					VehiclePartsRotCondition(
							CModel *pModel,
							PARTS_ROT_TYPE type);			// �p�[�c����]�����邽�߂̏���

	/* �I�t�Z�b�g�ǂݍ��݊֐� */
	void LoadOffset			(VEHICLE_TYPE nType);			// �I�t�Z�b�g�̓ǂݍ���

	/* �p�����[�^�ݒ�֐� */
	void SetPosition		(D3DXVECTOR3 pos)						{ m_pos = pos; };						// ���W�̐ݒ�
	void SetPotisionOld		(D3DXVECTOR3 posOld)					{ m_posOld = posOld; };					// ��t���[���O�̍��W�̐ݒ�
	void SetMove			(D3DXVECTOR3 move)						{ m_move = move; };						// �ړ��ʂ̐ݒ�
	void SetRot				(D3DXVECTOR3 rot)						{ m_rot = rot; };						// ��]�ʂ̐ݒ�
	void SetRotDest			(D3DXVECTOR3 rotDest)					{ m_rotDest = rotDest; };				// ��]�ʂ̐ݒ�
	void SetLife			(int nLife)								{ m_nLife = nLife; };					// �̗͂̐ݒ�
	void SetJump			(bool bJump)							{ m_bJump = bJump; };					// �W�����v�t���O�̐ݒ�
	void SetState			(VEHICLE_STATE state)					{ m_state = state; };					// ��蕨�̏�Ԃ̐ݒ�
	void SetBehaviorState	(VEHICLE_BEHAVIOR_STATE state)			{ m_Behaviorstate = state; };			// ��蕨�̏�Ԃ̐ݒ�
	void SetMtxWorld		(D3DXMATRIX mtxWorld)					{ m_mtxWorld = mtxWorld; };				// ���[���h�}�g���b�N�X�̐ݒ�
	void SetVehicleType		(VEHICLE_TYPE CharaType)				{ m_VehicleType = CharaType; };			// ��蕨�̎�ނ̐ݒ�
	void SetGravity			(bool gravity)							{ m_bGravity = gravity; };//			// �d�͂̐ݒ�
	void SetVehicleDirection(VEHICLE_DIRECTION direction)			{ m_VehicleDirection = direction; };	// ��蕨�̌����̐ݒ�
	void SetShotDirection	(D3DXVECTOR3 direction)					{ m_ShotRot = direction; };				// �e���������̐ݒ�
	void SetDieFlag			(bool DieFlag)							{ m_bDieFlag = DieFlag; };				// ���S�t���O�̐ݒ�

	/* �p�����[�^�擾�֐� */
	D3DXVECTOR3				&GetPosition()							{ return m_pos; };						// ���W�̎擾
	D3DXVECTOR3				&GetPositionOld()						{ return m_posOld; };					// 1�t���[���O�̍��W�̎擾
	D3DXVECTOR3				&GetMove()								{ return m_move; };						// �ړ��ʂ̎擾
	D3DXVECTOR3				&GetRot()								{ return m_rot; };						// ��]�ʂ̎擾
	D3DXVECTOR3				&GetRotDest()							{ return m_rotDest; };					// ��]�ʂ̎擾
	VEHICLE_STATE			GetVehicleState()						{ return m_state; };					// ��蕨�̏�Ԃ��擾
	D3DXMATRIX				*GetMtxWorld()							{ return &m_mtxWorld; };				// ���[���h�}�g���b�N�X�̎擾
	D3DXVECTOR3				GetShotDirection()						{ return m_ShotRot; };					// �e���������̎擾
	int						GetLife()								{ return m_nLife; };					// �̗͂̎擾
	bool					GetJump()								{ return m_bJump; };					// �W�����v�t���O�̎擾
	bool					GetGravity()							{ return m_bGravity; };					// �d�͂̎擾
	VEHICLE_TYPE			GetVehicleType()						{ return m_VehicleType; };				// �L�����N�^�[�̎�ގ擾
	std::vector<CModel*>	&GetVehicleModelList()					{ return m_vModelList; };				// �L�����N�^�[�̃��f���擾
	CModel					*GetVehicleModelPartsList(int nCnt)		{ return m_vModelList[nCnt]; };			// �L�����N�^�[�̃��f���p�[�c�擾
	VEHICLE_DIRECTION		GetVehicleDirection()					{ return m_VehicleDirection; };			// �����̎擾
	char					*GetOffsetFileName(VEHICLE_TYPE type)	{ return m_LoadOffsetFileName[type]; }; // �I�t�Z�b�g�̃t�@�C�����擾
	bool					GetDieFlag()							{ return m_bDieFlag; };					// ���S�t���O�̎擾
	CCollision				*GetCollision()							{ return m_pCollision; };				// �����蔻��̃|�C���^�擾

	/* �ÓI�����o�֐� */

	/* �����o�֐� */
	void					DebugInfo(void);						// �f�o�b�O�p�֐�

protected:

private:
	/* �����o�֐� */
	virtual void			Inertia();								// ��������
	void					Gravity();								// �d�͏���
	void					Rot();									// ��]�ʌv�Z
	void					State();								// ��ԕʏ���
	void					ShotDirection();						// �e���������̌v�Z
	void					WheelRot(CModel *pModel);				// �ԗփ��f���̉�]����
	void					GunRot(CModel *pModel);					// �e���f���̉�]����
	void					VehiclePartsRot(
											CModel *pModel,
											float fRot);			// ��ނ�������Ƃ̃p�[�c�̉�]����
	void					VehiclePartsRotLimit(
												CModel *pModel,
												float fRot);		// ��ނ�������Ƃ̃p�[�c�̉�]���� ��]���


	/* �ÓI�����o�ϐ� */
	static char *m_LoadOffsetFileName[VEHICLE_TYPE_MAX];			// �ǂݍ��ރI�t�Z�b�g�t�@�C����

	/* �����o�ϐ� */
	std::vector<CModel*>	m_vModelList;							// �ϒ��z�� �ݒu�������f��
	D3DXVECTOR3				m_rotBET[MAX_VEHICLE_MODEL];			// ��]
	D3DXVECTOR3				m_pos;									// �ʒu
	D3DXVECTOR3				m_posOld;								// �O�̈ʒu
	D3DXVECTOR3				m_move;									// �ړ���
	D3DXVECTOR3				m_rot;									// ��]
	D3DXVECTOR3				m_rotDest;								// ��]���鍷��
	D3DXVECTOR3				m_ShotRot;								// ������
	D3DXVECTOR3				m_AddRot;								// ��]�ʂ����Z
	D3DXMATRIX				m_mtxWorld;								// �}�g���b�N�X
	VEHICLE_STATE			m_state;								// ��蕨�̏��
	VEHICLE_BEHAVIOR_STATE	m_Behaviorstate;						// ��蕨�̍s�����
	VEHICLE_TYPE			m_VehicleType;							// �L�����N�^�[�̃^�C�v
	int						m_nLife;								// �̗�
	int						m_nStateCnt;							// ��Ԃ̃J�E���g
	VEHICLE_DIRECTION		m_VehicleDirection;						// �L�����N�^�[�̌���
	PARTS_ROT_TYPE			m_RotType;								// �p�[�c����]������
	bool					m_bJump;								// �W�����v�t���O
	bool					m_bGravity;								// �d�͂������邩�̃t���O
	bool					m_bDieFlag;								// ���S�t���O
	CCollision				*m_pCollision;							// �����蔻��̃|�C���^
};
#endif
