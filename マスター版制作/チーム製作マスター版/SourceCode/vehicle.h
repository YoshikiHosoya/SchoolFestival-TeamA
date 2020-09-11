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
class CPlayer;

// =====================================================================================================================================================================
// ��蕨�̃p�����[�^�[
// =====================================================================================================================================================================
typedef struct
{
}VEHICLE_PARAM;

// =====================================================================================================================================================================
// ��蕨�N���X
// =====================================================================================================================================================================
class CVehicle
{
public:
	/* ��蕨�̎�� */
	typedef enum
	{
		VEHICLE_TYPE_TANK,									// ���
		VEHICLE_TYPE_PLANE,									// �퓬�@
		VEHICLE_TYPE_HELICOPTER,							// �w���R�v�^�[
		VEHICLE_TYPE_MAX									// ��蕨�̍ő吔
	}VEHICLE_TYPE;

	/* ��Ԃ̋��� */
	typedef enum
	{
		VEHICLE_BEHAVIOR_NORMAL = 0,						// �ʏ���
		VEHICLE_BEHAVIOR_MOVE,								// �ړ�
		VEHICLE_BEHAVIOR_SQUAT,								// ���Ⴊ�� �v���C���[��荞�ݎ�
		VEHICLE_BEHAVIOR_JUMP,								// �W�����v
		VEHICLE_BEHAVIOR_CANNON,							// �L���m���@
		VEHICLE_BEHAVIOR_MAX								// �ő吔
	}VEHICLE_BEHAVIOR_STATE;

	/* ���f���p�[�c�̉�]��� */
	typedef enum
	{
		MODEL_ROT_TYPE_NONE = 0,							// ����]
		MODEL_ROT_TYPE_ALWAYS,								// ���������ŏ�ɉ�]���Ă���
		MODEL_ROT_TYPE_MOVING,								// �ړ����Ă��鎞�̂�
		MODEL_ROT_TYPE_OPERATION,							// �e���𑀍삵�Ă��鎞�̂�
	}PARTS_ROT_TYPE;

	/* �����o�֐� */
	CVehicle();								// �R���X�g���N�^
	~CVehicle();											// �f�X�g���N�^

	//virtual void			SetPlayerTank(CPlayer *pPlayer)	{ m_pPlayer = pPlayer; };	//�v���C���[�̃|�C���^�ݒ�
	//CPlayer					*GetPlayer(void)				{return m_pPlayer; };
	void SetRideerTag(TAG tag) { m_RideerTag = tag; };
	TAG GetRideerTag(void) { return m_RideerTag; };
	void					VehiclePartsRotCondition(
							CModel *pModel,
							PARTS_ROT_TYPE type,
							D3DXVECTOR3 move,
							D3DXVECTOR3 rot,
							DIRECTION direction);			// �p�[�c����]�����邽�߂̏���

	/* �p�����[�^�ݒ�֐� */
	void SetBehaviorState	(VEHICLE_BEHAVIOR_STATE state)			{ m_Behaviorstate = state; };			// ��蕨�̏�Ԃ̐ݒ�
	void SetVehicleType		(VEHICLE_TYPE CharaType)				{ m_VehicleType = CharaType; };			// ��蕨�̎�ނ̐ݒ�

	/* �p�����[�^�擾�֐� */
	VEHICLE_TYPE			GetVehicleType()						{ return m_VehicleType; };				// �L�����N�^�[�̎�ގ擾
	char					*GetOffsetFileName(VEHICLE_TYPE type)	{ return m_LoadOffsetFileName[type]; }; // �I�t�Z�b�g�̃t�@�C�����擾

	/* �ÓI�����o�֐� */

	/* �����o�֐� */
	void					DebugInfo(void);						// �f�o�b�O�p�֐�

protected:

private:
	/* �����o�֐� */
	void					WheelRot(CModel *pModel, D3DXVECTOR3 move);										// �ԗփ��f���̉�]����
	void					GunRot(CModel *pModel, D3DXVECTOR3 shotrot,DIRECTION direction);					// �e���f���̉�]����
	void					VehiclePartsRot(
											CModel *pModel,
											float fRot);			// ��ނ�������Ƃ̃p�[�c�̉�]����
	void					VehiclePartsRotLimit(
												CModel *pModel,
												float fRot);		// ��ނ�������Ƃ̃p�[�c�̉�]���� ��]���
	/* �ÓI�����o�ϐ� */
	static char *m_LoadOffsetFileName[VEHICLE_TYPE_MAX];			// �ǂݍ��ރI�t�Z�b�g�t�@�C����

	/* �����o�ϐ� */
	//std::vector<CModel*>	m_vModelList;							// �ϒ��z�� �ݒu�������f��
	VEHICLE_BEHAVIOR_STATE	m_Behaviorstate;						// ��蕨�̍s�����
	VEHICLE_TYPE			m_VehicleType;							// �L�����N�^�[�̃^�C�v
	PARTS_ROT_TYPE			m_RotType;								// �p�[�c����]������
	int						m_nGravityCnt;							// �d�͗p�J�E���g
	CPlayer				*m_pPlayer;							// �v���C���[�̃|�C���^
	TAG	m_RideerTag;

};
#endif
