// ------------------------------------------
//
// ���[�V�������� [motion.h]
// Author : Fujiwara Masato
// ------------------------------------------
#ifndef _MOTION_H_
#define _MOTION_H_

#define _CRT_SECURE_NO_WARNINGS

// ------------------------------------------
// �C���N���[�h�t�@�C��
// ------------------------------------------
#include "manager.h"
#include "model_info.h"

//=============================================================================
// �\����
//=============================================================================
// �L�[
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ��]
} KEY;

// �L�[���
typedef struct
{
	int	nFrame;	// �t���[��
	KEY *Key;	// �L�[
} KEY_INFO;

// ���[�W�������
typedef struct
{
	int			nLoop;					// ���[�v
	int			nNumKey;				// �L�[���̐�

	// �����蔻��p //
	int			Collision_nParts;		// �p�[�c�ԍ�
	D3DXVECTOR3	Collision_Ofset;		// �I�t�Z�b�g
	float		Collision_Radius;		// �~�̔��a
	int			Collision_StartFram;	// �J�n�t���[����
	int			Collision_EndFram;		// �I���t���[����
	int			Collision_Damage;		// �_���[�W��

	// �O�՗p //
	int			Orbit_nParts;			// �p�[�c�ԍ�
	D3DXVECTOR3	Orbit_Ofset;			// �I�t�Z�b�g
	int			Orbit_Mesh;				// �O�Ղ̐�
	int			Orbit_StartFram;		// �J�n�t���[����
	int			Orbit_EndFram;			// �I���t���[����
	int			Orbit_nType;			// �^�C�v
	int			Orbit_nIdTrajectory;	// �O�Ղ̔ԍ�
	bool		Orbit_bUse;				// �O�Ղ̎g�p���
	KEY_INFO	*KeyInfo;				// �L�[���(���[�V������)
} MOTION;

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CMotion
{
public:
	/* �֐� */
	CMotion();
	~CMotion();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	// �쐬
	static CMotion * Create();		
	static void Load(
		MOTION * pMotion,
		MODEL_OFFSET * pOffset,
		int nMaxkey,
		const char * file_name
	);
	static void UnLoad(
		MOTION * pMotion,
		int nMaxMotion
	);
protected:
private:
};
#endif