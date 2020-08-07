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
#include "Enemy.h"

// =====================================================================================================================================================================
// �{�X1�̃f�[�^
// =====================================================================================================================================================================
typedef struct
{
	int					nLife;			// �̗�
	int					nCoolTime;		// �N�[���^�C��
	D3DXVECTOR3			CollisionSize;	// �����蔻��̃T�C�Y
} BOSS_ONE_DATA;

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModel;

// =====================================================================================================================================================================
// �ߗ��N���X
// =====================================================================================================================================================================
class CBoss_One :public CEnemy
{
public:
	// �{�X1�̏��
	enum BOSS_ONE_STATE
	{
		BOSS_ONE_STATE_NONE = -1,								//
		BOSS_ONE_STATE_STAY,									//
		BOSS_ONE_STATE_MAX										// �ő吔
	};

	// �U���̎��
	enum BOSS_ONE_ATTACKTYPE
	{
		ATTACKTYPE_BULLET,										//
		ATTACKTYPE_MAX											// �ő吔
	};

	CBoss_One(OBJ_TYPE type);									// �R���X�g���N�^
	~CBoss_One();												// �f�X�g���N�^
	/* �����o�֐� */
	HRESULT Init(void);											// ������
	void	Uninit(void);										// �I��
	void	Update(void);										// �X�V
	void	Draw(void);											// �`��

	/* �ÓI�����o�֐� */
	static CBoss_One	*Create();								// ����
	static	void		Boss_One_DataLoad();					// �ߗ����̃��[�h
	static	void		SetBoss_OneData();						// �ߗ��̃f�[�^�ݒ�

	/* �����o�֐� */
	void				DebugInfo(void);						// �f�o�b�O
	bool				Motion(void);							// �f�t�H���g���[�V����
	bool				DefaultMotion(void);

	BOSS_ONE_STATE				GetBossOneState()
	{
		return m_BossOneState;
	};									// �ߗ��̏�Ԃ̎擾

	BOSS_ONE_ATTACKTYPE		GetPrisonerDropType()
	{
		return m_BossOneType;
	};								// �ߗ��̎��

	void						SetPrisonerState(BOSS_ONE_STATE state)
	{
		m_BossOneState = state;
	};									// �ߗ��̏�Ԃ̐ݒ�

	void				SetPrisonerType(BOSS_ONE_ATTACKTYPE type)
	{
		m_BossOneType = type;
	};								// �ߗ��̎�ނ̐ݒ�
private:
	/* �ÓI�����o�ϐ� */
	static char				*m_BossOneFileName;				// �ߗ��̃t�@�C����
	static BOSS_ONE_DATA	m_BossOneData;						// �ߗ��̃f�[�^
	static int				m_nDeleteTime;						// �ߗ������ł���܂ł̎���
	static float			m_fMoveSpeed;						// �ړ����x
	static D3DXVECTOR3		m_CollisionSize;					// �����蔻��̑傫��

	/* �����o�֐� */
	void					BossOneState();					// �ߗ��̏�ԕʏ���
	void					SetStateTime(int time)
	{
		m_StateTime = time;
	};				// �X�e�[�g���؂�ւ��܂ł̎��Ԃ̐ݒ�

	/* �����o�ϐ� */
	BOSS_ONE_STATE			m_BossOneState;						// �f�o�b�O�̃X�e�[�^�X
	BOSS_ONE_ATTACKTYPE		m_BossOneType;						// �ߗ��̎��

	int						m_nDieCount;						// �ߗ������ł���܂ł̃J�E���g
	bool					m_bUse;								// �|�C���^���g�p�ł��邩�ǂ���
	int						m_StateTime;						// �X�e�[�g���؂�ւ��܂ł̎���
};
#endif