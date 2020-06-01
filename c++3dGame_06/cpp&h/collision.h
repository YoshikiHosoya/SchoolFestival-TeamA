// ����������������������������������������������������������������������
//
// Collision�w�b�_�[�����̐���[calculation.h]
// Author : Fujiwara Masato
//
// ����������������������������������������������������������������������

#ifndef _COLLISION_H_
#define _COLLISION_H_	 // �t�@�C������������߂�

// ����������������������������������������������������������������������
//
// �C���N���[�h�t�@�C��
//
// ����������������������������������������������������������������������
#include "main.h"

// ����������������������������������������������������������������������
//
// �}�N����`
//
// ����������������������������������������������������������������������
#define COLLISION_MAX (128)

// ����������������������������������������������������������������������
//
// Collision���
//
// ����������������������������������������������������������������������

// ����������������������������������������������������������������������
//
// �\���̒�`
//
// ����������������������������������������������������������������������

// ------------------------------------------
//
// ���O��`
//
// ------------------------------------------

// ------------------------------------------
//
// �O���錾
//
// ------------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CCollision
{
public:
	/* �񋓌^ */
	// �I�u�W�F�N�g�̎��
	typedef enum
	{
		OBJTYPE_PLAYER = 0,
		OBJTYPE_ENEMY,
		OBJTYPE_ACTOR,
		OBJTYPE_ITEM,
		OBJTYPE_WAIT,
		OBJTYPE_MAX
	} OBJTYPE;
	// �����蔻��̌`
	typedef enum
	{
		COLLISIONTYPE_SQUARE = 0,
		COLLISIONTYPE_CIRCLE,
		COLLISIONTYPE_MAX
	} COLLISIONTYPE;
	/* �\���� */
	typedef struct
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR3 size;
		OBJTYPE type;
	} INFO;
	/* �֐� */
	CCollision();
	~CCollision();
	void Init(void);
	void Uninit(void);
	void Update(void);
	static void UpdateAll(void);		// �����蔻��X�V
	static void Delete(int ID);
	static void DeleteAll(void);
	static CCollision * Create(void);
	static void LoadCreate(void);		// �ǂݍ��񂾂��̂𐶐�
	static void LoadCreate2D(void);

	static CCollision * Create_Single(
		D3DXVECTOR3 pos,
		D3DXVECTOR3 size);// �I�u�W�F�N�g��ǂݍ��ݐ������鎞�ɐ���

	// �ݒ�
	void SetPos(D3DXVECTOR3 *pos);
	void SetSize(D3DXVECTOR3 size);
	void SetSize2D(D3DXVECTOR3 size);
	void SetMove(D3DXVECTOR3 *move);
	void SetType(OBJTYPE type);
	// �����蔻��
	bool Collision_Come(void);
	bool Collision_Player(void);
	static void Load(void);
	void Collision(void);

protected:

private:
	/* �֐� */
	static int TextLoad(void);
	// �����蔻��
	/* �ϐ� */
	static int m_nAll;					// ����
	static int m_nNumLoad;				// ���[�h��
	static INFO m_Info[COLLISION_MAX];	// ���
	int m_ID;							// �ԍ�
	OBJTYPE m_objtype;						// �^�C�v
	D3DXVECTOR3 *m_ppos;				// �ʒu���
	D3DXVECTOR3 m_posOld;				// �O��̈ʒu���
	D3DXVECTOR3 m_size;					// �T�C�Y���
	D3DXVECTOR3 *m_pmove;				// �ړ����
	static CCollision * m_pTop;			// �擪�I�u�W�F�N�g�ւ̃|�C���^
	static CCollision * m_pCur;			// ���݃I�u�W�F�N�g�ւ̃|�C���^
	CCollision * m_pNext;				// ���̃I�u�W�F�N�g�ւ̃|�C���^
	CCollision * m_pPrey;				// �O�̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeadFrag;					// �t���O
};

// ����������������������������������������������������������������������
//
// �v���g�^�C�v�錾
//
// ����������������������������������������������������������������������

#endif