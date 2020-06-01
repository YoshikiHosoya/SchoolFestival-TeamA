// ----------------------------------------
//
// �X�^�[�g�S�[�������̐���[startgoal.h]
// Author : Fujiwara Masato
//
// ----------------------------------------
#ifndef _STARTGOALPOINT_H_
#define _STARTGOALPOINT_H_	 // �t�@�C������������߂�

// ----------------------------------------
//
// �C���N���[�h�t�@�C��
//
// ----------------------------------------
#include "scene.h"

// ----------------------------------------
//
// �}�N����`
//
// ----------------------------------------


// ----------------------------------------
//
// �O���錾
//
// ----------------------------------------

// ------------------------------------------
//
// �N���X
//
// ------------------------------------------
class CStartGoal : public CScene
{
public:
	/* �񋓌^ */
	typedef enum
	{
		TYPE_START = 0,	// �X�^�[�g
		TYPE_GOAL,			// �S�[��
		TYPE_MAX
	} TYPE;

	/* �֐� */
	CStartGoal();
	~CStartGoal();
	void Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CStartGoal * Create(D3DXVECTOR3 pos , TYPE type);
protected:

private:
	/* �֐� */
	/* �ϐ� */
	D3DXVECTOR3					m_pos;			// �ʒu
	TYPE						m_type;			// ���
};

#endif