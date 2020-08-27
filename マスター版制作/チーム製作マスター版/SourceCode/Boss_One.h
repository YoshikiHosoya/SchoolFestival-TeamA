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
// �{�X1�̃f�[�^
// =====================================================================================================================================================================
typedef struct
{
	int					nLife;					// �̗�
	int					nCoolTime;				// �N�[���^�C��
	D3DXVECTOR3			CollisionSize[2];		// �����蔻��̃T�C�Y
	D3DXVECTOR3			GunShotOfsetPos[3];		// �K���̃I�t�Z�b�g���W
} BOSS_ONE_DATA;

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
	// �{�X1�̏��
	enum BOSS_ONE_STATE
	{
		BOSS_ONE_STATE_NONE = -1,									// �����l �������Ȃ�
		BOSS_ONE_STATE_STAY,										// �������Ȃ� �ҋ@��
		BOSS_ONE_STATE_ATTACK,										// �U������
		BOSS_ONE_STATE_SHIFT_POSTURE,								// �̐���ς���
		BOSS_ONE_STATE_MAX											// �ő吔
	};

	// �U���̎��
	enum BOSS_ONE_ATTACKTYPE
	{
		ATTACKTYPE_NONE = -1,
		ATTACKTYPE_BALKAN,											// �o���J���C
		ATTACKTYPE_FLAMERADIATION,									// �Ή����� �������̂�
		ATTACKTYPE_INCENDIARY,										// �ĈΒe
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
	static	void			SetBoss_OneData();						// �{�X�̃f�[�^�ݒ�

	/* �����o�֐� */
	void					DebugInfo(void);						// �f�o�b�O
	void					Motion(void);							// �{�X�̃p�[�c�̓���
	bool					DefaultMotion(void);					// �f�t�H���g���[�V����

	// ----- ��Ԃ̎擾�ݒ� ----- //
	BOSS_ONE_STATE			GetBossOneState()						{ return m_BossOneState; };				// �{�X�̏�Ԃ̎擾
	BOSS_ONE_ATTACKTYPE		GetBossOneType()						{ return m_AttckType; };				// �{�X�̍U���̎��
	void					SetBossState(BOSS_ONE_STATE state)		{ m_BossOneState = state; };			// �{�X�̏�Ԃ̐ݒ�
	void					SetBossType(BOSS_ONE_ATTACKTYPE type)	{ m_AttckType = type; };				// �{�X�̍U���̎�ނ̐ݒ�
	CCollision				*GetCollision()							{ return m_pCollision; };				// �����蔻��̃|�C���^�擾

private:
	/* �ÓI�����o�ϐ� */
	static char				*m_BossOneFileName;							// �{�X�̃t�@�C����
	static BOSS_ONE_DATA	m_BossOneData;								// �{�X�̃f�[�^

	// �X�e�[�^�X�p //
	static int				m_nLife;									// �̗�
	static D3DXVECTOR3		m_CollisionSize[POSTURETYPE_MAX];			// �����蔻��̑傫��
	static D3DXVECTOR3		m_GunShotOfsetPos[WEAPONTYPE_MAX];			// �K���̃I�t�Z�b�g

	/* �����o�֐� */

	// --- ��ԊǗ��֐� ---  //
	void					BossOneStateManager();						// �{�X�̏�ԕʏ���
	void					BossOneAttackManager();						// �{�X�̍U���Ǘ�����

	// --- �֐� ---  //
	void					DamageReaction();							// �_���[�W���󂯂��Ƃ��̔���
	void					DeathReaction();							// ���S�������̏���
	void					StateChangeReaction();						// ��Ԃ�ς���
	void					Behavior();									// �G�̍s��

	void					SetShotIntervalTime(int time)	{ m_nShotIntervalTime = time; };		// �C���^�[�o���̎��Ԃ̐ݒ�
	void					SetShotCount(int nCount)		{ m_nShotCount = nCount; };				// �V���b�g�J�E���g�̎��Ԃ̐ݒ�
	void					SetCoolTime(int time)			{ m_nCoolTime = time;};					// �X�e�[�g���؂�ւ��܂ł̎��Ԃ̐ݒ�
	void					SetTriggerCount(int nCount)		{ m_nTriggerCount = nCount; };			// �g���K�[�̃J�E���g�̐ݒ�
	void					SetBalkanRot(float fRot)		{ m_fBalkanRot = fRot; };				// �o���J���̉�]�ʂ̐ݒ�
	void					SetGunOffsetPos(D3DXVECTOR3 pos);										// �K���̃I�t�Z�b�g���W�̐ݒ�
	D3DXVECTOR3				GetGunOffsetPos(BOSS_ONE_WEAPONTYPE type);								// �K���̃I�t�Z�b�g���W�̎擾
	void					SetGunPos();															// �K���̍��W�̐ݒ�
	void					MoveGun(D3DXVECTOR3 &PartsPos, D3DXVECTOR3 move);						// �K���̈ړ�
	void					Cooltime_Decrease();													// �N�[���^�C���̌���
	void					CalcRotationBalkan(const float fTarget, float fCurrent);				// �ڕW�ƌ���

	float					get_vector_length(D3DXVECTOR3 vectol);									// �x�N�g���̒������v�Z����
	float					dot_product(D3DXVECTOR3 vl, D3DXVECTOR3 vr);							// �x�N�g������
	float					AngleOf2Vector(D3DXVECTOR3 A, D3DXVECTOR3 B);							// �Q�̃x�N�g��AB�̂Ȃ��p�x�Ƃ����߂�

	void					SetFlameThrower(bool bOpen);// �Ή����ˊ�̈ړ�
	void					SetBalkan(bool bOpen);// �o���J���̈ړ�


	// --- �U���Ǘ��֐� ---  //
	void					ShotIncendiary();														// �ĈΒe
	void					ShotBalkan();															// �o���J��
	void					ShotWarning();															// �ĈΒe�̍ŏ��̔���
	void					ShotFlameRadiation();													// �t���C���Ή����ˊ�

	void					ShotFlameManager();														// �Ή����˂̊Ǘ�

	void					RandomAttack();															// �U�����@�������_���Ɍ��߂�
	void					SetRotBalkan();															// �o���J���̉�]
	uint64_t				get_rand_range(uint64_t min_val, uint64_t max_val);						// �����_���֐� �͈�

	/* �����o�ϐ� */
	CGun					*m_pGun[WEAPONTYPE_MAX];			// �K���N���X�̃|�C���^
	CCollision				*m_pCollision;						// �����蔻��̃|�C���^
	BOSS_ONE_STATE			m_BossOneState;						// �{�X�̃X�e�[�^�X
	BOSS_ONE_ATTACKTYPE		m_AttckType;						// �{�X�̍U���̎��
	BOSS_ONE_ATTACKTYPE		m_AttckTypeOld;						// 1�O�̍U���p�^�[��
	int						m_ShotCount;						// �ꔭ�����Ă��玟�̒e�����܂ł̎���
	int						m_nCoolTime;						// �X�e�[�g���؂�ւ��܂ł̎���
	int						m_nShotIntervalTime;				// �A�����Č��e�̎��̒e�����܂ł̎���
	D3DXVECTOR3				m_Gun_OffsetPos[WEAPONTYPE_MAX];	// �K���̃I�t�Z�b�g���W
	D3DXVECTOR3				m_Gun_Pos[WEAPONTYPE_MAX];			// �K���̍��W
	int						m_nShotCount;						// �V���b�g������
	int						m_nTriggerCount;					// ���g���K�[��������
	bool					m_bFlame;							//
	bool					m_bBalkanRotFlag;					// ��]���t���O
	float					m_fBalkanRot;						// �K���̉�]���
	int						m_nBalkanAngle;						// ��r�p�K���̉�]���

	int						m_nShot;
	bool					m_bBalkanGunRotFlag;					// ��]���t���O

	float					m_fRotTarget;
	float					m_fPartsRotVentilation;
	bool					m_bSetBossState;
	bool					m_bOpenWeapon;//
};
#endif