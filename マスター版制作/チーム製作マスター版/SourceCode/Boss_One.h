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
#include "Character.h"

// =====================================================================================================================================================================
// �{�X1�̃f�[�^
// =====================================================================================================================================================================
typedef struct
{
	int					nLife;				// �̗�
	int					nCoolTime;			// �N�[���^�C��
	D3DXVECTOR3			CollisionSize[2];	// �����蔻��̃T�C�Y
	D3DXVECTOR3			GunShotOfsetPos[3];		// �K���̃I�t�Z�b�g���W
} BOSS_ONE_DATA;

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModel;
class CGun;

// =====================================================================================================================================================================
// �ߗ��N���X
// =====================================================================================================================================================================
class CBoss_One :public CCharacter
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
		ATTACKTYPE_BALKAN,											// �o���J���C
		ATTACKTYPE_FLAMETHROWER,									// �Ή����� �������̂�
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
	static CBoss_One		*Create();								// ����
	static	void			Boss_One_DataLoad();					// �{�X���̃��[�h
	static	void			SetBoss_OneData();						// �{�X�̃f�[�^�ݒ�

	/* �����o�֐� */
	void					DebugInfo(void);						// �f�o�b�O
	bool					Motion(void);							// �f�t�H���g���[�V����
	bool					DefaultMotion(void);

	// ----- ��Ԃ̎擾�ݒ� ----- //
	BOSS_ONE_STATE			GetBossOneState()						{ return m_BossOneState; };				// �{�X�̏�Ԃ̎擾
	BOSS_ONE_ATTACKTYPE		GetPrisonerDropType()					{ return m_BossOneType; };				// �{�X�̎��
	void					SetBossState(BOSS_ONE_STATE state)		{ m_BossOneState = state; };			// �{�X�̏�Ԃ̐ݒ�
	void					SetBossType(BOSS_ONE_ATTACKTYPE type)	{ m_BossOneType = type; };				// �{�X�̎�ނ̐ݒ�
private:
	/* �ÓI�����o�ϐ� */
	static char				*m_BossOneFileName;					// �{�X�̃t�@�C����
	static BOSS_ONE_DATA	m_BossOneData;						// �{�X�̃f�[�^

	// �X�e�[�^�X�p //
	static int				m_nLife;							// �̗�
	static D3DXVECTOR3		m_CollisionSize[POSTURETYPE_MAX];	// �����蔻��̑傫��
	static D3DXVECTOR3		m_GunShotOfsetPos[WEAPONTYPE_MAX];	// �K���̃I�t�Z�b�g

	/* �����o�֐� */
	void					BossOneState();						// �{�X�̏�ԕʏ���
	void					DamageReaction();
	void					DeathReaction();
	void					StateChangeReaction();
	void					Behavior();							// �G�̍s��

	void					SetStateTime(int time)
	{
		m_StateTime = time;
	};															// �X�e�[�g���؂�ւ��܂ł̎��Ԃ̐ݒ�

	/* �����o�ϐ� */
	BOSS_ONE_STATE			m_BossOneState;						// �f�o�b�O�̃X�e�[�^�X
	BOSS_ONE_ATTACKTYPE		m_BossOneType;						// �{�X�̎��
	int						m_ShotCount;						// �ꔭ�����Ă��玟�̒e�����܂ł̎���

	int						m_StateTime;						// �X�e�[�g���؂�ւ��܂ł̎���
	CGun					*m_pGun[WEAPONTYPE_MAX];			// �K���N���X�̃|�C���^
};
#endif