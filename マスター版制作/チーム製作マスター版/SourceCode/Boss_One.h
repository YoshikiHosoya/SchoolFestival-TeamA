// =====================================================================================================================================================================
//
// �{�X1�̏��� [boss_one.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _BOSS_ONE_H_
#define _BOSS_ONE_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "enemy.h"
// =====================================================================================================================================================================
// �}�N����`
// =====================================================================================================================================================================
#define MIN_PLAYER_DISTANCE (300)										// �����Ȃ����� �v���C���[�Ɣ��肷��ŒZ����
#define MAX_PLAYER_DISTANCE (800)										// �����Ȃ����� �v���C���[�Ɣ��肷��Œ�����
#define RANGE_CENTER ((MAX_PLAYER_DISTANCE - MIN_PLAYER_DISTANCE) - 50)	// �����Ȃ����� �v���C���[�Ɣ��肷��˒��͈͂̒��S
#define CENTER_RANGE (100)												// �����Ȃ����� �v���C���[�Ɣ��肷��˒��͈͂̒��S
#define SAVE_ATTACKOLD_NUM (2)											// �ۑ����Ă����ߋ��̍U�����@�̐�

// =====================================================================================================================================================================
// �{�X�̃f�[�^�x�[�X
// =====================================================================================================================================================================
struct BOSS_ONE_DATABASE
{
	int					nLife;					// �̗�
	int					nCoolTime;				// �N�[���^�C��
	D3DXVECTOR3			CollisionSize[2];		// �����蔻��̃T�C�Y
	D3DXVECTOR3			GunShotOfsetPos[3];		// �K���̃I�t�Z�b�g���W







};

// =====================================================================================================================================================================
// �{�X��AI�f�[�^
// =====================================================================================================================================================================
typedef struct
{
	std::vector<int *> nPriorityData;			// �D��x���i�[����ϐ�
	int AttackType[4];							// �D��x
} BOSS_ONE_AI_PRIORITY;

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModel;
class CGun;
class CCollision;

// =====================================================================================================================================================================
// �ߗ��N���X
// =====================================================================================================================================================================
class CBoss_One :public CEnemy
{
public:
	// �{�X�̏��
	enum BOSS_ONE_STATE
	{
		STATE_NORMAL,												// �ʏ���
		STATE_RUNAWAY, 												// �\�����
		STATE_MAX													// �ő吔
	};

	// �{�X�̍U���pAI�̏��
	enum BOSS_ONE_ATTACK_AI_STATE
	{
		AI_STATE_GET_INFORMATION,									// ���̎擾
		AI_STATE_AI, 												// �������ɍU�����@��I������
		AI_STATE_MAX												// �ő吔
	};

	// �{�X�̍s���p�^�[��
	enum BOSS_ONE_ACTION_PATTERN
	{
		ACTION_PATTERN_NONE = -1,									// �����l �������Ȃ�
		ACTION_PATTERN_STAY,										// �������Ȃ� �ҋ@��
		ACTION_PATTERN_AI_ATTACK,									// ���̍U�����@���l����
		ACTION_PATTERN_ATTACK,										// �U������
		ACTION_PATTERN_SHIFT_POSTURE,								// �̐���ς���
		ACTION_PATTERN_MAX											// �ő吔
	};

	// �U���̎��
	enum BOSS_ONE_ATTACKTYPE
	{
		ATTACKTYPE_NONE = -1,
		ATTACKTYPE_BALKAN,											// �o���J���C
		ATTACKTYPE_FLAMERADIATION,									// �Ή����� �������̂�
		ATTACKTYPE_INCENDIARY,										// �ĈΒe
		ATTACKTYPE_SHIFTPOSTURE,									// �p���ύX
		ATTACKTYPE_MAX												// �ő吔
	};

	// �p���̎��
	enum BOSS_ONE_POSTURETYPE
	{
		POSTURETYPE_STAND,											// �N��
		POSTURETYPE_SQUAT,											// ���Ⴊ��
		POSTURETYPE_MAX												// �ő吔
	};

	// ����̎��
	enum BOSS_ONE_WEAPONTYPE
	{
		WEAPONTYPE_BALKAN,											// �o���J��
		WEAPONTYPE_FLAMETHROWER,									// �Ή����ˊ�
		WEAPONTYPE_INCENDIARY,										// �ĈΒe
		WEAPONTYPE_MAX												// �ő吔
	};

	// �D��x�̃|�C���g
	enum BOSS_ONE_PRIORITY_POINT
	{// �����قǗD��x���オ��
		PRIORITY_POINT_MINUS = -1,									// -1
		PRIORITY_POINT_NONE,										// 0
		PRIORITY_POINT_ONE,											// 1
		PRIORITY_POINT_TWO,											// 2
		PRIORITY_POINT_THREE,										// 3
		PRIORITY_POINT_MAX = 100,									// �ŗD��
	};

	CBoss_One(OBJ_TYPE type);										// �R���X�g���N�^
	~CBoss_One();													// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT Init(void);												// ������
	void	Uninit(void);											// �I��
	void	Update(void);											// �X�V
	void	Draw(void);												// �`��

	/* �ÓI�����o�֐� */
	static	CBoss_One		*Create();								// ����
	static	void			Boss_One_DataLoad();					// �{�X���̃��[�h

	/* �����o�֐� */
	void					DebugInfo(void);						// �f�o�b�O
	void					Motion(void);							// �{�X�̃p�[�c�̓���
	bool					DefaultMotion(void);					// �f�t�H���g���[�V����

	// ----- ��Ԃ̎擾�ݒ� ----- //
	BOSS_ONE_STATE			GetBossState()									{ return m_BossState; };				// �{�X�̏�Ԃ̎擾
	BOSS_ONE_ACTION_PATTERN	GetBossOneActionPattern()						{ return m_BossOneActionPattern; };		// �{�X�̍U���p�^�[���̎擾
	BOSS_ONE_ATTACKTYPE		GetBossOneType()								{ return m_AttckType; };				// �{�X�̍U���̎��
	CCollision				*GetCollision()									{ return m_pCollision; };				// �����蔻��̃|�C���^�擾
	BOSS_ONE_POSTURETYPE	GetPostureType()								{ return m_PostureType; };				// �{�X�̎p�����̎擾
	bool					GetIntermediateSquat()							{ return m_bIntermediateSquat; };		// ���Ⴊ�ݓr���Ȃ�true��Ԃ�

	// ----- ��Ԃ̐ݒ� ----- //
	void					SetBossState(BOSS_ONE_STATE state)				{ m_BossState = state; };				// �{�X�̏�Ԃ̐ݒ�
	void					SetBossAction(BOSS_ONE_ACTION_PATTERN pattern)	{ m_BossOneActionPattern = pattern; };	// �{�X�̍U���p�^�[���̐ݒ�
	void					SetBossType(BOSS_ONE_ATTACKTYPE type)			{ m_AttckType = type; };				// �{�X�̍U���̎�ނ̐ݒ�
private:
	/* �ÓI�����o�ϐ� */
	static char				*m_BossOneFileName;									// �{�X�̃t�@�C����
	static BOSS_ONE_DATABASE m_BossOneData;										// �{�X�̃f�[�^

	// �X�e�[�^�X�p //
	//static int				m_nLife;											// �̗�
	//static D3DXVECTOR3		m_CollisionSize[POSTURETYPE_MAX];					// �����蔻��̑傫��
	//static D3DXVECTOR3		m_GunShotOfsetPos[WEAPONTYPE_MAX];					// �K���̃I�t�Z�b�g

	/* �����o�֐� */

	// --- ��ԊǗ��֐� ---  //
	void					BossOneStateManager();								// �{�X�̏�ԊǗ�����
	void					Behavior();											// �{�X�̍s���ʏ���
	void					BossOneAttackManager();								// �{�X�̍U���Ǘ�����

	// --- �U���pAI�֘A ---  //
	void					Attack_AI();										// �{�X�̍U���pAI
	void					Attack_Priority();									// �U���̗D��x���v�Z
	void					Attack_InitializeDataAll();							// �D��x�̐��l��������
	void					Attack_InitializeData(BOSS_ONE_ATTACKTYPE type);	// �w�肵���s���̗D��x��������
	void					Attack_Exception();									// �D��x�����߂�ɂ������Ă̗�O

	// --- �֐� ---  //
	void					DamageReaction();									// �_���[�W���󂯂��Ƃ��̔���
	void					DeathReaction();									// ���S�������̏���
	void					StateChangeReaction();								// ��Ԃ�ς���
	void					StayAction();										// �ҋ@���̍s��
	void					BubbleSort(std::vector<int*> &data);				// �D��x�̓���ւ� ��������0�Ԗڂ���

	// --- �ݒ�֐� ---  //
	void					SetShotIntervalTime(int time)	{ m_nShotIntervalTime = time; };		// �C���^�[�o���̎��Ԃ̐ݒ�
	void					SetShotCount(int nCount)		{ m_nShotCount = nCount; };				// �V���b�g�J�E���g�̎��Ԃ̐ݒ�
	void					SetCoolTime(int time);													// �X�e�[�g���؂�ւ��܂ł̎��Ԃ̐ݒ�
	void					SetTriggerCount(int nCount)		{ m_nTriggerCount = nCount; };			// �g���K�[�̃J�E���g�̐ݒ�
	void					SetBalkanRot(float fRot)		{ m_fBalkanRot = fRot; };				// �o���J���̉�]�ʂ̐ݒ�
	void					SetGunOffsetPos(D3DXVECTOR3 pos);										// �K���̃I�t�Z�b�g���W�̐ݒ�
	void					SetGunPos();															// �K���̍��W�̐ݒ�
	void					SetFlameThrower(bool bOpen);											// �Ή����ˊ�̈ړ�
	void					SetBalkan(bool bOpen, BOSS_ONE_STATE state);							// �o���J���̈ړ�
	void					SetRotBalkan(BOSS_ONE_STATE state);										// �o���J���̉�]
	void					SetCollision();															// �����蔻��̐ݒ�
	void					SetAttackType(BOSS_ONE_ATTACKTYPE type);								// ���肵���U�����@��ݒ肷��

	void					SetBossInfo();															// �{�X�̏��̐ݒ�
	void					CreateGun();															// �K���̐����Ə����ݒ�

	// --- �擾�֐� ---  //
	D3DXVECTOR3				GetGunOffsetPos(BOSS_ONE_WEAPONTYPE type);								// �K���̃I�t�Z�b�g���W�̎擾

	// --- �K���̍��W�̐ݒ� ---  //
	void					MoveGun(D3DXVECTOR3 &PartsPos, D3DXVECTOR3 move);						// �K���̈ړ�
	void					CalcRotationBalkan(const float fTarget, float fCurrent);				// �ڕW�ƌ���
	float					get_vector_length(D3DXVECTOR3 vectol);									// �x�N�g���̒������v�Z����
	float					dot_product(D3DXVECTOR3 vl, D3DXVECTOR3 vr);							// �x�N�g������
	float					AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);							// �Q�̃x�N�g��AB�̂Ȃ��p�x�Ƃ����߂�

	// --- ���̑� ---  //
	void					Cooltime_Decrease();													// �N�[���^�C���̌���
	uint64_t				get_rand_range(uint64_t min_val, uint64_t max_val);						// �����_���֐� �͈�
	void					UpdateCollision();														// �����蔻��̍X�V

	// --- �U���Ǘ��֐� ---  //
	void					ShotIncendiary();														// �ĈΒe
	void					ShotBalkan();															// �o���J��
	void					ShotWarning();															// �ĈΒe�̍ŏ��̔���
	void					ShotFlameRadiation();													// �t���C���Ή����ˊ�
	void					ShiftPosture();															// �p���ύX
	void					ShotFlameManager();														// �Ή����˂̊Ǘ�
	void					RandomAttack();															// �U�����@�������_���Ɍ��߂�

	/* �����o�ϐ� */
	CGun						*m_pGun[WEAPONTYPE_MAX];						// �K���N���X�̃|�C���^
	CCollision					*m_pCollision;									// �����蔻��̃|�C���^
	BOSS_ONE_STATE				m_BossState;									// �{�X�̏��
	BOSS_ONE_ACTION_PATTERN		m_BossOneActionPattern;							// �{�X�̍s���p�^�[��
	BOSS_ONE_ATTACKTYPE			m_AttckType;									// �{�X�̍U���̎��
	BOSS_ONE_ATTACKTYPE			m_AttckTypeOld[SAVE_ATTACKOLD_NUM];				// 1�O�̍U���p�^�[��
	BOSS_ONE_POSTURETYPE		m_PostureType;									// �p��
	BOSS_ONE_ATTACK_AI_STATE	m_AttackAIState;								// �U��AI�̏��
	BOSS_ONE_AI_PRIORITY		m_AIPriorityData;								// ai�̗D��x�̏��

	D3DXVECTOR3					m_Gun_OffsetPos[WEAPONTYPE_MAX];				// �K���̃I�t�Z�b�g���W
	D3DXVECTOR3					m_Gun_Pos[WEAPONTYPE_MAX];						// �K���̍��W

	int							m_ShotCount;									// �ꔭ�����Ă��玟�̒e�����܂ł̎���
	int							m_nCoolTime;									// �X�e�[�g���؂�ւ��܂ł̎���
	int							m_nShotIntervalTime;							// �A�����Č��e�̎��̒e�����܂ł̎���
	int							m_nShotCount;									// �V���b�g������
	int							m_nTriggerCount;								// ���g���K�[��������
	int							m_nBalkanAngle;									// ��r�p�K���̉�]���
	int							m_nFirstShotCount;								// ���e�����܂ł̎���
	float						m_fRotTarget;									// ��]�ڕW
	float						m_fBalkanRot;									// �K���̉�]���
	float						m_fPartsRotVentilation;							// �{�X�̑��b�p�[�c�̉�]�p
	float						m_AddMove;										// �ړ��ʂ̉��Z�p
	float						m_fBalkanRotDifferencial;						// ��]�̍����p
	bool						m_bOpenWeapon;									// �o���J���ƉΉ����ˊ���o���Ă��邩�ǂ���
	bool						m_bShiftPosture;								// �p����ς���t���O
	bool						m_bBalkanGunRotFlag;							// ��]���t���O
	bool						m_bFlame;										// �Ή����˂𔭎˂��鋖��
	bool						m_bBalkanRotFlag;								// ��]���t���O
	bool						m_bIntermediateSquat;							// ���Ⴊ�ݓr�����ǂ����̃t���O
};
#endif