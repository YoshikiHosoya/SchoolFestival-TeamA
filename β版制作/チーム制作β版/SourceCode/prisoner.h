// =====================================================================================================================================================================
//
// �ߗ��̏��� [prisoner.h]
// Author : fujiwara masato
//
// =====================================================================================================================================================================
#ifndef _PRISONER_H_
#define _PRISONER_H_

// =====================================================================================================================================================================
// �C���N���[�h�t�@�C��
// =====================================================================================================================================================================
#include "main.h"
#include "Scene.h"
#include "Character.h"

// =====================================================================================================================================================================
// �ߗ��̃f�[�^
// =====================================================================================================================================================================
typedef struct
{
	int					nDeleteTime;	// ���ł���܂ł̎���
	float				fMoveSpeed;		// �ړ����x
	D3DXVECTOR3			CollisionSize;	// �����蔻��̃T�C�Y
}PRISONER_DATA;

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModel;
// =====================================================================================================================================================================
// �ߗ��N���X
// =====================================================================================================================================================================
class CPrisoner :public CCharacter
{
public:
	// �ߗ��̏��
	enum PRISONER_STATE
	{
		PRISONER_STATE_STAY,									// �����Ă��鏉�����
		PRISONER_STATE_DROPITEM,								// �A�C�e���𗎂Ƃ�
		PRISONER_STATE_RUN,										// �����ď�����
		PRISONER_STATE_MAX										// �ő吔
	};

	// �ߗ��̎��
	enum PRISONER_ITEM_DROPTYPE
	{
		PRISONER_ITEM_DROPTYPE_DESIGNATE_ONE,					// �h���b�v����A�C�e�����P��ގw�肷��
		PRISONER_ITEM_DROPTYPE_DESIGNATE_RANGE,					// �h���b�v����A�C�e���̎�ނ��w�肷�� - ����n���X�R�A�n��
		PRISONER_ITEM_DROPTYPE_ALL,								// �S�ẴA�C�e�����烉���_���Ńh���b�v������
		PRISONER_ITEM_DROPTYPE_MAX								// �ő吔
	};

	CPrisoner(OBJ_TYPE type);									// �R���X�g���N�^
	~CPrisoner();												// �f�X�g���N�^

	/* �����o�֐� */
	HRESULT Init(void);											// ������
	void	Uninit(void);										// �I��
	void	Update(void);										// �X�V
	void	Draw(void);											// �`��

	/* �ÓI�����o�֐� */
	static CPrisoner	*Create();								// ����
	static	void		PrisonerLoad();							// �ߗ����̃��[�h
	static	void		SetPrisonerData();						// �ߗ��̃f�[�^�ݒ�

	/* �����o�֐� */
	void				DebugInfo(void);						// �f�o�b�O
	bool				DefaultMotion(void);					// �f�t�H���g���[�V����

	PRISONER_STATE		GetPrisonerState()
	{
		return m_PrisonerState;
	};															// �ߗ��̏�Ԃ̎擾

	PRISONER_ITEM_DROPTYPE		GetPrisonerDropType()
	{
		return m_PrisonerDropType;
	};															// �ߗ��̎��

	void				SetPrisonerState(PRISONER_STATE state)
	{
		m_PrisonerState = state;
	};															// �ߗ��̏�Ԃ̐ݒ�

	void				SetPrisonerType(PRISONER_ITEM_DROPTYPE type)
	{
		m_PrisonerDropType = type;
	};															// �ߗ��̎�ނ̐ݒ�

private:
	/* �ÓI�����o�ϐ� */
	static char				*m_PrisonerFileName;				// �ߗ��̃t�@�C����
	static PRISONER_DATA	m_PrisonerData;						// �ߗ��̃f�[�^
	static int				m_nDeleteTime;						// �ߗ������ł���܂ł̎���
	static float			m_fMoveSpeed;						// �ړ����x
	static D3DXVECTOR3		m_CollisionSize;					// �����蔻��̑傫��

	/* �����o�֐� */
	void					PrisonerState();					// �ߗ��̏�ԕʏ���
	void					PrisonerDropType();					// �ߗ��̃^�C�v�ʏ���

	/* �����o�ϐ� */
	PRISONER_STATE			m_PrisonerState;					// �f�o�b�O�̃X�e�[�^�X
	PRISONER_ITEM_DROPTYPE	m_PrisonerDropType;					// �ߗ��̎��
	void					Move(float move, float fdest);		// �ߗ��̈ړ�
	int						m_nDieCount;						// �ߗ������ł���܂ł̃J�E���g
	bool					m_bUse;								// �|�C���^���g�p�ł��邩�ǂ���
};
#endif