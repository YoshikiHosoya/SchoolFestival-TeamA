//=============================================================================
//
// �G���f������ [enemy.h]
// Author : Fujiwara Masato
//
//=============================================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_

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

//=============================================================================
// �O���錾
//=============================================================================
class CFloarTile;
//=============================================================================
// �N���X
//=============================================================================
class CEnemy : public CScene
{
public:
	// ---------���[�V�����^�C�v---------- //
	typedef enum
	{
		MOTIONTYPE_ENEMY_WAIT = 0,		//�ҋ@���[�V����
		MOTIONTYPE_ENEMY_TUTORIAL,		//�������[�V����
		MOTIONTYPE_ENEMY_RUN,			//�ړ����[�V����(����)
		MOTIONTYPE_ENEMY_KILLCAMERA,	//�v���C���[��߂܂�����
		MOTIONTYPE_ENEMY_MAX
	} MOTIONTYPE_ENEMY;

	typedef enum
	{
		ENEMY_STATE_LEVEL1 = 0,	//�ʏ펞
		ENEMY_STATE_LEVEL2		//������
	} ENEMY_STATE;

	// ---------���f�����---------- //
	typedef enum
	{//J = JOINT R = RIGHT L = LEFT
		ENEMYTYPE_00_BODY = 0,		// [��]			00
		ENEMYTYPE_01_HEAD,			// [��]			01
		ENEMYTYPE_02_ARM_L,			// [���r]		02
		ENEMYTYPE_03_ARM_R,			// [�E�r]		03
		ENEMYTYPE_04_LEG_L,			// [����]		04
		ENEMYTYPE_05_LEG_R,			// [�E��]		05
		ENEMYTYPE_MAX				//���v�p�[�c��
	} ENEMYTYPE;

	typedef enum
	{
		ROT_FORWARD = 0,	// �O��
		ROT_BACKWARD,		// ���
		ROT_LEFT,			// ��
		ROT_RIGHT			// �E
	} ROT;

	/* �֐� */
	CEnemy();
	~CEnemy();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetRot(D3DXVECTOR3 rot, ROT rotstate);			// ��]�X�V
	void StopMove(void);			//
	D3DXVECTOR3 GetPos(void);		// �ʒu�擾
	D3DXVECTOR3 GetRot(void);		// ��]�擾
	ROT GetEnemyROT(void);			// �G�̌��݂̉�]����
	static CEnemy * Create();		// �쐬
	static void Load(void);			// �ǂݍ���
	static void UnLoad(void);		// UnLoad����

	// �X�e�[�^�X�㏸
	void AddLevel(void);
	// �G�̍s��AI
	void EnemyAI(void);
	// ���Ƃ̔���
	void EnemyColi(void);
	// �i�s�����̌���
	void Direction(void);
	// ��������߂�
	void SeekBackwards(void);

	static bool GetEndFlag(void);	// �t���O�̎擾
	static void SetFreezeFlag(void);

protected:
private:
	/* �֐� */
	void Move(void);				// �ړ�
	void Rot(ROT rot);				// ��]
	void Motion(void);				// ���[�V����
	void RotInertia(void);			// ��]����
	static void SetEndFlag(void);	// �߂܂������t���O��true

	/* �ϐ� */
	static CLoad				*m_pload;							// ���[�h
	static CModel_info			*m_pModel_info;						// ���f�����̕ۑ�
	static MODEL_OFFSET			*m_pModel_offset;					// ���f���̏����z�u
	static MOTION				*m_pMotion;							// ���[�V�������̕ۑ�

	static bool					m_bFreeze;							//

	CModel 						*m_pModel[ENEMYTYPE_MAX] = {};		// ���f��
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
	bool						m_bStopMove;						// �������~�߂�
	bool						m_bJudg;
	bool						m_bProcessing;
	CFloarTile					*m_pFloarTile;
	CFloarTile					*m_pFloarTile_One;
	bool						m_bUse;
	int							m_nResult;							// �����_������
	int							m_nCount;
	static	bool				m_bCaught;							// �v���C���[��߂܂������̃t���O
	bool						m_bForward;							// �O��
	bool						m_bBackward;						// ���
	bool						m_bLeft;								// ��
	bool						m_bRight;							// �E
	ROT							m_RotState;							// ���݌����Ă������
	ROT							m_RotCurrentB;						// ���݂̌��
	ROT							m_RotPossible;						// �i�s�ł������
	int							m_nDirectionCnt;					// �i�s�ł�������̐�
	bool						m_bStopFlag;
	int							m_FreezeCnt;

};
#endif

