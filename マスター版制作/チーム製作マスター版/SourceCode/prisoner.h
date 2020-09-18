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
#include "item.h"

// =====================================================================================================================================================================
// �ߗ��̃f�[�^
// =====================================================================================================================================================================
struct PRISONER_DATA
{
	int					nDeleteTime;	// ���ł���܂ł̎���
	float				fMoveSpeed;		// �ړ����x
	D3DXVECTOR3			CollisionSize;	// �����蔻��̃T�C�Y
};

// =====================================================================================================================================================================
// �O���錾
// =====================================================================================================================================================================
class CModel;
//class CItem;

// =====================================================================================================================================================================
// �ߗ��N���X
// =====================================================================================================================================================================
class CPrisoner :public CCharacter, public CGameObject
{
public:
	// �ߗ��̏��
	enum PRISONER_STATE
	{
		PRISONER_STATE_STAY,									// �����Ă��鏉�����
		PRISONER_STATE_THINKING,								// ���̍s�����l����
		PRISONER_STATE_SKIP,									// �v���C���[�Ƃ̋���������Ă�����X�L�b�v����
		PRISONER_STATE_DROPITEM,								// �A�C�e���𗎂Ƃ�
		PRISONER_STATE_RAMPAGE,									// �\���
		PRISONER_STATE_RUN,										// �����ď�����
		PRISONER_STATE_MAX										// �ő吔
	};

	// �ߗ��̎��
	enum PRISONER_ITEM_DROPTYPE
	{
		PRISONER_ITEM_DROPTYPE_PICK_ONE,						// �h���b�v����A�C�e�����P��ގw�肷��
		PRISONER_ITEM_DROPTYPE_RANGE,							// �h���b�v����A�C�e���̎�ނ��w�肷�� - �e��n���X�R�A�n��
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

	/* �����o�֐� */
	void				DebugInfo(void);						// �f�o�b�O
	bool				DefaultMotion(void);					// �f�t�H���g���[�V����

	PRISONER_STATE				GetPrisonerState()
	{return m_PrisonerState;};									// �ߗ��̏�Ԃ̎擾

	PRISONER_ITEM_DROPTYPE		GetPrisonerDropType()
	{return m_PrisonerDropType;};								// �ߗ��̎��

	void						SetPrisonerState(PRISONER_STATE state)
	{m_PrisonerState = state;};									// �ߗ��̏�Ԃ̐ݒ�

	void				SetPrisonerType(PRISONER_ITEM_DROPTYPE type)
	{m_PrisonerDropType = type;};								// �ߗ��̎�ނ̐ݒ�

	CItem::ITEMTYPE		GetPrisonerDropItem()
	{return m_DropItem;};										// �h���b�v����A�C�e���̎擾

	void				SetPrisonerItem(CItem::ITEMTYPE type)
	{m_DropItem = type;};										// �h���b�v����A�C�e���̐ݒ�
	void Collision();											//�@�����蔻��
private:
	/* �ÓI�����o�ϐ� */
	static char				*m_PrisonerFileName;				// �ߗ��̃t�@�C����
	static PRISONER_DATA	m_PrisonerData;						// �ߗ��̃f�[�^

	/* �����o�֐� */
	void					PrisonerState();					// �ߗ��̏�ԕʏ���
	void					PrisonerDropType();					// �ߗ��̃^�C�v�ʏ���
	void					SetStateTime(int time)
							{m_StateTime = time;};				// �X�e�[�g���؂�ւ��܂ł̎��Ԃ̐ݒ�

	unsigned int			GetDistance_Player_This();			// �v���C���[�ƑI�����ꂽ�ߗ��̋����̒��������߂Č��ʂ�Ԃ�
	bool					PrisonerPosX_Than_Large();			// �ߗ���x���W���猩�č��ɂ��邩�E�ɂ��邩�̌��ʂ�Ԃ�

	/* �����o�ϐ� */
	PRISONER_STATE			m_PrisonerState;					// �f�o�b�O�̃X�e�[�^�X
	PRISONER_ITEM_DROPTYPE	m_PrisonerDropType;					// �ߗ��̎��

	void					Move(float move, float fdest);		// �ߗ��̈ړ�
	int						m_nDieCount;						// �ߗ������ł���܂ł̃J�E���g
	int						m_StateTime;						// �X�e�[�g���؂�ւ��܂ł̎���
	CItem::ITEMTYPE			m_DropItem;							// �m��h���b�v�̎��
	bool					m_bDrop;
};
#endif