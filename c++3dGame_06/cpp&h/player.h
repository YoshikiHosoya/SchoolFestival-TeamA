//=============================================================================
//
// ���f������ [player.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _PLAYER_H_
#define _PLAYER_H_

#define _CRT_SECURE_NO_WARNINGS

//=============================================================================
// �C���N���[�h�t�@�C��
//=============================================================================
#include "scene.h"
#include "model.h"
#include "motion.h"

//=============================================================================
// �}�N����`
//=============================================================================
#define PLAYERCOLLISION_SIZE (60.0f)

//=============================================================================
// �O���錾
//=============================================================================

//=============================================================================
// �N���X
//=============================================================================
class CPlayer : public CScene
{
public:
	// ---------���[�V�����^�C�v---------- //
	typedef enum
	{
		MOTIONTYPE_WAIT = 0,
		MOTIONTYPE_JUMP,
		MOTIONTYPE_LANDING,
		MOTIONTYPE_LANDING_FAIL1,
		MOTIONTYPE_LANDING_FAIL2,
		MOTIONTYPE_MAX
	} MOTIONTYPE;

	typedef enum
	{
		PLAYER_STATE_NORMAL = 0,
		PLAYER_STATE_DAMAGE,
		PLAYER_STATE_DIE
	} PLAYER_STATE;

	// ---------���f�����---------- //
	typedef enum
	{
		PLAYERTYPE_00_RION_BODY = 0,
		PLAYERTYPE_01_RION_HEAD,
		PLAYERTYPE_MAX
	} PLAYERTYPE;

	typedef enum
	{
		COLLISION_LOCATION_LEFT = 0,	//��
		COLLISION_LOCATION_RIGHT,		//�E
		COLLISION_LOCATION_BACK,		//��
		COLLISION_LOCATION_FRONT,		//�\
		COLLISION_LOCATION_MAX
	} COLLISION_LOCATION;

	/* �֐� */
	CPlayer();
	~CPlayer();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	//void SetRot(D3DXVECTOR3 rot);
	D3DXVECTOR3 GetPos(void);				// �ʒu�擾
	D3DXVECTOR3 GetRot(void);				// ��]�擾
	static CPlayer * Create();				// �쐬
	static void Load(void);					// �ǂݍ���
	static void UnLoad(void);				// UnLoad����
	// �������
	void Restriction(void);

	bool GetbCol(void);
	D3DXVECTOR3 GetMove(void);

	void SetAbilityPoint(void);
	bool GetAbilityFlag(void);

protected:
private:
	/* �֐� */
	void Move(void);				// �ړ�
	void Ability(void);				// �\��

	/* �ϐ� */
	static CModel_info			*m_pModel_info;						// ���f�����̕ۑ�
	static MODEL_OFFSET			*m_pModel_offset;					// ���f���̏����z�u
	static MOTION				*m_pMotion;							// ���[�V�������̕ۑ�
	CModel 						*m_pModel[PLAYERTYPE_MAX] = {};		// ���f��
	D3DXMATRIX					m_mtxWorld;							// �s��
	D3DXVECTOR3					m_pos;								// �ʒu
	D3DXVECTOR3					m_posold;							// �O�̈ʒu
	D3DXVECTOR3					m_move;								// �ړ���
	D3DXVECTOR3					m_rot;								// ���݉�]��
	D3DXVECTOR3					m_rotLast;							// ������������
	D3DXVECTOR3					m_rotbetween;						// ��]�̍���
	D3DXVECTOR3					m_size;								// ���f���̃T�C�Y
	int							m_nMaxModel;						// �ő僂�f����
	int							m_nMotiontype;						// ���[�V�����^�C�v
	int							m_nMotiontypeOld;					// �O��̃��[�V�����^�C�v
	int							m_nMaxMotion;						// �ő僂�[�V������
	int							m_keyinfoCnt;						// �L�[���̃J�E���g
	int							m_nFrame;							// �t���[���J�E���g
	// �����蔻��
	CCollision					*m_pCollision;						// �����蔻����

	bool						m_bRun;

	int							m_nAbilityPoint;					// �\�͂��g�����߂̃|�C���g
	int							m_nCoolTime;
	bool						m_bAbilityFlag;
};
#endif
