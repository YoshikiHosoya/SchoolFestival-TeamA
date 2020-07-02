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
// �O���錾
// =====================================================================================================================================================================
class CModel;
// =====================================================================================================================================================================
// �ߗ��N���X
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

	/* ��蕨���g���L�����N�^�[�̎�� */
	typedef enum
	{
		VEHICLE_USE_TYPE_TYPE_PLAYER,						// �v���C���[�p��蕨
		VEHICLE_USE_TYPE_TYPE_ENEMY,						// �G�l�~�[�p��蕨
		VEHICLE_USE_TYPE_TYPE_BOSS,							// �{�X�p��蕨
		VEHICLE_USE_TYPE_TYPE_MAX							// ��蕨���g���L�����N�^�[�̍ő吔
	}VEHICLE_USE_TYPE;

	/* ��蕨�̎�� */
	typedef enum
	{
		VEHICLE_TYPE_TYPE_TANK,								// ���
		VEHICLE_TYPE_TYPE_UNKNOWN,							// �s��
		VEHICLE_TYPE_TYPE_MAX
	}VEHICLE_TYPE;

	/* ��蕨�̃L�[�v�f */
	typedef struct KEY
	{
		D3DXVECTOR3 pos;									// �ʒu
		D3DXVECTOR3 rot;									// ��]

		//�R���X�g���N�^�@���̏�����
		KEY()
		{
			pos = ZeroVector3;
			rot = ZeroVector3;
		}
	}KEY;

	/* ��蕨�̃L�[��� */
	typedef struct KEY_INFO
	{
		int nFram;											// �t���[����
		std::vector<KEY*> key;								// �L�[���

		//�R���X�g���N�^
		KEY_INFO()
		{
			nFram = 60;
			key = {};
		}
	}KEY_INFO;

	/* ��蕨���f���̃��[�V������� */
	typedef struct
	{
		int nLoop;											// ���[�v
		int nNumKey;										// �L�[���̐�
		std::vector<KEY_INFO*> key_info;
	}VEHICLE_MOTION;

	/* ��蕨���f���̃��[�V���� */
	typedef enum
	{
		VEHICLE_MOTION_STATE_NONE = -1,						// �������Ȃ����
		TANK_MOTION_NORMAL = 0,								// �j���[�g����
		TANK_MOTION_MOVE,									// �ړ�
		TANK_MOTION_SQUAT,									// ���Ⴊ�� �v���C���[��荞�ݎ�
		TANK_MOTION_JUMP,									// �W�����v
		TANK_MOTION_CANNON,									// �L���m���@

		VEHICLE_MOTION_MAX									// �ő吔
	}VEHICLE_MOTION_STATE;








	CVehicle(OBJ_TYPE type);								// �R���X�g���N�^
	~CVehicle();											// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT Init(void);										// ������
	void	Uninit(void);									// �I��
	void	Update(void);									// �X�V
	void	Draw(void);										// �`��

	/* �ÓI�����o�֐� */

	/* �����o�֐� */
	void				DebugInfo(void);					// �f�o�b�O

private:
	/* �����o�֐� */
	/* �����o�ϐ� */
};
#endif
